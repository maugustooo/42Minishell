#include "minishell.h"

int	check_file_echo(char *file)
{
	struct stat	path_stat;

	if (stat(file, &path_stat) == -1)
	{
		ft_printf_fd(STDERR_FILENO, Error_Msg(ERROR_CMD), file);
		return (0);
	}
	if (S_ISREG(path_stat.st_mode))
	{
		if (access(file, R_OK) == 0)
			return (1);
		else
		{
			ft_printf_fd(STDERR_FILENO, Error_Msg(ERROR_PERMS), file);
			return(0);
		}
	}
	else if (S_ISDIR(path_stat.st_mode))
	{
		ft_printf_fd(STDERR_FILENO, Error_Msg(ERROR_ISDIR), file);
		return(0);
	}
	else
		ft_printf_fd(STDERR_FILENO, Error_Msg(ERROR_CD), file);
	return (0);
}
