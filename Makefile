#																#
#			 ██████╗██╗   ██╗██████╗ ██████╗ ██████╗ 			#
#			██╔════╝██║   ██║██╔══██╗╚════██╗██╔══██╗			#
#			██║     ██║   ██║██████╔╝ █████╔╝██║  ██║			#
#			██║     ██║   ██║██╔══██╗ ╚═══██╗██║  ██║			#
#			╚██████╗╚██████╔╝██████╔╝██████╔╝██████╔╝			#
#			 ╚═════╝ ╚═════╝ ╚═════╝ ╚═════╝ ╚═════╝ 			#
                                         


DEBUG_VALUE ?= 0
DBG ?= 1
FULL_NAME ?= 1

CC = cc
CFLAGS = -Wall -Werror -Wextra -MMD -DDEBUG_VALUE=${DEBUG_VALUE} -g3
SHELL = /bin/bash

EXECFLAGS = -lXext -lX11 -lm

FILES	=									\
				main.c						\

UTILS	=									\
				abs_value.c 				\
				debug.c						\
				dup.c						\
				free.c						\
				ft_bzero.c					\
				ft_strcmp.c					\
				ft_strlen.c					\
				time.c						

FILES	+=	$(addprefix srcs/utils/,$(UTILS))

PARSING	=									\
				read_content.c				\
				start_parsing.c				\
				fill_color.c				\
				fill_texture.c				\
				fill_texture_utils.c		\
				check_map_is_closed.c		\
				open_texture.c				\
				verif_map.c					\
				init.c						\

FILES	+=	$(addprefix srcs/parsing/,$(PARSING))

STRUCT	=									\
				init_t_coo.c				

FILES	+=	$(addprefix srcs/struct/,$(STRUCT))

MLX_UTILS	=								\
				handle_window.c				\
				mini_map.c					\
				mini_move.c					\
				mini_rotate.c				\
				aff_mini_map.c				\
				utils_aff_mini_map.c		\
				aff_player_mini_map.c		\

FILES	+=	$(addprefix srcs/mlx_utils/,$(MLX_UTILS))

GAME		=								\
				raycasting.c				\
				raycasting_utils.c			\
				display/display.c 			\
				input_move.c				\
				game_loop.c					\
				display/display_floor.c		\
				display/display_sky.c		\

			
FILES	+=	$(addprefix srcs/game/,$(GAME))

FILES_BONUS =								\
				main_bonus.c				\

UTILS_BONUS =								\
				abs_value.c 				\
				debug.c						\
				dup.c						\
				free.c						\
				ft_bzero.c					\
				ft_strcmp.c					\
				ft_strlen.c					\
				time.c						

FILES_BONUS	+=	$(addprefix srcs_bonus/utils/,$(UTILS_BONUS))

PARSING_BONUS	=							\
				read_content.c				\
				start_parsing.c				\
				fill_texture.c				\
				fill_texture_wall.c			\
				fill_texture_utils.c		\
				check_map_is_closed.c		\
				open_texture.c				\
				verif_map.c					\
				init.c						\

FILES_BONUS	+=	$(addprefix srcs_bonus/parsing/,$(PARSING_BONUS))

STRUCT_BONUS	=							\
				init_t_coo.c				

FILES_BONUS	+=	$(addprefix srcs_bonus/struct/,$(STRUCT_BONUS))

MLX_UTILS_BONUS	=							\
				handle_window.c				\
				mini_map.c					\
				mini_move.c					\
				mini_rotate.c				\
				handle_foot_mini.c 			\
				aff_mini_map.c				\
				utils_aff_mini_map.c		\
				aff_player_mini_map.c		\

FILES_BONUS	+=	$(addprefix srcs_bonus/mlx_utils/,$(MLX_UTILS_BONUS))

GAME_BONUS		=								\
				raycasting_door.c				\
				raycasting.c					\
				raycasting_utils.c				\
				display/display.c 				\
				display/display_hand.c			\
				display/display_door.c			\
				display/display_msg.c			\
				environment/handle_door.c 		\
				input_move.c					\
				game_loop.c						\
				display/display_floor.c			\
				display/display_sky.c			\
				menu/start_menu/display_menu.c	\
				menu/start_menu/draw_border.c	\
				menu/pause_menu/handle_pause_menu.c \
				spell/spell.c				\

