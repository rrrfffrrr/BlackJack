# Root of project
cmake_minimum_required(VERSION 3.21)

project(BLACKJACK
    DESCRIPTION "A blackjack game"
    LANGUAGES CXX C
    VERSION 1.0.0
)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_definitions(-DUNICODE)

set(HDRS
    Blackjack.hpp
    Card.hpp
    CardUtils.hpp
    ShuffleMachine.hpp
)

set(SRCS
    main.cpp
    Blackjack.cpp
    Card.cpp
    CardUtils.cpp
    ShuffleMachine.cpp
)

add_executable(BLACKJACK ${HDRS} ${SRCS})