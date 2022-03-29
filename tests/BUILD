cc_test(
    name = "GoogleTest",
    size = "small",
    srcs = ["test_main.cc"],
    deps = [
        "@googletest//:gtest_main",
        "//src/IPC:IpcLib",
    ],
    data = ["//data:input.txt", "//data:output.txt", "//data:pipe_input.txt", "//data:pipe_output.txt"],
)
