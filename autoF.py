#!/usr/env/python

import os
import commands

path = "./2017concat"
pathF = "./2017concatF"
files = os.listdir(path)

for file in files:
    if '17' in file:
        cmd = 'python ./dFilter.py 2017concat/'+file+' > '+'2017concatF/'+file
        print(cmd)
        ret = commands.getoutput(cmd)
