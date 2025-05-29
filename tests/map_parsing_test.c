#include "tests_internal.h"
#include "../sources/cube3d.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/wait.h>
#include <signal.h>

#define DEBUG
#define START 4
#define END 5

typedef struct {
    const char *map_path;
    const char *test_name;
    int expected_result;
} t_unit_test_case;

static int run_validate_map_test(const t_unit_test_case *test_case) {
    t_mlx data;
    memset(&data, 0, sizeof(t_mlx));
    data.dbg = DBG_NOEXIT | DBG_TEXTURE_PATH;

    #ifdef DEBUG
    printf("\n----------\nRunning validate_map test: %s (%s)...\n", test_case->test_name, test_case->map_path);
    #endif

    int result = validate_map(&data, (char *)test_case->map_path);
    if (data.map.map)
        free_map(data.map.map);
    if (result == test_case->expected_result) {
        #ifdef DEBUG
        printf("OK (expected %d, got %d)\n", test_case->expected_result, result);
        #endif
        return 1;
    } else {
        #ifdef DEBUG
        printf("FAIL (expected %d, got %d)\n", test_case->expected_result, result);
        #endif
        return 0;
    }
}

int map_test(void) {
    t_unit_test_case test_cases[] = {
        {"tests/maps/good/color_duplicate.cub", "Valid Map", 1},
        {"tests/maps/good/open_map.cub", "Valid Map", 1},
        {"tests/maps/good/order.cub", "Valid Map", 1},
        {"tests/maps/bad/bad_map_symbol_0.cub", "Bad Map - Wrong player symbol", 0},
        {"tests/maps/bad/bad_map_symbol_1.cub", "Bad Map - Wrong wall", 0},
		{"tests/maps/bad/bad_map_symbol_2.cub", "Bad Map - Two players", 0},
		{"tests/maps/bad/color_0.cub", "Bad Map - color component too big", 0},
		{"tests/maps/bad/color_1.cub", "Bad Map - color component missing", 0},
		{"tests/maps/bad/color_2.cub", "Bad Map - bad color separator", 0},
		{"tests/maps/bad/color_3.cub", "Bad Map - missing color", 0},
		{"tests/maps/bad/color_4.cub", "Bad Map - wrong color name", 0},
		{"tests/maps/bad/color_6.cub", "Bad Map - letter in color", 0},
		{"tests/maps/bad/extension.cud", "Bad Map - wrong extension", 0},
		{"tests/maps/bad/no_texture_0.cub", "Bad Map - no such file", 0},
		{"tests/maps/bad/no_texture_1.cub", "Bad Map - no file text at all", 0},
		{"tests/maps/bad/no_texture_2.cub", "Bad Map - texture line missing", 0},
		{"tests/maps/bad/no_texture_3.cub", "Bad Map - no such file", 0}
    };
    int num_test_cases = sizeof(test_cases) / sizeof(test_cases[0]);
    int all_tests_passed = 1;

    #ifdef DEBUG
    printf("Starting validate_map unit tests...\n");
	printf("number of test cases: %d\n", num_test_cases);
    #endif
    for (int i = START; i < END; i++) {
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
