// const app = require('express')();
// const bodyParser = require('body-parser');

// const port = 10043;

// app.use(bodyParser.json());

// app.post('/', (req, res) => {
//   const data = req.body;

//   console.log(`Problem name: ${data.name}`);
//   console.log(`Problem group: ${data.group}`);
//   console.log('Full body:');
//   console.log(JSON.stringify(data, null, 4));

//   res.sendStatus(200);
// });

// app.listen(port, err => {
//   if (err) {
//     console.error(err);
//     process.exit(1);
//   }

//   console.log(`Listening on port ${port}`);
// });
const { execFile } = require('child_process');

const compiler = "g++";
const version = "-std=c++17";
const out ="-o";
const infile = "contest.cpp";
const outfile = "contest.out";
const command = "hello world";

execFile(compiler, [version,infile, out, outfile], (err, stdout, stderr) => {
  if (err) {
    console.log(err);
  } else {
    let executable = `./${outfile}`;
    execFile(executable, (err, stdout, stderr) => {
      if (err) {
        console.log(err);
      } else {
        execFile("echo", [command], { shell: true }, (err, stdout, stderr) => {
          if (err) {
            console.log(err);
          } else {
            console.log(`what is printed to the console: ${stdout}`);
          }
        });
      }
    })
  }
})