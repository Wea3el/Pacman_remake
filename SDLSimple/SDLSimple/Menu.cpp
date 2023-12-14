#include "Menu.h"
#include "Utility.h"


#define LEVEL2_WIDTH 20
#define LEVEL2_HEIGHT 8




unsigned int LEVEL_2_DATA[] =
{
    0,  0,  0, 0,   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0,  0,  0, 0,   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0,  0,  0, 0,   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0,  0,  0, 0,   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0,  0,  0, 0,   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0,  0,  0, 0,   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0,  0,  0, 0,   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0,  0,  0, 0,   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
};

Menu::~Menu()
{
    delete[] m_state.enemies;
    delete    m_state.player;
    delete    m_state.map;

    Mix_FreeMusic(m_state.bgm);
}

void Menu::initialise(int thing)
{
    GLuint map_texture_id = Utility::load_texture("assets/tilesset.png");
    m_state.map = new Map(LEVEL2_WIDTH, LEVEL2_HEIGHT, LEVEL_2_DATA, map_texture_id, 1.0f, 25, 24);
    m_state.next_scene_id = -1;

    m_state.player = new Entity();
    m_state.player->set_entity_type(PLAYER);
    m_state.player->set_position(glm::vec3(28, -7.0f, 0.0f));
    m_state.player->set_movement(glm::vec3(0.0f));
    m_state.player->set_speed(2.0f);
    
    m_state.player->m_texture_id = Utility::load_texture("assets/Pacman.png");
    
    // Walking
    m_state.player->m_walking[m_state.player->LEFT]  = new int[2] {2, 3};
    m_state.player->m_walking[m_state.player->RIGHT] = new int[2] {0, 1};
    m_state.player->m_walking[m_state.player->UP]    = new int[2] {4, 5};
    m_state.player->m_walking[m_state.player->DOWN]  = new int[2] {6, 7};

    m_state.player->m_animation_indices = m_state.player->m_walking[m_state.player->LEFT];  // start George looking left
    m_state.player->m_animation_frames = 2;
    m_state.player->m_animation_index  = 0;
    m_state.player->m_animation_time   = 0.0f;
    m_state.player->m_animation_cols   = 2;
    m_state.player->m_animation_rows   = 4;
    m_state.player->set_height(0.7f);
    m_state.player->set_width(0.7f);
    
    
    
    
    /**
     Enemies' stuff */
    GLuint bliky_texture = Utility::load_texture("assets/blinky.png");
    GLuint pinky_texture = Utility::load_texture("assets/pinky.png");
    GLuint clyde_texture = Utility::load_texture("assets/clyde.png");
    GLuint inky_texture = Utility::load_texture("assets/inky.png");
    
    
    m_state.enemies = new Entity[4];
    for(int i = 0; i < 4; i++){
        m_state.enemies[i].set_entity_type(ENEMY);
        m_state.enemies[i].set_ai_type(WALKER);
        m_state.enemies[i].set_ai_state(GO_LEFT);
        
        m_state.enemies[i].set_position(glm::vec3((i)+30, -7.0f, 0.0f));
        m_state.enemies[i].set_speed(2.0f);
        
        m_state.enemies[i].m_walking[Entity::LEFT]  = new int[2] {2, 3};
        m_state.enemies[i].m_walking[Entity::RIGHT] = new int[2] {0, 1};
        m_state.enemies[i].m_walking[Entity::UP]    = new int[2] {4, 5};
        m_state.enemies[i].m_walking[Entity::DOWN]  = new int[2] {6, 7};
        m_state.enemies[i].m_animation_indices = m_state.enemies[i].m_walking[Entity::LEFT];
        
        m_state.enemies[i].m_animation_frames = 2;
        m_state.enemies[i].m_animation_index  = 0;
        m_state.enemies[i].m_animation_time   = 0.0f;
        m_state.enemies[i].m_animation_cols   = 8;
        m_state.enemies[i].m_animation_rows   = 1;
        m_state.enemies[i].set_width(0.7f);
        m_state.enemies[i].set_height(0.7f);
        
    }
    m_state.enemies[0].m_texture_id = clyde_texture;
    m_state.enemies[1].m_texture_id = inky_texture;
    m_state.enemies[2].m_texture_id = bliky_texture;
    m_state.enemies[3].m_texture_id = pinky_texture;
    
    Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 4096);
    
    m_state.monch_sfx1 = Mix_LoadWAV("assets/pacman_beginning.wav");
    Mix_PlayChannel(1, m_state.monch_sfx1, 0);
    Mix_Volume(1, 10);
    }




void Menu::update(float delta_time)
{
    m_state.player->move_left();
    for (int i = 0; i < 4; i++) m_state.enemies[i].update(delta_time, m_state.player, NULL, 0, m_state.map);
    if (delta_time == -1) {
           m_state.next_scene_id = 0;
       }
    m_state.player->update(delta_time, m_state.player, m_state.enemies, 4, m_state.map);
          
    
}


void Menu::render(ShaderProgram *program)
{
    
    GLuint text_texture_id = Utility::load_texture("assets/font1.png");
    for (int i = 0; i < 4; i++){
        if(m_state.enemies[i].is_active()){
            m_state.enemies[i].render(program);
        }
    }
    m_state.player->render(program);
    Utility::draw_text(program, text_texture_id, "PACEMAN",  1.0f, -0.1f,glm::vec3(10.0f, -9.0f, 0.0f));
    Utility::draw_text(program, text_texture_id, "PRESS ENTER TO START",  1.0f, -0.1f,glm::vec3(4.0f, -12.0f, 0.0f));
   
}

