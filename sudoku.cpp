#include <iostream>
#include <locale.h>
#include <time.h>

// Ciência da Computação | UNIVALI - Itajaí
// Trabalho M3 da matéria de Algoritmos e Programação(22760), ministrada pelo professor Rafael Ballottin Martins
// Integrantes da equipe:
// João Vitor Silveira de Freitas
// Gabriel Rodrigues Leite
// Daniel Uesler de Brito
// Ismael Antonio da Silva Junior
// Novembro/2024

#define TAM 9

using namespace std;

// Matrizes globais
int matTabuleiro[TAM][TAM] = {
    {4, 9, 5, 2, 8, 7, 3, 6, 1},
    {7, 2, 8, 6, 1, 3, 4, 9, 5},
    {3, 6, 1, 9, 5, 4, 7, 2, 8},
    {6, 5, 3, 8, 4, 9, 2, 1, 7},
    {9, 8, 4, 1, 7, 2, 6, 5, 3},
    {2, 1, 7, 5, 3, 6, 9, 8, 4},
    {1, 3, 2, 4, 6, 5, 8, 7, 9},
    {5, 4, 6, 7, 9, 8, 1, 3, 2},
    {8, 7, 9, 3, 2, 1, 5, 4, 6},
};

int matGabarito[TAM][TAM]; // Matriz gerada dinamicamente
int matJogo[TAM][TAM]; // Tabuleiro do jogo (inicialmente com zeros)

void inicializarTabuleiro() {
    for (int i = 0; i < TAM; i++) {
        for (int j = 0; j < TAM; j++) {
            matJogo[i][j] = 0; // Inicializa o tabuleiro com zeros (vazio)
        }
    }
}

void gerarGabarito(int matGabarito[TAM][TAM], int matTabuleiro[TAM][TAM]) {
    int numeroAleatorio = rand() % 4 + 1; // Escolhe um número aleatório de 1 a 4

    // Gerar uma das 4 variações do gabarito
    switch (numeroAleatorio) {
        case 1: // Sem modificação
            for (int i = 0; i < TAM; i++) {
                for (int j = 0; j < TAM; j++) {
                    matGabarito[i][j] = matTabuleiro[i][j];
                }
            }
            break;
        case 2: // Transposta
            for (int i = 0; i < TAM; i++) {
                for (int j = 0; j < TAM; j++) {
                    matGabarito[i][j] = matTabuleiro[j][i];
                }
            }
            break;
        case 3: // Invertida por linha
            for (int i = 0; i < TAM; i++) {
                for (int j = 0; j < TAM; j++) {
                    matGabarito[i][j] = matTabuleiro[TAM - i - 1][j];
                }
            }
            break;
        case 4: // Invertida por coluna
            for (int i = 0; i < TAM; i++) {
                for (int j = 0; j < TAM; j++) {
                    matGabarito[i][j] = matTabuleiro[i][TAM - j - 1];
                }
            }
            break;
    }
}

void exibirTabuleiro(int matJogo[TAM][TAM]) {
    for (int i = 0; i < TAM; i++) {
        for (int j = 0; j < TAM; j++) {
            if (matJogo[i][j] == 0)
                cout << "- "; // Mostrar "-" para células vazias
            else
                cout << matJogo[i][j] << " ";
        }
        cout << endl;
    }
}

// Função para controlar o jogo
void jogar() {
    int vidas = 3, tentativas = 0, linJogo, colJogo, numJogo;
    int sortPos = 0;

    inicializarTabuleiro();
    gerarGabarito(matGabarito, matTabuleiro);

    while (sortPos < 41) { // Sorteia 41 posições para preencher inicialmente
        int i = rand() % TAM;
        int j = rand() % TAM;
        if (matJogo[i][j] == 0) {
            matJogo[i][j] = matGabarito[i][j];
            sortPos++;
        }
    }

    while (vidas > 0) {
        system("cls");  // Limpa a tela

        cout << "Tentativas: " << tentativas << " | Vidas restantes: " << vidas << endl;
        exibirTabuleiro(matJogo);

        cout << "Escolha a linha (1 a 9): ";
        cin >> linJogo;
        cout << "Escolha a coluna (1 a 9): ";
        cin >> colJogo;
        cout << "Escolha o número (1 a 9): ";
        cin >> numJogo;

        if (linJogo >= 1 && linJogo <= 9 && colJogo >= 1 && colJogo <= 9 && numJogo >= 1 && numJogo <= 9) {
            linJogo--; colJogo--; // Ajuste para índices de 0 a 8

            if (matJogo[linJogo][colJogo] == 0) {
                tentativas++;
                if (matGabarito[linJogo][colJogo] == numJogo) {
                    matJogo[linJogo][colJogo] = numJogo;
                    cout << "Você acertou! Boa jogada!" << endl;
                } else {
                    vidas--;
                    cout << "Erro! O número está errado. Vidas restantes: " << vidas << endl;
                }
            } else {
                cout << "Essa posição já está preenchida. Tente outra!" << endl;
            }
        } else {
            cout << "Entrada inválida! Por favor, insira valores entre 1 e 9." << endl;
        }

        if (tentativas == 81 || vidas == 0) break;
    }

    system("cls"); // Limpa a tela

    if (vidas > 0) {
        cout << "Parabéns, você venceu! Tentativas: " << tentativas << " | Vidas restantes: " << vidas << endl;
    } else {
        cout << "Você perdeu! Tentativas realizadas: " << tentativas << endl;
    }
    system("pause");
}

int main() {
    srand(time(NULL)); // Inicializa a semente do número aleatório
    setlocale(LC_ALL, "Portuguese");

    int opcao;

    do {
        cout << "===== SUDOKU: O DESAFIO DOS DESAFIOS =====" << endl;
        cout << "1 - Iniciar Desafio" << endl;
        cout << "2 - Sobre o Projeto" << endl;
        cout << "3 - Encerrar Jogo" << endl;
        cout << "Escolha sua próxima jogada: ";
        cin >> opcao;

        switch (opcao) {
            case 1: // JOGAR
                system("cls");

                // Gerar o gabarito do Sudoku
                gerarGabarito(matGabarito, matTabuleiro);
                cout << "Prepare-se! Sua mente será desafiada. Vamos ver se você consegue vencer este quebra-cabeça." << endl;
                jogar();
                break;
            case 2: // SOBRE
                system("cls");
                cout << "Este jogo de Sudoku foi desenvolvido com o objetivo de estudar e aprimorar habilidades em C++." << endl;
                cout << "Equipe de desenvolvimento:" << endl;
                cout << "- João Vitor Silveira Freitas." << endl << endl;
                cout << "- Gabriel Rodrigues Leite." << endl;
                cout << "- Daniel Uesler de Brito." << endl;
                cout << "- Ismael Antonio da Silva Junior." << endl;
                cout << "Professor/Disciplina:" << endl;
                cout << "- Rafael Ballottin Martins/Algoritmos e Programação." << endl;
                cout << "Novembro/2024." << endl << endl;
                system("pause");
                system("cls");
                break;
            case 3: // SAIR
                system("cls");
                cout << "O jogo está sendo encerrado. Até a próxima, campeão!" << endl;
                system("pause");
                break;
            default:
                cout << "Escolha inválida! Tente novamente, a aventura não acabou!" << endl;
                system("cls");
        }
    } while (opcao != 3);

    return 0;
}