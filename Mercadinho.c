#include <locale.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#define RGSTRS "REGISTROS"

struct Dados
{
    int codigo;
    int codigo2;
    char nome[40];
    char descricao[250];
    char lote[20];
    float valor;
    int unidades;
};

// struct Dados cadastro;
struct Dados dados;
struct Dados dados2;
struct Dados dados3;
// struct Dados agora;
// struct Dados validade;


struct DataEHorario
{
    int dia, mes, ano;
    int horas, minutos, segundos;
};
struct DataEHorario data_e_horario;


struct Validade
{
    int dia, mes, ano;
};
struct Validade validade;


bool verificarData(int dia, int mes, int ano)
{
    if(ano>=1900 && ano<=2200)
    {
        if(dia>0 && dia<=31 && (mes==1 || mes==3 || mes==5 || mes==7 || mes==8 || mes==10 || mes==12))
            return true;
        if(dia>0 && dia<=30 && (mes==4 || mes==6 || mes==9 || mes==11))
            return true;
        if(mes==2 && (dia>0 && dia<=29 && ano%4==0 && (ano%400==0 || ano%100!=0)))
            return true;
        if(mes==2 && (dia>0 && dia<=28))
            return true;
        else
            return false;
    }
    else
        return false;
}

int dataDeValidade(char alternativa)
{
    int dia, mes, ano;

    if((alternativa == 'n') || (alternativa == 'N'))
    {
        validade.dia = 0;
        validade.mes = 0;
        validade.ano = 0;
        return 0;
    }

    else if((alternativa == 's') || (alternativa == 'S'))
    {
        printf("DIGITE A DATA DE VALIDADE:\n");
        scanf("%d %d %d", &dia, &mes, &ano);

        if(verificarData(dia, mes, ano) == true)
        {
            validade.dia = dia;
            validade.mes = mes;
            validade.ano = ano;
        }

        else if((alternativa == 's') || (alternativa == 'S'))
        {
            system("cls");
            printf("DATA INVÁLIDA!\nDIGITE NOVAMENTE.\n\n");
            system("pause");
            system("cls");

            printf("DIGITE A DATA DE VALIDADE:\n");
            scanf("%d %d %d", &dia, &mes, &ano);
            printf("\n");

            if(verificarData(dia, mes, ano) == true)
            {
                validade.dia = dia;
                validade.mes = mes;
                validade.ano = ano;
            }

            else
            {
                system("cls");
                printf("DATA INVÁLIDA!\nDIGITE NOVAMENTE.\n\n");
                system("pause");
                system("cls");
                dataDeValidade(alternativa);
            }
        }
    }

    else
        return 0;

return 0;
}

void obterDataEHorario()
{
    struct tm *local;
    time_t t;
    t = time(NULL);
    local=localtime(&t);

    data_e_horarioano = local -> tm_year+1900;
    data_e_horariomes = local -> tm_mon+1;
    data_e_horariodia = local -> tm_mday;
    data_e_horariohoras = local -> tm_hour;
    data_e_horariominutos = local -> tm_min;
    data_e_horariosegundos = local -> tm_sec;
}

