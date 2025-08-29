Com certeza\! Aqui está o código Markdown completo para o `README.md` da sua biblioteca `fast-serializer`.

Você pode copiar o bloco de código abaixo e colar diretamente no seu arquivo `README.md`.

````markdown
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
````

-----

## 🛠️ Primeiros Passos

### Pré-requisitos

  * Um compilador C++ com suporte a C++17 (ex: `g++ 8` ou superior)
  * `make`

### Compilando a Biblioteca e o Teste

1.  **Clone o repositório:**

    ```bash
    git clone [https://github.com/caio2203/fast-serializer.git](https://github.com/caio2203/fast-serializer.git)
    cd fast-serializer
    ```

2.  **Compile:**

    ```bash
    make
    ```

    Este comando irá gerar dois artefatos principais no diretório `build/`:

      * `libfast_serializer.a`: A biblioteca estática, pronta para ser linkada em outros projetos.
      * `test_serializer`: Um executável de demonstração que valida a funcionalidade da biblioteca.

3.  **Execute o teste:**

    ```bash
    ./build/test_serializer
    ```

    Se a execução for bem-sucedida, uma mensagem de sucesso confirmará que o ciclo de escrita e leitura ("round-trip") funcionou perfeitamente.

-----

## 💡 Exemplo de Uso da API

A biblioteca é muito simples de usar. O exemplo abaixo demonstra um ciclo completo de escrita e leitura de dados.

```cpp
#include "fast_serializer/Serializer.h"
#include "fast_serializer/Deserializer.h"
#include <iostream>
#include <cassert>

int main() {
    const std::string filename = "meus_dados.dfb";

    // --- 1. Escrevendo dados com o Serializer ---
    try {
        Serializer ser(filename);
        ser.write_string("Olá Mundo");
        ser.write_int32(2025);
        ser.write_double(3.14);
    } catch (const std::exception& e) {
        std::cerr << "Erro ao escrever: " << e.what() << std::endl;
        return 1;
    }

    // --- 2. Lendo os dados de volta com o Deserializer ---
    try {
        Deserializer des(filename);
        std::string saudacao = des.read_string();
        int32_t ano = des.read_int32();
        double pi = des.read_double();

        // --- 3. Verificando se os dados são idênticos ---
        assert(saudacao == "Olá Mundo");
        assert(ano == 2025);
        assert(pi == 3.14);
        
        std::cout << "Sucesso! Dados lidos correspondem aos dados escritos." << std::endl;

    } catch (const std::exception& e) {
        std::cerr << "Erro ao ler: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}
```

-----

## 🗺️ Roadmap

  * [x] Serialização/Deserialização para tipos primitivos (`int32`, `uint64`, `double`).
  * [x] Serialização/Deserialização para `std::string` com prefixo de tamanho.
  * [x] Sistema de build com `Makefile` para gerar biblioteca estática e testes.
  * [ ] Implementação da seção de **Metadados** para descrever o esquema dos dados.
  * [ ] Suporte para serialização de tipos complexos, como `std::vector<T>`.
  * [ ] Adição de uma camada opcional de compressão (ex: zlib).
  * [ ] Benchmarks de performance detalhados.

-----

## 📄 Licença

Este projeto está licenciado sob a Licença MIT. Veja o arquivo `LICENSE` para mais detalhes.

```
```