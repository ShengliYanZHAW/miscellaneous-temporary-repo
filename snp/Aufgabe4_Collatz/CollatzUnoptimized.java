import java.util.concurrent.TimeUnit;

public class CollatzUnoptimized {

    // Calculates the length of the Collatz sequence for a given number n_orig
    public static int getCollatzLength(long n_orig) {
        if (n_orig <= 0) {
            throw new IllegalArgumentException("Input must be a positive integer.");
        }
        
        long n = n_orig; // Use a mutable copy
        int length = 1;
        while (n != 1) {
            if (n % 2 == 0) {
                n = n / 2;
            } else {
                // Check for potential overflow with 3*n + 1
                if (n > (Long.MAX_VALUE - 1) / 3) {
                     System.err.println("Warning: Potential overflow for 3*n + 1 with n = " + n + " (original start: " + n_orig + "). Result might be incorrect.");
                }
                n = 3 * n + 1;
            }
            length++;
        }
        return length;
    }

    public static void main(String[] args) {
        if (args.length < 1) {
            System.out.println("Usage: java CollatzUnoptimized <x_value>");
            System.out.println("Example: java CollatzUnoptimized 10000");
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

        System.out.println("Running Unoptimized Collatz for x = " + x);

        long numberWithMaxLength = 0;
        int maxLength = 0;

        long startTime = System.nanoTime();

        for (long i = 1; i <= x; i++) {
            int currentLength = getCollatzLength(i);
            if (currentLength > maxLength) {
                maxLength = currentLength;
                numberWithMaxLength = i;
            }
        }

        long endTime = System.nanoTime();
        long durationMillis = TimeUnit.NANOSECONDS.toMillis(endTime - startTime);

        System.out.println("\n--- Results for Unoptimized Version ---");
        System.out.println("Input x: " + x);
        System.out.println("Smallest number (1 to " + x + ") with the longest Collatz sequence: " + numberWithMaxLength);
        System.out.println("Length of its sequence: " + maxLength);
        System.out.println("Time taken: " + durationMillis + " ms");
    }
}
