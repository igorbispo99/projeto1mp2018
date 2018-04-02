#define CATCH_CONFIG_MAIN
#include <catch.hpp>
#include "arvore.h"

TEST_CASE("Testando construtores", "[arvore]") {
  arvores::ArvoreBinaria construtor_string("arquivo_teste");
  arvores::ArvoreBinaria construtor_padrao;
}

TEST_CASE("Testando leitura de arvores", "[arvore]") {
  arvores::ArvoreBinaria arvore_padrao;
  REQUIRE(arvore_padrao.EstaVazia());
}