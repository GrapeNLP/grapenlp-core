#
# GRAPENLP
#
# Copyright (C) 2004-2019 Javier Miguel Sastre Martínez <javier.sastre@telefonica.net>
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
LABEL grapenlp.ubuntu.16_04.docker.version="2.0"

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

# Install native libs needed by some module dependencies
RUN apt-get install -y libboost-dev libboost-program-options-dev

# Install JDK 8 from tar.gz
RUN apt-get install -y openjdk-8-jdk
WORKDIR /usr/lib/jvm/java-8-openjdk-amd64/include
ENV JAVA_HOME=/usr/lib/jvm/java-8-openjdk-amd64

# Install python 3.6 from Launchpad
RUN add-apt-repository -y ppa:deadsnakes/ppa
RUN apt-get update
RUN apt-get install -y python3.6
RUN apt-get install -y python3.6-dev
RUN apt-get install -y virtualenv

# Install SWIG
RUN apt-get install -y swig

# Install CMake 3.9.6 from tar.gz
ADD https://cmake.org/files/v3.9/cmake-3.9.6.tar.gz /root
WORKDIR /root
RUN tar xfz cmake-3.9.6.tar.gz
RUN rm cmake-3.9.6.tar.gz
WORKDIR /root/cmake-3.9.6
RUN ./bootstrap && make && make install

# Install GIT
RUN apt-get install -y git

# Create build user
RUN useradd -ms /bin/bash build
WORKDIR /home/build

# This is what you will have to run inside the docker in order to clone and build grapenlp-core
# su build
# git clone git://github.com/GrapeNLP/grapenlp-core.git
# cd grapenlp-core
# build/scripts/build.sh release

