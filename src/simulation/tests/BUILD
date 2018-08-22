cc_test(
    name = "geometry_tests",
    srcs = [
        "geometry_tests.cpp",
    ],
    copts = ["-Iexternal/gtest/include"],
    deps = [
        "//src/simulation:world",
        "//src/simulation:commons",
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
        "//src/simulation:world",
        "//src/simulation:commons",
        "@gtest//:main",
    ],
)

