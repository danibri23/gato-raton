#include <iostream>
#include <vector>

using namespace std;

int dataObtenido;

enum Casilla {
    VACIA,
    PERSONA,
    IA,
};

vector<Casilla> tablero(9, VACIA);

void generarTablero() {
    cout << "Tablero:\n";
    for (int i = 0; i < 9; ++i) {
        if (i % 3 == 0 && i != 0)
            cout << "\n---------\n";
        cout << (tablero[i] == VACIA ? " " : tablero[i] == PERSONA ? "X" : "O");
        if (i % 3 != 2)
            cout << " | ";
    }
    cout << endl;
}

// Función para convertir la entrada del usuario en coordenadas válidas para el tablero
pair<int, int> convertirEntrada(string entrada) {
    int fila = entrada[0] - 'a'; // Convertir la letra en un índice de fila (0-2)
    int columna = entrada[1] - '1'; // Convertir el número en un índice de columna (0-2)
    return make_pair(fila, columna);
}

// Función minimax
struct Movimiento {
    int indice;
    int puntuacion;
};

Movimiento minimax(vector<Casilla> nuevoTablero, Casilla jugador);

bool tablaGanadora(const vector<Casilla>& tablero, Casilla jugador);

vector<int> emptyIndexies(const vector<Casilla>& tablero);

Movimiento minimax(vector<Casilla> nuevoTablero, Casilla jugador) {

    // Espacios disponibles
    vector<int> availSpots = emptyIndexies(nuevoTablero);

    // Comprobar los estados terminales como ganar, perder y empate y devolver un valor en consecuencia
    if (tablaGanadora(nuevoTablero, jugador)) {
        if (jugador == IA) {
            return { -1, -10 };
        } else {
            return { -1, 10 };
        }
    } else if (availSpots.size() == 0) {
        return { -1, 0 };
    }

    // Un vector para recopilar todos los movimientos
    vector<Movimiento> movimientos;

    // Iterar sobre los espacios disponibles
    for (int i = 0; i < availSpots.size(); ++i) {
        // Crear un objeto para cada movimiento y almacenar el índice de ese espacio
        Movimiento movimiento;
        movimiento.indice = availSpots[i];

        // Establecer el espacio vacío al jugador actual
        nuevoTablero[availSpots[i]] = jugador;

        // Recopilar la puntuación resultante de llamar a minimax en el oponente del jugador actual
        if (jugador == PERSONA) {
            movimiento.puntuacion = minimax(nuevoTablero, IA).puntuacion;
        } else {
            movimiento.puntuacion = minimax(nuevoTablero, PERSONA).puntuacion;
        }

        // Restablecer el espacio a vacío
        nuevoTablero[availSpots[i]] = VACIA;

        // Añadir el movimiento al vector
        movimientos.push_back(movimiento);
    }

    // Si es el turno de la computadora, elegir el movimiento con la puntuación más alta
    if (jugador == PERSONA) {
        int mejorPuntuacion = -10000;
        int mejorMovimientoIndice = -1;
        for (int i = 0; i < movimientos.size(); ++i) {
            if (movimientos[i].puntuacion > mejorPuntuacion) {
                mejorPuntuacion = movimientos[i].puntuacion;
                mejorMovimientoIndice = i;
            }
        }
        return movimientos[mejorMovimientoIndice];
    } else {
        // Si no, elegir el movimiento con la puntuación más baja
        int mejorPuntuacion = 10000;
        int mejorMovimientoIndice = -1;
        for (int i = 0; i < movimientos.size(); ++i) {
            if (movimientos[i].puntuacion < mejorPuntuacion) {
                mejorPuntuacion = movimientos[i].puntuacion;
                mejorMovimientoIndice = i;
            }
        }
        return movimientos[mejorMovimientoIndice];
    }
}

