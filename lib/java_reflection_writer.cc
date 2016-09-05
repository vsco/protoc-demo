#include "java_reflection_writer.h"
#include "codegen/java_reflection_map_entry.h"
#include "codegen/java_reflection_iface_implements_writer.h"
#include "codegen/java_reflection_iface_implementation_writer.h"

#include <iostream>
#include <string>
#include <cctype>

using namespace google::protobuf;
using namespace std;

namespace vsco {
namespace protobuf {

// Type mappings from
// https://github.com/google/protobuf/blob/master/java/util/src/main/java/com/google/protobuf/util/JsonFormat.java#L859
JavaReflectionWriter::TypeToJavaMap JavaReflectionWriter::typeToJavaMap = { 
  { FieldDescriptor::TYPE_INT32, "Integer" },
  { FieldDescriptor::TYPE_SINT32, "Integer" },
  { FieldDescriptor::TYPE_SFIXED32, "Integer" },
  { FieldDescriptor::TYPE_INT64, "Long" },
  { FieldDescriptor::TYPE_SINT64, "Long" },
  { FieldDescriptor::TYPE_SFIXED64, "Long" },
  { FieldDescriptor::TYPE_BOOL, "Boolean" },
  { FieldDescriptor::TYPE_FLOAT, "Float" },
  { FieldDescriptor::TYPE_DOUBLE, "Double" },
  { FieldDescriptor::TYPE_UINT32, "Long" },
  { FieldDescriptor::TYPE_FIXED32, "Long "},
  { FieldDescriptor::TYPE_UINT64, "java.math.BigInteger" },
  { FieldDescriptor::TYPE_FIXED64, "java.math.BigInteger" },
  { FieldDescriptor::TYPE_STRING, "String" },
  { FieldDescriptor::TYPE_BYTES, "com.google.protobuf.ByteString" },
};

bool
JavaReflectionWriter::Write(const string& java_filename,
                            const Descriptor* message,
                            compiler::GeneratorContext* context)
{
  JavaReflectionIfaceImplementsWriter interface_insertion(message->full_name());
  if (!interface_insertion.Write(java_filename, context)) {
    return false;
  }

  vector<shared_ptr<JavaReflectionMapEntry>> entries;
  for (int i = 0; i < message->field_count(); i++) {
    const FieldDescriptor* field = message->field(i);
    auto field_type = field->type();
    string box_type_string;
    string getter_string;
    string value;
    javatype java_type;
    getter_string = field->camelcase_name();
    getter_string[0] = toupper(getter_string[0]);


    if (field_type == FieldDescriptor::TYPE_ENUM) {
      const EnumDescriptor* ed = field->enum_type();
      if (ed->full_name() == "google.protobuf.NullValue") {
        continue;
      }

      box_type_string = "Integer";
      java_type = enumeration;
    } else if (field_type == FieldDescriptor::TYPE_MESSAGE) {
      box_type_string = "java.util.HashMap<String, Object>";
      java_type = object;
    } else if (field_type == FieldDescriptor::TYPE_UINT64 || field_type == FieldDescriptor::TYPE_FIXED64) {
      box_type_string = typeToJavaMap[field_type];
      java_type = bigint;
    } else if (field_type == FieldDescriptor::TYPE_BYTES) {
      box_type_string = typeToJavaMap[field_type];
      java_type = bytes;  
    } else {
      box_type_string = typeToJavaMap[field_type];
      java_type = primitive;
    }

    if (field->is_repeated()) {
      value = "this.get" + getter_string + "List()";
      java_type = list;
    } else {
      value = "this.get" + getter_string + "()";
    }


    shared_ptr<JavaReflectionMapEntry> entry(
      new JavaReflectionMapEntry(field->camelcase_name(),
                                 box_type_string, 
                                 value,
                                 java_type)
    );
    entries.push_back(entry);
  }

  // Recurse when nested types are encountered.
  for (int i = 0; i < message->nested_type_count(); i++) {
    if (!Write(java_filename, message->nested_type(i), context)) {
      return false;
    }
  }

  JavaReflectionIfaceImplementationWriter implementation_writer(message->full_name(), entries);
  return implementation_writer.Write(java_filename, context);
}

} // namespace protobuf
} // namespace vsco
