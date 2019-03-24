//Aluno: Joao Guilherme Da Costa Augustinho
//Cap 5 (Projeto de Programação 9)(Conway's Game of Life)

//=================================================================================================
#include <iostream>                              //INCLUDES
#include <fstream>
#include <cstdlib>                               //Para usar algumas funçoes (system e rand)
#include <ctime>                                 //Usado na função srand (set random)
#include <string>                                //Para trabalhar com o nome do arquivo

#ifdef _WIN32
    #include <windows.h>                         // Para sistemas Windows

    void sleep(unsigned milliseconds){           //Testado e funciona
        Sleep(milliseconds);
    }
#else
    #include <unistd.h>                         //Para sistemas Unix. Não testado
                                              
    void sleep(unsigned milliseconds){          //Não tenho certeza se vai funcionar
        usleep(milliseconds * 1000);            //Argumento em microsegundos por isso * 1000
    }
#endif
//=================================================================================================
using namespace std;
//=================================================================================================
const int LINHAS = 22;             //CONSTANTES E VARIÁVEIS
const int COLUNAS = 80;
const int BORDAS = 2;              //Bordas na Vida. Significa celulas vazias nas bordas
const int CHANCES_CELULA_VIVA = 6; // Recomendo que não seja um numero primo muito grande
const char CELULA_VIVA = '*';
const char CELULA_VAZIA = '.';
const string NOME_ARQUIVO = "mundo.txt";
const bool DELAY = true;           //Se verdadeiro a execução mostra loadings. Se faldo não mostra
//=================================================================================================
void apresentacao();											//FUNÇÕES DO PROGRAMA
void menu(char vida[][COLUNAS], char vidaEvoluida[][COLUNAS]);	//Menu
void criar_arquivo();											//Cria um arquivo com entradas rand
void ler_arquivo(char vida[][COLUNAS]);		//Le um arquivo criado ou existente
void loading(int tempo);									//Mostra carregamento
void carregar();												  //Limpa tela e mostra cabecalho
void pause();													    //Pause execução
void iniciar_jogo(char vida[][COLUNAS], char vidaEvoluida[][COLUNAS]); //Inicia instrucoes e funcoes
void nova_geracao(char vida[][COLUNAS], char vidaEvoluida[][COLUNAS]); //Gera novo vetor
void mostrar_vida(char vida[][COLUNAS]);							                 //Mostra o vetor
int num_celulas_vizinhas(char vida[][COLUNAS], int linha, int coluna);
void copiar_vida(char vida[][COLUNAS], char vidaEvoluida[][COLUNAS]);  //Copia um vetor pra outro
void limpar_tela();
//==============================================================MAIN FUNCTION=====================
int main(){
    char vida[LINHAS][COLUNAS], vidaEvoluida[LINHAS][COLUNAS];
    system("color A"); 						// Por que não. Essa vai ser melhor
    apresentacao();						    // Chama função apresentação
    carregar();
    ler_arquivo(vida);                  // Chama função ler arquivo
    copiar_vida(vidaEvoluida, vida);		// Duplica o vetor de entrada
    menu(vida, vidaEvoluida);				    // Inicia o Menu
    pause();
    return 0;
}
//=================================================================================================
void apresentacao(){
    int cond;
    cout << "============================================================" << endl;
    cout << "\tBem vindo ao Jogo da Vida de Conway" << endl;
    cout << "============================================================\n" << endl;
    cout << "Para a execucao desse programa e necessario que" << endl
         << "exista um arquivo com configucoes iniciais.\n" << endl;

    cout << "( 1 ) Eu possuo o arquivo e ele esta na raiz do programa!" << endl
         << "( 2 ) Nao tenho o arquivo e gostaria que um fosse criado!" << endl;

    cout << "\nEscolha uma das opcoes acima ( 1 ou 2 ):  ";
    cin >> cond;
    cout << endl;
    if (cond == 1) {
        cout << "\t\tOtimo! \n" << endl;
        cout << "Certifique que o nome do arquivo com as configuracoes seja:" << endl;
        cout << "\t\t'" << NOME_ARQUIVO << "'!" << endl << endl;
        pause();
    }
    else{
        cout << "As dimensoes padroes sao de " << LINHAS << " linhas e "
              << COLUNAS << " colunas." << endl << endl
              << "O nome do arquivo sera '" << NOME_ARQUIVO << "'!"
              << endl << endl
              << "Para alterar procure a parte de constantes do codigo."
              << endl << endl;
              pause();
              cout << endl;
        carregar();
        criar_arquivo(); // Chama funcao para criar o arquivo
    }
}
//=================================================================================================
void menu(char vida[][COLUNAS], char vidaEvoluida[][COLUNAS]){
    int escolha = 1;
    do{

		do{
            carregar();
            if (escolha > 5 || escolha < 1 )
                cout << "A escolha '" << escolha << "' nao e valida"
                     << endl << endl;
            cout << "Menu" << endl << endl
				 << "( 1 ) Jogar Jogo da Vida;" << endl
				 << "( 2 ) Mostrar Vida Atual;" << endl
				 << "( 3 ) Gerar Novo Arquivo;" << endl
				 << "( 4 ) Obter dados do arquivo;" << endl
				 << "( 5 ) Sair do jogo;" << endl << endl;
			cout << "Escolha uma das opcoes acima: ";
			cin  >> escolha;
            limpar_tela();                      // Chama Limpar tela
		} while(escolha > 5 || escolha < 1);

		if(escolha == 1){
            carregar();
			iniciar_jogo(vida, vidaEvoluida); // Chama Iniciar Jogo
		}
        else if(escolha == 2){
            mostrar_vida(vidaEvoluida); //Chamar Mostras Vida
            cout << "Geracao atual.\n" << endl;
            pause();
        }
        else if(escolha == 3){
            carregar();
			criar_arquivo();// Chamar Criar arquivo
        }
        else if (escolha == 4 ){
            carregar();
            ler_arquivo(vida);
            copiar_vida(vidaEvoluida, vida);
        }
		else if(escolha == 5){
            carregar();
            cout << "Ate breve quando quiser manipular a VIDA novamente!"
                 << endl << endl
                 << "\t\t\t\tAdeus Jovem Tita!" << endl << endl;
        }
	}while(escolha != 5);
}
//=================================================================================================
void limpar_tela(){
    //Testado somente Windows
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}
//=================================================================================================
void pause(){
    system("pause");
}
//=================================================================================================
void criar_arquivo(){
	fstream arquivo;
	arquivo.open(NOME_ARQUIVO, ios::out);
    if (arquivo.is_open() == false){      // Verifica se o arquivo foi criado e aberto corretamente
        cerr << "Ocorreu erro ao gerar um Arquivo!\n" << endl
             << endl
             << "Execucao encerrada" << endl << endl;
        exit(1);
    }
    srand(time(NULL) % 20);                    //Usa Set random. Tem vinte formas diferentes de criar
	for(int i =  0; i < LINHAS; i++){

		for(int j = 0; j < COLUNAS; j++){
			if ((i <= BORDAS) || (j <= BORDAS) ||
                (i >= (LINHAS - BORDAS - 1)) || j >= (COLUNAS - BORDAS - 1))
                arquivo << CELULA_VAZIA;
			else{						//Com o numero recebido verifica a chance de ele ser multiplo
                if (rand() % CHANCES_CELULA_VIVA == 0) // de "CHANCES_CELULA_VIVA"
					arquivo << CELULA_VIVA;
                else
					arquivo << CELULA_VAZIA;
			}
        }
        arquivo << endl;
	}
	arquivo.close();
    cout << "As informacoes da vida e do Mundo foram criadas!" << endl;
    cout << endl;
    pause();
}
//=================================================================================================
void carregar(){
    limpar_tela();
    cout << "============================================================" << endl;
    cout << "\tBem vindo ao Jogo da Vida de Conway" << endl;
    cout << "============================================================\n" << endl;
    for (int i = 0; i < 60; i++){
        cout << ">";
        if (DELAY) sleep(8);
    }
    cout << endl << endl;
}
void loading(int tempo){
    for (int i = 0; i < 60; i++){

        sleep(tempo);
    }
}
//=================================================================================================
void ler_arquivo(char vida[][COLUNAS]){
	fstream arquivo;
	arquivo.open(NOME_ARQUIVO, ios::in);
    if (arquivo.is_open() == false){      // Verifica se o arquivo foi criado e aberto corretamente
        cerr << "Ocorreu erro ao ler um Arquivo!\n" << endl;
        exit(1);
    }

	for(int i = 0; i < LINHAS; i++){
		for(int j = 0; j < COLUNAS; j++){
			arquivo >> vida[i][j];
		}
	}

	arquivo.close();
    cout << "Conhecimentos sobre a Vida e Mundo recebidos com sucesso!\n" << endl;
    pause();
}
//=================================================================================================
void iniciar_jogo(char vida[][COLUNAS], char vidaEvoluida[][COLUNAS]){
	int numGeracoes, escolha, tempo;
    int gen = 0;
    cout << "Voce pode dizer quantas geracoes quer avancar." << endl
         << endl << "Um numero pequeno sera muito rapido e um numero"
         << endl << "muito grande ira demorar muito.\n" << endl
         << "Quantas geracoes voce deseja evoluir ( Escolha ate 50 ): ";
	cin  >> numGeracoes;

    limpar_tela();
    carregar();
    cout << "Voce pode escolher passar as geracoes manualmente ou" << endl
         << "deixar que elas carreguem sozinhas com um loading."
         << endl << endl
         << "( 1 ) Manualmente;" << endl
         << "( 2 ) Com um loading;" << endl << endl
         << "Como prefere: ";
    cin >> escolha;
    if (escolha == 2){
        cout << endl
             << "Forneca um tempo de loading  em milisegundos para a exibicao" << endl
             << "de cada geracao. Recomendandos cerca de 10 ms." << endl << endl
             << "Qual o seu tempo: ";
        cin >> tempo;
    }
	for(; gen < numGeracoes; gen++){
        mostrar_vida(vidaEvoluida);
        cout << "Geracao: " << gen + 1 << endl << endl;
        if (escolha == 2) loading(tempo);
        else pause();
        nova_geracao(vidaEvoluida, vida);
		copiar_vida(vida, vidaEvoluida);
	}
	carregar();
	cout << "Fim da Exibicao de " << gen << " Geracoes" << endl << endl;
	pause();

}
//=================================================================================================
void nova_geracao(char novaGeracao[][COLUNAS], char antiga[][COLUNAS]){
    int vizinhos;
    for(int i = 0; i < LINHAS; i++){
        for(int j = 0; j < COLUNAS; j++){
            vizinhos = num_celulas_vizinhas(antiga, i, j);
            // Caso para nascimento de cecula
            if (vizinhos == 3 && antiga[i][j] == CELULA_VAZIA)
                novaGeracao[i][j] = CELULA_VIVA;
            // Caso para morte de célula
            else if (vizinhos < 2)
                novaGeracao[i][j] = CELULA_VAZIA;
            else if (vizinhos > 3 && antiga[i][j] == CELULA_VIVA)
                novaGeracao[i][j] = CELULA_VAZIA;
            else if (vizinhos == 3 && antiga[i][j] == CELULA_VAZIA)
                novaGeracao[i][j] = CELULA_VIVA;
            else
                novaGeracao[i][j] = antiga[i][j];
        }
    }
}
//=================================================================================================
void mostrar_vida(char vida[][COLUNAS]){
    limpar_tela();
	for(int i = 0; i < LINHAS; i++){
		for(int j = 0; j < COLUNAS; j++){
			cout << vida[i][j];
		}
		cout << endl;
    }
    cout << endl;
}
//=================================================================================================
int num_celulas_vizinhas(char vida[][COLUNAS], int linha, int coluna){
	int vizinhos = 0;

	if(vida[linha-1][coluna-1] == CELULA_VIVA)
		++vizinhos;
	if(vida[linha][coluna-1] == CELULA_VIVA)
		++vizinhos;
	if(vida[linha-1][coluna] == CELULA_VIVA)
		++vizinhos;
	if(vida[linha-1][coluna+1] == CELULA_VIVA)
		++vizinhos;
	if(vida[linha+1][coluna-1] == CELULA_VIVA)
		++vizinhos;
	if(vida[linha+1][coluna] == CELULA_VIVA)
		++vizinhos;
	if(vida[linha][coluna+1] == CELULA_VIVA)
		++vizinhos;
	if(vida[linha+1][coluna+1] == CELULA_VIVA)
		++vizinhos;

	return vizinhos;
}
//=================================================================================================
void copiar_vida(char para[][COLUNAS], char de[][COLUNAS]){
	for(int i = 0; i < LINHAS; i++){
		for(int j = 0; j < COLUNAS; j++){
			para[i][j] = de[i][j];
		}
	}
}
//=================================================================================================
