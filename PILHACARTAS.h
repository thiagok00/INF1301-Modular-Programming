#if ! defined( PILHACARTAS_ )
#define PILHACARTAS_

/***************************************************************************
*
*  $MCD Módulo de definição: PIL Pilha Cartas
*
*  Arquivo gerado:              PILHACARTAS.h
*  Letras identificadoras:      PIL
*
*  Nome da base de software:   Paciência Spider
*  Arquivo da base de software:
*
*  Projeto: INF 1301 / Paciência Spider
*  Gestor:  
*  Autores: thk, adp, ilg
*
*  $HA Histórico de evolução:
*     Versão  Autor    Data			Observações
*	  4		  thk	25/maio/2015	finalizado para entrega3
*	  3       thk   28/abr/2015		mudança de retorno de funçoes
*	  2		  thk   27/abr/2015		implentacao de novas funçoes
*	  1		  thk   25/abr/2015		inicio desenvolvimento
*
*  $ED Descrição do módulo
*     Implementa estrutura para uma pilha de cartas 
*     Podem existir n pilhas de cartas em operação simultaneamente.
*     As pilhas possuem uma cabeça encapsulando o seu estado.
*	  É possivel percorrer a pilha de cartas, adicionar e remover cartas.
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
/***** Declarações exportadas pelo módulo *****/

/* Tipo referência para uma pilha de cartas */
typedef struct PIL_tagPilha * PIL_tpPilha;

/***********************************************************************
*
*  $TC Tipo de dados: PIL Condições de retorno
*
*
*  $ED Descrição do tipo
*     Condições de retorno das funções da pilha de cartas
*
***********************************************************************/

typedef enum {

         PIL_CondRetOK ,
               /* Concluiu corretamente */

         PIL_CondRetPilhaVazia ,
			   /* A pilha está vazia */
		 
         PIL_CondRetFimPilha ,
               /* Foi atingido o fim da pilha */

         PIL_CondRetPilhaNaoExiste ,
               /* Tentou manipular pilha não existente */

         PIL_CondRetFaltouMemoria,
               /* Faltou memória ao alocar uma estutura (pilha ou carta) */

		 PIL_CondRetCartaNaoExiste
			   /* A carta manipilada não existe */

   } PIL_tpCondRet ;


/***********************************************************************
*
*  $FC Função: PIL  &Criar PilhaCartas
*
*  $ED Descrição da função
*     Cria uma pilha de cartas.
*
*  $EP Parâmetros
*     pPilha  - Endereço de ponteiro para a pilha de cartas.
*                    
*
*  $FV Valor retornado
*     PIL_CondRetOk - Se executou corretamente.
*     PIL_CondRetFaltouMemoria - Se ocorreu falta de memória
*     Não será dada mais informação quanto ao problema ocorrido.
*
*     Assertivas de entrada:
*     - É esperado que o endereço de ponteiro para a pilha seja válido
*     Assertivas de saída:
*     - Espaço para a pilha foi alocado com êxito
*
***********************************************************************/

PIL_tpCondRet PIL_CriarPilhaCartas (PIL_tpPilha *pPilha);


/***********************************************************************
*
*  $FC Função: PIL  &Destruir PilhaCartas
*
*  $ED Descrição da função
*     Destrói a cabeca pilha de cartas passada sem destruir as cartas nela contida;
*
*  $EP Parâmetros
*     pPilha  - ponteiro para a pilha de cartas.
*                    
*
*  $FV Valor retornado
*     PIL_CondRetOk - Se executou corretamente.
*     PIL_CondRetPilhaNaoExiste - se a pilha passada como parâmetro não existe
*     PIL_CondRetPilhaVazia - caso a pilha esteja vazia
*     Não será dada mais informação quanto ao problema ocorrido.
*
*     Assertivas de entrada:
*     - É esperado que o ponteiro da pilha seja válido
*     Assertivas de saída:
*     - Espaço para a pilha foi desalocado com êxito
*
***********************************************************************/
PIL_tpCondRet PIL_DestruirPilhaCartas (PIL_tpPilha pPilha);


/***********************************************************************
*
*  $FC Função: PIL  &Esvaziar PilhaCartas
*
*  $ED Descrição da função
*     Esvazia a pilha de cartas, destruindo todas as cartas nela.
*	  Sem destruir a cabeça da pilha.
*
*  $EP Parâmetros
*     pPilha  - ponteiro para a pilha de cartas.
*                    
*  $FV Valor retornado
*     PIL_CondRetOk - Se executou corretamente.
*     PIL_CondRetPilhaNaoExiste - se a pilha passada como parâmetro não existe
*     PIL_CondRetPilhaVazia - caso a pilha esteja vazia
*     Não será dada mais informação quanto ao problema ocorrido.
*
*     Assertivas de entrada:
*     - É esperado que o ponteiro da pilha seja válido
*     Assertivas de saída:
*     - Espaço para a pilha recebeu NULL,ou seja, foi esvaziado corretamente
*
***********************************************************************/
PIL_tpCondRet PIL_EsvaziarPilhaCartas(PIL_tpPilha pPilha);

