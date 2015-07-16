/***************************************************************************
*  $MCI Módulo de implementação: 
*
*  Arquivo gerado:  PRINCIPAL.c          
*  Letras identificadoras: PAC 
*
*  Nome da base de software:    Paciência Spider
*  Arquivo da base de software: 
*
*  Projeto: INF 1301 Paciência Spider
*  Gestor:  LES/DI/PUC-Rio
*  Autores: adp, ilg, thk
*
*  $HA Histórico de evolução:
*     Versão  Autor    Data			 Observações
*	  4		  adp	25/maio/2015	 revisão e documentação das funções
*	  3		  thk	16/maio/2015	 implementado salvar/carregar jogo de arquivo .txt
*	  2		  thk   12/maio/2015	 feito jogabilidade e navegaçao de menu
*     1       thk   09/maio/2015	 início desenvolvimento
*
***************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include "BARALHO.h"
#include "MONTE.h"
#include "SEQFINAL.h"
#include "SEQUENCIA.h"
#include "PILHACARTAS.h"
#include "LISTA.h"
#include "CARTA.h"

#define NOME_ARQ "paciencia.txt"
#define TOT_SEQ 10
#define TOT_MON 5
#define TOT_FIN 8

typedef enum {

	PAC_CondRetOK,
	PAC_CondRetFaltouMemoria,
	PAC_CondRetErroLeituraArquivo,
	PAC_CondRetCartaInvalida,
	PAC_CondRetJogoGanho

}PAC_tpCondRet;


/***** Protótipos das funções encapsuladas no módulo *****/

void ImprimirJogo ();
PAC_tpCondRet MenuJogo (void);
PAC_tpCondRet MoverSequencias (int indexOrigem, int indexDestino, int qtdCartas);
PAC_tpCondRet ComprarCartas();
void TerminarJogoGanho ();
void DestruirEstrutura();

PAC_tpCondRet IniciarEstrutura();
PAC_tpCondRet IniciarNovoJogo (int dificuldade);
PAC_tpCondRet SalvarJogo();
PAC_tpCondRet CarregarJogo ();


void ExcluirSequencia (void* pSequencia);
void ExcluirMonteCompras(void* pMonte);
void ExcluirSeqFinal(void* pSeqFin);
void ExcluirBaralho(void* pBaralho);


PAC_tpCondRet ObterStringValor ( CAR_tpValor valor, char *cValor );
PAC_tpCondRet ObterStringNaipe ( CAR_tpNaipe naipe, char *cNaipe );
PAC_tpCondRet ObterStringEstado ( CAR_tpEstado estado, char *cEstado );
PAC_tpCondRet ObterTipoValor ( char cValor,CAR_tpValor *valor);
PAC_tpCondRet ObterTipoNaipe ( char cNaipe, CAR_tpNaipe *naipe );
PAC_tpCondRet ObterTipoEstado ( char cEstado, CAR_tpEstado *estado );

/***********************************************************************
*
*  $TC Tipo de dados: PAC Paciencia
*
***********************************************************************/
typedef struct paciencia {

	LIS_tppLista pJogo;
	int qtdCompras;
	int qtdSeqFinais;

}PAC_tpPaciencia;


/*****  Dados encapsulados no módulo  *****/

/*	ponteiro para o jogo */
PAC_tpPaciencia tpPaciencia;


/* Função main	*/
int main (void){

   int comando = 0 ;
   int dificuldade=0;
   PAC_tpCondRet condRetPac;

   while (comando != 3) {
  
	   printf("1. Iniciar Jogo\n2. Carregar jogo salvo\n3. Sair\n");   
	   scanf(" %i",&comando);
	   while(getchar() != '\n');

	   switch (comando) {
		
	   case 1:
		   printf("Selecione Dificuldade:\n1. Facil\n2. Medio\n3. Dificil\n4. Muito Dificil\n");
		   scanf(" %i",&dificuldade);	
		   while(getchar() != '\n');			
		   
		   if(dificuldade < 1 || dificuldade > 4){
				printf("\n>>Dificuldade Invalida\n\n");
				system("pause");
			}
		   else {
				condRetPac = IniciarNovoJogo (dificuldade);
				if(condRetPac != PAC_CondRetOK){		
					printf("\n>>Faltou Memoria\n\n");
					exit(1);
				}
				condRetPac = MenuJogo();
		   }
			break;
		case 2: condRetPac = CarregarJogo ();
				if(condRetPac != PAC_CondRetOK){		
					
					if(condRetPac == PAC_CondRetErroLeituraArquivo)
						printf("\n>>Erro Leitura Arquivo\n\n");
					else 
						printf("\n>>Faltou Memoria\n\n");
						
					system("pause");
					exit(1);
				}
				condRetPac = MenuJogo();
				break;
		case 3:
			break;

		default: 
			printf("\n>>Opcao Invalida\n\n");
			system("pause");
				  break;	
	   } /* switch */   				 
	   if(condRetPac == PAC_CondRetFaltouMemoria){		
		   printf("\n>>Faltou Memoria\n\n");		 
		   system("pause");	  
		   exit(1);
	   }
	   system("cls");
   }
   return 0 ;
}

/*							*/
/*****  Código das funções encapsuladas no módulo  *****/

void ExcluirLista (void* pLista) {
	
	LIS_EsvaziarLista((LIS_tppLista)pLista);
	LIS_DestruirLista((LIS_tppLista) pLista);
}

void ExcluirSequencia (void* pSequencia) {
	
	SEQ_EsvaziarSequencia((SEQ_tpSequencia) pSequencia);
	SEQ_DestruirSequencia((SEQ_tpSequencia) pSequencia);
}
void ExcluirMonteCompras(void* pMonte){

	MON_EsvaziarMonteCompras((MON_tpMonte) pMonte);
	MON_DestruirMonteCompras((MON_tpMonte) pMonte);
}
void ExcluirSeqFinal(void* pSeqFin){

	FIN_EsvaziarSeqFinal((FIN_tpSeqFin) pSeqFin);
	FIN_DestruirSeqFinal((FIN_tpSeqFin) pSeqFin);
}
void ExcluirBaralho(void* pBaralho){

	BAR_EsvaziarBaralho((BAR_tpBaralho) pBaralho);
	BAR_DestruirBaralho((BAR_tpBaralho) pBaralho);
}

