#include "exception.h"

std::string ExpectionString(int exc_code) {
    switch (exc_code) {
    case WrongFormatOfN: return "E100: Nֵ��ʽ����";
    case InvalidValueOfN: return "E101: Nֵ�Ƿ�";
    case WrongFormatOfObjectIdentifier: return "E200: ���ζ����ʶ����ʽ����";
    case WrongFormatOfObjectDescription: return "E300: ���ζ�����������";
    case CoordinateValueExceed: return "E301: ���������������";
    case TwoPointsCoincideOfLine: return "E302: �ߵ����������غ�";
    case InvalidRadiusOfCircle: return "E303: Բ�İ뾶�Ƿ�";
    case ObjectInputTooLittle: return "E400: ���뼸�ζ������";
    case ObjectInputTooMuch: return "E401: ���뼸�ζ������";
    case InfiniteIntersectionsFound: return "E500: ������ཻ��";
    case ElementToDeleteNotFound: return "E600: �Ҳ���Ҫɾ����Ԫ��";
    }
    return "NoExpection";
}