/***********************************************************************
*
*  $FC Função: PIL  &Avançar Elemento Corrente
*
*  $ED Descrição da função
*     Recebe numero de elementos (cartas) a se avançar na pilha.
*
*  $EP Parâmetros
*     pPilha  - ponteiro para a pilha de cartas.
*     numElem - inteiro indicando quantas cartas irá "andar" na pilhh de cartas
*
*  $FV Valor retornado
*     PIL_CondRetOk - Se executou corretamente.
*     PIL_CondRetPilhaNaoExiste - se a pilha passada como parâmetro não existe
*     PIL_CondRetPilhaVazia - caso a pilha esteja vazia 
*     PIL_CondRetFimPilha - se chegou ao final da pilha
*     Não será dada mais informação quanto ao problema ocorrido.
*     
*     Assertivas de entrada:
*     - É esperado que o ponteiro da pilha seja válido
*     - É esperado que o número de elemento não ultrapasse o "tamanho" da pilha
*     Assertivas de saída:
*     - O ponteiro passou a apontar para outro nó da pilha
*
***********************************************************************/
PIL_tpCondRet PIL_AvancarElementoCorrente( PIL_tpPilha pPilha ,int numElem );

/***********************************************************************
*
*  $FC Função: PIL  &Ver Carta
*
*  $ED Descrição da função
*      Obtem a referência para a carta corrente da pilha de cartas, não a remove da pilha.
*
*  $EP Parâmetros
*     pPilha  - ponteiro para a pilha de cartas.
*     pCarta - Endereço de ponteiro para uma estrutura carta
*
*  $FV Valor retornado
*     PIL_CondRetOk - Se executou corretamente.
*     PIL_CondRetPilhaNaoExiste - se a pilha passada como parâmetro não existe
*     PIL_CondRetPilhaVazia - caso a pilha esteja vazia
*     Não será dada mais informação quanto ao problema ocorrido.
*     
*     Assertivas de entrada:
*     - É esperado que o ponteiro da pilha seja válido
*     - É esperado que o endereço de ponteiro para a carta seja válido
*     Assertivas de saída:
*     - Foi possível obter o valor da carta em questão
*
*
***********************************************************************/
PIL_tpCondRet PIL_VerCarta( PIL_tpPilha pPilha , CAR_tpCarta * pCarta );

/***********************************************************************
*
*  $FC Função: PIL  &Adicionar Carta
*
*  $ED Descrição da função
*     Adiciona uma carta a uma pilha de cartas ( a carta será inserido antes corrente )
*
*  $EP Parâmetros
*     pPilha  - ponteiro para a pilha de cartas.
*     carta - ponteiro para uma estrutura carta
*
*  $FV Valor retornado
*     PIL_CondRetOk - Se executou corretamente.
*     PIL_CondRetPilhaNaoExiste - se a pilha passada como parâmetro não existe
*     PIL_CondRetFaltouMemoria  - se faltou memória 
*     Não será dada mais informação quanto ao problema ocorrido.
*     
*     Assertivas de entrada:
*     - É esperado que o ponteiro da pilha seja válido
*     - É esperado que o eponteiro da carta seja válido
*     Assertivas de saída:
*     - Foi possível adicionar a carta na pilha questão
*
***********************************************************************/
PIL_tpCondRet PIL_AdicionarCarta (PIL_tpPilha pPilha, CAR_tpCarta carta);

/***********************************************************************
*
*  $FC Função: PIL  &Imprimir Pilha Cartas
*
*  $ED Descrição da função
*     Imprime a pilha de cartas que recebe como parâmetros.
*	  O ultimo elemento da pilha de cartas é o primeiro imprimido.
*
*  $EP Parâmetros
*     pPilha  - ponteiro para a pilha de cartas.
*
*  $FV Valor retornado
*     PIL_CondRetOk - Se executou corretamente.
*     PIL_CondRetPilhaNaoExiste - se a pilha passada como parâmetro não existe
*     PIL_CondRetPilhaVazia - caso a pilha esteja vazia 
*     Não será dada mais informação quanto ao problema ocorrido.
*     
*     Assertivas de entrada:
*     - É esperado que o ponteiro da pilha seja válido
*     Assertivas de saída:
*     - Foi possível imprimir a pilha em questão
*
***********************************************************************/
PIL_tpCondRet PIL_ImprimirPilhaCartas (PIL_tpPilha pPilha);

/***********************************************************************
*
*  $FC Função: PIL  &Ir FinalPilha
*
*  $ED Descrição da função
*     Vai para o final da pilha de cartas
*
*  $EP Parâmetros
*     pPilha  - ponteiro para a pilha de cartas.
*
*  $FV Valor retornado
*     PIL_CondRetOk - Se executou corretamente.
*     PIL_CondRetPilhaNaoExiste - se a pilha passada como parâmetro não existe
*     Não será dada mais informação quanto ao problema ocorrido.
*     
*     Assertivas de entrada:
*     - É esperado que o ponteiro da pilha seja válido
*     Assertivas de saída:
*     - O ponteiro passou a apontar para o final da pilha em questão
*
***********************************************************************/

