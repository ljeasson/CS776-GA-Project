# treeseg.R
# Call this function per eval()
# CHROMOSOME: ALG, P1, P2, P3, ... Pn


library(lidR)
las = readLAS("D:/PointClouds/ferguson/registered/postfire_als_clip/fergusonfire_20180916_TLS_0401_20180822_01_clipped_30.las")
args = commandArgs(trailingOnly = TRUE)
alg <- as.integer(args[1])

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
if (alg == 0) {
  cat("dalponte2016(", as.character(args[2]), ", ", as.character(args[3]), ", th_tree = ", as.character(args[4]), ", th_seed = ", as.character(args[5]), ", th_cr = ", as.character(args[6]), ", max_cr = ", as.character(args[7]), ", ID = 'treeID')")
  
  las = segment_trees(las, dalponte2016(
    chm = as.double(args[2]), # Get CHM with grid_canopy()
    treetops = as.double(args[3]), # Get treetops with find_trees()
    th_tree = as.double(args[4]),
    th_seed = as.double(args[5]),
    th_cr = as.double(args[6]),
    max_cr = as.double(args[7]) ))
}

# watershed(chm, th_tree = 2, tol = 1, ext = 1)
# CHROMOSOME: 1, th_tree, tol, ext
if (alg == 1) {
  cat("watershed(", as.character(args[2]), ", th_tree = ", as.character(args[3]), ", tol = ", as.character(args[4]), ", ext = ", as.character(args[5]),")")
  
  las = segment_trees(las, watershed(
    chm = as.double(args[2]), # Get CHM with grid_canopy()
    th_tree = as.double(args[3]),
    tol = as.double(args[4]),
    ext = as.double(args[5]) ))
}

# mcwatershed(chm, treetops, th_tree = 2, ID = "treeID")
# CHROMOSOME: 2, th_tree
if (alg == 2) {
  cat("mcwatershed(", as.character(args[2]), ", treetops = ", as.character(args[3]), ", th_tree = ", as.character(args[4]), ")")
  
  las = segment_trees(las, watershed(
    chm = as.double(args[2]), # Get CHM with grid_canopy()
    treetops = as.double(args[3]),
    th_tree = as.double(args[4]) ))
}

# li2012(dt1 = 1.5, dt2 = 2, R = 2, Zu = 15, hmin = 2, speed_up = 10)
# CHROMOSOME: 3, dt1, dt2, R, Zu, hmin, speed_up
if (alg == 3) {
  cat("li2012(dt1 = ", as.character(args[2]), ", dt2 = ", as.character(args[3]), ", R = ", as.character(args[4]), ", Zu = ", as.character(args[5]), ", hmin = ", as.character(args[6]), ", speed_up = ", as.character(args[7]), ")")
  
  #las = segment_trees(las, li2012(dt1=1.5, dt2=2, R=2, Zu=15, hmin=2, speed_up=10))
  las = segment_trees(las, li2012(
      dt1 = as.double(args[2]), 
      dt2 = as.double(args[3]),
      R = as.double(args[4]),
      Zu = as.double(args[5]),
      hmin = as.double(args[6]),
      speed_up = as.double(args[7]) ))
}

# silva2016(chm, treetops, max_cr_factor = 0.6, exclusion = 0.3, ID = "treeID")
# CHROMOSOME: 4, max_cr_factor, exclusion
if (alg == 4) {
  cat("silva2016(", as.character(args[2]), ", treetops = ", as.character(args[3]), ", max_cr_factor = ", as.character(args[4]), ", exclusion = ", as.character(args[5]), ")")
  
  las = segment_trees(las, watershed(
    chm = as.double(args[2]), # Get CHM with grid_canopy()
    treetops = as.double(args[3]), # Get treetops with find_trees()
    max_cr_factor = as.double(args[4]),
    exclusion = as.double(args[5]) ))
}

#col = random.colors(200)
#plot(las, color = "treeID", colorPalette = col)