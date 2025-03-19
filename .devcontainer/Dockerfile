FROM mcr.microsoft.com/devcontainers/base:ubuntu-24.04

ENV DEBIAN_FRONTEND=noninteractive

# Update packages and install essentials
RUN apt-get update && \
    apt-get install -y \
    build-essential \
    curl \
    wget \
    git \
    vim \
    emacs \
    python3 \
    python3-pip \
    sudo \
    bc \
    gcc-riscv64-linux-gnu qemu-system-riscv64 \
    && apt-get clean && rm -rf /var/lib/apt/lists/*

USER vscode
WORKDIR /home/vscode