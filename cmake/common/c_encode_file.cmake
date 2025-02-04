cmake_minimum_required(VERSION 3.18.0)  
function(generate_hex_header)
    set(options )
    set(oneValueArgs INPUT OUTPUT PATH)
    set(multiValueArgs NAMESPACE)
    cmake_parse_arguments("" "${options}" "${oneValueArgs}" "${multiValueArgs}" ${ARGN} )

    #Notice all these arrays are nullterminated except the TEXT content_name, because it could be a binary file which contains 0x00 we can not concider it a null termianted string
    #But its just two helpful not to to terminate PATH and SHA1.
    if (_INPUT AND _OUTPUT)
      file (READ ${_INPUT}  _content  HEX)
      get_filename_component( content_name ${_INPUT} NAME_WE)
      string(REPEAT "[0-9a-f]" 32 TOUPLE_LIMIT)
      string(REGEX REPLACE "(${TOUPLE_LIMIT})" "\\1\n\        " text_c_tuples "${_content}")
      string(REGEX REPLACE "([0-9a-f][0-9a-f])" "0x\\1, " text_c_tuples ${text_c_tuples})
      string(REGEX REPLACE ", " "," text_c_tuples ${text_c_tuples})
      string(REGEX REPLACE ",$" "" text_c_tuples ${text_c_tuples})

      file (SHA1 ${_INPUT}  _content )
      string(HEX ${_content} sha1_c_tuples)
      string(APPEND sha1_c_tuples "00")
      string(REGEX REPLACE "(${TOUPLE_LIMIT})" "\\1\n\        " sha1_c_tuples "${sha1_c_tuples}")
      string(REGEX REPLACE "([0-9a-f][0-9a-f])" "0x\\1, " sha1_c_tuples ${sha1_c_tuples})
      string(REGEX REPLACE ", " "," sha1_c_tuples ${sha1_c_tuples})
      string(REGEX REPLACE ",$" "" sha1_c_tuples ${sha1_c_tuples})

      string(HEX ${_PATH} _PATH)
      string(APPEND _PATH "00")
      string(REGEX REPLACE "(${TOUPLE_LIMIT})" "\\1\n\        " path_c_tuples "${_PATH}")
      string(REGEX REPLACE "([0-9a-f][0-9a-f])" "0x\\1, " path_c_tuples ${path_c_tuples})
      string(REGEX REPLACE ", " "," path_c_tuples ${path_c_tuples})
      string(REGEX REPLACE ",$" "" path_c_tuples ${path_c_tuples})
      
      string(REGEX REPLACE "@" "_at_" safe_content_name ${content_name})
      string(MAKE_C_IDENTIFIER  "${safe_content_name}" safe_content_name)

      #Header File
      set(header_file "${_OUTPUT}.hxx")
      file (WRITE ${header_file} "#pragma once\n")
      file (APPEND ${header_file} "\n" 
                                  "#include <cstddef>" 
                                  "\n"
      )
      foreach (_ns IN LISTS _NAMESPACE)
         file(APPEND ${header_file} "namespace ${_ns} { \n")
      endforeach()

      file (APPEND ${header_file} 
                   "  char const*  get_${safe_content_name}_path();\n"
                   "  std::size_t  ${safe_content_name}_path_size();\n"
                   "  char const*  get_${safe_content_name}_sha1();\n"
                   "  std::size_t  ${safe_content_name}_sha1_size();\n"
                   "  char const*  get_${safe_content_name}_text();\n"
                   "  std::size_t  ${safe_content_name}_text_size();\n"
      )
      foreach (_ns IN LISTS _NAMESPACE)
         file(APPEND ${header_file} "}\n")
      endforeach()


      #Source File
      set(source_file "${_OUTPUT}.cxx")
      get_filename_component( import_name ${_INPUT} NAME)
      file (WRITE ${source_file} "#include \"${import_name}.hxx\"\n")
      file (APPEND ${source_file} "\n#include <cstddef>\n")
      file (APPEND ${source_file} "\n\n" )

      foreach (_ns IN LISTS _NAMESPACE)
         file(APPEND ${source_file} "namespace ${_ns} { \n")
      endforeach()
      file (APPEND ${source_file} 
                   "  unsigned char const ${safe_content_name}_path[]={\n"
                   "        ${path_c_tuples}"
                   "\n  };\n"
                   "  constexpr std::size_t  size_of_${safe_content_name}_path=sizeof(${safe_content_name}_path);\n"
                   "\n\n"
                   "  char const*  get_${safe_content_name}_path(){\n"
                   "    return reinterpret_cast<char const *>(${safe_content_name}_path);\n"
                   "  }\n\n"
                   "  std::size_t ${safe_content_name}_path_size() {\n"
                   "    return size_of_${safe_content_name}_path;\n"
                   "  }\n\n"
                   "\n\n"

                   "  unsigned char const ${safe_content_name}_sha1[]={\n"
                   "        ${sha1_c_tuples}"
                   "\n  };\n"
                   "  constexpr std::size_t  size_of_${safe_content_name}_sha1=sizeof(${safe_content_name}_sha1);\n"
                   "\n\n"
                   "  char const*  get_${safe_content_name}_sha1(){\n"
                   "    return reinterpret_cast<char const *>(${safe_content_name}_sha1);\n"
                   "  }\n\n"
                   "  std::size_t ${safe_content_name}_sha1_size() {\n"
                   "    return size_of_${safe_content_name}_sha1;\n"
                   "  }\n\n"
                   "\n\n"

                   "  unsigned char const ${safe_content_name}_text[]={\n"
                   "        ${text_c_tuples}"
                    "\n  };\n"
                   "  constexpr std::size_t  size_of_${safe_content_name}=sizeof(${safe_content_name}_text);\n"
                   "\n\n"
                   " char const*  get_${safe_content_name}_text(){\n"
                   "    return reinterpret_cast<char const *>(${safe_content_name}_text);\n"
                   "  }\n\n"
                   "  std::size_t ${safe_content_name}_text_size() {\n"
                   "    return size_of_${safe_content_name};\n"
                   "  }\n\n"
      )
      foreach (_ns IN LISTS _NAMESPACE)
         file(APPEND ${source_file} "}\n")
      endforeach()


    else()    
      message(FATAL_ERROR "generate_hex_header requires arguments INPUT <file> and OUTPUT <file> ")
    endif()
  endfunction(generate_hex_header)

  generate_hex_header(INPUT "${IN}" OUTPUT "${OUT}" NAMESPACE "${NS}" PATH "${PATH}")