bool tablaGanadora(const vector<Casilla>& tablero, Casilla jugador) {
    // Verificar todas las combinaciones posibles para ganar el juego
    return 
        (tablero[0] == jugador && tablero[1] == jugador && tablero[2] == jugador) ||
        (tablero[3] == jugador && tablero[4] == jugador && tablero[5] == jugador) ||
        (tablero[6] == jugador && tablero[7] == jugador && tablero[8] == jugador) ||
        (tablero[0] == jugador && tablero[3] == jugador && tablero[6] == jugador) ||
        (tablero[1] == jugador && tablero[4] == jugador && tablero[7] == jugador) ||
        (tablero[2] == jugador && tablero[5] == jugador && tablero[8] == jugador) ||
        (tablero[0] == jugador && tablero[4] == jugador && tablero[8] == jugador) ||
        (tablero[2] == jugador && tablero[4] == jugador && tablero[6] == jugador);
}


// Función para devolver los espacios disponibles en el tablero
vector<int> emptyIndexies(const vector<Casilla>& tablero) {
    vector<int> espaciosDisponibles;
    for (int i = 0; i < tablero.size(); ++i) {
        if (tablero[i] == VACIA) {
            espaciosDisponibles.push_back(i);
        }
    }
    return espaciosDisponibles;
}



int main() {
    cout << "Bienvenido al juego del PERSONA (Tom 🐈) y el ratón (Jerry 🐁)" << endl;

    cout << "Introduce uno (1) para comenzar: "; 
    cin >> dataObtenido;

    if (dataObtenido == 1) {
        bool juegoActivo = true;

        while (juegoActivo) {
            cout << "Introduce la fila y la columna (Ejemplo: a2): ";
            string entrada;
            cin >> entrada;

            // Convertir la entrada del usuario en coordenadas válidas para el tablero
            pair<int, int> coordenadas = convertirEntrada(entrada);

            // Verificar si la posición está ocupada
            int indice = coordenadas.first * 3 + coordenadas.second;
            if (tablero[indice] != VACIA) {
                cout << "¡Esa posición ya está ocupada! Intenta de nuevo.\n";
                continue;  // Volver al principio del bucle para solicitar una nueva entrada
            }

            // Actualizar el tablero con la marca "X" en las coordenadas especificadas
            tablero[indice] = PERSONA;
            cout << "¡El jugador PERSONA ha realizado su movimiento!" << endl;

            // Generar y mostrar el tablero actualizado
            generarTablero();

            // Verificar si hay un ganador
            if (tablaGanadora(tablero, PERSONA)) {
                cout << "¡El jugador PERSONA ha ganado!" << endl;
                juegoActivo = false;
            }

            // Verificar si no hay más movimientos disponibles
            bool tableroLleno = true;
            for (int i = 0; i < tablero.size(); ++i) {
                if (tablero[i] == VACIA) {
                    tableroLleno = false;
                    break;
                }
            }
            if (tableroLleno) {
                cout << "¡El juego ha terminado en empate!" << endl;
                juegoActivo = false;
            }

            // Si el juego no ha terminado, es el turno de la IA
            if (juegoActivo) {
                Movimiento movimientoIA = minimax(tablero, IA);
                tablero[movimientoIA.indice] = IA;
                cout << "¡La IA ha realizado su movimiento!" << endl;
                generarTablero();

                // Verificar si hay un ganador después del movimiento de la IA
                if (tablaGanadora(tablero, IA)) {
                    cout << "¡La IA ha ganado!" << endl;
                    juegoActivo = false;
                }

                // Verificar si no hay más movimientos disponibles después del movimiento de la IA
                tableroLleno = true;
                for (int i = 0; i < tablero.size(); ++i) {
                    if (tablero[i] == VACIA) {
                        tableroLleno = false;
                        break;
                    }
                }
                if (tableroLleno) {
                    cout << "¡El juego ha terminado en empate!" << endl;
                    juegoActivo = false;
                }
            }
        }
    } else {
        cout << "Hasta luego" << endl;
    }

    return 0;
}
