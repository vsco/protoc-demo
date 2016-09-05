#include "lib/demo-generator.h"
#include <google/protobuf/compiler/command_line_interface.h>
#include <google/protobuf/compiler/java/java_generator.h>
#include "test_utils/googletest.h"
#include "test_utils/file.h"
#include "gtest/gtest.h"

using namespace google::protobuf;

namespace vsco {
namespace protobuf {

// Just a basic test of command line invocation
// For an example of more extensive testing, see the plugin tests
// in the protobuf tree, such as
// <https://github.com/google/protobuf/blob/master/src/google/protobuf/compiler/java/java_plugin_unittest.cc>
TEST(PluginTest, CheckInsertions) {
  GOOGLE_CHECK_OK(File::SetContents(TestTempDir() + "/test.proto",
                             "syntax = \"proto2\";\n"
                             "package foo;\n"
                             "option java_package = \"\";\n"
                             "option java_outer_classname = \"Test\";\n"
                             "message Bar {\n"
                             "  message Baz {}\n"
                             "}\n"
                             "enum Qux { BLAH = 1; }\n",
                             true));

  compiler::CommandLineInterface cli;
  cli.SetInputsAreProtoPathRelative(true);

  compiler::java::JavaGenerator java_generator;
  DemoGenerator demo_generator;
  cli.RegisterGenerator("--java_out", &java_generator, "");
  cli.RegisterGenerator("--vsco-demo_out", &demo_generator, "");

  string proto_path = "-I" + TestTempDir();
  string java_out = "--java_out=" + TestTempDir();
  string vsco_demo_out = "--vsco-demo_out=" + TestTempDir();

  const char* argv[] = {
    "protoc",
    proto_path.c_str(),
    java_out.c_str(),
    vsco_demo_out.c_str(),
    "test.proto"
  };

  EXPECT_EQ(0, cli.Run(5, argv));
}

} // namespace protobuf
} // namespace vsco