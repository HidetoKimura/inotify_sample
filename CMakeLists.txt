cmake_minimum_required(VERSION 3.1)

# define a variable of project name
set( project_name "Inofify Sample")

# define a project name
project (${project_name} C)

# define executable
add_executable(inotify_sample main.c)