#ifndef CCHESS_RULES_H
#define CCHESS_RULES_H

#include "cchess_rules_global.h"
//#include "genmove.h"
#include <QDebug>
#include <QObject>
#include "types.h"
#include <iostream>
#include <ostream>
#include <vector>

class CCHESS_RULES_EXPORT Cchess_rules
{
public:
    Cchess_rules();
};
/*
class CCHESS_RULES_EXPORT GenMove : public QObject
{
    Q_OBJECT
public:
    GenMove() {}
    GenMove(QObject *parent = nullptr) {}
    // Copy-Konstruktor
    GenMove(const GenMove &other);
    GenMove(const Piece p[ROWS][COLS], color onMove);
    GenMove &operator=(const GenMove &other)
    {
        copyBoard(this->pieces, other.pieces);
        this->playerOnMove = other.playerOnMove;
        return *this;
    }

    ~GenMove() {}
    // Array der Spielsteine kopieren
    void copyBoard(Piece pieces[ROWS][COLS], const Piece other[ROWS][COLS]);

    bool IsValidPosition(int row, int col);
    bool IsVacantOrOpponent(int row, int col, color color);
    bool IsValidSoldierMove(QPoint from, QPoint to, color color);
    bool IsValidCannonMove(QPoint from, QPoint to, color color);
    bool IsValidHorseMove(QPoint from, QPoint to, color color);
    bool IsValidElephantMove(QPoint from, QPoint to, color color);
    bool IsValidAdvisorMove(QPoint from, QPoint to, color color);
    bool IsValidGeneralMove(QPoint from, QPoint to, color color);
    bool IsValidChariotMove(QPoint from, QPoint to, color color);

    std::vector<std::pair<QPoint, QPoint>> GenerateLegalMoves(color currentPlayerColor);
    bool IsCheck(color currentPlayerColor);
    bool IsCheckmate(color currentPlayerColor);
    bool IsEvilGlare(color color);
    //bool isStaleMate(Color currentPlayerColor);
    bool PerformMove(QPoint from, QPoint to, color currentPlayerColor);
    color GetColor(QPoint p);
    Piece GetPiece(QPoint p);
    QPoint FindGeneralPosition(color currentPlayerColor);
    void PlacePiece(int row, int col, pieceType type, color color);

    // Gibt zurück, ob ein Zug gülig ist
    bool IsValidMove(QPoint from, QPoint to, color currentPlayerColor);
    std::vector<std::pair<QPoint, QPoint>> AllValidMoves(const QPoint from);

    Piece pieces[ROWS][COLS];
    color playerOnMove;
};
*/
enum class Color { Red, Black };

enum class PieceType {
    General,
    Advisor,
    Elephant,
    Horse,
    Chariot,
    Cannon,
    Soldier
};
class CCHESS_RULES_EXPORT Position {

public:
    struct PPiece {
        PieceType piece_type;
        Color color;
    };

    struct Square
    {
        PPiece *piece;
    };
    Square board[10][9];

    Color players_color;



    Position() {
        for (int rank = 0; rank < 10; ++rank) {
            for (int file = 0; file < 9; ++file) {
                board[rank][file].piece = nullptr;
            }
        }
    }