FILES_BONUS	+=	$(addprefix srcs_bonus/game/,$(GAME_BONUS))

ENEMY			=							\
				init.c						\
				free.c						\
				move.c						\

FILES_BONUS	+=	$(addprefix srcs_bonus/game/enemy/,$(ENEMY))

OBJS =			$(addprefix .obj/, $(FILES:.c=.o))

OBJS_BONUS =	$(addprefix .obj/, $(FILES_BONUS:.c=.o))

DEPS =			$(addprefix .obj/, $(FILES:.c=.d))

DEPS_BONUS =	$(addprefix .obj/, $(FILES_BONUS:.c=.d))

# path to lib folder to exec norm
NORM_LIB = \
lib/

# path to .h for the main project basic
MY_HEADER = \
includes/cub3d.h	\
includes/debug.h	\
includes/parsing.h	\
includes/player.h	\
includes/color.h	\
includes/libmlx.h	\
includes/struct.h	\
includes/texture.h	\
includes/time.h		\
includes/utils.h	\

# set the path to the .h main project bonus
HEADER_BONUS = \
includes/header_bonus/cub3d_bonus.h	\
includes/header_bonus/debug_bonus.h	\
includes/header_bonus/parsing_bonus.h	\
includes/header_bonus/player_bonus.h	\
includes/header_bonus/color_bonus.h	\
includes/header_bonus/libmlx_bonus.h	\
includes/header_bonus/struct_bonus.h	\
includes/header_bonus/texture_bonus.h	\
includes/header_bonus/time_bonus.h	\
includes/header_bonus/utils_bonus.h	\


# set the main project header dir
HEADER_DIR = \
includes

# set the path to the .a lib
STATIC_LIB	=						\
lib/printf_fd_buffer/ft_printf.a	\
lib/t_lst/t_lst.a					\
lib/gnl/get_next_line.a					

EXTERN_LIB	=						\
minilibx-linux/libmlx_Linux.a

# set the -I before the path
# the path to the header lib dir
ALL_I_DIR_HEADER	=				\
-I includes/header_mandatory		\
-I lib/printf_fd_buffer/header		\
-I lib/t_lst/header					\
-I lib/gnl/header					\
-I minilibx-linux					

ALL_I_DIR_HEADER_BONUS	=			\
-I includes/header_bonus			\
-I lib/printf_fd_buffer/header		\
-I lib/t_lst/header					\
-I lib/gnl/header					\
-I minilibx-linux					

CURRENT_HEADERS = $(ALL_I_DIR_HEADER)

# exec name for bonus
BONUS_NAME = cub3D_bonus

#executable name for the main project
MY_NAME = cub3D

G3 = OFF

MSG="modif Makefile"

MAKEFLAGS += --no-print-directory

.DEFAULT_GOAL = all

#
#
#
#
#
#			██████╗ ███████╗██████╗ ███████╗███████╗██╗███╗   ██╗██╗████████╗██╗ ██████╗ ███╗   ██╗
#			██╔══██╗██╔════╝██╔══██╗██╔════╝██╔════╝██║████╗  ██║██║╚══██╔══╝██║██╔═══██╗████╗  ██║
#			██████╔╝█████╗  ██║  ██║█████╗  █████╗  ██║██╔██╗ ██║██║   ██║   ██║██║   ██║██╔██╗ ██║
#			██╔══██╗██╔══╝  ██║  ██║██╔══╝  ██╔══╝  ██║██║╚██╗██║██║   ██║   ██║██║   ██║██║╚██╗██║
#			██║  ██║███████╗██████╔╝███████╗██║     ██║██║ ╚████║██║   ██║   ██║╚██████╔╝██║ ╚████║
#			╚═╝  ╚═╝╚══════╝╚═════╝ ╚══════╝╚═╝     ╚═╝╚═╝  ╚═══╝╚═╝   ╚═╝   ╚═╝ ╚═════╝ ╚═╝  ╚═══╝

