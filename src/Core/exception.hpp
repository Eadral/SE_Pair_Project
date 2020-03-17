#pragma once
#include <exception>
#include <string>

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

std::string ExpectionString(int exc_code) {
	switch (exc_code) {
	case WrongFormatOfN: return "E100: N值格式错误";
	case InvalidValueOfN: return "E101: N值非法";
	case WrongFormatOfObjectIdentifier: return "E200: 几何对象标识符格式错误";
	case WrongFormatOfObjectDescription: return "E300: 几何对象描述错误";
	case CoordinateValueExceed: return "E301: 输入坐标分量超限";
	case TwoPointsCoincideOfLine: return "E302: 线的两点坐标重合";
	case InvalidRadiusOfCircle: return "E303: 圆的半径非法";
	case ObjectInputTooLittle: return "E400: 输入几何对象过少";
	case ObjectInputTooMuch: return "E401: 输入几何对象过多";
	case InfiniteIntersectionsFound: return "E500: 有无穷多交点";
	case ElementToDeleteNotFound: return "E600: 找不到要删除的元素";
	}
	return "NoExpection";
}

struct CoreException : public std::exception
{
	int exc_code;
	int line_number;
	int line2_number;
	CoreException(const int exc_code,  const int line_number = 1, const int line2_number = 1) 
		noexcept:exc_code(exc_code), line_number(line_number), line2_number(line2_number) {}
	const std::string showExceptionMessage() noexcept
	{
		if (exc_code == InfiniteIntersectionsFound) {
			return ExpectionString(exc_code) + " on line " + std::to_string(line_number) + " and " + std::to_string(line2_number);
		}
		else if (exc_code == ElementToDeleteNotFound) {
			return ExpectionString(exc_code);
		}
		else {
			return ExpectionString(exc_code) + " on line " + std::to_string(line_number);
		}		
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
		for (int i = 0; i < 3; i++) {
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
		for (int i = 0; i < 1; i++) {
			if (para.at(i) < MIN_COORDINATE || para.at(i) > MAX_COORDINATE) {
				throw CoreException(CoordinateValueExceed);
			}
		}
		if (para.at(2) < MIN_RADIUS || para.at(2) > MAX_COORDINATE) {
			throw CoreException(InvalidRadiusOfCircle);
		}
	}
}