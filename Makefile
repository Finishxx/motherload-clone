CXX=g++
LD=g++
CXXFLAGS=-Wall -pedantic -g -std=c++17 -MMD
LDFLAGS= -DDEBUG
LIBS=-lSDL2 -lSDL2_ttf

OBJECTS=Pos.o RectColor.o RectID.o Config.o Input.o Parser.o Player.o Camera.o Graphics.o Map.o \
  Tile.o TileBedrock.o TileCoal.o TileDirt.o TileEmpty.o TileGold.o TileIron.o TileTitanium.o TileUndergroundEmpty.o\
	MapParser.o MapGenerator.o Shop.o ShopFuelHealth.o ShopUpgrade.o ShopHandler.o MiningHandler.o HUD.o MovementHandler.o GameSaver.o Game.o main.o

SRC_DIR=src
BUILD_DIR=build
BINARY=tomanma9
SAVES_DIR=saves
DOC_DIR=doc

.PHONY: all

compile: $(BINARY)

all: compile

doc:
	doxygen

#https://stackoverflow.com/questions/1814270/gcc-g-option-to-place-all-object-files-into-separate-directory
BUILD_OBJECTS=$(patsubst %.o, $(BUILD_DIR)/%.o,$(OBJECTS) )

$(BINARY): $(BUILD_OBJECTS)
	if [ ! -d $(SAVES_DIR) ] ; then mkdir $(SAVES_DIR); fi
	$(LD) -g -o $@ $^ $(LIBS)
#-fsanitize=address

#$< - select first prerequisite
#^ all prerequisites until you hit |
#@ target name

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp Makefile
	if [ ! -d $(BUILD_DIR) ] ; then mkdir $(BUILD_DIR); fi
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -dr $(BUILD_DIR) $(BINARY) $(DOC_DIR) $(SAVES_DIR)

.PHONY: clean

run:
	./$(BINARY)

# source: https://stackoverflow.com/questions/37669439/specify-makefile-command-target
git-ignore-create:
	touch .gitignore ;\
	echo '*.o' > .gitignore ;\

#source: https://newbedev.com/generate-dependencies-for-a-makefile-for-a-project-in-c-c
-include $(BUILD_OBJECTS:%.o=%.d)

#-include Makefile.d
