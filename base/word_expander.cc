/* <base/word_expander.cc>

   Implements <base/word_expander.h>.

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

#include <base/word_expander.h>

#include <new>

#include <base/no_default_case.h>
#include <base/zero.h>

using namespace std;
using namespace Base;

TWordExpander::TWordExpander(const char *str, int flags) {
  /* Mask out all but the flags know we can deal with. */
  flags &= (WRDE_NOCMD | WRDE_UNDEF | WRDE_SHOWERR);
  /* Initialize the linux-standard structure.  If we get
     an error, barf meaningfully. */
  Zero(OsObj);
  switch (wordexp(str, &OsObj, 0)) {
    /* A-ok. */
    case 0: {
      break;
    }
    /* Out of memory. */
    case WRDE_NOSPACE: {
      throw bad_alloc();
    }
    /* Some random syntax error. */
    case WRDE_SYNTAX: {
      throw TError("word expander; syntax error");
    }
    /* Illegal occurence of a newline, operator, or punctuation. */
    case WRDE_BADCHAR: {
      throw TError("word expander; bad char");
    }
    /* Reference to an undefined shell variable.  If we don't get flag
       WRDE_UNDEF, this error is won't happen. */
    case WRDE_BADVAL: {
      throw TError("word expander; bad val");
    }
    /* We had to do a command substitution.  If we don't get flag
       WRDE_NOCMD, this error is won't happen. */
    case WRDE_CMDSUB: {
      throw TError("word expander; command substitution");
    }
    NO_DEFAULT_CASE;
  }
}

TWordExpander::~TWordExpander() {
  assert(this);
  wordfree(&OsObj);
}
