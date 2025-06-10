#include "Chess.h"
#include <iostream>
#include <string>

using namespace std;

#ifdef _WIN32

// clear the screen "cls"
void Chess::clear() const 
{
	COORD topLeft = { 0, 0 };
	HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFO screen;
	DWORD written;

	GetConsoleScreenBufferInfo(console, &screen);
	FillConsoleOutputCharacterA(
		console, ' ', screen.dwSize.X * screen.dwSize.Y, topLeft, &written
	);
	FillConsoleOutputAttribute(
		console, FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_BLUE,
		screen.dwSize.X * screen.dwSize.Y, topLeft, &written
	);
	SetConsoleCursorPosition(console, topLeft);
}

// create the GUI - ASCII art
void Chess::setFrames() 
{ 
	for (size_t row = 0; row < _SIZE; ++row)
		for (size_t col = 0; col < _SIZE; ++col)
			m_board[row][col] = 32;

	m_board[0][0] = 201;  m_board[0][20] = 187;
	m_board[20][0] = 200; m_board[20][20] = 188;

	for (size_t i = 1; i < 20; ++i)
	{
		m_board[0][i] = 205;
		m_board[20][i] = 205;
		m_board[i][0] = 186;
		m_board[i][20] = 186;
	} 

	m_board[2][2] = 218;  m_board[2][18] = 191;
	m_board[18][2] = 192; m_board[18][18] = 217;

	for (size_t i = 4; i < 17; i += 2)
	{
		m_board[2][i] = 194;
		m_board[18][i] = 193;
		m_board[i][2] = 195;
		m_board[i][18] = 180;
	}

	for (size_t i = 2; i < 19; i += 2)
		for (size_t j = 3; j < 19; j += 2)
			m_board[i][j] = 196;

	for (size_t i = 3; i < 18; i += 2)
		for (size_t j = 2; j < 19; j += 2)
			m_board[i][j] = 179;

	for (size_t i = 4; i < 17; i += 2)
		for (size_t j = 4; j < 17; j += 2)
			m_board[i][j] = 197;

	for (size_t i = 4; i < 17; i += 2)
		m_board[2][i] = 194;
	for (size_t i = 4; i < 17; i += 2)
		m_board[18][i] = 193;
	for (size_t i = 4; i < 17; i += 2)
		m_board[i][2] = 195;
	for (size_t i = 4; i < 17; i += 2)
		m_board[i][18] = 180;

	for (size_t i = 3, t = 0; i < 19; i += 2, ++t)
		m_board[1][i] = m_board[19][i] = ('1' + t);

	for (size_t i = 3, t = 0; i < 19; i += 2, ++t)
		m_board[i][1] = m_board[i][19] = ('A' + t);
}

void Chess::setPieces()
{
	for (size_t row = 0, t = 0; row < 8; ++row)
		for (size_t col = 0; col < 8; ++col, ++t)
			m_board[(3 + (row * 2))][(3 + (col * 2))] = ((m_boardString[t] == '#') ? 32 : m_boardString[t]);
}

#else // non-Windows

void Chess::clear() const
{
	cout << "\033[2J\033[3J\033[H";
}

void Chess::setFrames()
{
	for (size_t row = 0; row < _SIZE; ++row)
		for (size_t col = 0; col < _SIZE; ++col)
			m_board[row][col] = ' ';

	m_board[0][0] = '+';
	m_board[0][20] = '+';
	m_board[20][0] = '+';
	m_board[20][20] = '+';

	for (size_t i = 1; i < 20; ++i)
	{
		m_board[0][i] = '-';
		m_board[20][i] = '-';
		m_board[i][0] = '|';
		m_board[i][20] = '|';
	}

	m_board[2][2] = '+';
	m_board[2][18] = '+';
	m_board[18][2] = '+';
	m_board[18][18] = '+';

	for (size_t i = 4; i < 17; i += 2)
	{
		m_board[2][i] = '+';
		m_board[18][i] = '+';
		m_board[i][2] = '+';
		m_board[i][18] = '+';
	}

	for (size_t i = 2; i < 19; i += 2)
		for (size_t j = 3; j < 19; j += 2)
			m_board[i][j] = '-';

	for (size_t i = 3; i < 18; i += 2)
		for (size_t j = 2; j < 19; j += 2)
			m_board[i][j] = '|';

	for (size_t i = 4; i < 17; i += 2)
		for (size_t j = 4; j < 17; j += 2)
			m_board[i][j] = '+';

	for (size_t i = 4; i < 17; i += 2)
		m_board[2][i] = '+';
	for (size_t i = 4; i < 17; i += 2)
		m_board[18][i] = '+';
	for (size_t i = 4; i < 17; i += 2)
		m_board[i][2] = '+';
	for (size_t i = 4; i < 17; i += 2)
		m_board[i][18] = '+';

	for (size_t i = 3, t = 0; i < 19; i += 2, ++t)
		m_board[1][i] = m_board[19][i] = ('1' + t);

	for (size_t i = 3, t = 0; i < 19; i += 2, ++t)
		m_board[i][1] = m_board[i][19] = ('A' + t);
}

