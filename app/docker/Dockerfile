FROM debian:bookworm AS qt-builder

RUN apt-get update \
    && apt-get install -y --no-install-recommends \
    build-essential \
    cmake \
    git \
    wget \
    ninja-build \
    python3 \
    perl \
    ca-certificates \
    locales \
    pkg-config \
    \
    # Font and text rendering
    libfontconfig-dev \
    libfreetype-dev \
    libpng-dev \
    \
    # X11 and display system libraries for Qt XCB platform
    libx11-dev \
    libx11-xcb-dev \
    libxext-dev \
    libxfixes-dev \
    libxrender-dev \
    \
    # XCB libraries
    libxcb1-dev \
    libxcb-glx0-dev \
    libxcb-icccm4-dev \
    libxcb-image0-dev \
    libxcb-keysyms1-dev \
    libxcb-render-util0-dev \
    libxcb-shm0-dev \
    libxcb-xinerama0-dev \
    libxcb-xkb-dev \
    libxcb-util0-dev \
    libxcb-cursor-dev \
    libxcb-randr0-dev \
    libxcb-render0-dev \
    libxcb-shape0-dev \
    libxcb-sync-dev \
    libxcb-xfixes0-dev \
    \
    # Keyboard and input support
    libxkbcommon-dev \
    libxkbcommon-x11-dev \
    \
    # Graphics and OpenGL libraries
    libgl1-mesa-dev \
    libglu1-mesa-dev \
    libegl1-mesa-dev \
    libgles2-mesa-dev \
    \
    # System integration
    libdbus-1-dev \
    libcurl4-openssl-dev \
    \
    # SSL/TLS dev libraries
    libssl-dev \
    openssl \
    && update-ca-certificates \ 
    && rm -rf /var/lib/apt/lists/*

RUN sed -i '/en_US.UTF-8/s/^# //g' /etc/locale.gen && locale-gen
ENV LANG=en_US.UTF-8
ENV LANGUAGE=en_US:en
ENV LC_ALL=en_US.UTF-8

WORKDIR /opt

RUN wget https://download.qt.io/official_releases/qt/6.8/6.8.0/single/qt-everywhere-src-6.8.0.tar.xz \
    && tar -xf qt-everywhere-src-6.8.0.tar.xz

WORKDIR /opt/qt-everywhere-src-6.8.0

# Download and compile Qt into /opt/Qt6.8

RUN mkdir build && cd build \
    && ../configure -prefix /opt/Qt6.8 \
    -release \
    -opensource \
    -confirm-license \
    -xcb \
    -ssl \
    -openssl-runtime \
    -nomake examples \
    -nomake tests \
    -skip qtsvg \
    -skip qttools \
    -skip qtserialbus \
    -skip qtserialport \
    -skip qtlocation \
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

RUN apt-get update \
    && apt-get install -y --no-install-recommends \
    build-essential \
    cmake \
    git \
    ninja-build \
    ca-certificates \
    locales \
    \
    # Font and text rendering
    libfontconfig1-dev \
    libfreetype6-dev \
    libpng-dev \
    \
    # X11 and display system libraries
    libx11-dev \
    libx11-xcb-dev \
    libxext-dev \
    libxfixes-dev \
    libxrender-dev \
    \
    # XCB runtime libraries
    libxcb-glx0-dev \
    libxcb-icccm4-dev \
    libxcb-image0-dev \
    libxcb-keysyms1-dev \
    libxcb-render-util0-dev \
    libxcb-shm0-dev \
    libxcb-xinerama0-dev \
    libxcb-xkb-dev \
    libxcb-cursor0 \
    libxcb-shape0 \
    libxcb-util1 \
    libxcb-randr0 \
    \
    # Keyboard support
    libxkbcommon-dev \
    libxkbcommon-x11-dev \
    \
    # Graphics libraries
    libgl1-mesa-dev \
    libglu1-mesa-dev \
    libegl1-mesa-dev \
    libgles2-mesa-dev \
    \
    # System integration
    libdbus-1-dev \
    libcurl4-openssl-dev \
    \
    # SSL/TLS dev libraries
    libssl-dev \
    libcrypto++-dev \
    && update-ca-certificates \ 
    && rm -rf /var/lib/apt/lists/*

RUN sed -i '/en_US.UTF-8/s/^# //g' /etc/locale.gen && locale-gen
ENV LANG=en_US.UTF-8
ENV LANGUAGE=en_US:en
ENV LC_ALL=en_US.UTF-8

COPY --from=qt-builder /opt/Qt6.8 /opt/Qt6.8

WORKDIR /app
COPY . .

RUN cmake -G Ninja -S . -B build/docker/ \
    && ninja -C build/docker/

FROM debian:bookworm-slim

RUN apt-get update\
    && apt-get install -y --no-install-recommends \
    locales \
    \
    # X11 utilities for debugging
    x11-utils \
    \
    # Graphics libraries
    libgl1 \
    libegl1 \
    \
    # X11 runtime libraries
    libx11-6 \
    libx11-xcb1 \
    libxext6 \
    libxfixes3 \
    libxrender1 \
    \
    # XCB runtime libraries
    libxcb1 \
    libxcb-glx0 \
    libxcb-icccm4 \
    libxcb-image0 \
    libxcb-keysyms1 \
    libxcb-render0 \
    libxcb-render-util0 \
    libxcb-shape0 \
    libxcb-shm0 \
    libxcb-sync1 \
    libxcb-xfixes0 \
    libxcb-xinerama0 \
    libxcb-xkb1 \
    libxcb-cursor0 \
    libxcb-util1 \
    libxcb-randr0 \
    \
    # Keyboard and input support
    libxkbcommon0 \
    libxkbcommon-x11-0 \
    \
    # Font and text rendering
    libfontconfig1 \
    libfreetype6 \
    libpng16-16 \
    \
    # System integration
    libdbus-1-3 \
    libcurl4 \
    \
    # SSL/TLS support
    libssl3 \
    libcrypto3 \
    ca-certificates \
    openssl \
    && rm -rf /var/lib/apt/lists/*

RUN sed -i '/en_US.UTF-8/s/^# //g' /etc/locale.gen && locale-gen
ENV LANG=en_US.UTF-8
ENV LANGUAGE=en_US:en
ENV LC_ALL=en_US.UTF-8

COPY --from=qt-builder /opt/Qt6.8 /opt/Qt6.8
COPY --from=app-builder /app/build/docker/appWeathered /app/appWeathered

WORKDIR /app

ENV LD_LIBRARY_PATH=/opt/Qt6.8/lib
ENV QT_QPA_PLATFORM_PLUGIN_PATH=/opt/Qt6.8/plugins

CMD ["./appWeathered"]
