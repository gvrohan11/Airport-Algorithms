#include "ProgressBar.h"
#include <sstream>
#include <iomanip>
#include <cmath>

using namespace std;

string ProgressBar::toString() const {
    int progressChars = round(length_ * progress_);
    string progressString = "";
    progressString += "[";
    for (int i = 0; i < length_; i++) {
        if (i < progressChars) {
            progressString += "=";
        } else {
            progressString += " ";
        }
    }
    progressString += "] ";
    stringstream stream;
    stream << fixed << setprecision(2) << progress_ * 100;
    progressString += stream.str() + "%";
    return progressString;
}

ostream & operator<<(ostream & out, const ProgressBar & pb) {
    out << "\r";
    out.flush();
    out << pb.toString();
    return out;
}
