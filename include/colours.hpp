#ifndef QUIKMATH_COLOURS_HPP
#define QUIKMATH_COLOURS_HPP

#include "functions.hpp"
#include "random.hpp"

/**
 * @brief Represents a colour in RGBA format as normalized floating-point values in the range
 * [0.0, 1.0]..
 */
struct Colour {
    f32 r, g, b, a;

    /**
     * @brief Default Constructor for Colour.
     */
    Colour() : r{0.0f}, g{0.0f}, b{0.0f}, a{0.0f} {}

    /**
     * @brief Single value constructor for Colour.
     *
     * Note: Values are clamped to normalized floating-point values in the range [0.0, 1.0].
     *
     * @param value The value for all components (0.0 to 1.0).
     */
    Colour(f32 value)
        : r{qm::clamp(value, 0.0f, 1.0f)},
          g{qm::clamp(value, 0.0f, 1.0f)},
          b{qm::clamp(value, 0.0f, 1.0f)},
          a{qm::clamp(value, 0.0f, 1.0f)}
    {
    }

    /**
     * @brief Constructor for Colour.
     *
     * Note: Values are clamped to normalized floating-point values in the range [0.0, 1.0].
     *
     * @param red The red component (0.0 to 1.0).
     * @param green The green component (0.0 to 1.0).
     * @param blue The blue component (0.0 to 1.0).
     * @param alpha The alpha component (0.0 to 1.0). Defaults to 1.0.
     */
    constexpr Colour(f32 red, f32 green, f32 blue, f32 alpha = 1.0f)
        : r(qm::clamp(red, 0.0f, 1.0f)),
          g(qm::clamp(green, 0.0f, 1.0f)),
          b(qm::clamp(blue, 0.0f, 1.0f)),
          a(qm::clamp(alpha, 0.0f, 1.0f))
    {
    }

    /**
     * @brief Addition of two colours.
     *
     * @param other The other colour to add.
     * @return The result of adding the two colours.
     */
    constexpr Colour operator+(const Colour &other) const
    {
        return Colour(qm::clamp(r + other.r, 0.0f, 1.0f), qm::clamp(g + other.g, 0.0f, 1.0f),
                      qm::clamp(b + other.b, 0.0f, 1.0f), qm::clamp(a + other.a, 0.0f, 1.0f));
    }

    /**
     * @brief Subtraction of one colour from another.
     *
     * @param other The colour to subtract.
     * @return The result of subtracting the other colour.
     */
    constexpr Colour operator-(const Colour &other) const
    {
        return Colour(qm::clamp(r - other.r, 0.0f, 1.0f), qm::clamp(g - other.g, 0.0f, 1.0f),
                      qm::clamp(b - other.b, 0.0f, 1.0f), qm::clamp(a - other.a, 0.0f, 1.0f));
    }

    /**
     * @brief Scaling a colour by a scalar value to make it lighter or darker.
     *
     * @param scalar The scaling factor.
     * @return The scaled colour.
     */
    constexpr Colour operator*(f32 scalar) const
    {
        return Colour(qm::clamp(r * scalar, 0.0f, 1.0f), qm::clamp(g * scalar, 0.0f, 1.0f),
                      qm::clamp(b * scalar, 0.0f, 1.0f), qm::clamp(a * scalar, 0.0f, 1.0f));
    }

    /**
     * @brief Linearly interpolate between two colours.
     *
     * @param endColor The end colour to interpolate towards.
     * @param t The interpolation factor (0.0 to 1.0).
     * @return The interpolated colour.
     */
    constexpr Colour lerp(const Colour &endColor, f32 t) const
    {
        t = qm::clamp(t, 0.0f, 1.0f);
        f32 complementT = 1.0f - t;
        return Colour(r * complementT + endColor.r * t, g * complementT + endColor.g * t,
                      b * complementT + endColor.b * t, a * complementT + endColor.a * t);
    }

    /**
     * @brief Blend two colours using alpha blending.
     *
     * @param srcColor The source colour to blend with.
     * @return The blended colour.
     */
    constexpr Colour blend(const Colour &srcColor) const
    {
        f32 srcAlpha = srcColor.a;
        f32 destAlpha = 1.0f - srcAlpha;
        return Colour(srcColor.r * srcAlpha + r * destAlpha, srcColor.g * srcAlpha + g * destAlpha,
                      srcColor.b * srcAlpha + b * destAlpha, srcAlpha + a * destAlpha);
    }

