#include <iostream>
#include <locale.h>
#include <time.h>

#define TAM 9

// Ciência da Computação | UNIVALI - Itajaí
// Trabalho M3 da matéria de Algoritmos e Programação(22760), ministrada pelo professor Rafael Ballottin Martins
// Integrantes da equipe:
// João Vitor Silveira de Freitas
// Gabriel Rodrigues Leite
// Daniel Uesler de Brito
// Ismael Antonio da Silva Junior
// Novembro/2024

using namespace std;

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
        cout << "Escolha sua próxima ação: ";
        cin >> opcaoJogo;

        switch(opcaoJogo) {
            case 1: // JOGAR
                sortPos = 0;
                vidas = 3;
                tentativas = 0;
                numeroAleatorio = (rand() % 4) + 1;
                system("cls");
                for(i=0; i<TAM; i++) {
                    for(j=0; j<TAM; j++) {
                        matJogo[i][j] = 0;
                    }
                }
                switch(numeroAleatorio) { // Define o Gabarito
                    case 1: // Sem modificação
                        for(i=0; i<TAM; i++) {
                            for(j=0; j<TAM; j++) {
                                matGabarito[i][j] = matPrincipal[i][j];
                            }
                        }
                        break;
                    case 2: // Transposta
                        for(i=0; i<TAM; i++) {
                            for(j=0; j<TAM; j++) {
                                matGabarito[i][j] = matPrincipal[j][i];
                            }
                        }
                        break;
                    case 3: // Invertida por linha
                        for(i=0; i<TAM; i++) {
                            for(j=0; j<TAM; j++) {
                                matGabarito[i][j] = matPrincipal[TAM-i-1][j];
                            }
                        }
                        break;
                    case 4: // Invertida por coluna
                        for(i=0; i<TAM; i++) {
                            for(j=0; j<TAM; j++) {
                                matGabarito[i][j] = matPrincipal[i][TAM-j-1];
                            }
                        }
                        break;
                }

                while(sortPos < 41) { // Sorteia 41 posições diferentes para pré-preencher
                    i = rand() % 9;
                    j = rand() % 9;
                    if(matJogo[i][j] == 0) {
                        matJogo[i][j] = matGabarito[i][j];
                        sortPos++;
                    }
                }
                for(i=0; i<TAM; i++) {
                    cout<<"| ";
                    for(j=0; j<TAM; j++) {
                        if(matJogo[i][j] == 0) {
                            	cout<<"-"<<" | ";
                            } else {
                            	cout<<matJogo[i][j]<<" | ";
                        	}
                    }
                    cout<<endl;
                }
                while(!((tentativas == 40 && vidas == 3) || (tentativas == 41 && vidas == 2) || (tentativas == 42 && vidas == 1) || vidas == 0)) {
                    cout<<"Insira as coordenas para jogar (1 a 9)"<<endl;
                    cout<<"Linha: ";
                    cin>>linJogo;
                    if(linJogo <= 9 && linJogo > 0) {
                        linJogo -= 1;
                        cout<<"Coluna: ";
                        cin>>colJogo;
                        if(colJogo <= 9 && colJogo > 0) {
                                colJogo -= 1;
                                if(matJogo[linJogo][colJogo] == 0) {
                                        cout<<"Insira um número de 1 a 9: ";
                                        cin>>numJogo;
                                        if(numJogo > 0 && numJogo <= 9) {
                                            tentativas++;
                                            if(matGabarito[linJogo][colJogo] == numJogo) {
                                                matJogo[linJogo][colJogo] = numJogo;
                                                system("cls");
                                                cout<<"Número Correto. "<<vidas<<" vidas restantes. ("<<tentativas<<" tentativas)"<<endl;
                                            } else {
                                                system("cls");
                                                vidas--;
                                                cout<<"Número Errado. "<<vidas<<" vidas restantes. ("<<tentativas<<" tentativas)"<<endl;
                                            }
                                        } else {
                                            system("cls");
                                            cout<<"Insira um número válido (entre 1 e 9)"<<endl;
                                        }
                                } else {
                                    system("cls");
                                    cout<<"Essa posição já está preenchida! Tente outra."<<endl;
                                }
                        } else {
                            system("cls");
                            cout<<"Número inválido! Insira um valor entre 1 e 9 para Coluna."<<endl;
                        }
                    } else {
                        system("cls");
                        cout<<"Número inválido! Digite um valor entre 1 e 9 para Linha."<<endl;
                    }
                    for(i=0; i<TAM; i++) {
                        cout<<"| ";
                        for(j=0; j<TAM; j++) {
                            if(matJogo[i][j] == 0) {
                            	cout<<"-"<<" | ";
                            } else {
                            	cout<<matJogo[i][j]<<" | ";
                        	}
                        }
                        cout<<endl;
                    }
                }
                system("cls");
                if(vidas > 0) {
                    cout<<"Parabéns! Você completou o Sudoku! Com "<<tentativas<<" tentativas e "<<vidas<<" vidas restantes."<<endl;
                } else {
                    cout<<"Game over! Você perdeu todas as vidas, com "<<tentativas<<" tentativas."<<endl;
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
                cout << "Opção inválida. Por gentileza tente novamente." << endl;
        }
    } while(opcaoJogo != 3);

    return 0;
}
