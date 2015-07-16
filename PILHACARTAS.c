/***************************************************************************
*  $MCI M�dulo de implementa��o: PIL Pilha Cartas
*
*  Arquivo gerado:              PILHACARTAS.c
*  Letras identificadoras:      PIL
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
*	  3       thk   28/abr/2015 mudan�a de retorno de fun�oes
*	  2		  thk   27/abr/2015 implentacao de novas fun�oes
*	  1		  thk   25/abr/2015	inicio desenvolvimento
*
***************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "PILHACARTAS.h"
#include "LISTA.h"
#include "carta.h"

/***********************************************************************
*
*  $TC Tipo de dados: PIL Descritor da cabe�a da pilha de cartas
*
*
***********************************************************************/

typedef struct PIL_tagPilha {

	LIS_tppLista cabeca;

}PIL_tppPilha;


/***** Prot�tipos das fun��es encapuladas no m�dulo *****/
static char* PegarStringValor (CAR_tpValor valor);
static char* PegarStringNaipe (CAR_tpNaipe naipe);


/*****  C�digo das fun��es exportadas pelo m�dulo  *****/

/***************************************************************************
*
*  Fun��o: PIL  &Criar Pilha Cartas
*  ****/
PIL_tpCondRet PIL_CriarPilhaCartas (PIL_tpPilha *pPilha) {

	LIS_tpCondRet condRet;

	*pPilha = (PIL_tppPilha*) malloc (sizeof(PIL_tppPilha));
	if (*pPilha == NULL)
		return PIL_CondRetFaltouMemoria;

	condRet = LIS_CriarLista( &((*pPilha)->cabeca) ,CAR_DestruirCarta );

	if (condRet == LIS_CondRetFaltouMemoria){
		free(*pPilha);
		return PIL_CondRetFaltouMemoria;
	}
	else
		return PIL_CondRetOK;
}		/* Fim fun��o: PIL  &Criar Pilha Cartas */
/***************************************************************************
*
*  Fun��o: PIL  &Destruir Pilha Cartas
*  ****/
PIL_tpCondRet PIL_DestruirPilhaCartas (PIL_tpPilha pPilha) {
	
	LIS_tpCondRet condRet;
	
	if (pPilha == NULL)
		return PIL_CondRetPilhaNaoExiste;
	
	condRet = LIS_DestruirLista( pPilha->cabeca );
	
		free(pPilha);
		pPilha = NULL;
		return PIL_CondRetOK;
	


}/* Fim fun��o: PIL  &Destruir Pilha Cartas */

/***************************************************************************
*
*  Fun��o: PIL  &Esvaziar Pilha Cartas
*  ****/
PIL_tpCondRet PIL_EsvaziarPilhaCartas(PIL_tpPilha pPilha) {
	LIS_tpCondRet condRet;
	
	if (pPilha == NULL)
		return PIL_CondRetPilhaNaoExiste;

	condRet = LIS_EsvaziarLista (pPilha->cabeca);

	if (condRet == LIS_CondRetListaNaoExiste)
		return PIL_CondRetPilhaVazia;
	else
		return PIL_CondRetOK;

}/* Fim fun��o: PIL  &Esvaziar Pilha Cartas */


/***************************************************************************
*
*  Fun��o: PIL  &Imprimir Pilha Cartas
*  ****/
PIL_tpCondRet PIL_ImprimirPilhaCartas (PIL_tpPilha pPilha) {
	
	CAR_tpCondRet condRetCarta = CAR_CondRetOK;
	LIS_tpCondRet condRetLista;
	int qtd = 0;

	if (pPilha == NULL)
		return PIL_CondRetPilhaNaoExiste;

	printf("\n > ");
	
	PIL_QuantidadeCartas(pPilha,&qtd);
	if (qtd == 0 ) {	
		printf("\n");
		return PIL_CondRetPilhaVazia;
	}

	IrFinalLista(pPilha->cabeca);
	while (qtd) {
	
		CAR_tpCarta carta;
		CAR_tpValor valor;
		CAR_tpNaipe naipe;
		PIL_tpCondRet condRetPilha;

		condRetPilha = PIL_VerCarta(pPilha,&carta);
		if (condRetPilha == PIL_CondRetPilhaVazia)
			return condRetPilha;
	
		
		condRetCarta = CAR_ObterValor(carta,&valor);
		CAR_ObterNaipe(carta,&naipe);

	
		if(condRetCarta == CAR_CondRetCartaInvisivel)
			printf("# ");
		else
			printf(" %s%s ",PegarStringValor(valor),PegarStringNaipe(naipe));

			condRetLista = LIS_AvancarElementoCorrente( pPilha->cabeca , -1 );
	qtd--;
	}
	printf("\n");
	return PIL_CondRetOK;
}	/* Fim fun��o: PIL  &Imprimir Pilha Cartas */


