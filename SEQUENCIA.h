#if ! defined( SEQUENCIA )
#define SEQUENCIA
/***************************************************************************
*
*  $MCD Módulo de definição: SEQ Sequencia
*
*  Arquivo gerado:              SEQUENCIA.h
*  Letras identificadoras:      SEQ
*
*  Nome da base de software:   
*  Arquivo da base de software:
*
*  Projeto: INF 1301 / Paciência Spider
*  Gestor:  
*  Autores: thk, adp, ilg
*
*  $HA Histórico de evolução:
*     Versão  Autor    Data			Observações
*	  4		  thk	25/maio/2015	finalizado para entrega3
*	  3       thk   28/abr/2015		mudança das condiçoes de retorno
*	  2		  thk   27/abr/2015		implentacao de novas funçoes
*	  1		  thk   27/abr/2015		inicio desenvolvimento
*
*  $ED Descrição do módulo
*	Modulo implementa estrutura para uma sequência de cartas, pode-se existir
*
*
*
***************************************************************************/
#if defined( SEQUENCIA_OWN )
   #define SEQUENCIA_EXT
#else
   #define SEQUENCIA_EXT extern
#endif
#include "PILHACARTAS.h"


/***** Declarações exportadas pelo módulo *****/

/* Tipo referência para uma lista */
typedef struct SEQ_tagSequencia * SEQ_tpSequencia;

/***********************************************************************
*
*  $TC Tipo de dados: SEQ Condições de retorno
*
*
*  $ED Descrição do tipo
*     Condições de retorno das funções da sequência
*
***********************************************************************/

typedef enum {

         SEQ_CondRetOK ,
               /* Concluiu corretamente */

         SEQ_CondRetFaltouMemoria,
               /* Faltou memória ao tentar criar um elemento da sequencia */

		SEQ_CondRetSeqVazia,
			  /*Sequencia não tem cartas */

		SEQ_CondRetMovimentoInvalido,
			  /* Não conseguiu mover cartas para sequência */

		 SEQ_CondRetSeqNaoCompleta,
			 /*	Não completou uma sequência final	*/

		 SEQ_CondRetSeqNaoExiste,
			 /*	Sequência que se quis manipular não existe	*/

   } SEQ_tpCondRet ;



/***********************************************************************
*
*  $FC Função: SEQ  &Criar Sequencia
*
*  $ED Descrição da função
*     Cria uma sequencia de jogo, com uma pilha de cartas encapsulada vazia.
*
*  $EP Parâmetros
*     pSequencia  - Referencia para criar a sequencia
*                    
*
*  $FV Valor retornado
*	  SEQ_CondRetFaltouMemoria
*	  SEQ_CondRetOK
*
*     Assertivas de entrada:
*     - É esperado que o endereço de ponteiro para a sequência seja válido
*     Assertivas de saída:
*     - O espaço de memória para Sequência foi alocado com êxito
*
***********************************************************************/

SEQ_tpCondRet SEQ_CriarSequencia (SEQ_tpSequencia *pSequencia);

/***********************************************************************
*
*  $FC Função: SEQ  &Destruir Sequencia
*
*  $ED Descrição da função
*     Destroi a sequencia de jogo passada sem esvaziar a sua pilha de cartas.
*
*  $EP Parâmetros
*     pSequencia  - Ponteiro para a sequencia.
*                    
*
*  $FV Valor retornado
*	  SEQ_CondRetSeqNaoExiste - pSequencia == NULL
*	  SEQ_CondRetOK
*
*     Assertivas de entrada:
*     - É esperado que o ponteiro para a sequência seja válido
*     Assertivas de saída:
*     - Sequência foi destruida com êxito
*
***********************************************************************/
SEQ_tpCondRet SEQ_DestruirSequencia (SEQ_tpSequencia pSequencia);

/***********************************************************************
*
*  $FC Função: SEQ  &Esvaziar Sequencia
*
*  $ED Descrição da função
*     Esvazia a sequencia de jogo passada sem destruir a cabeca da sequencia.
*
*  $EP Parâmetros
*     pSequencia  - Ponteiro para a sequencia.
*                    
*
*  $FV Valor retornado
*	  SEQ_CondRetSeqNaoExiste - pSequencia == NULL
*	  SEQ_CondRetOK
*
*     Assertivas de entrada:
*     - É esperado que o ponteiro para a sequência seja válido
*     Assertivas de saída:
*     - Sequência foi esvaziada com êxito
*
***********************************************************************/

