cmake_minimum_required (VERSION 3.14)

# Включение горячей перезагрузки для компиляторов MSVC, если поддерживается.
if (POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

project ("stack_and_queue" LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Заголовочная библиотека: myStack.h, myQueue.h, rootedTree.h
add_library(containers INTERFACE)
target_include_directories(containers INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/include)

# Исполняемый файл
add_executable(stack_and_queue src/main.cpp)
target_link_libraries(stack_and_queue PRIVATE containers)

enable_testing()
add_subdirectory(tests)