#!/usr/bin/env python3

import sys
import subprocess

def main(argc, argv):
	for i in range(0, int(sys.argv[2])):
		cmd = 'povray '
		cmd += argv[1]
		cmd = cmd % i
		subprocess.call(cmd, shell=True)

if __name__ == '__main__':
	argc = len(sys.argv)
	argv = sys.argv
	main(argc, argv)

