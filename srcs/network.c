#include <durex.h>

void	connection(int sock)
{
	char	buf[512];

	write(sock, "Hello", 5);

	int r = read(sock, buf, 511);
	buf[r] = '\0';
	write(sock, buf, r);
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
