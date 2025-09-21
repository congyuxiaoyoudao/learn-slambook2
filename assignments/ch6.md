1. 证明线性方程 $Ax=b$ 当系数矩阵 $A$ 超定时，最小二乘解为 $x = (A^TA)^{-1}A^Tb$。

    $\textcolor{orange}{Answer:}$ 系数矩阵超定时，即矩阵行数大于列数 $m>n$ 时，线性方程组通常没有严格解，此时可以求最小二乘得到近似解：
    $$
    \min_{x}||Ax-b||_2^2
    $$
    定义目标函数为残差项的平方和并展开：
    $$
    \begin{aligned}
    S(x)&=||Ax-b||_2^2=(Ax-b)^T(Ax-b)\\
    &=(x^TA^T-b^T)(Ax-b)\\
    &=x^TA^TAx-x^TA^Tb-b^TAx+b^Tb\\
    &=x^T(A^TA)x-2b^TAx+b^Tb
    \end{aligned}
    $$
    目标函数对 $x$ 求梯度并令其为零：
    $$
    \nabla S(x)=2A^TAx-2(b^TA)^{T}=0
    $$
    即求解 $A^TAx=A^Tb$，若 $A$ 可逆，则最小二乘解为 $x=(A^TA)^{-1}A^Tb$。

2. 调研最速下降法、牛顿法、高斯牛顿法和列文伯格——马夸尔特方法各有什么优缺点？除了我们举的 Ceres 库和 g2o 库，还有哪些常用的优化库？(你可能会找到一些 MATLAB 上的库。)

    $\textcolor{orange}{Answer:}$ 优缺点如下：
    | 优化方法 | 优点 | 缺点 |
    | -- | -- | -- |
    | 最速下降法 |实现简单、计算开销小 | 收敛速度较慢（在狭长山谷区域可能出现 zig-zag 路径） |
    | 牛顿法 | 目标函数接近二次时，局部收敛快 | 需要 Hessian 矩阵、更新方向不一定下降 |
    | 高斯牛顿法 | 避免显式 Hessian、计算高效 | 对初始值敏感、$JJ^T$ 可能奇异或病态导致无法收敛 |
    | 列文伯格——马夸尔特法 | 在高斯牛顿法上增加了阻尼项、综合最速下降和高斯牛顿法的优点、鲁棒性强 | 对参数 $\lambda$ 敏感、计算开销比高斯牛顿法大 |

    其它常用的优化库有：GSL, PETSc/TAO, NLopt, IPOPT

3. 为什么高斯牛顿法的增量方程系数矩阵可能不正定？不正定有什么几何含义？为什么在这种情况下求解就不稳定了？

    $\textcolor{orange}{Answer:}$ 增量方程系数矩阵 $H=J(x)J^T(x)$，$J(x)$ 是 $f(x)$ 关于 $x$ 的导数，$\forall v$：
    $$
    v^TJJ^Tv=(J^Tv)^T(J^Tv)=||J^Tv||_2^2\,\geq 0
    $$
    所以 $JJ^T$ 总是半正定的，这意味着在某些情况下会出现 0 特征值。几何层面上，$JJ^T$ 用于近似目标函数在参数空间里的局部曲率，不正定性表示目标函数局部梯度可能为 0，这会导致优化方向不唯一，在解 $\Delta x=H^{-1}g$ 时，小的数值误差会被放大，导致求解不稳定（在局部左右跳动）。

4. DogLeg 是什么？它与高斯牛顿法和列文伯格——马夸尔特方法有何异同？请搜索相关的材料，例如，http://www.numerical.rl.ac.uk/people/ning/course/lectures/raphael/lectures/lec7slides.pdf。

    $\textcolor{orange}{Answer:}$ DogLeg 是一种二阶梯度法，为了解决高斯牛顿法使用 $JJ^T$ 近似 Hessian 产生的问题。它结合高斯牛顿法与最速下降法，通过定义信赖域衡量近似可行的范围，既保证了稳定性，又兼顾了收敛速度。其核心步骤如下：
    - 求解高斯牛顿法的迭代步长 $\Delta x_{GN}=H^{-1}g$
    - 求解最速下降法的迭代步长 $\Delta x_{SD}=-\lambda J$
    - 根据 $\Delta x_{GN},\Delta x_{SD}$ 相对于当前信赖域半径 $\mu$ 确定 DogLeg 更新步长 $\Delta x_{DL}$
    - 使用 $\Delta x_{DL}$ 作为更新步长，并计算 $\rho$（和 L-M 方法相同），然后根据 $\rho$ 的值判断是否执行本次更新，并更新信赖域半径
    
    DogLeg 方法在高斯牛顿法的基础上增加了最速下降法的更新方向的计算，最终更新的方向在这两个方向之间选择，在高斯牛顿法不可行时转而使用最速下降法更新，保证解的稳定；DogLeg 方法和 L-M 方法都是信赖域方法，通过定义信赖域确定近似的有效性，但 L-M 方法通过增加一个阻尼项 $\lambda I$ 调整更新，而 DogLeg 方法则通过在高斯牛顿法-最速下降法间选择路径调整更新。

5. 阅读 Ceres 的教学材料 (http://ceres-solver.org/tutorial.html) 以更好地掌握其用法。

6. 阅读 g2o 自带的文档，你能看懂它吗？如果还不能完全看懂，请在阅读第 10 讲和第 11 讲之后再回来看。

7. 请更改曲线拟合实验中的曲线模型，并用 Ceres 和 g2o 进行优化实验。例如，可以使用更多的参数和更复杂的模型。

    $\textcolor{orange}{Answer:}$ 将拟合曲线模型更改为 $y=a*\exp^{bx}+c*\sin(dx+e)+fx$，实现过程详见 ceresCurveFitting.cpp 和 g2oCurveFitting.cpp。