-include $(DEPS_BONUS) $(DEPS)

ifeq ($(G3), ON)
CFLAGS += -g3
endif

ifeq ($(NAME), FULL)
FULL_NAME = 1
else
	ifneq ($(NAME),)
		FULL_NAME = 0
	endif
endif

ifeq (${DBG}, 1)
	ifeq (${DEBUG_VALUE}, 1)
override DEBUG_VALUE = 0
override DBG = 2
	endif
endif

#
#
#
#
#
#			██████╗ ██╗   ██╗██╗     ███████╗███████╗
#			██╔══██╗██║   ██║██║     ██╔════╝██╔════╝
#			██████╔╝██║   ██║██║     █████╗  ███████╗
#			██╔══██╗██║   ██║██║     ██╔══╝  ╚════██║
#			██║  ██║╚██████╔╝███████╗███████╗███████║
#			╚═╝  ╚═╝ ╚═════╝ ╚══════╝╚══════╝╚══════╝

#	▌     ▘
#	▛▌▀▌▛▘▌▛▘▛▘
#	▙▌█▌▄▌▌▙▖▄▌

.PHONY:all
all: change_name_full clear_console reset_debug $(STATIC_LIB) $(EXTERN_LIB) start_build_aff ${MY_NAME}


${MY_NAME}: CURRENT_HEADERS = $(ALL_I_DIR_HEADER)
${MY_NAME}:  $(STATIC_LIB) $(EXTERN_LIB) $(OBJS)
	@echo -e "    ${_BOLD}${_GREEN}💿  ◀◀◀ ${_LIME}Creating Executable 📑🗂️   ${_YELLOW}$(MY_NAME)${_END}"
	@$(CC) $(OBJS) $(STATIC_LIB) $(EXTERN_LIB) -o $(MY_NAME) $(EXECFLAGS)


.PHONY:bonus
bonus: change_name_full clear_console $(STATIC_LIB) $(EXTERN_LIB) start_build_aff_bonus $(BONUS_NAME)

$(BONUS_NAME): CURRENT_HEADERS = $(ALL_I_DIR_HEADER_BONUS)
$(BONUS_NAME): $(STATIC_LIB) $(EXTERN_LIB) $(OBJS_BONUS)
	@echo -e "    ${_BOLD}${_GREEN}💿  ◀◀◀ ${_LIME}Creating Executable 📑🗂️   ${_YELLOW}$(BONUS_NAME)${_END}"
	@$(CC) $(OBJS_BONUS) $(STATIC_LIB) $(EXTERN_LIB) -o $(BONUS_NAME) $(EXECFLAGS)


.obj/%.o: %.c
	@mkdir -p $(call GET_ALL_FOLDER,$@)
	@if [ "${FULL_NAME}" = "1" ]; then\
		echo -e "	${_LIME}${_BOLD}${MY_NAME}	${_END}${_GREEN}Compiling : ${_END}$(CC) ${_BLUE} $(CFLAGS) ${_PURPLE} $<${_END}";\
	else \
		echo -e "	${_LIME}${_BOLD}${MY_NAME}	${_END}${_GREEN}Compiling : ${_END}$(CC) ${_BLUE} $(CFLAGS) ${_PURPLE} $(call GET_FILE,$(call DELETE_EXT,$<))${_END}";\
	fi;
	@$(CC) $(CURRENT_HEADERS) $(CFLAGS) -c $< -o $@



#	  ▜
#	▛▘▐ █▌▀▌▛▌
#	▙▖▐▖▙▖█▌▌▌

.PHONY:re
re: fclean all


.PHONY:re_all
re_all: fclean_all all


.PHONY:clean
clean:
	@rm -rf .obj
	@echo -e "    ${_RED}${_BOLD}🗑️  ◀◀◀ Deleting files 🚮 ${_YELLOW}${MY_NAME} objects${_END}\n"


.PHONY:clean_all
clean_all: clean clean_lib


