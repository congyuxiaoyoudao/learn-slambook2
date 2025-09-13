1. 有线性方程 $Ax = b$，若已知 $A, b$，需要求解 $x$。该如何求解？这对 $A$ 和 $b$ 有哪些要求？  
   提示：从 $A$ 的维度和秩角度来分析。

    $\textcolor{orange}{Answer:}$ 可以将 $A$ 想象为一个映射，其列向量可以组成其映射后空间的一组基（不一定是标准正交基）。若 $A$ 满秩，则映射后的维度和原来的维度相同，该方程总有唯一解。反之，若 $A$ 不满秩，则分两种情况讨论，如果 $b$ 落在 $A$ 的列空间（列向量长成的空间）内，则有无限多解；反之则无解。

2. 高斯分布是什么？它的一维形式是怎么样？它的高维形式是什么样子？

    $\textcolor{orange}{Answer:}$ 高斯分布是一种在统计和机器学习中最常见的连续型概率分布，其一维形式的概率密度函数为 $p(x)=\frac{1}{\sqrt{2\pi\sigma^2}}\exp\left(-\frac{(x-\mu)^2}{2\sigma^2}\right)$，呈一个钟形曲线形状。高斯分布的高维形式其变量为一个 $n$ 维向量 $\mathbf{v}$，其概率密度函数为 $p(\mathbf{v}) = \frac{1}{(2\pi)^{n/2} |\Sigma|^{1/2}} \exp\left(-\frac{1}{2}(\mathbf{x} - \boldsymbol{\mu})^T \Sigma^{-1} (\mathbf{x} - \boldsymbol{\mu})\right)$。其中 $\Sigma$ 为每个维度变量间的协方差矩阵。

3. 你知道 C++ 的**类**吗？你知道 STL 吗？你使用过它们吗？

    $\textcolor{orange}{Answer:}$ C++ 相对于 C 的一个重要优势就是引入了类（class）的概念，从面向过程转到面向对象，支持封装、继承、多态以及模板编程的特性，大大提升开发效率。STL（**S**tandard **T**emplate **L**ibrary）即标准模板库，提供了一整套基于模板的数据结构和算法，经常使用的容器有 `vector`，`queue`，`map`，使用的算法有 `sort`。

4. 你以前怎样书写 C++ 程序？（你完全可以说只是 Visual C++ 6.0 下写过 C++ 工程，只要你有写 C++ 和 C 语言的经验就行。）

    $\textcolor{orange}{Answer:}$ 用 VisualStudio，VSCode 等 IDE/代码编辑器。

5. 你知道 C++11 标准吗？你听说过或用过其中哪些新特性？有没有其他的标准？

    $\textcolor{orange}{Answer:}$ `auto` 自动类型推导、lambda 表达式和 `std::function`、智能指针等。

    其它的标准如 C++14，C++17，C++20，C++23，C++26（试验中）。

6. 你知道 Linux 吗？你有没有至少使用过一种（不算安卓）操作系统，比如 Ubuntu？

    $\textcolor{orange}{Answer:}$ Linux 是由 Linus Torvalds 开发的一个开源的类 Unix 的操作系统，拥有多个发行版和活跃的社区支持。

    使用过的操作系统有 Ubuntu, CentOS, MacOS, Windows。

7. Linux 的目录结构是什么样的？你知道哪些基本命令，比如 ls、cat 等？

    $\textcolor{orange}{Answer:}$ 树型结构，但不像 Windows 那样硬盘分区。根目录为 `/`，其下有子目录如 `root`，`home`，`bin` 等，用户目录在 `home/` 的用户名文件夹下，也可以写为 `~`。
    
    常见的 Linux 命令有 `cd`（修改当前目录），`ls`（列出当前目录下所有文件），`cat`（显示指定文件内容），`rm`（移除指定文件或目录），`mkdir`（新建目录） 等。

    ~~如果你是 Linux 萌新，也许听说过 `sudo rm -rf /*` 这条命令，千万不要去试.jpg~~

8. 如何在 Ubuntu 系统中安装软件（不打开软件中心的情况下）？这些软件被安装在什么地方？如果只知道模糊的软件名称（比如想要装一个名称中含有 Eigen 的库），应该如何安装它？

    $\textcolor{orange}{Answer:}$ 使用命令 `sudo apt install`，这些软件通常被安装在 `/usr/bin/` 中。如果只知道模糊的软件名称，可以使用命令 `apt search` 模糊查找含有任意关键字的包名称，例如 `apt search eigen`。

9. 花一个小时学习 Vim，因为你迟早会用它。你可以在终端中输入 `vimtutor` 阅读一遍所有内容。我们不需要你非常熟练地操作它，只要能够在学习本书的过程中使用它输入代码即可。**不要在它的插件上浪费时间，不要想着把 Vim 用成 IDE，我们只用它做文本编辑的工作。**