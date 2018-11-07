# GRAPE: Grammar Annotation Pattern Engine

GRAPE-core is an efficent engine for the application of local grammars, based on the algorithms described in http://igm.univ-mlv.fr/~sastre/publications/sastre11t.zip. GRAPE can be used as a sentence recognizer in chatbots (see http://igm.univ-mlv.fr/~sastre/publications/sastre09ip.pdf). In this case, grammar outputs are XML tags that either delimit the entities to extract or simply identify the intent the sentences belong to. The supported grammars are those written with the Unitex software (http://unitexgramlab.org/). These grammars are equivalent to CFGs with output but have a more readable graphical representation similar to flowcharts. Grammar boxes contain possible words to recognize and/or calls to subgrammars, and can also define an output. The sentences recognized by a Unitex grammar can be identified by following the flowchart, provided that subgrammar names are descriptive enough or proper comments are added to the grammar boxes.

Words to be recognized can be given by a set of conditions or predicates on their lexical, syntactic and semantic features (e.g. any inflected form of verb "to be"). GRAPE automatically adds weights to the grammar transitions depending of the specificity degree of the predicates used (e.g. &lt;TOKEN&gt; predicate gets 0 points since it recognizes any token, while other predicates or specific words get a greater score). This enables GRAPE to later compute the sentence interpretation with the greatest overall score for the case of ambiguous grammars. For instance, let it be the following sentence to be recognized by a chatbot:

Send Merry Christmas to the phone 555-555-555

GRAPE is able to understand that the message to send is "Merry Christmas" and not "Merry Christmas to the phone 555-555-555" if we define a grammar that uses predicate &lt;TOKEN&gt; to recognize the message and more restrictive predicates to recognize left and right contexts of the message. GRAPE ensures that the highest score interpretation is computed in O(n^3), and in linear time for most of the natural language sentences. In my experience, GRAPE is able to process thousands of sentences per second in a standard PC, and can also be run in smartphones in order to leverage backend processing.

## Supported platforms

* Alpine (tested 3.6, 3.7 & 3.8)
* MacOS (tested High Sierra)
* Ubuntu (tested 16.04 & 18.04)

## Required compilation & test tools

* gcc 5.4.0 or greater
* CMake 3.6 or greater
* SWIG 3.0.8 or greater
* Java JDK 8 for the Java SWIG interface
* Python 3.6 for the Python SWIG interface
* Google Test 1.7.0 or greater

## Dependencies

* libboost-dev 1.58.0 or greater
* libboost-program-options-dev 1.58.0 or greater

## How to build

Run script build/scripts/build.sh, providing it a target version. For instance:

`build.sh release`

Run the script without arguments to get the list of available targets.

Additionally, several Dockerfiles can be found in folder build/docker, which can be used for building docker images that contain all the needed tools for compiling grapenlp-core, namely:

* Alpine 3.6, 3.7 and 3.8
* Ubuntu 16.04 and 18.04

The purpose of these Dockerfiles is twofold:
* you may compile grapenlp-core with these docker images (indeed, for generating the Alpine version there is no other choice), or
* you may install the compilation and test tools in your own machine, extracting the installation commands from the Dockerfile, then compile grapenlp-core in your machine.

For the second option, follow the Dockerfile that corresponds to your system. Note that it is not possible to make a MacOS docker image, so I cannot provide such a Dockerfile. However, you can install the C++ compiler and a git client by installing XCode from the Apple Store, and cmake, swig, boost and python with brew (see https://brew.sh/). GoogleTest must be compiled from the sources, which can be downloaded from https://github.com/google/googletest/releases. Finally, installation instructions of the JDK in MacOS can be found in the Web.

For building the docker images, enter the folder with the Dockerfile you want to build (e.g. build/docker/ubuntu/16.04) and type the following command, replacing "image_name" with the name you want to give the image (e.g. grapenlp-ubuntu1604):

`docker build -t image_name .`

To run the image, type the following command replacing "image_name" with the name you chose for the image:

`docker run -it image_name bash`

Once inside the docker, type the following commad to switch to the build user (compiling grapenlp-core does not require special permissions):

`su build`

You can clone the project without having to create a GitHub account with the following command:

`git clone git://github.com/GrapeNLP/grapenlp-core.git`

Now enter the project folder:

`cd grapenlp-core`

Finally, run the build script:

`build/scripts/build.sh`

The compiled files will be placed in folder bin/release.

## License

<a href="/LICENSE"><img height="48" align="left" src="http://www.gnu.org/graphics/empowered-by-gnu.svg"></a>

This program is licensed under the GNU Lesser General Public License version 2.1. Contact javier.sastre@telefonica.net for further inquiries.

Some files for the implementation of Unicode management have been borrowed from the Unitex project, which is licensed under the same license. These can be distinguished by their license headers.
