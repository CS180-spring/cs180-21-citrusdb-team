import React, { useState } from 'react';
import ReactModal from 'react-modal';
import { getUser} from '../Login/Login.js';
import { useNavigate } from 'react-router-dom';
import UCRLOGO from '../../images/cutiehack.png'
import './Collection.css';


export default function Collection() {
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

    // Upload Event states
    const [isUploadOpen, setIsUploadOpen] = useState(false);
    // TODO: Implement upload functionality

    // Filter Event states
    const [isFilterOpen, setIsFilterOpen] = useState(false);
    // TODO: Implement filter functionality

    // Modify Event states
    const [isModifyOpen, setIsModifyOpen] = useState(false);
    // TODO: Implement modify functionality

    // Delete Event states
    const [isDeleteOpen, setIsDeleteOpen] = useState(false);
    // TODO: Implement delete functionality

    // For moving between pages
    const navigate = useNavigate();

    const handleMoveDash = () => {
        navigate('/dashboard');
    }

    const currUser = getUser();
    
    return(
        <div className="dash-wrapper">
        <h1>Collection </h1>
        <h2>Welcome, {currUser}!</h2>
        <div className="logo-wrapper">
            <p className="logo-text">CitrusDB</p>
            <img src={UCRLOGO} alt="UCRLOGO.png" className="logo"/>
            <button className="move-dash" onClick={handleMoveDash}>Back to dashboard</button>
        </div>
        <button id="filter" onClick={() => setIsFilterOpen(true)}>Filter</button>
            <ReactModal
            isOpen={isFilterOpen}
            contentLabel="Filter Modal"
            onRequestClose={() => setIsFilterOpen(false)}
            >
            <form>
                <label>
                    <p>Choose type of query</p>
                    <select>
                        <option value="document">Document</option>
                        <option value="value">Value</option>
                    </select>
                </label>
                <br />
                <label>
                    <p>Query</p>
                    <input type="text" />
                </label>
                <br /><br />
                <button type="submit">Filter</button>
            </form>
            </ReactModal>
        <div className="box" id="documents">
        </div>
        <div className="crud-wrapper">
            <p>Actions</p>
            <button id="create" onClick={() => setIsCreateOpen(true)}>Create Document</button>
            <ReactModal
            isOpen={isCreateOpen}
            contentLabel="Create Modal"
            onRequestClose={handleCloseCreateModal}
            >
            <form onSubmit={handleCreateSubmit}>
            <label>
                <p>Document Name</p>
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
            <button id="upload" onClick={() => setIsUploadOpen(true)}>Upload</button>
            <ReactModal
            isOpen={isUploadOpen}
            contentLabel="Upload Modal"
            onRequestClose={() => setIsUploadOpen(false)}
            >
            <form>
            <label>
                <p>Document Name</p>
                <input type="text" />
            </label>
            <br /><br />
            <label>
                <input type="file" />
            </label>
            <br />
            <br />
            <button type="submit">Upload</button>
            </form>
            </ReactModal>
            <br /><br />
            <button id="modify" onClick={() => setIsModifyOpen(true)}>Modify</button>
            <ReactModal
            isOpen={isModifyOpen}
            contentLabel="Modify Modal"
            onRequestClose={() => setIsModifyOpen(false)}
            >
            <form>
                <label>
                    <p>Document Name</p>
                    <input type="text" />
                </label>
                <label>
                    <p>Variable</p>
                    <input type="text" />
                </label>
                <label>
                    <p>Value</p>
                    <input type="text" />
                </label>
                <br /><br />
                <button type="submit">Modify</button>
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
                    <p>Document Name</p>
                    <input type="text" />
                </label>
                <br /><br />
                <button type="submit">Delete</button>
            </form>
            </ReactModal>
        </div>
        </div>
    );
};