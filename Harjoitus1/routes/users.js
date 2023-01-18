const { response } = require('express');
var express = require('express');
var router = express.Router();

/* GET users listing. */
router.get('/', function(req, res, next) {
  res.send('respond with a resource');
  console.log("Kukkuluuruu");
});

router.use(function (request, response,next)
{
  
  console.log("Olen middleware 1");
  next();
});

router.get('/toka',function(req,res,next){
  res.send("Olen toka :D");
  console.log("Tokapa hyvinkin");
});

router.use(function (request, response,next)
{
  
  console.log("Olen middleware 2");
  next();
});


router.get('/kolmas/:nimi',function(req,res,next){
  res.send("Olen toki vaan "+req.params.nimi);
  console.log(req.params.nimi);
});

router.use(function (request, response,next)
{
  console.log("Olen middleware 3");
  next();
});

router.get('/kolmas/:enimi/:snimi',function(req,res,next){
  res.send("Olen toki vaan "+req.params.enimi+" "+req.params.snimi);
  console.log(req.params.enimi+" "+req.params.snimi);
});
router.use(function (request, response,next)
{
  console.log("Olen middleware 4");
  next();
});


router.post('/',function(request,response)
{
  response.send(request.body);

});

module.exports = router;
