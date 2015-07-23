/*
Copyright 2013-2015 Stanford University

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

    http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.
*/

#include <array>

#include "src/opcode.h"
#include "src/fail.h"

using namespace std;
using namespace x64asm;
using namespace cpputil;

namespace {

constexpr array<const char*, X64ASM_NUM_OPCODES> att_() {
  return {
    // Internal mnemonics
    "<label>"
    // Auto-generated mnemonics
    #include "src/opcode.att"
  };
}

constexpr array<const char*, X64ASM_NUM_OPCODES> names_() {
  return {
    // Internal mnemonics
    "<label>"
    // Auto-generated mnemonics
    #include "src/opcode.names"
  };
}


} // namespace

namespace x64asm {

/** Get the at&t string representation of an opcode */
string opcode_write_att(Opcode o) {
  return string(att_()[o]);
}

/** Write the text representation of an opcode */
ostream& opcode_write_text(ostream& os, const x64asm::Opcode& op) {
  os << names_()[op];
  return os;
}

/** Read the text representation of an opcode */
istream& opcode_read_text(istream& is, x64asm::Opcode& op) {
  string s;
  is >> s;
  bool found = false;
  for(size_t i = 0; i < X64ASM_NUM_OPCODES; ++i) {
    if(string(names_()[i]) == s) {
      op = (Opcode)i;
      found = true;
      break;
    }
  }
  if(!found) {
    fail(is) << "Could not find opcode named '" << s << "'" << endl;
  }
  return is;
}

} // namespace x64asm



