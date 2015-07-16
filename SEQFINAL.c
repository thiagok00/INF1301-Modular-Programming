/***************************************************************************
*  $MCI M�dulo de implementa��o: FIN SEQUENCIA FINAL
*
*  Arquivo gerado:              SEQFINAL.c
*  Letras identificadoras:      FIN
*
*  Nome da base de software:    Paci�ncia Spider
*  Arquivo da base de software: 
*
*  Projeto: INF 1301 Paci�ncia Spider
*  Gestor:  LES/DI/PUC-Rio
*  Autores: adp,ilg , thk
*
*  $HA Hist�rico de evolu��o:
*     Vers�o  Autor    Data     Observa��es
*		3		ilg	  29/abr/2017	fim do desenvolvimento para entrega
*		2		adp	  28/abr/2015	conserto de fun�oes
*		1       thk   27/abr/2015	in�cio desenvolvimento
*
***************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include "SEQFINAL.h"
#include "CARTA.h"

/***********************************************************************
*
*  $TC Tipo de dados: FIN Descritor da cabe�a da sequencia final
*
*
***********************************************************************/
typedef struct FIN_tagSeqFin {
	int preenchida;
	PIL_tpPilha cabeca;

} FIN_tppSeqFin;

/*****  C�digo das fun��es exportadas pelo m�dulo  *****/

/***************************************************************************
*
*  Fun��o: FIN  &Criar Sequencia Final
*  ****/
FIN_tpCondRet FIN_CriarSeqFinal (FIN_tpSeqFin *pSequencia) {
	
		PIL_tpCondRet CondRetPilha;

		*pSequencia = (FIN_tppSeqFin*) malloc (sizeof(FIN_tppSeqFin));
		if  (*pSequencia == NULL)
			return FIN_CondRetFaltouMemoria;

		CondRetPilha = PIL_CriarPilhaCartas (&(*pSequencia)->cabeca);

		if (CondRetPilha == PIL_CondRetFaltouMemoria)
			return FIN_CondRetFaltouMemoria;

		(*pSequencia)->preenchida = 0;

	return FIN_CondRetOK;
} /* Fim fun��o: FIN  Criar Sequencia Final */

/***************************************************************************
*
*  Fun��o: FIN  &Destruir Sequencia Final
*  ****/
FIN_tpCondRet FIN_DestruirSeqFinal (FIN_tpSeqFin pSequencia) {
	
	PIL_tpCondRet condRetPil;
	condRetPil = PIL_DestruirPilhaCartas (pSequencia->cabeca);
	
	if(condRetPil != PIL_CondRetOK)
		return FIN_CondRetSeqFinalNaoExiste;

	return FIN_CondRetOK;
} /* Fim fun��o: FIN  Destruir Sequencia Final */

/***************************************************************************
*
*  Fun��o: FIN  &Esvaziar Sequencia Final
*  ****/
FIN_tpCondRet FIN_EsvaziarSeqFinal (FIN_tpSeqFin pSequencia) {

	PIL_tpCondRet condRetPil;
	
	condRetPil = PIL_EsvaziarPilhaCartas(pSequencia->cabeca);
	
	if(condRetPil != PIL_CondRetOK)
		return FIN_CondRetSeqFinalNaoExiste;


	pSequencia->preenchida = 0;

	return FIN_CondRetOK;

} /* Fim fun��o: FIN  Esvaziar Sequencia Final */
/***************************************************************************
*
*  Fun��o: FIN  &Adicionar Pilha Em Sequencia Final
*  ****/
FIN_tpCondRet FIN_AdicionarPilhaEmSeqFinal(FIN_tpSeqFin pSequencia, PIL_tpPilha pPilha) {


	PIL_tpCondRet condRetPilha;
	int i;

	if (pSequencia == NULL)
		return FIN_CondRetSeqFinalNaoExiste;

	if (pSequencia->preenchida)
		return FIN_CondRetSeqFinalJaCompleta;


	if(PIL_IrInicioPilhaCartas(pPilha) != PIL_CondRetOK)
		return FIN_CondRetMovimentoInvalido;
		

	condRetPilha = PIL_AvancarElementoCorrente(pPilha, 12 );
	if (condRetPilha != PIL_CondRetOK)
		return FIN_CondRetMovimentoInvalido;

	for ( i = 0; i < 13 ; i++) {
	
		CAR_tpCarta carta;
		
		
		condRetPilha=PIL_RemoverCarta(pPilha,&carta);

		if (condRetPilha == PIL_CondRetFaltouMemoria)
		    return FIN_CondRetFaltouMemoria;
		
		condRetPilha=PIL_AdicionarCarta(pSequencia->cabeca,carta);
		
		if (condRetPilha == PIL_CondRetFaltouMemoria)
		    return FIN_CondRetFaltouMemoria;
	}

	pSequencia->preenchida = 1;
	return FIN_CondRetOK;

} /* Fim fun��o: FIN  Adicionar Pil Em Seq Fin */

/***************************************************************************
*
*  Fun��o: FIN  &Seq Final Esta Completa
*  ****/
FIN_tpCondRet FIN_SeqFinalEstaCompleta (FIN_tpSeqFin pSeqFin) {

	if( pSeqFin == NULL )
		return FIN_CondRetSeqFinalNaoExiste;


	if(pSeqFin->preenchida == 1)
		return FIN_CondRetOK;
	else
		return FIN_CondRetSeqFinalVazia;
}	/* Fim fun��o: FIN  Seq Final Esta Completa */

/***************************************************************************
*
*  Fun��o: FIN  &Imprimir Seq Fin
*  ****/
FIN_tpCondRet FIN_ImprimirSeqFin( FIN_tpSeqFin pSeqFin){

	PIL_tpCondRet condRetPilha;

	condRetPilha = PIL_ImprimirPilhaCartas(pSeqFin->cabeca);

	if (condRetPilha == PIL_CondRetPilhaVazia)
		return FIN_CondRetSeqFinalVazia;

	if (condRetPilha == PIL_CondRetOK)
		return FIN_CondRetOK;
	else
		return FIN_CondRetSeqFinalNaoExiste;

}	/* Fim fun��o: FIN  Imprimir Seq Fin */
/***************************************************************************
*
*  Fun��o: FIN  &FIN_ObterPilhaSeqFin
*  ****/
FIN_tpCondRet FIN_ObterPilhaSeqFin( FIN_tpSeqFin pSeqFin, PIL_tpPilha *pPilha){

	PIL_tpCondRet condRetPilha;
	if (pSeqFin == NULL)
		return FIN_CondRetSeqFinalNaoExiste;
	
	*pPilha = pSeqFin->cabeca;
	pSeqFin->preenchida = 0;
	pSeqFin->cabeca = NULL;

	condRetPilha = PIL_CriarPilhaCartas(&pSeqFin->cabeca);
	if (condRetPilha == PIL_CondRetFaltouMemoria)
		return FIN_CondRetFaltouMemoria;


	return FIN_CondRetOK;
}

/********** Fim do m�dulo de implementa��o: FIN  Sequencia Final **********/