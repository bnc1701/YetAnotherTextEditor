# yetanothertexteditor

a tiny terminal text editor written in c++

## what it does

- open an existing file
- create a new empty buffer
- append text as new lines
- print the current buffer
- save the file
- quit the editor

## project structure

```text
yetanothertexteditor/
├── src/
│   ├── main.cpp
│   ├── editor.cpp
│   └── buffer.cpp
├── include/
│   ├── editor.h
│   └── buffer.h
├── makefile
├── readme.md
├── .gitignore
└── license
```

## build

```bash
make
```

this produces the binary `yetanothertexteditor` in the project root

## run

```bash
./yetanothertexteditor
```

## commands

```text
:help          display available commands
:open <file>   open a file
:save          save the current file
:save <file>   save to a specific file
:print         print the current buffer
:new           clear the current buffer
:q             quit the editor
```

any other non-empty line is treated as a new line of text to insert into the buffer

## license

mit license
