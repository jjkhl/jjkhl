#include <iostream>
#include <thread>
#include <vector>
using namespace std;

#include <stdio.h>
#include <Windows.h>

int nScreenWidth = 80;			// Console Screen Size X (columns)
int nScreenHeight = 30;			// Console Screen Size Y (rows)
wstring tetromino[7];
int nFieldWidth = 12;
int nFieldHeight = 18;
unsigned char* pField = nullptr;

int Rotate(int px, int py, int r)
{
	int pi = 0;
	switch (r % 4)
	{
	case 0: // 0 degrees			// 0  1  2  3
		pi = py * 4 + px;			// 4  5  6  7
		break;						// 8  9 10 11
									//12 13 14 15

	case 1: // 90 degrees			//12  8  4  0
		pi = 12 + py - (px * 4);	//13  9  5  1
		break;						//14 10  6  2
									//15 11  7  3

	case 2: // 180 degrees			//15 14 13 12
		pi = 15 - (py * 4) - px;	//11 10  9  8
		break;						// 7  6  5  4
									// 3  2  1  0

	case 3: // 270 degrees			// 3  7 11 15
		pi = 3 - py + (px * 4);		// 2  6 10 14
		break;						// 1  5  9 13
	}								// 0  4  8 12

	return pi;
}

bool DoesPieceFit(int nTetromino, int nRotation, int nPosX, int nPosY)
{
	// All Field cells >0 are occupied
	for (int px = 0; px < 4; px++)//所有图形最多占4×4格
		for (int py = 0; py < 4; py++)
		{
			// Get index into piece
			int pi = Rotate(px, py, nRotation);

			// Get index into field
			int fi = (nPosY + py) * nFieldWidth + (nPosX + px);

			// Check that test is in bounds. Note out of bounds does
			// not necessarily mean a fail, as the long vertical piece
			// can have cells that lie outside the boundary, so we'll
			// just ignore them
			if (nPosX + px >= 0 && nPosX + px < nFieldWidth)
			{
				if (nPosY + py >= 0 && nPosY + py < nFieldHeight)
				{
					// In Bounds so do collision check
					if (tetromino[nTetromino][pi] != L'.' && pField[fi] != 0)
						return false; // fail on first hit
				}
			}
		}

	return true;
}

