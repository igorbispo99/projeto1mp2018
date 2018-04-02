#ifndef ARVORE_H_
#define ARVORE_H_

#include <iostream>
#include <fstream>
#include <list>
#include <string>

namespace arvores {

class NoArvore {
  public:
    std::string pergunta;
    NoArvore* no_esquerda;
    NoArvore* no_direita;
    
    NoArvore(std::string nova_pergunta);
    NoArvore(void);
    int InserirEsquerda(NoArvore novo_no);
    int InserirDireita(NoArvore novo_no);
};

class ArvoreBinaria {
  public:
    ArvoreBinaria(std::string diretorio_arquivo);
    ArvoreBinaria(void);
    void PrintarArvore(void);
    bool EstaVazia(void);

  
  private:
    NoArvore* no_raiz;
    
};

} //namespace arvores

#endif 