void Chess::setPieces()
{
	for (size_t row = 0, t = 0; row < 8; ++row)
		for (size_t col = 0; col < 8; ++col, ++t)
			m_board[(3 + (row * 2))][(3 + (col * 2))] = ((m_boardString[t] == '#') ? ' ' : m_boardString[t]);
}

#endif // WINDOWS

// print the only the board to screen 
void Chess::show() const 
{
	for (size_t row = 0; row < _SIZE; ++row)
	{
		for (size_t col = 0; col < _SIZE; ++col)
			cout << m_board[row][col];
		cout << endl;
	}
}
// clear screen and print the board and the relevant msg 
void Chess::displayBoard() const
{
    // It prevents me from printing the recommended moves (in the Linux terminal), so I put it in a comment.
//	clear();
	show();
	cout << m_msg<< m_errorMsg;
	
}
// print the who is turn before getting input 
void Chess::showAskInput() const 
{
	if (m_turn)
		cout << "Player 1 (White - Capital letters) >> ";
	else
		cout << "Player 2 (Black - Small letters)   >> ";
}
// check if the _source and dest are the same
bool Chess::isSame() const 
{
	return ((m_input[0] == m_input[2]) && (m_input[1] == m_input[3]));
} 
// check if the input is lockations at board
bool Chess::isValid() const
{
	return ((('A' <= m_input[0]) && (m_input[0] <= 'H')) || (('a' <= m_input[0]) && (m_input[0] <= 'h')) &&
		(('1' <= m_input[1]) && (m_input[1] <= '8')) &&
		(('A' <= m_input[2]) && (m_input[2] <= 'H')) || (('a' <= m_input[2]) && (m_input[2] <= 'h')) &&
		(('1' <= m_input[3]) && (m_input[3] <= '8')));
}
	
