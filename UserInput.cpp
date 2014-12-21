#include "UserInput.h"

int Input::ReadChar(void)
{
	cin.getline(buf, sizeof(buf) -1, '\n');

	return buf[0];
}

char *Input::ReadString(void)
{
	cin.getline(buf, sizeof(buf) -1, '\n');
	
	return buf;
}
