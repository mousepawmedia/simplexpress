none:
	@echo "=== SIMPLEXpress 1.0 ==="
	@echo "Select a build target:"
	@echo "   make ready                Build SIMPLEXpress and bundle it for distribution."
	@echo
	@echo "   make clean                Clean up SIMPLEXpress and Tester."
	@echo "   make cleandebug           Clean up SIMPLEXpress and Tester Debug."
	@echo "   make cleanrelease         Clean up SIMPLEXpress and Tester Release."
	@echo "   make docs                 Generate HTML docs."
	@echo "   make simplexpress         Build SIMPLEXpress as release."
	@echo "   make simplexpress_debug   Build SIMPLEXpress as debug."
	@echo "   make tester               Build SIMPLEXpress Tester (+ SIMPLEXpress) as release."
	@echo "   make tester_debug         Build SIMPLEXpress Tester (+ SIMPLEXpress) as debug."
	@echo "   make all                  Build everything."
	@echo "   make allfresh             Clean and rebuild everything."
	@echo
	@echo "Clang Sanitizers (requires Debug build and Clang.)"
	@echo "  SAN=address     Use AddressSanitizer"
	@echo "  SAN=leak        Use LeakSanitizer w/o AddressSanitizer (Linux only)"
	@echo "  SAN=memory      Use MemorySanitizer"
	@echo "  SAN=thread      Use ThreadSanitizer"
	@echo "  SAN=undefined   Use UndefiniedBehaviorSanitizer"
	@echo
	@echo "Optional Architecture (only when building SIMPLEXpress or Tester)"
	@echo "  ARCH=32	Make x86 build (-m32)"
	@echo "  ARCH=64	Make x64 build (-m64)"
	@echo
	@echo "Use Configuration File"
	@echo "  CONFIG=foo      Uses the configuration file 'foo.config'"
	@echo "                  in the root of this repository."
	@echo "  When unspecified, default.config will be used."
	@echo
	@echo "For other build options, see the 'make' command in 'docs/', 'simplexpress-source/', and 'simplexpress-tester/'."

clean:
	$(MAKE) clean -C simplexpress-source
	$(MAKE) clean -C simplexpress-tester
	@rm -f tester
	@rm -f tester_debug

cleanall: clean
	$(MAKE) clean -C docs

cleandebug:
	$(MAKE) cleandebug -C simplexpress-source
	$(MAKE) cleandebug -C simplexpress-tester
	@rm -f tester_debug

cleanrelease:
	$(MAKE) cleanrelease -C simplexpress-source
	$(MAKE) cleanrelease -C simplexpress-tester
	@rm -f tester

docs:
	$(MAKE) html -C docs
	@echo "-------------"
	@echo "<<<<<<< FINISHED >>>>>>>"
	@echo "View docs at 'docs/build/html/index.html'."
	@echo "-------------"

docs_pdf:
	$(MAKE) latexpdf -C docs
	@echo "-------------"
	@echo "<<<<<<< FINISHED >>>>>>>"
	@echo "View docs at 'docs/build/latex/PawLIB.pdf'."
	@echo "-------------"

simplexpress:
	$(MAKE) release ARCH=$(ARCH) CONFIG=$(CONFIG) -C simplexpress-source
	@echo "-------------"
	@echo "<<<<<<< FINISHED >>>>>>>"
	@echo "SIMPLEXpress is in 'simplexpress-library/lib/Release'."
	@echo "-------------"

simplexpress_debug:
	$(MAKE) debug ARCH=$(ARCH) CONFIG=$(CONFIG) SAN=$(SAN) -C simplexpress-source
	@echo "-------------"
	@echo "<<<<<<< FINISHED >>>>>>>"
	@echo "SIMPLEXpress is in 'simplexpress-library/lib/Debug'."
	@echo "-------------"

ready: library
	@rm -rf simplexpress
	@echo "Creating file structure..."
	@mkdir -p simplexpress/lib
	@echo "Copying SIMPLEXpress..."
	@cp -r simplexpress-source/include simplexpress/
	@cp simplexpress-source/lib/Release/libsimplexpress.a simplexpress/lib/libsimplexpress.a
	@echo "Copying README and LICENSE..."
	@cp README.md simplexpress/README.md
	@cp LICENSE.md simplexpress/LICENSE.md
	@echo "-------------"
	@echo "<<<<<<< FINISHED >>>>>>>"
	@echo "The library is in 'simplexpress'."
	@echo "-------------"

tester: simplexpress
	$(MAKE) release ARCH=$(ARCH) CONFIG=$(CONFIG) -C tester
	@rm -f tester
	@ln -s simplexpress-tester/bin/Release/simplexpress-tester simplexpress-tester
	@echo "-------------"
	@echo "<<<<<<< FINISHED >>>>>>>"
	@echo "SIMPLEXpress Tester is in 'simplexpress-tester/bin/Release'."
	@echo "The link './tester' has been created for convenience."
	@echo "-------------"

tester_debug: simplexpress_debug
	$(MAKE) debug ARCH=$(ARCH) CONFIG=$(CONFIG) SAN=$(SAN) -C simplexpress-tester
	@rm -f tester_debug
	@ln -s simplexpress-tester/bin/Debug/simplexpress-tester tester_debug
	@echo "-------------"
	@echo "<<<<<<< FINISHED >>>>>>>"
	@echo "SIMPLEXpress Tester is in 'simplexpress-tester/bin/Debug'."
	@echo "The link './tester_debug' has been created for convenience."
	@echo "-------------"

all: docs tester

allfresh: cleanall all

.PHONY: all allfresh clean cleandebug cleanrelease docs docs_pdf simplexpress simplexpress_debug ready tester tester_debug
