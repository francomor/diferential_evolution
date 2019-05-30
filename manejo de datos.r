datos_leidos <- read.table(file.choose(), header = FALSE, sep = "", dec = ".")

names(datos_leidos)[names(datos_leidos) == "V1"] <- "D"
names(datos_leidos)[names(datos_leidos) == "V2"] <- "NP"
names(datos_leidos)[names(datos_leidos) == "V3"] <- "F"
names(datos_leidos)[names(datos_leidos) == "V4"] <- "CR"
names(datos_leidos)[names(datos_leidos) == "V5"] <- "total_iter"
names(datos_leidos)[names(datos_leidos) == "V6"] <- "best_global_fitness"
names(datos_leidos)[names(datos_leidos) == "V7"] <- "generation_of_best_fitness"
names(datos_leidos)[names(datos_leidos) == "V8"] <- "time_of_best_global_fitness"
names(datos_leidos)[names(datos_leidos) == "V9"] <- "total_running_time"

datos1 <- datos_leidos[datos_leidos$NP == '10' & datos_leidos$F == '0.9' & datos_leidos$CR == '0.1',]
datos2 <- datos_leidos[datos_leidos$NP == '50' & datos_leidos$F == '0.9' & datos_leidos$CR == '0.1',]
datos3 <- datos_leidos[datos_leidos$NP == '100' & datos_leidos$F == '0.9' & datos_leidos$CR == '0.1',]
datos4 <- datos_leidos[datos_leidos$NP == '50' & datos_leidos$F == '0.9' & datos_leidos$CR == '0.9',]
datos5 <- datos_leidos[datos_leidos$NP == '100' & datos_leidos$F == '0.9' & datos_leidos$CR == '0.9',]

prom_total_iter <- double(5)
  prom_total_iter[1] <- mean(datos1[["total_iter"]])
  prom_total_iter[2] <- mean(datos2[["total_iter"]])
  prom_total_iter[3] <- mean(datos3[["total_iter"]])
  prom_total_iter[4] <- mean(datos4[["total_iter"]])
  prom_total_iter[5] <- mean(datos5[["total_iter"]])

prom_best_global_fitness <- double(5)
  prom_best_global_fitness[1] <- mean(datos1[["best_global_fitness"]])
  prom_best_global_fitness[2] <- mean(datos2[["best_global_fitness"]])
  prom_best_global_fitness[3] <- mean(datos3[["best_global_fitness"]])
  prom_best_global_fitness[4] <- mean(datos4[["best_global_fitness"]])
  prom_best_global_fitness[5] <- mean(datos5[["best_global_fitness"]])

prom_generation_of_best_fitness <- double(5)
  prom_generation_of_best_fitness[1] <- mean(datos1[["generation_of_best_fitness"]])
  prom_generation_of_best_fitness[2] <- mean(datos2[["generation_of_best_fitness"]])
  prom_generation_of_best_fitness[3] <- mean(datos3[["generation_of_best_fitness"]])
  prom_generation_of_best_fitness[4] <- mean(datos4[["generation_of_best_fitness"]])
  prom_generation_of_best_fitness[5] <- mean(datos5[["generation_of_best_fitness"]])

prom_time_of_best_global_fitness <- double(5)
  prom_time_of_best_global_fitness[1] <- mean(datos1[["time_of_best_global_fitness"]])
  prom_time_of_best_global_fitness[2] <- mean(datos2[["time_of_best_global_fitness"]])
  prom_time_of_best_global_fitness[3] <- mean(datos3[["time_of_best_global_fitness"]])
  prom_time_of_best_global_fitness[4] <- mean(datos4[["time_of_best_global_fitness"]])
  prom_time_of_best_global_fitness[5] <- mean(datos5[["time_of_best_global_fitness"]])

prom_total_running_time <- double(5)
  prom_total_running_time[1] <- mean(datos1[["total_running_time"]])
  prom_total_running_time[2] <- mean(datos2[["total_running_time"]])
  prom_total_running_time[3] <- mean(datos3[["total_running_time"]])
  prom_total_running_time[4] <- mean(datos4[["total_running_time"]])
  prom_total_running_time[5] <- mean(datos5[["total_running_time"]])

min_best_global_fitness <- double(5)
  min_best_global_fitness[1] <- min(datos1[["best_global_fitness"]])
  min_best_global_fitness[2] <- min(datos2[["best_global_fitness"]])
  min_best_global_fitness[3] <- min(datos3[["best_global_fitness"]])
  min_best_global_fitness[4] <- min(datos4[["best_global_fitness"]])
  min_best_global_fitness[5] <- min(datos5[["best_global_fitness"]])

ocurr_min_best_global_fitness <- double(5)
  ocurr_min_best_global_fitness[1] <- sum(datos1[["best_global_fitness"]] == min_best_global_fitness[1])
  ocurr_min_best_global_fitness[2] <- sum(datos2[["best_global_fitness"]] == min_best_global_fitness[2])
  ocurr_min_best_global_fitness[3] <- sum(datos3[["best_global_fitness"]] == min_best_global_fitness[3])
  ocurr_min_best_global_fitness[4] <- sum(datos4[["best_global_fitness"]] == min_best_global_fitness[4])
  ocurr_min_best_global_fitness[5] <- sum(datos5[["best_global_fitness"]] == min_best_global_fitness[5])

Ds <- double(5)
  Ds[1] <- min(datos1[["D"]])
  Ds[2] <- min(datos2[["D"]])
  Ds[3] <- min(datos3[["D"]])
  Ds[4] <- min(datos4[["D"]])
  Ds[5] <- min(datos5[["D"]])

NPs <- double(5)
  NPs[1] <- min(datos1[["NP"]])
  NPs[2] <- min(datos2[["NP"]])
  NPs[3] <- min(datos3[["NP"]])
  NPs[4] <- min(datos4[["NP"]])
  NPs[5] <- min(datos5[["NP"]])
  
Fs <- double(5)
  Fs[1] <- min(datos1[["F"]])
  Fs[2] <- min(datos2[["F"]])
  Fs[3] <- min(datos3[["F"]])
  Fs[4] <- min(datos4[["F"]])
  Fs[5] <- min(datos5[["F"]])
  
CRs <- double(5)
  CRs[1] <- min(datos1[["CR"]])
  CRs[2] <- min(datos2[["CR"]])
  CRs[3] <- min(datos3[["CR"]])
  CRs[4] <- min(datos4[["CR"]])
  CRs[5] <- min(datos5[["CR"]])
  
  datos_finales <- data.frame(Ds,NPs,Fs,CRs,prom_total_iter,prom_best_global_fitness,prom_generation_of_best_fitness,prom_time_of_best_global_fitness,prom_total_running_time,min_best_global_fitness,ocurr_min_best_global_fitness)

