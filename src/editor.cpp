#include "editor.h"

#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>

// create the editor and keep the state alive during the session
editor::editor() : running_(true), buffer_() {}

// show the initial welcome text
void editor::print_welcome_message() const {
    std::cout << "yetanothertexteditor\n";
    std::cout << "type :help for commands\n";
}

// list the available commands
void editor::print_help() const {
    std::cout << "commands:\n";
    std::cout << "  :help                  display available commands\n";
    std::cout << "  :open <file>           open a file\n";
    std::cout << "  :save                  save the current file\n";
    std::cout << "  :save <file>           save to a specific file\n";
    std::cout << "  :print                 print the current buffer\n";
    std::cout << "  :insert <n> <text>     insert a line before line n\n";
    std::cout << "  :edit <n> <text>       replace a line\n";
    std::cout << "  :delete <n>            delete a line\n";
    std::cout << "  :search <text>         find matching lines\n";
    std::cout << "  :new                   clear the current buffer\n";
    std::cout << "  :q                     quit the editor\n";
}

// keep reading input until the user quits
void editor::run() {
    print_welcome_message();

    while (running_) {
        std::cout << "yetanothertexteditor> ";

        std::string input;
        if (!std::getline(std::cin, input)) {
            break;
        }

        if (input.empty()) {
            continue;
        }

        if (input.rfind(":", 0) == 0) {
            handle_command(input);
            continue;
        }

        buffer_.append_line(input);
        std::cout << "inserted line\n";
    }
}

// handle all command inputs starting with a colon
void editor::handle_command(const std::string& input) {
    if (input == ":help") {
        print_help();
        return;
    }

    if (input == ":q") {
        quit();
        return;
    }

    if (input == ":print") {
        print_buffer();
        return;
    }

    if (input == ":new") {
        create_new_buffer();
        return;
    }

    if (input == ":save") {
        save_current_file();
        return;
    }

    if (input.rfind(":save ", 0) == 0) {
        const std::string path = input.substr(6);
        if (path.empty()) {
            std::cout << "usage: :save <file>\n";
            return;
        }
        save_file(path);
        return;
    }

    if (input.rfind(":open ", 0) == 0) {
        const std::string path = input.substr(6);
        if (path.empty()) {
            std::cout << "usage: :open <file>\n";
            return;
        }
        open_file(path);
        return;
    }

    if (input.rfind(":insert ", 0) == 0) {
        const std::string payload = input.substr(8);
        const std::size_t space_pos = payload.find(' ');
        if (space_pos == std::string::npos) {
            std::cout << "usage: :insert <line> <text>\n";
            return;
        }

        insert_line(payload.substr(0, space_pos), payload.substr(space_pos + 1));
        return;
    }

    if (input.rfind(":edit ", 0) == 0) {
        const std::string payload = input.substr(6);
        const std::size_t space_pos = payload.find(' ');
        if (space_pos == std::string::npos) {
            std::cout << "usage: :edit <line> <text>\n";
            return;
        }

        edit_line(payload.substr(0, space_pos), payload.substr(space_pos + 1));
        return;
    }

    if (input.rfind(":delete ", 0) == 0) {
        const std::string line_number = input.substr(8);
        if (line_number.empty()) {
            std::cout << "usage: :delete <line>\n";
            return;
        }
        delete_line(line_number);
        return;
    }

    if (input.rfind(":search ", 0) == 0) {
        const std::string text = input.substr(8);
        if (text.empty()) {
            std::cout << "usage: :search <text>\n";
            return;
        }
        search_text(text);
        return;
    }

    std::cout << "unknown command, type :help for available commands\n";
}

// open a file and load it into the current buffer
void editor::open_file(const std::string& path) {
    if (!buffer_.load_file(path)) {
        std::cout << "error: could not open file: " << path << '\n';
        return;
    }

    std::cout << "opened file: " << path << '\n';
    buffer_.print();
}

// save the current buffer and remember the path for later saves
void editor::save_file(const std::string& path) {
    if (!buffer_.save_file(path)) {
        std::cout << "error: could not save file: " << path << '\n';
        return;
    }

    buffer_.set_current_file(path);
    std::cout << "saved file: " << path << '\n';
}

// save the active file if one was opened earlier
void editor::save_current_file() {
    const std::string current_file = buffer_.current_file();
    if (current_file.empty()) {
        std::cout << "no file is currently open, use :save <file>\n";
        return;
    }

    save_file(current_file);
}

// print the current buffer content
void editor::print_buffer() const {
    buffer_.print();
}

// clear the current working buffer and its file path
void editor::create_new_buffer() {
    buffer_.clear();
    std::cout << "current buffer cleared\n";
}

// parse a positive one based line number
bool editor::parse_line_number(const std::string& text, std::size_t& line_index) const {
    if (text.empty()) {
        return false;
    }

    try {
        std::size_t parsed_length = 0;
        const unsigned long long line_number = std::stoull(text, &parsed_length);
        if (parsed_length != text.size() || line_number == 0) {
            return false;
        }
        line_index = static_cast<std::size_t>(line_number - 1);
    } catch (const std::exception&) {
        return false;
    }

    return true;
}

// insert a line before the selected line number
void editor::insert_line(const std::string& line_number, const std::string& text) {
    std::size_t line_index = 0;
    if (!parse_line_number(line_number, line_index)) {
        std::cout << "invalid line number\n";
        return;
    }

    if (!buffer_.insert_line(line_index, text)) {
        std::cout << "line out of range\n";
        return;
    }

    std::cout << "line inserted\n";
}

// replace the content of a line by its number
void editor::edit_line(const std::string& line_number, const std::string& new_text) {
    std::size_t line_index = 0;
    if (!parse_line_number(line_number, line_index)) {
        std::cout << "invalid line number\n";
        return;
    }

    if (!buffer_.edit_line(line_index, new_text)) {
        std::cout << "line out of range\n";
        return;
    }

    std::cout << "line updated\n";
}

// remove one line from the buffer by number
void editor::delete_line(const std::string& line_number) {
    std::size_t line_index = 0;
    if (!parse_line_number(line_number, line_index)) {
        std::cout << "invalid line number\n";
        return;
    }

    if (!buffer_.remove_line(line_index)) {
        std::cout << "line out of range\n";
        return;
    }

    std::cout << "line removed\n";
}

// print every line containing the requested text
void editor::search_text(const std::string& text) const {
    const std::vector<std::size_t> matches = buffer_.find_lines(text);
    if (matches.empty()) {
        std::cout << "no matches found\n";
        return;
    }

    for (const std::size_t index : matches) {
        std::cout << index + 1 << ": " << buffer_.lines()[index] << '\n';
    }
}

// stop the editor loop
void editor::quit() {
    running_ = false;
    std::cout << "goodbye\n";
}
