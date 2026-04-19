TARGET ?= desktop 

SRCDIR := src
BUILDDIR := build
LIBDIR := lib
INCLUDEDIR := src
LIB_INCLUDEDIRS := $(shell find $(LIBDIR) -type d)
INCFLAGS := $(addprefix -I,$(OTHER_INCLUDEDIRS)) $(addprefix -I,$(INCLUDEDIR)) $(addprefix -I,$(LIB_INCLUDEDIRS)) -I/home/gw/data/libraries/include

ifeq ($(TARGET), web)
	CC = emcc
	OUT = build/bin/web/app.js
	CFLAGS = -D__EMSCRIPTEN__ -s USE_GLFW=3 -s FULL_ES2=1 -s WASM=1 -O2 -s ASSERTIONS=1 -s DEMANGLE_SUPPORT=0 -s ALLOW_MEMORY_GROWTH=1 -s USE_WEBGL2=1 -s MODULARIZE=1 -s EXPORT_NAME='createAppModuleSnake' -L./$(BUILDDIR)/lib -L/home/gw/data/libraries/lib
	SOURCES := lib/src/glad.c $(shell find $(SRCDIR) -name "*.cpp")
else
	CC = g++
	OUT = build/bin/desktop/app
	SOURCES := $(shell find $(SRCDIR) -name "*.cpp")
	OBJECTS := $(patsubst $(SRCDIR)/%, $(BUILDDIR)/%, $(SOURCES:.cpp=.o))
	OTHER_INCLUDEDIRS := $(shell find $(SRCDIR) -type d)
	CFLAGS := -L./$(BUILDDIR)/lib -L/home/gw/data/libraries/lib
	LIB := -lm -lglfw3 $(BUILDDIR)/lib/glad.a -ldl -lgsl -lgslcblas -lglmc
endif

# all: web desktop

web:
	$(info building for web target)
	@mkdir -p $(dir $(OUT))
	$(CC) $(SOURCES) $(INCFLAGS) $(CFLAGS) $^ -o $(OUT) $(LIB) --preload-file shaders@/shaders

desktop: glad $(OBJECTS)
	$(info building for deskop target)
	@mkdir -p $(dir $(OUT))
	cp -r shaders $(dir $(OUT))
	$(CC) $(INCFLAGS) $(SOURCES) $(CFLAGS) $(LIB) -o $(OUT)

glad:
	@mkdir -p $(BUILDDIR)/lib
	$(CC) $(INCFLAGS) $(CFLAGS) -c $(LIBDIR)/src/glad.c -o $(BUILDDIR)/lib/glad.o
	@ar rcs $(BUILDDIR)/lib/glad.a $(BUILDDIR)/lib/glad.o

$(BUILDDIR)/%.o: $(SRCDIR)/%.cpp
	@mkdir -p $(dir $@)
	$(CC) $(INCFLAGS) $(CFLAGS) -c $< -o $@

clean:
	$(RM) -r $(BUILDDIR)

.PHONY: clean


