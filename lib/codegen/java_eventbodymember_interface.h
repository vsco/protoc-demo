#ifndef VSCO_EVENTBODYMEMBER_INTERFACE_
#define VSCO_EVENTBODYMEMBER_INTERFACE_

#include "codegen.h"

using namespace google::protobuf;

namespace vsco {
namespace protobuf {

class JavaEventBodyMemberInterface : public CodeGen {
public:
  JavaEventBodyMemberInterface(const std::string& message_name)
    : CodeGen(message_name, "message_implements") {}
  virtual ~JavaEventBodyMemberInterface() {}
protected:
  virtual bool WriteCode(const std::string& filename,
                         compiler::GeneratorContext* context,
                         io::Printer *printer)
  {
    printer->Print("EventBody.EventBodyMember,\n");
    return true;
  }
};

} // namespace protobuf
} // namespace vsco

#endif // VSCO_EVENTBODYMEMBER_INTERFACE_
