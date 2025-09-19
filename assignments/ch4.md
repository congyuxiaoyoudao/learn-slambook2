1. 验证 SO(3)、SE(3) 和 Sim(3) 关于乘法成群。

    $\textcolor{orange}{Answer:}$ 封闭性和结合律显然成立，SO(3) 的单位元为 $I_3$，SE(3) 和 Sim(3) 的单位元均为 $I_4$；因为 SO(3) 正交，所以其逆等于转置，对于 Sim(3)，有 $S=\begin{bmatrix}
    sR & t \\
    0 & 1
    \end{bmatrix}$ 的逆元为 $S^{-1}=\begin{bmatrix}
    \frac{1}{s}R^{-1} & -\frac{1}{s}R^{-1}t \\
    0 & 1
    \end{bmatrix}$，SE(3) 为当 $s=1$ 的特殊情况。故 SO(3)、SE(3)、Sim(3) 均在乘法上构成群。

2. 验证 $(\mathbb{R}^3, \mathbb{R}, \times)$ 构成李代数。

    $\textcolor{orange}{Answer:}$ 依次证明其满足李代数的四个性质：

    - 封闭性：$\forall X,Y \in \mathbb{R}^3, [X,Y]=X\times Y\in \mathbb{R}^3$
    - 双线性：$\forall X,Y,Z\in\mathbb{R}^3,a,b\in\mathbb{R},$ 有
    $$
    \begin{aligned}
    [aX+bY,Z]&=(aX+bY)\times Z=aX\times Z+bY\times Z=a[X,Z]+b[Y,Z] \\
    [Z,aX+bY]&=Z\times(aX+bY)=aZ\times X+bZ\times Y=a[Z,X]+b[Z,Y]
    \end{aligned}
    $$
    - 自反性： $\forall X \in \mathbb{R}^3,[X,X]=0$
    - 雅可比等价： $\forall X,Y,Z \in \mathbb{R}^3$，有
    $$
    [X,[Y,Z]] + [Z,[X,Y]] + [Y,[Z,X]]
    = X \times (Y \times Z) + Z \times (X \times Y) + Y \times (Z \times X) = 0
    $$
    利用向量三重积恒等式，代入：
    $$
    A\times(B\times C)=B(A\cdot C)-C(A\cdot B)
    $$
    逐项相消，可证最终为 0。因此 $\mathfrak{g}=(\mathbb{R}^3,\mathbb{R},\times)$ 构成一个李代数。

3. 验证 $\mathfrak{so}(3)$ 和 $\mathfrak{se}(3)$ 满足李代数要求的性质。

    $\textcolor{orange}{Answer:}$ 先证 $\mathfrak{so}(3)$ 为李代数，对 $\forall \phi_1,\phi_2,\phi_3\in \mathbb{R}^3,\forall a,b\in \mathbb{R},\exist \phi'\in \mathbb{R}^3$，满足：
    - 封闭性：$[\phi_1,\phi_2]=(\mathbf{\Phi}_1\mathbf{\Phi}_2-\mathbf{\Phi}_2\mathbf{\Phi}_1)^{\vee}=\phi'$
    - 双线性：$[a\phi_1+b\phi_2,\phi_3]=((a\mathbf{\Phi_1}+b\mathbf{\Phi_2})\Phi_3-\Phi_3(a\mathbf{\Phi_1}+b\mathbf{\Phi_2}))^{\vee}=(a(\Phi_1\Phi_3-\Phi_3\Phi_1)+b(\Phi_2\Phi_3-\Phi_3\Phi_2))^{\vee}=a[\phi_1,\phi_3]+b[\phi_2,\phi_3]$，类似可证 $[\phi_3,a\phi_1+b\phi_2]=a[\phi_3,\phi_1]+b[\phi_3,\phi_2]$
    - 自反性：$[\phi_1,\phi_1]=(\mathbf{\Phi}_1\mathbf{\Phi}_1-\mathbf{\Phi}_1\mathbf{\Phi}_1)^{\vee}=0$
    - 雅可比等价：$[\phi_1,[\phi_2,\phi_3]]+[\phi_3,[\phi_1,\phi_2]]+[\phi_2,[\phi_3,\phi_1]]=\mathbf{0}^{\vee}=0$
    
    所以 $\mathfrak{so}(3)$ 为李代数，同理可证 $\mathfrak{se}(3)$ 也为李代数。

