var express = require('express');
var router = express.Router();

/* GET home page. */
router.get('/', function(req, res, next) {
  res.sendStatus(204);
  next();
});

module.exports = router;
