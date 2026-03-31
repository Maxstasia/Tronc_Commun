import { Injectable } from '@nestjs/common';
import { UnoEngine } from './uno.engine';
import { UnoCard, UnoColor, UnoGameState, UnoPlayer } from './uno.types';

@Injectable()
export class UnoService {
  private readonly rooms = new Map<string, UnoGameState>();

  constructor(private readonly unoEngine: UnoEngine) {}

  createRoom(roomId: string): UnoGameState {
    const existing = this.rooms.get(roomId);
    if (existing) {
      return existing;
    }

    const deck = this.unoEngine.createDeck();
    const firstCard = this.drawInitialTopCard(deck);

    if (!firstCard) {
      throw new Error('Deck generation failed');
    }

    const state: UnoGameState = {
      roomId,
      players: [],
      drawPile: deck,
      discardPile: [firstCard],
      currentPlayerIndex: 0,
      direction: 1,
      started: false,
    };

    this.rooms.set(roomId, state);
    return state;
  }

  getRoom(roomId: string): UnoGameState | undefined {
    return this.rooms.get(roomId);
  }

  joinRoom(roomId: string, playerId: string, name: string): UnoGameState {
    const room = this.createRoom(roomId);
    const alreadyPresent = room.players.some((player) => player.id === playerId);
    if (alreadyPresent) {
      return room;
    }

    const player: UnoPlayer = { id: playerId, name, hand: [] };
    room.players.push(player);
    return room;
  }

  startGame(roomId: string): UnoGameState {
    const room = this.rooms.get(roomId);
    if (!room) {
      throw new Error('Room not found');
    }

    if (room.players.length < 2) {
      throw new Error('At least 2 players are required');
    }

    if (room.started) {
      return room;
    }

    room.winnerId = undefined;
    room.pendingWildDrawFour = undefined;

    for (const player of room.players) {
      for (let index = 0; index < 7; index += 1) {
        const drawn = room.drawPile.pop();
        if (!drawn) {
          throw new Error('Not enough cards to start');
        }
        player.hand.push(drawn);
      }
    }

    room.started = true;
    room.currentPlayerIndex = 0;
    return room;
  }

  playCard(roomId: string, playerId: string, card: UnoCard): UnoGameState {
    const room = this.rooms.get(roomId);
    if (!room) {
      throw new Error('Room not found');
    }

    if (!room.started) {
      throw new Error('Game not started');
    }

    if (room.pendingWildDrawFour) {
      throw new Error('Resolve Wild Draw Four challenge first');
    }

    const currentPlayer = room.players[room.currentPlayerIndex];
    if (!currentPlayer || currentPlayer.id !== playerId) {
      throw new Error('Not your turn');
    }

    const handIndex = this.findCardIndexInHand(currentPlayer.hand, card);
    if (handIndex < 0) {
      throw new Error('Card not in hand');
    }

    if ((card.kind === 'wild' || card.kind === 'wildDrawFour') && !card.declaredColor) {
      throw new Error('Declared color is required for wild cards');
    }

    const topCard = room.discardPile[room.discardPile.length - 1];
    if (!topCard || !this.unoEngine.isPlayable(card, topCard)) {
      throw new Error('Invalid card');
    }

    const previousActiveColor = this.unoEngine.getActiveColor(topCard);
    const offenderHadMatchingColor =
      card.kind === 'wildDrawFour' && previousActiveColor
        ? currentPlayer.hand.some(
            (handCard, index) =>
              index !== handIndex && this.cardMatchesColor(handCard, previousActiveColor),
          )
        : false;

    const [played] = currentPlayer.hand.splice(handIndex, 1);
    if (!played) {
      throw new Error('Card not in hand');
    }

    const playedCard: UnoCard =
      card.kind === 'wild' || card.kind === 'wildDrawFour'
        ? { ...played, declaredColor: card.declaredColor }
        : played;

    room.discardPile.push(playedCard);

    if (currentPlayer.hand.length === 0) {
      room.winnerId = currentPlayer.id;
      room.started = false;
      room.pendingWildDrawFour = undefined;
      return room;
    }

    switch (playedCard.kind) {
      case 'skip':
        this.advanceTurn(room, 2);
        break;
      case 'reverse':
        if (room.players.length === 2) {
          this.advanceTurn(room, 2);
        } else {
          room.direction = room.direction === 1 ? -1 : 1;
          this.advanceTurn(room, 1);
        }
        break;
      case 'drawTwo': {
        const penalizedPlayerIndex = this.getNextPlayerIndex(room, room.currentPlayerIndex, 1);
        this.drawCards(room, penalizedPlayerIndex, 2);
        this.advanceTurn(room, 2);
        break;
      }
      case 'wild':
        this.advanceTurn(room, 1);
        break;
      case 'wildDrawFour': {
        const challengerIndex = this.getNextPlayerIndex(room, room.currentPlayerIndex, 1);
        const challenger = room.players[challengerIndex];
        if (!challenger) {
          throw new Error('Challenger not found');
        }

        room.pendingWildDrawFour = {
          offenderId: currentPlayer.id,
          challengerId: challenger.id,
          offenderHadMatchingColor,
        };
        room.currentPlayerIndex = challengerIndex;
        break;
      }
      case 'number':
      default:
        this.advanceTurn(room, 1);
        break;
    }

    return room;
  }

