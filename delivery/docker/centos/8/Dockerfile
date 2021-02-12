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
 
FROM centos:8

# Version label to force docker image rebuild
LABEL grapenlp.centos.8.docker.version="1.0"

# System update
RUN yum -y update

# Install tools
RUN yum install -y gcc-c++ make wget

# Install native libs needed by some module dependencies
RUN yum install -y boost-devel boost-program-options

# Install JDK 8 from tar.gz
RUN yum install -y java-1.8.0-openjdk-devel
ENV JAVA_HOME=/usr/lib/jvm/java-1.8.0-openjdk

# Install python 3
RUN yum install -y python3 python3-pip python3-devel
RUN pip3 install --upgrade pip

# Install SWIG
RUN yum install -y swig

# Install CMake
RUN yum install -y openssl-devel
RUN wget https://github.com/Kitware/CMake/releases/download/v3.19.4/cmake-3.19.4.tar.gz
RUN tar -zxvf cmake-3.19.4.tar.gz
RUN rm cmake-3.19.4.tar.gz
WORKDIR /cmake-3.19.4
RUN ./bootstrap
RUN make
RUN make install
WORKDIR /
RUN rm -Rf /cmake-3.19.4 

# Install Doxygen along with its optional dependencies
RUN yum install -y dnf-plugins-core
RUN yum config-manager --set-enabled powertools
RUN yum install -y doxygen graphviz

# Install GIT
RUN yum install -y git

# Create build user
RUN useradd -ms /bin/bash build
WORKDIR /home/build

# This is what you will have to run inside the docker in order to clone and build grapenlp-core
# su build
# git clone https://github.com/GrapeNLP/grapenlp-core.git
# cd grapenlp-core
# delivery/scripts/build.sh release
