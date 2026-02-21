
#include "philo_bonus.h"

int	error_msg(char *str, char *detail, int ret)
{
	if (!detail)
		printf(str, STR_PROG_NAME);
	else
		printf(str, STR_PROG_NAME, detail);
	return (ret);
}

int error_failure(char *s, char *details, t_table *t)
{
	if (t != NULL)
		free_table(t);
	return (msg(s, details, 0));
}

void	*error_null(char *s, char *details, t_table *t)
{
	if (t != NULL)
		free_table(t);
	msg(s, details, EXIT_FAILURE);
	return (NULL);
}

// void child_exit : to do

