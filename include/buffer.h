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
    bool insert_line(std::size_t index, const std::string& line);
    bool edit_line(std::size_t index, const std::string& line);
    bool remove_line(std::size_t index);
    std::vector<std::size_t> find_lines(const std::string& text) const;
    std::string current_file() const;
    void set_current_file(const std::string& path);
    std::size_t size() const;
    bool empty() const;
    void print() const;

private:
    std::vector<std::string> lines_;
    std::string current_file_;
};

#endif
