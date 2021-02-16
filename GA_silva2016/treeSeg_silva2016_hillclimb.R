# treeseg.R
# Call this function per eval()
# CHROMOSOME: [max_cr_factor, exclusion = 0.3]

options(warn=-1)
options("rgdal_show_exportToProj4_warnings"="none")

# Open a file to send messages to
zz <- file("messages.Rout", open = "wt")
# Divert messages to that file
sink(zz, type = "message")
message("not gonna show up in console")

suppressWarnings(suppressMessages(library(lidR)))
suppressWarnings(suppressMessages(library(rgdal)))
suppressWarnings(suppressMessages(library(raster)))
suppressWarnings(suppressMessages(library(sf)))

library(lidR)
library(rgdal)
library(raster)
library(sf)

SEGMENT <- function(las, ground_truths, vals)
{
  # Calculate the canopy height model (CHM) and TREETOPS
  args <-commandArgs(trailingOnly = TRUE)
  
  algo = pitfree(thresholds = c(0,10,20,30,40,50), subcircle = 0.2)
  CHM  = grid_canopy(las, 0.5, algo)
  TREETOPS <- find_trees(las, lmf(5))
  
  # Optionally smooth the CHM with a 3x3 pixel moving window with a median statistic
  ker = matrix(1,3,3)
  CHM = focal(CHM, w = ker, fun = median)
  CHM = focal(CHM, w = ker, fun = median)
  
  # silva2016(
  #    chm,
  #    treetops,
  #    max_cr_factor = 0.6,
  #    exclusion = 0.3,
  #    ID = "treeID")
  cat("silva2016(chm, treetops, max_cr_factor = ", as.character(args[1]), ", exclusion = ", as.character(args[2]), ")")
    
  las = segment_trees(las, silva2016(
    chm = CHM,
    treetops = TREETOPS,
    max_cr_factor = as.double(args[1]),
    exclusion = as.double(args[2]) ))
  
  
  
  # remove points that are not assigned to a tree
  trees = lasfilter(las, !is.na(treeID))
  
  # Calculate tree metrics and convex hulls
  metric = tree_metrics(las, .stdtreemetrics)
  hulls  = tree_hulls(las)
  print(hulls)
  
  hulls@data = dplyr::left_join(hulls@data, metric@data)
  #print(hulls@data)
  
  
  # Convert ground truth SHP to SF
  ground_truths_sf <- st_as_sf(ground_truths, coords = c("x", "y", "area", "radius"), crs = 3310)
  st_crs(ground_truths_sf) <- "+proj=aea +lat_1=34 +lat_2=40.5 +lat_0=0 +lon_0=-120 +x_0=0 +y_0=-4000000 +ellps=GRS80 +towgs84=0,0,0,0,0,0,0 +units=m +no_defs"
  
  # Convert hull data to SF
  hulls_sf <- st_as_sf(hulls, coords = c("x", "y", "area", "radius"), crs = 3310)
  st_crs(hulls_sf) <- "+proj=aea +lat_1=34 +lat_2=40.5 +lat_0=0 +lon_0=-120 +x_0=0 +y_0=-4000000 +ellps=GRS80 +towgs84=0,0,0,0,0,0,0 +units=m +no_defs"
  
  
  # Detect presence/absence detection with st_intersects()
  intersects <- st_intersects(ground_truths_sf, hulls_sf)
  overlap = sapply(X=intersects, FUN=function(X) length(X)>1)
  cluster_id = sapply(X=intersects, FUN=function(X) paste(X, collapse=' '))
  
  # Count number of overlaps
  overlap_length <<- length(intersects)
  overlap_num = 0
  overlap_frac = 0
  for (i in 1:overlap_length){
    if (length(intersects[[i]]) > 0){
      overlap_num = overlap_num + 1 
    }
  }
  if (vals == "001"){ls_001_vals <<- c(ls_001_vals, overlap_num)}
  if (vals == "002"){ls_002_vals <<- c(ls_002_vals, overlap_num)}
  if (vals == "017"){ls_017_vals <<- c(ls_017_vals, overlap_num)}
  if (vals == "022"){ls_022_vals <<- c(ls_022_vals, overlap_num)}
  if (vals == "026"){ls_026_vals <<- c(ls_026_vals, overlap_num)}
  if (vals == "121"){ls_121_vals <<- c(ls_121_vals, overlap_num)}
  
  overlap_frac = overlap_num / overlap_length
  overlap_frac_total <<- overlap_frac_total + overlap_frac
  
  cat("Overlap Num: ", as.character(overlap_num), "\n")
  cat("Overlap Len: ", as.character(overlap_length), "\n")
  cat("Overlap Frac: ", as.character(overlap_frac), "\n")
  
  print("-----------------------------------------------------------------")
}

