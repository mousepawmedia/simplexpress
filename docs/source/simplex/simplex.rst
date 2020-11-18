Simplex
###################################

What is Simplex?
===================================

Simplex is the basic class used in SIMPLEXpress to store a model and process
matches against the model. The priority with Simplex models is ease of use
compared to regex. 


Using Simplex
=========================================

Including Simplex
---------------------------------------

To include Simplex, use the following:

..  code-block:: c++

    #include "simplexpress/simplex.hpp"


Creating a Simplex
------------------------------------------

A ``Simplex`` object is created by whatever means is convenient. 

When the Simplex is first created, you must specify the model you are using to
match as a onestring (from PawLIB).

..  code-block:: c++

    onestring model = "^d/";
    Simplex simplex(model);


Match
------------------------------------------

The :code:`match()` member function is used to determine whether input matches
the specified model or not. It takes a onestring as a parameter (the input to
check), and the function returns true if the input is an exact match to the
model, false if not. This replaces both match and search in standard regex, as
Simplex is a single pass parser; if you want to include matches in the middle of
an input, build the model accordingly (ie, with :code:`^.+?/` - which is any
character, one or more, optionally). 

Note that this treats snag groups (``~``) as regular units.

..  code-block:: c++

    onestring search_input1 = "3";
    bool match1 = simplex.match(search_input1);
    // match is true
    onestring search_input2 = "abc";
    bool match2 = simplex.match(search_input2);
    // match is false
    onestring search_input3 = "3a";
    bool match3 = simplex.match(search_input3);
    // match is false

..  note::
    We are also planning a :code:`match()` function that will work statically,
    taking a model and the input to check as parameters, but it is not yet
    implemented.


Snag
------------------------------------------

..  note::
    In process for v0.1. "Match" is a tentative name for the object.

The :code:`snag()` member function is used to separate the part(s) of input
matching the specified model from the remainder of the input. It takes a
onestring as parameter, and returns a Match object containing each of the matched
snag groups in order. (It checks for, but does not return, regular units.)

For example, if you wanted to get times, you could set up a model like this:

..  code-block:: c++

    onestring model = "~d+/:~d+/ ~[(AM)(PM)]?/";
    Simplex times(model);
    Match match1 = times.snag("18:05")     // contains ("18", "05", "")
    Match match2 = times.snag("04:15 PM")  // contains ("04", "15", "PM")
    Match match3 = times.snag("11 03 pm")  // NULL or empty, because it doesn't match the model (no ':')


Simplex Parser
------------------------------------------

..  note::
    In process for v0.1. This section may be inaccurate, or even removed later

The :code:`simplex_parser()` private member function is where Simplex generates
a parsed match with the part of the input that matches the specified model. It
takes a onestring as a parameter (the input to check), and returns a
:ref:`parseresult` object. The `ParseResult` will contain either the matched
result, and the remainder, or an error message and the complete input. 

..  code-block:: c++

    onestring parse_input1 = "3a";
    ParseResult parse1 = simplex.simplex_parser(parse_input1);
    // ParseResult contains tril 'result' == true, onestring 's' == "3",
    // and onestring 'remainder' == "a"
    onestring parse_input2 = "abc";
    ParseResult parse2 = simplex.simplex_parser(parse_input2);
    // ParseResult contains tril 'result' == false, onestring 's' == 
    // "No digits found", and onestring 'remainder' == "abc"

