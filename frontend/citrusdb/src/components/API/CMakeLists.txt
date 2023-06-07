cmake_minimum_required(VERSION 3.14)
project(API)

set(CMAKE_CXX_STANDARD 17)

# Catch errors
add_compile_options(-Wall -Wextra -Wpedantic)


# Include the Crow library
set(ASIO_INCLUDE_DIR "/home/ec2-user/asio-1.28.0/include")
add_subdirectory(Crow)

# Add the main executable target
add_executable(
    main 
    crow.cpp
    ../../../../../backend/document.cpp
    ../../../../../backend/collection.cpp
    ../../../../../backend/userDatabase.cpp
    ../../../../../backend/file.cpp
    ../../../../../backend/databaseEngine.cpp
        
)

# Link the Crow library to the main target
target_link_libraries(main PRIVATE Crow::Crow)
