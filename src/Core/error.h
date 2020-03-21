#pragma once
#include <string>

#include "intersect_dll.h"

enum Error {
    MaxPointsExceed = 1,
    InvalidInput,
};


INTERSECT_API std::string ErrorString(int err_code);