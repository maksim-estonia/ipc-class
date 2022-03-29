# https://docs.bazel.build/versions/master/be/c-cpp.html#cc_binary
cc_binary(
    name = "main",
    srcs = ["main.cc"],
    deps = ["//src/IPC:IpcLib", "//data:input.txt", "//data:output.txt", "//data:pipe_input.txt", "//data:pipe_output.txt"],
)

cc_binary(
    name = "send_main",
    srcs = ["send_main.cc"],
    deps = ["//src/IPC:IpcLib", "//data:input.txt", "//data:output.txt", "//data:pipe_input.txt", "//data:pipe_output.txt"],
)

cc_binary(
    name = "receive_main",
    srcs = ["receive_main.cc"],
    deps = ["//src/IPC:IpcLib", "//data:input.txt", "//data:output.txt", "//data:pipe_input.txt", "//data:pipe_output.txt"],
)