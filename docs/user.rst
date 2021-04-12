.. _user_manual:

###########
User Manual
###########

***********
Quick Start
***********

This stub repo contains hooks for writing Abaqus :cite:`ABAQUS2019` subroutines, like those found in the `Abaqus UMAT
documentation`_, and a template UMAT c++ interface. However, this template repository does not yet have a meaningful c++
constitutive model to be the subject of a user manual.

Until this template repository includes a `CMake`_ ``--install`` definition, user's are referred to the :ref:`build`
section of the :ref:`devops_manual` for build instructions.

The template UMAT can be used after build with the following Abaqus options

.. code:: bash

   $ abaqus -job <my_input_file> -user relative/path/to/abaqus_tools/build/src/cpp/umat.o

Until the template repository and all upstream c++ libraries are built as shared library objects it is recommended that
the subroutines are left in the project build directory. However, it is possible to copy the shared library files to any
other directory provided the upstream projects ``{error,vector,stress,solver,constitutive}_tools`` are present in the
build directory, e.g. ``abaqus_tools/build/_deps/{error,vector,stress,solver,constitutive}_tools-build/``.

.. code:: bash

   $ pwd
   /path/to/my/abaqus/job
   $ cp /path/to/abaqus_tools/build/src/cpp/{umat.o,libabaqus_tools.so} .
   $ abaqus -job <my_input_file> -user umat.o

*************
Dummy Section
*************

You can read more about Sphinx ReST formatting in this `Sphinx style guide`_
:cite:`sphinx-style`.

Placeholder for a user manual with example code and figures and references.

.. code:: bash

   $ ./build_docs.sh
