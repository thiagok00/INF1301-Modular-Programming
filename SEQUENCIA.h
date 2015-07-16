#if ! defined( SEQUENCIA )
#define SEQUENCIA
/***************************************************************************
*
*  $MCD M�dulo de defini��o: SEQ Sequencia
*
*  Arquivo gerado:              SEQUENCIA.h
*  Letras identificadoras:      SEQ
*
*  Nome da base de software:   
*  Arquivo da base de software:
*
*  Projeto: INF 1301 / Paci�ncia Spider
*  Gestor:  
*  Autores: thk, adp, ilg
*
*  $HA Hist�rico de evolu��o:
*     Vers�o  Autor    Data			Observa��es
*	  4		  thk	25/maio/2015	finalizado para entrega3
*	  3       thk   28/abr/2015		mudan�a das condi�oes de retorno
*	  2		  thk   27/abr/2015		implentacao de novas fun�oes
*	  1		  thk   27/abr/2015		inicio desenvolvimento
*
*  $ED Descri��o do m�dulo
*	Modulo implementa estrutura para uma sequ�ncia de cartas, pode-se existir
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


/***** Declara��es exportadas pelo m�dulo *****/

/* Tipo refer�ncia para uma lista */
typedef struct SEQ_tagSequencia * SEQ_tpSequencia;

/***********************************************************************
*
*  $TC Tipo de dados: SEQ Condi��es de retorno
*
*
*  $ED Descri��o do tipo
*     Condi��es de retorno das fun��es da sequ�ncia
*
***********************************************************************/

typedef enum {

         SEQ_CondRetOK ,
               /* Concluiu corretamente */

         SEQ_CondRetFaltouMemoria,
               /* Faltou mem�ria ao tentar criar um elemento da sequencia */

		SEQ_CondRetSeqVazia,
			  /*Sequencia n�o tem cartas */

		SEQ_CondRetMovimentoInvalido,
			  /* N�o conseguiu mover cartas para sequ�ncia */

		 SEQ_CondRetSeqNaoCompleta,
			 /*	N�o completou uma sequ�ncia final	*/

		 SEQ_CondRetSeqNaoExiste,
			 /*	Sequ�ncia que se quis manipular n�o existe	*/

   } SEQ_tpCondRet ;



/***********************************************************************
*
*  $FC Fun��o: SEQ  &Criar Sequencia
*
*  $ED Descri��o da fun��o
*     Cria uma sequencia de jogo, com uma pilha de cartas encapsulada vazia.
*
*  $EP Par�metros
*     pSequencia  - Referencia para criar a sequencia
*                    
*
*  $FV Valor retornado
*	  SEQ_CondRetFaltouMemoria
*	  SEQ_CondRetOK
*
*     Assertivas de entrada:
*     - � esperado que o endere�o de ponteiro para a sequ�ncia seja v�lido
*     Assertivas de sa�da:
*     - O espa�o de mem�ria para Sequ�ncia foi alocado com �xito
*
***********************************************************************/

SEQ_tpCondRet SEQ_CriarSequencia (SEQ_tpSequencia *pSequencia);

/***********************************************************************
*
*  $FC Fun��o: SEQ  &Destruir Sequencia
*
*  $ED Descri��o da fun��o
*     Destroi a sequencia de jogo passada sem esvaziar a sua pilha de cartas.
*
*  $EP Par�metros
*     pSequencia  - Ponteiro para a sequencia.
*                    
*
*  $FV Valor retornado
*	  SEQ_CondRetSeqNaoExiste - pSequencia == NULL
*	  SEQ_CondRetOK
*
*     Assertivas de entrada:
*     - � esperado que o ponteiro para a sequ�ncia seja v�lido
*     Assertivas de sa�da:
*     - Sequ�ncia foi destruida com �xito
*
***********************************************************************/
SEQ_tpCondRet SEQ_DestruirSequencia (SEQ_tpSequencia pSequencia);

/***********************************************************************
*
*  $FC Fun��o: SEQ  &Esvaziar Sequencia
*
*  $ED Descri��o da fun��o
*     Esvazia a sequencia de jogo passada sem destruir a cabeca da sequencia.
*
*  $EP Par�metros
*     pSequencia  - Ponteiro para a sequencia.
*                    
*
*  $FV Valor retornado
*	  SEQ_CondRetSeqNaoExiste - pSequencia == NULL
*	  SEQ_CondRetOK
*
*     Assertivas de entrada:
*     - � esperado que o ponteiro para a sequ�ncia seja v�lido
*     Assertivas de sa�da:
*     - Sequ�ncia foi esvaziada com �xito
*
***********************************************************************/

