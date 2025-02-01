# Estágio de build
FROM ubuntu:22.04 AS build-stage

# Instala dependências do sistema
RUN apt-get update && apt-get install -y \
  build-essential \
  cmake \
  git \
  curl \
  zip \
  libcurl4-openssl-dev \
  libssl-dev \
  libpq-dev \
  libsodium-dev \
  pkg-config \
  && rm -rf /var/lib/apt/lists/*

# Instala o vcpkg
WORKDIR /opt
RUN git clone https://github.com/Microsoft/vcpkg.git && \
  cd vcpkg && \
  ./bootstrap-vcpkg.sh && \
  ./vcpkg install crow spdlog nlohmann-json

# Copia o código-fonte para o contêiner
WORKDIR /app
COPY . .

# Configura e compila o projeto
RUN cmake -B build -S . -DCMAKE_TOOLCHAIN_FILE=/opt/vcpkg/scripts/buildsystems/vcpkg.cmake && \
  cmake --build build --config Release

# Estágio de runtime
FROM ubuntu:22.04 AS runtime-stage

# Instala dependências de runtime
RUN apt-get update && apt-get install -y \
  libcurl4 \
  libssl3 \
  libpq5 \
  libsodium23 \
  && rm -rf /var/lib/apt/lists/*

# Copia o executável do estágio de build
COPY --from=build-stage /app/build/Dailyhub_Server /usr/local/bin/Dailyhub_Server

# Define o diretório de trabalho e o comando padrão
WORKDIR /app
EXPOSE 7845
CMD ["Dailyhub_Server"]