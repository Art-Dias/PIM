//o arquivo interface.c, ficam as telas, onde o usuário poderá ver as opções do que ele pode interagir
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "interface.h"
#include "structs.h"
#include "funcoes.h"
#include "estilos.h"

// matriz global
char matrizItens[100][3][20];
int tamanho_carrinho = 0;
//#include "C:\Users\Arthur Dias\Desktop\Nova pasta\PIM\funcoes.c"

void telaTamanho()
{
    system("MODE con cols=168 lines=60");// configura a quantidad de colunas e linhas que o console terá;
}

void telaLimpa()
{
    system("cls");// limpa a tela;
}

void telaPause()
{
    system("pause > NULL");// pausa a tela sem mostrar o texto padrão da função;
}

void telaEstilo()
{
    system("color F0");// define a cor "f" verde para o fundo e a cor "0" preto para o texto
}

void telaInicio()
{

    system("title Início");

    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO consoleInfo;
    WORD saved_attributes;

    /* Salvar estado atual */
    GetConsoleScreenBufferInfo(hConsole, &consoleInfo);
    saved_attributes = consoleInfo.wAttributes;

    SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN | BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_INTENSITY | BACKGROUND_RED);
    animacao_de_carregamento();
    SetConsoleTextAttribute(hConsole, saved_attributes);

    telaLimpa();

    printf("\n\n\n\n\n\n\n\n\n\n\n\n"
           "                                                    ");
    SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN | BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_INTENSITY | BACKGROUND_RED);
    bold(1);
    animacao_de_aparecimento("HORTIFRUT FRESH\n\n");
    bold(0);
    SetConsoleTextAttribute(hConsole, saved_attributes);
    printf("\n                                           Pressione Enter para continuar...");


    telaPause();
    telaLimpa();
    telaLogin();
}

void telaLogin()
{

    system("title Login");

    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO consoleInfo;
    WORD saved_attributes;

    /* Salvar estado atual */
    GetConsoleScreenBufferInfo(hConsole, &consoleInfo);
    saved_attributes = consoleInfo.wAttributes;

    char usuario[TAM_user], ent_senha, senha[TAM_user];
    int comparador;

    do
    {
        printf("\n\n\n\n\n\n\n"
               "\n                                         ");
        SetConsoleTextAttribute(hConsole, BACKGROUND_BLUE | BACKGROUND_INTENSITY);
        printf(                                            "                                      ");
        SetConsoleTextAttribute(hConsole, saved_attributes);
        printf(                                                                                   "                                         \n"
                "                                         ");
        SetConsoleTextAttribute(hConsole, FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_INTENSITY | FOREGROUND_RED | BACKGROUND_BLUE | BACKGROUND_INTENSITY);
        bold(1);
        printf(                                            "                Login                 ");
        bold(0);
        SetConsoleTextAttribute(hConsole, saved_attributes);
        printf(                                                                                   "                                         \n"
                "                                         ");
        SetConsoleTextAttribute(hConsole, BACKGROUND_BLUE | BACKGROUND_INTENSITY);
        printf(                                            "                                      ");
        SetConsoleTextAttribute(hConsole, saved_attributes);
        printf(                                                                                   "                                         \n\n"
                "\n                                                ");
        SetConsoleTextAttribute(hConsole, FOREGROUND_BLUE| FOREGROUND_GREEN | FOREGROUND_INTENSITY| FOREGROUND_RED | BACKGROUND_INTENSITY);
        printf(                                                " Usuário: ");
        SetConsoleTextAttribute(hConsole, saved_attributes);
        printf(" ");

        gets(usuario);
        fflush(stdin);

        printf("\n                                                ");
        SetConsoleTextAttribute(hConsole, FOREGROUND_BLUE| FOREGROUND_GREEN | FOREGROUND_INTENSITY| FOREGROUND_RED | BACKGROUND_INTENSITY);
        printf(                                                " Senha: ");
        SetConsoleTextAttribute(hConsole, saved_attributes);
        printf(" ");

        mascSenha(ent_senha, &senha);
        fflush(stdin);

        verificaLogin(usuario, senha, &comparador);

        if(comparador == 1)
        {
            bold(1);
            printf(RED "\n\n\t\t\t\t\t\t  [!] Login incorreto!\n"
                   "\t\t\t\t\t   Usuário ou senha estão incorretos!\a");
            bold(0);
            SetConsoleTextAttribute(hConsole, saved_attributes);
            Sleep(800);
            telaLimpa();
        }
        else
        {
            telaLimpa();
            telaMenuAdmin();
            break;
        }

    }
    while(comparador == 1);
}

