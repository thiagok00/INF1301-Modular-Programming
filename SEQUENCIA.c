/***************************************************************************
*  $MCI M�dulo de implementa��o: SEQ SEQUENCIA
*
*  Arquivo gerado:              SEQUENCIA.c
*  Letras identificadoras:      SEQ
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
*	  3       thk   28/abr/2015 mudan�a das condi�oes de retorno
*	  2		  adp   27/abr/2015 implentacao de novas fun�oes
*	  1		  ilg   27/abr/2015	inicio desenvolvimento
*
***************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include "SEQUENCIA.h"
#include "CARTA.h"
#define TAM_SEQ_COMPLETA 13

/***********************************************************************
*
*  $TC Tipo de dados: SEQ Descritor da cabe�a da sequencia
*
*
***********************************************************************/

typedef struct SEQ_tagSequencia {

	PIL_tpPilha cabeca;

} SEQ_tppSequencia;

/***** Prot�tipos das fun��es encapuladas no m�dulo *****/
static SEQ_tpCondRet SEQ_MoverEntrePilhas (PIL_tpPilha pPilhaOrigem, PIL_tpPilha  pPilhaDestino,int tam);

/*****  C�digo das fun��es exportadas pelo m�dulo  *****/

/***************************************************************************
*
*  Fun��o: SEQ  &Criar Sequencia
*  ****/
SEQ_tpCondRet SEQ_CriarSequencia (SEQ_tpSequencia *pSequencia) {
	
		PIL_tpCondRet CondRetPilha;

		*pSequencia = (SEQ_tppSequencia*) malloc (sizeof(SEQ_tppSequencia));
		if  (*pSequencia == NULL)
			return SEQ_CondRetFaltouMemoria;

		CondRetPilha = PIL_CriarPilhaCartas (&(*pSequencia)->cabeca);

		if (CondRetPilha == PIL_CondRetFaltouMemoria)
			return SEQ_CondRetFaltouMemoria;

	return SEQ_CondRetOK;
} /* Fim fun��o: Criar Sequencia  */

/***************************************************************************
*
*  Fun��o: SEQ  &Destruir Sequencia
*  ****/
SEQ_tpCondRet SEQ_DestruirSequencia (SEQ_tpSequencia pSequencia) {
	
	PIL_tpCondRet condRetPil;
	condRetPil = PIL_DestruirPilhaCartas (pSequencia->cabeca);
	if(condRetPil != PIL_CondRetOK)
		return SEQ_CondRetSeqNaoExiste;

	return SEQ_CondRetOK;
} /* Fim fun��o: Destruir Sequencia  */

/***************************************************************************
*
*  Fun��o: SEQ  &Esvaziar Sequencia
*  ****/
SEQ_tpCondRet SEQ_EsvaziarSequencia(SEQ_tpSequencia pSequencia){
	PIL_tpCondRet condRetPil;
	
	condRetPil = PIL_EsvaziarPilhaCartas(pSequencia->cabeca);
	
	if(condRetPil != PIL_CondRetOK)
		return SEQ_CondRetSeqNaoExiste;

	return SEQ_CondRetOK;
} /* Fim fun��o: Esvaziar Sequencia  */

/***************************************************************************
*
*  Fun��o: SEQ  &Iniciar Sequencia
*  ****/
SEQ_tpCondRet SEQ_IniciarSequencia (SEQ_tpSequencia pSequencia, PIL_tpPilha pPilha,int tam) {

	if (pSequencia == NULL)
		return SEQ_CondRetSeqNaoExiste;

	return SEQ_MoverEntrePilhas(pPilha,pSequencia->cabeca,tam);
} /* Fim fun��o: Iniciar Sequencia  */

