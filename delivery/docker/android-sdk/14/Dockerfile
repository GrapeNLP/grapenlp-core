#
# GRAPENLP
#
# Copyright (C) 2004-2021 Javier Miguel Sastre Martínez <javier.sastre@gmail.com>
#
# This library is free software; you can redistribute it and/or
# modify it under the terms of the GNU Lesser General Public
# License as published by the Free Software Foundation; either
# version 2.1 of the License, or (at your option) any later version.
#
# This library is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
# Lesser General Public License for more details.
#
# You should have received a copy of the GNU Lesser General Public
# License along with this library; if not, write to the Free Software
# Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA.
#
#
#
#
# @author Javier Sastre
#
 
# Specific Android component versions to install
ARG ANDROID_SDK_VERSION="4333796"
ARG ANDROID_NDK_VERSION="r16b"
ARG ANDROID_BUILD_TOOLS_VERSION="28.0.3"
ARG ANDROID_PLATFORM_VERSION="14"
ARG ANDROID_CMAKE_VERSION="3.10.2.4988404"
ARG BOOST_VERSION="1.68.0"

########################################
# Target image with Ubuntu, JDK & SWIG #
########################################
FROM ubuntu:18.04 AS base

# Version label to force docker image rebuild
LABEL grapenlp.android-sdk.14.docker.version="2.0"

# This avoids some warning messages due to running in a headless environment
RUN echo 'debconf debconf/frontend select Noninteractive' | debconf-set-selections

# System update
RUN apt-get update
RUN apt-get upgrade -y
RUN apt-get dist-upgrade -y

# Set locale
RUN apt-get install -y locales
RUN locale-gen en_US.UTF-8
ENV LANG en_US.UTF-8
ENV LANGUAGE en_US:en
ENV LC_ALL en_US.UTF-8

# Install tools
RUN apt-get install -y software-properties-common
RUN apt-get install -y build-essential
RUN apt-get install -y wget
RUN apt-get install -y unzip

# Install JDK 8
RUN apt-get install -y openjdk-8-jdk
ENV JAVA_HOME=/usr/lib/jvm/java-8-openjdk-amd64

# Install SWIG
RUN apt-get install -y swig

#########################################
# Transient image gathering Android SDK #
#########################################
FROM base AS android_sdk_base
ARG ANDROID_SDK_VERSION
ARG ANDROID_BUILD_TOOLS_VERSION
ARG ANDROID_PLATFORM_VERSION
ARG ANDROID_CMAKE_VERSION

RUN mkdir /opt/android-sdk
WORKDIR /opt/android-sdk
RUN wget -q https://dl.google.com/android/repository/sdk-tools-linux-${ANDROID_SDK_VERSION}.zip && \
    unzip -qq sdk-tools-linux-${ANDROID_SDK_VERSION}.zip && \
    rm sdk-tools-linux-${ANDROID_SDK_VERSION}.zip
ENV PATH="${PATH}:/opt/android-sdk/tools/bin"
RUN mkdir ${HOME}/.android && \
    touch ${HOME}/.android/repositories.cfg
RUN sdkmanager --update
RUN yes | sdkmanager "build-tools;${ANDROID_BUILD_TOOLS_VERSION}" "platforms;android-${ANDROID_PLATFORM_VERSION}" "cmake;${ANDROID_CMAKE_VERSION}"

#########################################
# Transient image gathering Android NDK #
#########################################
FROM base AS android_ndk_base
ARG ANDROID_NDK_VERSION

RUN mkdir /opt/android-sdk
WORKDIR /opt/android-sdk
RUN wget -q https://dl.google.com/android/repository/android-ndk-${ANDROID_NDK_VERSION}-linux-x86_64.zip && \
    unzip -qq android-ndk-${ANDROID_NDK_VERSION}-linux-x86_64.zip && \
    rm android-ndk-${ANDROID_NDK_VERSION}-linux-x86_64.zip && \
    mv android-ndk-${ANDROID_NDK_VERSION} ndk-bundle

####################################
# Target image + Android SDK & NDK #
####################################
FROM base as android_sdk_ndk_base
COPY --from=android_sdk_base /opt/android-sdk /opt/android-sdk
COPY --from=android_ndk_base /opt/android-sdk/ndk-bundle /opt/android-sdk/ndk-bundle
ENV ANDROID_SDK_ROOT=/opt/android-sdk
ENV NDK_ROOT=/opt/android-sdk/ndk-bundle

#############################################
# Transient image compiling Boost libraries #
#############################################
FROM android_sdk_ndk_base as boost_for_android_compilation
ARG BOOST_VERSION

WORKDIR /opt
RUN wget -q https://github.com/GrapeNLP/Boost-for-Android/archive/master.zip && \
    unzip -qq master.zip && \
    rm master.zip && \
    mv Boost-for-Android-master Boost-for-Android
WORKDIR /opt/Boost-for-Android
RUN ./build-android.sh --boost=${BOOST_VERSION} ${NDK_ROOT}

#########################################
# Target image + Android Boost binaries #
#########################################
FROM android_sdk_ndk_base as android_base
COPY --from=boost_for_android_compilation /opt/Boost-for-Android/build/out /opt/Boost-for-Android/build/out
ENV BOOSTFORANDROID_ROOT=/opt/Boost-for-Android

# Install GIT
RUN apt-get install -y git

# Create build user
RUN useradd -ms /bin/bash build
WORKDIR /home/build

# This is what you will have to run inside the docker in order to clone and build grapenlp-core, replacing $ANDROID_ABI by the target ABI (e.g. armeabi-v7a)
# su build
# git clone https://github.com/GrapeNLP/grapenlp-core.git
# cd grapenlp-core
# delivery/scripts/buildforandroid.sh release $ANDROID_ABI $ANDROID_PLATFORM_VERSION
