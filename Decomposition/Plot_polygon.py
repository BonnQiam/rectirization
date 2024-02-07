import matplotlib.pyplot as plt

# Coordinates of the polygon

coordinates = [
(0, 350000),
(0, 400000),
(1014, 400000),
(1014, 350000),
(1014, 400000),
(0, 400000),
(0, 350000)
]

# Identify duplicate points
seen = set()
duplicates = set(x for x in coordinates if x in seen or seen.add(x))

print(duplicates)

# Unzip the coordinates
x, y = zip(*coordinates)

# Plot the polygon with duplicates in red
plt.plot(x, y, marker='^', color='blue')
#plt.plot(x, y, color='blue')
plt.scatter(*zip(*duplicates), color='red')  # Mark duplicate points in red
#plt.fill(x, y, alpha=0.3)  # Fill the polygon

# Set labels and title
plt.xlabel('X Coordinate')
plt.ylabel('Y Coordinate')
plt.title('Polygon Plot')

# Display the plot
plt.show()