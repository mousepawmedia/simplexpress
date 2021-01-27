Simplex
###################################

What is Simplex?
===================================

Simplex is the basic class used in SIMPLEXpress to store a model and process
matches against the model. Simplex is designed to be easier to read and write
compared to standard regex. The priority with Simplex models is ease of use.


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

When the Simplex is first created, you must specify the
:ref:`model<simplex_model>` you are using to process matches. A onestring (from
PawLIB) is preferred, but for models using only ``char``, you can define it in
the declaration, too:

..  code-block:: c++

    // Using onestring
    onestring model = "^d/";
    Simplex simplex(model);
    // Using char
    Simplex char_simplex("^l/");

The major functions of Simplex, ``match`` and ``snag``, can be also used without
creating a Simplex object. (See the function pages for details on use.) Creating
a Simplex object is the more efficient of these two methods when you will be
reusing the model, however.