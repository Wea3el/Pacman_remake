#include "Scene.h"

class LevelA : public Scene {
public:
    int ENEMY_COUNT = 4;
    
    ~LevelA();
    
    int cur = 4;
    int dot_count;
    void initialise() override;
    void update(float delta_time) override;
    void render(ShaderProgram *program) override;
    
};