.PHONY:fclean
fclean: clean cln


.PHONY:fclean_all
fclean_all: fclean cln_all clean_all


.PHONY:cln
cln:
	@rm -rf $(MY_NAME)
	@echo -e "    ${_RED}${_BOLD}🗑️  ◀◀◀ Deleting file  🚮 ${_YELLOW}$(MY_NAME)${_END}\n"
	@rm -rf $(BONUS_NAME)
	@echo -e "    ${_RED}${_BOLD}🗑️  ◀◀◀ Deleting file  🚮 ${_YELLOW}$(BONUS_NAME)${_END}\n"


.PHONY:cln_all
cln_all: cln cln_lib



#	▜ ▘▌
#	▐ ▌▛▌
#	▐▖▌▙▌

%.a: force
	@make -C $(call GET_ALL_FOLDER,$@);


.PHONY:clean_lib
clean_lib:
	@for lib in $(STATIC_LIB) $(EXTERN_LIB); do\
		make -C $(call GET_ALL_FOLDER,$$lib) clean;\
	done


.PHONY:fclean_lib
fclean_lib:
	@for lib in $(STATIC_LIB); do\
		make -C  $(call GET_ALL_FOLDER,$$lib) fclean;\
	done


.PHONY:cln_lib
cln_lib:
	@for lib in $(STATIC_LIB); do\
		make -C $(call GET_ALL_FOLDER,$$lib) cln;\
	done

#
#
#
#
#
#			███╗   ███╗███████╗███████╗███████╗ █████╗  ██████╗ ███████╗
#			████╗ ████║██╔════╝██╔════╝██╔════╝██╔══██╗██╔════╝ ██╔════╝
#			██╔████╔██║█████╗  ███████╗███████╗███████║██║ ████╗█████╗
#			██║╚██╔╝██║██╔══╝  ╚════██║╚════██║██╔══██║██║   ██║██╔══╝
#			██║ ╚═╝ ██║███████╗███████║███████║██║  ██║╚██████╔╝███████╗
#			╚═╝     ╚═╝╚══════╝╚══════╝╚══════╝╚═╝  ╚═╝ ╚═════╝ ╚══════╝

.PHONY:start_build_aff
start_build_aff:
	@echo -e -n "\n${_BOLD}${_RED}Start Building  ⚙️  🛠️  ⚙️ 	${_GREEN}${_UNDER}$(MY_NAME)${_END} :	"
	@echo "( $(call TO_MAJ_OBJ,${FILES}) / $(call NB_FILE,${FILES}) to update )"


.PHONY:start_build_aff_bonus
start_build_aff_bonus:
	@echo -e "\n${_BOLD}${_RED}Start Building  ⚙️  🛠️  ⚙️ 	${_GREEN}${_UNDER}$(BONUS_NAME)${_END}		: "


.PHONY:clear_console
clear_console:
	clear

#
#
#
#
#
#			███╗   ██╗ ██████╗ ██████╗ ███╗   ███╗██╗███╗   ██╗███████╗████████╗████████╗███████╗
#			████╗  ██║██╔═══██╗██╔══██╗████╗ ████║██║████╗  ██║██╔════╝╚══██╔══╝╚══██╔══╝██╔════╝
#			██╔██╗ ██║██║   ██║██████╔╝██╔████╔██║██║██╔██╗ ██║█████╗     ██║      ██║   █████╗
#			██║╚██╗██║██║   ██║██╔══██╗██║╚██╔╝██║██║██║╚██╗██║██╔══╝     ██║      ██║   ██╔══╝
#			██║ ╚████║╚██████╔╝██║  ██║██║ ╚═╝ ██║██║██║ ╚████║███████╗   ██║      ██║   ███████╗
#			╚═╝  ╚═══╝ ╚═════╝ ╚═╝  ╚═╝╚═╝     ╚═╝╚═╝╚═╝  ╚═══╝╚══════╝   ╚═╝      ╚═╝   ╚══════╝

