#include "jinping.h"
#include "../projectiles/crown.h"
#include "../projectiles/winnie.h"
#include "../projectiles/tank.h"

void JinPing_Load_Assets(Character *chara) {
    // Load animations
    const char *states[] = {"idle", "run", "attack", "hurt"};
    for (int i = 0; i < MAX_GIF; i++) {
        char path[64];
        snprintf(path, sizeof(path), "assets/characters/jin_ping/%s.gif", states[i]);
        chara->gif_status[i] = algif_new_gif(path, -1);
    }

    // Load sounds
    const char *sound_files[MAX_SOUNDS] = {
        "attack_0.wav",
        "attack_1.wav",
        "attack_2.wav",
        "attack_3.wav",
        "charging.mp3",
        "hurt.mp3",
        "death.mp3",
    };

    for (int i = 0; i < MAX_SOUNDS; i++) {
        char sound_path[64];
        snprintf(sound_path, sizeof(sound_path), "assets/characters/jin_ping/%s", sound_files[i]);

        ALLEGRO_SAMPLE *sample = al_load_sample(sound_path);
        if (sample) {
            chara->sounds[i] = al_create_sample_instance(sample);
            al_set_sample_instance_playmode(chara->sounds[i], ALLEGRO_PLAYMODE_ONCE);
            al_attach_sample_instance_to_mixer(chara->sounds[i], al_get_default_mixer());
            al_set_sample_instance_gain(chara->sounds[i], 0.2);
        } else {
            chara->sounds[i] = NULL;
            fprintf(stderr, "Failed to load sound: %s\n", sound_path);
        }
    }
}
void JinPing_Attack(Elements *self) {
    Character *chara = (Character *)self->pDerivedObj;
    if (chara->new_proj) return;
    
    if (chara->atk_level < 1000) _JinPing_Attack_0(self);
    else if (chara->atk_level >= 1000 && chara->atk_level < 5000) _JinPing_Attack_1(self);
    else _JinPing_Attack_2(self);
}

void _JinPing_Attack_0(Elements *self) {
    Character *chara = (Character *)self->pDerivedObj;

    float angle_deg = chara->atk_angle;
    float power = chara->atk_power;

    int x = chara->x + chara->width / 2 - CROWN_WIDTH / 2;
    int y = chara->y + chara->height / 2 - CROWN_HEIGHT / 2;

    if (!chara->dir) angle_deg = 180.0f - angle_deg;
    
    Elements *proj = New_Projectile(Projectile_L, x, y - 16, angle_deg, power, CROWN, chara->player);
    _Register_elements(scene, proj);
    chara->new_proj = true;

    al_play_sample_instance(chara->sounds[SOUND_ATTACK_0]);
}

void _JinPing_Attack_1(Elements *self) {
    Character *chara = (Character *)self->pDerivedObj;

    float angle_deg = chara->atk_angle;
    float power = chara->atk_power;

    int x = chara->x + chara->width / 2 - WINNIE_WIDTH / 2;
    int y = chara->y + chara->height / 2 - WINNIE_HEIGHT / 2;

    if (!chara->dir) angle_deg = 180.0f - angle_deg;

    Elements *proj_0 = New_Projectile(Projectile_L, x, y - 16, angle_deg +  0, power, WINNIE, chara->player);
    Elements *proj_1 = New_Projectile(Projectile_L, x, y - 16, angle_deg + 10, power, WINNIE, chara->player);
    Elements *proj_2 = New_Projectile(Projectile_L, x, y - 16, angle_deg - 10, power, WINNIE, chara->player);
    _Register_elements(scene, proj_0);
    _Register_elements(scene, proj_1);
    _Register_elements(scene, proj_2);

    chara->new_proj = true;

    al_play_sample_instance(chara->sounds[SOUND_ATTACK_1]);
}

void _JinPing_Attack_2(Elements *self) {
    Character *chara = (Character *)self->pDerivedObj;

    float angle_deg = chara->atk_angle;
    float power = chara->atk_power;

    int x = chara->x + chara->width / 2 - TANK_WIDTH / 2;
    int y = chara->y + chara->height / 2 - TANK_HEIGHT / 2;

    if (!chara->dir) angle_deg = 180.0f - angle_deg;

    Elements *proj = New_Projectile(Projectile_L, x, y - 16, angle_deg, power, TANK, chara->player);
    _Register_elements(scene, proj);

    chara->new_proj = true;

    al_play_sample_instance(chara->sounds[SOUND_ATTACK_2]);
}
