#ifndef DUREX_H
# define DUREX_H

# include <libft.h>
# include <stdio.h>
# include <unistd.h>
# include <sys/file.h>
# include <sys/socket.h>
# include <sys/types.h>
# include <netdb.h>

# define BUF_SIZE 4096

# define LOGIN "magouin-jcamhi\n"

# define PASSWORD "3d09baddc21a365b7da5ae4d0aa5cb95"
# define SHELL "shell"

extern const char *durex_service;


char	*md5(char *str);

/*
 *	network.c
 */
void	handle_connection(int sock);
int		create_server();


#endif
