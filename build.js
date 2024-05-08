const { exec } = require('child_process');

function runCommand(command, callback) {
    exec(command, (error, stdout, stderr) => {
        if (error) {
            console.error(`exec error: ${error}`);
            return;
        }
        console.log(`stdout: ${stdout}`);
        console.error(`stderr: ${stderr}`);
        if (callback) callback();
    });
}

// Install deps and run make in Blue_Interpreter
runCommand('cd Blue_Interpreter && npm install && make', () => {
    // After done in Blue_Interpreter, install deps in Frontend
    runCommand('cd Frontend && npm install', () => {
        console.log("Build process completed successfully.");
    });
});
