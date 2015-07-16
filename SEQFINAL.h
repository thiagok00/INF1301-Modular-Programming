#if ! defined( SEQFINAL_ )
#define SEQFINAL_
/***************************************************************************
*
*  $MCD M�dulo de defini��o: FIN SEQFINAL
*
*  Arquivo gerado:              SEQFINAL.h
*  Letras identificadoras:      FIN
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
*		4		thk	  25/maio/2015  finalizado para entrega 3
*		3		ilg	  29/abr/2015	fim do desenvolvimento para entrega2
*		2		adp	  28/abr/2015	conserto de fun�oes
*		1       thk   27/abr/2015	in�cio desenvolvimento
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

#if defined( SEQFINAL_OWN )
   #define SEQFINAL_EXT
#else
   #define SEQFINAL_EXT extern
#endif

#include "PILHACARTAS.h"

/* Tipo refer�ncia para uma sequencia final */
typedef struct FIN_tagSeqFin * FIN_tpSeqFin;

/***********************************************************************
*
*  $TC Tipo de dados: FIN Condi��es de retorno
*
*
*  $ED Descri��o do tipo
*     Condi��es de retorno das fun��es de Sequencia Final
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
*  $FC Fun��o: SEQ  &Criar SequenciaFinal
*
*  $ED Descri��o da fun��o
*		Cria uma sequ�ncia final, seus dados devem ser passados para cria��o.
*
*  $EP Par�metros
*     pSequencia - Endere�o de ponteiro para a sequ�ncia final
*
*  $FV Valor retornado
*     FIN_CondRetOk - se a fun��o funcionar perfeitamente
*     FIN_CondRetFaltouMemoria - se faltou mem�ria para criar a seqFinal
*     N�o ser� dada mais informa��o quanto ao problema ocorrido.
*
*     Assertivas de entrada: 
*     - � esperado um endere�o de ponteiro v�lido para a seqFinal
*     - � esperado que possua espa�o na mem�ria
*     Assertivas de sa�da:
*     - A sequ�ncia final foi criada com sucesso
*
***********************************************************************/

FIN_tpCondRet FIN_CriarSeqFinal (FIN_tpSeqFin *pSequencia);

/***********************************************************************
*
*  $FC Fun��o: SEQ  &Destruir SequenciaFinal
*
*  $ED Descri��o da fun��o
*		Destr�i uma sequ�ncia final, seus dados devem ser passados para destrui��o.
*
*  $EP Par�metros
*     pSequencia - ponteiro para a sequ�ncia final
*
*  $FV Valor retornado
*     FIN_CondRetOk - se a fun��o funcionar perfeitamente
*     FIN_CondRetSeqNaoExiste - se a sequ�ncia final � nula
*     N�o ser� dada mais informa��o quanto ao problema ocorrido.
*
*     Assertivas de entrada: 
*     - � esperado um endere�o de ponteiro v�lido para a seqFinal
*     Assertivas de sa�da:
*     - A sequ�ncia final foi destruida com sucesso
*
***********************************************************************/

FIN_tpCondRet FIN_DestruirSeqFinal (FIN_tpSeqFin pSequencia);

/***********************************************************************
*
*  $FC Fun��o: SEQ  &Esvaziar SequenciaFinal
*
*  $ED Descri��o da fun��o
*		Destr�i uma sequ�ncia final, seus dados devem ser passados para esvaziar.
*
*  $EP Par�metros
*     pSequencia - ponteiro para a sequ�ncia final
*
*  $FV Valor retornado
*     FIN_CondRetOk - se a fun��o funcionar perfeitamente
*     FIN_CondRetSeqNaoExiste - se a sequ�ncia final � nula
*     N�o ser� dada mais informa��o quanto ao problema ocorrido.
*
*     Assertivas de entrada: 
*     - � esperado um endere�o de ponteiro v�lido para a seqFinal
*     Assertivas de sa�da:
*     - A sequ�ncia final foi esvaziada com sucesso
*
***********************************************************************/

FIN_tpCondRet FIN_EsvaziarSeqFinal (FIN_tpSeqFin pSequencia);

