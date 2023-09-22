#ifndef QUIKMAFF_RANDOM_HPP
#define QUIKMAFF_RANDOM_HPP

#include <chrono>
#include <random>

#include "functions.hpp"

/**
 * @brief A random number generator class based on PCG algorithm.
 */
class Random {
public:
    /**
     * @brief Constructs a Random instance and seeds it.
     */
    Random() { seed(); }

    /**
     * @brief Generates a random integer.
     * @return Random integer.
     *
     * Example usage:
     * @code
     * int randomValue = randGen.rand(); // Generates a random integer.
     * @endcode
     */
    inline constexpr u32 rand() noexcept
    {
        std::lock_guard<std::mutex> lock(m_mutex);

        const qm::u_least64 old_state = m_generatorState.State;
        m_generatorState.State = old_state * 6364136223846793005ULL + m_generatorState.Sequence;

        const qm::u_least32 xor_shifted =
            static_cast<qm::u_least32>(((old_state >> 18u) ^ old_state) >> 27u);
        const qm::u_least32 rot = static_cast<qm::u_least32>(old_state >> 59u);

        return static_cast<u32>((xor_shifted >> rot) | (xor_shifted << ((-rot) & 31)));
    }

    /**
     * @brief Generates a random integer within a specified range.
     * @param min Minimum value of the generated integer (inclusive).
     * @param max Maximum value of the generated integer (inclusive).
     * @return Random integer within the specified range.
     *
     * Example usage:
     * @code
     * int randomValue = randGen.rand(1, 100); // Generates a random integer between 1 and 100.
     * @endcode
     */
    inline constexpr int rand(const int min, const int max) noexcept
    {
        // Note: Mutex is locked by rand() call above

        return min + (this->rand() % (max - min + 1));
    }

    /**
     * @brief Generates a random float within a specified range.
     * @param min Minimum value of the generated float.
     * @param max Maximum value of the generated float.
     * @return Random float within the specified range.
     *
     * Example usage:
     * @code
     * int randomValue = randGen.randF(0.0f, 100.0f); // Generates a random integer between 1.0f and
     * 100.0f.
     * @endcode
     */
    inline constexpr f32 randF(const f32 min, const f32 max) noexcept
    {
        // Note: Mutex is locked by rand() call above

        const f32 random_float =
            static_cast<f32>(this->rand()) / static_cast<f32>(std::numeric_limits<u32>::max());

        return min + random_float * (max - min);
    }

    /**
     * @brief Generates a random string of the specified length using lower and uppercase alpha
     * characters.
     * @param length Length of the generated string.
     * @return Random alpha string of the specified length.
     *
     * Example usage:
     * @code
     * std::string id = randGen.randString(10); // Generates a string of given length using alpha
     * characters
     * @endcode
     */
    inline std::string randString(const std::size_t length)
    {
        // Note: Mutex is locked by rand() call above

        if (length <= 0) {
            throw std::invalid_argument("Invalid length for randAlphaNumericString");
        }

        const std::string charset =
            "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";

        std::string result;
        for (std::size_t i = 0; i < length; ++i) {
            result += charset[this->rand() % charset.length()];
        }

        return result;
    }

    /**
     * @brief Generates a random string of the specified length using alphanumeric characters.
     * @param length Length of the generated string.
     * @return Random alphanumeric string of the specified length.
     *
     * Example usage:
     * @code
     * std::string id = randGen.randAlphaNumericString(10); // Generates a string of given length
     * using alphanumeric characters
     * @endcode
     */
    inline std::string randAlphaNumericString(const std::size_t length)
    {
        // Note: Mutex is locked by rand() call above

        if (length <= 0) {
            throw std::invalid_argument("Invalid length for randAlphaNumericString");
        }
        const std::string charset =
            "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";

        std::string result;
        for (std::size_t i = 0; i < length; ++i) {
            result += charset[this->rand() % charset.length()];
        }

        return result;
    }

    /**
     * @brief Generates a random float from a normal (Gaussian) distribution.
     * @param mean Mean (average) value of the distribution.
     * @param stddev Standard deviation of the distribution.
     * @return Random float from the normal distribution.
     *
     * This function generates a random float from a normal (Gaussian) distribution
     * with the specified mean and standard deviation.
     *
     * Example usage:
     * @code
     * Random randGen;
     * float mean = 0.0f;
     * float stddev = 1.0f;
     * float randomValue = randGen.randNormal(mean, stddev); // Generate a random float from a
     * normal distribution.
     * @endcode
     */
    inline f32 randNormal(f32 mean, f32 stddev)
    {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::normal_distribution<f32> dist(mean, stddev);
        return dist(gen);
    }