    Position(Piece p[ROWS][COLS], color c) {
        if (c == color::Black)
            players_color = Color::Black;
        else
            players_color = Color::Red;

        for (int rank = 0; rank < 10; ++rank) {
            for (int file = 0; file < 9; ++file) {

                switch (p[rank][file].type) {
                case pieceType::Advisor:
                    board[rank][file].piece = new PPiece();
                    board[rank][file].piece->piece_type = PieceType::Advisor;
                    break;
                case pieceType::Cannon:
                    board[rank][file].piece = new PPiece();
                    board[rank][file].piece->piece_type = PieceType::Cannon;
                    break;
                case pieceType::Chariot:
                    board[rank][file].piece = new PPiece();
                    board[rank][file].piece->piece_type = PieceType::Chariot;
                    break;
                case pieceType::Elephant:
                    board[rank][file].piece = new PPiece();
                    board[rank][file].piece->piece_type = PieceType::Elephant;
                    break;
                case pieceType::General:
                    board[rank][file].piece = new PPiece();
                    board[rank][file].piece->piece_type = PieceType::General;
                    break;
                case pieceType::Horse:
                  board[rank][file].piece = new PPiece();
                  board[rank][file].piece->piece_type = PieceType::Horse;
                  break;
                case pieceType::Soldier:
                    board[rank][file].piece = new PPiece();
                    board[rank][file].piece->piece_type = PieceType::Soldier;
                    break;
                case pieceType::Empty:
                    board[rank][file].piece = new PPiece();
                    board[rank][file].piece = nullptr;
                    break;
                default:
                    break;
                }

            switch (p[rank][file].colr) {
                case color::Black:
                if (!(board[rank][file].piece == nullptr))
                    board[rank][file].piece->color = Color::Black;
                break;
                case color::Red:
                    if (!(board[rank][file].piece == nullptr))
                    board[rank][file].piece->color = Color::Red;
                    break;
            default:
                break;
            }
        }
        }
    }

    void initBoard()
    {
        for (int rank = 0; rank < 10; ++rank) {
            for (int file = 0; file < 9; ++file) {
                board[rank][file].piece = nullptr;
            }
        }

        // Adding red pieces
        add_piece(new PPiece{ PieceType::Chariot, Color::Red }, 0, 0);
        add_piece(new PPiece{ PieceType::Chariot, Color::Red }, 8, 0);
        add_piece(new PPiece{ PieceType::Horse, Color::Red }, 1, 0);
        add_piece(new PPiece{ PieceType::Horse, Color::Red }, 7, 0);
        add_piece(new PPiece{ PieceType::Elephant, Color::Red }, 2, 0);
        add_piece(new PPiece{ PieceType::Elephant, Color::Red }, 6, 0);
        add_piece(new PPiece{ PieceType::Advisor, Color::Red }, 3, 0);
        add_piece(new PPiece{ PieceType::Advisor, Color::Red }, 5, 0);
        add_piece(new PPiece{ PieceType::General, Color::Red }, 4, 0);
        add_piece(new PPiece{ PieceType::Cannon, Color::Red }, 1, 2);
        add_piece(new PPiece{ PieceType::Cannon, Color::Red }, 7, 2);
        for (int i = 0; i < 9; i = i + 2) {
            add_piece(new PPiece{ PieceType::Soldier, Color::Red }, i, 3);
        }

        // Adding black pieces
        add_piece(new PPiece{ PieceType::Chariot, Color::Black }, 0, 9);
        add_piece(new PPiece{ PieceType::Chariot, Color::Black }, 8, 9);
        add_piece(new PPiece{ PieceType::Horse, Color::Black }, 1, 9);
        add_piece(new PPiece{ PieceType::Horse, Color::Black }, 7, 9);
        add_piece(new PPiece{ PieceType::Elephant, Color::Black }, 2, 9);
        add_piece(new PPiece{ PieceType::Elephant, Color::Black }, 6, 9);
        add_piece(new PPiece{ PieceType::Advisor, Color::Black }, 3, 9);
        add_piece(new PPiece{ PieceType::Advisor, Color::Black }, 5, 9);
        add_piece(new PPiece{ PieceType::General, Color::Black }, 4, 9);
        add_piece(new PPiece{ PieceType::Cannon, Color::Black }, 1, 7);
        add_piece(new PPiece{ PieceType::Cannon, Color::Black }, 7, 7);
        for (int i = 0; i < 9; i = i + 2) {
            add_piece(new PPiece{ PieceType::Soldier, Color::Black }, i, 6);
        }
    }

    bool is_inside_board(int file, int rank) const {
        return file >= 0 && file < 9 && rank >= 0 && rank < 10;
    }

    void add_piece(PPiece* piece, int file, int rank) {
        if (is_inside_board(file, rank)) {
            board[rank][file].piece = piece;
        }
    }

