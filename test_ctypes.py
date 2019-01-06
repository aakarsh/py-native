#!/usr/bin/env python

import re
import ctypes
import os
import locale
import mmap
import itertools

from functools import * 

_lib_file="libunix.so"
_path = os.path.join(*(os.path.split(__file__)[:-1] + (_lib_file,)))
_mod = ctypes.cdll.LoadLibrary(_path)

multiply = _mod.multiply
multiply.args_type = (ctypes.c_int, ctypes.c_int)
multiply.agrs_type = ctypes.c_int

def file_lines(f):
	with open(f,"r") as f: 
		try: 
			while True: yield next(f).strip()
		except StopIteration: pass	

def match_lines(regex, lines):
	m = re.compile(regex)
	for line in lines:
		if m.match(line): 
			yield line

def sep_by(f, from_sep , to_sep):
	max_field_widths = []
	with open(f, "r") as f:
		lines = []
		for line in f:
			line  = line.strip()
			fields = line.split(from_sep)
			field_widths = map(len, fields)
			if len(max_field_widths) == 0 :
				max_field_widths = [0] * len(field_widths)
			max_field_widths = map(lambda t: max(t[0], t[1]),zip(field_widths,max_field_widths))
			lines.append(fields)
		fmt_string =""
		for mw in max_field_widths:
			fmt_string+= "%"+str(mw)+"s"+to_sep
			
		for line in lines:
			yield fmt_string % tuple(line)

def write_lines(lines,f):
	with open(f,"w") as f:
		for line in lines:
			f.write(line)
			f.write("\n")

def dir_tree(dir_name, depth=1,max_depth = 3):
	names = os.listdir(dir_name)	
	print (" "*depth)+"+"+os.path.basename(dir_name)
	for name in sorted(names):
		file_path = os.path.join(dir_name,name)
		if os.path.isdir(file_path) and depth < max_depth:
			dir_tree(file_path, depth+1)
		else:
			print (" "*depth)+" - "+name

if __name__ == "__main__":
	sorted_list  = sorted(list(sep_by("/etc/passwd", ":", "\t")),key= cmp_to_key(locale.strcoll), reverse=True)
	for s in sorted_list:
		print s
	dir_tree(os.path.expanduser("~"))#os.path.dirname(__file__)))
	print list(match_lines(".*aakarsh.*",file_lines("/etc/passwd")))
