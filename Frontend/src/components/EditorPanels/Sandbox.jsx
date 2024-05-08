import React, { useRef, useState } from "react";
import { Box, HStack } from "@chakra-ui/react";
import { CODE_SNIPPETS } from "../../Constants/languages";
import Editor from "@monaco-editor/react";
import LanguageSelector from "../Buttons/LanguageSelector";
import Output from "./Output";

const Sandbox = () => {
  const editorRef = useRef();
  const [value, setValue] = useState("");
  const [language, setLanguage] = useState("cpp");

  const onMount = (editor) => {
    editorRef.current = editor; // Store editor instance in ref
    editor.focus(); // Focus the editor for immediate typing
  };

  // Function to update the language and the editor content based on the selected language
  const onSelect = (language) => {
    setLanguage(language); // Update the current language
    setValue(CODE_SNIPPETS[language]); // Update the editor content with the snippet for the selected language
  };

  return (
    <Box>
      <HStack spacing={4}>
        {" "}
        <Box w="50%">
          {" "}
          <LanguageSelector language={language} onSelect={onSelect} />{" "}
          <Editor
            options={{ minimap: { enabled: false } }} // Disable the minimap for simplicity
            height="90vh" 
            theme="vs-dark" 
            language={language} 
            defaultValue={CODE_SNIPPETS[language]} // Initialize with a default snippet
            onMount={onMount} // Focus the editor when it mounts
            value={value} // Controlled content of the editor
            onChange={(value) => setValue(value)} // Update the state on content change
          />
        </Box>
        <Output editorRef={editorRef} language={language} />{" "}
        {/* Display the output panel */}
      </HStack>
    </Box>
  );
};

export default Sandbox; 
