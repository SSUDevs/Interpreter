// Import the axios library for making HTTP requests
import axios from "axios";
import { LANGUAGE_VERSIONS } from "./Constants/languages";

// Create an axios instance configured with the base URL of the Piston API
const API = axios.create({
  baseURL: "https://emkc.org/api/v2/piston",
});

export const executeCode = async (language, sourceCode) => {
  // Perform a POST request to the '/execute' endpoint of the Piston API
  const response = await API.post("/execute", {
    // The programming language in which the source code is written
    language: language,
    version: LANGUAGE_VERSIONS[language],
    // An array of objects, each representing a file. For simplicity, only one file with the source code is sent.
    files: [
      {
        content: sourceCode, // The source code to execute (Whats in the sandbox)
      },
    ],
  });
  return response.data;
};
