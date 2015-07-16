/***************************************************************************
*  $MCI Módulo de implementação: BAR  Baralho
*
*  Arquivo gerado:              BARALHO.c
*  Letras identificadoras:      BAR
*
*  Nome da base de software:    Paciência Spider
*  Arquivo da base de software: 
*
*  Projeto: INF 1301 Paciência Spider
*  Gestor:  LES/DI/PUC-Rio
*  Autores: adp, ilg, thk
*
*  $HA Histórico de evolução:
*     Versão  Autor    Data     Observações
*	  2		  thk	28/abr/2015 ajuste em erros
*     1       thk   16/abr/2015 início desenvolvimento
*
***************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "BARALHO.H"

/***********************************************************************
*
*  $TC Tipo de dados: CAR Descritor da cabeça de baralho
*
*
***********************************************************************/

typedef struct BAR_tagBaralho {

	PIL_tpPilha cabeca;
} BAR_tppBaralho;


/***************************************************************************
*
*  Função: BAR  &Criar Baralho
*  ****/

BAR_tpCondRet BAR_CriarBaralho (BAR_tpBaralho * pBaralho) {
	
	PIL_tpCondRet condRetPil;


	*pBaralho = (BAR_tppBaralho*) malloc (sizeof(BAR_tppBaralho));
	
	if (*pBaralho == NULL)
		return BAR_CondRetFaltouMemoria;
		
		condRetPil = PIL_CriarPilhaCartas (&(*pBaralho)->cabeca);
		
		if(condRetPil == PIL_CondRetFaltouMemoria)
			return BAR_CondRetFaltouMemoria;

		return BAR_CondRetOK;

} /*fim função criar baralho */

/***************************************************************************
*
*  Função: BAR  &Destruir Baralho
*  ****/

BAR_tpCondRet BAR_DestruirBaralho(BAR_tpBaralho pBaralho) {
	
	PIL_tpCondRet condRetPil;

	if(pBaralho == NULL)
		return BAR_CondRetBaralhoNaoExiste;

	condRetPil = PIL_DestruirPilhaCartas (pBaralho->cabeca);
	if(condRetPil != PIL_CondRetOK)
		return BAR_CondRetBaralhoNaoExiste;


	return BAR_CondRetOK;
} /*fim função Destruir Baralho */

/***************************************************************************
*
*  Função: BAR  &Esvaziar Baralho
*  ****/

BAR_tpCondRet BAR_EsvaziarBaralho (BAR_tpBaralho pBaralho){
	
	PIL_tpCondRet condRetPil;

	if (pBaralho == NULL)
		return BAR_CondRetBaralhoNaoExiste;

	condRetPil = PIL_EsvaziarPilhaCartas(pBaralho->cabeca);

	if (condRetPil != PIL_CondRetOK)
		return BAR_CondRetBaralhoNaoExiste;

	return BAR_CondRetOK;

} /*fim função Esvaziar Baralho */

/***************************************************************************
*
*  Função: BAR  &Iniciar Baralho
*  ****/

BAR_tpCondRet BAR_IniciarBaralho (BAR_tpBaralho pBaralho, int qtdBaralhos, int qtdNaipes) {

	
	CAR_tpCarta *vetorCartas;
	int naipe,valor,tam,i;


	if (pBaralho == NULL)
		return BAR_CondRetBaralhoNaoExiste;

	if (qtdBaralhos < 1 || qtdNaipes < 1 || qtdNaipes > 4)
		return BAR_CondRetQuantidadeInvalida;

	tam = qtdBaralhos*52;
	vetorCartas = (CAR_tpCarta*)malloc(tam*sizeof(CAR_tpCarta));
	if (vetorCartas == NULL)
		return BAR_CondRetFaltouMemoria;


	for ( i = 0, naipe = 0; i < tam; naipe++) {
		
		for (valor = _A ; valor <= _K ; valor++,i++) {
			CAR_tpCondRet condRetCarta;
		
			condRetCarta = CAR_CriarCarta(&vetorCartas[i],(CAR_tpValor) valor, (CAR_tpNaipe) (naipe%qtdNaipes));
			if (condRetCarta == CAR_CondRetFaltouMemoria){
				free(vetorCartas);
				return BAR_CondRetFaltouMemoria;}
		}
	}
	srand ( time(NULL) );
	
	
	for (i = 0 ; i < tam ; tam--) {
	
		CAR_tpCarta carta;
		PIL_tpCondRet condRetPilha;

		int random = rand()%tam;

		carta = vetorCartas[random];
		
		condRetPilha = PIL_AdicionarCarta (pBaralho->cabeca, carta);

		if (condRetPilha == PIL_CondRetFaltouMemoria){
			free(vetorCartas);
			return BAR_CondRetFaltouMemoria;
		}
		vetorCartas[random] = vetorCartas[tam-1];
		
		
	}
	free(vetorCartas);
	return BAR_CondRetOK;

} /*fim função Iniciar Baralho */

/***************************************************************************
*
*  Função: BAR  &Criar SubPilhaBaralho
*  ****/

BAR_tpCondRet BAR_CriarSubPilhaBaralho (BAR_tpBaralho pBaralho, PIL_tpPilha * pPilha, int tam) {

	PIL_tpCondRet condRetPilha;
	int i;

	if (pBaralho == NULL)
		return BAR_CondRetBaralhoNaoExiste;
 
	if (tam < 1 )
		return BAR_CondRetQuantidadeInvalida;


	PIL_IrInicioPilhaCartas(pBaralho->cabeca);
	condRetPilha = PIL_AvancarElementoCorrente( pBaralho->cabeca ,tam-1 );

	if (condRetPilha != PIL_CondRetOK)
		return BAR_CondRetBaralhoInsuficiente;

	condRetPilha = PIL_CriarPilhaCartas(pPilha);
	if (condRetPilha == PIL_CondRetFaltouMemoria)
		return BAR_CondRetFaltouMemoria;


	for (i = 0 ; i < tam ; i++) {
		
		CAR_tpCarta carta;

		condRetPilha = PIL_RemoverCarta(pBaralho->cabeca,&carta);
		
		if (condRetPilha == PIL_CondRetFaltouMemoria)
			return BAR_CondRetFaltouMemoria;

		condRetPilha = PIL_AdicionarCarta(*pPilha,carta);
		
		if (condRetPilha == PIL_CondRetFaltouMemoria)
			return BAR_CondRetFaltouMemoria;

	}



	return BAR_CondRetOK;

}/*fim função CriarSubPilha Baralho */

/***************************************************************************
*
*  Função: BAR  &Imprimir Baralho
*  ****/
BAR_tpCondRet BAR_ImprimirBaralho(BAR_tpBaralho pBaralho){

	PIL_ImprimirPilhaCartas(pBaralho->cabeca);

	return BAR_CondRetOK;
}/*fim função Imprimir Baralho */

/* Fim das funções implementadas do módulo Baralho */