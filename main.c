#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>

#include "files.h"

int main(int argc, char **argv) {
	char file[BUFSIZ + 12];
	char c;

	char pwd[BUFSIZ];
	getcwd(pwd, sizeof(pwd));

	char name[BUFSIZ];

	if (argc == 1) {
		printf("Do \"paclfs -h\" for help.\n");
		return 0;
	}
	if (strcmp(*(argv + 1), "install") == 0) {
		sprintf(name, "%s", strrchr(pwd, '/') + 1);
		sprintf(file, "/etc/paclfs/%s", name);
		while (1) {
			printf("Do you want to install \"%s\" as an lfspackage? (y/n) ", name);
			scanf(" %c", &c);
			if (c == 'y') {
				break;
			}
			else if (c == 'n') {
				return 0;
			}
		}

		char recursive_path[BUFSIZ];
		*recursive_path = '\0';

		FILE *f;
		f = fopen(file, "w");
	
		if (!f)
			return -1;
	
		fprintf(f, "########################################\n");
		fclose(f);

		print_files(pwd, recursive_path, file);
	}
	else if (strcmp(*(argv + 1), "uninstall") == 0) {
		if (argc == 2) {
			printf("Please specify a package to uninstall.\n");
			return 0;
		}

		while (1) {
			printf("Do you want to uninstall \"%s\"? (y/n) ", *(argv + 2));
			scanf(" %c", &c);
			if (c == 'y') {
				break;
			}
			else if (c == 'n') {
				return 0;
			}
		}

		uninstall_package(*(argv + 2));
	}
	else if (strcmp(*(argv + 1), "list") == 0) {
		if (argc == 2) {
			list_packages();
		}
		else if (strcmp(*(argv + 2), "deps") == 0) {
			if (argc == 3) {
				printf("Please specify a package to list dependencies for.\n");
				return 0;
			}
			
			char **mem = malloc(sizeof(char*) * BUFSIZ);
			for (int i = 0; i < BUFSIZ; i++)
				*(mem + i) = malloc(sizeof(char) * BUFSIZ);
			strcpy(*mem, *(argv + 3));
			int *length = malloc(sizeof(int));
			*length = 1;
			list_deps(*(argv + 3), mem, length);
			for (int i = 0; i < BUFSIZ; i++)
				free(mem[i]);
			free(mem);
			free(length);
		}
	}
	else {
		printf("Do \"paclfs -h\" for help.\n");
		return 0;
	}
}
