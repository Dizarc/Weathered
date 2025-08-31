# Qt6 and build tools for ARM64
FROM debian:bookworm as builder

RUN apt-get update && \
    apt-get install -y --no-install-recommends \
    build-essential \
    qt6-base-dev \
    qt6-declarative-dev \
    qt6-qml-dev \
    libqt6quick6 \
    qml6-module-qtquick \
    qml6-module-qtquick-controls \
    git \
    cmake

WORKDIR /app
COPY . .

RUN cmake -B build -S . && cmake --build build -j$(nproc)

FROM debian:bookworm-slim

RUN apt-get update && \
    apt-get install -y --no-install-recommends \
    libqt6core6 \
    libqt6gui6 \
    libqt6qml6 \
    libqt6quick6 \
    libqt6network6 \
    qml6-module-qtquick \
    qml6-module-qtquick-controls && \
    rm -rf /var/lib/apt/lists/*

WORKDIR /app

COPY --from=builder /app/build/appWeathered .
COPY --from=builder /app/Qml ./Qml

# TODO: Environmental variables for the API stuff.
CMD ["./appWeathered"]