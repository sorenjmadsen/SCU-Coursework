
const baseURL = "https://xkcd.now.sh/?comic="
const latestSpecifier = "latest"
let lastComicNumber = 2377;
let comicNumber;

window.onload = () => {
    let queryParam = new URLSearchParams(window.location.search);
    let queryNum = queryParam.get('comic');

    let requestURL;
    if (isNaN(queryNum) || queryNum === null || queryNum === ""){
        // Not a valid number
        requestURL = baseURL + latestSpecifier
    }
    else {
        // For a valid number
        requestURL = baseURL + queryNum
    }
    let promise = fetch(requestURL).then(response => response.json())
    .then((data) => {
        updateComic(data)
        const buttons = document.querySelectorAll(".button")
        buttons.forEach(button => button.addEventListener('click', handleClick))
        comicNumber = data["num"]
    });
    
}

function updateComic(data){
    // Set the title
    document.getElementById("comic-title").textContent = data["title"]
    // Set the img src
    document.getElementById("comic-img").src = data["img"]
    // Set the img alt text
    document.getElementById("alt-text").textContent = data["alt"]
}

function handleClick(event){
    let button = event.target.id
    if (button === "next"){
        if (comicNumber < lastComicNumber)
            comicNumber++;
    }
    if (button === "previous"){
        if (comicNumber > 1)
            comicNumber--;
    }
    if (button === "random"){
        comicNumber = Math.ceil(Math.random() * lastComicNumber);
    }
    if (comicNumber === 1) debugger;

    window.location.href = "?comic=" + comicNumber;
}



