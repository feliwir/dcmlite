cc_test(
    name = "loading_test",
    srcs = ["load.cpp"],
    copts = ["-Iexternal/gtest/include", "-std=c++17"],
    linkopts = ["-lstdc++fs"],
    deps = [
        "@gtest//:main",
        "//dcmlite",
    ],
    data = [
        "//data:CR"
    ],
    size = "small"
)