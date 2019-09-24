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

MaquinaDeEstados maquina;
int linha = 1;
int coluna = 1;

bool ehCharValido(char c) {
    return ( c == 32 || c == 9 || c == 10 || c == -1 ||
            (c >= 48 && c <= 57) || 
            (c >= 65 && c <= 90) || 
            (c >= 97 && c <= 122));
}

bool eh_letra(char c) {
    return ((c >= 65 && c <= 90) || (c >= 97 && c <= 122));
}

bool eh_numero(char c) {
    return (c >= 48 && c <= 57);
}

bool eh_separador(char c) {
    return ((c == 9) || (c == 10) || (c == 32));
}

bool eh_EOF(char c){
    return (c == -1);
}

void gerarLexema(){
    maquina.str_acumulado = "";
}

void consome(char c){
    maquina.str_acumulado += c;
    maquina.ult_linha = linha;
    maquina.ult_coluna = coluna;
}

int qzero(char c) {
    if (eh_letra(c)) {
        consome(c);
        return ID;
    } else if (eh_numero(c)) {
        consome(c);
        return NUM;
    } else if (eh_separador(c)) {
        if (c == 10){
            linha++;
            coluna = 0;
        }
        return Q0;
    } else if (eh_EOF(c)) {
        return Q0;
    }    
}

int id(char c) {
    if (eh_letra(c)) {
        consome(c);
        return ID;
    } else if (eh_numero(c)) {
        consome(c);
        return NUM;
    } else if (eh_separador(c)) {
        if (c == 10){
            linha++;
            coluna = 0;
        }
        return Q0;
    } else if (eh_EOF(c)) {
        return Q0;
    }
}

int num(char c){
    if (eh_letra(c)) {
        gerarLexema();
        cout << "Erro Léxico " << linha << "." << coluna << "." << ": Não pode ter digito seguido de letra." << endl;
        // imprimeErro(maquina.ult_linha, maquina.ult_coluna);
        consome(c);
        return ID;
    } else if (eh_numero(c)) {
        consome(c);
        return NUM;
    } else if (eh_separador(c)) {
        if (c == 10){
            linha++;
            coluna = 0;
        }
        return Q0;
    } else if (eh_EOF(c)) {
        return Q0;
    }
}

void analisadorLexico(string buffer) {
    maquina.estado = Q0;
    
    for(int i = 0; i < buffer.size(); i++, coluna++){
        switch (maquina.estado) {
            case Q0:
                maquina.estado = qzero(buffer[i]);
                break;
            case ID:
                maquina.estado = id(buffer[i]);
                break;
            case NUM:
                maquina.estado = num(buffer[i]);
                break;
            default:
                cout << "Tratar alguma coisa!\n";
                break;
        }
    }
}    


int main()
{
    string buffer;
    char c;

    while((c = getchar()) && (c != EOF))
        buffer += c;
    buffer += -1;

    analisadorLexico(buffer);
    
    cout << "Analise léxica concluída com sucesso!" << endl;
    
    return 0;
}
