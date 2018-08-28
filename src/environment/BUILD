cc_library(
    name = "world",
    srcs = glob(["world/*.cpp", "observers/*.cpp", "dynamics/*.cpp"]),
    hdrs = glob(["world/*.h", "observers/*.h", "dynamics/*.h"]),
    deps = [
        "@com_github_eigen_eigen//:eigen",
        "@boost//:geometry",
        "//src/environment:commons",
        "//src/proto:object_cc_proto",
        "//src/proto:world_cc_proto",
    ],
    visibility = ["//visibility:public"],
)

cc_library(
    name = "commons",
    srcs = glob(["commons/*.cpp"]),
    hdrs = glob(["commons/*.h"]),
    deps = [
        "@com_github_eigen_eigen//:eigen",
        "@boost//:geometry",
    ],
    visibility = ["//visibility:public"],
)

py_binary(
    name = "environment",
    srcs = ["environment.py", "viewer/viewer.py"],
    data = ['//src/python_bindings:divine_rl.so', "//tests/python:object_test_data"],
    imports = ['./python_bindings'],
    deps = ["//src/proto:py_commons"]
)