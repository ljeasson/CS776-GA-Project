import matplotlib.pyplot as plt
import numpy as np
import math 
import sys

def main(argv):

    # Read outfile
    fr = open("outfile", "r")
    fr = fr.read()
    lines = fr.split("\n") 

    # Write to file
    #fileName = str(argv[0])
    #fw = open("figs/"+fileName+"_data.txt", "w")

    ''' PERFORMANCE GRAPHS '''
    ''' AVG-AVG FITNESS and MAX-AVG FITNESS '''
    graph_avg_fitness = {}
    graph_max_fitness = {}
    
    # Get average and maximum fitness per generations
    for line in lines:
        line = line.replace(" ", "")
        data = line.split("\t")
        if (len(data) > 1):
            graph_avg_fitness[data[0]] = graph_avg_fitness.get(data[0], 0) + float(data[2])
            graph_max_fitness[data[0]] = graph_max_fitness.get(data[0], 0) + float(data[3])

    # Get average average fitness for each generation
    # Divide total average fitness by 5 iterations
    for key, value in graph_avg_fitness.items():
        graph_avg_fitness[key] = value/5.0
	    
    # Get average maximum fitness for each generation
    # Divide total average fitness by 5 iterations
    for key, value in graph_max_fitness.items():
        graph_max_fitness[key] = value/5.0

    # Sort dictionaries into lists
    generations = list(graph_avg_fitness.keys())
    average_fitnesses = list(graph_avg_fitness.values())
    maximum_fitnesses = list(graph_max_fitness.values())
            
    # LINE PLOT - average avg and max fitness for each generation
    plt.plot(generations, average_fitnesses, "-b", label="Avg Fitness")
    plt.plot(generations, maximum_fitnesses, "-r", label="Max Fitness")
    plt.legend(loc="upper left")

    plt.xticks(np.arange(0, 10, 1))
    #plt.yticks(np.arange(min(average_fitnesses), max(maximum_fitnesses), max(maximum_fitnesses)-max(average_fitnesses)))
    plt.yticks(np.arange(10, 11, 0.05))

    plt.xlabel("Generation")
    plt.ylabel("Average Fitness")
    #plt.title('Genetic Algorithm - ' + fileName + '\nAverage Fitness per Generation')
    plt.title('Genetic Algorithm\nAverage Fitness per Generation')
    plt.legend(loc="lower right")

    #plt.savefig("figs/"+fileName+"_fitness.png")
    plt.savefig("C:/Users/Lee/Desktop/CS776-GA-Project/GA_watershed/figs/fitness.png")
    plt.draw()
    plt.waitforbuttonpress(0)
    plt.close()
    


    # Read data file
    fr = open("data.txt", "r")
    fr = fr.read()
    lines = fr.split("\n") 

    ''' PARAMETERS '''
    graph_parameters = {}

    # Get (fitness: parameters)
    for i in range(0,len(lines)-1,3):
        parameters = lines[i].split("\t")
        fitness = float(lines[i+1].split(" ")[1])
        graph_parameters[fitness] = graph_parameters.get(fitness, parameters)
    
    collabel=("Fitness", "Parameters (th_tree, th_seed, th_cr, max_cr)")
    rowlabel=("   1   ","   2   ","   3   ","   4   ","   5   ")
    plt.axis('tight')
    plt.axis('off')
    
    '''
    table = plt.table(cellText=cell_text, cellColours=colors[0],
          rowColours=colors[1], rowLabels=row_labels,
          colColours=colors[2], colLabels=columns,
          colWidths=[0.3 for x in columns],
          bbox=[0.0, -1.3, 1.0, 1.0], cellLoc='center')
    '''
    the_table = plt.table(cellText=list(sorted(graph_parameters.items(), reverse=True))[0:5], 
                            rowLabels=rowlabel,
                            colLabels=collabel, 
                            colWidths=[0.15, 0.4], 
                            loc='center')
    the_table.set_fontsize(20)
    the_table.scale(2, 2)
    plt.savefig("C:/Users/Lee/Desktop/CS776-GA-Project/GA_watershed/figs/rankings.png")
    plt.draw()
    plt.waitforbuttonpress(0)
    plt.close()
    
    
    '''
    x = ['Nuclear', 'Hydro', 'Gas', 'Oil', 'Coal', 'Biofuel']
    energy = [5, 6, 15, 22, 24, 8]

    x_pos = [i for i, _ in enumerate(x)]

    plt.bar(x_pos, energy, color='green')
    plt.xlabel("Energy Source")
    plt.ylabel("Energy Output (GJ)")
    plt.title("Energy output from various fuel sources")

    plt.xticks(x_pos, x)

    plt.show()
    '''
    

if __name__ == "__main__":
   main(sys.argv[1:])