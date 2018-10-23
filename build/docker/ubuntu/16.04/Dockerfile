#
# GRAPENLP
#
# Copyright (C) 2004-2018 Javier Miguel Sastre Martínez <javier.sastre@telefonica.net>
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
 
FROM ubuntu:16.04

# Version label to force docker image rebuild
LABEL grapenlp-core.ubuntu.16.04.docker.version="1.0"

# Build user and source repo URL
ENV BUILDER_USER builder
ENV GRAPENLP_CORE_URL https://github.com/GrapeNLP/grapenlp-core.git

# This avoids some warning messages due to running in a headless environment
RUN echo 'debconf debconf/frontend select Noninteractive' | debconf-set-selections

# System update
RUN apt-get update
RUN apt-get upgrade -y
RUN apt-get dist-upgrade -y

# This is to avoid a debconf warning
RUN apt-get install -y --no-install-recommends apt-utils

# Set locale
RUN apt-get install -y locales
RUN locale-gen en_US.UTF-8
ENV LANG en_US.UTF-8
ENV LANGUAGE en_US:en
ENV LC_ALL en_US.UTF-8

# Install tools
RUN apt-get install -y software-properties-common
RUN apt-get install -y build-essential

# Install native libs needed by some module dependencies
RUN apt-get install -y libboost-dev libboost-program-options-dev

# Install CMake 3.9.6 from tar.gz
ADD https://cmake.org/files/v3.9/cmake-3.9.6.tar.gz /root
WORKDIR /root
RUN tar xfz cmake-3.9.6.tar.gz
RUN rm cmake-3.9.6.tar.gz
WORKDIR /root/cmake-3.9.6
RUN ./bootstrap && make && make install

# Install GTest
RUN apt-get install libgtest-dev
WORKDIR /usr/src/gtest
RUN cmake CMakeLists.txt && make && ln -s libgtest.a /usr/lib && ln -s libgtest_main.a /usr/lib

# Install SWIG
RUN apt-get install -y swig

# Install python 3.6 from Launchpad
RUN add-apt-repository -y ppa:deadsnakes/ppa
RUN apt-get update
RUN apt-get install -y python3.6
RUN apt-get install -y python3.6-dev
RUN apt-get install -y virtualenv

# Create virtualenv folder where "contint" user will install all the modules
# RUN mkdir /opt/pygrapenlp
# RUN chown contint:contint /opt/aura

# Install JDK 8 from tar.gz
RUN apt-get install -y openjdk-8-jdk-headless
#RUN mkdir -p /usr/lib/jvm
#ADD http://artifactory.hi.inet/artifactory/misc-aura-files/software/jdk-8u161-linux-x64.tar.gz /usr/lib/jvm
#WORKDIR /usr/lib/jvm
#RUN tar xfz jdk-8u161-linux-x64.tar.gz
#RUN rm jdk-8u161-linux-x64.tar.gz
#RUN ln -s jdk1.8.0_161 jdk1.8.0
WORKDIR /usr/lib/java-8-openjdk-amd64/include
#RUN ln -s linux/jawt_md.h
#RUN ln -s linux/jni_md.h
RUN echo 'JAVA_HOME=/usr/lib/jvm/java-8-openjdk-amd64/' >> /etc/environment
#RUN update-alternatives --install "/usr/bin/java" "java" "/usr/lib/jvm/jdk1.8.0/bin/java" 9999
#RUN update-alternatives --install "/usr/bin/javac" "javac" "/usr/lib/jvm/jdk1.8.0/bin/javac" 9999
#RUN update-alternatives --install "/usr/bin/javah" "javah" "/usr/lib/jvm/jdk1.8.0/bin/javah" 9999

# Install Git client
RUN apt-get install -y git

# Create "builder" user
RUN useradd -ms /bin/bash $BUILDER_USER

USER $BUILDER_USER
WORKDIR /home/$BUILDER_USER

# To build grapenlp-core inside this docker simply run a bash terminal inside the docker and enter the following commands:
# git clone $GRAPENLP_CORE_URL
# cd grapenlp-core
# build/scripts/build.sh debug
# build/scripts/build.sh release
