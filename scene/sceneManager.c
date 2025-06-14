#include "sceneManager.h"
#include "menu.h"
#include "gamescene.h"
#include "pause.h"
#include "end.h"
#include "../global.h"

Scene *scene = NULL;
void create_scene(SceneType type)
{
    switch (type)
    {
    case Menu_L:
        scene = New_Menu(Menu_L);
        break;
    case GameScene_L:
        scene = New_GameScene(GameScene_L, selected_player1, selected_player2, selected_map);
        break;
    case End_L:
        scene = New_End(End_L);
        break;    
    case Pause_L:
        scene = New_Pause(Pause_L);
        break;
    default:
        break;
    }
}