    /**
     * @brief Convert an RGB colour to HSV (Hue, Saturation, Value) colour representation.
     *
     * @param hue The resulting hue value.
     * @param saturation The resulting saturation value.
     * @param value The resulting value.
     */
    void rgbToHsv(f32 &hue, f32 &saturation, f32 &value) const
    {
        f32 maxVal = qm::max({r, g, b});
        f32 minVal = qm::min({r, g, b});

        // Calculate hue
        if (maxVal == minVal) {
            hue = 0.0f;
        }
        else if (maxVal == r) {
            hue = (60.0f * ((g - b) / (maxVal - minVal)) + 360.0f) / 60.0f;
        }
        else if (maxVal == g) {
            hue = (60.0f * ((b - r) / (maxVal - minVal)) + 120.0f) / 60.0f;
        }
        else if (maxVal == b) {
            hue = (60.0f * ((r - g) / (maxVal - minVal)) + 240.0f) / 60.0f;
        }

        // Calculate saturation
        saturation = (maxVal == 0.0f) ? 0.0f : (1.0f - (minVal / maxVal));

        // Calculate value
        value = maxVal;
    }

    /**
     * @brief Convert an HSV (Hue, Saturation, Value) colour to RGB colour representation.
     *
     * @param hue The hue value (0.0 to 360.0).
     * @param saturation The saturation value (0.0 to 1.0).
     * @param value The value (0.0 to 1.0).
     * @return The RGB colour.
     */
    static constexpr Colour hsvToRgb(f32 hue, f32 saturation, f32 value)
    {
        int hi = static_cast<int>(hue / 60.0f) % 6;
        f32 f = (hue / 60.0f) - hi;
        f32 p = value * (1.0f - saturation);
        f32 q = value * (1.0f - f * saturation);
        f32 t = value * (1.0f - (1.0f - f) * saturation);

        switch (hi) {
            case 0:
                return Colour(value, t, p);
            case 1:
                return Colour(q, value, p);
            case 2:
                return Colour(p, value, t);
            case 3:
                return Colour(p, q, value);
            case 4:
                return Colour(t, p, value);
            default: // case 5:
                return Colour(value, p, q);
        }
    }

    // Colour Comparison -------------------------------------------------------------------------

    /**
     * @brief Compare two colours for equality within a specified tolerance.
     *
     * @param other The other colour to compare.
     * @param tolerance The allowed tolerance for each colour component.
     * @return true if the colours are equal within the tolerance, false otherwise.
     */
    bool equals(const Colour &other, f32 tolerance) const
    {
        return qm::abs(r - other.r) <= tolerance && qm::abs(g - other.g) <= tolerance &&
               qm::abs(b - other.b) <= tolerance && qm::abs(a - other.a) <= tolerance;
    }

    /**
     * @brief Check if a colour is similar to another colour within a specified tolerance.
     *
     * This function is an alias for `equals` and checks if the colours are equal within
     * the given tolerance for each colour component.
     *
     * @param other The other colour to compare.
     * @param tolerance The allowed tolerance for each colour component.
     * @return true if the colours are similar within the tolerance, false otherwise.
     */
    bool isSimilar(const Colour &other, f32 tolerance) const { return equals(other, tolerance); }

    // Colour Generation ---------------------------------------------------------------------------

    /**
     * @brief Generate a random RGB colour within specified constraints.
     * @param minRed The minimum red component (0.0 to 1.0).
     * @param maxRed The maximum red component (0.0 to 1.0).
     * @param minGreen The minimum green component (0.0 to 1.0).
     * @param maxGreen The maximum green component (0.0 to 1.0).
     * @param minBlue The minimum blue component (0.0 to 1.0).
     * @param maxBlue The maximum blue component (0.0 to 1.0).
     * @return A random Colour within the specified constraints.
     */
    Colour randomColour(f32 minRed, f32 maxRed, f32 minGreen, f32 maxGreen, f32 minBlue,
                        f32 maxBlue)
    {
        Random random;

        f32 red = random.randF(minRed, maxRed);
        f32 green = random.randF(minGreen, maxGreen);
        f32 blue = random.randF(minBlue, maxBlue);

        return Colour(red, green, blue);
    }

    // Colour Modification
    // ----------------------------------------------------------------------------

    /**
     * @brief Invert the colour.
     */
    void invert()
    {
        r = 1.0f - r;
        g = 1.0f - g;
        b = 1.0f - b;
    }

