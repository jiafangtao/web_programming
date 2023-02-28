var express = require('express');
var router = express.Router();

router.get('/', function(req, res, next) {
  res.json({'description': 'All commands supported in this namespace ......'});
});


router.get('/ls', function(req, res, next) {
  res.json({'action': 'ls', 'type': 'command'});
});

module.exports = router;
