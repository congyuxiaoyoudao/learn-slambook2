# include <iostream>
# include <cmath>
# include <Eigen/Core>
# include <Eigen/Geometry>
# include <sophus/se3.hpp>

using namespace std;
using namespace Eigen;

/// 本程序演示sophus的基本用法
int main(int argc, char **argv) {
  // 沿Z轴转90度的旋转矩阵
  Matrix3d R = AngleAxisd(M_PI/2,Vector3d(0,0,1)).toRotationMatrix();
  // 或者四元数
  Quaterniond q(R);
  Sophus::SO3d SO3_R(R);  // Sophus::SO3d可以直接从旋转矩阵构造
  Sophus::SO3d SO3_q(q);  // 也可以通过四元数构造
  // 二者是等价的
  cout << "SO(3) from matrix: \n" << SO3_R.matrix() << endl;
  cout << "SO(3) from quaternion: \n" << SO3_q.matrix() << endl;
  cout << "they are equal" << endl;

  // 使用对数映射获得它的李代数
  Vector3d so3 = SO3_R.log();
  cout << "so3 = " << so3.transpose() << endl;
  // hat为向量到反对称矩阵
  cout << "so3 hat=\n" << Sophus::SO3d::hat(so3) << endl;
  // 相对的，vee为反对称到向量
  cout << "so3 hat vee= " << Sophus::SO3d::vee(Sophus::SO3d::hat(so3)).transpose() << endl;

  // 增量扰动模型的更新
  Vector3d update_so3(1e-4,0,0); //假设更新量为这么多
  Sophus::SO3d SO3_updated = Sophus::SO3d::exp(update_so3) * SO3_R;
  cout << "SO(3) updated: \n" << SO3_updated.matrix() << endl;

  cout << "*********************************************" << endl;
  
  // almost same for SE(3)
  Vector3d t(1, 0, 0);
  Sophus::SE3d SE3_Rt(R, t); // from R, t
  Sophus::SE3d SE3_qt(q, t); // from q, t
  cout << "SE(3) from R, t: \n" << SE3_Rt.matrix() << endl;
  cout << "SE(3) from q, t: \n" << SE3_qt.matrix() << endl;
  cout << "they are equal" << endl;
  // also, hat and vee operations
  typedef Matrix<double, 6, 1> Vector6d;
  Vector6d se3 = SE3_Rt.log();
  cout << "se3 = " << se3.transpose() << endl;
  cout << "se3 hat=\n" << Sophus::SE3d::hat(se3) << endl;
  cout << "se3 hat vee=" << Sophus::SE3d::vee(Sophus::SE3d::hat(se3)).transpose() << endl;
  // update se3
  Vector6d update_se3;
  update_se3.setZero();
  update_se3(0, 0) = 1e-4;
  Sophus::SE3d SE3_updated = Sophus::SE3d::exp(update_se3) * SE3_Rt;
  cout << "SE(3) updated: \n" << SE3_updated.matrix() << endl;
  return 0;
}