void telaMenuAdmin()
{

    system("title Menu Administrador");

    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO consoleInfo;
    WORD saved_attributes;

    /* Salvar estado atual */
    GetConsoleScreenBufferInfo(hConsole, &consoleInfo);
    saved_attributes = consoleInfo.wAttributes;

    char escolha;

    //do{
    while (escolha == NULL)
    {
        printf("\n\n\n\n\n\n\n"
               "\n                                          ");
        SetConsoleTextAttribute(hConsole, BACKGROUND_BLUE | BACKGROUND_GREEN);
        printf(                                            "                                 ");
        SetConsoleTextAttribute(hConsole, saved_attributes);
        printf(                                                                              "                                            \n"
                "                                          ");
        SetConsoleTextAttribute(hConsole, FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_INTENSITY | FOREGROUND_RED | BACKGROUND_BLUE | BACKGROUND_GREEN);
        printf(                                            "              MENU               ");
        SetConsoleTextAttribute(hConsole, saved_attributes);
        printf(                                                                              "                                            \n"
                "                                          ");
        SetConsoleTextAttribute(hConsole, BACKGROUND_BLUE | BACKGROUND_GREEN);
        printf(                                            "                                 ");
        SetConsoleTextAttribute(hConsole, saved_attributes);
        printf(                                                                              "                                            \n"
                "                                          |                               |                                             \n"
                "                                          |   [1] - Tela do Gerente       |                                             \n"
                "                                          |   [2] - Tela do Funcionário   |                                             \n"
                "                                          |   [0] - Sair                  |                                             \n"
                "                                          |                               |                                             \n"
                "                                          #===============================#                                             \n"
                "\n                                         Escolha uma opção para continuar: ");

        scanf("%c", &escolha);

        switch(escolha)
        {
        case '1':
            telaLimpa();
            telaGerente();
            break;
        case '2':
            telaLimpa();
            telaFuncionario();
            break;
        case '0':
            telaLimpa();
            SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN | BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_INTENSITY | BACKGROUND_RED);
            animacao_de_saida();
            SetConsoleTextAttribute(hConsole, saved_attributes);

            telaLimpa();
            telaSaida();
            break;
        default :
            printf("\n\n\t\t\t\t\t\t [!} Opção Inválida!");
            Sleep(800);
            //escolha='3';
            printf("%c", escolha);
        }
        telaLimpa();
        //}
    }
    while(escolha != '3');
    //telaLimpa();
}

void telaGerente()
{

    system("title Menu Gerencia");

    int escolha;
    int contador;

    contador = 0;


    printf("\n\n\n\n\n\n\n"
           "\n                                          #===============================#                                             \n"
           "                                          |             MENU              |                                             \n"
           "                                          #===============================#                                             \n"
           "                                          |                               |                                             \n"
           "                                          |   [1] - Cadastros             |                                             \n"
           "                                          |   [2] - Pedidos               |                                             \n"
           "                                          |   [3] - Estoque               |                                             \n"
           "                                          |   [4] - Minhas Informações    |                                             \n"
           "                                          |   [0] - Sair                  |                                             \n"
           "                                          |                               |                                             \n"
           "                                          #===============================#                                             \n"
           "\n                                         Escolha uma opção para continuar: ");
    scanf("%d", &escolha);
    printf("\n%d, valor escolhido\n", escolha);

    switch(escolha)
    {
    case 1:
        contador++;
        telaLimpa();
        telaCadastro();
        break;
    case 2:
        telaLimpa();
        telaPedido();

        break;
    case 3:
        telaLimpa();
        telaEstoque();

    default :
        printf("\n\n\t\t\t\t\t\t [!} Opção Inválida!");
        Sleep(800);
    }
    telaLimpa();
}

void telaFuncionario()
{

    system("title Menu Funcionário");

    int escolha;

    do
    {
        printf("\n\n\n\n\n\n\n"
               "\n                                          #===============================#                                             \n"
               "                                          |             MENU              |                                             \n"
               "                                          #===============================#                                             \n"
               "                                          |                               |                                             \n"
               "                                          |   [1] - Pedidos               |                                             \n"
               "                                          |   [2] - Estoque               |                                             \n"
               "                                          |   [3] - Minhas Informações    |                                             \n"
               "                                          |   [0] - Sair                  |                                             \n"
               "                                          |                               |                                             \n"
               "                                          #===============================#                                             \n"
               "\n                                         Escolha uma opção para continuar: ");
        scanf("%d", &escolha);

        switch(escolha)
        {
        case 1:
            telaLimpa();

            break;
        case 2:
            telaLimpa();

            break;
        default :
            printf("\n\n\t\t\t\t\t\t [!} Opção Inválida!");
            Sleep(800);
        }
        telaLimpa();
    }
    while(escolha != 0);
    telaLimpa();
}

