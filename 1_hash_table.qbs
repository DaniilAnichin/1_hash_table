import qbs

CppApplication {
    type: "application" // To suppress bundle generation on Mac
    consoleApplication: true

    cpp.cppFlags: "-std=c++11"

    files: [
        "hash_table.cpp",
        "hash_table.h",
        "main.cpp",
        "my_conio.cpp",
        "my_conio.h",
    ]

    Group {     // Properties for the produced executable
        fileTagsFilter: product.type
        qbs.install: true
    }
}

