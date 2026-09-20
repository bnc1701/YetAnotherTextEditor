#ifndef BUFFER_H
#define BUFFER_H

#include <string>
#include <vector>

class buffer {
public:
    buffer();

    void clear();
    bool load_file(const std::string& path);
    bool save_file(const std::string& path) const;
    void append_line(const std::string& line);
    std::string current_file() const;
    void set_current_file(const std::string& path);
    const std::vector<std::string>& lines() const;
    void print() const;

private:
    std::vector<std::string> lines_;
    std::string current_file_;
};

#endif
