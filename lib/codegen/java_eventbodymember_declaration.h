#ifndef VSCO_EVENTBODYMEMBER_DECLARATION_
#define VSCO_EVENTBODYMEMBER_DECLARATION_

#include "codegen.h"

using namespace google::protobuf;

namespace vsco {
namespace protobuf {

class JavaEventBodyMemberDeclaration : public CodeGen {
public:
  JavaEventBodyMemberDeclaration(const std::string& message_name)
    : CodeGen(message_name, "class_scope") {}
  virtual ~JavaEventBodyMemberDeclaration() {}
protected:
  virtual bool WriteCode(const std::string& filename,
                         compiler::GeneratorContext* context,
                         io::Printer *printer)
  {
    printer->Print("public interface EventBodyMember {\n");
    printer->Print("  public int getEventBodyMemberCode();\n");
    printer->Print("  public String getEventName();\n");
    printer->Print("}\n");
    return true;
  }
};

} // namespace protobuf
} // namespace vsco

#endif // VSCO_EVENTBODYMEMBER_DECLARATION_
