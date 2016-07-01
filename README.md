##### Clone the project
```bash
git clone https://github.com/ArthurSonzogni/CBNA_PHPBB_Analysis --recursive
```

CBNA_forum_analysis
===================

A set of functions to **download**, **parse** and **transform** PHPBB forums.

Dependencies
------------

* libcurl
* cmake
* c++ compiler

Hidden dependencies
-------------------

* gumbo-parser
* gumbo-query

theses dependencies are git-downloaded (submodules)
If you fail to clone the repository recursively, you can type : 

```bash
git submodule init
git submodule update
```

Build
-----
```bash
mkdir build
cd build
cmake ..
make
./importer
```
