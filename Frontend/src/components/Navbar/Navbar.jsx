import React from "react";
import { Tabs, TabList, Tab, Divider } from "@chakra-ui/react";
import { Link } from "react-router-dom";
const Navbar = () => {
  return (
    <Tabs variant="soft-rounded" colorScheme="teal">
      <TabList>
        <Tab as={Link} to="/" color="white">
          Sandbox
        </Tab>
        <Tab as={Link} to="/BNF" color="white">
          Language BNF
        </Tab>
        <Tab as={Link} to="/about" color="white">
          About
        </Tab>
      </TabList>
      <Divider borderColor="white" mt={4} mb={2} />
    </Tabs>
  );
};

export default Navbar;
