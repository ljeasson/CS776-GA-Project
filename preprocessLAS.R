options("rgdal_show_exportToProj4_warnings"="none")

library(lidR)
library(rgdal)
#library(EBImage)

# Read in LAS, classify and normalize
processLAS <- function(pointCloud, plot = FALSE) {
  
  las = readLAS(pointCloud)
  if (plot) plot(las)
  
  # Classify ground points
  las = lasground(las, csf())
  if (plot) plot(las, color = "Classification")
  
  # Normalize points
  las = lasnormalize(las, tin())
  if (plot) plot(las)
  
  return(las)
}

# Get canopy height model (CHM)
canopyHeight <- function(las, smooth = TRUE, plotName = "plot.png", plot = TRUE) {
  
  algo = pitfree(thresholds = c(0,10,20,30,40,50), subcircle = 0.2)
  chm  = grid_canopy(las, 0.5, algo)
  plot(chm, col = height.colors(50))
  
  # Optionally smooth the CHM with a 3x3 pixel moving window 
  # with a median statistic
  if (smooth) {
    ker = matrix(1,3,3)
    chm = focal(chm, w = ker, fun = median)
  }
  
  if (plot) {
    png(plotName)
    plot(chm, col = height.colors(50))
    dev.off ();
  }
  
  return(chm)
}

# Get shape file
getShapeFile <- function(las, chm, plotName = "shape.png") {
  
  #algo = watershed(chm, th = 4)
  las  = lastrees(las, algo)
  
  # Remove points that are not assigned to a tree
  trees = lasfilter(las, !is.na("treeID"))
  plot(trees, color = "treeID", colorPalette = pastel.colors(100))
  
  # Calculate tree metrics and convex hulls
  metric = tree_metrics(las, .stdtreemetrics)
  hulls  = tree_hulls(las)
  hulls@data = dplyr::left_join(hulls@data, metric@data)
  #png(plotName)
  spplot(hulls, "Z")
  #dev.off();
  
  # Write to shapefile in equal area projection
  writeOGR(obj=hulls, dsn="C:/Users/Lee/Documents/", layer="hulls", driver="ESRI Shapefile")

}

las = processLAS(pointCloud = "D:/PointClouds/ferguson/registered/postfire_als_clip/fergusonfire_20180916_TLS_0401_20180822_01_clipped_30.las")
chm = canopyHeight(las, plotName = "plot1.png")
#getShapeFile(las, chm, plotName = "plot1_shape.png")
