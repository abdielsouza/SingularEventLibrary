if(EXISTS "/home/abdiel/Documentos/vscode-projects/libraries/SingularEventHandler/build/singular_test[1]_tests.cmake")
  include("/home/abdiel/Documentos/vscode-projects/libraries/SingularEventHandler/build/singular_test[1]_tests.cmake")
else()
  add_test(singular_test_NOT_BUILT singular_test_NOT_BUILT)
endif()