PIL_tpCondRet PIL_IrFinalPilhaCartas( PIL_tpPilha pPilha );

/***********************************************************************
*
*  $FC Função: PIL  &Ir InicioPilha
*
*  $ED Descrição da função
*     Vai para o início da pilha de cartas
*
*  $EP Parâmetros
*     pPilha  - ponteiro para a pilha de cartas.
*
*  $FV Valor retornado
*     PIL_CondRetOk - Se executou corretamente.
*     PIL_CondRetPilhaNaoExiste - se a pilha passada como parâmetro não existe
*     Não será dada mais informação quanto ao problema ocorrido.
*     
*     Assertivas de entrada:
*     - É esperado que o ponteiro da pilha seja válido
*     Assertivas de saída:
*     - O ponteiro passou a apontar para o início da pilha em questão
*
***********************************************************************/

PIL_tpCondRet PIL_IrInicioPilhaCartas( PIL_tpPilha pPilha );

/***********************************************************************
*
*  $FC Função: PIL  &Remover Carta
*
*  $ED Descrição da função
*     Remove uma carta da pilha de cartas obtendo-se a referencia para ela
*
*  $EP Parâmetros
*     pPilha - ponteiro para a pilha de cartas a qual será removida a carta.
*     pCarta - Endereço de ponteiro para a carta
*
*  $FV Valor retornado
*     PIL_CondRetOk - Se executou corretamente.
*	  PIL_CondRetFaltouMemoria - caso falte memória para a criação da carta auxiliar
*     PIL_CondRetPilhaNaoExiste - se a pilha passada como parâmetro não existe
*     PIL_CondRetPilhaVazia - se a pilha origem estiver vazia
*     Não será dada mais informação quanto ao problema ocorrido.
*     
*     Assertivas de entrada:
*     - É esperado que o ponteiro da pilha seja válido
*     - É esperado que o endereço de ponteiro para a carta seja válido
*     Assertivas de saída:
*     - A carta foi removida da pilha de cartas com sucesso
*
***********************************************************************/

PIL_tpCondRet PIL_RemoverCarta( PIL_tpPilha pPilha , CAR_tpCarta * pCarta );

/***********************************************************************
*
*  $FC Função: PIL  &Tornar Carta Invisivel
*
*  $ED Descrição da função
*     Torna a carta corrente invisivel
*
*  $EP Parâmetros
*     pPilha - ponteiro para a pilha de cartas.
*
*  $FV Valor retornado
*     PIL_CondRetOk - Se executou corretamente.
*	  PIL_CondRetPilhaNaoExiste
*     
*     Assertivas de entrada:
*     - É esperado que o ponteiro da pilha seja válido
*     - É esperado que a pilha não seja vazia
*     Assertivas de saída:
*     - A carta foi tornada invisivel
*
***********************************************************************/

PIL_tpCondRet PIL_TornarCartaVisivel( PIL_tpPilha pPilha);

/***********************************************************************
*
*  $FC Função: PIL  &Tornar Carta Visivel
*
*  $ED Descrição da função
*     Torna a carta corrente visivel
*
*  $EP Parâmetros
*     pPilha - ponteiro para a pilha de cartas.
*
*  $FV Valor retornado
*     PIL_CondRetOk - Se executou corretamente.
*	  PIL_CondRetPilhaNaoExiste
*     
*     Assertivas de entrada:
*     - É esperado que o ponteiro da pilha seja válido
*     - É esperado que a pilha não seja vazia
*     Assertivas de saída:
*     - A carta foi tornada visivel
*
***********************************************************************/
PIL_tpCondRet PIL_TornarCartaInvisivel( PIL_tpPilha pPilha);

/***********************************************************************
*
*  $FC Função: PIL  &Quantidade Cartas
*
*  $ED Descrição da função
*     Retorna a quantidade de cartas na pilha por parametro
*
*  $EP Parâmetros
*     pPilha - ponteiro para a pilha de cartas.
*	  qtd - ponteiro para o valor quantidade
*
*  $FV Valor retornado
*     PIL_CondRetOk - Se executou corretamente.
*	  PIL_CondRetPilhaNaoExiste - pPilha == NULL
*     
*     Assertivas de entrada:
*     - É esperado que o ponteiro da pilha seja válido
*     Assertivas de saída:
*     - Valor em qtd corresponde a quantidade de cartas da pilha
*
***********************************************************************/

PIL_tpCondRet PIL_QuantidadeCartas(PIL_tpPilha pPilha, int *qtd);

#undef PILHACARTAS_EXT

/********** Fim do módulo de definição: PIL Pilha **********/

#else
#endif
