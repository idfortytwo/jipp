#include <iostream>
using namespace std;

int main(int argc, char *argv[]) {
    char* masa_ciala = (char*) malloc(sizeof(char));
    char* wzrost = (char*) malloc(sizeof(char));

    cout << "masa ciała [kg]: ";
    cin >> masa_ciala;

    cout << "wzrost [m]: ";
    cin >> wzrost;

    double bmi = atof(masa_ciala) / (atof(wzrost) * atof(wzrost));
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