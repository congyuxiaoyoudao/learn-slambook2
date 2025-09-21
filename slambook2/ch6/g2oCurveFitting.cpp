#include <iostream>
#include <g2o/core/g2o_core_api.h>
#include <g2o/core/base_vertex.h>
#include <g2o/core/base_unary_edge.h>
#include <g2o/core/block_solver.h>
#include <g2o/core/optimization_algorithm_levenberg.h>
#include <g2o/core/optimization_algorithm_gauss_newton.h>
#include <g2o/core/optimization_algorithm_dogleg.h>
#include <g2o/solvers/dense/linear_solver_dense.h>
#include <Eigen/Core>
#include <opencv2/core/core.hpp>
#include <cmath>
#include <chrono>

using namespace std;

// 曲线模型的顶点，模板参数：优化变量维度和数据类型
class CurveFittingVertex : public g2o::BaseVertex<3, Eigen::Vector3d> {
public:
  EIGEN_MAKE_ALIGNED_OPERATOR_NEW

  // 重置
  virtual void setToOriginImpl() override {
    _estimate << 0, 0, 0;
  }

  // 更新
  virtual void oplusImpl(const double *update) override {
    _estimate += Eigen::Vector3d(update);
  }

  // 存盘和读盘：留空
  virtual bool read(istream &in) {}

  virtual bool write(ostream &out) const {}
};

// 误差模型 模板参数：观测值维度，类型，连接顶点类型
class CurveFittingEdge : public g2o::BaseUnaryEdge<1, double, CurveFittingVertex> {
public:
  EIGEN_MAKE_ALIGNED_OPERATOR_NEW

  CurveFittingEdge(double x) : BaseUnaryEdge(), _x(x) {}

  // 计算曲线模型误差
  virtual void computeError() override {
    const CurveFittingVertex *v = static_cast<const CurveFittingVertex *> (_vertices[0]);
    const Eigen::Vector3d abc = v->estimate();
    _error(0, 0) = _measurement - std::exp(abc(0, 0) * _x * _x + abc(1, 0) * _x + abc(2, 0));
  }

  // 计算雅可比矩阵
  virtual void linearizeOplus() override {
    const CurveFittingVertex *v = static_cast<const CurveFittingVertex *> (_vertices[0]);
    const Eigen::Vector3d abc = v->estimate();
    double y = exp(abc[0] * _x * _x + abc[1] * _x + abc[2]);
    _jacobianOplusXi[0] = -_x * _x * y;
    _jacobianOplusXi[1] = -_x * y;
    _jacobianOplusXi[2] = -y;
  }

  virtual bool read(istream &in) {}

  virtual bool write(ostream &out) const {}

public:
  double _x;  // x 值， y 值为 _measurement
};

typedef Eigen::Matrix<double, 6, 1> Vector6d;

class CurveFittingVertex2 : public g2o::BaseVertex<6, Vector6d> {
public:
  EIGEN_MAKE_ALIGNED_OPERATOR_NEW

  // 重置
  virtual void setToOriginImpl() override {
    _estimate << 0, 0, 0, 0, 0, 0;
  }

  // 更新
  virtual void oplusImpl(const double *update) override {
    _estimate += Vector6d(update);
  }

  // 存盘和读盘：留空
  virtual bool read(istream &in) {}

  virtual bool write(ostream &out) const {}
};

class CurveFittingEdge2 : public g2o::BaseUnaryEdge<1, double, CurveFittingVertex2> {
public:
  EIGEN_MAKE_ALIGNED_OPERATOR_NEW

  CurveFittingEdge2(double x) : BaseUnaryEdge(), _x(x) {}

  // 计算曲线模型误差
  virtual void computeError() override {
    const CurveFittingVertex2 *v = static_cast<const CurveFittingVertex2 *> (_vertices[0]);
    const Vector6d abcdef = v->estimate();
    _error(0, 0) = _measurement - abcdef(0,0) * std::exp(abcdef(1, 0) * _x) - \
                    abcdef(2,0)*std::sin(abcdef(3,0)*_x+abcdef(4,0)) - abcdef(5,0)*_x;
  }

  // 计算雅可比矩阵
  virtual void linearizeOplus() override {
    const CurveFittingVertex2 *v = static_cast<const CurveFittingVertex2 *> (_vertices[0]);
    const Vector6d abcdef = v->estimate();
    double y = abcdef(0,0) * std::exp(abcdef(1, 0) * _x) + \
                abcdef(2,0)*std::sin(abcdef(3,0)*_x+abcdef(4,0)) + abcdef(5,0)*_x;
    
                double exp_term = exp(abcdef(1)*_x);
    double sin_term = sin(abcdef(3)*_x + abcdef(4));

    _jacobianOplusXi[0] = -exp_term;
    _jacobianOplusXi[1] = -abcdef(0) * _x * exp_term;
    _jacobianOplusXi[2] = -sin_term;
    _jacobianOplusXi[3] = -abcdef(2) * _x * cos(abcdef(3)*_x + abcdef(4));
    _jacobianOplusXi[4] = -abcdef(2) * cos(abcdef(3)*_x + abcdef(4));
    _jacobianOplusXi[5] = -_x;
  }