  challengeWildDrawFour(roomId: string, playerId: string): UnoGameState {
    const room = this.rooms.get(roomId);
    if (!room) {
      throw new Error('Room not found');
    }

    if (!room.started) {
      throw new Error('Game not started');
    }

    const pending = room.pendingWildDrawFour;
    if (!pending) {
      throw new Error('No Wild Draw Four to challenge');
    }

    const currentPlayer = room.players[room.currentPlayerIndex];
    if (!currentPlayer || currentPlayer.id !== playerId || currentPlayer.id !== pending.challengerId) {
      throw new Error('Not your turn');
    }

    if (pending.offenderHadMatchingColor) {
      const offenderIndex = this.getPlayerIndexById(room, pending.offenderId);
      this.drawCards(room, offenderIndex, 4);
      room.pendingWildDrawFour = undefined;
      room.currentPlayerIndex = this.getPlayerIndexById(room, playerId);
      return room;
    }

    this.drawCards(room, room.currentPlayerIndex, 6);
    room.pendingWildDrawFour = undefined;
    this.advanceTurn(room, 1);
    return room;
  }

  drawCard(roomId: string, playerId: string): UnoGameState {
    const room = this.rooms.get(roomId);
    if (!room) {
      throw new Error('Room not found');
    }

    if (!room.started) {
      throw new Error('Game not started');
    }

    const currentPlayer = room.players[room.currentPlayerIndex];
    if (!currentPlayer || currentPlayer.id !== playerId) {
      throw new Error('Not your turn');
    }

    if (room.pendingWildDrawFour) {
      if (room.pendingWildDrawFour.challengerId !== playerId) {
        throw new Error('Not your turn');
      }
      this.drawCards(room, room.currentPlayerIndex, 4);
      room.pendingWildDrawFour = undefined;
      this.advanceTurn(room, 1);
      return room;
    }

    this.drawCards(room, room.currentPlayerIndex, 1);
    this.advanceTurn(room, 1);
    return room;
  }

  private drawInitialTopCard(deck: UnoCard[]): UnoCard | undefined {
    const initialDeckSize = deck.length;

    for (let drawCount = 0; drawCount < initialDeckSize; drawCount += 1) {
      const candidate = deck.pop();
      if (!candidate) {
        break;
      }

      if (candidate.kind === 'wild' || candidate.kind === 'wildDrawFour') {
        deck.unshift(candidate);
        continue;
      }

      return candidate;
    }

    return undefined;
  }

  private findCardIndexInHand(hand: UnoCard[], cardToFind: UnoCard): number {
    return hand.findIndex((handCard) => {
      if (handCard.kind !== cardToFind.kind) {
        return false;
      }

      switch (handCard.kind) {
        case 'number':
          return handCard.color === cardToFind.color && handCard.value === cardToFind.value;
        case 'skip':
        case 'reverse':
        case 'drawTwo':
          return handCard.color === cardToFind.color;
        case 'wild':
        case 'wildDrawFour':
          return true;
        default:
          return false;
      }
    });
  }

  private cardMatchesColor(card: UnoCard, color: UnoColor): boolean {
    return card.color === color;
  }

  private drawCards(room: UnoGameState, playerIndex: number, count: number): void {
    const player = room.players[playerIndex];
    if (!player) {
      throw new Error('Player not found');
    }

    for (let index = 0; index < count; index += 1) {
      player.hand.push(this.drawFromPile(room));
    }
  }

  private drawFromPile(room: UnoGameState): UnoCard {
    if (room.drawPile.length === 0) {
      this.refillDrawPile(room);
    }

    const card = room.drawPile.pop();
    if (!card) {
      throw new Error('No card available');
    }

    return card;
  }

  private getPlayerIndexById(room: UnoGameState, playerId: string): number {
    const playerIndex = room.players.findIndex((player) => player.id === playerId);
    if (playerIndex < 0) {
      throw new Error('Player not found');
    }

    return playerIndex;
  }

  private advanceTurn(room: UnoGameState, steps: number): void {
    room.currentPlayerIndex = this.getNextPlayerIndex(room, room.currentPlayerIndex, steps);
  }

  private refillDrawPile(room: UnoGameState): void {
    if (room.discardPile.length <= 1) {
      return;
    }

    const topCard = room.discardPile[room.discardPile.length - 1];
    if (!topCard) {
      return;
    }

    const rest = room.discardPile.slice(0, -1);
    room.discardPile = [topCard];

    for (let index = rest.length - 1; index > 0; index -= 1) {
      const randomIndex = Math.floor(Math.random() * (index + 1));
      const temp = rest[index];
      rest[index] = rest[randomIndex];
      rest[randomIndex] = temp;
    }

    room.drawPile.push(...rest);
  }

  private getNextPlayerIndex(room: UnoGameState, fromIndex: number, steps = 1): number {
    const rawIndex = fromIndex + room.direction * steps;
    return (rawIndex % room.players.length + room.players.length) % room.players.length;
  }
}
