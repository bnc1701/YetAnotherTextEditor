#ifndef BUFFER_H
#define BUFFER_H

#include <cstddef>
#include <string>
#include <vector>

class buffer {
public:
    buffer();

    void clear();
    bool load_file(const std::string& path);
    bool save_file(const std::string& path) const;
    void append_line(const std::string& line);
    void edit_line(std::size_t index, const std::string& line);
    void remove_line(std::size_t index);
    std::string current_file() const;
    void set_current_file(const std::string& path);
    const std::vector<std::string>& lines() const;
    std::size_t size() const;
    bool empty() const;
    void print() const;

private:
    std::vector<std::string> lines_;
    std::string current_file_;
};

#endif
