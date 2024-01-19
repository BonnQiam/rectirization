import matplotlib.pyplot as plt

rectangle_1 = [
(308, 2),
(314, 2),
(314, 66),
(308, 66),
(308, 2)
]

rectangle_2 = [
(175, 66),
(308, 66),
(308, 82),
(175, 82),
(175, 66)
]

rectangle_3 = [
(308, 66),
(537, 66),
(537, 82),
(308, 82),
(308, 66)
]

rectangle_4 = [
(175, 82),
(297, 82),
(297, 98),
(175, 98),
(175, 82)
]

rectangle_5 = [
(485, 82),
(537, 82),
(537, 306),
(485, 306),
(485, 82)
]

rectangle_6 = [
(5, 98),
(175, 98),
(175, 146),
(5, 146),
(5, 98)
]

rectangle_7 = [
(175, 98),
(297, 98),
(297, 146),
(175, 146),
(175, 98)
]

rectangle_8 = [
(228, 146),
(297, 146),
(297, 242),
(228, 242),
(228, 146)
]

rectangle_9 = [
(264, 242),
(297, 242),
(297, 322),
(264, 322),
(264, 242)
]

rectangle_10 = [
(297, 306),
(485, 306),
(485, 322),
(297, 322),
(297, 306)
]

rectangle_11 = [
(485, 306),
(537, 306),
(537, 322),
(485, 322),
(485, 306)
]

# plot all rectangles
for rectangle in [rectangle_1, rectangle_2, rectangle_3, rectangle_4, rectangle_5, rectangle_6, rectangle_7, rectangle_8, rectangle_9, rectangle_10, rectangle_11]:
    x, y = zip(*rectangle)
    plt.plot(x, y, marker='^', color='blue')
    plt.fill(x, y, alpha=0.3)
    
plt.show()