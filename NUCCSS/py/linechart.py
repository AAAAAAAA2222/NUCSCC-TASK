import matplotlib.pyplot as plt
import pandas as pd

# 设置字体，确保支持中文
plt.rcParams['font.sans-serif'] = ['Microsoft Yahei']

# 读取Excel文件
df = pd.read_excel('python_data.xlsx')
print(df.head())

# 获取DataFrame的数值数据
data = df.values
print(data)

# 提取三列数据
y1 = data[:, 0:1]
y2 = data[:, 1:2]
y3 = data[:, 2:3]
print("y1\n", y1)
print("y2\n", y2)
print("y3\n", y3)

# 绘制折线图
plt.figure()
plt.plot(y1.flatten(), color='r', marker='+', label='bubble')
plt.plot(y2.flatten(), color='b', marker='o', label='heap')
plt.plot(y3.flatten(), color='g', marker='v', label='fibheap')

# 添加图例、标签和标题
plt.legend()
plt.xlabel('opt')
plt.ylabel('time/s')
plt.title('可视化数据')

# 保存图形为PNG文件
plt.savefig('visualization.png', dpi=300)  # 可以指定dpi以提高图像质量

# 显示图形
plt.show()


