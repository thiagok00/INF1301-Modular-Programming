#if ! defined( LISTA_ )
#define LISTA_
/***************************************************************************
*
*  $MCD M�dulo de defini��o: LIS  Lista duplamente encadeada
*
*  Arquivo gerado:              LISTA.h
*  Letras identificadoras:      LIS
*
*  Nome da base de software:    Arcabou�o para a automa��o de testes de programas redigidos em C
*  Arquivo da base de software: D:\AUTOTEST\PROJETOS\LISTA.BSW
*
*  Projeto: INF 1301 / 1628 Automatiza��o dos testes de m�dulos C
*  Gestor:  LES/DI/PUC-Rio
*  Autores: avs, thk , adp, ilg
*
*  $HA Hist�rico de evolu��o:
*     Vers�o  Autor    Data     Observa��es
*	  5       thk	25/abr/2015 adapta��o dos retornos das fun��es
*     4       avs   01/fev/2006 criar linguagem script simb�lica
*     3       avs   08/dez/2004 uniformiza��o dos exemplos
*     2       avs   07/jul/2003 unifica��o de todos os m�dulos em um s� projeto
*     1       avs   16/abr/2003 in�cio desenvolvimento
*
*  $ED Descri��o do m�dulo
*     Implementa listas gen�ricas duplamente encadeadas.
*     Podem existir n listas em opera��o simultaneamente.
*     As listas possuem uma cabe�a encapsulando o seu estado.
*
*     Cada lista � homog�nea quanto ao tipo dos dados que armazena.
*     Cada elemento da lista referencia o valor que cont�m.
*
*     Os ponteiros para os dados s�o copiados para elementos da lista.
*        N�o � copiado o valor apontado por estes ponteiros.
*
*     O controle da destrui��o do valor de um elemento a ser exclu�do
*        � realizado por uma fun��o fornecida pelo usu�rio.
*
*     Cada lista referencia uma fun��o que determina como devem ser
*        desalocados os dados nela contidos.
*
*     A fun��o de libera��o dos valores contidos nos elementos deve
*        assegurar a libera��o de todos os espa�os refer�nciados pelo
*        valor contido em um elemento.
*        Esta fun��o � chamada antes de se desalocar um elemento
*        de uma lista.
*        Caso n�o seja necess�rio desalocar o valor referenciado pelo
*        elemento, o ponteiro para a fun��o de libera��o poder� ser NULL .
*        Caso o elemento da lista seja a �nica �ncora do valor referenciado,
*        esta fun��o deve promover a destrui��o (free) desse valor e
*        de todos os dados nele ancorados.
*
***************************************************************************/
 
#if defined( LISTA_OWN )
   #define LISTA_EXT
#else
   #define LISTA_EXT extern
#endif

/***** Declara��es exportadas pelo m�dulo *****/

/* Tipo refer�ncia para uma lista */

typedef struct LIS_tagLista * LIS_tppLista ;


/***********************************************************************
*
*  $TC Tipo de dados: LIS Condi��es de retorno
*
*
*  $ED Descri��o do tipo
*     Condi��es de retorno das fun��es da lista
*
***********************************************************************/

   typedef enum {

         LIS_CondRetOK ,
               /* Concluiu corretamente */

         LIS_CondRetListaVazia ,
               /* A lista n�o cont�m elementos */

         LIS_CondRetFimLista ,
               /* Foi atingido o fim de lista */

         LIS_CondRetNaoAchou ,
               /* N�o encontrou o valor procurado */

         LIS_CondRetFaltouMemoria,
               /* Faltou mem�ria ao tentar criar um elemento de lista */

		 LIS_CondRetListaNaoExiste

   } LIS_tpCondRet ;


