/***************************************************************************
*  $MCI Módulo de implementação: CAR  Carta
*
*  Arquivo gerado:              CARTA.c
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

/*****  Código das funções exportadas pelo módulo  *****/

/***************************************************************************
*
*  Função: CAR  &Criar Carta
*  ****/

CAR_tpCondRet CAR_CriarCarta(CAR_tpCarta *carta, CAR_tpValor valor, CAR_tpNaipe naipe) {


		
		(*carta) = ( CAR_tppCarta * ) malloc( sizeof( CAR_tppCarta )) ;
		if ( (*carta) == NULL)
			return CAR_CondRetFaltouMemoria;

		(*carta)->naipe = naipe;
		(*carta)->valor = valor;
		(*carta)->estado = CAR_EstadoVisivel;

	return CAR_CondRetOK;

} /* Fim função: CAR  &Criar Carta */


/***************************************************************************
*
*  Função: CAR  &Destruir Carta
*  ****/

void CAR_DestruirCarta(void* pCarta) {
	
	CAR_tpCarta pCartaAux = (CAR_tpCarta) pCarta;
	
	if (pCarta == NULL)
		return;

	free(pCartaAux);

} /* Fim função: CAR  &Criar Carta */

/***************************************************************************
*
*  Função: CAR  &Obter Valor
*  ****/
CAR_tpCondRet CAR_ObterValor(CAR_tpCarta pCarta, CAR_tpValor *pValor) {

	if (pCarta == NULL)
		return CAR_CondRetCartaVazia;
	
		
	*pValor =  pCarta->valor;
	
	if (pCarta->estado == CAR_EstadoInvisivel)
		return CAR_CondRetCartaInvisivel;
		
		
		

		return CAR_CondRetOK;
} /* Fim função: CAR  &Obter Valor */


/***************************************************************************
*
*  Função: CAR  &Obter Naipe
*  ****/
CAR_tpCondRet CAR_ObterNaipe(CAR_tpCarta pCarta, CAR_tpNaipe *pNaipe ) {
	
	if (pCarta == NULL)
		return CAR_CondRetCartaVazia;
	
	*pNaipe =  pCarta->naipe;
		
	if (pCarta->estado == CAR_EstadoInvisivel)
		return CAR_CondRetCartaInvisivel;
		

		
		return CAR_CondRetOK;
} /* Fim função: CAR  &Obter Naipe */

/***************************************************************************
*
*  Função: CAR  &Obter Estado
*  ****/

CAR_tpCondRet CAR_ObterEstado(CAR_tpCarta pCarta,CAR_tpEstado *pEstado) {

	if (pCarta == NULL)
		return CAR_CondRetCartaVazia;

	*pEstado = pCarta->estado;
	
	return CAR_CondRetOK;
} /* Fim função: CAR  &Obter Estado */

/***************************************************************************
*
*  Função: CAR  &Tornar Visivel
*  ****/
CAR_tpCondRet CAR_TornarVisivel(CAR_tpCarta pCarta ) {
	
	if (pCarta == NULL)
		return CAR_CondRetCartaVazia;

	pCarta->estado = CAR_EstadoVisivel;
	return CAR_CondRetOK;
	
} /* Fim função: CAR  &Tornar Visivel */

/***************************************************************************
*
*  Função: CAR  &Tornar Invisivel
*  ****/

CAR_tpCondRet CAR_TornarInvisivel(CAR_tpCarta pCarta ) {
	
	if (pCarta == NULL)
		return CAR_CondRetCartaVazia;

	pCarta->estado = CAR_EstadoInvisivel;
	
	return CAR_CondRetOK;

} /* Fim função: CAR  &Tornar Invisivel */

/********** Fim do módulo de implementação: CAR  Carta **********/

