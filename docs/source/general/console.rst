Tester Console (from PawLIB)
################################

SIMPLExpress uses the included PawLIB tester application, Goldilocks, which 
allows you to run tests and benchmarks using GoldilocksShell.

SIMPLExpress currently includes various functionality tests. Please see 
`Goldilocks in PawLIB documentation 
<https://docs.mousepawmedia.com/pawlib/goldilocks/goldilocks.html>`__ for more
information on Goldilocks tests.

See :ref:`setup-build-tester` for instructions on how to build the SIMPLExpress
Tester.

Once it's built, you can run the tester from within the SIMPLExpress repository
via ``./tester``.

For SIMPLExpress test and suite ID naming conventions, see :ref:`tests`.

Interactive Mode
================================

We can start Interactive Mode by running the tester application without
arguments, via ``./tester``. Type commands at the ``>>`` prompt.

All commands are detailed under `Goldilocks Interactive 
<https://mousepawmedia.net/docs/pawlib/goldilocks/shell.html#goldilocksshell-interactive>`__.

Command-Line Mode
==============================

We can run tests and suites by passing arguments to our ``./tester``
application. This is especially useful if you want to run tests in a
automated manner, such as with a continuous integration system.

You can get help via ``./tester --help``.

Multiple commands may be run in a single line. They will be executed in order.

All commands are detailed under 
`Goldilocks Command Line Interface <https://mousepawmedia.net/docs/pawlib/goldilocks/shell.html#goldilocksshell-cli>`__.