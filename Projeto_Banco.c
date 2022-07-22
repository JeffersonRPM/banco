#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#define CLI 30

typedef struct
{
    char nome[100];
    int RG;
    char endereco[200];
    int telefone;
    float renda;
    int tipo_cliente;
    union
    {
        int cpf;
        int cnpj;
    } cpf_cnpj;
    int num_cl;
} Cliente;
Cliente cliente[CLI];
char nome[100];
char endereco[200];

int posicao;

typedef struct
{
    int Numero_Conta;
    int Agencia;
    float Saldo_Conta;
    int Tipo_Conta;
    struct Cliente *Titular;
    char pix;

} Dados_Contas;
Dados_Contas contas[CLI];


void pausar()
{
    #ifdef WIN32
    system("pause");
    #else
    system("read -p \"Pressione enter para sair\"");
    #endif
}


void limparTela()
{
    #ifdef WIN32
    system("cls");
    #else
    system("clear");
    #endif
}


void limparEntrada()
{
    #ifdef WIN64
    fflush(stdin);
    #else
    __fpurge(stdin);
    #endif
}


void Add_Cliente(int i)
{
    printf("\n*****NOVO CLIENTE*****\n");

    printf("\nNome: ");
    limparEntrada();
    gets(cliente[i].nome);
    fflush(stdin);

    printf("\nRG: ");
    scanf("%d", &cliente[i].RG);

    printf("\nEndereco: ");
    limparEntrada();
    gets(cliente[i].endereco);
    fflush(stdin);

    printf("\nTelefone: ");
    scanf("%d", &cliente[i].telefone);

    printf("\nRenda: ");
    scanf("%f", &cliente[i].renda);

    printf("\nTipo de Cliente: \n1 - Private\n2 - Alta renda\n3 - Varejo\n");
    scanf("%d", &cliente[i].tipo_cliente);

    printf("\nCPF ou CNPJ: ");
    scanf("%d", &cliente[i].cpf_cnpj);

    cliente[i].num_cl = i;
    printf("\nO numero do cliente eh: %d - NAO PERCA ESSE NUMERO\n\n\n ", i);
}

void Add_Conta(int j, int num)
{
    int id, menu;
    printf("\n*****NOVA CONTA*****\n");
    printf("Digite o numero (identificador) do cliente titular: ");
    scanf("%d", &id);

    if(cliente[id].num_cl==-1)
    {
    limparTela();
    printf("\nEsse cliente nao esta cadastrado!");
    }

    else
    {
    contas[j].Titular = &cliente[id];
    printf("\nNome do Titular: %s", contas[j].Titular);
    printf("\nAgencia: ");
    scanf("%d%*c", &contas[j].Agencia);

    contas[j].Numero_Conta = num;
    printf("\nO sistema definiu o seguinte numero para a conta: %d - (NAO PERCA ESSE NUMERO)", num);
    printf("\n\nSaldo da conta:");
    scanf("%f%*c", &contas[j].Saldo_Conta);

    printf("\nTipo da conta:\n1 - CONTA-CORRENTE\n2 - CONTA POUPANCA\n3 - CONTA-SALARIO\n");
    scanf("%d%*c", &contas[j].Tipo_Conta);

    printf("\nCrie sua chave PIX (CPF ou Telefone): ");
    gets(contas[j].pix);

    }
}

