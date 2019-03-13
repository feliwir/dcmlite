cc_library(
    name = "main",
    srcs = glob([
        "src/*.cpp",
        "src/*.h",
    ]),
    hdrs = glob(["include/charls/*.h"]),
    copts = [
        "-Iexternal/charls/include",
        "-std=c++14"
    ],
    visibility = ["//visibility:public"],
)
