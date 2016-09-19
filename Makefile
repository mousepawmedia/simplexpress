none:
	@echo "=== SIMPLEXpress 1.0 ==="
	@echo "Select a build target:"
	@echo "   make ready         Build SIMPLEXpress and bundles it for distribution."
	@echo "   make clean         Clean up SIMPLEXpress and Tester."
	@echo "   make cleanall      Clean up everything."
	@echo "   make cleandebug    Clean up SIMPLEXpress and Tester Debug."
	@echo "   make cleanrelease  Clean up SIMPLEXpress and Tester Release."
	@echo "   make docs          Generate HTML docs."
	@echo "   make docs_pdf      Generate PDF docs."
	@echo "   make library       Build SIMPLEXpress as release."
	@echo "   make library_debug Build SIMPLEXpress as debug."
	@echo "   make tester        Build SIMPLEXpress Tester (+ SIMPLEXpress) as release."
	@echo "   make tester_debug  Build SIMPLEXpress Tester (+ SIMPLEXpress) as debug."
	@echo "   make all           Build everything."
	@echo "   make allfresh      Clean and rebuild everything."
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
	@echo "For other build options, see the 'make' command in 'docs/', 'library/', and 'tester/'."

clean:
	$(MAKE) clean -C library
	$(MAKE) clean -C tester

cleanall: clean
	$(MAKE) clean -C docs

cleandebug:
	$(MAKE) cleandebug -C library
	$(MAKE) cleandebug -C tester

cleanrelease:
	$(MAKE) cleanrelease -C library
	$(MAKE) cleanrelease -C tester

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
	@echo "View docs at 'docs/build/latex/SIMPLEXpress.pdf'."
	@echo "-------------"

library:
	$(MAKE) release ARCH=$(ARCH) CONFIG=$(CONFIG) -C library
	@echo "-------------"
	@echo "<<<<<<< FINISHED >>>>>>>"
	@echo "PuppeteerXML is in 'library/lib/Release'."
	@echo "-------------"

library_debug:
	$(MAKE) debug ARCH=$(ARCH) CONFIG=$(CONFIG) -C library
	@echo "-------------"
	@echo "<<<<<<< FINISHED >>>>>>>"
	@echo "PuppeteerXML is in 'library/lib/Debug'."
	@echo "-------------"

ready: library
	@rm -rf simplexpress
	@echo "Creating file structure..."
	@mkdir -p simplexpress/lib
	@echo "Copying SIMPLEXpress..."
	@cp -r library/include simplexpress/
	@cp library/lib/Release/libsimplexpress.a simplexpress/lib/libsimplexpress.a
	@echo "Copying README and LICENSE..."
	@cp README.md simplexpress/README.md
	@cp LICENCE.md simplexpress/LICENCE.md
	@echo "-------------"
	@echo "<<<<<<< FINISHED >>>>>>>"
	@echo "The library is in 'simplexpress'."
	@echo "-------------"

tester: library
	$(MAKE) release ARCH=$(ARCH) CONFIG=$(CONFIG) -C tester
	@rm -f tester
	@ln -s simplexpress-tester/bin/Release/simplexpress-tester tester
	@echo "-------------"
	@echo "<<<<<<< FINISHED >>>>>>>"
	@echo "SIMPLEXpress Tester is in 'tester/bin/Release'."
	@echo "The link './tester' has been created for convenience."
	@echo "-------------"


tester_debug: library_debug
	$(MAKE) debug ARCH=$(ARCH) CONFIG=$(CONFIG) -C tester
	@rm -f tester_debug
	@ln -s simplexpress-tester/bin/Debug/simplexpress-tester tester_debug
	@echo "-------------"
	@echo "<<<<<<< FINISHED >>>>>>>"
	@echo "SIMPLEXpress Tester is in 'tester/bin/Debug'."
	@echo "The link './tester_debug' has been created for convenience."
	@echo "-------------"

all: docs tester

allfresh: cleanall all

.PHONY: all allfresh clean cleanall cleandebug cleanrelease docs docs_pdf library library_debug ready tester tester_debug
