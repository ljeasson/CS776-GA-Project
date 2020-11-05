
import random
import Options
from Population import Population

class GA:

	def __init__(self):
		self.options = Options.Options()
		random.seed(self.options.randomSeed)

	def Init(self):
		self.parent = Population(self.options)
		self.parent.evaluate()
		self.parent.statistics()
		self.parent.report(0)
		self.child = Population(self.options)
		return

	def Run(self):
		for	i in range(1, self.options.maxGen):
			self.parent.generation(self.child)
			self.child.evaluate()
			self.child.statistics()
			self.child.report(i)

			tmp = self.parent
			self.parent = self.child
			self.child = tmp

		self.parent.printPop()
		return


if __name__ == "__main__":
	ga = GA()
	ga.Init()
	ga.Run()
