/* <base/word_expander.h>

   Basically just an RAII wrapper around the Linux wordexp() call.
   We don't do fancy on this one.

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

#pragma once

#include <cassert>
#include <stdexcept>

#include <wordexp.h>

#include <base/no_copy_semantics.h>

namespace Base {

  /* Constructs from a string and performs shell-like word expansion on it,
     breaking it into the familiar argc/argv arrangement.  This guy is
     sensitive to your environment and will pick up shell variables like
     $PATH.  So, if you're using this in a unit test, make sure you're not
     introducing environmental dependencies that could make your test
     fragile. */
  class TWordExpander final {
    NO_COPY_SEMANTICS(TWordExpander);
    public:

    /* An error thrown by our constructor if the string to be parsed isn't
       invalid in some way. */
    class TError final
        : public std::runtime_error {
      public:

      /* Pass-thru to our base class. */
      TError(const char *msg)
          : std::runtime_error(msg) {}

    };  // TWordExpander::TError

    /* Expand the string and make the argc/argv results available as members.
       Flags are as for wordexp(), but may only contain WRDE_NOCMD,
       WRDE_SHOWERROR, and/or WRDE_UNDEF.  The other flags, which have to do
       with reusing old buffer space or prefixing the argv array with nulls,
       are not supported.  If the given string contains errors, we throw a
       (moderately descriptive) TError.  If we run low on memory, we eschew the
       wordexp-specific OOM error and throw the conventional std::bad_alloc
       instead. */
    explicit TWordExpander(const char *str, int flags = 0);

    /* Frees up the secondary space used for argv and its members. */
    ~TWordExpander();

    /* The standard argc resulting from parsing the constructor's argument. */
    size_t GetArgc() const noexcept {
      assert(this);
      return OsObj.we_wordc;
    }

    /* The standard argv resulting from parsing the constructor's argument. */
    char **GetArgv() const noexcept {
      assert(this);
      return OsObj.we_wordv;
    }

    private:

    /* The structure used by wordexp(). */
    wordexp_t OsObj;

  };  // TWordExpander

}  // Base
