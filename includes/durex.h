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

extern const char *durex_service;


/*
 *	network.c
 */
void	handle_connection(int sock);
int		create_server();


#endif
