import React from 'react';
import { getUser } from '../Login/Login.js';
import UCRLOGO from '../../images/cutiehack.png'
import './Dashboard.css';


export default function Dashboard() {
  const currUser = getUser();
  return(
    <div className="dash-wrapper">
      <h1>Dashboard</h1>
      <h2>Welcome, {currUser}!</h2>
      <div className="logo-wrapper">
        <p className="logo-text">CitrusDB</p>
        <img src={UCRLOGO} alt="UCRLOGO.png" className="logo"/>
        <p className="profile-text">Profile</p>
        <button className="edit-profile">Edit Profile</button>
        <button className="logout">Log out</button>
      </div>
      <button id="filter">Filter</button>
      <div className="box" id="documents">
      </div>
      <div className="crud-wrapper">
        <p>Actions</p>
        <button id="upload">Upload</button>
        <br /><br />
        <button id="modify">Modify</button>
        <br /><br />
        <button id="delete">Delete</button>
      </div>
    </div>
  );
};