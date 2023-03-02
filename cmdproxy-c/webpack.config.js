// webpack.config.js

const path = require('path');

module.exports = {
    entry: './public/main',
    output: {
        path: path.resolve(__dirname, 'output'),
        filename: '[name].[hash].js'
    }
};
