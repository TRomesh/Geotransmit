const express = require('express');
const bodyParser = require('body-parser');
const cors = require('cors')();
const app = express();

const port =process.env.PORT || 4000;

app.use(bodyParser.json());
app.use(bodyParser.urlencoded({
   extended:true
}));

app.use(cors);

app.post('/addgeo',(req,res) => {
    res.send("true");
 });

app.get('/getgeo',(req,res) => {
    res.send("true");
 });


 app.listen(port,()=> console.log('Running on port: '+port));