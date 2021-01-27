Match
####################################

..  _simplex_match:

Simplex Match
------------------------------------------

The :code:`match()` member function is used to determine whether input matches
the specified :ref:`model<simplex_model>` or not. When used with a generated
Simplex object, it takes either a onestring or a string of ``char`` as a
parameter (the input to check), and the function returns true if the input is an
exact match to the model, false if not. This replaces both match and search in
standard regex, as Simplex is a single pass parser; if you want to include
matches in the middle of an input, build the model accordingly (ie, with a Unit
like :code:`^.*/` - which is any character, one or more, optionally, on either
end of the units you're trying to match).


..  code-block:: c++

    // Using the model example on the main Simplex page:
    onestring model = "^d/";

    onestring match_input1 = "3";
    bool match1 = simplex.match(search_input1);
    // match1 is true
    onestring match_input2 = "abc";
    bool match2 = simplex.match(search_input2);
    // match2 is false
    onestring match_input3 = "3a";
    bool match3 = simplex.match(search_input3);
    // match3 is false

..  note::
    Match treats :ref:`snag<simplex_snag>` groups (``~``) as regular units.


Static Match
---------------------------------------

The ``match()`` function also can operate statically using two parameters
instead of one. The first parameter is still the input that you would like to
check, and the second parameter is then the :ref:`model<simplex_model>` you want
to check against. This works either with two assigned onestrings, or in the case
of simpler models and inputs, a string of ``char``:

..  code-block:: c++

    // Onestrings:
    onestring static_model = "^l/";
    onestring static_input1 = "a";
    bool static1 = Simplex::match(static_input1, static_model);
    // static1 is true

    // Chars
    bool static2 = Simplex::match("g", static_model);
    // static2 is true
    bool static3 = Simplex::match(static_input1, "^d/");
    // static3 is false
    bool static4 = Simplex::match("7", "^d/");
    // static4 is true

Either match function will only return true if the entire input matches the
entire model.