workspace(name = "dcmlite")

# Generic rules we need
load("@bazel_tools//tools/build_defs/repo:http.bzl", "http_archive")

new_http_archive(
    name = "gtest",
    url = "https://github.com/google/googletest/archive/release-1.8.1.zip",
    build_file = "third_party/gtest.BUILD",
    strip_prefix = "googletest-release-1.8.1/googletest",
)

new_http_archive(
    name = "cxxopts",
    url = "https://github.com/jarro2783/cxxopts/archive/v2.1.2.tar.gz",
    build_file = "third_party/cxxopts.BUILD",
    strip_prefix = "cxxopts-2.1.2",
)