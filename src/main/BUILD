# https://docs.bazel.build/versions/master/be/c-cpp.html#cc_binary

cc_binary(
    name = "send_main",
    srcs = ["send_main.cc", "ipc_common.h", "ipc_common.cc"],
    deps = ["//src/IPC:IpcLib"],
    data = ["//data:pipe_input.txt", "//data:pipe_output.txt", "//data:queue_input.txt", "//data:queue_output.txt", "//data:shm_input.txt", "//data:shm_output.txt", "//data:5mb_input.txt", "//data:5mb_output.txt"],
)

cc_binary(
    name = "receive_main",
    srcs = ["receive_main.cc", "ipc_common.h", "ipc_common.cc"],
    deps = ["//src/IPC:IpcLib"],
    data = ["//data:pipe_input.txt", "//data:pipe_output.txt", "//data:queue_input.txt", "//data:queue_output.txt", "//data:shm_input.txt", "//data:shm_output.txt", "//data:5mb_input.txt", "//data:5mb_output.txt"],
)