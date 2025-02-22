#pragma once

#include <torch/csrc/distributed/c10d/Types.hpp>
#include <c10/core/ScalarType.h>

#include <csrc_dipu/common.h>
#include <csrc_dipu/vendor/vendorapi.h>
// #include <csrc_dipu/runtime/distributed/ProcessGroupDICL.hpp>

namespace dipu {

// need enhance return status.
// refer nccl & ascend & camb
namespace devapis {
  using ReduceOp = c10d::ReduceOp;

  // DIPU_API c10::intrusive_ptr<ProcessGroupDICL> createProcessGroupDICL(const c10::intrusive_ptr<::c10d::Store> &store,
  //     int rank, int size, const std::chrono::duration<float> &timeout);
  extern const int DICL_UNIQUE_ID_BYTES_SIZE;

  DIPU_API diclResult_t diclGetCommAsyncError(diclComm_t comm);

  DIPU_API diclResult_t diclGetUniqueId(commUniqueId* uniqueId);

  DIPU_API diclResult_t diclCommInitRank(diclComm_t* comm, int nranks, commUniqueId uniqueId, int rank, int localDeviceId = -1);

  // DIPU_API void diclCommInitAll(diclComm_t* comms, int ndev, const int* devlist);

  DIPU_API diclResult_t diclCommDestroy(diclComm_t comm);

  // DIPU_API diclResult_t diclCommFinalize(diclComm_t comm);

  // DIPU_API diclResult_t diclCommAbort(diclComm_t comm);

  DIPU_API diclResult_t diclAllReduce(const void *sendbuff, void *recvbuff, size_t count, at::ScalarType datatype,
                              const ReduceOp& reduceOp, diclComm_t comm, deviceStream_t stream);

  DIPU_API diclResult_t diclBroadcast(const void *sendbuff, void* recvbuff, size_t count, at::ScalarType datatype,
                              int root, diclComm_t comm, deviceStream_t stream);

  DIPU_API diclResult_t diclAllGather(const void *sendBuf, void *recvBuf, size_t count, at::ScalarType datatype,
                              diclComm_t comm, deviceStream_t stream);

  DIPU_API diclResult_t diclReduce(const void* sendbuff, void* recvbuff, size_t count, at::ScalarType datatype,
                            const ReduceOp& reduceOp, int root, diclComm_t comm, deviceStream_t stream);

  DIPU_API diclResult_t diclReduceScatter(void *sendBuf, void *recvBuf, uint64_t recvCount, at::ScalarType dataType, 
                                  const ReduceOp& op, diclComm_t comm, deviceStream_t stream);

  DIPU_API diclResult_t diclSend(void* sendbuff, size_t count, at::ScalarType datatype, int peer,
                          diclComm_t comm, deviceStream_t stream);

  DIPU_API diclResult_t diclRecv(void* recvbuff, size_t count, at::ScalarType datatype, int peer,
                          diclComm_t comm, deviceStream_t stream);


} // namespace devapis

} // namespace dipu