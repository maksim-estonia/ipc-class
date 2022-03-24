set -x 

#build
bazel build --cxxopt='-std=c++14' //src/main:receive_main
bazel build --cxxopt='-std=c++14' //src/main:send_main

bazel test --cxxopt='-std=c++14' --test_output=all //tests:GoogleTest

bazel clean
set +x