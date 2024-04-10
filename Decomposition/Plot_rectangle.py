import matplotlib.pyplot as plt

# 打开并读取文件
with open('Rectangle.txt', 'r') as file:
    lines = file.readlines()

# 创建一个空列表来存储矩形
rectangles = []

# 循环遍历每四行
for i in range(0, len(lines), 4):
    # 将四行的坐标转换为元组，并添加到矩形列表中
    rectangle = [tuple(map(int, line.strip().split(','))) for line in lines[i:i+4]]
    rectangles.append(rectangle)

# plot all rectangles
for rectangle in rectangles:
    x, y = zip(*rectangle)
    plt.plot(x, y, marker='^', color='blue')
    plt.fill(x, y, alpha=0.3)
    
plt.show()