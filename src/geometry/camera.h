#ifndef GEOMETRY_CAMERA_H_
#define GEOMETRY_CAMERA_H_

#include "Eigen/Dense"

namespace ogl {

class Camera {
  public:
    Camera() = default;
    Camera(float focal_x, float focal_y,
           float center_x, float center_y,
           float size_x, float size_y,
           float near, float far);

    void SetFocal(float focal_x, float focal_y);
    float FocalX() const { return focal_x_; };
    float FocalY() const { return focal_y_; };

    void SetCenter(float center_x, float center_y);
    float CenterX() const { return center_x_; };
    float CenterY() const { return center_y_; };

    void SetSize(float size_x, float size_y);
    float SizeX() const { return size_x_; };
    float SizeY() const { return size_y_; };

    void SetNearfar(float near, float far);
    float Near() const { return near_; };
    float Far() const { return far_; };

    void SetRotation(const Eigen::Matrix3f& rotation);
    void SetRotation(float angle, const Eigen::Vector3f& axis);
    Eigen::Matrix3f Rotation() const;
    void Rotate(float angle, const Eigen::Vector3f& axis);

    void ApplyMatrix4(const Eigen::Matrix4f& matrix);

    void SetTranslation(const Eigen::Vector3f& translation);
    Eigen::Vector3f Translation() const;

    Eigen::Matrix4f SetViewMatrix(const Eigen::Matrix4f& view_matrix);
    Eigen::Matrix4f ViewMatrix() const;

    Eigen::Matrix4f ProjectionMatrix() const;
    Eigen::Matrix3f Intrinsics() const;
  private:
    float focal_x_, focal_y_;
    float center_x_, center_y_;
    float size_x_, size_y_;
    float near_ = 0.001;
    float far_ = 1000;
    Eigen::Matrix4f view_matrix_ = Eigen::Matrix4f::Identity();
};

}  // namespace ogl

#endif  // GEOMETRY_CAMERA_H_