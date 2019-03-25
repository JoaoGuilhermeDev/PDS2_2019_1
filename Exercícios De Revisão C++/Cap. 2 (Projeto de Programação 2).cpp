#include <iostream>

using namespace std;

int main()
{
    //Variaveis
    int numMeses = 0;
    double valorPrincipal = 1000, valorTotal, valorRestante, valorJuroMensal,
           valorJuroTotal = 0, valorPagar, taxaJuroMensal = 0.015;

    //Informacoes sobre a precisao
    cout.setf(ios::fixed);
    cout.setf(ios::showpoint);
    cout.precision(2);

    valorRestante = valorPrincipal;

    //Iteração
    while(valorRestante > 0){
        //Incrementa o Mes
        numMeses++;
        //Calculo das Variaveis
        valorJuroMensal = valorRestante * taxaJuroMensal;
        valorPagar = 50 - valorJuroMensal;
        valorJuroTotal += valorJuroMensal;

        //Condicional para divida maior que parcela mensal
         if (valorRestante >= 50) {
             valorRestante -= valorPagar;
         }
        //Condicional para quitar a dívida
        else if (valorPagar > valorRestante){
            cout << "Divida Quitada no Mes " << numMeses << endl;
            cout << "Valor em Juros: " << valorJuroMensal << endl;
            cout << "Valor a pagar e R$ " << valorPagar << " e valor restante R$ " << valorRestante << endl;
            cout << "Sobrou R$ " << valorPagar - valorRestante << " na ultima parcela." << endl;
            cout << endl;
            valorRestante = 0;
            break;
        }
        else{
            valorRestante -= valorPagar;
        }

        cout << "Mes: " << numMeses << endl;
        cout << "Valor em Juros: " << valorJuroMensal << endl;
        cout << "Valor a Pagar: " << valorPagar << endl;
        cout << "Valor Restante: " << valorRestante << endl;
        cout << endl;
    }

    valorTotal = valorJuroTotal + valorPrincipal;
    cout << "Valor total foi de R$ " << valorTotal << " pago em " << numMeses << " meses." << endl;
    cout << endl;

    return 0;
}