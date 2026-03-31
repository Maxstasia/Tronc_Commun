import { Injectable } from '@nestjs/common';
import { UnoCard, UnoColor } from './uno.types';

@Injectable()
export class UnoEngine {
  createDeck(): UnoCard[] {
    const colors: UnoColor[] = ['red', 'yellow', 'green', 'blue'];
    const deck: UnoCard[] = [];

    for (const color of colors) {
      deck.push({ kind: 'number', color, value: 0 });

      for (let value = 1; value <= 9; value += 1) {
        deck.push({ kind: 'number', color, value });
        deck.push({ kind: 'number', color, value });
      }

      deck.push({ kind: 'skip', color });
      deck.push({ kind: 'skip', color });
      deck.push({ kind: 'reverse', color });
      deck.push({ kind: 'reverse', color });
      deck.push({ kind: 'drawTwo', color });
      deck.push({ kind: 'drawTwo', color });
    }

    for (let index = 0; index < 4; index += 1) {
      deck.push({ kind: 'wild' });
      deck.push({ kind: 'wildDrawFour' });
    }

    this.shuffle(deck);
    return deck;
  }

  isPlayable(cardToPlay: UnoCard, topCard: UnoCard): boolean {
    if (cardToPlay.kind === 'wild' || cardToPlay.kind === 'wildDrawFour') {
      return true;
    }

    const activeColor = this.getActiveColor(topCard);
    if (cardToPlay.color && activeColor && cardToPlay.color === activeColor) {
      return true;
    }

    if (cardToPlay.kind === 'number' && topCard.kind === 'number') {
      return cardToPlay.value === topCard.value;
    }

    return cardToPlay.kind === topCard.kind;
  }

  getActiveColor(card: UnoCard): UnoColor | undefined {
    if (card.kind === 'wild' || card.kind === 'wildDrawFour') {
      return card.declaredColor;
    }

    return card.color;
  }

  private shuffle(cards: UnoCard[]): void {
    for (let index = cards.length - 1; index > 0; index -= 1) {
      const randomIndex = Math.floor(Math.random() * (index + 1));
      const temp = cards[index];
      cards[index] = cards[randomIndex];
      cards[randomIndex] = temp;
    }
  }
}