    /**
     * @brief Adjust the brightness of the colour.
     * @param brightnessFactor The factor to adjust brightness by.
     */
    void adjustBrightness(f32 brightnessFactor)
    {
        r *= brightnessFactor;
        g *= brightnessFactor;
        b *= brightnessFactor;
    }

    /**
     * @brief Adjust the contrast of the colour.
     * @param contrastFactor The factor to adjust contrast by.
     */
    void adjustContrast(f32 contrastFactor)
    {
        f32 midpoint{0.5f}; // Neutral gray

        r = midpoint + (r - midpoint) * contrastFactor;
        g = midpoint + (g - midpoint) * contrastFactor;
        b = midpoint + (b - midpoint) * contrastFactor;
    }

    /**
     * @brief Convert the Colour object to a formatted string.
     *
     * This function converts the Colour object to a formatted string that represents
     * its RGBA (Red, Green, Blue, Alpha) components with a specified precision.
     *
     * @return A string representation of the Colour object in the format:
     *         "Colour(red: [red_value], green: [green_value], blue: [blue_value], alpha:
     * [alpha_value])"
     */
    std::string toString() const
    {
        return std::format("Colour(red: {:.5f}, green: {:.5f}, blue: {:.5f}, alpha: {:.5f})", r, g,
                           b, a);
    }

    /**
     * @brief Print the Colour object to the standard output.
     *
     * This function prints the Colour object's string representation to the standard output
     * with a specified precision.
     */
    void print() const
    {
        // Print the string representation of the Colour object to the standard output.
        std::cout << toString() << '\n';
    }
};

// For Merica cos f**k yeah!
using Color = Colour;

/**
 * @brief Create a Colour object from an array of u8 values.
 *
 * This function takes an array of unsigned 8-bit integer values representing the RGBA
 * (Red, Green, Blue, Alpha) components of a color and constructs a Colour object.
 *
 * @param values An array containing the RGBA components in the following order:
 *               - values[0]: Red component (0-255)
 *               - values[1]: Green component (0-255)
 *               - values[2]: Blue component (0-255)
 *               - values[3]: Alpha component (0-255)
 *
 * @return A Colour object with the specified RGBA components.
 */
constexpr Colour createColour(const u8 *values)
{
    // Create and return a Colour object using the provided values.
    return Colour(values[0], values[1], values[2], values[3]);
}

constexpr Colour createColour(const f32 *values)
{
    // Create and return a Colour object using the provided values.
    return Colour(values[0], values[1], values[2], values[3]);
}

/**
 * @brief Constructs a color with normalized floating-point components from integer values.
 *
 * This constructor creates a color with red, green, blue, and alpha components
 * represented as normalized floating-point values in the range [0.0, 1.0].
 *
 * @param r_ The integer value for the red component (0-255).
 * @param g_ The integer value for the green component (0-255).
 * @param b_ The integer value for the blue component (0-255).
 * @param a_ The integer value for the alpha component (0-255).
 */
constexpr Colour createColour(u8 red, u8 green, u8 blue, u8 alpha = 0)
{
    return Colour(static_cast<f32>(red / 255.0f), static_cast<f32>(green / 255.0f),
                  static_cast<f32>(blue / 255.0f), static_cast<f32>(alpha / 255.0f));
}

