Purpose
=======

specfile and readspec are program utilities to parse and display binary specification files from SGI's propietary tardist package format for the IRIX operating system. They have been created to retrieve package dependency information from these specification files on other OS'ses like Linux and other Unix variants.

With this information available, this can be used to recreate the ASCII .spec files from which the package has been created and can be exported to common formats like XML.

Overview of tardist format
==========================

The tardist package consist of at least three files: The specification file, the idb file and one or more image files:

  - The image files contain the actual binary or text files, compressed with the gzip compress() function and stored sequentially in the image file.

  - The idb file stores all file details like which image file stores the file with offset and length, install location, owners and permissions, pre- or post- or exit-install scripts and hardware dependencies.

  - The specification file will contain information on product name and the names of images and subsystems, version numbering, and prerequirements for the product subsystems, as well as lists of product subsystems which will get replaced and even incompatibilities with subsystems from other products.

A program for retrieving files from image files has already been made: mydb.c made by Luc Chouinard, available at http://persephone.cps.unizar.es/~spd/src/other/mydb.c
