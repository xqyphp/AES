#include "Base64.h"

#define base64_encoded_length(len)  (((len + 2) / 3) * 4)
#define base64_decoded_length(len)  (((len + 3) / 4) * 3)


std::string  Base64::EncodeString(const std::string& input)
{
	static u_char   basis64[] =
		"ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
	return EncodeStringInternal(input,basis64, true);
}

std::string  Base64::EncodeStringUrl(const std::string& input)
{
	static u_char   basis64[] =
		"ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789-_";
	return EncodeStringInternal(input, basis64, true);
}

bool Base64::DecodeString(const std::string& input,std::string & dst)
{
	static u_char   basis64[] = {
		77, 77, 77, 77, 77, 77, 77, 77, 77, 77, 77, 77, 77, 77, 77, 77,
		77, 77, 77, 77, 77, 77, 77, 77, 77, 77, 77, 77, 77, 77, 77, 77,
		77, 77, 77, 77, 77, 77, 77, 77, 77, 77, 77, 62, 77, 77, 77, 63,
		52, 53, 54, 55, 56, 57, 58, 59, 60, 61, 77, 77, 77, 77, 77, 77,
		77,  0,  1,  2,  3,  4,  5,  6,  7,  8,  9, 10, 11, 12, 13, 14,
		15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 77, 77, 77, 77, 77,
		77, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40,
		41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 51, 77, 77, 77, 77, 77,

		77, 77, 77, 77, 77, 77, 77, 77, 77, 77, 77, 77, 77, 77, 77, 77,
		77, 77, 77, 77, 77, 77, 77, 77, 77, 77, 77, 77, 77, 77, 77, 77,
		77, 77, 77, 77, 77, 77, 77, 77, 77, 77, 77, 77, 77, 77, 77, 77,
		77, 77, 77, 77, 77, 77, 77, 77, 77, 77, 77, 77, 77, 77, 77, 77,
		77, 77, 77, 77, 77, 77, 77, 77, 77, 77, 77, 77, 77, 77, 77, 77,
		77, 77, 77, 77, 77, 77, 77, 77, 77, 77, 77, 77, 77, 77, 77, 77,
		77, 77, 77, 77, 77, 77, 77, 77, 77, 77, 77, 77, 77, 77, 77, 77,
		77, 77, 77, 77, 77, 77, 77, 77, 77, 77, 77, 77, 77, 77, 77, 77
	};
	return DecodeStringInternal(input, basis64,true,dst);
}

bool Base64::DecodeStringUrl(const std::string& input,std::string & dst)
{
	static u_char   basis64[] = {
		77, 77, 77, 77, 77, 77, 77, 77, 77, 77, 77, 77, 77, 77, 77, 77,
		77, 77, 77, 77, 77, 77, 77, 77, 77, 77, 77, 77, 77, 77, 77, 77,
		77, 77, 77, 77, 77, 77, 77, 77, 77, 77, 77, 62, 77, 77, 77, 63,
		52, 53, 54, 55, 56, 57, 58, 59, 60, 61, 77, 77, 77, 77, 77, 77,
		77,  0,  1,  2,  3,  4,  5,  6,  7,  8,  9, 10, 11, 12, 13, 14,
		15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 77, 77, 77, 77, 77,
		77, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40,
		41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 51, 77, 77, 77, 77, 77,

		77, 77, 77, 77, 77, 77, 77, 77, 77, 77, 77, 77, 77, 77, 77, 77,
		77, 77, 77, 77, 77, 77, 77, 77, 77, 77, 77, 77, 77, 77, 77, 77,
		77, 77, 77, 77, 77, 77, 77, 77, 77, 77, 77, 77, 77, 77, 77, 77,
		77, 77, 77, 77, 77, 77, 77, 77, 77, 77, 77, 77, 77, 77, 77, 77,
		77, 77, 77, 77, 77, 77, 77, 77, 77, 77, 77, 77, 77, 77, 77, 77,
		77, 77, 77, 77, 77, 77, 77, 77, 77, 77, 77, 77, 77, 77, 77, 77,
		77, 77, 77, 77, 77, 77, 77, 77, 77, 77, 77, 77, 77, 77, 77, 77,
		77, 77, 77, 77, 77, 77, 77, 77, 77, 77, 77, 77, 77, 77, 77, 77
	};
	return DecodeStringInternal(input, basis64, true, dst);
}


std::string Base64::EncodeStringInternal(const std::string& input,u_char* basis,bool padding)
{
	u_char         *d, *s;
	size_t         len,dst_len;

	len = input.size();
	dst_len = base64_encoded_length(len);

	std::string dst(dst_len, 0);
	
	s = (u_char*)input.c_str();
	d = (u_char*)dst.c_str();

	while (len > 2) {
		*d++ = basis[(s[0] >> 2) & 0x3f];
		*d++ = basis[((s[0] & 3) << 4) | (s[1] >> 4)];
		*d++ = basis[((s[1] & 0x0f) << 2) | (s[2] >> 6)];
		*d++ = basis[s[2] & 0x3f];

		s += 3;
		len -= 3;
	}

	if (len) {
		*d++ = basis[(s[0] >> 2) & 0x3f];

		if (len == 1) {
			*d++ = basis[(s[0] & 3) << 4];
			if (padding) {
				*d++ = '=';
			}

		}
		else {
			*d++ = basis[((s[0] & 3) << 4) | (s[1] >> 4)];
			*d++ = basis[(s[1] & 0x0f) << 2];
		}

		if (padding) {
			*d++ = '=';
		}
	}
	return dst;
}



bool Base64::DecodeStringInternal(const std::string& input, u_char* basis, bool padding, std::string& dst)
{
	size_t          len;
	u_char          *d, *s;
	const std::string& src = input;
	for (len = 0; len < src.size(); len++) {
		if (src[len] == '=') {
			break;
		}

		if (basis[src[len]] == 77) {
			return false;
		}
	}

	if (len % 4 == 1) {
		return false;
	}

	s = (u_char*)src.c_str();
	dst.resize(base64_decoded_length(src.size()));
	d = (u_char*)dst.c_str();

	while (len > 3) {
		*d++ = (u_char)(basis[s[0]] << 2 | basis[s[1]] >> 4);
		*d++ = (u_char)(basis[s[1]] << 4 | basis[s[2]] >> 2);
		*d++ = (u_char)(basis[s[2]] << 6 | basis[s[3]]);

		s += 4;
		len -= 4;
	}

	if (len > 1) {
		*d++ = (u_char)(basis[s[0]] << 2 | basis[s[1]] >> 4);
	}

	if (len > 2) {
		*d++ = (u_char)(basis[s[1]] << 4 | basis[s[2]] >> 2);
	}
	dst.resize(d - (u_char*)dst.c_str());

	return true;
}
