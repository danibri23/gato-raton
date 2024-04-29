/*
Veamos el estado del juego anterior

                                   O |   | X
                                   ---------
                                   X |   | X
                                   ---------
                                     | O | O

                             //       ||        \\

                O | X | X          O |   | X        O |   | X
                ---------          ---------        ---------
                X |   | X          X | X | X        X |   | X
                ---------          ---------        ---------
                  | O | O            | O | O        X | O | O

              //          \\                     //          \\

        O | X | X          O | X | X        O | O | X       O |   | X
        ---------          ---------        ---------       ---------
        X | O | X          X |   | X        X |   | X       X | O | X
        ---------          ---------        ---------       ---------
          | O | O          O | O | O        X | O | O       X | O | O

                                        //

                                   O | O | X
                                   ---------
                                   X | X | X
                                   ---------
                                   O | O | O

*/
// Humano
var huPlayer = "O";
// IA
var aiPlayer = "X";

// Este es el tablero aplanado y llenado con algunos valores para facilitar la evaluación de la inteligencia artificial.
// var origBoard = ["O", "X", "X", "X", "O", "X", "X", "O", "O"];
var origBoard = [1, 2, 3, 4, 5, 6, 7, 8, 9];

// Lleva un conteo de las llamadas a la función
var fc = 0;

// Encontrar el mejor movimiento en el juego que favorezca a la computadora
var bestSpot = minimax(origBoard, aiPlayer);

// Registrar los resultados
console.log("Índice: " + bestSpot.index);
console.log("Llamadas a la función: " + fc);

// La función minimax principal
function minimax(newBoard, player) {
  // Aumentar en uno las llamadas a la función
  fc++;

  // Espacios disponibles
  var availSpots = emptyIndexies(newBoard);

  // Comprobar los estados terminales como ganar, perder y empate y devolver un valor en consecuencia
  if (winning(newBoard, huPlayer)) {
    return { score: -10 };
  } else if (winning(newBoard, aiPlayer)) {
    return { score: 10 };
  } else if (availSpots.length === 0) {
    return { score: 0 };
  }

  // Un array para recopilar todos los objetos
  var moves = [];

  // Iterar sobre los espacios disponibles
  for (var i = 0; i < availSpots.length; i++) {
    // Crear un objeto para cada uno y almacenar el índice de ese espacio que se almacenó como un número en la clave de índice del objeto
    var move = {};
    move.index = newBoard[availSpots[i]];

    // Establecer el espacio vacío al jugador actual
    newBoard[availSpots[i]] = player;

    // Si recopilar la puntuación resultante de llamar a minimax en el oponente del jugador actual
    if (player == aiPlayer) {
      var result = minimax(newBoard, huPlayer);
      move.score = result.score;
    } else {
      var result = minimax(newBoard, aiPlayer);
      move.score = result.score;
    }

    // Restablecer el espacio a vacío
    newBoard[availSpots[i]] = move.index;

    // Añadir el objeto al array
    moves.push(move);
  }

  // Si es el turno de la computadora, recorrer los movimientos y elegir el movimiento con la puntuación más alta
  var bestMove;
  if (player === aiPlayer) {
    var bestScore = -10000;
    for (var i = 0; i < moves.length; i++) {
      if (moves[i].score > bestScore) {
        bestScore = moves[i].score;
        bestMove = i;
      }
    }
  } else {
    // Si no, recorrer los movimientos y elegir el movimiento con la puntuación más baja
    var bestScore = 10000;
    for (var i = 0; i < moves.length; i++) {
      if (moves[i].score < bestScore) {
        bestScore = moves[i].score;
        bestMove = i;
      }
    }
  }

  // Devolver el movimiento elegido (objeto) del array a la profundidad superior
  return moves[bestMove];
}

// Devuelve los espacios disponibles en el tablero
function emptyIndexies(board) {
  return board.filter((s) => s != "O" && s != "X");
}

// Combinaciones ganadoras usando los índices del tablero, por ejemplo, la primera victoria podría ser 3 equis seguidos
function winning(board, player) {
  if (
    (board[0] == player && board[1] == player && board[2] == player) ||
    (board[3] == player && board[4] == player && board[5] == player) ||
    (board[6] == player && board[7] == player && board[8] == player) ||
    (board[0] == player && board[3] == player && board[6] == player) ||
    (board[1] == player && board[4] == player && board[7] == player) ||
    (board[2] == player && board[5] == player && board[8] == player) ||
    (board[0] == player && board[4] == player && board[8] == player) ||
    (board[2] == player && board[4] == player && board[6] == player)
  ) {
    return true;
  } else {
    return false;
  }
}
