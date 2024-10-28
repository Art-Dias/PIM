//o arquivo interface.c, ficam as telas, onde o usuário poderá ver as opções do que ele pode interagir
#include "interface.h"
#include "structs.h"
#include "funcoes.h"
#include "estilos.h"
#include "cadastros.h"

// matriz global
char matrizItens[100][3][20];
int tamanho_carrinho = 0;

// Vetores para guardar itens durante venda
char itensSelecionados[100][50];  // Max 100 items e 50 char names
float quantidadeSelecionada[100];  // Guarda quantidade
int contagemItems = 0;  // Contador de itens selecionados
float valor_final;

void telaTamanho(){
    system("MODE con cols=168");// configura a quantidad de colunas e linhas que o console terá;
}

void telaLimpa(){
    system("cls");// limpa a tela;
}

void telaPause(){
    system("pause > NULL");// pausa a tela sem mostrar o texto padrão da função;
}

void telaEstilo(){
    system("color F0");// define a cor "f" verde para o fundo e a cor "0" preto para o texto
}

void telaInicio(){

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

void telaLogin(){

    system("title Login");

    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO consoleInfo;
    WORD saved_attributes;

    /* Salvar estado atual */
    GetConsoleScreenBufferInfo(hConsole, &consoleInfo);
    saved_attributes = consoleInfo.wAttributes;

    Pessoa pessoa;

    while (1) {
        // Exibe o campo de entrada do usuário
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

        // Campo de entrada do usuário
        fgets(pessoa.login.usuario, sizeof(pessoa.login.usuario), stdin);
        pessoa.login.usuario[strcspn(pessoa.login.usuario, "\n")] = 0; // Remove caractere de nova linha.

        if (strlen(pessoa.login.usuario) == 0) {
            printf(RED "\n\n                                     [!] O campo usuário não pode estar vazio!\a" RESET);
            SetConsoleTextAttribute(hConsole, saved_attributes);
            Sleep(800);
            telaLimpa();
            continue; // Reinicia o loop se o campo estiver vazio
        }

        // Exibe o campo de entrada da senha
        printf("\n                                                ");
        SetConsoleTextAttribute(hConsole, FOREGROUND_BLUE| FOREGROUND_GREEN | FOREGROUND_INTENSITY| FOREGROUND_RED | BACKGROUND_INTENSITY);
        printf(                                                " Senha: ");
        SetConsoleTextAttribute(hConsole, saved_attributes);
        printf(" ");

        char senha1[TAM_user] = {0}; // Inicializa a senha
        mascSenha('\0', senha1); // Função para mascarar a entrada da senha

        if (strlen(senha1) == 0) {
            printf(RED "\n\n                                      [!] O campo senha não pode estar vazio!\a" RESET);
            SetConsoleTextAttribute(hConsole, saved_attributes);
            Sleep(800);
            telaLimpa();
            continue; // Reinicia o loop se o campo estiver vazio
        }

        // Verifica login
        if(verificaLogin(pessoa.login.usuario, senha1, pessoa.cargo)){
            telaLimpa();
            // Aqui você pode usar o cargo para redirecionar o usuário
            if(strcmp(pessoa.cargo, "ADMINISTRADOR") == 0){
                telaMenuAdmin(); // Chama a tela do menu do administrador
            }else if(strcmp(pessoa.cargo, "GERENTE") == 0){
                telaGerente(); // Chama a tela do gerente
            }else if(strcmp(pessoa.cargo, "OPERADOR DE CAIXA") == 0 || strcmp(pessoa.cargo, "ESTOQUISTA") == 0){
                telaFuncionario(); // Chama a tela do funcionário
            }
            break; // Sai do loop se o login for bem-sucedido
        }else{
            bold(1);
            printf(RED "\n\n\t\t\t\t\t\t  [!] Login incorreto!\n"
                       "\t\t\t\t\t   Usuário ou senha estão incorretos!\a" RESET);
            bold(0);
            SetConsoleTextAttribute(hConsole, saved_attributes);
            Sleep(800);
            telaLimpa();
        }
    }
}

void telaMenuAdmin(){

    system("title Menu Administrador");

    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO consoleInfo;
    WORD saved_attributes;

    /* Salvar estado atual */
    GetConsoleScreenBufferInfo(hConsole, &consoleInfo);
    saved_attributes = consoleInfo.wAttributes;

    int escolha;

    do{
        printf("\n\n\n\n\n\n\n"
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
        printf(                                           "    [1] - Tela do Gerente           ");
        SetConsoleTextAttribute(hConsole, saved_attributes);
        printf(                                                                                "                                        \n"
                 "                                        ");
        SetConsoleTextAttribute(hConsole, FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_INTENSITY | FOREGROUND_RED | BACKGROUND_INTENSITY);
        printf(                                           "    [2] - Tela do Funcionário       ");
        SetConsoleTextAttribute(hConsole, saved_attributes);
        printf(                                                                                "                                        \n"
                 "                                        ");
        SetConsoleTextAttribute(hConsole, FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_INTENSITY | FOREGROUND_RED | BACKGROUND_INTENSITY);
        printf(                                           "    [0] - Sair                      ");
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

        scanf("%i", &escolha);
        fflush(stdin);
        SetConsoleTextAttribute(hConsole, saved_attributes);

        switch(escolha){
        case 0:
            telaLimpa();
            SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN | BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_INTENSITY | BACKGROUND_RED);
            animacao_de_saida();
            SetConsoleTextAttribute(hConsole, saved_attributes);

            telaLimpa();
            telaSaida();
            break;
        case 1:
            telaLimpa();
            telaGerente();
            break;
        case 2:
            telaLimpa();
            telaFuncionario();
            break;
        default :
            bold(1);
            printf(RED "\n\n\t\t\t\t\t\t [!] Opção Inválida!");
            bold(0);
            SetConsoleTextAttribute(hConsole, saved_attributes);
            Sleep(800);
        }
        telaLimpa();
    }while(escolha != 0);
    telaLimpa();
}

void telaGerente(){

    system("title Menu Gerencia");

    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO consoleInfo;
    WORD saved_attributes;

    /* Salvar estado atual */
    GetConsoleScreenBufferInfo(hConsole, &consoleInfo);
    saved_attributes = consoleInfo.wAttributes;

    int escolha;

    do{
        printf("\n\n\n\n\n\n\n"
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
        printf(                                           "    [1] - Cadastro                  ");
        SetConsoleTextAttribute(hConsole, saved_attributes);
        printf(                                                                                "                                        \n"
                 "                                        ");
        SetConsoleTextAttribute(hConsole, FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_INTENSITY | FOREGROUND_RED | BACKGROUND_INTENSITY);
        printf(                                           "    [2] - Ponto de Venda            ");
        SetConsoleTextAttribute(hConsole, saved_attributes);
        printf(                                                                                "                                        \n"
                 "                                        ");
        SetConsoleTextAttribute(hConsole, FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_INTENSITY | FOREGROUND_RED | BACKGROUND_INTENSITY);
        printf(                                           "    [3] - Estoque                   ");
        SetConsoleTextAttribute(hConsole, saved_attributes);
        printf(                                                                                "                                        \n"
                 "                                        ");
        SetConsoleTextAttribute(hConsole, FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_INTENSITY | FOREGROUND_RED | BACKGROUND_INTENSITY);
        printf(                                           "    [4] - Preços                    ");
        SetConsoleTextAttribute(hConsole, saved_attributes);
        printf(                                                                                "                                        \n"
                 "                                        ");
        SetConsoleTextAttribute(hConsole, FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_INTENSITY | FOREGROUND_RED | BACKGROUND_INTENSITY);
        printf(                                           "    [5] - Informações               ");
        SetConsoleTextAttribute(hConsole, saved_attributes);
        printf(                                                                                "                                        \n"
                 "                                        ");
        SetConsoleTextAttribute(hConsole, FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_INTENSITY | FOREGROUND_RED | BACKGROUND_INTENSITY);
        printf(                                           "    [0] - Sair                      ");
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

        scanf("%i", &escolha);
        fflush(stdin);
        SetConsoleTextAttribute(hConsole, saved_attributes);

        switch(escolha){
        case 0:
            telaLimpa();
            SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN | BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_INTENSITY | BACKGROUND_RED);
            animacao_de_saida();
            SetConsoleTextAttribute(hConsole, saved_attributes);

            telaLimpa();
            telaSaida();
            break;
        case 1:
            telaLimpa();
            TelaCadastro();
            break;
        case 2:
            telaLimpa();
            telaPedido();

            break;
        case 3:
            telaLimpa();
            telaEstoque();
            break;
        case 4:
            telaLimpa();
            break;
        case 5:
            telaLimpa();
            DadosUsuario();
            break;
        default :
            bold(1);
            printf(RED "\n\n\t\t\t\t\t\t [!] Opção Inválida!");
            bold(0);
            SetConsoleTextAttribute(hConsole, saved_attributes);
            Sleep(800);
        }
        telaLimpa();
    }while(escolha != 0);
    telaLimpa();
}

void telaFuncionario(){

    system("title Menu Funcionário");

    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO consoleInfo;
    WORD saved_attributes;

    /* Salvar estado atual */
    GetConsoleScreenBufferInfo(hConsole, &consoleInfo);
    saved_attributes = consoleInfo.wAttributes;

    int escolha;

    do{
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

        scanf("%i", &escolha);
        fflush(stdin);

        switch(escolha){
        case 0:
            telaLimpa();
            SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN | BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_INTENSITY | BACKGROUND_RED);
            animacao_de_saida();
            SetConsoleTextAttribute(hConsole, saved_attributes);

            telaLimpa();
            telaSaida();
            break;
        case 1:
            telaLimpa();

            break;
        case 2:
            telaLimpa();

            break;
        case 3:
            telaLimpa();

            break;
        default :
            bold(1);
            printf(RED "\n\n\t\t\t\t\t\t [!] Opção Inválida!");
            bold(0);
            SetConsoleTextAttribute(hConsole, saved_attributes);
            Sleep(800);
        }
        telaLimpa();
    }while(escolha != 0);
    telaLimpa();
}

