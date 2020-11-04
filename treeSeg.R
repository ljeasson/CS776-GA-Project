library(lidR)

las = readLAS("D:/PointClouds/ferguson/registered/postfire_als_clip/fergusonfire_20180916_TLS_0401_20180822_01_clipped_30.las")
las = segment_trees(las, li2012())
col = random.colors(200)
plot(las, color = "treeID", colorPalette = col)