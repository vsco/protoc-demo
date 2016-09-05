#ifndef VSCO_EVENTBODYMEMBER_IMPLEMENTATION_
#define VSCO_EVENTBODYMEMBER_IMPLEMENTATION_

#include "codegen.h"

using namespace google::protobuf;

namespace vsco {
namespace protobuf {

class JavaEventBodyMemberImplementation : public CodeGen {
public:
  JavaEventBodyMemberImplementation(const std::string& message_name, int field_number, const std::string& name)
    : CodeGen(message_name, "class_scope"), field_number(field_number), name(name) {}
  virtual ~JavaEventBodyMemberImplementation() {}
protected:
  int field_number;
  std::string name;
  virtual bool WriteCode(const std::string& filename,
                         compiler::GeneratorContext* context,
                         io::Printer *printer)
  {
    printer->Print("private int eventBodyMemberCodeGenerated_ = $field_number$;\n", "field_number", to_string(field_number));
    printer->Print("public int getEventBodyMemberCode() { return eventBodyMemberCodeGenerated_; }\n");
    printer->Print("private String eventBodyNameGenerated_ = new String(\"$name$\");\n", "name", name);
    printer->Print("public String getEventName() {\n");
    printer->Print("  return eventBodyNameGenerated_;\n");
    printer->Print("}\n");
    return true;
  }
};

} // namespace protobuf
} // namespace vsco

#endif // VSCO_EVENTBODYMEMBER_IMPLEMENTATION_
