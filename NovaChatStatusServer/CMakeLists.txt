cmake_minimum_required(VERSION 3.28)

project(NovaChatStatusServer)

aux_source_directory(${STATUS_PATH} SRC)

add_executable(${APP2} ${SRC})

target_link_libraries(${APP2} PRIVATE ZLIB::ZLIB unofficial::uwebsockets::uwebsockets nlohmann_json::nlohmann_json PostgreSQL::PostgreSQL libpqxx::pqxx hiredis::hiredis redis++::redis++ Boost::asio gRPC::gpr gRPC::grpc gRPC::grpc++ gRPC::grpc++_alts Boost::filesystem)
