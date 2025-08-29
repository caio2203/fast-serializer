// Arquivo: src/main.cpp

#include "fast_serializer/Serializer.h"
#include "fast_serializer/Deserializer.h" // Agora podemos incluir o Deserializer
#include <iostream>
#include <cassert>
#include <iomanip>

int main() {
    const std::string test_filename = "build/test.dfb";
    
    // --- Valores Originais que vamos escrever ---
    const int32_t ano_original = 2025;
    const uint64_t id_original = 1234567890123456789ULL;
    const double pi_original = 3.1415926535;
    const std::string nome_original = "DataForge";

    // --- FASE DE ESCRITA (Serialização) ---
    std::cout << "Fase de Escrita (Serialização)..." << std::endl;
    try {
        Serializer ser(test_filename);
        dfb::Header header_escrita = {{'D','F','B','1'}, 4, 0};
        ser.write_struct(header_escrita);
        ser.write_int32(ano_original);
        ser.write_uint64(id_original);
        ser.write_double(pi_original);
        ser.write_string(nome_original);
    } catch (const std::exception& e) {
        std::cerr << "Erro na escrita: " << e.what() << std::endl;
        return 1;
    }
    std::cout << "Arquivo '" << test_filename << "' gerado." << std::endl;

    // --- FASE DE LEITURA (Deserialização) ---
    std::cout << "\nFase de Leitura (Deserialização)..." << std::endl;
    try {
        Deserializer des(test_filename);
        
        dfb::Header header_leitura;
        des.read_struct(header_leitura);
        
        int32_t ano_lido = des.read_int32();
        uint64_t id_lido = des.read_uint64();
        double pi_lido = des.read_double();
        std::string nome_lido = des.read_string();

        std::cout << "Dados lidos com sucesso." << std::endl;

        // --- VERIFICAÇÃO AUTOMÁTICA ---
        std::cout << "Verificando integridade dos dados..." << std::endl;
        assert(ano_lido == ano_original);
        assert(id_lido == id_original);
        assert(pi_lido == pi_original);
        assert(nome_lido == nome_original);

    } catch (const std::exception& e) {
        std::cerr << "Erro na leitura: " << e.what() << std::endl;
        return 1;
    }
    
    std::cout << "\nSUCESSO! Os dados escritos e lidos são idênticos." << std::endl;
    
    return 0;
}// Arquivo: src/main.cpp