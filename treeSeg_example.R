library(lidR)
library(rgdal)
library(raster)
library(sf)

las = readLAS("D:/PointClouds/for_lee/clipped_als/001_clipped_30.las")
plot(las)

# Classify ground points
las = lasground(las, csf())
plot(las, color = "Classification")

# Normalize points
las = lasnormalize(las, tin())
plot(las)

# Calculate the canopy height model (CHM)
algo = pitfree(thresholds = c(0,10,20,30,40,50), subcircle = 0.2)
chm  = grid_canopy(las, 0.5, algo)
plot(chm, col = height.colors(50))

# Optionally smooth the CHM with a 3x3 pixel moving window with a median statistic
ker = matrix(1,3,3)
chm = focal(chm, w = ker, fun = median)
chm = focal(chm, w = ker, fun = median)

plot(chm, col = height.colors(50)) # check the image



algo = watershed(chm, th = 4, tol = 2, ext = 2)
#algo = li2012(dt1 = 1.5, dt2 = 2, R = 2, Zu = 15, hmin = 2, speed_up = 10)
las  = lastrees(las, algo)

# remove points that are not assigned to a tree
trees = lasfilter(las, !is.na(treeID))

plot(trees, color = "treeID", colorPalette = pastel.colors(100))


# Calculate tree metrics and convex hulls
metric = tree_metrics(las, .stdtreemetrics)
hulls  = tree_hulls(las)
hulls@data = dplyr::left_join(hulls@data, metric@data)

spplot(hulls, "Z")

#ground_truths <- st_read("D:/PointClouds/for_lee/ground_truth/shp/TLS_0001_20170531_01_clipped_30_height_norm_1.345_1.395.shp")
#plot(ground_truths)
