/*
* Não sei o que aconteceu, mas parece que a fórmula do exercício está errada.
* Para alguns valores o Indice é menor que a temperatura informada.
* Tente 2 m/s e 10 Cº. O resultado seria aproximadamente 9.6.
*
*   Formula aplicada
*
*   frioDoVento =  13.12 + (0.6215 * temperatura) - (11.37 * pow(velocidadeVento, 0.16))
*                  + (0.3965 * temperatura * pow(velocidadeVento, 0.016));
*
*/
#include <iostream>
#include <cmath>

using namespace std;

double frio_do_vento(double temperatura, double velocidadeVento);

int main(){
    //Main Function
    double temperatura, velocidadeVento, indice;
    cout << "Calculo do Wind Chill (Indice de Frio do Vento)" << endl;
    cout << endl;
    cout << "Forneca a Velocidade(m\s) do Vento: ";
    cin >> velocidadeVento;
    cout << "Forneca a Temperatura(Celsius) do ar: ";
    cin >> temperatura;
    cout << endl;

    indice = frio_do_vento(temperatura, velocidadeVento);
    cout << "O Indice de Frio do Vento para os valores informados e: "
         <<  indice << " Celsius" << endl;

    return 0;
}

double frio_do_vento(double temperatura, double velocidadeVento){
    /*
    *Usada para calcular o Wind Chil (Temperatura sentida em dias frios em relacao a velocidade do vento)
    *Parametros: temperatura (double) <= 10;
    *            velocidadeVento (double);
    */
    double frioDoVento, velocidadePow;
    if (temperatura > 10){
        cout << "O Indice sera definido apenas para temperaturas maiores que 10 graus.";
        cout << endl;
        exit(1);
    }
    else{

        frioDoVento =  13.12 + (0.6215 * temperatura) - (11.37 * pow(velocidadeVento, 0.16))
                       + (0.3965 * temperatura * pow(velocidadeVento, 0.016));
    }
    return frioDoVento;
}