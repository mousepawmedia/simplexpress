# Building SIMPLEXpress

## Building Basics

CMake 3.1 or later is used to build SIMPLEXpress and SIMPLEXpress Tester. For
your convenience, we've included Makefiles to automate all common build
scenarios on Linux. Run `$ make` in the root of this repository for more
information.

At this time, the Makefiles are only designed for Linux. If you are building
on another system, you can interact with CMake directly.

Currently, SIMPLEXpress is only designed to be built by GCC (5.3 or later) or
Clang (3.4 or later).

## Building and Linking Dependencies

SIMPLEXpress relies on CPGF and PawLIB. The default behavior of the build
system is to look for MousePaw Media's `libdeps/` and `pawlib/` repositories,
cloned parallel to this repository's main folder. Simply run `$ make ready` in
each of those repositories (optionally, you can run `$ make cpgf`
in `libdeps/`) before building this one. (This is our default for company
development environments.)

You can specify custom paths for these libraries by creating a `.config` file
in the root of this repository. Make a copy of `build.config.txt` and save it
with the ending `.config`. See that file for more information.

## Ready-To-Use Build

If you just want to build SIMPLEXpress to use in your own project, the fastest
way is to run `$ make ready`. This will build SIMPLEXpress and place it in a
folder called `simplexpress/`, then point your compiler and linker to
`simplexpress/include` and `simplexpress/lib` respectively. Our other
repositories point to this by default.

## Building HTML Docs

If you want the HTML documentation for SIMPLEXpress, run `$ make docs`. Then,
grab the `docs/build/html` folder, or just open `docs/build/html/index.html` in
your favorite web browser.

## Building Tester

If you want to test out SIMPLEXpress directly, run `make tester`. Then, look
for the `simplexpress-tester` executable in
`simplexpress-tester/bin/[Debug/Release]`. Alternatively, you may use the
symbolic link `tester` or `tester_debug` in the root of this repository.

## IDE Support

SIMPLEXpress was written and built in VSCode. The configuration files in
`.vscode/` are pre-configured to provide the best IDE experience, and allow
building and debugging.

## Source Directories

- The '/docs' folder contains the Sphinx documentation for SIMPLEXpress.
- The '/simplexpress-source' folder contains the source code for the
  SIMPLEXpress library.
- The '/simplexpress-tester' folder contains the console application for
  testing the SIMPLEXpress library.
