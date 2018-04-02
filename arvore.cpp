#include "arvore.h"

namespace arvores {

ArvoreBinaria::ArvoreBinaria(std::string diretorio_arquivo) {

}

ArvoreBinaria::ArvoreBinaria(void) {
  std::ifstream arquivo_padrao("arvore_padrao.txt");
  no_raiz = nullptr;

  //Checando se o arquivo padrao pode ser carregado
  if (!arquivo_padrao.good()) {
    const char* mensagem_erro = "O arquivo padrao (arvore_padrao.txt) nao pode ser carregado";
    std::cerr << mensagem_erro << std::endl;
    exit(-1);
  }


}

bool ArvoreBinaria::EstaVazia(void) {
  if (no_raiz == nullptr) {
    return true;
  } else {
    return false;
  }
}

void ArvoreBinaria::PrintarArvore(void) {
  
}

NoArvore::NoArvore(std::string nova_pergunta) {
  pergunta = nova_pergunta;
  no_esquerda = nullptr;
  no_direita = nullptr;
}

NoArvore::NoArvore(void) {
  //Por padrao, todas as strings sao inicializadas com "\0"
  pergunta = "\0";
  no_esquerda = nullptr;
  no_direita = nullptr;
}

} //namespace arvores