cmake_minimum_required(VERSION 3.28)

project(NovaChatGateServer)

aux_source_directory(${GATE_PATH} SRC)
include_directories(${HEAD_PATH})

add_executable(${APP1} ${SRC})

target_link_libraries(NovaChatGateServer PRIVATE ZLIB::ZLIB unofficial::uwebsockets::uwebsockets nlohmann_json::nlohmann_json PostgreSQL::PostgreSQL libpqxx::pqxx hiredis::hiredis redis++::redis++ Boost::asio gRPC::gpr gRPC::grpc gRPC::grpc++ gRPC::grpc++_alts Boost::filesystem)
