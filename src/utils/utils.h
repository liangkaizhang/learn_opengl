#ifndef UTILS_UTILS_H_
#define UTILS_UTILS_H_

#include <absl/status/status.h>
#include "absl/status/statusor.h"

namespace ogl {

#ifndef CHECK_OK
#define CHECK_OK(status_expr)                  \
  do {                                         \
    const absl::Status status = (status_expr); \
    CHECK(status.ok()) << status;              \
  } while (false)
#endif  // CHECK_OK

// #ifndef RETURN_IF_ERROR
// #define RETURN_IF_ERROR(status_expr)   \
//   do {                                 \
//     const auto status = (status_expr); \
//     if (!status.ok()) return status;   \
//   } while (false)
// #endif  // RETURN_IF_ERROR

// Helper macro that checks if the right hand side (rexpression) evaluates to a
// StatusOr with Status OK, and if so assigns the value to the value on the left
// hand side (lhs), otherwise returns the error status.
#ifndef ASSIGN_OR_RETURN
#define ASSIGN_OR_RETURN(lhs, rexpr)                                           \
  PRIVATE_RETRIEVAL_ASSIGN_OR_RETURN_IMPL_(                                    \
      PRIVATE_RETRIEVAL_STATUS_MACROS_IMPL_CONCAT_(status_or_value, __LINE__), \
      lhs, rexpr)

// Internal helper.
#define PRIVATE_RETRIEVAL_ASSIGN_OR_RETURN_IMPL_(statusor, lhs, rexpr) \
  auto statusor = (rexpr);                                             \
  if (ABSL_PREDICT_FALSE(!statusor.ok())) {                            \
    return std::move(statusor).status();                               \
  }                                                                    \
  lhs = *std::move(statusor)
#endif  // ASSIGN_OR_RETURN

// Helper macro that checks if the given expression evaluates to a
// Status with Status OK. If not,  returns the error status.
#ifndef RETURN_IF_ERROR
#define RETURN_IF_ERROR(expr)                                               \
  PRIVATE_RETRIEVAL_RETURN_IF_ERROR_IMPL_(                                  \
      PRIVATE_RETRIEVAL_STATUS_MACROS_IMPL_CONCAT_(status_value, __LINE__), \
      expr)

// Internal helper.
#define PRIVATE_RETRIEVAL_RETURN_IF_ERROR_IMPL_(status, expr) \
  auto status = (expr);                                       \
  if (ABSL_PREDICT_FALSE(!status.ok())) {                     \
    return status;                                            \
  }
#endif  // RETURN_IF_ERROR

// Internal helper for concatenating macro values.
#define PRIVATE_RETRIEVAL_STATUS_MACROS_IMPL_CONCAT_INNER_(x, y) x##y
#define PRIVATE_RETRIEVAL_STATUS_MACROS_IMPL_CONCAT_(x, y) \
  PRIVATE_RETRIEVAL_STATUS_MACROS_IMPL_CONCAT_INNER_(x, y)

}  // namespace ogl

#endif  // UTILS_UTILS_H_
