1. 寻找一部相机（你的手机或笔记本的摄像头即可），标定它的内参。你可能会用到标定板，或者自己打印一张标定用的棋盘格。

    $\textcolor{orange}{Answer:}$ 没有设备 QAQ

2. 叙述相机内参的物理意义。如果一部相机的分辨率变为原来的两倍而其他地方不变，那么它的内参将如何变化？

    $\textcolor{orange}{Answer:}$ 相机内参组成内参矩阵，其将相机坐标系下的三维点变换到像素坐标系，相机内参完全由相机本身的光学性质决定，与相机位姿无关。相机的分辨率变为原来的两倍，而物理尺寸不变，则每个像素宽高变为原来的 1/2，缩放系数 $f_x,f_y$ 和平移 $c_x,c_y$ 均变为原来的两倍。

3. 搜索特殊相机（鱼眼或全景相机）的标定方法。它们与普通的针孔模型有何不同？

    $\textcolor{orange}{Answer:}$ [鱼眼相机模型](https://docs.opencv.org/4.x/db/d58/group__calib3d__fisheye.html) 通常使用等距投影的方法标定。鱼眼相机的 FOV 极大，因此会有很大的畸变，而针孔模型只允许较小的畸变。

4. 调研全局快门（global shutter）相机和卷帘快门（rolling shutter）相机的异同。它们在 SLAM 中有何优缺点？

    $\textcolor{orange}{Answer:}$ 全局快门和卷帘快门都是基于 CMOS（或更早的 CCD）传感器实现的，成像流程相同，只是像素的读出方式不同：

    - 全局快门：相机所有像素同时开始和结束曝光，整幅图像反映同一时刻的物体信息。如果曝光时间过长，可能会产生模糊和噪声，并且硬件成本较高，帧率较低
    - 卷帘快门：相机逐行（逐列）依次开始曝光，不同像素之间存在时间差，可能会导致畸变，且难以拍摄高速运动的物体

5. RGB-D 相机是如何标定的？以 Kinect 为例，需要标定哪些参数？（参照 [https://github.com/code-iai/iai_kinect2](https://github.com/code-iai/iai_kinect2)）

    $\textcolor{orange}{Answer:}$ 需要分别标定 RGB 相机和 Depth 相机的内参以及两个相机之间的刚性变换，标定 RGB 相机和标定 Depth 相机的方法与普通针孔相机一致，可采用张正友标定法。标定 RGB 和 Depth 相机的变换需要求解两个相机变换的外参 $R,t$。
    
    Kinect 需要标定的参数有：
    - RGB 相机的焦距、主点坐标、径向畸变参数和切向畸变参数
    - Depth 相机的焦距、主点坐标、径向畸变参数和切向畸变参数
    - RGB 相机和 Depth 相机之间的变换矩阵

6. 除了示例程序演示的遍历图像的方式，你还能举出哪些遍历图像的方法？
   
    $\textcolor{orange}{Answer:}$ 迭代器、`cv::Mat::data`，详见 ch5/imageBasics.cpp。

7. 阅读 OpenCV 官方教程，学习它的基本用法。

    $\textcolor{orange}{Answer:}$ [OpenCV tutorials](https://docs.opencv.org/4.x/d9/df8/tutorial_root.html)