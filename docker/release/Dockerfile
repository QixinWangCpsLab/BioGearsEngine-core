# Base image
FROM ubuntu:20.04
ENV TZ=Asia/Hong_Kong

# # COPY the resolv.conf from current folder to the container
# COPY resolv.conf /etc/resolv.conf

# Set timezone:
RUN ln -snf /usr/share/zoneinfo/$CONTAINER_TIMEZONE /etc/localtime && echo $CONTAINER_TIMEZONE > /etc/timezone

# add security repo (complimentary for the package libpython3.8-minimal_3.8.10-0ubuntu1~20.04.9_amd64.deb)
# RUN echo "deb http://security.ubuntu.com/ubuntu focal-security main" >> /etc/apt/sources.list

# install/reinstall ca-certificates
RUN apt-get update && apt-get install --reinstall -y --no-install-recommends ca-certificates

# # # ADD necessary folders
# RUN mkdir -p /var/cache/apt/archives/partial
# RUN mkdir -p /var/cache/apt/archives

# # Install dependencies

# RUN apt update

# RUN apt-get update & \
#     apt-get install -y software-properties-common

# RUN add-apt-repository ppa:ubuntu-toolchain-r/test

RUN apt update

RUN apt-get install -y --no-install-recommends \
    wget \
    build-essential \
    ninja-build \
    automake \
    libssl-dev 

# Install CMake
RUN mkdir -p /src && cd /src \
    && wget https://github.com/Kitware/CMake/releases/download/v3.20.0/cmake-3.20.0.tar.gz --no-check-certificate \
    && tar -xf cmake-3.20.*.tar.gz \
    && cd cmake-3.20.0 \
    && ./bootstrap --parallel=4 --prefix=/usr/local \
    && make -j16 \
    && make install

# install xerces-c
RUN wget http://mirror.olnevhost.net/pub/apache//xerces/c/3/sources/xerces-c-3.2.5.tar.gz \
    && tar -xf xerces-c-3.2.5.tar.gz \
    && cd xerces-c-3.2.5 \
    && mkdir build \
    && cd build \
    && cmake -DCMAKE_INSTALL_PREFIX=/usr/local -DCMAKE_BUILD_TYPE=Release -DBUILD_SHARED_LIBS=ON -DBUILD_TESTING=OFF -DBUILD_SAMPLES=OFF .. \
    && make -j16 \
    && make install

# Install XSD
RUN wget https://www.codesynthesis.com/download/xsd/4.0/linux-gnu/x86_64/xsd_4.0.0-1_amd64.deb --no-check-certificate \
    && dpkg -i xsd_4.0.0-1_amd64.deb

# Install Pthread
RUN apt-get install -y --no-install-recommends \
    libpthread-stubs0-dev

# install Eigen3
RUN wget https://gitlab.com/libeigen/eigen/-/archive/3.4.0/eigen-3.4.0.tar.gz \
    && tar -xf eigen-3.4.0.tar.gz \
    && cd eigen-3.4.0 \
    && mkdir build \
    && cd build \
    && cmake -DCMAKE_INSTALL_PREFIX=/usr/local -DCMAKE_BUILD_TYPE=Release .. \
    && make -j16 \
    && make install

RUN mkdir -p /opt/biogears

# git clone from the repo of the biogears
# First clone the ~/.ssh/id_ed25519.pub to the container corresponding location
RUN mkdir -p /root/.ssh
COPY id_ed25519.pub /root/.ssh/id_ed25519.pub
# clone the repo
RUN cd /opt/biogears && git clone https://github.com/QixinWangCpsLab/BioGearsEngine-core.git core

# Build BioGears
RUN mkdir -p /opt/biogears/core/build && cd /opt/biogears/core/build \
    && cmake -DCMAKE_BUILD_TYPE=Release \
        -DCMAKE_INSTALL_PREFIX=/opt/biogears/core/build/usr \
        -DCMAKE_CXX_STANDARD=20 \
        -DBiogears_BUILD_JAVATOOLS=OFF \
        -DBiogears_SWIG_PYTHON_BINDINGS=OFF \
        -DBiogears_BUILD_SWIG_BINDINGS=OFF \
        -DBiogears_SWIG_CSHARP_BINDINGS=OFF ..

RUN mkdir -p /opt/biogears/core/build/projects/biogears/generated/Debug/biogears/schema/cdm \
    && mkdir -p /opt/biogears/core/build/projects/biogears/generated/Debug/biogears/schema/biogears \
    && mkdir -p /opt/biogears/core/build/projects/biogears/generated/Release/biogears/schema/cdm \
    && mkdir -p /opt/biogears/core/build/projects/biogears/generated/Release/biogears/schema/biogears

RUN apt-get install libxerces-c3.2
RUN apt-get update && apt-get install -y gdb && apt-get install -y libboost-all-dev
RUN cp -r /usr/local/include/eigen3/Eigen /usr/include/Eigen

RUN cd /opt/biogears/core/build && \
    make -j 16 \
    && make install

RUN cp -r /opt/biogears/core/build/usr/* /usr/