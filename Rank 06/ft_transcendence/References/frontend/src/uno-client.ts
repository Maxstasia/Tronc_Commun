import { io, Socket } from 'socket.io-client';
import { UnoCard, UnoGameState } from './types';

export class UnoClient {
  private socket: Socket;

  constructor(url: string) {
    this.socket = io(`${url}/uno`);
  }

  onState(handler: (state: UnoGameState) => void): void {
    this.socket.on('uno:state', handler);
  }

  offState(handler: (state: UnoGameState) => void): void {
    this.socket.off('uno:state', handler);
  }

  onConnect(handler: () => void): void {
    this.socket.on('connect', handler);
  }

  offConnect(handler: () => void): void {
    this.socket.off('connect', handler);
  }

  getSocketId(): string | undefined {
    return this.socket.id;
  }

  createRoom(roomId: string): void {
    this.socket.emit('uno:createRoom', { roomId });
  }

  joinRoom(roomId: string, playerName: string): void {
    this.socket.emit('uno:joinRoom', { roomId, playerName });
  }

  startGame(roomId: string): void {
    this.socket.emit('uno:startGame', { roomId });
  }

  playCard(roomId: string, card: UnoCard): void {
    this.socket.emit('uno:playCard', { roomId, card });
  }

  drawCard(roomId: string): void {
    this.socket.emit('uno:drawCard', { roomId });
  }

  challengeWildDrawFour(roomId: string): void {
    this.socket.emit('uno:challengeWildDrawFour', { roomId });
  }
}
