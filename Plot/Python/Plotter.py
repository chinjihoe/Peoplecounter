import matplotlib.pyplot as plt
import ast

#open file with average values
f = open("./results/results_average.txt", 'r')
val = ast.literal_eval(str(f.read()))
f.close()

average = [val[3],val[3]]

for x in xrange(3,len(val),2):
    average.append((val[x]))

xAxis = []
for x in range(16):
    xAxis.append(0+10*x)

#Plot graph
plt.plot(xAxis, average, 'k-',xAxis, average, 'ko')
plt.plot([20,20],[0,3], 'r-')
plt.plot([70,70],[0,3], 'r-')

#Extra design settings
plt.axvspan(0, 20, facecolor='r', alpha=0.3)
plt.axvspan(70, 150, facecolor='r', alpha=0.3)

plt.xlim(0,150)
plt.xticks(xAxis)
plt.grid(True)
plt.ylabel('Output voltage(V)')
plt.xlabel('Distance to reflective object(cm)')
plt.show()
