# 🖥️ Unix Shell (C)

A custom Unix-like shell built from scratch in C, implementing core operating system concepts such as process management, inter-process communication, and signal handling.

---

## 🚀 Features

* 🔹 Command execution using `fork()` and `execvp()`
* 🔹 Built-in commands:

  * `cd`
  * `exit`
* 🔹 Input/Output Redirection:

  * `>` (overwrite)
  * `>>` (append)
  * `<` (input)
* 🔹 Multiple Pipes:

  ```bash
  ls | grep txt | wc
  ```
* 🔹 Background Execution:

  ```bash
  sleep 5 &
  ```
* 🔹 Signal Handling:

  * Ctrl+C (`SIGINT`) does NOT terminate the shell
  * Proper handling of foreground processes

---

## 🧠 Concepts Implemented

This project demonstrates strong understanding of:

* Process creation (`fork`)
* Program execution (`execvp`)
* Inter-process communication (`pipe`)
* File descriptor manipulation (`dup2`)
* Signal handling (`SIGINT`)
* Foreground vs background execution
* Command parsing and tokenization

---

## 📁 Project Structure

```
unixshell/
├── src/
│   ├── main.c
│   ├── parser.c
│   ├── executor.c
│   ├── builtins.c
│   ├── redirection.c
│
├── include/
│   └── shell.h
│
├── Makefile
└── README.md
```

---

## 🛠️ Build & Run

### Compile:

```bash
make
```

### Run:

```bash
./unixshell
```

### Clean:

```bash
make clean
```

---

## 🧪 Example Usage

```bash
myshell> ls
myshell> ls | wc
myshell> cat file.txt | grep hello | wc
myshell> echo hello > file.txt
myshell> sleep 5 &
```

---

## ⚠️ Limitations

* No job control (`fg`, `bg`)
* No command history
* Limited error handling for complex syntax

---

## 📈 Future Improvements

* Job control (foreground/background switching)
* Command history and navigation
* Tab auto-completion
* Advanced parsing (quotes, escape characters)

---

## 💡 Author Notes

This project was built to deeply understand how Unix shells work internally, focusing on system-level programming rather than relying on libraries.

---

## ⭐ Why this project stands out

* Implements **multi-process pipelines**
* Handles **low-level file descriptor manipulation**
* Demonstrates **real OS concepts**, not just syntax
* Clean modular structure (parser, executor, redirection)

---

## 📜 License

MIT License
