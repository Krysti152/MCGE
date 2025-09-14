#pragma once

#include <MCGE/Essentials/Objects/Headers/KinematicBody.hpp>
#include <MCGE/Essentials/Objects/Headers/StaticBody.hpp>


gm::KinematicBody::KinematicBody() {
    is_static = false;
    node_type_id = 4;
    init();
    // if (node_type_id == 0) {
    // }
    // this->log("Initialized KinematicBody");
}

gm::KinematicBody::KinematicBody(int _x, int _y) {
    KinematicBody();
    transform.setPosition(_x,_y);
}

gm::KinematicBody::~KinematicBody() {
}

void gm::KinematicBody::collide(int _dir) {
    std::vector<std::string> dirs = {"Top", "Right", "Bottom", "Left"};

    // 0 - top
    // 1 - right
    // 2 - bottom
    // 3 - left

    colliding[_dir] = true;

    // std::cout<<"Kolizja na "<<dirs[_dir]<<std::endl;
}

void gm::KinematicBody::start() {

}

void gm::KinematicBody::update() {
    gm::Body::update();
    // shape.circle.setPosition(shape.transform.position.x, shape.transform.position.y);
    // shape.rect.setPosition(shape.transform.position.x, shape.transform.position.y);
}


void gm::KinematicBody::isColliding(gm::StaticBody _b) {
    
}

void gm::KinematicBody::move_and_collide() {
    this->body_id = 0;
    this->colliding = {false,false,false,false};
    // For every Static bodies
    for (const gm::StaticBody* bodyB : STATIC_BODIES) {
        // For every my own collision shapes
        for (const gm::CollisionShape& shapeA : this->collisions) {
            // For every Static Body Collision Shapes
            for (const gm::CollisionShape& shapeB : bodyB->collisions) {
                if (shapeA.is_circle != shapeB.is_circle) {
                    return;
                }
                if (shapeA.is_circle) {

                } else {
                    // RECTANGLE
                    if (shapeA.transform.position.x + shapeA.size.x > shapeB.transform.position.x &&
                        shapeA.transform.position.x < shapeB.transform.position.x + shapeB.size.x &&
                        shapeA.transform.position.y + shapeA.size.y + this->velocity.y * gm::calcDelta() > shapeB.transform.position.y &&
                        shapeA.transform.position.y + this->velocity.y * gm::calcDelta() < shapeB.transform.position.y + shapeB.size.y
                    ) {
                        // this->velocity.y *= -1;
                        if (this->velocity.y > 0) {
                            this->collide(2);
                            this->body_id = shapeB.parent->node_id;
                            // this->log("Colliding with " + shapeB.parent->getName());
                        } else if (this->velocity.y < 0) {
                            this->collide(0);
                            this->body_id = shapeB.parent->node_id;
                            // this->log("Colliding with " + shapeB.parent->getName());
                        }
                        this->velocity.y = 0;
                    }
                    if (shapeA.transform.position.x + shapeA.size.x + this->velocity.x * gm::calcDelta() > shapeB.transform.position.x &&
                        shapeA.transform.position.x + this->velocity.x * gm::calcDelta() < shapeB.transform.position.x + shapeB.size.x &&
                        shapeA.transform.position.y + shapeA.size.y > shapeB.transform.position.y &&
                        shapeA.transform.position.y < shapeB.transform.position.y + shapeB.size.y
                    ) {
                        // this->velocity.x *= -1;
                        if (this->velocity.x > 0) {
                            this->collide(3);
                            this->body_id = shapeB.parent->node_id;
                            // this->log("Colliding with " + shapeB.parent->getName());
                        } else if (this->velocity.x < 0) {
                            this->collide(1);
                            this->body_id = shapeB.parent->node_id;
                            // this->log("Colliding with " + shapeB.parent->getName());
                        }
                        this->velocity.x = 0;
                    }

                }
            }
        }
    }
    for (const gm::KinematicBody* bodyB : KINEMATIC_BODIES) {
        if (bodyB == this) {
            continue;
        }
        // For every my own collision shapes
        for (const gm::CollisionShape& shapeA : this->collisions) {
            // For every Static Body Collision Shapes
            for (const gm::CollisionShape& shapeB : bodyB->collisions) {
                if (shapeA.is_circle != shapeB.is_circle) {
                    return;
                }
                if (shapeA.is_circle) {

                } else {
                    // RECTANGLE
                    if (shapeA.transform.position.x + shapeA.size.x > shapeB.transform.position.x &&
                        shapeA.transform.position.x < shapeB.transform.position.x + shapeB.size.x &&
                        shapeA.transform.position.y + shapeA.size.y + this->velocity.y * gm::calcDelta() > shapeB.transform.position.y &&
                        shapeA.transform.position.y + this->velocity.y * gm::calcDelta() < shapeB.transform.position.y + shapeB.size.y
                    ) {
                        // this->velocity.y *= -1;
                        if (this->velocity.y > 0) {
                            this->collide(2);
                            this->body_id = shapeB.parent->node_id;
                            // this->log("Colliding with " + shapeB.parent->getName());
                        } else if (this->velocity.y < 0) {
                            this->collide(0);
                            this->body_id = shapeB.parent->node_id;
                            // this->log("Colliding with " + shapeB.parent->getName());
                        }
                        this->velocity.y = 0;
                    }
                    if (shapeA.transform.position.x + shapeA.size.x + this->velocity.x * gm::calcDelta() > shapeB.transform.position.x &&
                        shapeA.transform.position.x + this->velocity.x * gm::calcDelta() < shapeB.transform.position.x + shapeB.size.x &&
                        shapeA.transform.position.y + shapeA.size.y > shapeB.transform.position.y &&
                        shapeA.transform.position.y < shapeB.transform.position.y + shapeB.size.y
                    ) {
                        // this->velocity.x *= -1;
                        if (this->velocity.x > 0) {
                            this->collide(3);
                            this->body_id = shapeB.parent->node_id;
                            // this->log("Colliding with " + shapeB.parent->getName());
                        } else if (this->velocity.x < 0) {
                            this->collide(1);
                            this->body_id = shapeB.parent->node_id;
                            // this->log("Colliding with " + shapeB.parent->getName());
                        }
                        this->velocity.x = 0;
                    }

                }
            }
        }
    }
        
    this->transform.position.x += this->velocity.x * gm::calcDelta();
    this->transform.position.y += this->velocity.y * gm::calcDelta();
    this->update();

        
}