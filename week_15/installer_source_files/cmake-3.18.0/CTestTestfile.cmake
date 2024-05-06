# CMake generated Testfile for 
# Source directory: /home/justin/junk/spriNGboard_pt2/week_15/installer_source_files/cmake-3.18.0
# Build directory: /home/justin/junk/spriNGboard_pt2/week_15/installer_source_files/cmake-3.18.0
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
include("/home/justin/junk/spriNGboard_pt2/week_15/installer_source_files/cmake-3.18.0/Tests/EnforceConfig.cmake")
add_test("SystemInformationNew" "/home/justin/junk/spriNGboard_pt2/week_15/installer_source_files/cmake-3.18.0/bin/cmake" "--system-information" "-G" "Unix Makefiles")
set_tests_properties(SystemInformationNew PROPERTIES  _BACKTRACE_TRIPLES "/home/justin/junk/spriNGboard_pt2/week_15/installer_source_files/cmake-3.18.0/CMakeLists.txt;848;add_test;/home/justin/junk/spriNGboard_pt2/week_15/installer_source_files/cmake-3.18.0/CMakeLists.txt;0;")
subdirs("Source/kwsys")
subdirs("Utilities/std")
subdirs("Utilities/KWIML")
subdirs("Utilities/cmlibrhash")
subdirs("Utilities/cmzlib")
subdirs("Utilities/cmcurl")
subdirs("Utilities/cmnghttp2")
subdirs("Utilities/cmexpat")
subdirs("Utilities/cmbzip2")
subdirs("Utilities/cmzstd")
subdirs("Utilities/cmliblzma")
subdirs("Utilities/cmlibarchive")
subdirs("Utilities/cmjsoncpp")
subdirs("Utilities/cmlibuv")
subdirs("Source/CursesDialog/form")
subdirs("Source")
subdirs("Utilities")
subdirs("Tests")
subdirs("Auxiliary")
