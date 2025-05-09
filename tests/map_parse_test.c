#include "tests_internal.h"
#include <stdlib.h> 
#include <stdio.h> 
#include <string.h>
#include <sys/wait.h>

#define CUB3D_EXECUTABLE "./cube3D" 

typedef struct {
	const char *map_path;
	const char *test_name;
} t_e2e_test_case;

int run_single_e2e_test(const t_e2e_test_case *test_case) {
	char command[256];
	if (!CUB3D_EXECUTABLE || !test_case || !test_case->map_path) {
		fprintf(stderr, "Error: Invalid arguments to run_single_e2e_test.\n");
		return 0; 
	}
	sprintf(command, "%s %s", CUB3D_EXECUTABLE, test_case->map_path);

	printf("Running E2E test: %s (%s)... ", test_case->test_name ? test_case->test_name : "Unnamed Test", test_case->map_path);
	int status = system(command);

	if (WIFEXITED(status)) {
		int exit_code = WEXITSTATUS(status);
		printf("OK (exited with code %d)\n", exit_code);
		return 1; 
	} else if (WIFSIGNALED(status)) {
		int signal_num = WTERMSIG(status);
		printf("FAIL (terminated by signal %d)\n", signal_num);
		if (signal_num == SIGSEGV) {
			fprintf(stderr, "Error: Test %s (%s) SEGMENTATION FAULTED.\n", test_case->test_name ? test_case->test_name : "Unnamed Test", test_case->map_path);
		} else {
			fprintf(stderr, "Error: Test %s (%s) crashed with signal %d.\n", test_case->test_name ? test_case->test_name : "Unnamed Test", test_case->map_path, signal_num);
		}
		return 0; 
	} else {
		printf("FAIL (unknown termination status %d for command: %s)\n", status, command);
		return 0; 
	}
}

int map_test(void) {

t_e2e_test_case test_cases[] = {
		// {"tests/maps/maps_short/good/valid_map.cub", "Valid Map"}, // Adjusted path to be relative to workspace root likely
		{"tests/maps/maps_short/bad/0player.cub", "Bad Map - 0 Player"},
		{"tests/maps/maps_short/bad/not_enclosed.cub", "Bad Map - Not Enclosed"},
		{"tests/maps/maps_short/bad/empty_row.cub", "Bad Map - Empty Row"},
		{"tests/maps/maps_short/bad/2palyers.cub", "Bad Map - 2 Players"}
	};
	int num_test_cases = sizeof(test_cases) / sizeof(test_cases[0]);
	int all_tests_passed = 1; 

	printf("Starting E2E tests...\n");

	for (int i = 0; i < num_test_cases; i++) {
		if (!run_single_e2e_test(&test_cases[i])) {
			all_tests_passed = 0; 
		}
	}

	if (all_tests_passed) {
		printf("All E2E tests passed successfully (no crashes detected)!\n");
		return 0; 
	} else {
		printf("Some E2E tests failed (crashes detected).\n");
		return 1; 
	}
}