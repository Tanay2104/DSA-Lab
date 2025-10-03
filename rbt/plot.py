import matplotlib.pyplot as plt
import sys
import math
import numpy as np
n_rotations = []
with open("output.txt", 'r') as file:
    lines = file.readlines()
    for line in lines:
        n_rotations.append(int(line.strip()))

n = int(sys.argv[1])
x_values = np.arange(1, n + 1) 
y = []
for value in x_values:
    y.append(value - 2*math.log2(value))

plt.plot(n_rotations, label="number of rotations")
plt.plot(y, label="n - 2log(n)")
plt.legend()
plt.xlabel("Number of Elements Inserted")
plt.ylabel("Cumulative Number of Rotations")
plt.suptitle("Dependence of Rotations on Sorted Insertions in a Red-Black Tree", fontsize=12)
plt.title(f"Test for n = {n}", fontsize=10, loc='center')
plt.grid(True) # Add a grid to make it easier to read
plt.savefig("plot.png", bbox_inches="tight")
print(f"Plot saved to plot.png for n = {n}")

plt.clf()
error = []
for i in range(len(y)):
    error.append((abs(float(y[i] - x_values[i]))))
plt.plot(error, label="Error in estimate and actual")
plt.legend()
plt.xlabel("Number of Elements Inserted")
plt.ylabel("Error")

plt.suptitle("Dependence of Rotations on Sorted Insertions in a Red-Black Tree", fontsize=12)
plt.title(f"Test for n = {n}", fontsize=10, loc='center')
plt.grid(True) # Add a grid to make it easier to read
plt.savefig("plot_error.png", bbox_inches="tight")
print(f"Plot saved to plot_error.png for n = {n}")