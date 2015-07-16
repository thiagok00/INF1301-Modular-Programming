#if ! defined( CARTA_ )
#define CARTA_

/***************************************************************************
*
*  $MCD M�dulo de defini��o: CAR Carta
*
*  Arquivo gerado:              CARTA.h
*  Letras identificadoras:      CAR
*
*  Nome da base de software:   
*  Arquivo da base de software:
*
*  Projeto: INF 1301 / Paci�ncia Spider
*  Gestor:  
*  Autores: thk, adp, ilg
*
*  $HA Hist�rico de evolu��o:
*     Vers�o  Autor    Data     Observa��es
*	  2       thk   20/abr/2015 mudan�a dos retornos das fun�oes
*     1       thk   16/abr/2015 in�cio desenvolvimento
*
*  $ED Descri��o do m�dulo
*     Implementa uma carta de baralho
*
*	  Cada carta deve possuir o seu valor e seu naipe, al�m do estado se est� visivel ou n�o
*     O controle da destrui��o(free) da carta � realizada pela fun��o CAR Destruir Carta
*
*
*
***************************************************************************/

#if defined( CARTA_OWN )
   #define CARTA_EXT
#else
   #define CARTA_EXT extern
#endif

/***** Declara��es exportadas pelo m�dulo *****/

/* Tipo refer�ncia para uma carta */
typedef struct carta * CAR_tpCarta ;

/***********************************************************************
*
*  $TC Tipo de dados: CAR Condi��es de retorno
*
*
*  $ED Descri��o do tipo
*     Condi��es de retorno das fun��es de carta
*
***********************************************************************/

typedef enum {

	CAR_CondRetOK,
	
	CAR_CondRetCartaNaoExiste,

	CAR_CondRetFaltouMemoria,
	
	CAR_CondRetCartaVazia,
	
	CAR_CondRetCartaInvisivel,

	CAR_CondRetValorInvalido,

	CAR_CondRetNaipeInvalido,

   } CAR_tpCondRet;

/***********************************************************************
*
*  $TC Tipo de dados: CAR tpValor
*
*
*  $ED Descri��o do tipo
*     Dominio dos possiveis valores de uma carta, ValorIndefinido se carta n�o est� visivel, ValorInexistente se carta n�o existe (=NULL)
*
***********************************************************************/
typedef enum {

	_A,
	_2,
	_3,
	_4,
	_5,
	_6,
	_7,
	_8,
	_9,
	_10,
	_J,
	_Q,
	_K
   } CAR_tpValor ;

/***********************************************************************
*
*  $TC Tipo de dados: CAR tpNaipe
*
*
*  $ED Descri��o do tipo
*     Dominio dos possiveis naipes de uma carta, NaipeIndefinido se carta n�o est� visivel, NaipeInexistente se carta n�o existe (=NULL)
*
***********************************************************************/
typedef enum {

	Espadas,
	Copas,
	Ouros,
	Paus
   } CAR_tpNaipe ;

/***********************************************************************
*
*  $TC Tipo de dados: CAR estados
*
*
*  $ED Descri��o do tipo
*     Dominio dos possiveis estados de uma carta, CAR SemEstado se carta n�o existe (=NULL)
*
***********************************************************************/
typedef enum {

	CAR_EstadoVisivel,
	CAR_EstadoInvisivel,

} CAR_tpEstado ;

/***********************************************************************
*
*  $FC Fun��o: LIS  &Criar Carta
*
*  $ED Descri��o da fun��o
*		Cria uma carta, seus dados devem ser passados para cria��o.
*		Por padr�o seu estado � CAR Visivel.
*
*  $EP Par�metros
*     Valor  - Valor fixo do valor para a carta
*	  Naipe - Valor fixo do naipe para a carta
*
*  $FV Valor retornado
*     Se executou corretamente retorna o ponteiro para a carta.
*     Este ponteiro ser� utilizado pelas fun��es que manipulem esta carta.
*
*     Se ocorreu algum erro, por exemplo falta de mem�ria ou dados errados,
*     a fun��o retornar� NULL.
*     N�o ser� dada mais informa��o quanto ao problema ocorrido.
*
*     Assertivas de entrada:
*     - O endere�o de ponteiro para a carta deve ser v�lido
*     - O valor deve estar dentro do intervalo definido (0 a 12)
*     - O naipe deve ser v�lido
*     Assertivas de sa�da:
*     - O espa�o de mem�ria para a carta foi alocado com sucesso e seus valores definidos corretamente
*     
*
***********************************************************************/
CAR_tpCondRet CAR_CriarCarta(CAR_tpCarta *carta, CAR_tpValor valor, CAR_tpNaipe naipe);


