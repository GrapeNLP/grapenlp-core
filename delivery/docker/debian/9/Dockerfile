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
 
FROM debian:9-slim

# Version label to force docker image rebuild
LABEL grapenlp.debian.9.docker.version="1.0"

# This avoids some warning messages due to running in a headless environment
#RUN echo 'debconf debconf/frontend select Noninteractive' | debconf-set-selections

# System update
RUN apt-get update
RUN apt-get dist-upgrade -y

# Set locale
RUN apt-get install -y locales
RUN sed -i '/en_US.UTF-8/s/^# //g' /etc/locale.gen && locale-gen
ENV LANG en_US.UTF-8  
ENV LANGUAGE en_US:en  
ENV LC_ALL en_US.UTF-8

# Install tools
RUN apt-get install -y build-essential

# Install native libs needed by some module dependencies
RUN apt-get install -y libboost-program-options-dev

# Install JDK 8 from tar.gz
RUN mkdir -p /usr/share/man/man1 && apt-get install -y openjdk-8-jdk
ENV JAVA_HOME=/usr/lib/jvm/java-8-openjdk-amd64

# Install python 3
RUN apt-get install -y python3 python3-dev virtualenv

# Install SWIG
RUN apt-get install -y swig

# Install CMake
RUN apt-get install -y cmake

# Install GoogleTest source
RUN apt-get install -y googletest

# Install Doxygen along with its optional dependencies
RUN apt-get install -y doxygen graphviz

# Install GIT
RUN apt-get install -y git

# Create build user
RUN useradd -ms /bin/bash build
WORKDIR /home/build

# This is what you will have to run inside the docker in order to clone and build grapenlp-core
# su build
# git clone https://github.com/GrapeNLP/grapenlp-core.git
# cd grapenlp-core
# delivery/scripts/build.sh release
