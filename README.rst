========================
 xopreplace user manual
========================

+-------------------+----------------------------------------------------------+
| **Title**         | xopreplace (Machine-SUIF pass for replacing a function   |
|                   | call by a SUIFvm operator)                               |
+-------------------+----------------------------------------------------------+
| **Author**        | Nikolaos Kavvadias 2005, 2006, 2007, 2008, 2009, 2010,   |
|                   | 2011, 2012, 2013, 2014                                   |
+-------------------+----------------------------------------------------------+
| **Contact**       | nikos@nkavvadias.com                                     |
+-------------------+----------------------------------------------------------+
| **Website**       | http://www.nkavvadias.com                                |
+-------------------+----------------------------------------------------------+
| **Release Date**  | 02 October 2014                                          |
+-------------------+----------------------------------------------------------+
| **Version**       | 1.0.0                                                    |
+-------------------+----------------------------------------------------------+
| **Rev. history**  |                                                          |
+-------------------+----------------------------------------------------------+
|        **v1.0.0** | 2004-10-02                                               |
|                   |                                                          |
|                   | Initial release.                                         |
+-------------------+----------------------------------------------------------+


1. Introduction
===============

``xopreplace`` is a transformation pass that is used for replacing occurences of 
certain function calls by instances of equivalent operators, if such exist. It 
can be used on the SUIFvm IR (intermediate representation) for replacing builtin 
functions by SUIFvm operators that provide the same functionality. This allows 
for expanding basic blocks and identifying better opportunities for 
optimizations in the context of software and hardware synthesis.

The supported operators currently are:

``abs``: 
  absolute value
``min``:
  minimum of two operands
``max``:
  maximum of two operands.

This pass depends on the machine, cfg and suifvm libraries MachSUIF. 
The ``xopreplace`` pass has been tested with MachSUIF 2.02.07.15.


2. File listing
===============

The ``xopreplace`` distribution includes the following files:
   
+-----------------------+------------------------------------------------------+
| /xopreplace           | Top-level directory                                  |
+-----------------------+------------------------------------------------------+
| AUTHORS               | List of ``xopreplace`` authors.                      |
+-----------------------+------------------------------------------------------+
| LICENSE               | The modified BSD license governs ``xopreplace``.     |
+-----------------------+------------------------------------------------------+
| README.rst            | This file.                                           |
+-----------------------+------------------------------------------------------+
| README.html           | HTML version of README.                              |
+-----------------------+------------------------------------------------------+
| README.pdf            | PDF version of README.                               |
+-----------------------+------------------------------------------------------+
| VERSION               | Current version of the project sources.              |
+-----------------------+------------------------------------------------------+
| rst2docs.sh           | Bash script for generating the HTML and PDF versions |
|                       | of the documentation (README).                       |
+-----------------------+------------------------------------------------------+
| suif_main.cpp         | Entry point for building the standalone program      |
|                       | ``do_xopreplace`` that implements the pass.          |
+-----------------------+------------------------------------------------------+
| suif_pass.cpp         | Define the SUIF pass built as the dynamically        |
|                       | loadable library ``libxopreplace.so``.               |
+-----------------------+------------------------------------------------------+
| suif_main.h           | C++ header file for the above.                       |
+-----------------------+------------------------------------------------------+
| utils.h               | C header file with implementations of auxiliary      |
|                       | functions.                                           |
+-----------------------+------------------------------------------------------+
| xopreplace.cpp        | Implementation of the ``xopreplace`` pass.           |
+-----------------------+------------------------------------------------------+
| xopreplace.h          | C++ header file containing declarations and          |
|                       | prototypes for the above.                            |
+-----------------------+------------------------------------------------------+


3. Installation
===============

Unpack the ``xopreplace`` archive wherever you like, e.g. in 
``$MACHSUIFHOME/cfa/xopreplace``.
You don't need to modify anything in the Makefile, if you have a working
MachSUIF 2 installation.

The program binary (``do_xopreplace``) will be installed at ``$NCIHOME/bin`` and 
the shared library (``libxopreplace.so``) at ``$NCIHOME/solib``, where NCIHOME is 
the SUIF 2 top-level directory.


4. Usage details
================

The pass accepts an input file in CFG form to operate. Textual output is 
generated, written to stdout by default.

Usage synopsys:
| ``$ do_xopreplace test.cfg``
