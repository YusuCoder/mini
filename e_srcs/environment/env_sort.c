
#include "../../includes/minishell.h"

// Swap function for quicksort
void	swap(char **a, char **b)
{
	char	*temp;

	temp = *a;
	*a = *b;
	*b = temp;
}

// Partition function for quicksort
int	partition(char **arr, int low, int high)
{
	char	*pivot;
	int		i;
	int		j;

	pivot = arr[high];
	i = low - 1;
	j = low;
	while (j < high)
	{
		if (ft_strcmp(arr[j], pivot) < 0)
		{
			i++;
			swap(&arr[i], &arr[j]);
		}
		j++;
	}
	swap(&arr[i + 1], &arr[high]);
	return (i + 1);
}

// Quicksort implementation
void	quicksort(char **arr, int low, int high)
{
	int	pi;

	if (low < high)
	{
		pi = partition(arr, low, high);
		quicksort(arr, low, pi - 1);
		quicksort(arr, pi + 1, high);
	}
}

// Sort environment variables in alphabetic order
char **env_sort(char **env)
{
	char	**sorted_env;
	int		len_env;

	sorted_env = env_set(env);
	if (!sorted_env)
		return (NULL);
	len_env = env_len(env);
	quicksort(sorted_env, 0, len_env - 1);
	return (sorted_env);
}
