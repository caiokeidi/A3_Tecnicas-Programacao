#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>

void opcao(), cadastroClientes(), removerCliente(), virarMes(), listarClientes(), gastosCliente(), organizar(), adc_gastos(), remover();

typedef struct{
    char nome[30];
    int ano_nascimento[5];
    float gastos;
} CLIENTE;

typedef struct{
    CLIENTE *pcliente;
} LISTA;

LISTA listaClientes;

int n_clientes = 0, max_clientes = 1;


void menu(){

    int op = 0;

    while(op != 7){

        op = 0;
        while(op < 1 || op > 7){
            printf("\n////CADASTRO DE CLIENTES////");
            printf("\n[ 1 ] Cadastrar novo cliente");
            printf("\n[ 2 ] Remover cliente");
            printf("\n[ 3 ] Adicionar gastos do cliente");
            printf("\n[ 4 ] Listar clientes (por melhor comprador)");
            printf("\n[ 5 ] Virar o mês (Zerar compras)");
            printf("\n[ 6 ] Ver gastos de cliente");
            printf("\n[ 7 ] Sair");
            printf("\n////////////////////////////");
            printf("\nOpção Escolhida: ");
            fflush(stdin);
            scanf("%d", &op);

            opcao(op);
        }

    }

}

void opcao(int op_escolhida){
    switch(op_escolhida)
    {
        case 1:
            cadastroClientes();
            break;

        case 2:
            removerCliente();
            break;

        case 3:
            adc_gastos();
            break;

        case 4:
            listarClientes();
            break;

        case 5:
            virarMes();
            break;

        case 6:
            gastosCliente();
            break;

        case 7:
            printf("\nObrigado por usar nosso programa!\n");
            break;
    }
}

void swap(int element1, int element2){
    CLIENTE temporario = listaClientes.pcliente[element1];
    listaClientes.pcliente[element1] = listaClientes.pcliente[element2];
    listaClientes.pcliente[element2] = temporario;
}


void cadastroClientes(){
    if(n_clientes >= max_clientes){
        max_clientes += 10;
        listaClientes.pcliente = (CLIENTE *)realloc(listaClientes.pcliente, max_clientes * sizeof(CLIENTE));
    }

    CLIENTE novo;

    printf("\nNOVO CLIENTE:\n");
    printf("Nome: ");
    scanf("%s", novo.nome);
    printf("Ano de Nascimento: ");
    scanf("%d", novo.ano_nascimento);
    printf("Gastos realizados: ");
    scanf("%f", &novo.gastos);

    listaClientes.pcliente[n_clientes] = novo;

    n_clientes++;
    organizar();
}

void removerCliente(){
    char cliente_solicitado[30];
    int i, qtd = 0;

    printf("\nRemover Cliente:");
    printf("\nCliente: ");
    fflush(stdin);
    scanf("%s", cliente_solicitado);

    for(i = 0; i < n_clientes; i++){
        int check;

        check = strcmp(listaClientes.pcliente[i].nome, cliente_solicitado);
        if(check == 0){
            qtd++;
            remover(i);
            printf("Cliente removido com sucesso!");
        }
    }
    if(qtd == 0){
        printf("\nNão foram encontrados clientes com esse nome!");
    }
}

void remover(int index){
    int i;

    for(i = index; i < n_clientes; i++){
        memcpy(&listaClientes.pcliente[i], &listaClientes.pcliente[i+1], sizeof(CLIENTE));
    }
    n_clientes--;
}

void gastosCliente(){
    if(n_clientes <= 0){
        printf("\nSem Clientes cadastrados!\n");
    }
    else{
        int i;
        char nome_selecionado[30];
        printf("\nNome do cliente: ");
        fflush(stdin);
        scanf("%s", nome_selecionado);

        for(i = 0; i < n_clientes; i++){
            int check;

            check = strcmp(listaClientes.pcliente[i].nome, nome_selecionado);
            if(check == 0){
                printf("\nGastos do cliente %s:  R$%3.2f\n",
                       listaClientes.pcliente[i].nome,
                       listaClientes.pcliente[i].gastos);
            }
        }
    }
}

void listarClientes(){
    organizar();

    int i = 0;
    if(n_clientes <= 0){
        printf("\nSem Clientes cadastrados!\n");
    }
    else{
        printf("\nCLIENTES CADASTRADOS (Por Gastos):");
        for(i = 0; i < n_clientes; i++){
            printf("\nNome: %s --- Ano de Nascimento: %d --- Gastos: R$%3.2f",
                   listaClientes.pcliente[i].nome,
                   *listaClientes.pcliente[i].ano_nascimento,
                   listaClientes.pcliente[i].gastos);
        }
        printf("\n");
    }
}

void adc_gastos(){
    char cliente_solicitado[30];
    int i, qtd = 0;
    float valor = 0;

    printf("\nAdicionar Gastos de Clientes:");
    printf("\nCliente: ");
    scanf("%s", cliente_solicitado);

    for(i = 0; i < n_clientes; i++){
        int check;

        check = strcmp(listaClientes.pcliente[i].nome, cliente_solicitado);
        if(check == 0){
            qtd++;
            printf("\nValor a ser adicionado: ");
            fflush(stdin);
            scanf("%f", &valor);
            listaClientes.pcliente[i].gastos += valor;
            printf("\nValor adicionado");
        }
    }

    if(qtd == 0){
        printf("\nNão foram encontrados clientes com esse nome!");
    }
}

void virarMes(){
    int i = 0;
    printf("\nMês virado - Gastos dos clientes zerados.\n");
    for(i = 0; i < n_clientes; i++){
        listaClientes.pcliente[i].gastos = 0;
    }
}

void organizar(){
    //Checa a ordem dos itens,para ver se estão ordenados pelos valores.
    int i = 0, k = 0;

    for(i = 0; i < n_clientes; i++){
        for(k = 0; k < i; k++){
            if(listaClientes.pcliente[i].gastos > listaClientes.pcliente[k].gastos){
                swap(i, k);
            }
        }
    }
}



int main()
{
    setlocale(LC_ALL, "Portuguese");
    listaClientes.pcliente = (CLIENTE *)malloc(max_clientes * sizeof(CLIENTE));
    menu();

    return 0;
}

