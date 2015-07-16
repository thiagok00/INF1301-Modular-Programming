#if ! defined( CARTA_ )
#define CARTA_

/***************************************************************************
*
*  $MCD Módulo de definição: CAR Carta
*
*  Arquivo gerado:              CARTA.h
*  Letras identificadoras:      CAR
*
*  Nome da base de software:   
*  Arquivo da base de software:
*
*  Projeto: INF 1301 / Paciência Spider
*  Gestor:  
*  Autores: thk, adp, ilg
*
*  $HA Histórico de evolução:
*     Versão  Autor    Data     Observações
*	  2       thk   20/abr/2015 mudança dos retornos das funçoes
*     1       thk   16/abr/2015 início desenvolvimento
*
*  $ED Descrição do módulo
*     Implementa uma carta de baralho
*
*	  Cada carta deve possuir o seu valor e seu naipe, além do estado se está visivel ou não
*     O controle da destruição(free) da carta é realizada pela função CAR Destruir Carta
*
*
*
***************************************************************************/

#if defined( CARTA_OWN )
   #define CARTA_EXT
#else
   #define CARTA_EXT extern
#endif

/***** Declarações exportadas pelo módulo *****/

/* Tipo referência para uma carta */
typedef struct carta * CAR_tpCarta ;

/***********************************************************************
*
*  $TC Tipo de dados: CAR Condições de retorno
*
*
*  $ED Descrição do tipo
*     Condições de retorno das funções de carta
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
*  $ED Descrição do tipo
*     Dominio dos possiveis valores de uma carta, ValorIndefinido se carta não está visivel, ValorInexistente se carta não existe (=NULL)
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
*  $ED Descrição do tipo
*     Dominio dos possiveis naipes de uma carta, NaipeIndefinido se carta não está visivel, NaipeInexistente se carta não existe (=NULL)
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
*  $ED Descrição do tipo
*     Dominio dos possiveis estados de uma carta, CAR SemEstado se carta não existe (=NULL)
*
***********************************************************************/
typedef enum {

	CAR_EstadoVisivel,
	CAR_EstadoInvisivel,

} CAR_tpEstado ;

/***********************************************************************
*
*  $FC Função: LIS  &Criar Carta
*
*  $ED Descrição da função
*		Cria uma carta, seus dados devem ser passados para criação.
*		Por padrão seu estado é CAR Visivel.
*
*  $EP Parâmetros
*     Valor  - Valor fixo do valor para a carta
*	  Naipe - Valor fixo do naipe para a carta
*
*  $FV Valor retornado
*     Se executou corretamente retorna o ponteiro para a carta.
*     Este ponteiro será utilizado pelas funções que manipulem esta carta.
*
*     Se ocorreu algum erro, por exemplo falta de memória ou dados errados,
*     a função retornará NULL.
*     Não será dada mais informação quanto ao problema ocorrido.
*
*     Assertivas de entrada:
*     - O endereço de ponteiro para a carta deve ser válido
*     - O valor deve estar dentro do intervalo definido (0 a 12)
*     - O naipe deve ser válido
*     Assertivas de saída:
*     - O espaço de memória para a carta foi alocado com sucesso e seus valores definidos corretamente
*     
*
***********************************************************************/
CAR_tpCondRet CAR_CriarCarta(CAR_tpCarta *carta, CAR_tpValor valor, CAR_tpNaipe naipe);


/***********************************************************************
*
*  $FC Função: CAR  &Destruir Carta
*
*  $ED Descrição da função
*     Destrói a carta fornecida.
*     OBS. não existe previsão para possíveis falhas de execução.
*
*  $EP Parâmetros
*     pCarta - ponteiro para a carta a ser destruida
*
*     Assertivas de entrada:
*     - O ponteiro para a carta deve ser válido
*     Assertivas de saída:
*     - A carta passada como parâmetro foi destruida (espaço foi desalocado)
*
*
***********************************************************************/
void CAR_DestruirCarta(void* pCarta);


