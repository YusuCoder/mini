/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkubanyc <tkubanyc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 19:20:07 by tkubanyc          #+#    #+#             */
/*   Updated: 2024/08/09 21:39:28 by tkubanyc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	print_wrong_command(char *arg, int *exit_code)
{
	write(2, "minishell: ", 12);
	write(2, arg, ft_strlen(arg));
	write(2, ": command not found\n", 21);
	*exit_code = 127;
}

void	execute_builtin(char **args, char ***env, int *exit_code)
{
	if (is_cd(args[0]))
		execute_cd(args, *env, exit_code);
	else if (is_pwd(args[0]))
		execute_pwd(exit_code);
	else if (is_env(args[0]))
		execute_env(*env, exit_code);
	else if (is_echo(args[0]))
		execute_echo(args, exit_code);
	else if (ft_strcmp(args[0], "export") == 0)
		execute_export(args, env, exit_code);
	else if (ft_strcmp(args[0], "unset") == 0)
		execute_unset(args, env, exit_code);
	else if (ft_strcmp(args[0], "exit") == 0)
		execute_exit(args, exit_code);
	else
		return ;
}

void	execute(t_command *cmd, int *exit_code)
{
	if (cmd->tokens[0] == NULL)
		*exit_code = 0;
	else if (is_builtin(cmd->tokens[0]))
		execute_builtin(cmd->tokens, &cmd->envp, exit_code);
	else
		print_wrong_command(cmd->tokens[0], exit_code);
}

// void	execute(t_command *cmd, int *exit_code)
// {
// 	t_sub_commands	*sub_cmd;
// 	int				fd_pipe[2];
// 	int				fd_input;
// 	pid_t			pid;
// 	int				i;

// 	if ((cmd->cmd_num == 0) || (&cmd->sub_command[0] == NULL))
// 	{
// 		*exit_code = 0;
// 		return ;
// 	}
// 	fd_input = STDIN_FILENO;
// 	i = -1;
// 	while (++i < cmd->cmd_num)
// 	{
// 		sub_cmd = &cmd->sub_command[i];
// 		if (i < cmd->cmd_num - 1)
// 		{
// 			if (pipe(fd_pipe) == -1)
// 			{
// 				perror("pipe");
// 				*exit_code = 1;
// 				exit(*exit_code);
// 			}
// 		}
// 		pid = fork();
// 		if (pid == -1)
// 		{
// 			perror("fork");
// 			*exit_code = 1;
// 			exit(*exit_code);
// 		}
// 		else if (pid == 0)  // Child process
// 		{
// 			// Handle input redirection
// 			if (sub_cmd->input_fd > 0)
// 			{
// 				dup2(sub_cmd->input_fd, STDIN_FILENO);
// 				close(sub_cmd->input_fd);
// 			}
// 			else if (i > 0)
// 				dup2(fd_input, STDIN_FILENO);
// 			// Handle output redirection
// 			if (sub_cmd->output_fd > 0)
// 			{
// 				dup2(sub_cmd->output_fd, STDOUT_FILENO);
// 				close(fd_pipe[0]);
// 				close(fd_pipe[1]);
// 			}

// 			// Execute the command
// 			if (is_builtin(sub_cmd->argv[0]))
// 			{
// 				execute_builtin(cmd->tokens, &cmd->envp, exit_code);
// 				exit(*exit_code); // exit after running builtin in child
// 			}
// 			else
// 			{
// 				execve(sub_cmd->argv[0], sub_cmd->argv, cmd->envp);
// 				perror("execve");
// 				*exit_code = 1;
// 				exit(*exit_code);
// 			}
// 			// print_wrong_command(cmd->tokens[0], exit_code);
// 		}
// 		else // Parent process
// 		{
// 			waitpid(pid, exit_code, 0);
// 			close(fd_input);
// 			close(fd_pipe[1]);
// 			fd_input = fd_pipe[0];
// 		}
// 	}
// }


// function execute(command_line)
//     commands = parse_commands(command_line)  // Split by pipes '|'
//     num_commands = length(commands)
//     previous_pipe = None

//     for i from 0 to num_commands - 1
//         command = commands[i]

//         // Handle pipes, except for the last command
//         if i < num_commands - 1
//             pipe_fd = create_pipe()

//         // Fork process for the command
//         pid = fork()
//         if pid == 0 then  // Child process
//             // Input redirection
//             if command has input redirection '<'
//                 input_file = open_file(command.input_redirection_file)
//                 dup2(input_file, STDIN_FILENO)  // Redirect stdin
//                 close(input_file)

//             // Output redirection
//             if command has output redirection '>' or '>>'
//                 if command has '>'
//                     output_file = open_file(command.output_redirection_file, truncate=true)
//                 else if command has '>>'
//                     output_file = open_file(command.output_redirection_file, append=true)
//                 dup2(output_file, STDOUT_FILENO)  // Redirect stdout
//                 close(output_file)

//             // Pipe handling
//             if previous_pipe != None
//                 dup2(previous_pipe.read_end, STDIN_FILENO)  // Read from previous pipe
//                 close(previous_pipe.write_end)
//                 close(previous_pipe.read_end)

//             if i < num_commands - 1
//                 close(pipe_fd.read_end)
//                 dup2(pipe_fd.write_end, STDOUT_FILENO)  // Write to current pipe
//                 close(pipe_fd.write_end)

//             // Execute the command
//             if command is a built-in command
//                 execute_builtin(command)
//                 exit(0)
//             else
//                 execute_external(command)
//                 exit_on_failure("execve")

//         else  // Parent process
//             if previous_pipe != None
//                 close(previous_pipe.read_end)
//                 close(previous_pipe.write_end)

//             if i < num_commands - 1
//                 close(pipe_fd.write_end)
//                 previous_pipe = pipe_fd

//             wait_for_process(pid)

//     // Clean up any remaining file descriptors or resources

// function parse_commands(command_line)
//     // This function splits command_line by pipes '|',
//     // and for each command detects input/output redirections
//     return array_of_commands
