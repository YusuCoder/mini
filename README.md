# 42Cursus Minishell

### Project overview for 42Minishell 
![GitHub last commit](https://img.shields.io/github/last-commit/YusuCoder/minishell)
![GitHub code size in bytes](https://img.shields.io/github/languages/code-size/YusuCoder/minishell)
![GitHub repo size](https://img.shields.io/github/repo-size/YusuCoder/minishell)
![GitHub language count](https://img.shields.io/github/languages/count/YusuCoder/minishell)
![GitHub contributors](https://img.shields.io/github/contributors/YusuCoder/minishell)

## [About](#about) | [Supported Features](#supported-features) | [Tests](#test-examples) | [Run the Program](#run-the-program) | [Study Summary](#study-summary)


# :speaking_head: About
> The objective of this project is for us to create a simple shell. Yes, out own little bash or zsh. We will lear a lot about processes and file descriptors and This project was one of the most challenging yet
  indulging projects of the 42 curriculum that I have faced so far, when you have to deal with many test cases and when you get to learn many things, from software architecture, system calls, file descriptors… to team coordination, management, and work distribution

# :hammer_and_wrench: Supported Features

### Minishell is a miniature shell program based on Bash and it suppports:
- Ponmpt display
- Command history(up and down arrows)
- System executables available from the environment(ls, cat, grep ... etc.)
- Local executable(./minishell)
- Builtin commands :
   - `echo` (with option -n)
   - `cd` (with ~ (tilde) flag, - (prev. dir), absalute and relative paths)
   - `pwd` (with no options)
   - `export` (with no options)
   - `unset` (with no options)
   - `exit` (with exit number)
   - `env` (with no options or arguments)
- Pipes `|` with redirect output from one command to input for the next
- Redirections:
     - `>` redirects output
     - `>>` redirects output in append mode
     - `<` redirects input
     - `<< DELIMETER` Heredoc displays a new prompt, reads user input untill reachinig DELIMETER, redirects user input to command input (does not update history)
- Environment variables (i.e. `$USER` or `$VAR`) that expand to their values.
    - `$?` expands to the exit status of last executed foreground pipeline.
- User keybord signals:
     - `Ctrl+C` displays new prompt line in interactive mode (Parent process), in non-interactive mode (child process) interupts process with the signal `SIGINT` and updates exit_status to 131.
     - `Ctrl+D` exits any  kind of process (if the prompt is empty)
     - `Ctrl+\` does nothing in interactive mode (parent process) and in non-interactive mode (child process) sends the signal `SIGQUIT` to interupt non-interactive process.
> [!NOTE]
> Minishell does not support `\`, `;`, `&&`, `||`, or `wildcards`

# :rocket: Test examples: 

> ### REDIRECTIONS
  - `>` (rederction of output)
    
  - ![redir.png](https://github.com/YusuCoder/minishell/blob/master/test_pics/redir.png)

  - `>>` (redirection of output in append mode)

  - ![append.png](https://github.com/YusuCoder/minishell/blob/master/test_pics/append.png)

  - `<<` (HEREDOC)

  - ![heredoc.png](https://github.com/YusuCoder/minishell/blob/master/test_pics/heredoc.png)

  - `|` (PIPES)

  - ![pipe.png](https://github.com/YusuCoder/minishell/blob/master/test_pics/pipe.png)

  - `export` (EXPORT)

  - ![export.png](https://github.com/YusuCoder/minishell/blob/master/test_pics/export.png)

  - `unset` (UNSET)

  - ![unset.png](https://github.com/YusuCoder/minishell/blob/master/test_pics/unset.png)




> [!TIP]
> For more test cases you can clone the repo and run the program :shushing_face:


# :hammer_and_pick: Run the program
## Unix
  > Clone the repository:
```

  git clone https://github.com/YusuCoder/minishell.git

``` 
> Go to the root folder run following commands:
```

      make
      ./minishell

```


    
