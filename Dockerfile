FROM ubuntu:24.04

# タイムゾーン等のインタラクティブな入力を避ける設定
ENV DEBIAN_FRONTEND=noninteractive

# 必要なライブラリのインストール
RUN apt-get update && apt-get install -y \
    build-essential \
    cmake \
    git \
    libasound2-dev \
    libx11-dev \
    libxrandr-dev \
    libxi-dev \
    libgl1-mesa-dev \
    libglu1-mesa-dev \
    libxcursor-dev \
    libxinerama-dev \
    libwayland-dev \
    libxkbcommon-dev \
    pkg-config \
    && rm -rf /var/lib/apt/lists/*

# raylibのビルドとインストール
RUN git clone --depth 1 https://github.com/raysan5/raylib.git /raylib \
    && cd /raylib && mkdir build && cd build \
    && cmake .. -DBUILD_EXAMPLES=OFF \
    && make && make install

WORKDIR /app