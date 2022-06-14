#pragma once
#include <string>

using namespace std;

// Эх, если бы мне платили каждый раз, когда в C++
// приходилось лепить подобное г...
char letterToLowercase(char c) {
	int code = (int)c;

	if (code >= -64 && code <= -33) {
		return (char)(code + 32);
	}

	switch (c) {
	case 'A': return 'a';
	case 'B': return 'b';
	case 'C': return 'c';
	case 'D': return 'd';
	case 'E': return 'e';
	case 'F': return 'f';
	case 'G': return 'g';
	case 'H': return 'h';
	case 'I': return 'i';
	case 'J': return 'j';
	case 'K': return 'k';
	case 'L': return 'l';
	case 'M': return 'm';
	case 'N': return 'n';
	case 'O': return 'o';
	case 'P': return 'p';
	case 'Q': return 'q';
	case 'R': return 'r';
	case 'S': return 's';
	case 'T': return 't';
	case 'U': return 'u';
	case 'V': return 'v';
	case 'W': return 'w';
	case 'X': return 'x';
	case 'Y': return 'y';
	case 'Z': return 'z';
	case 'А': return 'а';
	case 'Б': return 'б';
	case 'В': return 'в';
	case 'Г': return 'г';
	case 'Д': return 'д';
	case 'Е': return 'е';
	case 'Ё': return 'ё';
	case 'Ж': return 'ж';
	case 'З': return 'з';
	case 'И': return 'и';
	case 'Й': return 'й';
	case 'К': return 'к';
	case 'Л': return 'л';
	case 'М': return 'м';
	case 'Н': return 'н';
	case 'О': return 'о';
	case 'П': return 'п';
	case 'Р': return 'р';
	case 'С': return 'с';
	case 'Т': return 'т';
	case 'У': return 'у';
	case 'Ф': return 'ф';
	case 'Х': return 'х';
	case 'Ц': return 'ц';
	case 'Ч': return 'ч';
	case 'Ш': return 'ш';
	case 'Щ': return 'щ';
	case 'Ъ': return 'ъ';
	case 'Ы': return 'ы';
	case 'Ь': return 'ь';
	case 'Э': return 'э';
	case 'Ю': return 'ю';
	case 'Я': return 'я';
    default: return c;
	}
}

string toLowercase(string str) {
	string strLower = str;

	for (char& c : strLower) {
		c = letterToLowercase(c);
	}

	return strLower;
}
