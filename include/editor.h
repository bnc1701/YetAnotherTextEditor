#ifndef EDITOR_H
#define EDITOR_H

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
    void create_new_buffer();
    void edit_line(const std::string& line_number, const std::string& new_text);
    void delete_line(const std::string& line_number);
    void quit();

    bool running_;
    buffer buffer_;
};

#endif
