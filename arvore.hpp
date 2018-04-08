#ifndef ARVORE_H_
#define ARVORE_H_

#include <iostream>
#include <memory>
#include <string>
#include <type_traits> // Incluido na biblioteca padrao a partir do C++17
#include <fstream>

namespace arvores {

/*
  O acesso as celulas da arvore se da pelo sistema de coordenadas "nivel" e "posicao".
  "Nivel" representa os niveis da arvore binaria, sendo nivel 0 a raiz da arvore.
  "Posicao" representa a posicao da celula em relacao a cada nivel, sendo a posicao
  mais a esquerda de cada nivel considerada posicao 0.

  Exemplo: (Pos. indica Posicao)
  Nivel 0             (Pos.0)        
                    /         \                   
  Nivel 1        (Pos.0)     (Pos.1)    
                /     \      /     \ 
  Nivel 2    (Pos.0)(Pos.1) (Pos.2) (Pos. 3) 
  ...                  ...
*/

enum CodigosDirecao {ESQUERDA = '0', DIREITA}; //Definindo os codigos que representam as direcoes
enum CodigosErro {EXITO = 2, FALHA}; //Definindo os codigos de erro para as funcoes

//Declaracao da funcao que converte um numero decimal para uma string de "0" e "1"
//representando o numero "decimal" em base 2 com "numero_de bits" de digitos
std::string DecimalParaBinario(const int decimal, const int numero_de_bits);

/*
  A arvore binaria é definida de forma genérica pra armazenar qualquer tipo de dados.
  Para que o codigo compile, é necessario que tanto a declaracao quanto a definicao
  das funcoes genericas estejam no arquivo header (.hpp) pois o compilador precisa 
  saber em tempo de compilacao quais os tipos foram instanciados pelo arquivo body (.cpp).

  Caso as funcoes genericas fossem declaradas no arquivo "arvore.hpp" e definidas 
  no arquivo "arvore.cpp", a compilacao falharia,
*/

template <class T>
class ArvoreBinaria {
  public:
    ArvoreBinaria(void);
    bool EstaVazia(void);
    int InserirCelula(const uint nivel, const uint posicao, const T);
    int LerCelula(const uint nivel, const uint posicao, T& saida_dado);
    int MudarValorCelula(const uint nivel, const uint posicao, const T);
    int LerDoArquivo(const std::string diretorio_arquivo);

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
      CelulaArvore (const T dado) {
        dados = dado;
        pai = nullptr;
        esquerda = nullptr;
        direita = nullptr;
      }
    };

    PtrCelulaArvore raiz;

    //Funcoes usadas somento dentro da classe para evitar a repeticao 
    //de blocos de codigo.Essas funcoes nao deve ser chamadas diretamente 
    //pelo usuario e, portanto, sao funcoes privadas.
    bool CelulaNula(PtrCelulaArvore celula_arvore);
    PtrCelulaArvore BuscarCelula(const uint nivel, const uint posicao); 
    void ErroInsercaoCelulaInvalida(const uint nivel, const uint posicao);
    void ErroInsercaoCelulaExiste(const uint nivel, const uint posicao);
    void ErroBuscaCelulaNaoExiste(const uint nivel, const uint posicao); 
    void ErroNaoPodeAbrirArquivo(const std::string diretorio_arquivo);
    void ErroArquivoInvalido(const std::string diretorio_arquivo);
    void ErroTipoLeituraDeArquivo(void);
};

//As funcoes genericas tem que ser definidas no arquivo header (.hpp) caso
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

template <class T>
typename ArvoreBinaria<T>::PtrCelulaArvore ArvoreBinaria<T>::BuscarCelula(const uint nivel, const uint posicao) {
 
}

//Mensagem de erro caso o usuario tente inserir uma celula em um lugar invalido
template <class T>
void ArvoreBinaria<T>::ErroBuscaCelulaNaoExiste(const uint nivel, const uint posicao) {
  std::cerr << "Nao existe celula inicializada em ("<< nivel << "," << posicao << ")" << std::endl;
}

