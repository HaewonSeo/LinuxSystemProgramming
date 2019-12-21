#include <stdio.h>
#include <time.h>

#define	MAX_BUF	40

main()
{
	time_t		cal;
	struct tm	*gmtm, *lctm;
	char		buf[MAX_BUF];

	if ((cal = time(NULL)) < 0)  {
		fprintf(stderr, "time failure\n");
		exit(1);
	}

	gmtm = gmtime(&cal);
	lctm = localtime(&cal);

	printf("Time: %s\n", ctime(&cal));
	printf("GM time: %s\n", asctime(gmtm));

	strftime(buf, MAX_BUF, "%c", lctm);
	printf("Local time: %s\n", buf);

	strftime(buf, MAX_BUF, "%A %B %d %H:%M:%S %Y (%Z))", lctm);
	printf("strftime: %s\n", buf);
}
