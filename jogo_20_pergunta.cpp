#include "arvore.hpp"

enum CodigosJogo {
  ERRO = -1, SIM, NAO
};

inline int AvaliarResposta(std::string resposta) {
  if (resposta == "SIM" || resposta == "sim" || resposta == "S") {
    return SIM;
  } else if (resposta == "NAO" || resposta == "nao" || resposta == "N") {
    return NAO;
  } else {
    return ERRO;
  }
}

int RodarJogo(const std::string diretorio_jogo) {
  arvores::ArvoreBinaria<std::string> arvore_jogo;
  std::string buffer;
  if (arvore_jogo.LerDoArquivo("arvore_padrao.txt") == arvores::FALHA) {
    return ERRO;
  }

  if (arvore_jogo.LerCelula(0, 0, buffer) == arvores::FALHA) {
    std::cout << "Arquivo de arvore vazio." << std::endl;
    return ERRO;
  }

  bool continua_jogo = true;
  bool acertou_objeto = true;
  int ultima_celula_nivel;
  int ultima_celula_posicao;

  for (int i = 0, j = 0;continua_jogo && i < 20;i++) {
    std::string string_arvore;
    arvore_jogo.LerCelula(i, j, string_arvore);

    if (arvore_jogo.TemFilho(i,j)) {
      std::string resposta_usuario;
      std::cout << string_arvore << " (SIM/NAO)" << std::endl;
      std::getline(std::cin, resposta_usuario);

      int resposta_avaliada = AvaliarResposta(resposta_usuario);

      while(resposta_avaliada == ERRO) {
        std::cout << "Resposta invalida, responda com sim ou nao." << std::endl;
        std::getline(std::cin, resposta_usuario);
        resposta_avaliada = AvaliarResposta(resposta_usuario);
      }

      if(resposta_avaliada == SIM) {
        j = j*2;
      } else {
        j = j*2 + 1;
      }
    } // arvore_jogo.TemFilho(i,j)
    else {
      std::string resposta_usuario;
      std::cout << "Seu objeto é um/a " << string_arvore << "? (SIM/NAO)" << std::endl;
      std::getline(std::cin, resposta_usuario);

      int resposta_avaliada = AvaliarResposta(resposta_usuario);

      while(resposta_avaliada == ERRO) {
        std::cout << "Resposta invalida, responda com sim ou nao." << std::endl;
        std::getline(std::cin, resposta_usuario);
        resposta_avaliada = AvaliarResposta(resposta_usuario);
      }

      continua_jogo = false;

      if(resposta_avaliada == SIM) { // Significa que o usuario respondeu sim
        acertou_objeto = true;
      } else {
        acertou_objeto = false;
      }

      ultima_celula_nivel = i;
      ultima_celula_posicao = j;
      
    } //else
  }// for (i = 0, j = 0;continua_jogo;i++)

  if (!acertou_objeto) {
    std::cout << "Parabens, voce venceu! Agora me ensine a adivinhar." << std::endl;

    std::cout << "Escreva o seu objeto." << std::endl;
    std::string objeto_usuario;
    std::getline(std::cin, objeto_usuario);

    std::cout << "Agora escreva uma pergunta que poderia me ajudar a diferenciar seu objeto do que eu te sugeri." << std::endl;
    std::string pergunta_usuario;
    std::getline(std::cin, pergunta_usuario);

    std::cout << "Essa pergunta deve ser respondida com SIM ou com NAO?" << std::endl;
    std::string alternativa_usuario;
    std::getline(std::cin, alternativa_usuario);

    int alternativa_avaliada = AvaliarResposta(alternativa_usuario);

    while(alternativa_avaliada == ERRO) {
      std::cout << "Resposta invalida, responda com sim ou nao." << std::endl;
      std::getline(std::cin, alternativa_usuario);
      alternativa_avaliada = AvaliarResposta(alternativa_usuario);
    }

    //Verifica qual a reposta dada pelo computador ao usuario
    std::string objeto_sugerido;
    arvore_jogo.LerCelula(ultima_celula_nivel, ultima_celula_posicao, objeto_sugerido);

    //Substitui a resposta sugerida pelo computador pela pergunta do usuario
    arvore_jogo.MudarValorCelula(ultima_celula_nivel, ultima_celula_posicao, pergunta_usuario);

    //Insere mais duas celulas, uma com a resposta sugerida
    //pelo usuario, outra com a resposta antiga ja presente na arvore.
    if(alternativa_avaliada == SIM) { 
      //O objeto que o usuario escolheu vai ser inserido a esquerda pois o usuario
      //definiu que a resposta para sua pergunta é SIM
      arvore_jogo.InserirCelula(ultima_celula_nivel + 1, ultima_celula_posicao*2, objeto_usuario);
      arvore_jogo.InserirCelula(ultima_celula_nivel + 1, ultima_celula_posicao*2 + 1, objeto_sugerido);;
    } else {
      arvore_jogo.InserirCelula(ultima_celula_nivel + 1, ultima_celula_posicao*2, objeto_sugerido);
      arvore_jogo.InserirCelula(ultima_celula_nivel + 1, ultima_celula_posicao*2 + 1, objeto_usuario);
    }


  } // if(!acertou_objeto)

  
  for(int i = 0;i < 4;i++){
    for(int j = 0;j < (1 << i);j++){
      std::string buffer;

      if(arvore_jogo.LerCelula(i, j, buffer) == arvores::EXITO)
        std::cout << "(" <<i<<","<<j<<")"<<" => "<< buffer << std::endl;
    }
  }
}

int main(){
  RodarJogo("arvore_padrao.txt");
}