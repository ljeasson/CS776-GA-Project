library("lidR")
preALS <- list("C:/Users/Leeasson/Desktop/ga/prefire_als_clip/fergusonfire_20180722_TLS_0401_20180720_01_clipped_30.las",
               "C:/Users/Leeasson/Desktop/ga/prefire_als_clip/fergusonfire_20180722_TLS_0402_20180720_01_clipped_30.las",
               "C:/Users/Leeasson/Desktop/ga/prefire_als_clip/fergusonfire_20180722_TLS_0403_20180720_01_clipped_30.las",
               "C:/Users/Leeasson/Desktop/ga/prefire_als_clip/fergusonfire_20180722_TLS_0404_20180721_01_clipped_30.las",
               "C:/Users/Leeasson/Desktop/ga/prefire_als_clip/fergusonfire_20180722_TLS_0405_20180721_01_clipped_30.las",
               "C:/Users/Leeasson/Desktop/ga/prefire_als_clip/fergusonfire_20180722_TLS_0406_20180721_01_clipped_30.las")

postALS <- list("C:/Users/Leeasson/Desktop/ga/postfire_als_clip/fergusonfire_20180916_TLS_0401_20180822_01_clipped_30.las",
                "C:/Users/Leeasson/Desktop/ga/postfire_als_clip/fergusonfire_20180916_TLS_0402_20180822_01_clipped_30.las",
                "C:/Users/Leeasson/Desktop/ga/postfire_als_clip/fergusonfire_20180916_TLS_0403_20180822_01_clipped_30.las",
                "C:/Users/Leeasson/Desktop/ga/postfire_als_clip/fergusonfire_20180916_TLS_0404_20180823_01_clipped_30.las",
                "C:/Users/Leeasson/Desktop/ga/postfire_als_clip/fergusonfire_20180916_TLS_0405_20181011_01_clipped_30.las",
                "C:/Users/Leeasson/Desktop/ga/postfire_als_clip/fergusonfire_20180916_TLS_0406_20180823_01clipped_30.las")

for (pointCloud in postALS) {
  las <- readLAS(pointCloud)
  las <- segment_trees(las, li2012())
  col <- random.colors(200)
  plot(las, color = "treeID", colorPalette = col)
}
