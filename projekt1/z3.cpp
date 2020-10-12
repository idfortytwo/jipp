#include <iostream>
using namespace std;

int main(int argc, char *argv[]) {
    double masa_ciala;
    double wzrost;

    cout << "masa ciała [kg]: ";
    cin >> masa_ciala;
    cout << "wzrost [m]: ";
    cin >> wzrost;

    // obliczenie bmi
    double bmi = masa_ciala / (wzrost * wzrost);

    // printowanie w zależności od wartości bmi
    cout << "bmi: " << bmi << " - ";
    if (bmi < 16)        cout << "wygłodzenie";
    else if (bmi < 17)   cout << "wychudzenie";
    else if (bmi < 18.5) cout << "niedowaga";
    else if (bmi < 25)   cout << "wartość prawidłowa";
    else if (bmi < 30)   cout << "nadwaga";
    else if (bmi < 35)   cout << "I stopień otyłości";
    else if (bmi < 40)   cout << "II stopień otyłości";
    else if (bmi >= 40)  cout << "otyłość skrajna";    

    return 0;
}