# Sol Library
> Progressive toolkit for rapid application development in C


## License
[![GitHub license](https://img.shields.io/github/license/achakravarti/sol.svg)](https://github.com/achakravarti/sol/blob/master/LICENSE)

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


## Features

The Sol Library is designed as a set of modules, with each module responsible
for providing a specific set of related functionality:
  1. The **Environment Module** helps identity the compiler and host environment
  2. The **Compiler Hints Module** provides compiler hints that can potentially
     optimise code
  3. The **Primitive Data Types Module** defines the primitive data types along
     with their related constants
  4. The **Exception Handling Module** provides a basic structure to handle
     exceptions
  5. The **Unit Testing Module** provides a framework for executing unit tests


## Development
[![Build Status](https://travis-ci.org/achakravarti/sol.svg?branch=master)](https://travis-ci.org/achakravarti/sol) [![codecov](https://codecov.io/gh/achakravarti/sol/branch/master/graph/badge.svg)](https://codecov.io/gh/achakravarti/sol) [![GitHub last commit](https://img.shields.io/github/last-commit/achakravarti/sol.svg)](https://github.com/achakravarti/sol/graphs/commit-activity)

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
[![Issues](http://img.shields.io/github/issues/achakravarti/sol.svg)](https://github.com/achakravarti/sol/issues) [![GitHub issues-closed](https://img.shields.io/github/issues-closed/achakravarti/sol.svg)](https://github.com/achakravarti/sol/issues?q=is%3Aissue+is%3Aclosed)

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
[![GitHub pull-requests](https://img.shields.io/github/issues-pr/achakravarti/sol.svg)](https://github.com/achakravarti/sol/pull/) [![GitHub pull-requests closed](https://img.shields.io/github/issues-pr-closed/achakravarti/sol.svg)](https://github.com/achakravart/sol/pull/) [![PRs Welcome](https://img.shields.io/badge/pull%20requests-welcome-blue.svg)](http://makeapullrequest.com)

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
[![GitHub contributors](https://img.shields.io/github/contributors/achakravarti/sol.svg)](https://github.com/achakravarti/sol/graphs/contributors/)

The Sol Library was written, and is currently maintained, by 
[Abhishek Chakravarti][].


## Acknowledgements
TODO

* * *


[Abhishek Chakravarti]:https://github.com/achakravarti
[Arch Linux]:https://www.archlinux.org
[Clang]:https://clang.llvm.org
[CONTRIBUTING.md]:https://github.com/achakravarti/sol/blob/master/CONTRIBUTING.md/
[copy]:https://github.com/achakravarti/sol/blob/master/LICENSE
[Free Software Foundation]:https://www.fsf.org
[GCC]:https://gcc.gnu.org
[Git]:https://git-scm.com
[GitHub]:https://github.com
[GNU General Public License]:https://choosealicense.com/licenses/gpl-3.0
[issue tracker]:https://github.com/achakravarti/sol/issues
[macOS]:https://www.apple.com/macos
[releases]:https://github.com/achakravarti/sol/releases
[repository]:https://github.com/achakravarti/sol
[Semantic Versioning]:http://semver.org
[Travis CI]:https://travis-ci.org
[version 3]:https://www.gnu.org/licenses/gpl-3.0.en.html
[Ubuntu Trusty 14.04]:http://releases.ubuntu.com/14.04
[Windows Server 1803]:https://docs.microsoft.com/en-us/windows-server/get-started/get-started-with-1803

