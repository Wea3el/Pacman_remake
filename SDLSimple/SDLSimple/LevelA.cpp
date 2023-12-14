#include "LevelA.h"
#include "Utility.h"

#define LEVEL_WIDTH 25
#define LEVEL_HEIGHT 19

unsigned int LEVELA_DATA[] =
{
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 6, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 7, 6, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 7,
    0, 5, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 5, 5, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 5,
    0, 5, 0, 1, 2, 2, 3, 0, 1, 2, 2, 2,12,11, 2, 2, 2, 3, 0, 1, 2, 2, 3, 0, 5,
    0, 5, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 5,
    0, 5, 0, 6, 2, 2, 7, 0, 1, 2, 2, 2, 2, 2, 2, 2, 2, 3, 0, 6, 2, 2, 7, 0, 5,
    0, 5, 0, 11,2, 2,12, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 11,2, 2,12, 0, 5,
    0, 5, 0, 0, 0, 0, 0, 0, 6, 9, 2, 2, 2, 2, 2, 2, 9, 7, 0, 0, 0, 0, 0, 0, 5,
    0,11, 2, 2, 2, 2, 3, 0, 8,14, 0, 0, 0, 0, 0, 0, 8,14, 0, 1, 2, 2, 2, 2,12,
    0, 0, 0, 0, 0, 0, 0, 0, 8,14, 0, 0, 0, 0, 0, 0, 8,14, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,11,13, 2, 2, 2, 2, 2, 2,13,12, 0, 0, 0, 0, 0, 0, 0,
    0, 6, 2, 2, 2, 2, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 2, 2, 2, 2, 7,
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
    
    Mix_FreeChunk(m_state.monch_sfx1);
    
    Mix_FreeMusic(m_state.bgm);
}


