// Arquivo: include/fast_serializer/Serializer.h

#ifndef SERIALIZER_H
#define SERIALIZER_H // arquivo: include/fast_serializer/Serializer.h
// responsavel por escrer strcuts e outros dados em um arquivo

#include <string>
#include <fstream>
#include "fast_serializer/format.h"

class Serializer {
private:
    std::ofstream file_stream; // O fluxo de arquivo para escrita

public:
    // Construtor: abre o arquivo em modo binário
    Serializer(const std::string& filename);

    // Destrutor: fecha o arquivo
    ~Serializer();

    // Métodos para escrever tipos de dados primitivos
    void write_int32(int32_t value);
    void write_uint64(uint64_t value);
    void write_double(double value);
    void write_string(const std::string& value);

    // Método para escrever um bloco de dados genérico (como nossos structs)
    template<typename T>
    void write_struct(const T& data) {
        file_stream.write(reinterpret_cast<const char*>(&data), sizeof(T));
    }
};

#endif // SERIALIZER_H
