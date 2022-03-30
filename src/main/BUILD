# https://docs.bazel.build/versions/master/be/c-cpp.html#cc_binary

cc_binary(
    name = "send_main",
    srcs = ["send_main.cc", "ipc_common.h"],
    deps = ["//src/IPC:IpcLib"],
    data = ["//data:pipe_input.txt", "//data:pipe_output.txt", "//data:queue_input.txt", "//data:queue_output.txt", "//data:shm_input.txt", "//data:shm_output.txt"],
)

cc_binary(
    name = "receive_main",
    srcs = ["receive_main.cc", "ipc_common.h"],
    deps = ["//src/IPC:IpcLib"],
    data = ["//data:pipe_input.txt", "//data:pipe_output.txt", "//data:queue_input.txt", "//data:queue_output.txt", "//data:shm_input.txt", "//data:shm_output.txt"],
)