# https://docs.bazel.build/versions/master/be/c-cpp.html#cc_binary
cc_binary(
    name = "dcmdump",
    srcs = ["dcmdump.cpp"],
    copts = [
        "-std=c++17",
        "-Iexternal/cxxopts/include",
    ],
    deps = [
        "//dcmcore",
        "@cxxopts//:main",
    ],
)

cc_binary(
    name = "dcm2pnm",
    srcs = ["dcm2pnm.cpp"],
    copts = [
        "-std=c++17",
        "-Iexternal/cxxopts/include",
    ],
    deps = [
        "//dcmcore",
        "//dcmimg",
        "@cxxopts//:main",
        "@pnm//:main",
    ],
)
