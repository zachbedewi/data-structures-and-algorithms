# Competitive programming Makefile.
#
#   make          build sol (debug: libstdc++ assertions, overflow traps, LOCAL)
#   make run      build + run against in.txt
#   make r        same as `make run`
#   make fast     build with -O2, no debug flags (mirrors the judge)
#   make clean
#
# The nix devShell exports CPLUS_INCLUDE_PATH for clang-tidy, which makes g++
# pull in libc++ headers and fail. Keep it out of recipes.
unexport CPLUS_INCLUDE_PATH

CXX      := g++
SRC      := sol.cpp
BIN      := sol
IN       := in.txt

STD      := -std=c++23
WARN     := -Wall -Wextra -Wshadow -Wconversion
DEBUG    := -g -DLOCAL -D_GLIBCXX_DEBUG -D_GLIBCXX_DEBUG_PEDANTIC -D_GLIBCXX_ASSERTIONS -ftrapv -fstack-protector-all
RELEASE  := -O2

.PHONY: all run r fast clean
all: $(BIN)

$(BIN): $(SRC)
	$(CXX) $(STD) $(WARN) $(DEBUG) -o $@ $<

fast: $(SRC)
	$(CXX) $(STD) $(WARN) $(RELEASE) -o $(BIN) $<

run r: $(BIN)
	@./$(BIN) < $(IN)

clean:
	rm -rf $(BIN) $(BIN).dSYM
