#define CATCH_CONFIG_MAIN
#include <catch.hpp>
#include "arvore.hpp"

//Definindo funcoes de teste de falhas/exitos para evitar repeticoes pelo codigo

TEST_CASE("Testando construtores", "[arvore]") {
  arvores::ArvoreBinaria<int> arvore_int;
  arvores::ArvoreBinaria<std::string> arvore_string;
  REQUIRE(arvore_int.EstaVazia());
  REQUIRE(arvore_int.EstaVazia());
}

TEST_CASE("Testando funcao de conversao de decimal para binario", "[arvore]") {
  REQUIRE(arvores::DecimalParaBinario(100, 7) == "1100100");
  REQUIRE(arvores::DecimalParaBinario(128, 8) == "10000000");
  REQUIRE(arvores::DecimalParaBinario(127, 10) == "0001111111");
}

TEST_CASE("Testando insercao de celulas nas arvores", "[arvore]") {
  arvores::ArvoreBinaria<double> arvore_double;

  //Testando insercoes na origem e em posicoes invalidas
  REQUIRE(arvore_double.InserirCelula(0, 0, 1.5) == arvores::EXITO);
  REQUIRE(arvore_double.InserirCelula(0, 0, 3.10) == arvores::FALHA); // Tentando inserir uma celula em lugar ja ocupado
  REQUIRE(arvore_double.InserirCelula(2, 100, 0.500001) == arvores::FALHA); //Tentando inserir uma celula em posicao invalida (2,100)
  REQUIRE(arvore_double.InserirCelula(3, 8, 1.5678987) == arvores::FALHA); // Tentando inserir umar celular em posicao invalida (3,8)  

  REQUIRE(arvore_double.InserirCelula(10, 2, 10.8) == arvores::FALHA); // Tentando inserir um no em um nivel ainda nao preenchido
  REQUIRE(arvore_double.InserirCelula(1, 0, 0.000001) == arvores::EXITO); 
  REQUIRE(arvore_double.InserirCelula(1,1,1) == arvores::EXITO);

  arvores::ArvoreBinaria<uint> arvore_uint;
  REQUIRE(arvore_uint.InserirCelula(1, 0, 100) == arvores::FALHA); // Tentando inserir um no antes de incializar a raiz da arvore
  REQUIRE(arvore_uint.InserirCelula(0, 0, 0) == arvores::EXITO);
  REQUIRE(arvore_uint.InserirCelula(10, 2, 10) == arvores::FALHA); // Tentando inserir um no em um nivel ainda nao preenchido
  REQUIRE(arvore_uint.InserirCelula(1, 0, 3) == arvores::EXITO); 
  REQUIRE(arvore_uint.InserirCelula(1,1,1) == arvores::EXITO);
}

TEST_CASE("Testando busca de celulas pela arvore", "[arvore]") {
  arvores::ArvoreBinaria<float> arvore_float;
  float saida_arvore;
  float saida_esperada;

  //Inserindo celulas para serem testadas
  arvore_float.InserirCelula(0, 0, 0.1);
  arvore_float.InserirCelula(1, 1, 0.001);
  arvore_float.InserirCelula(2, 2, 100);

  //Verificando se a celula 0,0 foi inserida corretamente e o valor retornado corresponde ao valor esperado
  saida_esperada = 0.1;
  REQUIRE(arvore_float.LerCelula(0, 0) == saida_esperada);

  //Verificando se a celula 1,1 foi inserida corretamente
  saida_esperada = 0.001;
  REQUIRE(arvore_float.LerCelula(1,1) == saida_esperada);

  saida_esperada = 100;
  REQUIRE(arvore_float.LerCelula(2, 2) == saida_esperada);

  //Verificando a leitura de celulas nao existentes
  REQUIRE(arvore_float.LerCelula(10, 10) == arvores::NAOENCONTROU);
  REQUIRE(arvore_float.LerCelula(0, 10) == arvores::NAOENCONTROU);
}

TEST_CASE("Testando mudanca de dados na arvores", "[arvore]") {
  arvores::ArvoreBinaria<int> arvore_int;
  arvore_int.InserirCelula(0, 0, 1000);
  arvore_int.InserirCelula(1, 1, 10);
  arvore_int.InserirCelula(2, 2, 0);

  int novo_valor = 1;
  REQUIRE(arvore_int.MudarValorCelula(2, 2, novo_valor) == arvores::EXITO);
  REQUIRE(arvore_int.LerCelula(2, 2) == novo_valor);
}