    /**
     * @brief Generates a random ID composed of a timestamp, random component, and a counter.
     * @return Random ID string.
     *
     * Example usage:
     * @code
     * std::string id = randGen.generateID(); // Generates a random ID composed of a timestamp,
     * random component, and a counter.
     * @endcode
     */
    inline std::string generateID()
    {
        // Note: Mutex is locked by rand() call above

        static u64 counter;
        // Get current timestamp
        auto timestamp = std::chrono::high_resolution_clock::now().time_since_epoch().count();

        // Get random component
        auto randomComponent = this->rand();

        // Increment the m_counter
        counter++;

        // Combine components to form the ID using std::format
        return std::format("{0}{1}{2}", timestamp, randomComponent, counter);
    }

    /**
     * @brief Generates a random boolean value (true or false).
     * @return Random boolean (true, false).
     *
     * Example usage:
     * @code
     * bool outcome = randGen.coinFlip(); // Generates a random boolean value (true or false).
     * @endcode
     */
    inline constexpr bool coinFlip()
    {

        // Note: Mutex is locked by rand() call above

        return (this->rand() % 2) ? true : false;
    }

    /**
     * @brief Gets a random element from a vector of elements.
     * @param elements Vector containing elements.
     * @return Random element from the vector.
     *
     * This function selects a random element from the provided vector and returns it.
     * If the vector is empty, it throws an invalid_argument exception.
     *
     * Example usage:
     * @code
     * Random randGen;
     * std::vector<int> numbers = {1, 2, 3, 4, 5};
     * int randomValue = randGen.getRandomElement(numbers); // Get a random element from 'numbers'.
     * @endcode
     */
    template <typename T>
    inline const T &getRandomElement(const std::vector<T> &elements)
    {
        // Note: Mutex is locked by rand() call above

        if (elements.empty()) {
            throw std::invalid_argument("Empty container in getRandomElement");
        }
        return elements[this->rand() % elements.size()];
    }

    /**
     * @brief Shuffles the elements of a vector randomly.
     * @param container Vector to be shuffled.
     *
     * This function shuffles the elements of the provided vector randomly using the
     * default random engine. It modifies the order of elements in the container.
     *
     * Example usage:
     * @code
     * Random randGen;
     * std::vector<int> numbers = {1, 2, 3, 4, 5};
     * randGen.shuffleVector(numbers); // Shuffle the elements of 'numbers' randomly.
     * @endcode
     */
    template <typename T>
    inline void shuffleVector(std::vector<T> &container)
    {
        // Note: Mutex is locked by rand() call above

        std::shuffle(container.begin(), container.end(), std::default_random_engine(rand()));
    }

    /**
     * @brief Seeds the random number generator.
     * @param seedValue Seed value for the generator. If not provided, a random seed will be used.
     *
     * Example usage:
     * @code
     * Random randGen;
     * randGen.seed(); // Seed with a random value
     * randGen.seed(123); // Seed with a custom value
     * @endcode
     */
    void seed(const unsigned int seedValue = 0)
    {
        // Note: Mutex is locked by rand() call above

        if (seedValue == 0) {
            std::random_device rd;

            m_generatorState.State = rd();
            m_generatorState.Sequence = (rd() << 1u) | 1u;

            this->rand(); // To shuffle the state a bit more.
            m_generatorState.State += rd();
        }
        else {

            m_generatorState.State = static_cast<qm::u_least64>(seedValue);
            m_generatorState.Sequence = 1u; // Set a constant sequence for custom seeds
            this->rand();                   // Shuffle the state
            m_generatorState.State += 0x853c49e6748fea9bULL;
        }

        this->rand(); // And some more...
    }

private:
    /**
     * @brief Represents the internal state of the PCG generator.
     */
    struct PCGState {
        qm::u_least64 State;
        qm::u_least64 Sequence;
    };

private:
    PCGState m_generatorState;
    std::mutex m_mutex;
};

#endif // QUIKMAFF_RANDOM_HPP
