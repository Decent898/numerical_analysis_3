### 实验报告
#### 尝试
原计划使用python的manim库进行可视化求解过程，但是效果不佳，正在研究。
最终使用c语言实现。
#### 实验目标
本实验的目标是实现两种矩阵分解方法——高斯消元法和克劳特消元法。在程序中，实现了这两种消元方法来求解线性方程组。

#### 实验内容
使用两种不同的矩阵分解方法：
1. **高斯消元法**：通过将矩阵化为上三角矩阵后，使用回代法求解线性方程组。
2. **克劳特消元法**：将矩阵分解为上三角矩阵，后通过下式归一化，并通过回代法求解。

$$u_{ij} = \frac{u_{ij}}{l_{ii}}$$




#### 实验内容实现过程

##### 1. **程序结构**
定义了矩阵打印函数、两种消元法的实现函数（`gaussianSimplify` 和 `croutSimplify`），求解上三角矩阵的函数 `solve`。主程序输入方程组的阶数和矩阵值，选择消元法进行求解。

##### 2. **高斯消元法**
高斯消元法的核心思想是将矩阵逐步化为上三角矩阵，通过行操作消去下三角区域的元素。实现时，程序首先将主对角线上方的元素逐行消为0，然后通过回代法逐步解出线性方程组的解。

##### 3. **克劳特消元法**
将矩阵分解为上三角矩阵，在高斯消元法基础上后通过l系数归一化，并通过回代法求解。

##### 4. **求解过程**
`solve` 函数基于上三角矩阵的回代求解过程，从最后一个方程向前解出所有变量。

#### 输入与输出

##### 输入：
1. 方程组的阶数 `N`。
2. 增广矩阵的系数，每行系数以空格分隔。
3. 选择消元法：
   - 1：高斯消元法
   - 2：克劳特消元法

##### 输出：
1. 初始矩阵。
2. 上三角化简后矩阵 `U` 和下三角系数矩阵 `L`。
3. 线性方程组的解。

#### 实验样例

##### 输入：
```
1. 高斯消元法
2. 克劳特消元法
2
请输入方程组的阶数 N: 3
请输入增广矩阵的系数 (每行元素用空格分开):
2 3 4 6
3 5 2 5
4 3 30 32
```

##### 选择：
```
2. 克劳特消元法
```

##### 输出：
```
初始矩阵:
┌────────────────────────────────────────────────┬────────────────┐
│     2.00000000      3.00000000      4.00000000 │     6.00000000 │
├────────────────────────────────────────────────┼────────────────┤
│     3.00000000      5.00000000      2.00000000 │     5.00000000 │
├────────────────────────────────────────────────┼────────────────┤
│     4.00000000      3.00000000     30.00000000 │    32.00000000 │
└────────────────────────────────────────────────┴────────────────┘

上三角矩阵 U:
┌────────────────────────────────────────────────┬────────────────┐
│     1.00000000      1.50000000      2.00000000 │     3.00000000 │
├────────────────────────────────────────────────┼────────────────┤
│     0.00000000      1.00000000     -8.00000000 │    -8.00000000 │
├────────────────────────────────────────────────┼────────────────┤
│     0.00000000      0.00000000      1.00000000 │     2.00000000 │
└────────────────────────────────────────────────┴────────────────┘

下三角矩阵 L:
┌────────────────────────────────────────────────┬────────────────┐
│     2.00000000      0.00000000      0.00000000 │     0.00000000 │
├────────────────────────────────────────────────┼────────────────┤
│     3.00000000      0.50000000      0.00000000 │     0.00000000 │
├────────────────────────────────────────────────┼────────────────┤
│     4.00000000     -3.00000000     -2.00000000 │     0.00000000 │
└────────────────────────────────────────────────┴────────────────┘

求解结果:
x1 = -13.0000
x2 = 8.0000
x3 = 2.0000
```

#### 实验分析
1. **高斯消元法**：通过行消元，逐步将矩阵化为上三角形式，再通过回代法求出方程的解。此方法实现简单，但在上三角矩阵求解过程中运算量较大。
   
2. **克劳特消元法**：通过分解矩阵为下三角和上三角两个矩阵，再结合回代法求解。该方法相对高斯消元法具有更多的数值稳定性，但实现稍微复杂一些。

3. **0输入的问题**：这类方法最大缺陷是在对角线元素存在0时会出现$${u_{ij}} = \frac{0}{0}$$的情况，导致无法进行消元。

#### 实验结论
通过实验，成功实现了高斯消元法和克劳特消元法的编程实现，并通过输入不同的矩阵对这两种方法进行了求解验证。但实际情况下，主元素法和全主元法等改进算法可以避免0元素带来的问题，提高算法的稳定性。