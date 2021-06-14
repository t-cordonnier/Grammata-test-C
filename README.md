WHAT IS IT
==========

Grammata is a project to create a character encoding giving priority to efficiency of algorithms.
 
 Actually most people use Unicode for every program.
 Unicode has been designed giving priority to compatibility with older encodings, mainly ASCII, ISO-8859-1 and later, existing encodings for non-latin alphabets.
 Unfortunately, some algorithms which are fast with ASCII may loose their efficiency when applied to an extension of it such as Unicode.
 
 The idea now is to check whenever a new encoding starting from scratch, without being necessarily compatible with ASCII, could enable to provide more efficient implementations
 for algorithms such as ordering of words or case conversion, whic are very often used during searches (or during creation of an index).
 
 For the latin alphabet, Grammata differs from Unicode like this:
 - zone between hexadecimal 40 and 7F is strictly reserved to letters. 40, 60, 5A-5F and 7A-7F are intentionally left blank.
   This enables to check if a character is a letter, or to do lower/uppercase conversion by using bit filters
 - characters with accents are always represented in a canonical form, i.e. where accent is considered as a distinct character.
   However, contrarily to Unicode, a dedicated zone between 80 and BF, is dedicated to them, so they would not take 2 bytes as canonical forms in UTF-8.
   This enables easier implementation of complex collation algorithms such as the one used for french language
   (collation is the algorithm which says whenever a word is before or after another one in alphabetical order).
   
WHAT YOU WILL FIND HERE
=======================

For the moment I mostly did tests to check whenever such an encoding would really be more performant than Unicode. Here you can find a few test programs, written in C, to do this check.
The programs will re-order a long list of french words, using the complex french rules (http://www.lirmm.fr/~lafourcade/Souk/trif/tri-du-francais.html): first without accents,
then for words which differ only by accent or case, use the last accent of the word, then previous one, etc.

IN this test I volontarily use a slow sort algorithm: what I want to compare is the speed for collation, not for the sort, so the most collations I can do, the better the test is.

According to these tests last time I launched them, Grammata looked about 20% faster than ISO-8859-1 (latin1), and only 10% slower than pure ASCII (which would not respect french rules).
Since Unicode extends ISO-8859-1, I can say that almost for french language, there is a potential gain.
And more generally, Grammata would enable to be close to performances of pure binary collation (but respecting rules of your human language, which binary collation does not)

There is no formal specification for Grammata yet, but if I can do again this work for other languages, then it will be time to write it.
