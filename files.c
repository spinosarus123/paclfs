#include "files.h"

#include <string.h>
#include <dirent.h>
#include <stdio.h>
#include <sys/stat.h>

#include "util.h"

void print_files(char *base_path, char *recursive_path , char *file) {
	char path[BUFSIZ];

	struct dirent *d;

	sprintf(path, "%s/%s", base_path, recursive_path);
	DIR *dir = opendir(path);
	
	if (!dir)
		return;

	while ((d = readdir(dir))) {
		if (strcmp(d->d_name, ".") && strcmp(d->d_name, "..")) {
			sprintf(path, "%s/%s/%s", base_path, recursive_path, d->d_name);

			struct stat s;
			if (stat(path, &s) == 0 && S_ISDIR(s.st_mode)) {
				sprintf(path, "%s/%s", recursive_path, d->d_name);
				print_files(base_path, path, file);
			}
			FILE *f;
			f = fopen(file, "a");
			if (!f)
				return;
			
			fprintf(f, "%s/%s\n", recursive_path, d->d_name);
			fclose(f);

		}
	}

	closedir(dir);
}

void uninstall_package(char *name) {
	struct dirent *d;

	DIR *dir = opendir("/etc/paclfs");
	
	if (!dir)
		return;

	while ((d = readdir(dir))) {
		if (strcmp(d->d_name, ".") && strcmp(d->d_name, "..")) {
			char *c = strrchr(d->d_name, '-');
			if (c) {
				*c = '\0';
			}
			if (strcmp(d->d_name, name) == 0) {
				*c = '-';
				goto lab1;
			}
		}
	}
	printf("There is no installed lfspackage with the name \"%s\"\n.", name);
	return;
lab1:;
	closedir(dir);
	FILE *f;
	char path[BUFSIZ + 12];
	sprintf(path, "/etc/paclfs/%s", d->d_name);
	f = fopen(path, "r");
	if (!f)
		return;
	char line[BUFSIZ];
	while ((fgets(line, sizeof(line), f))) {
		if (strcmp(line, "########################################\n") == 0)
			break;
	}
	while ((fgets(line, sizeof(line), f))) {
		line[strlen(line) - 1] = '\0';
		printf("%s\n", line);
		remove(line);
	}
	fclose(f);
}

void list_packages() {
	struct dirent *d;

	DIR *dir = opendir("/etc/paclfs");
	
	if (!dir)
		return;

	while ((d = readdir(dir))) {
		if (strcmp(d->d_name, ".") && strcmp(d->d_name, "..")) {
			printf("%s\n", d->d_name);
		}
	}
	return;
}

void list_deps(char *name, char **mem, int *length) {
	char line[BUFSIZ];

	char path[BUFSIZ];

	struct dirent *d;

	DIR *dir = opendir("/etc/paclfs");

	if (!dir)
		return;

	while ((d = readdir(dir))) {
		if (strcmp(d->d_name, ".") && strcmp(d->d_name, "..")) {
			char *c = strrchr(d->d_name, '-');
			if (c) {
				*c = '\0';
			}
			if (strcmp(d->d_name, name) == 0) {
				*c = '-';
				goto lab2;
			}
		}
	}
	printf("There is no installed lfspackage with the name \"%s\"\n.", name);
	return;
lab2:;
	closedir(dir);
	sprintf(path, "/etc/paclfs/%s", d->d_name);
	
	FILE *f;

	f = fopen(path, "r");
	
	if (!f)
		return;

	while (fgets(line, sizeof(line), f)) {
		if (strcmp(line, "########################################\n") == 0)
			break;
		line[strlen(line) - 1] = '\0';

		if (!contains(mem, line, *length)) {
			printf("%s\n", line);

			strcpy(*(mem + *length), line);

			(*length)++;
			list_deps(line, mem, length);
		}

	}

	fclose(f);
}
