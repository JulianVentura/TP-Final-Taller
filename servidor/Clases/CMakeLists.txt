project(TP-Final-Taller) 

FILE (GLOB misArchivos "*.cpp")
message (STATUS "Cargue ${misArchivos}")
add_library(misClases
  ${misArchivos}
)
