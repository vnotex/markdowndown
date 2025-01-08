# MarkdownDown
A markdown parser using PEG in native C.

[PackCC](https://github.com/arithy/packcc) is used as the parser generator.

## How to build
```sh
mkdir build
cd build
cmake -GNinja -DCMAKE_EXPORT_COMPILE_COMMANDS=ON -DMDD_GENERATE_PEG=ON ..
cmake --build .
ctest -C Debug --output-on-failure
```

If you want to manually debug the generated files, you can set `MDD_GENERATE_PEG=OFF` on config to stop the auto-generation.