4. 验证性质 (4.20) 和 (4.21)。

    $\textcolor{orange}{Answer:}$ 先证式 (4.20)：
    $$
    a^\wedge a^\wedge=aa^T-I
    $$ 
    左右两侧分别进行矩阵乘法：
    $$
    \text{LHS}=\begin{bmatrix}
    -a_2^2-a_3^2 & a_1a_2 & a_1a_3 \\
    a_1a_2 & -a_1^2-a_3^2 & a_2a_3 \\
    a_1a_3 & a_2a_3 & -a_1^2-a_2^2
    \end{bmatrix},\;
    \text{RHS}=\begin{bmatrix}
    a_1^2 & a_1a_2 & a_1a_3 \\
    a_1a_2 & a_2^2 & a_2a_3 \\
    a_1a_3 & a_2a_3 & a_3^2
    \end{bmatrix}
    $$
    因为 $a$ 是单位向量，所以有 $a_1^2+a_2^2+a_3^2=1$，显然上面两式是相等的。

    再证式 (4.21)：
    $$
    a^\wedge a^\wedge a^\wedge=a^\wedge(aa^T-I)=-a^\wedge
    $$
    即证 $a^\wedge aa^T=0$，而：
    $$
    a^\wedge a=\begin{bmatrix}
    0 & -a_3 & a_2 \\
    a_3 & 0 & -a_1 \\
    -a_2 & a_1 & 0
    \end{bmatrix}\begin{bmatrix}
    a_1\\a_2\\a_3
    \end{bmatrix}=\mathbf{0}
    $$
    显然成立。

5. 证明：
    $$
    Rp^\wedge R^T = (Rp)^\wedge
    $$
    $\textcolor{orange}{Answer:}$ 将两边转化为各自的平方，等式仍然成立，即证：
    $$
    Rp^\wedge R^T Rp^\wedge R^T = (Rp)^\wedge (Rp)^\wedge
    $$
    等式左边：
    $$
    \begin{aligned}
    \text{LHS} &= Rp^\wedge R^T Rp^\wedge R^T\\
    &=Rp^\wedge p^\wedge R^T\\
    &=R(pp^T-I)R^T\\
    &=Rpp^TR^T-I\\
    &=(Rp)(Rp)^T-I\\
    &=p'p'^T-I\\
    &=(Rp)^{\wedge}(Rp)^{\wedge} = \text{RHS}
    \end{aligned}
    $$
    倒数第二步，记 $p'=Rp$ 为变换后的点，第二步和最后一步则利用性质 (4.20) 进行了代换。

