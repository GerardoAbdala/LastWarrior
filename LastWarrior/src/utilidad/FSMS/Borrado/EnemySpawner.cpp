#include "EnemySpawner.hpp"
#include "FMSEnemies.hpp"

EnemySpawner::EnemySpawner()
    : spawnTimer(0.0),
      spawnInterval(3.0) // Adjust the spawn interval as desired
{
    // Initialize the random engine and distribution
    std::random_device rd;
    randomEngine = std::default_random_engine(rd());
    spawnTimeDistribution = std::uniform_real_distribution<double>(0.5, 2.0); // Adjust the spawn time range as desired
}

EnemySpawner::~EnemySpawner()
{
    // Clean up dynamically allocated enemies
    for (FMSEnemies* enemy : enemies)
    {
        delete enemy;
    }
}

void EnemySpawner::update(double dt)
{
    spawnTimer += dt;

    if (spawnTimer >= spawnInterval)
    {
        spawnEnemy();
        spawnTimer = 0.0;
    }

    // Update existing enemies
    for (FMSEnemies* enemy : enemies)
    {
        enemy->update(dt);
    }
}

void EnemySpawner::spawnEnemy()
{
    // Generate a new enemy and add it to the vector
    FMSEnemies* newEnemy = nullptr;
    // Customize the enemy spawning logic here, such as choosing a random position or enemy type
    // For example:
    // newEnemy = new EnemyStateIdle();
    // newEnemy->enter();
    // newEnemy->set_position(randomPosition);
    // ...
    enemies.push_back(newEnemy);
}

