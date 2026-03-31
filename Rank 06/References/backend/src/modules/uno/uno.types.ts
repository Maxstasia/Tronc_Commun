export type UnoColor = 'red' | 'yellow' | 'green' | 'blue';

export type UnoCardKind =
  | 'number'
  | 'skip'
  | 'reverse'
  | 'drawTwo'
  | 'wild'
  | 'wildDrawFour';

export type UnoCard = {
  kind: UnoCardKind;
  color?: UnoColor;
  value?: number;
  declaredColor?: UnoColor;
};

export type UnoPlayer = {
  id: string;
  name: string;
  hand: UnoCard[];
};

export type UnoPendingWildDrawFour = {
  offenderId: string;
  challengerId: string;
  offenderHadMatchingColor: boolean;
};

export type UnoGameState = {
  roomId: string;
  players: UnoPlayer[];
  drawPile: UnoCard[];
  discardPile: UnoCard[];
  currentPlayerIndex: number;
  direction: 1 | -1;
  started: boolean;
  winnerId?: string;
  pendingWildDrawFour?: UnoPendingWildDrawFour;
};