/***************************************************************************
*
*  Fun��o: PIL  &Ir Inicio Pilha
*  ****/
PIL_tpCondRet PIL_IrInicioPilhaCartas( PIL_tpPilha pPilha ) {
	
	LIS_tpCondRet retorno;

	if (pPilha == NULL)
		return PIL_CondRetPilhaNaoExiste;

	retorno = IrInicioLista( pPilha->cabeca ) ;

	if ( retorno == PIL_CondRetPilhaNaoExiste)
		return PIL_CondRetPilhaNaoExiste;

	return PIL_CondRetOK;
}	/* Fim fun��o: PIL  &Ir Inicio Pilha Cartas */

/***************************************************************************
*
*  Fun��o: PIL  &IR Final Pilha
*  ****/
PIL_tpCondRet PIL_IrFinalPilhaCartas( PIL_tpPilha pPilha ) {
	
	LIS_tpCondRet retorno;

	if (pPilha == NULL)
		return PIL_CondRetPilhaNaoExiste;

	retorno = IrFinalLista( pPilha->cabeca ) ;

	if ( retorno == PIL_CondRetPilhaNaoExiste)
		return PIL_CondRetPilhaNaoExiste;

	return PIL_CondRetOK;
}	/* Fim fun��o: PIL  &Ir Final Pilha Cartas */
/***************************************************************************
*
*  Fun��o: PIL  &Avancar Elemento Corrente
*  ****/
PIL_tpCondRet PIL_AvancarElementoCorrente( PIL_tpPilha pPilha ,int numElem ) {
	     
		LIS_tpCondRet condRet;
		
		if (pPilha == NULL)
			return PIL_CondRetPilhaNaoExiste;

		condRet = LIS_AvancarElementoCorrente( pPilha->cabeca, numElem ) ;

		
		if (condRet == LIS_CondRetFimLista)
			return PIL_CondRetFimPilha;
		if (condRet == LIS_CondRetListaVazia)
			return PIL_CondRetPilhaVazia;
		
		return PIL_CondRetOK;
   }

/***************************************************************************
*
*  Fun��o: PIL  &Adicionar Carta
*  ****/
PIL_tpCondRet PIL_AdicionarCarta (PIL_tpPilha pPilha, CAR_tpCarta carta) {


	LIS_tpCondRet retorno;
	CAR_tpCarta copiaCarta;
	CAR_tpValor	copiaValor;
	CAR_tpNaipe	copiaNaipe;
	CAR_tpEstado copiaEstado;
	CAR_tpCondRet condRetCarta;
	int tornarInvisivel = 0;

	if (pPilha == NULL)
		return PIL_CondRetPilhaNaoExiste;

	if (carta == NULL)
		return PIL_CondRetCartaNaoExiste;


	condRetCarta = CAR_ObterEstado(carta,&copiaEstado);
		
	if (condRetCarta != CAR_CondRetOK)
		return PIL_CondRetCartaNaoExiste;
		
	if (copiaEstado == CAR_EstadoInvisivel){
			CAR_TornarVisivel(carta);
			tornarInvisivel = 1;
		}

	condRetCarta = CAR_ObterValor(carta,&copiaValor);
		
	if (condRetCarta != CAR_CondRetOK)
		return PIL_CondRetCartaNaoExiste;
		
	condRetCarta = CAR_ObterNaipe(carta,&copiaNaipe);
		
	if (condRetCarta != CAR_CondRetOK)
		return PIL_CondRetCartaNaoExiste;
		
	condRetCarta = CAR_CriarCarta(&copiaCarta,copiaValor,copiaNaipe);

	if(condRetCarta == CAR_CondRetFaltouMemoria)
		return PIL_CondRetFaltouMemoria;

	if (tornarInvisivel)
		CAR_TornarInvisivel(copiaCarta);

	
	retorno = LIS_InserirElementoAntes( pPilha->cabeca ,copiaCarta);

	if (retorno == LIS_CondRetFaltouMemoria)
		return PIL_CondRetFaltouMemoria;


	return PIL_CondRetOK;

}

