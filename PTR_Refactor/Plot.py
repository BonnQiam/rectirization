import matplotlib.pyplot as plt

# Coordinates of the polygon

coordinates = [
    (79808, 342852),
    (79808, 342916),
    (79675, 342916),
    (79675, 342948),
    (79505, 342948),
    (79505, 342996),
    (79728, 342996),
    (79728, 343092),
    (79764, 343092),
    (79764, 343172),
    (79985, 343172), #! duplicate point
    (79985, 343156),
    (79797, 343156),
    (79797, 342932),
    (79985, 342932),
    (79985, 343172),
    (80037, 343172),
    (80037, 342916),
    (79814, 342916),
    (79814, 342852),
    (79808, 342852),
]

# for all coordinate in coordinates: x - 79500 and y - 342850
coordinates = [(x - 79500, y - 342850) for x, y in coordinates]
print(coordinates)

"""
coordinates = [
    (79385, 56692),
    (79385, 57236),
    (80174, 57236),
    (80174, 57132),
    (80105, 57132),
    (80105, 57196),
    (79917, 57196),
    (79917, 56796),
    (80237, 56796),
    (80237, 56788),
    (79934, 56788),
    (79934, 56692),
    (79385, 56692)
]
"""
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
