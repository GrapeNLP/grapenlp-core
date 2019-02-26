#!/bin/bash 
SCRIPTFOLDER="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"

. ${SCRIPTFOLDER}/util.sh

TARGET="release"
DISTRIBUTION=`lsb_release -cs`

USAGE="Usage:\n"
USAGE="${USAGE}`basename "$0"`"

# Validate arguments
if_help_flag_show_usage_and_exit "${USAGE}" "$1"
validate_argument_count_or_exit "${USAGE}" $# 0

# Create build root folder
BUILD_FOLDER="$(make_build_folder "${SCRIPTFOLDER}" "${TARGET}")"
cd "${BUILD_FOLDER}"

# Create build subfolders and compilation scripts
log_info_banner "Configuring"
cmake -DCMAKE_BUILD_TYPE="$TARGET" -DCPACK_DEBIAN_PACKAGE_DISTRIBUTION=$DISTRIBUTION ../..
success_or_exit

# Package
log_info_banner "Packaging"
make package_ubuntu
success_or_exit

# Report success
log_info_banner "Packaging completed"

# On Linux, inform about the location of the resulting Debian packages
if [[ "$OSTYPE" == "linux-gnu" ]]; then
  echo "To upload the source package to Launchpad, enter folder"
  echo "${BUILD_FOLDER}"
  echo "and run"
  echo "make dput"
  echo
fi
