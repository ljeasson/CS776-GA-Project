import matplotlib.pyplot as plt
import numpy as np
import math 
import sys


def performance_graph(alg, outfile):
    # PERFORMANCE GRAPHS ========================================================================
    # Read outfile
    fr = open(outfile, "r")
    fr = fr.read()
    lines = fr.split("\n") 

    # Get average and maximum fitness per generations
    graph_avg_fitness = {}  # AVG-AVG FITNESS
    graph_max_fitness = {}  # MAX-AVG FITNESS

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
    #plt.yticks(np.arange(0, 2, 0.1))
    plt.yticks(np.arange(min(average_fitnesses), max(maximum_fitnesses), 
                        ( max(maximum_fitnesses) - min(average_fitnesses)) / 10.0 ))

    plt.xlabel("Generation")
    plt.ylabel("Average Fitness")
    #plt.title('Genetic Algorithm - ' + fileName + '\nAverage Fitness per Generation')
    plt.title(str(alg) + ' - Genetic Algorithm\nAverage Fitness per Generation')
    plt.legend(loc="lower right")

    #plt.savefig("figs/"+fileName+"_fitness.png")
    plt.savefig("C:/Users/Lee/Desktop/CS776-GA-Project/figs/"+str(alg)+"_fitness.png")
    plt.draw()
    plt.waitforbuttonpress(0)
    plt.close()


def get_overlaps(alg, ls):
    # WORST, AVERAGE, MAX OVERLAP ===============================================================
    # Read overlap file
    fr = open(ls, "r")
    fr = fr.read()
    lines = fr.split("\n")
    
    ls_001_vals = []
    ls_002_vals = []
    ls_017_vals = []
    ls_022_vals = []
    ls_026_vals = []
    ls_121_vals = []
    num_groups = 0
    
    for i in range(0,len(lines)-1,7):
        ls_001 = lines[i].split(" ")
        ls_001 = [i for i in ls_001 if i != '']
        ls_001 = [int(i) for i in ls_001]
        ls_001_vals.append(min(ls_001))
        ls_001_vals.append(max(ls_001))
        ls_001_vals.append(sum(ls_001)/len(ls_001))

        ls_002 = lines[i+1].split(" ")
        ls_002 = [i for i in ls_002 if i != '']
        ls_002 = [int(i) for i in ls_002]
        ls_002_vals.append(min(ls_002))
        ls_002_vals.append(max(ls_002))
        ls_002_vals.append(sum(ls_002)/len(ls_002))
        
        ls_017 = lines[i+2].split(" ")
        ls_017 = [i for i in ls_017 if i != '']
        ls_017 = [int(i) for i in ls_017]
        ls_017_vals.append(min(ls_017))
        ls_017_vals.append(max(ls_017))
        ls_017_vals.append(sum(ls_017)/len(ls_017))
        
        ls_022 = lines[i+3].split(" ")
        ls_022 = [i for i in ls_022 if i != '']
        ls_022 = [int(i) for i in ls_022]
        ls_022_vals.append(min(ls_022))
        ls_022_vals.append(max(ls_022))
        ls_022_vals.append(sum(ls_022)/len(ls_022))
        
        ls_026 = lines[i+4].split(" ")
        ls_026 = [i for i in ls_026 if i != '']
        ls_026 = [int(i) for i in ls_026]
        ls_026_vals.append(min(ls_026))
        ls_026_vals.append(max(ls_026))
        ls_026_vals.append(sum(ls_026)/len(ls_026))

        ls_121 = lines[i+5].split(" ")
        ls_121 = [i for i in ls_121 if i != '']
        ls_121 = [int(i) for i in ls_121]
        ls_121_vals.append(min(ls_121))
        ls_121_vals.append(max(ls_121))
        ls_121_vals.append(sum(ls_121)/len(ls_121))

        num_groups += 1
 
    global OVERLAPS
    OVERLAPS['TLS_0001'].append([ls_001_vals[0], ls_001_vals[1], ls_001_vals[2]])
    OVERLAPS['TLS_0002'].append([ls_002_vals[0], ls_002_vals[1], ls_002_vals[2]])
    OVERLAPS['TLS_0017'].append([ls_017_vals[0], ls_017_vals[1], ls_017_vals[2]])
    OVERLAPS['TLS_0022'].append([ls_022_vals[0], ls_022_vals[1], ls_022_vals[2]])
    OVERLAPS['TLS_0026'].append([ls_026_vals[0], ls_026_vals[1], ls_026_vals[2]])
    OVERLAPS['TLS_0121'].append([ls_121_vals[0], ls_121_vals[1], ls_121_vals[2]])

    