int listar(FILE *arquivo)
{
    if(arquivo == NULL)
    {
        printf("\nNÃO FORAM ENCONTRADOS DADOS NOS REGISTROS.\n\n");
        return 0;
    }

    while(!feof(arquivo))
    {
        fscanf(arquivo, "%d\n", &dados.codigo);
        fflush(stdin);
        fscanf(arquivo, "%d\n", &dados.codigo2);
        fflush(stdin);
        fgets(dados.nome, 40, arquivo);
        fgets(dados.descricao, 250, arquivo);
        fflush(stdin);
        fgets(dados.lote, 20, arquivo);
        fflush(stdin);
        fscanf(arquivo, "%f\n", &dados.valor);
        fflush(stdin);
        fscanf(arquivo, "%d\n", &dados.unidades);
        fflush(stdin);
        fscanf(arquivo, "%d %d %d", &validade.dia, &validade.mes, &validade.ano);
        fflush(stdin);

        if(dados.codigo2 != 0)
            fscanf(arquivo, "%d %d %d %d %d %d\n", &data_e_horariodia, &data_e_horariomes, &data_e_horarioano, &data_e_horariohoras, &data_e_horariominutos, &data_e_horariosegundos);

        else
            fscanf(arquivo, "\n");

        fflush(stdin);

        if(dados.codigo2 == 0)
        {
            printf("CÓDIGO DO PRODUTO:\tEST%d\n", dados.codigo);
        }
        else if(dados.codigo2 != 0)
        {
            printf("CÓDIGO DO PRODUTO:\tEST%d\n", dados.codigo);
            printf("NOTA FISCAL:\t\tVND%d\n", dados.codigo2);
        }

        fflush(stdout);
        printf("NOME:\t\t\t%s", dados.nome);
        printf("DESCRIÇÃO:\t\t%s", dados.descricao);
        printf("LOTE:\t\t\t%s", dados.lote);

        if(dados.codigo2 == 0)
        {
            printf("VALOR UNITÁRIO:\t\tR$%.2f\n", dados.valor);
            printf("UNIDADES DISPONÍVEIS:\t%d\n", dados.unidades);
        }
        else if(dados.codigo2 != 0)
        {
            printf("VALOR TOTAL:\t\tR$%.2f\n", dados.valor);
            printf("UNIDADES VENDIDAS:\t%d\n", dados.unidades);
        }


        if(validade.dia == 0)
        {
            printf("DATA DE VALIDADE:\tNÃO POSSUI.\n");
        }
        else
        {
            printf("DATA DE VALIDADE:\t%02d/%02d/%04d\n", validade.dia, validade.mes, validade.ano);
        }

        if(dados.codigo2 == 0)
        {
            printf("\n\n");
        }
        else if(dados.codigo2 != 0)
        {
            printf("HORARIO DA VENDA:\t%02d:%02d:%02d\n", data_e_horariohoras, data_e_horariominutos, data_e_horariosegundos);
            printf("DATA DA VENDA:\t\t%02d/%02d/%04d\n\n\n", data_e_horariodia, data_e_horariomes, data_e_horarioano);
        }
    }

    fclose(arquivo);
}

int codigoDaVenda()
{
    int codVnd = 8210870;
    FILE *codigoVnd;
    codigoVnd = fopen("CdgoVnd.txt", "r+");

    if(codigoVnd == NULL)
    {
        codigoVnd = fopen("CdgoVnd.txt", "w+");
        fprintf(codigoVnd, "%d", codVnd);
        fclose(codigoVnd);
        return codVnd;
    }

    else
    {
        int codgVnd;
        fscanf(codigoVnd, "%d", &codgVnd);
        codgVnd++;
        codigoVnd = fopen("CdgoVnd.txt", "w+");
        fprintf(codigoVnd, "%d", codgVnd);
        fclose(codigoVnd);
        return codgVnd;
    }
}

int codigoDoEstoque(int *pont)
{
    int codEst = 4210870;
    FILE *codigoEst;
    codigoEst = fopen("CdgoEst.txt", "r+");

    if(codigoEst == NULL)
    {
        codigoEst = fopen("CdgoEst.txt", "w+");
        fprintf(codigoEst, "%d", codEst);
        fclose(codigoEst);
        *pont = codEst;
        return codEst;
    }

    else
    {
        int codgEst;
        fscanf(codigoEst, "%d", &codgEst);
        codgEst++;
        codigoEst = fopen("CdgoEst.txt", "w+");
        fprintf(codigoEst, "%d", codgEst);
        fclose(codigoEst);
        *pont = codgEst;
        return codgEst;
    }
}

void RealocarDadosEstoque()
{
    int a;
    char caractere;

    FILE *origem, *destino;
    destino = fopen("ESTOQUE.txt", "w+");
    origem = fopen("ESTOQUE_3.txt", "r");

   while((caractere = fgetc(origem)) != EOF)
        fputc(caractere, destino);

    fclose(origem);
    fclose(destino);
}

