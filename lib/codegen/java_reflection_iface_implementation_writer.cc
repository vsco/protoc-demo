#include "java_reflection_iface_implementation_writer.h"

using namespace google::protobuf;

namespace vsco {
namespace protobuf {

bool
JavaReflectionIfaceImplementationWriter::WriteCode(const std::string& filename,
                                                   compiler::GeneratorContext* context,
                                                   io::Printer *printer)
{
  printer->Print("public java.util.Map<String, Object> asMap() {\n");
  printer->Print("  java.util.Map<String, Object> map = new java.util.HashMap<>();\n");
  for (auto it = entries.begin(); it != entries.end(); ++it) {
    shared_ptr<JavaReflectionMapEntry> entry = *it;
    printer->Print("  map.put(new String(\"");
    printer->Print(entry->key_name.data());
    printer->Print("\"), ");

    switch (entry->java_type) {
      case list:
        printer->Print(entry->value.data());
        printer->Print(");\n");
        break;
      case object:
        printer->Print(entry->value.data());
        printer->Print(" == null ? null : ");
        printer->Print(entry->value.data());
        printer->Print(".asMap());\n");
        break;
      case primitive:
        printer->Print("new ");
        printer->Print(entry->type_name.data());
        printer->Print("(");
        printer->Print(entry->value.data());
        printer->Print("));\n");
        break;
      case bigint:
        printer->Print(entry->type_name.data());
        printer->Print(".valueOf(");
        printer->Print(entry->value.data());
        printer->Print("));\n");
        break;        
      case bytes:
        printer->Print(entry->type_name.data());
        printer->Print(".copyFrom(");
        printer->Print(entry->value.data());
        printer->Print(".toByteArray()));\n");
        break;  
      case enumeration:
        printer->Print("new ");
        printer->Print(entry->type_name.data());
        printer->Print("(");
        printer->Print(entry->value.data());
        printer->Print(".getNumber()");
        printer->Print("));\n");
        break;
    }
  }
  printer->Print("  return map;\n");
  printer->Print("}\n");
  return true;
}

} // namespace protobuf
} // namespace vsco
