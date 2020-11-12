// TASK 1A: What does the require function do?
// The require function imports modules, JSON, and local files.
const express = require('express')
const fs = require('fs/promises')

// TASK 1B: What are these two parameters and how do they work with express?
// The first parameter, req, is the HTTP GET request to process. The second
// parameter, res, is the going to be the HTTP response returned. These parameters
// workd to route HTTP requests.
const getAllMoods = (req, res) => {
  const allMoods = Object.keys(res.app.locals.reactions);

  // TASK 1C: What does the res.status() function do? What allows this to be chained?
  // The res.status() function sets the status code of the HTTP response. Promises then
  // allow us to callback and send the response with allMoods.
  res.status(200).send(allMoods);
};

const getAllGifs = (req, res) => {
  const allGifs = res.app.locals.reactions;

  res.status(200).send(allGifs)
};

const getMoodGif = (req, res) => {
  const mood = req.params["mood"];
  const gifs = res.app.locals.reactions[mood];
  
  if (gifs){
    const length = res.app.locals.reactions[mood].length;
    let gif = {"gif" : gifs[Math.floor(Math.random() * length)]};
    res.status(200).send(gif);
  }
  else {
    let msg = {"msg" : "No gif found"};
    res.status(404).send(msg);
  }
}

const postMood = (req, res) => {
  let msg;
  const mood = req.body.mood
  if (mood){
    if (!res.app.locals.reactions[mood])
      res.app.locals.reactions[mood] = [];
    res.status(204);
  }
  else {
    msg = {"msg" : "Request not understood"};
    res.status(400).send(msg);
  }
};

const postGif = (req, res) => {
  const mood = req.params.mood
  const link = req.body.link
  if (mood && link){
    res.app.locals.reactions[mood].push(link)
    res.status(204);
  }
  else {
    msg = {"msg" : "Request not understood"};
    res.status(400).send(msg);
  }
}

const deleteMood = (req, res) => {
  let msg;
  const mood = req.params.mood
  if (mood && res.app.locals.reactions[mood]){
    delete res.app.locals.reactions[mood];
    res.status(204);
  }
  else {
    msg = {"msg" : "Request not understood"};
    res.status(400).send(msg);
  }
}

const deleteGif = (req, res) => {
  let msg;
  const mood = req.params.mood
  const link = req.body.link
  if (mood && link){
    if (res.app.locals.reactions[mood][link]);
      delete res.app.locals.reactions[mood][link];
    res.status(204);
  }
  else {
    msg = {"msg" : "Request not understood"};
    res.status(400).send(msg);
  }
}


const main = () => {
  const app = express();
  const port = 3000;

  // TASK 1D: What does this line do?
  // This mounts the middleware to parse HTTP requests as JSON objects
  app.use(express.json());

  // TASK 1E: What does this line do?
  // This routes a GET request with a specified path and runs the callback function.
  app.get("/moods", getAllMoods);

  // ADDITIONS FOR LAB
  app.get("/gifs", getAllGifs);
  app.get("/gif/:mood", getMoodGif);

  app.post("/mood", postMood);
  app.post("/gif/:mood", postGif);

  app.delete("/mood/:mood", deleteMood);
  app.delete("/gif/:mood", deleteGif)
  

  fs.readFile("./gifs.json", "utf-8")
    .then((fileContents) => JSON.parse(fileContents))
    .then((data) => {
      // TASK 1F: What is the locals property in on the app object?
      // The locals property is storage for variables that are intended to
      // persist through the duration of the application rather than a
      // request or a response.
      app.locals.reactions = data;

      // TASK 1G: What does this do?
      // This binds the port to the server and begins listening for requests.
      app.listen(port, () => {
        console.log(`Reaction gifs started on http://localhost:${port}`);
      });
    });
};

main();
