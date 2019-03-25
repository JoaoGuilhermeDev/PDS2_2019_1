#include <iostream>
#include <cmath>

using namespace std;

double leitura(int cond);
double libra_grama(double valor);
double onca_grama(double valor);
void imprimir(double valor, double valorOut, int cond);

int main(){

    int cond = 1;
    double valorIn, valorOut;
    while(true){
        cout << "============================================" << endl << endl;
        cout << "Qual Medida deseja converter" << endl;
        cout << "( 1 ) Onca \t( 0 ) Libra \t Escolha: ";
        cin >> cond;
        cout << endl;
        valorIn = leitura(cond);
        if (cond == 1){
            valorOut = onca_grama(valorIn);
        }
        else {
            valorOut = libra_grama(valorIn);
        }
        imprimir(valorIn, valorOut, cond);
        cout << "Deseja realizar outro calculo?" << endl;
        cout << endl;
        cout << "( 1 ) Sim \t( 0 ) Nao \t Escolha: ";
        cin >> cond;
        cout << endl;
        if (cond == 0) {
            break;
        }
    }

    return 0;
}

double leitura(int cond){
    double valor;
    cout << "Digite a quantidade de ";
    if (cond == 1) cout << "Onca(s): ";
    else cout << "Libra(s): ";
    cin >> valor;
    cout << endl;
    return valor;

}

double libra_grama(double valor){
    return valor * 453.59;
}

double onca_grama(double valor){
    return valor * 28.34;
}

void imprimir(double valor, double valorOut, int tipoEntrada){
    double grama, kiloGrama, mil = 1000;

    grama = fmod(valorOut, 1000);
    kiloGrama = ((valorOut - grama) / 1000);

    cout << "O valor de " << valor;
    if (tipoEntrada == 1) {
        cout << " Onca(s) = ";
    }
    else{
        cout << " Libra(s) = ";
    }
    if (kiloGrama > 0) {
        cout << kiloGrama << " Kg " << grama << " gramas." << endl;
    }
    else{
        cout << grama << " gramas." << endl;
    }
    cout << endl << "============================================" << endl;
    cout << endl;
}
