#include "jinping.h"

void JinPing_Load_Assets(Character *chara) {
    // Load animations
    const char *states[] = {"idle", "run", "attack", "hurt"};
    for (int i = 0; i < MAX_GIF; i++) {
        char path[64];
        snprintf(path, sizeof(path), "assets/jinping/%s.gif", states[i]);
        chara->gif_status[i] = algif_new_gif(path, -1);
    }

    // Load sounds
    const char *sound_files[MAX_SOUNDS] = {
        "attack_0.wav",
        "attack_1.wav",
        "attack_2.wav",
        "attack_3.wav"
    };

    for (int i = 0; i < MAX_SOUNDS; i++) {
        char sound_path[64];
        snprintf(sound_path, sizeof(sound_path), "assets/jinping/%s", sound_files[i]);

        ALLEGRO_SAMPLE *sample = al_load_sample(sound_path);
        if (sample) {
            chara->sounds[i] = al_create_sample_instance(sample);
            al_set_sample_instance_playmode(chara->sounds[i], ALLEGRO_PLAYMODE_ONCE);
            al_attach_sample_instance_to_mixer(chara->sounds[i], al_get_default_mixer());
        } else {
            chara->sounds[i] = NULL;
            fprintf(stderr, "Failed to load sound: %s\n", sound_path);
        }
    }
}
void JinPing_Attack(Elements *self) {
    if (!self || !self->pDerivedObj) return;
    Character *chara = (Character *)self->pDerivedObj;
    if (chara->new_proj) return;

    if (chara->atk_level < 100) _JinPing_Attack_0(self);
    else if (chara->atk_level >= 100 && chara->atk_level < 500) _JinPing_Attack_1(self);
    else if (chara->atk_level >= 500 && chara->atk_level < 2000) _JinPing_Attack_2(self);
}

void _JinPing_Attack_0(Elements *self) {
    // Character *chara = (Character *)self->pDerivedObj;

    // float angle_deg = chara->atk_angle;
    // float power = chara->atk_power;

    // int x = chara->x + chara->width / 2;
    // int y = chara->y + chara->height / 2;

    // if (!chara->dir) angle_deg = 180.0f - angle_deg;

    // Elements *proj = New_Projectile(Projectile_L, x, y, angle_deg, power);
    // _Register_elements(scene, proj);
    // chara->new_proj = true;

    // al_play_sample_instance(chara->sounds[SOUND_ATTACK_0]);
}

void _JinPing_Attack_1(Elements *self) {
    // Character *chara = (Character *)self->pDerivedObj;
    // chara->atk_angle = -45.0f;
    // chara->atk_power = 10.0f;

    // float angle_deg = chara->atk_angle;
    // float power = chara->atk_power;

    // int x = chara->x + chara->width / 2;
    // int y = chara->y + chara->height / 2;

    // if (!chara->dir) angle_deg = 180.0f - angle_deg;

    // Elements *proj_0 = New_Projectile(Projectile_L, x, y, angle_deg, power);
    // _Register_elements(scene, proj_0);
    // chara->new_proj = true;

    // al_play_sample_instance(chara->sounds[SOUND_ATTACK_1]);
}

void _JinPing_Attack_2(Elements *self) {
    // Character *chara = (Character *)self->pDerivedObj;
    // chara->atk_angle = -60.0f;
    // chara->atk_power = 12.0f;

    // float angle_deg = chara->atk_angle;
    // float power = chara->atk_power;

    // int x = chara->x + chara->width / 2;
    // int y = chara->y + chara->height / 2;

    // if (!chara->dir) angle_deg = 180.0f - angle_deg;

    // Elements *proj = New_Projectile(Projectile_L, x, y, angle_deg, power);
    // _Register_elements(scene, proj);
    // chara->new_proj = true;

    // al_play_sample_instance(chara->sounds[SOUND_ATTACK_2]);
}