// check if the input is exit or quit  
bool Chess::isExit() const 
{
	return ((m_input == "exit") || (m_input == "quit") || (m_input == "EXIT") || (m_input == "QUIT"));
}
// execute the movement on board 
void Chess::excute()
{
//	int row = (m_input[0] - 'a');
//	int col = (m_input[1] - '1');
//	char pieceInSource = m_boardString[(row * 8) + col];
//	m_boardString[(row * 8) + col] = '#';
//
//
//	row = (m_input[2] - 'a');
//	col = (m_input[3] - '1');
//	m_boardString[(row * 8) + col] = pieceInSource;
//
//	setPieces();


    int sourceRow = (m_input[0] - 'a');
    int sourceCol = (m_input[1] - '1');
    int destRow = (m_input[2] - 'a');
    int destCol = (m_input[3] - '1');

    char pieceInSource = m_boardString[(sourceRow * 8) + sourceCol];
    char pieceAtDestination = m_boardString[(destRow * 8) + destCol];

    // White King side castle: e1g1
    if (pieceInSource == 'K' && sourceRow == 0 && sourceCol == 4 && destRow == 0 && destCol == 6) {
        m_boardString[(0 * 8) + 4] = '#'; // Clear King's original position (a5)
        m_boardString[(0 * 8) + 7] = '#'; // Clear Rook's original position (a8)
        m_boardString[(0 * 8) + 6] = 'K'; // Place King at a7
        m_boardString[(0 * 8) + 5] = 'R'; // Place Rook at a6
    }
        // White Queen side castle: e1c1 (input is e1c1)
    else if (pieceInSource == 'K' && sourceRow == 0 && sourceCol == 4 && destRow == 0 && destCol == 2) {
        m_boardString[(0 * 8) + 4] = '#'; // Clear King's original position (a5)
        m_boardString[(0 * 8) + 0] = '#'; // Clear Rook's original position (a1)
        m_boardString[(0 * 8) + 2] = 'K'; // Place King at a3
        m_boardString[(0 * 8) + 3] = 'R'; // Place Rook at a4
    }
        // Black King side castle: e8g8 (input is e8g8)
    else if (pieceInSource == 'k' && sourceRow == 7 && sourceCol == 4 && destRow == 7 && destCol == 6) {
        m_boardString[(7 * 8) + 4] = '#'; // Clear King's original position (h5)
        m_boardString[(7 * 8) + 7] = '#'; // Clear Rook's original position (h8)
        m_boardString[(7 * 8) + 6] = 'k'; // Place King at h7
        m_boardString[(7 * 8) + 5] = 'r'; // Place Rook at h6
    }
        // Black Queen side castle: e8c8 (input is e8c8)
    else if (pieceInSource == 'k' && sourceRow == 7 && sourceCol == 4 && destRow == 7 && destCol == 2) {
        m_boardString[(7 * 8) + 4] = '#'; // Clear King's original position (h5)
        m_boardString[(7 * 8) + 0] = '#'; // Clear Rook's original position (h1)
        m_boardString[(7 * 8) + 2] = 'k'; // Place King at h3
        m_boardString[(7 * 8) + 3] = 'r'; // Place Rook at h4
    }
        // Special handling for Pawn Promotion: A pawn reaching the end of the board
        // In this case, the `Board` class has already handled the promotion choice,
        // so `m_boardString` needs to be updated with the *new* promoted piece
        // that is now at the destination.
    else if (((pieceInSource == 'P' && destRow == 7) || (pieceInSource == 'p' && destRow == 0)) &&
             (pieceAtDestination != '#' && pieceAtDestination != 'P' && pieceAtDestination != 'p')) {
        // This condition checks if a pawn has reached the end of the board
        // AND if the piece at the destination is *not* empty and *not* the original pawn.
        // This implies that Board::makeMove has already placed the promoted piece.
        m_boardString[(sourceRow * 8) + sourceCol] = '#'; // Clear the original pawn position
        // The pieceAtDestination already holds the promoted piece character
        // m_boardString[(destRow * 8) + destCol] = pieceAtDestination; // No need, it's already there
    }
        // Normal move: clear source, place piece at destination
    else {
        m_boardString[(sourceRow * 8) + sourceCol] = '#'; // Clear source
        m_boardString[(destRow * 8) + destCol] = pieceInSource; // Place piece at destination
    }

    setPieces(); // Update the graphical board with the new m_boardString
}
// check the response code and switch turn if needed 
void Chess::doTurn()
{
	m_errorMsg = "\n"; 
	switch (m_codeResponse)
	{
	case 11:
	{
		m_msg = "there is not piece at the _source \n";
		break;
	}
	case 12:
	{
		m_msg = "the piece in the _source is piece of your opponent \n";
		break;
	}
	case 13:
	{
		m_msg = "there one of your pieces at the _destination \n";
		break;
	}
	case 21:
	{
		m_msg = "illegal movement of that piece \n";
		break;
	}
	case 31:
	{
		m_msg = "this movement will cause you checkmate \n";
		break;
	}
	case 41:
	{
//		excute();
		m_turn = !m_turn;
		m_msg = "the last movement was legal and cause check \n";
		break;
	}
	case 42:
	{
//		excute();
		m_turn = !m_turn;
		m_msg = "the last movement was legal \n";
		break;
	}
	}
}

// C'tor
Chess::Chess(const string& start)
	: m_boardString(start),m_codeResponse(-1)
{
	setFrames();
	setPieces();
}

/**
 * @brief Gets a move input string either from the user or computer.
 *        Validates the input format and ensures source and destination differ.
 *
 * @param user True if the input is from the user, false if from computerMove string.
 * @param computerMove The computer's move string (used if user == false).
 * @param currentBoard Current board state (used for display and validation).
 * @return Validated move string in format like "e2e4", or "exit" if quitting.
 */
string Chess::getInput(bool user, string& computerMove, const Board& currentBoard)
{
	static bool isFirst = true;

	if (isFirst){
        isFirst = false;
        m_boardString = currentBoard.boardToString();
    }
	else{
        doTurn();
        m_boardString = currentBoard.boardToString();
        setPieces();
    }


	displayBoard();
    if (user){
        showAskInput();
        cin >> m_input;
    }
    else{
        m_input = computerMove;
    }


	if (isExit())
		return "exit";
	while (!isValid() || isSame())
	{
		if (!isValid())
			m_errorMsg = "Invalid input !! \n";
		else
			m_errorMsg = "The _source and the _destination are the same !! \n";
		displayBoard();
        if(user){
            showAskInput();
            cin >> m_input;
        }
        else{
            m_input = computerMove;
        }

		if (isExit())
			return "exit";
	}

	if (m_input != "exit")
	{
		if (('A' <= m_input[0]) && (m_input[0] <= 'H'))
			m_input[0] = (m_input[0] - 'A' + 'a');
		if (('A' <= m_input[2]) && (m_input[2] <= 'H'))
			m_input[2] = (m_input[2] - 'A' + 'a');
	}


	return m_input;
}

void Chess::setCodeResponse(int codeResponse)
{
	if (((11 <= codeResponse) && (codeResponse <= 13)) ||
		((21 == codeResponse) || (codeResponse == 31)) ||
		((41 == codeResponse) || (codeResponse == 42)))
		m_codeResponse = codeResponse;
}