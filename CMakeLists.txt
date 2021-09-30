project (neuromag2mne)

set(SOURCES
    main.cpp
    sharedmemorywatcher.cpp
)

add_executable(neuromag2mne ${SOURCES})

target_include_directories(neuromag2mne
    PRIVATE 
        ${PROJECT_SOURCE_DIR}
)