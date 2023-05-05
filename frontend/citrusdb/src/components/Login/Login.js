import React, { useState } from 'react';
import PropTypes from 'prop-types';
import accounts from '../../database/accounts.json';
import UCRLOGO from '../../images/cutiehack.png'

import './Login.css';
import { useNavigate } from 'react-router-dom';

var userGlobal = '';

export function loginUser(account) {
    if (accounts.hasOwnProperty(account[0]) && accounts[account[0]] === account[1]) {
        return 'valid';
    }
    return 'invalid';
};

export function getUser() {
    if (userGlobal !== '') {
        return userGlobal;
    }
    return '';
}

export default function Login({ setToken }) {
    const [username, setUserName] = useState('');
    const [password, setPassword] = useState('');
    const navigate = useNavigate();

    const handleLogin = (event) => {
        event.preventDefault();
        const token = loginUser([username, password]);
        if (token === 'valid') {
            //alert("nice");
            setToken(true);
            userGlobal = username;
            navigate('/dashboard');
        }
        else {
            alert("Invalid Login");
        }
    }

    const handleForgot = (event) => {
        event.preventDefault();
        //alert("Forgot");
        navigate("/forgot");
    }

    const handleRegister = (event) => {
        event.preventDefault();
        ///alert("register");
        navigate("/register");
    }
    
    var disableButton = (username.length === 0) || (password.length === 0);

    return(
        <div className="login-wrapper">
            <h1>CitrusDB</h1>
            <h2>Login</h2>
            <img src={UCRLOGO} alt="UCRLOGO.png"/>
            <form onSubmit={handleLogin}>
            <label>
                    <p>Username/Email</p>
                    <input type="text" onChange={e => setUserName(e.target.value)} />
                </label>
                <label>
                    <p>Password</p>
                    <input type="password" onChange={e => setPassword(e.target.value)} />
                </label>
                    <div>
                        <button type="button" id="registerButton" onClick={handleRegister}>Register</button>
                        <button type="button" id="forgotButton" onClick={handleForgot}>Forgot Password?</button>
                    </div>
                    <br />
                    <button type="submit" id="loginButton" disabled={disableButton}>Login</button>
            </form>
        </div>
    )
};

Login.propTypes = {
    setToken: PropTypes.func.isRequired
};