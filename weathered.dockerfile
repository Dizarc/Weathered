# Qt6 and build tools for ARM64
# TODO: memory issues, add less CPUs or switch to compiling on desktop
FROM debian:bookworm as qt-builder

RUN apt-get update && \
    apt-get install -y --no-install-recommends \
    build-essential \
    cmake \
    git \
    wget \
    ninja-build \
    python3 \
    perl \
    libfontconfig1-dev \
    libfreetype6-dev \
    libx11-dev \
    libx11-xcb-dev \
    libxcb-glx0-dev \
    libxcb-icccm4-dev \
    libxcb-image0-dev \
    libxcb-keysyms1-dev \
    libxcb-render-util0-dev \
    libxcb-shm0-dev \
    libxcb-xinerama0-dev \
    libxcb-xkb-dev \
    libxext-dev \
    libxfixes-dev \
    libxrender-dev \
    libgl-dev \
    libegl-dev \
    libdbus-1-dev \
    libcurl4-openssl-dev \
    ca-certificates \
    && update-ca-certificates \ 
    && rm -rf /var/lib/apt/lists/*


WORKDIR /opt

RUN wget https://download.qt.io/official_releases/qt/6.8/6.8.0/single/qt-everywhere-src-6.8.0.tar.xz \
    && tar -xf qt-everywhere-src-6.8.0.tar.xz

WORKDIR /opt/qt-everywhere-src-6.8.0

# Install Qt into /opt/Qt6.8
RUN mkdir build && cd build && \
    cmake .. \
        -DCMAKE_INSTALL_PREFIX=/opt/Qt6.8 \
        -DCMAKE_BUILD_TYPE=Release \
        -DBUILD_EXAMPLES=OFF \
        -DQT_BUILD_EXAMPLES=OFF \
        -DQT_BUILD_TESTS=OFF \
        -DQT_BUILD_QUICK3D=OFF \
        -DQT_BUILD_WEBENGINE=OFF \
        -DQT_FEATURE_DBUS=OFF && \
    cmake --build . --parallel ${nproc} && \
    cmake --install .

FROM debian:bookworm as app-builder

RUN apt-get update && \ 
    apt-get install -y --no-install-recommends \
    build-essential \
    git \
    cmake \
    ninja-build \
    ca-certificates \
    && update-ca-certificates \
    && rm -rf /var/lib/apt/lists/*

COPY --from=qt-builder /opt/Qt6.8 /opt/Qt6.8

WORKDIR /app
COPY . .
RUN /opt/Qt6.8/bin/qt-cmake -B build -S . && cmake --build build -j$(nproc)


FROM debian:bookworm-slim

RUN apt-get update && \
    apt-get install -y --no-install-recommends \
    libgl1 \
    libegl1 \
    libxcb-xinerama0 \
    libcurl4 \
    && rm -rf /var/lib/apt/lists/*


COPY --from=qt-builder /opt/Qt6.8 /opt/Qt6.8
COPY --from=app-builder /app/build/appWeathered /app/appWeathered

WORKDIR /app

ENV LD_LIBRARY_PATH=/opt/Qt6.8/lib
ENV QT_QPA_PLATFORM_PLUGIN_PATH=/opt/Qt6.8/plugins

CMD ["./appWeathered"]