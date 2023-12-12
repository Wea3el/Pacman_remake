
#include "Lose.h"
#include "Utility.h"


#define LOSE_WIDTH 20
#define LOSE_HEIGHT 8



unsigned int LOSE_DATA[] =
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

Lose::~Lose()
{
    delete[] m_state.enemies;
    delete    m_state.player;
    delete    m_state.map;

    Mix_FreeMusic(m_state.bgm);
}

void Lose::initialise()
{
    

    

    
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
    m_state.player->set_position(glm::vec3(12.0f, -10.0f, 0.0f));
    m_state.player->set_movement(glm::vec3(0.0f));
    m_state.player->set_speed(2.5f);
    m_state.player->set_acceleration(glm::vec3(0.0f, -9.81f, 0.0f));
    m_state.player->m_texture_id = Utility::load_texture("assets/Pacman.png");
    
    // Walking
    m_state.player->m_walking[m_state.player->LEFT]  = new int[2] {2, 3};
    m_state.player->m_walking[m_state.player->RIGHT] = new int[2] {0, 1};
    m_state.player->m_walking[m_state.player->UP]    = new int[2] {4, 5};
    m_state.player->m_walking[m_state.player->DOWN]  = new int[2] {6, 7};

    m_state.player->m_animation_indices = m_state.player->m_walking[m_state.player->RIGHT];  // start George looking left
    m_state.player->m_animation_frames = 2;
    m_state.player->m_animation_index  = 0;
    m_state.player->m_animation_time   = 0.0f;
    m_state.player->m_animation_cols   = 2;
    m_state.player->m_animation_rows   = 4;
    m_state.player->set_height(0.7f);
    m_state.player->set_width(0.7f);
    

    }


void Lose::update(float delta_time)
{
    
    
        
    
}


void Lose::render(ShaderProgram *program)
{
    
    GLuint text_texture_id = Utility::load_texture("assets/font1.png");
    Utility::draw_text(program, text_texture_id, "YOU LOSE L ", 1.0f, -0.1f,glm::vec3(10.0f, -10.0f, 0.0f));
   
}

