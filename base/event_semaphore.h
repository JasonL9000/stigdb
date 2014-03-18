/* <base/event_semaphore.h>

   TODO

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

#include <cstdint>
#include <cassert>

#include <base/fd.h>
#include <base/no_copy_semantics.h>

namespace Base {

  /* TODO */
  class TEventSemaphore {
    NO_COPY_SEMANTICS(TEventSemaphore);
    public:

    /* TODO */
    TEventSemaphore(uint64_t initial_count = 0, bool nonblocking = false);

    /* TODO */
    const TFd &GetFd() const {
      assert(this);
      return Fd;
    }

    /* If the nonblocking option was passed to the constructor, this returns
       true if the pop was successful, or false if the pop failed because the
       semaphore had a count of 0 immediately before the call.  It the
       nonblocking option was not passed to the constructor, this always
       returns true. */
    bool Pop();

    /* TODO */
    void Push(uint64_t count = 1);

    private:

    /* TODO */
    TFd Fd;

  };  // TEventSemaphore

}  // Base
