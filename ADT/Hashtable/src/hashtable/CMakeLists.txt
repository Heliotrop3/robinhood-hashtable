add_library(objHtbl OBJECT hashtable.c)
target_link_libraries(objHtbl PRIVATE m) # Link the math library
