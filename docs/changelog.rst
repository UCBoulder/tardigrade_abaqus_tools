.. _changelog:


#########
Changelog
#########

******************
0.5.1 (unreleased)
******************

Breaking changes
================
- Deploy to the Conda environment preferred ``lib`` directory instead of the CMake linux default ``lib64`` (:issue:`22`,
  :merge:`38`). By `Kyle Brindley`_.

******************
0.4.1 (2023-05-16)
******************

Internal Changes
================
- Add a gcc 10 conda build variant (:issue:`18`, :merge:`32`). By `Sergio Cordova`_.
- Upgrade to Anaconda 2021 on Gitlab-CI environment (:issue:`66`, :merge:`67`).
- Clean up conda package CI files after ``conda build`` (:issue:`21`, :merge:`35`). By `Sergio Cordova`_.

Bug fixes
=========
- Added inline to functions to allow for abaqus_tools to be included multiple times (:merge:`36`). By `Nathan Miller`_.

******************
0.3.1 (2023-03-16)
******************

Internal Changes
================
- Project configuration and conda build recipe changes to allow macOS builds and conda-build test stage (:merge:`20`).
  By `Kyle Brindley`_.
- Add a gcc 11 conda build variant (:issue:`14`, :merge:`23`). By `Kyle Brindley`_.
- Force CI environment consistent conda-forge packages and make the CI environment file OS-agnostic (:merge:`25`). By
  `Kyle Brindley`_.
- Remove ``-ansi`` compiler option and update to c++17 standard (:merge:`26`). By `Kyle Brindley`_.


******************
0.2.2 (2022-12-14)
******************

Internal Changes
================
- Remove the upper bound on compiler version in the shared development environment (:merge:`13`). By `Kyle Brindley`_.
- Remove the Python dependency and add an additional compiler version package (:merge:`14`). By `Kyle Brindley`_.
- Remove deprecated CI shell scripts (:issue:`9`, :merge:`15`). By `Kyle Brindley`_.
- Remove unused runtime requirement (:issue:`10`, :merge:`16`). By `Kyle Brindley`_.
- Convert to BOOST vector equality checks for more informative unit test failure output (:issue:`11`, :merge:`18`). By
  `Kyle Brindley`_.

Enhancements
============
- Check for matching dimensions in row-to-column major array unpacking (c++ to Fortran) and throw an exception when the
  dimensions don't match (:issue:`8`, :merge:`17`). By `Kyle Brindley`_.

******************
0.2.1 (2022-08-23)
******************

Internal Changes
================
- Build, package, and deploy as a Conda package to the AEA Conda channel (:issue:`4`, :merge:`8`). By `Kyle Brindley`_.
- Fix the environment creation command for Gitlab-CI environment (:merge:`9`). By `Kyle Brindley`_.


******************
0.1.3 (2022-03-21)
******************

Internal Changes
================
- Update the build configuration to handle conda environments than manage cpp compilers and libraries ( :merge:`4`). By
  `Kyle Brindley`_.
- Add back compiler flags related to code warnings for the project wide compile options (:issue:`2`, :merge:`5`). By
  `Kyle Brindley`_.


******************
0.1.2 (2021-07-12)
******************

Internal Changes
================
- Migrate from ddw-bitcket.lanl.gov to re-git.lanl.gov (:issue:`1` :merge:`1`). By `Kyle Brindley`_.

******************
0.1.1 (2021-07-01)
******************

Internal Changes
================
- Use Git SCM tags for semantic versioning (:jira:`698`, :pull:`22`). By `Kyle
  Brindley`_.
- Master branch production release logic for CD, including automated micro-version bumps (:jira:`698`, :pull:`22`). By `Kyle
  Brindley`_.


******************
0.1.0 (2021-05-28)
******************

New Features
============
- Add deploy CMake files for build, deploy, discovery, and version comparisons (:jira:`658`, :pull:`18`). By `Kyle
  Brindley`_.

Internal Changes
================
- Add multi-agent Jenkins jobs for CI/CD (:jira:`646`, :pull:`17`). By `Kyle Brindley`_.
- Remove CXX compiler specification in build scripts (:jira:`667`, :pull:`19`). By `Kyle Brindley`_.

******************
0.0.3 (2021-05-06)
******************

New Features
============
- Add full tensor construction from Abaqus stress and strain type ``NTENS`` vectors (:jira:`610`, :pull:`12`). By `Kyle
  Brindley`_.
- Add full tensor deconstruction to Abaqus stress and strain type ``NTENS`` vectors (:jira:`614`, :pull:`13`). By `Kyle
  Brindley`_.
- Add full Voigt matrix (9x9) contraction to Abaqus Voigt (6x6) matrix and (``NTENS`` x ``NTENS``) matrix (:jira:`615`,
  :pull:`14`). By `Kyle Brindley`_.

Internal Changes
================
- Updates to documentation source for ReST style guide (:jira:`610`, :pull:`12`). By `Kyle Brindley`_.
- Add support for multi-host, multi-environment CI/CD (:jira:`646`, :pull:`15`). By `Kyle Brindley`_.
- Remove the ``CXX`` compiler variable settings for build scripts (:jira:`667`,
  :pull:`16`. By `Kyle Brindley`_.


******************
0.0.2 (2021-04-30)
******************

Breaking changes
================
- Change Abaqus stress-type vector expansion function name to match the general purpose nature for both Standard and
  Explicit (:jira:`591`, :pull:`7`). By `Kyle Brindley`_.
- Change Abaqus stress-type vector contraction function name to match the general purpose nature for both Standard and
  Explicit (:jira:`592`, :pull:`8`). By `Kyle Brindley`_.
- Change Abaqus NTENS matrix contraction function name to match the general purpose nature for both Standard and
  Explicit (:jira:`593`, :pull:`9`). By `Kyle Brindley`_.


******************
0.0.1 (2021-04-13)
******************

Breaking changes
================

New Features
============

Bug fixes
=========

Documentation
=============
- First production release (:jira:`543`, :pull:`5`). By `Kyle Brindley`_.

Internal Changes
================
- Setup Jenkins PR builder:
  https://toolbox-jenkins.lanl.gov/view/VIPor%20and%20C++/job/abaqus_tools_Pull_Request_Builder/ (:jira:`540`,
  :pull:`4`). By `Kyle Brindley`_.
- Update change log for abaqus\_tools release versions and update repository tags (:jira:`539`, :pull:`3`). By `Kyle
  Brindley`_.
- Remove everything except the abaqus\_tools (:jira:`538`, :pull:`2`). By `Kyle Brindley`_.
- Update project name (:jira:`537`, :pull:`1`). By `Kyle Brindley`_.
- Creation from cpp_stub (:jira:`534`). By `Kyle Brindley`_.

Enhancements
============

