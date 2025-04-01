#include <stdio.h>
#include <stdlib.h>

void flood_fill(char **map, int x, int y, int *is_valid)
{
    // Base cases: out of bounds or hit a wall
    if (x < 0 || y < 0 || !map[y] || !map[y][x])
        return;
    
    // If we hit a space outside the map or a non-valid character, map is not enclosed
    if (map[y][x] == ' ' || map[y][x] == '\0')
    {
        *is_valid = 0;
        return;
    }
    
    // If we hit a wall, stop the recursion
    if (map[y][x] == '1')
        return;
    
    // Mark as visited (can use a temporary character like 'V')
    map[y][x] = 'V';
    
    // Recursively check all four directions
    flood_fill(map, x + 1, y, is_valid); // right
    flood_fill(map, x - 1, y, is_valid); // left
    flood_fill(map, x, y + 1, is_valid); // down
    flood_fill(map, x, y - 1, is_valid); // up
    
    // Optional: restore the original character if needed
    // map[y][x] = original_char;
}

int check_map_enclosed(char **map, int player_x, int player_y)
{
    int is_valid = 1;
    
    // Create a copy of the map to avoid modifying the original
    char **map_copy = copy_map(map);
    if (!map_copy)
        return 0; // Memory allocation error
    
    // Start flood fill from player position
    flood_fill(map_copy, player_x, player_y, &is_valid);
    
    // Free the copy
    free_map_copy(map_copy);
    
    return is_valid;
}