*This project has been created as part of the 42 curriculum by <erzhuo> and <ziyang>.*

# minishell

## Description

**minishell** is a 42 School project whose goal is to build a simplified, working command-line interpreter (shell) in C, similar in spirit to `bash`.

The purpose of the project is to understand, from the inside, how a shell actually works: how a line of user input is read, tokenized, parsed, expanded and finally turned into one or several processes connected by pipes and redirections. It forces a deep dive into POSIX process and file-descriptor management (`fork`, `execve`, `pipe`, `dup2`, `wait`), signal handling, and manual parsing/lexing without relying on any shell grammar library.

Our implementation supports:

- An interactive prompt built on the **readline** library, with command history.
- **Pipes** (`|`) chaining any number of simple commands together.
- **Redirections**: input (`<`), output (`>`), append (`>>`) and heredoc (`<<`).
- **Environment variable expansion**  inside single/double quotes according to shell quoting rules.
- The following **builtins**, implemented internally (not calling `/bin/...`):
  - `cd`
  - `pwd`
  - `echo` (with `-n` option only)
  - `export` (with and without arguments)
  - `unset`
  - `env`
  - `exit` 
- Correct **exit status** propagation (`$?`), including for signals (SIGINT/SIGQUIT).
- Signal handling matching bash's interactive behavior (`Ctrl-C`, `Ctrl-D`, `Ctrl-\`).
- Execution of external binaries found via `PATH`, or via relative/absolute paths.
- The input line is turned into commands through a small **parsing pipeline**:
  - **Lexer** (`lexer.c`, `lexer_helper.c`) — splits the line into tokens (`WORD`, `|`, `<`, `>`, `<<`, `>>`); quotes are scanned as a block, so spaces and operators inside them stay literal.
  - **Syntax check** (`syntax_check.c`) — rejects invalid token sequences (leading `|`, trailing operator, `| |`, redirection with no target) and unclosed quotes, setting `$?` to `2`.
  - **Parser** (`parser.c`, `parser_helper.c`) — groups tokens into a list of commands split on `|`, each with a NULL-terminated `argv` and an ordered list of redirections.
  - **Expander** (`expander.c`, `expander_helper_core.c`, `expander_helper_is.c`, `expander_helper_rm.c`) — one left-to-right pass per string doing `$VAR` / `$?` substitution and quote removal together; expanded text is never re-scanned, so a value's own quotes and `$` stay literal.
  
## Instructions

### Compilation

From the root of the repository:

```bash
make
```

This builds the `libft` dependency (if needed) and compiles the project, producing the `minishell` executable at the project root.

Other standard Makefile targets are available:

```bash
make clean   # remove object files
make fclean  # remove object files and the executable
make re      # fclean + make
```

### Running

```bash
./minishell
```

This launches an interactive prompt (`minishell> `). Type any shell command as you would in `bash`:

```bash
minishell> echo "hello $USER"
minishell> ls -l | grep minishell
minishell> cat << EOF > out.txt
heredoc line
EOF
minishell> export Z=1
minishell> echo $Z
minishell> exit
```

`minishell` requires an interactive TTY on stdin/stdout/stderr; it will refuse to run otherwise (e.g. when piped input is used at startup).


## Resources

Classic references used to understand the topic and the underlying system calls:

- The Open Group Base Specifications — [POSIX Shell Command Language](https://pubs.opengroup.org/onlinepubs/9699919799/utilities/V3_chap02.html)
- Linux man pages: `fork(2)`, `execve(2)`, `pipe(2)`, `dup2(2)`, `wait(2)`/`waitpid(2)`, `signal(2)`, `readline(3)`, `access(2)`, `stat(2)`
- GNU Bash Reference Manual — [https://www.gnu.org/software/bash/manual/bash.html](https://www.gnu.org/software/bash/manual/bash.html) (used to cross-check quoting, expansion and builtin semantics)
- GNU Readline Library documentation — [https://tiswww.case.edu/php/chet/readline/readline.html](https://tiswww.case.edu/php/chet/readline/readline.html)
- Minishell: Building a Mini Bash — A 42 Project (Medium article walking through the design and implementation of a 42 minishell) -[https://m4nnb3ll.medium.com/minishell-building-a-mini-bash-a-42-project-b55a10598218]


### AI usage

AI assistance (claude) was used during this project in a supporting.
