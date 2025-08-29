// Arquivo: include/fast_serializer/format.h
// planta do formato de arquivo

#ifndef FORMAT_H
#define FORMAT_H

#include <cstdint> // essencial para tamanho fixo 

// garante que o compoilador no add paddings inesperados
// na nossa struct, crucial para formato binario
#pragma pack(push, 1)

namespace dfb { // namespace para Dataforge Binary
    
    // o header do arquivo .dfb
    struct  Header {
    char magic [4]; // identificador do arquivo
    uint64_t record_count; 
    uint32_t metadata_size; 
    // comeplatar campos ...
    };

    // enum para tipos de dados suportados
    enum class FieldType : uint8_t {
    INT32  = 1,
    UINT64 = 2,
    DOUBLE = 3,
    STRING = 4
    };

    // descrição de uma unica coluna/campo
    struct FieldMetaData {
        char field_name[32]; // nome do campo tam. fixo
        FieldType field_type; // tipo de campo do enum
    };
}; // namespace dfb

#pragma pack(pop)
#endif // FORMAT_H

