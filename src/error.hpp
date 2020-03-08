#pragma once

enum Error {
    MaxPointsExceed = 1,
    InvalidInput,
};


std::string ErrorString(int err_code) {
    switch (err_code) {
    case MaxPointsExceed: return "MaxPointsExceed";
    case InvalidInput: return "InvalidInput";
    }
}