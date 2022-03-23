set -x 

bazel build --cxxopt='-std=c++14' //src/main:receive_main
bazel build --cxxopt='-std=c++14' //src/main:send_main

bazel clean
set +x