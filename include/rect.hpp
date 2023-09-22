#ifndef QUIKMATH_RECT_HPP
#define QUIKMATH_RECT_HPP

#include "functions.hpp"
#include "vec2.hpp"
#include "vec4.hpp"

/**
 * @brief Represents a 2D rectangle with top, bottom, left, and right sides.
 */
struct Rect {
    /**
     * @brief Default constructor. Initializes all sides to 0.0.
     */
    constexpr Rect() : Top{0.0f}, Bottom{0.0f}, Left{0.0f}, Right{0.0f} {}

    /**
     * @brief Constructs a rectangle with specified top, bottom, left, and right sides.
     * @param top The top side of the rectangle.
     * @param bottom The bottom side of the rectangle.
     * @param left The left side of the rectangle.
     * @param right The right side of the rectangle.
     */
    constexpr Rect(f32 top, f32 bottom, f32 left, f32 right)
        : Top{qm::max(top, bottom)},
          Bottom{qm::min(top, bottom)},
          Left{qm::min(left, right)},
          Right{qm::max(left, right)}
    {
    }

    /**
     * @brief Constructs a rectangle from two Vec2 points representing the top-left and bottom-right
     * corners.
     *
     * This constructor calculates the rectangle's top, bottom, left, and right sides based on the
     * provided points.
     *
     * @param topLeft The top-left corner of the rectangle.
     * @param bottomRight The bottom-right corner of the rectangle.
     */
    constexpr Rect(const Vec2 &topLeft, const Vec2 &bottomRight)
        : Top{qm::max(topLeft.y, bottomRight.y)},
          Bottom{qm::min(topLeft.y, bottomRight.y)},
          Left{qm::min(topLeft.x, bottomRight.x)},
          Right{qm::max(topLeft.x, bottomRight.x)}
    {
    }

    /**
     * @brief Constructs a rectangle from a Vec4 representing top, bottom, left, and right values.
     * @param vector The Vec4 containing top, bottom, left, and right values.
     */
    constexpr Rect(const Vec4 &vector)
        : Top{qm::max(vector.y, vector.w)},
          Bottom{qm::min(vector.y, vector.w)},
          Left{qm::min(vector.x, vector.z)},
          Right{qm::max(vector.x, vector.z)}
    {
    }

    /**
     * @brief Returns the value of the top side of the rectangle.
     * @return The value of the top side.
     */
    constexpr f32 top() const { return Top; }

    /**
     * @brief Returns the value of the bottom side of the rectangle.
     * @return The value of the bottom side.
     */
    constexpr f32 bottom() const { return Bottom; }

    /**
     * @brief Returns the value of the left side of the rectangle.
     * @return The value of the left side.
     */
    constexpr f32 left() const { return Left; }

    /**
     * @brief Returns the value of the right side of the rectangle.
     * @return The value of the right side.
     */
    constexpr f32 right() const { return Right; }

    /**
     * @brief Calculates and returns the top-left corner of the rectangle.
     * @return The top-left corner as a Vec2.
     */
    constexpr Vec2 topLeft() const { return Vec2(Left, Top); }

    /**
     * @brief Calculates and returns the top-right corner of the rectangle.
     * @return The top-right corner as a Vec2.
     */
    constexpr Vec2 topRight() const { return Vec2(Right, Top); }

    /**
     * @brief Calculates and returns the bottom-left corner of the rectangle.
     * @return The bottom-left corner as a Vec2.
     */
    constexpr Vec2 bottomLeft() const { return Vec2(Left, Bottom); }

    /**
     * @brief Calculates and returns the bottom-right corner of the rectangle.
     * @return The bottom-right corner as a Vec2.
     */
    constexpr Vec2 bottomRight() const { return Vec2(Right, Bottom); }

    /**
     * @brief Calculates and returns the area of the rectangle.
     * @return The area of the rectangle.
     */
    constexpr f32 area() const { return (Right - Left) * (Top - Bottom); }

    /**
     * @brief Checks if this rectangle intersects with another rectangle.
     * @param other The other rectangle to check for intersection.
     * @return True if the rectangles intersect; otherwise, false.
     */
    constexpr bool intersects(const Rect &other) const
    {
        return !(Right < other.Left || Left > other.Right || Top < other.Bottom ||
                 Bottom > other.Top);
    }

    /**
     * @brief Calculates and returns a new rectangle representing the union of this rectangle
     *        and another rectangle.
     * @param other The other rectangle to compute the union with.
     * @return A new rectangle representing the union.
     */
    constexpr Rect unionWith(const Rect &other) const
    {
        return Rect(qm::min(Left, other.Left), qm::max(Right, other.Right), qm::max(Top, other.Top),
                    qm::min(Bottom, other.Bottom));
    }

    /**
     * @brief Checks if a specified point is inside the rectangle.
     * @param point The point to check.
     * @return True if the point is inside the rectangle; otherwise, false.
     */
    constexpr bool contains(const Vec2 &point) const
    {
        return (point.x >= Left && point.x <= Right && point.y >= Bottom && point.y <= Top);
    }

    /**
     * @brief Sets the properties of the rectangle to new values.
     * @param top The new top side.
     * @param bottom The new bottom side.
     * @param left The new left side.
     * @param right The new right side.
     */
    constexpr void set(f32 top, f32 bottom, f32 left, f32 right)
    {
        Top = top;
        Bottom = bottom;
        Left = left;
        Right = right;
    }

    /**
     * @brief Clamps a specified point to be inside the rectangle.
     * @param point The point to clamp.
     * @return The clamped point as a Vec2.
     */
    constexpr Vec2 clampPoint(const Vec2 &point) const
    {
        return Vec2(qm::clamp(point.x, Left, Right), qm::clamp(point.y, Bottom, Top));
    }

    /**
     * @brief Returns a string representation of the rectangle.
     * @return A string containing the rectangle's properties.
     */
    constexpr std::string toString() const
    {
        return std::format("Rect(Top: {0}, Bottom: {1}, Left: {2}, Right: {3})", Top, Bottom, Left,
                           Right);
    }

    /**
     * @brief Returns a string representation of the rectangle's corners.
     * @return A string containing the rectangle's corner coordinates.
     */
    constexpr std::string cornersToString() const
    {
        return std::format("Rect(TopLeft: {0}, TopRight: {1}, BottomLeft: {2}, BottomRight: {3})",
                           topLeft(), topRight(), bottomLeft(), bottomRight());
    }

private:
    f32 Top;
    f32 Bottom;
    f32 Left;
    f32 Right;
};

#endif // QUIKMATH_RECT_HPP