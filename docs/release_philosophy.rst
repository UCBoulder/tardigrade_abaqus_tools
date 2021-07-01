.. _releasephilosophy:


##################
Release Philosophy
##################
Release Philosophy

This section discusses topics related to |project| releases and version numbering.


**********************
Release and Deployment
**********************

.. warning::

   The |project| project does not yet have a template ``cmake3 --install`` definition and is not yet deployable to the
   W-13 Python Environments. Instead, users are directed to the :ref:`user_manual` and :ref:`build` section of the
   :ref:`devops_manual`.

The |project| project is built and installed as a c++ library in the `W-13 Python Environments`_ available on hamming,
sstelmo, and any local linux machines with home and project drives mapped from the W-13 NFS server. These are Anaconda
Python 3 environments with installed packages required for W-13 software development and engineering analysis. There are
two versions of the W-13 Python Environments:

1) release
2) beta

The release environment contains the deployed final release versions of W-13 software projects, e.g. Toolbox and ECMF,
as tested against the installed Python packages. The beta environment contains the deployed developer release of W-13
software projects. While the deployed projects in beta have been unit and integration tested, the beta environment may
include updated or new Python modules that result in less stable behavior. The beta environment is used to test W-13
software projects against an updated Python environment before releasing the new environment.


***************
Version Numbers
***************

The |project| project follows the `PEP-440`_ standard for version numbering. The
final release version number uses the three component ("major.minor.micro")
scheme. The developer (a.k.a. dev or beta) version number follows the final
release number with an appended "+dev" local version number. The version numbers
correspond to git tags in the `upstream cpp\_stub repo`_ which point to a static
release of the |project| project.

Because the deployed release of the developer version is constantly updated
against development work, the version number found in the developer version
contains additional information. During deployment, the developer version number
is appended with the git information from the most recent build. This
information contains the most recent git tag ("major.minor.micro+dev") followed
by the number of commits since the last final release and a short hash.

Major Number
============

The major number is expected to increment infrequently. After the first major release, it is recommended that the major
version number only increments for major breaking changes.

Minor Number
============

The minor number is updated for the following reasons:

* New features
* Major internal implementation changes
* Non-breaking interface updates

Incrementing the minor version requires a manual update to the release number found in  the root ``CMakeLists.txt`` on a
dedicated release commit. Until the first major release, minor version changes may also contain breaking changes. It is
recommended that all minor version changes are announced to the user community prior to release.

Micro Number
============

.. warning::

The micro number is automatically incremented after any merge from the
development (dev) branch into the release (master) branch. The micro version
number indicates the following changes:

* Bug fixes
* Minor internal implementation changes

Until the first major release, micro version number releases may be made without announcement at the discretion of the
lead developer. It is recommended that the developer community periodically discuss priorities for minor version release
with the user community.

.. _releasebranchreq:


***************************
Release Branch Requirements
***************************

All production releases require a release branch.
Releases correspond to a variety of bug fixes and features that characterize
the release, as documented in :ref:`changelog`.

The following steps will trigger a micro bump. Major and minor version bumps
require a manual Git tag update for the otherwise automated ``GetVersionFromGitTag.cmake``
SCM version script.

Steps needed for a release include:

1. Create a release branch.
2. Modify ``docs/changelog.rst`` to move version number for release PR commit and
   add description as relevant.
3. Commit changes and submit a pull request to the ``dev`` branch at `ECMF Bitbucket`_.
4. **Major and Minor bumps ONLY**: Manually add the new developer version tag to the "Merge" commit on the ``dev``
   branch.  Reset all numbers to the right of the bump to ``0``, e.g. ``1.2.3`` becomes ``2.0.0+dev`` for a Major version
   bump or ``1.3.0+dev`` for a Minor version bump.
5. Immediately submit a ``dev->master`` PR after merging the release branch to ``dev``.
6. Review tests and notes, receive approval, and merge to ``master``.
