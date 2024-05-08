const express = require("express");
const cors = require("cors");
const colors = require("colors");
const fs = require("fs").promises;
const { exec } = require("child_process");
const app = express();
const port = 3001;

app.use(cors());
app.use(express.json());

app.post("/execute-blue-code/:type", async (req, res) => {
  const { sourceCode } = req.body;
  const { type } = req.params; // "run", "tokens", "cst", or "symbolTable"
  const filePath = "./tempSourceCode.c";

  try {
    await fs.writeFile(filePath, sourceCode);
    exec(`./main ${filePath} ${type}`, (error, stdout, stderr) => {
      if (error) {
        return res.status(500).send({ error: error.message });
      }
      res.send({ output: stdout, stderr: stderr });
    });
  } catch (error) {
    console.error(error);
    res.status(500).send({ error: `Server error: ${error.message}` });
  }
});

app.listen(port, () => console.log(`Server running on port ${port}`.cyan));