    std::vector<std::pair<int, int>> generate_piece_moves(
        PieceType piece_type, int file, int rank) const {
        std::vector<std::pair<int, int>> moves;

        switch (piece_type) {
        case PieceType::General:
            generate_general_moves(file, rank, moves);
            break;
        case PieceType::Advisor:
            generate_advisor_moves(file, rank, moves);
            break;
        case PieceType::Elephant:
            generate_elephant_moves(file, rank, moves);
            break;
        case PieceType::Horse:
            generate_horse_moves(file, rank, moves);
            break;
        case PieceType::Chariot:
            generate_chariot_moves(file, rank, moves);
            break;
        case PieceType::Cannon:
            generate_cannon_moves(file, rank, moves);
            break;
        case PieceType::Soldier:
            generate_soldier_moves(file, rank, moves);
            break;
        default:
            break;
        }
        return moves;
    }

    std::vector<std::pair<QPoint, QPoint>> generate_all_moves()
    {
        std::vector<std::pair<int, int>> moves;
        std::vector<std::pair<int, int>> all_moves_to;
        std::vector<std::pair<int, int>> all_moves_from;
        std::vector<std::pair<QPoint, QPoint>> all_moves;


        // find all possible moves
        for (int file1 = 0; file1 < 9; file1++) {
            for (int rank1 = 0; rank1 < 10; rank1++) {
                if (board[rank1][file1].piece != nullptr)
                    if (board[rank1][file1].piece->color == players_color
                        && is_inside_board(file1, rank1)) {
                        PieceType piece_type = board[rank1][file1].piece->piece_type;
                        moves = generate_piece_moves(piece_type, file1, rank1);
                        for (auto m : moves) {
                            all_moves.push_back(std::make_pair(QPoint(file1, rank1),QPoint(m.first,m.second)));
                        }
                    }
            }
        }
        return all_moves;
    }

    bool is_check(Color color) const
    {
        int general_file = -1;
        int general_rank = -1;

        // Find the position of the general
        for (int rank = 0; rank < 10; ++rank) {
            for (int file = 0; file < 9; ++file) {
                PPiece *piece = board[rank][file].piece;
                if (piece != nullptr && piece->piece_type == PieceType::General
                    && piece->color == color) {
                    general_file = file;
                    general_rank = rank;
                    break;
                }
            }
            if (general_file != -1 && general_rank != -1) {
                break;
            }
        }

        // Check if the opponent's pieces can attack the general
        for (int rank = 0; rank < 10; ++rank) {
            for (int file = 0; file < 9; ++file) {
                PPiece *piece = board[rank][file].piece;
                if (piece != nullptr && piece->color != color) {
                    std::vector<std::pair<int, int>> moves = generate_piece_moves(piece->piece_type,
                                                                                  file,
                                                                                  rank);
                    int i = 0;
                    for (const auto &move : moves) {
                        if (move.first == general_file && move.second == general_rank) {
                            return true;
                        }
                    }
                }
            }
        }

        return false;
    }

    bool is_checkmate(Color color, std::vector<std::pair<int, int>> &moves)
    {
        // Check if the general is in check
        //if (!is_check(color)) {
        //	return false;
        //}

        // Try moving each of the player's pieces to see if the check can be escaped
        //   for (int rank = 0; rank < 10; ++rank) {
        //       for (int file = 0; file < 9; ++file) {
        //           Piece *piece = board[rank][file].piece;
        //           if (piece != nullptr && piece->color == color) {
        //               //std::vector<std::pair<int, int>> moves = generate_piece_moves(piece->piece_type, file, rank);
        //               for (const auto &move : moves) {
        //                   // Try the move
        //                   Piece *captured_piece = board[move.second][move.first].piece;
        //                   board[move.second][move.first].piece = piece;
        //                   board[rank][file].piece = nullptr;

        //                   // Check if the check is still present
        //                   bool is_still_check = is_check(color);

        //                   // Undo the move
        // board[rank][file].piece = piece;
        // board[move.second][move.first].piece = captured_piece;

        // if (!is_still_check) {
        // 	// The check can be escaped
        // 	return false;
        // }
        //               }
        //           }
        //       }
        //   }

        // All possible moves have been checked and the general is still in check
        // Checkmate!
        return true;
    }

