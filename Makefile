#==============================================================================
#	Default Setting
#==============================================================================
NAME		= 	ft_containers

SRC			=	main.cpp \

SRC_DIR		=
OBJ_DIR		=	object/
INC_DIR		=	containers/\
				include/ \
				include/meta_function/

INC			=	$(addprefix -I , $(INC_DIR))

OBJ			=	$(addprefix $(OBJ_DIR), $(SRC:.cpp=.o))

#==============================================================================
#	Compile Flags
#==============================================================================

RM			=	rm -f

CXX			=	c++
CXX_WARN_FLAGS	=	all extra error
CXX_STD_FLAGS	=	c++98
CXXFLAGS	+=	$(addprefix -W, $(CXX_WARN_FLAGS))
CXXFLAGS	+= -pedantic
CXXFLAGS	+=	$(addprefix -std=, $(CXX_STD_FLAGS))

DEBUG_FLAG	+=	LOG
DEBUG_FLAG	+=	DEBUG

FT_VERSION	=	03

ifdef FT_VERSION
	CXXFLAGS	+=	-D FT_VERSION=$(FT_VERSION)
endif

ifdef DEBUG_FLAG
	LOG	+=	$(addprefix -D , $(DEBUG_FLAG))
else
	LOG += -D NDEBUG
endif

DEBUG		=	-g
SNTZ		=	-fsanitize=address -fsanitize=undefined -fno-omit-frame-pointer
MEM			=	-fsanitize=memory -fsanitize-memory-track-origins \
				-fPIE -pie -fno-omit-frame-pointer
LEAK		=	-fsanitize=leak

#==============================================================================
#	Make Part
#==============================================================================
.PHONY		:	all clean fclean re
all			:	$(NAME)
clean		:	; $(RM) -r $(OBJ_DIR)
fclean		:	clean ; $(RM) $(NAME)
re			:
		make fclean
		make all -j 8

$(NAME)		:	$(OBJ);	$(CXX) $(CXXFLAGS) $^ -o $@
$(OBJ_DIR)	:	;	mkdir -p $(OBJ_DIR)
$(OBJ)		:	| $(OBJ_DIR)
$(OBJ_DIR)%.o:	$(SRC_DIR)%.cpp $(INC_DIR);	$(CXX) $(CXXFLAGS) $(INC) -o $@ -c $<

#==============================================================================
.PHONY		:	log sntz std
std			:	; make re CXXFLAGS="$(CXXFLAGS) -D STD"
log			:	; make re CXXFLAGS="$(CXXFLAGS) $(LOG)"
sntz		:	; make re CXXFLAGS="$(CXXFLAGS) $(DEBUG) $(SNTZ)"
