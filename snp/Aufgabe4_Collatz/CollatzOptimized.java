import java.util.HashMap;
import java.util.Map;
import java.util.concurrent.TimeUnit;

public class CollatzOptimized {

    // Calculates the length of the Collatz sequence for a given number n, using memoization
    private static int calculateSequenceLength(long n, Map<Long, Integer> cache) {
        if (n <= 0) {
            throw new IllegalArgumentException("Input must be a positive integer.");
        }
        if (cache.containsKey(n)) {
            return cache.get(n);
        }
        if (n == 1) {
            return 1; // Base case: sequence for 1 has length 1
        }

        long nextVal;
        if (n % 2 == 0) {
            nextVal = n / 2;
        } else {
            if (n > (Long.MAX_VALUE - 1) / 3) {
                System.err.println("Warning: Potential overflow for 3*n + 1 with n = " + n + ". The sequence might be too long or result in error.");
            }
            nextVal = 3 * n + 1;
        }
        
        int length = 1 + calculateSequenceLength(nextVal, cache);
        cache.put(n, length);
        return length;
    }

    public static void main(String[] args) {
        if (args.length < 1) {
            System.out.println("Usage: java CollatzOptimized <x_value>");
            System.out.println("Example: java CollatzOptimized 10000");
            return;
        }

        long x;
        try {
            x = Long.parseLong(args[0]);
        } catch (NumberFormatException e) {
            System.out.println("Invalid input for x. Please provide a positive integer.");
            return;
        }
        
        if (x <= 0) {
            System.out.println("Input x must be a positive integer.");
            return;
        }

        System.out.println("Running Optimized Collatz for x = " + x);

        Map<Long, Integer> cache = new HashMap<>();
        long numberWithMaxLength = 0;
        int maxLength = 0;

        long startTime = System.nanoTime();

        for (long i = 1; i <= x; i++) {
            int currentLength = calculateSequenceLength(i, cache);
            if (currentLength > maxLength) {
                maxLength = currentLength;
                numberWithMaxLength = i;
            }
        }

        long endTime = System.nanoTime();
        long durationMillis = TimeUnit.NANOSECONDS.toMillis(endTime - startTime);

        System.out.println("\n--- Results for Optimized Version ---");
        System.out.println("Input x: " + x);
        System.out.println("Smallest number (1 to " + x + ") with the longest Collatz sequence: " + numberWithMaxLength);
        System.out.println("Length of its sequence: " + maxLength);
        System.out.println("Time taken: " + durationMillis + " ms");
    }
}