.PHONY:norm
norm: change_name_full clear_console
	@echo -e "\n	${_BOLD}${_RED}Do you want to ignore INVALID_HEADER error?${_END} ${_ORANGE}(y/n)${_END}";\
	echo -n ">>> ";\
	read -n 1 response;\
	echo -e "\n⚙️ ⚙️ ${_BOLD}${_BLUE}${_UNDER}Executing norminette${_END} ⚙️ ⚙️ ";\
	L_OK="";\
	L_KO="";\
	STATE=0;\
	tmp_tab=(" ." " .." " ..." " ...." " .....");\
	lib="";\
	for l in ${STATIC_LIB}; do\
		lib="$$lib $(call GET_ALL_FOLDER,$$l)";\
	done;\
	for file in ${FILES} ${MY_HEADER} $$lib ; do\
		STATE=$$(((STATE + 1) % 5));\
		echo -e -n "${_ERASE}\r $${tmp_tab[$$STATE]}\r";\
		if [ "${FULL_NAME}" = "1" ]; then\
			tmp_name="$$file";\
		else \
			tmp_name="$(call GET_FILE,$$file)";\
		fi;\
		temp=$$(norminette $$file);\
		if [ "$$response" = "y" ]; then\
			gp=$$(echo "$$temp" | grep "Error: " | grep -v "INVALID_HEADER");\
		else \
			gp=$$(echo "$$temp" | grep "Error: ");\
		fi;\
		if [ "$$gp" = "" ]; then\
			L_OK="$$L_OK $$tmp_name";\
		else \
			L_KO="$$L_KO $$tmp_name";\
		fi;\
	done;\
	echo -e -n "${_ERASE}\r";\
	echo -e "${_BOLD}${_LIME}NORM OK :${_END}";\
	for file in $$L_OK; do\
		echo -e "    ${_GREEN}❯❯❯❯  ${_PURPLE}$$file${_END}";\
	done;\
	echo -e "${_BOLD}${_RED}NORM KO :${_END}";\
	for file in $$L_KO; do\
		echo -e "    ${_RED}❯❯❯❯  ${_PURPLE}$$file${_END}";\
	done;

#
#
#
#
#
#			██████╗ ███████╗██████╗ ██╗   ██╗ ██████╗
#			██╔══██╗██╔════╝██╔══██╗██║   ██║██╔════╝
#			██║  ██║█████╗  ██████╔╝██║   ██║██║  ███╗
#			██║  ██║██╔══╝  ██╔══██╗██║   ██║██║   ██║
#			██████╔╝███████╗██████╔╝╚██████╔╝╚██████╔╝
#			╚═════╝ ╚══════╝╚═════╝  ╚═════╝  ╚═════╝


#	      ▌ ▜                ▐▘  ▜ ▜ 
#	█▌▛▌▀▌▛▌▐ █▌  ▛▌▀▌▛▛▌█▌  ▜▘▌▌▐ ▐ 
#	▙▖▌▌█▌▙▌▐▖▙▖  ▌▌█▌▌▌▌▙▖  ▐ ▙▌▐▖▐▖
#                                 

.PHONY:change_name_full
change_name_full:
	@if [ "${NAME}" = "FULL" ]; then\
		$(call MODIF_FULL_NAME_VALUE,1)\
	else \
		if [ "${NAME}" != "" ]; then\
			$(call MODIF_FULL_NAME_VALUE,0)\
		fi;\
	fi


#	      ▌ ▜         ▘  ▗    ▌  ▌
#	█▌▛▌▀▌▛▌▐ █▌  ▛▌▛▘▌▛▌▜▘  ▛▌█▌▛▌▌▌▛▌
#	▙▖▌▌█▌▙▌▐▖▙▖  ▙▌▌ ▌▌▌▐▖  ▙▌▙▖▙▌▙▌▙▌
#	              ▌                  ▄▌
.PHONY:debug
debug: clear_console
	@$(call PRINT_GET_DBG)\
	read -s -n 1 dbg;\
	while ! echo $$dbg | grep -Eq "[01]"; do\
		clear;\
		$(call BAD_VALUE_GET,$$dbg)\
		$(call PRINT_GET_DBG)\
		read -s -n 1 dbg;\
	done;\
	old_val="$$(cat Makefile | grep -oP '^DEBUG_VALUE \?= \K\d+')";\
	if [ "$$old_val" != "$$dbg" ]; then\
		$(call MODIF_DEBUG_VALUE,$$dbg)\
		touch ${HEADER_DIR}/debug.h;\
	fi;\
	make DBG=0

