const buildOptions = {
    input: ["src/index.js"],
    // 将 output 改造成一个数组
    output: [{
        dir: "dist/es", format: "esm",
    }, { dir: "dist/cjs", format: "cjs", },
    ],
};
export default buildOptions;