/***********************************************************************
*
*  $FC Fun��o: CAR  &Destruir Carta
*
*  $ED Descri��o da fun��o
*     Destr�i a carta fornecida.
*     OBS. n�o existe previs�o para poss�veis falhas de execu��o.
*
*  $EP Par�metros
*     pCarta - ponteiro para a carta a ser destruida
*
*     Assertivas de entrada:
*     - O ponteiro para a carta deve ser v�lido
*     Assertivas de sa�da:
*     - A carta passada como par�metro foi destruida (espa�o foi desalocado)
*
*
***********************************************************************/
void CAR_DestruirCarta(void* pCarta);


/***********************************************************************
*
*  $FC Fun��o: CAR  &Obter Valor
*
*  $ED Descri��o da fun��o
*     Obtem o valor da carta passada
*
*  $EP Par�metros
*     pCarta - ponteiro para a carta de onde se quer o valor
*
*  $FV Valor retornado
*	ValorIndefinido - se a carta n�o esta visivel
*	ValorInexistente - se a carta n�o existe (pCarta == NULL)
*	CAR_tpValor(possiveis valores de uma carta) - se a carta existe e est� visivel
*
*     Assertivas de entrada:
*     - O ponteiro para a carta deve ser v�lido
*     - O valor deve estar dentro do intervalo definido (0 a 12)
*     Assertivas de sa�da:
*     - o pValor recebeu o valor da carta com sucesso
*
*
***********************************************************************/

CAR_tpCondRet CAR_ObterValor(CAR_tpCarta pCarta, CAR_tpValor *pValor);

/***********************************************************************
*
*  $FC Fun��o: CAR  &Obter Naipe
*
*  $ED Descri��o da fun��o
*     Obtem o naipe da carta passada
*
*  $EP Par�metros
*     pCarta - ponteiro para a carta de onde se quer o naipe
*
*  $FV Valor retornado
*	NaipeIndefinido - se a carta n�o esta visivel
*	NaipeInexistente - se a carta n�o existe (pCarta == NULL)
*	CAR_tpValor(possiveis naipes de uma carta) - se a carta existe e est� visivel
*
*
*     Assertivas de entrada:
*     - O ponteiro para a carta deve ser v�lido
*     - O naipe da carta deve ser v�lido
*     Assertivas de sa�da:
*     - o pNaipe recebeu o naipe da carta com sucesso
*
***********************************************************************/

CAR_tpCondRet CAR_ObterNaipe(CAR_tpCarta pCarta, CAR_tpNaipe *pNaipe );

/***********************************************************************
*
*  $FC Fun��o: CAR  &Obter Estado
*
*  $ED Descri��o da fun��o
*     Obtem o estado da carta passada
*
*  $EP Par�metros
*     pCarta - ponteiro para a carta de onde se quer saber o estado
*
*  $FV Valor retornado
*	  CAR_EstadoInexistente - caso a carta n�o existe (pCarta == NULL)
*	  CAR_Visivel - se carta est� visivel
*	  CAR_Invisivel - se a carta n�o est� visivel
*
*     Assertivas de entrada:
*     - O ponteiro para a carta deve ser v�lido
*     - O estado da carta deve ser v�lido
*     Assertivas de sa�da:
*     - o pEstado recebeu o estado da carta com sucesso
*
*
***********************************************************************/

CAR_tpCondRet CAR_ObterEstado(CAR_tpCarta pCarta,CAR_tpEstado *pEstado);

/***********************************************************************
*
*  $FC Fun��o: CAR  &Tornar Visivel
*
*  $ED Descri��o da fun��o
*     Torna estado da carta visivel caso exista, n�o faz nada caso carta n�o exista
*	  N�o � definido como erro tornar uma carta que j� esta visivel como visivel
*
*  $EP Par�metros
*     pCarta - ponteiro para a carta
*
*     Assertivas de entrada:
*     - O ponteiro para a carta deve ser v�lido
*     Assertivas de sa�da:
*     - O estado da carta passou a ser vis�vel, caso j� fosse, continuou sendo v�sivel
*
*
***********************************************************************/
CAR_tpCondRet CAR_TornarVisivel(CAR_tpCarta pCarta );
/***********************************************************************
*
*  $FC Fun��o: CAR  &Tornar Invisivel
*
*  $ED Descri��o da fun��o
*     Torna estado da carta invisivel caso exista, n�o faz nada caso carta n�o exista
*	  N�o � definido como erro tornar uma carta que j� est� com estado invisivel como invisivel
*
*  $EP Par�metros
*     pCarta - ponteiro para a carta
*
*     Assertivas de entrada:
*     - O ponteiro para a carta deve ser v�lido
*     Assertivas de sa�da:
*     - O estado da carta passou a ser invis�vel, caso j� fosse, continuou sendo invis�vel
*
*
***********************************************************************/
CAR_tpCondRet CAR_TornarInvisivel(CAR_tpCarta pCarta );


#undef CARTA_EXT

/********** Fim do m�dulo de defini��o: CAR  Carta **********/
#else
#endif
