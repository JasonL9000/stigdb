/* <base/cmd.test.cc>

   Unit test for <base/cmd.h>.

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

#include <base/cmd.h>

#include <iostream>
#include <stdexcept>

#include <wordexp.h>

#include <base/zero.h>
#include <test/kit.h>

using namespace std;

class TWordExp final {
  NO_COPY_SEMANTICS(TWordExp);
  public:

  /* TODO */
  explicit TWordExp(const char *str) {
    Base::Zero(Os);
    switch (wordexp(str, &Os, 0)) {
      case 0: {
        break;
      }
      default: {
        throw runtime_error("barf");
      }
    }
  }

  /* TODO */
  ~TWordExp() {
    assert(this);
    wordfree(&Os);
  }

  /* TODO */
  size_t GetArgc() const noexcept {
    assert(this);
    return Os.we_wordc;
  }

  /* TODO */
  char **GetArgv() const noexcept {
    assert(this);
    return Os.we_wordv;
  }

  /* TODO */
  wordexp_t Os;

};  // TWordExp

FIXTURE(Typical) {
  TWordExp we("--hello --doctor --name=$PATH");
  for (size_t i = 0; i < we.GetArgc(); ++i) {
    cout << i << ", \"" << we.GetArgv()[i] << '"' << endl;
  }
}

#if 0
#include <base/cmd.h>

#include <cstring>
#include <initializer_list>
#include <string>
#include <vector>

#include <base/no_copy_semantics.h>
#include <socket/address.h>

#include <test/kit.h>

using namespace std;

class TShape
    : public Base::TCmd {
  public:

  bool IsFilled, IsOutlined;

  double LineWeight;

  vector<int> Things, OtherThings;

  set<int> UniqueThings;

  set<int> Ids;

  set<Socket::TAddress> Addrs;

  protected:

  TShape()
      : IsFilled(false), IsOutlined(false), LineWeight(1.2), OtherThings({ 99, 98, 97 }), Ids({ 1, 2, 3 }) {}

  class TMeta
      : public TCmd::TMeta {
    protected:

    TMeta(const char *desc)
        : TCmd::TMeta(desc) {
      Param(&TShape::IsFilled, "is_filled", Optional, "filled\0", "The shape should be drawn filled-in.");
      Param(&TShape::IsOutlined, "is_outlined", Optional, "outlined\0", "The shape should be drawn with an outline.");
      Param(&TShape::LineWeight, "line_weight", Optional, "line_weight\0lw\0", "The weight of the line used to outline, in points.");
      Param(&TShape::Things, "thing", Optional, "thing\0t\0", "A thing, which is a number.");
      Param(&TShape::OtherThings, "other_thing", Optional, "other_thing\0ot\0", "Other thing, which is a number.");
      Param(&TShape::UniqueThings, "unique_thing", Optional, "unique_thing\0ut\0", "Unique thing, which is a number.");
      ParamCsv(&TShape::Ids, "ids", Optional, "ids\0", "A CSV of id numbers.");
      ParamCsv(&TShape::Addrs, "addrs", Optional, "addrs\0", "A CSV of IP addresses.");
    }

  };

};

class TCircle
    : public TShape {
  public:

  TCircle(int argc, char *argv[])
      : Radius(1.0) {
    Parse(argc, argv, TMeta());
  }

  double Radius;

  private:

  class TMeta
      : public TShape::TMeta {
    public:

    TMeta()
        : TShape::TMeta("Draw a circle.") {
      Param(&TCircle::Radius, "radius", Required, "The radius of the circle.");
    }

  };

};

class TArgs {
  NO_COPY_SEMANTICS(TArgs);
  public:

  TArgs(initializer_list<const char *> strs) {
    try {
      for (const char *str: strs) {
        char *dup = strdup(str);
        try {
          Strs.push_back(dup);
        } catch (...) {
          free(dup);
          throw;
        }
      }
      Strs.push_back(nullptr);
    } catch (...) {
      Cleanup();
      throw;
    }
  }

  ~TArgs() {
    Cleanup();
  }

  int GetArgc() const {
    return Strs.size() - 1;
  }

  char **GetArgv() const {
    return const_cast<char **>(&Strs[0]);
  }

  private:

  void Cleanup() {
    for (char *str: Strs) {
      free(str);
    }
  }

  vector<char *> Strs;

};

FIXTURE(Typical) {
  TArgs args({ "a/b/c/prog", "2.5" });
  TCircle circle(args.GetArgc(), args.GetArgv());
  EXPECT_EQ(string(circle.GetDir()), string("a/b/c"));
  EXPECT_EQ(string(circle.GetProg()), string("prog"));
  EXPECT_FALSE(circle.IsFilled);
  EXPECT_EQ(circle.Radius, 2.5);
}

