Simplex Model
####################################

..  _simplex_model:

What is a Simplex model?
-----------------------------------

As a regular expression parser, SIMPLEXpress uses the model to determine what
exactly you are trying to match. The model communicates to the SIMPLEXpress code
the specifics of what qualifies as a match or not.

For the most part, SIMPLEXpress models are read literally. The only time they
are not literal is if you include something into a Unit, and the only reserved
characters outside of a Unit are the characters used to mark the beginning of a
Unit, or escape them.

..  note::
    Behind the scenes, each individual literal character is also considered a
    Unit, so when you see references to Units, consider the context to know
    whether they may also include individual literals.

Throughout this document, where relevant, current functionality as of v0.1 and
planned functionality will be split into separate subsections.

Reserved characters
--------------------------------------

Outside a Unit
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
There are only three hard reserved characters in Simplex models, which are used
outside of a Unit:

* ``^``: Used to indicate the beginning of a non-literal Unit.
* ``~``: Used to indicate the beginning of a snag Unit.
* ``%``: Used to escape any of the three reserved characters as needed.

Inside a Unit (Soft Reserved)
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

Inside of a Unit, various characters are used to indicate different behavior.

* ``/``: Closes Unit. After all other characters describing Unit.
* ``!``: NOT. Before the matcher.
* ``?``: Optional. After matcher.
* ``+``: Multiple. After the matcher.
* ``*``: Optional *and* Multiple. After matcher.

..  _model_planned_reserved:

Planned Functionality (Soft Reserved Characters)
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

* ``[ ]``: Set. Match any one of the Unit values within. Space delimited.
* ``<>``: Literal Set: Any literal character within.
* ``( )``: Group. Allows for literal characters, strings, and further Units
  (simplex-ception!) within a Unit. For example, ``^(abc)?/`` matches optional
  abc.
* ``%``: Escape following character (to make literal). Affects exactly one
  character. Modifiers following that character will affect that character's
  Unit.
* ``{ }``: Exclusion. Anything within is checked, but is not returned as part of
  the result. Parallels regex "lookahead".
* ``$``: Line beginning or end. Logically, we can combine the two together,
  because nothing can follow a line end, and nothing can precede a line
  beginning. In multi-line mode, this would match a line break.
* ``#1``, ``#2-3``, (etc, any number): Exact number or range of matches.

Examples:

* ``^[(abc) (123)]/`` matches either ``abc`` or ``123``, but not both.
* ``^[lu d]/`` matches either an uppercase letter or a digit, but not both.
* ``^[(abc) d]/`` matches either ``abc`` or a digit.
* ``^[<abc> d]/`` matches either ``a``, ``b``, ``c``, or a digit.

Units
---------------------------------------

Current Unit Functionality (v0.1)
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

Units are the basic blocks of a Simplex model. Each Unit indicates one discrete
item that Simplex needs to match. A literal Unit consists of a single character
to be matched exactly (any single character - other than the three hard reserved
characters mentioned above - if used outside of a non-literal Unit). A
non-literal Unit consists of the opening Unit marker, indicators for any
desired, modifiers, and the matcher. The most common 'matcher' will be one of
the one or two character :ref:`simplex_specifiers` which indicates a match such
a digit, an alphanumeric character, and so on.

As of verison 0.1, these are the only functioning matchers.

Planned Unit Functionality
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

In later versions, matchers will also be able to include various tools for sets
and groups. See :ref:`model_planned_reserved` for more information.

Modifiers
--------------------------------------------

..  note::
    Individual literals cannot have modifiers of any kind. If you need to use
    modifiers on a literal, you must place it into a specifier Unit.

Modifiers affect the behavior of the Unit in various ways. The base behavior of
a specifier Unit, for example, ``^a/`` for an alphanumeric match, will match
exactly one alphanumeric character, and will fail the match if there is no
alphanumeric character present in the corresponding position in the input
string. Modifiers are as follows:

* Negative: the ``!`` character preceding the matcher will negate the specifier
  (or other matcher). The single character requirement (if not otherwise
  modified) remains the same; it instead becomes one single character of
  anything *but* the matcher. Using our alphanumeric example, if you wanted a
  single character that was *anything non-alphanumeric* (symbols, for example),
  your model would look like ``^!a/``. Note this must come before the matcher,
  placing it afterward will not work.

* Optional: the ``?`` character after the matcher indicates that the Unit is
  optional. Thus, either 0 or 1 matching characters will satisfy the
  requirement. So, to match whether there is an alphanumeric character in that
  position or not, you would use the model ``^a?/``.

* Multiple: the ``+`` character after the matcher indicates the Unit can be
  multiple. This reads as "one or more"; it has to have at least *one* matching
  character to pass, but will match and consume as many characters from the
  input as fit the criteria until it encounters a character that does *not*
  match. To match one or more alphanumeric characters in a row, your model would
  look like ``^a+/``.

* Multiple *and* Optional: the ``*`` character after the matcher indicates that
  the Unit is both optional and multiple. Thus, 0 or more matching characters
  will cause the match to pass. As with Multiple, it will continue to match and
  consume characters from the input as long as it encounters characters that
  match. The model for matching any number (including none) of alphanumeric
  characters in a row looks like ``^a*/``.

* Snag: the ``~`` character in place of the Unit opener ``^`` indicates a snag
  Unit. Snag Units behave a little differently from the the other modifiers and
  can be used with any of them. Snag Units are used with the snag function to
  return matched characters; if used in a match function, behavior is identical
  to a regular Unit. This difference is useful when you know that specific parts
  of your matches are not meaningful except that they are there, but need to
  capture other parts of the matches to process. Using the alphanumeric example,
  we can demonstrate a slightly more complicated model. For example, you need to
  capture one or more alphanumeric characters before a comma, but you know the
  comma is going to be there regardless and don't need to store it; you could
  write a model like ``~a+/,`` (in this case the comma is a literal Unit), and
  then when using the snag function your return array would contain anything
  before the comma. Example: ``12345,`` would return an array containing the
  onestring ``12345``; ``s,`` would return an array containing ``s``, and so on.

..  note::
    If you have an optional Unit between two other potentially overlapping
    Units, the model will still fail if the optional is not met. For example,
    with the model ``~l+/~d*/~l+/``, an input of ``stevefred`` would fail,
    whereas an input of ``steve12345fred`` would pass. The reasoning for this is
    that in the case of ``stevefred`` there are not, in fact, two separate "one
    or more latin letters" chunks, only one, which we have no way to arbitrarily
    split.

..  _simplex_specifiers:

Specifiers
--------------------------------------------

Current Specifier Functionality (v0.1)
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

Specifiers consist of a single letter that indicates which type of character is
being matched. Currently operational specifiers are:

* ``a``: alphanumeric
* ``d``: digit
* ``l``: latin Letter
* ``n``: newline (`\n`)
* ``o``: math operator
* ``p``: punctuation
* ``r``: Carriage return (`\r`)
* ``s``: Literal space
* ``t``: tab
* ``w``: whitespace
* ``.``: Any character.

Planned Specifier Functionality
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

* Multi character specifiers:

    * Inclusion of ``u`` or ``l`` after a specifier that includes letters to
      indicate upper or lower case.
    * ``c``: classification (Reserved for later expanded character classes, such
      as ``c_hangal`` for Hangal characters) (2.0-3.0)
    * ``u#``: unicode (accepts ``u78`` or ``u57-78``) (2.0)

* ``e``: extended Latin (2.0)
* ``g``: greek (2.0)
* ``i``: iPA (2.0)