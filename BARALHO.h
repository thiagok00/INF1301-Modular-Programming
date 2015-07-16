#if ! defined( BARALHO_ )
#define BARALHO_
/***************************************************************************
*
*  $MCD Módulo de definição: BAR Baralho
*
*  Arquivo gerado:              BARALHO.h
*  Letras identificadoras:      BAR
*
*  Nome da base de software:   Paciência Spider
*  Arquivo da base de software:
*
*  Projeto: INF 1301 / Paciência Spider
*  Gestor:  
*  Autores: thk, adp, ilg
*
*  $HA Histórico de evolução:
*     Versão  Autor    Data     Observações
*	  2		  thk	28/abr/2015 ajuste em erros
*     1       thk   16/abr/2015 início desenvolvimento
*
*  $ED Descrição do módulo
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

/***** Declarações exportadas pelo módulo *****/


/* Tipo referência para um baralho */
typedef struct BAR_tagBaralho * BAR_tpBaralho;


/***********************************************************************
*
*  $TC Tipo de dados: BAR Condições de retorno
*
*
*  $ED Descrição do tipo
*     Condições de retorno das funções do baralho
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
*  $FC Função: BAR  &Criar Baralho
*
*  $ED Descrição da função
*		Cria um baralho, seus dados devem ser passados para criação.
*
*  $EP Parâmetros
*     pBaralho - Endereço de ponteiro para um baralho
*
*  $FV Valor retornado
*     BAR_CondRetOk - se a função funcionar perfeitamente
*     BAR_CondRetFaltouMemoria - se faltou memória para criar o baralho
*     Não será dada mais informação quanto ao problema ocorrido.
*
*     Assertivas de entrada: 
*     - É esperado que o endereço de ponteiro seja válido
*     - É esperado que possua espaço na memória
*     Assertivas de saída:
*     - O baralho foi criada com sucesso
*
***********************************************************************/
BAR_tpCondRet BAR_CriarBaralho (BAR_tpBaralho * pBaralho);

/***********************************************************************
*
*  $FC Função: BAR  &Destruir Baralho
*
*  $ED Descrição da função
*		Destrói um baralho, seus dados devem ser passados para destruição.
*
*  $EP Parâmetros
*     pBaralho -Ponteiro para um baralho
*
*  $FV Valor retornado
*     BAR_CondRetOk - se a função funcionar perfeitamente
*     BAR_CondRetBaralhoNaoExiste - caso pBaralho == NULL
*     Não será dada mais informação quanto ao problema ocorrido.
*
*     Assertivas de entrada: 
*     - É esperado que o ponteiro seja válido
*     Assertivas de saída:
*     - O espaço de memória do baralho tenha sido desalocado com sucesso
*
***********************************************************************/
BAR_tpCondRet BAR_DestruirBaralho(BAR_tpBaralho pBaralho);

/***********************************************************************
*
*  $FC Função: BAR  &Esvaziar Baralho
*
*  $ED Descrição da função
*		Esvazia um baralho, seus dados devem ser passados para esvaziar.
*
*  $EP Parâmetros
*     pBaralho -Ponteiro para um baralho
*
*  $FV Valor retornado
*     BAR_CondRetOk - se a função funcionar perfeitamente
*     BAR_CondRetBaralhoNaoExiste - caso pBaralho == NULL
*     Não será dada mais informação quanto ao problema ocorrido.
*
*     Assertivas de entrada: 
*     - É esperado que o ponteiro seja válido
*     Assertivas de saída:
*     - o espaço alocado pelo pBaralho tenha recebido NULL
*
***********************************************************************/

BAR_tpCondRet BAR_EsvaziarBaralho (BAR_tpBaralho pBaralho);

/***********************************************************************
*
*  $FC Função: BAR  &iniciar Baralho
*
*  $ED Descrição da função
*		Inicia(embaralha) os dois baralhos, seus dados devem ser passados para o embaralhamento.
*
*  $EP Parâmetros
*     pBaralho -Ponteiro para um baralho
*     qtdBaralhos - quantidade de baralhos que serão usados
*     qtdNaipes - quantidade de naipes que serão usados no embaralhamento
*
*  $FV Valor retornado
*     BAR_CondRetOk - se a função funcionar perfeitamente
*     BAR_CondRetBaralhoNaoExiste - caso pBaralho == NULL
*     BAR_CondRetFaltouMemoria - caso falte memória para alocar o baralho
*     Não será dada mais informação quanto ao problema ocorrido.
*
*     Assertivas de entrada: 
*     - É esperado que o ponteiro para o baralho seja válido
*     - Quantidade de baralhos é esperado que seja 2 (104 cartas)
*     - Quantidade de naipes é esperado que seja válida (de 1 a 4 naipes)
*     Assertivas de saída:
*     - O baralho formado com 104 cartas está embaralhado
*
***********************************************************************/

BAR_tpCondRet BAR_IniciarBaralho (BAR_tpBaralho pBaralho, int qtdBaralhos, int qtdNaipes);

/***********************************************************************
*
*  $FC Função: BAR  &Criar SubPilha Baralho
*
*  $ED Descrição da função
*		Cria uma subpilha de um baralho, seus dados devem ser passados para criação.
*
*  $EP Parâmetros
*     pBaralho -Ponteiro para um baralho
*     pPilha - Endereço de ponteiro para uma pilha de cartas
*     tam - tamanho exato da subpilha
*
*  $FV Valor retornado
*     BAR_CondRetOk - se a função funcionar perfeitamente
*     BAR_CondRetBaralhoNaoExiste - caso pBaralho == NULL
*     BAR_CondRetFaltouMemoria - caso falte memória para alocar o baralho
*     BAR_CondRetBaralhoInsuficiente - caso o baralho seja menor que a subpilha
*     Não será dada mais informação quanto ao problema ocorrido.
*
*     Assertivas de entrada: 
*     - É esperado que o ponteiro para o baralho seja válido
*     - É esperado que o ponteiro para a pilha de cartas seja válido
*     - Quantidade de naipes é esperado que seja válida (de 1 a 4 naipes)
*     Assertivas de saída:
*     - A subpilha passa a possuir um subconjunto de um baralho
*
***********************************************************************/
BAR_tpCondRet BAR_CriarSubPilhaBaralho (BAR_tpBaralho pBaralho, PIL_tpPilha * pPilha, int tam) ;


/***********************************************************************
*
*  $FC Função: BAR  &Imprimir Baralho
*
*  $ED Descrição da função
*		Imprime a pilha de cartas do baralho
*
*  $EP Parâmetros
*     pBaralho -Ponteiro para um baralho
*
*  $FV Valor retornado
*     BAR_CondRetOk - se a função funcionar perfeitamente
*     BAR_CondRetBaralhoNaoExiste - caso pBaralho == NULL
*     BAR_CondRetBaralhoVazio
*
*     Assertivas de entrada: 
*     - É esperado que o ponteiro seja válido para um baralho com uma pilha de cartas com cartas
*     Assertivas de saída:
*     - O baralho foi imprimido com sucesso
*
***********************************************************************/
BAR_tpCondRet BAR_ImprimirBaralho(BAR_tpBaralho pBaralho);

#undef BARALHO_EXT

/********** Fim do módulo de definição: BAR  Baralho **********/



#else
#endif