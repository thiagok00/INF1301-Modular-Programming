#if ! defined( PILHACARTAS_ )
#define PILHACARTAS_

/***************************************************************************
*
*  $MCD M�dulo de defini��o: PIL Pilha Cartas
*
*  Arquivo gerado:              PILHACARTAS.h
*  Letras identificadoras:      PIL
*
*  Nome da base de software:   Paci�ncia Spider
*  Arquivo da base de software:
*
*  Projeto: INF 1301 / Paci�ncia Spider
*  Gestor:  
*  Autores: thk, adp, ilg
*
*  $HA Hist�rico de evolu��o:
*     Vers�o  Autor    Data			Observa��es
*	  4		  thk	25/maio/2015	finalizado para entrega3
*	  3       thk   28/abr/2015		mudan�a de retorno de fun�oes
*	  2		  thk   27/abr/2015		implentacao de novas fun�oes
*	  1		  thk   25/abr/2015		inicio desenvolvimento
*
*  $ED Descri��o do m�dulo
*     Implementa estrutura para uma pilha de cartas 
*     Podem existir n pilhas de cartas em opera��o simultaneamente.
*     As pilhas possuem uma cabe�a encapsulando o seu estado.
*	  � possivel percorrer a pilha de cartas, adicionar e remover cartas.
*	  
*
*
***************************************************************************/
#if defined( PILHACARTAS_OWN )
   #define PILHACARTAS_EXT
#else
   #define PILHACARTAS_EXT extern
#endif


#include "CARTA.h"
/***** Declara��es exportadas pelo m�dulo *****/

/* Tipo refer�ncia para uma pilha de cartas */
typedef struct PIL_tagPilha * PIL_tpPilha;

/***********************************************************************
*
*  $TC Tipo de dados: PIL Condi��es de retorno
*
*
*  $ED Descri��o do tipo
*     Condi��es de retorno das fun��es da pilha de cartas
*
***********************************************************************/

typedef enum {

         PIL_CondRetOK ,
               /* Concluiu corretamente */

         PIL_CondRetPilhaVazia ,
			   /* A pilha est� vazia */
		 
         PIL_CondRetFimPilha ,
               /* Foi atingido o fim da pilha */

         PIL_CondRetPilhaNaoExiste ,
               /* Tentou manipular pilha n�o existente */

         PIL_CondRetFaltouMemoria,
               /* Faltou mem�ria ao alocar uma estutura (pilha ou carta) */

		 PIL_CondRetCartaNaoExiste
			   /* A carta manipilada n�o existe */

   } PIL_tpCondRet ;


/***********************************************************************
*
*  $FC Fun��o: PIL  &Criar PilhaCartas
*
*  $ED Descri��o da fun��o
*     Cria uma pilha de cartas.
*
*  $EP Par�metros
*     pPilha  - Endere�o de ponteiro para a pilha de cartas.
*                    
*
*  $FV Valor retornado
*     PIL_CondRetOk - Se executou corretamente.
*     PIL_CondRetFaltouMemoria - Se ocorreu falta de mem�ria
*     N�o ser� dada mais informa��o quanto ao problema ocorrido.
*
*     Assertivas de entrada:
*     - � esperado que o endere�o de ponteiro para a pilha seja v�lido
*     Assertivas de sa�da:
*     - Espa�o para a pilha foi alocado com �xito
*
***********************************************************************/

PIL_tpCondRet PIL_CriarPilhaCartas (PIL_tpPilha *pPilha);