/***************************************************************************
*
*  Fun��o: SEQ  &Adicionar Pilha Em Sequencia
*  ****/
SEQ_tpCondRet SEQ_AdicionarPilhaEmSequencia (SEQ_tpSequencia pSequencia, PIL_tpPilha pPilha,int tam) {

	PIL_tpCondRet condRetPilha;
	CAR_tpCarta carta;
	CAR_tpValor valorTopo;
	CAR_tpCondRet condRetCarta;
	int existeTopo = 0 ;

	if(pSequencia == NULL)
		return SEQ_CondRetSeqNaoExiste;

	PIL_IrInicioPilhaCartas(pSequencia->cabeca);

	/* Verificando o topo da sequencia e pegando o valor */
	condRetPilha = PIL_VerCarta(pSequencia->cabeca,&carta);
	if (condRetPilha == PIL_CondRetOK){
		
		condRetCarta = CAR_ObterValor(carta,&valorTopo);
		if( condRetCarta != CAR_CondRetOK)
			return SEQ_CondRetMovimentoInvalido;

		existeTopo = 1;
	}
	/* Se existe topo verifica se a primeira da pilha � igual a 1 menos que ele */
	if(existeTopo) {
		CAR_tpValor valorAux;
		
		condRetPilha = PIL_AvancarElementoCorrente( pPilha ,tam-1);
		if (condRetPilha != PIL_CondRetOK)
			return SEQ_CondRetMovimentoInvalido;

		condRetPilha = PIL_VerCarta(pPilha,&carta);
		if (	condRetPilha != PIL_CondRetOK)
			return SEQ_CondRetMovimentoInvalido;

		condRetCarta = CAR_ObterValor(carta,&valorAux);
		if (	condRetCarta != CAR_CondRetOK || valorTopo != valorAux+1	)
			return SEQ_CondRetMovimentoInvalido;

		}
	/*	Movimento Valido entao move as Pilhas	*/
	return SEQ_MoverEntrePilhas(pPilha,pSequencia->cabeca,tam);
} /* Fim fun��o: Adicionar Pilha Em Sequencia */

/***************************************************************************
*
*  Fun��o: SEQ  &Verificar Sequencia Completa
*  ****/

SEQ_tpCondRet SEQ_VerificarSequenciaCompleta ( SEQ_tpSequencia pSequencia) {

	PIL_tpCondRet condRetPil;

	if (pSequencia == NULL)
		return SEQ_CondRetSeqNaoExiste;

	/* verificando se a sequencia tem pelo menos TAM_SEQ_COMPLETA cartas */
	condRetPil = PIL_AvancarElementoCorrente( pSequencia->cabeca ,TAM_SEQ_COMPLETA-1);
	if (condRetPil != PIL_CondRetOK)
		return SEQ_CondRetSeqNaoCompleta;
	/*****															*****/
	else {
		
		CAR_tpCarta carta;
		CAR_tpValor valorEsperado;
		CAR_tpNaipe naipeEsperado;

		CAR_tpCondRet condRetCarta;
		int i;

		PIL_VerCarta(pSequencia->cabeca,&carta);
		
		/*Verificando se a carta � um rei*/
		condRetCarta = CAR_ObterValor(carta,&valorEsperado);
		if(condRetCarta != CAR_CondRetOK || valorEsperado != _K)
			return SEQ_CondRetSeqNaoCompleta;
	
		/*Obtendo o naipe do rei*/
		condRetCarta = CAR_ObterNaipe(carta,&naipeEsperado);
		if(condRetCarta != CAR_CondRetOK)
			return SEQ_CondRetSeqNaoCompleta;

		for (i=0 ; i <12 ; i++) {
			
			CAR_tpValor valor;
			CAR_tpNaipe naipe;
			
			/* Ja � garantido que carta existe */
			PIL_AvancarElementoCorrente( pSequencia->cabeca ,-1);
			
			PIL_VerCarta(pSequencia->cabeca,&carta);
			
			/* Verificando se o valor est� na posi�ao certa */
			condRetCarta = CAR_ObterValor(carta,&valor);
			if (condRetCarta != CAR_CondRetOK || valorEsperado != (valor+i+1) )
				return SEQ_CondRetSeqNaoCompleta;
			
			/* Verificando se o naipe � o mesmo */
			condRetCarta = CAR_ObterNaipe(carta,&naipe);
			if (condRetCarta != CAR_CondRetOK || naipeEsperado != naipe)
				return SEQ_CondRetSeqNaoCompleta;
		}
		
		return SEQ_CondRetOK;
	
	}
} /* Fim fun��o: Verificar Sequencia Completa */

