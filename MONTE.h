#if ! defined( MONTE_ )
#define MONTE_
/***************************************************************************
*
*  $MCD M�dulo de defini��o: MON Monte
*
*  Arquivo gerado:              Monte.h
*  Letras identificadoras:      MON
*
*  Nome da base de software: Paci�ncia Spider
*  Arquivo da base de software:
*
*  Projeto: INF 1301 / Paci�ncia Spider
*  Gestor:
*  Autores: thk, adp, ilg
*
*  $HA Hist�rico de evolu��o:
*     Vers�o  Autor    Data     Observa��es
*	  3       adp   29/04/2015  ajustes nos comentarios e condi��es de retorno
*	  2		  ilg	21/04/2015  t�rmino de desenvolvimento da vers�o 1
*     1       ilg   20/abr/2015 in�cio desenvolvimento
*
*
*  $ED Descri��o do m�dulo
*     Implementa o monte de cartas para compra do jogo Paci�ncia Spider
*	  O monte usa modulo de pilhas de cartas e cartas, o monte segura o ponteiro
*	  para uma pilha de cartas com 10 cartas e a disponibiliza quando necessario
*
*
***************************************************************************/

#if defined( MONTE_OWN )
   #define MONTE_EXT
#else
   #define MONTE_EXT extern
#endif

#include "PILHACARTAS.h"

/***** Declara��es exportadas pelo m�dulo *****/

/* Tipo refer�ncia para um monte */
typedef struct MON_tagMonte * MON_tpMonte;

/***********************************************************************
*
*  $TC Tipo de dados: MON Condi��es de retorno
*
*
*  $ED Descri��o do tipo
*     Condi��es de retorno das fun��es do monte de compras
*
***********************************************************************/
typedef enum {

	MON_CondRetOK,
	/* Concluiu corretamente */

	MON_CondRetMonteVazio,
	/* N�o h� cartas no monte */

	MON_CondRetMonteCheio,
	/* O monte j� cont�m 10 cartas na� nulas */

	MON_CondRetMonteNaoExiste,
	/* O monte n�o foi criado antes de requerida opera��o de trabalho sobre ele */

	MON_CondRetFaltouMemoria,
	/* Faltou mem�ria ao tentar criar monte ou adicionar pilhas a ele */

	MON_CondRetFaltamCartas
	/* Faltou cartas na hora de inicializar o monte */
} MON_tpCondRet;

/***********************************************************************
*
*  $FC Fun��o: MON  &Criar Monte Compras
*
*  $ED Descri��o da fun��o
*     Cria um monte de compras
*
*  $EP Par�metros
*	  pMonte - endere�o de ponteiro para o monte
*
*  $FV Valor retornado
*     MON_CondRetOk - se foi criado corretamente
*	  MON_CondRetFaltouMeMoria - se n�o conseguiu alocar espa�o para o tpMonte ou para tpMonte->cabeca
*
*    Assertivas de entrada:
*    - � esperado um endere�o de ponteiro v�lido para o monte
*    - � esperado que se tenha espa�o na mem�ria para ser alocado
*    Assertivas de sa�da:
*    - Espa�o de mem�ria para o monte alocado com sucesso.
*
***********************************************************************/
MON_tpCondRet MON_CriarMonteCompras(MON_tpMonte * pMonte);

/***********************************************************************
*
*  $FC Fun��o: MON  &Destruir Monte Compras
*
*  $ED Descri��o da fun��o
*     Destr�i a cabe�a do monte de compras passado como argumento.
*	  A fun��o n�o destr�i as pilhas de cartas do monte, para isso � necessario esvazi�-lo.
*
*  $EP Par�metros 
*	  pMonte - ponteiro para o monte
*
*  $FV Valor Retornado
*	  MON_CondRetMonteInexistente - se pMonte � NULL
*	  MON_CondRetMonteVazio 
*	  MON_CondRetOk - se os proccedimentos foram executados corretamente
*
*    Assertivas de entrada:
*    - � esperado um ponteiro v�lido para o monte
*    Assertivas de sa�da:
*    - Espa�o de mem�ria para o monte desalocado com sucesso.
*
***********************************************************************/

MON_tpCondRet MON_DestruirMonteCompras(MON_tpMonte pMonte);

