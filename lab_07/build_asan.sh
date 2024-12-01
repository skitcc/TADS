#!/bin/bash

# Получаем директорию скрипта
SCRIPT_DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"

cd "$SCRIPT_DIR" || exit

mkdir -p ./out

clang -fsanitize=address -fno-omit-frame-pointer -std=c99 -Wall -Werror -Wpedantic -Wextra -Wvla -Wfloat-conversion -Wfloat-equal -g -I./inc -c ./src/*.c -o ./out/

clang ./*.o -o app.exe -lm -fsanitize=address
