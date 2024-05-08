import { useState } from "react";
import { Box, Text, useToast } from "@chakra-ui/react";
import { executeCode } from "../../api";
import CodeExecutionButtons from "../Buttons/CodeExecutionButtons";

const Output = ({ editorRef, language }) => {
  // useToast is a Chakra UI hook for showing toast notifications
  const toast = useToast();
  const [output, setOutput] = useState(null);
  const [isLoading, setIsLoading] = useState(false);
  const [isError, setIsError] = useState(false);

  async function executeBlueCode(sourceCode, type = "run") {
    try {
      const response = await fetch(
        `https://interpreter-mqqc.onrender.com/execute-blue-code/${type}`, 
        {
          method: "POST",
          headers: {
            "Content-Type": "application/json",
          },
          body: JSON.stringify({ sourceCode }),
        }
      );

      if (!response.ok) {
        const error = await response.json();
        throw new Error(error.error);
      }

      const result = await response.json();
      return result;
    } catch (error) {
      console.error("Failed to execute Blue code:", error);
      throw error;
    }
  }

  const executeType = async (type) => {
    const sourceCode = editorRef.current.getValue();
    if (!sourceCode) return;
    setIsLoading(true);
    try {
      const result = await executeBlueCode(sourceCode, type);
      setOutput(result.output.split("\n"));
      setIsError(!!result.stderr);
      if (result.stderr) {
        setOutput(result.stderr.split("\n"));
      }
    } catch (error) {
      console.log(error);
      setIsError(true);
      setOutput([error.message || `Unable to run ${type} code`]);
      toast({
        title: "An error occurred.",
        description: error.message || `Unable to run ${type} code`,
        status: "error",
        duration: 6000,
      });
    } finally {
      setIsLoading(false);
    }
  };

  const runCode = async () => {
    // Get the source code from the editor using its reference
    const sourceCode = editorRef.current.getValue();
    // If there's no source code, do nothing
    if (!sourceCode) return;
    try {
      // Set loading state to true before making the API call
      setIsLoading(true);

      let result;
      if (language === "cpp") {
        // AKA blue and Execute the code via the blue API
        result = await executeBlueCode(sourceCode);
      } else {
        // Execute the code via the piston API and destructure to get the 'run' object
        const response = await executeCode(language, sourceCode);
        result = response.run;
      }

      // Split the output string into an array of lines and update state
      setOutput(result.output.split("\n"));
      // Check if there's an error message in stderr, set error state and output accordingly
      if (result.stderr) {
        setIsError(true);
        setOutput(result.stderr.split("\n"));
      } else {
        setIsError(false);
        // Split the output string into an array of lines and update state
        setOutput(result.output.split("\n"));
      }
    } catch (error) {
      // Log any errors to the console and show a toast notification
      console.log(error);
      setIsError(true); // Ensure text color is set to red
      setOutput([error.message || "Unable to run code"]); // Convert error message into an array to be consistent with successful output

      toast({
        title: "An error occurred.",
        description: error.message || "Unable to run code",
        status: "error",
        duration: 6000,
      });
    } finally {
      // After execution, reset the loading state
      setIsLoading(false);
    }
  };

  return (
    <Box w="50%">
      <Text mb={2} fontSize="lg">
        Output
      </Text>
      <CodeExecutionButtons
        isLoading={isLoading}
        onRunCode={runCode}
        onExecuteType={executeType}
        language={language}
      />
      <Box
        height="90vh"
        color={isError ? "red.400" : "white"}
        border="1px solid"
        borderColor={isError ? "red.500" : "#333"}
        overflowY="auto"
      >
        {output ? (
          output.map((line, i) => (
            <Text key={i} color="white">
              {" "}
              {line}
            </Text>
          ))
        ) : (
          <Text color="white">Click "Run Code" to see the output here</Text>
        )}
      </Box>
    </Box>
  );
};

export default Output;
