#ifndef LIB_VSCO_DEMO_GENERATOR_
#define LIB_VSCO_DEMO_GENERATOR_

#include <google/protobuf/compiler/code_generator.h>
#include <google/protobuf/descriptor.h>

#include <string>

using namespace std;
using namespace google::protobuf;

namespace vsco {
namespace protobuf {

class DemoGenerator : public compiler::CodeGenerator {
public:
  DemoGenerator() {}
  virtual ~DemoGenerator() {}

  virtual bool Generate(const google::protobuf::FileDescriptor* file,
                        const string& parameter,
                        compiler::GeneratorContext* context,
                        string* error) const;
private:
  string FindOutputDir(const FileDescriptor* file) const;
};

} // namespace protobuf
} // namespace vsco

#endif // LIB_VSCO_DEMO_GENERATOR_