//Mensagem de erro caso o usuario tente inserir uma celula em um lugar invalido
template <class T>
void ArvoreBinaria<T>::ErroInsercaoCelulaInvalida(const uint nivel, const uint posicao) {
  std::cerr << "Nao foi possivel inserir a celula em ("<< nivel << "," << posicao << ")";
  std::cerr << " => Posicao Invalida" << std::endl;
}

//Mensagem de erro caso o usuario tente inserir uma celula em um lugar ja ocupado
template <class T>
void ArvoreBinaria<T>::ErroInsercaoCelulaExiste(const uint nivel, const uint posicao) {
  std::cerr << "Nao foi possivel inserir a celula em ("<< nivel << "," << posicao << ")";
  std::cerr << " => Ja existe uma celula nessa posicao." << std::endl;
}

//Mensagem de erro caso o arquivo nao possa ser aberto
template <class T>
void ArvoreBinaria<T>::ErroNaoPodeAbrirArquivo(const std::string diretorio_arquivo) {
  std::cerr << "Arquivo " << diretorio_arquivo << " nao pode ser aberto." << std::endl;
}

//Mensagem de erro caso o arquivo seja invalido
template <class T>
void ArvoreBinaria<T>::ErroArquivoInvalido(const std::string diretorio_arquivo) {
  std::cerr << "Arquivo " << diretorio_arquivo << " nao é um arquivo de arvore valido." << std::endl;
}

//Mensagem de erro caso o usuario tente usar leitura/escrita de arquivo em tipo invalido
template <class T>
void ArvoreBinaria<T>::ErroTipoLeituraDeArquivo(void) {
  std::cerr << "Nao pode salvar esse tipo de arvore em arquivo" << std::endl;
}


template <class T>
int ArvoreBinaria<T>::InserirCelula(const uint nivel, const uint posicao, const T dado) {
  PtrCelulaArvore nova_celula = std::make_shared<CelulaArvore>(dado);
  //Tratando o caso de quando o usuario deseja inserir a celula diretamente na raiz
  if (nivel == 0 && posicao == 0) {
    if (EstaVazia()) {
      raiz = nova_celula;
      return EXITO;
    } else {
      ErroInsercaoCelulaExiste(nivel, posicao);
      return FALHA;
    }
  } // if nivel == 0 && posicao == 0

  //Se a funcao cair neste else, significa que o usuario tentou inserir uma celula
  //sem antes inicializar a raiz da arvore
  else { 
    if (EstaVazia()) {
      ErroInsercaoCelulaInvalida(nivel, posicao);
      return FALHA;
    }
  }
      
  //Foi feita uma operacao bitwise para representar a potencia 2^nivel
  //Como o numero 1 em representacao binaria equivale a 1, se for feito
  //"nivel" shifts de bits para a esquerda, o resultado sera (em representacao 
  // binaria) 1000.. (1 seguido de "nivel" zeros), o que equivale a 2^nivel.
  //Exemplo :
  //  1 << 5 = 100000 (em representacao binaria) ou 32 (em representacao decimal) = 2^5

  //Caso a posicao seja maior do que 2^nivel, com certeza trata-se de uma
  //posicao invalida pois cada nivel tem (no maximo) 2^nivel celulas
  if (posicao >= (1 << nivel)) {
    ErroInsercaoCelulaInvalida(nivel, posicao);
    return FALHA;
  }

  std::string caminho_em_bits = DecimalParaBinario(posicao, nivel);
  
  int nivel_atual = 0;
  int nivel_alvo = nivel - 1; 
  PtrCelulaArvore ptr_celula = raiz;

  while(nivel_atual < nivel_alvo && ptr_celula != nullptr) {
    if (caminho_em_bits[nivel_atual] == ESQUERDA) {
      ptr_celula = ptr_celula->esquerda;
    } else {
      ptr_celula = ptr_celula->direita;
    }
    nivel_atual++;
  }

  //Se o ultimo nivel da arvore que pôde ser atingido nao corresponde ao nivel desejado
  //pelo usuario, significa que o usuario escolheu inserir a celula em um nivel ainda
  //nao inicializado, tal operacao nao é permitida.
  if (nivel_atual != nivel_alvo) {
    ErroInsercaoCelulaInvalida(nivel, posicao);
    return FALHA;
  }

  //Verifica se a posicao que o usuario quer inserir a celula já está ocupada
  if ((caminho_em_bits[nivel_atual] == ESQUERDA ? ptr_celula->esquerda : ptr_celula->direita) != nullptr) {
    ErroInsercaoCelulaExiste(nivel, posicao);
    return FALHA;
  }

  if (caminho_em_bits[nivel_atual] == ESQUERDA) {
    ptr_celula->esquerda = nova_celula; // nova_celula está definida no comeco da funcao
    nova_celula->pai = ptr_celula;
  } else {
    ptr_celula->direita = nova_celula; // nova_celula está definida no comeco da funcao
    nova_celula->pai = ptr_celula;
  }

  return EXITO;

}