/***************************************************************************
*
*  Função: PAC  &Iniciar Estrutura
*
*  $ED Descrição da função
*  Cria toda estrutura necessaria para o jogo de paciência, lista de listas das sequencias, sequencias finais, montes, e baralho.
*
*  ****/

PAC_tpCondRet IniciarEstrutura(){

	int i;
	LIS_tppLista auxLis;
	LIS_tpCondRet condRetLista;
	BAR_tpBaralho pBaralho = NULL;

	tpPaciencia.qtdSeqFinais = 0;
	tpPaciencia.qtdCompras = 0;

	condRetLista = LIS_CriarLista(&(tpPaciencia.pJogo),ExcluirLista);
	if (condRetLista != LIS_CondRetOK)
		return PAC_CondRetFaltouMemoria;

	/*			Criando Baralho			*/
	
	condRetLista = LIS_CriarLista(&auxLis,ExcluirBaralho);
	if (condRetLista != LIS_CondRetOK)
		return PAC_CondRetFaltouMemoria;

	condRetLista = LIS_InserirElementoAntes(tpPaciencia.pJogo,auxLis);
	if (condRetLista != LIS_CondRetOK)
		return PAC_CondRetFaltouMemoria;
	else {
		BAR_tpCondRet condRetBaralho;
		
		condRetBaralho = BAR_CriarBaralho(&pBaralho);
		
		if (condRetBaralho != BAR_CondRetOK)
			return PAC_CondRetFaltouMemoria;

		condRetLista = LIS_InserirElementoAntes(auxLis,pBaralho);
		if (condRetLista != LIS_CondRetOK)
			return PAC_CondRetFaltouMemoria;
	}
	auxLis = NULL;
	IrInicioLista(tpPaciencia.pJogo);
	/************************************/
	
	/*		Criando 8 Sequencia Finais		 */

	condRetLista = LIS_CriarLista(&auxLis,ExcluirSeqFinal);
	if (condRetLista != LIS_CondRetOK)
		return PAC_CondRetFaltouMemoria;

	condRetLista = LIS_InserirElementoAntes(tpPaciencia.pJogo,auxLis);
	if (condRetLista != LIS_CondRetOK)
		return PAC_CondRetFaltouMemoria;

	for (i = 0 ; i < TOT_FIN ; i ++) {
		FIN_tpSeqFin pSeqFin = NULL;
		FIN_tpCondRet condRetSeqFin;
		
		condRetSeqFin = FIN_CriarSeqFinal(&pSeqFin);
		if ( condRetSeqFin != FIN_CondRetOK)
			return PAC_CondRetFaltouMemoria;

		condRetLista = LIS_InserirElementoAntes(auxLis,pSeqFin);
		if (condRetLista != LIS_CondRetOK)
			return PAC_CondRetFaltouMemoria;
	
	}
	auxLis = NULL;
	IrInicioLista(tpPaciencia.pJogo);
	/************************************/

	/*		Criando 5 montes de compra		*/

	condRetLista = LIS_CriarLista(&auxLis,ExcluirMonteCompras);
	if (condRetLista != LIS_CondRetOK)
			return PAC_CondRetFaltouMemoria;

	condRetLista = LIS_InserirElementoAntes(tpPaciencia.pJogo,auxLis);
	if (condRetLista != LIS_CondRetOK)
			return PAC_CondRetFaltouMemoria;

	for (i = 0 ; i < TOT_MON ; i ++) {
		PIL_tpPilha auxPilha = NULL;
		MON_tpMonte pMonte = NULL;	
		MON_tpCondRet condRetMonte;
		
		condRetMonte = MON_CriarMonteCompras(&pMonte);
		if (condRetMonte != BAR_CondRetOK)
			return PAC_CondRetFaltouMemoria;

		condRetLista = LIS_InserirElementoAntes(auxLis,pMonte);
		if (condRetLista != LIS_CondRetOK)
			return PAC_CondRetFaltouMemoria;
	}
	auxLis = NULL;
	IrInicioLista(tpPaciencia.pJogo);
	/***************************************/

	/*		Criando 10 sequencias de jogo		*/
	
	condRetLista = LIS_CriarLista(&auxLis,ExcluirSequencia);
	if (condRetLista != LIS_CondRetOK)
			return PAC_CondRetFaltouMemoria;

	condRetLista = LIS_InserirElementoAntes(tpPaciencia.pJogo,auxLis);
	if (condRetLista != LIS_CondRetOK)
			return PAC_CondRetFaltouMemoria;

		for (i = 0; i < TOT_SEQ; i ++) {
			SEQ_tpSequencia pSequencia;		
			SEQ_tpCondRet condRetSeq;

			condRetSeq = SEQ_CriarSequencia(&pSequencia);
			if (condRetSeq != SEQ_CondRetOK)
				return PAC_CondRetFaltouMemoria;

			condRetLista = LIS_InserirElementoAntes(auxLis,pSequencia);
			if (condRetLista != LIS_CondRetOK)
				return PAC_CondRetFaltouMemoria;
		}

	/********************************************/
	return PAC_CondRetOK;
}

