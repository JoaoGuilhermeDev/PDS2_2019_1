#include <iostream>

using namespace std;
int main()
{
    //variaveis
    int numHoraTrabalhada, numDependentes;
    double valorHoraTrabalhada = 16.78, custoPrevidencia = 0.06, impostoRenda = 0.14,
           impostoEstadual = 0.05, multiplicadorHoraExtra = 1.5, custoDependente = 35,
           custoSindicato = 10, salarioBruto, salarioLiquido;

    //Informacoes sobre a precisao
    cout.setf(ios::fixed);
    cout.setf(ios::showpoint);
    cout.precision(2);

    cout << "###################################################" << endl;
    cout << endl;
    cout << "Quanto terei de salario?" << endl;
    cout << endl;
    cout << "Horas trabalhadas na semana: ";
    cin >> numHoraTrabalhada;
    cout << endl;
    cout << "Numero de dependentes: ";
    cin >> numDependentes;
    cout << endl;

    //Soma do salário
    if (numHoraTrabalhada > 44) {
        salarioBruto = 44 * valorHoraTrabalhada;
        salarioBruto += (valorHoraTrabalhada * multiplicadorHoraExtra) * (numHoraTrabalhada - 44);
    }

    else
    {
        salarioBruto = numHoraTrabalhada * valorHoraTrabalhada;
    }

    //Descontos
    salarioLiquido = salarioBruto;
    salarioLiquido -= salarioBruto * custoPrevidencia;
    salarioLiquido -= salarioBruto * impostoRenda;
    salarioLiquido -= salarioBruto * impostoEstadual;
    salarioLiquido -= custoSindicato;
    if (numDependentes >= 3){
        salarioLiquido -= custoDependente;
    }

    cout << "###################################################" << endl;
    cout << endl;
    cout << "Salario Bruto na Semana: " << salarioBruto << endl;
    cout << endl;
    cout << "Descontos:" << endl;
    cout << endl;
    cout << "Previdencia: " << salarioBruto * custoPrevidencia << endl;
    cout << "Imposto de Renda: " << salarioBruto * impostoRenda << endl;
    cout << "Imposto Estadual: " << salarioBruto * impostoEstadual << endl;
    cout << "Contribuicao Sindical: " << custoSindicato << endl;
    if (numDependentes >= 3) {
        cout << "Plano de Saude: " << custoDependente << endl;
    }
    cout << endl;
    cout << "Salario Liquido na Semana: " << salarioLiquido << endl;
    cout << endl;
    cout << "###################################################" << endl;

    return 0;
}