void LevelA::initialise(int lives)
{

    m_state.next_scene_id = -1;
    
    GLuint map_texture_id = Utility::load_texture("assets/tilesset.png");
    m_state.map = new Map(LEVEL_WIDTH, LEVEL_HEIGHT, LEVELA_DATA, map_texture_id, 1, 5, 3);
    
    // Code from main.cpp's initialise()
    /**
     George's Stuff
     */
    
    // Existing
    m_state.player = new Entity();
    m_state.player->set_entity_type(PLAYER);
    m_state.player->set_position(glm::vec3(12.0f, -11.0f, 0.0f));
    m_state.player->set_movement(glm::vec3(0.0f));
    m_state.player->set_speed(10.0f);
    
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
    
    
    
    /**
     Enemies' stuff */
    GLuint bliky_texture = Utility::load_texture("assets/blinky.png");
    GLuint pinky_texture = Utility::load_texture("assets/pinky.png");
    GLuint clyde_texture = Utility::load_texture("assets/clyde.png");
    GLuint inky_texture = Utility::load_texture("assets/inky.png");
    GLuint dot_texture = Utility::load_texture("assets/dot.png");
    GLuint power_texture = Utility::load_texture("assets/powerup.png");
    GLuint ghost_texture = Utility::load_texture("assets/ghostDie.png");
    if(lives == 3){
        m_state.enemies = new Entity[189];
        
    }
   
   
    ENEMY_COUNT = 4;

    cur = 0;
    dot_count = 0;
    //top_right accross
    for(int i = 0; i < 10; i++){
        m_state.enemies[i+cur].m_texture_id = dot_texture;
        m_state.enemies[i+cur].set_ai_type(DOT);
        m_state.enemies[i+cur].set_position(glm::vec3(i+2, -2, 0.0f));
        dot_count++;
    }
    m_state.enemies[cur].set_ai_type(POWERUP);
    m_state.enemies[cur].m_texture_id = power_texture;
    
    cur += dot_count;
    dot_count = 0;
    //top left accross
    for(int i = 0; i < 10; i++){
        m_state.enemies[i+cur].m_texture_id = dot_texture;
        m_state.enemies[i+cur].set_ai_type(DOT);
        m_state.enemies[i+cur].set_position(glm::vec3(i+14, -2, 0.0f));
        dot_count++;
    }
    
    
    
    cur += dot_count;
    dot_count = 0;
    
    for(int i = 0; i < 5; i++){
        m_state.enemies[i+cur].m_texture_id = dot_texture;
        m_state.enemies[i+cur].set_ai_type(DOT);
        m_state.enemies[i+cur].set_position(glm::vec3(2, -3-i, 0.0f));
        dot_count++;
    }
    cur += dot_count;
    dot_count = 0;
    
    for(int i = 0; i < 13; i++){
        m_state.enemies[i+cur].m_texture_id = dot_texture;
        m_state.enemies[i+cur].set_ai_type(DOT);
        m_state.enemies[i+cur].set_position(glm::vec3(7, -3-i, 0.0f));
        dot_count++;
    }
    cur += dot_count;
    dot_count = 0;
    
    for(int i = 0; i < 21; i++){
        m_state.enemies[i+cur].m_texture_id = dot_texture;
        m_state.enemies[i+cur].set_ai_type(DOT);
        m_state.enemies[i+cur].set_position(glm::vec3(3+i, -4, 0.0f));
        dot_count++;
    }
    cur += dot_count;
    dot_count = 0;

    
    for(int i = 0; i < 4; i++){
        m_state.enemies[i+cur].m_texture_id = dot_texture;
        m_state.enemies[i+cur].set_ai_type(DOT);
        m_state.enemies[i+cur].set_position(glm::vec3(3+i, -7, 0.0f));
        dot_count++;
    }
    cur += dot_count;
    dot_count = 0;
    
    for(int i = 0; i < 11; i++){
        m_state.enemies[i+cur].m_texture_id = dot_texture;
        m_state.enemies[i+cur].set_ai_type(DOT);
        m_state.enemies[i+cur].set_position(glm::vec3(8+i, -6, 0.0f));
        dot_count++;
    }
    cur += dot_count;
    dot_count = 0;

    
    
    //bottom line
    for(int i = 0; i < 22; i++){
        m_state.enemies[i+cur].m_texture_id = dot_texture;
        m_state.enemies[i+cur].set_ai_type(DOT);
        m_state.enemies[i+cur].set_position(glm::vec3(2+i, -17, 0.0f));
        dot_count++;
    }
    
    m_state.enemies[cur].set_ai_type(POWERUP);
    m_state.enemies[cur].m_texture_id = power_texture;
    
 
    cur += dot_count;
    dot_count = 0;
    
    for(int i = 0; i < 6; i++){
        m_state.enemies[i+cur].m_texture_id = dot_texture;
        m_state.enemies[i+cur].set_ai_type(DOT);
        m_state.enemies[i+cur].set_position(glm::vec3(2+i, -15, 0.0f));
        dot_count++;
    }
    cur += dot_count;
    dot_count = 0;
    
    for(int i = 0; i < 6; i++){
        m_state.enemies[i+cur].m_texture_id = dot_texture;
        m_state.enemies[i+cur].set_ai_type(DOT);
        m_state.enemies[i+cur].set_position(glm::vec3(10+i, -15, 0.0f));
        dot_count++;
    }
    cur += dot_count;
    dot_count = 0;
    
    for(int i = 0; i < 6; i++){
        m_state.enemies[i+cur].m_texture_id = dot_texture;
        m_state.enemies[i+cur].set_ai_type(DOT);
        m_state.enemies[i+cur].set_position(glm::vec3(18+i, -15, 0.0f));
        dot_count++;
    }
    cur += dot_count;
    dot_count = 0;
    
    for(int i = 0; i < 6; i++){
        m_state.enemies[i+cur].m_texture_id = dot_texture;
        m_state.enemies[i+cur].set_ai_type(DOT);
        m_state.enemies[i+cur].set_position(glm::vec3(2, -17+i, 0.0f));
        dot_count++;
    }
    cur += dot_count;
    dot_count = 0;
    
    for(int i = 0; i < 6; i++){
        m_state.enemies[i+cur].m_texture_id = dot_texture;
        m_state.enemies[i+cur].set_ai_type(DOT);
        m_state.enemies[i+cur].set_position(glm::vec3(23, -17+i, 0.0f));
        dot_count++;
    }
   
    cur += dot_count;
    dot_count = 0;
    
    for(int i = 0; i < 6; i++){
        m_state.enemies[i+cur].m_texture_id = dot_texture;
        m_state.enemies[i+cur].set_ai_type(DOT);
        m_state.enemies[i+cur].set_position(glm::vec3(23-i, -12, 0.0f));
        dot_count++;
    }
    m_state.enemies[cur].set_ai_type(POWERUP);
    m_state.enemies[cur].m_texture_id = power_texture;
    
    cur += dot_count;
    dot_count = 0;
    
    for(int i = 0; i < 6; i++){
        m_state.enemies[i+cur].m_texture_id = dot_texture;
        m_state.enemies[i+cur].set_ai_type(DOT);
        m_state.enemies[i+cur].set_position(glm::vec3(2+i, -12, 0.0f));
        dot_count++;
    }
    
    m_state.enemies[cur].set_ai_type(POWERUP);
    m_state.enemies[cur].m_texture_id = power_texture;
    cur += dot_count;
    dot_count = 0;
    
    for(int i = 0; i < 5; i++){
        m_state.enemies[i+cur].m_texture_id = dot_texture;
        m_state.enemies[i+cur].set_ai_type(DOT);
        m_state.enemies[i+cur].set_position(glm::vec3(7+i, -13, 0.0f));
        dot_count++;
    }
    cur += dot_count;
    
    for(int i = 0; i < 5; i++){
        m_state.enemies[i+cur].m_texture_id = dot_texture;
        m_state.enemies[i+cur].set_ai_type(DOT);
        m_state.enemies[i+cur].set_position(glm::vec3(14+i, -13, 0.0f));
        dot_count++;
    }
    cur += dot_count;
    dot_count = 0;
    
    for(int i = 0; i < 2; i++){
        m_state.enemies[i+cur].m_texture_id = dot_texture;
        m_state.enemies[i+cur].set_ai_type(DOT);
        m_state.enemies[i+cur].set_position(glm::vec3(10+i, -14, 0.0f));
        dot_count++;
    }
    cur += dot_count;
    dot_count = 0;
    
    for(int i = 0; i < 2; i++){
        m_state.enemies[i+cur].m_texture_id = dot_texture;
        m_state.enemies[i+cur].set_ai_type(DOT);
        m_state.enemies[i+cur].set_position(glm::vec3(12+i, -16, 0.0f));
        dot_count++;
    }
    cur += dot_count;
    dot_count = 0;
    
    for(int i = 0; i < 2; i++){
        m_state.enemies[i+cur].m_texture_id = dot_texture;
        m_state.enemies[i+cur].set_ai_type(DOT);
        m_state.enemies[i+cur].set_position(glm::vec3(14+i, -14, 0.0f));
        dot_count++;
    }
    cur += dot_count;
    dot_count = 0;
    
    for(int i = 0; i < 14; i++){
        m_state.enemies[i+cur].m_texture_id = dot_texture;
        m_state.enemies[i+cur].set_ai_type(DOT);
        m_state.enemies[i+cur].set_position(glm::vec3(18, -2-i, 0.0f));
        dot_count++;
    }
    
    cur += dot_count;
    dot_count = 0;
    
    for(int i = 0; i < 6; i++){
        m_state.enemies[i+cur].m_texture_id = dot_texture;
        m_state.enemies[i+cur].set_ai_type(DOT);
        m_state.enemies[i+cur].set_position(glm::vec3(23, -2-i, 0.0f));
        dot_count++;
    }
    m_state.enemies[cur].set_ai_type(POWERUP);
    m_state.enemies[cur].m_texture_id = power_texture;
    cur += dot_count;
    dot_count = 0;
    
    for(int i = 0; i < 5; i++){
        m_state.enemies[i+cur].m_texture_id = dot_texture;
        m_state.enemies[i+cur].set_ai_type(DOT);
        m_state.enemies[i+cur].set_position(glm::vec3(19+i, -7, 0.0f));
        dot_count++;
    }
    cur += dot_count;
    dot_count = 0;
    
    ENEMY_COUNT += cur;
    for(int i = 4; i < ENEMY_COUNT; i++){
        
        m_state.enemies[i].set_width(0.6f);
        m_state.enemies[i].set_height(0.6f);
    }
    for(int i = cur; i < ENEMY_COUNT; i++){
        m_state.enemies[i].set_entity_type(ENEMY);
        m_state.enemies[i].set_ai_type(WALKER);
        m_state.enemies[i].set_ai_state(GO_LEFT);
        
        m_state.enemies[i].set_position(glm::vec3((ENEMY_COUNT-i)+10, -9.0f, 0.0f));
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
    m_state.enemies[cur].m_texture_id = clyde_texture;
    m_state.enemies[cur+1].m_texture_id = inky_texture;
    m_state.enemies[cur+2].m_texture_id = bliky_texture;
    m_state.enemies[cur+3].m_texture_id = pinky_texture;
    m_state.player->dot_count = cur-5;
    for(int i = 0; i < ENEMY_COUNT; i++){
        if(!m_state.enemies[i].is_active()){
            m_state.player->dot_count -=1;
        }
    }
    

    /**
     BGM and SFX
     */
    Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 4096);
    
    m_state.bgm = Mix_LoadMUS("assets/siren_1.wav");
    
    Mix_PlayMusic(m_state.bgm, -1);
    
    Mix_VolumeMusic(50.0f);
    
    m_state.bgm2 = Mix_LoadWAV("assets/power_pellet.wav");
    
    Mix_ResumeMusic();
    m_state.monch_sfx1 = Mix_LoadWAV("assets/munch.wav");
    
    
}

