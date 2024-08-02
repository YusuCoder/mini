/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sub_cmd_arrays.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ryusupov <ryusupov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/02 10:57:03 by ryusupov          #+#    #+#             */
/*   Updated: 2024/08/02 13:22:53 by ryusupov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*
	This function copies contents of each subcommand tokens to the memory of array sub_cmd_array untill the first pipe
	then allocates another memory for another subcmd and does the same
*/
void	sub_cmds_array(t_command *cmd, char **tokens)
{
	int	i;
	int	x;
	int	c;

	i = 0;
	x = 0;
	while (i < cmd->cmd_num)
	{
		c = 0;
		cmd->sub_command[i].sub_cmd_array = (char **)malloc(sizeof(char *) * (cmd->sub_command[i].sub_argc_count + 1));
		if (!cmd->sub_command)
			exit(EXIT_FAILURE);
			// _err_msg("Allcation failed!\n", EXIT_FAILURE);
		while (c < cmd->sub_command[i].sub_argc_count)
		{
			cmd->sub_command[i].sub_cmd_array[c] = ft_strdup(tokens[x]);
			c++;
			x++;
		}
		cmd->sub_command[i].sub_cmd_array[c] = NULL;
		if (tokens[x] && ft_strncmp(tokens[x], "|", 1) == 0)
			x++;
		i++;
	}
}

// int main() {
//     char *tokens[] = {"echo", "hello", "|", "wc", "-l", NULL};

//     t_command cmd;
// 	int i = 0;
// 	int j;
//     cmd.cmd_num = 2;

//     cmd.sub_command = (t_sub_commands *)malloc(sizeof(t_sub_commands) * cmd.cmd_num);

//     cmd.sub_command[0].sub_argc_count = 2; // "echo" "hello"
//     cmd.sub_command[1].sub_argc_count = 2; // "wc" "-l"

//     sub_cmds_array(&cmd, tokens);

//     while (i < cmd.cmd_num)
// 	{
// 		j = 0;
//         printf("Sub-command %d:\n", i + 1);
//         while ( j < cmd.sub_command[i].sub_argc_count)
// 		{
//             printf("  %s\n", cmd.sub_command[i].sub_cmd_array[j]);
// 			j++;
//         }
// 		i++;
//     }

//     return 0;
// }


