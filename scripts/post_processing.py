import sys
import glob
import os
import time

if(len(sys.argv) != 2):
    print("Error: exactly one argument is needed\n")

offset = time.time() - time.clock_gettime(time.CLOCK_MONOTONIC)
offset_seconds = int(offset)
offset_cycles = int((offset - offset_seconds) * 1000000000)

metadata_file = glob.glob(sys.argv[1] + "/metadata", recursive = True)[0]
metadata_f = open(metadata_file, "r")
list_of_lines = metadata_f.readlines()
list_of_lines[71] = "\toffset_s = " + str(offset_seconds) +";\n"
list_of_lines[72] = "\toffset = " + str(offset_cycles) +";\n"


metadata_f = open(metadata_file, "w")
metadata_f.writelines(list_of_lines)
metadata_f.close()