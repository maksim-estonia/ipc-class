- [IPC class](#ipc-class)
  - [UML graph](#uml-graph)
  - [xdot graph](#xdot-graph)
    - [build - receive_main](#build---receive_main)
    - [build - send_main](#build---send_main)
    - [test](#test)
  - [Setup](#setup)
  - [Build & Run](#build--run)
    - [Run](#run)
  - [Testing](#testing)

# IPC class

A (factory) class-based implementation for conducting IPC using pipe, queue or shared memory.

## UML graph

![uml-graph.jpg](/uml-graph.jpg)

## xdot graph

### build - receive_main

`xdot <(bazel query --notool_deps --noimplicit_deps "deps(//src/main:receive_main)" --output graph)`

![images/build-receive-main.png](/images/build-receive-main.png)

### build - send_main

`xdot <(bazel query --notool_deps --noimplicit_deps "deps(//src/main:send_main)" --output graph)`

![images/build-send-main.png](/images/build-send-main.png)

### test

`xdot <(bazel query --notool_deps --noimplicit_deps "deps(//tests:test_main)" --output graph)`

![images/test-graph.png](/images/test-graph.png)

## Setup

Execute `./setup_environment.sh`

## Build & Run

Execute `./build_and_run_tests.sh`

For building we use Bazel

- Build (receive)
  
```
bazel build //src/main:receive_main
```

- Build (send)
  
```
bazel build //src/main:send_main
```

There is also an option to build with `PRINT` (prints out more information)

`bazel build --cxxopt='-std=c++14' --copt="-D PRINT" //src/main:receive_main`

`bazel build --cxxopt='-std=c++14' --copt="-D PRINT" //src/main:send_main`

### Run

- pipe

  - start receive side

  ```
  cd bazel-bin/src/main
  ./receive_main --pipe --file output.txt
  ```

  - start send side

  ```
  cd bazel-bin/src/main
  ./send_main --pipe --file input.txt
  ```

## Testing

For testing we use the GoogleTest framework

- Build (test)

```
bazel build --cxxopt='-std=c++14' //tests:GoogleTest
```

- Test (test)

```
bazel test --cxxopt='-std=c++14' //tests:GoogleTest
```

- Run (shows output)

```
bazel run --cxxopt='-std=c++14' //tests:GoogleTest
```