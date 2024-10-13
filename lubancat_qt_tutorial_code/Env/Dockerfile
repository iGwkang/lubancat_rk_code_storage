FROM ubuntu:20.04

COPY sources.list /etc/apt/sources.list

ENV DEBIAN_FRONTEND=noninteractive

RUN apt-get update && \
apt install -y \
  make \
  build-essential \
  libclang-dev \
  ninja-build \
  gcc \
  git \
  bison \
  python3 \
  gperf \
  pkg-config \
  libfontconfig1-dev \
  libfreetype6-dev \
  freeglut3-dev \
  cmake \
  unzip \
  gfortran \
  subversion \
  nano \
  wget \
  flex \
  texinfo \
  gawk \
  openssl \
  pigz \
  libncurses-dev \
  tar \
  figlet \
  lsb-release \
  rsync
  