template <class T>
int ArvoreBinaria<T>::LerCelula(const uint nivel, const uint posicao, T& saida_dado) {
  
  //Verifica se a posicao que o usuario tentou acessar é valida
  if (posicao >= (1 << nivel)) {
    ErroBuscaCelulaNaoExiste(nivel, posicao);
    return FALHA;
  }
  //Calculando o caminho a ser percorrido ate a celula
  std::string caminho_em_bits = DecimalParaBinario(posicao, nivel);

  int nivel_atual = 0;
  int nivel_alvo = nivel; 
  PtrCelulaArvore ptr_celula = raiz;

  while(nivel_atual < nivel_alvo && ptr_celula != nullptr) {
    if (caminho_em_bits[nivel_atual] == ESQUERDA) {
      ptr_celula = ptr_celula->esquerda;
    } else {
      ptr_celula = ptr_celula->direita;
    }
    nivel_atual++;
  }

  //Verifica se foi possivel chegar no nivel desejado pelo usuario
  if (nivel_atual != nivel_alvo) {
    ErroBuscaCelulaNaoExiste(nivel, posicao);
    return FALHA;
  }

   //Verifica se existe uma celula na posicao desejada pelo usuario
  if (ptr_celula == nullptr) {
    ErroBuscaCelulaNaoExiste(nivel, posicao);
    return FALHA;
  }

  saida_dado = ptr_celula->dados;

  return EXITO;
}

template <class T>
int ArvoreBinaria<T>::MudarValorCelula(const uint nivel, const uint posicao, const T novo_dado) {
  //Verifica se a posicao que o usuario tentou acessar nao 
  if (posicao >= (1 << nivel)) {
    ErroBuscaCelulaNaoExiste(nivel, posicao);
    return FALHA;
  }
  //Calculando o caminho a ser percorrido ate a celula
  std::string caminho_em_bits = DecimalParaBinario(posicao, nivel);

  int nivel_atual = 0;
  int nivel_alvo = nivel; 
  PtrCelulaArvore ptr_celula = raiz;

  while(nivel_atual < nivel_alvo && ptr_celula != nullptr) {
    if (caminho_em_bits[nivel_atual] == ESQUERDA) {
      ptr_celula = ptr_celula->esquerda;
    } else {
      ptr_celula = ptr_celula->direita;
    }
    nivel_atual++;
  }

  //Verifica se foi possivel chegar no nivel desejado pelo usuario
  if (nivel_atual != nivel_alvo) {
    ErroBuscaCelulaNaoExiste(nivel, posicao);
    return FALHA;
  }

   //Verifica se existe uma celula na posicao desejada pelo usuario
  if (ptr_celula == nullptr) {
    ErroBuscaCelulaNaoExiste(nivel, posicao);
    return FALHA;
  }

  ptr_celula->dados = novo_dado;

  return EXITO;
}

