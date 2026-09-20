# yetanothertexteditor

a tiny terminal text editor written in c++

## what it does

- open existing files
- create empty buffers
- append text as new lines
- insert, edit and delete lines
- search for text in the buffer
- print the current buffer with line numbers
- save the buffer to a file
- quit from the terminal

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
:help                  display available commands
:open <file>           open a file
:save                  save the current file
:save <file>           save to a specific file
:print                 print the current buffer
:insert <n> <text>     insert a line before line n
:edit <n> <text>       replace a line
:delete <n>            delete a line
:search <text>         find matching lines
:new                   clear the current buffer
:q                     quit the editor
```

any other non-empty line is treated as a new line of text to insert into the buffer

line numbers start at one. `:insert 1 text` inserts before the first line. to append a line, use a number one larger than the current line count

## license

mit license
