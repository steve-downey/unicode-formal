include(GNUInstallDirs)

add_executable(main "")

target_sources(
  main
  PRIVATE
  main.cpp)

target_link_libraries(main unicode_formal)

install(
  TARGETS main
  DESTINATION ${CMAKE_INSTALL_BINDIR}
  )