SEQ_tpCondRet SEQ_EsvaziarSequencia(SEQ_tpSequencia pSequencia);

/***********************************************************************
*
*  $FC Função: SEQ  &Iniciar Sequencia
*
*  $ED Descrição da função
*	  Inicia a sequencia adicionando uma pilha de cartas, indepedente das regras do jogo.
*
*  $EP Parâmetros
*     pSequencia  - Ponteiro para a sequencia.
*     pPilha -		Ponteiro para pilha de cartas
*	  tam -			Quantidade de cartas da pilha a ser adicionada em sequência
*
*  $FV Valor retornado
*	  SEQ_CondRetSeqNaoExiste - pSequencia == NULL
*	  SEQ_CondRetOK
*	  SEQ_CondRetMovimentoInvalido - caso a pilha seja menor que tam
*	  SEQ_CondRetFaltouMemoria
*
*     Assertivas de entrada:
*     - É esperado que o ponteiro para a sequência seja válido
*     - É esperado que a pilha esteja válida
*     - tam pode variar entre 5 ou 6
*     Assertivas de saída:
*     - Sequência recebeu com êxito uma Pilha
*
***********************************************************************/

SEQ_tpCondRet SEQ_IniciarSequencia (SEQ_tpSequencia pSequencia, PIL_tpPilha pPilha,int tam);

/***********************************************************************
*
*  $FC Função: SEQ  &Adicionar Pilha Em Sequencia
*
*  $ED Descrição da função
*     Adiciona a pilha em na sequencia de acordo com as regras do
*	  jogo Paciência Spider, não é verificado se a pilha passada é uma pilha valida (sequencia do mesmo naipe)
*	  essa condição é garantida pela SEQ Obter Pilha Cartas
*
*  $EP Parâmetros
*     pSequencia  - Ponteiro para a sequencia.
*     pPilha - Ponteiro para pilha de cartas.
*	  tam - quantidade de cartas da pilha a ser adicionada na sequência.
*
*  $FV Valor retornado
*	  SEQ_CondRetSeqNaoExiste - pSequencia == NULL
*	  SEQ_CondRetOK
*	  SEQ_CondRetMovimentoInvalido - caso o movimento não satisfaça as regras
*	  SEQ_CondRetFaltouMemoria
*
*     Assertivas de entrada:
*     - É esperado que o ponteiro para a sequência seja válido
*     - É esperado que a pilha esteja válida
*     Assertivas de saída:
*     - Sequência recebeu com êxito uma Pilha
*
*
***********************************************************************/

SEQ_tpCondRet SEQ_AdicionarPilhaEmSequencia (SEQ_tpSequencia pSequencia, PIL_tpPilha pPilha,int tam);

/***********************************************************************
*
*  $FC Função: SEQ  &Verificar Sequencia Completa
*
*  $ED Descrição da função
*	  Verifica se a sequência passada completou uma sequência completa(ou final)
*
*  $EP Parâmetros
*     pSequencia  - Ponteiro para a sequencia.
*
*  $FV Valor retornado
*	  SEQ_CondRetOK - completou a sequencia final
*	  SEQ_CondRetSeqNaoExiste
*	  SEQ_CondRetSeqNaoCompleta
*
*     Assertivas de entrada:
*     - É esperado que o ponteiro para a sequência seja válido
*     Assertivas de saída:
*     - foi verificado se a sequência foi completa
*
***********************************************************************/

SEQ_tpCondRet SEQ_VerificarSequenciaCompleta ( SEQ_tpSequencia pSequencia);

