#if ! defined( LISTA_ )
#define LISTA_
/***************************************************************************
*
*  $MCD Módulo de definição: LIS  Lista duplamente encadeada
*
*  Arquivo gerado:              LISTA.h
*  Letras identificadoras:      LIS
*
*  Nome da base de software:    Arcabouço para a automação de testes de programas redigidos em C
*  Arquivo da base de software: D:\AUTOTEST\PROJETOS\LISTA.BSW
*
*  Projeto: INF 1301 / 1628 Automatização dos testes de módulos C
*  Gestor:  LES/DI/PUC-Rio
*  Autores: avs, thk , adp, ilg
*
*  $HA Histórico de evolução:
*     Versão  Autor    Data     Observações
*	  5       thk	25/abr/2015 adaptação dos retornos das funções
*     4       avs   01/fev/2006 criar linguagem script simbólica
*     3       avs   08/dez/2004 uniformização dos exemplos
*     2       avs   07/jul/2003 unificação de todos os módulos em um só projeto
*     1       avs   16/abr/2003 início desenvolvimento
*
*  $ED Descrição do módulo
*     Implementa listas genéricas duplamente encadeadas.
*     Podem existir n listas em operação simultaneamente.
*     As listas possuem uma cabeça encapsulando o seu estado.
*
*     Cada lista é homogênea quanto ao tipo dos dados que armazena.
*     Cada elemento da lista referencia o valor que contém.
*
*     Os ponteiros para os dados são copiados para elementos da lista.
*        Não é copiado o valor apontado por estes ponteiros.
*
*     O controle da destruição do valor de um elemento a ser excluído
*        é realizado por uma função fornecida pelo usuário.
*
*     Cada lista referencia uma função que determina como devem ser
*        desalocados os dados nela contidos.
*
*     A função de liberação dos valores contidos nos elementos deve
*        assegurar a liberação de todos os espaços referênciados pelo
*        valor contido em um elemento.
*        Esta função é chamada antes de se desalocar um elemento
*        de uma lista.
*        Caso não seja necessário desalocar o valor referenciado pelo
*        elemento, o ponteiro para a função de liberação poderá ser NULL .
*        Caso o elemento da lista seja a única âncora do valor referenciado,
*        esta função deve promover a destruição (free) desse valor e
*        de todos os dados nele ancorados.
*
***************************************************************************/
 
#if defined( LISTA_OWN )
   #define LISTA_EXT
#else
   #define LISTA_EXT extern
#endif

/***** Declarações exportadas pelo módulo *****/

/* Tipo referência para uma lista */

typedef struct LIS_tagLista * LIS_tppLista ;


/***********************************************************************
*
*  $TC Tipo de dados: LIS Condições de retorno
*
*
*  $ED Descrição do tipo
*     Condições de retorno das funções da lista
*
***********************************************************************/

   typedef enum {

         LIS_CondRetOK ,
               /* Concluiu corretamente */

         LIS_CondRetListaVazia ,
               /* A lista não contém elementos */

         LIS_CondRetFimLista ,
               /* Foi atingido o fim de lista */

         LIS_CondRetNaoAchou ,
               /* Não encontrou o valor procurado */

         LIS_CondRetFaltouMemoria,
               /* Faltou memória ao tentar criar um elemento de lista */

		 LIS_CondRetListaNaoExiste

   } LIS_tpCondRet ;


/***********************************************************************
*
*  $FC Função: LIS  &Criar lista
*
*  $ED Descrição da função
*     Cria uma lista genérica duplamente encadeada.
*     Os possíveis tipos são desconhecidos a priori.
*     A tipagem é implicita.
*     Não existe identificador de tipo associado à lista.
*
*  $EP Parâmetros
*     pLista - endereço de ponteiro para lista onde deve ser criada
*     ExcluirValor  - ponteiro para a função que processa a
*                     exclusão do valor referenciado pelo elemento
*                     a ser excluído.
*                     Ver descrição do módulo.
*
*  $FV Valor retornado
*     Se executou corretamente retorna condRetOK e pLista será o ponteiro da lista criada.
*     Este ponteiro será utilizado pelas funções que manipulem esta lista.
*
*     Se ocorreu algum erro, por exemplo falta de memória ou dados errados,
*     a função retornará CondRetFaltouMemoria.
*
*     Assertivas de entrada:
*     - O endereço de ponteiro para a lista recebida como parâmetro deve ser válido
*     - O ponteiro para a função ExcluirValor deve apontar para a função
*     Assertivas de saída:
*     - O espaço de memória para a lista foi alocado com sucesso
*
*
***********************************************************************/

LIS_tpCondRet LIS_CriarLista( LIS_tppLista *pLista ,void   ( * ExcluirValor ) ( void * pDado ) );


