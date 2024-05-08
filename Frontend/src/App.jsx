import React from "react";
import { Routes, Route } from "react-router-dom";
import { Box } from "@chakra-ui/react";
import Navbar from "./components/Navbar/Navbar";
import Sandbox from "./components/EditorPanels/Sandbox";
import About from "./components/About/About";
import BNF from "./components/BNF/BNF";
import GithubLink from "./components/Contributors/GithubLink";

function App() {
  return (
    <>
      <GithubLink />
      <Box minH="100vh" bg="#0f0a19" color="gray.500" px={6} py={8}>
        <Navbar />
        <Routes>
          <Route path="/" element={<Sandbox />} />
          <Route path="/BNF" element={<BNF />} />
          <Route path="/about" element={<About />} />
        </Routes>
      </Box>
    </>
  );
}

export default App;
