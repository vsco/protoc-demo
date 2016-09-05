#ifndef VSCO_JAVA_REFLECTION_IFACE_IMPLEMENTS_WRITER_
#define VSCO_JAVA_REFLECTION_IFACE_IMPLEMENTS_WRITER_

#include "java_reflection_iface_declaration_writer.h"

namespace vsco {
namespace protobuf {

const string impl_class = event_outer_classname + ".Map";

class JavaReflectionIfaceImplementsWriter : public CodeGen {
public:
  JavaReflectionIfaceImplementsWriter(const std::string& message_name)
    : CodeGen(message_name, "message_implements") {}
  virtual ~JavaReflectionIfaceImplementsWriter() {}
protected:
  virtual bool WriteCode(const string& filename,
                         compiler::GeneratorContext* context,
                         io::Printer *printer)
  {
    const string message = impl_class + ",\n";
    printer->Print(message.data());
    return true;
  }
};

} // namespace protobuf
} // namespace vsco

#endif // VSCO_JAVA_REFLECTION_IFACE_IMPLEMENTS_WRITER_
