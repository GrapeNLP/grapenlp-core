# GRAPE: Grammar Annotation Pattern Engine

GRAPE-core is an efficent engine for the application of local grammars, based on the algorithms described in http://igm.univ-mlv.fr/~sastre/publications/sastre11t.zip. GRAPE can be used as a sentence recognizer in chatbots (see http://igm.univ-mlv.fr/~sastre/publications/sastre09ip.pdf). In this case, grammar outputs are XML tags that either delimit the entities to extract or simply identify the intent the sentences belong to. The supported grammars are those written with the Unitex software (http://unitexgramlab.org/). These grammars are equivalent to CFGs with output but have a more readable graphical representation similar to flowcharts. Grammar boxes contain possible words to recognize and/or calls to subgrammars, and can also define an output. The sentences recognized by a Unitex grammar can be identified by following the flowchart, provided that subgrammar names are descriptive enough or proper comments are added to the grammar boxes. 

Words to be recognized can be given by a set of conditions or predicates on their lexical, syntactic and semantic features (e.g. any inflected form of verb "to be"). GRAPE automatically adds weights to the grammar transitions depending of the specificity degree of the predicates used (e.g. &lt;TOKEN&gt; predicate gets 0 points since it recognizes any token, while other predicates or specific words get a greater score). This enables GRAPE to later compute the sentence interpretation with the greatest overall score for the case of ambiguous grammars. For instance, let it be the following sentence to be recognized by a chatbot:

Send Merry Christmas to the phone 555-555-555

GRAPE is able to understand that the message to send is "Merry Christmas" and not "Merry Christmas to the phone 555-555-555" if we define a grammar that uses predicate &lt;TOKEN&gt; to recognize the message and more restrictive predicates to recognize left and right contexts of the message. GRAPE ensures that the highest score interpretation is computed in O(n^3), and in linear time for most of the natural language sentences. In my experience, GRAPE is able to process thousands of sentences per second in a standard PC, and can also be run in smartphones in order to leverage backend processing.


## Supported platforms

* Ubuntu (tested 16.04 & 18.04)
* Alpine (tested 3.6)

## Required compilation tools

* gcc 5.4.0 or greater
* CMake 3.6 or greater
* SWIG 3.0.8 or greater
* Java JDK 8 for the Java SWIG interface
* Python 3.6 for the Python SWIG interface

## Dependencies

* libboost-dev 1.58.0 or greater
* libboost-program-options-dev 1.58.0 or greater

## How to build

Run script build/scripts/build.sh, providing it a target version. For instance:

build.sh release

## Building the Android version

In order to build GrapeNLP for a particular Android ABI $ANDROID_ABI and Android native API level $ANDROID_NATIVE_API_LEVEL, run the script

`build/script/buildforandroid.sh release $ANDROID_ABI $ANDROID_NATIVE_API_LEVEL`

For the moment it is not possible to compile the debug version for Android, so the target version must be `release`.

Available Android ABIs, depending on your NDK version, are: 
* armeabi (up to NDK r16)
* arm64-v8a
* armeabi-v7a
* mips (up to NDK r16)
* mips64 (up to NDK r16)
* x86
* x86_64

Note that NDK versions r17 and onwards no longer support ABIs armeabi, mips and mips64. If needed, you may download an older NDK version from

https://developer.android.com/ndk/downloads/older_releases

Android native API levels are to be specified as integer numbers (e.g. 21 for Android Lollipop). A comprehensive list of native API levels can be found at

https://developer.android.com/ndk/guides/stable_apis

The binaries are placed in folder

`bin/$TARGET-$ANDROID_ABI-$ANDROID_NATIVE_API_LEVEL`

As for the non-Android build, native libraries are placed in folder

`bin/$TARGET-$ANDROID_ABI-$ANDROID_NATIVE_API_LEVEL/libs`

and Java interface files in folder

`bin/$TARGET-$ANDROID_ABI-$ANDROID_NATIVE_API_LEVEL/java`

In order to use GrapeNLP in an Android app, copy all the .so files inside the libs folder to your Android project folder

`app/src/main/jniLibs/$ANDROID_ABI`

and the Java files to folder

`app/src/main/java`

respecting the Java package folder structure (com/grapenlp/core).

## License

<a href="/LICENSE"><img height="48" align="left" src="http://www.gnu.org/graphics/empowered-by-gnu.svg"></a>

This program is licensed under the GNU Lesser General Public License version 2.1. Contact javier.sastre@telefonica.net for further inquiries.

Some files for the implementation of Unicode management have been borrowed from the Unitex project, which is licensed under the same license. These can be distinguished by their license headers.

