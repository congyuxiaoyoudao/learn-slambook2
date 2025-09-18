1. 验证旋转矩阵是正交矩阵。

    $\textcolor{orange}{Answer:}$ 旋转矩阵表示一种刚体旋转，不改变向量模长和内积，所以有：

    $$
    (Rv)^T\cdot(Rw)=v^T\cdot w
    $$

    $$
    v^TR^TRw=v^T\cdot w
    $$

    $$
    R^TR=I
    $$

    所以 $R$ 是正交矩阵。

2. 寻找罗德里格斯公式的推导过程并加以理解。

    $\textcolor{orange}{Answer:}$ 对于一个向量 $\mathbf{v}$ 绕单位向量 $\mathbf{u}$ 旋转角度 $\theta$ 的问题，可以将向量 $\mathbf{v}$ 分解为平行和垂直 $\mathbf{u}$ 的分量：
    - $\mathbf{v}_{||}=(\mathbf{v}\cdot\mathbf{u})\mathbf{u}$
    - $\mathbf{v}_{\perp}=\mathbf{v}-\mathbf{v}_{||}$
    
    旋转过程中，平行分量保持不变，垂直分量在垂直于 $\mathbf{u}$ 的平面上旋转角度 $\theta$：
    $$
    \mathbf{v}_{\perp}'=\cos\theta\mathbf{v}_{\perp}+\sin\theta(\mathbf{u}\times\mathbf{v})
    $$
    代入 $\mathbf{v}_{\perp}$，整理后旋转后的向量 $\mathbf{v}'$ ：
    $$
    \mathbf{v}'=\cos\theta\mathbf{v}+(1-\cos\theta)(\mathbf{u}\cdot \mathbf{v})\mathbf{u}+\sin\theta(\mathbf{u}\times\mathbf{v})
    $$
    对于叉乘的部分，定义反对称矩阵 $\mathbf{u}^{\wedge}$：
    $$
    \mathbf{u}^{\wedge}=\begin{bmatrix}
    0 & -u_3 & u_2\\
    u_3 & 0 & -u_1\\
    -u_2 & u_1 & 0
    \end{bmatrix}
    $$
    使用 $\mathbf{u}^{\wedge}$ 与向量 $\mathbf{v}$ 相乘，相当于 $\mathbf{u}$ 与 $\mathbf{v}$ 进行叉乘。此外， $(\mathbf{u}\cdot\mathbf{v})\mathbf{u}=\mathbf{u}\mathbf{u}^T\mathbf{v}$，用这两个恒等式替换原表达式中的点乘和叉乘：
    $$
    \begin{aligned}
    \mathbf{v}'&=\cos\theta\mathbf{v}+(1-\cos\theta)\mathbf{u}\mathbf{u}^T\mathbf{v}+\sin\theta\mathbf{u}^{\wedge}\mathbf{v} \\
    &=(\cos\theta I+(1-\cos\theta)\mathbf{u}\mathbf{u}^T+\sin\theta\mathbf{u}^{\wedge})\mathbf{v}\\
    &=R\mathbf{v}
    \end{aligned}
    $$
    所以旋转矩阵 $R$ 为：
    $$
    R=\cos\theta I+(1-\cos\theta)\mathbf{u}\mathbf{u}^T+\sin\theta\mathbf{u}^{\wedge}
    $$

3. 验证四元数旋转某个点后，结果是一个虚四元数（实部为零），所以仍然对应到一个三维空间点，见式 (3.33)。

    $\textcolor{orange}{Answer:}$ 对于点 $p$，使用一个四元数对其进行旋转：
    $$
    p'=qpq^{-1}
    $$
    按照四元数乘法展开后的实部为：
    $$
    s_{p'}=-s_{q^{-1}}v_q^{T}v_p-s_qv_p^Tv_{q^{-1}}-(v_q\times v_p)^T\cdot v_{q^{-1}}
    $$
    由于 $q$ 是单位四元数，其逆等于转置，所以上式可以化简为：
    $$
    \begin{aligned}
    s_{p'}&=-s_{q}v_q^{T}v_p+s_qv_p^Tv_{q}+(v_q\times v_p)^T\cdot v_{q}\\
    &=s_q(v_p^Tv_{q}-v_q^{T}v_p)-(v_q\times v_p)^T\cdot v_{q}\\
    &=0
    \end{aligned}
    $$
    最后的等号是因为，左边都表示虚部的点积，右边两向量叉积乘点积恒为零，故均为零。

4. 画表总结旋转矩阵、轴角、欧拉角、四元数的转换关系。

    $\textcolor{orange}{Answer:}$

    | 旋转表达 | 优点 | 缺点 | 转换 |
    | ---------- | ----------------- | ---------------- |  ---------------- |
    | 旋转矩阵 |直接用于计算、没有奇异点 | 参数多（九个） | 罗德里格斯公式 |
    | 四元数 | 紧凑表达（只需要四个元素）、<br>容易插值 | 不够直观 | 定义四元数的矩阵乘法
    | 欧拉角 | 使用三个元素描述旋转、 <br> 表达直白易于人机交互 | 万向节死锁、插值困难、<br>旋转顺序影响结果 | 表示为轴角，进而转换为矩阵

5. 假设有一个大的 Eigen 矩阵，想把它左上角 3x3 的块取出来，然后赋值为 $I_{3\times 3}$。请编程实现。

    $\textcolor{orange}{Answer:}$ 见 ch3/useEigen/matrixExtractAssign.cpp

6. 一般线性方程 $Ax = b$ 有哪几种做法？你能在 Eigen 中实现吗？

    $\textcolor{orange}{Answer:}$ 
    
    1. 若 $A$ 有逆，则两边同时左乘 $A^{-1}$，$x=A^{-1}b$
    2. 高斯消元法，将 $A$ 逐步转化为上三角矩阵，回代求解
    3. LU 分解，将 $A=LU$，然后先解 $Ly=b$，再解 $Ux=y$
    4. Cholesky 分解，如果 $A$ 对称正定，将 $A=LL^T$