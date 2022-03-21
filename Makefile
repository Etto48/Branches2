CC 				:=	g++

#available modes: DEBUG, RELEASE
MODE			:=	DEBUG

GIT_BRANCH		:= 	$(shell git rev-parse --abbrev-ref HEAD)
GIT_COMMITN		:=	$(shell git rev-list --count $(GIT_BRANCH))

DEFINE_LIST		:=	$(MODE) VERSION=$(GIT_COMMITN)
CPPARGS			:=	-Wall -Wextra -pedantic $(addprefix -D, $(DEFINE_LIST)) -std=c++2a

ifeq ($(MODE),DEBUG)
	CPPARGS		+=	-g
else ifeq ($(MODE),RELEASE)
	CPPARGS		+=	-O3
endif

CPPFILES		:= 	$(shell find ./ -name "*.cpp")
OBJ				:=	$(patsubst %.cpp, %.o, $(CPPFILES))
HEADERS			:=	$(shell find ./ -name "*.hpp")
ALL_OBJ			:=	$(shell find ./ -name "*.o")
THIS			:=	./Makefile

PROJECT			:=	Branches

all: $(PROJECT)

$(PROJECT): $(OBJ)
	@echo Linking $@
	@$(CC) $(OBJ) -o $@ $(CARGS)

./%.o: ./%.cpp $(HEADERS) $(THIS)
	@echo Compiling $@
	@$(CC) -c $< -o $@ $(CPPARGS)

.PHONY: clean
clean:
	@echo Removing object files and executables
	@rm -f $(ALL_OBJ) $(PROJECT)
