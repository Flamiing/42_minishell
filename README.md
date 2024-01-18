# <p align="center">🐚MINISHELL🐚</p>

### <p align="center">Environment variables, redirections, command execution, built-in commands and pipes</p>

---
## What is this project about? </br>
**Minishell** is a program written in **C** that behaves as a simplified version of an actual shell. You can use redirections, environment variables, pipes, built-in commands and execution of commands like you would in a normal shell.</br></br>

---
## Biggest Challenges 💪

I faced three major challenges while working on the project. Firstly, I had to learn and implement two complex concepts which were the parser and lexer. Then I faced the next two most difficult problems which were to handle the proper execution of commands that were inputted alongside pipes and/or redirections, and also ensuring the proper handling of exit codes. Additionally, it was challenging to deal with the Heredoc implementation so it worked as intended. </br></br> However, it was really interesting to learn about how to organize files and the different functions. If I had to redo the project, I would definitely take more time to design the code in a different way, even though I don't think the work was bad after all.

## Built-in Commands:
  This are commands that I had to program from scratch to implement them as built-in.
  | Command | Options |
  |---|---|
  |`echo`| With option `-n` |
  |`cd`| With only a relative or absolute path |
  |`pwd` | With no options |
  |`export`| With no options |
  |`unset`| With no options |
  |`env`| With no options or arguments |
  |`exit`| With no options |
  
## How to use?

```bash
# Clone the repository:
git clone git@github.com:Flamiing/42_minishell.git

# Access the folder:
cd 42_minishell/

# Compile the program:
make

# To run the program:
./minishell
```

## Demo
![minishell](https://github.com/Flamiing/42_minishell/assets/58707234/93409084-f57c-44a5-a423-14e635c99012)








