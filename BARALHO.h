#if ! defined( BARALHO_ )
#define BARALHO_
/***************************************************************************
*
*  $MCD M�dulo de defini��o: BAR Baralho
*
*  Arquivo gerado:              BARALHO.h
*  Letras identificadoras:      BAR
*
*  Nome da base de software:   Paci�ncia Spider
*  Arquivo da base de software:
*
*  Projeto: INF 1301 / Paci�ncia Spider
*  Gestor:  
*  Autores: thk, adp, ilg
*
*  $HA Hist�rico de evolu��o:
*     Vers�o  Autor    Data     Observa��es
*	  2		  thk	28/abr/2015 ajuste em erros
*     1       thk   16/abr/2015 in�cio desenvolvimento
*
*  $ED Descri��o do m�dulo
*     Implementa uma estrtura de baralho usando pilhas de carta e carta.
*
*
*
***************************************************************************/

#if defined( BARALHO_OWN )
   #define BARALHO_EXT
#else
   #define BARALHO_EXT extern
#endif

#include "PILHACARTAS.h"

/***** Declara��es exportadas pelo m�dulo *****/


/* Tipo refer�ncia para um baralho */
typedef struct BAR_tagBaralho * BAR_tpBaralho;


/***********************************************************************
*
*  $TC Tipo de dados: BAR Condi��es de retorno
*
*
*  $ED Descri��o do tipo
*     Condi��es de retorno das fun��es do baralho
*
***********************************************************************/
typedef enum {

         BAR_CondRetOK ,
               /* Concluiu corretamente */

         BAR_CondRetBaralhoNaoExiste,
               /* Baralho Inexistente */

		 BAR_CondRetFaltouMemoria,
			  /* Faltou Memoria */

		 BAR_CondRetBaralhoInsuficiente,
			/* Tentou pegar quantidade de cartas maior que a quantidade no baralho */

		 BAR_CondRetQuantidadeInvalida
			/* Quantidade de baralhos ou de naipes invalida */


   } BAR_tpCondRet ;


/***********************************************************************
*
*  $FC Fun��o: BAR  &Criar Baralho
*
*  $ED Descri��o da fun��o
*		Cria um baralho, seus dados devem ser passados para cria��o.
*
*  $EP Par�metros
*     pBaralho - Endere�o de ponteiro para um baralho
*
*  $FV Valor retornado
*     BAR_CondRetOk - se a fun��o funcionar perfeitamente
*     BAR_CondRetFaltouMemoria - se faltou mem�ria para criar o baralho
*     N�o ser� dada mais informa��o quanto ao problema ocorrido.
*
*     Assertivas de entrada: 
*     - � esperado que o endere�o de ponteiro seja v�lido
*     - � esperado que possua espa�o na mem�ria
*     Assertivas de sa�da:
*     - O baralho foi criada com sucesso
*
***********************************************************************/
BAR_tpCondRet BAR_CriarBaralho (BAR_tpBaralho * pBaralho);

/***********************************************************************
*
*  $FC Fun��o: BAR  &Destruir Baralho
*
*  $ED Descri��o da fun��o
*		Destr�i um baralho, seus dados devem ser passados para destrui��o.
*
*  $EP Par�metros
*     pBaralho -Ponteiro para um baralho
*
*  $FV Valor retornado
*     BAR_CondRetOk - se a fun��o funcionar perfeitamente
*     BAR_CondRetBaralhoNaoExiste - caso pBaralho == NULL
*     N�o ser� dada mais informa��o quanto ao problema ocorrido.
*
*     Assertivas de entrada: 
*     - � esperado que o ponteiro seja v�lido
*     Assertivas de sa�da:
*     - O espa�o de mem�ria do baralho tenha sido desalocado com sucesso
*
***********************************************************************/
BAR_tpCondRet BAR_DestruirBaralho(BAR_tpBaralho pBaralho);

/***********************************************************************
*
*  $FC Fun��o: BAR  &Esvaziar Baralho
*
*  $ED Descri��o da fun��o
*		Esvazia um baralho, seus dados devem ser passados para esvaziar.
*
*  $EP Par�metros
*     pBaralho -Ponteiro para um baralho
*
*  $FV Valor retornado
*     BAR_CondRetOk - se a fun��o funcionar perfeitamente
*     BAR_CondRetBaralhoNaoExiste - caso pBaralho == NULL
*     N�o ser� dada mais informa��o quanto ao problema ocorrido.
*
*     Assertivas de entrada: 
*     - � esperado que o ponteiro seja v�lido
*     Assertivas de sa�da:
*     - o espa�o alocado pelo pBaralho tenha recebido NULL
*
***********************************************************************/

