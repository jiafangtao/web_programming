// demo of map
type Resolver<T> = (value: T | PromiseLike<T>) => void
type Rejecter = (reason: string) => void
interface ResolverRejecter<T> {
    resolver: Resolver<T>
    rejecter: Rejecter
}

class ResolveContext<T> {
    private _map = new Map<string, ResolverRejecter<T>>()

    constructor() {
        this._map = new Map()
    }

    add(key: string, resolver: Resolver<T>, rejecter: Rejecter) {
        this._map.set(key, {resolver, rejecter})
    }

    resolve(key: string, result?: T) {
        if (this._map.has(key)) {
            const { resolver } = this._map.get(key)
            console.log(resolver);
            resolver(result);
            this._map.delete(key)
        }
    }

    reject(key: string, reason: string) {
        if (this._map.has(key)) {
            const { rejecter } = this._map.get(key)
            console.log(rejecter);
            rejecter(reason);
            this._map.delete(key);
        }
    }

    withTimeout(key: string, timeOut: number) {
        setTimeout(() => {
            this.reject(key, 'time out')
        }, timeOut)
    }
}

const procContext = new ResolveContext<Object>()
const killContext = new ResolveContext<void>()

procContext.add("command_1", myResolver, myRejector);
procContext.add("command_2", myResolver, myRejector);


function myResolver(arg: Object) {
	console.log("calling myResolver with arg: ", arg);
}

function myRejector(arg: String) {
	console.log("calling myRejector with arg: ", arg);
}


setTimeout(function() {
	procContext.resolve("command_1", "bingo")
}, 3000);


setTimeout(function() {
	procContext.reject("command_2", "failed")
}, 3000);


var object = {
	first: "first",
	second: "second"
};

let { first } = object;
let { second } = object;

console.log(first);
console.log(second);
