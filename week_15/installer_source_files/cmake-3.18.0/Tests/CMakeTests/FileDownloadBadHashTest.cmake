if(NOT "/home/justin/junk/spriNGboard_pt2/week_15/installer_source_files/cmake-3.18.0/Tests/CMakeTests" MATCHES "^/")
  set(slash /)
endif()
set(url "file://${slash}/home/justin/junk/spriNGboard_pt2/week_15/installer_source_files/cmake-3.18.0/Tests/CMakeTests/FileDownloadInput.png")
set(dir "/home/justin/junk/spriNGboard_pt2/week_15/installer_source_files/cmake-3.18.0/Tests/CMakeTests/downloads")

file(DOWNLOAD
  ${url}
  ${dir}/file3.png
  TIMEOUT 2
  STATUS status
  EXPECTED_HASH SHA1=5555555555555555555555555555555555555555
  )
