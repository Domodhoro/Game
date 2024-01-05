#!/bin/bash

# Nome do arquivo de origem.
source_file="main.cpp"

# Nome do executável a ser gerado.
executable="Game"

# Verifica se o compilador g++ está disponível.
if ! command -v g++ &> /dev/null; then
    echo "Erro: GCC não encontrado. Por favor, instale o GCC."
    exit 1
fi

# Verifica se as bibliotecas SDL2 estão disponíveis usando pkg-config.
if ! pkg-config --cflags --libs sdl2 &> /dev/null; then
    echo "Erro: Biblioteca SDL2 não encontrada. Por favor, instale a biblioteca SDL2."
    exit 1
fi

# Verifica se o arquivo da biblioteca Lua (liblua54.a) está presente.
if [ ! -f "liblua54.a" ]; then
    echo "Aviso: Não foi possível encontrar o arquivo 'liblua54.a'."
fi

# Remove o executável antigo, se existir.
if [ -f "$executable" ]; then
    rm "$executable"
fi

# Compilação do código-fonte usando g++ e vinculando as bibliotecas necessárias.
g++ -std=c++17 -o "$executable" "$source_file" -lm -lSDL2 -lSDL2_image -lSDL2_ttf -lSDL2_mixer -I/path/to/SDL2_image/headers "liblua54.a"

# Verifica se a compilação foi bem-sucedida.
if [ $? -eq 0 ]; then
    echo "Compilação bem-sucedida. Executando o programa..."
    "./$executable"
else
    echo "Erro durante a compilação."
fi
