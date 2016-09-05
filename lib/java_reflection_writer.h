#ifndef VSCO_JAVA_REFLECTION_WRITER_
#define VSCO_JAVA_REFLECTION_WRITER_

#include <google/protobuf/descriptor.h>
#include <google/protobuf/descriptor.pb.h>
#include <google/protobuf/compiler/code_generator.h>

using namespace google::protobuf;

namespace vsco {
namespace protobuf {

class JavaReflectionWriter {
public:
  JavaReflectionWriter() {}
  virtual ~JavaReflectionWriter() {} 
  bool Write(const string& java_filename,
             const Descriptor* descriptor,
             compiler::GeneratorContext* context);
private:
  typedef std::map<FieldDescriptor::Type, std::string> TypeToJavaMap;
  static TypeToJavaMap typeToJavaMap;
};

} // namespace protobuf
} // namespace vsco

#endif // VSCO_JAVA_REFLECTION_WRITER_
