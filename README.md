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

## Setting up a new project from this stub repo

This section has a corresponding section in the formatted and hyperlinked html
documentation. The html documentation also includes setup instructions for
Jenkins Continuous Integration (CI) setup. Build and view instructions are
included in following sections, separated from project setup by horizontal bars.

### Prerequisites

Set up your profile on Bitbucket with ssh keys. You can follow the instructions
on the W-13 Confluence page [Gitting started with W-13
Bitbucket](https://xcp-confluence.lanl.gov/display/GIT/Gitting+Started+W-13%27s+Git+Server)

### Clone cpp\_stub into a local repository

1. Navigate to the [upstream cpp\_stub repo](https://xcp-stash.lanl.gov/projects/MM/repos/abaqus_tools/browse)

2. Copy the ssh url from the Bitbucket "Clone" button on the Bitbucket
   repository web page. It should look like the following:

```
ssh://git@xcp-stash.lanl.gov:7999/mm/abaqus_tools.git
```

3. Navigate to your preferred repository directory in a terminal or use the
   example commands below

```
$ ssh -X sstelmo.lanl.gov
$ pwd
/home/<moniker>
$ mkdir -p /projects/$USER/w13repos
$ cd /projects/$USER/w13repos
$ pwd
/projects/<moniker>/w13repos
```

4. Clone the stub repository using the url copied in step 2.

```
$ pwd
/projects/<moniker>/w13repos
$ git clone ssh://git@xcp-stash.lanl.gov:7999/mm/abaqus_tools.git
```

5. Rename the local repository directory for your project.

```
$ pwd
/projects/<moniker>/w13repos
$ ls abaqus_tools -d
abaqus_tools
$ mv abaqus_tools my_project
$ ls abaqus_tools -d
ls: cannot access 'abaqus_tools': No such file or directory
$ mv abaqus_tools my_project
my_project
```

6. Change to your project's repository directory

```
$ pwd
/projects/<moniker>/w13repos
$ cd my_project
$ pwd
/projects/<moniker>/w13repos/my_project
```

### Create a new repository on Bitbucket

> Note: These notes are a text copy of a variation on the [New Bitbucket Repo
> Guide](https://simulia.lanl.gov/ECMF-D/devops_guide.html#new-bitbucket-repo-guide)
> which can also be found in the [W-13 DevOps
> Manual](https://xcp-confluence.lanl.gov/display/COM/W-13+DevOps)

1. Navigate to the W-13 [Material Models](https://xcp-stash.lanl.gov/projects/MM) Bitbucket project.

2. Create a new repository by clicking on the "+" sign in the upper left corner.

3. Enter a name for your project and click "Create repository"

4. Follow the "My code is already tracked by Git" instructions.

```
$ pwd
/projects/<moniker>/w13repos/my_project
$ git remote set-url origin ssh://git@xcp-stash.lanl.gov:7999/mm/my_project.git
$ git push -u origin --all
$ git push origin --tags
```

5. Refresh the Bitbucket webpage and verify that the repository code was pushed
   correctly. You should see a list of source files and this Bitbucket parsed
   ``README.md`` displayed. You can also select the drop down branch menu to
   view a "master" and "dev" branch.

### Update settings for your repository

Bitbucket repositories in the [Material
Models](https://xcp-stash.lanl.gov/projects/MM) project inherit permissions and
settings from that project. This included read permission for the
``w13bitbucket`` [UNIX
group](https://xcp-confluence.lanl.gov/pages/viewpage.action?pageId=150929410&searchId=Y1EVB37UN).
For most developers, these inherited repository settings are appropriate and
only a small number of settings must be updated.

1. Click on the gear icon in the lower left sidebar.

2. From the "Repository details" landing page, update the default branch from
   "master" to "dev".

3. From the "Repository permissions" tab you can add additional permissions by
   user and UNIX group.

4. From the "Default reviewers" tab you can add yourself and any project
   co-owners as default reviewers.

### Fork the upstream repository

In the [Forking
Workflow](https://www.atlassian.com/git/tutorials/comparing-workflows/forking-workflow)
the repository you just created in the [Material
Models](https://xcp-stash.lanl.gov/projects/MM) project is called the "upstream"
repository. Throughout older W-13 documentation this may also be called the
"official" repository.

Bitbucket repositories that inherit permissions from W-13 projects use the
[Forking
Workflow](https://www.atlassian.com/git/tutorials/comparing-workflows/forking-workflow)
and limit permissions for pushing changes to the upstream repository. Now that
branches exist on this repository, no one will be able to push directly to
*existing branches* of the upstream respository.

1. Click the fork button in the left hand sidebar just above the gear icon.

2. Click "fork this repository" button.

3. Verify

   a. The "Project" points to your personal project space in Bitbucket. It will
      probably show your full name as it appears in the phonebook.

   b. The "Name" matches your project name

   c. The "Enable fork syncing" checkbox is checked

4. Click the "Fork Repository" button. You should land on a familiar looking
   source code view of your repository, but now located in your personal project
   space.

This repository is referred to as the "fork" or "remote" repository throughout
W-13 DevOps documentation.

### Update the remote url in your local repository

The final repo setup step is to update the remote url of the local clone of
``my_project``.  We will return to the terminal session.

1. Copy the url of your "remote" repository from the Bitbucket webpage. It
should look like:

```
ssh://git@xcp-stash.lanl.gov:7999/~<moniker>/my_project.git
```

2. Return to your terminal session and update the remote repository for the
   final time.

```
$ pwd
/projects/<moniker>/w13repos/my_project
$ git remote set-url origin ssh://git@xcp-stash.lanl.gov:7999/~<moniker>/my_project.git
$ git push -u origin --all
$ git push origin --tags
```

### Update project name throughout repository

> Note: the remaining steps are a truncated version of the W-13 Git project
> [contribution guide](https://simulia.lanl.gov/ECMF-D/contribution_guide.html)
> which can also be found in the [W-13 DevOps
> Manual](https://xcp-confluence.lanl.gov/display/COM/W-13+DevOps). Critically,
> these steps will omit the Jira task creation and Bitbucket Pull-Request (PR)
> steps. The Bitbucket PR steps may be reproduced using the contribution guide,
> but your project will have to create a Jira project prior to integrating the
> Jira workflow. Contact the xcp devops team <devops-help@lanl.gov> to create a
> Jira project. You can email the W-13 DevOps team <w13devops@lanl.gov> for
> notes about setup.

1. Create a feature branch for your project name updates

```
$ pwd
/projects/<moniker>/w13repos/my_project
$ git checkout -b feature/project-name-updates
$ git branch
  dev
* feature/project-name-updates
  master
```

2. Search for all instances of ``abaqus_tools``. The list of occurrences will look
   quite long, but we can search and replace with ``sed`` to avoid manual file
   edits.

```
$ pwd
/projects/<moniker>/w13repos/my_project

# Recursive, case-insensitive search and count occurrences
$ grep -ri abaqus_tools . --exclude-dir={build,.git} | wc -l
57

# Recursive, case-insensitive search and display
$ grep -ri abaqus_tools . --exclude-dir={build,.git}
...

# Clean list of files with project name
$ grep -ri abaqus_tools . --exclude-dir={build,.git} -l
./CMakeLists.txt
./docs/api.rst
./docs/devops.rst
./README.md
./set_vars.sh
./src/cpp/abaqus_tools.cpp
./src/cpp/abaqus_tools.h
./src/cpp/tests/test_abaqus_tools.cpp
```

3. Search and replace from command line

```
$ pwd
/projects/<moniker>/w13repos/my_project

# Replace lower case occurrences in place
$ sed -i 's/abaqus_tools/my_project/g' $(grep -ri abaqus_tools . --exclude-dir={build,.git} -l)
$ grep -ri abaqus_tools . --exclude-dir={build,.git} -l
./src/cpp/abaqus_tools.h

# Replace upper case occurrences in place
$ sed -i 's/ABAQUS_TOOLS/MY_PROJECT/g' $(grep -ri abaqus_tools . --exclude-dir={build,.git} -l)
```

4. Verify no more occurrences of project name ``abaqus_tools``

```
$ pwd
/projects/<moniker>/w13repos/my_project
$ grep -ri abaqus_tools . --exclude-dir={build,.git} | wc -l
0
$ grep -ri abaqus_tools . --exclude-dir={build,.git}
# no stdout to terminal because no files found
$ grep -ri abaqus_tools . --exclude-dir={build,.git} -l
# no stdout to terminal because no files found
```

5. Commit and push your changes to your "remote" or "fork" repository

```
$ pwd
/projects/<moniker>/w13repos/my_project
# Add tracked files and message
$ git commit -a -m "FEAT: replace abaqus_tools with my_project through repository"
$ git push origin feature/project-name-updates
```

You can also perform some cleanup in ``README.md`` to remove this walk-through.

From here, the W-13 best practice workflow would return to the Bitbucket webpage
and submit a Pull-Request from the ``feature/project-name-updates`` branch of
"\<moniker\>/my_project" repository (a.k.a. fork or remote) to the ``dev`` branch
of "Material Models/my_project" repository (a.k.a. upstream or official).

After updating your project by merging to the upstream repository, the fork
syncing feature of Bitbucket will automatically update any identically named
branches in your fork repository. Best practices suggest you should limit the
upstream repository branches to clean ``dev`` and ``master`` branches and
*NEVER* develop directly on the ``dev`` and ``master`` branches of your fork
repository. Limit development work to ``feature/thing`` type branches on your
fork/remote repo and frequently commit changes and push from the local feature
branch back to the fork/remote repo.

Happy hacking!

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

* [Eigen](https://eigen.tuxfamily.org/dox/) >= 3.3.7
* [BOOST](https://www.boost.org/doc/libs/1_53_0/) >= 1.53.0
* error\_tools: https://xcp-stash.lanl.gov/projects/MM/repos/error_tools
* vector\_tools: https://xcp-stash.lanl.gov/projects/MM/repos/vector_tools
* stress\_tools: https://xcp-stash.lanl.gov/projects/MM/repos/stress_tools
* solver\_tools: https://xcp-stash.lanl.gov/projects/MM/repos/solver_tools
* constitutive\_tools: https://xcp-stash.lanl.gov/projects/MM/repos/consitutive_tools

#### Constitutive Tools

All of the ``{error,vector,stress,solver,constitutive}_tools`` libraries are
pulled from their git repos by branch name and built with their respective cmake
files as part of the cmake build for this project.

#### Eigen

https://gitlab.com/libeigen/eigen

Eigen must be "installed" following the ``eigen/INSTALL`` instructions. The
Eigen dependence is easiest to resolve if eigen is installed in the default
install directory.  However, if you don't have admin privileges, you can also
insall Eigen to your home directory in ``$HOME/.local/include`` or
``$HOME/include``.

#### Non-admin Eigen install

[Reference](https://unix.stackexchange.com/questions/36871/where-should-a-local-executable-be-placed)

```
# Create personal include file directory
$ pwd
/home/$USER
$ mkdir -p .local/include
# Move to repository directory
$ cd /preferred/path/to/repos
# Example
$ pwd
/projects/$USER/w13repos
# Clone eigen
$ git clone https://gitlab.com/libeigen/eigen.git
$ cd eigen
$ git checkout 3.3.7
# Create build directory
$ mkdir build
$ cd build
# OPTIONAL. Set c++ compiler separate from system default
$ export CXX=$(command -v g++)
# Build eigen
$ cmake3 .. -DCMAKE_INSTALL_PREFIX=$HOME/.local
$ make install
```

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
