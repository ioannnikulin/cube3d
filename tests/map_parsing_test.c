#include "tests_internal.h"
#include "../sources/cube3d.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/wait.h>
#include <signal.h>

#define CUB3D_EXECUTABLE "./cube3D"

typedef struct {
    const char *map_path;
    const char *test_name;
    int expected_result;
} t_unit_test_case;

int run_validate_map_test(const t_unit_test_case *test_case) {
    t_mlx data;
    memset(&data, 0, sizeof(t_mlx)); // Initialize the data structure to zero

    printf("Running validate_map test: %s (%s)... ", test_case->test_name, test_case->map_path);

    int result = validate_map(&data, (char *)test_case->map_path);
    if (data.map.map) {
        free_map(data.map.map);
    }
    if (result == test_case->expected_result) {
        printf("OK (expected %d, got %d)\n", test_case->expected_result, result);
        return 1;
    } else {
        printf("FAIL (expected %d, got %d)\n", test_case->expected_result, result);
        return 0;
    }
}

int map_test(void) {
    t_unit_test_case test_cases[] = {
        {"tests/maps/maps_short/good/valid_map.cub", "Valid Map", 1},
        {"tests/maps/maps_short/bad/no_player.cub", "Bad Map - 0 Player", 0},
        {"tests/maps/maps_short/bad/not_enclosed.cub", "Bad Map - Not Enclosed", 0},
        {"tests/maps/maps_short/bad/2players.cub", "Bad Map - 2 Players", 0},
		{"tests/maps/maps_short/bad/wrong_char.cub", "Bad Map - Wrong character in a map", 0}
    };
    int num_test_cases = sizeof(test_cases) / sizeof(test_cases[0]);
    int all_tests_passed = 1;

    printf("Starting validate_map unit tests...\n");

	printf("number of test cases: %d\n", num_test_cases);
    for (int i = 0; i < num_test_cases; i++) {
        if (!run_validate_map_test(&test_cases[i])) {
            all_tests_passed = 0;
        }
    }

    if (all_tests_passed) {
        printf("All validate_map tests passed successfully!\n");
		return 0;
    } else {
        printf("Some validate_map tests failed.\n");
		assert(false);
        return 1;
    }
}
