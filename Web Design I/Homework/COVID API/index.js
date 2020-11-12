const countries = [ "south-africa",
                    "barbados",
                    "switzerland",
                    "china",
                    "denmark",
                    "italy"];

const apiUrl = "https://api.covid19api.com/total/dayone/country/";

function checkResponse(response){
    return response.ok ? response.json() : Promise.reject("No data");
}

// Takes in a data file fetched and a case type to return total count
function getCaseCount(data){
    let casesObj = {
        "active" : 0,
        "recovered" : 0,
        "deaths": 0
    }
    let len = data.length
    let recentData = data[len-1]
    casesObj["active"] = recentData.Active
    casesObj["recovered"] = recentData.Recovered
    casesObj["deaths"] = recentData.Deaths
    return casesObj;
}

function updateWebpage(countryList, active, recovered, death){
    const activeP = document.querySelector("#active");
    const recoveredP = document.querySelector("#recovered");
    const deathsP = document.querySelector("#deaths");

    activeP.innerText = active;
    recoveredP.innerText = recovered;
    deathsP.innerText = death;
}

let totalD = 0;
let totalA = 0;
let totalR = 0;

let promises = countries.map(c => 
    fetch(apiUrl + c).then(checkResponse).then(data => getCaseCount(data)))
Promise.all(promises)
    .then(cases => {
        cases.forEach(c => {
            totalA = c.active;
            totalD = c.deaths;
            totalR = c.recovered;
        })
        updateWebpage(countries, totalA, totalR, totalD)
    })


