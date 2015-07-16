/***************************************************************************
*  $MCI M�dulo de implementa��o: CAR  Carta
*
*  Arquivo gerado:              CARTA.c
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
***************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include "CARTA.h"

/***********************************************************************
*
*  $TC Tipo de dados: CAR Carta
*
*
***********************************************************************/
typedef struct carta {

	CAR_tpValor valor;
	CAR_tpNaipe naipe;
	CAR_tpEstado estado;


} CAR_tppCarta;

/*****  C�digo das fun��es exportadas pelo m�dulo  *****/

/***************************************************************************
*
*  Fun��o: CAR  &Criar Carta
*  ****/

CAR_tpCondRet CAR_CriarCarta(CAR_tpCarta *carta, CAR_tpValor valor, CAR_tpNaipe naipe) {


		
		(*carta) = ( CAR_tppCarta * ) malloc( sizeof( CAR_tppCarta )) ;
		if ( (*carta) == NULL)
			return CAR_CondRetFaltouMemoria;

		(*carta)->naipe = naipe;
		(*carta)->valor = valor;
		(*carta)->estado = CAR_EstadoVisivel;

	return CAR_CondRetOK;

} /* Fim fun��o: CAR  &Criar Carta */


/***************************************************************************
*
*  Fun��o: CAR  &Destruir Carta
*  ****/

void CAR_DestruirCarta(void* pCarta) {
	
	CAR_tpCarta pCartaAux = (CAR_tpCarta) pCarta;
	
	if (pCarta == NULL)
		return;

	free(pCartaAux);

} /* Fim fun��o: CAR  &Criar Carta */

/***************************************************************************
*
*  Fun��o: CAR  &Obter Valor
*  ****/
CAR_tpCondRet CAR_ObterValor(CAR_tpCarta pCarta, CAR_tpValor *pValor) {

	if (pCarta == NULL)
		return CAR_CondRetCartaVazia;
	
		
	*pValor =  pCarta->valor;
	
	if (pCarta->estado == CAR_EstadoInvisivel)
		return CAR_CondRetCartaInvisivel;
		
		
		

		return CAR_CondRetOK;
} /* Fim fun��o: CAR  &Obter Valor */


/***************************************************************************
*
*  Fun��o: CAR  &Obter Naipe
*  ****/
CAR_tpCondRet CAR_ObterNaipe(CAR_tpCarta pCarta, CAR_tpNaipe *pNaipe ) {
	
	if (pCarta == NULL)
		return CAR_CondRetCartaVazia;
	
	*pNaipe =  pCarta->naipe;
		
	if (pCarta->estado == CAR_EstadoInvisivel)
		return CAR_CondRetCartaInvisivel;
		

		
		return CAR_CondRetOK;
} /* Fim fun��o: CAR  &Obter Naipe */

/***************************************************************************
*
*  Fun��o: CAR  &Obter Estado
*  ****/

CAR_tpCondRet CAR_ObterEstado(CAR_tpCarta pCarta,CAR_tpEstado *pEstado) {

	if (pCarta == NULL)
		return CAR_CondRetCartaVazia;

	*pEstado = pCarta->estado;
	
	return CAR_CondRetOK;
} /* Fim fun��o: CAR  &Obter Estado */

/***************************************************************************
*
*  Fun��o: CAR  &Tornar Visivel
*  ****/
CAR_tpCondRet CAR_TornarVisivel(CAR_tpCarta pCarta ) {
	
	if (pCarta == NULL)
		return CAR_CondRetCartaVazia;

	pCarta->estado = CAR_EstadoVisivel;
	return CAR_CondRetOK;
	
} /* Fim fun��o: CAR  &Tornar Visivel */

/***************************************************************************
*
*  Fun��o: CAR  &Tornar Invisivel
*  ****/

CAR_tpCondRet CAR_TornarInvisivel(CAR_tpCarta pCarta ) {
	
	if (pCarta == NULL)
		return CAR_CondRetCartaVazia;

	pCarta->estado = CAR_EstadoInvisivel;
	
	return CAR_CondRetOK;

} /* Fim fun��o: CAR  &Tornar Invisivel */

/********** Fim do m�dulo de implementa��o: CAR  Carta **********/