SEQ_tpCondRet SEQ_EsvaziarSequencia(SEQ_tpSequencia pSequencia);

/***********************************************************************
*
*  $FC Fun��o: SEQ  &Iniciar Sequencia
*
*  $ED Descri��o da fun��o
*	  Inicia a sequencia adicionando uma pilha de cartas, indepedente das regras do jogo.
*
*  $EP Par�metros
*     pSequencia  - Ponteiro para a sequencia.
*     pPilha -		Ponteiro para pilha de cartas
*	  tam -			Quantidade de cartas da pilha a ser adicionada em sequ�ncia
*
*  $FV Valor retornado
*	  SEQ_CondRetSeqNaoExiste - pSequencia == NULL
*	  SEQ_CondRetOK
*	  SEQ_CondRetMovimentoInvalido - caso a pilha seja menor que tam
*	  SEQ_CondRetFaltouMemoria
*
*     Assertivas de entrada:
*     - � esperado que o ponteiro para a sequ�ncia seja v�lido
*     - � esperado que a pilha esteja v�lida
*     - tam pode variar entre 5 ou 6
*     Assertivas de sa�da:
*     - Sequ�ncia recebeu com �xito uma Pilha
*
***********************************************************************/

SEQ_tpCondRet SEQ_IniciarSequencia (SEQ_tpSequencia pSequencia, PIL_tpPilha pPilha,int tam);

/***********************************************************************
*
*  $FC Fun��o: SEQ  &Adicionar Pilha Em Sequencia
*
*  $ED Descri��o da fun��o
*     Adiciona a pilha em na sequencia de acordo com as regras do
*	  jogo Paci�ncia Spider, n�o � verificado se a pilha passada � uma pilha valida (sequencia do mesmo naipe)
*	  essa condi��o � garantida pela SEQ Obter Pilha Cartas
*
*  $EP Par�metros
*     pSequencia  - Ponteiro para a sequencia.
*     pPilha - Ponteiro para pilha de cartas.
*	  tam - quantidade de cartas da pilha a ser adicionada na sequ�ncia.
*
*  $FV Valor retornado
*	  SEQ_CondRetSeqNaoExiste - pSequencia == NULL
*	  SEQ_CondRetOK
*	  SEQ_CondRetMovimentoInvalido - caso o movimento n�o satisfa�a as regras
*	  SEQ_CondRetFaltouMemoria
*
*     Assertivas de entrada:
*     - � esperado que o ponteiro para a sequ�ncia seja v�lido
*     - � esperado que a pilha esteja v�lida
*     Assertivas de sa�da:
*     - Sequ�ncia recebeu com �xito uma Pilha
*
*
***********************************************************************/

SEQ_tpCondRet SEQ_AdicionarPilhaEmSequencia (SEQ_tpSequencia pSequencia, PIL_tpPilha pPilha,int tam);

/***********************************************************************
*
*  $FC Fun��o: SEQ  &Verificar Sequencia Completa
*
*  $ED Descri��o da fun��o
*	  Verifica se a sequ�ncia passada completou uma sequ�ncia completa(ou final)
*
*  $EP Par�metros
*     pSequencia  - Ponteiro para a sequencia.
*
*  $FV Valor retornado
*	  SEQ_CondRetOK - completou a sequencia final
*	  SEQ_CondRetSeqNaoExiste
*	  SEQ_CondRetSeqNaoCompleta
*
*     Assertivas de entrada:
*     - � esperado que o ponteiro para a sequ�ncia seja v�lido
*     Assertivas de sa�da:
*     - foi verificado se a sequ�ncia foi completa
*
***********************************************************************/

SEQ_tpCondRet SEQ_VerificarSequenciaCompleta ( SEQ_tpSequencia pSequencia);

