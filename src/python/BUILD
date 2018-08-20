package(default_visibility = ["//visibility:public"])
licenses(["notice"])  # Apache 2.0

load(
  "@io_bazel_rules_python//python:python.bzl",
  "py_binary", "py_library", "py_test",
)

load("@my_deps//:requirements.bzl", "requirement")

cc_library(
    name = "pybind11",
    hdrs = glob([
        "include/**/**/*.h",
    ]),
    linkopts = ["-pthread"],
    visibility = ["//visibility:public"],
    strip_include_prefix = "include/"
)

cc_binary(
  name = "divine_rl.so",
  srcs = glob(["python_bindings/*.cpp",
               "python_bindings/*.h"]),
  deps = ["@python_linux//:python-lib",
          "@pybind11//:pybind11",
         ],
  linkshared = 1
)

py_binary(
    name = "simulation",
    srcs = ["simulation.py"],
    deps = [
    ],
)