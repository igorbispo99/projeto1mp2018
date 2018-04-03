#ifndef ARVORE_H_
#define ARVORE_H_

#include <iostream>
#include <fstream>
#include <memory>

namespace arvores {

//A arvore binaria é definida de forma genérica pra armazenar qualquer tipo de dados
template <class T>
class ArvoreBinaria {
  public:
    ArvoreBinaria(void);
    bool EstaVazia(void);
    bool CelulaNula(PtrCelulaArvore celula_arvore);
    int InserirCelulaEsquerda(uint nivel, uint posicao, const T&);
    void InserirCelulaDireita(uint nivel, uint posicao, const T&);
    void ErroInsercaoCelula(void);
    bool PresenteNaArvore(const T&);

  private:
    //Para facilitar a escrita do codigo, o ponteiro para CelulaArvore sera
    //definido como PtrCelulaArvore, foi usado um ponteiro inteligente do C++
    //para facilitar o gerenciamento de memoria
    struct CelulaArvore;
    typedef std::unique_ptr<CelulaArvore> PtrCelulaArvore;

    //Definindo um no tipico da arvore binaria com ponteiros para os nos
    //da direita e esquerda e um tipo de dado generico
    struct CelulaArvore {
      T dados;
      PtrCelulaArvore esquerda;
      PtrCelulaArvore direita

      //Definindo construtor de CelulaArvore
      CelulaArvore (const T& dado) {
        dados = dado;
        pai = nullptr;
        esquerda = nullptr;
        direita = nullptr;
      }
    };

    //Definindo os codigos de erro para as funcoes
    enum CodigosErro {
      EXITO,
      FALHA
    };

    PtrCelulaArvore raiz;
    
};

//As funcoes genericas tem que ser definidas no arquivo header (.h) caso
//contrario, a compilacao do programa falhara na linkagem das bibliotecas

//Por padrao, a raiz é inicializada com null
template <class T>
ArvoreBinaria<T>::ArvoreBinaria(void) {
  raiz = nullptr;
}

//A arvore é vazia se a raiz é nula
template <class T>
bool ArvoreBinaria<T>::EstaVazia(void) {
  return CelulaNula(raiz);
}

template <class T>
bool ArvoreBinaria<T>::CelulaNula(PtrCelulaArvore) {
  if(PtrCelulaArvore == nullptr) {
    return true;
  } else {
    return false;
  }
}

//Mensagem de erro caso o usuario tente inserir uma celula em um lugar ja alocado
template <class T>
void ArvoreBinaria<T>::ErroInsercaoCelula(void) {
  std::cerr << "Nao foi possivel inserir a celula na posicao desejada, celula ja ocupada" << std::endl;
}

template <class T>
int ArvoreBinaria<T>::InserirCelulaEsquerda(uint nivel, uint posicao, const T& dado) {
  PtrCelulaArvore nova_celula = std::make_unique<CelulaArvore>(dado);

  //Tratando o caso de quando o usuario deseja inserir a celula diretamente na raiz
  if (nivel == 0 && posicao == 0) {
    if (EstaVazia()) {
      raiz = nova_celula;
      return EXITO;
    } else {
      ErroInsercaoCelula();
      return FALHA;
    }
  }
}

// template <class T>
// void ArvoreBinaria<T>::PresenteNaArvore(const T& dado) { 

// }

} //namespace arvores

#endif 