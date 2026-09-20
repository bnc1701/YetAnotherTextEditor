# YetAnotherTextEditor

A tiny terminal text editor written in C++.

## What it does

- open an existing file
- create a new empty buffer
- append text as new lines
- print the current buffer
- save the file
- quit the editor

## Project structure

```text
YetAnotherTextEditor/
├── src/
│   ├── main.cpp
│   ├── editor.cpp
│   └── buffer.cpp
├── include/
│   ├── editor.h
│   └── buffer.h
├── Makefile
├── README.md
├── .gitignore
└── LICENSE
```

## Build

```bash
make
```

This produces the binary `yetanothertexteditor` in the project root.

## Run

```bash
./yetanothertexteditor
```

## Commands

```text
:help          display available commands
:open <file>   open a file
:save          save the current file
:save <file>   save to a specific file
:print         print the current buffer
:new           clear the current buffer
:q             quit the editor
```

Any other line is treated as a new line of text to insert into the buffer.

## License

MIT License.
