const express = require('express');
const fs = require('fs');
const cors = require('cors');
const app = express();

app.use(cors()); // fecth the web
app.use(express.json());

//post save json
app.post('/save', (req, res) => {
  fs.writeFileSync('save/road_data.json', JSON.stringify(req.body, null, 2));
  res.send({ status: 'ok' });
});

app.use(express.static('public')); 

app.listen(3000, () => console.log('Server running on port 3000'));
