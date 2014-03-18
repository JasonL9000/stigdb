# BUILDING STIG

* [Quick Start](#quick-start)
* [Supported Platforms](#supported-platforms)
* [Pre-Requisites](#pre-requisites)
    * [Compiler](#compiler)
    * [Libraries](#libraries)
    * [Other programs](#other-programs)
    * [Platform-specific package install command lines](#platform-specific-package-install-command-lines)
        * [Ubuntu](#ubuntu)
        * [CentOS](#centos)
* [Retrieving the Stig Source Code](#retrieving-the-stig-source-code)
* [Build Commands](#build-commands)
    * [make](#make)
    * [make test](#make-test)
    * [make test_lang](#make-test_lang)
    * [make clean](#make-clean)
* [Platform-specific](#platform-specific)
    * [Ubuntu (13.10 and above)](#ubuntu-1310-and-above)
    * [CentOS (6.4 and above)](#centos-64-and-above)
* [Troubleshooting](#troubleshooting)
* [gcc compile tips](#gcc-compile-tips)

## Quick Start

The below will build stig in _debug_ mode:

```
(create a separate stig partition)
(install prerequisites for your platform per below)
cd ~
git clone git://github.com/stigdb/stigdb.git ./src
cd src
export PATH=${PATH}:${HOME}/src/tools
chmod +x bootstrap.sh
make
make test
```

To build stig in _release_ mode, simply replace the `make` line above with `make release`.

## Supported Platforms

Stig should work on any Linux-based operating system which uses kernel version 2.6.32 or greater.

The versions on which it is known to build and run:

* [Ubuntu 13.10](http://releases.ubuntu.com/13.10/)
* [CentOS 6.4](http://isoredirect.centos.org/centos/6/isos/x86_64/)
* [Arch Linux](https://www.archlinux.org)

## Create a new partition/volume

Because of the specialized nature of its storage requirements, Stig must maintain its database files in a separate partition/volume.

While this step is not required for building the Stig binaries, it may be something you'd prefer to do prior to installing any other required software.

Please create the new partition according to the directions for your Linux distribution. The minimum recommended partition size is 1GB. 

**WARNING!** Stig will overwrite and destroy any data which exists in this partition. Please do not re-use a partition which contains information you'd like to retain.

## Pre-Requisites

There are several prerequisites which must be installed for a successful build of Stig:

### Compiler

* gcc-4.8.2 or above (4.8.0 has a nasty bug which craters Stig and 4.8.1 has several bugs in its handling of c++11). 4.7 will work for the moment, but we'll be adopting some C++11 features which 4.7 doesn't support in the near future. So it's best you just start out with a more modern version of the compiler.
    * The preferred method of installing gcc-4.8.2 is to use [a pre-compiled binary](https://launchpad.net/~ubuntu-toolchain-r/+archive/test?field.series_filter=saucy). If that does not work or is not available for your Linux distribution, please see the [gcc compile tips](#gcc-compile-tips) below.

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
* valgrind

### Platform-specific package install command lines

#### Ubuntu

```
apt-get install flex bison util-linux git build-essential uuid-dev libaio-dev libgmp-dev libsctp-dev lksctp-tools zlib1g-dev libicu-dev libreadline6-dev libsnappy-dev valgrind
```

#### CentOS

```
yum groupinstall "Development Tools" --exclude=git
yum install flex bison util-linux uuid-devel libaio-devel gmp-devel mpfr-devel libmpc-devel libuuid-devel glibc-devel libicu-devel lksctp-tools lksctp-tools-devel readline-devel zlib-devel snappy-devel valgrind
```

## Retrieving the Stig source code

Currently the build system requires that the Stig source code be located in a directory named `src`.

The Stig source code is located in the [stigdb](http://github.com/stigdb/stigdb) repository on Github. To clone the repository:

```
git clone git://github.com/stigdb/stigdb.git ./src
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

**NOTA BENE**: The `starsha` build tool is designed to compile Stig as quickly as possible. In order to do this, it grabs as many system resources as it can. This means that running starsha _will peg your machine_. The build will finish quickly, but in the duration you may find that other applications will not be very responsive.

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

### make clean

If the build ever fails, please run the following before trying again:

```
make clean
```
### warning: memset used with constant zero length parameter

This error can occur during a `make release`. It is due to using an old version of gcc. 

To resolve: Please upgrade to gcc 4.8.2 or newer.

Example of this error:

```
stig/indy/disk/util/stig_dm.o:
../out/release/stig/indy/disk/util/volume_manager.o (symbol from plugin): warning: memset used with constant zero length parameter; this could be due to transposed parameters
make: *** [release] Error 1
```

### warning: call to '__poll_chk_warn' declared with attribute warning

This error can occur during a `make release`. It is due to using an old version of gcc.

To resolve: Please upgrade to gcc 4.8.2 or newer.

Exmple of this error:

```
stig/core_import.o: 
/usr/include/x86_64-linux-gnu/bits/poll2.h: In member function 'IoMain':
/usr/include/x86_64-linux-gnu/bits/poll2.h:41:60: warning: call to '__poll_chk_warn' declared with attribute warning: poll called with fds buffer too small file nfds entries [enabled by default]
  return __poll_chk (__fds, __nfds, __timeout, __bos (__fds));
                                                            ^
make: *** [release] Error 1
```

## gcc compile tips

gcc can be a real bear to compile, but if your Linux distribution does not have a package available for a gcc version higher than 4.8.1, you'll need to compile it from source.

The [gcc installation docs](http://gcc.gnu.org/install/index.html) and [wiki](http://gcc.gnu.org/wiki/InstallingGCC) have a lot of good information on how to do this compile and installation from source. However, we've a few additional tips which may make the process go a little more smoothly:

* The easiest way to get all of the gcc dependencies downloaded and placed where the build process can locate them is to use the `./contrib/download_prerequisites` script in the gcc source directory.
* Other dependencies you may need to install (on Ubuntu): libcloog-isl-dev, gcc-multilib
* As well, since many of the libraries required to compile Stig are also necessary for compiling gcc, installing Stig pre-requisites before building gcc can sometimes make the process run more smoothly.
* We've found that the gcc build frequently will fail when building for Java compiling. As Stig has no need for this, we typically run `configure` with the `--enable-languages=c,c++` flag.
* Make sure to use `--prefix=` during configuration and set it to a directory which will be in your `$PATH`, `$LD_LIBRARY_PATH`, and `$LD_RUN_PATH` (or be sure to add it to these paths after the installation is complete).
* Building gcc takes a lot of space. Before starting, make sure that your build directory has at least 5GB of free space available.

For Ubuntu 13.10, it's possible to get a successful gcc build and installation with the following steps:

```
cd ~
sudo apt-get install flex bison util-linux git build-essential uuid-dev libaio-dev libgmp-dev libsctp-dev lksctp-tools zlib1g-dev libicu-dev libreadline6-dev libsnappy-dev valgrind libcloog-isl-dev gcc-multilib
sudo apt-get install g++
wget http://www.netgull.com/gcc/releases/gcc-4.8.2/gcc-4.8.2.tar.gz
tar zxvf gcc-4.8.2.tar.gz
cd gcc-4.8.2
./contrib/download_prerequisites
cd ..
mkdir build
cd build
../gcc-4.8.2/configure --enable-languages=c,c++
make
make test
sudo make install
```

-----

build.md Copyright 2010-2014 Stig LLC

build.md is licensed under a Creative Commons Attribution-ShareAlike 4.0 International License.

You should have received a copy of the license along with this work. If not, see <http://creativecommons.org/licenses/by-sa/4.0/>.
