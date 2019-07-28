# GENIVI/vsomeip Bazel Example

This project builds [GENIVI/vsomeip](https://github.com/GENIVI/vsomeip) and its Boost dependencies using Bazel. This project can be used as an example of using Bazel to build external projects using cmake and Boost b2 via [bazelbuild/rules_foreign_cc](https://github.com/bazelbuild/rules_foreign_cc).

# Requirements

This project has only been tested on x86 Ubuntu 18 (bionic).

# Dependencies

- [Bazel 0.26.1](https://docs.bazel.build/versions/master/install.html) or later
- [GoogleTest](https://github.com/google/googletest) for unit testing and mocking
- [GENIVI/vsomeip](https://github.com/GENIVI/vsomeip) SOME/IP stands for Scalable service-Oriented MiddlewarE over IP

# Origin

This project was created via the [Abseil Bazel Quickstart](https://abseil.io/docs/cpp/quickstart) on March 2019.

# VirtualBox Tips

If you share a github folder on your host, you need to enable symlinking to it. Run the following command from the host's command line. Replace virtual_machine_name and share_name in the following command:

```
VBoxManage setextradata virtual_machine_name VBoxInternal2/SharedFoldersEnableSymlinksCreate/share_name  1
```

# Usage

## Clean

```bash
bazel clean --expunge
```

## Build tests

```bash
bazel build -s test
```

## Run tests

```bash
bazel test -s test
```

## Run test, viewing console output

```bash
bazel-bin/test/test -s
```

The output looks like:


```bash
bazel-out/k8-fastbuild/bin/test/test -s

Running main() from gmock_main.cc
[==========] Running 1 test from 1 test suite.
[----------] Global test environment set-up.
[----------] 1 test from vsomeip
[ RUN      ] vsomeip.one
2019-06-08 18:57:51.458673 [warning] Reading of configuration file "./vsomeip/BUILD" failed. Configuration may be incomplete.
2019-06-08 18:57:51.458824 [info] Parsed vsomeip configuration in 5ms
2019-06-08 18:57:51.458861 [info] Using configuration folder: "./vsomeip".
2019-06-08 18:57:51.458895 [info] Default configuration module loaded.
2019-06-08 18:57:51.458919 [info] Initializing vsomeip application "Hello".
2019-06-08 18:57:51.459047 [info] SOME/IP client identifier configured. Using 0001 (was: 0000)
2019-06-08 18:57:51.459082 [info] No routing manager configured. Using auto-configuration.
2019-06-08 18:57:51.459105 [info] Instantiating routing manager [Host].
2019-06-08 18:57:51.459162 [info] init_routing_endpoint Routing endpoint at /tmp/vsomeip-0
2019-06-08 18:57:51.459279 [info] Client [1] is connecting to [0] at /tmp/vsomeip-0
2019-06-08 18:57:51.459316 [info] Service Discovery enabled. Trying to load module.
2019-06-08 18:57:51.459451 [info] Service Discovery module loaded.
2019-06-08 18:57:51.459556 [info] Application(Hello, 1) is initialized (11, 100).
2019-06-08 18:57:51.459597 [info] OFFER(0001): [1234.5678:0.0]
2019-06-08 18:57:51.459709 [info] REQUEST(0001): [1234.5678:255.4294967295]
2019-06-08 18:57:51.459854 [info] Starting vsomeip application "Hello" using 2 threads
2019-06-08 18:57:51.466850 [info] main dispatch thread id from application: 0001 (Hello) is: 7ff0ba6fd700 TID: 4423
CLIENT: Service [1234.5678] is available.
CLIENT: Received message with Client/Session [0001/0001] 00 01 02 03 04 05 06 07 08 09 
The application is stopping
2019-06-08 18:57:51.467260 [info] Watchdog is disabled!
2019-06-08 18:57:51.467290 [info] STOP OFFER(0001): [1234.5678:0.0]
2019-06-08 18:57:51.467351 [info] Stopping vsomeip application "Hello".
2019-06-08 18:57:51.467350 [info] io thread id from application: 0001 (Hello) is: 7ff0c1578200 TID: 4421
2019-06-08 18:57:51.467431 [info] shutdown thread id from application: 0001 (Hello) is: 7ff0b9efc700 TID: 4424
2019-06-08 18:57:51.467580 [info] io thread id from application: 0001 (Hello) is: 7ff0baefe700 TID: 4426
2019-06-08 18:57:51.467720 [info] Network interface "lo" state changed: up
2019-06-08 18:57:51.467600 [info] vSomeIP 2.10.21 | (default)
2019-06-08 18:57:51.469615 [info] utility::auto_configuration_exit: munmap succeeded.
[       OK ] vsomeip.one (17 ms)
[----------] 1 test from vsomeip (17 ms total)

[----------] Global test environment tear-down
[==========] 1 test from 1 test suite ran. (17 ms total)
[  PASSED  ] 1 test.
```
