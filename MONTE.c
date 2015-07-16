/***************************************************************************
*  $MCI M�dulo de implementa��o: MON  Monte
*
*  Arquivo gerado:              MONTE.c
*  Letras identificadoras:      MON
*
*  Nome da base de software:    Paci�ncia Spider
*  Arquivo da base de software: 
*
*  Projeto: INF 1301 Paci�ncia Spider
*  Gestor:  LES/DI/PUC-Rio
*  Autores: adp, ilg ,thk
*
*  $HA Hist�rico de evolu��o:
*     Vers�o  Autor    Data     Observa��es
*	  3       adp   29/04/2015  ajustes nos comentarios e condi��es de retorno
*	  2		  ilg	21/04/2015  t�rmino de desenvolvimento da vers�o 1
*     1       ilg   20/abr/2015 in�cio desenvolvimento
*
***************************************************************************/
# include <stdio.h>
# include <stdlib.h>
# include "MONTE.h"
# include "CARTA.h"
# define TOTAL_MONTE 10 

/***********************************************************************
*
*  $TC Tipo de dados: MON Descritor da cabe�a de monte
*
*
***********************************************************************/
typedef struct MON_tagMonte {
	int cheio;
	PIL_tpPilha cabeca;
} MON_tppMonte;


/*****  C�digo das fun��es encapsuladas no m�dulo  *****/
static MON_tpCondRet MON_MoverEntrePilhas (PIL_tpPilha pPilhaOrigem, PIL_tpPilha  pPilhaDestino,int tam);

/*****  C�digo das fun��es exportadas pelo m�dulo  *****/

/***************************************************************************
*
*  Fun��o: MON  &Criar Monte Compras
*  ****/
MON_tpCondRet MON_CriarMonteCompras(MON_tpMonte * pMonte) {
	
	PIL_tpCondRet pilhaRet;

		*pMonte = (MON_tppMonte*) malloc (sizeof(MON_tppMonte));

		if (*pMonte == NULL) 
			return MON_CondRetFaltouMemoria;
		
		pilhaRet = PIL_CriarPilhaCartas ( &(*pMonte)->cabeca);

		if (pilhaRet == PIL_CondRetFaltouMemoria)
			return MON_CondRetFaltouMemoria;

		(*pMonte)->cheio = 0;

		return MON_CondRetOK;
}	/* Fim fun��o: MON  &Criar Monte Compras */

/***************************************************************************
*
*  Fun��o: MON  &Destruir Monte Compras
*  ****/
MON_tpCondRet MON_DestruirMonteCompras(MON_tpMonte pMonte) {

	PIL_tpCondRet condRetPilha;

	if (pMonte == NULL)
		return MON_CondRetMonteNaoExiste;

	condRetPilha = PIL_DestruirPilhaCartas(pMonte->cabeca);

	if (condRetPilha != PIL_CondRetOK) {

		free(pMonte);
		return MON_CondRetMonteVazio;
	}

	free(pMonte);

	return MON_CondRetOK;
}	/* Fim fun��o: MON  &Destruir Monte Compras */

/***************************************************************************
*
*  Fun��o: MON  &Esvaziar Monte Compras
*  ****/
MON_tpCondRet MON_EsvaziarMonteCompras(MON_tpMonte pMonte) {

	PIL_tpCondRet condRetPil;
	
	condRetPil = PIL_EsvaziarPilhaCartas(pMonte->cabeca);
	
	if(condRetPil != PIL_CondRetOK)
		return MON_CondRetMonteNaoExiste;
	
	pMonte->cheio = 0;

	return MON_CondRetOK;
}	/* Fim fun��o: MON  &Esvaziar Monte Compras */

