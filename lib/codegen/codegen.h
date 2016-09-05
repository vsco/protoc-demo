#ifndef VSCO_CODEGEN_
#define VSCO_CODEGEN_

#include <google/protobuf/compiler/code_generator.h>
#include <google/protobuf/io/printer.h>

using namespace std;
using namespace google::protobuf;

namespace vsco {
namespace protobuf {

class CodeGen {
public:
  CodeGen(const string& message_name, const string insertion_name)
  : message_name(message_name),
    insertion_name(insertion_name),
    insertion_point(insertion_name) {
      if (!message_name.empty()) {
        insertion_point = insertion_name + ":" + message_name;
      }
    }
  virtual ~CodeGen() {}
  bool Write(const string& filename, compiler::GeneratorContext* context);
protected:
  virtual bool WriteCode(const string& filename,
                         compiler::GeneratorContext* context,
                         io::Printer *printer) = 0;
  string message_name;
  string insertion_name;
  string insertion_point;
};

} // namespace protobuf
} // namespace vsco

#endif // VSCO_CODEGEN_
