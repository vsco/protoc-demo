#ifndef VSCO_JAVA_REFLECTION_IFACE_IMPLEMENTATION_WRITER_
#define VSCO_JAVA_REFLECTION_IFACE_IMPLEMENTATION_WRITER_

#include "codegen.h"
#include "java_reflection_map_entry.h"
#include <memory>

using namespace std;

namespace vsco {
namespace protobuf {

class JavaReflectionIfaceImplementationWriter : public CodeGen {
public:
  JavaReflectionIfaceImplementationWriter(const string& message_name, 
                                          vector<shared_ptr<JavaReflectionMapEntry>> entries)
    : CodeGen(message_name, "class_scope"), entries(entries) {}
  virtual ~JavaReflectionIfaceImplementationWriter() {}
protected:
  vector<shared_ptr<JavaReflectionMapEntry>> entries;
  virtual bool WriteCode(const string& filename,
                         compiler::GeneratorContext* context,
                         io::Printer *printer);
};

} // namespace protobuf
} // namespace vsco

#endif // VSCO_JAVA_REFLECTION_IFACE_IMPLEMENTATION_WRITER_
