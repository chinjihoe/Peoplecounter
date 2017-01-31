import matplotlib.pyplot as plt
import ast

#open files of the 2 measurements
#each measurements consisted of 50 samples
f1 = open("./results/results0.txt", 'r')
f2 = open("./results/results1.txt", 'r')

#string to array
val1 = ast.literal_eval(str(f1.read()))
val2 = ast.literal_eval(str(f2.read()))

f1.close()
f2.close()

#calculate average of the first value
first = (val1[0][1] + val2[0][1])/2
average = [first,first,first] #distances 5, 10 and 15cm have the same values 

#calculate the average of the remaining values
for x in range(len(val1)):
    average.append((val1[x][1] + val2[x][1])/2)

print average

#write averages to new file
f3 = open("./results/results_average.txt",'w')
f3.write(str(average))
f3.close()