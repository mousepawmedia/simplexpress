SIMPLExpress Tests
###########################

For instructions on using the SIMPLExpress Tester, see :ref:`console`.

Test Namespaces
=========================

Because we use Goldilocks for multiple projects at MousePaw Media, we follow
certain conventions for test and suite IDs.

The `Live-In Testing Standard <https://standards.mousepawmedia.com/lit.html>`__
defines the first part of the ID. For example,

* ``X-`` refers to the SIMPLExpress project.

* ``s`` is a suite, while ``t`` is a test.

* ``B`` is a "behavior" test, and ``S`` is a "stress" test, etc.

The first digit indicate the major sector of SIMPLExpress the suite and its
tests are related to. The second digit is the specific sector, usually a
single class.

Currently, we have just a few test sectors delineated in SIMPLExpress. 

+----+--------------------+
| ID | Sector             |
+====+====================+
| 00 | Simplex class      |
+----+--------------------+
| 01 | UnitParser         |
+----+--------------------+
| 10 | Integration Tests  |
+----+--------------------+


Any subsequent digits indicate the test number. A number may be shared
between behavior and stress tests; both use the same implementation, but
vary in their variables (such as iterations).
