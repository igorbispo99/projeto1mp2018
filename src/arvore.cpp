#include "arvore.hpp"

//A funcao tem como entrada um numero inteiro em base 10 e o numero de bits
//que serao usados para representar o numero. A funcao retorna uma string de 
//"0" e "1" contendo a representacao binaria de "decimal"
namespace arvores {
std::string DecimalParaBinario (const int decimal, const int numero_de_bits) {
  std::string numero_binario;
  
  for(int i = 0;i < numero_de_bits;i++) numero_binario.push_back('0'); //Por padrao, preenche a string com zeros

  if(decimal == 0)
    return numero_binario;

  int numero = decimal;
  for(int i = numero_binario.length() - 1; numero != 0 && i >= 0;i--) {
    numero_binario[i] = numero % 2 + '0';
    numero /= 2;
  }

    return numero_binario;
}



} //namespace arvores