/***********************************************************************
*
*  $FC Função: SEQ  &Obter Pilha Cartas
*
*  $ED Descrição da função
*	 Cria uma sub pilha de cartas de sequência para movimentação.
*	 Só pode remover uma pilha de cartas que obedece as regras de paciência spider;
*	 ( Cartas em sequencia de valor e mesmo naipe)
*
*  $EP Parâmetros
*     pSequencia  - Ponteiro para a sequencia.
*	  pPilha - Ponteiro para endereço de pilha.
*	  tam - tamanho da pilha a ser removida de sequencia
*
*  $FV Valor retornado
*	  SEQ_CondRetOK 
*	  SEQ_CondRetMovimentoInvalido
*	  SEQ_CondRetSeqNaoExiste
*
*     Assertivas de entrada:
*     - É esperado que o ponteiro para a sequência seja válido
*     - É esperado que a pilha esteja vazia e válida
*     - É esperado que o tam seja menor ou igual ao tamanho da sequência
*     Assertivas de saída:
*     - pPilha carta recebeu com êxito um subconjunto da sequência
*
***********************************************************************/

SEQ_tpCondRet SEQ_ObterPilhaCartas ( SEQ_tpSequencia pSequencia,PIL_tpPilha *pPilha, int tam);

/***********************************************************************
*
*  $FC Função: SEQ  &Verificar Virar Carta
*
*  $ED Descrição da função
*	  Verifica se a ultima carta de sequencia está virada (invisivel) logo deve ser virada, e a vira (torna visivel).
*	
*
*  $EP Parâmetros
*     pSequencia  - Ponteiro para a sequencia.
*
*  $FV Valor retornado
*	  SEQ_CondRetOK 
*	  SEQ_CondRetMovimentoInvalido
*	  SEQ_CondRetSeqNaoExiste
*
*     Assertivas de entrada:
*     - É esperado que o ponteiro para a sequência seja válido
*     Assertivas de saída:
*     - a última carta da sequência deve se tornar visível
*
***********************************************************************/
SEQ_tpCondRet SEQ_VerificarVirarCarta ( SEQ_tpSequencia pSequencia);

/***********************************************************************
*
*  $FC Função: SEQ  &Tornar Ultima Invisivel
*
*  $ED Descrição da função
*	  Torna a primeira carta visivel em invisivel, caso haja alguma.
*	
*
*  $EP Parâmetros
*     pSequencia  - Ponteiro para a sequencia.
*
*  $FV Valor retornado
*	  SEQ_CondRetOK 
*	  SEQ_CondRetMovimentoInvalido
*	  SEQ_CondRetSeqNaoExiste
*
*     Assertivas de entrada:
*     - É esperado que o ponteiro para a sequência seja válido
*     Assertivas de saída:
*     - a última carta da sequência deve se tornar visível
*
***********************************************************************/

SEQ_tpCondRet SEQ_TornarUltimaInvisivel ( SEQ_tpSequencia pSequencia);

/***********************************************************************
*
*  $FC Função: SEQ  &Imprimir Sequencia
*
*  $ED Descrição da função
*	  Imprime a Sequencia
*	
*
*  $EP Parâmetros
*     pSequencia  - Ponteiro para a sequencia.
*
*  $FV Valor retornado
*	  SEQ_CondRetOK 
*	  SEQ_CondRetSeqVazia
*	  SEQ_CondRetSeqNaoExiste
*
*     Assertivas de entrada:
*     - É esperado que o ponteiro para a sequência seja válido
*     Assertivas de saída:
*     - A sequencia foi imprimida.
*
***********************************************************************/

SEQ_tpCondRet SEQ_ImprimirSequencia(SEQ_tpSequencia pSequencia);

/***********************************************************************
*
*  $FC Função: SEQ  &Retornar Pilha Sequencia
*
*  $ED Descrição da função
*	  Retorna a pilha de cartas de sequencia
*	
*
*  $EP Parâmetros
*     pSequencia  - Ponteiro para a sequencia.
*	  pPilha - ponteiro para pilha
*
*  $FV Valor retornado
*	  SEQ_CondRetOK 
*	  SEQ_CondRetSeqNaoExiste
*	  SEQ_CondRetFaltouMemoria
*
*     Assertivas de entrada:
*     - É esperado que o ponteiro para a sequência seja válido e de pilha vazio
*     Assertivas de saída:
*     - pPilha contem a pilha de sequencia e sequencia está vazia
*
***********************************************************************/
SEQ_tpCondRet SEQ_RetornarPilhaSequencia(SEQ_tpSequencia pSequencia, PIL_tpPilha *pPilha);


#undef SEQUENCIA_EXT

/********** Fim do módulo de definição: SEQ  Sequencia **********/
#else
#endif
