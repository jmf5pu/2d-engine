# file paths
ANIMATION = src\engine\animation\animation.c
AUDIO = src\engine\audio\audio.c
RENDER = src\engine\render\render.c src\engine\render\render_init.c src\engine\render\render_util.c
IO = src\engine\io\io.c
CONFIG = src\engine\config\config.c
INPUT = src\engine\input\keyboard_input.c src\engine\input\controller_input.c
TIME = src\engine\time\time.c
PHYSICS = src\engine\physics\physics.c
ENTITY = src\engine\entity\entity.c
CAMERA = src\engine\camera\camera.c
ARRAY_LIST = src\engine\array_list\array_list.c
HASH_MAP = src\engine\hash_map\hash_map.c
GAME = src\player_helpers\player_anims.c src\effects\effects.c src\collision_behavior\collision_behavior.c src\player_helpers\player_helpers.c src\player_helpers\player_input.c src\player_helpers\player_movement.c src\enemy_helpers\enemy_helpers.c src\enemy_helpers\enemy_anims.c src\map_helpers\map_helpers.c src\map_helpers\dynamic_prop_logic.c src\map_helpers\spawning_logic.c src\weapon_types\weapon_types.c src\hud\hud.c src\menu_helpers\menu_helpers.c src\main_helpers\main_helpers.c
FILES = src\glad.c src\main.c src\engine\global.c $(RENDER) $(IO) $(CONFIG) $(INPUT) $(TIME) $(PHYSICS) $(ENTITY) $(ANIMATION) $(AUDIO) $(CAMERA) $(ARRAY_LIST) $(HASH_MAP) $(GAME)
LIBS = ..\lib\SDL2main.lib ..\lib\SDL2.lib ..\lib\SDL2_mixer.lib

# compiler and flags
CC = CL
CFLAGS = /Zi /I

all: clean build run

prep: clean format

clean:
	rm -f *.ilk *.obj *.pdb *.exe mygame.lib mygame.exp

build:
	$(CC) $(CFLAGS) ..\include $(FILES) /link $(LIBS) /OUT:mygame.exe

build-sanitize: CFLAGS = /fsanitize=address /Zi /I
build-sanitize: build

run:
	mygame.exe

format:
	#$(foreach file,$(wildcard src/**/*.h src/**/*.c src/**/*.cpp),clang-format -style=file -i $(file);)
	find src/ -iname *.h -o -iname *.c -o -iname *.cpp | xargs clang-format -style=file -i
	