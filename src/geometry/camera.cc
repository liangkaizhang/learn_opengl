#include "geometry/camera.h"

#include <glog/logging.h>

namespace ogl {
namespace {
using Eigen::AngleAxisf;
using Eigen::Vector3f;
using Eigen::Matrix4f;
using Eigen::Matrix3f;
}  // namespace

Camera::Camera(float focal_x, float focal_y,
               float center_x, float center_y,
               float size_x, float size_y,
               float near, float far)
               : focal_x_(focal_x), focal_y_(focal_y),
                 center_x_(center_x), center_y_(center_y),
                 size_x_(size_x), size_y_(size_y),
                 near_(near), far_(far) {
}

void Camera::SetFocal(float focal_x, float focal_y) {
    focal_x_ = focal_x;
    focal_y_ = focal_y;
}

void Camera::SetCenter(float center_x, float center_y) {
    center_x_ = center_x;
    center_y_ = center_y;
}

void Camera::SetSize(float size_x, float size_y) {
    size_x_ = size_x;
    size_y_ = size_y;
}

void Camera::SetNearfar(float near, float far) {
    near_ = near;
    far_ = far;
}

void Camera::SetRotation(float angle, const Eigen::Vector3f& axis) {
    view_matrix_.topLeftCorner<3, 3>() =
            AngleAxisf(angle, axis).toRotationMatrix();
}

void Camera::SetRotation(const Eigen::Matrix3f& rotation) {

}

Eigen::Matrix3f Camera::Rotation() const {
}

void Camera::Rotate(float angle, const Eigen::Vector3f& axis) {
    const auto rotation = Eigen::AngleAxisf(angle, axis).toRotationMatrix();
    view_matrix_.topLeftCorner<3, 3>() = rotation * view_matrix_.topLeftCorner<3, 3>();
};

void Camera::ApplyMatrix4(const Eigen::Matrix4f& matrix) {
    view_matrix_ = matrix * view_matrix_;
};

void Camera::SetTranslation(const Eigen::Vector3f& translation) {
    view_matrix_.topRightCorner<3, 1>() = translation;
}

Eigen::Matrix4f Camera::ProjectionMatrix() const {
    Matrix4f projection;
    projection << 2 * focal_x_ / size_x_, 0, (size_x_ - 2 * center_x_) / size_x_, 0,
                  0, 2 * focal_y_ / size_y_, (-size_y_ + 2 * center_y_) / size_y_, 0,
                  0, 0, (-far_ - near_) / (far_ - near_), -2 * far_ * near_ / (far_ - near_),
                  0, 0, -1, 0;
    return projection;
}

Eigen::Matrix4f Camera::ViewMatrix() const {
    return view_matrix_;
}

Eigen::Matrix3f Camera::Intrinsics() const {

}

}  // namespace ogl