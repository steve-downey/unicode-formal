add_library(unicode_formal STATIC "")

target_sources(
  unicode_formal
  PRIVATE
  unicode_formal.cpp)

include(GNUInstallDirs)

target_include_directories(unicode_formal PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/../>
  $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}/${CMAKE_LOWER_PROJECT_NAME}>  # <prefix>/include/unicode_formal
  )

install(
  TARGETS unicode_formal
  EXPORT ${TARGETS_EXPORT_NAME}
  DESTINATION ${CMAKE_INSTALL_LIBDIR}
  )

string(TOLOWER ${CMAKE_PROJECT_NAME} CMAKE_LOWER_PROJECT_NAME)

install(
  DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/
  DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/${CMAKE_LOWER_PROJECT_NAME}
  FILES_MATCHING PATTERN "*.h"
  )


## Tests
add_executable(unicode_formal_test "")

target_sources(
  unicode_formal_test
  PRIVATE
  unicode_formal.t.cpp)

target_link_libraries(unicode_formal_test unicode_formal)
target_link_libraries(unicode_formal_test gtest)
target_link_libraries(unicode_formal_test gtest_main)

include(GoogleTest)
gtest_discover_tests(unicode_formal_test)
