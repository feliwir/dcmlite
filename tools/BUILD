# https://docs.bazel.build/versions/master/be/c-cpp.html#cc_binary
cc_binary(
    name = "dcmdump",
    srcs = ["dcmdump.cpp"],
    copts = [
        "-std=c++17",
        "-Iexternal/cxxopts/include",
    ],
    deps = [
        "//dcmlite",
        "@cxxopts//:main",
    ],
)
