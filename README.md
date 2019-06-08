# GENIVI/vsomeip Bazel Example

# Requirements

This project has only been tested on Ubuntu 18 (bionic).

# Setup

Run the 'ubuntu' script.

# Dependencies

- [GoogleTest](https://github.com/google/googletest) for unit testing and mocking
- [GENIVI/vsomeip](https://github.com/GENIVI/vsomeip) SOME/IP stands for Scalable service-Oriented MiddlewarE over IP

# Origin

This project was created via the [Abseil Bazel Quickstart](https://abseil.io/docs/cpp/quickstart) on March 2019.

# VirtualBox Tips

If you share a github folder on your host, you need to enable symlinking to it. Run the following command from the host's command line. Replace virtual_machine_name and share_name in the following command:

```
VBoxManage setextradata virtual_machine_name VBoxInternal2/SharedFoldersEnableSymlinksCreate/share_name  1
```

# Visual Studio Code Configuration

## Extensions

- vscode-bazel
- C/C++ (Microsoft)
- EditorConfig
- Rainbow Brackets
- GitLens

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

The subdirectory of bazel-out depends on your operating system. For Ubuntu, it's
k8-fastbuild.

```bash
bazel-out/k8-fastbuild/bin/test/test -s
```
