/* <tools/demangle.cc>

   Take all given command line arguments and demangle them.

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

#include <iostream>

#include <base/demangle.h>
#include <base/error.h>

using namespace Base;
using namespace std;


int main(int argc, char **argv) {
  if(argc <= 1) {
    cout<<"USAGE: "<<argv[0]<<" mangled_name [...]"<<endl;
    return -1;
  }

  for(int i=1; i<argc; ++i) {
    try {
      std::cout<<argv[i]<<" -> ";
      std::cout<<TDemangle(argv[i]).Get()<<std::endl;
    } catch (const TDemangleError &ex) {
      std::cout<<ex.what()<<std::endl;
    }
  }
  return 0;
}