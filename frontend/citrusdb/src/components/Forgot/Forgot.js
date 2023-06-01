import React, { useState } from 'react';
import UCRLOGO from '../../images/cutiehack.png'
import { useNavigate } from 'react-router-dom';
import './Forgot.css';

function Forgot() {
    const [username, setUserName] = useState('');
    const navigate = useNavigate();

    const handleForgot = (event) => {
        event.preventDefault();
        alert("Sent recovery!");
        navigate("/login");
    }

    var disableButton = username.length === 0;

    return(
        <div className="forgot-wrapper">
                <h1>CitrusDB</h1>
                <h2>Forgot Password</h2>
                <img src={UCRLOGO} alt="UCRLOGO.png"/>
                <form onSubmit={handleForgot}>
                    <label>
                        <p>Username/Email</p>
                        <input type="text" onChange={e => setUserName(e.target.value)} />
                    </label>
                    <br />
                    <button type="submit" id="forgotPageButton" disabled={disableButton}>Send Recovery!</button>
                </form>
        </div>
    );
};

export default Forgot;