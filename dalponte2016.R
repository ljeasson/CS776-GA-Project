library(lidR)
las = readLAS("D:/PointClouds/ferguson/registered/postfire_als_clip/fergusonfire_20180916_TLS_0401_20180822_01_clipped_30.las")
args = commandArgs(trailingOnly = TRUE)

#dalponte2016(
#  chm,  [grid_canopy() or read external file]
#  treetops,  [find_trees() or read shp file]
#  th_tree = 2,  
#  th_seed = 0.45,  [between 0 and 1]
#  th_cr = 0.55,  [between 0 and 1]
#  max_cr = 10,  
#  ID = "treeID"  []
#)
# CHROMOSOME: 0, th_tree, th_seed, th_cr, max_cr 
cat("dalponte2016(", as.character(args[2]), ", ", as.character(args[3]), ", th_tree = ", as.character(args[4]), ", th_seed = ", as.character(args[5]), ", th_cr = ", as.character(args[6]), ", max_cr = ", as.character(args[7]), ", ID = 'treeID')")
  
las = segment_trees(las, dalponte2016(
  chm = as.double(args[2]), # Get CHM with grid_canopy()
  treetops = as.double(args[3]), # Get treetops with find_trees()
  th_tree = as.double(args[4]),
  th_seed = as.double(args[5]),
  th_cr = as.double(args[6]),
  max_cr = as.double(args[7]) )
)