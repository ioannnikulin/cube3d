CC = cc
NAME = cube3D
COMPILE_FLAGS = -Wall -Wextra -Werror -g -c -O0 -fno-builtin-printf
LINK_FLAGS = -lft -Llibft -lreadline -lm #-fsanitize=address #not compatible with valgrind from fulltest
MLX_F =
INCLUDES = -I . -I libft -I $(MLX_F)
MLX_COMPILE_FLAGS =
MLX_LINK_FLAGS =

MLX_SOURCE_ADDRESS =
MLX_ARCHIVE = minilibx.tgz
PREFIX =
PREPROC_DEFINES =

UNAME := $(shell uname)

MLX_L_FLAGS			=	-L$(MLX_F) -lmlx -lXext -lX11 -L/usr/lib -lXext -lX11 -lz
MLX_M_FLAGS			=	-L$(MLX_F) -lmlx -framework OpenGL -framework AppKit

ifeq ($(UNAME), Linux)
	MLX_SOURCE_ADDRESS 		= 	https://cdn.intra.42.fr/document/document/31891/minilibx-linux.tgz
	MLX_F 					=	minilibx-linux
	MLX_COMPILE_FLAGS		=	$(MLX_LINUX_COMPILE_FLAGS)
	MLX_LINK_FLAGS			=	$(MLX_L_FLAGS)
else
	MLX_SOURCE_ADDRESS 		= 	https://cdn.intra.42.fr/document/document/31892/minilibx_opengl.tgz
	MLX_F 					=	minilibx_opengl_20191021
	MLX_COMPILE_FLAGS		=	$(MLX_MACOS_COMPILE_FLAGS)
	MLX_LINK_FLAGS			=	$(MLX_M_FLAGS)
endif

SOURCE_F = sources
TEST_F = tests

MAP_PARSING_NAMES = map_parse.c check_walls.c parse_utils.c parse_utils2.c
MAP_PARSING_F = map_parse
MAP_PARSING_SRCS = $(addprefix $(MAP_PARSING_F)/,$(MAP_PARSING_NAMES))

DRAWING_NAMES = \
	player.c \
	render_frame.c
DRAWING_F = drawing
DRAWING_SRCS = $(addprefix $(DRAWING_F)/,$(DRAWING_NAMES))

PRIMITIVES_NAMES = \
	line.c \
	line_endpoint.c \
	line_math.c \
	pixel.c \
	circle.c \
	ray.c \
	quadrangle.c \
	triangle.c \
	triangle_factories.c \
	get_color.c
PRIMITIVES_F = ${DRAWING_F}/primitives
PRIMITIVES_SRCS = $(addprefix $(PRIMITIVES_F)/,$(PRIMITIVES_NAMES))

RAYCAST_NAMES = \
	rays.c \
	hor_isect.c \
	ver_isect.c \
	draw_ver_stripe.c
RAYCAST_F = ${DRAWING_F}/rays
RAYCAST_SRCS = $(addprefix $(RAYCAST_F)/,$(RAYCAST_NAMES))

PLAYER_CONTROLS_NAMES = \
	keyboard.c \
	utils.c
PLAYER_CONTROLS_F = player_controls
PLAYER_CONTROLS_SRCS = $(addprefix $(PLAYER_CONTROLS_F)/,$(PLAYER_CONTROLS_NAMES))

WORLD_CREATION_NAMES = \
	world_create.c
WORLD_CREATION_F = world_creation
WORLD_CREATION_SRCS = $(addprefix $(WORLD_CREATION_F)/,$(WORLD_CREATION_NAMES))

SRC_NAMES = finalize.c core_utils.c pre.c make_image.c
ENDPOINT_NAME = main.c

SRC_SRCS = $(addprefix $(SOURCE_F)/, $(SRC_NAMES))
ENDPOINT_SRC = $(addprefix $(SOURCE_F)/, $(ENDPOINT_NAME))
ENDPOINT_OBJ = $(OBJ_F)$(ENDPOINT_NAME:.c=.o)

