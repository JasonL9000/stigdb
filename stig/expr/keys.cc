/* <stig/expr/keys.cc>

   Implements <stig/expr/keys.h>

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

#include <stig/expr/keys.h>

#include <stig/expr/visitor.h>
#include <stig/type/addr.h>
#include <stig/type/seq.h>
#include <stig/type/util.h>

using namespace Stig;
using namespace Stig::Expr;

TKeys::TPtr TKeys::New(const TAddr::TMemberVec &members, const Type::TType &value_type, const TPosRange &pos_range) {
  return TKeys::TPtr(new TKeys(members, value_type, pos_range));
}

TKeys::TKeys(const TAddr::TMemberVec &members, const Type::TType &value_type, const TPosRange &pos_range)
    : TNAry(members, pos_range), ValueType(value_type) {
}

void TKeys::Accept(const TVisitor &visitor) const {
  assert(this);
  assert(&visitor);
  visitor(this);
}

Type::TType TKeys::GetAddrType() const {
  assert(this);
  Type::TAddr::TElems elems;
  bool is_sequence = false;
  for (auto member : GetMembers()) {
    elems.push_back(std::make_pair(member.first, (member.second)->GetType()));
    is_sequence |= member.second->GetType().Is<Type::TSeq>();
  }
  Type::TType type = Type::TAddr::Get(elems);
  if (is_sequence) {
    type = Type::TSeq::Get(type);
  }
  return type;
}

Type::TType TKeys::GetType() const {
  return Type::TSeq::Get(this->GetAddrType());
}