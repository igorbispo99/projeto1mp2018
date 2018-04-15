#define CATCH_CONFIG_MAIN
#define DEBUG_ARVORES

#include <catch.hpp>
#include "arvore.hpp"

//Definindo funcoes de teste de falhas/exitos para evitar repeticoes pelo codigo
void inline TesteExito(int codigo_erro) {
  REQUIRE(codigo_erro == arvores::EXITO);
}

void inline TesteFalha(int codigo_erro) {
  REQUIRE(codigo_erro == arvores::FALHA);
}

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
  TesteExito(arvore_double.InserirCelula(0, 0, 1.5));

  TesteFalha(arvore_double.InserirCelula(0, 0, 3.10)); // Tentando inserir uma celula em lugar ja ocupado
  TesteFalha(arvore_double.InserirCelula(2, 100, 0.500001)); //Tentando inserir uma celula em posicao invalida (2,100)
  TesteFalha(arvore_double.InserirCelula(3, 8, 1.5678987)); // Tentando inserir umar celular em posicao invalida (3,8)  
  TesteFalha(arvore_double.InserirCelula(10, 2, 10.8)); // Tentando inserir um no em um nivel ainda nao preenchido

  TesteExito(arvore_double.InserirCelula(1, 0, 0.000001)); 
  TesteExito(arvore_double.InserirCelula(1,1,1));

  arvores::ArvoreBinaria<uint> arvore_uint;
  TesteFalha(arvore_uint.InserirCelula(1, 0, 100)); // Tentando inserir um no antes de incializar a raiz da arvore
  TesteExito(arvore_uint.InserirCelula(0, 0, 0));
  TesteFalha(arvore_uint.InserirCelula(10, 2, 10)); // Tentando inserir um no em um nivel ainda nao preenchido
  TesteExito(arvore_uint.InserirCelula(1, 0, 3)); 
  TesteExito(arvore_uint.InserirCelula(1,1,1));
}

TEST_CASE("Testando busca de celulas pela arvore", "[arvore]") {
  arvores::ArvoreBinaria<float> arvore_float;
  float saida_arvore;
  float saida_esperada;

  //Inserindo celulas para serem testadas
  arvore_float.InserirCelula(0, 0, 0.1);
  arvore_float.InserirCelula(1, 1, 0.001);
  arvore_float.InserirCelula(2, 2, 100);

  //Verificando se a celula 0,0 foi inserida corretamente e o valor retornado corresponde ao valor esperado (0.1)
  saida_esperada = 0.1;
  TesteExito(arvore_float.LerCelula(0, 0, saida_arvore));
  REQUIRE(saida_arvore == saida_esperada);

  //Verificando se a celula 1,1 foi inserida corretamente
  saida_esperada = 0.001;
  TesteExito(arvore_float.LerCelula(1, 1, saida_arvore));
  REQUIRE(saida_arvore == saida_esperada);

  saida_esperada = 100;
  TesteExito(arvore_float.LerCelula(2, 2, saida_arvore));
  REQUIRE(saida_arvore == saida_esperada);

  //Verificando a leitura de celulas nao existentes
  TesteFalha(arvore_float.LerCelula(10, 10, saida_arvore));
  TesteFalha(arvore_float.LerCelula(0, 10, saida_arvore));
}

TEST_CASE("Testando mudanca de dados na arvores", "[arvore]") {
  arvores::ArvoreBinaria<int> arvore_int;
  arvore_int.InserirCelula(0, 0, 1000);
  arvore_int.InserirCelula(1, 1, 10);
  arvore_int.InserirCelula(2, 2, 0);

  int novo_valor = 1;
  int valor_arvore;
  TesteExito(arvore_int.MudarValorCelula(2, 2, novo_valor));
  TesteExito(arvore_int.LerCelula(2, 2, valor_arvore));
  REQUIRE(valor_arvore == novo_valor);
}

TEST_CASE("Testando leitura de arvores a partir de arquivos", "[arvore]") {
  arvores::ArvoreBinaria<std::string> arvore_strings;
  std::string saida_esperada;
  std::string saida_arvore;

  TesteExito(arvore_strings.LerDoArquivo("arvore_padrao.txt"));

  //Testando se o valores foram lidos corretamente do arquivo
  saida_esperada = "Seu objeto pode ser encontrado na cozinha?";
  TesteExito(arvore_strings.LerCelula(0, 0, saida_arvore));

  REQUIRE(saida_arvore == saida_esperada);

  saida_esperada = "Cama";
  TesteExito(arvore_strings.LerCelula(2, 2, saida_arvore));
  REQUIRE(saida_arvore == saida_esperada);

  //Testa se a verificacao de filhos funciona
  REQUIRE(arvore_strings.TemFilho(0,0) == true);
  REQUIRE(arvore_strings.TemFilho(1,0) == true);
  REQUIRE(arvore_strings.TemFilho(3,7) == false);
  REQUIRE(arvore_strings.TemFilho(4,13) == false);
  REQUIRE(arvore_strings.TemFilho(100,100) == false); // Testando celula que nao existe

  //Testa a leitura de uma celula que nao esta presente no arquivo
  TesteFalha(arvore_strings.LerCelula(100, 100, saida_arvore)); 
  
  // Testando leitura de um arquivo que nao existe
  arvores::ArvoreBinaria<std::string> arvore;
  TesteFalha(arvore.LerDoArquivo("foo")); 
}

TEST_CASE("Testando a funcao de salvar as arvores no arquivo", "[arvores]") {
  arvores::ArvoreBinaria<double> arvore_double_escrita;
  std::string arquivo_saida = "arvore_saida.txt";

  arvore_double_escrita.InserirCelula(0, 0, 2.33);
  arvore_double_escrita.InserirCelula(1, 0, 30.000001);
  arvore_double_escrita.InserirCelula(1, 1, 0.01);

  TesteExito(arvore_double_escrita.SalvarNoArquivo(arquivo_saida));

  arvores::ArvoreBinaria<double> arvore_double_leitura;
  TesteExito(arvore_double_leitura.LerDoArquivo(arquivo_saida));

  double saida_arvore;
  TesteExito(arvore_double_leitura.LerCelula(1, 1, saida_arvore));

  double saida_esperada = 0.01;
  REQUIRE(saida_arvore == saida_esperada);
}

TEST_CASE("Testando funcoes para excluir celulas da arvore", "[arvores]") {
  arvores::ArvoreBinaria<std::string> arvore_string;
  std::string saida_celula;
  TesteExito(arvore_string.LerDoArquivo("arvore_padrao.txt"));

  TesteFalha(arvore_string.ApagarCelula(10, 10)); // Tenta apagar uma celula que nao existe
  TesteExito(arvore_string.ApagarCelula(2, 3));
  TesteFalha(arvore_string.LerCelula(2, 3, saida_celula)); // Verifica se a celula foi apagada
  TesteExito(arvore_string.ApagarCelula(0, 0)); //Tenta apagar a raiz da arvore
  REQUIRE(arvore_string.EstaVazia() == true); //Verifica se a arvore esta vazia apos a remocao da raiz 
}