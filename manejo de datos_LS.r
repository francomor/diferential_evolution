datos_leidos <- read.table(file.choose(), header = FALSE, sep = "", dec = ".")

names(datos_leidos)[names(datos_leidos) == "V1"] <- "D"
names(datos_leidos)[names(datos_leidos) == "V2"] <- "NP"
names(datos_leidos)[names(datos_leidos) == "V3"] <- "F"
names(datos_leidos)[names(datos_leidos) == "V4"] <- "CR"
names(datos_leidos)[names(datos_leidos) == "V5"] <- "PLS"
names(datos_leidos)[names(datos_leidos) == "V6"] <- "total_iter"
names(datos_leidos)[names(datos_leidos) == "V7"] <- "best_global_fitness"
names(datos_leidos)[names(datos_leidos) == "V8"] <- "generation_of_best_fitness"
names(datos_leidos)[names(datos_leidos) == "V9"] <- "time_of_best_global_fitness"
names(datos_leidos)[names(datos_leidos) == "V10"] <- "total_running_time"
names(datos_leidos)[names(datos_leidos) == "V11"] <- "total_of_evaluation_in_local_search"

datos1 <- datos_leidos[datos_leidos$PLS == '0.1',]
datos2 <- datos_leidos[datos_leidos$PLS == '0.5',]
datos3 <- datos_leidos[datos_leidos$PLS == '0.7',]

prom_total_iter <- double(3)
  prom_total_iter[1] <- mean(datos1[["total_iter"]])
  prom_total_iter[2] <- mean(datos2[["total_iter"]])
  prom_total_iter[3] <- mean(datos3[["total_iter"]])

prom_best_global_fitness <- double(3)
  prom_best_global_fitness[1] <- mean(datos1[["best_global_fitness"]])
  prom_best_global_fitness[2] <- mean(datos2[["best_global_fitness"]])
  prom_best_global_fitness[3] <- mean(datos3[["best_global_fitness"]])

prom_generation_of_best_fitness <- double(3)
  prom_generation_of_best_fitness[1] <- mean(datos1[["generation_of_best_fitness"]])
  prom_generation_of_best_fitness[2] <- mean(datos2[["generation_of_best_fitness"]])
  prom_generation_of_best_fitness[3] <- mean(datos3[["generation_of_best_fitness"]])

prom_time_of_best_global_fitness <- double(3)
  prom_time_of_best_global_fitness[1] <- mean(datos1[["time_of_best_global_fitness"]])
  prom_time_of_best_global_fitness[2] <- mean(datos2[["time_of_best_global_fitness"]])
  prom_time_of_best_global_fitness[3] <- mean(datos3[["time_of_best_global_fitness"]])

prom_total_running_time <- double(3)
  prom_total_running_time[1] <- mean(datos1[["total_running_time"]])
  prom_total_running_time[2] <- mean(datos2[["total_running_time"]])
  prom_total_running_time[3] <- mean(datos3[["total_running_time"]])

prom_total_of_evaluation_in_local_search <- double(3)
  prom_total_of_evaluation_in_local_search[1] <- mean(datos1[["total_of_evaluation_in_local_search"]])
  prom_total_of_evaluation_in_local_search[2] <- mean(datos2[["total_of_evaluation_in_local_search"]])
  prom_total_of_evaluation_in_local_search[3] <- mean(datos3[["total_of_evaluation_in_local_search"]])  

min_best_global_fitness <- double(3)
  min_best_global_fitness[1] <- min(datos1[["best_global_fitness"]])
  min_best_global_fitness[2] <- min(datos2[["best_global_fitness"]])
  min_best_global_fitness[3] <- min(datos3[["best_global_fitness"]])

ocurr_min_best_global_fitness <- double(3)
  ocurr_min_best_global_fitness[1] <- sum(datos1[["best_global_fitness"]] == min_best_global_fitness[1])
  ocurr_min_best_global_fitness[2] <- sum(datos2[["best_global_fitness"]] == min_best_global_fitness[2])
  ocurr_min_best_global_fitness[3] <- sum(datos3[["best_global_fitness"]] == min_best_global_fitness[3])

Ds <- double(3)
  Ds[1] <- min(datos1[["D"]])
  Ds[2] <- min(datos2[["D"]])
  Ds[3] <- min(datos3[["D"]])

NPs <- double(3)
  NPs[1] <- min(datos1[["NP"]])
  NPs[2] <- min(datos2[["NP"]])
  NPs[3] <- min(datos3[["NP"]])
  
Fs <- double(3)
  Fs[1] <- min(datos1[["F"]])
  Fs[2] <- min(datos2[["F"]])
  Fs[3] <- min(datos3[["F"]])
  
CRs <- double(3)
  CRs[1] <- min(datos1[["CR"]])
  CRs[2] <- min(datos2[["CR"]])
  CRs[3] <- min(datos3[["CR"]])
  
PLSs <- double(3)
  PLSs[1] <- min(datos1[["PLS"]])
  PLSs[2] <- min(datos2[["PLS"]])
  PLSs[3] <- min(datos3[["PLS"]])
  datos_finales <- data.frame(Ds,NPs,Fs,CRs,PLSs,prom_total_iter,prom_best_global_fitness,prom_generation_of_best_fitness,prom_time_of_best_global_fitness,prom_total_running_time,prom_total_of_evaluation_in_local_search,min_best_global_fitness,ocurr_min_best_global_fitness)

