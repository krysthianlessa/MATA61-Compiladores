#include <bits/stdc++.h>

using namespace std;

#define Q0 0
#define ID 1
#define NUM 2
#define CMT 3

#define LINHAS 75
#define COLUNAS 60

typedef struct {
    string str;
    string original;
    int linha;
    int coluna;
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
vector<string> instrucoesDeclaradas;
vector<string> gramatica;
vector<int> qtdRegras;
int linha = 1;
int coluna = 1;
int qtdErros = 0;

string tableLR[LINHAS][COLUNAS] = {{"#","programainicio","fimprograma","execucaoinicio","fimexecucao","definainstrucao","id","como","inicio","fim","repita","num","vezes","fimrepita","enquanto","faca","fimpara","se","entao","fimse","senao","fimsenao","mova","passos","vire_para","pare","finalize","apague_lampada","acenda_lampada","aguarde_ate","robo_pronto","robo_ocupado","robo_parado","robo_movimentando","frente_robo_bloqueada","direita_robo_bloqueada","esquerda_robo_bloqueada","lampada_acesa_a_frente","lampada_apagada_a_frente","lampada_acesa_a_esquerda","lampada_apagada_a_esquerda","lampada_acesa_a_direita","lampada_apagada_a_direita","esquerda","direita","$","programa'","programa","execucao","declaracoes","declaracao","comando","bloco","pre_comando","iteracao","laco","condicional","instrucao","condicao","sentido"},{"0","s2","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","1","#","#","#","#","#","#","#","#","#","#","#","#"},{"1","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","acc","#","#","#","#","#","#","#","#","#","#","#","#","#","#"},{"2","#","#","s6","#","s7","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","4","3","5","#","#","#","#","#","#","#","#","#"},{"3","#","#","s6","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","8","#","#","#","#","#","#","#","#","#","#","#"},{"4","#","s9","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#"},{"5","#","#","r4","#","s7","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","10","5","#","#","#","#","#","#","#","#","#"},{"6","#","#","#","#","#","s23","#","s17","#","s18","#","#","#","s19","#","#","s20","#","#","#","#","s21","#","s22","s24","s25","s26","s27","s28","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","11","12","#","13","14","15","16","#","#"},{"7","#","#","#","#","#","s29","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#"},{"8","#","s30","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#"},{"9","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","r2","#","#","#","#","#","#","#","#","#","#","#","#","#","#"},{"10","#","#","r5","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#"},{"11","#","#","#","s31","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#"},{"12","#","#","r7","r7","r7","r7","#","r7","r7","r7","#","#","r7","r7","#","r7","r7","#","r7","#","r7","r7","#","r7","r7","r7","r7","r7","r7","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#"},{"13","#","#","r8","r8","r8","r8","#","r8","r8","r8","#","#","r8","r8","#","r8","r8","#","r8","#","r8","r8","#","r8","r8","r8","r8","r8","r8","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#"},{"14","#","#","r9","r9","r9","r9","#","r9","r9","r9","#","#","r9","r9","#","r9","r9","#","r9","#","r9","r9","#","r9","r9","r9","r9","r9","r9","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#"},{"15","#","#","r10","r10","r10","r10","#","r10","r10","r10","#","#","r10","r10","#","r10","r10","#","r10","#","r10","r10","#","r10","r10","r10","r10","r10","r10","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#"},{"16","#","#","r11","r11","r11","r11","#","r11","r11","r11","#","#","r11","r11","#","r11","r11","#","r11","#","r11","r11","#","r11","r11","r11","r11","r11","r11","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#"},{"17","#","#","#","#","#","s23","#","s17","s32","s18","#","#","#","s19","#","#","s20","#","#","#","#","s21","#","s22","s24","s25","s26","s27","s28","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","34","12","33","13","14","15","16","#","#"},{"18","#","#","#","#","#","#","#","#","#","#","s35","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#"},{"19","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","s37","s38","s39","s40","s41","s42","s43","s44","s45","s46","s47","s48","s49","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","36","#"},{"20","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","s37","s38","s39","s40","s41","s42","s43","s44","s45","s46","s47","s48","s49","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","50","#"},{"21","#","#","r20","r20","r20","r20","#","r20","r20","r20","s51","#","r20","r20","#","r20","r20","#","r20","#","r20","r20","s52","r20","r20","r20","r20","r20","r20","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#"},{"22","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","s54","s55","#","#","#","#","#","#","#","#","#","#","#","#","#","#","53"},{"23","#","#","r25","r25","r25","r25","#","r25","r25","r25","#","#","r25","r25","#","r25","r25","#","r25","#","r25","r25","#","r25","r25","r25","r25","r25","r25","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#"},{"24","#","#","r26","r26","r26","r26","#","r26","r26","r26","#","#","r26","r26","#","r26","r26","#","r26","#","r26","r26","#","r26","r26","r26","r26","r26","r26","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#"},{"25","#","#","r27","r27","r27","r27","#","r27","r27","r27","#","#","r27","r27","#","r27","r27","#","r27","#","r27","r27","#","r27","r27","r27","r27","r27","r27","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#"},{"26","#","#","r28","r28","r28","r28","#","r28","r28","r28","#","#","r28","r28","#","r28","r28","#","r28","#","r28","r28","#","r28","r28","r28","r28","r28","r28","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#"},{"27","#","#","r29","r29","r29","r29","#","r29","r29","r29","#","#","r29","r29","#","r29","r29","#","r29","#","r29","r29","#","r29","r29","r29","r29","r29","r29","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#"},{"28","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","s37","s38","s39","s40","s41","s42","s43","s44","s45","s46","s47","s48","s49","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","56","#"},{"29","#","#","#","#","#","#","s57","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#"},{"30","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","r1","#","#","#","#","#","#","#","#","#","#","#","#","#","#"},{"31","#","r3","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#"},{"32","#","#","r12","r12","r12","r12","#","r12","r12","r12","#","#","r12","r12","#","r12","r12","#","r12","#","r12","r12","#","r12","r12","r12","r12","r12","r12","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#"},{"33","#","#","#","#","#","s23","#","s17","s58","s18","#","#","#","s19","#","#","s20","#","#","#","#","s21","#","s22","s24","s25","s26","s27","s28","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","59","12","#","13","14","15","16","#","#"},{"34","#","#","#","#","#","r14","#","r14","r14","r14","#","#","#","r14","#","#","r14","#","#","#","#","r14","#","r14","r14","r14","r14","r14","r14","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#"},{"35","#","#","#","#","#","#","#","#","#","#","#","s60","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#"},{"36","#","#","#","#","#","#","#","#","#","#","#","#","#","#","s61","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#"},{"37","#","#","r31","r31","r31","r31","#","r31","r31","r31","#","#","r31","r31","r31","r31","r31","r31","r31","#","r31","r31","#","r31","r31","r31","r31","r31","r31","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#"},{"38","#","#","r32","r32","r32","r32","#","r32","r32","r32","#","#","r32","r32","r32","r32","r32","r32","r32","#","r32","r32","#","r32","r32","r32","r32","r32","r32","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#"},{"39","#","#","r33","r33","r33","r33","#","r33","r33","r33","#","#","r33","r33","r33","r33","r33","r33","r33","#","r33","r33","#","r33","r33","r33","r33","r33","r33","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#"},{"40","#","#","r34","r34","r34","r34","#","r34","r34","r34","#","#","r34","r34","r34","r34","r34","r34","r34","#","r34","r34","#","r34","r34","r34","r34","r34","r34","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#"},{"41","#","#","r35","r35","r35","r35","#","r35","r35","r35","#","#","r35","r35","r35","r35","r35","r35","r35","#","r35","r35","#","r35","r35","r35","r35","r35","r35","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#"},{"42","#","#","r36","r36","r36","r36","#","r36","r36","r36","#","#","r36","r36","r36","r36","r36","r36","r36","#","r36","r36","#","r36","r36","r36","r36","r36","r36","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#"},{"43","#","#","r37","r37","r37","r37","#","r37","r37","r37","#","#","r37","r37","r37","r37","r37","r37","r37","#","r37","r37","#","r37","r37","r37","r37","r37","r37","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#"},{"44","#","#","r38","r38","r38","r38","#","r38","r38","r38","#","#","r38","r38","r38","r38","r38","r38","r38","#","r38","r38","#","r38","r38","r38","r38","r38","r38","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#"},{"45","#","#","r39","r39","r39","r39","#","r39","r39","r39","#","#","r39","r39","r39","r39","r39","r39","r39","#","r39","r39","#","r39","r39","r39","r39","r39","r39","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#"},{"46","#","#","r40","r40","r40","r40","#","r40","r40","r40","#","#","r40","r40","r40","r40","r40","r40","r40","#","r40","r40","#","r40","r40","r40","r40","r40","r40","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#"},{"47","#","#","r41","r41","r41","r41","#","r41","r41","r41","#","#","r41","r41","r41","r41","r41","r41","r41","#","r41","r41","#","r41","r41","r41","r41","r41","r41","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#"},{"48","#","#","r42","r42","r42","r42","#","r42","r42","r42","#","#","r42","r42","r42","r42","r42","r42","r42","#","r42","r42","#","r42","r42","r42","r42","r42","r42","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#"},{"49","#","#","r43","r43","r43","r43","#","r43","r43","r43","#","#","r43","r43","r43","r43","r43","r43","r43","#","r43","r43","#","r43","r43","r43","r43","r43","r43","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#"},{"50","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","s62","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#"},{"51","#","#","r21","r21","r21","r21","#","r21","r21","r21","#","#","r21","r21","#","r21","r21","#","r21","#","r21","r21","s63","r21","r21","r21","r21","r21","r21","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#"},{"52","#","#","r22","r22","r22","r22","#","r22","r22","r22","#","#","r22","r22","#","r22","r22","#","r22","#","r22","r22","#","r22","r22","r22","r22","r22","r22","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#"},{"53","#","#","r24","r24","r24","r24","#","r24","r24","r24","#","#","r24","r24","#","r24","r24","#","r24","#","r24","r24","#","r24","r24","r24","r24","r24","r24","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#"},{"54","#","#","r44","r44","r44","r44","#","r44","r44","r44","#","#","r44","r44","#","r44","r44","#","r44","#","r44","r44","#","r44","r44","r44","r44","r44","r44","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#"},{"55","#","#","r45","r45","r45","r45","#","r45","r45","r45","#","#","r45","r45","#","r45","r45","#","r45","#","r45","r45","#","r45","r45","r45","r45","r45","r45","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#"},{"56","#","#","r30","r30","r30","r30","#","r30","r30","r30","#","#","r30","r30","#","r30","r30","#","r30","#","r30","r30","#","r30","r30","r30","r30","r30","r30","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#"},{"57","#","#","#","#","#","s23","#","s17","#","s18","#","#","#","s19","#","#","s20","#","#","#","#","s21","#","s22","s24","s25","s26","s27","s28","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","64","12","#","13","14","15","16","#","#"},{"58","#","#","r13","r13","r13","r13","#","r13","r13","r13","#","#","r13","r13","#","r13","r13","#","r13","#","r13","r13","#","r13","r13","r13","r13","r13","r13","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#"},{"59","#","#","#","#","#","r15","#","r15","r15","r15","#","#","#","r15","#","#","r15","#","#","#","#","r15","#","r15","r15","r15","r15","r15","r15","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#"},{"60","#","#","#","#","#","s23","#","s17","#","s18","#","#","#","s19","#","#","s20","#","#","#","#","s21","#","s22","s24","s25","s26","s27","s28","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","65","12","#","13","14","15","16","#","#"},{"61","#","#","#","#","#","s23","#","s17","#","s18","#","#","#","s19","#","#","s20","#","#","#","#","s21","#","s22","s24","s25","s26","s27","s28","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","66","12","#","13","14","15","16","#","#"},{"62","#","#","#","#","#","s23","#","s17","#","s18","#","#","#","s19","#","#","s20","#","#","#","#","s21","#","s22","s24","s25","s26","s27","s28","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","67","12","#","13","14","15","16","#","#"},{"63","#","#","r23","r23","r23","r23","#","r23","r23","r23","#","#","r23","r23","#","r23","r23","#","r23","#","r23","r23","#","r23","r23","r23","r23","r23","r23","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#"},{"64","#","#","r6","#","r6","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#"},{"65","#","#","#","#","#","#","#","#","#","#","#","#","s68","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#"},{"66","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","s69","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#"},{"67","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","s70","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#"},{"68","#","#","r16","r16","r16","r16","#","r16","r16","r16","#","#","r16","r16","#","r16","r16","#","r16","#","r16","r16","#","r16","r16","r16","r16","r16","r16","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#"},{"69","#","#","r17","r17","r17","r17","#","r17","r17","r17","#","#","r17","r17","#","r17","r17","#","r17","#","r17","r17","#","r17","r17","r17","r17","r17","r17","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#"},{"70","#","#","r18","r18","r18","r18","#","r18","r18","r18","#","#","r18","r18","#","r18","r18","#","r18","s71","r18","r18","#","r18","r18","r18","r18","r18","r18","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#"},{"71","#","#","#","#","#","s23","#","s17","#","s18","#","#","#","s19","#","#","s20","#","#","#","#","s21","#","s22","s24","s25","s26","s27","s28","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","72","12","#","13","14","15","16","#","#"},{"72","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","s73","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#"},{"73","#","#","r19","r19","r19","r19","#","r19","r19","r19","#","#","r19","r19","#","r19","r19","#","r19","#","r19","r19","#","r19","r19","r19","r19","r19","r19","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#"}};

void preencherGramatica() {
    gramatica.push_back("programa'");
    gramatica.push_back("programa");
    gramatica.push_back("programa");
    gramatica.push_back("execucao");
    gramatica.push_back("declaracoes");
    gramatica.push_back("declaracoes");
    gramatica.push_back("declaracao");
    gramatica.push_back("comando");
    gramatica.push_back("comando");
    gramatica.push_back("comando");
    gramatica.push_back("comando");
    gramatica.push_back("comando");
    gramatica.push_back("bloco");
    gramatica.push_back("bloco");
    gramatica.push_back("pre_comando");
    gramatica.push_back("pre_comando");
    gramatica.push_back("iteracao");
    gramatica.push_back("laco");
    gramatica.push_back("condicional");
    gramatica.push_back("condicional");
    gramatica.push_back("instrucao");
    gramatica.push_back("instrucao");
    gramatica.push_back("instrucao");
    gramatica.push_back("instrucao");
    gramatica.push_back("instrucao");
    gramatica.push_back("instrucao");
    gramatica.push_back("instrucao");
    gramatica.push_back("instrucao");
    gramatica.push_back("instrucao");
    gramatica.push_back("instrucao");
    gramatica.push_back("instrucao");
    gramatica.push_back("condicao");
    gramatica.push_back("condicao");
    gramatica.push_back("condicao");
    gramatica.push_back("condicao");
    gramatica.push_back("condicao");
    gramatica.push_back("condicao");
    gramatica.push_back("condicao");
    gramatica.push_back("condicao");
    gramatica.push_back("condicao");
    gramatica.push_back("condicao");
    gramatica.push_back("condicao");
    gramatica.push_back("condicao");
    gramatica.push_back("condicao");
    gramatica.push_back("sentido");
    gramatica.push_back("sentido");

    qtdRegras.push_back(1);
    qtdRegras.push_back(4);
    qtdRegras.push_back(3);
    qtdRegras.push_back(3);
    qtdRegras.push_back(1);
    qtdRegras.push_back(2);
    qtdRegras.push_back(4);
    qtdRegras.push_back(1);
    qtdRegras.push_back(1);
    qtdRegras.push_back(1);
    qtdRegras.push_back(1);
    qtdRegras.push_back(1);
    qtdRegras.push_back(2);
    qtdRegras.push_back(3);
    qtdRegras.push_back(1);
    qtdRegras.push_back(2);
    qtdRegras.push_back(5);
    qtdRegras.push_back(5);
    qtdRegras.push_back(5);
    qtdRegras.push_back(8);
    qtdRegras.push_back(1);
    qtdRegras.push_back(2);
    qtdRegras.push_back(2);
    qtdRegras.push_back(3);
    qtdRegras.push_back(2);
    qtdRegras.push_back(1);
    qtdRegras.push_back(1);
    qtdRegras.push_back(1);
    qtdRegras.push_back(1);
    qtdRegras.push_back(1);
    qtdRegras.push_back(2);
    qtdRegras.push_back(1);
    qtdRegras.push_back(1);
    qtdRegras.push_back(1);
    qtdRegras.push_back(1);
    qtdRegras.push_back(1);
    qtdRegras.push_back(1);
    qtdRegras.push_back(1);
    qtdRegras.push_back(1);
    qtdRegras.push_back(1);
    qtdRegras.push_back(1);
    qtdRegras.push_back(1);
    qtdRegras.push_back(1);
    qtdRegras.push_back(1);
    qtdRegras.push_back(1);
    qtdRegras.push_back(1);
}



vector<string> geraPalavrasReservadas() {
    vector<string> vetor;

    vetor.push_back("programainicio");
    vetor.push_back("execucaoinicio");
    vetor.push_back("fimexecucao");
    vetor.push_back("fimprograma");
    vetor.push_back("definainstrucao");
    vetor.push_back("como");
    vetor.push_back("inicio");
    vetor.push_back("fim");
    vetor.push_back("repita");
    vetor.push_back("vezes");
    vetor.push_back("fimrepita");
    vetor.push_back("enquanto");
    vetor.push_back("faca");
    vetor.push_back("fimpara");
    vetor.push_back("se");
    vetor.push_back("entao");
    vetor.push_back("fimse");
    vetor.push_back("senao");
    vetor.push_back("fimsenao");
    vetor.push_back("mova");
    vetor.push_back("passos");
    vetor.push_back("vire_para");
    vetor.push_back("pare");
    vetor.push_back("finalize");
    vetor.push_back("apague_lampada");
    vetor.push_back("acenda_lampada");
    vetor.push_back("aguarde_ate");
    vetor.push_back("robo_pronto");
    vetor.push_back("robo_ocupado");
    vetor.push_back("robo_parado");
    vetor.push_back("robo_movimentando");
    vetor.push_back("frente_robo_bloqueada");
    vetor.push_back("direita_robo_bloqueada");
    vetor.push_back("esquerda_robo_bloqueada");
    vetor.push_back("lampada_acesa_a_frente");
    vetor.push_back("lampada_apagada_a_frente");
    vetor.push_back("lampada_acesa_a_esquerda");
    vetor.push_back("lampada_apagada_a_esquerda");
    vetor.push_back("lampada_acesa_a_direita");
    vetor.push_back("lampada_apagada_a_direita");
    vetor.push_back("esquerda");
    vetor.push_back("direita");

    return vetor;
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
    lex.linha = linha;
    lex.coluna = coluna;
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

Lexema join(vector<Lexema> vetor){
    Lexema palavrasJuntas;
    palavrasJuntas.str = "";

    for (int i = 0; i < vetor.size(); i++){
        palavrasJuntas.str += vetor[i].str;
        palavrasJuntas.str += '_';
    }
    palavrasJuntas.str.pop_back();
    palavrasJuntas.linha = vetor[vetor.size() - 1].linha;
    palavrasJuntas.coluna = vetor[vetor.size() - 1].coluna;
    return palavrasJuntas;
}


list<Lexema> juntarPalavras() {
    list<Lexema> listaDeLexemasNova;
    vector<Lexema> lexemasParaJuntar;
    Lexema lexema;

    while (!listaDeLexemas.empty()) {
        lexema = listaDeLexemas.front();
        listaDeLexemas.pop_front();

        if(lexema.str == "robo" && !listaDeLexemas.empty()) {
            lexemasParaJuntar.push_back(lexema);
            lexema = listaDeLexemas.front();
            listaDeLexemas.pop_front();

            if(lexema.str == "pronto" || lexema.str == "ocupado" || 
                lexema.str == "parado" || lexema.str == "movimentando") {
                lexemasParaJuntar.push_back(lexema);
                listaDeLexemasNova.push_back(join(lexemasParaJuntar));
                lexemasParaJuntar.clear();
            } else {
                listaDeLexemasNova.push_back(lexemasParaJuntar[0]);
                listaDeLexemas.push_front(lexema);
                lexemasParaJuntar.pop_back();
            }
        } else if (lexema.str == "vire" && !listaDeLexemas.empty()) {
            lexemasParaJuntar.push_back(lexema);
            lexema = listaDeLexemas.front();
            listaDeLexemas.pop_front();

            if(lexema.str == "para"){
                lexemasParaJuntar.push_back(lexema);
                listaDeLexemasNova.push_back(join(lexemasParaJuntar));
                lexemasParaJuntar.clear();
            } else {
                listaDeLexemasNova.push_back(lexemasParaJuntar[0]);
                listaDeLexemas.push_front(lexema);
                lexemasParaJuntar.pop_back();
            }

        } else if ((lexema.str == "apague" || lexema.str == "acenda") && !listaDeLexemas.empty()) {
            lexemasParaJuntar.push_back(lexema);
            lexema = listaDeLexemas.front();
            listaDeLexemas.pop_front();

            if(lexema.str == "lampada"){
                lexemasParaJuntar.push_back(lexema);
                listaDeLexemasNova.push_back(join(lexemasParaJuntar));
                lexemasParaJuntar.clear();
            } else {
                listaDeLexemasNova.push_back(lexemasParaJuntar[0]);
                listaDeLexemas.push_front(lexema);
                lexemasParaJuntar.pop_back();
            }
        } else if(lexema.str == "aguarde" && !listaDeLexemas.empty()) {
            lexemasParaJuntar.push_back(lexema);
            lexema = listaDeLexemas.front();
            listaDeLexemas.pop_front();

            if(lexema.str == "ate"){
                lexemasParaJuntar.push_back(lexema);
                listaDeLexemasNova.push_back(join(lexemasParaJuntar));
                lexemasParaJuntar.clear();
            } else {
                listaDeLexemasNova.push_back(lexemasParaJuntar[0]);
                listaDeLexemas.push_front(lexema);
                lexemasParaJuntar.pop_back();
            }
        } else if((lexema.str == "frente" || lexema.str == "direita" || lexema.str == "esquerda") && !listaDeLexemas.empty()) {
            lexemasParaJuntar.push_back(lexema);
            lexema = listaDeLexemas.front();
            listaDeLexemas.pop_front();

            if (lexema.str == "robo" && !listaDeLexemas.empty()) {
                lexemasParaJuntar.push_back(lexema);
                lexema = listaDeLexemas.front();
                listaDeLexemas.pop_front();

                if (lexema.str == "bloqueada") {
                    lexemasParaJuntar.push_back(lexema);
                    listaDeLexemasNova.push_back(join(lexemasParaJuntar));
                    lexemasParaJuntar.clear();
                } else {
                    listaDeLexemasNova.push_back(lexemasParaJuntar[0]);
                    listaDeLexemas.push_front(lexema);
                    listaDeLexemas.push_front(lexemasParaJuntar[1]);
                    lexemasParaJuntar.clear();
                }
            } else {
                listaDeLexemasNova.push_back(lexemasParaJuntar[0]);
                listaDeLexemas.push_front(lexema);
                lexemasParaJuntar.pop_back();
            }
        } else if(lexema.str == "lampada" && !listaDeLexemas.empty()) {
            lexemasParaJuntar.push_back(lexema);
            lexema = listaDeLexemas.front();
            listaDeLexemas.pop_front();

            if ((lexema.str == "acesa" || lexema.str == "apagada") && !listaDeLexemas.empty()) {
                lexemasParaJuntar.push_back(lexema);
                lexema = listaDeLexemas.front();
                listaDeLexemas.pop_front();

                if (lexema.str == "a"  && !listaDeLexemas.empty()) {
                    lexemasParaJuntar.push_back(lexema);
                    lexema = listaDeLexemas.front();
                    listaDeLexemas.pop_front();

                    if (lexema.str == "frente" || lexema.str == "direita" || lexema.str == "esquerda") {
                        lexemasParaJuntar.push_back(lexema);
                        listaDeLexemasNova.push_back(join(lexemasParaJuntar));
                        lexemasParaJuntar.clear();
                    } else {
                        listaDeLexemasNova.push_back(lexemasParaJuntar[0]);
                        listaDeLexemas.push_front(lexema);
                        listaDeLexemas.push_front(lexemasParaJuntar[2]);
                        listaDeLexemas.push_front(lexemasParaJuntar[1]);
                        lexemasParaJuntar.clear();
                    }
                } else {
                    listaDeLexemasNova.push_back(lexemasParaJuntar[0]);
                    listaDeLexemas.push_front(lexema);
                    listaDeLexemas.push_front(lexemasParaJuntar[1]);
                    lexemasParaJuntar.clear();
                }
            } else {
                listaDeLexemasNova.push_back(lexemasParaJuntar[0]);
                listaDeLexemas.push_front(lexema);
                lexemasParaJuntar.pop_back();
            }
        } else {
            listaDeLexemasNova.push_back(lexema);
        }
    }
    
    return listaDeLexemasNova;
}

/*Funções do sintático*/

bool ehPalavraReservada(string lexema){
    for (int i = 0; i < palavrasReservadas.size(); i++)
        if (palavrasReservadas[i] == lexema)
            return true;
    
    return false;
}

list<Lexema> pegarIdeNum(list<Lexema> lexemas) {
    list<Lexema> :: iterator it; 
    Lexema lex;
        
    for(it = lexemas.begin(); it != lexemas.end(); ++it) {
        lex = *it;
        if (!ehPalavraReservada(lex.str)) { //É id ou Num
            if (eh_numero(lex.str[0])) {
                lex.original = lex.str;
                lex.str = "num";
                *it = lex;
            } else {
                lex.original = lex.str;
                lex.str = "id";
                *it = lex;
            }
        }
    }

    return lexemas; 
}

string getEstadoNonTerminal(int estado, string str) {
    for (int coluna = 46; coluna < COLUNAS; coluna++ )
        if (str == tableLR[0][coluna])
            return tableLR[estado + 1][coluna];
    return "false";
}

string getAcao(string str, int estado) {    
    for (int col = 1; col <= 45; col++)
        if (str == tableLR[0][col])
            return tableLR[estado][col];

    return "false";
}

bool analisadorSintatico(list<Lexema> entrada) {
    stack<string> pilha;
    string acao;
    int estado = 0;
    Lexema lexema;
    
    lexema.str = "$";
    entrada.push_back(lexema);
    pilha.push("$");
    pilha.push("0");
    
    while(!pilha.empty() && !entrada.empty()) {
        lexema = entrada.front();
        acao = getAcao(lexema.str, estado + 1);

        if (acao == "acc")
            return true;
        if ((acao == "false") || (acao == "#")) {
            cout << "Erro sintático " << lexema.linha << "." << lexema.coluna << endl;
            return false;
        }

        if (acao[0] == 's') {
            pilha.push(lexema.str);
            pilha.push(acao.substr(1));
            entrada.pop_front();
            estado = stoi(acao.substr(1));
        }

        if (acao[0] == 'r') {
            int idcRegra = stoi(acao.substr(1));
            int numDePops = (qtdRegras[idcRegra] * 2);
            for (int i = 0; i < numDePops; i++)
                pilha.pop();
            estado = stoi(pilha.top());
            pilha.push(gramatica[idcRegra]);
            string str = getEstadoNonTerminal(estado, gramatica[idcRegra]);
            if (str == "acc")
                return true;
            if (str == "false" || str == "#") {
                cout << "Erro sintático " << lexema.linha << "." << lexema.coluna << endl;
                return false;
            }
            estado = stoi(str);
            pilha.push(str);
        }
    }

    return true;
}

/* Funções do Analisador Semântico */

vector<Lexema> passarParaVector(list<Lexema> lexemas) {
    vector<Lexema> vetor;

    for (int i = 0; !lexemas.empty(); i++) {
        vetor.push_back(lexemas.front());
        lexemas.pop_front();
    }

    return vetor;
}

bool contemNaListaDeInstrucoes(string instrucao) {
    for (int i = 0; i < instrucoesDeclaradas.size(); i++) {
        if (instrucao == instrucoesDeclaradas[i]) 
            return true;
    }
    return false;
}

bool analisadorSemantico(vector<Lexema> lexemas) {
    bool flag = true;

    for(int i = 0; i < lexemas.size();i++) {
        if (i > 0 && lexemas[i - 1].str == "definainstrucao") { //Declaração de instrução
            if (contemNaListaDeInstrucoes(lexemas[i].original)) {
                cout 
                    << "Erro Semântico " << lexemas[i].linha << "." << lexemas[i].coluna 
                    << ": Instrução já declarada." << endl;
                flag = false;
            } else {
                instrucoesDeclaradas.push_back(lexemas[i].original);
            }   
        }
        if ((lexemas[i].str == "esquerda") && (lexemas[i - 1].str == "vire_para")) {
            if ((lexemas[i - 3].str == "vire_para") && (lexemas[i - 2].str == "direita")) {
                cout 
                    << "Erro Semântico " << lexemas[i].linha << "." << lexemas[i].coluna 
                    << ": Declarações de 'Vire Para' imediatamente subsequentes com sentidos diferentes." << endl;
                flag = false;
            }
            
        }
        if ((lexemas[i].str == "direita") && (lexemas[i - 1].str == "vire_para")) {
            if ((lexemas[i - 3].str == "vire_para") && (lexemas[i - 2].str == "esquerda")) {
                cout 
                    << "Erro Semântico " << lexemas[i].linha << "." << lexemas[i].coluna 
                    << ": Declarações de 'Vire Para' imediatamente subsequentes com sentidos diferentes." << endl;
                flag = false;
            }
        }
        if ((lexemas[i].str == "passos") && (lexemas[i - 1].str == "num") && 
            (lexemas[i - 2].str == "mova")) {
            if (lexemas[i + 1].str != "aguarde_ate" && lexemas[i + 2].str != "robo_pronto") {
                cout 
                    << "Erro Semântico " << lexemas[i].linha << "." << lexemas[i].coluna 
                    << ": A instrução 'Mova n Passos' deve ser precedida por 'Aguarde Ate Robo Pronto'." << endl;
                flag = false;
            }
        }
    }
    
    return flag;
}

int main() {
    char c;
    string buffer;
    palavrasReservadas = geraPalavrasReservadas();
    preencherGramatica();

    while((c = getchar()) && (c != EOF)){
        if((c >= 65) && (c <= 90))
            c += ' ';
        buffer += c;
    }
    buffer += -1;

    analisadorLexico(buffer);

    if (qtdErros == 0)
        cout << "Analise léxica concluída sem erros!" << endl;
    else {
        cout << qtdErros << " erros léxicos encotrados." << endl;
        cout << endl << "Resolva os erros léxicos para fazer a análise sintática." << endl;
        return 0;
    }
    
    list<Lexema> lexemas = pegarIdeNum(juntarPalavras());

    if (analisadorSintatico(lexemas))
        cout << "Analise sintática concluída sem erros!" << endl;
    else {
        cout << endl << "Resolva o erro sintático para fazer a análise semântica." << endl;
        return 0;
    }

    if (analisadorSemantico(passarParaVector(lexemas)))
        cout << "Analise semântica concluída sem erros!" << endl;
    else {
        cout << endl << "Resolva os erros semânticos para concluir compilação." << endl;
        return 0;
    }
    
    
    return 0;
}