/***************************************************************************
*
*  Fun��o: PIL  &Remover Carta
*  ****/
PIL_tpCondRet PIL_RemoverCarta( PIL_tpPilha pPilha , CAR_tpCarta * pCarta ) {

	LIS_tpCondRet condRetLis;
	CAR_tpCarta carta;

	if (pPilha == NULL)
		return PIL_CondRetPilhaNaoExiste;

	condRetLis = LIS_ObterValor( pPilha->cabeca , (void**)&carta);

	if (condRetLis != LIS_CondRetOK)
		return PIL_CondRetPilhaVazia; 
	else {
		CAR_tpCarta cartaCriada;
		CAR_tpValor valor;
		CAR_tpNaipe naipe;
		CAR_tpEstado estado;
		CAR_tpCondRet condRetCar;

		//nao precisa testar cond de ret porque j� foi garantido que carta existe
		CAR_ObterValor(carta,&valor);
		
		CAR_ObterNaipe(carta,&naipe);
	
		CAR_ObterEstado(carta,&estado);

		condRetCar = CAR_CriarCarta( &cartaCriada,valor,naipe);

		if (estado == CAR_EstadoInvisivel)
			CAR_TornarInvisivel(cartaCriada);

		if (condRetCar == CAR_CondRetFaltouMemoria)
			return PIL_CondRetFaltouMemoria;
		else {
			 LIS_ExcluirElemento( pPilha->cabeca );
			 *pCarta = cartaCriada;
			//aqui h� garantia que a lista nao esta vazia pois ja se obteve o valor anteriormente
			return PIL_CondRetOK;
		}

	}
}

/***************************************************************************
*
*  Fun��o: PIL  &Ver Carta
*  ****/
PIL_tpCondRet PIL_VerCarta( PIL_tpPilha pPilha , CAR_tpCarta * pCarta ) {

		LIS_tpCondRet condRetLis;

	if (pPilha == NULL)
		return PIL_CondRetPilhaNaoExiste;

	condRetLis = LIS_ObterValor( pPilha->cabeca , (void**)pCarta);

	if (condRetLis != LIS_CondRetOK)
		return PIL_CondRetPilhaVazia; 

	return PIL_CondRetOK;

}
/***************************************************************************
*
*  Fun��o: PIL  &Tornar Carta Visivel
*  ****/
PIL_tpCondRet PIL_TornarCartaVisivel( PIL_tpPilha pPilha){
	
	CAR_tpCarta carta;
	PIL_tpCondRet condRet;

	condRet = PIL_VerCarta( pPilha ,&carta );
	if(condRet == PIL_CondRetOK)
		CAR_TornarVisivel(carta);

	return PIL_CondRetOK;
}

/***************************************************************************
*
*  Fun��o: PIL  &Tornar Carta Invisivel
*  ****/
PIL_tpCondRet PIL_TornarCartaInvisivel( PIL_tpPilha pPilha){

	CAR_tpCarta carta;
	PIL_tpCondRet condRet;

	condRet = PIL_VerCarta( pPilha ,&carta);
	if( condRet == PIL_CondRetOK )
		CAR_TornarInvisivel(carta);
	
	return condRet;
}

/***************************************************************************
*
*  Fun��o: PIL  &Quantidade Cartas
*  ****/

PIL_tpCondRet PIL_QuantidadeCartas(PIL_tpPilha pPilha,int *qtd){

	int qtdAux;
	if(pPilha == NULL) {
		*qtd = 0;
		return PIL_CondRetPilhaNaoExiste;
	}

	LIS_QtdElem(pPilha->cabeca, &qtdAux);
		
	*qtd = qtdAux;
	return PIL_CondRetOK;

}

/*****  C�digo das fun��es encapsuladas no m�dulo  *****/

/***********************************************************************
*
*  $FC Fun��o: Pegar String Valor
*
*  $ED Descri��o da fun��o
*	Troca o tipo valor por string para impress�o
*
***********************************************************************/

char* PegarStringValor (CAR_tpValor valor){

	     switch( valor )
     {
        case _A : return "A";
                   break;
        case _2 : return "2";
                   break;
        case _3 : return "3";
                   break;
        case _4 : return "4";
                   break;
        case _5 : return "5";
                   break;
        case _6 : return "6";;
                   break;
        case _7 : return "7";
                   break;
        case _8 : return "8";
                   break;
        case _9 : return "9";
                   break;
        case _10 : return "10";
                   break;
		case _J : return "J";
					   break;
		case _Q : return "Q";
					   break;
		case _K : return "K";
					   break;
		default  : return "sem valor";
					   break;
		 }
	} /* Fim fun��o:   Pegar String Valor  */


/***********************************************************************
*
*  $FC Fun��o: Pegar String Naipe
*
*  $ED Descri��o da fun��o
*	Troca o tipo naipe por string para impress�o
*
***********************************************************************/
	char* PegarStringNaipe (CAR_tpNaipe naipe){

			 switch( naipe )
		 {
			case Espadas : return "E";
					   break;
			case Copas : return "C";
					   break;
			case Ouros : return "O";
					   break;
			case Paus : return "P";
					   break;
			default  : return "sem naipe";
					   break;
		 }
	} /* Fim fun��o:   Pegar String Naipe  */

/********** Fim do m�dulo de implementa��o: PIL  Pilha Cartas **********/