/***********************************************************************
*
*  $FC Fun��o: PIL  &Destruir PilhaCartas
*
*  $ED Descri��o da fun��o
*     Destr�i a cabeca pilha de cartas passada sem destruir as cartas nela contida;
*
*  $EP Par�metros
*     pPilha  - ponteiro para a pilha de cartas.
*                    
*
*  $FV Valor retornado
*     PIL_CondRetOk - Se executou corretamente.
*     PIL_CondRetPilhaNaoExiste - se a pilha passada como par�metro n�o existe
*     PIL_CondRetPilhaVazia - caso a pilha esteja vazia
*     N�o ser� dada mais informa��o quanto ao problema ocorrido.
*
*     Assertivas de entrada:
*     - � esperado que o ponteiro da pilha seja v�lido
*     Assertivas de sa�da:
*     - Espa�o para a pilha foi desalocado com �xito
*
***********************************************************************/
PIL_tpCondRet PIL_DestruirPilhaCartas (PIL_tpPilha pPilha);


/***********************************************************************
*
*  $FC Fun��o: PIL  &Esvaziar PilhaCartas
*
*  $ED Descri��o da fun��o
*     Esvazia a pilha de cartas, destruindo todas as cartas nela.
*	  Sem destruir a cabe�a da pilha.
*
*  $EP Par�metros
*     pPilha  - ponteiro para a pilha de cartas.
*                    
*  $FV Valor retornado
*     PIL_CondRetOk - Se executou corretamente.
*     PIL_CondRetPilhaNaoExiste - se a pilha passada como par�metro n�o existe
*     PIL_CondRetPilhaVazia - caso a pilha esteja vazia
*     N�o ser� dada mais informa��o quanto ao problema ocorrido.
*
*     Assertivas de entrada:
*     - � esperado que o ponteiro da pilha seja v�lido
*     Assertivas de sa�da:
*     - Espa�o para a pilha recebeu NULL,ou seja, foi esvaziado corretamente
*
***********************************************************************/
PIL_tpCondRet PIL_EsvaziarPilhaCartas(PIL_tpPilha pPilha);

/***********************************************************************
*
*  $FC Fun��o: PIL  &Avan�ar Elemento Corrente
*
*  $ED Descri��o da fun��o
*     Recebe numero de elementos (cartas) a se avan�ar na pilha.
*
*  $EP Par�metros
*     pPilha  - ponteiro para a pilha de cartas.
*     numElem - inteiro indicando quantas cartas ir� "andar" na pilhh de cartas
*
*  $FV Valor retornado
*     PIL_CondRetOk - Se executou corretamente.
*     PIL_CondRetPilhaNaoExiste - se a pilha passada como par�metro n�o existe
*     PIL_CondRetPilhaVazia - caso a pilha esteja vazia 
*     PIL_CondRetFimPilha - se chegou ao final da pilha
*     N�o ser� dada mais informa��o quanto ao problema ocorrido.
*     
*     Assertivas de entrada:
*     - � esperado que o ponteiro da pilha seja v�lido
*     - � esperado que o n�mero de elemento n�o ultrapasse o "tamanho" da pilha
*     Assertivas de sa�da:
*     - O ponteiro passou a apontar para outro n� da pilha
*
***********************************************************************/
PIL_tpCondRet PIL_AvancarElementoCorrente( PIL_tpPilha pPilha ,int numElem );

/***********************************************************************
*
*  $FC Fun��o: PIL  &Ver Carta
*
*  $ED Descri��o da fun��o
*      Obtem a refer�ncia para a carta corrente da pilha de cartas, n�o a remove da pilha.
*
*  $EP Par�metros
*     pPilha  - ponteiro para a pilha de cartas.
*     pCarta - Endere�o de ponteiro para uma estrutura carta
*
*  $FV Valor retornado
*     PIL_CondRetOk - Se executou corretamente.
*     PIL_CondRetPilhaNaoExiste - se a pilha passada como par�metro n�o existe
*     PIL_CondRetPilhaVazia - caso a pilha esteja vazia
*     N�o ser� dada mais informa��o quanto ao problema ocorrido.
*     
*     Assertivas de entrada:
*     - � esperado que o ponteiro da pilha seja v�lido
*     - � esperado que o endere�o de ponteiro para a carta seja v�lido
*     Assertivas de sa�da:
*     - Foi poss�vel obter o valor da carta em quest�o
*
*
***********************************************************************/
PIL_tpCondRet PIL_VerCarta( PIL_tpPilha pPilha , CAR_tpCarta * pCarta );

