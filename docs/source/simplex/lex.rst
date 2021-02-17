Lex
####################################

..  _simplex_lex:

Simplex Lex
------------------------------------------

The :code:`lex()` member function is used to determine whether the beginning of
input matches the specified :ref:`model<simplex_model>` or not, and also
processes any :ref:`snag<simplex_snag>` units included. When used with a
generated Simplex object, it takes either a onestring or a string of ``char`` as
a parameter (the input to check), and the function returns a SimplexResult
object with the details of the match. The boolean ``match`` in this object will
be true if the beginning of input matches the model, false if not. (It will return true whether there are
characters remaining after the matched characters or not. If you want the match
to succeed *only* if the entire input matches the entire model, use
:ref:`match<simplex_match>` instead.) If match is true, the FlexArray<onestring>
``snag_array`` will be populated with the results of any snag units, and
``match_length`` will contain the total length of matched characters.

Simplex is a single pass parser; if you want to include matches in the middle of
an input, build the model accordingly (ie, with a Unit like :code:`^.*/` - which
is any character, one or more, optionally - at the beginning of the units you're
trying to match or lex).


..  code-block:: c++

    // Using the model example on the main Simplex page:
    onestring model = "^d/";
    Simplex simplex(model);

    onestring lex_input1 = "3";
    SimplexResult lex1 = simplex.lex(lex_input1);
    // lex1.match is true, and lex1.matched_length = 1
    onestring lex_input2 = "abc";
    SimplexResult lex2 = simplex.lex(search_input2);
    // lex2.match is false, and lex2.matched_length = 0
    onestring lex_input3 = "3a";
    SimplexResult lex3 = simplex.lex(lex_input3);
    // lex3.match is true, and lex3.matched_length = 1

..  note::
    Lex contains a true result on the final input, while match would not. It
    also provides the length of 1 so you can know that only the first character
    matched the model you provided.

Lex will also handle snag units:

..  code-block:: c++

    // A model for one or more digits
    onestring model_snag = "~d+/";
    Simplex simplex_snag(model_snag);

    onestring lex_input4 = "123";
    SimplexResult lex4 = simplex_snag(lex_input4);
    // lex4.match is true, lex4.matched_length = 3,
    // and lex4.snag_array[0] = "123"
    onestring lex_input5 = "123steve";
    SimplexResult lex5 = simplex_snag(lex_input5);
    // lex5.match is true, lex5.matched_length = 3 because only the first three
    // characters match, and lex5.snag_array[0] = "123" again.


Static Lex
---------------------------------------

The ``lex()`` function also can operate statically using two parameters
instead of one. The first parameter is still the input that you would like to
check, and the second parameter is then the :ref:`model<simplex_model>` you want
to check against. This works either with two assigned onestrings, or in the case
of simpler models and inputs, a string of ``char``:

..  code-block:: c++

    // Onestrings:
    onestring static_model = "^l/";
    onestring static_input1 = "a";
    SimplexResult static1 = Simplex::lex(static_input1, static_model);
    // static1.match is true, static1.matched_length = 1

    // Chars
    SimplexResult static2 = Simplex::match("g", static_model);
    // static2.match is true
    SimplexResult static3 = Simplex::match(static_input1, "^d/");
    // static3.match is false
    SimplexResult static4 = Simplex::match("7", "^d/");
    // static4.match is true, static4.matched_length = 1

Lex will return true if the characters at the beginning of the input match the
model provided, either in static or member form.