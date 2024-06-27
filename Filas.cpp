#include <iostream>
#include <locale.h>
using namespace std;
//Eduardo Miranda 

struct No {
    int senha;
    No* prox;
};

struct senhasGeradas {
    No* ini;
    No* fim;
};

senhasGeradas* init() {
    senhasGeradas* s = new senhasGeradas;
    s->ini = NULL;
    s->fim = NULL;
    return s;
}

int isEmpty(senhasGeradas* s) {
    return (s->ini == NULL);
}

void enqueue(senhasGeradas* s, int v) {
    No* no = new No;
    no->senha = v;
    no->prox = NULL;
    if (isEmpty(s)) {
        s->ini = no;
    } else {
        s->fim->prox = no;
    }
    s->fim = no;
}

int dequeue(senhasGeradas* s) {
    int ret;
    if (isEmpty(s)) {
        ret = -1;
    } else {
        No* no = s->ini;
        ret = no->senha;
        s->ini = no->prox;
        if (s->ini == NULL) {
            s->fim = NULL;
        }
        delete no;
    }
    return ret;
}

int count(senhasGeradas* s) {
    int qtde = 0;
    No* no;
    no = s->ini;
    while (no != NULL) {
        qtde++;
        no = no->prox;
    }
    return qtde;
}

void print(senhasGeradas* s) {
    No* no;
    no = s->ini;
    cout << "-- Senhas aguardando atendimento: " << count(s) << endl;
    while (no != NULL) {
        cout << no->senha << endl;
        no = no->prox;
    }
}

void freeFila(senhasGeradas* s) {
    No* no = s->ini;
    while (no != NULL) {
        No* temp = no->prox;
        delete no;
        no = temp;
    }
    delete s;
}

int main(int argc, char** argv)
{
	setlocale(LC_ALL, "");
	
    senhasGeradas* senha = init();
    senhasGeradas* senhasAtendidas = init();
    int controle_senhas = 0;
    int opcao;

    while (true) {
        cout << "\nOpções:" << endl;
        cout << "0. Sair" << endl;
        cout << "1. Gerar senha" << endl;
        cout << "2. Realizar atendimento" << endl;
        cout << "Senhas aguardando atendimento: " << count(senha) << endl;
        cout << "Escolha uma opção: ";
        cin >> opcao;
        cout << endl;

        switch (opcao) {
            case 0:
                if (isEmpty(senha)) {
                    cout << "Encerrando sistema. Total de senhas atendidas: " << count(senhasAtendidas) << endl;
                    freeFila(senha);
                    freeFila(senhasAtendidas);
                    return 0;
                } else {
                    cout << "Ainda há senhas aguardando atendimento. Não é possível encerrar o sistema." << endl;
                }
                break;
            case 1:
                controle_senhas++;
                enqueue(senha, controle_senhas);
                cout << "Senha " << controle_senhas << " gerada e enfileirada." << endl;
                
                break;
            case 2:
                if (!isEmpty(senha)) {
                    int senha_da_vez = dequeue(senha);
                    enqueue(senhasAtendidas, senha_da_vez);
                    cout << "Atendendo senha: " << senha_da_vez << endl;
                } else {
                    cout << "Não há senhas aguardando atendimento." << endl;
                    
                }
                break;
            default:
                cout << "Opção inválida! Tente novamente." << endl;
                break;
        }
    }

    return 0;
}
