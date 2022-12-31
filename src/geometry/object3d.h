
#ifndef GEOMETRY_OBJECT_3D_H_
#define GEOMETRY_OBJECT_3D_H_

#include <cstdint>
#include <string>
#include <vector>

#include <absl/status/status.h>
#include "Eigen/Dense"
#include <GL/glew.h> 

#include "geometry/buffer_geometry.h"
#include "geometry/camera.h"

namespace ogl {

class Object3d {
  public:
    using Ptr = std::unique_ptr<Object3d>;

    Object3d() : visible_(true), order_(0), matrix_(Eigen::Matrix4f::Identity()) {};
    virtual ~Object3d() = default;

    virtual absl::Status Draw(const Camera& camera) const = 0;
    virtual absl::Status Draw() const = 0;

    void Rotate(float angle, const Eigen::Vector3f& axis) {
      Eigen::Matrix4f transform = Eigen::Matrix4f::Identity();
      transform.topLeftCorner<3, 3>() =
          Eigen::AngleAxisf(angle, axis).toRotationMatrix();
      this->ApplyMatrix4(transform);
    };

    void SetRotation(float angle, const Eigen::Vector3f& axis) {
      matrix_.topLeftCorner<3, 3>() =
          Eigen::AngleAxisf(angle, axis).toRotationMatrix();
    };

    void SetRotation(const Eigen::Matrix3f& rotation) {
      matrix_.topLeftCorner<3, 3>() = rotation;
    };

    Eigen::Matrix3f Rotation() const {
      return matrix_.topLeftCorner<3, 3>();
    }

    void SetTranslation(const Eigen::Vector3f& translation) {
      matrix_.topRightCorner<3, 1>() = translation;
    }

    Eigen::Vector3f Translation() const {
      return matrix_.topRightCorner<3, 1>();
    }

    void ApplyMatrix4(const Eigen::Matrix4f& matrix) {
      matrix_ = matrix * matrix_;
    };

    void SetMatrix(const Eigen::Matrix4f& matrix) {
      matrix_ = matrix;
    };

    const Eigen::Matrix4f& Matrix() const {
      return matrix_;
    }

    void SetVisible(bool value) {
      visible_ = value;
    };

    bool Visible() const {
      return visible_;
    };

    void SetOrder(size_t order) {
      order_ = order;
    }

    size_t Order() const {
      return order_;
    }

  protected:
    bool visible_;
    size_t order_;
    Eigen::Matrix4f matrix_;
};

}  // namespace ogl

#endif  // GEOMETRY_OBJECT_3D_H_