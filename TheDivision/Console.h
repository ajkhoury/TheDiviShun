#pragma once

#ifndef _CONSOLE_H_
#define _CONSOLE_H_

#include <stdio.h>

class Console
{
public:
	Console();
	~Console();

	void Release();
	void Clear();

private:
	_iobuf* m_Stream;
	bool m_OwnConsole;
};

#endif