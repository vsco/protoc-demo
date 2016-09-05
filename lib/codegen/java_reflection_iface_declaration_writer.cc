#include "java_reflection_iface_declaration_writer.h"

namespace vsco {
namespace protobuf {

bool
JavaReflectionIFaceDeclarationWriter::WriteCode(const string& filename,
                                                compiler::GeneratorContext* context,
                                                io::Printer *printer)
{
  printer->Print("public interface Map {\n");
  printer->Print("  public java.util.Map<String, Object> asMap();\n");
  printer->Print("}\n");
  return true;
}

} // namespace protobuf
} // namespace vsco
