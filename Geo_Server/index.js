const express = require("express");
const bodyParser = require("body-parser");
const cors = require("cors")();
const app = express();
const server = require("http").Server(app);
const io = require("socket.io")(server);
const mongoose = require("mongoose");
const geo = require("./geoModel");
//Set up default mongoose connection
const mongoDB = "mongodb://devx:devx123@ds259463.mlab.com:59463/geodb";
mongoose.connect(
  mongoDB,
  { useCreateIndex: true, useNewUrlParser: true }
);
// Get Mongoose to use the global promise library
mongoose.Promise = global.Promise;
//Get the default connection
const db = mongoose.connection;
//Bind connection to error event (to get notification of connection errors)
db.on("error", console.error.bind(console, "MongoDB connection error:"));

const port = process.env.PORT || 4000;

app.use(bodyParser.json());
app.use(
  bodyParser.urlencoded({
    extended: true
  })
);

app.use(cors);

app.post("/addgeo", (req, res) => {
  var Geo = new geo({
    package: req.body.package,
    longitude: req.body.longitude,
    lattitude: req.body.lattitude
  });
  Geo.save(function(err) {
    if (err) {
      res.json({ status: "ON" });
    } else {
      res.json({ status: "OFF" });
    }
  });
});

app.get("/getgeo", (req, res) => {
  geo.find({}, function(err, data) {
    res.json(data);
  });
});

io.on("connection", function(socket) {
  socket.on("temp", function(data) {
    console.log(data);

    console.log({
      package: data.package,
      longitude: data.longitude,
      lattitude: data.lattitude
    });
    const Geo = new geo({
      package: data.package,
      longitude: data.longitude,
      lattitude: data.lattitude
    });
    Geo.save(function(err) {
      if (err) {
        socket.emit("light", { status: "ON" });
      } else {
        socket.emit("light", { status: "OFF" });
      }
    });
  });
});

server.listen(port, () => console.log("Running on port: " + port));
