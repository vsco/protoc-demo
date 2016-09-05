#ifndef VSCO_JAVA_REFLECTION_IFACE_DECLARATION_WRITER_
#define VSCO_JAVA_REFLECTION_IFACE_DECLARATION_WRITER_

#include "codegen.h"

#include <google/protobuf/descriptor.h>
#include <google/protobuf/descriptor.pb.h>
#include <google/protobuf/compiler/code_generator.h>

using namespace std;
using namespace google::protobuf;

namespace vsco {
namespace protobuf {

const string event_outer_classname = "ProtoEvent";

class JavaReflectionIFaceDeclarationWriter : public CodeGen {
public:JavaReflectionIFaceDeclarationWriter(const string& message_name)
  : CodeGen(message_name, "outer_class_scope") {}
  virtual ~JavaReflectionIFaceDeclarationWriter() {} 
protected:
  bool WriteCode(const string& filename,
                 compiler::GeneratorContext* context,
                 io::Printer *printer);
};

} // namespace protobuf
} // namespace vsco

#endif // VSCO_JAVA_REFLECTION_IFACE_DECLARATION_WRITER_
