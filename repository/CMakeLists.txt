
add_library(repository Repository.h Repository.cpp models/User.h models/User.cpp Connection.h Connection.cpp)

target_link_libraries(repository
    PRIVATE
        Boost::headers Threads::Threads OpenSSL::Crypto OpenSSL::SSL
        ${Boost_LIBRARIES}
    ${Boost_LIBRARIES})
