#ifndef BUFFER_H
#define BUFFER_H

#include <string>
#include <vector>

class Buffer {
public:
    Buffer();

    void clear();
    bool loadFile(const std::string& path);
    bool saveFile(const std::string& path) const;
    void appendLine(const std::string& line);
    std::string currentFile() const;
    void setCurrentFile(const std::string& path);
    const std::vector<std::string>& lines() const;
    void print() const;

private:
    std::vector<std::string> lines_;
    std::string current_file_;
};

#endif
