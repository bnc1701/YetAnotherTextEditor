#include "buffer.h"

#include <fstream>
#include <iostream>
#include <string>

// keep the current file state for the active session
buffer::buffer() : current_file_() {}

// clear the current buffer and reset the active file path
void buffer::clear() {
    lines_.clear();
    current_file_.clear();
}

// read all lines from a file into the buffer
bool buffer::load_file(const std::string& path) {
    std::ifstream input(path);
    if (!input) {
        return false;
    }

    lines_.clear();
    std::string line;
    while (std::getline(input, line)) {
        lines_.push_back(line);
    }

    current_file_ = path;
    return true;
}

// save every line in the buffer back to disk
bool buffer::save_file(const std::string& path) const {
    std::ofstream output(path, std::ios::out | std::ios::trunc);
    if (!output) {
        return false;
    }

    for (const std::string& line : lines_) {
        output << line << '\n';
    }

    return true;
}

// append one more line to the end of the buffer
void buffer::append_line(const std::string& line) {
    lines_.push_back(line);
}

// return the active file path, if there is one
std::string buffer::current_file() const {
    return current_file_;
}

// keep track of the file opened for the current session
void buffer::set_current_file(const std::string& path) {
    current_file_ = path;
}

// expose the current lines for the editor
const std::vector<std::string>& buffer::lines() const {
    return lines_;
}

// print the buffer contents with line numbers
void buffer::print() const {
    for (std::size_t i = 0; i < lines_.size(); ++i) {
        std::cout << i + 1 << ": " << lines_[i] << '\n';
    }
}
