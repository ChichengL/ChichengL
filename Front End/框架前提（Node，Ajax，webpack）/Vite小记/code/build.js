const { build } = require("esbuild");
const httpImport = require("../http-import-plugin");
async function runBuild() {
    build({
        absWorkingDir: process.cwd(),
        entryPoints: ["./index.jsx"],
        outdir: "dist",
        bundle: true,
        format: "esm",
        splitting: true,
        sourcemap: true,
        metafile: true,
        plugins: [httpImport()],

    }).then(() => {
        console.log(" Build Finished!");
    });
}
runBuild();