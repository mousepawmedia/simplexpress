Building PuppeteerXML
=====================

Building Basics
----------------------
CMake is used to build SIMPLEXpress. For your convenience,
we've included Makefiles to automate all common build scenarios on Linux.
Type "make" in the root of this repository for more information.

At this time, the Makefiles are only designed for Linux. If you are building
on another system, you can interact with CMake directly.

Currently, SIMPLEXpress can only be built using GCC 5 or later (or a compiler
that can emulate that).

Building and Linking Dependencies
-----------------------------------
SIMPLEXpress relies on CPGF and PawLIB. The default behavior is for the build
system to look in a 'pawlib-git/pawlib' folder in the same directory as this
repository. (This is our default for company development environments.)

You can specify custom paths for these libraries by creating a ".config" file
in the root of this repository. Make a copy of "build.config.txt" and save it
with the ending ".config". See that file for more information.

Ready-To-Use Build
--------------------
If you just want to build SIPLEXPress to use in your own project, the fastest
way is to run "make ready". This will build SIMPLEXpress and place it in a
folder called "simplexpress". Simply copy that folder to a convenient location,
and point your compiler and linker to "simplexpress/include" and
"simplexpress/lib" respectively.

Building HTML Docs
--------------------------
The Ready-To-Use build includes the PDF documentation. If you want the HTML
documentation instead, run "make docs". Then, grab the 'docs/build/html'
folder, or just open 'docs/build/html/index.html' in your favorite web
browser.

Building Tester
----------------------
If you want to test out SIMPLEXpress directly, run "make tester". Then, look
for the simplexpress-tester executable in tester/bin/[Debug/Release].

Code::Blocks
---------------------
SIMPLEXpress was written and built in CodeBlocks. The projects (.cbp) in this
repository are pre-configured to build directly in the repository.

Source Directories
---------------------
- The '/docs' folder contains the Sphinx documentation for SIMPLEXpress.
- The '/library' folder contains the source code for the SIMPLEXpress
  library.
- The '/tester' folder contains the console application for testing
  the SIMPLEXpress library.
