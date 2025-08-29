// Arquivo: src/Deserializer.cpp

#include "fast_serializer/Deserializer.h"
#include <stdexcept>
#include <vector>

Deserializer::Deserializer(const std::string& filename) {
    // Abre o arquivo para LEITURA (in) e em modo binário (binary)
    file_stream.open(filename, std::ios::in | std::ios::binary);
    if (!file_stream.is_open()) {
        throw std::runtime_error("Não foi possível abrir o arquivo para leitura: " + filename);
    }
}

Deserializer::~Deserializer() {
    if (file_stream.is_open()) {
        file_stream.close();
    }
}

int32_t Deserializer::read_int32() {
    int32_t value;
    // Lê sizeof(value) bytes do arquivo e os coloca no endereço de memória de 'value'
    file_stream.read(reinterpret_cast<char*>(&value), sizeof(value));
    return value;
}

uint64_t Deserializer::read_uint64() {
    uint64_t value;
    file_stream.read(reinterpret_cast<char*>(&value), sizeof(value));
    return value;
}

double Deserializer::read_double() {
    double value;
    file_stream.read(reinterpret_cast<char*>(&value), sizeof(value));
    return value;
}

std::string Deserializer::read_string() {
    // Passo 1: Ler o tamanho da string, que foi escrito primeiro
    uint32_t size;
    file_stream.read(reinterpret_cast<char*>(&size), sizeof(size));

    // Passo 2: Criar um "buffer" (um espaço na memória) com esse tamanho
    std::vector<char> buffer(size);

    // Passo 3: Ler exatamente 'size' bytes do arquivo para dentro do buffer
    file_stream.read(buffer.data(), size);

    // Passo 4: Converter o buffer de bytes de volta para uma std::string
    return std::string(buffer.begin(), buffer.end());
}