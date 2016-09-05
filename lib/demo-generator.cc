#include "lib/demo-generator.h"
#include "lib/java_event_rewriter.h"
#include "lib/java_reflection_writer.h"
#include "lib/codegen/java_reflection_iface_declaration_writer.h"
#include <google/protobuf/compiler/java/java_names.h>

#include <string>

using namespace std;
using namespace google::protobuf;

namespace vsco {
namespace protobuf {

const string java = ".java";

bool 
DemoGenerator::Generate(const FileDescriptor* file,
                        const string& parameter,
                        compiler::GeneratorContext* context,
                        string* error) const
{
  const string output_dir = FindOutputDir(file);

  // This demo is concerned with rewriting a specific Event protobuf.
  // When it's invoked in a larger build process, it may encounter proto
  // files it wasn't designed for.
  FileOptions options = file->options();
  if (options.java_outer_classname() != event_outer_classname) {
    return true;
  }

  // Adds an interface declaration to the outer class file specified
  // by the proto file.
  const string outer_class_file = output_dir + event_outer_classname + java;
  JavaReflectionIFaceDeclarationWriter iface_writer("");
  if (!iface_writer.Write(outer_class_file, context)) {
    return false;
  }

  // Loops through each message in the Event protobuf file and provides
  // a reflection capability to each. 
  for (int i = 0; i < file->message_type_count(); i++) {
    const Descriptor* message = file->message_type(i);
    const string java_filename = output_dir + message->name() + java;

    JavaReflectionWriter writer;
    if (!writer.Write(java_filename, message, context)) {
      return false;
    }

    // The "Event" message definition gets additional code generation
    // applied to it.
    if (message->name() == "Event") {
      JavaEventRewriter rewriter;
      if (!rewriter.Write(java_filename, message, context)) {
        return false;
      }
    }
  }

  return true;
}

// From 
// <https://github.com/grpc/grpc-java/blob/master/compiler/src/java_plugin/cpp/java_plugin.cpp>
string
DemoGenerator::FindOutputDir(const FileDescriptor* file) const
{
  string package_name = compiler::java::ClassName(file);
  size_t last_dot_pos = package_name.find_last_of('.');
  if (last_dot_pos != string::npos) {
    package_name.resize(last_dot_pos);
  } else {
    package_name = "";
  }

  string package_dir = package_name;
  for (size_t i = 0; i < package_dir.size(); ++i) {
    if (package_dir[i] == '.') {
      package_dir[i] = '/';
    }
  }

  if (!package_dir.empty()) {
    package_dir += "/";
  }

  return package_dir;
}

} // namespace protobuf
} // namespace vsco
