console.log("consume stuff from extract.mjs")

import {Footer, Header, TwoPi} from './extract.mjs'

console.log(Header())
console.log(Footer())

console.log("2 * pi = ", TwoPi)


import helloworld from './extract.mjs'

console.log("use default export: ", helloworld)
