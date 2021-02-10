#!/bin/bash 
SCRIPTFOLDER="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"

. ${SCRIPTFOLDER}/util.sh

TARGET="$1"
TARGETS=("debug" "mtrace" "release")
USAGE="Usage:\n"
USAGE="${USAGE}`basename "$0"` TARGET\n"
USAGE="${USAGE}Available targets are:\n"
USAGE="${USAGE}`join "|" ${TARGETS[@]}`"

# Validate arguments
if_help_flag_show_usage_and_exit "${USAGE}" "$1"
validate_argument_count_or_exit "${USAGE}" $# 1
check_argument_in_range_or_exit "${USAGE}" "target" "${TARGET}" "${TARGETS[@]}"
CMAKE_TARGET="$(to_proper_noun "${TARGET}")"

# Get distro ID
DISTRO_ID="$(get_distro_id)"

# Create build root folder
BUILD_FOLDER="$(make_build_folder "${SCRIPTFOLDER}" "${TARGET}")"
cd "${BUILD_FOLDER}"

# Create build subfolders and compilation scripts
log_info_banner "Configuring"
cmake -Wno-dev -DCMAKE_BUILD_TYPE="${CMAKE_TARGET}" ../..
success_or_exit

# Compile
log_info_banner "Compiling"
make
success_or_exit

# Test
log_info_banner "Testing"
make test
success_or_exit

# On Ubuntu, make the Debian packages
if [ "$DISTRO_ID" == "debian" ] || ["$DISTRO_ID" == "ubuntu" ]; then
  log_info_banner "Packaging"
  make package
  success_or_exit
fi

# Report success
log_info_banner "Build completed"

# On Debian or Ubuntu, inform about the location of the resulting Debian packages
if [ "$DISTRO_ID" == "debian" ] || ["$DISTRO_ID" == "ubuntu" ]; then
  echo "You may now install the packages at ${BUILD_FOLDER}/package:"
  echo
  echo "sudo dpkg -i \"${BUILD_FOLDER}/package/*.deb\""
  echo
fi