void telaSaida()
{
    system("title Menu");

    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO consoleInfo;
    WORD saved_attributes;

    /* Salvar estado atual */
    GetConsoleScreenBufferInfo(hConsole, &consoleInfo);
    saved_attributes = consoleInfo.wAttributes;

    int escolha;

    do
    {
        printf("\n\n\n\n\n\n\n\n\n"
               "\n                                        ");
        SetConsoleTextAttribute(hConsole, BACKGROUND_BLUE | BACKGROUND_GREEN);
        printf(                                           "                                    ");
        SetConsoleTextAttribute(hConsole, saved_attributes);
        printf(                                                                                "                                        \n"
                "                                        ");
        SetConsoleTextAttribute(hConsole, FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_INTENSITY | FOREGROUND_RED | BACKGROUND_BLUE | BACKGROUND_GREEN);
        printf(                                           "                MENU                ");
        SetConsoleTextAttribute(hConsole, saved_attributes);
        printf(                                                                                "                                        \n"
                "                                        ");
        SetConsoleTextAttribute(hConsole, BACKGROUND_BLUE | BACKGROUND_GREEN);
        printf(                                           "                                    ");
        SetConsoleTextAttribute(hConsole, saved_attributes);
        printf(                                                                                "                                        \n"
                "                                        ");
        SetConsoleTextAttribute(hConsole, FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_INTENSITY | FOREGROUND_RED | BACKGROUND_INTENSITY);
        printf(                                           "                                    ");
        SetConsoleTextAttribute(hConsole, saved_attributes);
        printf(                                                                                "                                        \n"
                "                                        ");
        SetConsoleTextAttribute(hConsole, FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_INTENSITY | FOREGROUND_RED | BACKGROUND_INTENSITY);
        printf(                                           "      [1] - Voltar ao Início        ");
        SetConsoleTextAttribute(hConsole, saved_attributes);
        printf(                                                                                "                                        \n"
                "                                        ");
        SetConsoleTextAttribute(hConsole, FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_INTENSITY | FOREGROUND_RED | BACKGROUND_INTENSITY);
        printf(                                           "      [2] - Login                   ");
        SetConsoleTextAttribute(hConsole, saved_attributes);
        printf(                                                                                "                                        \n"
                "                                        ");
        SetConsoleTextAttribute(hConsole, FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_INTENSITY | FOREGROUND_RED | BACKGROUND_INTENSITY);
        printf(                                           "      [0] - Encerrar Programa       ");
        SetConsoleTextAttribute(hConsole, saved_attributes);
        printf(                                                                                "                                        \n"
                "                                        ");
        SetConsoleTextAttribute(hConsole, FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_INTENSITY | FOREGROUND_RED | BACKGROUND_INTENSITY);
        printf(                                           "                                    ");
        SetConsoleTextAttribute(hConsole, saved_attributes);
        printf(                                                                                "                                        \n"
                "                                        ");
        SetConsoleTextAttribute(hConsole, FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_INTENSITY | FOREGROUND_RED | BACKGROUND_INTENSITY);
        printf(                                           "                                    ");
        SetConsoleTextAttribute(hConsole, saved_attributes);
        printf(                                                                                "                                        \n"
                "                                        ");
        SetConsoleTextAttribute(hConsole, FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_INTENSITY | FOREGROUND_RED | BACKGROUND_BLUE | BACKGROUND_GREEN);
        printf(                                           " Escolha uma opção para continuar: ");

        scanf("%d", &escolha);
        SetConsoleTextAttribute(hConsole, saved_attributes);

        switch(escolha)
        {
        case 1:
            telaLimpa();
            telaInicio();
            break;
        case 2:
            telaLimpa();
            telaLogin();
            break;
        case 0:
            telaLimpa();
            break;
        default :
            printf("\n\n\t\t\t\t\t\t [!} Opção Inválida!");
            Sleep(800);
        }
        telaLimpa();
    }
    while(escolha != 0);
    telaLimpa();
}

// Struct item
struct Item
{
    char nome[50];
    float preco;
    float quantidade;
};

void salvarItensMatrizFor(int linha, char nome[20], char preco[15], char quantidade[15])
{
    int coluna;
    char nome_temp[20], preco_temp[15], quantidade_temp[15];
    //printf("\nfunc chamada %d\n", linha);

    // string copy para fazer variavel receber o valor da string
    strcpy(nome_temp, nome);
    strcpy(preco_temp, preco);
    strcpy(quantidade_temp, quantidade);
    //char *matrizItens[100][3];
    for(coluna=0; coluna<3; coluna++)
    {
        if (coluna == 0)
        {
            //printf("%s", nome_temp);
            strcpy(matrizItens[linha][coluna], nome_temp);
        }
        else if (coluna == 1)
        {
            strcpy(matrizItens[linha][coluna], preco_temp);
        }
        else
        {
            strcpy(matrizItens[linha][coluna], quantidade_temp);
        }
    }
}

