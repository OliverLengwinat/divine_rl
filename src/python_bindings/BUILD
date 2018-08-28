package(default_visibility = ["//visibility:public"])
licenses(["notice"])  # Apache 2.0

load(
  "@io_bazel_rules_python//python:python.bzl",
  "py_binary", "py_library", "py_test",
)

cc_binary(
  name = "divine_rl.so",
  srcs = glob(["*.cpp",
               "*.h"]),
  deps = ["@python_linux//:python-lib",
          "@pybind11//:pybind11",
          "//src/environment:world",
          "//src/environment:commons",
          "//src/proto:object_cc_proto",
          "//src/proto:world_cc_proto",
         ],
  linkshared = 1,
  linkstatic = 1,
)