/***********************************************************************
*
*  $FC Fun��o: LIS  &Criar lista
*
*  $ED Descri��o da fun��o
*     Cria uma lista gen�rica duplamente encadeada.
*     Os poss�veis tipos s�o desconhecidos a priori.
*     A tipagem � implicita.
*     N�o existe identificador de tipo associado � lista.
*
*  $EP Par�metros
*     pLista - endere�o de ponteiro para lista onde deve ser criada
*     ExcluirValor  - ponteiro para a fun��o que processa a
*                     exclus�o do valor referenciado pelo elemento
*                     a ser exclu�do.
*                     Ver descri��o do m�dulo.
*
*  $FV Valor retornado
*     Se executou corretamente retorna condRetOK e pLista ser� o ponteiro da lista criada.
*     Este ponteiro ser� utilizado pelas fun��es que manipulem esta lista.
*
*     Se ocorreu algum erro, por exemplo falta de mem�ria ou dados errados,
*     a fun��o retornar� CondRetFaltouMemoria.
*
*     Assertivas de entrada:
*     - O endere�o de ponteiro para a lista recebida como par�metro deve ser v�lido
*     - O ponteiro para a fun��o ExcluirValor deve apontar para a fun��o
*     Assertivas de sa�da:
*     - O espa�o de mem�ria para a lista foi alocado com sucesso
*
*
***********************************************************************/

LIS_tpCondRet LIS_CriarLista( LIS_tppLista *pLista ,void   ( * ExcluirValor ) ( void * pDado ) );


/***********************************************************************
*
*  $FC Fun��o: LIS  &Destruir lista
*
*  $ED Descri��o da fun��o
*     Destr�i a lista fornecida.
*     O par�metro ponteiro para a lista n�o � modificado.
*     Se ocorrer algum erro durante a destrui��o, a lista resultar�
*     estruturalmente incorreta.
*     OBS. n�o existe previs�o para poss�veis falhas de execu��o.
*
*  $FV Valor retornado
*     LIS_CondRetOK    - destruiu sem problemas
*	  LIS_CondRetListaNaoExiste - recebeu lista inexistente
*
*     Assertivas de entrada:
*     - O ponteiro para a lista recebida como par�metro deve ser v�lido
*     Assertivas de sa�da:
*     - O espa�o de mem�ria para a lista foi liberado com sucesso
*
***********************************************************************/

   LIS_tpCondRet LIS_DestruirLista( LIS_tppLista pLista ) ;


/***********************************************************************
*
*  $FC Fun��o: LIS  &Esvaziar lista
*
*  $ED Descri��o da fun��o
*     Elimina todos os elementos, sem contudo eliminar a lista
*
*  $EP Par�metros
*     pLista - ponteiro para a lista a ser esvaziada
*
*  $FV Valor retornado
*     LIS_CondRetOK    - esvaziou
*	  LIS_CondRetListaNaoExiste - recebeu lista inexistente
*
*     Assertivas de entrada:
*     - O ponteiro para a lista recebida como par�metro deve ser v�lido
*     Assertivas de sa�da:
*     - O espa�o de mem�ria para a lista foi esvaziado (recebido NULL) com sucesso
*
*
***********************************************************************/

	LIS_tpCondRet LIS_EsvaziarLista( LIS_tppLista pLista );


/***********************************************************************
*
*  $FC Fun��o: LIS  &Inserir elemento antes
*
*  $ED Descri��o da fun��o
*     Insere novo elemento antes do elemento corrente.
*     Caso a lista esteja vazia, insere o primeiro elemento da lista.
*
*  $EP Par�metros
*     pLista - ponteiro para a lista onde deve ser inserido o elemento
*     pValor - ponteiro para o valor do novo elemento
*              Pode ser NULL
*
*  $FV Valor retornado
*     LIS_CondRetOK
*     LIS_CondRetFaltouMemoria
*
*     Assertivas de entrada:
*     - O ponteiro para a lista recebida como par�metro deve ser v�lido
*     - O valor deve ser gen�rico
*     Assertivas de sa�da:
*     - O n�mero de elementos da lista foi acrescentado 1
*     - O ponteiro para o n� corrente passou a apontar para o novo n�
*
***********************************************************************/

   LIS_tpCondRet LIS_InserirElementoAntes( LIS_tppLista pLista ,
                                           void * pValor        ) ;


