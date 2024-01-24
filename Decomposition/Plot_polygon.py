import matplotlib.pyplot as plt

# Coordinates of the polygon

coordinates = [
(308, 2),
(308, 66),
(175, 66),
(175, 98),
(5, 98),
(5, 146),
(228, 146),
(228, 242),
(264, 242),
(264, 322),
(485, 322),
(485, 306),
(297, 306),
(297, 82),
(485, 82),
(485, 322),
(537, 322),
(537, 66),
(314, 66),
(314, 2),
(314, 66),
(308, 66),
(308, 2)
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