/***********************************************************************
*
*  $FC Função: LIS  &Destruir lista
*
*  $ED Descrição da função
*     Destrói a lista fornecida.
*     O parâmetro ponteiro para a lista não é modificado.
*     Se ocorrer algum erro durante a destruição, a lista resultará
*     estruturalmente incorreta.
*     OBS. não existe previsão para possíveis falhas de execução.
*
*  $FV Valor retornado
*     LIS_CondRetOK    - destruiu sem problemas
*	  LIS_CondRetListaNaoExiste - recebeu lista inexistente
*
*     Assertivas de entrada:
*     - O ponteiro para a lista recebida como parâmetro deve ser válido
*     Assertivas de saída:
*     - O espaço de memória para a lista foi liberado com sucesso
*
***********************************************************************/

   LIS_tpCondRet LIS_DestruirLista( LIS_tppLista pLista ) ;


/***********************************************************************
*
*  $FC Função: LIS  &Esvaziar lista
*
*  $ED Descrição da função
*     Elimina todos os elementos, sem contudo eliminar a lista
*
*  $EP Parâmetros
*     pLista - ponteiro para a lista a ser esvaziada
*
*  $FV Valor retornado
*     LIS_CondRetOK    - esvaziou
*	  LIS_CondRetListaNaoExiste - recebeu lista inexistente
*
*     Assertivas de entrada:
*     - O ponteiro para a lista recebida como parâmetro deve ser válido
*     Assertivas de saída:
*     - O espaço de memória para a lista foi esvaziado (recebido NULL) com sucesso
*
*
***********************************************************************/

	LIS_tpCondRet LIS_EsvaziarLista( LIS_tppLista pLista );


/***********************************************************************
*
*  $FC Função: LIS  &Inserir elemento antes
*
*  $ED Descrição da função
*     Insere novo elemento antes do elemento corrente.
*     Caso a lista esteja vazia, insere o primeiro elemento da lista.
*
*  $EP Parâmetros
*     pLista - ponteiro para a lista onde deve ser inserido o elemento
*     pValor - ponteiro para o valor do novo elemento
*              Pode ser NULL
*
*  $FV Valor retornado
*     LIS_CondRetOK
*     LIS_CondRetFaltouMemoria
*
*     Assertivas de entrada:
*     - O ponteiro para a lista recebida como parâmetro deve ser válido
*     - O valor deve ser genérico
*     Assertivas de saída:
*     - O número de elementos da lista foi acrescentado 1
*     - O ponteiro para o nó corrente passou a apontar para o novo nó
*
***********************************************************************/

   LIS_tpCondRet LIS_InserirElementoAntes( LIS_tppLista pLista ,
                                           void * pValor        ) ;


/***********************************************************************
*
*  $FC Função: LIS  &Inserir elemento após
*
*  $ED Descrição da função
*     Insere novo elemento apás o elemento corrente.
*     Caso a lista esteja vazia, insere o primeiro elemento da lista.
*
*  $EP Parâmetros
*     Parâmetros
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
*     - O ponteiro para a lista recebida como parâmetro deve ser válido
*     - O valor deve ser genérico
*     Assertivas de saída:
*     - O número de elementos da lista foi acrescentado 1
*     - O ponteiro para o nó corrente passou a apontar para o novo nó
*
***********************************************************************/

   LIS_tpCondRet LIS_InserirElementoApos( LIS_tppLista pLista ,
                                          void * pValor        )
       ;


/***********************************************************************
*
*  $FC Função: LIS  &Excluir elemento
*
*  $ED Descrição da função
*     Exclui o elemento corrente da lista dada.
*     Se existir o elemento aa esquerda do corrente será o novo corrente.
*     Se não existir e existir o elemento à direita, este se tornará corrente.
*     Se este também não existir a lista tornou-se vazia.
*
*  $EP Parâmetros
*     pLista    - ponteiro para a lista na qual deve excluir.
*
*  $FV Valor retornado
*     LIS_CondRetOK
*     LIS_CondRetListaVazia
*
*     Assertivas de entrada:
*     - O ponteiro para a lista recebida como parâmetro deve ser válido
*     Assertivas de saída:
*     - O número de elementos da lista foi reduzido
*     - O ponteiro para o nó corrente passou a apontar para o nó seguinte
*
***********************************************************************/

   LIS_tpCondRet LIS_ExcluirElemento( LIS_tppLista pLista ) ;


/***********************************************************************
*
*  $FC Função: LIS  &Obter referência para o valor contido no elemento
*
*  $ED Descrição da função
*     Obtem a referência para o valor contido no elemento corrente da lista
*
*  $EP Parâmetros
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
*     - O ponteiro para a lista recebida como parâmetro deve ser válido
*     - O valor deve poder receber algo genérico
*     Assertivas de saída:
*     - O valor (segundo parâmetro) possui o valor do nó corrente da lista
*
*
***********************************************************************/

      LIS_tpCondRet LIS_ObterValor( LIS_tppLista pLista, void **valor);


