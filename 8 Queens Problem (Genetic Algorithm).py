# -*- coding: utf-8 -*-
"""22L-6721-6J-A2-Q2.ipynb

Automatically generated by Colab.

Original file is located at
    https://colab.research.google.com/drive/13y3lZVO-GE_7jQ8PrrXUWFhtSzal_QVS
"""

import random

ProblemSize = 8
PopulationSize = 500
Generations = 100

# Function to print board
def printBoard(state):
  board = [[' ' for _ in range(ProblemSize)] for _ in range(ProblemSize)]
  i = 0
  for row in state:
    board[row][i] = 'Q'
    i += 1
  for row in board:
    print(row)

# Function that return fitness value of a state i.e. number of attacking queens
def fitnessValue(state):
    max_pair = len(state) * (len(state) - 1) / 2

    count = 0
    for i in range(len(state)):
        for j in range(i + 1, len(state)):
            if state[i] == state[j]:
                count += 1
            elif abs(state[i] - state[j]) == abs(i - j):
                count += 1
    return max_pair - count

# Function that generate random population of specified size
def generateInitialPopulation():
  population = set()
  while len(population) < PopulationSize:
    indiviual = tuple(random.sample(range(ProblemSize), ProblemSize))
    population.add(indiviual)

  return list(population)

# Tournament selection
def tournamentSelection(population, count):
  selected_individuals = set()
  while len(selected_individuals) < count:
    tournament_participants = random.choices(population, k = 5)
    best_one = max(tournament_participants, key=lambda x:fitnessValue(x))
    selected_individuals.add(best_one)

  return list(selected_individuals)

# Roulette wheel selection
def rouletteWheelSelection(population, count):
  selected_individuals = set()
  total_fitness = sum(fitnessValue(individual) for individual in population)
  while len(selected_individuals) < count:
    random_fitness = random.uniform(0, total_fitness)
    current_fitness = 0
    for individual in population:
      current_fitness += fitnessValue(individual)
      if current_fitness >= random_fitness:
        selected_individuals.add(individual)
        break

  return list(selected_individuals)

# Function to perform crossover
def crossover(one, two):
  flag = True
  while flag:
    first = random.randint(1, ProblemSize - 1)
    second = random.randint(1, ProblemSize - 1)
    if(first < second):
      flag = False

  child_one = one[:first] + two[first:second] + one[second:]
  child_two = two[:first] + one[first:second] + two[second:]

  return (child_one,child_two)

# Function to perform crossover
def performCrossover(population, count):
  result = set()
  while len(result) < count:
    parents = tournamentSelection(population, 2)
    childs = crossover(parents[0], parents[1])
    result.add(childs[0])
    result.add(childs[1])

  return list(result)

# Function to perform mutation on indiviual
def mutation(individual):
  new_child = list(individual)
  new_child[random.randint(0,len(new_child )- 1)] = random.randint(0,ProblemSize - 1)

  return new_child

# Function to perfrom mutation
def performMutation(population, count):
  result = []
  selected_parents = tournamentSelection(population, count)
  for parent in selected_parents:
    child = mutation(parent)
    result.append(child)

  return result

selection_range = int(0.25 * PopulationSize)
crossover_range = int(0.65 * PopulationSize)
mutation_range = int(0.10 * PopulationSize)
flag = False

population = generateInitialPopulation()
print("Iniital Population: ")
for indiviual in population:
  print(indiviual,fitnessValue(indiviual))
solution = max(population, key=lambda x:fitnessValue(x))
if fitnessValue(solution) == 28:
  flag = True

if not flag:
  for i in range(Generations):
    next_generation = rouletteWheelSelection(population, selection_range)
    next_generation.extend(performCrossover(population, crossover_range))
    next_generation.extend(performMutation(population, mutation_range))
    print("Generation " + str(i) + ": ")
    for indiviual in next_generation:
      print(indiviual,fitnessValue(indiviual))

    solution = max(next_generation, key=lambda x:fitnessValue(x))
    if fitnessValue(solution) == 28:
      flag = True
      break

if not flag:
  print("Solution not found")
else:
  print("Solution found")
  printBoard(solution)
  print(solution,fitnessValue(solution))