/***************************************************************************
*
*  Função: PAC  &Iniciar Novo Jogo
*
*  $ED Descrição da função
*  Cria as cartas e as destribui, baseado em uma dificuldade.
*
*  ****/
PAC_tpCondRet IniciarNovoJogo (int dificuldade) {

	int i;
	LIS_tppLista auxLis = NULL;
	LIS_tpCondRet condRetLista;
	BAR_tpBaralho pBaralho = NULL;

	/*	Inicia a Estrutura do jogo	*/
	if ( IniciarEstrutura() != PAC_CondRetOK )
		return PAC_CondRetFaltouMemoria;
	


	/*			Iniciando cartas de Baralho			*/
	
	IrFinalLista(tpPaciencia.pJogo);

	LIS_ObterValor(tpPaciencia.pJogo,(void**)&auxLis);
	LIS_ObterValor(auxLis,(void**)&pBaralho);
	
	BAR_IniciarBaralho(pBaralho,2,dificuldade);
	auxLis = NULL;
	

	/*		Iniciando cartas de 5 montes de compra		*/

	LIS_AvancarElementoCorrente(tpPaciencia.pJogo,-2);
	LIS_ObterValor(tpPaciencia.pJogo,(void**)&auxLis);
	IrInicioLista(auxLis);
	for (i = 0 ; i < TOT_MON ; i ++) {
		PIL_tpPilha auxPilha = NULL;
		MON_tpMonte pMonte = NULL;
		MON_tpCondRet condRetMonte;
		BAR_tpCondRet condRetBaralho;

		condRetBaralho = BAR_CriarSubPilhaBaralho(pBaralho,&auxPilha,10);
		if (condRetBaralho != BAR_CondRetOK)
			return PAC_CondRetFaltouMemoria;

		LIS_ObterValor(auxLis,(void**)&pMonte);
		
		condRetMonte = MON_AdicionarAoMonteCompras(pMonte,auxPilha);
		if (condRetMonte != MON_CondRetOK)
			return PAC_CondRetFaltouMemoria;
		
		tpPaciencia.qtdCompras++;
		
		PIL_DestruirPilhaCartas(auxPilha);
		LIS_AvancarElementoCorrente(auxLis,1);
		
	}
	auxLis = NULL;
	
	/*		Criando 10 sequencias de jogo		*/
	IrInicioLista(tpPaciencia.pJogo);
	condRetLista = LIS_ObterValor(tpPaciencia.pJogo,(void**)&auxLis);
	if (condRetLista == LIS_CondRetOK) {
		
		PIL_tpPilha auxPilha = NULL;
		BAR_tpCondRet condRetBaralho;

		condRetBaralho = BAR_CriarSubPilhaBaralho(pBaralho,&auxPilha,54);
		if(condRetBaralho != BAR_CondRetOK)
			return PAC_CondRetFaltouMemoria;

		IrFinalLista(auxLis);
		for (i = 0; i < TOT_SEQ; i ++) {
			
			SEQ_tpSequencia pSequencia = NULL;
			SEQ_tpCondRet condRetSeq;
			

			LIS_ObterValor(auxLis,(void**)&pSequencia);
			

			if (i > 5)
				condRetSeq = SEQ_IniciarSequencia (pSequencia, auxPilha,6);
			else
				condRetSeq = SEQ_IniciarSequencia (pSequencia, auxPilha,5);
			
			if(condRetSeq != SEQ_CondRetOK)
				return PAC_CondRetFaltouMemoria;

			SEQ_TornarUltimaInvisivel(pSequencia);
			SEQ_TornarUltimaInvisivel(pSequencia);
			SEQ_TornarUltimaInvisivel(pSequencia);
			SEQ_TornarUltimaInvisivel(pSequencia);
			if ( i > 5)
				SEQ_TornarUltimaInvisivel(pSequencia);

			LIS_AvancarElementoCorrente(auxLis,-1);
		} /* for */
	PIL_DestruirPilhaCartas(auxPilha);
	} /* if */
	/********************************************/
	return PAC_CondRetOK;
} /*fim função: Iniciar Jogo */

/***************************************************************************
*
*  Função: PAC  &Imprimir Jogo
*
*  $ED Descrição da função
*  Interface do jogo. Imprime todo estado do jogo atual para o usuario.
*
*  ****/

void ImprimirJogo () {

	int i;
	LIS_tppLista pListaSeq = NULL,pListaMonte = NULL, pListaSeqFin = NULL;
	

	/*		Imprimir Sequencias de Jogo		 */

	IrInicioLista(tpPaciencia.pJogo);
	LIS_ObterValor(tpPaciencia.pJogo,(void**)&pListaSeq);
	IrInicioLista(pListaSeq);
	for ( i = 0 ; i < TOT_SEQ ; i++ ) {
	
		SEQ_tpSequencia pSequencia = NULL;
		
		LIS_ObterValor(pListaSeq,(void**)&pSequencia);
		printf("%i. Sequencia",i);
		SEQ_ImprimirSequencia(pSequencia);
		LIS_AvancarElementoCorrente(pListaSeq,1);
	}

	printf("\nMontes de Compras Disponiveis: %i\nSequencias Finais Completas: %i\n\n",tpPaciencia.qtdCompras,tpPaciencia.qtdSeqFinais);
}	/*fim função: Imprimir Jogo */

/***************************************************************************
*
*  Função:  &Menu Jogo
*
*  $ED Descrição da função
*  Função implementa o menu dentro de um jogo.
*
*  ****/

