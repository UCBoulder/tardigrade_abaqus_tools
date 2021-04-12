# C++ Stub repository

A stub repository for C++ development projects in W-13.

This repository will contain the necessary setup files to integrate C++ doc strings,
[CMake](https://cmake.org/cmake/help/v3.14/), [Doxygen](https://www.doxygen.nl/manual/docblocks.html),
[Sphinx](https://www.sphinx-doc.org/en/master/), and [Breathe](https://breathe.readthedocs.io/en/latest/) for a complete
build system with integrated documentation. It will also include the necessary hooks to commonly used C++ libraries for
constitutive modeling. This stub repository also includes template hooks for integrating C++ code as Abaqus subroutines.

> Note: you can use this repo as a stub for fortran projects as well! A
> step-by-step may never happen because c++ is the future of W-13 subroutines.
> For now, refer to the following references:
>
> * [CMake for Fortran example
>   ``CMakeLists.txt``](https://gitlab.kitware.com/cmake/community/-/wikis/doc/cmake/languages/fortran/ForFortranExample)
> * [CMake documentation starting point](https://cmake.org/cmake/help/v3.14/module/CheckFortranSourceRuns.html)
> * [Stack Overflow thread](https://stackoverflow.com/questions/12705562/using-cmake-with-fortran)
> * [Doxygen comments for Fortran](https://www.doxygen.nl/manual/docblocks.html#fortranblocks)

## Setting up a Jenkins CI job

This section has a corresponding section in the formatted and hyperlinked html
documentation. Build and view instructions are included in following sections,
separated from project setup by horizontal bars.

See ``jenkins_job_creation.md`` in this repo.

## Version control for a Jenkins job

This section has a corresponding section in the formatted and hyperlinked html
documentation. Build and view instructions are included in following sections,
separated from project setup by horizontal bars.

See ``jenkins_job_xml.md`` in this repo.

---

---

## Dependencies

### Compilers

* c++11 compiler (listed version number has been tested at some point)

  * g++ >= GNU 4.8.5

### Executables

* [CMake](https://cmake.org/cmake/help/v3.14/) >= 3.14
* [Doxygen](https://www.doxygen.nl/manual/docblocks.html) >= 1.8.5
* [LaTeX](https://www.latex-project.org/help/documentation/) >= 2017

### Python Modules (for documentation)

* [Sphinx](https://www.sphinx-doc.org/en/master/) >= 3.0.4
* [Breathe](https://breathe.readthedocs.io/en/latest/) >= 4.18.1
* [sphinx\_rtd\_theme](https://sphinx-rtd-theme.readthedocs.io/en/stable/) >= 0.4.3

For convenience, the minimal Python environment requirements for the
documentation build are included in ``environment.yaml`` and
``requirements.txt``. A minimal anaconda environment for building the
documentation can be created from an existing anaconda installation with the
following commands.

```
$ conda env create --file environment.yaml
```

You can learn more about Anaconda Python environment creation and management in
the [Anaconda
Documentation](https://docs.conda.io/projects/conda/en/latest/user-guide/tasks/manage-environments.html)

### C++ Libraries

* [BOOST](https://www.boost.org/doc/libs/1_53_0/) >= 1.53.0
* vector\_tools: https://xcp-stash.lanl.gov/projects/MM/repos/vector_tools

#### Constitutive c++ Tools

All of the ``*_tools`` libraries are
pulled from their git repos by branch name and built with their respective cmake
files as part of the cmake build for this project.

---

---

## Build and Test

This project is built with [CMake](https://cmake.org/cmake/help/v3.14/) and uses
[Sphinx](https://www.sphinx-doc.org/en/master/) to build the documentation with
[Doxygen](https://www.doxygen.nl/manual/docblocks.html) +
[Breathe](https://breathe.readthedocs.io/en/latest/) for the c++ API.

### Build on sstelmo

1) Activate the correct python environment

```
$ module load python/2019.10-python-3.7
$ sv3r
```

2) Create a build directory

```
$ pwd
/path/to/abaqus_tools/

$ mkdir build
$ cd build
```

3) Configure ``cmake3``

> This step only needs to be performed once unless you need to specify a new CMake configuration for a re-build. Most
> command line arguments and environment variables are stored in the CMake cache. Anything found in cache will not be
> re-configured unless you remove the cache file or clobber the build directory.

```
$ pwd
/path/to/abaqus_tools/build
$ cmake3 ..
```

4) Build various portions of the project

> Most of the project will re-build only as necessary after source updates. Some portions of the documentation
> require a ``make clean`` after documentation source file updates to force a re-build.

```
$ pwd
/path/to/abaqus_tools/build

# Build everything
$ cmake3 --build .

# Build only the c++ primary libraries
$ cmake3 --build src/cpp
```

5) Locate build files

> The build directory structure may change between version releases. Developers and users are encouraged to become
> familiar with the bash ``find``, ``grep``, and ``tree`` commands to locate build files.

```
$ pwd
/path/to/abaqus_tools/build

# find c++ libraries and ignore intermediate files with similar extensions
$ find . \( -name "*.o" -o -name "*.so" -o -name "*.a" \) | grep -vE "\.cpp\."
```

6) Clean build directory to force a re-build

> :warning: :warning: :warning: HEALTH WARNING :warning: :warning: :warning:
>
> The abaqus input files and bash scripts used for integration testing are not cleaned with this command. Changes to
> those source files are also not handled by ``cmake3`` re-builds. Updates to these files must be manually cleaned between
> changes.

```
$ pwd
/path/to/abaqus_tools/build

$ make clean
```

### Test on sstelmo

4) Build tests of the project

```
$ pwd
/path/to/abaqus_tools/build

# Build c++ tests
$ cmake3 --build src/cpp/tests
```

5) Run the tests

```
$ pwd
/path/to/abaqus_tools/build

# Run ctest
$ ctest

# Results print to screen
# View details of most recent test execution including failure messages
$ less Testing/Temporary/LastTest.log
```

### Convenience build wrappers

Two build scripts have been created for convenience, ``new_build.sh`` and
``build_docs.sh``. The first will build everything including the library binary,
the test binary, and the documentation. This is the same build script used by
``jenkins_build.sh`` for CI builds and testing. The ``build_docs.sh`` script
only builds the documentation. Both build scripts clobber existing build
directories, reset any bash environment variables, and run the cmake
configuration from scratch.

2) Build everything and run tests

```
$ pwd
/path/to/abaqus_tools/

# Just perform the build (pick one)
$ ./new_build.sh <cxx compiler>
$ ./new_build.sh c++
$ ./new_build.sh g++
$ ./new_build.sh icpc

# Perform tests from PWD
$ ./build/src/cpp/tests/test_abaqus_tools

# Build and perform tests
$ ./jenkins_build.sh
```

3) View test results
```
# As built directly to PWD
$ cat results.tex

# As built by jenkins_build.sh
$ cat build/src/cpp/tests/*_results.tex
$ cat *results.tex
```

4) Display docs

```
# Sphinx
$ firefox build/docs/sphinx/index.html &

# Doxygen
$ firefox build/docs/doxygen/html/index.html &
```

### Building the documentation

> :warning: :warning: :warning: HEALTH WARNING :warning: :warning: :warning:
>
> **API Health Note**: The sphinx API docs are a work-in-progress. The doxygen
> API is much more useful.

The documentation can be built with ``build_docs.sh``. The steps used in that
shell script are repeated here.

To build just the documentation pick up the steps here:

2) Create the build directory and move there

```
$ pwd
/path/to/abaqus_tools/
$ mkdir build/
$ cd build/
```

3) Run cmake3 configuration

```
$ pwd
/path/to/abaqus_tools/build/
$ cmake3 ..
```

4) Build the docs

```
$ cmake3 --build docs
```

5) Documentation builds to:

```
abaqus_tools/build/docs/sphinx/index.html
```

6) Display docs

```
$ pwd
/path/to/abaqus_tools/build/
$ firefox docs/sphinx/index.html &
```

7) While the Sphinx API is still a WIP, try the doxygen API

```
$ pwd
/path/to/abaqus_tools/build/
$ firefox docs/doxygen/html/index.html &
```

---

---

## Contribution Guidelines

### Git Commit Message

Begin Git commit messages with one of the following headings:

* BUG: bug fix
* DOC: documentation
* FEAT: feature
* MAINT: maintenance
* TST: tests
* REL: release
* WIP: work-in-progress

For example:

```
git commit -m "FEAT: short intent of new feature"
git commit -m "BUG: fixes nasty bug"
git commit -m "DOC: adds documentation for feature"
```

### Git Branch Names

When creating branches use one of the following naming conventions. When in
doubt use ``feature/<description>``.

* bugfix/\<description>
* feature/\<description>
* release/\<description>

### reStructured Text

[Sphinx](https://www.sphinx-doc.org/en/master/) reads in docstrings and other special portions of the code as
reStructured text. Developers should follow styles in this [Sphinx style
guide](https://documentation-style-guide-sphinx.readthedocs.io/en/latest/style-guide.html#).

### Style Guide

This project does not yet have a full style guide. Generally, wherever a style can't be
inferred from surrounding code this project falls back to
[PEP-8](https://www.python.org/dev/peps/pep-0008/)-like styles. There are two
notable exceptions to the notional PEP-8 fall back:

1. [Doxygen](https://www.doxygen.nl/manual/docblocks.html) style docstrings are
   required for automated, API from source documentation.
2. This project prefers expansive whitespace surrounding parentheses, braces, and
   brackets.
   * No leading space between a function and the argument list.
   * One space following an open paranthesis ``(``, brace ``{``, or bracket
     ``[``
   * One space leading a close paranthesis ``)``, brace ``}``, or bracket ``]``

An example of the whitespace style:

```
my_function( arg1, { arg2, arg3 }, arg4 );
```

The following ``sed`` commands may be useful for updating white space, but must
be used with care. The developer is recommended to use a unique git commit
between each command with a corresponding review of the changes and a unit test
run.

* Trailing space for open paren/brace/bracket

```
sed -i 's/\([({[]\)\([^ ]\)/\1 \2/g' <list of files to update>
```

* Leading space for close paren/brace/bracket

```
sed -i 's/\([^ ]\)\([)}\]]\)/\1 \2/g' <list of files to update>
```

* White space between adjacent paren/brace/bracket

```
sed -i 's/\([)}\]]\)\([)}\]]\)/\1 \2/g' <list of files to update>
```
