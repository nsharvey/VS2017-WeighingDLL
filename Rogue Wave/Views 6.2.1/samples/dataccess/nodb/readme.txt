
                             Rogue Wave Views 6.2
                             Data Access Package

                                Samples 'nodb'


To compile the programs, go to the directory <system>, and run the 'make'
utility provided on your system.
Some ports are provided with compiler-specific project files.
Run the samples from the <system> directory.

Sample: 'folio'
---------------
  This sample shows how to customize a Table Gadget look and how to define a
  custom subclass.

  Table Gadget's even rows are white and odd rows gray.

  The font color is blue except for the Profits column if it's value is
  negative: it that case, the color is red.

  Buttons:

    * Load: to load a pfl file in the Table Gadget

    * Save: to save the Table Gadget contents in a pfl file

    * Clear: to clear the Table Gadget

  Source files:
    - include/folio.h
    - src/folio.cpp
    - include/foliotbl.h
    - src/foliotbl.cpp


Sample: 'form'
--------------
  This sample shows how to modify a datasource by using db-gadgets connected to
  it.

  The Navigator lets you move from one row to another.

  The Lock data button lets you edit or not the differents fields you depending
  it is on or off.

  The Name field is always in capital letter even if it is edited with small
  letters. The Account field font is blue if positive, red if negative.

  Source files:
    - include/form.h
    - src/form.cpp


Sample: 'html'
--------------
  This sample shows how to use the HTML Reporter to generate a HTML report.

  The generated report is named "report.html" and can be opened with any HTML
  browser.

  You can choose:

    * if you want a table of contents or not and if you want it at the end or
      at the beginning of the report

    * which model you want for the generated file

  When this is done, you just have to click the Generate button.

  Source files:
    - include/html.h
    - src/html.cpp


Sample: 'sintoggl'
------------------
  This sample shows how to modify the current editor of a Table Gadget's
  column.

  The Sell's column contains a three states button instead of a boolean.

  Source files:
    - include/sintoggl.h
    - src/sintoggl.cpp


Sample: 'usercall'
------------------
  This sample shows how to define global callbacks.

  Buttons:

    * Load: to load a mem file in the Table Gadget

    * Save: to save the Table Gadget contents in a mem file

  Source files:
    - include/usercall.h
    - src/usercall.cpp

