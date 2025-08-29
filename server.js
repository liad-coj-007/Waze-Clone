const express = require('express');
const fs = require('fs');
const cors = require('cors');
const app = express();
const { execFile } = require('child_process');
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
      
    execFile(binaryPath, args, (error, stdout, stderr) => {
        if (error) {
            console.error("Error: ", error);
            return res.status(500).send({ error: error.message });
        }
        console.log(stdout);
        res.send({ output: stdout, error: stderr });
    });

}

app.use(express.static('public')); 

app.listen(3000, () => console.log('Server running on port 3000'));
