#ifndef PARTICLESYSTEM_HPP
#define PARTICLESYSTEM_HPP

#include <raylib.h>
#include <vector>

struct Particle {
    Vector2 position;
    Vector2 velocity;
    Color color;
    float size;
    float life;      // Current life in seconds
    float maxLife;   // Initial life span
};

class ParticleSystem {
public:
    ParticleSystem();

    void spawnLineClearParticles(int row, int colsCount, Color blockColor);
    void spawnHardDropParticles(int col, int row, Color blockColor);
    void update(float dt);
    void draw() const;

private:
    std::vector<Particle> particles;
};

#endif // PARTICLESYSTEM_HPP
