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
    name = "tensorforce_io",
    srcs = ["tensorforce_io.py"],
    deps = ["//src/proto:py_commons",
            "//src/environment:viewer",
            "//src/environment:environment"]
)

py_binary(
    name = "stablebaselines_ppo1",
    srcs = ["stablebaselines_ppo1.py"],
    deps = ["//src/proto:py_commons",
            "//src/environment:viewer",
            "//src/environment:environment"]
)