void LevelA::update(float delta_time)
{
    GLuint bliky_texture = Utility::load_texture("assets/blinky.png");
    GLuint pinky_texture = Utility::load_texture("assets/pinky.png");
    GLuint clyde_texture = Utility::load_texture("assets/clyde.png");
    GLuint inky_texture = Utility::load_texture("assets/inky.png");
    GLuint dot_texture = Utility::load_texture("assets/dot.png");
    GLuint ghost_texture = Utility::load_texture("assets/ghostDie.png");
    cur_time += delta_time;
    if(cur_time > 10){
        cur_time = 0;
        
        for(int i = cur; i < ENEMY_COUNT; i++){
          
            if(m_state.enemies[i].get_position().x> 10 && m_state.enemies[i].get_position().x <15 && m_state.enemies[i].get_position().y >-9.5&& m_state.enemies[i].get_position().y <-7){
                m_state.enemies[i].set_position(glm::vec3(12.0f,-6.0f,1.0f));
                break;
            }
        }
    }
    m_state.player->update(delta_time, m_state.player, m_state.enemies, ENEMY_COUNT, m_state.map);
    for (int i = 0; i < ENEMY_COUNT; i++) m_state.enemies[i].update(delta_time, m_state.player, NULL, 0, m_state.map);
    if (m_state.player->dot_count == 0){
        m_state.next_scene_id = 1;
    }
    if(m_state.player->die) m_state.next_scene_id = 3;
    if(m_state.player->eat){
        
            m_state.player->eat= false;
            Mix_PlayChannel(1, m_state.monch_sfx1, 0);
            Mix_Volume(1, 10);
        }
    if(m_state.player->power){
        m_state.player->powerup_time+=delta_time;
        Mix_PauseMusic();
        Mix_PlayChannel(2, m_state.bgm2, 0);
        Mix_Volume(2, 10);
        
        for(int i = cur; i < ENEMY_COUNT; i++){
            m_state.enemies[i].set_speed(0.5f);
            m_state.enemies[i].m_texture_id = ghost_texture;
            m_state.enemies[i].m_animation_cols   = 2;
        }
        if(m_state.player->powerup_time >10){
            m_state.player->power = false;
        }
    }else{
        Mix_HaltChannel(2);
        Mix_ResumeMusic();
        m_state.player->powerup_time =0;
        for(int i = cur; i < ENEMY_COUNT; i++){
            
            m_state.enemies[i].set_speed(2.0f);
            m_state.enemies[i].m_animation_cols   = 8;
        }
        m_state.enemies[cur].m_texture_id = clyde_texture;
        m_state.enemies[cur+1].m_texture_id = inky_texture;
        m_state.enemies[cur+2].m_texture_id = bliky_texture;
        m_state.enemies[cur+3].m_texture_id = pinky_texture;
        
    }
    
    if(m_state.player->get_position().x <0){
        m_state.player->set_position(glm::vec3(25.0f,m_state.player->get_position().y,1.0f));
    }
    if(m_state.player->get_position().x >25){
        m_state.player->set_position(glm::vec3(0.0f,m_state.player->get_position().y,1.0f));
    }
    
}

void LevelA::render(ShaderProgram *program)
{
    m_state.map->render(program);
    m_state.player->render(program);
    for (int i = 0; i < ENEMY_COUNT; i++){
        if(m_state.enemies[i].is_active()){
            m_state.enemies[i].render(program);
        }
            
    }
}