/***********************************************************************
*
*  $FC Fun��o: SEQ  &Adicionar Pilha em SequenciaFinal
*
*  $ED Descri��o da fun��o
*		Adiciona uma pilha em uma sequ�ncia final.
*
*  $EP Par�metros
*     pSequencia - ponteiro para a sequ�ncia final
*     pPilha - ponteiro para a pilha a ser adicionada
*
*  $FV Valor retornado
*     FIN_CondRetOk - se a fun��o funcionar perfeitamente
*     FIN_CondRetSeqFinalJaCompleta - caso a sequ�ncia final em quest�o ja esteja preenchida
*     FIN_CondRetMovimentoInvalido - caso a pilha n�o seja uma sequ�ncia completa
*     FIN_CondRetFaltouMemoria - se faltou mem�ria para criar a seqFinal
*     N�o ser� dada mais informa��o quanto ao problema ocorrido.
*
*     Assertivas de entrada: 
*     - � esperado um endere�o de ponteiro v�lido para a seqFinal
*     - � esperado uma pilha que j� esteja na ordem certa (de A a K, com mesmo naipe)
*     Assertivas de sa�da:
*     - A sequ�ncia final foi preenchida com a pilha em quest�o com sucesso.
*
***********************************************************************/
FIN_tpCondRet FIN_AdicionarPilhaEmSeqFinal(FIN_tpSeqFin pSequencia, PIL_tpPilha pPilha);

/***********************************************************************
*
*  $FC Fun��o: SEQ  &Seq Final Esta Completa
*
*  $ED Descri��o da fun��o
*		Verifica se a sequencia final ja esta completa.
*
*  $EP Par�metros
*     pSeqFin - ponteiro para a sequ�ncia final
*
*  $FV Valor retornado
*     FIN_CondRetOk - se a sequencia final estiver completa
*	  FIN_CondRetSeqFinalVazia
*	  FIN_CondRetSeqFinalNaoExiste
*
*     Assertivas de entrada: 
*     - � esperado um endere�o de ponteiro v�lido para a seqFinal
*     Assertivas de sa�da:
*     - Estado atual da sequencia final
*
***********************************************************************/
FIN_tpCondRet FIN_SeqFinalEstaCompleta (FIN_tpSeqFin pSeqFin);

/***********************************************************************
*
*  $FC Fun��o: SEQ  &Imprimir Seq Fin
*
*  $ED Descri��o da fun��o
*		Imprime a pilha de cartas da sequencia final
*
*  $EP Par�metros
*     pSeqFin - ponteiro para a sequ�ncia final
*
*  $FV Valor retornado
*     FIN_CondRetOK
*	  FIN_CondRetSeqFinalVazia
*	  FIN_CondRetSeqFinalNaoExiste
*
*     Assertivas de entrada: 
*     - � esperado um endere�o de ponteiro v�lido para a seqFinal
*     Assertivas de sa�da:
*     - Imprime a pilha de cartas da sequencia final
*
***********************************************************************/

FIN_tpCondRet FIN_ImprimirSeqFin( FIN_tpSeqFin pSeqFin);

/***********************************************************************
*
*  $FC Fun��o: FIN  &Obter Pilha Seq Fin
*
*  $ED Descri��o da fun��o
*		Obtem a pilha de cartas da sequencia final
*
*  $EP Par�metros
*     pSeqFin - ponteiro para a sequ�ncia final
*	  *pPilha - endere�o de ponteiro para pilha
*
*  $FV Valor retornado
*     FIN_CondRetOk
*	  FIN_CondRetSeqFinalNaoExiste
*	  FIN_CondRetFaltouMemoria
*
*     Assertivas de entrada: 
*     - � esperado um endere�o de ponteiro v�lido para a seqFinal
*     Assertivas de sa�da:
*     - pPilha contem o endere�o da pilha de cartas da sequencia final e sequencia final vazia
*
***********************************************************************/

FIN_tpCondRet FIN_ObterPilhaSeqFin( FIN_tpSeqFin pSeqFin, PIL_tpPilha *pPilha);


#undef SEQFINAL_EXT
/********** Fim do m�dulo de defini��o: FIN  SeqFinal **********/
#else
#endif