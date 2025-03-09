# CMakeList.txt: NovaChat 的 CMake 项目，在此处包括源代码并定义
# 项目特定的逻辑。
#

# 将源代码添加到此项目的可执行文件。
add_executable (NovaChat "GateServer.cpp" "CServer.cpp" "HttpConnection.cpp" "LogicSystem.cpp" "VerifyGrpcClient.cpp" "ConfigMgr.cpp" "RedisMgr.cpp" "SQLMgr.cpp" "PostgreSQLMgr.cpp" "AsioIOServicePool.cpp" "message.grpc.pb.cc" "message.pb.cc")

include_directories(${HEAD_PATH})

target_link_libraries(NovaChat PRIVATE ZLIB::ZLIB unofficial::uwebsockets::uwebsockets nlohmann_json::nlohmann_json PostgreSQL::PostgreSQL libpqxx::pqxx hiredis::hiredis redis++::redis++ Boost::asio gRPC::gpr gRPC::grpc gRPC::grpc++ gRPC::grpc++_alts Boost::filesystem)

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET NovaChat PROPERTY CXX_STANDARD 20)
endif()

# TODO: 如有需要，请添加测试并安装目标。
