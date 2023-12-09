
#include "Scene.h"

class Lose : public Scene {
public:
    // ————— STATIC ATTRIBUTES ————— //
    
    // ————— CONSTRUCTOR ————— //
    ~Lose();
    
    // ————— METHODS ————— //
    void initialise() override;
    void update(float delta_time) override;
    void render(ShaderProgram *program) override;
};

