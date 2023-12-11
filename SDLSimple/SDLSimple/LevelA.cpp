#include "LevelA.h"
#include "Utility.h"

#define LEVEL_WIDTH 25
#define LEVEL_HEIGHT 20

unsigned int LEVELA_DATA[] =
{
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 6, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 7, 6, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 7,
    0, 5, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 5, 5, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 5,
    0, 5, 0, 1, 2, 2, 3, 0, 1, 2, 2, 2,12,11, 2, 2, 2, 3, 0, 1, 2, 2, 3, 0, 5,
    0, 5, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 5,
    0, 5, 0, 6, 2, 2, 7, 0, 1, 2, 2, 2, 2, 2, 2, 2, 2, 3, 0, 6, 2, 2, 7, 0, 5,
    0, 5, 0, 11,2, 2,12, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 11,2, 2,12, 0, 5,
    0, 5, 0, 0, 0, 0, 0, 0, 6, 9, 2, 2, 0, 0, 2, 2, 9, 7, 0, 0, 0, 0, 0, 0, 5,
    0,11, 2, 2, 2, 2, 3, 0, 8,14, 0, 0, 0, 0, 0, 0, 8,14, 0, 1, 2, 2, 2, 2, 7,
    0, 0, 0, 0, 0, 0, 0, 0, 8,14, 0, 0, 0, 0, 0, 0, 8,14, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,11,13, 2, 2, 2, 2, 2, 2,13,12, 0, 0, 0, 0, 0, 0, 0,
    0, 6, 2, 2, 2, 2, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 2, 2, 2, 2,12,
    0, 5, 0, 0, 0, 0, 0, 0, 1, 2, 2, 2, 9, 9, 2, 2, 2, 3, 0, 0, 0, 0, 0, 0, 5,
    0, 5, 0, 6, 2, 2, 7, 0, 0, 0, 0, 0, 8,14, 0, 0, 0, 0, 0, 6, 2, 2, 7, 0, 5,
    0, 5, 0, 11,2, 2,12, 0, 6, 7, 0, 0,11,12, 0, 0, 6, 7, 0,11, 2, 2,12,0, 5,
    0, 5, 0, 0, 0, 0, 0, 0, 8,14, 0, 0, 0, 0, 0, 0, 8,14, 0, 0, 0, 0, 0, 0, 5,
    0, 5, 0, 1, 2, 2, 2, 2,13,13, 2, 3, 0, 0, 1, 2,13,13, 2, 2, 2, 2, 3, 0, 5,
    0, 5, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 5,
    0, 11,2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 12,
};



LevelA::~LevelA()
{
    delete [] m_state.enemies;
    delete    m_state.player;
    delete    m_state.map;
    Mix_FreeChunk(m_state.jump_sfx);
    Mix_FreeMusic(m_state.bgm);
}


