# treeseg.R
# Call this function per eval()
# CHROMOSOME: ALG, P1, P2, P3, ... Pn

options("rgdal_show_exportToProj4_warnings"="none")

library(lidR)
library(rgdal)
library(raster)
#library(EBImage)

# Calculate the canopy height model (CHM) and TREETOPS
las = readLAS("D:/PointClouds/for_lee/clipped_als/001_clipped_30.las")
args <-commandArgs(trailingOnly = TRUE)
alg <- as.integer(args[1])

algo = pitfree(thresholds = c(0,10,20,30,40,50), subcircle = 0.2)
CHM  = grid_canopy(las, 0.5, algo)
TREETOPS <- find_trees(las, lmf(5))

# Optionally smooth the CHM with a 3x3 pixel moving window with a median statistic
ker = matrix(1,3,3)
CHM = focal(CHM, w = ker, fun = median)
CHM = focal(CHM, w = ker, fun = median)


#dalponte2016(
#  chm,  [grid_canopy() or read external file]
#  treetops,  [find_trees() or read shp file]
#  th_tree = 2,  
#  th_seed = 0.45,  [between 0 and 1]
#  th_cr = 0.55,  [between 0 and 1]
#  max_cr = 10,  
#  ID = "treeID"  
#)
if (alg == 0) {
  cat("dalponte2016(chm, treetops, th_tree = ", as.character(args[2]), ", th_seed = ", as.character(args[3]), ", th_cr = ", as.character(args[4]), ", max_cr = ", as.character(args[5]), ", ID = 'treeID')")
  
  las = segment_trees(las, dalponte2016(
    chm = CHM, 
    treetops = TREETOPS, 
    th_tree = as.double(args[2]),
    th_seed = as.double(args[3]),
    th_cr = as.double(args[4]),
    max_cr = as.double(args[5]) ))
}

# watershed(chm, th_tree = 2, tol = 1, ext = 1)
if (alg == 1) {
  cat("watershed(chm, th_tree = ", as.character(args[2]), ", tol = ", as.character(args[6]), ", ext = ", as.character(args[7]),")")
  
  las = segment_trees(las, watershed(
    chm = CHM,
    th_tree = as.double(args[2]),
    tol = as.double(args[3]),
    ext = as.double(args[4]) ))
}

# li2012(dt1 = 1.5, dt2 = 2, R = 2, Zu = 15, hmin = 2, speed_up = 10)
if (alg == 2) {
  cat("li2012(dt1 = ", as.character(args[8]), ", dt2 = ", as.character(args[9]), ", R = ", as.character(args[10]), ", Zu = ", as.character(args[11]), ", hmin = ", as.character(args[12]), ", speed_up = ", as.character(args[13]), ")")
  
  las = segment_trees(las, li2012(
    dt1 = as.double(args[2]), 
    dt2 = as.double(args[3]),
    R = as.double(args[4]),
    Zu = as.double(args[5]),
    hmin = as.double(args[6]),
    speed_up = as.double(args[7]) ))
}

# silva2016(chm, treetops, max_cr_factor = 0.6, exclusion = 0.3, ID = "treeID")
if (alg == 3) {
  cat("silva2016(chm, treetops, max_cr_factor = ", as.character(args[14]), ", exclusion = ", as.character(args[15]), ")")
  
  las = segment_trees(las, watershed(
    chm = CHM,
    treetops = TREETOPS,
    max_cr_factor = as.double(args[2]),
    exclusion = as.double(args[3]) ))
}


# remove points that are not assigned to a tree
trees = lasfilter(las, !is.na(treeID))

# Calculate tree metrics and convex hulls
metric = tree_metrics(las, .stdtreemetrics)
hulls  = tree_hulls(las)
hulls@data = dplyr::left_join(hulls@data, metric@data)
spplot(hulls, "Z")

# Write to shapefile
writeOGR(obj=hulls, dsn="D:/PointClouds/for_lee/clipped_als", layer="001_clipped_30", driver="ESRI Shapefile", overwrite_layer = TRUE)

# Compare shape files