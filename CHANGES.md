# v2.1.0
* Added several Dockerfiles for building docker images that contain all the needed tools for compiling grapenlp-core in different platforms, namely Alpine 3.6, Alpine 3.7, Alpine 3.8, Ubuntu 16.04 and Ubuntu 18.04.

# v2.0.2
* Minor fixes to allow compilation in MacOS (tested with High Sierra)
* Enabled compilation of Java interface (jgrapenlp)
* Fixed warning in unicode.cpp

# v2.0.1
* Added version number management in CMakefiles

# v2.0.0
* Renamed all grape "stuff" (libraries, namespaces, include folders, etc.) to grapenlp to avoid collisions with other open-source projects (sorry folks, grapes are popular among the open-source community)

# v1.0.1
* Corrected some typos in README.md
* Added LICENSE file to main folder

# v1.0.0

This is the first version uploaded to GitHub. It is operative, though documentation is still lacking. Debug and release versions can be compiled using the script at build/scripts/build.sh. Compilation has been tested in Ubuntu and Alpine, and interfaces for Python and Java have also been developed (see modules pygrapenlp and jgrapenlp).
