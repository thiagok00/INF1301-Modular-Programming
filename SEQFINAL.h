#if ! defined( SEQFINAL_ )
#define SEQFINAL_
/***************************************************************************
*
*  $MCD Módulo de definição: FIN SEQFINAL
*
*  Arquivo gerado:              SEQFINAL.h
*  Letras identificadoras:      FIN
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
*		4		thk	  25/maio/2015  finalizado para entrega 3
*		3		thk	  29/abr/2015	fim do desenvolvimento para entrega2
*		2		thk	  28/abr/2015	conserto de funçoes
*		1       thk   27/abr/2015	início desenvolvimento
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

#if defined( SEQFINAL_OWN )
   #define SEQFINAL_EXT
#else
   #define SEQFINAL_EXT extern
#endif

#include "PILHACARTAS.h"

/* Tipo referência para uma sequencia final */
typedef struct FIN_tagSeqFin * FIN_tpSeqFin;

/***********************************************************************
*
*  $TC Tipo de dados: FIN Condições de retorno
*
*
*  $ED Descrição do tipo
*     Condições de retorno das funções de Sequencia Final
*
***********************************************************************/

typedef enum {

         FIN_CondRetOK ,
               /* Concluiu corretamente */

		 FIN_CondRetSeqFinalVazia,


		 FIN_CondRetSeqFinalNaoExiste,
			  /* Sequencia Final Inexistente */
		 
		 FIN_CondRetFaltouMemoria,
			
		 
		 FIN_CondRetSeqFinalJaCompleta,
				/* Sequencia Final completa tenetou ser inicializada */

		 FIN_CondRetMovimentoInvalido
				/* Caso a pilha a ser inicializada nao tenha as 13 cartas */



   } FIN_tpCondRet ;

/***********************************************************************
*
*  $FC Função: SEQ  &Criar SequenciaFinal
*
*  $ED Descrição da função
*		Cria uma sequência final, seus dados devem ser passados para criação.
*
*  $EP Parâmetros
*     pSequencia - Endereço de ponteiro para a sequência final
*
*  $FV Valor retornado
*     FIN_CondRetOk - se a função funcionar perfeitamente
*     FIN_CondRetFaltouMemoria - se faltou memória para criar a seqFinal
*     Não será dada mais informação quanto ao problema ocorrido.
*
*     Assertivas de entrada: 
*     - É esperado um endereço de ponteiro válido para a seqFinal
*     - É esperado que possua espaço na memória
*     Assertivas de saída:
*     - A sequência final foi criada com sucesso
*
***********************************************************************/

FIN_tpCondRet FIN_CriarSeqFinal (FIN_tpSeqFin *pSequencia);

/***********************************************************************
*
*  $FC Função: SEQ  &Destruir SequenciaFinal
*
*  $ED Descrição da função
*		Destrói uma sequência final, seus dados devem ser passados para destruição.
*
*  $EP Parâmetros
*     pSequencia - ponteiro para a sequência final
*
*  $FV Valor retornado
*     FIN_CondRetOk - se a função funcionar perfeitamente
*     FIN_CondRetSeqNaoExiste - se a sequência final é nula
*     Não será dada mais informação quanto ao problema ocorrido.
*
*     Assertivas de entrada: 
*     - É esperado um endereço de ponteiro válido para a seqFinal
*     Assertivas de saída:
*     - A sequência final foi destruida com sucesso
*
***********************************************************************/

FIN_tpCondRet FIN_DestruirSeqFinal (FIN_tpSeqFin pSequencia);

/***********************************************************************
*
*  $FC Função: SEQ  &Esvaziar SequenciaFinal
*
*  $ED Descrição da função
*		Destrói uma sequência final, seus dados devem ser passados para esvaziar.
*
*  $EP Parâmetros
*     pSequencia - ponteiro para a sequência final
*
*  $FV Valor retornado
*     FIN_CondRetOk - se a função funcionar perfeitamente
*     FIN_CondRetSeqNaoExiste - se a sequência final é nula
*     Não será dada mais informação quanto ao problema ocorrido.
*
*     Assertivas de entrada: 
*     - É esperado um endereço de ponteiro válido para a seqFinal
*     Assertivas de saída:
*     - A sequência final foi esvaziada com sucesso
*
***********************************************************************/

