################################################################################
#                                     CONFIG                                   #
################################################################################


NAME	= minishell
CC 		= gcc

#CFLAGS	= -Wall -Wextra -Werror -lreadline -L/opt/homebrew/opt/readline/lib -I/opt/homebrew/opt/readline/include -fsanitize=address
#CFLAGS	= -Wall -Wextra -Werror -lreadline -L/usr/local/opt/readline/lib -I/usr/local/opt/readline/include -fsanitize=address
CFLAGS	= -Wall -Wextra -Werror -lreadline -L/Users/$(USER)/.brew/opt/readline/lib -I/Users/$(USER)/.brew0/opt/readline/include -fsanitize=address -g

CFLAGS_WRL = -Wall -Wextra -Werror
MAKE 	= make
MAKE_CLEAN	= make clean
MAKE_FCLEAN = make fclean
AUTHOR	= Dorian, Pauline, Tanguy, Alex
DATE	= 17/08/2022

NOVISU 	= 1 # 1 = no progress bar usefull when tty is not available

################################################################################
#                                 PROGRAM'S SRCS                               #
################################################################################

FILE_EXTENSION	= .c

SRCS_PATH		= ./src

INCLUDE_PATH	= ./include

LIB 			= ./libft/libft.a

TOK 			= ./tokenisation/
GNL 			= ./gnl/
BUILTINS 		= ./builtins/
ENV 			= ./environnement/
PARS			= ./parsing/
EXEC 			= ./execution/

SRCS			= $(TOK)tokenisation.c	$(TOK)tok_cmd.c $(TOK)tok_stdin.c $(TOK)tok_stdout.c $(TOK)utils_tokenisation.c $(TOK)check_type.c $(TOK)utils_tok_cmd.c $(TOK)utils_less_redir.c $(TOK)utils_great_redir.c $(TOK)check_status_binary.c \
 				  $(GNL)gnl.c	$(GNL)gnl_utils.c \
				  $(BUILTINS)echo.c $(BUILTINS)pwd.c $(BUILTINS)export.c $(BUILTINS)cd.c $(BUILTINS)env.c $(BUILTINS)unset.c $(BUILTINS)exit.c $(BUILTINS)utils_builtins.c \
				  $(ENV)clone_envp.c $(ENV)utils_envp.c \
				  $(PARS)parsing.c $(PARS)dollar.c $(PARS)utils_quotes.c $(PARS)remove_quotes.c $(PARS)utils_parsing.c $(PARS)syntax_errors.c $(PARS)syntax_errors_2.c $(PARS)get_full_pipe.c $(PARS)preparsing.c $(PARS)parsing_redirection.c $(PARS)utils_manage_redir.c \
				  $(EXEC)exec_global.c $(EXEC)pipe.c $(EXEC)get_path.c $(EXEC)split_pipe.c $(EXEC)utils_pipe.c $(EXEC)utils_run_exec.c \
				  welcome.c signals.c utils.c initializer.c errors.c

MAIN			= main.c

################################################################################
#                                  Makefile  objs                              #
################################################################################

SHELL := /bin/bash


OBJS				= $(addprefix objs/, ${SRCS:$(FILE_EXTENSION)=.o})
OBJ_MAIN			= $(addprefix objs/, ${MAIN:$(FILE_EXTENSION)=.o})

################################################################################
#                                 Makefile logic                               #
################################################################################

