import {
  Box,
  Button,
  Menu,
  MenuButton,
  MenuItem,
  MenuList,
  Text,
} from "@chakra-ui/react";
import { LANGUAGE_VERSIONS } from "../../Constants/languages";

// Transforming LANGUAGE_VERSIONS object into an array of [language, version] pairs
const languages = Object.entries(LANGUAGE_VERSIONS);
// Constant for the active language color in the UI
const ACTIVE_COLOR = "blue.400";

const LanguageSelector = ({ language, onSelect }) => {
  return (
    <Box ml={2} mb={4}>
      <Text mb={2} fontSize="lg">
        Language: 
      </Text>
      <Menu isLazy>
        <MenuButton as={Button}>
          {language === "cpp" ? "blue" : language}{" "}
        </MenuButton>
        <MenuList bg="#110c1b">
          {" "}
          {languages.map(
            (
              [lang, version] // Mapping each language-version pair to a MenuItem
            ) => (
              <MenuItem
                key={lang}
                color={lang === language ? ACTIVE_COLOR : ""} // Highlights the currently selected language
                bg={lang === language ? "gray.900" : "transparent"} // Background color changes for the active item
                _hover={{
                  // Styling for hover state
                  color: ACTIVE_COLOR,
                  bg: "gray.900",
                }}
                onClick={() => onSelect(lang)} // Triggers onSelect prop function with the selected language
              >
                {lang === "cpp" ? "blue" : lang}{" "}
                &nbsp; {/* Non-breaking space for styling */}
                <Text as="span" color="gray.600" fontSize="sm">
                  ({version}){" "}
                  {/* Displays the version of the language in gray */}
                </Text>
              </MenuItem>
            )
          )}
        </MenuList>
      </Menu>
    </Box>
  );
};

export default LanguageSelector;
