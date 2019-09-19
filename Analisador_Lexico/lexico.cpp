#include <iostream>
#include <string>
#include <vector>

using namespace std;

#define Q0 0
#define ID 1
#define NUM 2

typedef struct {
    string str;
} Lexema;

typedef struct {
    int estado;
    int ult_linha;
    int ult_coluna;
    string str_acumulado;
} MaquinaDeEstados;

bool analisadorLexico(string buffer){
    return true;
}    


int main()
{
    char c;
    string buffer;

    while((c = getchar()) && (c != EOF))
        buffer += c;
    buffer += -1;

    if (analisadorLexico(buffer))
        cout << "Analise léxica concluída com sucesso!" << endl;
    
    
    return 0;
}
