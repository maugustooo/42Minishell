#include "minishell.h"

void move_left(char **args, int i)
{
    while (args[i])
	{
        args[i] = args[i + 2];
        i++;
    }
}

void handle_heredoc(char ***args, int *i)
{
	char buffer[1024];
    int bytes_read;
	char *delimiter;
	int pipefd[2];

	if (pipe(pipefd) == -1)
    {
        perror("pipe");
        exit(EXIT_FAILURE);
    }
	delimiter = (*args)[*i + 1];
	while (1)
	{
		ft_printf("> ");
		bytes_read = read(STDIN_FILENO, buffer, sizeof(buffer) - 1);
		if (bytes_read <= 0)
        {
            perror("read");
            exit(EXIT_FAILURE);
        }
		buffer[bytes_read] = '\0';
		if (ft_strncmp(buffer, delimiter, ft_strlen(delimiter)) == 0 && buffer[ft_strlen(delimiter)] == '\n')
			break;
		ft_printf_fd(pipefd[1], buffer);
	}
	close(pipefd[1]);
	dup2(pipefd[0], STDIN_FILENO);
	close(pipefd[0]);
	move_left((*args), *i);
}

int handle_input(char ***args, int	*i)
{
	int fd_in;
	fd_in = 0;

	fd_in = open((*args)[*i + 1], O_RDONLY);
	if(!fd_in)
		return(0);
	dup2(fd_in, STDIN_FILENO);
	close(fd_in);
	move_left((*args), *i);
	return(1);
}

int handle_output(char ***args, int	*i)
{
	int fd_out;
	fd_out = 0;

	if(ft_strcmp((*args)[*i], ">") == 0)
		fd_out = open((*args)[*i + 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else
		fd_out = open((*args)[*i + 1], O_WRONLY | O_CREAT | O_APPEND, 0644);
	if(!fd_out)
		return(0);
	dup2(fd_out, STDOUT_FILENO);
	close(fd_out);
	move_left((*args), *i);
	return(1);
}
