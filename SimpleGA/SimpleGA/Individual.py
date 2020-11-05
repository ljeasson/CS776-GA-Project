import random
import Utils

class Individual:

	def __init__(self, options):
		self.chromosome = []
		self.chromosomeLength = options.chromosomeLength
		self.fitness = -1
		self.objective = -1
		for i in range(options.chromosomeLength):
			self.chromosome.append(random.choice((0, 1)))

	def mutate(self, options):
		for i in range(options.chromosomeLength):
			if Utils.flip(options.pMut):
				self.chromosome[i] = 1 - self.chromosome[i]

