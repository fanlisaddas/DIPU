// Copyright (c) 2023, DeepLink.
#pragma once

#include <ATen/Utils.h>
#include <c10/core/DispatchKey.h>

#define DIPU_API __attribute__ ((visibility ("default")))

#define DIPU_WEAK  __attribute__((weak))

// "default", "hidden", "protected" or "internal
#define DIPU_HIDDEN __attribute__ ((visibility ("hidden")))


typedef int32_t enum_t;

#define C10_COMPILE_TIME_MAX_DIPUS 16

#define DIPU_STRING(x) #x
#define DIPU_CODELOC __FILE__ " (" DIPU_STRING(__LINE__) ")"


#define DIPU_LOGE(fmt, ...)          \
  printf(                           \
      "[ERROR]%s,%s:%u:" #fmt "\n", \
      __FUNCTION__,                 \
      __FILE__,                     \
      __LINE__,                     \
      ##__VA_ARGS__)

#define DIPU_LOGW(fmt, ...)         \
  printf(                          \
      "[WARN]%s,%s:%u:" #fmt "\n", \
      __FUNCTION__,                \
      __FILE__,                    \
      __LINE__,                    \
      ##__VA_ARGS__)

namespace dipu {
namespace devapis {

enum class VendorDeviceType : enum_t {
  MLU,  //camb
  NPU,  //ascend
  CUDA, //cuda
  GCU,  //gcu
  SUPA, //Biren
  STPU, //stpu
};

constexpr const char* VendorTypeToStr(VendorDeviceType t) noexcept {
  switch (t) {
    case VendorDeviceType::MLU: return "MLU";
    case VendorDeviceType::CUDA: return "CUDA";
    case VendorDeviceType::NPU: return "NPU";
    case VendorDeviceType::GCU: return "GCU";
    case VendorDeviceType::SUPA: return "SUPA";
    case VendorDeviceType::STPU: return "STPU";
  }
}

enum class EventStatus: enum_t {
  PENDING,
  RUNNING,
  DEFERRED,
  READY
};

enum class OpStatus: enum_t {
  SUCCESS,
  ERR_UNKNOWN,
  ERR_NOMEM,
};

enum class MemCPKind: enum_t {
  D2H,
  H2D,
  D2D,
};

typedef enum {
  /*! The operation was successful. */
  DICL_SUCCESS = 0x0,

  /*! undefined error */
  DICL_ERR_UNDEF = 0x01000,

} diclResult_t;

} // end ns devapis


// XPU is originally intel output-of-tree code https://github.com/intel/intel-extension-for-pytorch ( branch xpu-master )
// we use this type but PrivateUse1 not to impersonate our DIPU device. because compared with PrivateUse1,
// XPU has richer support in pytorch trunk and not too much feature in torch to interfere our logic (as XLA).
const auto DIPU_DEVICE_TYPE = at::DeviceType::XPU;

const auto DIPU_DISPATCH_KEY = c10::DispatchKey::XPU;
const auto DIPU_DISPATCH_AUTOGRAD_KEY = c10::DispatchKey::AutogradXPU;


const auto DIPU_Backend_TYPE = c10::Backend::XPU;

const auto DICL_BACKEND_NAME = "dicl";

DIPU_API bool isDeviceTensor(const at::Tensor &tensor);

} // end ns dipu

#define DIPU_DEVICE_TYPE_MACRO XPU
#define DIPU_AUTOGRAD_DEVICE_TYPE_MACRO AutogradXPU