/***************************************************************************
*
*  Fun��o: SEQ  &Obter Pilha Cartas
*  ****/
SEQ_tpCondRet SEQ_ObterPilhaCartas ( SEQ_tpSequencia pSequencia,PIL_tpPilha *pPilha, int tam){

	PIL_tpCondRet condRetPilha;
	CAR_tpCarta carta;
	CAR_tpNaipe naipeAnt;
	CAR_tpValor valorAnt;
	CAR_tpCondRet condRetCarta;
	int i;

	if (pSequencia == NULL)
		return SEQ_CondRetSeqNaoExiste;

	/*****		Verifica se tem "tam" cartas		 *****/
	condRetPilha = PIL_AvancarElementoCorrente( pSequencia->cabeca ,tam-1);
	if (condRetPilha != PIL_CondRetOK)
		return SEQ_CondRetMovimentoInvalido;

	/*****	Verifica se a pilha tem uma sequencia valida para movimenta�ao	*****/

	condRetPilha = PIL_VerCarta(pSequencia->cabeca,&carta);
	if(condRetPilha != PIL_CondRetOK)
		return SEQ_CondRetMovimentoInvalido;


	condRetCarta = CAR_ObterNaipe(carta,&naipeAnt);
	if(condRetCarta != CAR_CondRetOK)
		return SEQ_CondRetMovimentoInvalido;

	condRetCarta = CAR_ObterValor(carta,&valorAnt);
	if(condRetCarta != CAR_CondRetOK)
		return SEQ_CondRetMovimentoInvalido;

	for (i=0; i < tam-1 ; i++) {
	
		CAR_tpValor valorAux;
		CAR_tpNaipe naipeAux;
		/* Obtendo Valor e Naipe */
		PIL_AvancarElementoCorrente( pSequencia->cabeca ,-1);

		condRetPilha = PIL_VerCarta(pSequencia->cabeca,&carta);
		if(condRetPilha != PIL_CondRetOK)
			return SEQ_CondRetMovimentoInvalido;

		condRetCarta= CAR_ObterNaipe(carta,&naipeAux);
		if(condRetCarta != CAR_CondRetOK)
			return SEQ_CondRetMovimentoInvalido;

		condRetCarta = CAR_ObterValor(carta,&valorAux);
		if(condRetCarta != CAR_CondRetOK)
			return SEQ_CondRetMovimentoInvalido;
		
		/* Teste */
		if ( naipeAux != naipeAnt || valorAux+1 != valorAnt ) 
			return SEQ_CondRetMovimentoInvalido;

		valorAnt = valorAux;
		}

		
	/*****		Cria Pilha		 *****/
	condRetPilha = PIL_CriarPilhaCartas(pPilha);
	if (condRetPilha == PIL_CondRetFaltouMemoria)
		return SEQ_CondRetFaltouMemoria;

	/*****		  Mover  		*****/
	return SEQ_MoverEntrePilhas(pSequencia->cabeca,*pPilha,tam);
}	/* Fim fun��o: SEQ  Obter Pilha Cartas */

/***************************************************************************
*
*  Fun��o: SEQ  &Verificar Virar Carta
*  ****/
SEQ_tpCondRet SEQ_VerificarVirarCarta ( SEQ_tpSequencia pSequencia) {

	CAR_tpCarta carta = NULL;
	PIL_tpCondRet condRetPil;
	
	if(pSequencia == NULL)
		return SEQ_CondRetSeqNaoExiste;
	
	condRetPil = PIL_IrInicioPilhaCartas( pSequencia->cabeca ) ;
	
	PIL_TornarCartaVisivel(pSequencia->cabeca);
	
	
	return SEQ_CondRetOK;
	

} /* Fim fun��o: SEQ  Verificar Virar Carta */

