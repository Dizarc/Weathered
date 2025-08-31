FROM debian:bookworm-slim as builder

RUN apt-get update && \ 
    apt-get install -y --no-install-recommends \
    build-essential \
    git \
    cmake \
    wget

WORKDIR /opt
RUN git clone https://github.com/ggml-org/llama.cpp.git && \
WORKDIR /opt/llama.cpp

RUN cmake -B build -DLLAMA_SERVER=ON -DLLAMA_BLAS=OFF -DLLAMA_MPI=OFF
RUN cmake --build build --config Release -j --target server


FROM debian:bookworm-slim

WORKDIR /app

COPY --from=builder /opt/llama.cpp/build/bin/server .

EXPOSE 8080

CMD ["./server", "-m", "./model.gguf", "--host", "0.0.0.0", "--port", "8080", "--n-gpu-layers", "0"]
