#ifndef ARVORE_H_
#define ARVORE_H_

#include <iostream>
#include <fstream>
#include <memory>

namespace arvores {

//A arvore binaria é definida de forma genérica pra armazenar qualquer tipo de dados
template <class TIPODADOS>
class ArvoreBinaria {
  public:
    ArvoreBinaria(void);
    bool EstaVazia(void);

  private:
    //Para facilitar a escrita do codigo, o ponteiro para CelulaArvore sera
    //definido como PtrCelulaArvore, foi usado um ponteiro inteligente do C++
    //para facilitar o gerenciamento de memoria
    struct CelulaArvore;
    typedef std::unique_ptr<CelulaArvore> PtrCelulaArvore;

    //Definindo um no tipico da arvore binaria com ponteiros para os nos
    //da direita e esquerda e um tipo de dado generico
    struct CelulaArvore {
      TIPODADOS dados;
      PtrCelulaArvore esquerda;
      PtrCelulaArvore direita;

      //Definindo construtor de CelulaArvore
      CelulaArvore (const TIPODADOS &dado) {
        dados = dado;
        esquerda = nullptr;
        direita = nullptr;
      }
    };

    PtrCelulaArvore raiz;

    
};

//Definindo funcoes genericas
template <class TIPODADOS>
ArvoreBinaria<TIPODADOS>::ArvoreBinaria(void) {
  raiz = nullptr;
}

template <class TIPODADOS>
bool ArvoreBinaria<TIPODADOS>::EstaVazia(void) {
  if (raiz == nullptr) {
    return true;
  } else {
    return false;
  }
}


} //namespace arvores

#endif 