void Imprimir_Conta()
{
    int ct, ag, count = 0;
    printf("\n*****BUSCAR CONTA*****\n");
    printf("\nDigite o numero da conta que voce deseja buscar: ");
    scanf("%d", &ct);
    printf("\nDigite a agencia que essa conta pertence: ");
    scanf("%d", &ag);
    limparTela();
    for (int var = 0; var < 30; var++)
    {
        if (ct == contas[var].Numero_Conta && ag == contas[var].Agencia)
        {
            printf("\n*****DADOS DA CONTA*****\n");
            printf("\nNumero da conta: %d", contas[var].Numero_Conta);
            printf("\nAgencia: %d", contas[var].Agencia);
            printf("\nSaldo: %.2f", contas[var].Saldo_Conta);
            printf("\nTipo de conta: %d", contas[var].Tipo_Conta);
            printf("\nNome do Titular: %s \n", contas[var].Titular);
            printf("\nSua chave PIX eh: %s", contas[var].pix);

            count = count + 1;
        }
    }
    if (count == 0)
    {
        printf("\n*****ERRO*****\n");
        printf("\nNao foi encontrada nenhuma conta com esses dados!");
    }
}

void Imprimir_Cliente()
{
    int n, count = 0;
    printf("\n*****BUSCAR CLIENTE*****\n");
    printf("\nDigite o numero do cliente que voce deseja buscar: ");
    scanf("%d", &n);
    limparTela();
    for (int var = 0; var < 30; var++)
    {
        if (n == cliente[var].num_cl)
        {
            printf("\n*****DADOS DO CLIENTE*****\n");
            printf("\nNome: %s", cliente[var].nome);
            printf("\nRG: %d", cliente[var].RG);
            printf("\nEndereco: %s", cliente[var].endereco);
            printf("\nTelefone: %d", cliente[var].telefone);
            printf("\nRenda: %.2f", cliente[var].renda);
            printf("\nTipo de Cliente: %d", cliente[var].tipo_cliente);
            printf("\nCPF ou CNPJ: %d", cliente[var].cpf_cnpj);
            printf("\nNumero do Cliente: %d", cliente[var].num_cl);
            count = count + 1;
        }
    }
    if (count == 0)
    {
        printf("\n*****ERRO*****\n");
        printf("\nNao foi encontrada nenhuma cadastro com esses dados!");
    }
}

