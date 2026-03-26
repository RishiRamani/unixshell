# 🖥️ Unix Shell in C

A fully functional Unix-like shell built from scratch in C, implementing core operating system concepts such as process management, inter-process communication, and signal handling.

---

## 🚀 Features

* 🔹 Execute system commands using `fork()` and `execvp()`
* 🔹 Built-in commands:

  * `cd`
  * `exit`
* 🔹 Input/Output Redirection:

  * `>` overwrite output
  * `>>` append output
  * `<` input redirection
* 🔹 Multi-stage Pipelines:

  ```bash
  ls | grep txt | wc
  ```
* 🔹 Background Execution:

  ```bash
  sleep 5 &
  ```
* 🔹 Signal Handling:

  * Ctrl+C (`SIGINT`) handled correctly
  * Shell remains active while terminating foreground processes

---

## 🧠 Core Concepts Demonstrated

This project showcases strong understanding of:

* Process creation (`fork`)
* Program execution (`execvp`)
* Inter-process communication (`pipe`)
* File descriptor manipulation (`dup2`)
* Signal handling (`SIGINT`)
* Concurrent execution (foreground vs background)
* Command parsing and tokenization

---

## 📁 Project Structure

```bash
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

### Compile

```bash
make
```

### Run

```bash
./unixshell
```

### Clean

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
* Limited syntax error handling

---

## 📈 Future Improvements

* Job control (foreground/background switching)
* Command history support
* Auto-completion
* Advanced parsing (quotes, escape characters)

---

## 💡 Why this project stands out

* Implements **multi-process pipelines**
* Handles **low-level file descriptor manipulation**
* Demonstrates **real OS concepts (not just syntax)**
* Clean modular architecture

---

## 👨‍💻 Author

Built as a systems programming project to understand how real Unix shells work internally.

---

## ⭐ If you like this project

Give it a star ⭐ — it helps!
## 📸 Demo

![Demo](https://github.com/user-attachments/assets/bc1c6e78-1e9a-4180-aaa9-97f39f122a12)
