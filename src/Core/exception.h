#pragma once
#include <exception>
#include <string>
#include <vector>

#include "intersect_dll.h"

#define MIN_COORDINATE -99999
#define MAX_COORDINATE 99999
#define MIN_RADIUS 1
#define MAX_RADIUS MAX_COORDINATE

enum Exception {
	WrongFormatOfN = 100,
	InvalidValueOfN,
	WrongFormatOfObjectIdentifier = 200,
	WrongFormatOfObjectDescription = 300,
	CoordinateValueExceed,
	TwoPointsCoincideOfLine,
	InvalidRadiusOfCircle,
	ObjectInputTooLittle = 400,
	ObjectInputTooMuch,
	InfiniteIntersectionsFound = 500,
	ElementToDeleteNotFound = 600
};

INTERSECT_API std::string ExpectionString(int exc_code);

struct CoreException : public std::exception
{
	int exc_code;
	int line_number;
	int line2_number;
	CoreException(const int exc_code,  const int line_number = 1, const int line2_number = 1) 
		noexcept:exc_code(exc_code), line_number(line_number), line2_number(line2_number) {}
	const std::string showExceptionMessage() noexcept
	{
		return ExpectionString(exc_code);	
	}
};

inline bool isDegital(const std::string str) {
	for (int i = 0; i < str.size(); i++) {
		if (str.at(i) == '-' && str.size() > 1)
			continue;
		if (str.at(i) > '9' || str.at(i) < '0')
			return false;
	}
	return true;
}

inline std::vector<int> readPara(const int argc, const std::string line) {
	std::vector<int> ret;
	for (int i = 1; i < line.size(); i++) {
		if (line.at(i) == ' ') continue;
		if (isdigit(line.at(i)) || line.at(i) == '-') {
			std::string temp = "";
			temp.push_back(line.at(i));
			i++;
			while (i < line.size() && line.at(i) != ' ') {
				temp.push_back(line.at(i));
				i++;
			}
			if (!isDegital(temp)) {
				throw CoreException(WrongFormatOfObjectDescription);
			}
			else {
				ret.push_back(stoi(temp));
			}
		}
	}
	if (ret.size() != argc) {
		throw CoreException(WrongFormatOfObjectDescription);
	}
	return ret;
}

inline void checkPara(const std::vector<int> para) {
	if (para.size() == 4) {
		for (int i = 0; i < 4; i++) {
			if (para.at(i) < MIN_COORDINATE || para.at(i) > MAX_COORDINATE) {
				throw CoreException(CoordinateValueExceed);
			}
		}
		if (para.at(0) == para.at(2) && para.at(1) == para.at(3)) {
			throw CoreException(TwoPointsCoincideOfLine);
		}
	}
	else {
		//para.size() == 3
		for (int i = 0; i < 2; i++) {
			if (para.at(i) < MIN_COORDINATE || para.at(i) > MAX_COORDINATE) {
				throw CoreException(CoordinateValueExceed);
			}
		}
		if (para.at(2) < MIN_RADIUS || para.at(2) > MAX_COORDINATE) {
			throw CoreException(InvalidRadiusOfCircle);
		}
	}
}