#!/usr/bin/python
# coding: UTF-8

import sys

#IN_DIR = './2017concat/'
R = 39.;

argvs = sys.argv
argc = len(argvs)

print 'time, number, all_points, high_points, duration, speed, distance, ratio'
f = open(argvs[1])
line = f.readline()
count = 1

high0 = 0
all0 = 0
while line:
    line = line.replace('\n','')
    line = line.replace('\r','')
    data = line.split(',')

    high = int(data[3])
    all = int(data[2])
    ratio = float(high)/float(all)*100.

    data.append(" "+str(ratio))
    if high >= 4:
        dist = 2. * 3.1415927 * R * float(count)
        highP = high + high0
        allP = all + all0
        ratioP = float(highP)/float(allP)*100.
        data[1] = " "+str(count)
        data[2] = " "+str(allP)
        data[3] = " "+str(highP)
        data[6] = " "+str(dist)
        data[7] = " "+str(ratioP)
        if ratioP >= 3. and ratioP <= 7.:
            print ','.join(data)
        high0 = 0
        all0 = 0
        count = count+1
    else:
        high0 = high
        all0 = all
    line = f.readline()
f.close


