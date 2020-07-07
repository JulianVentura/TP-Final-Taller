project(TP-Final-Taller) 

FILE (GLOB misArchivos "*.cpp")
add_library(misClases
  ${misArchivos}
)
