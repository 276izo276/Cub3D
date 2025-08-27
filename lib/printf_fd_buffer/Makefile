CC = cc
CFLAGS = -Wall -Wextra -Werror -MD -g3
SHELL = /bin/bash
SRCS = \
printf_charlst_1.c \
printf_charlst_2.c \
printf_decimal.c \
printf_hex.c \
printf_pointer.c \
printf_printf.c \
printf_putchar.c \
printf_putstr.c \
printf_unsigned.c \
printf_utils.c

HEADER_DIR = header
HEADER = header/ft_printf.h

MY_NAME = ft_printf.a

OBJS = $(addprefix .obj/, $(SRCS:.c=.o))
DEPS = $(addprefix .obj/, $(SRCS:.c=.d))

G3 = OFF

MAKEFLAGS += --no-print-directory

.DEFAULT_GOAL = all

-include $(DEPS)

# Redefinition
ifeq ($(G3), ON)
CFLAGS += -g3
endif

all: start_build_aff $(MY_NAME)

$(MY_NAME): $(OBJS) $(HEADER)
	@ar rc $(MY_NAME) $(OBJS)
	@echo -e "    ${_BOLD}${_GREEN}🗂️  ◀◀◀ ${_LIME}Creating File 📑📑📑 ${_YELLOW}$(MY_NAME)${_END}"

.obj/%.o: %.c 
	@mkdir -p .obj
	@echo -e "    ${_LIME}${_BOLD}$(call DELETE_EXT,${MY_NAME})	${_END}${_GREEN}Compiling : ${_END}$(CC) ${_BLUE} $(CFLAGS) ${_PURPLE} $(call GET_FILE,$(call DELETE_EXT,$<))${_END}"
	@$(CC) $(CFLAGS) -c $< -o $@ -I $(HEADER_DIR)

re: fclean all

clean:
	@rm -rf .obj
	@echo -e "    ${_RED}${_BOLD}🗑️  ◀◀◀ Deleting files 🚮 ${_YELLOW}$(call DELETE_EXT,${MY_NAME}) objects${_END}\n"

fclean: clean cln

cln:
	@rm -rf $(MY_NAME)
	@echo -e "    ${_RED}${_BOLD}🗑️  ◀◀◀ Deleting file  🚮 ${_YELLOW}$(MY_NAME)${_END}\n"

.PHONY:start_build_aff
start_build_aff:
	@echo -e -n "\n${_BOLD}${_RED}Start Building  ⚙️  🛠️  ⚙️ 	${_GREEN}${_UNDER}$(MY_NAME)${_END} :	( "
	@$(call TO_MAJ_OBJ,${SRCS})
	@echo " / $(call NB_FILE,${SRCS}) to update )"

# Macro
define GET_FOLDER
$$(echo -e $(1) | sed 's/\/.*//g')
endef

define GET_FILE
$$(echo -e $(1) | sed 's/.*\///g')
endef

define	DELETE_EXT
$$(echo -e "$(1)" | sed -E 's/\.[a-z]+$$//g')
endef

define	NB_FILE
$$(echo $(1) | wc -w)
endef

define TO_MAJ_OBJ
to_maj=0;\
for file in $(1); do\
	f="$(call DELETE_EXT,$$file)";\
	f=".obj/$$f.o";\
	if [ "$$f" -ot "$$file" ];then\
		to_maj=$$((to_maj + 1));\
	fi;\
done;\
echo -n "$$to_maj";
endef

# Modifiers
_END=		\033[0m
_BOLD=		\033[1m
_ITALIC=	\033[3m
_UNDER=		\033[4m
_REV=		\033[7m
_ROD=		\033[9m

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