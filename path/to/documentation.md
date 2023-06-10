# Minishell

![Minishell Logo](/path/to/logo.png)

## A Custom Shell Implementation

Minishell is a custom shell implementation project written in C. It provides a command-line interface for users to execute commands, manage processes, and perform various operations typically associated with a shell environment. This documentation will guide you through the installation process, explain the key features of Minishell, and provide usage instructions to help you make the most of its capabilities.

## Table of Contents
- [Installation](#installation)
- [Usage](#usage)
  - [Interactive Command Prompt](#interactive-command-prompt)
  - [Command History](#command-history)
  - [Command Execution](#command-execution)
  - [Redirection](#redirection)
  - [Pipes](#pipes)
  - [Environment Variable Expansion](#environment-variable-expansion)
  - [Signal Handling](#signal-handling)
  - [Built-in Commands](#built-in-commands)
- [Norm Compliance](#norm-compliance)
- [Memory Management](#memory-management)
- [Additional Resources](#additional-resources)

## Installation
To install and run Minishell, follow these steps:

1. Clone the Minishell repository to your local machine:
   ```bash
   git clone <repository-url>
   ```

2. Change to the project directory:
   ```bash
   cd Minishell
   ```

3. Build the project using the provided Makefile:
   ```bash
   make
   ```

4. Run Minishell:
   ```bash
   ./minishell
   ```

Now that you have Minishell up and running, let's explore its key features and learn how to use them effectively.

## Usage
### Interactive Command Prompt
Upon running Minishell, you will be presented with an interactive command prompt. This prompt indicates that Minishell is ready to accept your commands. You can start entering commands and executing them.

```
minishell >
```

### Command History
Minishell supports a command history feature, allowing you to navigate and repeat previously executed commands. To browse through the command history, use the up and down arrow keys. Press Enter to execute a selected command from the history.

### Command Execution
Minishell allows you to execute various commands, either built-in commands or external executables. To execute a command, simply type it in and press Enter. Minishell will search for the appropriate executable based on the PATH variable or the specified path.

```bash
minishell > ls -l
```

### Redirection
Minishell supports input and output redirection. You can redirect input from files or redirect output to files using the following operators:

- `<`: Redirects input from a file.
  ```bash
  minishell > cat < input.txt
  ```

- `>`: Redirects output to a file, overwriting the file if it already exists.
  ```bash
  minishell > echo "Hello, world!" > output.txt
  ```

- `>>`: Redirects output to a file, appending to the file if it already exists.
  ```bash
  minishell > echo "Additional content" >> output.txt
  ```

### Pipes
Minishell supports command pipelines using the pipe operator (`|`). You can connect the output of one command to the input of another, enabling complex command sequences.

```bash
minishell > ls -l | grep .txt
```

### Environment Variable Expansion
Minishell allows you to expand environment variables within command arguments. Simply prefix the variable name with a dollar sign `$`, and Minishell will replace it with the corresponding value.

```bash


minishell > echo $HOME
```

### Signal Handling
Minishell handles signals such as `ctrl-C`, `ctrl-D`, and `ctrl-\` similar to how they behave in a typical shell environment. Pressing `ctrl-C` will display a new prompt on a new line, `ctrl-D` will exit the shell, and `ctrl-\` does nothing.

### Built-in Commands
Minishell includes several built-in commands that provide essential functionality. These commands are implemented within Minishell and do not rely on external executables. The available built-in commands are:

- `echo`: Displays text or variables.
  ```bash
  minishell > echo Hello, world!
  ```

- `cd`: Changes the current working directory.
  ```bash
  minishell > cd /path/to/directory
  ```

- `pwd`: Prints the current working directory.
  ```bash
  minishell > pwd
  ```

- `export`: Sets or modifies environment variables.
  ```bash
  minishell > export VAR=value
  ```

- `unset`: Removes environment variables.
  ```bash
  minishell > unset VAR
  ```

- `env`: Displays the current environment variables.
  ```bash
  minishell > env
  ```

- `exit`: Exits Minishell.
  ```bash
  minishell > exit
  ```

Refer to the Minishell project documentation or README for more detailed information on each feature, including examples and usage instructions.

## Norm Compliance
The Minishell project adheres to coding standards and norms, ensuring clean and readable code. It follows the specified norms for writing C code, ensuring that the project is consistent and maintainable.

## Memory Management
Minishell takes care of dynamically allocated memory to avoid memory leaks and ensure efficient resource utilization. The project properly frees allocated memory when necessary, ensuring that no memory leaks occur during its execution.

## Additional Resources
For more information and detailed instructions, please refer to the project documentation or README included in the Minishell repository. These resources provide comprehensive explanations, examples, and guidelines to help you understand and utilize the features of Minishell effectively.

Remember to consult the documentation whenever you need clarification or want to explore advanced features and techniques.

Enjoy using Minishell and have a great experience exploring the world of custom shell implementations!