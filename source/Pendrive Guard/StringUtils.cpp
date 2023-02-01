#include "StringUtils.h"

std::string WStringToString(const std::wstring &w)
{
    return std::string(w.begin(), w.end());
}
//----------------------
std::wstring StringToWString(const std::string &w)
{
    return std::wstring(w.begin(), w.end());
}
//----------------------
void StringTokenize(const String &str, std::vector<String> & tokens,const String & delimiters)
{
	// przeskoczenie rozdzielacza na pocz¹tku
	String::size_type lastPos = str.find_first_not_of(delimiters);
	// odnalezienie pierwszego nie-rozdzielacza
	String::size_type pos =	str.find_first_of(delimiters, lastPos);

	while(String::npos != pos || String::npos != lastPos)
	{
		// znajdz token i wrzuæ go do wektora
		tokens.push_back(str.substr(lastPos, pos - lastPos));
		// przeskocz rozdzielacze
		lastPos = str.find_first_not_of(delimiters,pos);
		// znajdŸ nastêpny "nie-rozdzielacz"
		pos = str.find_first_of(delimiters, lastPos);
	}
}