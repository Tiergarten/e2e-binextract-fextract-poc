from capstone import *

import sys
from hexdump import hexdump
import unittest

from fext_common import *

DEBUG = True
EXTRACTOR_NAME = 'ext-dump-ins'

class TestDecode(unittest.TestCase):
	def test_decode(self):
		allocate_stack_space = ["0x7ff768ea737f:4883ec28:EOL"]
		expected = '0x7ff768ea737f:\tsub\trsp, 0x28\n' 
		print "testing %s -> %s" % (allocate_stack_space, expected)
		instructions = dump_instructions(allocate_stack_space)
		self.assertEqual(instructions, expected)

def dump_instructions(ascii_lines):
	(bytestream, start_addr) = ascii_stream_to_hex(ascii_lines)

	md = Cs(CS_ARCH_X86, CS_MODE_64)
	d = md.disasm(bytestream, int(start_addr, 16))

	str_list = []
	for i in d:
		str_list.append("0x%x:\t%s\t%s\n" % (i.address, i.mnemonic, i.op_str))

	return ''.join(str_list)

def ascii_stream_to_hex(ascii_lines):
	start_addr = 0
	stream = ""

	print len(ascii_lines)

	for l in ascii_lines:

		if start_addr == 0:
			start_addr = l.split(':')[0]

		bytecode = l.split(':')[1]
		stream += bytecode.decode('hex')

	return (stream, start_addr)


if __name__ == '__main__':
	print dump_instructions(get_pintool_output(EXTRACTOR_NAME))