/***********************************************************************
*
*  $FC Função: CAR  &Obter Valor
*
*  $ED Descrição da função
*     Obtem o valor da carta passada
*
*  $EP Parâmetros
*     pCarta - ponteiro para a carta de onde se quer o valor
*
*  $FV Valor retornado
*	ValorIndefinido - se a carta não esta visivel
*	ValorInexistente - se a carta não existe (pCarta == NULL)
*	CAR_tpValor(possiveis valores de uma carta) - se a carta existe e está visivel
*
*     Assertivas de entrada:
*     - O ponteiro para a carta deve ser válido
*     - O valor deve estar dentro do intervalo definido (0 a 12)
*     Assertivas de saída:
*     - o pValor recebeu o valor da carta com sucesso
*
*
***********************************************************************/

CAR_tpCondRet CAR_ObterValor(CAR_tpCarta pCarta, CAR_tpValor *pValor);

/***********************************************************************
*
*  $FC Função: CAR  &Obter Naipe
*
*  $ED Descrição da função
*     Obtem o naipe da carta passada
*
*  $EP Parâmetros
*     pCarta - ponteiro para a carta de onde se quer o naipe
*
*  $FV Valor retornado
*	NaipeIndefinido - se a carta não esta visivel
*	NaipeInexistente - se a carta não existe (pCarta == NULL)
*	CAR_tpValor(possiveis naipes de uma carta) - se a carta existe e está visivel
*
*
*     Assertivas de entrada:
*     - O ponteiro para a carta deve ser válido
*     - O naipe da carta deve ser válido
*     Assertivas de saída:
*     - o pNaipe recebeu o naipe da carta com sucesso
*
***********************************************************************/

CAR_tpCondRet CAR_ObterNaipe(CAR_tpCarta pCarta, CAR_tpNaipe *pNaipe );

/***********************************************************************
*
*  $FC Função: CAR  &Obter Estado
*
*  $ED Descrição da função
*     Obtem o estado da carta passada
*
*  $EP Parâmetros
*     pCarta - ponteiro para a carta de onde se quer saber o estado
*
*  $FV Valor retornado
*	  CAR_EstadoInexistente - caso a carta não existe (pCarta == NULL)
*	  CAR_Visivel - se carta está visivel
*	  CAR_Invisivel - se a carta não está visivel
*
*     Assertivas de entrada:
*     - O ponteiro para a carta deve ser válido
*     - O estado da carta deve ser válido
*     Assertivas de saída:
*     - o pEstado recebeu o estado da carta com sucesso
*
*
***********************************************************************/

CAR_tpCondRet CAR_ObterEstado(CAR_tpCarta pCarta,CAR_tpEstado *pEstado);

/***********************************************************************
*
*  $FC Função: CAR  &Tornar Visivel
*
*  $ED Descrição da função
*     Torna estado da carta visivel caso exista, não faz nada caso carta não exista
*	  Não é definido como erro tornar uma carta que já esta visivel como visivel
*
*  $EP Parâmetros
*     pCarta - ponteiro para a carta
*
*     Assertivas de entrada:
*     - O ponteiro para a carta deve ser válido
*     Assertivas de saída:
*     - O estado da carta passou a ser visível, caso já fosse, continuou sendo vísivel
*
*
***********************************************************************/
CAR_tpCondRet CAR_TornarVisivel(CAR_tpCarta pCarta );
/***********************************************************************
*
*  $FC Função: CAR  &Tornar Invisivel
*
*  $ED Descrição da função
*     Torna estado da carta invisivel caso exista, não faz nada caso carta não exista
*	  Não é definido como erro tornar uma carta que já está com estado invisivel como invisivel
*
*  $EP Parâmetros
*     pCarta - ponteiro para a carta
*
*     Assertivas de entrada:
*     - O ponteiro para a carta deve ser válido
*     Assertivas de saída:
*     - O estado da carta passou a ser invisível, caso já fosse, continuou sendo invisível
*
*
***********************************************************************/
CAR_tpCondRet CAR_TornarInvisivel(CAR_tpCarta pCarta );


#undef CARTA_EXT

/********** Fim do módulo de definição: CAR  Carta **********/
#else
#endif
