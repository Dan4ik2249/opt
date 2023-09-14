#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

int main(int argc, char *argv[])
{
	int fd;
	FILE *out = stdout;
	int a[256] = {0};
	int ind, opt;
	int count = 0;

	while ((opt = getopt(argc, argv, "vo:")) != -1) {
		switch(opt) {
			case 'o':
				out = fopen(optarg, "wb");
			/*	if ((fd = open(argv[optind], "rb")) == -1) {
					perror("File opening error");
					return __LINE__;
				}*/
				break;

			case 'v':
				count = 1;
				printf("Flag activated\n");
				break;

			default:
				break;
		}
	}

	if ((fd = open(argv[optind], O_RDONLY)) == -1) {
		perror("File opening error");
		return __LINE__;
	}
	else if (count == 1) printf("File create\n");

	if (count == 1) printf("Counting the quantity\n");
	while (read(fd, &ind, 1) == 1) {
		a[ind]++;
	}

	if (count == 1) printf("Printing result...\n");
	for (int i = 0; i < 256; i++) {
		fprintf(out, "a[%d] = %d \n", i, a[i]);
	}

	if (count == 1) printf("Close file\n");
	fclose(out);
	close(fd);
	return 0;
}
