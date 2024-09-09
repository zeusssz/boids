#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define WIDTH 800
#define HEIGHT 600
#define NUM_BOIDS 100
#define MAX_SPEED 2.0
#define MAX_FORCE 0.03

typedef struct {
    float x, y;
} Vector;

typedef struct {
    Vector position;
    Vector velocity;
    Vector acceleration;
} Boid;

Boid boids[NUM_BOIDS];
Vector create_vector(float x, float y) {
    Vector v = {x, y};
    return v;
}
Vector add_vectors(Vector a, Vector b) {
    return create_vector(a.x + b.x, a.y + b.y);
}
Vector subtract_vectors(Vector a, Vector b) {
    return create_vector(a.x - b.x, a.y - b.y);
}
Vector multiply_vector(Vector v, float scalar) {
    return create_vector(v.x * scalar, v.y * scalar);
}
Vector limit_vector(Vector v, float max) {
    float magnitude = sqrt(v.x * v.x + v.y * v.y);
    if (magnitude > max) {
        v.x = (v.x / magnitude) * max;
        v.y = (v.y / magnitude) * max;
    }
    return v;
}
void initialize_boids() {
    for (int i = 0; i < NUM_BOIDS; i++) {
        boids[i].position = create_vector(rand() % WIDTH, rand() % HEIGHT);
        boids[i].velocity = create_vector((float)rand() / RAND_MAX * 2 - 1, (float)rand() / RAND_MAX * 2 - 1);
        boids[i].acceleration = create_vector(0, 0);
    }
}
void update_boids() {
    for (int i = 0; i < NUM_BOIDS; i++) {
        boids[i].velocity = add_vectors(boids[i].velocity, boids[i].acceleration);
        boids[i].velocity = limit_vector(boids[i].velocity, MAX_SPEED);
        boids[i].position = add_vectors(boids[i].position, boids[i].velocity);
        boids[i].acceleration = create_vector(0, 0);
        if (boids[i].position.x < 0) boids[i].position.x += WIDTH;
        if (boids[i].position.x > WIDTH) boids[i].position.x -= WIDTH;
        if (boids[i].position.y < 0) boids[i].position.y += HEIGHT;
        if (boids[i].position.y > HEIGHT) boids[i].position.y -= HEIGHT;
    }
}
void print_boids() {
    for (int i = 0; i < NUM_BOIDS; i++) {
        printf("Boid %d: Position (%.2f, %.2f)\n", i, boids[i].position.x, boids[i].position.y);
    }
}

int main() {
    initialize_boids();
    for (int frame = 0; frame < 100; frame++) {
        update_boids();
        print_boids();
    }
    return 0;
}