BAR_tpCondRet BAR_EsvaziarBaralho (BAR_tpBaralho pBaralho);

/***********************************************************************
*
*  $FC Fun��o: BAR  &iniciar Baralho
*
*  $ED Descri��o da fun��o
*		Inicia(embaralha) os dois baralhos, seus dados devem ser passados para o embaralhamento.
*
*  $EP Par�metros
*     pBaralho -Ponteiro para um baralho
*     qtdBaralhos - quantidade de baralhos que ser�o usados
*     qtdNaipes - quantidade de naipes que ser�o usados no embaralhamento
*
*  $FV Valor retornado
*     BAR_CondRetOk - se a fun��o funcionar perfeitamente
*     BAR_CondRetBaralhoNaoExiste - caso pBaralho == NULL
*     BAR_CondRetFaltouMemoria - caso falte mem�ria para alocar o baralho
*     N�o ser� dada mais informa��o quanto ao problema ocorrido.
*
*     Assertivas de entrada: 
*     - � esperado que o ponteiro para o baralho seja v�lido
*     - Quantidade de baralhos � esperado que seja 2 (104 cartas)
*     - Quantidade de naipes � esperado que seja v�lida (de 1 a 4 naipes)
*     Assertivas de sa�da:
*     - O baralho formado com 104 cartas est� embaralhado
*
***********************************************************************/

BAR_tpCondRet BAR_IniciarBaralho (BAR_tpBaralho pBaralho, int qtdBaralhos, int qtdNaipes);

/***********************************************************************
*
*  $FC Fun��o: BAR  &Criar SubPilha Baralho
*
*  $ED Descri��o da fun��o
*		Cria uma subpilha de um baralho, seus dados devem ser passados para cria��o.
*
*  $EP Par�metros
*     pBaralho -Ponteiro para um baralho
*     pPilha - Endere�o de ponteiro para uma pilha de cartas
*     tam - tamanho exato da subpilha
*
*  $FV Valor retornado
*     BAR_CondRetOk - se a fun��o funcionar perfeitamente
*     BAR_CondRetBaralhoNaoExiste - caso pBaralho == NULL
*     BAR_CondRetFaltouMemoria - caso falte mem�ria para alocar o baralho
*     BAR_CondRetBaralhoInsuficiente - caso o baralho seja menor que a subpilha
*     N�o ser� dada mais informa��o quanto ao problema ocorrido.
*
*     Assertivas de entrada: 
*     - � esperado que o ponteiro para o baralho seja v�lido
*     - � esperado que o ponteiro para a pilha de cartas seja v�lido
*     - Quantidade de naipes � esperado que seja v�lida (de 1 a 4 naipes)
*     Assertivas de sa�da:
*     - A subpilha passa a possuir um subconjunto de um baralho
*
***********************************************************************/
BAR_tpCondRet BAR_CriarSubPilhaBaralho (BAR_tpBaralho pBaralho, PIL_tpPilha * pPilha, int tam) ;


/***********************************************************************
*
*  $FC Fun��o: BAR  &Imprimir Baralho
*
*  $ED Descri��o da fun��o
*		Imprime a pilha de cartas do baralho
*
*  $EP Par�metros
*     pBaralho -Ponteiro para um baralho
*
*  $FV Valor retornado
*     BAR_CondRetOk - se a fun��o funcionar perfeitamente
*     BAR_CondRetBaralhoNaoExiste - caso pBaralho == NULL
*     BAR_CondRetBaralhoVazio
*
*     Assertivas de entrada: 
*     - � esperado que o ponteiro seja v�lido para um baralho com uma pilha de cartas com cartas
*     Assertivas de sa�da:
*     - O baralho foi imprimido com sucesso
*
***********************************************************************/
BAR_tpCondRet BAR_ImprimirBaralho(BAR_tpBaralho pBaralho);

#undef BARALHO_EXT

/********** Fim do m�dulo de defini��o: BAR  Baralho **********/



#else
#endif