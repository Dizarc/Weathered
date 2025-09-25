# Qt6 and build tools for ARM64

FROM debian:bookworm AS qt-builder

RUN apt-get update && \
    apt-get install -y --no-install-recommends \
    build-essential \
    cmake \
    git \
    wget \
    ninja-build \
    python3 \
    perl \
    ca-certificates \
    # Qt Dependencies
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
    libgl1-mesa-dev \
    libglu1-mesa-dev \
    libegl1-mesa-dev \
    libgles2-mesa-dev \
    libxkbcommon-dev \
    libxkbcommon-x11-dev \
    libdbus-1-dev \
    libpng-dev \
    libcurl4-openssl-dev \
    && update-ca-certificates \ 
    && rm -rf /var/lib/apt/lists/*

WORKDIR /opt

RUN wget https://download.qt.io/official_releases/qt/6.8/6.8.0/single/qt-everywhere-src-6.8.0.tar.xz \
    && tar -xf qt-everywhere-src-6.8.0.tar.xz

WORKDIR /opt/qt-everywhere-src-6.8.0

# Download and compile Qt into /opt/Qt6.8

RUN mkdir build && cd build && \
    ../configure -prefix /opt/Qt6.8 \
    -release \
    -opensource \
    -confirm-license \
    -nomake examples \
    -nomake tests \
    -skip qtsvg \
    -skip qttools \
    -skip qtserialbus \
    -skip qtserialport -skip qtlocation \
    -skip qttimeline \
    -skip qtpositioning \
    -skip qtmultimedia \
    -skip qt3d \
    -skip qtquick3d \
    -skip qtquick3dphysics \
    -skip qtdatavis3d \
    -skip qtsensors \ 
    -skip qtnetworkauth \
    -skip qtconnectivity \ 
    -skip qtwebsockets \
    -skip qtwebchannel \
    -skip qtcharts \
    -skip qtwayland \
    -skip qtvirtualkeyboard \
    -skip qtwebengine \
    -skip qtscxml \
    -skip qtgrpc \
    -skip qthttpserver \
    -skip qtspeech \
    -skip qt5compat \
    -skip qtdoc \
    -skip qtlottie \
    -skip qtmqtt \
    -skip qtquickeffectmaker \
    -skip qttranslations \
    -skip qtquicktimeline \
    -skip qtcoap \
    -skip qtgraphs \
    -skip qtwebview \
    && cmake --build . --parallel 6 \
    && cmake --install .

FROM debian:bookworm AS app-builder

RUN apt-get update && \
    apt-get install -y --no-install-recommends \
    build-essential \
    cmake \
    git \
    ninja-build \
    ca-certificates \
    # Qt Dependencies
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
    libgl1-mesa-dev \
    libglu1-mesa-dev \
    libegl1-mesa-dev \
    libgles2-mesa-dev \
    libxkbcommon-dev \
    libxkbcommon-x11-dev \
    libdbus-1-dev \
    libpng-dev \
    libcurl4-openssl-dev \
    && update-ca-certificates \ 
    && rm -rf /var/lib/apt/lists/*

COPY --from=qt-builder /opt/Qt6.8 /opt/Qt6.8

WORKDIR /app
COPY . .
# ENV PATH=/opt/Qt6.8/bin

RUN cmake -B build -S . \
    && cmake --build build -j6

FROM debian:bookworm-slim

RUN apt-get update && \
    apt-get install -y --no-install-recommends \
    libgl1 \
    libegl1 \
    libxcb-xinerama0 \
    libxcd-icccm4 \
    ligxcd-image0 \
    libxcd-keysyms1 \
    libxcd-render-util0 \
    lixbcd-xinerama0 \
    libxkbcommon-x11-0 \
    libcurl4 \
    libfontconfig1 \
    libfreetype6 \
    libdbus-1-3 \
    libpng16-16 \
    && rm -rf /var/lib/apt/lists/*

COPY --from=qt-builder /opt/Qt6.8 /opt/Qt6.8
COPY --from=app-builder /app/build/appWeathered /app/appWeathered

WORKDIR /app

ENV LD_LIBRARY_PATH=/opt/Qt6.8/lib
ENV QT_QPA_PLATFORM_PLUGIN_PATH=/opt/Qt6.8/plugins

CMD ["./appWeathered"]
