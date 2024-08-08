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

// Sort environment variables for export
char **export_sort_env(char **env)
{
	char	**sorted_env;
	int		count;
	int		i;

	count = 0;
	while (env[count]) count++;
	sorted_env = malloc((count + 1) * sizeof(char *));
	if (!sorted_env) return NULL;
	i = 0;
	while (i < count)
	{
		sorted_env[i] = ft_strdup(env[i]);
		if (!sorted_env[i])
		{
			while (i > 0) free(sorted_env[--i]);
			free(sorted_env);
			return (NULL);
		}
		i++;
	}
	sorted_env[count] = NULL;
	quicksort(sorted_env, 0, count - 1);
	return (sorted_env);
}