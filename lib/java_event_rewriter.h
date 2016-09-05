#ifndef VSCO_JAVA_EVENT_REWRITER_
#define VSCO_JAVA_EVENT_REWRITER_

#include <google/protobuf/descriptor.h>
#include <google/protobuf/descriptor.pb.h>
#include <google/protobuf/compiler/code_generator.h>

using namespace google::protobuf;

namespace vsco {
namespace protobuf {

class JavaEventRewriter {
public:
  JavaEventRewriter() {}
  virtual ~JavaEventRewriter() {}
  bool Write(const string& java_filename,
             const Descriptor* event,
             compiler::GeneratorContext* context);
protected:
  bool WriteEventBodyMember(const string& java_filename,
                            const Descriptor* event,
                            int field_number,
                            compiler::GeneratorContext* context);
};

} // namespace protobuf
} // namespace vsco

#endif // VSCO_JAVA_EVENT_REWRITER_
