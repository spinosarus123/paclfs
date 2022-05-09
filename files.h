#ifndef FILES_H
#define FILES_H

void print_files(char *base_name, char *recursive_path, char *file);

void uninstall_package(char *name);

void list_packages();

void list_deps(char *name, char **mem, int *length);

#endif
