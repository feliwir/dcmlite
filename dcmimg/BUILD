#https: //docs.bazel.build/versions/master/be/c-cpp.html#cc_library
cc_library(
    name = "dcmimg",
    srcs = glob(["*.cpp"]),
    hdrs = glob(["*.h"]),
    copts = [
        "-std=c++17",
        "-Iexternal/charls/include",
    ],
    visibility = ["//visibility:public"],
    deps = [
        "//dcmcore",
        "@charls//:main",
    ],
)
