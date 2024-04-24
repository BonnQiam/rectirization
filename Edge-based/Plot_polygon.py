"""
according Polygon.txt ploy polygon
"""
import matplotlib.pyplot as plt

# 读取文件
#with open('Polygon.txt', 'r') as file:
#with open('Edge_1.txt', 'r') as file:
with open('Edge.txt', 'r') as file:
    lines = file.readlines()

edges = []
for line in lines:
    # 分割每一行并转换为坐标点
    point1, point2 = line.strip().split(') (')
    point1 = tuple(map(int, point1[1:].split(', ')))
    point2 = tuple(map(int, point2[:-1].split(', ')))
    edges.append((point1, point2))
    
# 绘制多边形
fig, ax = plt.subplots()
for edge in edges:
    ax.plot([edge[0][0], edge[1][0]], [edge[0][1], edge[1][1]], color='black')

# collect all points
points = []
for edge in edges:
    points.append(edge[0])
    points.append(edge[1])
# plot all points
for point in points:
    ax.plot(point[0], point[1], 'ro')

plt.show()