TEST_NAMES = units.c e2e.c map_parsing_test.c
TEST_ENDPOINT_NAME = main_test.c
TEST_SRCS = $(addprefix $(TEST_F)/, $(TEST_NAMES))
TEST_ENDPOINT_SRC = $(addprefix $(TEST_F)/, $(TEST_ENDPOINT_NAME))
TEST_FNAME = $(TEST_F)/test

OBJ_F = build/

OBJS = \
	$(addprefix $(OBJ_F), $(SRC_SRCS:.c=.o)) \
	$(addprefix $(OBJ_F), $(MAP_PARSING_SRCS:.c=.o)) \
	$(addprefix $(OBJ_F), $(PRIMITIVES_SRCS:.c=.o)) \
	$(addprefix $(OBJ_F), $(DRAWING_SRCS:.c=.o)) \
	$(addprefix $(OBJ_F), $(RAYCAST_SRCS:.c=.o)) \
	$(addprefix $(OBJ_F), $(PLAYER_CONTROLS_SRCS:.c=.o)) \
	$(addprefix $(OBJ_F), $(WORLD_CREATION_SRCS:.c=.o))

TEST_OBJS = $(addprefix $(OBJ_F), $(TEST_SRCS:.c=.o))
TEST_ENDPOINT_OBJ = $(OBJ_F)$(TEST_ENDPOINT_SRC:.c=.o)
TEST_OBJ_F = $(OBJ_F)tests/

DIRS = \
	$(SOURCE_F) \
	$(MAP_PARSING_F) \
	$(DRAWING_F) \
	$(PRIMITIVES_F) \
	$(RAYCAST_F) \
	$(PLAYER_CONTROLS_F) \
	$(WORLD_CREATION_F)

OBJ_DIRS = $(addprefix $(OBJ_F), $(DIRS))

vpath %.c $(DIRS) $(TEST_F)

all: pre $(NAME)

bonus: all

$(OBJ_DIRS):
	$(PREFIX)mkdir -p $(OBJ_DIRS)

pre:
	$(PREFIX)cd libft && make all
	$(PREFIX)curl $(MLX_SOURCE_ADDRESS) -o $(MLX_ARCHIVE) && tar -xf $(MLX_ARCHIVE)
	$(PREFIX)cd $(MLX_F) && make -s
	$(PREFIX)rm -f $(MLX_ARCHIVE)

$(NAME): $(OBJS) $(ENDPOINT_OBJ) $(OBJ_DIRS)
	$(PREFIX)$(CC) $(OBJS) $(ENDPOINT_OBJ) -o $@ $(LINK_FLAGS) $(MLX_LINK_FLAGS)

$(OBJ_F)%.o: %.c $(OBJ_DIRS)
	$(PREFIX)$(CC) $(COMPILE_FLAGS) $(MLX_COMPILE_FLAGS) $< -o $@ $(INCLUDES) $(PREPROC_DEFINES)

$(TEST_OBJ_F):
	$(PREFIX)mkdir -p $(TEST_OBJ_F)

$(TEST_OBJ_F)%.o: $(TEST_F)/%.c $(TEST_OBJ_F)
	$(PREFIX)$(CC) $(COMPILE_FLAGS) $(MLX_COMPILE_FLAGS) $< -o $@ $(INCLUDES) $(PREPROC_DEFINES)

test_trapped:
	$(PREFIX)make PREPROC_DEFINES="$(PREPROC_DEFINES) -DFT_CALLOC_IF_TRAPPED" test

test: $(OBJ_DIRS) $(TEST_OBJ_F) $(OBJS) $(TEST_OBJS) $(TEST_ENDPOINT_OBJ)
	$(PREFIX)$(CC) $(OBJS) $(TEST_OBJS) $(TEST_ENDPOINT_OBJ) -o $(TEST_FNAME) $(LINK_FLAGS) $(MLX_LINK_FLAGS)

