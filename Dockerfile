FROM debian:9

RUN apt-get update && apt-get install --no-install-recommends -y \
    avr-libc \
    avrdude \
    binutils-arm-none-eabi \
    binutils-avr \
    build-essential \
    dfu-programmer \
    dfu-util \
    gcc \
    gcc-arm-none-eabi \
    gcc-avr \
    git \
    libnewlib-arm-none-eabi \
    software-properties-common \
    unzip \
    wget \
    zip \
    python \
    && rm -rf /var/lib/apt/lists/*

ENV KEYBOARD=thock/conundrum
ENV KEYMAP=wheredoesyourmindgo:uf2
ENV OPTIONS='-e EXECUTE_ON_FUNC=yes -e QWERTY_BASE=no'

VOLUME /qmk_firmware
WORKDIR /qmk_firmware
COPY . .

CMD make $KEYBOARD:$KEYMAP $OPTIONS