PAC_tpCondRet MenuJogo (void) {

	int comando=0,indexOrigem,indexDestino,qtdCartas;
	PAC_tpCondRet condRetPaciencia;

	while (comando != 3 ) {
		
		ImprimirJogo();	
		printf("1. Mover Carta\n2. Comprar Cartas\n3. Salvar Jogo e Sair\n4. Sair\n");
		scanf(" %i",&comando);
		while(getchar() != '\n');
		
		switch (comando) {
		case 1: 
			printf("\nInsira Sequencia Origem, Destino, e quantidade de cartas\n");		
			scanf(" %i %i %i",&indexOrigem,&indexDestino,&qtdCartas);
			while(getchar() != '\n');
			condRetPaciencia = MoverSequencias(indexOrigem,indexDestino,qtdCartas);
			if (condRetPaciencia == PAC_CondRetJogoGanho) {
					TerminarJogoGanho();
					return PAC_CondRetOK;
			}
			break;	
		case 2: 
			condRetPaciencia = ComprarCartas();
			break;	
		case 3:
			condRetPaciencia = SalvarJogo();
			break;
		case 4: 
			printf("\nSeu jogo nao sera salvo <1 para continuar, 0 para voltar>\n");
			scanf(" %i",&comando);
			while(getchar() != '\n');
			//assegura para satisfazer o loop
			if(comando != 1)
				comando = 0;
			else {
				comando = 3;
				DestruirEstrutura();
			}	
			break;
		default: printf("\n>>Comando Invalido\n\n");
			system("pause");
			break;			
		}/*switch*/

		if (condRetPaciencia == PAC_CondRetFaltouMemoria)
			return condRetPaciencia;

	} /*while*/

	return condRetPaciencia;
}/*fim função: Menu Jogo */
/***************************************************************************
*
*  Função:  &Mover Sequencia
*
*  $ED Descrição da função
*  Função responsável por mover as cartas de uma sequência para outro, mensagens de erro aparecem na tela.
*
*  ****/
PAC_tpCondRet MoverSequencias (int indexOrigem, int indexDestino, int qtdCartas) {

	LIS_tppLista pLisSeq = NULL;
	SEQ_tpSequencia pSeqOrigem = NULL, pSeqDestino ;
	SEQ_tpCondRet condRetSeq;
	PIL_tpPilha pPilhaAux = NULL;
	FIN_tpCondRet condRetFin;

	//Tratar entradas erradas.
	if (indexOrigem > 9 || indexOrigem < 0 ) {
		printf("\n>>Sequencia de Origem invalida.\n\n");
		system("pause");
		return PAC_CondRetOK;
	}
	if(indexDestino > 9 || indexDestino < 0 ) {
		printf("\n>>Sequencia de Destino invalida.\n\n");
		system("pause");
		return PAC_CondRetOK;
	}
	if(qtdCartas < 1) {
		printf("\n>>Quantidade de cartas invalida.\n\n");
		system("pause");
		return PAC_CondRetOK;
	}

	//Obter a lista de sequencias
	IrInicioLista(tpPaciencia.pJogo);
	LIS_ObterValor(tpPaciencia.pJogo,(void**)&pLisSeq);

	//Obter a sequencia origem
	IrInicioLista(pLisSeq);
	LIS_AvancarElementoCorrente(pLisSeq,indexOrigem);
	LIS_ObterValor(pLisSeq,(void**)&pSeqOrigem);
	
	//Obter cartas da sequencia origem para pPilhaAux
	condRetSeq = SEQ_ObterPilhaCartas(pSeqOrigem,&pPilhaAux,qtdCartas);
	if (condRetSeq == SEQ_CondRetMovimentoInvalido){
		printf("\n>>Movimento Invalido\n\n");
		system("pause");
		return PAC_CondRetOK;
	}
	
	//Obter sequencia destino
	IrInicioLista(pLisSeq);
	LIS_AvancarElementoCorrente(pLisSeq,indexDestino);
	LIS_ObterValor(pLisSeq,(void**)&pSeqDestino);

	//Adicionar cartas em pilha destino
	condRetSeq = SEQ_AdicionarPilhaEmSequencia(pSeqDestino,pPilhaAux,qtdCartas);
	if (condRetSeq == SEQ_CondRetMovimentoInvalido){		
		//Devolver cartas para pilha origem
		SEQ_IniciarSequencia(pSeqOrigem,pPilhaAux,qtdCartas);
		printf("\n>>Movimento Invalido\n\n");
		system("pause");
		return PAC_CondRetOK;
	}

	PIL_DestruirPilhaCartas(pPilhaAux);
	
	//Virar carta em origem caso seja necessario.
	SEQ_VerificarVirarCarta(pSeqOrigem);
	
	//Adicionar sequência destino em sequência final caso necessário.
	condRetSeq = SEQ_VerificarSequenciaCompleta(pSeqDestino);
	if (condRetSeq == SEQ_CondRetOK) {
		LIS_tppLista pListaSeqFin =  NULL ;
		FIN_tpSeqFin pSeqFin = NULL;
		
		//Obter 13 cartas da sequencia final
		condRetSeq = SEQ_ObterPilhaCartas(pSeqDestino,&pPilhaAux,13);
		if ( condRetSeq != SEQ_CondRetOK)
			return PAC_CondRetFaltouMemoria;
		

		SEQ_VerificarVirarCarta(pSeqDestino);

		//Obter Lista de Sequencias Finais
		LIS_AvancarElementoCorrente(tpPaciencia.pJogo,2);
		LIS_ObterValor(tpPaciencia.pJogo,(void **)&pListaSeqFin);

		//Obter ultima Sequencia Final vazia
		IrInicioLista(pListaSeqFin);
		LIS_AvancarElementoCorrente(pListaSeqFin,tpPaciencia.qtdSeqFinais);
		LIS_ObterValor(pListaSeqFin,(void **)&pSeqFin);
		
		//Adicionar cartas na Sequência final
		condRetFin = FIN_AdicionarPilhaEmSeqFinal(pSeqFin,pPilhaAux);
		if( condRetFin != FIN_CondRetOK)
			return PAC_CondRetFaltouMemoria;

		tpPaciencia.qtdSeqFinais++;
		
		if(tpPaciencia.qtdSeqFinais == 8)
			return PAC_CondRetJogoGanho;
	}
	return PAC_CondRetOK;
}
/***************************************************************************
*
*  Função:   &Comprar Cartas
*
*  $ED Descrição da função
*  Funçao responsavel por obter um monte de compras valido e destribuir as cartas para as sequências de jogo.
*
*  ****/
PAC_tpCondRet ComprarCartas() {

	LIS_tppLista pLisSeq = NULL, pLisMonte = NULL;
	PIL_tpPilha pPilhaAux = NULL;
	MON_tpMonte pMonte = NULL;
	int i, posMonte = 5 - tpPaciencia.qtdCompras;


	//nao há compras disponiveis
	if (posMonte < 0 || posMonte > 4){
		printf("\n>>Nao ha compras disponiveis.\n\n");
		system("pause");
		return PAC_CondRetOK;
	}

	//obter lista de sequencias
	IrInicioLista(tpPaciencia.pJogo);
	LIS_ObterValor(tpPaciencia.pJogo,(void**)&pLisSeq);

	//obter lista de montes
	LIS_AvancarElementoCorrente(tpPaciencia.pJogo,1);
	LIS_ObterValor(tpPaciencia.pJogo,(void**)&pLisMonte);

	//obter monte nao vazio
	IrInicioLista(pLisMonte);
	LIS_AvancarElementoCorrente(pLisMonte,posMonte);
	LIS_ObterValor(pLisMonte,(void**)&pMonte);

	//preencher pilha com suas cartas
	if (PIL_CriarPilhaCartas(&pPilhaAux) != PIL_CondRetOK)
		return PAC_CondRetFaltouMemoria;

	if (MON_RetornarCompra(pMonte,pPilhaAux) != MON_CondRetOK)
		return PAC_CondRetFaltouMemoria;

	//destribuir cartas para as sequencias
	IrInicioLista(pLisSeq);
	for ( i = 0; i < TOT_SEQ ; i ++) {
	
		SEQ_tpSequencia pSequencia = NULL;

		LIS_ObterValor(pLisSeq,(void**)&pSequencia);

		if (SEQ_IniciarSequencia(pSequencia,pPilhaAux,1) != SEQ_CondRetOK)
			return PAC_CondRetFaltouMemoria;

		LIS_AvancarElementoCorrente(pLisSeq,1);
	}

	tpPaciencia.qtdCompras--;
	return PAC_CondRetOK;

}
/***************************************************************************
*
*  Função:   &Terminar Jogo Ganho
*
*  $ED Descrição da função
*  Função responsável por apresentar mensagem de ganho de jogo
*
*  ****/
void TerminarJogoGanho(){

system("cls");
printf("\n***********************************");
printf("\n*");
printf("\n* Parabens voce ganhou o jogo!");
printf("\n*");
printf("\n***********************************\n\n");
system("pause");
return;
}

