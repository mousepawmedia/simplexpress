..  _parseresult:

Parse Result
###################################

What is a Parse Result?
===================================

``ParseResult`` is the object created by ``UnitParser`` to return results. It
uses one of the different parser functions defined in ``UnitParser`` to match
input against a specified model, and will return either ``make_success`` with
the matching contents separated from the remainder of the onestring, or a
``make_error`` with an error message separated from the input.

Using ParseResult
===================================

ParseResult will be created automatically by the functions that call it. You can
access the information in a ParseResult manually, and it includes some helper
functions to use the results directly.

Public member variables
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
For manual use, ParseResult includes three public member variables:

- ``result`` is a trilean that will read ``maybe`` until parsing is complete, 
  ``true`` if a match is successful, and ``false`` if a match fails 

- ``s`` is a onestring storing the successful match result, or error message if 
  match failed

- ``remainder`` is a onestring the remaining input after any successful match 
  (or the entire input if match failed)


To string
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
The ParseResult class includes a helper function to make it easy to produce a
onestring result from a ParseResult object. 

To use, call :code:`.to_string()` on the object:

..  code-block:: c++

    // Example object:
    onestring model = "^d/";
    Simplex simplex(model);
    // Example creation of ParseResult through input:
    onestring input = "3a";
    ParseResult parse = simplex.simplex_parser(input);
    // ParseResult contains tril 'result' == true, onestring 's' == "3",
    // and onestring 'remainder' == "a"
    std::cout << parse.to_string() << std::endl;

Output is :code:`Ok(3, s)`.

