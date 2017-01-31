import serial
import os
import time
import sys
from msvcrt import getch
import msvcrt

#the arduino
ser = serial.Serial('COM3', 9600)

results = []

for x in range((150-20)/5+1):
    results.append([])


print "Waiting on key press"
getch()

#read and save Vout and distance of the Sharp IR using the arduino
while True:
    val = str(ser.readline()).split()
    if len(val) == 2:
        dis, volt = val
        
    
        if int(dis) > 19 and int(dis) < 151 and int(dis) % 5 is 0:
            results[(int(dis) / 5 - 4)].append(volt)        
        
        count = []
        for x in range((150-20)/5+1):
            count.append([20+(x*5),len(results[x])])

        os.system('cls')
        print "Distance: " + str(dis),
        print "Volt: " + str(volt),
        print count
    

    if msvcrt.kbhit():
        if str(msvcrt.getch()) is 'c':
            break

print "\n Average:"

#calculate average values
average = []
tmp = 0.00
for x in range((150-20)/5+1):
    tmp = 0.00
    
    if len(results[x]) > 0:
        for y in range(len(results[x])):
            tmp += float(results[x][y])
        average.append([20+(x*5),tmp/len(results[x])])
    else:
        average.append([20+(x*5),0])


print average

#write average values to file
f = open("results.txt", 'w')
f.write(str(average))
f.close()