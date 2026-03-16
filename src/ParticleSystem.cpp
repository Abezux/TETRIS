#include "ParticleSystem.hpp"
#include "Common.hpp"
#include <cstdlib>
#include <cmath>

ParticleSystem::ParticleSystem() {}

static float GetRandomFloat(float min, float max) {
    return min + static_cast<float>(rand()) / (static_cast<float>(RAND_MAX / (max - min)));
}

void ParticleSystem::spawnLineClearParticles(int row, int colsCount, Color blockColor) {
    int startY = BOARD_OFFSET_Y + row * CELL_SIZE + CELL_SIZE / 2;

    for (int c = 0; c < colsCount; ++c) {
        int startX = BOARD_OFFSET_X + c * CELL_SIZE + CELL_SIZE / 2;

        for (int i = 0; i < 6; ++i) {
            Particle p;
            p.position = Vector2{ (float)startX, (float)startY };
            float angle = GetRandomFloat(0.0f, 6.28318f);
            float speed = GetRandomFloat(60.0f, 220.0f);
            p.velocity = Vector2{ cosf(angle) * speed, sinf(angle) * speed };
            p.color = blockColor;
            p.size = GetRandomFloat(3.0f, 7.0f);
            p.maxLife = GetRandomFloat(0.4f, 0.8f);
            p.life = p.maxLife;

            particles.push_back(p);
        }
    }
}

void ParticleSystem::spawnHardDropParticles(int col, int row, Color blockColor) {
    int startX = BOARD_OFFSET_X + col * CELL_SIZE + CELL_SIZE / 2;
    int startY = BOARD_OFFSET_Y + row * CELL_SIZE + CELL_SIZE;

    for (int i = 0; i < 10; ++i) {
        Particle p;
        p.position = Vector2{ (float)startX, (float)startY };
        p.velocity = Vector2{ GetRandomFloat(-80.0f, 80.0f), GetRandomFloat(-150.0f, -40.0f) };
        p.color = blockColor;
        p.size = GetRandomFloat(2.5f, 5.5f);
        p.maxLife = GetRandomFloat(0.3f, 0.6f);
        p.life = p.maxLife;

        particles.push_back(p);
    }
}

void ParticleSystem::update(float dt) {
    for (auto it = particles.begin(); it != particles.end();) {
        it->life -= dt;
        if (it->life <= 0) {
            it = particles.erase(it);
        } else {
            it->position.x += it->velocity.x * dt;
            it->position.y += it->velocity.y * dt;
            it->velocity.y += 180.0f * dt; // Subtle gravity pull
            ++it;
        }
    }
}

void ParticleSystem::draw() const {
    for (const auto& p : particles) {
        float alpha = p.life / p.maxLife;
        Color col = ColorAlpha(p.color, alpha);
        DrawCircleV(p.position, p.size * alpha, col);
    }
}
