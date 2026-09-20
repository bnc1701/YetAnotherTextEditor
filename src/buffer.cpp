#include "buffer.h"

#include <fstream>
#include <iostream>
#include <string>

Buffer::Buffer() : current_file_() {}

void Buffer::clear() {
    lines_.clear();
    current_file_.clear();
}

bool Buffer::loadFile(const std::string& path) {
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

bool Buffer::saveFile(const std::string& path) const {
    std::ofstream output(path, std::ios::out | std::ios::trunc);
    if (!output) {
        return false;
    }

    for (const std::string& line : lines_) {
        output << line << '\n';
    }

    return true;
}

void Buffer::appendLine(const std::string& line) {
    lines_.push_back(line);
}

std::string Buffer::currentFile() const {
    return current_file_;
}

void Buffer::setCurrentFile(const std::string& path) {
    current_file_ = path;
}

const std::vector<std::string>& Buffer::lines() const {
    return lines_;
}

void Buffer::print() const {
    for (std::size_t i = 0; i < lines_.size(); ++i) {
        std::cout << i + 1 << ": " << lines_[i] << '\n';
    }
}
