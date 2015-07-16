/***************************************************************************
*  $MCI Módulo de implementação: FIN SEQUENCIA FINAL
*
*  Arquivo gerado:              SEQFINAL.c
*  Letras identificadoras:      FIN
*
*  Nome da base de software:    Paciência Spider
*  Arquivo da base de software: 
*
*  Projeto: INF 1301 Paciência Spider
*  Gestor:  LES/DI/PUC-Rio
*  Autores: adp,ilg , thk
*
*  $HA Histórico de evolução:
*     Versão  Autor    Data     Observações
*		3		thk	  29/abr/2017	fim do desenvolvimento para entrega
*		2		thk	  28/abr/2015	conserto de funçoes
*		1       thk   27/abr/2015	início desenvolvimento
*
***************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include "SEQFINAL.h"
#include "CARTA.h"

/***********************************************************************
*
*  $TC Tipo de dados: FIN Descritor da cabeça da sequencia final
*
*
***********************************************************************/
typedef struct FIN_tagSeqFin {
	int preenchida;
	PIL_tpPilha cabeca;

} FIN_tppSeqFin;

/*****  Código das funções exportadas pelo módulo  *****/

/***************************************************************************
*
*  Função: FIN  &Criar Sequencia Final
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
} /* Fim função: FIN  Criar Sequencia Final */

/***************************************************************************
*
*  Função: FIN  &Destruir Sequencia Final
*  ****/
FIN_tpCondRet FIN_DestruirSeqFinal (FIN_tpSeqFin pSequencia) {
	
	PIL_tpCondRet condRetPil;
	condRetPil = PIL_DestruirPilhaCartas (pSequencia->cabeca);
	
	if(condRetPil != PIL_CondRetOK)
		return FIN_CondRetSeqFinalNaoExiste;

	return FIN_CondRetOK;
} /* Fim função: FIN  Destruir Sequencia Final */

/***************************************************************************
*
*  Função: FIN  &Esvaziar Sequencia Final
*  ****/
FIN_tpCondRet FIN_EsvaziarSeqFinal (FIN_tpSeqFin pSequencia) {

	PIL_tpCondRet condRetPil;
	
	condRetPil = PIL_EsvaziarPilhaCartas(pSequencia->cabeca);
	
	if(condRetPil != PIL_CondRetOK)
		return FIN_CondRetSeqFinalNaoExiste;


	pSequencia->preenchida = 0;

	return FIN_CondRetOK;

} /* Fim função: FIN  Esvaziar Sequencia Final */
/***************************************************************************
*
*  Função: FIN  &Adicionar Pilha Em Sequencia Final
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

} /* Fim função: FIN  Adicionar Pil Em Seq Fin */

/***************************************************************************
*
*  Função: FIN  &Seq Final Esta Completa
*  ****/
FIN_tpCondRet FIN_SeqFinalEstaCompleta (FIN_tpSeqFin pSeqFin) {

	if( pSeqFin == NULL )
		return FIN_CondRetSeqFinalNaoExiste;


	if(pSeqFin->preenchida == 1)
		return FIN_CondRetOK;
	else
		return FIN_CondRetSeqFinalVazia;
}	/* Fim função: FIN  Seq Final Esta Completa */

/***************************************************************************
*
*  Função: FIN  &Imprimir Seq Fin
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

}	/* Fim função: FIN  Imprimir Seq Fin */
/***************************************************************************
*
*  Função: FIN  &FIN_ObterPilhaSeqFin
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

/********** Fim do módulo de implementação: FIN  Sequencia Final **********/