def rankings(alg, parameters):
    # GA PARAMETER RANKINGS =====================================================================
    # Read parameters file
    fr = open(parameters, "r")
    fr = fr.read()
    lines = fr.split("\n") 
    
    graph_parameters = {}
    for i in range(0,len(lines)-1,3):
        parameters = lines[i].split("\t")
        fitness = float(lines[i+1])
        graph_parameters[tuple(parameters)] = fitness

    graph_parameters = dict(sorted(graph_parameters.items(), key=lambda item: item[1], reverse=True))


    collabel=("Parameters", "Fitness")
    rowlabel=(" 1 "," 2 "," 3 "," 4 "," 5 ")
    plt.axis('tight')
    plt.axis('off')
    plt.title(str(alg) + '\nParameter Rankings')

        
    the_table = plt.table(cellText=list(graph_parameters.items())[0:5], 
                            rowLabels=rowlabel,
                            colLabels=collabel, 
                            colWidths=[0.3, 0.1], 
                            loc='center')
    the_table.set_fontsize(20)
    the_table.scale(2, 2)
    plt.savefig("C:/Users/Lee/Desktop/CS776-GA-Project/figs/"+str(alg)+"_rankings.png")
    plt.draw()
    plt.waitforbuttonpress(0)
    plt.close()


def overlap_graph(plot):
    N = 4
    ls_min = (OVERLAPS.get(plot)[0][0], OVERLAPS.get(plot)[1][0], OVERLAPS.get(plot)[2][0], OVERLAPS.get(plot)[3][0])
    ls_avg = (OVERLAPS.get(plot)[0][1], OVERLAPS.get(plot)[1][1], OVERLAPS.get(plot)[2][1], OVERLAPS.get(plot)[3][1])
    ls_max = (OVERLAPS.get(plot)[0][2], OVERLAPS.get(plot)[1][2], OVERLAPS.get(plot)[2][2], OVERLAPS.get(plot)[3][2])

    ind = np.arange(N) 
    width = 0.15       
    plt.bar(ind, ls_min, width, label='Min')
    plt.bar(ind + width, ls_avg, width, label='Average')
    plt.bar(ind + 2*width, ls_max, width, label='Max')

    plt.xlabel("ALGORITHM")
    plt.ylabel('OVERLAP COUNT')
    plt.title(str(plot)+'.las\nAverage Overlap Count')

    plt.xticks(ind + width / 2, ('dalponte2016', 'li2012', 'silva2016', 'watershed'))
    plt.legend(loc='best')
    
    plt.savefig("C:/Users/Lee/Desktop/CS776-GA-Project/figs/"+str(plot)+"_overlaps.png")
    plt.draw()
    plt.waitforbuttonpress(0)
    plt.close()



if __name__ == "__main__":
    OVERLAPS = {"TLS_0001": [], "TLS_0002": [], "TLS_0017": [], "TLS_0022": [], "TLS_0026": [], "TLS_0121": []}
        
    performance_graph("dalponte2016", "C:/Users/Lee/Desktop/CS776-GA-Project/GA_dalponte2016/outfile")
    get_overlaps("dalponte2016", "C:/Users/Lee/Desktop/CS776-GA-Project/GA_dalponte2016/ls.txt")
    rankings("dalponte2016", "C:/Users/Lee/Desktop/CS776-GA-Project/GA_dalponte2016/parameters.txt")
        
    performance_graph("li2012", "C:/Users/Lee/Desktop/CS776-GA-Project/GA_li2012/outfile")
    get_overlaps("li2012", "C:/Users/Lee/Desktop/CS776-GA-Project/GA_li2012/ls.txt")
    rankings("li2012", "C:/Users/Lee/Desktop/CS776-GA-Project/GA_li2012/parameters.txt")

    performance_graph("silva2016", "C:/Users/Lee/Desktop/CS776-GA-Project/GA_silva2016/outfile")
    get_overlaps("silva2016", "C:/Users/Lee/Desktop/CS776-GA-Project/GA_silva2016/ls.txt")
    rankings("silva2016", "C:/Users/Lee/Desktop/CS776-GA-Project/GA_silva2016/parameters.txt")

    performance_graph("watershed", "C:/Users/Lee/Desktop/CS776-GA-Project/GA_watershed/outfile")
    get_overlaps("watershed", "C:/Users/Lee/Desktop/CS776-GA-Project/GA_watershed/ls.txt")
    rankings("watershed", "C:/Users/Lee/Desktop/CS776-GA-Project/GA_watershed/parameters.txt")

    rankings("silva2016_exhaustive", "C:/Users/Lee/Desktop/CS776-GA-Project/silva_parameters.txt")
    rankings("watershed_exhaustive", "C:/Users/Lee/Desktop/CS776-GA-Project/watershed_parameters.txt")

    for key, value in OVERLAPS.items():
        overlap_graph(key)    