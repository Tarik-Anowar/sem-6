import random
import string

# Target string to match
target_string = "genetic algorithm"

# Population size
population_size = 100

# Mutation rate
mutation_rate = 0.01

def generate_random_string(length):
    """Generate a random string of given length."""
    return ''.join(random.choice(string.ascii_lowercase + ' ') for _ in range(length))

def calculate_fitness(string):
    """Calculate the fitness of a string."""
    fitness = sum(1 for expected, actual in zip(target_string, string) if expected == actual)
    return fitness

def crossover(parent1, parent2):
    """Perform crossover operation."""
    crossover_point = random.randint(0, len(parent1) - 1)
    child = parent1[:crossover_point] + parent2[crossover_point:]
    return child


def mutate(input_string):
    """Mutate a string."""
    mutated_string = ''.join(random.choice(string.ascii_lowercase + ' ') if random.random() < mutation_rate else char for char in input_string)
    return mutated_string



def select_parent(population):
    """Select a parent from the population using roulette wheel selection."""
    fitness_sum = sum(calculate_fitness(individual) for individual in population)
    selection_point = random.uniform(0, fitness_sum)
    current_sum = 0
    for individual in population:
        current_sum += calculate_fitness(individual)
        if current_sum > selection_point:
            return individual

def evolve(population):
    """Evolve the population by performing selection, crossover, and mutation."""
    new_population = []
    for _ in range(population_size):
        parent1 = select_parent(population)
        parent2 = select_parent(population)
        child = crossover(parent1, parent2)
        child = mutate(child)
        new_population.append(child)
    return new_population

# Initialize population
population = [generate_random_string(len(target_string)) for _ in range(population_size)]
print(population)

# generation = 0
# while True:
#     population = evolve(population)
#     best_individual = max(population, key=calculate_fitness)
#     print(f"Generation {generation}: {best_individual} (Fitness: {calculate_fitness(best_individual)})")
#     if best_individual == target_string:
#         print("Target string found!")
#         break
#     generation += 1
