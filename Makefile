# M-Boma Housing Project Makefile

CC = g++
CFLAGS = -std=c++11 -Wall -Wextra
INCLUDEDIR = src/include
SRCDIR = src
OBJDIR = obj
BINDIR = bin

# Source files
SOURCES = $(wildcard $(SRCDIR)/*.cpp)
OBJECTS = $(patsubst $(SRCDIR)/%.cpp,$(OBJDIR)/%.o,$(SOURCES))

# Target executable
TARGET = $(BINDIR)/mboma

# MySQL config flags
MYSQL_CFLAGS = $(shell mysql_config --cflags)
MYSQL_LIBS = $(shell mysql_config --libs)

# OpenSSL for password hashing
SSL_LIBS = -lssl -lcrypto

.PHONY: all clean directories

all: directories $(TARGET)

directories:
	mkdir -p $(OBJDIR)
	mkdir -p $(BINDIR)

$(OBJDIR)/%.o: $(SRCDIR)/%.cpp
	$(CC) $(CFLAGS) $(MYSQL_CFLAGS) -I$(INCLUDEDIR) -c $< -o $@

$(TARGET): $(OBJECTS)
	$(CC) $(OBJECTS) $(MYSQL_LIBS) $(SSL_LIBS) -o $@

clean:
	rm -rf $(OBJDIR) $(BINDIR)

run: all
	$(TARGET)
