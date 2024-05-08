import React from "react";
import "./UserPics.css";

const contributors = [
  {
    name: "Zeroxa",
    url: "https://github.com/Zeroxa",
    imageUrl: "https://avatars.githubusercontent.com/u/22488037?v=4",
  },
  {
    name: "Oasiss999",
    url: "https://github.com/Oasiss999",
    imageUrl: "https://avatars.githubusercontent.com/u/128113553?v=4",
  },
  {
    name: "EvanW2k",
    url: "https://github.com/EvanW2k",
    imageUrl: "https://avatars.githubusercontent.com/u/125333331?v=4",
  },
  {
    name: "harrisb002",
    url: "https://github.com/harrisb002",
    imageUrl: "https://avatars.githubusercontent.com/u/119838576?v=4",
  },
];

const UserPics = () => (
  <>
    <h1>Made by SSU Students!</h1>
    <div className="user-pictures">
      {contributors.map((contributor, index) => (
        <a
          href={contributor.url}
          key={contributor.name}
          className="user-picture-link"
        >
          <div className="user-picture" style={{ "--order-factor": index + 1 }}>
            <img src={contributor.imageUrl} alt={contributor.name} />
          </div>
        </a>
      ))}
    </div>
  </>
);

export default UserPics;
