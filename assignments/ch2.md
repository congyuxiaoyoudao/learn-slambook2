1. 阅读文献 [1] 和 [14]，你能看懂其中的内容吗？

2. 阅读 SLAM 的综述文献，例如 [9, 15-18] 等。这些文献中关于 SLAM 的看法与本书有何异同？
    
3. g++ 命令有哪些参数？怎么填写参数可以更改生成的程序文件名？
    
    $\textcolor{orange}{Answer:}$ 运行 `g++ --help` 可以查看 `g++` 的命令文档，其中常用的参数有：
    - `-o <file>`：指定输出文件名
    - `-c`：指定编译器编译但不链接
    - `-L <directory>`：指定库文件
    - `-I <directory>`：指定头文件包含目录
    - `-shared`：创建一个共享库
    - `-std=<standard>`：指定编译时按照的 c++ 标准
    
    更改生成程序文件名只需运行以下命令：
    ```bash
    g++ main.cpp -o my_program
    ```

4. 使用 build 文件夹来编译你的 cmake 工程，然后在 KDevelop 中试试。

5. 刻意在代码中添加一些语法错误，看看编译会生成什么样的信息。你能看懂 g++ 的错误信息吗？

    $\textcolor{orange}{Answer:}$ 例如在 helloSLAM.cpp 中更改 `main` 函数：
    ```c++
    int main(int argc, char **argv) {
        cout << "[From helloSLAM.cpp]: Hello SLAM!" << endl;
        return 0;
        man what can i say // this line is error
    }
    ```
    运行 `g++ helloSLAM.cpp` 就会报错：
    ```bash
    helloSLAM.cpp: In function ‘int main(int, char**)’:
    helloSLAM.cpp:7:3: error: ‘man’ was not declared in this scope; did you mean ‘main’?
        7 |   man what can i say
          |   ^~~
          |   main
    ```

6. 如果忘了把库链接到可执行程序上，编译会报错吗？报什么样的错？
    
    $\textcolor{orange}{Answer:}$ 会，例如在 ch2 下的 CMakeLists.txt 中注释链接库 `target_link_libraries( useHello hello_shared )`，使用 cmake 编译会如下报错：

    ```bash
    /usr/bin/ld: CMakeFiles/useHello.dir/useHello.cpp.o: in function `main':
    /home/apeiria/learn-slambook2/slambook2/ch2/useHello.cpp:5: undefined reference to `printHello()'
    collect2: error: ld returned 1 exit status
    make[2]: *** [CMakeFiles/useHello.dir/build.make:84: useHello] Error 1
    make[1]: *** [CMakeFiles/Makefile2:84: CMakeFiles/useHello.dir/all] Error 2
    ```
    可以看到报错信息提示了代码中含有未定义的对 `printHello()` 的引用。

7. 阅读《cmake 实践》，了解 cmake 的其他语法。

8. 完善 Hello SLAM 小程序，把它做成一个小程序库，安装到本地硬盘中。然后，新建一个工程，使用 find_package 找这个库并调用。

9. 阅读其他 cmake 教学材料，例如 https://github.com/TheErk/CMake-tutorial。

10. 找到 KDevelop 的官方网站，看看它还有哪些特性。你都用上了吗？

11. 如果在第 1 讲学习了 Vim，那么请试试 KDevelop 的 Vim 编辑功能。