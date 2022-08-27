BUILD_DIR=../build
OS=$(BUILD_DIR)/sus

CFLAGS+=-ffreestanding -nostdlib -gdwarf-4 -m32 -ggdb3

OS_SRCS := $(wildcard *.c)
OS_OBJS := $(patsubst %.c, $(OS)/%.o, $(OS_SRCS))
OS_OUT := $(patsubst %.o, %, $(OS_OBJS))

all: $(OS)

$(OS_OBJS): $(OS_SRCS)
	gcc $(CFLAGS) -c $< -o $@

$(OS): $(OS_OBJS)
	ld -m elf_i386 --nmagic -T sus.lds $(OS_OBJS) -o $(OS_OUT)

clean:
	rm $(OS)/*

