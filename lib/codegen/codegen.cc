#include "codegen.h"
#include <google/protobuf/io/zero_copy_stream.h>

using namespace std;
using namespace google::protobuf;

namespace vsco {
namespace protobuf {

bool
CodeGen::Write(const string& filename, compiler::GeneratorContext* context)
{
  scoped_ptr<io::ZeroCopyOutputStream> output(context->OpenForInsert(filename, insertion_point));
  io::Printer printer(output.get(), '$');

  printer.Print("\n// Begin code inserted by VSCO plugin.\n");
  if (!WriteCode(filename, context, &printer)) {
    return false;
  }
  printer.Print("// End code inserted by VSCO plugin.\n\n");

  // Return status is whether any i/o failed.
  return !printer.failed();
}

} // namespace protobuf
} // namespace vsco
