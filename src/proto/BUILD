load("@org_pubref_rules_protobuf//python:rules.bzl", "py_proto_compile")
load("@org_pubref_rules_protobuf//python:rules.bzl", "py_proto_library")

py_proto_library(
  name = "py_commons",
  protos = ["commons.proto", "world.proto", "object.proto"],
  with_grpc = False, # only one file is generated with or without grpc
  visibility = ["//visibility:public"],
)

cc_proto_library(
    name = "object_cc_proto",
    deps = [":object_proto"],
	visibility = ["//visibility:public"]
)

cc_proto_library(
    name = "commons_cc_proto",
    deps = [":commons_proto"],
	visibility = ["//visibility:public"]
)


cc_proto_library(
    name = "world_cc_proto",
    deps = [":world_proto"],
	visibility = ["//visibility:public"]
)

proto_library(
    name = "world_proto",
    srcs = ["world.proto"],
    deps = [":commons_proto",
            ":object_proto"]
)

proto_library(
    name = "object_proto",
    srcs = ["object.proto"],
    deps = [":commons_proto"],
)

proto_library(
    name = "commons_proto",
    srcs = ["commons.proto"],
    deps = [],
)
