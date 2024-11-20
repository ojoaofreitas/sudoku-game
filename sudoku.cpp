#include <iostream>
#include <locale.h>
#include <time.h>

#define TAM 9

using namespace std;

// Ciência da Computação | UNIVALI - Itajaí
// Trabalho M3 da matéria de Algoritmos e Programação(22760), ministrada pelo professor Rafael Ballottin Martins
// Integrantes da equipe:
// João Vitor Silveira de Freitas
// Gabriel Rodrigues Leite
// Daniel Uesler de Brito
// Ismael Antonio da Silva Junior
// Novembro/2024

int main() {
    int opcaoJogo, numeroAleatorio, sortPos, i, j, linJogo, colJogo, numJogo, tentativas, vidas = 3, matJogo[TAM][TAM], matGabarito[TAM][TAM], matPrincipal[TAM][TAM] = {
        {4, 9, 5, 2, 8, 7, 3, 6, 1},
        {7, 2, 8, 6, 1, 3, 4, 9, 5},
        {3, 6, 1, 9, 5, 4, 7, 2, 8},
        {6, 5, 3, 8, 4, 9, 2, 1, 7},
        {9, 8, 4, 1, 7, 2, 6, 5, 3},
        {2, 1, 7, 5, 3, 6, 9, 8, 4},
        {1, 3, 2, 4, 6, 5, 8, 7, 9},
        {5, 4, 6, 7, 9, 8, 1, 3, 2},
        {8, 7, 9, 3, 2, 1, 5, 4, 6}
    };

    srand(time(NULL));
    setlocale(LC_ALL, "Portuguese");

    do {
        cout << "===== SUDOKU: O DESAFIO DOS DESAFIOS =====" << endl;
        cout << "1 - Iniciar Desafio" << endl;
        cout << "2 - Sobre o Projeto" << endl;
        cout << "3 - Encerrar Jogo" << endl;
        cout << "Escolha sua próxima jogada: ";
        cin >> opcaoJogo;

        switch(opcaoJogo) {
            case 1: // JOGAR
                sortPos = 0;
                vidas = 3;
                tentativas = 0;
                numeroAleatorio = (rand() % 4) + 1;
                system("cls");

                // Inicializa o tabuleiro com zeros
                for(i = 0; i < TAM; i++) {
                    for(j = 0; j < TAM; j++) {
                        matJogo[i][j] = 0;
                    }
                }

                // Define o gabarito com base na modificação aleatória
                for(i = 0; i < TAM; i++) {
                    for(j = 0; j < TAM; j++) {
                        if (numeroAleatorio == 1) {
                            matGabarito[i][j] = matPrincipal[i][j];  // Sem modificação
                        } else if (numeroAleatorio == 2) {
                            matGabarito[i][j] = matPrincipal[j][i];  // Transposta
                        } else if (numeroAleatorio == 3) {
                            matGabarito[i][j] = matPrincipal[TAM - i - 1][j];  // Invertida por linha
                        } else if (numeroAleatorio == 4) {
                            matGabarito[i][j] = matPrincipal[i][TAM - j - 1];  // Invertida por coluna
                        }
                    }
                }

                // Sorteia 41 posições para preencher no tabuleiro
                while(sortPos < 41) {
                    i = rand() % 9;
                    j = rand() % 9;
                    if(matJogo[i][j] == 0) {
                        matJogo[i][j] = matGabarito[i][j];
                        sortPos++;
                    }
                }

                // Exibe o tabuleiro inicial
                cout << "Tabuleiro inicial:" << endl;
                for(i = 0; i < TAM; i++) {
                    cout << "| ";
                    for(j = 0; j < TAM; j++) {
                        cout << (matJogo[i][j] == 0 ? "-" : to_string(matJogo[i][j])) << " | ";
                    }
                    cout << endl;
                }

                // Loop principal do jogo
                while(!(tentativas == 42 || vidas == 0)) {
                    cout << "\nDigite a linha e a coluna (1 a 9) para preencher!" << endl;
                    cout << "Linha (1-9): ";
                    cin >> linJogo;
                    linJogo--;  // Ajuste para o índice começar de 0
                    cout << "Coluna (1-9): ";
                    cin >> colJogo;
                    colJogo--;  // Ajuste para o índice começar de 0

                    // Verifica a validade da entrada
                    if(linJogo >= 0 && linJogo < TAM && colJogo >= 0 && colJogo < TAM) {
                        if(matJogo[linJogo][colJogo] == 0) {
                            cout << "Digite um número entre 1 e 9: ";
                            cin >> numJogo;
                            if(numJogo >= 1 && numJogo <= 9) {
                                tentativas++;
                                if(matGabarito[linJogo][colJogo] == numJogo) {
                                    matJogo[linJogo][colJogo] = numJogo;
                                    system("cls");
                                    cout << "Número correto! " << vidas << " vidas restantes." << endl;
                                } else {
                                    vidas--;
                                    system("cls");
                                    cout << "Número errado! " << vidas << " vidas restantes." << endl;
                                }
                            } else {
                                system("cls");
                                cout << "Número inválido! Insira um valor entre 1 e 9." << endl;
                            }
                        } else {
                            system("cls");
                            cout << "Essa posição já está preenchida! Tente outra." << endl;
                        }
                    } else {
                        system("cls");
                        cout << "Coordenadas inválidas! Digite um valor entre 1 e 9." << endl;
                    }

                    // Exibe o tabuleiro após cada jogada
                    cout << "Tabuleiro atual:" << endl;
                    for(i = 0; i < TAM; i++) {
                        cout << "| ";
                        for(j = 0; j < TAM; j++) {
                            cout << (matJogo[i][j] == 0 ? "-" : to_string(matJogo[i][j])) << " | ";
                        }
                        cout << endl;
                    }

                    // Verifica se o jogo terminou
                    if(tentativas == 42 && vidas > 0) {
                        system("cls");
                        cout << "Parabéns! Você completou o Sudoku!" << endl;
                    } else if(vidas == 0) {
                        system("cls");
                        cout << "Game over! Você perdeu todas as vidas." << endl;
                    }
                }
                system("pause");
                system("cls");
                break;

            case 2: // SOBRE
                system("cls");
                cout << "Este jogo de Sudoku foi desenvolvido com o objetivo de estudar e aprimorar habilidades em C++." << endl;
                cout << "Equipe de desenvolvimento:" << endl;
                cout << "- João Vitor Silveira Freitas." << endl;
                cout << "- Gabriel Rodrigues Leite." << endl;
                cout << "- Daniel Uesler de Brito." << endl;
                cout << "- Ismael Antonio da Silva Junior." << endl;
                cout << "Professor/Disciplina:" << endl;
                cout << "- Rafael Ballottin Martins/Algoritmos e Programação." << endl;
                cout << "Novembro/2024." << endl << endl;
                system("pause");
                break;

            case 3: // SAIR
                system("cls");
                cout << "Encerrando o programa..." << endl;
                break;

            default:
                system("cls");
                cout << "Opção inválida! Tente novamente." << endl;
        }
    } while(opcaoJogo != 3);

    return 0;
}
