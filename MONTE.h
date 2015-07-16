#if ! defined( MONTE_ )
#define MONTE_
/***************************************************************************
*
*  $MCD Módulo de definição: MON Monte
*
*  Arquivo gerado:              Monte.h
*  Letras identificadoras:      MON
*
*  Nome da base de software: Paciência Spider
*  Arquivo da base de software:
*
*  Projeto: INF 1301 / Paciência Spider
*  Gestor:
*  Autores: thk, adp, ilg
*
*  $HA Histórico de evolução:
*     Versão  Autor    Data     Observações
*	  3       thk   29/04/2015  ajustes nos comentarios e condições de retorno
*	  2		  thk	21/04/2015  término de desenvolvimento da versão 1
*     1       ilg   20/abr/2015 início desenvolvimento
*
*
*  $ED Descrição do módulo
*     Implementa o monte de cartas para compra do jogo Paciência Spider
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

/***** Declarações exportadas pelo módulo *****/

/* Tipo referência para um monte */
typedef struct MON_tagMonte * MON_tpMonte;

/***********************************************************************
*
*  $TC Tipo de dados: MON Condições de retorno
*
*
*  $ED Descrição do tipo
*     Condições de retorno das funções do monte de compras
*
***********************************************************************/
typedef enum {

	MON_CondRetOK,
	/* Concluiu corretamente */

	MON_CondRetMonteVazio,
	/* Não há cartas no monte */

	MON_CondRetMonteCheio,
	/* O monte já contém 10 cartas naõ nulas */

	MON_CondRetMonteNaoExiste,
	/* O monte não foi criado antes de requerida operação de trabalho sobre ele */

	MON_CondRetFaltouMemoria,
	/* Faltou memória ao tentar criar monte ou adicionar pilhas a ele */

	MON_CondRetFaltamCartas
	/* Faltou cartas na hora de inicializar o monte */
} MON_tpCondRet;

/***********************************************************************
*
*  $FC Função: MON  &Criar Monte Compras
*
*  $ED Descrição da função
*     Cria um monte de compras
*
*  $EP Parâmetros
*	  pMonte - endereço de ponteiro para o monte
*
*  $FV Valor retornado
*     MON_CondRetOk - se foi criado corretamente
*	  MON_CondRetFaltouMeMoria - se não conseguiu alocar espaço para o tpMonte ou para tpMonte->cabeca
*
*    Assertivas de entrada:
*    - É esperado um endereço de ponteiro válido para o monte
*    - É esperado que se tenha espaço na memória para ser alocado
*    Assertivas de saída:
*    - Espaço de memória para o monte alocado com sucesso.
*
***********************************************************************/
MON_tpCondRet MON_CriarMonteCompras(MON_tpMonte * pMonte);

/***********************************************************************
*
*  $FC Função: MON  &Destruir Monte Compras
*
*  $ED Descrição da função
*     Destrói a cabeça do monte de compras passado como argumento.
*	  A função não destrói as pilhas de cartas do monte, para isso é necessario esvaziá-lo.
*
*  $EP Parâmetros 
*	  pMonte - ponteiro para o monte
*
*  $FV Valor Retornado
*	  MON_CondRetMonteInexistente - se pMonte é NULL
*	  MON_CondRetMonteVazio 
*	  MON_CondRetOk - se os proccedimentos foram executados corretamente
*
*    Assertivas de entrada:
*    - É esperado um ponteiro válido para o monte
*    Assertivas de saída:
*    - Espaço de memória para o monte desalocado com sucesso.
*
***********************************************************************/

MON_tpCondRet MON_DestruirMonteCompras(MON_tpMonte pMonte);

/***********************************************************************
*
*  $FC Função: MON  &Esvaziar Monte Compras
*
*  $ED Descrição da função
*     Elimina todas as pilhas de carta do monte, sem, contudo, destruir o monte em si.
*
*  $EP Parâmetros
*     pMonte - ponteiro para o monte a ser esvaziado
*
*  $FV Valor Retornado
*	  MON_CondRetMonteInexistente - se pMonte é NULL
*	  MON_CondRetMonteVazio - se o monte já está inicialmente vazio
*	  MON_CondRetOk - se os procedimentos fora mexecutados corretamente
*
*    Assertivas de entrada:
*    - É esperado um ponteiro válido para o monte
*    Assertivas de saída:
*    - Espaço de memória para o monte recebeu NULL (esvaziou) com sucesso
*
***********************************************************************/