.PHONY:reset_debug
reset_debug:
	@if [ "${DBG}" = "2" ]; then\
		$(call MODIF_DEBUG_VALUE,0)\
		touch ${HEADER_DIR}/debug.h;\
	fi;

#
#
#
#
#
#			██╗   ██╗████████╗██╗██╗     ███████╗
#			██║   ██║╚══██╔══╝██║██║     ██╔════╝
#			██║   ██║   ██║   ██║██║     ███████╗
#			██║   ██║   ██║   ██║██║     ╚════██║
#			╚██████╔╝   ██║   ██║███████╗███████║
#			 ╚═════╝    ╚═╝   ╚═╝╚══════╝╚══════╝

.PHONY:maj_deps
maj_deps:

.PHONY:push_all
push_all:
	make fclean_all
	git add .
	git commit -m ${MSG}
	git push


.PHONY:force
force:

start:
	valgrind --show-leak-kinds=all --leak-check=full --suppressions=.supp ./cub3D maps/t1.cub 

#
#
#
#
#
#			███╗   ███╗ █████╗  ██████╗██████╗  ██████╗
#			████╗ ████║██╔══██╗██╔════╝██╔══██╗██╔═══██╗
#			██╔████╔██║███████║██║     ██████╔╝██║   ██║
#			██║╚██╔╝██║██╔══██║██║     ██╔══██╗██║   ██║
#			██║ ╚═╝ ██║██║  ██║╚██████╗██║  ██║╚██████╔╝
#			╚═╝     ╚═╝╚═╝  ╚═╝ ╚═════╝╚═╝  ╚═╝ ╚═════╝


#	      ▌▘▐▘      ▗ ▌
#	▛▛▌▛▌▛▌▌▜▘  ▛▌▀▌▜▘▛▌
#	▌▌▌▙▌▙▌▌▐   ▙▌█▌▐▖▌▌
#	            ▌
define	GET_X_FOLDER
$$(\
	echo -e $(1) | sed -E "s/(\/[^\/]+){$2}$$//g";\
)
endef

define	GET_FIRST_FOLDER
$$(\
	echo -e $(1) | sed 's/\/.*//g';\
)
endef

define	GET_ALL_FOLDER
$$(\
	var=$$(echo -e $(1) | sed -E 's/\/?[^\/]+$$//g');\
	if [ "$$var" = "" ];then\
		echo "$$var";\
	else\
		echo "$$var/";\
	fi;\
)
endef

define	GET_LIST_FOLDER
$$(\
	echo -e $(1) | sed 's/\//\t/g';\
)
endef

define	DELETE_EXT
$$(\
	echo -e "$(1)" | sed -E 's/\.[a-z]+$$//g';\
)
endef


#	    ▘  ▗
#	▛▌▛▘▌▛▌▜▘  ▛▛▌█▌▛▘▛▘▀▌▛▌█▌
#	▙▌▌ ▌▌▌▐▖  ▌▌▌▙▖▄▌▄▌█▌▙▌▙▖
#	▌                     ▄▌
define MSG_LAUCH
echo -e "${_GREEN}Lauching ${_PURPLE}${_BOLD}${MY_NAME}${_END} ${_GREEN}with >>>${_END}"
endef

define	BAD_VALUE_GET
echo -e "${_RED}${_BOLD}Error ${_LIME}'$(1)' ${_RED}This is not a good value ${_END}";
endef

define	PRINT_GET_DBG
echo -e "${_BOLD}${_CYAN}Give a Value :${_END}";\
echo -e "\t${_PURPLE}Program ${_LIME}${_BOLD}Without ${_END}${_PURPLE}debug print >>>\t${_ORANGE}${_BOLD}0${_END}";\
echo -e "\t${_PURPLE}Program ${_RED}${_BOLD} With   ${_END}${_PURPLE}debug print >>>\t${_ORANGE}${_BOLD}1${_END}";
endef


