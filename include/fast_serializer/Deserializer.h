// Arquivo: include/fast_serializer/Deserializer.h

#ifndef DESERIALIZER_H
#define DESERIALIZER_H

#include <string>
#include <fstream>
#include "fast_serializer/format.h" // Usa as mesmas structs de formato

class Deserializer {
private:
    std::ifstream file_stream; // Agora um fluxo de ENTRADA (ifstream)

public:
    // Construtor: abre o arquivo para leitura em modo binário
    Deserializer(const std::string& filename);

    // Destrutor: fecha o arquivo
    ~Deserializer();

    // Métodos para ler os tipos de dados que escrevemos
    int32_t read_int32();
    uint64_t read_uint64();
    double read_double();
    std::string read_string();

    // Método genérico para ler structs de tamanho fixo
    template<typename T>
    void read_struct(T& data) {
        // file.read espera um ponteiro para char (não const) para poder escrever na variável
        file_stream.read(reinterpret_cast<char*>(&data), sizeof(T));
    }
};

#endif // DESERIALIZER_H