cc_library(
    name = "world",
    srcs = glob(["world/*.cpp"]),
    hdrs = glob(["world/*.h"]),
    deps = [
        "@com_github_eigen_eigen//:eigen",
        "@boost//:geometry",
        "//src/simulation:commons",
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

