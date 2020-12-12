#ifndef GAME_STATE_H
#define GAME_STATE_H

#include "math_util.h"

#define CHAIN_MAX_NODE_COUNT 8
#define PLAYER_CHAIN_SEGMENT_LENGTH 150
#define MAX_PLAYERS 4
#define MAX_ENEMIES 16
#define PLAYER_INVULNERABILITY_BLINK_HZ 4.0
#define PLAYER_INVULNERABILITY_MASS_MULTIPLIER 0.05

typedef struct VerletBody {
    Vec2f position;
    Vec2f oldPosition;
    float mass;
    float radius;
    float bounciness;
    float airResistance;
    float collisionMassMultiplier;
} VerletBody;

typedef struct ChainNode {
    Vec2f position;
    Vec2f oldPosition;
} ChainNode;

typedef struct Chain {
    VerletBody nodes[CHAIN_MAX_NODE_COUNT];
    int nodeCount;
    int segmentLength;
} Chain;

typedef struct Player {
    Chain chain; // First and last links correspond to player and boulder
    float movementSpeed;
    float invulnerabilityTimer;
    float despawnTimer;
    Vec2f movementControl;
    int health;
    int index;
    int score;
    float barrelSpeed;
} Player;

static inline VerletBody* player_getCharacter(Player* player) {
    return &player->chain.nodes[0];
}

static inline VerletBody* player_getBoulder(Player* player) {
    return &player->chain.nodes[player->chain.nodeCount - 1];
}

static inline int player_exists(Player* player) {
    return player->despawnTimer > 0.0f;
}

typedef struct Enemy {
    int targetPlayerIndex;
    int health;
    float despawnTimer;
    float bobTimer;
    float movementSpeed;
    VerletBody verletBody;
} Enemy;

static inline int enemy_exists(Enemy* enemy) {
    return enemy->despawnTimer > 0.0f;
}

typedef struct Camera {
    Vec3f startPosition;
    Vec3f position;
    Vec3f target;
    Vec3f up;
    float screenShake;
} Camera;

typedef struct Physics {
    int verletConstraintIterations;
    float timeAtLastPhysicsUpdate;
    float deltaTime;
    Vec2f gravity;
    Vec2f minBoundary;
    Vec2f maxBoundary;
} Physics;

typedef struct GameState {
    int hideMeshes;
    int nextEnemyTargetPlayerIndex;
    float enemySpawnInterval;
    float enemySpawnTimer;
    float endTimer;
    Player players[MAX_PLAYERS];
    Enemy enemies[MAX_ENEMIES];
    Camera camera;
    Physics physics;
    int freezeFrame;
    float deltaTime;
    float lastTick;
} GameState;

typedef enum GameMode { SURVIVAL, BATTLE } GameMode;

typedef struct GameConfig {
    int playerCount;
    GameMode gameMode;
} GameConfig;

typedef enum ScreenType { MENU, LOADING, GAME, END } ScreenType;

typedef struct ProgramState {
    ScreenType activeScreen;
    GameConfig gameConfig;
    GameState gameState;
} ProgramState;

#endif