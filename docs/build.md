# BUILDING STIG

## Quick Start

```
git clone http://github.com/stigdb/stigdb.git ./src
cd src
chmod +x bootstrap.sh
make
make test
```

## Supported Platforms

Stig should work on any Linux-based operating system which uses kernel version 2.6.32 or greater.

The versions on which it is known to build and run:

* [Ubuntu 13.10](http://releases.ubuntu.com/13.10/)
* [CentOS 6.4](http://isoredirect.centos.org/centos/6/isos/x86_64/)
* [Arch Linux](https://www.archlinux.org)

## Pre-Requisites

There are several prerequisites which must be installed for a successful build of Stig:

### Compiler

* gcc-4.8.2 or above (4.8.0 has a nasty bug which craters Stig). 4.7 will work for the moment, but we'll be adopting some C++11 features it doesn't short in the near future.

Shortly Stig will be switching from gcc to clang+LLVM 3.4, but at this moment compiling with clang is not yet supported.

### Libraries

* glibc
* libaio
* libgmp
* libgmpxx
* libgomp
* libicuuc
* libreadline
* libsctp
* libsnappy
* libuuid
* libz
* pthread

### Other programs

* git

### Platform-specific package install command lines

#### Ubuntu

```
apt-get install flex bison util-linux git build-essential uuid-dev libaio-dev libgmp-dev libsctp-dev lksctp-tools zlib1g-dev libicu-dev libreadline6-dev libsnappy-dev
```

#### CentOS

```
yum groupinstall "Development Tools" --exclude=git
yum install flex bison util-linux uuid-devel libaio-devel gmp-devel mpfr-devel libmpc-devel libuuid-devel glibc-devel libicu-devel lksctp-tools lksctp-tools-devel readline-devel zlib-devel snappy-devel
```

## Retrieving the Stig source code

Currently the build system requires that the Stig source code be located in a directory named `src`.

The Stig source code is located in the [stigdb](http://github.com/stigdb/stigdb) repository on Github. To clone the repository:

```
git clone http://github.com/stigdb/stigdb.git ./src
```

Naturally, adjust the destination path above accordingly for your needs. Just be sure the code ends up in a directory named `src`.

## Build Commands

While Stig has a Makefile, it's just a basic wrapper for Stig's `starsha` build tool.

### make

Runs `bootstrap.sh`. This builds the `starsha` build tool and then builds the core Stig apps. Behind the scenes, it's actually running these two commands:

```
make tools/starsha
make apps
```

### make test

Builds and then runs the Stig unit test suite.

NOTE: A number of the tests require specialized permissions to run.

### make test_lang

Builds and then runs the Stig language tests.

This is an optional step. It takes quite a while to run.

NOTE: Your limit for number of open files must be greater than 4096, or some tests will spuriously fail.

### make clean

Deletes the `../.starsha/.notes` file, the `../out` directory and the `starsha` binary.

This is an optional step. If you hit a build error, run this command before re-running the build.

## Platform-specific

### Ubuntu (13.10 and above)

TBD

### CentOS (6.4 and above)

TBD

## Troubleshooting

If the build ever fails, please run the following before trying again:

```
make clean
```

TBD as problems arise.

## gcc compile tips

gcc can be a real bear to compile, but if your Linux distribution does not have a package available for a gcc version higher than 4.8.0, you'll need to compile it from source.

The [gcc installation docs](http://gcc.gnu.org/install/index.html) and [wiki](http://gcc.gnu.org/wiki/InstallingGCC) have a lot of good information on how to do this compile and installation from source. However, we've a few additional tips which may make the process go a little more smoothly:

* The easiest way to get all of the gcc dependencies downloaded and placed where the build process can locate them is to use the `./contrib/download_prerequisites` script in the gcc source directory.
* We've found that the gcc build frequently will fail when building for Java compiling. As Stig has no need for this, we typically run `configure` with the `--enable-languages=c,c++` flag.
* Make sure to use `--prefix=` during configuration and set it to a directory which will be in your `$PATH`, `$LD_LIBRARY_PATH`, and `$LD_RUN_PATH` (or be sure to add it to these paths after the installation is complete).

-----

build.md Copyright 2010-2014 Stig LLC

build.md is licensed under a Creative Commons Attribution-ShareAlike 4.0 International License.

You should have received a copy of the license along with this work. If not, see <http://creativecommons.org/licenses/by-sa/4.0/>.
