# treeseg.R
# Call this function per eval()
# CHROMOSOME: [th_tree, th_seed, th_cr, max_cr]

options("rgdal_show_exportToProj4_warnings"="none")

library(lidR)
library(rgdal)
library(raster)
library(sf)

pa <- array(numeric(),c(3,0,0)) 
th <- array(numeric(),c(3,0,0)) 

# Calculate the canopy height model (CHM) and TREETOPS
las = readLAS("D:/PointClouds/for_lee/clipped_als/001_clipped_30.las")
args <-commandArgs(trailingOnly = TRUE)

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
cat("dalponte2016(chm, treetops, th_tree = ", as.character(args[1]), ", th_seed = ", as.character(args[2]), ", th_cr = ", as.character(args[3]), ", max_cr = ", as.character(args[4]), ", ID = 'treeID')")
las = segment_trees(las, dalponte2016(
    chm = CHM, 
    treetops = TREETOPS, 
    th_tree = as.double(args[1]),
    th_seed = as.double(args[2]),
    th_cr = as.double(args[3]),
    max_cr = as.double(args[4]) ))


# remove points that are not assigned to a tree
trees = lasfilter(las, !is.na(treeID))

# Calculate tree metrics and convex hulls
metric = tree_metrics(las, .stdtreemetrics)
hulls  = tree_hulls(las)
print(hulls)

hulls@data = dplyr::left_join(hulls@data, metric@data)
#print(hulls@data)
print("-----------------------------------------------------------------")


# Convert ground truth CSV to SF
ground_truths <- st_read("D:/PointClouds/for_lee/ground_truth/shp/TLS_0001_20170531_01_clipped_30_height_norm_1.345_1.395.shp")
ground_truths_sf <- st_as_sf(ground_truths, coords = c("x", "y", "area", "radius"), crs = 3310)
st_crs(ground_truths_sf) <- "+proj=aea +lat_1=34 +lat_2=40.5 +lat_0=0 +lon_0=-120 +x_0=0 +y_0=-4000000 +ellps=GRS80 +towgs84=0,0,0,0,0,0,0 +units=m +no_defs"

# Convert hull data to SF
hulls_sf <- st_as_sf(hulls, coords = c("x", "y", "area", "radius"), crs = 3310)
st_crs(hulls_sf) <- "+proj=aea +lat_1=34 +lat_2=40.5 +lat_0=0 +lon_0=-120 +x_0=0 +y_0=-4000000 +ellps=GRS80 +towgs84=0,0,0,0,0,0,0 +units=m +no_defs"

print("-----------------------------------------------------------------")

# TODO: Detect presence/absence detection with st_intersects()
intersects <- st_intersects(ground_truths_sf, hulls_sf)
overlap = sapply(X=intersects, FUN=function(X) length(X)>1)
cluster_id = sapply(X=intersects, FUN=function(X) paste(X, collapse=' '))

# Count number of overlaps
overlaps_num = 0
overlaps_frac = 0
for (i in 1:length(intersects)){
  if (length(intersects[[i]]) > 0){
    overlaps_num = overlaps_num + 1 
  }
}
overlaps_frac = overlaps_num / length(intersects)
pa[1] = overlaps_num


# TODO: Detect height difference

# TODO: Return as vector of fitness values
