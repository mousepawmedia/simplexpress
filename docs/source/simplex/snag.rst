Snag
####################################

..  _simplex_snag:

Simplex Snag
------------------------------------------

The :code:`snag()` function is used to capture the parts of an input matching
snag Units in the model. If the input is not a match for the model, it will
return an empty array. Otherwise, it will return a FlexArray of onestrings, and
each snag Unit generates its own onestring in the return, whether it is a single
character or multi character Unit.

The member function uses the :ref:`model<simplex_model>` specified when defining
the Simplex object, and takes a single parameter, which is either a onestring or
a string of ``char``, to be processed against the model.

For example, to get *just* the numbers out of a time, you could set up a model
like this:

..  code-block:: c++

    onestring model = "~d+/:~d+/ ~[(AM)(PM)]?/";
    // This model will snag one or more digits, followed by matching a literal :
    // then snag one or more digits again, then optionally snag either AM or PM.
    // NOTE: the syntax for the final unit, [(AM)(PM)], is not currently
    // implemented in v0.1
    Simplex times(model);
    FlexArray<onestring> match1 = times.snag("18:05")
    // contains ("18", "05", "")
    FlexArray<onestring> match2 = times.snag("04:15 PM")
    // contains ("04", "15", "PM")
    FlexArray<onestring> match3 = times.snag("11 03 pm")
    // empty, because it doesn't match the model (no ':')

Static Snag
-----------------------------------

The ``snag()`` function also can operate statically using two parameters
instead of one. The first parameter is still the input that you would like to
check, and the second parameter is then the :ref:`model<simplex_model>` you want
to check against. This works either with two assigned onestrings, or in the case
of simpler models and inputs, a string of ``char``:

..  code-block:: c++

    // Onestrings:
    onestring static_model = "~l/";
    onestring static_input1 = "a";

    FlexArray<onestring> static1 = Simplex::snag(static_input1, static_model);
    // static1.at(0) is "a"

    // Chars
    FlexArray<onestring> static2 = Simplex::match("g", static_model);
    // static2.at(0) is "g"
    FlexArray<onestring> static3 = Simplex::match(static_input1, "~d/");
    // static3 is an empty array
    FlexArray<onestring> static4 = Simplex::match("7", "~d/");
    // static4.at(0) is "7"

Either snag function will only return snag strings if the entire input matches
the entire model (in other words, if ``match()`` returns true). Otherwise the
array will be empty.