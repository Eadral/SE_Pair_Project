#include "exception.h"

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
