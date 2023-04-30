
set(TEXTURE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/res/texture)

function(bgfx_dev_add_texture_dir FOLDER)
    file(GLOB files "${FOLDER}/*.*")

    foreach(file ${files})
        file(COPY ${file} DESTINATION ${TEXTURE_RUNTIME_OUTPUT_DIRECTORY})
    endforeach()
endfunction()