  virtual bool read(istream &in) {}

  virtual bool write(ostream &out) const {}

public:
  double _x;  // x 值， y 值为 _measurement
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
    y2_data.push_back(ar*exp(br*x)+cr*sin(dr*x+er)+fr*x+rng.gaussian(w_sigma*w_sigma));
  }

  // 构建图优化，先设定g2o
  typedef g2o::BlockSolver<g2o::BlockSolverTraits<3, 1>> BlockSolverType;  // 每个误差项优化变量维度为3，误差值维度为1
  typedef g2o::BlockSolver<g2o::BlockSolverTraits<6, 1>> BlockSolverType2;  // 每个误差项优化变量维度为6，误差值维度为1
  typedef g2o::LinearSolverDense<BlockSolverType::PoseMatrixType> LinearSolverType; // 线性求解器类型
  typedef g2o::LinearSolverDense<BlockSolverType2::PoseMatrixType> LinearSolverType2;

  // 梯度下降方法，可以从GN, LM, DogLeg 中选
  auto solver = new g2o::OptimizationAlgorithmGaussNewton(
    g2o::make_unique<BlockSolverType>(g2o::make_unique<LinearSolverType>()));
  g2o::SparseOptimizer optimizer;     // 图模型
  optimizer.setAlgorithm(solver);   // 设置求解器
  optimizer.setVerbose(true);       // 打开调试输出

  // 往图中增加顶点
  CurveFittingVertex *v = new CurveFittingVertex();
  v->setEstimate(Eigen::Vector3d(ae, be, ce));
  v->setId(0);
  optimizer.addVertex(v);

  // 往图中增加边
  for (int i = 0; i < N; i++) {
    CurveFittingEdge *edge = new CurveFittingEdge(x_data[i]);
    edge->setId(i);
    edge->setVertex(0, v);                // 设置连接的顶点
    edge->setMeasurement(y1_data[i]);      // 观测数值
    edge->setInformation(Eigen::Matrix<double, 1, 1>::Identity() * 1 / (w_sigma * w_sigma)); // 信息矩阵：协方差矩阵之逆
    optimizer.addEdge(edge);
  }

  // 执行优化
  cout << "start optimization" << endl;
  chrono::steady_clock::time_point t1 = chrono::steady_clock::now();
  optimizer.initializeOptimization();
  optimizer.optimize(10);
  chrono::steady_clock::time_point t2 = chrono::steady_clock::now();
  chrono::duration<double> time_used = chrono::duration_cast<chrono::duration<double>>(t2 - t1);
  cout << "solve time cost = " << time_used.count() << " seconds. " << endl;

  // 输出优化值
  Eigen::Vector3d abc_estimate = v->estimate();
  cout << "estimated model: " << abc_estimate.transpose() << endl;

  cout << "=====================================================================================" << endl;
  
  // Now use another method
  auto solver2 = new g2o::OptimizationAlgorithmDogleg(
    g2o::make_unique<BlockSolverType2>(g2o::make_unique<LinearSolverType2>()));
  g2o::SparseOptimizer optimizer2;     // 图模型
  optimizer2.setAlgorithm(solver2);   // 设置求解器
  optimizer2.setVerbose(true); 

  CurveFittingVertex2 *v2 = new CurveFittingVertex2();
  Vector6d est;
  est << ae, be, ce, de, ee, fe;
  v2->setEstimate(est);
  v2->setId(0);
  optimizer2.addVertex(v2);

  for (int i = 0; i < N; i++) {
    CurveFittingEdge2 *edge = new CurveFittingEdge2(x_data[i]);
    edge->setId(i);
    edge->setVertex(0, v2);                // 设置连接的顶点
    edge->setMeasurement(y2_data[i]);      // 观测数值
    edge->setInformation(Eigen::Matrix<double, 1, 1>::Identity() * 1 / (w_sigma * w_sigma)); // 信息矩阵：协方差矩阵之逆
    optimizer2.addEdge(edge);
  }

  cout << "start optimization for another strongly non-linear problem" << endl;
  t1 = chrono::steady_clock::now();
  optimizer2.initializeOptimization();
  optimizer2.optimize(20);
  t2 = chrono::steady_clock::now();
  time_used = chrono::duration_cast<chrono::duration<double>>(t2 - t1);
  cout << "solve time cost = " << time_used.count() << " seconds. " << endl;

  // 输出优化值
  Vector6d abcdef_estimate = v2->estimate();
  cout << "estimated model: " << abcdef_estimate.transpose() << endl;

  return 0;
}