EXE = finalProj
TEST = test

# Add all object files needed for compiling:
EXE_OBJ = main.o
OBJS = Graph.o main.o finalProj.o readFromFile.o

# Generated files
CLEAN_RM = images/Out.png

# Use the cs225 makefile template:
include cs225/make/cs225.mk