/***************************************************************************
*
*  Função:   &Destruir Estrutura
*
*  $ED Descrição da função
*  Função responsável por apresentar mensagem de ganho de jogo
*
*  ****/

void DestruirEstrutura() {

	tpPaciencia.qtdCompras = 0;
	tpPaciencia.qtdSeqFinais = 0;
	LIS_DestruirLista(tpPaciencia.pJogo);
	tpPaciencia.pJogo = NULL;
	
}

/***************************************************************************
*
*  Função: PAC  &Salvar Jogo
*
*  $ED Descrição da função
*  Função responsavel por salvar o jogo em um arquivo txt. Função destroi toda as estruturas do jogo.
*
*  ****/
PAC_tpCondRet SalvarJogo() {

	int i;
	FILE *fp;
	LIS_tppLista pLisSeq = NULL, pLisMonte = NULL,pLisSeqFin = NULL,pLisBar = NULL;
	
	fp = fopen(NOME_ARQ,"wt");
	if ( fp == NULL) {
		printf("\n>>Erro ao abrir arquivo para salvar o jogo.\n\n");
		system("pause");
		return PAC_CondRetFaltouMemoria;
	}
	/*		Salvando Sequencias		*/

	//Obter lista de sequencias
	IrInicioLista(tpPaciencia.pJogo);
	LIS_ObterValor(tpPaciencia.pJogo,(void**)&pLisSeq);
	
	IrInicioLista(pLisSeq);
	for (i = 0 ; i < TOT_SEQ ; i ++) {
	
		SEQ_tpSequencia pSequencia = NULL;
		PIL_tpPilha pPilhaAux = NULL;
		CAR_tpCarta carta = NULL;
		int qtdCartas = 0 ;

		//Obter sequencia sua pilha e qtd de cartas nela
		LIS_ObterValor(pLisSeq,(void**)&pSequencia);	
		SEQ_RetornarPilhaSequencia(pSequencia,&pPilhaAux);
		PIL_QuantidadeCartas(pPilhaAux, &qtdCartas);
		
		fprintf(fp,"%i ",qtdCartas);
		
		//Escrever cartas no arquivo
		PIL_IrFinalPilhaCartas(pPilhaAux);
		while(qtdCartas) {
			CAR_tpValor valor;
			CAR_tpNaipe naipe;
			CAR_tpEstado estado;
			char letraValor,letraNaipe,letraEstado;
			PIL_tpCondRet condRetPilha;

			PIL_VerCarta(pPilhaAux,&carta);
			CAR_ObterValor(carta,&valor);
			CAR_ObterNaipe(carta,&naipe);
			CAR_ObterEstado(carta,&estado);

			ObterStringValor(valor,&letraValor);
			ObterStringNaipe(naipe,&letraNaipe);
			ObterStringEstado(estado,&letraEstado);		
			fprintf(fp,"%c%c%c ",letraValor,letraNaipe,letraEstado);

			condRetPilha = PIL_AvancarElementoCorrente(pPilhaAux,-1);
			qtdCartas--;
		}
		   fprintf(fp,"\n");
		  
		   PIL_EsvaziarPilhaCartas(pPilhaAux);
		   PIL_DestruirPilhaCartas(pPilhaAux);
		  
		   //Excluir sequência
		   LIS_ExcluirElemento( pLisSeq );	   
	}
	//Excluir cabeça da lista de sequências
	LIS_ExcluirElemento( tpPaciencia.pJogo );

	/*		Salvando Monte de Compras		*/
	
	//Obter lista de monte
	LIS_ObterValor(tpPaciencia.pJogo,(void**)&pLisMonte);
	
	IrInicioLista(pLisMonte);
	for (i = 0 ; i < TOT_MON ; i++) {
	
		MON_tpMonte pMonte = NULL;	
		PIL_tpPilha pPilhaAux = NULL;
		PIL_tpCondRet condRetPilha;
		int qtdCartas = 0;

		//Obter pilha de monte
		condRetPilha = PIL_CriarPilhaCartas(&pPilhaAux);
		if (condRetPilha != PIL_CondRetOK)
			return PAC_CondRetFaltouMemoria;

		LIS_ObterValor(pLisMonte,(void**)&pMonte);
		MON_RetornarCompra (pMonte, pPilhaAux);
		PIL_IrFinalPilhaCartas(pPilhaAux);
		PIL_QuantidadeCartas(pPilhaAux, &qtdCartas);
		fprintf(fp,"%i ",qtdCartas);

		//Escrever cartas no arquivo
		PIL_IrFinalPilhaCartas(pPilhaAux);

		while ( qtdCartas ){
			CAR_tpCarta carta;
			CAR_tpValor valor;
			CAR_tpNaipe naipe;
			CAR_tpEstado estado;
			char letraValor,letraNaipe,letraEstado;
			
			PIL_VerCarta(pPilhaAux,&carta);
			CAR_ObterValor(carta,&valor);
			CAR_ObterNaipe(carta,&naipe);
			CAR_ObterEstado(carta,&estado);

			ObterStringValor(valor,&letraValor);
			ObterStringNaipe(naipe,&letraNaipe);
			ObterStringEstado(estado, &letraEstado);
			fprintf(fp,"%c%c%c ",letraValor,letraNaipe,letraEstado);

			 condRetPilha = PIL_AvancarElementoCorrente(pPilhaAux,-1);
			 qtdCartas--;
		}
		   fprintf(fp,"\n");

		   PIL_EsvaziarPilhaCartas(pPilhaAux);
		   PIL_DestruirPilhaCartas(pPilhaAux);
		   //Excluir monte de compras
		   LIS_ExcluirElemento( pLisMonte );
	}
	//Excluir cabeça da lista de monte de compras
	LIS_ExcluirElemento( tpPaciencia.pJogo );

	//Obter lista de sequencias finais
	LIS_ObterValor(tpPaciencia.pJogo,(void**)&pLisSeqFin);

	for (i = 0 ; i < TOT_FIN ; i++ ) {
	
		FIN_tpSeqFin pSeqFin = NULL;	
		PIL_tpPilha pPilhaAux = NULL;
		int qtdCartas = 0;

		//Obter pilha de sequencia final
		PIL_CriarPilhaCartas(&pPilhaAux);
		LIS_ObterValor(pLisSeqFin,(void**)&pSeqFin);
		
		FIN_ObterPilhaSeqFin( pSeqFin, &pPilhaAux);


		PIL_IrFinalPilhaCartas(pPilhaAux);
		PIL_QuantidadeCartas(pPilhaAux, &qtdCartas);
		fprintf(fp,"%i ",qtdCartas);

		//Escrever cartas no arquivo
		PIL_IrFinalPilhaCartas(pPilhaAux);

		while ( qtdCartas ){
			CAR_tpCarta carta;
			CAR_tpValor valor;
			CAR_tpNaipe naipe;
			CAR_tpEstado estado;
			char letraValor,letraNaipe,letraEstado;
			
			PIL_VerCarta(pPilhaAux,&carta);
			CAR_ObterValor(carta,&valor);
			CAR_ObterNaipe(carta,&naipe);
			CAR_ObterEstado(carta,&estado);

			ObterStringValor(valor,&letraValor);
			ObterStringNaipe(naipe,&letraNaipe);
			ObterStringEstado(estado,&letraEstado);
			fprintf(fp,"%c%c%c ",letraValor,letraNaipe,letraEstado);

			 PIL_AvancarElementoCorrente(pPilhaAux,-1);
			 qtdCartas--;
		}
		   fprintf(fp,"\n");

		   PIL_EsvaziarPilhaCartas(pPilhaAux);
		   PIL_DestruirPilhaCartas(pPilhaAux);
		   FIN_DestruirSeqFinal(pSeqFin);

		   //Excluir sequencia final
		   LIS_ExcluirElemento( pLisSeqFin );
	}
	//Excluir cabeça da lista de sequencia final
	LIS_ExcluirElemento( tpPaciencia.pJogo );

	/*	 Excluir baralho e cabeça da lista de baralhos	*/
	LIS_ObterValor(tpPaciencia.pJogo,(void**)&pLisBar);
	LIS_ExcluirElemento( pLisBar );
	LIS_ExcluirElemento( tpPaciencia.pJogo );

	
	fclose(fp);

	printf("\n>>Jogo Salvo com Sucesso\n\n");
	system("pause");
	return PAC_CondRetOK;
}

