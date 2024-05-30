#!/bin/bash
set -exo pipefail

docker build --rm -t thock/conundrum --build-arg keymap=${keymap:-wheredoesyourmindgo:uf2} .
docker run --rm -v $PWD:/qmk_firmware -v $PWD/.build:/qmk_firmware/.build -it thock/conundrum