FIN_tpCondRet FIN_EsvaziarSeqFinal (FIN_tpSeqFin pSequencia);

/***********************************************************************
*
*  $FC Função: SEQ  &Adicionar Pilha em SequenciaFinal
*
*  $ED Descrição da função
*		Adiciona uma pilha em uma sequência final.
*
*  $EP Parâmetros
*     pSequencia - ponteiro para a sequência final
*     pPilha - ponteiro para a pilha a ser adicionada
*
*  $FV Valor retornado
*     FIN_CondRetOk - se a função funcionar perfeitamente
*     FIN_CondRetSeqFinalJaCompleta - caso a sequência final em questão ja esteja preenchida
*     FIN_CondRetMovimentoInvalido - caso a pilha não seja uma sequência completa
*     FIN_CondRetFaltouMemoria - se faltou memória para criar a seqFinal
*     Não será dada mais informação quanto ao problema ocorrido.
*
*     Assertivas de entrada: 
*     - É esperado um endereço de ponteiro válido para a seqFinal
*     - É esperado uma pilha que já esteja na ordem certa (de A a K, com mesmo naipe)
*     Assertivas de saída:
*     - A sequência final foi preenchida com a pilha em questão com sucesso.
*
***********************************************************************/
FIN_tpCondRet FIN_AdicionarPilhaEmSeqFinal(FIN_tpSeqFin pSequencia, PIL_tpPilha pPilha);

/***********************************************************************
*
*  $FC Função: SEQ  &Seq Final Esta Completa
*
*  $ED Descrição da função
*		Verifica se a sequencia final ja esta completa.
*
*  $EP Parâmetros
*     pSeqFin - ponteiro para a sequência final
*
*  $FV Valor retornado
*     FIN_CondRetOk - se a sequencia final estiver completa
*	  FIN_CondRetSeqFinalVazia
*	  FIN_CondRetSeqFinalNaoExiste
*
*     Assertivas de entrada: 
*     - É esperado um endereço de ponteiro válido para a seqFinal
*     Assertivas de saída:
*     - Estado atual da sequencia final
*
***********************************************************************/
FIN_tpCondRet FIN_SeqFinalEstaCompleta (FIN_tpSeqFin pSeqFin);

/***********************************************************************
*
*  $FC Função: SEQ  &Imprimir Seq Fin
*
*  $ED Descrição da função
*		Imprime a pilha de cartas da sequencia final
*
*  $EP Parâmetros
*     pSeqFin - ponteiro para a sequência final
*
*  $FV Valor retornado
*     FIN_CondRetOK
*	  FIN_CondRetSeqFinalVazia
*	  FIN_CondRetSeqFinalNaoExiste
*
*     Assertivas de entrada: 
*     - É esperado um endereço de ponteiro válido para a seqFinal
*     Assertivas de saída:
*     - Imprime a pilha de cartas da sequencia final
*
***********************************************************************/

FIN_tpCondRet FIN_ImprimirSeqFin( FIN_tpSeqFin pSeqFin);

/***********************************************************************
*
*  $FC Função: FIN  &Obter Pilha Seq Fin
*
*  $ED Descrição da função
*		Obtem a pilha de cartas da sequencia final
*
*  $EP Parâmetros
*     pSeqFin - ponteiro para a sequência final
*	  *pPilha - endereço de ponteiro para pilha
*
*  $FV Valor retornado
*     FIN_CondRetOk
*	  FIN_CondRetSeqFinalNaoExiste
*	  FIN_CondRetFaltouMemoria
*
*     Assertivas de entrada: 
*     - É esperado um endereço de ponteiro válido para a seqFinal
*     Assertivas de saída:
*     - pPilha contem o endereço da pilha de cartas da sequencia final e sequencia final vazia
*
***********************************************************************/

FIN_tpCondRet FIN_ObterPilhaSeqFin( FIN_tpSeqFin pSeqFin, PIL_tpPilha *pPilha);


#undef SEQFINAL_EXT
/********** Fim do módulo de definição: FIN  SeqFinal **********/
#else
#endif