void LevelA::initialise()
{

    m_state.next_scene_id = -1;
    
    GLuint map_texture_id = Utility::load_texture("assets/tilesset.png");
    m_state.map = new Map(LEVEL_WIDTH, LEVEL_HEIGHT, LEVELA_DATA, map_texture_id, 0.4, 5, 3);
    
    // Code from main.cpp's initialise()
    /**
     George's Stuff
     */
    // Existing
    m_state.player = new Entity();
    m_state.player->set_entity_type(PLAYER);
    m_state.player->set_position(glm::vec3(4.0f, -4.0f, 0.0f));
    m_state.player->set_movement(glm::vec3(0.0f));
    m_state.player->set_speed(2.5f);
    m_state.player->set_acceleration(glm::vec3(0.0f, -9.81f, 0.0f));
    m_state.player->m_texture_id = Utility::load_texture("assets/Pacman.png");
    
    // Walking
    m_state.player->m_walking[m_state.player->LEFT]  = new int[2] { 2, 3};
    m_state.player->m_walking[m_state.player->RIGHT] = new int[2] { 0, 1};
    m_state.player->m_walking[m_state.player->UP]    = new int[2] { 4, 5};
    m_state.player->m_walking[m_state.player->DOWN]  = new int[2] { 6, 7};

    m_state.player->m_animation_indices = m_state.player->m_walking[m_state.player->RIGHT];  // start George looking left
    m_state.player->m_animation_frames = 2;
    m_state.player->m_animation_index  = 0;
    m_state.player->m_animation_time   = 0.0f;
    m_state.player->m_animation_cols   = 2;
    m_state.player->m_animation_rows   = 4;
    m_state.player->set_height(0.3f);
    m_state.player->set_width(0.3f);
    
    
    
    /**
     Enemies' stuff */
    GLuint bliky_texture = Utility::load_texture("assets/blinky.png");
    GLuint pinky_texture = Utility::load_texture("assets/pinky.png");
    GLuint clyde_texture = Utility::load_texture("assets/clyde.png");
    GLuint inky_texture = Utility::load_texture("assets/inky.png");
    GLuint dot_texture = Utility::load_texture("assets/dot.png");
    
    m_state.enemies = new Entity[200];
    for(int i = 0; i < ENEMY_COUNT; i++){
        m_state.enemies[i].set_entity_type(ENEMY);
        m_state.enemies[i].set_ai_type(WALKER);
        m_state.enemies[i].set_ai_state(GO_LEFT);
        
        m_state.enemies[i].set_position(glm::vec3(i+6, -4.0f, 0.0f));
        m_state.enemies[i].set_speed(1.0f);
        
        m_state.enemies[i].m_walking[m_state.enemies[i].LEFT]  = new int[2] { 2, 3};
        m_state.enemies[i].m_walking[Entity::RIGHT] = new int[2] { 0, 1};
        m_state.enemies[i].m_walking[Entity::UP]    = new int[2] { 4, 5};
        m_state.enemies[i].m_walking[Entity::DOWN]  = new int[2] { 6, 7};
        m_state.enemies[i].m_animation_indices = m_state.enemies[i].m_walking[Entity::LEFT];
        
        m_state.enemies[i].m_animation_frames = 2;
        m_state.enemies[i].m_animation_index  = 0;
        m_state.enemies[i].m_animation_time   = 0.0f;
        m_state.enemies[i].m_animation_cols   = 8;
        m_state.enemies[i].m_animation_rows   = 1;
        m_state.enemies[i].set_width(0.3);
        m_state.enemies[i].set_height(0.3);
    }
    m_state.enemies[0].m_texture_id = clyde_texture;
    m_state.enemies[1].m_texture_id = inky_texture;
    m_state.enemies[2].m_texture_id = bliky_texture;
    m_state.enemies[3].m_texture_id = pinky_texture;
   
    ENEMY_COUNT = 4;

    //top_right
    for(int i = 0; i < 10; i++){
        m_state.enemies[i+cur].m_texture_id = dot_texture;
        m_state.enemies[i+cur].set_ai_type(DOT);
        m_state.enemies[i+cur].set_position(glm::vec3(i*0.4+0.80, -.75f, 0.0f));
        dot_count++;
    }
    cur += dot_count;
    
    
    for(int i = 0; i < 6; i++){
        m_state.enemies[i+cur].m_texture_id = dot_texture;
        m_state.enemies[i+cur].set_ai_type(DOT);
        m_state.enemies[i+cur].set_position(glm::vec3(0.80, -.75f-i*0.4, 0.0f));
        dot_count++;
    }
    cur += dot_count;
    for(int i = 0; i < 21; i++){
        m_state.enemies[i+cur].m_texture_id = dot_texture;
        m_state.enemies[i+cur].set_ai_type(DOT);
        m_state.enemies[i+cur].set_position(glm::vec3(1.3 +i*0.4, -1.55, 0.0f));
        dot_count++;
    }
    cur += dot_count;
    
    for(int i = 0; i < 10; i++){
        m_state.enemies[i+cur].m_texture_id = dot_texture;
        m_state.enemies[i+cur].set_ai_type(DOT);
        m_state.enemies[i+cur].set_position(glm::vec3(i*0.4+5.7, -.75f, 0.0f));
        dot_count++;
    }
    cur += dot_count;
    for(int i = 0; i < 6; i++){
        m_state.enemies[i+cur].m_texture_id = dot_texture;
        m_state.enemies[i+cur].set_ai_type(DOT);
        m_state.enemies[i+cur].set_position(glm::vec3(9.2, -.75f-i*0.4, 0.0f));
        dot_count++;
    }
    cur += dot_count;
    ENEMY_COUNT += cur;
    for(int i = 4; i < ENEMY_COUNT; i++){
        
        m_state.enemies[i].set_width(0.3);
        m_state.enemies[i].set_height(0.3);
    }
    m_state.player->dot_count = dot_count;


    
    
    
    
    /**
     BGM and SFX
     */
    Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 4096);
    
    m_state.bgm = Mix_LoadMUS("assets/dooblydoo.mp3");
    Mix_PlayMusic(m_state.bgm, -1);
    Mix_VolumeMusic(0.0f);
    
    m_state.jump_sfx = Mix_LoadWAV("assets/bounce.wav");
}

void LevelA::update(float delta_time)
{
    std::cout << cur << "hello"<<std::endl;
    m_state.player->update(delta_time, m_state.player, m_state.enemies, ENEMY_COUNT, m_state.map);
    std::cout << m_state.player->get_position().x << " " <<m_state.player->get_position().y << std::endl;
    for (int i = 0; i < ENEMY_COUNT; i++) m_state.enemies[i].update(delta_time, m_state.player, NULL, 0, m_state.map);
    if (m_state.player->dot_count == 0) m_state.next_scene_id = 1;
}

void LevelA::render(ShaderProgram *program)
{
    m_state.map->render(program);
    m_state.player->render(program);
    for (int i = 0; i < ENEMY_COUNT; i++){
            m_state.enemies[i].render(program);
        }
}