/***************************************************************************
*
*  Função: PAC  &Carregar Jogo
*
*  $ED Descrição da função
*  Função responsável por ler um arquivo de txt que seja valido e reconstrua o jogo a partir dele.
*
*  ****/
PAC_tpCondRet CarregarJogo (){

	int i;
	FILE *fp;
	LIS_tppLista pLisSeq = NULL, pLisMonte = NULL,pLisSeqFin = NULL,pLisBar = NULL;
	PIL_tpPilha pPilhaAux = NULL;
	PIL_tpCondRet condRetPilha;
	
	if ( IniciarEstrutura() != PAC_CondRetOK )
		return PAC_CondRetFaltouMemoria;

	fp = fopen(NOME_ARQ,"rt");
	if (fp == NULL)
		return PAC_CondRetErroLeituraArquivo;
	
	condRetPilha = PIL_CriarPilhaCartas(&pPilhaAux);
	if (condRetPilha != PIL_CondRetOK)
		return PAC_CondRetFaltouMemoria;
		
	/*		Salvando Sequencias		*/

	//Obter lista de sequencias
	IrInicioLista(tpPaciencia.pJogo);
	LIS_ObterValor(tpPaciencia.pJogo,(void**)&pLisSeq);

	IrInicioLista(pLisSeq);
	for (i = 0 ; i < TOT_SEQ ; i ++) {
		int qtdCartas = 0,j;
		char cValor,cNaipe,cEstado;
		SEQ_tpSequencia pSequencia = NULL;
		

		LIS_ObterValor(pLisSeq,(void**)&pSequencia);

		if(fscanf(fp," %i",&qtdCartas) != 1)
			return PAC_CondRetErroLeituraArquivo;		
		
			for (j = 0 ; j < qtdCartas ; j ++) {
				CAR_tpCarta carta;
				CAR_tpValor valor;
				CAR_tpNaipe naipe;
				CAR_tpEstado estado;
				CAR_tpCondRet condRetCarta;
				PAC_tpCondRet condRetPaciencia;

				if(fscanf(fp," %c%c%c",&cValor,&cNaipe,&cEstado) != 3)
					return PAC_CondRetErroLeituraArquivo;				

				condRetPaciencia = ObterTipoValor(cValor,&valor);
				if (condRetPaciencia == PAC_CondRetErroLeituraArquivo){
					return condRetPaciencia;
				}
				condRetPaciencia = ObterTipoNaipe(cNaipe,&naipe);
				if (condRetPaciencia == PAC_CondRetErroLeituraArquivo){
					return condRetPaciencia;
				}
				condRetPaciencia = ObterTipoEstado(cEstado,&estado);
				if (condRetPaciencia == PAC_CondRetErroLeituraArquivo){
					return condRetPaciencia;
				}

				condRetCarta = CAR_CriarCarta(&carta,valor,naipe);
				if (condRetCarta != CAR_CondRetOK)
					return PAC_CondRetFaltouMemoria;

				if (estado == CAR_EstadoInvisivel)
					CAR_TornarInvisivel(carta);
				condRetPilha = PIL_AdicionarCarta(pPilhaAux,carta);
				if (condRetPilha != PIL_CondRetOK)
					return PAC_CondRetFaltouMemoria;
			}
			SEQ_IniciarSequencia(pSequencia,pPilhaAux,qtdCartas);
			PIL_EsvaziarPilhaCartas(pPilhaAux);
		    LIS_AvancarElementoCorrente(pLisSeq,1);
	}

	LIS_AvancarElementoCorrente(tpPaciencia.pJogo,1);
	LIS_ObterValor(tpPaciencia.pJogo,(void**)&pLisMonte);
	IrInicioLista(pLisMonte);

	for (i = 0 ; i < TOT_MON ; i ++) {
		int qtdCartas = 0,j;
		char cValor,cNaipe,cEstado;
		MON_tpMonte pMonte = NULL;
				
		LIS_ObterValor(pLisMonte,(void**)&pMonte);

		if(fscanf(fp," %i",&qtdCartas) != 1)
			return PAC_CondRetErroLeituraArquivo;		
		
		if (qtdCartas == 10 ) {
			for (j = 0 ; j < qtdCartas ; j ++) {
				CAR_tpCarta carta = NULL;
				CAR_tpValor valor;
				CAR_tpNaipe naipe;
				CAR_tpEstado estado;
				CAR_tpCondRet condRetCarta;
				PAC_tpCondRet condRetPaciencia;

				if(fscanf(fp," %c%c%c",&cValor,&cNaipe,&cEstado) != 3)
					return PAC_CondRetErroLeituraArquivo;				

				condRetPaciencia = ObterTipoValor(cValor,&valor);		
				if (condRetPaciencia == PAC_CondRetErroLeituraArquivo){
					return condRetPaciencia;
				}
				condRetPaciencia = ObterTipoNaipe(cNaipe,&naipe);
				if (condRetPaciencia == PAC_CondRetErroLeituraArquivo){
					return condRetPaciencia;
				}
				condRetPaciencia = ObterTipoEstado(cEstado,&estado);
				if (condRetPaciencia == PAC_CondRetErroLeituraArquivo){
					return condRetPaciencia;
				}

				condRetCarta = CAR_CriarCarta(&carta,valor,naipe);
				if (condRetCarta != CAR_CondRetOK)
					return PAC_CondRetFaltouMemoria;

				condRetPilha = PIL_AdicionarCarta(pPilhaAux,carta);
				if (condRetPilha != PIL_CondRetOK)
					return PAC_CondRetFaltouMemoria;
			}
			MON_AdicionarAoMonteCompras(pMonte,pPilhaAux);
			tpPaciencia.qtdCompras++;
		}
		else if (qtdCartas !=0)
			return PAC_CondRetErroLeituraArquivo;

		LIS_AvancarElementoCorrente(pLisMonte,1);
	}

	LIS_AvancarElementoCorrente(tpPaciencia.pJogo,1);
	LIS_ObterValor(tpPaciencia.pJogo,(void**)&pLisSeqFin);
	IrInicioLista(pLisSeqFin);

	for (i = 0 ; i < TOT_FIN ; i ++) {
		int qtdCartas = 0,j;
		char cValor,cNaipe,cEstado;
		FIN_tpSeqFin pSeqFin = NULL;
		PIL_tpPilha pPilha = NULL;

		LIS_ObterValor(pLisSeqFin,(void**)&pSeqFin);
		PIL_CriarPilhaCartas(&pPilha);

		if(fscanf(fp," %i",&qtdCartas) != 1)
			return PAC_CondRetErroLeituraArquivo;		
		

		if(qtdCartas == 13) {

			for (j = 0 ; j < qtdCartas ; j ++) {
				CAR_tpCarta carta;
				CAR_tpValor valor;
				CAR_tpNaipe naipe;
				CAR_tpEstado estado;
				CAR_tpCondRet condRetCarta;
				PAC_tpCondRet condRetPaciencia;

				if(fscanf(fp," %c%c%c",&cValor,&cNaipe,&cEstado) != 3)
					return PAC_CondRetErroLeituraArquivo;				



				condRetPaciencia = ObterTipoValor(cValor,&valor);
				if (condRetPaciencia == PAC_CondRetErroLeituraArquivo){
					return condRetPaciencia;
				}
				ObterTipoNaipe(cNaipe,&naipe);
				if (condRetPaciencia == PAC_CondRetErroLeituraArquivo){
					return condRetPaciencia;
				}
				condRetPaciencia = ObterTipoEstado(cEstado,&estado);
				if (condRetPaciencia == PAC_CondRetErroLeituraArquivo){
					return condRetPaciencia;
				}

				condRetCarta = CAR_CriarCarta(&carta,valor,naipe);
				if (condRetCarta != CAR_CondRetOK)
					return PAC_CondRetFaltouMemoria;

				if (estado == CAR_EstadoInvisivel)
					CAR_TornarInvisivel(carta);
				
				condRetPilha = PIL_AdicionarCarta(pPilha,carta);
				if (condRetPilha != PIL_CondRetOK)
					return PAC_CondRetFaltouMemoria;
			}
			FIN_AdicionarPilhaEmSeqFinal(pSeqFin,pPilha);
			tpPaciencia.qtdSeqFinais++;
		}
		else if (qtdCartas != 0)
			return PAC_CondRetErroLeituraArquivo;

			LIS_AvancarElementoCorrente(pLisSeqFin,1);
	}

	PIL_DestruirPilhaCartas(pPilhaAux);

	return PAC_CondRetOK;
}