void ListaCliente_Agencia(){
    int ag=0;
    int x=0, count=0;
    printf("\n*****LISTA DE CLIENTES DE UMA AGENCIA*****\n ");
    printf("\nNumero da agencia: ");
    scanf("%d", &ag);
    limparTela();
    printf("\n*****NOME DOS CLIENTES DA AGENCIA*****\n ");
    for(x=0;x<=CLI;x++){
        if(contas[x].Agencia==ag){
            printf("     %s \n", contas[x].Titular);
            count=count+1;
        }
    }
    if (count==0){
        limparTela();
       printf("\nEssa busca nao encontrou nenhum resultado!\n ");
    }
}
void ListaContas_tipo_agencia(){
    int ag=0, tp=0, count=0;
    printf("\n*****LISTA DE CONTAS POR TIPO DE UMA AGENCIA*****\n ");
    printf("\nNumero da agencia: ");
    scanf("%d", &ag);
    printf("\n1 - CONTA-CORRENTE\n2 - CONTA POUPANCA\n3 - CONTA-SALARIO\nTipo de conta: ");
    scanf("%d", &tp);
    limparTela();
    printf("\n*****DADOS DAS CONTAS*****\n");
    for(int x=0;x<=CLI;x++){
        if(contas[x].Agencia==ag && contas[x].Tipo_Conta==tp){
            printf("\nNumero da conta: %d", contas[x].Numero_Conta);
            printf("\nAgencia: %d", contas[x].Agencia);
            printf("\nSaldo: %.2f", contas[x].Saldo_Conta);
            printf("\nTipo de conta: %d", contas[x].Tipo_Conta);
            printf("\nNome do Titular: %s", contas[x].Titular);
            printf("\nSua chave PIX eh: %s", contas[x].pix);
            count=count+1;
        }
    }
    if (count==0){
       limparTela();
       printf("\nEssa busca nao encontrou nenhum resultado!\n ");
    }
}
void Atualizar_Cliente(){
    int n=0, x=8;
    printf("\n*****ATUALIZAR CLIENTE*****\n");
    printf("\nQual o numero do cliente: ");
    scanf("%d", &n);
    limparTela();

    if(cliente[n].num_cl!=-1)
    {

    do{
    printf("\nSelecione uma opcao de atualizacao para o cliente %d ", n);
    printf("\n1 - Nome\n2 - RG\n3 - Endereco\n4 - Renda\n5 - Tipo de Cliente\n6 - Telefone\n7 - TODAS AS INFORMACOES\n0- Retornar ao Menu Principal"
           "\n\n Nao eh permitida a alteracao de CPF e do numero do cliente! \n");
    scanf("%d", &x);
    limparTela();
    switch(x){
        case 1:
            printf("\nNovo nome: ");
            limparEntrada();
            gets(cliente[n].nome); fflush(stdin);
            limparTela();
            printf("\n\nNome atualizado com sucesso!");
            pausar();
            limparTela();
        break;
        case 2:
            printf("\nNovo RG: ");
            scanf("%d", &cliente[n].RG);
            limparTela();
            printf("\n\nRG atualizado com sucesso!");
            pausar();
            limparTela();
        break;
        case 3:
            printf("\nNovo Endereco: ");
            limparEntrada();
            gets(cliente[n].endereco); fflush(stdin);
            limparTela();
            printf("\n\nEndereco atualizado com sucesso!");
            pausar();
            limparTela();
        break;
        case 4:
            printf("\nNova Renda: ");
            scanf("%.2f", &cliente[n].renda);
            limparTela();
            printf("\n\nRenda atualizado com sucesso!");
            pausar();
            limparTela();
        break;
        case 5:
            printf("\nNovo Tipo de Cliente:\n1 - Private\n2 - Alta renda\n3 - varejo\n");
            scanf("%d", &cliente[n].tipo_cliente);
            limparTela();
            printf("\n\nTipo de cliente atualizado com sucesso!");
            pausar();
            limparTela();
        break;
        case 6:
            printf("\nNovo Telefone: ");
            scanf("%d", &cliente[n].telefone);
            limparTela();
            printf("\n\nTelefone atualizado com sucesso!");
            pausar();
            limparTela();
        break;
        case 7:
            printf("\nNome: ");
            limparEntrada();
            gets(cliente[n].nome);
            fflush(stdin);

            printf("\nRG: ");
            scanf("%d", &cliente[n].RG);

            printf("\nEndereco: ");
            limparEntrada();
            gets(cliente[n].endereco);
            fflush(stdin);

            printf("\nTelefone: ");
            scanf("%d", &cliente[n].telefone);

            printf("\nRenda: ");
            scanf("%f", &cliente[n].renda);

            printf("\nTipo de Cliente:\n1 - Private\n2 - Alta renda\n3 - varejo\n");
            scanf("%d", &cliente[n].tipo_cliente);

            limparTela();
            printf("\n\nCadastro de Cliente atualizado com sucesso!\n");
            pausar();
            limparTela();
        break;
    }

    } while(x!=0);

    }
    else
    {
        printf("\n*****ERRO*****\n");
        printf("\nNao foi encontrada nenhuma cadastro com esses dados!");
    }
}