/***********************************************************************
*
*  $FC Fun��o: MON  &Esvaziar Monte Compras
*
*  $ED Descri��o da fun��o
*     Elimina todas as pilhas de carta do monte, sem, contudo, destruir o monte em si.
*
*  $EP Par�metros
*     pMonte - ponteiro para o monte a ser esvaziado
*
*  $FV Valor Retornado
*	  MON_CondRetMonteInexistente - se pMonte � NULL
*	  MON_CondRetMonteVazio - se o monte j� est� inicialmente vazio
*	  MON_CondRetOk - se os procedimentos fora mexecutados corretamente
*
*    Assertivas de entrada:
*    - � esperado um ponteiro v�lido para o monte
*    Assertivas de sa�da:
*    - Espa�o de mem�ria para o monte recebeu NULL (esvaziou) com sucesso
*
***********************************************************************/

MON_tpCondRet MON_EsvaziarMonteCompras(MON_tpMonte pMonte);

/***********************************************************************
*
*  $FC Fun��o: MON  &Adicionar Ao Monte Compras
*
*  $ED Descri��o da fun��o
*	Adiciona pilha de cartas para o monte de compras.
*
*  $EP Par�metros
*     pCarta - ponteiro para a carta
*     pMonte - ponteiro para o monte
*
*  $FV Valor retornado
*     MON_CondRetOk - se o monte estava inicialmente vazio e foi corretamente adicionada a pilha a ele.
*	  MON_CondRetFaltouMemoria - se faltou mem�ria para a opera��o e, portanto, nao p�de ser realizada.
*	  MON_CondRetMonteCheio - se tentou adicionar pilha de cartas a um monte que j� esta preenchido.
*	  MON_CondRetMonteNaoExiste - caso cabe�a do monte seja NULL
*
*    Assertivas de entrada:
*    - � esperado um ponteiro v�lido para o monte
*    - � esperado um ponteiro v�lido para pilha de cartas com 10 cartas
*    Assertivas de sa�da:
*    - A pilha de cartas foi adicionada ao monte com sucesso
*
***********************************************************************/

MON_tpCondRet MON_AdicionarAoMonteCompras(MON_tpMonte pMonte, PIL_tpPilha pPilha);


/***********************************************************************
*
*  $FC Fun��o: MON  &Retornar Compra
*
*  $ED Descri��o da fun��o
*     Retorna o endere�o para pilha de cartas do monte.
*	  Fun��o a ser acionada quando for solicitada compra de cartas do monte.
*
*  $EP Par�metros
*     pMonte - ponteiro para o monte de compras.
*	  pPilha - ponteiro para a pilha
*
*  $FV Valor retornado
*     MON_CondRetOk - caso os procedimentos tenham sido executados corretamente.
*	  MON_CondRetMonteNaoExiste - caso pMonte seja NULL.
*	  MON_CondRetMonteVazio 
*     MON_CondRetFaltouMemoria - caso falte espa�o na mem�ria.
*
*    Assertivas de entrada:
*    - � esperado um ponteiro v�lido para o monte
*    - � esperado um ponteiro v�lido para a pilha
*    Assertivas de sa�da:
*    - A pilha foi removida do monte com sucesso
*
***********************************************************************/
MON_tpCondRet MON_RetornarCompra (MON_tpMonte pMonte, PIL_tpPilha pPilha);



/***********************************************************************
*
*  $FC Fun��o: MON  &Imprimir Monte Compra
*
*  $ED Descri��o da fun��o
*	  Imprime as cartas presentes em um monte de compras.
*
*  $EP Par�metros
*     pMonte - ponteiro para o monte de compras.
*
*  $FV Valor retornado
*     MON_CondRetOk - caso os procedimentos tenham sido executados corretamente.
*	  MON_CondRetMonteNaoExiste - caso pMonte seja NULL.
*	  MON_CondRetMonteVazio 
*
*    Assertivas de entrada:
*    - � esperado um ponteiro v�lido para o monte
*    Assertivas de sa�da:
*    - A pilha do monte foi imprimida com sucesso
*
***********************************************************************/

MON_tpCondRet MON_ImprimirMonteCompras (MON_tpMonte pMonte);

/***********************************************************************
*
*  $FC Fun��o: MON  &Monte Compras Disponivel
*
*  $ED Descri��o da fun��o
*	  Retorna se o monte esta disponivel para ser comprado
*
*  $EP Par�metros
*     pMonte - ponteiro para o monte de compras.
*
*  $FV Valor retornado
*     MON_CondRetOk - caso esteja disponivel.
*	  MON_CondRetMonteNaoExiste - caso pMonte seja NULL.
*	  MON_CondRetMonteVazio
*
*    Assertivas de entrada:
*    - � esperado um ponteiro v�lido para o monte
*    Assertivas de sa�da:
*    - O estado do monte foi retornado com sucesso
*
***********************************************************************/

MON_tpCondRet MON_MonteComprasDisponivel (MON_tpMonte pMonte);


#undef MONTE_EXT

/********** Fim do m�dulo de defini��o: MON Monte **********/
#else
#endif