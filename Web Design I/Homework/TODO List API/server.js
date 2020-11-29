const express = require('express')
const fs = require('fs/promises')
const path = require('path')

const app = express();
    

const port = 3000;

const listTodos = (req, res) => {
    let todos = res.app.locals.todos;
    // console.log(todos.list)
    if (todos.list.length) {
        res.status(200).send(todos)
    }
    else {
        res.status(404).send({"msg" : "No todos on the list."})
    }
};

const addTodo = (req, res) => {
    console.log(req.headers)
    console.log("Todo Posted: " + req.body.todo);
    if (req.body.todo) {
        res.app.locals.todos.list.push(req.body.todo);
        res.status(204).send({});
        saveData(res.app.locals.todos);
    } else {
        msg = {"msg" : "Request not understood"};
        res.status(400).send(msg);
    }
};

const saveData = (todos) => {
    fs.writeFile("./todo-list.json", JSON.stringify(todos), 'utf-8');
};


const main = () => {
    const app = express();
    const port = 3000;
    app.use(express.json());
    app.use(express.static('client'));

    // API Endpoints
    app.get('/todo/list', listTodos);
    app.post('/todo/add', addTodo);

    // Load data and bind to port
    fs.readFile("./todo-list.json", "utf-8")
        .then((fileContents) => JSON.parse(fileContents))
        .then((data) => {
            app.locals.todos = data;
            app.listen(port, () => {
              console.log(`Todo list started on http://localhost:${port};`);
            });
        });
}
main();