/***************************************************************************
*
*  Fun��o: MON  &Adicionar Ao Monte Compras
*  ****/
MON_tpCondRet MON_AdicionarAoMonteCompras(MON_tpMonte pMonte, PIL_tpPilha pPilha) {

	MON_tpCondRet condRetMonte;

	if (pMonte == NULL) {
		return MON_CondRetMonteNaoExiste;
	}


	if (pMonte->cheio)
		return MON_CondRetMonteCheio;
	
	condRetMonte =  MON_MoverEntrePilhas (pPilha, pMonte->cabeca,TOTAL_MONTE);

	if (condRetMonte == MON_CondRetOK)
		pMonte->cheio = 1;

	return condRetMonte;
}	/* Fim fun��o: MON  &Adicionar Ao Monte Compras */

/***************************************************************************
*
*  Fun��o: MON  &Retornar Compra
* 
* ****/

MON_tpCondRet MON_RetornarCompra (MON_tpMonte pMonte, PIL_tpPilha pPilha) {

	MON_tpCondRet condRetMonte;

	if (pMonte == NULL)
		return MON_CondRetMonteNaoExiste;

	if (!pMonte->cheio)
		return MON_CondRetMonteVazio;


	condRetMonte =  MON_MoverEntrePilhas (pMonte->cabeca, pPilha,TOTAL_MONTE);

	if (condRetMonte == MON_CondRetOK)
		pMonte->cheio = 0;

	return condRetMonte;

}	/* Fim fun��o: MON  &Retornar Compras */

/***************************************************************************
*
*  Fun��o: MON  &Imprimir Monte Compras
* 
* ****/
MON_tpCondRet MON_ImprimirMonteCompras (MON_tpMonte pMonte) {

	PIL_tpCondRet condRetPilha;

	condRetPilha = PIL_ImprimirPilhaCartas(pMonte->cabeca);

	if (condRetPilha == PIL_CondRetPilhaVazia)
		return MON_CondRetMonteVazio;

	if (condRetPilha == PIL_CondRetOK)
		return MON_CondRetOK;
	else
		return MON_CondRetMonteNaoExiste;
}	/* Fim fun��o: MON  &Imprimir Monte Compras */

/***************************************************************************
*
*  Fun��o: MON  &Monte De Compras Disponivel
* 
* ****/
MON_tpCondRet MON_MonteComprasDisponivel (MON_tpMonte pMonte){

	if (pMonte == NULL)
		return MON_CondRetMonteNaoExiste;

	if (pMonte->cheio == 1)
		return MON_CondRetOK;
	else
		return MON_CondRetMonteVazio;

}

/*****  C�digo das fun��es encapsuladas no m�dulo  *****/

/***********************************************************************
*
*  $FC Fun��o: MON  Mover Entre Pilhas
*
*  $ED Descri��o da fun��o
*		Transfere 'tam' cartas de pilha origem para pilha destino
*
***********************************************************************/

MON_tpCondRet MON_MoverEntrePilhas (PIL_tpPilha pPilhaOrigem, PIL_tpPilha  pPilhaDestino,int tam) {
		int i;
		PIL_tpCondRet condRetPilha;

		if(PIL_IrInicioPilhaCartas(pPilhaOrigem) != PIL_CondRetOK)
			return MON_CondRetFaltamCartas;
		

		if(PIL_IrInicioPilhaCartas(pPilhaDestino) != PIL_CondRetOK)
		return MON_CondRetFaltamCartas;

		/* verificando se tem "TAM" cartas*/
		condRetPilha = PIL_AvancarElementoCorrente(pPilhaOrigem, tam-1);
		if (condRetPilha != PIL_CondRetOK)
			return MON_CondRetFaltamCartas;

		
		for (i=0 ; i < tam ; i++) {
	
		CAR_tpCarta carta;
	
		
		condRetPilha=PIL_RemoverCarta(pPilhaOrigem,&carta);

		if (condRetPilha == PIL_CondRetFaltouMemoria)
		    return MON_CondRetFaltouMemoria;
		
		condRetPilha=PIL_AdicionarCarta(pPilhaDestino,carta);
		
		if (condRetPilha == PIL_CondRetFaltouMemoria)
		    return MON_CondRetFaltouMemoria;
	}
	return MON_CondRetOK;
}	/* Fim fun��o: MON  &Mover Entre Pilhas */

/********** Fim do m�dulo de implementa��o: MON  Monte	**********/