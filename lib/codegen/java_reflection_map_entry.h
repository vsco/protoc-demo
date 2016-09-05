#ifndef VSCO_JAVA_REFLECTION_MAP_ENTRY_
#define VSCO_JAVA_REFLECTION_MAP_ENTRY_

namespace vsco {
namespace protobuf {

enum javatype {
  list,
  enumeration,
  object,
  primitive,
  bigint,
  bytes
};

class JavaReflectionMapEntry {
public:
  JavaReflectionMapEntry(string key_name, string type_name, string value, javatype java_type) 
  : key_name(key_name), type_name(type_name), value(value), java_type(java_type) {}
  virtual ~JavaReflectionMapEntry() {}
  const string key_name;
  const string type_name;
  const string value;
  javatype java_type;
};

} // namespace protobuf
} // namespace vsco

#endif // VSCO_JAVA_REFLECTION_MAP_ENTRY_
