#include "lib/demo-generator.h"
#include <google/protobuf/compiler/plugin.h>

using namespace google::protobuf;

int main(int argc, char** argv) {
  vsco::protobuf::DemoGenerator generator;
  return compiler::PluginMain(argc, argv, &generator);
}
