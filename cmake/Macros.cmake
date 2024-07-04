# Not sure if this is good form but it works.

macro(append_to_api _list _path)
    list(APPEND ${_list} ${_path})
    message("Added ${_path} to public API")
endmacro()

macro(append_to_tests _list _path)
    list(APPEND ${_list} ${_path})
    message("Added ${_path} to tests to run")
endmacro()