void atualizarEstoque(int unidades, int codigo, int i)
{
    int j;

    FILE *arq, *arq2, *arq3;
    arq = fopen("ESTOQUE_2.txt", "r");
    arq2= fopen("ESTOQUE.txt", "r");
    arq3= fopen("ESTOQUE_3.txt", "w+");

    if(arq != NULL)
    {
        for(j = 0; !feof(arq2); j++)
        {
            fscanf(arq, "%d\n", &dados2.codigo);
            fflush(stdin);
            fgets(dados2.nome, 40, arq);
            fgets(dados2.descricao, 250, arq);
            fflush(stdin);
            fgets(dados2.lote, 20, arq);
            fflush(stdin);
            fscanf(arq, "%f\n", &dados2.valor);
            fflush(stdin);
            fscanf(arq, "%d\n", &dados2.unidades);
            fflush(stdin);
            fscanf(arq, "%d %d %d\n", &dados2.dia, &dados2.mes, &dados2.ano);
            fflush(stdin);

            fscanf(arq2, "%d\n", &dados3.codigo);
            fflush(stdin);
            fgets(dados3.nome, 40, arq2);
            fgets(dados3.descricao, 250, arq2);
            fflush(stdin);
            fgets(dados3.lote, 20, arq2);
            fflush(stdin);
            fscanf(arq2, "%f\n", &dados3.valor);
            fflush(stdin);
            fscanf(arq2, "%d\n", &dados3.unidades);
            fflush(stdin);
            fscanf(arq2, "%d %d %d\n", &validade.dia, &validade.mes, &validade.ano);
            fflush(stdin);

            if(codigo == dados3.codigo)
            {
                fprintf(arq3, "%d\n", dados3.codigo);
                fputs(dados3.nome, arq3);
                fputs(dados3.descricao, arq3);
                fputs(dados3.lote, arq3);
                fprintf(arq3, "%.2f", dados3.valor);
                fprintf(arq3, "\n");
                fprintf(arq3, "%d", dados3.unidades-unidades);
                fprintf(arq3, "\n");
                fprintf(arq3, "%02d %02d %04d", validade.dia, validade.mes, validade.ano);
                fprintf(arq3, "\n");
            }

            else
            {
                fprintf(arq3, "%d\n", dados3.codigo);
                fputs(dados3.nome, arq3);
                fputs(dados3.descricao, arq3);
                fputs(dados3.lote, arq3);
                fprintf(arq3, "%.2f", dados3.valor);
                fprintf(arq3, "\n");
                fprintf(arq3, "%d", dados3.unidades);
                fprintf(arq3, "\n");
                fprintf(arq3, "%02d %02d %04d", validade.dia, validade.mes, validade.ano);
                fprintf(arq3, "\n");
            }
        }
    }

    fclose(arq);
    fclose(arq2);
    fclose(arq3);

    RealocarDadosEstoque();
}

int ProdutoVendido(int codigo_2, int unidades, int dia, int mes, int ano, int i)
{
    int j = 0;

    FILE *arq, *arq2;
    arq = fopen("ESTOQUE_2.txt", "w+");
    arq2 = fopen("ESTOQUE.txt", "r");

    if(arq2 == NULL)
        return 1;

    for(i = 0; !feof(arq2); i++)
    {
        fscanf(arq2, "%d\n", &dados3.codigo);
        fflush(stdin);
        fgets(dados3.nome, 40, arq2);
        fgets(dados3.descricao, 250, arq2);
        fflush(stdin);
        fgets(dados3.lote, 20, arq2);
        fflush(stdin);
        fscanf(arq2, "%f\n", &dados3.valor);
        fflush(stdin);
        fscanf(arq2, "%d\n", &dados3.unidades);
        fflush(stdin);
        fscanf(arq2, "%d %d %d\n", &validade.dia, &validade.mes, &validade.ano);
        fflush(stdin);

        if(codigo_2 == dados3.codigo)
        {
            fprintf(arq, "%d\n", dados3.codigo);
            fputs(dados3.nome, arq);
            fputs(dados3.descricao, arq);
            fputs(dados3.lote, arq);
            fprintf(arq, "%.2f", dados3.valor);
            fprintf(arq, "\n");
            fprintf(arq, "%d", dados3.unidades-unidades);
            fprintf(arq, "\n");
            fprintf(arq, "%02d %02d %04d", validade.dia, validade.mes, validade.ano);
            fprintf(arq, "\n");
            return 1;
        }
    }

    fclose(arq2);
    fclose(arq);

return 0;
}

