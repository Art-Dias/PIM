//as fun��es principais que foram feitas, ficam no arquivo funcoes.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h> //Permite que o c�digo entenda caracteres especiais.
#include <windows.h>
#include <conio.h>
#include <ctype.h>
#include "interface.c"
#include "funcoes.c"
#include "estilos.c"

int main(int argc, char *argv[]){

    setlocale(LC_ALL, "Portuguese"); /* Definindo configura��o padr�o do sistema */

    telaEstilo();
    //telaInicio();
    telaGerente();
    //Comando para posicionar tela
    system("powershell -command \"[console]::windowheight=[console]::largestwindowheight; [console]::windowwidth=[console]::largestwindowwidth\"");

    return 0;
}
