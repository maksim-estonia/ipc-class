# IPC class

A (factory) class-based implementation for conducting IPC using pipe, queue or shared memory.

## UML graph

![uml-graph.jpg](/uml-graph.jpg)

## Setup

Execute `./environment.sh`

## Building

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

- Build (test)

```
bazel build tests:tests
```

- Test (test)

```
bazel test tests:tests
```

## Testing

For testing we use the GoogleTest framework