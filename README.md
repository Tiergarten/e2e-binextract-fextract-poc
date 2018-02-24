# e2e-binextract-fextract

Proof of concept code to demonstrate the extraction of features from dynamic exectuion via Intel PinTool Dynamic Binary Instrumentation (DBI) for Machine Learning (ML).

The design has been split into two:
 - Agent Extractor - code which will be run in a sandbox and store raw data from the dynamic analysis of executables
 - Feature Extractor - code which translates the raw data from the agent extractors into feature sets suitable for training ML models

# Files 
- aext-dump-ins.cpp - PinTool to dump all instructions executed a executables 'main module' 
- fext_dump_ins.py - Script to decode this pin output, and turn it into readable assembly with the Python Capstone library

- aext-mem-rw-dump.cpp - PinTool to dump all memory read/writes by source and target address
- fext_mem_rw_dump.py - Script to decode this output, and turn it into a set of features used in the paper - M. Ozsoy, C. Donovick, I. Gorelik, N. Abu-Ghazaleh and D. Ponomarev, "Malware-aware processors: A framework for efficient online malware detection," 2015 IEEE 21st International Symposium on High Performance Computer Architecture (HPCA), Burlingame, CA, 2015, pp. 651-661.
doi: 10.1109/HPCA.2015.7056070

- e2e-binext-fext.sh - A runner script to compile, run, and capture output
- traceme.c - simple exe sample to be used for tracing
