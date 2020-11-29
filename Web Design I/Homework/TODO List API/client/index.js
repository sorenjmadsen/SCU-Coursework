const apiURL = "http://localhost:3000";
   
// Create a new list item when clicking on the "Add" button
function newElement() {
    var li = document.createElement("li");
    var inputValue = document.getElementById("myInput").value;
    var t = document.createTextNode(inputValue);
    li.appendChild(t);
    if (inputValue === '') {
        alert("You must write something!");
    } else {
        document.getElementById("list").appendChild(li);
        sendToServer(inputValue)
    }
    document.getElementById("myInput").value = "";
}

function sendToServer(data){
    let obj = {"todo" : data};
    console.log(obj)
    const headers = new Headers({
        'Content-Type': 'application/json'
    });
    const options = {
        headers: headers,
        method: 'POST',
        body: JSON.stringify(obj)
    };
    fetch('/todo/add', options)
    .then((res) => {res.ok ? console.log(":)") : console.log(":{")})
    .catch(() => {
        let missedTodos = localStorage.getItem("TODO")
        console.log(missedTodos)
        if (missedTodos) {
            missedTodos = JSON.stringify([
                ...JSON.parse(missedTodos), data
            ])
         
            localStorage.setItem("TODO", missedTodos)
        }
        else {
            missedTodos = JSON.stringify([
                data
            ])
            localStorage.setItem("TODO", missedTodos)
        }
    })
}