constexpr f32 aqua[] = {0.0f, 1.0f, 1.0f, 1.0f};
constexpr f32 bisque[] = {1.0f, 0.89f, 0.77f, 1.0f};
constexpr f32 black[] = {0.0f, 0.0f, 0.0f, 1.0f};
constexpr f32 blue[] = {0.0f, 0.0f, 1.0f, 1.0f};
constexpr f32 bronze[] = {0.8f, 0.5f, 0.2f, 1.0f};
constexpr f32 cadet_blue[] = {0.37f, 0.62f, 0.63f, 1.0f};
constexpr f32 caramel[] = {1.0f, 0.6f, 0.2f, 1.0f};
constexpr f32 chocolate[] = {0.82f, 0.41f, 0.12f, 1.0f};
constexpr f32 clear_colour[] = {0.1f, 0.1f, 0.1f, 1.0f};
constexpr f32 coral[] = {1.0f, 0.5f, 0.31f, 1.0f};
constexpr f32 cyan[] = {0.0f, 1.0f, 1.0f, 1.0f};
constexpr f32 dark_blue[] = {0.0f, 0.0f, 0.5f, 1.0f};
constexpr f32 dark_cyan[] = {0.0f, 0.5f, 0.5f, 1.0f};
constexpr f32 dark_grey[] = {0.4f, 0.4f, 0.4f, 1.0f};
constexpr f32 dark_green[] = {0.0f, 0.5f, 0.0f, 1.0f};
constexpr f32 dark_magenta[] = {0.5f, 0.0f, 0.5f, 1.0f};
constexpr f32 dark_orange[] = {0.8f, 0.4f, 0.0f, 1.0f};
constexpr f32 dark_pink[] = {0.7f, 0.3f, 0.3f, 1.0f};
constexpr f32 dark_purple[] = {0.3f, 0.0f, 0.3f, 1.0f};
constexpr f32 dark_red[] = {0.5f, 0.0f, 0.0f, 1.0f};
constexpr f32 dark_slate_blue[] = {0.28f, 0.24f, 0.55f, 1.0f};
constexpr f32 dark_slate_gray[] = {0.18f, 0.31f, 0.31f, 1.0f};
constexpr f32 dark_yellow[] = {0.5f, 0.5f, 0.0f, 1.0f};
constexpr f32 firebrick[] = {0.7f, 0.13f, 0.13f, 1.0f};
constexpr f32 forest_green[] = {0.13f, 0.55f, 0.13f, 1.0f};
constexpr f32 gold[] = {1.0f, 0.84f, 0.0f, 1.0f};
constexpr f32 goldenrod[] = {0.85f, 0.65f, 0.13f, 1.0f};
constexpr f32 green[] = {0.0f, 1.0f, 0.0f, 1.0f};
constexpr f32 indigo[] = {0.29f, 0.0f, 0.51f, 1.0f};
constexpr f32 lavender[] = {0.71f, 0.49f, 0.86f, 1.0f};
constexpr f32 lavender_blush[] = {1.0f, 0.94f, 0.96f, 1.0f};
constexpr f32 lemon_chiffon[] = {1.0f, 0.98f, 0.8f, 1.0f};
constexpr f32 light_grey[] = {0.8f, 0.8f, 0.8f, 1.0f};
constexpr f32 lavender_magenta[] = {0.93f, 0.51f, 0.93f, 1.0f};
constexpr f32 magenta[] = {1.0f, 0.0f, 1.0f, 1.0f};
constexpr f32 maroon[] = {0.5f, 0.0f, 0.0f, 1.0f};
constexpr f32 medium_orchid[] = {0.73f, 0.33f, 0.83f, 1.0f};
constexpr f32 midnight_blue[] = {0.1f, 0.1f, 0.44f, 1.0f};
constexpr f32 mint_cream[] = {0.96f, 1.0f, 0.98f, 1.0f};
constexpr f32 olive[] = {0.5f, 0.5f, 0.0f, 1.0f};
constexpr f32 orange[] = {1.0f, 0.5f, 0.0f, 1.0f};
constexpr f32 pale_violet_red[] = {0.86f, 0.44f, 0.58f, 1.0f};
constexpr f32 pink[] = {1.0f, 0.5f, 0.5f, 1.0f};
constexpr f32 red[] = {1.0f, 0.0f, 0.0f, 1.0f};
constexpr f32 rosy_brown[] = {0.74f, 0.56f, 0.56f, 1.0f};
constexpr f32 salmon[] = {0.98f, 0.5f, 0.45f, 1.0f};
constexpr f32 sandy_brown[] = {0.96f, 0.64f, 0.38f, 1.0f};
constexpr f32 sienna[] = {0.63f, 0.32f, 0.18f, 1.0f};
constexpr f32 silver[] = {0.75f, 0.75f, 0.75f, 1.0f};
constexpr f32 slate_blue[] = {0.42f, 0.35f, 0.8f, 1.0f};
constexpr f32 slate_gray[] = {0.44f, 0.5f, 0.56f, 1.0f};
constexpr f32 sky_blue[] = {0.53f, 0.81f, 0.92f, 1.0f};
constexpr f32 steel_blue[] = {0.27f, 0.51f, 0.71f, 1.0f};
constexpr f32 teal[] = {0.0f, 0.5f, 0.5f, 1.0f};
constexpr f32 tomato[] = {1.0f, 0.39f, 0.28f, 1.0f};
constexpr f32 turquoise[] = {0.25f, 0.88f, 0.82f, 1.0f};
constexpr f32 violet[] = {0.93f, 0.51f, 0.93f, 1.0f};
constexpr f32 white[] = {1.0f, 1.0f, 1.0f, 1.0f};
constexpr f32 yellow[] = {1.0f, 1.0f, 0.0f, 1.0f};

