import {
  ConnectedSocket,
  MessageBody,
  SubscribeMessage,
  WebSocketGateway,
  WebSocketServer,
} from '@nestjs/websockets';
import { Server, Socket } from 'socket.io';
import { UnoService } from './uno.service';
import { UnoCard } from './uno.types';

type JoinPayload = {
  roomId: string;
  playerName: string;
};

type PlayPayload = {
  roomId: string;
  card: UnoCard;
};

@WebSocketGateway({ namespace: '/uno', cors: { origin: '*' } })
export class UnoGateway {
  @WebSocketServer()
  server!: Server;

  constructor(private readonly unoService: UnoService) {}

  @SubscribeMessage('uno:createRoom')
  handleCreateRoom(@MessageBody() payload: { roomId: string }): void {
    const room = this.unoService.createRoom(payload.roomId);
    this.server.to(payload.roomId).emit('uno:state', room);
  }

  @SubscribeMessage('uno:joinRoom')
  handleJoinRoom(
    @ConnectedSocket() client: Socket,
    @MessageBody() payload: JoinPayload,
  ): void {
    client.join(payload.roomId);
    const room = this.unoService.joinRoom(payload.roomId, client.id, payload.playerName);
    this.server.to(payload.roomId).emit('uno:state', room);
  }

  @SubscribeMessage('uno:startGame')
  handleStartGame(@MessageBody() payload: { roomId: string }): void {
    const room = this.unoService.startGame(payload.roomId);
    this.server.to(payload.roomId).emit('uno:state', room);
  }

  @SubscribeMessage('uno:playCard')
  handlePlayCard(
    @ConnectedSocket() client: Socket,
    @MessageBody() payload: PlayPayload,
  ): void {
    const room = this.unoService.playCard(payload.roomId, client.id, payload.card);
    this.server.to(payload.roomId).emit('uno:state', room);
  }

  @SubscribeMessage('uno:drawCard')
  handleDrawCard(
    @ConnectedSocket() client: Socket,
    @MessageBody() payload: { roomId: string },
  ): void {
    const room = this.unoService.drawCard(payload.roomId, client.id);
    this.server.to(payload.roomId).emit('uno:state', room);
  }

  @SubscribeMessage('uno:challengeWildDrawFour')
  handleChallengeWildDrawFour(
    @ConnectedSocket() client: Socket,
    @MessageBody() payload: { roomId: string },
  ): void {
    const room = this.unoService.challengeWildDrawFour(payload.roomId, client.id);
    this.server.to(payload.roomId).emit('uno:state', room);
  }
}
