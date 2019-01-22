cc_test(
    name = "loading_test",
    size = "small",
    srcs = ["load.cpp"],
    copts = [
        "-Iexternal/gtest/include",
        "-std=c++17",
    ],
    data = [
        "//data:CR",
    ],
    linkopts = ["-lstdc++fs"],
    deps = [
        "//dcmlite",
        "@gtest//:main",
    ],
)
