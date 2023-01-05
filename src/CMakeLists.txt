add_library(coolslam SHARED
        frame.cpp
        
)   
target_link_libraries(
    coolslam
    ${THIRD_PARTY_LIBS}
)