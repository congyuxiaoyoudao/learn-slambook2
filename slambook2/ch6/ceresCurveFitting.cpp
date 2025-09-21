//
// Created by xiang on 18-11-19.
//

#include <iostream>
#include <opencv2/core/core.hpp>
#include <ceres/ceres.h>
#include <chrono>

using namespace std;

// 代价函数的计算模型
struct CURVE_FITTING_COST {
  CURVE_FITTING_COST(double x, double y) : _x(x), _y(y) {}

  // 残差的计算
  template<typename T>
  bool operator()(
    const T *const abc, // 模型参数，有3维
    T *residual) const {
    residual[0] = T(_y) - ceres::exp(abc[0] * T(_x) * T(_x) + abc[1] * T(_x) + abc[2]); // y-exp(ax^2+bx+c)
    return true;
  }

  const double _x, _y;    // x,y数据
};

// Another curve fitting cost function
// y=ae^{bx}+csin(dx+e)+fx
// so here this function is a strongly non-linear function,
// if initialized badly, the solution may not converge,
// or you may see it need more iterations to converge
struct CURVE_FITTING_COST2 {
  CURVE_FITTING_COST2(double x, double y) : _x(x), _y(y) {}

  // 残差的计算
  template<typename T>
  bool operator()(
    const T *const abcdef, // 6 dimension params
    T *residual) const {
    residual[0] = T(_y) - abcdef[0]*ceres::exp(abcdef[1]*T(_x))-abcdef[2]*ceres::sin(abcdef[3]*T(_x)+abcdef[4]) \
                  -abcdef[5]*T(_x); // y-ae^{bx}-csin(dx+e)-fx
    return true;
  }

  const double _x, _y;
};

int main(int argc, char **argv) {
  double ar = 1.0, br = 2.0, cr = 1.0, dr = 2.0, er = 3.0, fr = 4.0;         // 真实参数值
  double ae = 1.2, be = 1.0, ce = 0.5, de = 2.5, ee = 3.0, fe = 3.0;         // 估计参数值
  int N = 100;                                 // 数据点
  double w_sigma = 1.0;                        // 噪声Sigma值
  double inv_sigma = 1.0 / w_sigma;
  cv::RNG rng;                                 // OpenCV随机数产生器

  vector<double> x_data, y1_data, y2_data;      // 数据
  for (int i = 0; i < N; i++) {
    double x = i / 100.0;
    x_data.push_back(x);
    y1_data.push_back(exp(ar * x * x + br * x + cr) + rng.gaussian(w_sigma * w_sigma));
    y2_data.push_back(ar * exp(br * x) + cr * sin(dr * x + er) + fr * x + rng.gaussian(w_sigma * w_sigma));
  }

  double abc[3] = {ae, be, ce};
  double abcdef[6] = {ae, be, ce, de, ee, fe};

  // 构建最小二乘问题
  ceres::Problem problem1;
  for (int i = 0; i < N; i++) {
    problem1.AddResidualBlock(     // 向问题中添加误差项
      // 使用自动求导，模板参数：误差类型，输出维度，输入维度，维数要与前面struct中一致
      new ceres::AutoDiffCostFunction<CURVE_FITTING_COST, 1, 3>(
        new CURVE_FITTING_COST(x_data[i], y1_data[i])
      ),
      nullptr,            // 核函数，这里不使用，为空
      abc                 // 待估计参数
    );
  }

  // 配置求解器
  ceres::Solver::Options options1;     // 这里有很多配置项可以填
  options1.linear_solver_type = ceres::DENSE_NORMAL_CHOLESKY;  // 增量方程如何求解
  options1.minimizer_progress_to_stdout = true;   // 输出到cout

  ceres::Solver::Summary summary1;                // 优化信息
  chrono::steady_clock::time_point t1 = chrono::steady_clock::now();
  ceres::Solve(options1, &problem1, &summary1);  // 开始优化
  chrono::steady_clock::time_point t2 = chrono::steady_clock::now();
  chrono::duration<double> time_used = chrono::duration_cast<chrono::duration<double>>(t2 - t1);
  cout << "solve time cost = " << time_used.count() << " seconds. " << endl;

  // 输出结果
  cout << summary1.BriefReport() << endl; // CONVERGENCE over 17 iters
  cout << "estimated a,b,c = ";       // GT 1.0     2.0     1.0 
  for (auto a:abc) cout << a << " ";  // ES 1.05489 1.92158 1.02832
  cout << endl;

  cout << "=====================================================================================" << endl;
  ceres::Problem problem2;
  for (int i = 0; i < N; i++) {
    problem2.AddResidualBlock(     // 向问题中添加误差项
      // 使用自动求导，模板参数：误差类型，输出维度，输入维度，维数要与前面struct中一致
      new ceres::AutoDiffCostFunction<CURVE_FITTING_COST2, 1, 6>(
        new CURVE_FITTING_COST2(x_data[i], y2_data[i])
      ),
      nullptr,            // 核函数，这里不使用，为空
      abcdef                 // 待估计参数
    );
  }

  ceres::Solver::Options options2;  // use some different options
  options2.trust_region_strategy_type = ceres::DOGLEG;  // DogLeg method
  options2.minimizer_progress_to_stdout = true;

  ceres::Solver::Summary summary2;
  t1 = chrono::steady_clock::now();
  ceres::Solve(options2, &problem2, &summary2);
  t2 = chrono::steady_clock::now();
  time_used = chrono::duration_cast<chrono::duration<double>>(t2-t1);
  cout << "solve time cost = " << time_used.count() << " seconds. " << endl;

  cout << summary2.BriefReport() << endl; // CONVERGENCE over 24 iters
  cout << "estimated a,b,c,d,e,f = ";   // GT 1.0      2.0     1.0       2.0     3.0     4.0
  for (auto a:abcdef) cout << a << " "; // ES 0.522288 2.50634 -0.365476 6.14024 3.42716 4.3175
  cout << endl;

  return 0;
}