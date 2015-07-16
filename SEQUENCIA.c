/***************************************************************************
*  $MCI Módulo de implementação: SEQ SEQUENCIA
*
*  Arquivo gerado:              SEQUENCIA.c
*  Letras identificadoras:      SEQ
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
*	  3       thk   28/abr/2015 mudança das condiçoes de retorno
*	  2		  thk   27/abr/2015 implentacao de novas funçoes
*	  1		  thk   27/abr/2015	inicio desenvolvimento
*
***************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include "SEQUENCIA.h"
#include "CARTA.h"
#define TAM_SEQ_COMPLETA 13

/***********************************************************************
*
*  $TC Tipo de dados: SEQ Descritor da cabeça da sequencia
*
*
***********************************************************************/

typedef struct SEQ_tagSequencia {

	PIL_tpPilha cabeca;

} SEQ_tppSequencia;

/***** Protótipos das funções encapuladas no módulo *****/
static SEQ_tpCondRet SEQ_MoverEntrePilhas (PIL_tpPilha pPilhaOrigem, PIL_tpPilha  pPilhaDestino,int tam);

/*****  Código das funções exportadas pelo módulo  *****/

/***************************************************************************
*
*  Função: SEQ  &Criar Sequencia
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
} /* Fim função: Criar Sequencia  */

/***************************************************************************
*
*  Função: SEQ  &Destruir Sequencia
*  ****/
SEQ_tpCondRet SEQ_DestruirSequencia (SEQ_tpSequencia pSequencia) {
	
	PIL_tpCondRet condRetPil;
	condRetPil = PIL_DestruirPilhaCartas (pSequencia->cabeca);
	if(condRetPil != PIL_CondRetOK)
		return SEQ_CondRetSeqNaoExiste;

	return SEQ_CondRetOK;
} /* Fim função: Destruir Sequencia  */

/***************************************************************************
*
*  Função: SEQ  &Esvaziar Sequencia
*  ****/
SEQ_tpCondRet SEQ_EsvaziarSequencia(SEQ_tpSequencia pSequencia){
	PIL_tpCondRet condRetPil;
	
	condRetPil = PIL_EsvaziarPilhaCartas(pSequencia->cabeca);
	
	if(condRetPil != PIL_CondRetOK)
		return SEQ_CondRetSeqNaoExiste;

	return SEQ_CondRetOK;
} /* Fim função: Esvaziar Sequencia  */

/***************************************************************************
*
*  Função: SEQ  &Iniciar Sequencia
*  ****/
SEQ_tpCondRet SEQ_IniciarSequencia (SEQ_tpSequencia pSequencia, PIL_tpPilha pPilha,int tam) {

	if (pSequencia == NULL)
		return SEQ_CondRetSeqNaoExiste;

	return SEQ_MoverEntrePilhas(pPilha,pSequencia->cabeca,tam);
} /* Fim função: Iniciar Sequencia  */

/***************************************************************************
*
*  Função: SEQ  &Adicionar Pilha Em Sequencia
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
	/* Se existe topo verifica se a primeira da pilha é igual a 1 menos que ele */
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
} /* Fim função: Adicionar Pilha Em Sequencia */

/***************************************************************************
*
*  Função: SEQ  &Verificar Sequencia Completa
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
		
		/*Verificando se a carta é um rei*/
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
			
			/* Ja é garantido que carta existe */
			PIL_AvancarElementoCorrente( pSequencia->cabeca ,-1);
			
			PIL_VerCarta(pSequencia->cabeca,&carta);
			
			/* Verificando se o valor está na posiçao certa */
			condRetCarta = CAR_ObterValor(carta,&valor);
			if (condRetCarta != CAR_CondRetOK || valorEsperado != (valor+i+1) )
				return SEQ_CondRetSeqNaoCompleta;
			
			/* Verificando se o naipe é o mesmo */
			condRetCarta = CAR_ObterNaipe(carta,&naipe);
			if (condRetCarta != CAR_CondRetOK || naipeEsperado != naipe)
				return SEQ_CondRetSeqNaoCompleta;
		}
		
		return SEQ_CondRetOK;
	
	}
} /* Fim função: Verificar Sequencia Completa */

/***************************************************************************
*
*  Função: SEQ  &Obter Pilha Cartas
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

	/*****	Verifica se a pilha tem uma sequencia valida para movimentaçao	*****/

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
}	/* Fim função: SEQ  Obter Pilha Cartas */

/***************************************************************************
*
*  Função: SEQ  &Verificar Virar Carta
*  ****/
SEQ_tpCondRet SEQ_VerificarVirarCarta ( SEQ_tpSequencia pSequencia) {

	CAR_tpCarta carta = NULL;
	PIL_tpCondRet condRetPil;
	
	if(pSequencia == NULL)
		return SEQ_CondRetSeqNaoExiste;
	
	condRetPil = PIL_IrInicioPilhaCartas( pSequencia->cabeca ) ;
	
	PIL_TornarCartaVisivel(pSequencia->cabeca);
	
	
	return SEQ_CondRetOK;
	

} /* Fim função: SEQ  Verificar Virar Carta */

/***************************************************************************
*
*  Função: SEQ  &Tornar Ultima Invisivel
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
}	/* Fim função: SEQ  Tornar Ultima Invisivel */
/***************************************************************************
*
*  Função: SEQ  &Imprimir Sequencia
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

}	/* Fim função: SEQ  Imprimir Sequencia */

/***************************************************************************
*
*  Função: SEQ  &Retornar Pilha Sequencia
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

} /* Fim função: SEQ  Retornar Pilha Sequencia */


/*****  Código das funções encapsuladas no módulo  *****/


/***************************************************************************
*
*  Função: SEQ  &Mover Entre Pilhas
*
*  $ED Descrição da função
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
}	/* Fim função: SEQ  Mover Entre Pilhas */

/********** Fim do módulo de implementação: SEQ  Sequencia **********/