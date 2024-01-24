#ifndef CUSTOM_ERROR_H
#define CUSTOM_ERROR_H

// Função personalizada para imprimir mensagens de erro com informações de arquivo e linha.
void custom_error(const char *message, const char *file, int line) {
    fprintf(stderr, "Error: %s\nFile: %s\nLine: %d\n", message, file, line);
    
    exit(EXIT_FAILURE);
}

#endif // CUSTOM_ERROR_H