/***********************************************************************
*
*  $FC Fun��o: SEQ  &Obter Pilha Cartas
*
*  $ED Descri��o da fun��o
*	 Cria uma sub pilha de cartas de sequ�ncia para movimenta��o.
*	 S� pode remover uma pilha de cartas que obedece as regras de paci�ncia spider;
*	 ( Cartas em sequencia de valor e mesmo naipe)
*
*  $EP Par�metros
*     pSequencia  - Ponteiro para a sequencia.
*	  pPilha - Ponteiro para endere�o de pilha.
*	  tam - tamanho da pilha a ser removida de sequencia
*
*  $FV Valor retornado
*	  SEQ_CondRetOK 
*	  SEQ_CondRetMovimentoInvalido
*	  SEQ_CondRetSeqNaoExiste
*
*     Assertivas de entrada:
*     - � esperado que o ponteiro para a sequ�ncia seja v�lido
*     - � esperado que a pilha esteja vazia e v�lida
*     - � esperado que o tam seja menor ou igual ao tamanho da sequ�ncia
*     Assertivas de sa�da:
*     - pPilha carta recebeu com �xito um subconjunto da sequ�ncia
*
***********************************************************************/

SEQ_tpCondRet SEQ_ObterPilhaCartas ( SEQ_tpSequencia pSequencia,PIL_tpPilha *pPilha, int tam);

/***********************************************************************
*
*  $FC Fun��o: SEQ  &Verificar Virar Carta
*
*  $ED Descri��o da fun��o
*	  Verifica se a ultima carta de sequencia est� virada (invisivel) logo deve ser virada, e a vira (torna visivel).
*	
*
*  $EP Par�metros
*     pSequencia  - Ponteiro para a sequencia.
*
*  $FV Valor retornado
*	  SEQ_CondRetOK 
*	  SEQ_CondRetMovimentoInvalido
*	  SEQ_CondRetSeqNaoExiste
*
*     Assertivas de entrada:
*     - � esperado que o ponteiro para a sequ�ncia seja v�lido
*     Assertivas de sa�da:
*     - a �ltima carta da sequ�ncia deve se tornar vis�vel
*
***********************************************************************/
SEQ_tpCondRet SEQ_VerificarVirarCarta ( SEQ_tpSequencia pSequencia);

/***********************************************************************
*
*  $FC Fun��o: SEQ  &Tornar Ultima Invisivel
*
*  $ED Descri��o da fun��o
*	  Torna a primeira carta visivel em invisivel, caso haja alguma.
*	
*
*  $EP Par�metros
*     pSequencia  - Ponteiro para a sequencia.
*
*  $FV Valor retornado
*	  SEQ_CondRetOK 
*	  SEQ_CondRetMovimentoInvalido
*	  SEQ_CondRetSeqNaoExiste
*
*     Assertivas de entrada:
*     - � esperado que o ponteiro para a sequ�ncia seja v�lido
*     Assertivas de sa�da:
*     - a �ltima carta da sequ�ncia deve se tornar vis�vel
*
***********************************************************************/

SEQ_tpCondRet SEQ_TornarUltimaInvisivel ( SEQ_tpSequencia pSequencia);

/***********************************************************************
*
*  $FC Fun��o: SEQ  &Imprimir Sequencia
*
*  $ED Descri��o da fun��o
*	  Imprime a Sequencia
*	
*
*  $EP Par�metros
*     pSequencia  - Ponteiro para a sequencia.
*
*  $FV Valor retornado
*	  SEQ_CondRetOK 
*	  SEQ_CondRetSeqVazia
*	  SEQ_CondRetSeqNaoExiste
*
*     Assertivas de entrada:
*     - � esperado que o ponteiro para a sequ�ncia seja v�lido
*     Assertivas de sa�da:
*     - A sequencia foi imprimida.
*
***********************************************************************/

SEQ_tpCondRet SEQ_ImprimirSequencia(SEQ_tpSequencia pSequencia);

/***********************************************************************
*
*  $FC Fun��o: SEQ  &Retornar Pilha Sequencia
*
*  $ED Descri��o da fun��o
*	  Retorna a pilha de cartas de sequencia
*	
*
*  $EP Par�metros
*     pSequencia  - Ponteiro para a sequencia.
*	  pPilha - ponteiro para pilha
*
*  $FV Valor retornado
*	  SEQ_CondRetOK 
*	  SEQ_CondRetSeqNaoExiste
*	  SEQ_CondRetFaltouMemoria
*
*     Assertivas de entrada:
*     - � esperado que o ponteiro para a sequ�ncia seja v�lido e de pilha vazio
*     Assertivas de sa�da:
*     - pPilha contem a pilha de sequencia e sequencia est� vazia
*
***********************************************************************/
SEQ_tpCondRet SEQ_RetornarPilhaSequencia(SEQ_tpSequencia pSequencia, PIL_tpPilha *pPilha);


#undef SEQUENCIA_EXT

/********** Fim do m�dulo de defini��o: SEQ  Sequencia **********/
#else
#endif
