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

// insert a line before the selected line number
bool buffer::insert_line(std::size_t index, const std::string& line) {
    if (index > lines_.size()) {
        return false;
    }

    lines_.insert(lines_.begin() + static_cast<std::ptrdiff_t>(index), line);
    return true;
}

// replace the content of a specific line by index
bool buffer::edit_line(std::size_t index, const std::string& line) {
    if (index >= lines_.size()) {
        return false;
    }

    lines_[index] = line;
    return true;
}

// remove a specific line by index
bool buffer::remove_line(std::size_t index) {
    if (index >= lines_.size()) {
        return false;
    }

    lines_.erase(lines_.begin() + static_cast<std::ptrdiff_t>(index));
    return true;
}

// find every line containing the requested text
std::vector<std::size_t> buffer::find_lines(const std::string& text) const {
    std::vector<std::size_t> matches;

    for (std::size_t i = 0; i < lines_.size(); ++i) {
        if (lines_[i].find(text) != std::string::npos) {
            matches.push_back(i);
        }
    }

    return matches;
}

// return the active file path, if there is one
std::string buffer::current_file() const {
    return current_file_;
}

// keep track of the file opened for the current session
void buffer::set_current_file(const std::string& path) {
    current_file_ = path;
}

// return the current number of lines
std::size_t buffer::size() const {
    return lines_.size();
}

// check whether the buffer has any content
bool buffer::empty() const {
    return lines_.empty();
}

// print the buffer contents with line numbers
void buffer::print() const {
    if (lines_.empty()) {
        std::cout << "buffer is empty\n";
        return;
    }

    for (std::size_t i = 0; i < lines_.size(); ++i) {
        std::cout << i + 1 << ": " << lines_[i] << '\n';
    }
}
