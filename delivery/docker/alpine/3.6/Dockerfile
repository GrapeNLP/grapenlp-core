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

FROM alpine:3.6

LABEL grape.alpine.3_6.docker.version="3.0"

RUN apk --update add --no-cache bash dpkg g++ boost-dev boost-program_options make cmake swig python3-dev

#Install Oracle JDK
ADD https://github.com/sgerrand/alpine-pkg-glibc/releases/download/2.27-r0/glibc-2.27-r0.apk /tmp
RUN apk add --allow-untrusted /tmp/glibc-2.27-r0.apk
RUN rm /tmp/glibc-2.27-r0.apk
RUN apk --update add --no-cache openjdk8
WORKDIR /usr/lib/jvm/java-1.8-openjdk
RUN rm -rf *src.zip \
           lib/missioncontrol \
           lib/visualvm \
           lib/*javafx* \
           jre/lib/plugin.jar \
           jre/lib/ext/jfxrt.jar \
           jre/bin/javaws \
           jre/lib/javaws.jar \
           jre/lib/desktop \
           jre/plugin \
           jre/lib/deploy* \
           jre/lib/*javafx* \
           jre/lib/*jfx* \
           jre/lib/amd64/libdecora_sse.so \
           jre/lib/amd64/libprism_*.so \
           jre/lib/amd64/libfxplugins.so \
           jre/lib/amd64/libglass.so \
           jre/lib/amd64/libgstreamer-lite.so \
           jre/lib/amd64/libjavafx*.so \
           jre/lib/amd64/libjfx*.so

WORKDIR /usr/lib/jvm/java-8-openjdk-amd64/include
ENV JAVA_HOME=/usr/lib/jvm/java-1.8-openjdk

# Install GIT
RUN apk --update add --no-cache git

# Create build user
RUN addgroup -S build && adduser -S build -G build -s /bin/bash
WORKDIR /home/build

# This is what you will have to run inside the docker in order to clone and build grapenlp-core
# su build
# git clone git://github.com/GrapeNLP/grapenlp-core.git
# cd grapenlp-core
# build/scripts/build.sh release

