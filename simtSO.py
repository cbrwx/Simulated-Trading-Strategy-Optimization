import numpy as np

def simulate_trade(long_entry, short_entry, tp_pct, sl_pct, num_simulations):
    long_increases = 0
    long_decreases = 0
    short_increases = 0
    short_decreases = 0

    for _ in range(num_simulations):
        # Simulate price movement for long position
        long_exit = long_entry * (1 + np.random.uniform(-sl_pct, tp_pct))
        if long_exit > long_entry:
            long_increases += 1
        elif long_exit < long_entry:
            long_decreases += 1

        # Simulate price movement for short position
        short_exit = short_entry * (1 - np.random.uniform(-sl_pct, tp_pct))
        if short_exit > short_entry:
            short_increases += 1
        elif short_exit < short_entry:
            short_decreases += 1

    prob_long_increase = long_increases / num_simulations
    prob_long_decrease = long_decreases / num_simulations
    prob_short_increase = short_increases / num_simulations
    prob_short_decrease = short_decreases / num_simulations

    return (prob_long_increase, prob_long_decrease), (prob_short_increase, prob_short_decrease)

# Original values
long_entry = 1.02
short_entry = 0.98
tp_pct = 0.02
sl_pct = 0.01
num_simulations = 100000

# Define the percentage variation around the original values (adjust as needed)
variation_percentage = 0.02

# Calculate the range for random variation
long_variation_range = long_entry * variation_percentage
short_variation_range = short_entry * variation_percentage

# Randomly generate entry prices within the specified range for both positions with variation
long_entries = np.random.uniform(long_entry - long_variation_range, long_entry + long_variation_range, num_simulations)
short_entries = np.random.uniform(short_entry - short_variation_range, short_entry + short_variation_range, num_simulations)

# Initialize variables to track the best probabilities
best_long_probs = None
best_short_probs = None
best_total_prob = 0.0

# Simulate trades for each set of entry prices and find the best probability pair
for i, (long_entry, short_entry) in enumerate(zip(long_entries, short_entries)):
    long_probs, short_probs = simulate_trade(long_entry, short_entry, tp_pct, sl_pct, num_simulations)
    total_prob = long_probs[0] + short_probs[0]  # Sum of probabilities of increases
    
    if total_prob > best_total_prob:
        best_total_prob = total_prob
        best_long_probs = long_probs
        best_short_probs = short_probs
    
    print(f"Variation {i + 1} - Entry Prices: Long: {long_entry:.2f}, Short: {short_entry:.2f}")
    print(f"Long Position - Probability of increase: {long_probs[0]:.2%}, Probability of decrease: {long_probs[1]:.2%}")
    print(f"Short Position - Probability of increase: {short_probs[0]:.2%}, Probability of decrease: {short_probs[1]:.2%}")
    print()

# Print the best probability pair
print("Best Probability Pair:")
print(f"Long Position - Probability of increase: {best_long_probs[0]:.2%}, Probability of decrease: {best_long_probs[1]:.2%}")
print(f"Short Position - Probability of increase: {best_short_probs[0]:.2%}, Probability of decrease: {best_short_probs[1]:.2%}")
