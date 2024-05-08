import React from "react";

import { FontAwesomeIcon } from "@fortawesome/react-fontawesome";
import { faGithub } from "@fortawesome/free-brands-svg-icons";

const GithubLink = () => {
  const githubUrl = "https://github.com/harrisb002/BlueSandbox";

  return (
    <a href={githubUrl}>
      <FontAwesomeIcon
        icon={faGithub}
        style={{
          height: "22px",
          transform: "translateY(4px)",
          paddingRight: "4px",
        }}
      />{" "}
      Github
    </a>
  );
};

export default GithubLink;