/*
 Funcao que le as informacoes do tipo de dados arvore a partir de uma arquivo especificado
 como parametro pra funcao. So funciona para arvore de double, int, booleans e strings 
 para evitar exceptions e undefined behaviour.

 Como estrutura padrao, cada linha do arquivo de arvore deve conter uma instrucao
 valida de insercao de celula conforme o seguinte padrao: (nivel, posicao) = dado .
 Exemplo:
 (0,0) = 10
 (1,0) = 100
 (1,1) = 0
    .
    .
    .
  As insercoes de celula na arvore serao feitas pelo metodo InserirCelula da classe,
  logo, os erros de posicoes e niveis invalidos serao processados por InserirCelula.
*/
template <class T>
int ArvoreBinaria<T>::LerDoArquivo(std::string diretorio_arquivo) {
  std::ifstream arquivo_arvore;
  //Tentando abrir o arquivo especificado pelo usuario
  arquivo_arvore.open(diretorio_arquivo);

  //Verifica se o arquivo pode ser aberto
  if (!arquivo_arvore.is_open()) {
    ErroNaoPodeAbrirArquivo(diretorio_arquivo);
    return FALHA;
  }

  //Iterando pelas linhas do arquivo e verificando se é um arquivo valido
  std::string linha_arquivo;
  while (std::getline(arquivo_arvore, linha_arquivo)) {
    //Se a linha nao tem caracteres alem da quebra de linha, pula a iteracao do loop
    if (linha_arquivo.size() == 1) continue; 
    //Se a linha nao comeca com parenteses, o arquivo nao é valido
    if (linha_arquivo[0] != '(') {
      ErroArquivoInvalido(diretorio_arquivo);
      return FALHA;
    }
    //Procura pela virgula na especificacao das coordenadas
    uint posicao_virgula = linha_arquivo.find(",");

    //Procura pelo caracter de fechamento de parenteses
    uint posicao_fecha_parenteses = linha_arquivo.find(")");

    //Procura pelo caracter de igual entre as coordenada e os dados
    uint posicao_igual = linha_arquivo.find("=");

    //Se a virgula nao estiver entre os parenteses, o arquivo nao pode ser valido
    if (posicao_virgula > posicao_fecha_parenteses) {
      ErroArquivoInvalido(diretorio_arquivo);
      return FALHA;
    }
    //Se o igual nao estiver apos os parenteses e a virgula, o arquivo nao pode ser valido
    if (posicao_igual < posicao_fecha_parenteses) {
      ErroArquivoInvalido(diretorio_arquivo);
      return FALHA;
    }

    //Faz a leitura do nivel e posicao especificados no arquivo
    std::string string_nivel = linha_arquivo.substr(1, posicao_virgula - 1);
    std::string string_posicao = linha_arquivo.substr(posicao_virgula + 1, posicao_fecha_parenteses - (posicao_virgula + 1));

    //Converte a string para um numero inteiro
    uint _nivel = std::stoi(string_nivel);
    uint _posicao = std::stoi(string_posicao);

    //Faz a leitura do dado que vai ser inserido na celula
    std::string string_dado = linha_arquivo.substr(posicao_igual + 1);
    T _dado;

    //Faz a conversao do tipo de dados string para o que foi utilizado no template
    //Para tratar cada caso de conversao separadamente, foi usada a funcao std::is_same_v<T, "tipo">()
    //que retorna True caso o tipo de dados de V seja o mesmo do especificado a direita "tipo"

    //Caso seja string, remove o ultimo caracter pois este é um caracter especial de formatacao do texto
    if (std::is_same_v<T, std::string>) {
      string_dado.pop_back(); // Remove o ultimo caracter
      _dado = string_dado; 
    } 
    //Caso seja int, faz a conversao de string para int
    else if (std::is_same_v<T, int> || std::is_same_v<T,uint>) {
      _dado = std::stoi(string_dado);  
    }
    //Caso seja double, faz a conversao de string para double
    else if (std::is_same_v<T, double>) {
      _dado = std::stod(string_dado);
    }
    else if (std::is_same_v<T, float>) {
      _dado = std::stof(string_dado);
    }
    //Caso seja um booleano, converte a string True,true ou 1 para true booleano
    //e converte False, false, ou 0 para false booleano
    else if (std::is_same_v<T, bool>) {
      string_dado.pop_back();
      if (string_dado == "True" || string_dado == "true" || string_dado == "1") _dado = true;
      if (string_dado == "False" || string_dado == "false" || string_dado == "0") _dado = false;
    }
    //Adiciona os dados lidos na arvore com a funcao InserirCelula e verifica erros
    if (InserirCelula(_nivel, _posicao, _dado) == FALHA) return FALHA;

  } // while (getline (arquivo_arvore, linha_arquivo))

  return EXITO;

}

} //namespace arvores

#endif 