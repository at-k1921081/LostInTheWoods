#include "RectMovement.h"

static bool MoveX(VKKit::Rect& r, float x, float deltatime, ut::rspan<const VKKit::Rect> walls, const Bounds& bounds) noexcept
{
    bool has_collision = false;
    r.x += x * deltatime;
    
    for (const auto& w : walls) {
        if (VKKit::HasIntersection(r, w)) {
            if (x < 0.0) // Move left
                r.x = w.x + w.w; // Player will be at the left end of the wall
            else // Move right
                r.x = w.x - r.w; // Player will be at the right end of the wall
            has_collision = true;
        }
    }

    if (r.x < bounds.left) {
        r.x = bounds.left;
        has_collision = true;
    }
    if (r.x > bounds.right - r.w) {
        r.x = bounds.right - r.w;
        has_collision = true;
    }

    return has_collision;
}

static bool MoveY(VKKit::Rect& r, float y, float deltatime, ut::rspan<const VKKit::Rect> walls, const Bounds& bounds) noexcept
{
    bool has_collision = false;
    r.y += y * deltatime;
    
    for (const auto& w : walls) {
        if (VKKit::HasIntersection(r, w)) {
            if (y < 0.0) // Move up
                r.y = w.y + w.h; // Player will be at the top end of the wall
            else // Move down
                r.y = w.y - r.h; // Player will be at the bottom end of the wall
            has_collision = true;
        }
    }

    if (r.y < bounds.top) {
        r.y = bounds.top;
        has_collision = true;
    }
    if (r.y > bounds.bottom - r.h) {
        r.y = bounds.bottom - r.h;
        has_collision = true;
    }

    return has_collision;
}

static constexpr bool RectWithinBounds(const VKKit::Rect& r, const Bounds& bounds)
{
    return  (r.x > bounds.left) &&
            (r.x < bounds.right - r.w) &&
            (r.y > bounds.top) &&
            (r.y < bounds.bottom - r.h);
}

bool MoveRect(VKKit::Rect& r, float x, float y, float deltatime, ut::rspan<const VKKit::Rect> other_rects, const Bounds& bounds) noexcept
{
    bool horizontal_collsion = false, vertical_collision = false;
    if (x != 0.0f) horizontal_collsion = MoveX(r, x, deltatime, other_rects, bounds);
    if (y != 0.0f) vertical_collision = MoveY(r, y, deltatime, other_rects, bounds);

    return horizontal_collsion || vertical_collision;
}

bool TestCollisionWithTerrain(const VKKit::Rect& r, ut::rspan<const VKKit::Rect> walls, const Bounds& bounds)
{
    for (const auto& w : walls) {
        if (VKKit::HasIntersection(r, w))
            return true;
    }

    return !RectWithinBounds(r, bounds);
}