FIXTURE(Things) {
  TArgs args { "a/b/c/prog", "--t=101", "--t=202", "2.5" };
  TCircle circle(args.GetArgc(), args.GetArgv());
  if (EXPECT_EQ(circle.Things.size(), 2U)) {
    EXPECT_EQ(circle.Things[0], 101);
    EXPECT_EQ(circle.Things[1], 202);
  }
  if (EXPECT_EQ(circle.OtherThings.size(), 3U)) {
    EXPECT_EQ(circle.OtherThings[0], 99);
    EXPECT_EQ(circle.OtherThings[1], 98);
    EXPECT_EQ(circle.OtherThings[2], 97);
  }
  EXPECT_EQ(circle.Radius, 2.5);
}

FIXTURE(OtherThings) {
  TArgs args { "a/b/c/prog", "--t=101", "--t=202", "--ot=500", "--ot=501", "--ot=502", "2.5" };
  TCircle circle(args.GetArgc(), args.GetArgv());
  if (EXPECT_EQ(circle.Things.size(), 2U)) {
    EXPECT_EQ(circle.Things[0], 101);
    EXPECT_EQ(circle.Things[1], 202);
  }
  if (EXPECT_EQ(circle.OtherThings.size(), 3U)) {
    EXPECT_EQ(circle.OtherThings[0], 500);
    EXPECT_EQ(circle.OtherThings[1], 501);
    EXPECT_EQ(circle.OtherThings[2], 502);
  }
  EXPECT_EQ(circle.Radius, 2.5);
}

FIXTURE(UniqueThings) {
  TArgs args { "a/b/c/prog", "--ut=101", "--ut=202", "2.5" };
  TCircle circle(args.GetArgc(), args.GetArgv());
  if (EXPECT_EQ(circle.UniqueThings.size(), 2U)) {
    auto iter = circle.UniqueThings.begin();
    EXPECT_EQ(*iter++, 101);
    EXPECT_EQ(*iter++, 202);
  }
  EXPECT_EQ(circle.Radius, 2.5);
}

FIXTURE(Ids) {
  TArgs args { "a/b/c/prog", "--ids=31,32,33", "2.5" };
  TCircle circle(args.GetArgc(), args.GetArgv());
  if (EXPECT_EQ(circle.Ids.size(), 3U)) {
    auto iter = circle.Ids.begin();
    EXPECT_EQ(*iter++, 31);
    EXPECT_EQ(*iter++, 32);
    EXPECT_EQ(*iter++, 33);
  }
  EXPECT_EQ(circle.Radius, 2.5);
}

FIXTURE(Addrs) {
  TArgs args { "a/b/c/prog", "--addrs=192.168.10.11:9999,192.168.10.12:9999", "2.5" };
  TCircle circle(args.GetArgc(), args.GetArgv());
  if (EXPECT_EQ(circle.Addrs.size(), 2U)) {
    auto iter = circle.Addrs.begin();
    sockaddr_in sa;
    sa.sin_family = AF_INET;
    sa.sin_port = htons(9999);
    sa.sin_addr.s_addr = htonl(0xC0A80A0B);
    EXPECT_EQ(*iter++, Socket::TAddress(reinterpret_cast<const sockaddr &>(sa)));
    sa.sin_addr.s_addr = htonl(0xC0A80A0C);
    EXPECT_EQ(*iter++, Socket::TAddress(reinterpret_cast<const sockaddr &>(sa)));
  }
  EXPECT_EQ(circle.Radius, 2.5);
}

FIXTURE(ArgsFile) {
  TArgs args({ "a/b/c/prog", "--args=" SRC_ROOT "base/cmd.test.args", "2.5" });
  TCircle circle(args.GetArgc(), args.GetArgv());
  EXPECT_TRUE(circle.IsFilled);
  EXPECT_TRUE(circle.IsOutlined);
  EXPECT_EQ(circle.LineWeight, 3.0);
  if (EXPECT_EQ(circle.Things.size(), 2U)) {
    EXPECT_EQ(circle.Things[0], 101);
    EXPECT_EQ(circle.Things[1], 202);
  }
  if (EXPECT_EQ(circle.OtherThings.size(), 3U)) {
    EXPECT_EQ(circle.OtherThings[0], 500);
    EXPECT_EQ(circle.OtherThings[1], 501);
    EXPECT_EQ(circle.OtherThings[2], 502);
  }
  EXPECT_EQ(circle.Radius, 2.5);
}
#endif

