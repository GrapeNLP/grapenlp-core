#!/bin/bash
SCRIPTFOLDER="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"

. ${SCRIPTFOLDER}/util.sh

TARGET="$1"
TARGETS=("debug" "release")
ANDROID_ABIS="arm64-v8a armeabi-v7a mips mips64 x86 x86_64"
ANDROID_NATIVE_API_LEVEL="$2"
USAGE="Usage:\n"
USAGE="${USAGE}`basename "$0"` TARGET ANDROID_ABI ANDROID_NATIVE_API_LEVEL\n"
USAGE="${USAGE}Available targets are:\n"
USAGE="${USAGE}`join "|" ${TARGETS[@]}`\n"
USAGE="${USAGE}Available Android ABIs are:\n"
USAGE="${USAGE}`join "|" ${ANDROID_ABIS[@]}`\n"
USAGE="${USAGE}Android native API levels are integer numbers, e.g. 21 for Android 5.0 Lollipop.\n"
USAGE="${USAGE}A comprehensive list of native API levels can be found at https://developer.android.com/ndk/guides/stable_apis."

# Validate arguments
for ANDROID_ABI in ${ANDROID_ABIS}; do
    if_help_flag_show_usage_and_exit "${USAGE}" "$1"
    validate_argument_count_or_exit "${USAGE}" $# 2
    check_argument_in_range_or_exit "${USAGE}" "target" "${TARGET}" "${TARGETS[@]}"
    CMAKE_TARGET=$(to_proper_noun "${TARGET}")
    check_argument_is_a_natural_number_or_exit "${USAGE}" "Android native API level" "${ANDROID_NATIVE_API_LEVEL}"

    # Check needed Android software is installed
    ANDROID_SDK_FOLDER="$(find_android_sdk)"
    check_variable_is_not_empty_or_exit "Unable to find Android SDK; please install it and set environment variable ANDROID_SDK_ROOT" "${ANDROID_SDK_FOLDER}"
    ANDROID_SDK_CMAKE="$(find_android_sdk_cmake "${ANDROID_SDK_FOLDER}")"
    check_variable_is_not_empty_or_exit "Unable to find Android SDK tool CMake; please install it" "${ANDROID_SDK_CMAKE}"
    ANDROID_NDK_FOLDER="$(find_android_ndk)"
    check_variable_is_not_empty_or_exit "Unable to find Android SDK tool NDK; please install it" "${ANDROID_NDK_FOLDER}"
    ANDROID_TOOLCHAIN_FILE="${ANDROID_NDK_FOLDER}/build/cmake/android.toolchain.cmake"
    if [[ -f "$ANDROID_NDK_FOLDER" ]]; then
      echo "File ${ANDROID_NDK_FOLDER}/build/cmake/android.toolchain.cmake doesn't exist; maybe your Android NDK installation is corrupted, reinstall it and retry"
      exit 1
    fi
    BOOSTFORANDROID_NOT_FOUND_ERROR=\
    "Unable to find Boost-for-Android; you may clone it with the following command:\n\
    git clone git@github.com:GrapeNLP/Boost-for-Android.git\n\
    Either place Boost-for-Android next to grapenlp-core or \
    set the BOOSTFORANDROID_ROOT environment variable to the project location"
    BOOSTFORANDROID="$(find_boostforandroid "$SCRIPTFOLDER")"
    check_variable_is_not_empty_or_exit "${BOOSTFORANDROID_NOT_FOUND_ERROR}" "${BOOSTFORANDROID}"
    BOOSTFORANDROID_BUILD_NOT_FOUND_ERROR=\
    "Boost-For-Android build not found; maybe you didn't build Boost-For-Android, enter the Boost-For-Android folder and execute the following command to build the latest Boost libraries:\n\
    build-android.sh \"\$NDK_ROOT\"\n\
    For building a particular Boost version x.y.z, you may run the following command instead:\n\
    build-android.sh --boost=x.y.z \"\$NDK_ROOT\""
    BOOSTFORANDROID_INCLUDES="$(find_boostforandroid_includes "${BOOSTFORANDROID}" "${ANDROID_ABI}")"
    check_variable_is_not_empty_or_exit "${BOOSTFORANDROID_BUILD_NOT_FOUND_ERROR}" "${BOOSTFORANDROID_INCLUDES}"
    BOOSTFORANDROID_LIBPROGRAMOPTIONS="$(find_boostforandroid_libprogramoptions "${BOOSTFORANDROID}" "${ANDROID_ABI}")"
    check_variable_is_not_empty_or_exit "${BOOSTFORANDROID_BUILD_NOT_FOUND_ERROR}" "${BOOSTFORANDROID_LIBPROGRAMOPTIONS}"

    # Create build root folder
    BUILD_FOLDER="$(make_build_folder "${SCRIPTFOLDER}" "${TARGET}-${ANDROID_ABI}-${ANDROID_NATIVE_API_LEVEL}")"
    cd "${BUILD_FOLDER}"

    # Create build subfolders and compilation scripts
    log_info_banner "Configuring"
    ${ANDROID_SDK_CMAKE} \
     -DANDROID_ABI=${ANDROID_ABI} \
     -DANDROID_STL="c++_static" \
     -DANDROID_CPP_FEATURES="rtti exceptions" \
     -DCMAKE_BUILD_TYPE=${CMAKE_TARGET} \
     -DCMAKE_TOOLCHAIN_FILE="${ANDROID_TOOLCHAIN_FILE}" \
     -DANDROID_NATIVE_API_LEVEL=${ANDROID_NATIVE_API_LEVEL} \
     -DANDROID_TOOLCHAIN=clang \
     -DBoost_INCLUDE_DIR="${BOOSTFORANDROID_INCLUDES}" \
     -DBoost_PROGRAM_OPTIONS_LIBRARY="${BOOSTFORANDROID_LIBPROGRAMOPTIONS}" \
     ../..

    # Compile
    log_info_banner "Compiling"
    make
    success_or_exit

    # Report success
    log_info_banner "Build completed"
    echo "You may now install the packages at ${BUILD_FOLDER}/packages:"
    echo "sudo dpkg -i ${BUILD_FOLDER}/packages/*.deb"
done