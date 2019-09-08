cmake_minimum_required (VERSION 2.6)
project (Chess)

add_executable(chess
  src/main.c
  src/ui.c
  src/engine.c)
      
target_link_libraries(chess raylib)