/***********************************************************************
*
*  $FC Fun��o: LIS  &Inserir elemento ap�s
*
*  $ED Descri��o da fun��o
*     Insere novo elemento ap�s o elemento corrente.
*     Caso a lista esteja vazia, insere o primeiro elemento da lista.
*
*  $EP Par�metros
*     Par�metros
*        pLista - ponteiro para a lista onde deve ser inserido o elemento
*        pValor - ponteiro para o valor do novo elemento
*                 Pode ser NULL
*           
*
*  $FV Valor retornado
*     Valor retornado
*        LIS_CondRetOK
*        LIS_CondRetFaltouMemoria
*
*     Assertivas de entrada:
*     - O ponteiro para a lista recebida como par�metro deve ser v�lido
*     - O valor deve ser gen�rico
*     Assertivas de sa�da:
*     - O n�mero de elementos da lista foi acrescentado 1
*     - O ponteiro para o n� corrente passou a apontar para o novo n�
*
***********************************************************************/

   LIS_tpCondRet LIS_InserirElementoApos( LIS_tppLista pLista ,
                                          void * pValor        )
       ;


/***********************************************************************
*
*  $FC Fun��o: LIS  &Excluir elemento
*
*  $ED Descri��o da fun��o
*     Exclui o elemento corrente da lista dada.
*     Se existir o elemento aa esquerda do corrente ser� o novo corrente.
*     Se n�o existir e existir o elemento � direita, este se tornar� corrente.
*     Se este tamb�m n�o existir a lista tornou-se vazia.
*
*  $EP Par�metros
*     pLista    - ponteiro para a lista na qual deve excluir.
*
*  $FV Valor retornado
*     LIS_CondRetOK
*     LIS_CondRetListaVazia
*
*     Assertivas de entrada:
*     - O ponteiro para a lista recebida como par�metro deve ser v�lido
*     Assertivas de sa�da:
*     - O n�mero de elementos da lista foi reduzido
*     - O ponteiro para o n� corrente passou a apontar para o n� seguinte
*
***********************************************************************/

   LIS_tpCondRet LIS_ExcluirElemento( LIS_tppLista pLista ) ;


/***********************************************************************
*
*  $FC Fun��o: LIS  &Obter refer�ncia para o valor contido no elemento
*
*  $ED Descri��o da fun��o
*     Obtem a refer�ncia para o valor contido no elemento corrente da lista
*
*  $EP Par�metros
*     pLista - ponteiro para a lista de onde se quer o valor
*	 *valor - ponteiro para receber o valor
*
*  $FV Valor retornado
*
*		LIS_CondRetListaNaoExiste - pLista = NULL
*		LIS_CondRetListaVazia - elemento corrente nao existe
*		LIS_CondRetOK - obteve corretamente
*
*     Assertivas de entrada:
*     - O ponteiro para a lista recebida como par�metro deve ser v�lido
*     - O valor deve poder receber algo gen�rico
*     Assertivas de sa�da:
*     - O valor (segundo par�metro) possui o valor do n� corrente da lista
*
*
***********************************************************************/

      LIS_tpCondRet LIS_ObterValor( LIS_tppLista pLista, void **valor);


/***********************************************************************
*
*  $FC Fun��o: LIS  &Ir para o elemento inicial
*
*  $ED Descri��o da fun��o
*     Torna corrente o primeiro elemento da lista.
*     Faz nada se a lista est� vazia.
*
*  $EP Par�metros
*     pLista - ponteiro para a lista a manipular
*
*  $FV Valor retornado
*	LIS_CondRetListaNaoExiste - pLista = NULL
*	LIS_CondRetOK - executou corretamente
*
*
*     Assertivas de entrada:
*     - O ponteiro para a lista recebida como par�metro deve ser v�lido
*     Assertivas de sa�da:
*     - O n� corrente apontado pela pLista aponta para o primeiro n�
*
***********************************************************************/

   LIS_tpCondRet IrInicioLista( LIS_tppLista pLista ) ;


