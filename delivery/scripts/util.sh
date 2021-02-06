#!/bin/bash 

HELP_TARGETS=("help" "h" "-help" "--help" "-h" "?")

function get_distro_id
{
  os_release_pathname=""
  if [[ -f "/etc/os-release" ]]; then
    os_release_pathname="/etc/os-release"
  elif [[ -f "/usr/lib/os-release" ]]; then
    os_release_pathname="/usr/lib/os-release"
  fi

  if [[ -n "$os_release_pathname" ]]; then
    distro_id=`cat "${os_release_pathname}" | grep "^ID=" | sed -E "s/^ID=\"? *//" | sed -E "s/ *\"?$//"`
  else
    distro_id='not_linux'
  fi
  echo "${distro_id}"
}

function if_help_flag_show_usage_and_exit
{
  local usage="$1"
  local first_arg="$2"
  if [[ `index_of "$2" "${HELP_TARGETS[@]}"` -ge 0 ]]; then
    help_and_exit "$1" 0
  fi
}

function validate_argument_count_or_exit
{
  local usage="$1"
  local actual=$2
  if [[ $# -gt 3 ]]; then
    local min_expected=$3
    local max_expected=$4
    if [[ ${actual} -lt ${min_expected} ]]; then
      help_and_exit "${usage}" 1 "Wrong number of arguments: got ${actual} but expected at least ${min_expected}"
    fi
    if [[ ${actual} -gt ${max_expected} ]]; then
      help_and_exit "${usage}" 1 "Wrong number of arguments: got ${actual} but expected at most ${max_expected}"
    fi
  else
    local expected=$3
    if [[ ${actual} -ne ${expected} ]]; then
      help_and_exit "${usage}" 1 "Wrong number of arguments: got ${actual} but expected ${expected}"
    fi
  fi
}

function to_proper_noun
{
  local string="$1"
  local first_char=$(echo ${string:0:1} | tr [:lower:] [:upper:])
  local other_chars=$(echo ${string:1} | tr [:upper:] [:lower:])
  echo "${first_char}${other_chars}"
}

function print_star_line
{
  local star_count=$1
  for i in `seq 1 ${star_count}`; do
    echo -n "*"
  done
  echo
}

function log_info
{
  local message="$1"
  echo -e "\e[1m\e[92m${message}\e[0m"
}

function log_error
{
  local message="$1"
  echo -e "\e[1m\e[91m${message}\e[0m"
}

function print_banner
{
  local message="$1"
  local star_count=${#message}
  star_count=`expr ${star_count} + 4`
  print_star_line ${star_count}
  echo "* ${message} *"
  print_star_line ${star_count}
}

function log_info_banner
{
  local message="$1"
  local banner="$(print_banner "${message}")"
  log_info "\n${banner}\n"
}

function help_and_exit
{
  local usage="$1"
  local exit_code=$2
  if [[ $# -gt 2 ]]; then
    error_message="$3"
    log_error "${error_message}"
  fi
  echo -e "${usage}"
  exit ${exit_code}
}

function check_argument_is_a_natural_number_or_exit
{
  local usage="$1"
  local arg_name="$2"
  local arg_value="$3"
  if ! [[ "$arg_value" =~ ^[0-9]+$ ]]; then
    help_and_exit "${usage}" 1 "Invalid ${arg_name}: ${arg_value} is not a natural number"
  fi
}

function check_argument_in_range_or_exit
{
  local usage="$1"
  shift
  local arg_name="$1"
  shift
  local arg_value="$1"
  shift
  local arg_range=("$@")
  local index=`index_of "${arg_value}" "${arg_range[@]}"`
  if [[ ${index} -lt 0 ]]; then
    help_and_exit "${usage}" 1 "Invalid ${arg_name}: ${arg_value}"
  fi
}

function check_variable_is_not_empty_or_exit
{
  local error_message="$1"
  local variable=$2
  if [[ -z "${variable}" ]]; then
    log_error "${error_message}"
    exit 1
  fi
}

function success_or_exit
{
  local status=$?
  if [[ ${status} -ne 0 ]]; then
    exit ${status}
  fi
}

function join {
  local IFS="$1"
  shift
  echo "$*"
}

function index_of {
  local item="$1"
  shift
  local index=0
  while [[ $# -gt 0 && "$item" != "$1" ]]; do
    let "index++"
    shift
  done
  if [[ $# -eq 0 ]]; then
    echo -1
  else
    echo ${index}
  fi
}

function make_build_folder
{
    local scriptfolder="$1"
    local target="$2"
    cd "${scriptfolder}/../.."
    if [[ ! -d bin ]]; then
      mkdir build
    fi
    cd build
    if [[ ! -d ${target} ]]; then
      mkdir ${target}
    fi
    cd "$target"
    pwd
}

# Return the greatest of 2 version numbers $1 and $2, where a version number is a sequence of fields separated by dots
# and fields contain natural numbers only (e.g. 3.10.2.4988404)
function max_version
{
  local version_a="$1"
  local version_b="$2"
  local i=1
  local field_a="$(echo ${version_a} | cut -d"." -f${i})"
  local field_b="$(echo ${version_b} | cut -d"." -f${i})"
  while [[ -n "${field_a}" ]] && [[ -n "${field_b}" ]] && [[ "${field_a}" -eq "${field_b}" ]]; do
    ((i++))
    field_a="$(echo ${version_a} | cut -d"." -f${i})"
    field_b="$(echo ${version_b} | cut -d"." -f${i})"
  done
  # If version B is a prefix of version A or they are equal
  if [[ -z "${field_b}" ]]; then
    echo "${version_a}"
  # If version A is a prefix of version B
  elif [[ -z "${field_a}" ]]; then
    echo "${version_b}"
  # If version A is not a prefix of version B and vice-versa but A is greater
  elif [[ "${field_a}" -gt "${field_b}" ]]; then
    echo "${version_a}"
  # If version A is not a prefix of version B and vice-versa but B is greater
  else
    echo "${version_b}"
  fi
}

# Find Android SDK installation folder
function find_android_sdk
{
  if [[ -n "$ANDROID_SDK_ROOT" ]]; then
    echo "$ANDROID_SDK_ROOT"
  elif [[ -n "$ANDROID_HOME" ]]; then
      echo "$ANDROID_HOME"
  fi
}

# Find path to Android SDK cmake command
function find_android_sdk_cmake
{
  local android_sdk_root="$1"
  local android_sdk_cmake_root="$1/cmake"
  local android_sdk_cmake_version=""
  if [[ -d "${android_sdk_cmake_root}" ]]; then
    for candidate_version in `ls "${android_sdk_cmake_root}"`; do
      android_sdk_cmake_version=$(max_version "${android_sdk_cmake_version}" "${candidate_version}")
    done
  fi
  if [[ -n "${android_sdk_cmake_version}" ]]; then
    android_sdk_cmake="${android_sdk_cmake_root}/${android_sdk_cmake_version}/bin/cmake"
    if [[ -f ${android_sdk_cmake} ]]; then
      echo ${android_sdk_cmake}
    fi
  fi
}

# Find path to Android NDK
function find_android_ndk
{
  local android_sdk="$1"
  local android_ndk="${NDK_ROOT}"
  if [[ -z "${android_ndk}" ]]; then
    android_ndk="${android_sdk}/ndk-bundle"
  fi
  if [[ -d "${android_ndk}" ]]; then
    echo ${android_ndk}
  fi
}

# Find path to Boost-for-Android
function find_boostforandroid
{
  local scriptfolder="$1"
  local boostforandroid="${BOOSTFORANDROID_ROOT}"
  if [[ -z "${boostforandroid}" ]] || [[ ! -d "${boostforandroid}" ]]; then
    boostforandroid="$1/../../../Boost-for-Android"
  fi
  if [[ -n "${boostforandroid}" ]] && [[ -d "${boostforandroid}" ]]; then
    echo "${boostforandroid}"
  fi
}

function find_boostforandroid_includes
{
  local boostforandroid="$1"
  local android_abi="$2"
  boostforandroid_includes="${boostforandroid}/build/out/${android_abi}/include"
  if [[ -d "${boostforandroid_includes}" ]]; then
    boostforandroid_includes="$(find "${boostforandroid_includes}" -maxdepth 1 -type d -name "boost-*" | head -n 1)"
    if [[ -n "${boostforandroid_includes}" ]] && [[ -d "${boostforandroid_includes}" ]]; then
      echo "${boostforandroid_includes}"
    fi
  fi
}

function get_boostforandroid_version
{
  local includes="$1"
  local version_file="${includes}/boost/version.hpp"
  if [[ -e "${version_file}" ]]; then
    echo "$(grep -E "#define\s+BOOST_VERSION\s" "${version_file}" | grep -oE "[0-9]+")"
  fi
}

function find_boostforandroid_libprogramoptions
{
  local boostforandroid="$1"
  local android_abi="$2"
  boostforandroid_libprogramoptions="${boostforandroid}/build/out/${android_abi}/lib"
  if [[ -d "${boostforandroid_libprogramoptions}" ]]; then
    boostforandroid_libprogramoptions="$(find "${boostforandroid_libprogramoptions}" -maxdepth 1 -type f -name "libboost_program_options-*\.a" | head -n 1)"
    if [[ -n "${boostforandroid_libprogramoptions}" ]] && [[ -f "${boostforandroid_libprogramoptions}" ]]; then
      echo "${boostforandroid_libprogramoptions}"
    fi
  fi
}
