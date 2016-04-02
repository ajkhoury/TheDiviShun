#include <windows.h>
#include <io.h>
#include "console.h"

Console::Console() : m_OwnConsole(false)
{
	if (!AllocConsole())
		return;

	errno_t ret = freopen_s(&m_Stream, "CONOUT$", "w", stdout);
	if (ret != NULL)
		return;

	SetConsoleTitle("dbg");

	m_OwnConsole = true;
}

Console::~Console()
{
	//Release();
}

void Console::Release()
{
	if (m_OwnConsole)
	{
		FreeConsole();
		fclose(m_Stream);
	}
}

void Console::Clear()
{
	HANDLE console; 
	CONSOLE_SCREEN_BUFFER_INFO screen;
	DWORD written;
	COORD topLeft = { 0, 0 };

	console = GetStdHandle(STD_OUTPUT_HANDLE);
	GetConsoleScreenBufferInfo(console, &screen);
	FillConsoleOutputCharacter(console, ' ', screen.dwSize.X * screen.dwSize.Y, topLeft, &written);
	FillConsoleOutputAttribute(console, NULL, screen.dwSize.X * screen.dwSize.Y, topLeft, &written);
	SetConsoleCursorPosition(console, topLeft);
}