const express = require("express");
const cors = require("cors");
const colors = require("colors");
const fs = require("fs").promises;
const { exec } = require("child_process");
const app = express();

const dotenv = require("dotenv");
dotenv.config();
const port = process.env.BLUE_PORT || 10000;

app.use(express.json());
app.use(
  cors({
    origin: ["http://localhost:3000", "https://interpreter-5za8.onrender.com"],
  })
);

app.post("/execute-blue-code/:type", async (req, res) => {
  const { sourceCode } = req.body;
  const { type } = req.params; // "run", "tokens", "cst", or "symbolTable"
  const filePath = "./tempSourceCode.c";

  console.log("sourceCode is: ", sourceCode);
  console.log("type is: ", type);

  const command = `./main ${filePath} ${type}`;
  console.log("Executing command:", command);
  try {
    console.log("Writing to file");
    exec(command, (error, stdout, stderr) => {
      if (error) {
        return res.status(500).send({ error: error.message });
      }
      console.log("Output is: ", { output: stdout, stderr: stderr });

      res.send({ output: stdout, stderr: stderr });
    });
  } catch (error) {
    console.error(error);
    res.status(500).send({ error: `Server error: ${error.message}` });
  }
});

app.listen(port, "0.0.0.0", () =>
  console.log(`Server running on port ${port}`.cyan)
);
