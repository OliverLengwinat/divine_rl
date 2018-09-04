cc_library(
    name = "world",
    srcs = glob(["world/*.cpp", "observers/*.cpp", "dynamics/*.cpp"]),
    hdrs = glob(["world/*.h", "observers/*.h", "dynamics/*.h"]),
    deps = [
        "@com_github_eigen_eigen//:eigen",
        "@boost//:geometry",
        "//src/environment:commons",
        "//src/proto:object_cc_proto",
        "//src/proto:commons_cc_proto",
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

py_library(
    name = "viewer",
    srcs = ["viewer/viewer.py"],
    data = ['//src/python_bindings:divine_rl.so'],
    imports = ['../../python_bindings'],
    deps = ["//src/proto:py_commons"],
    visibility = ["//visibility:public"],
)

py_library(
    name = "environment",
    srcs = ["environment.py"],
    data = ['//src/python_bindings:divine_rl.so',
            "//tests/python:world_test_data"],
    imports = ['../python_bindings'],
    deps = ["//src/proto:py_commons",
            ":viewer"],
    visibility = ["//visibility:public"],
)