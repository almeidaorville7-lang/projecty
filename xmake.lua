set_project("projecty")
set_version("1.0.0")

set_languages("cxx23")

target("projecty")
    set_kind("binary")
    set_default(true)
    add_files("src/*.cpp")

    set_targetdir("build/bin")
