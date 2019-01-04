/*

Goal:
 * To create computer alagorithm for calculating the best coordinate in a given Board
 * To incorporate random element to the comp algorithm
 * To change grid input system from coordinate (row, elem) to simple reference number (single int 1-9 for 3*3 grid)
*/

#include <iostream>
#include <array>
#include <string>
#include <tuple>

enum PlayerState
{
	NONE,
	PLAYER1,
	PLAYER2
};

enum PlayerMode
{
	HUMAN,
	COMPUTER
};

class Board
{
private:
	std::array<std::array<PlayerState, 3>, 3> m_board{};
	
public:
	Board()
	{
	}

	int getBoardSize() { return m_board.size(); }
	bool checkCellExistance(int row, int elem) { return m_board[row][elem]; } // returns 0 (false) if there's NONE, true otherwise

	std::string cellStateToString(const PlayerState &state)
	{
		switch (state)
		{
		case(NONE):	return "?";
		case(PLAYER1):	return "O";
		case(PLAYER2):	return "X";
		default: return "!";
		}
	}

	void printBoard()
	{
		for (auto &row : m_board)
		{
			for (auto &element : row)
			{
				std::cout << cellStateToString(element) << ' ';
			}
			std::cout << '\n';
		}
		std::cout << "Empty: ?\nPlayer 1: O\nPlayer 2: X\n";
	}

	void updateCellState(std::tuple<int, int, PlayerState> info)
	{
		m_board[std::get<0>(info)][std::get<1>(info)] = std::get<2>(info); // coordinate in form (row, elem)
	}

	bool checkDraw() // returns false if any of the cells are empty, returns true otherwise
	{
		for (unsigned int i = 0; i < m_board.size(); i++)
		for (unsigned int j = 0; j < m_board.size(); j++)
		{
			if (m_board[i][j] == NONE) return false;
		}

		return true;
	}

	PlayerState checkGameState(PlayerState player) // if player won the game, return player. otherwise, return PlayerState NONE (0)
	{
		// Check row
		for (unsigned int row = 0; row < m_board.size(); row++)
		{
			if (m_board[row][0] == player && m_board[row][1] == player && m_board[row][2] == player) return player;
		}

		// Check elem
		for (unsigned int elem = 0; elem < m_board.size(); elem++)
		{
			if (m_board[0][elem] == player && m_board[1][elem] == player && m_board[2][elem] == player) return player;
		}

		// Check diagonals
		if (m_board[0][0] == player && m_board[1][1] == player && m_board[2][2] == player) return player;

		if (m_board[2][0] == player && m_board[1][1] == player && m_board[0][2] == player) return player;

		// Return false Otherwise
		return NONE;
	}
};

class Player 
{
private:
	PlayerState m_playerState;
	PlayerMode m_playerMode;

public:
	Player(PlayerState plState, PlayerMode plMode)
		: m_playerState(plState), m_playerMode(plMode)
	{
	}

	PlayerState getPlayerState() { return m_playerState; }
	PlayerMode getPlayerMode() { return m_playerMode; }

	std::tuple<int, int, PlayerState> chooseCoord(Board &b)
	{
		int row;
		int elem;

		if (m_playerMode == HUMAN) // need to prevent replacing existing player mark
		{
			while (true)
			{
				std::cout << "row index    : ";
				std::cin >> row;
				if (row >= b.getBoardSize())
				{
					std::cout << "row index cannot be higher than " << b.getBoardSize() - 1 << ".\n";
					continue;
				}

				std::cout << "element index: ";
				std::cin >> elem;
				if (elem >= b.getBoardSize())
				{
					std::cout << "element index cannot be higher than " << b.getBoardSize() - 1 << ".\n";
					continue;
				}

				std::cout << "";

				if (b.checkCellExistance(row, elem))
				{
					std::cout << "A player already occupied the specified coordinate.\n";
					continue;
				}

				break;
			}
			
		}
		else if (m_playerMode == COMPUTER)
		{
			// Best choice only
		}
		else
		{
			// throw error
		}
		return {row, elem, m_playerState};
	}
};

int main()
{
	Board board;
	
	std::array<Player, 2> players = { Player(PLAYER1, HUMAN), Player(PLAYER2, HUMAN) };

	PlayerState winner = NONE;
	bool isDraw = false;

	while (!winner && !isDraw)
	{
		for (auto &player : players)
		{
			system("cls");
			std::cout << player.getPlayerState() << "'s turn:\n";
			board.printBoard();
			std::tuple<int, int, PlayerState> inputInfo = player.chooseCoord(board);
			board.updateCellState(inputInfo);
			winner = board.checkGameState(player.getPlayerState());
			isDraw = board.checkDraw();

			if (winner || isDraw) break;
		}
	}

	system("cls");
	board.printBoard();
	if (winner != NONE)	std::cout << "Player " << winner << " is the winner!\n";
	else if (isDraw)	std::cout << "It's a draw!\n";

	return 0;
}