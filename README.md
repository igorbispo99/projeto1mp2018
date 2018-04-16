# Projeto Árvores Binárias - Métodos de Programação 2018/1  
Projeto sobre arvores binarias da disciplina de Métodos de Programacao de 2018 - UnB

## Como Compilar:
   Para compilar o módulo de teste, va até o diretório **src** e rode o comando **make testa_arvore**,
   será gerado um arquivo executável **testa_arvore** na pasta raiz do diretório projeto1mp2018.

   Para compilar o jogo das 20 perguntas, vá até o diretório **src** e execute **make jogo_20_perguntas**,
   será gerado um arquivo executável **jogo_20_perguntas** na pasta raíz do diretório projeto1mp2018.

## Acesso às células da árvore:
  O acesso às celulas da árvore nao é feito de forma direta pelo usuário. Para ler e modificar os
  valores das células da árvore, o usuário deverá usar as funcoes **LerCelula** e **ModificarCelula**
  da classe **ArvoreBinaria**.
  
  Para facilitar o acesso, foi usado um sistema de coordenadas
  de  **"nível"** e **"posição"**.  
  **"Nivel**" representa os níveis (ou andares) da árvore binária, sendo nível 0 a raíz da arvore.    
  **"Posição"** representa a posição da célula em relação a cada nível, sendo a posição mais à 
  esquerda de cada nível considerada posição 0.  

## Arquivo de jogo:
   O arquivo que guarda o estado do jogo é um arquivo de texto puro que contém, em cada linha, um
   comando de insercao de uma célula na árvore que gerencia o jogo.  
   Os comandos de inserçao seguem a seguinte sintaxe:&nbsp;**(nivel, posicao)="frase"**.
   
   Exemplo:
   
   **(0,0)="Seu objeto é vermelho?"**  
   **(1,0)="Seu objeto é uma fruta?"**  
   **(1,1)="Maçã"**  
   &emsp;&emsp;&emsp;&emsp;.  
   &emsp;&emsp;&emsp;&emsp;.  
   &emsp;&emsp;&emsp;&emsp;. 
   
   
   

## Como Usar:
### Módulo de Teste de Arvore.hpp
   Para rodar os teste especificados no arquivo *testa_arvore.cpp*, deve se executar o arquivo **testa_arvore**.
### Jogo 20 Perguntas
   O jogo começa ao rodar o executável **jogo_20_perguntas**, o jogo pode tanto abrir/salvar um arquivo de árvore
   especificado pelo usuário, quanto abrir/salvar o arquivo padrao **jogo_padrao.txt**.

   Para ler e salvar o estado do jogo no arquivo padrao (**jogo_padrao.txt**), o usuário deve executar 
   **jogo_20_perguntas** sem parâmetros na linha de comando:
   Exemplo : *./jogo_20_perguntas*

   Para ler e salvar o estado do jogo em um arquivo específico, o usuário deve executar 
   **jogo_20_perguntas** seguido do nome do arquivo que deseja ler e salvar o estado do jogo:
   Exemplo : *./jogo_20_perguntas arquivo.txt*

   Para ler e salvar o estado do jogo em arquivos diferentes, o usuário deve executar 
   **jogo_20_perguntas** seguido do nome do arquivo que deseja ler e do arquivo no qual
   se deseja salvar o estado do jogo:
   Exemplo : *./jogo_20_perguntas arquivo_entrada.txt arquivo_saida.txt*

  Nao é possível rodar o jogo sem um arquivo de árvore válido.
