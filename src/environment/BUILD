cc_library(
    name = "world",
    srcs = glob(["world/*.cpp", "observers/*.cpp"]),
    hdrs = glob(["world/*.h", "observers/*.h"]),
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
    srcs = ["environment.py"],
    deps = []
)