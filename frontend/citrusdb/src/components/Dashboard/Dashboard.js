import React, { useState } from 'react';
import ReactModal from 'react-modal';
import { getUser, clearUser } from '../Login/Login.js';
import { useNavigate } from 'react-router-dom';
import UCRLOGO from '../../images/cutiehack.png'
import './Dashboard.css';

export default function Dashboard({ setToken }) {
  // Edit Profile states
  const [isEditOpen, setIsEditOpen] = useState(false);
  const [editPassword , setEditPassword] = useState('');
  const [editConfirmPassword , setEditConfirmPassword] = useState('');

  const handleEdit = (event) => {
    event.preventDefault();
    if (editConfirmPassword !== editPassword) {
      console.log("Got ", editPassword, " ", editConfirmPassword);
      alert("Passwords do not match!");
    }
    else {
      alert("Profile Updated!");
    }
  }

  const handleCloseEditModal = () => {
    setEditPassword('');
    setEditConfirmPassword('');
    setIsEditOpen(false);
  };

  // Create Event states
  const [isCreateOpen, setIsCreateOpen] = useState(false);
  const initialVariableState = { variable: '', type: '' };
  const [variables, setVariables] = useState([{ variable: '', type: '' }]);

  const handleCloseCreateModal = () => {
    setVariables([initialVariableState]);
    setIsCreateOpen(false);
  };

  const handleVariableChange = (index, event) => {
    const updatedVariables = [...variables];
    updatedVariables[index][event.target.name] = event.target.value;
    setVariables(updatedVariables);
  };

  const handleAddVariable = () => {
    setVariables([...variables, { variable: '', type: '' }]);
  };

  const handleCreateSubmit = (event) => {
    event.preventDefault();
    console.log(variables);
  };

  // Delete Collection states
  const [isDeleteOpen, setIsDeleteOpen] = useState(false);
  // TODO: Implement delete collection

  // For moving between pages
  const navigate = useNavigate();

  const handleLogout = (event) => {
    event.preventDefault();
    setToken(false);
    clearUser();
    navigate("/login");
  }
  
  const handleGoCollection = (event) => {
    event.preventDefault();
    // TODO: Populate collection page
    navigate("/collection");
  }

  const currUser = getUser();
  return(
    <div className="dash-wrapper">
      <h1>Dashboard</h1>
      <h2>Welcome, {currUser}!</h2>
      <div className="logo-wrapper">
        <p className="logo-text">CitrusDB</p>
        <img src={UCRLOGO} alt="UCRLOGO.png" className="logo"/>
        <p className="profile-text">Profile</p>
        <button className="edit-profile" onClick={() => setIsEditOpen(true)}>Edit Profile</button>
        <ReactModal
        isOpen={isEditOpen}
        contentLabel="Edit Profile Modal"
        onRequestClose={handleCloseEditModal}
        >
        <div className="popup-wrapper">
            <h3>Edit Profile</h3>
            <form>
              <label>
                <p>Password</p>
                <input type="password" onChange={(e) => setEditPassword(e.target.value)} />
              </label>
              <label>
                <p>Confirm Password</p>
                <input type="password" onChange={(e) => setEditConfirmPassword(e.target.value)} />
              </label>
              <br />
              <button type="submit" onClick={handleEdit}>Save Changes</button>
            </form>
          </div>
        </ReactModal>
        <button className="logout" onClick={handleLogout}>Log out</button>
      </div>
      <div className="box" id="documents">
        <p>Collections</p>
        <button onClick={handleGoCollection}>TODO: Sample Collection</button>
      </div>
      <div className="crud-wrapper">
        <p>Actions</p>
        <button id="create" onClick={() => setIsCreateOpen(true)}>Create Collection</button>
        <ReactModal
        isOpen={isCreateOpen}
        contentLabel="Create Modal"
        onRequestClose={handleCloseCreateModal}
        >
        <form onSubmit={handleCreateSubmit}>
          <label>
            <p>Collection Name</p>
            <input type="text" />
          </label>
          {variables.map((variable, index) => (
            <div key={index}>
              <label>
                <p>Variable</p>
                <input
                  type="text"
                  name="variable"
                  value={variable.variable}
                  onChange={(event) => handleVariableChange(index, event)}
                />
              </label>

              <label>
                <p>Variable Type</p>
                <input
                  type="text"
                  name="type"
                  value={variable.type}
                  onChange={(event) => handleVariableChange(index, event)}
                />
              </label>
            </div>
          ))}
          <br />
          <button type="submit" onClick={handleAddVariable}>Add more variables</button>
          <br />
          <button type="submit">Create</button>
        </form>
        </ReactModal>
        <br /><br />
        <button id="delete" onClick={() => setIsDeleteOpen(true)}>Delete</button>
        <ReactModal
        isOpen={isDeleteOpen}
        contentLabel="Delete Modal"
        onRequestClose={() => setIsDeleteOpen(false)}
        >
        <form>
          <label>
            <p>Collection Name</p>
            <input type="text" />
          </label>
        </form>
        </ReactModal>
      </div>
    </div>
  );
};