load("@protobuf//:protobuf.bzl", "cc_proto_library")

cc_proto_library(
    name = "cc_test_protos",
    srcs = ["resources/event.proto"],
    include = "resources/",
    default_runtime = "@protobuf//:protobuf",
    protoc = "@protobuf//:protoc",
    deps = ["@protobuf//:cc_wkt_protos"],
)

cc_test(
    name = "test",
    srcs = ["basic-test.cc"],
    copts = ["-Iexternal/gtest/include"],
    size = "small",
    deps = [
        ":cc_test_protos",
        "@gtest//:main",
        "@protobuf//:protoc_lib",
        "//lib:vsco-demo",
        "//test/test_utils:test_utils",
    ],
)
