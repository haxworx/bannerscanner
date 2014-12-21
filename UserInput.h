#ifndef __User_Input_H__
#define __User_Input_H__

#include <iostream>

using namespace std;

class Input {
	public:
		int ReadChar(void);
		char *ReadString(void);
	private:
		char ch;
		char buf[1024];

};

#endif
