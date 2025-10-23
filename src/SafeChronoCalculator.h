/**
 * @file SafeChronoCalculator.h
 * @brief Safe chrono calculator with overflow protection
 * 
 * This header provides safe chrono calculations that prevent integer overflow
 * by using the _Whole and _Part algorithm that was removed in the diff.
 */

#ifndef SAFE_CHRONO_CALCULATOR_H
#define SAFE_CHRONO_CALCULATOR_H

#include <chrono>
#include <limits>
#include <stdexcept>

namespace SafeChrono {

/**
 * @class SafeChronoCalculator
 * @brief Provides safe chrono calculations with overflow protection
 */
class SafeChronoCalculator {
public:
    /**
     * @brief Safely calculate time_point duration with overflow protection
     * @param counter The counter value
     * @param frequency The frequency value
     * @param periodDen The period denominator
     * @return Safe duration calculation
     * @throws std::overflow_error if calculation would overflow
     */
    static std::chrono::nanoseconds safeCalculateDuration(
        long long counter, 
        long long frequency, 
        long long periodDen) {
        
        // Validate inputs
        if (frequency <= 0) {
            throw std::invalid_argument("Frequency must be positive");
        }
        if (periodDen <= 0) {
            throw std::invalid_argument("Period denominator must be positive");
        }
        
        // Use safe algorithm to prevent overflow
        return safeCalculateWithWholeAndPart(counter, frequency, periodDen);
    }
    
    /**
     * @brief Calculate duration for 10MHz frequency
     * @param counter The counter value
     * @return Safe duration calculation for 10MHz
     */
    static std::chrono::nanoseconds calculateFor10MHz(long long counter) {
        const long long frequency = 10000000; // 10MHz
        const long long periodDen = 1000000000; // nanoseconds
        return safeCalculateDuration(counter, frequency, periodDen);
    }
    
    /**
     * @brief Calculate duration for 24MHz frequency
     * @param counter The counter value
     * @return Safe duration calculation for 24MHz
     */
    static std::chrono::nanoseconds calculateFor24MHz(long long counter) {
        const long long frequency = 24000000; // 24MHz
        const long long periodDen = 1000000000; // nanoseconds
        return safeCalculateDuration(counter, frequency, periodDen);
    }
    
    /**
     * @brief Check if direct multiplication would overflow
     * @param a First operand
     * @param b Second operand
     * @return true if multiplication would overflow
     */
    static bool wouldOverflow(long long a, long long b) {
        if (a == 0 || b == 0) return false;
        
        if (a > 0 && b > 0) {
            return a > std::numeric_limits<long long>::max() / b;
        } else if (a < 0 && b < 0) {
            return a < std::numeric_limits<long long>::max() / b;
        } else if (a < 0 && b > 0) {
            return a < std::numeric_limits<long long>::min() / b;
        } else if (a > 0 && b < 0) {
            return b < std::numeric_limits<long long>::min() / a;
        }
        
        return false;
    }

private:
    /**
     * @brief Safe calculation using _Whole and _Part algorithm
     * @param counter The counter value
     * @param frequency The frequency value
     * @param periodDen The period denominator
     * @return Safe duration calculation
     */
    static std::chrono::nanoseconds safeCalculateWithWholeAndPart(
        long long counter, 
        long long frequency, 
        long long periodDen) {
        
        // Check if direct multiplication would be safe
        if (!wouldOverflow(counter, periodDen)) {
            // Safe to use direct calculation
            return std::chrono::nanoseconds((counter * periodDen) / frequency);
        }
        
        // Use _Whole and _Part algorithm to prevent overflow
        const long long whole = (counter / frequency) * periodDen;
        const long long part = (counter % frequency) * periodDen / frequency;
        
        // Check if the result would overflow
        if (whole > std::numeric_limits<long long>::max() - part) {
            throw std::overflow_error("Duration calculation would overflow even with safe algorithm");
        }
        
        return std::chrono::nanoseconds(whole + part);
    }
};

} // namespace SafeChrono

#endif // SAFE_CHRONO_CALCULATOR_H
