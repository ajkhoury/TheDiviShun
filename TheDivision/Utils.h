#pragma once

#include <Windows.h>
#include <iostream>
#include <fstream>
#include <fcntl.h>
#include <io.h>

#include "Sigs.h"

namespace Utils
{
	static void CreateConsole(const char* name)
	{
		HANDLE lStdHandle = 0;
		int hConHandle = 0;
		FILE *fp = 0;
		AllocConsole();
		lStdHandle = GetStdHandle(STD_OUTPUT_HANDLE);
		hConHandle = _open_osfhandle((intptr_t)lStdHandle, _O_TEXT);
		SetConsoleTitle(name);
		SetConsoleTextAttribute(lStdHandle, FOREGROUND_GREEN | FOREGROUND_INTENSITY | BACKGROUND_RED);
		fp = _fdopen(hConHandle, "w");
		freopen_s(&fp, "CONOUT$", "w", stdout);
		//*stdout = *fp;
		//setvbuf(stdout, NULL, _IONBF, 0);
	}

	static HMODULE GetModuleHandleSafe(const char* pszModuleName)
	{
		HMODULE hmModuleHandle = NULL;
		do hmModuleHandle = GetModuleHandle(pszModuleName);
		while (!hmModuleHandle);
		return hmModuleHandle;
	}

	static size_t FindPattern(size_t start_offset, DWORD size, unsigned char pattern[], int n)
	{
		//printf("n = %i\n", n);
		char mask[256];
		for (int i = 0; i <= n; i++)
		{
			if (i == n) mask[i] = '\0';
			else if (pattern[i] == 0xCC) mask[i] = '?';
			else mask[i] = 'x';
		}

		int pos = 0;
		int searchLen = static_cast<int>(strlen(mask)) - 1;

		for (size_t retAddress = start_offset; retAddress < start_offset + size; retAddress++)
		{
			if (*(BYTE*)retAddress == pattern[pos] || mask[pos] == '?')
			{
				if (mask[pos + 1] == '\0')
					return (retAddress - searchLen);
				pos++;
			}
			else
				pos = 0;
		}
		return NULL;
	}

	static size_t FindPattern(size_t start_offset, DWORD size, BYTE* pattern, char mask[])
	{
		DWORD pos = 0;
		int searchLen = static_cast<int>(strlen(mask)) - 1;

		for (size_t retAddress = start_offset; retAddress < start_offset + size; retAddress++)
		{
			if (*(BYTE*)retAddress == pattern[pos] || mask[pos] == '?')
			{
				if (mask[pos + 1] == '\0')
					return (retAddress - searchLen);
				pos++;
			}
			else
				pos = 0;
		}
		return NULL;
	}

	template<int N> __inline DWORD FindPattern(size_t start_offset, DWORD size, unsigned char(&pattern)[N])
	{
		return FindPattern(start_offset, size, pattern, N);
	}



};
