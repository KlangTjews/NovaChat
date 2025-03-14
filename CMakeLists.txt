cmake_minimum_required (VERSION 3.8)

# 如果支持，请为 MSVC 编译器启用热重载。
if (POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

project ("NovaChat")

set(GATE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/NovaChatGateServer)
set(STATUS_PATH ${CMAKE_CURRENT_SOURCE_DIR}/NovaChatStatusServer)
set(SERVER_PATH ${CMAKE_CURRENT_SOURCE_DIR}/NovaChatServer)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=gnu++20")

set(APP1 NovaChatGateServer)
set(APP2 NovaChatStatusServer)
set(APP3 NovaChatServer)

find_package(ZLIB REQUIRED)
find_package(unofficial-uwebsockets CONFIG REQUIRED)
find_package(nlohmann_json CONFIG REQUIRED)
find_package(PostgreSQL REQUIRED)
find_package(hiredis CONFIG REQUIRED)
find_package(redis++ CONFIG REQUIRED)
find_package(boost_asio REQUIRED CONFIG)
find_package(gRPC CONFIG REQUIRED)
find_package(libpqxx CONFIG REQUIRED)
find_package(boost_filesystem REQUIRED CONFIG)

add_subdirectory ("NovaChatGateServer")
add_subdirectory ("NovaChatStatusServer")
add_subdirectory ("NovaChatServer")