6. 证明：
    $$
    R \exp(p^\wedge) R^T = \exp((Rp)^\wedge)
    $$
    该式称为 SO(3) 上的伴随性质。同样地，在 SE(3) 上也有伴随性质：
    $$
    T \exp(\xi^\wedge) T^{-1} = \exp((\text{Ad}(T)\xi)^\wedge) \tag{4.54}
    $$
    其中：
    $$
    \text{Ad}(T) = 
    \begin{bmatrix}
    R & t^\wedge R \\
    \mathbf{0} & R
    \end{bmatrix} \tag{4.55}
    $$
    $\textcolor{orange}{Answer:}$ 先证 SO(3) 上的伴随性质：
    $$
    \begin{aligned}
    R\exp(p^{\wedge})R^T&=R\sum_n^{\infin}\frac{(p^{\wedge})^n}{n!}R^T\\
    &=\sum_n^{\infin}\frac{R(p^{\wedge})^n R^T}{n!}\\
    &=\sum_n^{\infin}\frac{Rp^{\wedge}R^TRR^T\cdots Rp^{\wedge}R^T}{n!}\\
    &=\sum_n^{\infin}\frac{((Rp)^{\wedge})^n}{n!}=\exp((Rp)^{\wedge})
    \end{aligned}
    $$
    最后一行用到了性质 $Rp^{\wedge}R^T=(Rp)^{\wedge}$，可以两边同时作用一个向量证明。
    
    再证 SE(3) 上的伴随性质：
    $$
    \begin{aligned}
    T\exp(\xi^{\wedge})T^{-1}&=\begin{bmatrix}
    R & t\\
    \mathbf{0}^T & 1
    \end{bmatrix}
    \begin{bmatrix}
    R_{\phi} & J\rho\\
    \mathbf{0}^T & 1
    \end{bmatrix}
    \begin{bmatrix}
    R^T & -R^Tt\\
    \mathbf{0}^T & 1
    \end{bmatrix}\\
    &=\begin{bmatrix}
    RR_{\phi} & RJ\rho+t\\
    \mathbf{0}^T & 1
    \end{bmatrix}\begin{bmatrix}
    R^T & -R^Tt\\
    \mathbf{0}^T & 1
    \end{bmatrix}\\
    &=\begin{bmatrix}
    RR_{\phi}R^T & -RR_{\phi}R^Tt+RJ\rho +t\\
    \mathbf{0}^T & 1
    \end{bmatrix}
    \end{aligned}
    $$
    其也可以视作一个变换矩阵，我们期望其等于 $\exp((\text{Ad}(T)\xi)^\wedge)$ 的展开形式，令 $\xi'=\text{Ad}(T)\xi=[\rho',\phi']^T$，知道平移部分 $\rho'=R\rho+t^{\wedge}R\phi$，旋转部分 $\phi'=R\phi$，则有：
    $$
    \exp(\xi'^\wedge)=\begin{bmatrix}
    \exp(\phi'^\wedge) & J(\phi')\rho'\\
    \mathbf{0}^T & 1
    \end{bmatrix}
    $$
    接下来验证 $T\exp(\xi^{\wedge})T^{-1}$ 的展开形式：
    
    旋转部分为：
    $$
    RR_{\phi}R^T=R\exp(\phi^{\wedge})R^T=\exp((R\phi)^{\wedge})
    $$
    显然相等。
    
    接下来平移部分需要证明：
    $$
    -RR_{\phi}R^Tt+RJ\rho +t=J(\phi')\rho'
    $$
    展开右侧：
    $$
    \text{RHS}=J(R\phi)R\rho+J(R\phi)t^\wedge R\phi
    $$
    引入恒等式 $RJ(\phi)R^T=J(R\phi)$，可证 $J(R\phi)R\rho=RJ\rho$，引入恒等式 $\exp(\phi'^\wedge)=I+\phi'J(\phi')$ 可证 $J(R\phi)t^\wedge R\phi=-RR_{\phi}R^Tt+t$。

    SE(3) 上的伴随性质这样推导比较复杂，最好还是直接泰勒展开。

7. 仿照左扰动的推导，推导 SO(3) 和 SE(3) 在右扰动下的导数。
    
    $\textcolor{orange}{Answer:}$ 先推导 SO(3) 在右扰动下的导数：

    $$
    \begin{aligned}
    \frac{\partial(Rp)}{\varphi}&=\lim_{\varphi\to 0}\frac{\exp(\phi^{\wedge})\exp(\varphi^{\wedge})p-\exp(\phi^{\wedge})p}{\varphi}\\
    &=\lim_{\varphi\to 0}\frac{\exp(\phi^{\wedge})(I+\varphi^{\wedge})p-\exp(\phi^{\wedge})p}{\varphi}\\
    &=\lim_{\varphi \to 0}\frac{R\varphi^{\wedge}p}{\varphi}=\lim_{\varphi\to 0}\frac{-Rp^{\wedge}\varphi}{\varphi}=-Rp^{\wedge}
    \end{aligned}
    $$
    再推导 SE(3) 下的导数：

    $$
    \begin{aligned}
    \frac{\partial(Tp)}{\partial\delta\xi}&=\lim_{\delta\xi\to 0}\frac{\exp(\xi^{\wedge})\exp(\delta\xi^{\wedge})p-\exp(\xi^{\wedge})p}{\delta\xi}\\
    &=\lim_{\delta\xi\to 0}\frac{\exp(\xi^{\wedge})(I+\delta\xi^{\wedge})p-\exp(\xi^{\wedge})p}{\delta\xi}\\
    &=\lim_{\delta\xi\to 0}\frac{\exp(\xi^{\wedge})\delta\xi^{\wedge} p}{\delta\xi}\\
    &=\lim_{\delta\xi\to 0}\frac{\begin{bmatrix}
    R & \mathbb{t} \\
    \mathbf{0}^{T} & 1 
    \end{bmatrix}\begin{bmatrix}
    \delta\phi^{\wedge} & \delta \rho\\
    \mathbb{0} & 1
    \end{bmatrix}p
    }{\delta\xi}\\
    &=\lim_{\delta\xi\to 0}\frac{\begin{bmatrix}
    R\delta\phi^{\wedge}p+R\delta\rho\\
    \mathbb{0}^T
    \end{bmatrix}}{\begin{bmatrix}
    \delta\rho & \delta\phi 
    \end{bmatrix}^T}=\begin{bmatrix}
    R & -Rp^{\wedge} \\
    \mathbb{0}^T & \mathbb{0}^T
    \end{bmatrix}
    \end{aligned}
    $$

8. 搜索 cmake 的 find_package 指令是如何运作的。它有哪些可选的参数？为了让 cmake 找到某个库，需要哪些先决条件？

    $\textcolor{orange}{Answer:}$ find_package 的经典用法如下：
    ```cmake
    find_package(<PackageName> [<version>] [REQUIRED] [COMPONENTS <components>...])
    ```
    它查找一个通常在项目外的包，并加载其详细信息，详细介绍可参考 cmake 官方文档 [find_package](https://cmake.org/cmake/help/latest/command/find_package.html)。

    为了让 cmake 找到某个库，需要：
    - 系统上已正确安装该库
    - 该库的安装路径存在于 cmake 的搜索路径中
    - 库最好包含 cmake 配置文件 xxx-config.cmake
