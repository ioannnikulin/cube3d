#include "tests_internal.h"
#include "libft.h"
#include <unistd.h>

#ifndef TRAP_COUNT
#define TRAP_COUNT 1000
#endif

#ifdef FT_CALLOC_IF_TRAPPED
static void	iterate_traps(void)
{
	system("rm -f trap.tgt cube.log");
#ifdef GITHUB
	int total = TRAP_COUNT;
#else // not GITHUB
	printf("User input emulation unavailable. Switching to manual testing.\n");
	printf("Now Cube3D will start. Please press a couple buttons (a couple, really) and exit normally (Esc)\n");
	system("bash -c \"./cube3D map.cub\" 1>cube.log");
	FILE *file = fopen("cube.log", "r");
	assert(file);
	char *line = NULL;
	ssize_t read;
	int total = 0;
	while ((read = getline(&line, &read, file)) != -1) {
		if (strstr(line, "Total ft_calloc_if calls: ")) {
			total = ft_atoi((line + 27), 0);
		}
	}
	fclose(file);
#endif
	for (int i = 0; i < total; i ++) {
		system("rm -f trap.tgt cube.log cube.err");
		file = fopen("trap.tgt", "w");
		assert(file);
		fprintf(file, "%d", i + 1);
		fclose(file);
		system("bash -c \"valgrind --leak-check=full --show-leak-kinds=all -s ./cube3D map.cub\" 1>cube.log 2>cube.err");
		file = fopen("cube.err", "r");
		assert(file);
		bool ok = false;
		while ((read = getline(&line, &read, file)) != -1) {
			if (strstr(line, "All heap blocks were freed -- no leaks are possible")) {
				ok = true;
				break ;
			}
		}
		fclose(file);
		if (ok) continue;
		printf("Leaks detected on trap %d. Set a breakpoint on ft_calloc_if_trapped.c:32, also read the logs in cube.err\n");
		assert(false);
	}
}
#endif

int e2e(void)
{
	#ifndef FT_CALLOC_IF_TRAPPED
	iterate_traps();
	#endif
	printf("e2e tests passed successfully\n");
	return (0);
}