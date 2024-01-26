#!/bin/bash

source_file="main.c"

executable="Game"

if ! command -v gcc &> /dev/null; then
    echo "Erro: GCC não encontrado. Por favor, instale o GCC."
    
    exit 1
fi

if ! pkg-config --cflags --libs sdl2 &> /dev/null; then
    echo "Erro: Biblioteca SDL2 não encontrada. Por favor, instale a biblioteca SDL2."

    exit 1
fi

if [ ! -f "liblua54.a" ]; then
    echo "Aviso: Não foi possível encontrar o arquivo 'liblua54.a'."
fi

if [ -f "$executable" ]; then
    rm "$executable"
fi

gcc -std=c17 -o "$executable" "$source_file" -lm -lSDL2 -lSDL2_image -lSDL2_ttf -lSDL2_mixer -I/path/to/SDL2_image/headers "liblua54.a"

if [ $? -eq 0 ]; then
    echo "Compilação bem-sucedida. Executando o programa..."
    "./$executable"
else
    echo "Erro durante a compilação."
fi