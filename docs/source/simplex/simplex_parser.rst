Simplex Parser
########################################

If you are using ``match()`` or snag()``, the Simplex class takes care of
everything on this page for you. However, if you want to call :ref:`Simplex
Parser<simplex_parser>` directly for a SimplexResult object, you will first need
to use ``parse_model`` to generate the model array.

.. _parse_model:

Parse Model
----------------------------------

The :code:`Unit::parse_model` function is a helper function in the Unit class.
It generates the Unit models from an input string, and is used for this purpose
in the Simplex constructor. It takes as parameters first a onestring containing
the entered model, and second the ``FlexArray<Unit*>`` that will have Unit
objects populated into it. This *does* modify the array parameter, but not the
onestring.

Example:

..  code-block:: c++

    // Create the model and model array objects, then parse
    onestring model = "~d+/^l?/";
    FlexArray<Unit*> model_array;
    Unit::parse_model(model, model_array);

In this example, the array is modified to contain two Units, the first of which
will snag one or more digit characters, the second of which will match exactly
zero or one latin characters.



.. _simplex_parser:

Simplex Parser Function
------------------------------------------

The :code:`simplex_parser()` function is internally used by the
``snag()`` and ``match()`` functions to produce their results, but can be
accessed directly if needed. This is where Simplex parses the input to determine
whether the results match, and snags any matching snag units to return to their
respective functions.

This function is not optimized or designed to be used externally, so there are
no helpful overloads currently implemented. If you need to use it, though, it
takes two parameters: an input string as a ``onestring`` to check, and a
``FlexArray<Unit*>`` containing the parsed model of units. (If you need to
generate this separately, see :ref:`Parse Model<parse_model>`.) It returns a
``SimplexResult`` object that consists of a boolean ``match`` (used by
``match``) and a FlexArray of onestrings ``snag_array`` (used by ``snag``),
which will be empty if the match fails.

Example:

..  code-block:: c++

    // After using the model generation in the above example...
    onestring input = "123a";
    SimplexResult result = simplex_parser(input, model_array);
    onestring input2 = "1234";
    SimplexResult result2 = simplex_parser(input, model_array);

The ``result`` object now contains the boolean ``match``, which is true, and the
FlexArray snag_array, which contains one onestring ``123``. However, in
``result2``, ``match`` is false, and the snag_array is empty, because the input
did not contain a match for the ``^l/`` Unit.