void Atualizar_Conta(){
    int n=0, x=4, id=-1;
    printf("\n*****ATUALIZAR CONTA*****\n");
    printf("\nQual o numero da conta que deseja atualizar? \n ");
    scanf("%d", &n);
    n=n-1000;

    limparTela();
    if(contas[n].Numero_Conta<0)
    {
        printf("\n*****ERRO*****\n");
        printf("\nNao foi encontrada nenhuma cadastro com esses dados!");
    }
    else
    {

    do{
    printf("\n Selecione uma opcao de atualizacao para a conta %d \n", n);
    printf("\n1- Saldo\n2- Titular\n3 - Chave PIX\n4 - Todas as informacoes\n0 - Retornar ao Menu Principal"
           "\n\n Nao eh permitida a alteracao de Agencia, Tipo de conta e do numero da conta! \n");
    scanf("%d", &x);
    limparTela();

    switch(x){
        case 1:
            printf("\nNovo saldo da conta: ");
            scanf("%f%*c", &contas[n].Saldo_Conta);
            limparTela();
            printf("\n\nNovo saldo da Conta atualizado com sucesso!\n");
            pausar();
            limparTela();
        break;
        case 2:
            printf("\nDigite o numero (identificador) do novo titular: ");
            scanf("%d", &id);
            contas[n].Titular = &cliente[id];

            limparTela();
            printf("\n\n Novo titular atualizado com sucesso!\n");
            pausar();
            limparTela();
            break;

        case 3:
            printf("\nDigite a nova chave PIX: ");
            gets(contas[n].pix);

            limparTela();
            printf("\n\nNova chave PIX atualizada com sucesso!\n");
            pausar();
            limparTela();
            break;

        case 4:
            printf("\nNovo saldo da conta: ");
            scanf("%f%*c", &contas[n].Saldo_Conta);
            printf("\nDigite o numero (identificador) do novo titular: ");
            scanf("%d", &id);
            contas[n].Titular = &cliente[id];

            limparTela();
            printf("\n\nNovo titular atualizado com sucesso!\n");
            pausar();
            limparTela();
            break;
    }
    } while(x!=0);
    }
}

void deposito ()
{
    int n=0, x=1;
    float novoDeposito;
    printf("\n\n*****DEPOSITAR*****\n");
    printf("\nQual o numero da conta que deseja efetuar o deposito?\n ");
    scanf("%d", &n);
    n=n-1000;

    limparTela();
    if(contas[n].Numero_Conta<0)
    {
        printf("\n*****ERRO*****\n");
        printf("\nNao foi encontrada nenhuma cadastro com esses dados!");
    }

    else
    {

    do{
    printf("\nDigite o valor que deseja depositar: ");
    scanf("%f", &novoDeposito);
    contas[n].Saldo_Conta += novoDeposito;

    printf("\nDigite '0'(zero) para voltar ao menu: ");
    scanf("%d", &x);

    }while(x!=0);

}
}

void saque (){
    int n=0, x=1;
    float novoSaque;
    printf("\n*****SACAR*****\n");
    printf("\nQual o numero da conta que deseja efetuar o saque? ");
    scanf("%d", &n);
    n=n-1000;

    limparTela();
    if(contas[n].Numero_Conta<0)
    {
        printf("\n*****ERRO*****\n");
        printf("\nNao foi encontrada nenhuma cadastro com esses dados!");
    }
    else
    {
    do{
    printf("\nDigite o valor que deseja sacar: ");
    scanf("%f", &novoSaque);
    contas[n].Saldo_Conta -= novoSaque;

    printf("\nDigite '0'(zero) para voltar ao menu: ");
    scanf("%d", &x);

    }while(x!=0);

}
}

void pix()
{
    int n, x = 1;
    float valorPIX;
    printf("\n*****PIX*****\n");
    printf("\nDigite o numero da sua conta: ");
    scanf("%d", &n);
    n = n - 1000;

    limparTela();
    if (contas[n].Numero_Conta < 0)
    {
        printf("\n*****ERRO*****\n");
        printf("\n Nao foi encontrada nenhuma cadastro com esses dados!");
    }
    else
    {
        do
        {
            printf("\nQual o PIX da conta que deseja fazer a transferencia: ");
            scanf("%s", &contas[n].pix);
            printf("\nDigite o valor que deseja transferir atraves do PIX: ");
            scanf("%f", &valorPIX);

            for (int cliente = 0; cliente <= CLI; cliente++)
            {
                if (contas[cliente].pix == contas[n].pix)
                {
                    contas[n].Saldo_Conta -= valorPIX;
                    contas[cliente].Saldo_Conta += valorPIX;
                    printf("Valor Transferido");
                }
            }
            printf("\nDigite '0'(zero) para voltar ao menu: ");
            scanf("%d", &x);

        } while (x != 0);
    }
}

