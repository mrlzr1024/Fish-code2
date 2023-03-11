# '''
# 截取屏幕保存为png
# '''
# # import pyautogui
# #
# # img = pyautogui.screenshot()
# # img.save("a.png")
#
# '''
# 图片转换为字节流
# '''
# import pyautogui
# from io import BytesIO
#
# img = pyautogui.screenshot()
#
# output_buffer = BytesIO()  # 建立二进制对象
#
# img.save(output_buffer, format='PNG', quality=100)  # quality提高图片分辨率
#
# frame = output_buffer.getvalue()  # 获取二进制数据
#
# print(frame)
import random
import matplotlib.pyplot as plt
print("ok")
plt.rcParams['font.sans-serif'] = ['SimHei']  # 步骤一（替换sans-serif字体）
plt.rcParams['axes.unicode_minus'] = False


class PSO(object):
    def __init__(self):
        self.x_bound = [-1, 1]
        self.T = 100
        self.w = 0.15
        self.N = 10000
        self.dim = 20
        self.c1 = 1.5
        self.c2 = 1.5

    def fun(self, x):
        result = 0
        for i in x:
            result = result + pow(i, 2)
        return result

    def pso_main(self):
        x = []
        v = []
        for j in range(self.N):
            x.append([random.random() for i in range(self.dim)])
            v.append([random.random() for m in range(self.dim)])
        fitness = [self.fun(x[j]) for j in range(self.N)]
        p = x
        best = min(fitness)
        pg = x[fitness.index(min(fitness))]
        best_all = []
        for t in range(self.T):
            for j in range(self.N):
                for m in range(self.dim):
                    v[j][m] = self.w * v[j][m] + self.c1 * random.random() * (
                            p[j][m] - x[j][m]) + self.c2 * random.random() * (pg[m] - x[j][m])
            for j in range(self.N):
                for m in range(self.dim):
                    x[j][m] = x[j][m] + v[j][m]
                    if x[j][m] > self.x_bound[1]:
                        x[j][m] = self.x_bound[1]
                    if x[j][m] < self.x_bound[0]:
                        x[j][m] = self.x_bound[0]
            fitness_ = []
            for j in range(self.N):
                fitness_.append(self.fun(x[j]))
            if min(fitness_) < best:
                pg = x[fitness_.index(min(fitness_))]
                best = min(fitness_)
            best_all.append(best)
            print('第' + str(t) + '次迭代：最优解位置在' + str(pg) + '，最优解的适应度值为：' + str(best))
        plt.plot([t for t in range(self.T)], best_all)
        plt.ylabel('适应度值')
        plt.xlabel('迭代次数')
        plt.title('粒子群适应度趋势')
        plt.show()