/*
constexpr u8 aqua[] = {0, 255, 255, 255};
constexpr u8 bisque[] = {255, 228, 196, 255};
constexpr u8 black[] = {0, 0, 0, 255};
constexpr u8 blue[] = {0, 0, 255, 255};
constexpr u8 bronze[] = {204, 128, 51, 255};
constexpr u8 cadet_blue[] = {94, 160, 161, 255};
constexpr u8 caramel[] = {255, 153, 51, 255};
constexpr u8 chocolate[] = {209, 104, 31, 255};
constexpr u8 clear_colour[] = {26, 26, 26, 255};
constexpr u8 coral[] = {255, 128, 79, 255};
constexpr u8 cyan[] = {0, 255, 255, 255};
constexpr u8 dark_blue[] = {0, 0, 128, 255};
constexpr u8 dark_cyan[] = {0, 128, 128, 255};
constexpr u8 dark_grey[] = {102, 102, 102, 255};
constexpr u8 dark_green[] = {0, 128, 0, 255};
constexpr u8 dark_magenta[] = {128, 0, 128, 255};
constexpr u8 dark_orange[] = {204, 102, 0, 255};
constexpr u8 dark_pink[] = {179, 77, 77, 255};
constexpr u8 dark_purple[] = {77, 0, 77, 255};
constexpr u8 dark_red[] = {128, 0, 0, 255};
constexpr u8 dark_slate_blue[] = {72, 61, 140, 255};
constexpr u8 dark_slate_gray[] = {46, 79, 79, 255};
constexpr u8 dark_yellow[] = {128, 128, 0, 255};
constexpr u8 firebrick[] = {178, 34, 34, 255};
constexpr u8 forest_green[] = {34, 139, 34, 255};
constexpr u8 gold[] = {255, 215, 0, 255};
constexpr u8 goldenrod[] = {218, 165, 35, 255};
constexpr u8 green[] = {0, 255, 0, 255};
constexpr u8 indigo[] = {74, 0, 130, 255};
constexpr u8 lavender[] = {181, 125, 220, 255};
constexpr u8 lavender_blush[] = {255, 240, 245, 255};
constexpr u8 lemon_chiffon[] = {255, 250, 205, 255};
constexpr u8 light_grey[] = {204, 204, 204, 255};
constexpr u8 lavender_magenta[] = {238, 130, 238, 255};
constexpr u8 magenta[] = {255, 0, 255, 255};
constexpr u8 maroon[] = {128, 0, 0, 255};
constexpr u8 medium_orchid[] = {186, 85, 211, 255};
constexpr u8 midnight_blue[] = {25, 25, 112, 255};
constexpr u8 mint_cream[] = {245, 255, 250, 255};
constexpr u8 olive[] = {128, 128, 0, 255};
constexpr u8 orange[] = {255, 128, 0, 255};
constexpr u8 pale_violet_red[] = {219, 112, 147, 255};
constexpr u8 pink[] = {255, 128, 128, 255};
constexpr u8 red[] = {255, 0, 0, 255};
constexpr u8 rosy_brown[] = {188, 143, 143, 255};
constexpr u8 salmon[] = {250, 128, 114, 255};
constexpr u8 sandy_brown[] = {244, 164, 96, 255};
constexpr u8 sienna[] = {160, 82, 45, 255};
constexpr u8 silver[] = {192, 192, 192, 255};
constexpr u8 slate_blue[] = {107, 89, 204, 255};
constexpr u8 slate_gray[] = {112, 128, 144, 255};
constexpr u8 sky_blue[] = {135, 206, 235, 255};
constexpr u8 steel_blue[] = {69, 131, 180, 255};
constexpr u8 teal[] = {0, 128, 128, 255};
constexpr u8 tomato[] = {255, 99, 71, 255};
constexpr u8 transparent[] = {0, 0, 0, 0};
constexpr u8 turquoise[] = {64, 224, 208, 255};
constexpr u8 violet[] = {238, 130, 238, 255};
constexpr u8 white[] = {255, 255, 255, 255};
constexpr u8 yellow[] = {255, 255, 0, 255};
*/

#endif // QUIKMATH_COLOURS_HPP