    bool is_evil_glare(Color color) const
    {
        std::cout << "info is_evil_glase()" << std::endl;

        int general_file = -1;
        int general_rank = -1;
        int opp_general_file = -1;
        int opp_general_rank = -1;
        PPiece* general = nullptr;
        PPiece* opp_general = nullptr;

        Color opp_color;

        // Find the position of the general
        for (int rank = 0; rank < 10; ++rank) {
            for (int file = 0; file < 9; ++file) {
                PPiece* piece = board[rank][file].piece;
                if (piece != nullptr && piece->piece_type == PieceType::General && piece->color == color) {
                    general_file = file;
                    general_rank = rank;
                    break;
                }
            }
            if (general_file != -1 && general_rank != -1) {
                break;
            }

        }
        if (general_file != -1 && general_rank != -1) {
            general = board[general_rank][general_file].piece;
        }
        else
            std::cout << "info error in is_evil_glare" << std::endl;

        // if (color == Color::Red)
        // 	opp_color = Color::Black;
        // else
        // 	opp_color = Color::Red;

        // Find the position of the opposite general
        for (int rank = 0; rank < 10; ++rank) {
            for (int file = 0; file < 9; ++file) {
                PPiece* piece = board[rank][file].piece;
                if (piece != nullptr && piece->piece_type == PieceType::General
                    && piece->color != color) {
                    opp_general_file = file;
                    opp_general_rank = rank;
                    break;
                }
            }
            if (opp_general_file != -1 && opp_general_rank != -1) {
                break;
            }

        }
        if (opp_general_file != -1 && opp_general_rank != -1) {
            opp_general = board[opp_general_rank][opp_general_file].piece;
        }
        else
            std::cout << "info error in is_evil_glare" << std::endl;

        std::cout << opp_general_file << general_file << std::endl;
        std::cout << opp_general_rank << general_rank << std::endl;

        if (opp_general_file == general_file) {
            if (opp_general_rank < general_rank) {
                for (size_t i = opp_general_rank + 1; i < general_rank; i++) {
                    std::cout << i << general_file << std::endl;
                    if (board[i][general_file].piece != nullptr) {
                        return false;
                    }
                }
            } else {
                for (size_t i = general_rank + 1; i < opp_general_rank; i++) {
                    std::cout << i << general_file << std::endl;
                    if (board[i][opp_general_file].piece != nullptr) {
                        return false;
                    }
                }
            }
        }
        return true;
    }

private:
    void add_move(int file, int rank, std::vector<std::pair<int, int>>& moves) const {
        if (is_inside_board(file, rank)) {
            PPiece *piece = board[rank][file].piece;
            if (piece == nullptr || piece->color != board[rank][file].piece->color
                || !is_evil_glare(board[rank][file].piece->color)
                /*|| !is_check(board[rank][file].piece->color)*/) {
                moves.push_back(std::make_pair(file, rank));
            }
        }
    }

