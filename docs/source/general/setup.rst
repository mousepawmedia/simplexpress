Setup and Compiling
################################

..  _setup-building:

Building
================================

SIMPLExpress is a static library which needs to be compiled before it can
be used.

..  NOTE:: Complete building instructions can be found in BUILDING.md

..  _setup-building-deps:

Environment and Dependencies
------------------------------------

To build SIMPLExpress, you must have the following installed on your system:

* CMake 3.1+ (`cmake.org <https://cmake.org/>`_)

* Clang 3.4+ OR GCC 5.3+ (MSVC is not presently supported.)

* CPGF 1.60, from either:

  * `libdeps 1.0 (GitHub) <https://github.com/mousepawmedia/libdeps/tree/v1.0.0>`_  [recommended], *or*

  * `CPGF (GitHub) <https://github.com/cpgf/cpgf/tree/1.6.0>`_.

* PawLIB, available on `GitHub <https://github.com/mousepawmedia/pawlib>`_.

..  _setup-building-config:

Build Configuration
-------------------------------------
Follow the instructions in the ``pawlib`` repository to set up PawLIB (which 
requires first setting up CPGF, whether by using our ``libdeps`` repository or 
by following PawLIB's alternative directions), then clone the ``simplexpress`` 
repository into an adjacent folder. 

..  _setup-building-compile:

Compiling SIMPLExpress
-------------------------------------

Make sure that PawLIB is built, also ensuring CPGF is built before building 
PawLIB. If you're using ``libdeps``, you can simply run ``make cpgf`` in that 
repository. Then in the PawLIB repository, run ``make ready`` to build PawLIB 
as a static library.

Finally, in the SIMPLExpress repository, run ``make ready`` to build 
SIMPLExpress for use in your project.

..  NOTE:: If you experience any errors in compiling, we invite you to
    contact us. See :ref:`support`.

..  _setup-linking:

Linking to SIMPLExpress
==============================

To use SIMPLExpress in your C++ project, you will need to statically link to
it, and both PawLIB and CPGF.

..  IMPORTANT:: Linking order is important in C++! You should link to
    SIMPLExpress first, then PawLIB, and then its dependencies (namely CPGF).

You can point your compiler and linker at the :file:`simplexpress/include`
and :file:`simplexpress/lib` directories, followed by :file:`pawlib/include/`
and :file:`pawlib/lib/` directories.

If you need help finding the paths for CPGF, refer to the path in the PawLIB
build configuration (see :ref:`setup-building-config`). The :file:`include/`
and :file:`lib/` directories should be in the path specified.

.. _setup-build-tester:

Using SIMPLExpress
==============================

All ``#include`` commands follow the format ``#include "simplexpress/HEADER.hpp"``,
where ``HEADER.hpp`` is the header file you wish to include.

Building Tester
============================

If you want to use the SIMPLExpress tester application, you can build that as
well. Once you've confirmed that SIMPLExpress itself can build without errors,
run ``make tester`` to build the tester.
