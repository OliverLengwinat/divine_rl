cc_test(
    name = "geometry_tests",
    srcs = [
        "geometry_tests.cpp",
    ],
    copts = ["-Iexternal/gtest/include"],
    deps = [
        "//src/environment:world",
        "//src/environment:commons",
        "@gtest//:main",
    ],
)

cc_test(
    name = "kinematics_tests",
    srcs = [
        "kinematics_tests.cpp",
    ],
    copts = ["-Iexternal/gtest/include"],
    deps = [
        "//src/environment:world",
        "//src/environment:commons",
        "@gtest//:main",
    ],
)

filegroup(
   name="agent_test_data",
   srcs=["agent.pb.txt"]
)

cc_test(
    name = "protobuf_tests",
    srcs = [
        "protobuf_tests.cpp",
    ],
    copts = ["-Iexternal/gtest/include"],
    deps = [
        "//src/environment:world",
        "//src/environment:commons",
        "@gtest//:main",
        "//src/proto:object_cc_proto"
    ],
    data = [":agent_test_data"]
)

