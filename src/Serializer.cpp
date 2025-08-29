// Arquivo: src/Serializer.cpp

#include "fast_serializer/Serializer.h"
#include <stdexcept>

Serializer::Serializer(const std::string& filename) {
    file_stream.open(filename, std::ios::out | std::ios::binary);
    if (!file_stream.is_open()) {
        throw std::runtime_error("Não foi possível abrir o arquivo para escrita: " + filename);
    }
}

Serializer::~Serializer() {
    if (file_stream.is_open()) {
        file_stream.close();
    }
}

// Corrija o 's' para 'S' em todos os seus métodos
void Serializer::write_int32(int32_t value) {
//   ^--- CORRIGIDO
    file_stream.write(reinterpret_cast<const char*>(&value), sizeof(value));
}

void Serializer::write_uint64(uint64_t value) {
//   ^--- CORRIGIDO
    file_stream.write(reinterpret_cast<const char*>(&value), sizeof(value));
}

void Serializer::write_double(double value) {
//   ^--- CORRIGIDO
    file_stream.write(reinterpret_cast<const char*>(&value), sizeof(value));
}

void Serializer::write_string(const std::string& value) {
//   ^--- CORRIGIDO
    uint32_t size = value.length();
    file_stream.write(reinterpret_cast<const char*>(&size), sizeof(size));
    file_stream.write(value.c_str(), size);
}