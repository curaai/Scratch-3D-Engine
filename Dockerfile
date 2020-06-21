FROM ubuntu:20.04

# set noninteractive installation
ENV DEBIAN_FRONTEND=noninteractive

RUN apt-get update
# download requirements for build task
RUN apt-get install -y build-essential cmake gdb pkg-config curl git vim clang-format
# install sdl2 library 
RUN apt-get install -y libsdl2-dev libsdl2-image-dev

RUN apt-get update

# download workspace 
RUN git clone https://github.com/curaai00/Doom-engine.git /workspace
WORKDIR /workspace
RUN git checkout 3d_engine
RUN git submodule init && git submodule update
