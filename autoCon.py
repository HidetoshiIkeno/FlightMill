#!/usr/env/python

import os
import commands

fp = open('expDate.dat')
date = fp.read()
fp.close()

lines = date.split('\n')
for line in lines:
    if '1' in line:
        cmd = './concat3-LJ 1 '+line+' > 2017concat/'+line+'A.csv'
        print cmd
        ret = commands.getoutput(cmd)
        cmd = './concat3-LJ 2 '+line+' > 2017concat/'+line+'B.csv'
        print cmd
        ret = commands.getoutput(cmd)
        cmd = './concat3-LJ 3 '+line+' > 2017concat/'+line+'C.csv'
        print cmd
        ret = commands.getoutput(cmd)