void salvarItensMatriz()
{
    //char *matrizItens[][];
    FILE *file;
    char nome[50];
    float preco, quantidade;
    int i, j, total_itens;
    char string_preco[15], string_quant[15];

    // Abrindo aruqivo em modo leitura "r"
    file = fopen("items.txt", "r");
    if (file == NULL)
    {
        perror("Erro");
        return 1;  // Se arquivo não abrir return
    }

    total_itens = 0;
    // Le cada linha do arquivo e da
    while (fscanf(file, "%49s %.2f %.2f", nome, &preco, &quantidade) == 3)
    {
        // convertendo float para char
        snprintf(string_preco, sizeof(string_preco), "%f", preco);
        snprintf(string_quant, sizeof(string_quant), "%f", quantidade);

        salvarItensMatrizFor(total_itens, nome, string_preco, string_quant);
        total_itens++;
    }

    //printf("\n%d\n", total_itens);
    /**
    for(i=0; i<total_itens; i++)
    {
        for(j=0; j<3; j++)
        {
            printf("%s  ", matrizItens[i][j]);
            if (j == 2)
            {
                printf("\n");
            }
        }
    }
     */

    telaPause();
    telaLimpa();
    telaGerente();
}

// 'Item' é a struct 'item' é meio que o apelido, é a meneira que navegarei na struct
void salvarItemArquivo(struct Item item)
{
    // Aqui estou abrindo o arquivo || "a" é para abrir o arquivo em modo de adicionar info ao final
    FILE *file = fopen("items.txt", "a");

    // Checando se arquivo abriu
    if (file == NULL)
    {
        printf("Erro ao abrir arquivo!\n");
        telaPause();
        telaLimpa();
        telaGerente();
    }
    // fprintf para escrever a variavel no arquivo
    fprintf(file, "%s %.2f %.2f\n", item.nome, item.preco, item.quantidade);
    fclose(file);
}

// Cadastro de item
void telaCadastro()
{
    system("title Cadastro Item");

    struct Item item;
    char continuar = 's';

    while (continuar == 's' || continuar == 'S')
    {
        // Entrada do item
        printf("Nome item: ");
        scanf("%s", item.nome);
        printf("Preço item: ");
        scanf("%f", &item.preco);
        printf("Quantidade item: ");
        scanf("%f", &item.quantidade);

        // Salvando
        salvarItemArquivo(item);

        // Continuar
        printf("Deseja adiconar um novo item? (s/n): ");
        scanf(" %c", &continuar);
    }

    printf("Itens salvos.\n");
    telaPause();
    telaLimpa();
    salvarItensMatriz();
    //telaGerente();
}

void telaEstoque()
{
    system("title Estoque");

    FILE *file;
    char nome[50];
    float preco, quantidade;

    // Abrindo aruqivo em modo leitura "r"
    file = fopen("items.txt", "r");
    if (file == NULL)
    {
        perror("Erro");
        return 1;  // Se arquivo não abrir return
    }

    printf("Nome                 Preço                Quatidade(gramas)\n");
    // Le cada linha do arquivo e da
    while (fscanf(file, "%49s %f %f", nome, &preco, &quantidade) == 3)
    {
        printf("%-20s %-20.2f %.2f\n", nome, preco, quantidade);
    }

    fclose(file);
    telaPause();
    telaLimpa();
    telaGerente();
    //return 0;
}

void telaPedido()
{
    system("title Pedido");

    FILE *file;
    char nome[50];
    float preco, quantidade;
    int i, j, total_itens, id_venda;
    char string_preco[15], string_quant[15];

    // Abrindo aruqivo em modo leitura "r"
    file = fopen("items.txt", "r");
    if (file == NULL)
    {
        perror("Erro");
        return 1;  // Se arquivo não abrir return
    }

    total_itens = 0;
    // Le cada linha do arquivo e da
    while (fscanf(file, "%49s %f %f", nome, &preco, &quantidade) == 3)
    {
        // convertendo float para char
        snprintf(string_preco, sizeof(string_preco), "%.2f", preco);
        snprintf(string_quant, sizeof(string_quant), "%.2f", quantidade);

        salvarItensMatrizFor(total_itens, nome, string_preco, string_quant);
        total_itens++;
    }

    printf(" Itens");
    printf("                      Preço/Kg\n");
    for(i=0; i<total_itens; i++)
    {
        for(j=0; j<3; j++)
        {
            if (j == 0)
            {
                id_venda = i + 1;
                printf(" %-3d - ", id_venda);
            }
            if (j != 2)
            {
                printf("%-20s  ", matrizItens[i][j]);
            }
            else
            {
                printf("\n");
            }
        }
    }

    listarCompras(total_itens);


    fclose(file);
    telaPause();
    telaLimpa();
    telaGerente();
    //return 0;
}


void listarCompras(total_itens)
{


}

void listarCompras1(int total_itens)
{

}