COM_COLOR   = \033[0;34m
OBJ_COLOR   = \033[0;36m
OK_COLOR    = \033[0;32m
ERROR_COLOR = \033[0;31m
WARN_COLOR  = \033[0;33m
NO_COLOR    = \033[m
BLACK =\e[0;30m
RED =\e[0;31m
G =\e[0;32m
Y =\e[0;33m
BLUE =\e[0;34m
MAGENTA =\e[0;35m
CYAN =\e[0;36m
WHITE =\e[0;37m
R =\e[0m

COM_STRING   = "Compiling:"

HASH	= 

ifeq ($(OS),Windows_NT) 
    detected_OS := Windows
else
    detected_OS := $(shell sh -c 'uname 2>/dev/null || echo Unknown')
endif

ifeq ($(detected_OS),Darwin) 
	RUN_CMD = script -q $@.log $1 > /dev/null; \
				RESULT=$$?
else ifeq ($(detected_OS),Linux)
	RUN_CMD = script -q -e -c "$(1)" $@.log > /dev/null; \
				RESULT=$$?; \
				sed -i '1d' $@.log; \
				sed -i "$$(($$(wc -l < $@.log)-1)),\$$d" $@.log
else
	RUN_CMD = $(1) 2> $@.log; \
				RESULT=$$?
endif

ifeq ($(shell git rev-parse HEAD &>/dev/null; echo $$?),0)
	DATE	:= $(shell git log -1 --date=format:"%d/%m/%Y %T" --format="%ad")
	HASH	:= $(shell git rev-parse --short HEAD)
endif

define run_and_test
printf "%b%-46b" "$(COM_COLOR)$(COM_STRING) " "$(OBJ_COLOR)$(@F)$(NO_COLOR)"; \
$(RUN_CMD); \
if [ $$RESULT -ne 0 ]; then \
	printf "%b\n" "$(ERROR_COLOR)[✖]$(NO_COLOR)"; \
	rm -rf .files_changed; \
	if [ $(NOVISU) -eq 0 ]; then \
		echo; \
	fi; \
elif [ -s $@.log ]; then \
	printf "%b\n" "$(WARN_COLOR)[⚠]$(NO_COLOR)"; \
else  \
	printf "%b\n" "$(OK_COLOR)[✓]$(NO_COLOR)"; \
fi; \
cat $@.log; \
rm -f $@.log; \
exit $$RESULT
endef

define save_files_changed
	FILE_CPP=`echo $(SRCS) $(MAIN)`; \
	FILE_OBJ=`find objs -type f -name '*.o' 2>/dev/null | sed 's/objs\///'`; \
	TO_COMPILE=`echo $$FILE_CPP | wc -w`; \
	for FILE in $$FILE_CPP; do \
		for OBJ in $$FILE_OBJ; do \
			if [ $${FILE%$(FILE_EXTENSION)} = $${OBJ%.o} ]; then \
				if [ $(SRCS_PATH)/$$FILE -ot objs/$$OBJ ]; then \
					FILE_DEP=`echo objs/$$OBJ | sed 's/\.o/\.d/'`; \
					HEAD_FILES=`< $$FILE_DEP xargs | grep -oh "\w*.h\w*"`; \
					RECOMPILE=0; \
					for HEAD in $$HEAD_FILES; do \
						if [ $(SRCS_PATH)/$$HEAD -nt objs/$$OBJ ]; then \
							RECOMPILE=1; \
							break; \
						fi; \
					done; \
					if [ $$RECOMPILE -eq 0 ]; then \
						((TO_COMPILE=$$TO_COMPILE-1)); \
					fi;\
				fi; \
			fi; \
		done; \
	done; \
	echo 0/$$TO_COMPILE > .files_changed
endef

define draw_bar
	FILE_TOTAL=`bash -c 'cat .files_changed | cut -d"/" -f2'`; \
	FILE_DONE=`bash -c 'cat .files_changed | cut -d"/" -f1'`; \
	if [ $$FILE_TOTAL -eq 0 ]; then \
		FILE_TOTAL=1; \
		FILE_DONE=1; \
	fi; \
	RES=`echo "scale=2; $$FILE_DONE/$$FILE_TOTAL*48" | bc`; \
	RES=`echo $${RES%%.*}`; \
	printf "$(OBJ_COLOR)[$(NO_COLOR)"; \
	i=0; \
	while [ $$i -lt 48 ]; do \
		if [ $$i -lt $$RES ]; then \
			printf "$(OK_COLOR)█$(NO_COLOR)"; \
		else \
			printf "$(COM_COLOR)▒$(NO_COLOR)"; \
		fi; \
		((i=$$i+1)); \
	done; \
	printf "$(OBJ_COLOR)]$(NO_COLOR)"; \
	printf " ($(COM_COLOR)$$FILE_DONE$(NO_COLOR)/$(COM_COLOR)$$FILE_TOTAL$(NO_COLOR))"; \
	printf " "; \
	((FILE_DONE=$$FILE_DONE+1)); \
	echo $$FILE_DONE/$$FILE_TOTAL > .files_changed;
endef

define display_progress_bar
	if [ $(NOVISU) -eq 0 ]; then \
		line=`bash -c 'oldstty=$$(stty -g); stty raw -echo min 0; tput u7 > /dev/tty; IFS=";" read -r -d R -a pos; stty $$oldstty; row=$$(($${pos[0]:2} - 1)); echo $$row'`; \
		max_line=`tput lines`; \
		((max_line=$$max_line-2));\
		new_line=0; \
		tput sc; \
		i=0; \
		while [ $$i -lt 60 ]; do \
			printf " "; \
			((i=$$i+1)); \
		done; \
		tput rc; \
		if [ $$line -gt $$max_line ]; then \
			new_line=1; \
			echo ; \
		else \
			((line=$$line+1));\
		fi; \
		tput sc; \
		tput cup $$line; \
		$(draw_bar) \
		if [ $$new_line -eq 1 ]; then \
			((line=$$line-1));\
			tput cup $$line; \
		else \
			tput rc; \
		fi; \
	fi
endef

################################################################################
#                                 Makefile rules                             #
################################################################################

all: header setup $(NAME)
	@rm -rf .files_changed

header:
		@printf "%b" "$(OBJ_COLOR)"
		@echo
		@echo
		@echo "    __  ___ _         _    _____  __           __ __"
		@echo "   /  |/  /(_)____   (_)  / ___/ / /_   ___   / // /"
		@echo "  / /|_/ // // __ \ / /   \__ \ / __ \ / _ \ / // / "
		@echo " / /  / // // / / // /   ___/ // / / //  __// // /  "
		@echo "/_/  /_//_//_/ /_//_/   /____//_/ /_/ \___//_//_/   "
		@echo "                                                    "

	@printf "%b" "$(OBJ_COLOR)Name:	$(WARN_COLOR)$(NAME)\n"
	@printf "%b" "$(OBJ_COLOR)Author:	$(WARN_COLOR)$(AUTHOR)\n"
	@printf "%b" "$(OBJ_COLOR)Date: 	$(WARN_COLOR)$(DATE)\n\033[m"
	@printf "%b" "$(OBJ_COLOR)CC: 	$(WARN_COLOR)$(CC)\n\033[m"
	@printf "%b" "$(OBJ_COLOR)Flags: 	$(WARN_COLOR)$(CFLAGS)\n\033[m"
	@echo


-include $(DEPS) $(DEPS_MAIN)
$(NAME):	$(OBJS) $(OBJ_MAIN)
			@$(MAKE) -C Libft
			@$(call display_progress_bar)
			@$(call run_and_test,$(CC) $(CFLAGS) -I$(INCLUDE_PATH) $(LIB) -o $@ ${COMPIL} ${OBJS} ${OBJ_MAIN})
			@printf "$(WARN_COLOR)Project Ready :)\n"

setup:
	@$(call save_files_changed)

objs/%.o: 	$(SRCS_PATH)/%$(FILE_EXTENSION)
			@mkdir -p $(dir $@)
			@$(call display_progress_bar)
			@$(call run_and_test,$(CC) $(CFLAGS_WRL) -c $< -o $@ -I$(INCLUDE_PATH))

clean:		header
			@rm -rf objs objs_tests
			@$(MAKE_CLEAN) -C Libft
			@printf "%-53b%b" "$(ERROR_COLOR)clean:" "$(OK_COLOR)[✓]$(NO_COLOR)\n"

fclean:		header clean
			@rm -rf $(NAME)
			@$(MAKE_FCLEAN) -C Libft
			@printf "%-53b%b" "$(ERROR_COLOR)fclean:" "$(OK_COLOR)[✓]$(NO_COLOR)\n"

re:			fclean all

.PHONY:		all clean fclean re header
