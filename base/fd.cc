/* <base/fd.cc>

   Implements <base/fd.h>.

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

#include <base/fd.h>

#include <poll.h>
#include <unistd.h>

using namespace Base;

bool TFd::IsReadable(int timeout) const {
  assert(this);
  pollfd p;
  p.fd = OsHandle;
  p.events = POLLIN;
  int result;
  IfLt0(result = poll(&p, 1, timeout));
  return result != 0;
}

const TFd Base::In(STDIN_FILENO), Base::Out(STDOUT_FILENO), Base::Err(STDERR_FILENO);
