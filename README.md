- [IPC class](#ipc-class)
  - [UML graph](#uml-graph)
  - [xdot graph](#xdot-graph)
    - [build - receive_main](#build---receive_main)
    - [build - send_main](#build---send_main)
    - [test](#test)
  - [Setup](#setup)
  - [Build & Run](#build--run)
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

Execute `./environment.sh`

## Build & Run

Execute `./build_and_run.sh`

For building we use Bazel

- Run (main)

```
bazel run src/main:main
```

- Run (receive)
  
```
bazel run src/main:receive_main
```

- Run (send)
  
```
bazel run src/main:send_main
```

## Testing

For testing we use the GoogleTest framework

- Build (test)

```
bazel build tests:GoogleTest
```

- Test (test)

```
bazel test tests:GoogleTest
```