const express = require('express');
const app = express();
const cors = require('cors');

app.use(cors());

const PORT = process.env.PORT || 5000;


app.get('/api/pacakges:name', (req,res)=>{
     const name = req.params.name;
})



app.listen(PORT, ()=>{
  console.log("Server, Running");
})
