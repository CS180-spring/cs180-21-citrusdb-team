# Set the minimum required CMake version
cmake_minimum_required(VERSION 3.14)

# Set the project name
project(API)

# Include the Crow library
find_package(Crow REQUIRED)

# Add the main executable target
add_executable(
    main 
    main.cpp
    ../../../../../backend/document.cpp
    ../../../../../backend/collection.cpp
    ../../../../../backend/userDatabase.cpp
    ../../../../../backend/file.cpp
    ../../../../../backend/databaseEngine.cpp
        
)

# Link the Crow library to the main target
target_link_libraries(main PRIVATE Crow::Crow)
