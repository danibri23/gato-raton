#include <iostream>
#include <vector>

using namespace std;


void imprimir () {

    vector<string> direcciones = {
        "Norte",
        "Sur",
        "Este",
        "Oeste"
    };
    
    for (const auto& dir : direcciones) {
        cout << dir << endl;
    }
}


int main () {

    cout << "Bienvenido al juego del gato (Tom 🐈) y el ratón (Jerry 🐁)" << endl;

    imprimir();

    return 0;
}