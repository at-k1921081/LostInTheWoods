#ifndef RECTMOVEMENT_H
#define RECTMOVEMENT_H

#include <functional>
#include "RenderData.h"
#include "rspan.h"

// The end parts of a level area, beyond which objects cannot pass
struct Bounds {
    float left, right, top, bottom;
};

/**
 * @brief Moves a rectangle on the screen. Checks for collision against terrain and level bounds.
 * @param r The rectangle which we will move
 * @param x x displacement
 * @param y y displacement
 * @param deltatime Time since last frame
 * @param other_rects The other rects, which represent terrain
 * @param bounds The level bounds
 * @return true if there has been a collision with terrain or level bounds, false otherwise
 */
bool MoveRect(VKKit::Rect& r, float x, float y, float deltatime, ut::rspan<const VKKit::Rect> other_rects, const Bounds& bounds) noexcept;

/**
 * @brief Tests if a rectangle is colliding with another object that has a rectangle hitbox
 * @tparam T The type of the object that collision testing will be done with
 * @tparam Collision Callable object with a bool operator() that tests for collision between a VKKit::Rect and an object of type T
 * @param r The rectangle
 * @param objects The objects that collision testing will be done with
 * @param collision An instance of the collision testing callable
 * @return true if there are collisions, false otherwise
 */
template<typename T, typename Collision>
bool TestCollisionWithObjects(const VKKit::Rect& r, ut::rspan<const T> objects, Collision collision)
{
    for (const auto& o : objects) {
        if (collision(r, o)) return true;
    }

    return false;
}

/**
 * @brief Tests if a given rectangle collides with any sort of terrain
 * @param r The rectangle
 * @param walls The walls of the level
 * @param bounds The bounds of the level area
 * @return true if there's a collision, false otherwise
 */
bool TestCollisionWithTerrain(const VKKit::Rect& r, ut::rspan<const VKKit::Rect> walls, const Bounds& bounds);

#endif