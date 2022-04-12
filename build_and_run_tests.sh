set -x 

#clean
bazel clean

#build
bazel build --cxxopt='-std=c++14' //src/main:receive_main
bazel build --cxxopt='-std=c++14' //src/main:send_main

#bazel test --cxxopt='-std=c++14' --linkopt="-pthread" --test_output=all //tests:GoogleTest
bazel run --cxxopt='-std=c++14' --linkopt="-pthread" //tests:GoogleTest > test.log

#bazel clean
set +x

echo "Test completed: output can be found in test-log.txt"