/***********************************************************************
*
*  $FC Fun��o: PIL  &Adicionar Carta
*
*  $ED Descri��o da fun��o
*     Adiciona uma carta a uma pilha de cartas ( a carta ser� inserido antes corrente )
*
*  $EP Par�metros
*     pPilha  - ponteiro para a pilha de cartas.
*     carta - ponteiro para uma estrutura carta
*
*  $FV Valor retornado
*     PIL_CondRetOk - Se executou corretamente.
*     PIL_CondRetPilhaNaoExiste - se a pilha passada como par�metro n�o existe
*     PIL_CondRetFaltouMemoria  - se faltou mem�ria 
*     N�o ser� dada mais informa��o quanto ao problema ocorrido.
*     
*     Assertivas de entrada:
*     - � esperado que o ponteiro da pilha seja v�lido
*     - � esperado que o eponteiro da carta seja v�lido
*     Assertivas de sa�da:
*     - Foi poss�vel adicionar a carta na pilha quest�o
*
***********************************************************************/
PIL_tpCondRet PIL_AdicionarCarta (PIL_tpPilha pPilha, CAR_tpCarta carta);

/***********************************************************************
*
*  $FC Fun��o: PIL  &Imprimir Pilha Cartas
*
*  $ED Descri��o da fun��o
*     Imprime a pilha de cartas que recebe como par�metros.
*	  O ultimo elemento da pilha de cartas � o primeiro imprimido.
*
*  $EP Par�metros
*     pPilha  - ponteiro para a pilha de cartas.
*
*  $FV Valor retornado
*     PIL_CondRetOk - Se executou corretamente.
*     PIL_CondRetPilhaNaoExiste - se a pilha passada como par�metro n�o existe
*     PIL_CondRetPilhaVazia - caso a pilha esteja vazia 
*     N�o ser� dada mais informa��o quanto ao problema ocorrido.
*     
*     Assertivas de entrada:
*     - � esperado que o ponteiro da pilha seja v�lido
*     Assertivas de sa�da:
*     - Foi poss�vel imprimir a pilha em quest�o
*
***********************************************************************/
PIL_tpCondRet PIL_ImprimirPilhaCartas (PIL_tpPilha pPilha);

/***********************************************************************
*
*  $FC Fun��o: PIL  &Ir FinalPilha
*
*  $ED Descri��o da fun��o
*     Vai para o final da pilha de cartas
*
*  $EP Par�metros
*     pPilha  - ponteiro para a pilha de cartas.
*
*  $FV Valor retornado
*     PIL_CondRetOk - Se executou corretamente.
*     PIL_CondRetPilhaNaoExiste - se a pilha passada como par�metro n�o existe
*     N�o ser� dada mais informa��o quanto ao problema ocorrido.
*     
*     Assertivas de entrada:
*     - � esperado que o ponteiro da pilha seja v�lido
*     Assertivas de sa�da:
*     - O ponteiro passou a apontar para o final da pilha em quest�o
*
***********************************************************************/

PIL_tpCondRet PIL_IrFinalPilhaCartas( PIL_tpPilha pPilha );

/***********************************************************************
*
*  $FC Fun��o: PIL  &Ir InicioPilha
*
*  $ED Descri��o da fun��o
*     Vai para o in�cio da pilha de cartas
*
*  $EP Par�metros
*     pPilha  - ponteiro para a pilha de cartas.
*
*  $FV Valor retornado
*     PIL_CondRetOk - Se executou corretamente.
*     PIL_CondRetPilhaNaoExiste - se a pilha passada como par�metro n�o existe
*     N�o ser� dada mais informa��o quanto ao problema ocorrido.
*     
*     Assertivas de entrada:
*     - � esperado que o ponteiro da pilha seja v�lido
*     Assertivas de sa�da:
*     - O ponteiro passou a apontar para o in�cio da pilha em quest�o
*
***********************************************************************/

