workspace(name = "dcmlite")

# Generic rules we need
load("@bazel_tools//tools/build_defs/repo:http.bzl", "http_archive")

http_archive(
    name = "gtest",
    url = "https://github.com/google/googletest/archive/release-1.8.1.zip",
    build_file = "@dcmlite//third_party:gtest.BUILD",
    strip_prefix = "googletest-release-1.8.1/googletest",
)

http_archive(
    name = "cxxopts",
    url = "https://github.com/jarro2783/cxxopts/archive/v2.1.2.tar.gz",
    build_file = "@dcmlite//third_party:cxxopts.BUILD",
    strip_prefix = "cxxopts-2.1.2",
)

http_archive(
    name = "charls",
    url = "https://github.com/team-charls/charls/archive/master.zip",
    build_file = "@dcmlite//third_party:charls.BUILD",
    strip_prefix = "charls-master",
)

http_archive(
    name = "pnm",
    url = "https://github.com/ToruNiina/pnm/archive/master.zip",
    build_file = "@dcmlite//third_party:pnm.BUILD",
    strip_prefix = "pnm-master",
)