/***********************************************************************
*
*  $FC Fun��o: LIS  &Ir para o elemento final
*
*  $ED Descri��o da fun��o
*     Torna corrente o elemento final da lista.
*     Faz nada se a lista est� vazia.
*
*  $EP Par�metros
*     pLista - ponteiro para a lista a manipular
*
*  $FV Valor retornado
*	LIS_CondRetListaNaoExiste - pLista = NULL
*	LIS_CondRetOK - executou corretamente
*
*     Assertivas de entrada:
*     - O ponteiro para a lista recebida como par�metro deve ser v�lido
*     Assertivas de sa�da:
*     - O n� corrente apontado pela pLista aponta para o �ltimo n�
*
***********************************************************************/

   LIS_tpCondRet IrFinalLista( LIS_tppLista pLista ) ;


/***********************************************************************
*
*  $FC Fun��o: LIS  &Avan�ar elemento
*
*  $ED Descri��o da fun��o
*     Avan�a o elemento corrente numElem elementos na lista
*     Se numElem for positivo avan�a em dire��o ao final
*     Se numElem for negativo avan�a em dire��o ao in�cio
*     numElem pode ser maior do que o n�mro de elementos existentes na
*               dire��o desejada
*     Se numElem for zero somente verifica se a lista est� vazia
*
*  $EP Par�metros
*     pLista  - ponteiro para a lista a ser manipulada
*     numElem - o n�mero de elementos a andar
*
*  $FV Valor retornado
*     CondRetOK         - se numElem elementos tiverem sido andados
*     CondRetFimLista   - se encontrou o fim da lista antes de andar numElem
*                         elementos
*     CondRetListaVazia - se a lista est� vazia
*
*     Assertivas de entrada:
*     - O ponteiro para a lista recebida como par�metro deve ser v�lido
*     - O n�mero de elementos deve ser menor ou igual ao tamanho da lista
*     Assertivas de sa�da:
*     - O n� corrente aponta para numElem n�s ap�s o que apontava antes
*
***********************************************************************/

   LIS_tpCondRet LIS_AvancarElementoCorrente( LIS_tppLista pLista ,
                                              int numElem ) ;


/***********************************************************************
*
*  $FC Fun��o: LIS  &Procurar elemento contendo valor
*
*  $ED Descri��o da fun��o
*     Procura o elemento que referencia o valor dado.
*     A fun��o compara ponteiro e n�o conte�do apontado.
*
*  $EP Par�metros
*     pLista  - ponteiro para a lista onde procura
*     pValor  - ponteiro para o valor procurado
*               Pode ser NULL
*
*  $FV Valor retornado
*     LIS_CondRetOK  - se encontrou.
*                      O elemento corrente � o primeiro elemento do
*                      elemento corrente inclusive para o fim da lista
*                      e que cont�m o ponteiro procurado
*
*     LIS_CondRetNaoEncontrou - se o ponteiro n�o foi encontrado
*                      O elemento corrente continua o mesmo
*     LIS_CondRetListaVazia   - se a lista estiver vazia
*
*     Assertivas de entrada:
*     - O ponteiro para a lista recebida como par�metro deve ser v�lido
*     - pValor deve poder receber algo gen�rico
*     Assertivas de sa�da:
*     - pValor possui o mesmo valor que o elemento procurado
*
***********************************************************************/

   LIS_tpCondRet LIS_ProcurarValor( LIS_tppLista pLista ,
                                    void * pValor        ) ;
/***********************************************************************
*
*  $FC Fun��o: LIS  &Qtd Elem
*
*  $ED Descri��o da fun��o
*	  Retorna a quantidade de elementos na lsita
*
*  $EP Par�metros
*     pLista  - ponteiro para a lista onde procura
*	  *qtd	  - ponteiro para valor
*
*  $FV Valor retornado
*     LIS_CondRetOK 
*	  LIS_CondRetListaNaoExiste - se pLista == NULL
*
*     Assertivas de entrada:
*     - O ponteiro para a lista recebida como par�metro deve ser v�lido
*     - "qtd" Deve apontar para um espa�o de memoria valido
*     Assertivas de sa�da:
*     - "qtd" Possui o mesmo valor da quantidade de elementos na lista
*
***********************************************************************/
   LIS_tpCondRet LIS_QtdElem(	LIS_tppLista pLista, int *qtd);

#undef LISTA_EXT

/********** Fim do m�dulo de defini��o: LIS  Lista duplamente encadeada **********/

#else
#endif
