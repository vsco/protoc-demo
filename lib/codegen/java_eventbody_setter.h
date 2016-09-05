#ifndef VSCO_EVENTBODY_SETTER_
#define VSCO_EVENTBODY_SETTER_

#include "codegen.h"

using namespace google::protobuf;

namespace vsco {
namespace protobuf {

class JavaEventBodySetter : public CodeGen {
public:
  JavaEventBodySetter(const std::string& message_name)
    : CodeGen(message_name, "class_scope") {}
  virtual ~JavaEventBodySetter() {}
protected:
  virtual bool WriteCode(const std::string& filename,
                         compiler::GeneratorContext* context,
                         io::Printer *printer)
  {
    printer->Print("public void setEventBodyMember(EventBodyMember ebm) {\n");
    printer->Print("  this.body_ = ebm;\n");
    printer->Print("  this.bodyCase_ = ebm.getEventBodyMemberCode();\n");
    printer->Print("}\n");
    return true;
  }
};

} // namespace protobuf
} // namespace vsco

#endif // VSCO_EVENTBODY_SETTER_
