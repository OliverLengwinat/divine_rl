py_binary(
    name = "run_structured",
    srcs = ["run_structured.py"],
    deps = ["//src/proto:py_commons",
            "//src/environment:viewer",
            "//src/environment:environment"]
)

py_binary(
    name = "run_unstructured",
    srcs = ["run_unstructured.py"],
    deps = ["//src/proto:py_commons",
            "//src/environment:viewer",
            "//src/environment:environment"]
)

py_binary(
    name = "ddpg",
    srcs = ["ddpg/ddpg.py"],
    deps = ["//src/proto:py_commons",
            "//src/environment:viewer",
            "//src/environment:environment"]
)