# https://docs.bazel.build/versions/master/be/c-cpp.html#cc_library
cc_library(
    name = "dcmcore",
    srcs = glob(["*.cpp"]),
    hdrs = glob(["*.h"]),
    copts = ["-std=c++17"],
    data = [":gen_tags"],
    visibility = ["//visibility:public"],
)

py_binary(
    name = "gen_tags",
    srcs = ["gen_tags.py"],
    data = ["dict.txt"],
)
