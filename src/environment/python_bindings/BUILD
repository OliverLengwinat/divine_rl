package(default_visibility = ["//visibility:public"])
licenses(["notice"])  # Apache 2.0

load(
  "@io_bazel_rules_python//python:python.bzl",
  "py_binary", "py_library", "py_test",
)

load("@my_deps//:requirements.bzl", "requirement")


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

py_test(
  name = "geometry_tests",
  srcs = ["tests/geometry_tests.py"],
  data = [':divine_rl.so'],
  imports = ['.'],
  deps = [],
)

py_test(
  name = "kinematics_tests",
  srcs = ["tests/kinematics_tests.py"],
  data = [':divine_rl.so'],
  imports = ['.'],
  deps = [],
)

filegroup(
   name="object_test_data",
   srcs=["tests/object.pb.txt"]
)

py_test(
  name = "protobuf_tests",
  srcs = ["tests/protobuf_tests.py"],
  data = [":divine_rl.so", ":object_test_data"],
  imports = ['.'],
  deps = ["//src/proto:py_commons"],
)

py_test(
  name = "world_tests",
  srcs = ["tests/world_tests.py"],
  data = [':divine_rl.so'],
  imports = ['.'],
  deps = ["//src/proto:py_commons"],
)

py_test(
  name = "road_tests",
  srcs = ["tests/road_tests.py"],
  data = [':divine_rl.so'],
  imports = ['.'],
  deps = ["//src/proto:py_commons"],
)