#	▐▘▘▜            ▌
#	▜▘▌▐ █▌▛▘  ▟▖  ▛▌█▌▛▌▛▘
#	▐ ▌▐▖▙▖▄▌  ▝   ▙▌▙▖▙▌▄▌
#	                   ▌
define	GET_FILE
$$(\
	echo -e $(1) | sed 's/.*\///g';\
)
endef

define	NB_FILE
$$(\
	echo $(1) | wc -w;\
)
endef

define	TO_MAJ_OBJ
$$(\
	to_maj=0;\
	for file in ${FILES}; do\
		if [ "$(call DEPS_NEWER,$$file)" != "0" ];then\
			to_maj=$$((to_maj + 1));\
		fi;\
	done;\
	echo "$$to_maj";\
)
endef

define DEPS_NEWER
$$(\
	name="$(1)";\
	dfile=".obj/$$(echo $$name | sed 's/\.c/\.d/g')";\
	if [ -r "$$dfile" ];then\
		all="$$(cat $$dfile | sed ':a; N; $$! ba; s/\\\n//g')";\
		first=$$(echo "$$all" | sed -E 's/(.*.o):([^.o].*)/\1/g');\
		deps=$$(echo "$$all" | sed -E 's/(.*.o):([^.o].*)/\2/g');\
		older=0;\
		newer=0;\
		for file in $$deps;do\
			if [ "$$file" -nt "$$first" ];then\
				newer=$$((newer + 1));\
			else\
				older=$$((older + 1));\
			fi;\
		done;\
		echo "$$newer";\
	else\
		echo "1";\
	fi;\
)
endef


#	  ▗ ▘▜
#	▌▌▜▘▌▐ ▛▘
#	▙▌▐▖▌▐▖▄▌
define	EXIT_CODE
$$(\
	echo $$?;\
)
endef

define	MODIF_DEBUG_VALUE
content="$$(cat Makefile | sed -E "s/DEBUG_VALUE \?= [0-9]/DEBUG_VALUE \?= $(1)/g")";\
echo "$$content" > Makefile;
endef

define	MODIF_FULL_NAME_VALUE
content="$$(cat Makefile | sed -E "s/FULL_NAME \?= [0-9]/FULL_NAME \?= $(1)/g")";\
echo "$$content" > Makefile;
endef


#
#
#
#
#
#			 ██████╗ ██████╗ ██╗      ██████╗ ██████╗
#			██╔════╝██╔═══██╗██║     ██╔═══██╗██╔══██╗
#			██║     ██║   ██║██║     ██║   ██║██████╔╝
#			██║     ██║   ██║██║     ██║   ██║██╔══██╗
#			╚██████╗╚██████╔╝███████╗╚██████╔╝██║  ██║
#			 ╚═════╝ ╚═════╝ ╚══════╝ ╚═════╝ ╚═╝  ╚═╝

_END=		\033[0m
_BOLD=		\033[1m
_ITALIC=	\033[3m
_UNDER=		\033[4m
_REV=		\033[7m
_ROD=		\033[9m
_ERASE=		\033[2K

# Colors
_GREY=		\033[30m
_RED=		\033[31m
_GREEN=		\033[32m
_YELLOW=	\033[33m
_BLUE=		\033[34m
_PURPLE=	\033[35m
_CYAN=		\033[36m
_WHITE=		\033[37m
_LIME=		\033[38;2;0;255;0m
_ORANGE=	\033[38;2;255;165;0m

# Backgroud Colors
_BGREY=		\033[40m
_BRED=		\033[41m
_BGREEN=	\033[42m
_BYELLOW=	\033[43m
_BBLUE=		\033[44m
_BPURPLE=	\033[45m
_BCYAN=		\033[46m
_BWHITE=	\033[47m
_BLIME=		\033[48;2;0;255;0m
_BORANGE=	\033[48;2;255;165;0m
