def pp_pin_output(output):
	ret = []
	for line in output:
		if line.startswith('#'):
			continue
		ret.append(line.rstrip())

	return ret

def get_pintool_output(extractor_name):
	fd = open('a%s.out' % (extractor_name), 'r')
	ret = pp_pin_output(fd.readlines())
	fd.close()

	return ret