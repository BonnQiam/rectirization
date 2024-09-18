import matplotlib.pyplot as plt

# 读取文件并解析顶点数据
vertices = []
with open('Input.txt', 'r') as file:
    for line in file:
        x, y = map(int, line.strip().split(','))
        vertices.append((x, y))

# 分离x和y坐标
x_coords, y_coords = zip(*vertices)

# 添加第一个顶点到最后以闭合多边形
x_coords += (x_coords[0],)
y_coords += (y_coords[0],)

# 绘制多边形
plt.figure()
plt.plot(x_coords, y_coords, marker='o')
plt.title('Polygon from Vertices')
plt.xlabel('X')
plt.ylabel('Y')
plt.grid(True)
plt.show()