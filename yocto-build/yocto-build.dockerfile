# https://docs.yoctoproject.org/ref-manual/system-requirements.html#supported-linux-distributions 
FROM ubuntu:22.04

# To avoid interactive prompts
ENV DEBIAN_FRONTEND=noninteractive

# Installs required packages for the yocto project build system (https://docs.yoctoproject.org/ref-manual/system-requirements.html#ubuntu-and-debian)
RUN apt-get update && \
    apt-get install -y --no-install-recommends \
    neovim \
    build-essential \
    chrpath \
    cpio \
    debianutils \
    diffstat \
    file \
    gawk \
    gcc \
    git \
    iputils-ping \
    libacl1 \
    liblz4-tool \
    locales \
    python3 \
    python3-git \
    python3-jinja2 \
    python3-pexpect \
    python3-pip \
    python3-subunit \
    socat \
    texinfo \
    unzip \
    wget \
    xz-utils \
    zstd  && \
    apt-get clean && \
    rm -rf /var/lib/apt/lists/*

# Need to ensure this locale is enabled
RUN echo "en_US.UTF-8 UTF-8" >> /etc/locale.gen && \
    locale-gen

RUN useradd -ms /bin/bash builder

USER builder

WORKDIR /home/builder

CMD ["/bin/bash"]

    