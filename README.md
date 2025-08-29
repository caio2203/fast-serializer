# Fast Serializer ⚡ C++ Library

![C++](https://img.shields.io/badge/C%2B%2B-17-blue.svg)
![Build](https://img.shields.io/badge/Build-Makefile-green.svg)
![Platform](https://img.shields.io/badge/Platform-Linux-lightgrey.svg)
![License](https://img.shields.io/badge/License-MIT-yellow.svg)

**Fast Serializer** é uma biblioteca leve, de alto desempenho, desenvolvida em C++17 moderno para serialização e deserialização binária customizada. Foi projetada para cenários onde o overhead de formatos textuais como JSON ou CSV é um gargalo de performance e armazenamento.

Esta biblioteca é o componente central da etapa **Load** do [DataForge ETL Engine](https://github.com/caio2203/dataforge-etl), mas foi desenvolvida para ser totalmente independente e reutilizável em qualquer projeto C++ que necessite de I/O de disco eficiente.

---

## 🎯 Filosofia e Vantagens

Em um mundo de engenharia de dados, a velocidade e a eficiência de armazenamento são cruciais. `fast-serializer` foi construído com base nestes princípios:

* **Performance Extrema:** A conversão de dados para um formato binário elimina completamente o custo de parsing textual. Operações de leitura e escrita são cópias diretas de memória, resultando em um throughput significativamente maior. Em benchmarks preliminares, a escrita/leitura é **4 a 5 vezes mais rápida** que com JSON.
* **Formato Compacto:** Ao remover a verbosidade do texto (chaves, aspas, colchetes, espaços), o formato binário reduz o tamanho final dos arquivos em até **75%**, economizando custos de armazenamento e banda de rede.
* **Controle de Baixo Nível:** A biblioteca oferece controle direto sobre a representação binária dos dados, utilizando tipos de tamanho fixo (`<cstdint>`) para garantir a portabilidade do formato entre diferentes sistemas (com a mesma endianness).
* **API Simples e Moderna:** A interface com as classes `Serializer` e `Deserializer` é intuitiva e utiliza recursos modernos de C++, como `std::string`, para ser segura e fácil de usar.

---

## 📦 O Formato Binário "DataForge Binary" (`.dfb`)

A biblioteca implementa um formato binário customizado e extensível, projetado para simplicidade e velocidade.

A estrutura de um arquivo `.dfb` é dividida em seções lógicas:

1.  **Header:** Um cabeçalho de tamanho fixo com informações essenciais sobre o arquivo.
2.  **Metadata (Planejado):** Uma seção de tamanho variável para descrever o esquema dos dados (nomes e tipos de colunas).
3.  **Data:** Os registros de dados em si, escritos sequencialmente em formato binário compacto.

A estrutura do header é definida em `format.h`:
```cpp
// namespace dfb
struct Header {
    char     magic[4];      // "DFB1" - Identificador do formato e versão
    uint64_t record_count;  // Número total de registros no arquivo
    uint32_t metadata_size; // Tamanho da seção de metadados
    // ... campos reservados para futuras extensões ...
};
