#ifndef editor_h
#define editor_h

#include <string>

#include "buffer.h"

class editor {
public:
    editor();

    void run();

private:
    void print_welcome_message() const;
    void print_help() const;
    void handle_command(const std::string& input);
    void open_file(const std::string& path);
    void save_file(const std::string& path);
    void save_current_file();
    void print_buffer() const;
    void create_new_buffer(const std::string& path = "");
    void append_line(const std::string& text);
    void insert_line(const std::string& line_number, const std::string& text);
    void edit_line(const std::string& line_number, const std::string& new_text);
    void delete_line(const std::string& line_number);
    void search_text(const std::string& text) const;
    bool parse_line_number(const std::string& text, std::size_t& line_index) const;
    void quit();

    bool running_;
    buffer buffer_;
};

#endif
