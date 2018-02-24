# DS-curriculum-design

## About

Project: Hust Data structure curriculum design 2018 winter.

Name: Friends, followers and followings manage system.[Based in AVL tree]

License: `GNU GENERAL PUBLIC LICENSE V3.0`

Developing language: C

## Requirements

Platform: `GNU/Linux x86_64`

Compiler: `gcc version 7.3.0 or more`

CMake： `VERSION 3.9`

## Project Introduction

A friends, followers and followings manage system developed in 2018 winter, with a shell-like interface. The user database built by Hash table, the friend, followers and following set built by AVL tree. The whole requirements can be seen in `Requirements&Report` file.

## Usage

py_manager [options]

* -h: Print help messages
* -p: Hide the prompt
* default: Start shell

**The User's Manual can be seen when you type "help" in shell**

## File Structure

```
./
 ├── Makefile
 ├── main.c
 └── src/
      ├── data/
      │
      ├── prompt/
      │     ├── py_exec.c
      │     ├── py_prompt.c
      │     └── Makefile
      ├── avltree.h
      ├── avltree.c
      ├── set.h
      ├── set.c
      ├── hashtable.h
      ├── hashtable.c
      └── Makefile
```

Finished by Pan Yue 2018.2.24