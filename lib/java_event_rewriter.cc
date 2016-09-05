#include "lib/java_event_rewriter.h"

#include "lib/codegen/java_eventbody_setter.h"
#include "lib/codegen/java_eventbodymember_declaration.h"
#include "lib/codegen/java_eventbodymember_interface.h"
#include "lib/codegen/java_eventbodymember_implementation.h"

using namespace google::protobuf;

namespace vsco {
namespace protobuf {

bool
JavaEventRewriter::Write(const string& java_filename,
                         const Descriptor* event,
                         compiler::GeneratorContext* context)
{  
  // Find the EventBody type descriptor so we can build a list of nested Message types
  const Descriptor* eventBody = event->FindNestedTypeByName("EventBody");
  if (!eventBody) {
    return false;
  }

  // Find the Oneof inside EventBody
  const OneofDescriptor* body = eventBody->FindOneofByName("body");
  if (!body) {
    return false;
  }

  // Write a setter implementation for EventBody that takes an EventBodyMember
  JavaEventBodySetter eventbody_setter(eventBody->full_name());
  if (!eventbody_setter.Write(java_filename, context)) {
    return false;
  }

  JavaEventBodyMemberDeclaration interface_declaration(eventBody->full_name());
  if (!interface_declaration.Write(java_filename, context)) {
    return false;
  }

  for (int i = 0; i < body->field_count(); i++) {
    const FieldDescriptor* field = body->field(i);

    if (field->type() != FieldDescriptor::TYPE_MESSAGE) {
      return false;
    }

    const Descriptor* message = field->message_type();
    if (!WriteEventBodyMember(java_filename, message, field->number(), context)) {
      return false;
    }
  }

  return true;
}

bool
JavaEventRewriter::WriteEventBodyMember(const string& java_filename,
                                        const Descriptor* event,
                                        int field_number,
                                        compiler::GeneratorContext* context)
{
  JavaEventBodyMemberInterface interface_insertion(event->full_name());
  if (!interface_insertion.Write(java_filename, context)) {
    return false;
  }

  JavaEventBodyMemberImplementation implementation_insertion(event->full_name(), field_number, event->name());
  if (!implementation_insertion.Write(java_filename, context)) {
    return false;
  }

  return true;
}

} // namespace protobuf
} // namespace vsco