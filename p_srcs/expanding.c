/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expanding.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rustam <rustam@student.42.fr>              #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-08-12 20:39:55 by rustam            #+#    #+#             */
/*   Updated: 2024-08-12 20:39:55 by rustam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char *replace_token(char *token, char *exp_name) {
  char *pre;
  char *post;
  char *result;
  char *result2;

  pre = get_prestring(token);
  post = get_poststring(token);
  result = ft_strjoin(pre, exp_name);
  free(pre);
  free(exp_name);
  result2 = ft_strjoin(result, post);
  free(result);
  free(post);
  return (result2);
}

char *remove_var(char *token, char *var_name) {
  int pos;
  int i;
  int j;
  char *new_token;

  new_token = (char *)malloc(
      (ft_strlen(token) - (ft_strlen(var_name)) * sizeof(char)) + 21);
  pos = 0;
  while (ft_strncmp(token + pos, var_name, ft_strlen(var_name)) != 0)
    pos++;
  i = 0;
  j = 0;
  while (token[i]) {
    if (i == pos - 1)
      i += ft_strlen(var_name) + 1;
    new_token[j] = token[i];
    i++;
    j++;
  }
  new_token[j] = '\0';
  return (new_token);
}

char *dollar_expansion(char *orig, char *token, t_command **env) {
  char *var_name;
  char *expanded_name;
  char *new_token;

  var_name = get_var_name(token);
  if (ft_strcmp(var_name, "?") == 0)
    expanded_name = ft_itoa(gl_command.exit_code);
  else
    expanded_name = get_expanded_name(var_name, env);
  if (expanded_name[0] == '\0')
    new_token = remove_var(orig, var_name);
  else {
    new_token = replace_token(orig, expanded_name);
  }
  if (var_name)
    free(var_name);
  return (new_token);
}

/*
|	ATTENTION: if the variable is not found (Such as $PWDlol), then the new
|	token will be '\0'.
|	Echo must then deal with this appropriately.
*/

int  is_not_between_squotes(char *token, int i) {
  int j;
  int left;
  int right;

  j = i;
  left = 0;
  right = 0;
  while (i-- >= 0) {
    if (token[i] == '\'')
      left = 1;
  }
  while (token[j++]) {
    if (token[j] == '\'')
      right = 1;
  }
  if (right && left)
    return (0);
  return (1);
}

void expand_tokens(char **tokens, t_command **env) {
  int i;
  int j;
  char *new_token;

  i = 0;
  while (tokens[i]) {
    if (find_first_expansion(tokens[i]) != -1) {
      if (ft_strchr(tokens[i], '$')[1] == '\0' ||
          cst(ft_strchr(tokens[i], '$')[1]) ||
          is_expand_exception(ft_strchr(tokens[i], '$')[1])) {
        i++;
        continue;
      }
      j = find_first_expansion(tokens[i]);
      new_token = dollar_expansion(tokens[i], tokens[i] + j + 1, env);
      free(tokens[i]);
      tokens[i] = new_token;
    }
    if (dollar_remaining(tokens[i]))
      continue;
    i++;
  }
}