/* <stig/synth/atomic_type.cc>

   Implements <stig/synth/atomic_type.h>.

   Copyright 2010-2014 Stig LLC

   Licensed under the Apache License, Version 2.0 (the "License");
   you may not use this file except in compliance with the License.
   You may obtain a copy of the License at

     http://www.apache.org/licenses/LICENSE-2.0

   Unless required by applicable law or agreed to in writing, software
   distributed under the License is distributed on an "AS IS" BASIS,
   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
   See the License for the specific language governing permissions and
   limitations under the License. */

#include <stig/synth/atomic_type.h>

using namespace Stig;
using namespace Stig::Synth;

TAtomicType::TAtomicType(TGet get)
    : Get(get) {}

void TAtomicType::ForEachRef(const std::function<void (TAnyRef &)> &) {}

Type::TType TAtomicType::ComputeSymbolicType() const {
  assert(this);
  return Get();
}
