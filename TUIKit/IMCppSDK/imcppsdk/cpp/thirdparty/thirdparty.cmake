get_filename_component(THIRD_PARTY_CMAKE_DIR "${CMAKE_CURRENT_LIST_FILE}" PATH)

set(THIRD_PARTY_PATH ${THIRD_PARTY_CMAKE_DIR})

include(${THIRD_PARTY_PATH}/json/json.cmake)

set(THIRD_PARTY_SRC
        ${JSON_SRC}
        )