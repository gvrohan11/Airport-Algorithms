#pragma once
#include <iostream>
#include <string>

/**
* @brief A progress bar to show whatever progress you want
* Intended for use in an ostream
*/
class ProgressBar {
private:
    int length_; // the length of the printed bar (not including ends)
    double progress_; // the proportion of progress made (between 0 and 1)
public:
    /**
    * @brief Constructs the ProgressBar class starting at 0 progress
    *
    * @param length The bar's length
    */
    ProgressBar(int length = 70) : length_(length), progress_(0) {}
    
    /**
    * @brief Gets the length of the progress bar
    *
    * @return int The length
    */
    int getLength() const { return length_; }

    /**
    * @brief Gets the progress of the progress bar
    *
    * @return int The progress
    */
    double getProgress() const { return progress_; }

    /**
    * @brief Sets the length
    *
    * @param length The new length
    */
    void setLength(int length)  { length_ = length; }

    /**
    * @brief Sets the progress
    *
    * @param progress The new progress
    */
    void setProgress(double progress)  { progress_ = progress; }

    /**
    * @brief Gets a string representing the progress bar
    * It will have [ and ] as its endpoints and be filled with
    * An appropriate amount of =
    *
    * @return string The progress bar string
    */
    std::string toString() const;

};

/**
* @brief Overloads the << operator to output a progress bar
* Will overwrite the previous line
*
* @param out The output stream
* @param pb The progress bar
* @return ostream The output stream
*/
std::ostream & operator<<(std::ostream & out, const ProgressBar & pb);
