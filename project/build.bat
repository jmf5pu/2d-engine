set render=src\engine\render\render.c src\engine\render\render_init.c src\engine\render\render_util.c
set io=src\engine\io\io.c
set config=src\engine\config\config.c
set input=src\engine\input\input.c
set time=src\engine\time\time.c
set physics=src\engine\physics\physics.c
set entity=src\engine\entity\entity.c
set animation=src\engine\animation\animation.c
set array_list=src\engine\array_list\array_list.c
set hash_map=src\engine\hash_map\hash_map.c
set game=src\collision_behavior.c src\player_helpers.c src\map_helpers.c src\weapon_types.c
set files=src\glad.c src\main.c src\engine\global.c %render% %io% %config% %input% %time% %physics% %entity% %animation% %array_list% %hash_map% %game%
set libs=..\lib\SDL2main.lib ..\lib\SDL2.lib

CL /Zi /I ..\include %files% /link %libs% /OUT:mygame.exe