int LerInfoProduto(int codigo_2)
{
    FILE *estoque;
    estoque = fopen("ESTOQUE.txt", "r");

    int i;

    for(i = 0; !feof(estoque); i++)
    {
        fscanf(estoque, "%d\n", &dados3.codigo);
        fflush(stdin);
        fgets(dados3.nome, 40, estoque);
        fgets(dados3.descricao, 250, estoque);
        fflush(stdin);
        fgets(dados3.lote, 20, estoque);
        fflush(stdin);
        fscanf(estoque, "%f\n", &dados3.valor);
        fflush(stdin);
        fscanf(estoque, "%d\n", &dados3.unidades);
        fflush(stdin);
        fscanf(estoque, "%d %d %d\n", &validade.dia, &validade.mes, &validade.ano);
        fflush(stdin);

        if(dados3.codigo == codigo_2)
            return 1;
    }

return 0;
}

int Vendas()
{
    FILE *estoque, *vendas;
    estoque = fopen("ESTOQUE.txt", "r");

    if(estoque == NULL)
    {
        printf("\nNÃO HÁ PRODUTOS NO ESTOQUE!\n\n");
        return 0;
    }

    fclose(estoque);

    int i = 0, j, codigo_2, unidades, dia, mes, ano;
    char nome[40], descricao[250], lote[20], a, b, c;
    float valor;

    printf("\n\n\t\t\t\t\t[VENDA DE PRODUTOS]\n\n");
    fflush(stdin);
    printf("\nDIGITE O CÓDIGO DO PRODUTO:\nEST");
    fflush(stdin);
    scanf("%d", &codigo_2);
    fflush(stdin);
    LerInfoProduto(codigo_2);

    if(dados3.codigo != codigo_2)
    {
        while(dados3.codigo != codigo_2)
        {
            printf("\nCÓDIGO INVÁLIDO!\nDIGITE O CÓDIGO DO PRODUTO:\nEST");
            scanf("%d", &codigo_2);
            fflush(stdin);
            LerInfoProduto(codigo_2);
        }
    }

    if(dados3.codigo == codigo_2)
    {
        printf("\nINFORMAÇÕES SOBRE O PRODUTO:\n\n", dados3.codigo);
        fflush(stdin);
        printf("NOME:\t\t\t%s", dados3.nome);
        fflush(stdin);
        printf("DESCRIÇÃO:\t\t%s", dados3.descricao);
        fflush(stdin);
        printf("LOTE:\t\t\t%s", dados3.lote);
        fflush(stdin);
        printf("VALOR:\t\t\tR$%.2f\n", dados3.valor);
        fflush(stdin);
        printf("UNIDADES DISPONÍVEIS:\t%d\n", dados3.unidades);
        fflush(stdin);

        if(validade.dia == 0)
        {
            printf("DATA DE VALIDADE:\tNÃO POSSUI.\n");
            fflush(stdin);
        }
        else
        {
            printf("DATA DE VALIDADE:\t%02d/%02d/%04d\n\n",
                            validade.dia, validade.mes, validade.ano);
            fflush(stdin);
        }
    }

    printf("\nQUANTAS UNIDADES SERÃO VENDIDAS?\n");
    scanf("%d", &unidades);
    fflush(stdin);
    while(unidades <= 0 || unidades > dados3.unidades)
    {
        printf("\nQUANTIDADE INVÁLIDA!\nINSIRA A QUANTIDADE:\n");
        scanf("%d", &unidades);
        fflush(stdin);
    }

    ProdutoVendido(codigo_2, unidades, dia, mes, ano, i);
    printf("\nVALOR TOTAL: R$%.2f\n\n", dados3.valor * unidades);

    vendas = fopen("HISTORICO_VENDAS.txt", "a+");

    fprintf(vendas, "%d\n", dados3.codigo);
    fprintf(vendas, "%d\n", codigoDaVenda());
    fputs(dados3.nome, vendas);
    fputs(dados3.descricao, vendas);
    fputs(dados3.lote, vendas);
    fprintf(vendas, "%.2f\n", dados3.valor*unidades);
    fprintf(vendas, "%d\n", unidades);
    obterDataEHorario();
    fprintf(vendas, "%02d %02d %04d\n", validade.dia, validade.mes, validade.ano);
    fprintf(vendas, "%02d %02d %04d %02d %02d %02d\n", data_e_horariodia, data_e_horariomes, data_e_horarioano, data_e_horariohoras, data_e_horariominutos, data_e_horariosegundos);
    fclose(vendas);
    atualizarEstoque(unidades, codigo_2, i);
}

