#pragma once

#include <vector>
#include <random>
#include "FMSEnemies.hpp"

class EnemySpawner
{
public:
    EnemySpawner();
    ~EnemySpawner();

    void update(double dt);
    void spawnEnemy();

private:
    std::vector<FMSEnemies*> enemies;
    std::default_random_engine randomEngine;
    std::uniform_real_distribution<double> spawnTimeDistribution;
    double spawnTimer;
    double spawnInterval;
};

