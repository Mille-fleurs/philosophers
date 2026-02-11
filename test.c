#include <sys/time.h>
#include <unistd.h>
#include <stdio.h>

size_t	get_current_time(void)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL) == -1)
		write(2, "gettimeofdday() error\n", 22);
    printf("secondes: %zu\n", time.tv_sec);
    printf("microsecondes: %zu\n", time.tv_usec);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

int main(void)
{
    printf("%zu\n", get_current_time());
    return (0);
}