struct Cadastro
{
    int codigo;
    char nome[40];
    char descricao[250];
    char lote[20];
    float valor;
};
struct Cadastro cadastro;


void cadastro()
{
    FILE *cadastro, *lote;

    printf("\n\n\t\t\t\t\t[CADASTRO DE PRODUTO]\n\n");
    fflush(stdin);

    printf("\nINSIRA O NOME DO PRODUTO:\n");
    gets(cadastro.nome);
    fflush(stdin);
    while(strlen(cadastro.nome) == 0)
    {
        printf("O NOME DO PRODUTO NÃO FOI INSERIDO!\nINSIRA O NOME:\n");
        gets(cadastro.nome);
        fflush(stdin);
    }

    printf("\nINSIRA A DESCRIÇÃO DO PRODUTO:\n");
    gets(cadastro.descricao);
    fflush(stdin);
    while(strlen(cadastro.descricao) == 0) {
        printf("A DESCRIÇÃO DO PRODUTO NÃO FOI INSERIDA!\nINSIRA A DESCRIÇÃO:\n");
        gets(cadastro.descricao);
        fflush(stdin);
    }

    printf("\nINSIRA O LOTE DO PRODUTO:\n");
    gets(cadastro.lote);
    fflush(stdin);
    while(strlen(cadastro.lote) == 0)
    {
        printf("O LOTE DO PRODUTO NÃO FOI INSERIDO!\nINSIRA O LOTE:\n");
        gets(cadastro.lote);
        fflush(stdin);
    }

    printf("\nINSIRA O VALOR UNITÁRIO DE VENDA DO PRODUTO:\n");
    scanf("%f", &cadastro.valor);
    fflush(stdin);
    while(cadastro.valor <= 0)
    {
        printf("\nO VALOR INSERIDO É INVÁLIDO!\nINSERIDO O VALOR:\n");
        scanf("%f", &cadastro.valor);
        fflush(stdin);
    }

    codigoDoEstoque(&cadastro.codigo);
    cadastro = fopen("ESTOQUE.txt", "a+");
    fprintf(cadastro, "%d\n", cadastro.codigo);
    fputs(cadastro.nome, cadastro);
    fprintf(cadastro, "\n");
    fputs(cadastro.descricao, cadastro);
    fprintf(cadastro, "\n");
    fputs(cadastro.lote, cadastro);
    fprintf(cadastro, "\n");
    fprintf(cadastro, "%.2f\n", cadastro.valor);

    fclose(cadastro);
    printf("\nO PRODUTO FOI CADASTRADO COM SUCESSO!\n");
    printf("O CÓDIGO DO PRODUTO É: EST%d.\n\n", cadastro.codigo);
}