/***********************************************************************
*
*  $FC Função: LIS  &Ir para o elemento inicial
*
*  $ED Descrição da função
*     Torna corrente o primeiro elemento da lista.
*     Faz nada se a lista está vazia.
*
*  $EP Parâmetros
*     pLista - ponteiro para a lista a manipular
*
*  $FV Valor retornado
*	LIS_CondRetListaNaoExiste - pLista = NULL
*	LIS_CondRetOK - executou corretamente
*
*
*     Assertivas de entrada:
*     - O ponteiro para a lista recebida como parâmetro deve ser válido
*     Assertivas de saída:
*     - O nó corrente apontado pela pLista aponta para o primeiro nó
*
***********************************************************************/

   LIS_tpCondRet IrInicioLista( LIS_tppLista pLista ) ;


/***********************************************************************
*
*  $FC Função: LIS  &Ir para o elemento final
*
*  $ED Descrição da função
*     Torna corrente o elemento final da lista.
*     Faz nada se a lista está vazia.
*
*  $EP Parâmetros
*     pLista - ponteiro para a lista a manipular
*
*  $FV Valor retornado
*	LIS_CondRetListaNaoExiste - pLista = NULL
*	LIS_CondRetOK - executou corretamente
*
*     Assertivas de entrada:
*     - O ponteiro para a lista recebida como parâmetro deve ser válido
*     Assertivas de saída:
*     - O nó corrente apontado pela pLista aponta para o último nó
*
***********************************************************************/

   LIS_tpCondRet IrFinalLista( LIS_tppLista pLista ) ;


/***********************************************************************
*
*  $FC Função: LIS  &Avançar elemento
*
*  $ED Descrição da função
*     Avança o elemento corrente numElem elementos na lista
*     Se numElem for positivo avança em direção ao final
*     Se numElem for negativo avança em direção ao início
*     numElem pode ser maior do que o númro de elementos existentes na
*               direção desejada
*     Se numElem for zero somente verifica se a lista está vazia
*
*  $EP Parâmetros
*     pLista  - ponteiro para a lista a ser manipulada
*     numElem - o número de elementos a andar
*
*  $FV Valor retornado
*     CondRetOK         - se numElem elementos tiverem sido andados
*     CondRetFimLista   - se encontrou o fim da lista antes de andar numElem
*                         elementos
*     CondRetListaVazia - se a lista está vazia
*
*     Assertivas de entrada:
*     - O ponteiro para a lista recebida como parâmetro deve ser válido
*     - O número de elementos deve ser menor ou igual ao tamanho da lista
*     Assertivas de saída:
*     - O nó corrente aponta para numElem nós após o que apontava antes
*
***********************************************************************/

   LIS_tpCondRet LIS_AvancarElementoCorrente( LIS_tppLista pLista ,
                                              int numElem ) ;


/***********************************************************************
*
*  $FC Função: LIS  &Procurar elemento contendo valor
*
*  $ED Descrição da função
*     Procura o elemento que referencia o valor dado.
*     A função compara ponteiro e não conteúdo apontado.
*
*  $EP Parâmetros
*     pLista  - ponteiro para a lista onde procura
*     pValor  - ponteiro para o valor procurado
*               Pode ser NULL
*
*  $FV Valor retornado
*     LIS_CondRetOK  - se encontrou.
*                      O elemento corrente é o primeiro elemento do
*                      elemento corrente inclusive para o fim da lista
*                      e que contém o ponteiro procurado
*
*     LIS_CondRetNaoEncontrou - se o ponteiro não foi encontrado
*                      O elemento corrente continua o mesmo
*     LIS_CondRetListaVazia   - se a lista estiver vazia
*
*     Assertivas de entrada:
*     - O ponteiro para a lista recebida como parâmetro deve ser válido
*     - pValor deve poder receber algo genérico
*     Assertivas de saída:
*     - pValor possui o mesmo valor que o elemento procurado
*
***********************************************************************/

   LIS_tpCondRet LIS_ProcurarValor( LIS_tppLista pLista ,
                                    void * pValor        ) ;
/***********************************************************************
*
*  $FC Função: LIS  &Qtd Elem
*
*  $ED Descrição da função
*	  Retorna a quantidade de elementos na lsita
*
*  $EP Parâmetros
*     pLista  - ponteiro para a lista onde procura
*	  *qtd	  - ponteiro para valor
*
*  $FV Valor retornado
*     LIS_CondRetOK 
*	  LIS_CondRetListaNaoExiste - se pLista == NULL
*
*     Assertivas de entrada:
*     - O ponteiro para a lista recebida como parâmetro deve ser válido
*     - "qtd" Deve apontar para um espaço de memoria valido
*     Assertivas de saída:
*     - "qtd" Possui o mesmo valor da quantidade de elementos na lista
*
***********************************************************************/
   LIS_tpCondRet LIS_QtdElem(	LIS_tppLista pLista, int *qtd);

#undef LISTA_EXT

/********** Fim do módulo de definição: LIS  Lista duplamente encadeada **********/

#else
#endif