/***************************************************************************
*
*  Fun��o: SEQ  &Tornar Ultima Invisivel
*  ****/
SEQ_tpCondRet SEQ_TornarUltimaInvisivel ( SEQ_tpSequencia pSequencia) {

	CAR_tpCarta carta = NULL;
	CAR_tpEstado estado;
	PIL_tpCondRet condRetPil;
	
	if(pSequencia == NULL)
		return SEQ_CondRetSeqNaoExiste;
	
	condRetPil = PIL_IrFinalPilhaCartas( pSequencia->cabeca ) ;
	
	while (condRetPil == PIL_CondRetOK) {
	
		condRetPil = PIL_VerCarta(pSequencia->cabeca,&carta);
		if(condRetPil != PIL_CondRetOK)
			return SEQ_CondRetMovimentoInvalido;

		CAR_ObterEstado(carta,&estado);
	
		if (estado == CAR_EstadoInvisivel)
			condRetPil = PIL_AvancarElementoCorrente(pSequencia->cabeca,-1);
		else {
			PIL_TornarCartaInvisivel(pSequencia->cabeca);		
			return SEQ_CondRetOK;	
		}
	}
	return SEQ_CondRetMovimentoInvalido;
}	/* Fim fun��o: SEQ  Tornar Ultima Invisivel */
/***************************************************************************
*
*  Fun��o: SEQ  &Imprimir Sequencia
*  ****/
SEQ_tpCondRet SEQ_ImprimirSequencia(SEQ_tpSequencia pSequencia){
	PIL_tpCondRet condRetPilha;

	condRetPilha = PIL_ImprimirPilhaCartas(pSequencia->cabeca);

	if (condRetPilha == PIL_CondRetPilhaVazia)
		return SEQ_CondRetSeqVazia;

	if (condRetPilha == PIL_CondRetOK)
		return SEQ_CondRetOK;
	else
		return SEQ_CondRetSeqNaoExiste;

}	/* Fim fun��o: SEQ  Imprimir Sequencia */

/***************************************************************************
*
*  Fun��o: SEQ  &Retornar Pilha Sequencia
*  ****/

SEQ_tpCondRet SEQ_RetornarPilhaSequencia(SEQ_tpSequencia pSequencia, PIL_tpPilha *pPilha){

	PIL_tpCondRet condRetPilha;
	if (pSequencia == NULL)
		return SEQ_CondRetSeqNaoExiste;

	*pPilha = pSequencia->cabeca;
	pSequencia->cabeca = NULL;
	
	condRetPilha = PIL_CriarPilhaCartas(&pSequencia->cabeca);
	if (condRetPilha == PIL_CondRetFaltouMemoria)
		return SEQ_CondRetFaltouMemoria;

	return SEQ_CondRetOK;

} /* Fim fun��o: SEQ  Retornar Pilha Sequencia */


/*****  C�digo das fun��es encapsuladas no m�dulo  *****/


/***************************************************************************
*
*  Fun��o: SEQ  &Mover Entre Pilhas
*
*  $ED Descri��o da fun��o
*  Move pilhas "tam" de cartas entre pilha origem e pilha destino
*
*  ****/

SEQ_tpCondRet SEQ_MoverEntrePilhas (PIL_tpPilha pPilhaOrigem, PIL_tpPilha  pPilhaDestino,int tam) {
		int i;
		PIL_tpCondRet condRetPilha;


		if(PIL_IrInicioPilhaCartas(pPilhaOrigem) != PIL_CondRetOK)
			return SEQ_CondRetMovimentoInvalido;
		
		if(PIL_IrInicioPilhaCartas(pPilhaDestino) != PIL_CondRetOK)
		return SEQ_CondRetMovimentoInvalido;

		/* verificando se tem "TAM" cartas*/
		condRetPilha = PIL_AvancarElementoCorrente(pPilhaOrigem, tam-1);
		if (condRetPilha != PIL_CondRetOK)
			return SEQ_CondRetMovimentoInvalido;


		for (i=0 ; i < tam ; i++) {
	
		CAR_tpCarta carta;
		PIL_tpCondRet condRetPil;
		
		condRetPil=PIL_RemoverCarta(pPilhaOrigem,&carta);

		if (condRetPilha == PIL_CondRetFaltouMemoria)
		    return SEQ_CondRetFaltouMemoria;
		
		condRetPil=PIL_AdicionarCarta(pPilhaDestino,carta);
		
		if (condRetPilha == PIL_CondRetFaltouMemoria)
		    return SEQ_CondRetFaltouMemoria;
	}
	return SEQ_CondRetOK;
}	/* Fim fun��o: SEQ  Mover Entre Pilhas */

/********** Fim do m�dulo de implementa��o: SEQ  Sequencia **********/