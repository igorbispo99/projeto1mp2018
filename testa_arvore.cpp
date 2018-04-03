#define CATCH_CONFIG_MAIN
#include <catch.hpp>
#include "arvore.h"

TEST_CASE("Testando construtores", "[arvore]") {
  arvores::ArvoreBinaria<int> arvore_int;
  //arvores::ArvoreBinaria<std::string> arvore_string;

  REQUIRE(arvore_int.EstaVazia());
  REQUIRE(arvore_int.InserirCelulaEsquerda(0, 0, 10) == 0);

}

TEST_CASE("Testando leitura de arvores", "[arvore]") {

}