from mpl_toolkits.mplot3d import Axes3d
import matplotlib.pyplot as plt

fig = plt.figure()
ax = fig.add_subplot(111, projection = "3d")

X = [0, 
0.0001,
0,
-0.0001,
-0.0002,
0,
0,
-0.0002,
-0.0004,
-0.0005,
-0.0008,
-0.0007]
Y = [0,
-0.0002,
-0.0004,
-0.0007,
-0.001,
-0.0011,
-0.0011,
-0.001,
-0.001,
-0.0009,
-0.0007,
-0.0008]
Z = [-4.7513,
-4.7516,
-4.7517,
-4.7517,
-4.7517,
-4.7518,
-4.7521,
-4.752,
-4.752,
-4.752,
-4.752,
-4.752]

ax.scatter(X, Y, Z, c='r', marker='o')
ax.set_xlabel('x axis')
ax.set_ylabel('y axis')
ax.set_zlabel('z axis')

plt.show()

