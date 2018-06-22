const ExifImage = require('exif').ExifImage;
const process = require('process');

let imagePath = null;
const argv = require('optimist').argv;

if (argv && argv.f) {
    imagePath = argv.f;
}
else {
    console.log ("Usage: " + __filename + "-f filepath");
    process.exit(1);
}

try {
    new ExifImage({'image': imagePath}, function (err, exifData) {
        if (err) {
            console.log ("Error: " + err.message);
        }
        else {
            console.log(exifData);
        }
    });
}
catch(error) {
    console.log ('Error: ' + error.message);
}
