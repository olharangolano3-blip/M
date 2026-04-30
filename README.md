*This project has been created as part of the 42 curriculum by dalde-ol, adjigo.*

# Minishell — As beautiful as a shell

## Description

Minishell is a minimal Unix shell written in C, built as part of the 42 curriculum.
The goal is to recreate the core behaviour of Bash: reading user input, parsing it
into commands, expanding variables, handling redirections and pipes, and executing
programs via `execve`.

The project covers the following features:

- Interactive prompt with command history (via `readline`)
- Execution of commands using the `PATH` variable or absolute/relative paths
- Input/output redirections: `<`, `>`, `>>`, and heredoc `<<`
- Pipes (`|`) connecting commands in a pipeline
- Environment variable expansion (`$VAR`, `$?`)
- Single (`'`) and double (`"`) quote handling
- Signal handling: `ctrl-C`, `ctrl-D`, `ctrl-\`
- One global variable (`g_signal`) used exclusively to store received signal numbers
- The following built-in commands:
  - `echo` with option `-n`
  - `cd` with relative or absolute path
  - `pwd`
  - `export`
  - `unset`
  - `env`
  - `exit`

## Instructions

### Requirements

- GCC or compatible C compiler
- GNU Make
- readline library (`libreadline-dev` on Debian/Ubuntu)

### Compilation

```bash
make
```

This compiles `libft` automatically and links the final binary `minishell`.

### Usage

```bash
./minishell
```

The shell displays a prompt and waits for commands. Type `exit` or press `ctrl-D`
to quit.

### Makefile rules

| Rule     | Description                          |
|----------|--------------------------------------|
| `all`    | Compiles the project                 |
| `clean`  | Removes object files                 |
| `fclean` | Removes objects and binary           |
| `re`     | Full recompilation                   |

### Common usage examples

```bash
# Basic command
ls -la

# Pipes
cat file.txt | grep hello | wc -l

# Redirections
echo "hello" > out.txt
cat < out.txt >> log.txt

# Environment variables
export MY_VAR=42
echo $MY_VAR
unset MY_VAR

# Heredoc
cat << EOF
line one
line two
EOF

# Exit status
ls nonexistent
echo $?
```

### Notes on behaviour

- `unset VARNAME` removes a variable. Do **not** use `unset $VARNAME`
  (the shell expands `$VARNAME` to its value before running `unset`,
  which is the same behaviour as Bash).
- `readline` may cause memory leaks that are not required to be fixed,
  as documented by the subject.
- `&&`, `||`, parentheses and wildcards `*` are bonus features and
  are not implemented in the mandatory part.

## Resources

### References

- [Bash Reference Manual](https://www.gnu.org/software/bash/manual/bash.html)
- [GNU readline documentation](https://tiswww.case.edu/php/chet/readline/rltop.html)
- [The Open Group — Shell Command Language](https://pubs.opengroup.org/onlinepubs/9699919799/utilities/V3_chap02.html)
- [Linux man pages: execve(2), fork(2), pipe(2), dup2(2), waitpid(2)](https://man7.org/linux/man-pages/index.html)
- [Writing a Unix Shell — Part I, II, III (Akash Mahajan)](https://indradhanush.github.io/blog/writing-a-unix-shell-part-1/)
- [CS 341 — Shell MP (University of Illinois)](https://cs341.cs.illinois.edu/assignments/shell.html)

### AI usage

AI tools (Claude) were used during the development of this project in the
following ways:

- **Architecture planning:** discussing the tokenizer → parser → expander →
  executor pipeline structure and data flow before writing code.
- **Debugging assistance:** identifying the root cause of environment variable
  issues (specifically, `env_set` not adding new variables when they did not
  already exist in the environment array).
- **Code review:** checking Norm compliance, identifying functions exceeding
  25 lines, files with more than 5 functions, and forbidden `//` comments.
- **Documentation:** drafting this README.

All AI-generated suggestions were reviewed, tested, and understood before being
incorporated into the project. No code was copied without full comprehension.