cc_proto_library(
    name = "agent_cc_proto",
    deps = [":agent_proto"],
	visibility = ["//visibility:public"]
)

proto_library(
    name = "agent_proto",
    srcs = ["agent.proto"],
    deps = [":commons_proto"],
)

proto_library(
    name = "commons_proto",
    srcs = ["commons.proto"],
    deps = [],
)
