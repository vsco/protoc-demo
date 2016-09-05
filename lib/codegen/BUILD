cc_library(
  name = "codegen",
  hdrs = glob(["*.h"]),
  srcs = glob(["*.cc"]),
  deps = [
    "@protobuf//:protobuf",
    "@protobuf//:protoc_lib",
  ],
  visibility = ["//lib:__pkg__"], 
)
