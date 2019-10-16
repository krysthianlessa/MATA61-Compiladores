#include <bits/stdc++.h>

using namespace std;

#define Q0 0
#define ID 1
#define NUM 2
#define CMT 3

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
vector<string> palavrasReservadas;
list<Lexema> listaDeLexemas;
int linha = 1;
int coluna = 1;
int qtdErros = 0;

void adicionaPalavrasReservadas() {
    palavrasReservadas.push_back("programainicio");
    palavrasReservadas.push_back("execucaoinicio");
    palavrasReservadas.push_back("fimexecucao");
    palavrasReservadas.push_back("fimprograma");
    palavrasReservadas.push_back("definainstrucao");
    palavrasReservadas.push_back("como");
    palavrasReservadas.push_back("inicio");
    palavrasReservadas.push_back("fim");
    palavrasReservadas.push_back("repita");
    palavrasReservadas.push_back("vezes");
    palavrasReservadas.push_back("fimrepita");
    palavrasReservadas.push_back("enquanto");
    palavrasReservadas.push_back("faca");
    palavrasReservadas.push_back("fimpara");
    palavrasReservadas.push_back("se");
    palavrasReservadas.push_back("entao");
    palavrasReservadas.push_back("fimse");
    palavrasReservadas.push_back("senao");
    palavrasReservadas.push_back("fimsenao");
    palavrasReservadas.push_back("mova");
    palavrasReservadas.push_back("passos");
    palavrasReservadas.push_back("vire");
    palavrasReservadas.push_back("para");
    palavrasReservadas.push_back("pare");
    palavrasReservadas.push_back("finalize");
    palavrasReservadas.push_back("apague");
    palavrasReservadas.push_back("lampada");
    palavrasReservadas.push_back("acenda");
    palavrasReservadas.push_back("aguarde");
    palavrasReservadas.push_back("ate");
    palavrasReservadas.push_back("robo");
    palavrasReservadas.push_back("pronto");
    palavrasReservadas.push_back("ocupado");
    palavrasReservadas.push_back("parado");
    palavrasReservadas.push_back("movimentando");
    palavrasReservadas.push_back("frente");
    palavrasReservadas.push_back("direita");
    palavrasReservadas.push_back("esquerda");
    palavrasReservadas.push_back("acessa");
    palavrasReservadas.push_back("a");
    palavrasReservadas.push_back("apagada");
}

bool ehCharValido(char c) {
    return (c == -1 || c == 9 || c == 10 || (c >= 32 && c <= 126));
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

bool eh_jogoDaVelha(char c) {
    return (c == '#');
}

bool eh_EOF(char c){
    return (c == -1);
}

void gerarLexema() {
    Lexema lex;
    lex.str = maquina.str_acumulado;
    listaDeLexemas.push_back(lex);
    maquina.str_acumulado = "";
}

void consome(char c) {
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
        if (c == 10) {
            linha++;
            coluna = 0;
        }
        return Q0;
    } else if (eh_jogoDaVelha(c)) {
        consome(c);
        return CMT;
    } else if (eh_EOF(c)) {
        return Q0;
    } else {
        cout << "Erro Léxico " << linha << "." << coluna << "." << ": Caracter inválido." << endl;
        qtdErros++;
        return Q0;
    }
}

int id(char c) {
    if (eh_letra(c)) {
        consome(c);
        return ID;
    } else if (eh_numero(c)) {
        consome(c);
        return ID;
    } else if (eh_separador(c)) {
        gerarLexema();
        if (c == 10) {
            linha++;
            coluna = 0;
        }
        return Q0;
    } else if (eh_EOF(c)) {
        gerarLexema();
        return Q0;
    } else {
        gerarLexema();
        cout << "Erro Léxico " << linha << "." << coluna << "." << ": Caracter inválido para constante identificadora." << endl;
        qtdErros++;
        return Q0;
    }
}

int num(char c) {
    if (eh_letra(c)) {
        gerarLexema();
        cout << "Erro Léxico " << linha << "." << coluna << "." << ": Não pode ter digito seguido de letra." << endl;
        qtdErros++;
        consome(c);
        return Q0;
    } else if (eh_numero(c)) {
        consome(c);
        return NUM;
    } else if (eh_separador(c)) {
        gerarLexema();
        if (c == 10){
            linha++;
            coluna = 0;
        }
        return Q0;
    } else if (eh_EOF(c)) {
        gerarLexema();
        return Q0;
    } else {
        gerarLexema();
        cout << "Erro Léxico " << linha << "." << coluna << "." << ": Caracter inválido para constante numérica." << endl;
        qtdErros++;
        return Q0;
    }
}

int cmt(char c) {
    if(c == 10) {
        gerarLexema();
        linha++;
        coluna = 0;
        return Q0;
    } else if(eh_EOF(c)) {
        gerarLexema();
        return Q0;
    } else {
        consome(c);
        return CMT;
    }
}

void analisadorLexico(string buffer) {
    maquina.estado = Q0;
    
    for(int i = 0; i < buffer.size(); i++, coluna++){
        
        if (!ehCharValido(buffer[i]) && maquina.estado != CMT) {
            cout << "Erro Léxico " << linha << "." << coluna << "." << ": Caracter não reconhecido pela linguagem." << endl;
            qtdErros++;
        } else {
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
                case CMT:
                    maquina.estado = cmt(buffer[i]);
                    break;
                default:
                    cout << buffer[i] << endl;
                    cout << "Tratar alguma coisa!\n";
                    break;
            }
        }
    }
}    

void analisadorSintatico(){}

int main()
{
    string buffer;
    char c;

    while((c = getchar()) && (c != EOF))
        buffer += c;
    buffer += -1;

    analisadorLexico(buffer);

    if (qtdErros == 0)
        cout << "Analise léxica concluída sem erros!" << endl;
    else
        cout << qtdErros << " erros léxicos encotrados." << endl;
    
    analisadorSintatico();
   
    return 0;
}