void telaSaida(){

    system("title Sair");

    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO consoleInfo;
    WORD saved_attributes;

    /* Salvar estado atual */
    GetConsoleScreenBufferInfo(hConsole, &consoleInfo);
    saved_attributes = consoleInfo.wAttributes;

    int escolha;

    do{
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

        scanf("%i", &escolha);
        fflush(stdin);
        SetConsoleTextAttribute(hConsole, saved_attributes);

        switch(escolha){
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
            exit(0); // Encerra o programa com sucesso.
            break;
        default :
            bold(1);
            printf(RED "\n\n\t\t\t\t\t\t [!] Opção Inválida!");
            bold(0);
            SetConsoleTextAttribute(hConsole, saved_attributes);
            Sleep(800);
        }
        telaLimpa();
    }while(escolha != 0);
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
void telaCadastroItem()
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

void telaPedido(int reChamar)
{
    system("title Pedido");

    FILE *file;
    char nome[50];
    float preco, quantidade;
    int i, j, total_itens, id_venda, reChamado;
    char string_preco[15], string_quant[15];

    // Caso a função tenha sido chamada pela listarCompras
    reChamado = reChamar;

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

    listarCompras(total_itens, reChamado);


    fclose(file);
    telaPause();
    telaLimpa();
    telaGerente();
    //return 0;
}

void listarCompras(int total_itens, int reChamado)
{
    int itemSelecionado;
    float quantidade, valorPorKG;
    char continuar = 's';

    // Voltando a primeira linha para printar
    //printf("\033[%dA", total_itens);

    // Esse rechamdo é pra checar se a função foi chamada por ela mesma
    if (reChamado == 9)
    {
        // Lista de Itens
        printf("\nItens selecionados:\n");
        printf("Nome               Quantidade(gramas)\n");
        for (int i = 0; i < contagemItems; i++)
        {
            printf("%-20s %.2f\n", itensSelecionados[i], quantidadeSelecionada[i]);
        }

    }
    while (continuar == 's' || continuar == 'S')
    {
        printf("\033[H");

        // Selecionar item
        printf("\n\033[45CSelecione o ID do item que deseja comprar: ");
        scanf("%d", &itemSelecionado);

        // Checar se seleção é valida
        if (itemSelecionado < 1 || itemSelecionado > total_itens)
        {
            printf("\033[45CItem inválido.\n");
            continue;  // Se for invalido, sai do loop
        }

        // Pedir quantidade
        printf("\033[45CDigite a quantidade (em gramas) que deseja comprar: ");
        scanf("%f", &quantidade);

        // Guarda item e quantidade
        int temp_indice = itemSelecionado - 1;  // Adjust to zero-based index
        strcpy(itensSelecionados[contagemItems], matrizItens[temp_indice][0]);  // Salvar nome do item
        quantidadeSelecionada[contagemItems] = quantidade;  // Salvar quantidade
        contagemItems++;

        // Somando o valor final da compra
        char *endptr;

        float valorPorKG = strtof(matrizItens[temp_indice][1], &endptr);   // Converte char para float
        valor_final = valor_final + (valorPorKG * (quantidade/1000));

        // Mostrar itens selecionados
        printf("\n\033[45CItens selecionados:\n");
        printf("\033[45CNome                   Quantidade(gramas)\n");
        for (int i = 0; i < contagemItems; i++)
        {
            printf("\033[45C%-20s %.2f\n", itensSelecionados[i], quantidadeSelecionada[i]);
        }

        // Continuar
        printf("\n\033[45CDeseja selecionar mais itens? (s/n): ");
        scanf(" %c", &continuar);

        if (continuar == 's' || continuar == 'S')
        {
            //telaPause();
            telaLimpa();
            // Chamando a função com parametro 9 para saber que está sendo chamada por esta função
            telaPedido(9);
            continue;
        }
        else
        {
            telaPause();
            telaLimpa();
            finalizarCompra();
            continue;
        }


        //telaLimpa();
        // Chamando a função com parametro 9 para saber que está sendo chamada por esta função
        //telaPedido(9);
        //continue;
    }

    telaPause();
    telaLimpa();
    telaGerente();
    //telaPedido();
}

void finalizarCompra()
{
    printf("\nItens selecionados:\n");
    printf("Nome               Quantidade(gramas)\n");
    for (int i = 0; i < contagemItems; i++)
    {
        printf("%-20s %.2f\n", itensSelecionados[i], quantidadeSelecionada[i]);
    }
    printf("\n Valor final R$:%.2f", valor_final);

    // Resetando variaveis
    memset(&itensSelecionados, 0, sizeof(itensSelecionados));
    memset(&quantidadeSelecionada, 0, sizeof(itensSelecionados));
    contagemItems = 0;
    valor_final = 0;

    telaPause();
    telaLimpa();
    telaGerente();
}