    void generate_general_moves(int file, int rank, std::vector<std::pair<int, int>> &moves) const
    {
        int directions[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
        for (const auto &dir : directions) {
            add_move(file + dir[0], rank + dir[1], moves);
        }
    }

    void generate_advisor_moves(int file, int rank, std::vector<std::pair<int, int>> &moves) const
    {
        int directions[4][2] = {{-1, -1}, {1, 1}, {1, -1}, {-1, 1}};
        for (const auto &dir : directions) {
            PPiece *piece = board[rank][file].piece;
            if ((file + dir[0] >= 0 && file + dir[0] <= 2) && rank + dir[1] >= 3
                && rank + dir[1] <= 5 && piece->color == Color::Red)
                add_move(file + dir[0], rank + dir[1], moves);
            if ((file + dir[0] >= 7 && file + dir[0] <= 9) && rank + dir[1] >= 3
                && rank + dir[1] <= 5 && piece->color == Color::Black)
                add_move(file + dir[0], rank + dir[1], moves);
        }
    }

    void generate_elephant_moves(int file, int rank, std::vector<std::pair<int, int>> &moves) const
    {
        int directions[4][2] = {{-2, -2}, {2, 2}, {2, -2}, {-2, 2}};
        int between_directions[4][2] = {{-1, -1}, {1, 1}, {1, -1}, {-1, 1}};
        for (int i = 0; i < 4; ++i) {
            int new_file = file + directions[i][0];
            int new_rank = rank + directions[i][1];
            int between_file = file + between_directions[i][0];
            int between_rank = rank + between_directions[i][1];
            if (is_inside_board(new_file, new_rank) && board[new_rank][new_file].piece == nullptr
                && is_inside_board(between_file, between_rank)
                && board[between_rank][between_file].piece == nullptr) {
                add_move(new_file, new_rank, moves);
            }
        }
    }

    void generate_horse_moves(int file, int rank, std::vector<std::pair<int, int>> &moves) const
    {
        int directions[8][2]
            = {{-2, -1}, {-2, 1}, {2, -1}, {2, 1}, {-1, -2}, {-1, 2}, {1, -2}, {1, 2}};
        for (const auto &dir : directions) {
            int new_file = file + dir[0];
            int new_rank = rank + dir[1];
            int between_file = file + dir[0] / 2;
            int between_rank = rank + dir[1] / 2;
            if (is_inside_board(new_file, new_rank)
                && (board[new_rank][new_file].piece == nullptr
                    || board[new_rank][new_file].piece->color != board[rank][file].piece->color)) {
                if (dir[0] == -2 || dir[0] == 2) {
                    if (is_inside_board(between_file, rank)
                        && board[rank][between_file].piece == nullptr) {
                        add_move(new_file, new_rank, moves);
                    }
                } else {
                    if (is_inside_board(file, between_rank)
                        && board[between_rank][file].piece == nullptr) {
                        add_move(new_file, new_rank, moves);
                    }
                }
            }
        }
    }

    void generate_chariot_moves(int file, int rank, std::vector<std::pair<int, int>> &moves) const
    {
        int directions[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
        for (const auto &dir : directions) {
            int new_file = file + dir[0];
            int new_rank = rank + dir[1];
            while (is_inside_board(new_file, new_rank)) {
                PPiece *piece = board[new_rank][new_file].piece;
                if (piece == nullptr) {
                    add_move(new_file, new_rank, moves);
                } else {
                    if (piece->color != board[rank][file].piece->color) {
                        add_move(new_file, new_rank, moves);
                    }
                    break;
                }
                new_file += dir[0];
                new_rank += dir[1];
            }
        }
    }

    void generate_cannon_moves(int file, int rank, std::vector<std::pair<int, int>> &moves) const
    {
        int directions[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
        for (const auto &dir : directions) {
            int new_file = file + dir[0];
            int new_rank = rank + dir[1];
            bool found_piece = false;
            while (is_inside_board(new_file, new_rank)) {
                PPiece *piece = board[new_rank][new_file].piece;
                if (piece == nullptr) {
                    if (!found_piece) {
                        add_move(new_file, new_rank, moves);
                    }
                } else {
                    if (!found_piece) {
                        found_piece = true;
                    } else {
                        if (piece->color != board[rank][file].piece->color) {
                            add_move(new_file, new_rank, moves);
                        }
                        break;
                    }
                }
                new_file += dir[0];
                new_rank += dir[1];
            }
        }
    }

    void generate_soldier_moves(int file, int rank, std::vector<std::pair<int, int>> &moves) const
    {
        int directions[3][2];
        if (board[rank][file].piece->color == Color::Red) {
            directions[0][0] = 0;
            directions[0][1] = 1;
            if (rank > 4) {
                directions[1][0] = -1;
                directions[1][1] = 0;
                directions[2][0] = 1;
                directions[2][1] = 0;
            }
        } else {
            directions[0][0] = 0;
            directions[0][1] = -1;

            if (rank < 4) {
                directions[1][0] = 1;
                directions[1][1] = 0;
                directions[2][0] = -1;
                directions[2][1] = 0;
            }
        }


        for (const auto &dir : directions) {
            int new_file = file + dir[0];
            int new_rank = rank + dir[1];
            if (is_inside_board(new_file, new_rank)) {
                PPiece *piece = board[new_rank][new_file].piece;
                if (piece == nullptr || piece->color != board[rank][file].piece->color) {
                    add_move(new_file, new_rank, moves);
                }
            }
        }
    }
};


#endif // CCHESS_RULES_H
