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
    int InserirCelulaEsquerda(uint nivel, uint posicao, const T&);
    void InserirCelulaDireita(uint nivel, uint posicao, const T&);
    bool PresenteNaArvore(const T&);

  private:
    //Para facilitar a escrita do codigo, o ponteiro para CelulaArvore sera
    //definido como PtrCelulaArvore, foi usado um ponteiro inteligente do C++
    //para facilitar o gerenciamento de memoria
    struct CelulaArvore;
    typedef std::shared_ptr<CelulaArvore> PtrCelulaArvore;

    //Definindo um no tipico da arvore binaria com ponteiros para os nos
    //da direita e esquerda e um tipo de dado generico
    struct CelulaArvore {
      T dados;
      PtrCelulaArvore pai;
      PtrCelulaArvore esquerda;
      PtrCelulaArvore direita;

      //Definindo construtor de CelulaArvore
      CelulaArvore (const T& dado) {
        dados = dado;
        pai = nullptr;
        esquerda = nullptr;
        direita = nullptr;
      }
    };

    //Definindo os codigos de erro para as funcoes
    enum CodigosErro {EXITO, FALHA};

    bool CelulaNula(PtrCelulaArvore celula_arvore);
    void ErroInsercaoCelula(void);
    PtrCelulaArvore raiz;
    
};

//As funcoes genericas tem que ser definidas no arquivo header (.h) caso
//contrario, a compilacao do programa falhara na linkagem das bibliotecas

//Por padrao, a raiz é inicializada com null
template <class T>
ArvoreBinaria<T>::ArvoreBinaria(void) {
  raiz = nullptr;
}

//Funcao para evitar a repeticao de if's pelo codigo
template <class T>
bool ArvoreBinaria<T>::CelulaNula(PtrCelulaArvore ptr_celula) {
  if (ptr_celula == nullptr) {
    return true;
  } else {
    return false;
  }
}

//A arvore é vazia se a raiz é nula
template <class T>
bool ArvoreBinaria<T>::EstaVazia(void) {
  return CelulaNula(raiz);
}

//Mensagem de erro caso o usuario tente inserir uma celula em um lugar ja alocado ou invalido
template <class T>
void ArvoreBinaria<T>::ErroInsercaoCelula(void) {
  std::cerr << "Nao foi possivel inserir a celula na posicao desejada." << std::endl;
  std::cerr << "Posicao ja ocupada ou invalida." << std::endl;
}

template <class T>
int ArvoreBinaria<T>::InserirCelulaEsquerda(uint nivel, uint posicao, const T& dado) {
  PtrCelulaArvore nova_celula = std::make_unique<CelulaArvore>(dado);
  //Tratando o caso de quando o usuario deseja inserir a celula diretamente na raiz
  if (nivel == 0 && posicao == 0) {
    if (EstaVazia()) {
      raiz = std::move(nova_celula);
      return EXITO;
    } else {
      ErroInsercaoCelula();
      return FALHA;
    } // if EstaVazia()
  } // if nivel == 0 && posicao == 0

  //Foi feita uma operacao bitwise para representar a potencia 2^nivel
  //Como o numero 1 em representacao binaria equivale a 1, se for feito
  //"nivel" shifts de bits para a esquerda, o resultado sera (em representacao 
  // binaria) 1000.. (1 seguido de "nivel" - 1 zeros), o que equivale a 2^nivel.
  //Exemplo :
  //  1 << 5 = 10000 (em representacao binaria) ou 32 (em representacao decimal) = 2^5

  if ( posicao >=  1 << nivel ) {
    ErroInsercaoCelula();
    return FALHA;
  }
}

// template <class T>
// void ArvoreBinaria<T>::PresenteNaArvore(const T& dado) { 

// }

} //namespace arvores

#endif 