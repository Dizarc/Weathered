FROM debian:bookworm-slim as builder

RUN apt-get update && \ 
    apt-get install -y --no-install-recommends \
    build-essential \
    git \
    cmake \
    wget

WORKDIR /opt
RUN git clone https://github.com/ggml-org/llama.cpp.git
WORKDIR /opt/llama.cpp

RUN cmake -B build -DLLAMA_SERVER=ON -DLLAMA_LINAL=OFF -DLLAMA_BLAS=OFF -DLLAMA_MPI=OFF
RUN cmake --build build --config Release -j --target server


FROM debian:bookworm-slim as model_downloader

RUN apt-get update && \
    apt-get install -y --no-install-recommends wget && \
    rm -rf /var/lib/apt/lists/*

WORKDIR /model

# Download button from hf
RUN wget https://huggingface.co/Qwen/Qwen3-1.7B-GGUF/resolve/main/Qwen3-1.7B-Q8_0.gguf?download=true -O model.gguf

FROM debian:bookworm-slim

WORKDIR /app

COPY --from=builder /opt/llama.cpp/build/bin/server .

COPY --from=model_downloader /model/model.gguf .

EXPOSE 8080

CMD ["./server", "-m", "./model.gguf", "--host", "0.0.0.0", "--port", :"8080", "--n-gpu-layers", "0"]