/***************************************************************************
*
*  Função: &Obter String Valor
*
*  $ED Descrição da função
*  Função recebe um tipo valor e retorna o caracter correspondente para escrever no arquivo.
*
*  ****/


PAC_tpCondRet ObterStringValor ( CAR_tpValor valor, char *cValor ) {


	switch (valor) {
	
	
	case _A: *cValor = 'A';
			break;
	case _2: *cValor = '2';
			break;
	case _3: *cValor = '3';
			break;
	case _4: *cValor = '4';
			break;
	case _5: *cValor = '5';
			break;	
	case _6: *cValor = '6';
			break;	
	case _7: *cValor = '7';
			break;	
	case _8: *cValor = '8';
			break;
	case _9: *cValor = '9';
			break;
	case _10: *cValor = 'D';
			break;
	case _J: *cValor = 'J';
			break;
	case _Q: *cValor = 'Q';
			break;
	case _K: *cValor = 'K';
			break;
	default: return PAC_CondRetCartaInvalida;
			break;
	}	
	return PAC_CondRetOK;
}

/***************************************************************************
*
*  Função: &Obter String Naipe
*
*  $ED Descrição da função
*  Função recebe um tipo naipe e retorna o caracter correspondente para escrever no arquivo.
*
*  ****/
PAC_tpCondRet ObterStringNaipe ( CAR_tpNaipe naipe, char *cNaipe ) {
		
	switch (naipe) {
	
	case Espadas: *cNaipe = 'E';
			break;
	case Ouros: *cNaipe = 'O';
			break;
	case Copas: *cNaipe = 'C';
			break;
	case Paus: *cNaipe = 'P';
			break;
	default: return PAC_CondRetCartaInvalida;
			break;
	}
	return PAC_CondRetOK;
}

