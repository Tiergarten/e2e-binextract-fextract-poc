# e2e-binextract-fextract

- aext-dump-ins.cpp - A Intel PinTool 'Pin' to dump all instructions executed within the .text section of a PE binary
- fext-dump-ins.py - A python script to decode the pin output, and turn it into readable assembly with the Capstone library
- e2e-binext-fext.sh - A runner script to compile, run, and capture output
- traceme.c - simple exe sample to be used for tracing