MON_tpCondRet MON_EsvaziarMonteCompras(MON_tpMonte pMonte);

/***********************************************************************
*
*  $FC Função: MON  &Adicionar Ao Monte Compras
*
*  $ED Descrição da função
*	Adiciona pilha de cartas para o monte de compras.
*
*  $EP Parâmetros
*     pCarta - ponteiro para a carta
*     pMonte - ponteiro para o monte
*
*  $FV Valor retornado
*     MON_CondRetOk - se o monte estava inicialmente vazio e foi corretamente adicionada a pilha a ele.
*	  MON_CondRetFaltouMemoria - se faltou memória para a operação e, portanto, nao pôde ser realizada.
*	  MON_CondRetMonteCheio - se tentou adicionar pilha de cartas a um monte que já esta preenchido.
*	  MON_CondRetMonteNaoExiste - caso cabeça do monte seja NULL
*
*    Assertivas de entrada:
*    - É esperado um ponteiro válido para o monte
*    - É esperado um ponteiro válido para pilha de cartas com 10 cartas
*    Assertivas de saída:
*    - A pilha de cartas foi adicionada ao monte com sucesso
*
***********************************************************************/

MON_tpCondRet MON_AdicionarAoMonteCompras(MON_tpMonte pMonte, PIL_tpPilha pPilha);


/***********************************************************************
*
*  $FC Função: MON  &Retornar Compra
*
*  $ED Descrição da função
*     Retorna o endereço para pilha de cartas do monte.
*	  Função a ser acionada quando for solicitada compra de cartas do monte.
*
*  $EP Parâmetros
*     pMonte - ponteiro para o monte de compras.
*	  pPilha - ponteiro para a pilha
*
*  $FV Valor retornado
*     MON_CondRetOk - caso os procedimentos tenham sido executados corretamente.
*	  MON_CondRetMonteNaoExiste - caso pMonte seja NULL.
*	  MON_CondRetMonteVazio 
*     MON_CondRetFaltouMemoria - caso falte espaço na memória.
*
*    Assertivas de entrada:
*    - É esperado um ponteiro válido para o monte
*    - É esperado um ponteiro válido para a pilha
*    Assertivas de saída:
*    - A pilha foi removida do monte com sucesso
*
***********************************************************************/
MON_tpCondRet MON_RetornarCompra (MON_tpMonte pMonte, PIL_tpPilha pPilha);



/***********************************************************************
*
*  $FC Função: MON  &Imprimir Monte Compra
*
*  $ED Descrição da função
*	  Imprime as cartas presentes em um monte de compras.
*
*  $EP Parâmetros
*     pMonte - ponteiro para o monte de compras.
*
*  $FV Valor retornado
*     MON_CondRetOk - caso os procedimentos tenham sido executados corretamente.
*	  MON_CondRetMonteNaoExiste - caso pMonte seja NULL.
*	  MON_CondRetMonteVazio 
*
*    Assertivas de entrada:
*    - É esperado um ponteiro válido para o monte
*    Assertivas de saída:
*    - A pilha do monte foi imprimida com sucesso
*
***********************************************************************/

MON_tpCondRet MON_ImprimirMonteCompras (MON_tpMonte pMonte);

/***********************************************************************
*
*  $FC Função: MON  &Monte Compras Disponivel
*
*  $ED Descrição da função
*	  Retorna se o monte esta disponivel para ser comprado
*
*  $EP Parâmetros
*     pMonte - ponteiro para o monte de compras.
*
*  $FV Valor retornado
*     MON_CondRetOk - caso esteja disponivel.
*	  MON_CondRetMonteNaoExiste - caso pMonte seja NULL.
*	  MON_CondRetMonteVazio
*
*    Assertivas de entrada:
*    - É esperado um ponteiro válido para o monte
*    Assertivas de saída:
*    - O estado do monte foi retornado com sucesso
*
***********************************************************************/

MON_tpCondRet MON_MonteComprasDisponivel (MON_tpMonte pMonte);


#undef MONTE_EXT

/********** Fim do módulo de definição: MON Monte **********/
#else
#endif