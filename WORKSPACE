workspace(name = "dcmlite")

# Generic rules we need
load("@bazel_tools//tools/build_defs/repo:http.bzl", "http_archive")

http_archive(
    name = "gtest",
    url = "https://github.com/google/googletest/archive/release-1.8.1.zip",
    build_file_content = """
cc_library(
    name = "main",
    srcs = glob(
        [
            "src/*.cc",
            "src/*.h",
        ],
        exclude = ["src/gtest-all.cc"],
    ),
    hdrs = glob([
        "include/**/*.h",
        "**/*.h",
    ]),
    copts = [
        "-Iexternal/gtest/include",
        "-Iexternal/gtest",
    ],
    linkopts = ["-pthread"],
    visibility = ["//visibility:public"],
)
    """,
    strip_prefix = "googletest-release-1.8.1/googletest",
)

http_archive(
    name = "cxxopts",
    url = "https://github.com/jarro2783/cxxopts/archive/v2.1.2.tar.gz",
    build_file_content = """
cc_library(
    name = "main",
    hdrs = ["include/cxxopts.hpp"],
    copts = [
        "-Iexternal/cxxopts/include",
    ],
    visibility = ["//visibility:public"],
)
    """,
    strip_prefix = "cxxopts-2.1.2",
)

http_archive(
    name = "charls",
    url = "https://github.com/team-charls/charls/archive/master.zip",
    build_file_content = """
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
    """,
    strip_prefix = "charls-master",
)