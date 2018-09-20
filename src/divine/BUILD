package(default_visibility = ["//visibility:public"])


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
    name = "openai_api",
    srcs = ["openai_api.py"],
    deps = ["//src/proto:py_commons",
            "//src/environment:viewer",
            "//src/environment:environment"]
)

py_binary(
    name = "ddpg",
    srcs = ["agents/ddpg.py"],
    deps = ["//src/proto:py_commons",
            "//src/environment:viewer",
            "//src/environment:environment"]
)

