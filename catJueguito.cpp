#include <iostream>
#include <map>
#include <cmath>
#include <cstdlib>
using namespace std;
// VARIABLES
const string raton = "\033[1;31mR\033[0m";
const string gato = "\033[1;34mG\033[0m";
// TABLERO
map<int, string> tablero = {
    {1, " "}, {2, " "}, {3, " "}, {4, " "}, {5, " "},
    {6, " "}, {7, " "}, {8, " "}, {9, " "}, {10, " "},
    {11, " "}, {12, " "}, {13, " "}, {14, " "}, {15, " "},
    {16, " "}, {17, " "}, {18, " "}, {19, " "}, {20, " "},
    {21, " "}, {22, " "}, {23, " "}, {24, " "}, {25, " "}
};

// funcion que imprime el tablero
void generarLaberinto(map<int, string> tablero){
    cout << "\n";
    cout << "# # # # # # # # # # # # # # # #\n";
    cout << "#  " << tablero[1] << "  #  " << tablero[2] << "  #  " << tablero[3] << "  #  " << tablero[4] << "  #  " << tablero[5] << "  #\n";
    cout << "# # # # # # # # # # # # # # # #\n";
    cout << "#  " << tablero[6] << "  #  " << tablero[7] << "  #  " << tablero[8] << "  #  " << tablero[9] << "  #  " << tablero[10] << "  # S\n";
    cout << "# # # # # # # # # # # # # # # #\n";
    cout << "#  " << tablero[11] << "  #  " << tablero[12] << "  #  " << tablero[13] << "  #  " << tablero[14] << "  #  " << tablero[15] << "  #\n";
    cout << "# # # # # # # # # # # # # # # #\n";
    cout << "#  " << tablero[16] << "  #  " << tablero[17] << "  #  " << tablero[18] << "  #  " << tablero[19] << "  #  " << tablero[20] << "  #\n";
    cout << "# # # # # # # # # # # # # # # #\n";
    cout << "#  " << tablero[21] << "  #  " << tablero[22] << "  #  " << tablero[23] << "  #  " << tablero[24] << "  #  " << tablero[25] << "  # E\n";
    cout << "# # # # # # # # # # # # # # # #\n";
    cout << "\n";
}
// funcion que verifica si una casilla esta libre
bool espacioL(int posicion){
    return tablero[posicion] == " ";
}
// funcion para colocar al gato o al raton en la casilla
void posicionGatoRaton(int posicion, string jugador){
    if(espacioL(posicion)){
        tablero[posicion] = jugador;
    }
}
// funcion para la primera posicion del jugador
int movimientoInicial(){
    generarLaberinto(tablero);
    int posicion;
    cout << "Elija una casilla del 21 al 25\nRespuesta: ";
    cin >> posicion;
    while (!(posicion >= 21 && posicion <= 25)){
        cout << "Opción no válida, elija una casilla del 21 al 25\nRespuesta: ";
        cin >> posicion;
    }
    posicionGatoRaton(posicion, raton);
    return posicion;
}
// funcion que calcula segun tu posicion previa tu nueva ubicacion y que no te saltes columnas
int nuevaPosicion(int posicion, int direccion){
    if(direccion == 1){
        return posicion - 5;
    } else if(direccion == 2){
        return posicion + 5;
    } else if(direccion == 3){
        if(posicion % 5 == 1){
            return posicion;
        }
        return posicion - 1;
    } else if(direccion == 4){
        if(posicion % 5 == 0){
            return posicion;
        }
        return posicion + 1;
    } else{
        cout << "Opción no válida";
        return posicion;
    }
}
// funcion para calcular las distancias de los jugadores
int calcularDistancia(int posicion_gato, int posicion_raton){
    int fila_gato = (posicion_gato - 1) / 5;
    int columna_gato = (posicion_gato - 1) % 5;
    int fila_raton = (posicion_raton - 1) / 5;
    int columna_raton = (posicion_raton - 1) % 5;
    int diferencia_filas = abs(fila_gato - fila_raton);
    int diferencia_columnas = abs(columna_gato - columna_raton);
    return diferencia_filas + diferencia_columnas;
}
// funcion que verifica si el movimiento se puede realizar.
bool movimientoValido(int posicion){
    return posicion >= 1 && posicion <= 25 && (espacioL(posicion) || tablero[posicion] == raton);
}
// función que verifica si el ratón ha ganado (llegado a la meta)
bool ratonGana(int posicion_raton){
    return posicion_raton == 10;
}
// funcion que determina la mejor posicion incial para el gato.
int posicionInicioGato(){
    // se inicializa con infinito para poder minimizar despues la evaluacion y con -1 para asegurar que cualquier posicion valida en el tablero va a ser mejor que el valor inicial
    float mejor_evaluacion = INFINITY;
    int mejor_posicion = -1;
    // recorre las cinco casillas donde puede empezar.
    for(int posicion = 1; posicion <= 5; posicion++){
        float maximizar = -INFINITY;
        // recorre en todas las direcciones
        for(int direccion = 1; direccion <= 4; direccion++){
            // clacula la nueva direccion
            int nueva_posicion = nuevaPosicion(posicion, direccion);
            if(movimientoValido(nueva_posicion)){
                // si la condicion es verdadera,calcula la distancia entre el gato y el raton.
                float evaluacion = static_cast<float>(calcularDistancia(posicion, nueva_posicion));
                maximizar = max(maximizar, evaluacion);
            }
        }
        if(maximizar < mejor_evaluacion){
            // actualiza la mejor evaluacion y su mejor posicion.
            mejor_evaluacion = maximizar;
            mejor_posicion = posicion;
        }
    }
    return mejor_posicion;
}
// funcion que determina la posicion del jugador cada vez que realiza un movimiento.
void determinarPosicion(int &posicion_raton){
    cout << "Te encuentras en la posición " << posicion_raton << ". En qué dirección quieres ir?\n";
    cout << "Seleccione una de las siguientes opciones:\n";
    cout << " - w si desea ir arriba\n";
    cout << " - s si desea ir abajo\n";
    cout << " - a si desea ir izquierda\n";
    cout << " - d si desea ir derecha\n";
    cout << "Respuesta: ";
    char mover;
    cin >> mover;
    int nueva_posicion;
    switch(mover) {
        case 'w':
            nueva_posicion = nuevaPosicion(posicion_raton, 1);
            break;
        case 's':
            nueva_posicion = nuevaPosicion(posicion_raton, 2);
            break;
        case 'a':
            nueva_posicion = nuevaPosicion(posicion_raton, 3);
            break;
        case 'd':
            nueva_posicion = nuevaPosicion(posicion_raton, 4);
            break;
        default:
            cout << "Movimiento no válido. Intenta de nuevo.\n";
            determinarPosicion(posicion_raton);
            return;
    }
    if(movimientoValido(nueva_posicion)){
        tablero[posicion_raton] = ' ';
        tablero[nueva_posicion] = raton;
        posicion_raton = nueva_posicion; // Actualiza la posición del ratón
        if(ratonGana(nueva_posicion)){
            generarLaberinto(tablero);
            cout << "¡Felicidades! ¡Has ganado!";
            exit(0);  // Terminar el juego
        }
    } else{
        cout << "Movimiento no válido. Intenta de nuevo.\n";
        determinarPosicion(posicion_raton);
        return;
    }
}
// Nueva función de evaluación para minimax
float minimaxEvaluacion(int posicion_gato, int posicion_raton) {
    // Calcular distancia al ratón
    int distancia_raton = calcularDistancia(posicion_gato, posicion_raton);
    // Calcular distancia a la casilla 5
    int distancia_a_casilla5 = abs((posicion_gato - 1) / 5 - 4);
    // Ponderar distancias (puedes ajustar los pesos según lo desees)
    return distancia_raton - 2 * distancia_a_casilla5;
}
// Función que determina el movimiento del gato
int movimientoGato(int posicion_gato, int posicion_raton) {
    // Verificar si el ratón está cerca de la casilla 5
    if (posicion_raton >= 21 && posicion_raton <= 25) {
        // Priorizar bloquear la casilla 5
        for (int direccion = 1; direccion <= 4; direccion++) {
            int nueva_posicion = nuevaPosicion(posicion_gato, direccion);
            if (movimientoValido(nueva_posicion) && nueva_posicion == 5) {
                return direccion; // Bloquear la casilla 5
            }
        }
    }
    // De lo contrario, utilizar el algoritmo minimax con la nueva función de evaluación
    float mejor_evaluacion = INFINITY;
    int mejor_movimiento = -1;
    for(int direccion = 1; direccion <= 4; direccion++){
        int nueva_posicion = nuevaPosicion(posicion_gato, direccion);
        if(movimientoValido(nueva_posicion)){
            float evaluacion = minimaxEvaluacion(nueva_posicion, posicion_raton);
            if(evaluacion < mejor_evaluacion){
                mejor_evaluacion = evaluacion;
                mejor_movimiento = direccion;
            }
        }
    }
    return mejor_movimiento;
}
// función que usaría cuando se ejecute el juego para que la PC pueda jugar, también analiza si se le atrapó al jugador.
int turnoGato(int posicion_gato, int &posicion_raton){
    int direccion = movimientoGato(posicion_gato, posicion_raton);
    int nueva_posicion = nuevaPosicion(posicion_gato, direccion);
    if(movimientoValido(nueva_posicion)){
        if(nueva_posicion == posicion_raton){
            cout << "¡El gato ha atrapado al ratón!\n¡Has perdido! :'(";
            exit(0);
        } else{
            tablero[posicion_gato] = ' ';
            tablero[nueva_posicion] = gato;
            return nueva_posicion;
        }
    } else{
        cout << "Movimiento no válido. El gato se queda en su posición."; // Se agrega un mensaje de advertencia
        return posicion_gato;
    }
    return posicion_gato;
}
int main(){
    int posicion_gato = posicionInicioGato();
    posicionGatoRaton(posicion_gato, gato);
    generarLaberinto(tablero);
    int posicion_raton = movimientoInicial();
    generarLaberinto(tablero);
    // El juego
    while (true){
        posicion_gato = turnoGato(posicion_gato, posicion_raton);
        generarLaberinto(tablero);
        determinarPosicion(posicion_raton);
        generarLaberinto(tablero);
        if(ratonGana(posicion_raton)){
            generarLaberinto(tablero);
            cout << "¡Felicidades! ¡Has ganado!";
            break;
        }
    }
    return 0;
}

