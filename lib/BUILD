cc_library(
  name = "vsco-demo",
  hdrs = glob(["*.h"]),
  srcs = glob(["*.cc"]),
  deps = [
    "//lib/codegen:codegen",
    "@protobuf//:protobuf",
    "@protobuf//:protoc_lib",
  ],
  visibility = ["//main:__pkg__", "//test:__pkg__"],
)
