async function tester() {
    let response = await fetch("http://18.118.28.109:80");
    console.log(response.status);
    if (response.status === 200) {
        let data = await response.text();
        console.log(data);
    }
}

tester();