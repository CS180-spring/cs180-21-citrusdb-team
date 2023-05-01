import React, { useState } from 'react';
import PropTypes from 'prop-types';
import accounts from '../../database/accounts.json';

import './Login.css';

export function loginUser(account) {
    // console.log(account);
    // console.log(account[0], account[1]);
    if (accounts.hasOwnProperty(account[0]) && accounts[account[0]] === account[1]) {
        return 'valid';
    }
    return 'invalid';
};

export default function Login({ setToken }) {
    const [username, setUserName] = useState();
    const [password, setPassword] = useState();

    const handleSubmit = e => {
        e.preventDefault();
        const token = loginUser([username, password]);
        if (token === 'valid') {
            setToken('valid');
        }
        else {
            alert("Invalid Login");
        }
    }
    return(
        <div className="login-wrapper">
        <h1>CitrusDB Log In</h1>
        <form onSubmit={handleSubmit}>
            <label>
                <p>Username</p>
                <input type="text" onChange={e => setUserName(e.target.value)} />
            </label>
            <label>
                <p>Password</p>
                <input type="password" onChange={e => setPassword(e.target.value)} />
            </label>
                <div>
                    <button type="submit">Submit</button>
                </div>
        </form>
        </div>
    )
};

Login.propTypes = {
    setToken: PropTypes.func.isRequired
};