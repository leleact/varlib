
#include <iostream>
#include <cstring>
void trim(char *str)
{
	if (str == NULL)
	{
		return;	
	}
	char *pstr = (char *) str;
	while(*pstr == 0x20
			|| *pstr == 0x09
			|| *pstr == 0x0d
			|| *pstr == 0x0a)
	{
		pstr++;	
	}

	int nLen = strlen(pstr) - 1;
	while(pstr[nLen] == 0x20
			|| pstr[nLen] == 0x09
			|| pstr[nLen] == 0x0d
			|| pstr[nLen] == 0x0a)
	{
		pstr[nLen--] = '\0';
	}
	strcpy(str, pstr);
	return;
}

int main()
{
	char str[100] = "\n	 ff \r";
	std::cout << "str=[" << str << "]" << std::endl;
	trim(str);
	std::cout << "str=[" << str << "]" << std::endl;
	return 0;
}
