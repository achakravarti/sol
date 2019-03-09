# Sol Library
> Primitives for progressive software development in C


[![GitHub license](https://img.shields.io/github/license/achakravarti/sol.svg)](https://github.com/achakravarti/sol/blob/master/LICENSE) [![GitHub release](https://img.shields.io/github/release/achakravarti/sol.svg)](https://img.shields.io/github/release/achakravarti/sol) [![GitHub release date](https://img.shields.io/github/release-date/achakravarti/sol.svg)](https://img.shields.io/github/release-date/achakravarti/sol)  
[![Build Status](https://travis-ci.com/achakravarti/sol.svg?branch=master)](https://travis-ci.com/achakravarti/sol) [![codecov](https://codecov.io/gh/achakravarti/sol/branch/master/graph/badge.svg)](https://codecov.io/gh/achakravarti/sol) [![GitHub last commit](https://img.shields.io/github/last-commit/achakravarti/sol.svg)](https://github.com/achakravarti/sol/graphs/commit-activity) [![Issues](http://img.shields.io/github/issues/achakravarti/sol.svg)](https://github.com/achakravarti/sol/issues) [![GitHub issues-closed](https://img.shields.io/github/issues-closed/achakravarti/sol.svg)](https://github.com/achakravarti/sol/issues?q=is%3Aissue+is%3Aclosed)  
[![GitHub pull-requests](https://img.shields.io/github/issues-pr/achakravarti/sol.svg)](https://github.com/achakravarti/sol/pull/) [![GitHub pull-requests closed](https://img.shields.io/github/issues-pr-closed/achakravarti/sol.svg)](https://github.com/achakravart/sol/pull/) [![PRs Welcome](https://img.shields.io/badge/PRs-welcome-blue.svg)](http://makeapullrequest.com) [![GitHub contributors](https://img.shields.io/github/contributors/achakravarti/sol.svg)](https://github.com/achakravarti/sol/graphs/contributors/)


## License

Copyright (c) 2019 [Abhishek Chakravarti][]. 
<abhishek@taranjali.org>

This Library is free software; you can redistribute it and/or modify it under 
the terms of the [GNU General Public License][] as published by the [Free 
Software Foundation][]; either [version 3][] of the License, or (at your option)
any later version.

This Library is distributed in the hope that it will be useful, but WITHOUT ANY
WARRANTY; without even the implied warranty of MERCHANTIBILITY or FITNESS FOR A
PARTICULAR PURPOSE. See the [GNU General Public License][] for more details.

You should have received a [copy][] of the [GNU General Public License][] along
with this Library; if not, contact the custodian of this Library, [Abhishek
Chakravarti][], at <abhishek@taranjali.org>.


## Overview

The Sol Library started out as a hobby project to explore the possibility of
building web applications that can run on resource constrained devices. When I
conceived of this project, I was heavily entrenched in the building of web
applications in the .NET ecosystem, and I became interested in the potential
carbon footprint of running such applications. 

Although I never actually measured the power requirements, I set out on a 
challenge to build a simple web application that could run on a [Raspberry Pi][]
SoC. I succeeded, and the insights that I gleaned led to the development of the
Sol Library.

The primary goal of the Sol Library is to provide a set of primitives for 
software development that leverages the power of C without sacrificing on 
progressive best practices. The secondary goal of the Library is that it should
be usable on a freestanding environment; although I don't have any experience in 
embedded programming, it's nice to envision that this Library is usable in such
environments. These goals are achieved through **seven modules**, which are 
described in the [Features](#features) section of this document.


## Documentation

The documentation for the Sol Library is structured as follows:
  * General information and guidelines are covered in this [README.md][] file
  * License details are covered in the [LICENSE][] file
  * Changes are logged in the [CHANGELOG.md][] file
  * Build and usage instructions are provided in the [Makefile][]
  * Contribution guidelines are detailed in the [CONTRIBUTING.md][] file
  * The API reference is in the header files of the `inc/` directory


## Features

The Sol Library is designed as a set of modules, with each module responsible
for providing a specific set of related functionality:
  1. The **Environment Module** provides diagnostics related to the compilation
     environment
  2. The **Compiler Hints Module** provides compiler hints that can potentially
     optimise code
  3. The **Libc Module** provides portably access to libc dependencies
  4. The **Primitive Data Types Module** defines the primitive data types along
     with their related constants
  5. The **Exception Handling Module** provides a basic structure to handle
     exceptions
  6. The **Unit Testing Module** provides a framework for executing unit tests
  7. The **Logging Module** provides support for runtime logging

Although this Library depends on a few libc functions, most notably malloc() and
free(), the Libc Module provides the means for freestanding environments to hook
their own libc implementations to the Sol Library. In future, I hope to be able
to provide a fallback libc implementation for freestanding environments that do
not provide their own.

Every attempt has been made to make this Library as portable as possible. The
Sol Library has been designed to be compatible with the C89 standard, but takes
advantage of the improved features provided by the newer dialects if supported
by the compilation environment.

Although this Library takes advantage of the features provided by C99 and newer
dialects, it will compile fine on the C89

The enhanced features of compiler hints and support for 64-bit integers are
considered to be optional, and are available only when GCC/Clang or a GCC-
compatible compiler is used. However, given the fact that GCC is the most widely
ported compiler, the enhanced features are likely to be available on most 
platforms.


## Development

The Sol Library source code is available via [Git][] from its [GitHub][]
[repository][]. The release versions are tagged on the `release` branch, and are
also available as [GitHub][] [releases][]. The latest development rolling 
release is always available on the `master` branch, which is built by 
integrating the issue  branches. All versions, release and development, adhere
to the [Semantic Versioning][] scheme.

Sol has been developed and tested on a 64-bit machine running [Arch Linux][]
with [GCC][] as the compiler. Additional testing has been done through the
[Travis CI][] continuous integration tool running [Ubuntu Trusty 14.04][],
[macOS][], and [Windows Server 1803][] with [GCC][] and [Clang][] as compilers.

Please see the [CONTRIBUTING.md][] file if you are interested in learning more
about the development process and tools used to build Sol.


## Getting Started
In order to use the Sol Library in a **hosted environment**, the following steps
must be performed:  
  1. Cloning the Git repository  
  2. Testing the Library
  3. Installing the Library


The commands to do so are:  
  - `git clone https://github.com/achakravarti/sol.git`  
  - `make -s test`  
  - `make -s install`  

On executing the second step, a message will be diplayed on the standard output
indicating the unit test results. If no unit tests fail, then you are good to go
with the third step of installation.

This Library does not comprise of any binaries, only a set of header files.
These header files are installed in the standard include directory, the default
being `/usr/local/include`. However, if required, you can change this by setting
the correct value in the `ipath_standard` build variable in the Makefile.

Once you have installed the Library, you can use it by including it in your C 
source code like so:  
  - `#include <sol/api.h>`  

If you no longer need the Library, you can uninstall it by running the
following command:  
  - `make -s uninstall`  

If you are using this Library in a **freestanding environment**, then you would
need to adapt these steps according to your use case.


## Support

If you're using this Library, and have encountered any issues that you would
require support for, please open an issue through this Library's [issue
tracker][]. 

The following categories of support requests are welcome, each of which comes
with its own label in the [issue tracker][]:
  * `bug` for a problem with an existing feature
  * `enhancement` for an enhancement to an existing feature
  * `feature` for a new feature request
  * `query` for a query on an existing feature

When documenting your issue, please keep the following points in mind:  
  * Keep the title short and sweet
  * Provide all relevant details in the description section
  * Tag the issue with the appropriate label
  * Do be polite and professional

While every effort would be taken to address all support requests, please note
that no guarantee is given that your support request would be resolved.


## Contributing

Contributions to the development of the Sol Library within the scope of its
objectives are encouraged and appreciated. Contributions can take one of the
following forms:  
  * Development
  * Documentation
  * Reviews
  * Testing

If you are interested in contributing to this Library, a good starting point
would be to read the [CONTRIBUTING.md][] file. This file provides guidelines on
the code of conduct, and on the development process and tools.


## Contributors

The Sol Library was written, and is currently maintained, by 
[Abhishek Chakravarti][].


## Acknowledgements
Special mention needs to be made for the following, which have significantly
influenced the development of the Sol Library:  
  * [Arch Linux][]  
  * [Clang][]  
  * [Codecov][]  
  * [fvcproductions/sampleREADME.md][]  
  * [GCC][]  
  * [Git][]  
  * [GitHub][]  
  * [Linux][]  
  * [Make A README][]  
  * [Naereen/badges][]  
  * [PurpleBooth/README-Template][]  
  * [Travis CI][]  
  * [Vim][]


* * *


[Abhishek Chakravarti]:https://github.com/achakravarti
[Arch Linux]:https://www.archlinux.org
[CHANGELOG.md]:https://github.com/achakravarti/sol/blob/master/CHANGELOG.md/
[Clang]:https://clang.llvm.org
[Codecov]:https://codecov.io
[CONTRIBUTING.md]:https://github.com/achakravarti/sol/blob/master/CONTRIBUTING.md/
[copy]:https://github.com/achakravarti/sol/blob/master/LICENSE
[Free Software Foundation]:https://www.fsf.org
[fvcproductions/sampleREADME.md]:https://gist.github.com/fvcproductions/1bfc2d4aecb01a834b46
[GCC]:https://gcc.gnu.org
[Git]:https://git-scm.com
[GitHub]:https://github.com
[GNU General Public License]:https://choosealicense.com/licenses/gpl-3.0
[issue tracker]:https://github.com/achakravarti/sol/issues
[LICENSE]:https://github.com/achakravarti/sol/blob/master/LICENSE
[Linux]:https://www.kernel.org
[macOS]:https://www.apple.com/macos
[Make A README]:https://makeareadme.com
[Makefile]:https://github.com/achakravarti/sol/blob/master/Makefile/
[Naereen/badges]:https://github.com/Naereen/badges
[PurpleBooth/README-Template]:https://gist.github.com/PurpleBooth/109311bb0361f32d87a2
[Raspberry Pi]:https://www.raspberrypi.org/
[README.md]:https://github.com/achakravarti/sol/blob/master/README.md/
[releases]:https://github.com/achakravarti/sol/releases
[repository]:https://github.com/achakravarti/sol
[Semantic Versioning]:http://semver.org
[Travis CI]:https://travis-ci.org
[version 3]:https://www.gnu.org/licenses/gpl-3.0.en.html
[Ubuntu Trusty 14.04]:http://releases.ubuntu.com/14.04
[Vim]:https://www.vim.org
[Windows Server 1803]:https://docs.microsoft.com/en-us/windows-server/get-started/get-started-with-1803

