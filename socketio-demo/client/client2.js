var __awaiter = (this && this.__awaiter) || function (thisArg, _arguments, P, generator) {
    function adopt(value) { return value instanceof P ? value : new P(function (resolve) { resolve(value); }); }
    return new (P || (P = Promise))(function (resolve, reject) {
        function fulfilled(value) { try { step(generator.next(value)); } catch (e) { reject(e); } }
        function rejected(value) { try { step(generator["throw"](value)); } catch (e) { reject(e); } }
        function step(result) { result.done ? resolve(result.value) : adopt(result.value).then(fulfilled, rejected); }
        step((generator = generator.apply(thisArg, _arguments || [])).next());
    });
};
const io = require('socket.io-client');
class Socket {
    constructor() {
        this.m_query = {
            connectionTimes: 0
        };
        this.m_onClose = () => __awaiter(this, void 0, void 0, function* () {
            // we don't care what the server returns
            yield fetch("/api/net/socket/" + this.id, {
                method: 'DELETE',
                headers: {
                    'Accept': 'application/json',
                    'Content-Type': 'application/json'
                }
            });
        });
    }
    open() {
        this.m_socket = io({
            transports: ['websocket', 'polling'],
            upgrade: true,
            reconnection: true,
            autoConnect: false,
            query: this.m_query
        });
        this.m_socket.on('connect', () => {
            console.log("Connected.");
            if (this.m_query['socketId'] === undefined) {
                // first time to connect websocket server
                this.m_query['socketId'] = this.m_socket.id;
                window.addEventListener('beforeunload', this.m_onClose);
            }
            if (this.m_timer !== undefined) {
                clearTimeout(this.m_timer);
                this.m_timer = undefined;
            }
            this.m_query.connectionTimes++;
            this.onOpen();
        });
        this.m_socket.on("disconnect", (reason) => {
            if (reason === 'transport close' ||
                reason === 'ping timeout') {
                this.m_timer = setTimeout(() => {
                    this.m_timer = undefined;
                    this.m_query.connectionTimes = 0;
                    delete this.m_query['socketId'];
                    this.doClose();
                }, 10 * 60 * 1000);
            }
        });
        this.m_socket.on('message', (message) => {
            this.onMessage(message);
        });
        this.m_socket.on('event', (event) => {
            this.onEvent(event);
        });
        this.m_socket.connect();
    }
    close() {
        this.doClose();
    }
    doClose() {
        this.m_socket.disconnect();
        window.removeEventListener('beforeunload', this.m_onClose);
        this.m_socket = undefined;
    }
    get connected() {
        return this.m_socket.connected;
    }
    get id() {
        return this.m_socket.id;
    }
    onOpen() {
    }
    onClose() {
    }
    onMessage(message) {
        console.log("bingo~~ we got a message: ", message)
    }
    onEvent(event) {
    }
}
const client = new Socket();
client.open();
//# sourceMappingURL=client2.js.map