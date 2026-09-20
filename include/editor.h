#ifndef EDITOR_H
#define EDITOR_H

#include <string>

#include "buffer.h"

class Editor {
public:
    Editor();

    void run();

private:
    void printWelcomeMessage() const;
    void printHelp() const;
    void handleCommand(const std::string& input);
    void openFile(const std::string& path);
    void saveFile(const std::string& path) const;
    void saveCurrentFile() const;
    void printBuffer() const;
    void createNewBuffer();
    void quit();

    bool running_;
    Buffer buffer_;
};

#endif
