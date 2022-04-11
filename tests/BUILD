cc_test(
    name = "GoogleTest",
    size = "small",
    srcs = ["test_main.cc"],
    deps = [
        "@googletest//:gtest_main",
        "//src/IPC:IpcLib",
    ],
    data = ["//data:pipe_input.txt", "//data:pipe_output.txt", "//data:queue_input.txt", "//data:queue_output.txt", "//data:shm_input.txt", "//data:shm_output.txt", "//data:5mb_input.txt", "//data:5mb_output.txt"],
)