int main()
{
	// Create Screen Buffer
	wchar_t* screen = new wchar_t[nScreenWidth * nScreenHeight];
	for (int i = 0; i < nScreenWidth * nScreenHeight; i++) screen[i] = L' ';
	HANDLE hConsole = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, 0, NULL, CONSOLE_TEXTMODE_BUFFER, NULL);
	SetConsoleActiveScreenBuffer(hConsole);
	DWORD dwBytesWritten = 0;

	tetromino[0].append(L"..X...X...X...X."); // Tetronimos 4x4
	tetromino[1].append(L"..X..XX...X.....");
	tetromino[2].append(L".....XX..XX.....");
	tetromino[3].append(L"..X..XX..X......");
	tetromino[4].append(L".X...XX...X.....");
	tetromino[5].append(L".X...X...XX.....");
	tetromino[6].append(L"..X...X..XX.....");

	pField = new unsigned char[nFieldWidth * nFieldHeight]; // Create play field buffer
	for (int x = 0; x < nFieldWidth; x++) // Board Boundary
		for (int y = 0; y < nFieldHeight; y++)
			pField[y * nFieldWidth + x] = (x == 0 || x == nFieldWidth - 1 || y == nFieldHeight - 1) ? 9 : 0;

	// Game Logic
	//设置下左右旋转键
	bool bKey[4];
	//设置初始形状
	int nCurrentPiece = 0;
	int nCurrentRotation = 0;
	int nCurrentX = nFieldWidth / 2;
	int nCurrentY = 0;

	int nSpeed = 20;//50ms*20,表示1s落下一个方块
	int nSpeedCount = 0;
	bool bForceDown = false;//判断能不能落下
	bool bRotateHold = true;//按下一次按键智能旋转一次
	int nPieceCount = 0;
	int nScore = 0;
	vector<int> vLines;
	bool bGameOver = false;

	while (!bGameOver) // Main Loop
	{
		// Timing =======================
		this_thread::sleep_for(50ms); // Small Step = 1 Game Tick
		nSpeedCount++;
		bForceDown = (nSpeedCount == nSpeed);

		// Input ========================
		for (int k = 0; k < 4; k++)								// R   L   D Z
			bKey[k] = (0x8000 & GetAsyncKeyState((unsigned char)("\x27\x25\x28Z"[k]))) != 0;

		// Game Logic ===================

		// Handle player movement
		nCurrentX += (bKey[0] && DoesPieceFit(nCurrentPiece, nCurrentRotation, nCurrentX + 1, nCurrentY)) ? 1 : 0;
		nCurrentX -= (bKey[1] && DoesPieceFit(nCurrentPiece, nCurrentRotation, nCurrentX - 1, nCurrentY)) ? 1 : 0;
		nCurrentY += (bKey[2] && DoesPieceFit(nCurrentPiece, nCurrentRotation, nCurrentX, nCurrentY + 1)) ? 1 : 0;

		// Rotate, but latch to stop wild spinning
		if (bKey[3])
		{
			nCurrentRotation += (bRotateHold && DoesPieceFit(nCurrentPiece, nCurrentRotation + 1, nCurrentX, nCurrentY)) ? 1 : 0;
			bRotateHold = false;
		}
		else
			bRotateHold = true;

		// Force the piece down the playfield if it's time
		if (bForceDown)
		{
			// Update difficulty every 50 pieces
			nSpeedCount = 0;
			nPieceCount++;
			if (nPieceCount % 50 == 0)
				if (nSpeed >= 10) nSpeed--;

			// Test if piece can be moved down
			if (DoesPieceFit(nCurrentPiece, nCurrentRotation, nCurrentX, nCurrentY + 1))
				nCurrentY++; // It can, so do it!
			else
			{
				//锁定方块
				for (int px = 0; px < 4; px++)
					for (int py = 0; py < 4; py++)
						if (tetromino[nCurrentPiece][Rotate(px, py, nCurrentRotation)] != L'.')
							pField[(nCurrentY + py) * nFieldWidth + (nCurrentX + px)] = nCurrentPiece + 1;

				//检查是否有消去
				for (int py = 0; py < 4; py++)
					if (nCurrentY + py < nFieldHeight - 1)//不检查边界之外的部分
					{
						bool bLine = true;
						for (int px = 1; px < nFieldWidth - 1; px++)//检查一行当中除边界以外的部分是否存在空格
							bLine &= (pField[(nCurrentY + py) * nFieldWidth + px]) != 0;

						if (bLine)
						{
							// Remove Line, set to =
							for (int px = 1; px < nFieldWidth - 1; px++)
								pField[(nCurrentY + py) * nFieldWidth + px] = 8;//8设置为等号
							vLines.push_back(nCurrentY + py);
						}
					}

				nScore += 25;
				if (!vLines.empty())	nScore += (1 << vLines.size()) * 100;

				// 随机下一个方块
				nCurrentX = nFieldWidth / 2;
				nCurrentY = 0;
				nCurrentRotation = 0;
				nCurrentPiece = rand() % 7;

				//游戏结束
				bGameOver = !DoesPieceFit(nCurrentPiece, nCurrentRotation, nCurrentX, nCurrentY);
			}
		}

		// Display ======================

		// Draw Field
		for (int x = 0; x < nFieldWidth; x++)
			for (int y = 0; y < nFieldHeight; y++)
				screen[(y + 2) * nScreenWidth + (x + 2)] = L" ABCDEFG=#"[pField[y * nFieldWidth + x]];

		// Draw Current Piece
		for (int px = 0; px < 4; px++)
			for (int py = 0; py < 4; py++)
				if (tetromino[nCurrentPiece][Rotate(px, py, nCurrentRotation)] != L'.')
					screen[(nCurrentY + py + 2) * nScreenWidth + (nCurrentX + px + 2)] = nCurrentPiece + 65;

		// Draw Score
		/*swprintf_s(&screen[2 * nScreenWidth + nFieldWidth + 6], 16, L"SCORE: %8d", nScore);*/

		// Animate Line Completion
		//if (!vLines.empty())
		//{
		//	// Display Frame (cheekily to draw lines)
		//	WriteConsoleOutputCharacter(hConsole, screen, nScreenWidth * nScreenHeight, { 0,0 }, &dwBytesWritten);
		//	this_thread::sleep_for(400ms); // Delay a bit

		//	for (auto& v : vLines)
		//		for (int px = 1; px < nFieldWidth - 1; px++)
		//		{
		//			for (int py = v; py > 0; py--)
		//				pField[py * nFieldWidth + px] = pField[(py - 1) * nFieldWidth + px];
		//			pField[px] = 0;
		//		}

		//	vLines.clear();
		//}

		// Display Frame
		WriteConsoleOutputCharacter(hConsole, screen, nScreenWidth * nScreenHeight, { 0,0 }, &dwBytesWritten);
	}

	// Oh Dear
	CloseHandle(hConsole);
	cout << "Game Over!! Score:" << nScore << endl;
	system("pause");
	return 0;
}
