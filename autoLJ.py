#!/usr/env/python

#!/usr/env/python

import os
import commands

path = "./2017data"
files = os.listdir(path)

for file in files:
    if 'kash' in file:
        output = file.replace('.csv', 'A.csv')
        cmd = './dA3-LJnew 1 2017data/'+file+' 1 > '+'2017output/'+output
        print(cmd)
        ret = commands.getoutput(cmd)

        output = file.replace('.csv', 'B.csv')
        cmd = './dA3-LJnew 2 2017data/'+file+' 1 > '+'2017output/'+output
        print(cmd)
        ret = commands.getoutput(cmd)
        
        output = file.replace('.csv', 'C.csv')
        cmd = './dA3-LJnew 3 2017data/'+file+' 1 > '+'2017output/'+output
        print(cmd)
        ret = commands.getoutput(cmd)
