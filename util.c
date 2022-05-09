#include "util.h"

#include <string.h>

int contains(char **mem, char *str, int length) {
	for (int i = 0; i < length; i++) {
		if (strcmp(*(mem + i), str) == 0)
			return 1;
	}
	return 0;
}
