#include "error.h"

std::string ErrorString(int err_code) {
    switch (err_code) {
    case MaxPointsExceed: return "MaxPointsExceed";
    case InvalidInput: return "InvalidInput";
    }
    return "NoError";
}