ls_001 <- c("D:/PointClouds/for_lee/clipped_trees_circle/plot_001_tree_2.las",
            "D:/PointClouds/for_lee/clipped_trees_circle/plot_001_tree_21.las",
            "D:/PointClouds/for_lee/clipped_trees_circle/plot_001_tree_23.las",
            "D:/PointClouds/for_lee/clipped_trees_circle/plot_001_tree_29.las",
            "D:/PointClouds/for_lee/clipped_trees_circle/plot_001_tree_30.las",
            "D:/PointClouds/for_lee/clipped_trees_circle/plot_001_tree_34.las",
            "D:/PointClouds/for_lee/clipped_trees_circle/plot_001_tree_36.las",
            "D:/PointClouds/for_lee/clipped_trees_circle/plot_001_tree_37.las",
            "D:/PointClouds/for_lee/clipped_trees_circle/plot_001_tree_39.las",
            "D:/PointClouds/for_lee/clipped_trees_circle/plot_001_tree_48.las",
            "D:/PointClouds/for_lee/clipped_trees_circle/plot_001_tree_49.las",
            "D:/PointClouds/for_lee/clipped_trees_circle/plot_001_tree_67.las",
            "D:/PointClouds/for_lee/clipped_trees_circle/plot_001_tree_70.las",
            "D:/PointClouds/for_lee/clipped_trees_circle/plot_001_tree_76.las",
            "D:/PointClouds/for_lee/clipped_trees_circle/plot_001_tree_78.las")

ls_002 <- c("D:/PointClouds/for_lee/clipped_trees_circle/plot_002_tree_79.las",
            "D:/PointClouds/for_lee/clipped_trees_circle/plot_002_tree_90.las",
            "D:/PointClouds/for_lee/clipped_trees_circle/plot_002_tree_94.las",
            "D:/PointClouds/for_lee/clipped_trees_circle/plot_002_tree_95.las",
            "D:/PointClouds/for_lee/clipped_trees_circle/plot_002_tree_110.las",
            "D:/PointClouds/for_lee/clipped_trees_circle/plot_002_tree_113.las")

ls_017 <- c("D:/PointClouds/for_lee/clipped_trees_circle/plot_017_tree_126.las",
            "D:/PointClouds/for_lee/clipped_trees_circle/plot_017_tree_132.las",
            "D:/PointClouds/for_lee/clipped_trees_circle/plot_017_tree_141.las",
            "D:/PointClouds/for_lee/clipped_trees_circle/plot_017_tree_142.las",
            "D:/PointClouds/for_lee/clipped_trees_circle/plot_017_tree_149.las",
            "D:/PointClouds/for_lee/clipped_trees_circle/plot_017_tree_151.las",
            "D:/PointClouds/for_lee/clipped_trees_circle/plot_017_tree_155.las",
            "D:/PointClouds/for_lee/clipped_trees_circle/plot_017_tree_159.las")

ls_022 <- c("D:/PointClouds/for_lee/clipped_trees_circle/plot_022_tree_171.las",
            "D:/PointClouds/for_lee/clipped_trees_circle/plot_022_tree_177.las",
            "D:/PointClouds/for_lee/clipped_trees_circle/plot_022_tree_179.las",
            "D:/PointClouds/for_lee/clipped_trees_circle/plot_022_tree_181.las",
            "D:/PointClouds/for_lee/clipped_trees_circle/plot_022_tree_193.las",
            "D:/PointClouds/for_lee/clipped_trees_circle/plot_022_tree_195.las",
            "D:/PointClouds/for_lee/clipped_trees_circle/plot_022_tree_200.las",
            "D:/PointClouds/for_lee/clipped_trees_circle/plot_022_tree_218.las",
            "D:/PointClouds/for_lee/clipped_trees_circle/plot_022_tree_234.las",
            "D:/PointClouds/for_lee/clipped_trees_circle/plot_022_tree_243.las")

ls_026 <- c("D:/PointClouds/for_lee/clipped_trees_circle/plot_026_tree_253.las",
            "D:/PointClouds/for_lee/clipped_trees_circle/plot_026_tree_269.las",
            "D:/PointClouds/for_lee/clipped_trees_circle/plot_026_tree_271.las",
            "D:/PointClouds/for_lee/clipped_trees_circle/plot_026_tree_276.las",
            "D:/PointClouds/for_lee/clipped_trees_circle/plot_026_tree_277.las")

ls_121 <- c("D:/PointClouds/for_lee/clipped_trees_circle/plot_121_tree_285.las",
            "D:/PointClouds/for_lee/clipped_trees_circle/plot_121_tree_289.las",
            "D:/PointClouds/for_lee/clipped_trees_circle/plot_121_tree_292.las",
            "D:/PointClouds/for_lee/clipped_trees_circle/plot_121_tree_295.las")

