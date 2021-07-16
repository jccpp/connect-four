#include <algorithm>
#include <iomanip>
#include <iostream>
#include <limits>

/**
 * Imprime el jugador de turno.
 */
void printPlayer(const int);

/**
 * Imprime el tablero con las fichas de cada jugador.
 * @param board Es el tablero de juego.
 */
template <size_t rows, size_t cols>
void printBoard(const int (&)[rows][cols]);

template <int rows, int cols>
bool isWinner(const int, const int, const int, const int (&)[rows][cols]);

/**
 * Lee el número de la fila, donde el jugador de turno
 * quiere introducir su ficha.
 */
void readColumn(const int, int &, const int[]);

/**
 *  Código ANSI para el color rojo(para jugador 1).
 */
const char COLOR_RED[] = "\033[38;5;124m";

/**
 *  Código ANSI para el color azul(para jugador 2).
 */
const char COLOR_PURPLE[] = "\033[38;5;27m";

/**
 *  Para imprimir la ficha del jugador 1 (rojo) --> 'R'.
 */
const char TOKEN_RED[] = "\033[38;5;124m R \033[0m";

/**
 *  Para imprimir la ficha del jugador 2 (azul) --> 'A'.
 */
const char TOKEN_PURPLE[] = "\033[38;5;27m A \033[0m";

int main(int argc, char *argv[]) {

    int player = 0;
    int turns = 1; // Para controlar la cantidad la cantidad de turnos.
    int winner = false;
    int board[6][7];
    int colsTop[7] = {5, 5, 5, 5, 5, 5, 5};
    for (auto &rows : board) {
        for (int &e : rows) {
            e = -1;
        }
    }

    do {
        int col = 0;
        printPlayer(player);
        printBoard(board);
        readColumn(player, col, colsTop);
        board[colsTop[col]][col] = player;

        // TODO: Verificar si hay ganador y finalizar el juego.
        if ((winner = isWinner(player, colsTop[col], col, board))) {
            std::cout << "  ¡¡¡Ganador!!!" << std::endl;
            break;
        }

        std::cout << std::endl;
        player = (player + 1) % 2;
        colsTop[col]--;
    } while (turns++ <= 21 * 2); // Cada jugador dispone de 21 fichas.

    // TODO: Indicar que fue un empate.
    if (!winner) {
        std::cout << "¡¡¡EMPATE!!!" << std::endl;
    }
}

void printPlayer(const int player) {
    system("clear");
    std::cout.fill('=');
    std::cout << std::setw(24) << '\0' << std::endl;
    std::cout << (player == 0 ? COLOR_RED : COLOR_PURPLE);
    std::cout << "  Turno -> Jugador " << (player) + 1 << std::endl;
    std::cout << "\033[0m";
}

void readColumn(const int player, int &col, const int colsTop[]) {
    std::cout << (player == 0 ? COLOR_RED : COLOR_PURPLE);
    std::cout << "Columna: ";
    std::cin >> col;
    while (std::cin.fail() || col < 1 || col > 7 || colsTop[col - 1] < 0) {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "\033[13;1H"
                  << "\033[2K"
                  << "\033[J";
        std::cout << "Columna: ";
        std::cin >> col;
    };
    std::cout << "\033[0m";
    col -= 1;
}

template <size_t rows, size_t cols>
void printBoard(const int (&board)[rows][cols]) {
    std::cout << std::endl;
    for (size_t r = 0; r < rows; r++) {
        for (size_t c = 0; c < cols; c++) {
            std::cout << (c == 0 ? '[' : '\0');
            std::cout << (board[r][c] == -1 ? " • " : (board[r][c] == 0 ? TOKEN_RED : TOKEN_PURPLE));
            std::cout << (c == cols - 1 ? ']' : '\0');
        }
        std::cout << std::endl;
    }
    std::cout.fill('-');
    std::cout << std::setw(24) << '\0' << std::endl
              << " ";
    for (size_t c = 0; c < cols; c++) {
        std::cout << " " << (c + 1) << " ";
    }
    std::cout << std::endl
              << std::endl;
}

template <int rows, int cols>
bool isWinner(const int player, const int row, const int col, const int (&board)[rows][cols]) {
    // Revisa la fila
    int startCol = std::max(0, col - 3);
    int endCol = std::min(cols - 1, col + 3);

    for (int i = startCol; i <= endCol; i++) {
        int count = 0;
        for (int j = 0; j < 4 && j <= endCol; j++) {
            (board[row][i + j] == player) ? count++ : j = 4;
        }
        if (count == 4) {
            return true;
        }
    }

    // Revisa la columna
    int startRow = std::max(0, row - 3);
    int endRow = std::min(rows - 1, row + 3);
    for (int i = startRow; i <= endRow; i++) {
        int count = 0;
        for (int j = 0; j < 4 && j <= endRow; j++) {
            (board[i + j][col] == player) ? count++ : j = 4;
        }
        if (count == 4) {
            return true;
        }
    }

    // Revisa diagonal 1

    // Revisa diagonal 2

    return false;
}