/***************************************************************************
*
*  Função: &Obter String Estado
*
*  $ED Descrição da função
*  Função recebe um tipo estado e retorna o caracter correspondente para escrever no arquivo.
*
*  ****/

PAC_tpCondRet ObterStringEstado ( CAR_tpEstado estado, char *cEstado ) {
	
	switch (estado) {
	
	case CAR_EstadoVisivel: *cEstado = 'V';
			break;
	case CAR_EstadoInvisivel: *cEstado = 'I';
			break;
	default: return PAC_CondRetCartaInvalida;
			break;
	}
	return PAC_CondRetOK;
}

/***************************************************************************
*
*  Função: &Obter Tipo Valor
*
*  $ED Descrição da função
*  Função recebe um caracter valor e retorna o tipo valor correto para reconstrução da carta
*
*  ****/
PAC_tpCondRet ObterTipoValor ( char cValor,CAR_tpValor *valor) {

	switch (cValor) {
		
	case 'A': *valor = _A;
			break;
	case '2': *valor = _2;
			break;
	case '3': *valor = _3;
			break;
	case '4': *valor = _4;
			break;
	case '5': *valor = _5;
			break;	
	case '6': *valor = _6;
			break;	
	case '7': *valor = _7;
			break;	
	case '8': *valor = _8;
			break;
	case '9': *valor = _9;
			break;
	case 'D': *valor = _10;
			break;
	case 'J': *valor = _J;
			break;
	case 'Q': *valor = _Q;
			break;
	case 'K': *valor = _K;
			break;
	default: return PAC_CondRetErroLeituraArquivo;
			break;
	}
	return PAC_CondRetOK;
}
/***************************************************************************
*
*  Função: &Obter Tipo Naipe
*
*  $ED Descrição da função
*  Função recebe um caracter naipe e retorna o tipo naipe correto para reconstrução da carta
*
*  ****/
PAC_tpCondRet ObterTipoNaipe ( char cNaipe, CAR_tpNaipe *naipe ) {
		
	switch (cNaipe) {
	
	case 'E': *naipe = Espadas;
			break;
	case 'O': *naipe =  Ouros;
			break;
	case 'C': *naipe =  Copas;
			break;
	case 'P': *naipe =  Paus;
			break;
	default: return PAC_CondRetErroLeituraArquivo;
			break;
	}
	return PAC_CondRetOK;
}

/***************************************************************************
*
*  Função: &Obter Tipo Estado
*
*  $ED Descrição da função
*  Função recebe um caracter estado e retorna o tipo estado correto para reconstrução da carta
*
*  ****/

PAC_tpCondRet ObterTipoEstado ( char cEstado, CAR_tpEstado *estado ) {

	if (cEstado == 'V')
		*estado = CAR_EstadoVisivel;
	else if (cEstado == 'I')
		*estado = CAR_EstadoInvisivel;
	else
		return PAC_CondRetErroLeituraArquivo;
	return PAC_CondRetOK;
}

/********** Fim do módulo de implementação: PAC Principal **********/