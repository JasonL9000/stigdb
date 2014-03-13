/* <base/word_expander.test.cc>

   Unit test for <base/word_expander.h>.

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

#include <string>

#include <test/kit.h>

using namespace std;
using namespace Base;

FIXTURE(Typical) {
  TWordExpander we("hello doctor name");
  if (EXPECT_EQ(we.GetArgc(), 3U)) {
    EXPECT_EQ(string(we.GetArgv()[0]), "hello");
    EXPECT_EQ(string(we.GetArgv()[1]), "doctor");
    EXPECT_EQ(string(we.GetArgv()[2]), "name");
  }
}

