const express = require('express');
const fs = require('fs');
const cors = require('cors');
const app = express();
const { spawnSync  } = require('child_process');
const { error } = require('console');
const { stderr, stdout } = require('process');


app.use(cors()); // fecth the web
app.use(express.json());

//post save json
app.post('/save', (req, res) => {
  fs.writeFileSync('save/road_data.json', JSON.stringify(req.body, null, 2));
  res.send({ status: 'ok' });
});



app.post('/run-binary', getResult);

function getResult(req,res){
    
    const binaryPath = 'build/main';
    const args = ["save/road_data.json"]; 

    const data = req.body;

    const child = spawnSync(binaryPath, [], {
        input: JSON.stringify(data), 
        encoding: 'utf-8'
    });
    
    sendRoad(child,res);
}

function sendRoad(child,res){
    if(child.error){
        console.error("child process failed:",child.error);
        return;
    }

    try{
        console.log("STDOUT from child:", 
        JSON.stringify(child.stdout));
        const json = JSON.parse(child.stdout);
        res.send({
            success : isFinite(json.dist),
            road : json.road
        });

    }catch(err){
        console.error("invalid JSON from child:",err);
        res.status(500).send({ error: 'Invalid JSON from binary' });
    }


}

app.use(express.static('public')); 

app.listen(3000, () => console.log('Server running on port 3000'));
