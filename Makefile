CC = cc
NAME = cube3D
COMPILE_FLAGS = -Wall -Wextra -Werror -g -c
LINK_FLAGS = -lft -Llibft -lreadline -lm
MLX_F = minilibx_opengl_20191021
INCLUDES = -I . -I libft -I $(MLX_F) -I get_next_line
MLX_FLAGS = -Lmlx -lmlx -L/usr/lib/X11 -lXext -lX11

MLX_SOURCE_ADDRESS = https://cdn.intra.42.fr/document/document/31892/minilibx_opengl.tgz
MLX_ARCHIVE = minilibx.tgz
PREFIX = 
PREPROC_DEFINES =

UNAME := $(shell uname)

MLX_L_FLAGS			=	-lXext -lX11 -lm -lz
MLX_M_FLAGS			=	-L$(MLX_F) -lmlx -framework OpenGL -framework AppKit

ifeq ($(UNAME), Linux)
	MLX_FLAGS		=	$(MLX_L_FLAGS)
else
	MLX_FLAGS		=	$(MLX_M_FLAGS)
endif

SOURCE_F = sources
TEST_F = tests

MAP_PARSING_NAMES = map_parse.c
MAP_PARSING_F = map_parse
MAP_PARSING_SRCS = $(addprefix $(MAP_PARSING_F)/,$(MAP_PARSING_NAMES))

SRC_NAMES = 
ENDPOINT_NAME = main.c

SRC_SRCS = $(addprefix $(SOURCE_F)/, $(SRC_NAMES))
ENDPOINT_SRC = $(addprefix $(SOURCE_F)/, $(ENDPOINT_NAME))
ENDPOINT_OBJ = $(OBJ_F)$(ENDPOINT_NAME:.c=.o)

TEST_NAMES = units.c e2e.c
TEST_ENDPOINT_NAME = main_test.c
TEST_SRCS = $(addprefix $(TEST_F)/, $(TEST_NAMES))
TEST_ENDPOINT_SRC = $(addprefix $(TEST_F)/, $(TEST_ENDPOINT_NAME))
TEST_FNAME = $(TEST_F)/test

OBJ_F = build/
TEST_OBJ_F = $(OBJ_F)tests/

OBJS = $(addprefix $(OBJ_F), $(SRC_NAMES:.c=.o)) $(addprefix $(OBJ_F), $(MAP_PARSING_SRCS:.c=.o))
TEST_OBJS = $(addprefix $(TEST_OBJ_F), $(TEST_NAMES:.c=.o))
TEST_ENDPOINT_OBJ = $(OBJ_F)$(TEST_ENDPOINT_NAME:.c=.o)

DIRS = $(MAP_PARSING_F)

OBJ_DIRS = $(addprefix $(OBJ_F), $(DIRS))

vpath %.c $(SOURCE_F) $(TEST_F)

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
	$(PREFIX)$(CC) $(OBJS) $(ENDPOINT_OBJ) -o $@ $(LINK_FLAGS) -L$(MLX_F) $(MLX_FLAGS)

$(OBJ_F)%.o: %.c $(OBJ_DIRS)
	$(PREFIX)$(CC) $(COMPILE_FLAGS) $< -o $@ $(INCLUDES) $(PREPROC_DEFINES)

$(TEST_OBJ_F):
	$(PREFIX)mkdir -p $(TEST_OBJ_F)

$(TEST_OBJ_F)%.o: $(TEST_F)/%.c $(TEST_OBJ_F)
	$(PREFIX)$(CC) $(COMPILE_FLAGS) $< -o $@ $(INCLUDES) $(PREPROC_DEFINES)

test_trapped:
	$(PREFIX)make PREPROC_DEFINES="$(PREPROC_DEFINES) -DFT_CALLOC_IF_TRAPPED" test

test: $(OBJ_DIRS) $(TEST_OBJ_F) $(OBJS) $(TEST_OBJS) $(TEST_ENDPOINT_OBJ) 
	$(PREFIX)$(CC) $(OBJS) $(TEST_OBJS) $(TEST_ENDPOINT_OBJ) -o $(TEST_FNAME) $(LINK_FLAGS)

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

fulltest_common:
	$(PREFIX)cd libft && make fulltest_trapped
	$(PREFIX)make fclean testfclean
	$(PREFIX)cd sources && norminette sources/*
	$(PREFIX)make pre all_trapped

fulltest_vania: fulltest_common
	$(PREFIX)make PREPROC_DEFINES="$(PREPROC_DEFINES) -DVANIA" test_trapped memcheck

fulltest: fulltest_common
	$(PREFIX)make test_trapped memcheck

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