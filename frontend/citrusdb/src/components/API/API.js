export async function registerUser(username, password, email) {
    // Change this to match the server's IP address and endpoint
    let response = await fetch("http://18.118.28.109:80");
    console.log(response.status);
    if (response.status === 200) {
        let data = await response.text();
        console.log(data);
    }

    // Have this return a 200 if the user was successfully registered
}