PIL_tpCondRet PIL_IrInicioPilhaCartas( PIL_tpPilha pPilha );

/***********************************************************************
*
*  $FC Fun��o: PIL  &Remover Carta
*
*  $ED Descri��o da fun��o
*     Remove uma carta da pilha de cartas obtendo-se a referencia para ela
*
*  $EP Par�metros
*     pPilha - ponteiro para a pilha de cartas a qual ser� removida a carta.
*     pCarta - Endere�o de ponteiro para a carta
*
*  $FV Valor retornado
*     PIL_CondRetOk - Se executou corretamente.
*	  PIL_CondRetFaltouMemoria - caso falte mem�ria para a cria��o da carta auxiliar
*     PIL_CondRetPilhaNaoExiste - se a pilha passada como par�metro n�o existe
*     PIL_CondRetPilhaVazia - se a pilha origem estiver vazia
*     N�o ser� dada mais informa��o quanto ao problema ocorrido.
*     
*     Assertivas de entrada:
*     - � esperado que o ponteiro da pilha seja v�lido
*     - � esperado que o endere�o de ponteiro para a carta seja v�lido
*     Assertivas de sa�da:
*     - A carta foi removida da pilha de cartas com sucesso
*
***********************************************************************/

PIL_tpCondRet PIL_RemoverCarta( PIL_tpPilha pPilha , CAR_tpCarta * pCarta );

/***********************************************************************
*
*  $FC Fun��o: PIL  &Tornar Carta Invisivel
*
*  $ED Descri��o da fun��o
*     Torna a carta corrente invisivel
*
*  $EP Par�metros
*     pPilha - ponteiro para a pilha de cartas.
*
*  $FV Valor retornado
*     PIL_CondRetOk - Se executou corretamente.
*	  PIL_CondRetPilhaNaoExiste
*     
*     Assertivas de entrada:
*     - � esperado que o ponteiro da pilha seja v�lido
*     - � esperado que a pilha n�o seja vazia
*     Assertivas de sa�da:
*     - A carta foi tornada invisivel
*
***********************************************************************/

PIL_tpCondRet PIL_TornarCartaVisivel( PIL_tpPilha pPilha);

/***********************************************************************
*
*  $FC Fun��o: PIL  &Tornar Carta Visivel
*
*  $ED Descri��o da fun��o
*     Torna a carta corrente visivel
*
*  $EP Par�metros
*     pPilha - ponteiro para a pilha de cartas.
*
*  $FV Valor retornado
*     PIL_CondRetOk - Se executou corretamente.
*	  PIL_CondRetPilhaNaoExiste
*     
*     Assertivas de entrada:
*     - � esperado que o ponteiro da pilha seja v�lido
*     - � esperado que a pilha n�o seja vazia
*     Assertivas de sa�da:
*     - A carta foi tornada visivel
*
***********************************************************************/
PIL_tpCondRet PIL_TornarCartaInvisivel( PIL_tpPilha pPilha);

/***********************************************************************
*
*  $FC Fun��o: PIL  &Quantidade Cartas
*
*  $ED Descri��o da fun��o
*     Retorna a quantidade de cartas na pilha por parametro
*
*  $EP Par�metros
*     pPilha - ponteiro para a pilha de cartas.
*	  qtd - ponteiro para o valor quantidade
*
*  $FV Valor retornado
*     PIL_CondRetOk - Se executou corretamente.
*	  PIL_CondRetPilhaNaoExiste - pPilha == NULL
*     
*     Assertivas de entrada:
*     - � esperado que o ponteiro da pilha seja v�lido
*     Assertivas de sa�da:
*     - Valor em qtd corresponde a quantidade de cartas da pilha
*
***********************************************************************/

PIL_tpCondRet PIL_QuantidadeCartas(PIL_tpPilha pPilha, int *qtd);

#undef PILHACARTAS_EXT

/********** Fim do m�dulo de defini��o: PIL Pilha **********/

#else
#endif
