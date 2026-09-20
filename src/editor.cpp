#include "editor.h"

#include "buffer.h"

#include <iostream>
#include <string>

Editor::Editor() : running_(true) {}

void Editor::printWelcomeMessage() const {
    std::cout << "YetAnotherTextEditor\n";
    std::cout << "Type :help for commands.\n";
}

void Editor::printHelp() const {
    std::cout << "Commands:\n";
    std::cout << "  :help          display available commands\n";
    std::cout << "  :open <file>   open a file\n";
    std::cout << "  :save          save the current file\n";
    std::cout << "  :save <file>   save to a specific file\n";
    std::cout << "  :print         print the current buffer\n";
    std::cout << "  :new           clear the current buffer\n";
    std::cout << "  :q             quit the editor\n";
}

void Editor::run() {
    printWelcomeMessage();

    Buffer buffer;

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
            handleCommand(input);
            continue;
        }

        buffer.appendLine(input);
        std::cout << "Inserted line.\n";
    }
}

void Editor::handleCommand(const std::string& input) {
    Buffer buffer;

    if (input == ":help") {
        printHelp();
        return;
    }

    if (input == ":q") {
        quit();
        return;
    }

    if (input == ":print") {
        printBuffer();
        return;
    }

    if (input == ":new") {
        createNewBuffer();
        return;
    }

    if (input == ":save") {
        saveCurrentFile();
        return;
    }

    if (input.rfind(":save ", 0) == 0) {
        std::string path = input.substr(6);
        if (path.empty()) {
            std::cout << "Usage: :save <file>\n";
            return;
        }
        saveFile(path);
        return;
    }

    if (input.rfind(":open ", 0) == 0) {
        std::string path = input.substr(6);
        if (path.empty()) {
            std::cout << "Usage: :open <file>\n";
            return;
        }
        openFile(path);
        return;
    }

    std::cout << "Unknown command. Type :help for available commands.\n";
}

void Editor::openFile(const std::string& path) {
    Buffer buffer;
    if (!buffer.loadFile(path)) {
        std::cout << "Error: could not open file: " << path << '\n';
        return;
    }

    std::cout << "Opened file: " << path << '\n';
    buffer.print();
}

void Editor::saveFile(const std::string& path) const {
    Buffer buffer;
    if (!buffer.saveFile(path)) {
        std::cout << "Error: could not save file: " << path << '\n';
        return;
    }

    std::cout << "Saved file: " << path << '\n';
}

void Editor::saveCurrentFile() const {
    Buffer buffer;
    std::string current_file = buffer.currentFile();
    if (current_file.empty()) {
        std::cout << "No file is currently open. Use :save <file>\n";
        return;
    }

    saveFile(current_file);
}

void Editor::printBuffer() const {
    Buffer buffer;
    buffer.print();
}

void Editor::createNewBuffer() {
    Buffer buffer;
    buffer.clear();
    std::cout << "Current buffer cleared.\n";
}

void Editor::quit() {
    running_ = false;
    std::cout << "Goodbye.\n";
}
