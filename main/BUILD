config_setting(
    name = "darwin_mode",
    values = {"cpu": "darwin"},
)

cc_binary(
  name = "protoc-gen-demo",
  srcs = ["protoc-gen-demo.cc"],
  deps = [
    "@protobuf//:protoc_lib",
    "//lib:vsco-demo",
  ],

  # Travis Android builds use a really old c++ stdlib.
  # This option forces a "FULLY_STATIC" build per
  # <https://bazel.io/docs/be/c-cpp.html#cc_binary.linkstatic>
  # linkopts = ["-static"],
  linkopts = select({
    ":darwin_mode": [], 
    "//conditions:default": ["-static"]
  }),
)
