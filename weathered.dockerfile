# Qt6 and build tools for ARM64
# TODO: memory issues, add less CPUs or switch to compiling on desktop
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
    libcurl4-openssl-dev \
    ca-certificates \
    && update-ca-certificates \ 
    && rm -rf /var/lib/apt/lists/*


WORKDIR /opt

RUN wget https://download.qt.io/official_releases/qt/6.8/6.8.0/single/qt-everywhere-src-6.8.0.tar.xz \
    && tar -xf qt-everywhere-src-6.8.0.tar.xz

WORKDIR /opt/qt-everywhere-src-6.8.0

# Install Qt into /opt/Qt6.8
# REMOVE qtquickeffectmaker qt3d

RUN mkdir build && cd build && \
    cmake .. \
        -DCMAKE_INSTALL_PREFIX=/opt/Qt6.8 \
        -DCMAKE_BUILD_TYPE=Release \
        -DBUILD_EXAMPLES=OFF \
        -DBUILD_TESTS=OFF \
        -DBUILD_qt3d=OFF \
        -DBUILD_qt5compat=OFF \
        -DBUILD_qtdoc=OFF \
        -DBUILD_qtgrpc=OFF \
        -DBUILD_qtlottie=OFF \
        -DBUILD_qtmqtt=OFF \
        -DBUILD_qtnetworkauth=OFF \
        -DBUILD_qtopcua=OFF \
        -DBUILD_qtquick3d=OFF \
        -DBUILD_qtquick3dphysics=OFF \
        -DBUILD_qtquickeffectmaker=OFF \
        -DBUILD_remoteobjects=OFF \
        -DBUILD_qtscxml=OFF \
        -DBUILD_qtsensors=OFF \
        -DBUILD_qtserialbus=OFF \
        -DBUILD_qtspeech=OFF \
        -DBUILD_qttranslations=OFF \
        -DBUILD_qtvirtualkeyboard=OFF \
        -DBUILD_qtwayland=OFF \
        -DBUILD_qtquicktimeline=OFF \
        -DBUILD_qtmultimedia=OFF \
        -DBUILD_qtcharts=OFF \
        -DBUILD_qtcoap=OFF \
        -DBUILD_qtgraphs=OFF \
        -DBUILD_qtactiveqt=OFF \
        -DBUILD_qtconnectivity=OFF \
        -DBUILD_qtdatavis3d=OFF \
        -DBUILD_qtgraphs=OFF \
        -DBUILD_qtserialport=OFF \
        -DBUILD_qtpositioning=OFF \
        -DBUILD_qtlocation=OFF \
        -DBUILD_qttools=OFF \
        -DBUILD_qthttpserver=OFF \
        -DBUILD_qtwebsockets=OFF \
        -DBUILD_qtwebview=OFF \
        -DBUILD_qtwebengine=OFF \
        -DBUILD_qtwebchannel=OFF \
        -DQT_FEATURE_DBUS=OFF && \
    cmake --build . --parallel 4 && \
    cmake --install .

FROM debian:bookworm AS app-builder

RUN apt-get update && \ 
    apt-get install -y --no-install-recommends \
    build-essential \
    git \
    cmake \
    ninja-build \
    libgl1-mesa-dev \
    libglu1-mesa-dev \
    libegl1-mesa-dev \
    libgles2-mesa-dev \
    libxkbcommon-dev \
    libxkbcommon-x11-dev \
    libfontconfig1-dev \
    libfreetype6-dev \
    libdbus-1-dev \
    libpng-dev \
    ca-certificates \
    && update-ca-certificates \
    && rm -rf /var/lib/apt/lists/*

COPY --from=qt-builder /opt/Qt6.8 /opt/Qt6.8

WORKDIR /app
COPY . .
RUN /opt/Qt6.8/bin/qt-cmake -B build -S . && cmake --build build -j4


FROM debian:bookworm-slim

RUN apt-get update && \
    apt-get install -y --no-install-recommends \
    libgl1 \
    libegl1 \
    libxcb-xinerama0 \
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