preclean:
	$(PREFIX)cd libft && make clean
	$(PREFIX)rm -rf $(MLX_ARCHIVE) $(MLX_F)

prefclean:
	$(PREFIX)cd libft && make fclean
	$(PREFIX)rm -rf $(MLX_ARCHIVE) $(MLX_F)

pretestfclean:
	$(PREFIX)cd libft && make testfclean

prere:
	$(PREFIX)cd libft && make re

clean: testclean #before submission: add preclean
	$(PREFIX)rm -f $(OBJS) $(ENDPOINT_OBJ)
	$(PREFIX)@if [ -d $(OBJ_F) ]; then rm -rf $(OBJ_F); fi
	$(PREFIX)rm -f all_calls.txt forbidden_calls.txt functions.txt

fclean: clean testfclean #before submission: add prefclean
	$(PREFIX)rm -f $(NAME)

re: fclean all

testclean:
	$(PREFIX)rm -f $(TEST_OBJS)
	$(PREFIX)@if [ -d $(TEST_OBJ_F) ]; then rm -rf $(TEST_OBJ_F); fi

testfclean: testclean
	$(PREFIX)rm -f $(TEST_FNAME)

retest: testfclean test

memcheck:
	$(PREFIX)valgrind --suppressions=tests/valgrind.supp --leak-check=full --show-leak-kinds=all $(TEST_FNAME)

ALLOWED_EXTERNAL_FUNCTIONS = mlx_ free printf __stack_chk_fail exit _GLOBAL_OFFSET_TABLE_ open close gettimeofday sqrt cos

ALLOW_EXTERNAL_GREP = $(foreach pattern,$(ALLOWED_EXTERNAL_FUNCTIONS),| grep -v "$(pattern)")

external_calls:
	$(PREFIX)ctags -R --c-kinds=f --fields=+n --output-format=xref --languages=c ./sources ./libft/sources | grep -v " static " | awk '{print $$1}' > functions.txt
	$(PREFIX)make
	$(PREFIX)find build -name "*.o" -exec nm -u {} \; | awk '{print $2}' | sort -u > all_calls.txt
	$(PREFIX)grep -vFf functions.txt all_calls.txt $(ALLOW_EXTERNAL_GREP) > forbidden_calls.txt || true
	@if [ -s forbidden_calls.txt ]; then \
        echo "Error: Forbidden external calls detected:"; \
        cat forbidden_calls.txt; \
        exit 1; \
    fi
	$(PREFIX)rm -f functions.txt all_calls.txt forbidden_calls.txt

fulltest_common:
	cd libft && make fulltest_trapped
	$(PREFIX)make fclean testfclean
	$(PREFIX)cd sources && norminette | tee norminette_log.txt && grep -q "^Error:" norminette_log.txt || true
	$(PREFIX)if grep -q "^Error:" sources/norminette_log.txt; then \
		echo "Norminette errors found. Please fix them before running the tests."; \
		exit 1; \
	fi
	$(PREFIX)make external_calls test_trapped memcheck

fulltest_vania: fulltest_common
	$(PREFIX)make PREPROC_DEFINES="$(PREPROC_DEFINES) -DVANIA" test_trapped memcheck

fulltest: fulltest_common
	#$(PREFIX)make test_trapped memcheck

PHONY: all pre clean fclean re test fulltest testclean testfclean retest memcheck memcheck_interactive fulltest_common fulltest_vania tania vania minivania all_trapped all_fancy all_printf bonus prere pretestfclean prefclean test_trapped run debug mem
########################################

all_trapped:
	$(PREFIX)make PREPROC_DEFINES="$(PREPROC_DEFINES) -DFT_CALLOC_IF_TRAPPED -DFANCY_IFACE" all

vania:
	$(PREFIX)cd libft && make fulltest_trapped_nonorm
	$(PREFIX)make fclean testfclean
	$(PREFIX)make minivania

minivania:
	$(PREFIX)make all_fancy test && ./$(TEST_FNAME)