int i = 0, j = 0, num = 1000;

int main()
{
    printf("Jefferson Roberto Piaia Martines - PC3015602\n\nLeandro Rodini - PC3015637\n\n");
    pausar();
    limparTela();

    int Menu0, Menu1 = 0, Menu2 = 0, Menu3 = 0;

    for (i = 0; i < 30; i++)
    {
        strcpy(cliente[i].nome, "NULL");
        cliente[i].RG = 0;
        strcpy(cliente[i].endereco, "NULL");
        cliente[i].telefone = 0;
        cliente[i].renda = 0.0;
        cliente[i].tipo_cliente = 0;
        cliente[i].cpf_cnpj.cpf = 0;
        cliente[i].num_cl = -1;
    }
    for (i = 0; i < 30; i++)
    {
        contas[i].Numero_Conta = -1;
        contas[i].Agencia = 0;
        contas[i].Saldo_Conta = 0.0;
        contas[i].Tipo_Conta = 0;
    }

    i = 0;
    j = 0;

    do {
        printf("\n*****MENU*****\n\n1 - Cadastrar Dados\n2 - Imprimir Dados\n3 - Atualizar Cadastro\n4 - Deposito\n5 - Saque\n6 - Pix\n0 - Sair \n");
        scanf("%d", &Menu0);
        limparTela();

        switch (Menu0)
        {

        case 1:
            printf("\n*****CADASTRAR*****\n\n1 - Nova Conta\n2 - Novo Cliente\n");
            scanf("%d", &Menu1);
            limparTela();

            if (Menu1 == 1)
            {
                Add_Conta(j, num);
                num=num+1;
            }
            else if (Menu1 == 2)
            {
                Add_Cliente(i);
            }

            else
            {
                printf("\n*****ERRO*****\n\n ");
                pausar();
            }

            if (Menu1 == 2)
            {
                i = i + 1;
                limparTela();
                printf("\nCadastro de Cliente realizado com sucesso!\n ");
                pausar();
                limparTela();
            }
            else if (Menu1 == 1)
            {
                limparTela();
                printf("\nCadastro da conta realizado com sucesso! \n\n ");
                j = j + 1;
                pausar();
                limparTela();
            }

            break;

        case 2:
            printf("\n*****IMPRIMIR*****\n1 - Dados de uma conta\n2 - Dados de um cliente\n3 - Lista de clientes de uma agencia\n"
            "4 - Lista de Contas por tipo de uma agencia \n");
            scanf("%d", &Menu2);
            limparTela();

            if (Menu2 == 1)
            {
                Imprimir_Conta();
            }
            else if (Menu2 == 2)
            {
                Imprimir_Cliente();
            }
            else if (Menu2 == 3)
            {
                ListaCliente_Agencia();
            }
            else if (Menu2 == 4)
            {
                ListaContas_tipo_agencia();
            }
            else
            printf("\n*****ERRO*****\n ");
            pausar();
            limparTela();
            break;


        case 3:
            printf("\nVoce deseja:\n1 - Atualizar dados de um cliente\n2 - Atualizar dados de uma conta\n");
            scanf("%d", &Menu3);
            if (Menu3 == 1)
            {
                Atualizar_Cliente();
            }
            else if (Menu3 == 2)
            {
                Atualizar_Conta();
            }
            else
                printf("\n*****ERRO*****\n");
            pausar();
            limparTela();
            break;

        case 4:
            deposito();
            Imprimir_Conta();
            pausar();
            limparTela();
            break;

        case 5:
            saque();
            Imprimir_Conta();
            pausar();
            limparTela();
            break;

        case 6:
            pix();
            Imprimir_Conta();
            pausar();
            limparTela();
            break;

        }

    } while (Menu0 != 0);

    return 0;

}