int comandos(int opcao)
{
    switch(opcao)
   {
        FILE *arquivo;

        case 1:
                system("cls");
                cadastro();
                system("pause");
                system("cls");
                break;
        case 2:
                system("cls");
                printf("");
                break;
        case 3:
                system("cls");
                printf("");
                break;
        case 4:
                system("cls");
                Vendas();
                system("pause");
                system("cls");
                printf("");
                break;
        case 5:
                system("cls");
                arquivo = fopen("HISTORICO_VENDAS.txt", "r");
                listar(arquivo);
                system("pause");
                system("cls");
                break;
        case 6:
                system("cls");
                dados.codigo2 = 0;
                arquivo = fopen("ESTOQUE.txt", "r");
                listar(arquivo);
                system("pause");
                system("cls");
                break;
        case 7:
                system("cls");
                printf("");
                break;
        case 8:
                system("cls");
                printf("");
                break;
        case 0:
                system("cls");
                printf("\nEncerrando...\n");
                exit(0);
        default:
                system("cls");
                printf("\nOpção inválida.\n\n");
                system("pause");
                system("cls");
                break;
    }
}

void menu()
{
    printf("\n\n");
    printf("\t\t\t  ########################################################  \n");
    printf("\t\t\t  #\t\t\t\t\t\t\t #\n");
    printf("\t\t\t  #\t\t\t  PRODUTOS\t\t         #\n");
    printf("\t\t\t  #\t\t\t\t\t\t\t #\n");
    printf("\t\t\t  ########################################################  \n");
    printf("\t\t\t  #\t\t\t\t\t\t\t #\n");
    printf("\t\t\t  #\t\t\t1 - Cadastrar\t\t\t #\n");
    printf("\t\t\t  #\t\t\t2 - Excluir\t\t\t #\n");
    printf("\t\t\t  #\t\t\t\t\t\t\t #\n");
    printf("\t\t\t  ########################################################  \n");
    printf("\t\t\t  #\t\t\t\t\t\t\t #\n");
    printf("\t\t\t  #\t\t      COMPRAS E VENDAS\t\t\t #\n");
    printf("\t\t\t  #\t\t\t\t\t\t\t #\n");
    printf("\t\t\t  ########################################################  \n");
    printf("\t\t\t  #\t\t\t\t\t\t\t #\n");
    printf("\t\t\t  #\t\t   3 - Comprar\t\t\t\t #\n");
    printf("\t\t\t  #\t\t   4 - Vender\t\t\t\t #\n");
    printf("\t\t\t  #\t\t   5 - Histórico de vendas\t\t #\n");
    printf("\t\t\t  #\t\t\t\t\t\t\t #\n");
    printf("\t\t\t  ########################################################  \n");
    printf("\t\t\t  #\t\t\t\t\t\t\t #\n");
    printf("\t\t\t  #\t\t\t  ESTOQUE\t\t\t #\n");
    printf("\t\t\t  #\t\t\t\t\t\t\t #\n");
    printf("\t\t\t  ########################################################  \n");
    printf("\t\t\t  #\t\t\t\t\t\t\t #\n");
    printf("\t\t\t  #\t\t\t6 - Exibir\t\t\t #\n");
    printf("\t\t\t  #\t\t\t7 - Aumentar\t\t\t #\n");
    printf("\t\t\t  #\t\t\t8 - Reduzir\t\t\t #\n");
    printf("\t\t\t  #\t\t\t\t\t\t\t #\n");
    printf("\t\t\t  ########################################################  \n");
    printf("\t\t\t  #\t\t\t\t\t\t\t #\n");
    printf("\t\t\t  #\t\t\t  PROGRAMA\t\t\t #\n");
    printf("\t\t\t  #\t\t\t\t\t\t\t #\n");
    printf("\t\t\t  ########################################################  \n");
    printf("\t\t\t  #\t\t\t\t\t\t\t #\n");
    printf("\t\t\t  #\t\t\t0 - Encerrar\t\t\t #\n");
    printf("\t\t\t  #\t\t\t\t\t\t\t #\n");
    printf("\t\t\t  ########################################################  \n\n\n");
}

void main()
{
    mkdir(RGSTRS);
    chdir(RGSTRS);
    system("cls");
    system("MODE con cols=109 lines=44");
    setlocale(LC_ALL, "Portuguese");

    int repetir, opcao, cont;

    while(repetir)
    {
        menu();
        printf("DIGITE A OPÇÃO DESEJADA: ");
        scanf("%d", &opcao);
        system("cls");
        comandos(opcao);
    }
}
