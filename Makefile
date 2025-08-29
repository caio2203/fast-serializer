# Makefile para a biblioteca fast-serializer

# ==========================================================
#  1. DEFINIÇÃO DE VARIÁVEIS (A PARTE MAIS IMPORTANTE)
#  Esta seção deve estar no topo do seu arquivo.
# ==========================================================
CXX = g++
CXXFLAGS = -std=c++17 -Wall -Iinclude
LDFLAGS =

# Diretórios
BUILDDIR = build
INCDIR = include

# Nome da biblioteca
LIB_NAME = libfast_serializer.a
LIB_TARGET = $(BUILDDIR)/$(LIB_NAME)

# Arquivos fonte da BIBLIOTECA (encontra .cpp em src/ e subpastas)
LIB_SRCS = $(shell find src -name '*.cpp' ! -name 'main.cpp')
LIB_OBJS = $(LIB_SRCS:src/%.cpp=$(BUILDDIR)/%.o)

# Arquivo fonte do EXECUTÁVEL DE TESTE
TEST_SRC = src/main.cpp
TEST_OBJ = $(TEST_SRC:src/%.cpp=$(BUILDDIR)/%.o)
TEST_TARGET = $(BUILDDIR)/test_serializer


# ==========================================================
#  2. REGRAS DE COMPILAÇÃO
# ==========================================================

# Regra principal: compila a biblioteca e o teste
all: $(TEST_TARGET)

# Regra para criar a biblioteca estática (.a)
$(LIB_TARGET): $(LIB_OBJS)
	@echo "Criando biblioteca estática $@"
	ar rcs $@ $(LIB_OBJS)

# Regra para linkar o executável de teste com a nossa biblioteca
$(TEST_TARGET): $(TEST_OBJ) $(LIB_TARGET)
	@echo "Linkando executável de teste $@"
	$(CXX) $(TEST_OBJ) -L$(BUILDDIR) -lfast_serializer -o $@ $(LDFLAGS)

# Regra genérica para compilar arquivos .o
$(BUILDDIR)/%.o: src/%.cpp
	@echo "Compilando $<"
	@mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Limpeza
clean:
	@echo "Limpando diretório de build..."
	@rm -rf $(BUILDDIR)

.PHONY: all clean