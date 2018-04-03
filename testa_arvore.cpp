#define CATCH_CONFIG_MAIN
#include <catch.hpp>
#include "arvore.h"

TEST_CASE("Testando construtores", "[arvore]") {
  arvores::ArvoreBinaria<int> arvore_int;
  arvores::ArvoreBinaria<std::string> arvore_string;

  REQUIRE(arvore_int.EstaVazia());
  REQUIRE(arvore_int.EstaVazia());
}

TEST_CASE("Testando insercao de celulas nas arvores", "[arvore]") {
  arvores::ArvoreBinaria<double> arvore_double;

  //Testando insercoes na origem
  REQUIRE(arvore_double.InserirCelulaEsquerda(0, 0, 1.5) == 0);
  REQUIRE(arvore_double.InserirCelulaEsquerda(0, 0, -10.23) == 1); // Tentando inserir uma celula em lugar ja ocupado
  REQUIRE(arvore_double.InserirCelulaEsquerda(2, 100, 0.500001) == 1); //Tentando inserir uma celula em posicao invalida (2,100)

}