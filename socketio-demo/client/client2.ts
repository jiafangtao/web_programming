import { io } from 'socket.io-client';

export class Socket {
    private m_timer: number;
    private m_socket;
    private m_query = {
        connectionTimes: 0
    };
    private m_onClose = async () => {
        // we don't care what the server returns
        await fetch("/api/net/socket/" + this.id, {
            method: 'DELETE',
            headers: {
                'Accept': 'application/json',
                'Content-Type': 'application/json'
            }
        });
    }

    constructor() {
    }

    open(): void {
        this.m_socket = io({
            transports: ['websocket', 'polling'],
            upgrade: true,
            reconnection: false,
            autoConnect: false,
            query: this.m_query
        });

        this.m_socket.on('error', (error) => { console.error(error)})

        this.m_socket.on('connect', (socket) => {
            console.log("connected, socket id: ", socket.id);

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

        this.m_socket.on('message', (message: Object) => {
            this.onMessage(message);
        });
        this.m_socket.on('event', (event: Object) => {
            this.onEvent(event);
        });
        this.m_socket.connect();
    }

    close(): void {
        this.doClose();
    }

    private doClose() {
        this.m_socket.disconnect();
        window.removeEventListener('beforeunload', this.m_onClose);            
        this.m_socket = undefined;
    }

    get connected(): boolean {
        return this.m_socket.connected;
    }

    get id(): string {
        return this.m_socket.id;
    }

    onOpen(): void {

    }

    onClose(): void {

    }

    onMessage(message: Object): void {

    }

    onEvent(event: Object): void {

    }
}

const client = new Socket();
client.open();
