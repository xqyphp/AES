#pragma once

#include <string>

typedef unsigned char u_char;

class Base64
{
public:
	static std::string EncodeString(const std::string& input);
	static std::string EncodeStringUrl(const std::string& input);
	static bool DecodeString(const std::string& input,std::string& dst);
	static bool DecodeStringUrl(const std::string& input,std::string& dst);
protected:
	static std::string EncodeStringInternal(const std::string& input, u_char* basis, bool padding);
	static bool DecodeStringInternal(const std::string& input,u_char* basis, bool padding, std::string& dst);
};