gt <- c("D:/PointClouds/for_lee/ground_truth/shp/TLS_0001_20170531_01_clipped_30_height_norm_1.345_1.395.shp",
        "D:/PointClouds/for_lee/ground_truth/shp/TLS_0002_20170518_01_clipped_30_height_norm_1.345_1.395.shp",
        "D:/PointClouds/for_lee/ground_truth/shp/TLS_0017_20170607_01_clipped_30_height_norm_1.345_1.395.shp",
        "D:/PointClouds/for_lee/ground_truth/shp/TLS_0022_20170627_01_clipped_30_height_norm_1.345_1.395.shp",
        "D:/PointClouds/for_lee/ground_truth/shp/TLS_0026_20170605_01_clipped_30_height_norm_1.345_1.395.shp",
        "D:/PointClouds/for_lee/ground_truth/shp/TLS_0121_20171010_01_clipped_30_height_norm_1.345_1.395.shp")




ls_001_vals <- array(numeric(),c(15,0,0))
ls_002_vals <- array(numeric(),c(6,0,0)) 
ls_017_vals <- array(numeric(),c(8,0,0)) 
ls_022_vals <- array(numeric(),c(10,0,0)) 
ls_026_vals <- array(numeric(),c(5,0,0)) 
ls_121_vals <- array(numeric(),c(4,0,0)) 
ov <- array(numeric(),c(6,0,0)) 
pa <- array(numeric(),c(6,0,0)) 


# ls_001
overlap_length = 0
overlap_frac_total = 0

for (i in 1:length(ls_001)){
  las = readLAS(ls_001[i])
  ground_truths <- st_read(gt[1])
  SEGMENT(las, ground_truths, "001")
}
print(overlap_length)
print(overlap_frac_total)
ov <- c(ov, overlap_length)
pa <- c(pa, overlap_frac_total)



# ls_002
overlap_length = 0
overlap_frac_total = 0

for (i in 1:length(ls_002)){
  las = readLAS(ls_002[i])
  ground_truths <- st_read(gt[2])
  SEGMENT(las, ground_truths, "002")
}
print(overlap_length)
print(overlap_frac_total)
ov <- c(ov, overlap_length)
pa <- c(pa, overlap_frac_total)



# ls_017
overlap_length = 0
overlap_frac_total = 0

for (i in 1:length(ls_017)){
  las = readLAS(ls_017[i])
  ground_truths <- st_read(gt[3])
  SEGMENT(las, ground_truths, "017")
}
print(overlap_length)
print(overlap_frac_total)
ov <- c(ov, overlap_length)
pa <- c(pa, overlap_frac_total)



# ls_022
overlap_length = 0
overlap_frac_total = 0

for (i in 1:length(ls_022)){
  las = readLAS(ls_022[i])
  ground_truths <- st_read(gt[4])
  SEGMENT(las, ground_truths, "022")
}
print(overlap_length)
print(overlap_frac_total)
ov <- c(ov, overlap_length)
pa <- c(pa, overlap_frac_total)



# ls_026
overlap_length = 0
overlap_frac_total = 0

for (i in 1:length(ls_026)){
  las = readLAS(ls_026[i])
  ground_truths <- st_read(gt[5])
  SEGMENT(las, ground_truths, "026")
}
print(overlap_length)
print(overlap_frac_total)
ov <- c(ov, overlap_length)
pa <- c(pa, overlap_frac_total)



# ls_121
overlap_length = 0
overlap_frac_total = 0

for (i in 1:length(ls_121)){
  las = readLAS(ls_121[i])
  ground_truths <- st_read(gt[6])
  SEGMENT(las, ground_truths, "121")
}
print(overlap_length)
print(overlap_frac_total)
ov <- c(ov, overlap_length)
pa <- c(pa, overlap_frac_total)


# TODO: Return as vector of fitness values
cat("ls_001: ", ls_001_vals, "\n")
cat("ls_002: ", ls_002_vals, "\n")
cat("ls_017: ", ls_017_vals, "\n")
cat("ls_022: ", ls_022_vals, "\n")
cat("ls_026: ", ls_026_vals, "\n")
cat("ls_121: ", ls_121_vals, "\n")


ls_str <- paste(c(ls_001_vals,"\n",ls_002_vals,"\n",ls_017_vals,"\n",ls_022_vals,"\n",ls_026_vals,"\n", ls_121_vals,"\n"), collapse=" ")
cat(ls_str, file="C:/Users/Lee/Desktop/CS776-GA-Project/GA_silva2016/ls.txt", sep="\n", append=TRUE)
#cat(ls_str, file="C:/Users/Lee/Desktop/CS776-GA-Project/silva_ls.txt", sep="\n", append=TRUE)
#writeLines(ls_str, ls_file)


cat("ov: ", ov, "\n")
cat("RESULT: ",pa)
