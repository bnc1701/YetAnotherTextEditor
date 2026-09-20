#include "editor.h"

#include <iostream>
#include <string>

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
    std::cout << "  :help          display available commands\n";
    std::cout << "  :open <file>   open a file\n";
    std::cout << "  :save          save the current file\n";
    std::cout << "  :save <file>   save to a specific file\n";
    std::cout << "  :print         print the current buffer\n";
    std::cout << "  :new           clear the current buffer\n";
    std::cout << "  :q             quit the editor\n";
}

// main editor loop
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
        std::string path = input.substr(6);
        if (path.empty()) {
            std::cout << "usage: :save <file>\n";
            return;
        }
        save_file(path);
        return;
    }

    if (input.rfind(":open ", 0) == 0) {
        std::string path = input.substr(6);
        if (path.empty()) {
            std::cout << "usage: :open <file>\n";
            return;
        }
        open_file(path);
        return;
    }

    std::cout << "unknown command, type :help for available commands\n";
}

// open a file and load it into the current session buffer
void editor::open_file(const std::string& path) {
    if (!buffer_.load_file(path)) {
        std::cout << "error: could not open file: " << path << '\n';
        return;
    }

    std::cout << "opened file: " << path << '\n';
    buffer_.print();
}

// save the current buffer to a specific path
void editor::save_file(const std::string& path) const {
    if (!buffer_.save_file(path)) {
        std::cout << "error: could not save file: " << path << '\n';
        return;
    }

    std::cout << "saved file: " << path << '\n';
}

// save the active file if one was opened earlier
void editor::save_current_file() const {
    std::string current_file = buffer_.current_file();
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

// clear the current working buffer
void editor::create_new_buffer() {
    buffer_.clear();
    std::cout << "current buffer cleared\n";
}

// stop the editor loop
void editor::quit() {
    running_ = false;
    std::cout << "goodbye\n";
}
