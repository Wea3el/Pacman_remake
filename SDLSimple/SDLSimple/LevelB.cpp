#include "LevelB.h"
#include "Utility.h"


#define LEVEL_B_WIDTH 20
#define LEVEL_B_HEIGHT 8



unsigned int LEVEL_B_DATA[] =
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

LevelB::~LevelB()
{
    delete[] m_state.enemies;
    delete    m_state.player;
    delete    m_state.map;

    Mix_FreeMusic(m_state.bgm);
}

void LevelB::initialise(int thing)
{
    GLuint map_texture_id = Utility::load_texture("assets/tilesset.png");
    m_state.map = new Map(LEVEL_B_WIDTH, LEVEL_B_HEIGHT, LEVEL_B_DATA, map_texture_id, 1, 5, 3);
    lives = thing;
    
    
    
    // ————— GEORGE SET-UP ————— //
    // Existing
    m_state.next_scene_id = -1;
    
    
    
    // Code from main.cpp's initialise()
    /**
     George's Stuff
     */
    
    // Existing
    m_state.player = new Entity();
    m_state.player->set_entity_type(PLAYER);
    m_state.player->set_movement(glm::vec3(0.0f));
    m_state.player->set_speed(2.5f);
    m_state.player->set_position(glm::vec3(12.0f, -11.0f, 0.0f));
    m_state.player->m_texture_id = Utility::load_texture("assets/deadPacman.png");
    
    // Walking
    
    m_state.player->m_walking[m_state.player->RIGHT] = new int[12] {1, 2,3,4,5,6,7,8,9,10,11,12};
    m_state.player->m_walking[m_state.player->LEFT] = new int[1]{0};
    
    m_state.player->m_animation_indices = m_state.player->m_walking[m_state.player->RIGHT];  // start George looking left
    m_state.player->m_animation_frames = 11;
    m_state.player->m_animation_index  = 0;
    m_state.player->m_animation_time   = 0.0f;
    m_state.player->m_animation_cols   = 12;
    m_state.player->m_animation_rows   = 1;
    m_state.player->set_height(0.7f);
    m_state.player->set_width(0.7f);
    
    m_state.bgm = Mix_LoadMUS("assets/death_1.wav");
    
    Mix_PlayMusic(m_state.bgm, -1);
}

void LevelB::update(float delta_time)
{
    m_state.player->update(delta_time, m_state.player, NULL, 0, m_state.map);
    
    if(m_state.player->m_animation_index == 10){
        m_state.player->deactivate();
        if(lives == 0){
            Mix_PauseMusic();
            m_state.next_scene_id = 2;
        }else{
            std::cout << lives << std::endl;
            m_state.next_scene_id = 0;
        }
        
    }
    
   
   
        
    
}


void LevelB::render(ShaderProgram *program)
{
    GLuint text_texture_id = Utility::load_texture("assets/font1.png");
    m_state.player->render(program);
   
    
}
