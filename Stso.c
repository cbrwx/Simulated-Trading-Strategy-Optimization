// Just doing some portability tests. cbrwx
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void simulate_trade(float long_entry, float short_entry, float tp_pct, float sl_pct, int num_simulations, float *prob_long_increase, float *prob_long_decrease, float *prob_short_increase, float *prob_short_decrease) {
    int long_increases = 0, long_decreases = 0, short_increases = 0, short_decreases = 0;
    for (int i = 0; i < num_simulations; ++i) {
        // Simulate price movement for long position
        float long_exit = long_entry * (1 + ((float)rand() / RAND_MAX * (tp_pct - (-sl_pct)) + (-sl_pct)));
        if (long_exit > long_entry) {
            long_increases++;
        } else if (long_exit < long_entry) {
            long_decreases++;
        }

        // Simulate price movement for short position
        float short_exit = short_entry * (1 - ((float)rand() / RAND_MAX * (tp_pct - (-sl_pct)) + (-sl_pct)));
        if (short_exit > short_entry) {
            short_increases++;
        } else if (short_exit < short_entry) {
            short_decreases++;
        }
    }

    *prob_long_increase = (float)long_increases / num_simulations;
    *prob_long_decrease = (float)long_decreases / num_simulations;
    *prob_short_increase = (float)short_increases / num_simulations;
    *prob_short_decrease = (float)short_decreases / num_simulations;
}

int main() {
    srand(time(0)); // Seed random number generator
    int num_simulations = 100000;
    float long_entry = 1.02, short_entry = 0.98, tp_pct = 0.02, sl_pct = 0.01;
    float variation_percentage = 0.02;

    float long_variation_range = long_entry * variation_percentage;
    float short_variation_range = short_entry * variation_percentage;

    float best_long_probs[2], best_short_probs[2], best_total_prob = 0.0;

    for (int i = 0; i < num_simulations; ++i) {
        float long_entry_var = long_entry + ((float)rand() / RAND_MAX * (long_variation_range - (-long_variation_range)) + (-long_variation_range));
        float short_entry_var = short_entry + ((float)rand() / RAND_MAX * (short_variation_range - (-short_variation_range)) + (-short_variation_range));

        float prob_long_increase, prob_long_decrease, prob_short_increase, prob_short_decrease;
        simulate_trade(long_entry_var, short_entry_var, tp_pct, sl_pct, num_simulations, &prob_long_increase, &prob_long_decrease, &prob_short_increase, &prob_short_decrease);
        float total_prob = prob_long_increase + prob_short_increase;

        if (total_prob > best_total_prob) {
            best_total_prob = total_prob;
            best_long_probs[0] = prob_long_increase;
            best_long_probs[1] = prob_long_decrease;
            best_short_probs[0] = prob_short_increase;
            best_short_probs[1] = prob_short_decrease;
        }

        printf("Variation %d - Entry Prices: Long: %.2f, Short: %.2f\n", i + 1, long_entry_var, short_entry_var);
        printf("Long Position - Probability of increase: %.2f%%, Probability of decrease: %.2f%%\n", prob_long_increase * 100, prob_long_decrease * 100);
        printf("Short Position - Probability of increase: %.2f%%, Probability of decrease: %.2f%%\n\n", prob_short_increase * 100, prob_short_decrease * 100);
    }

    printf("Best Probability Pair:\n");
    printf("Long Position - Probability of increase: %.2f%%, Probability of decrease: %.2f%%\n", best_long_probs[0] * 100, best_long_probs[1] * 100);
    printf("Short Position - Probability of increase: %.2f%%, Probability of decrease: %.2f%%\n", best_short_probs[0] * 100, best_short_probs[1] * 100);

    return 0;
}
