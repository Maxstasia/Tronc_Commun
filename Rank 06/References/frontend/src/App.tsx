import { useEffect, useMemo, useState } from 'react';
import { UnoClient } from './uno-client';
import { UnoCard, UnoColor, UnoGameState } from './types';

const backendUrl =
  import.meta.env.VITE_BACKEND_URL ?? `${window.location.protocol}//${window.location.hostname}:3000`;

function formatCard(card: UnoCard): string {
  switch (card.kind) {
    case 'number':
      return `${card.color ?? 'no-color'} ${card.value ?? '-'}`;
    case 'skip':
    case 'reverse':
    case 'drawTwo':
      return `${card.color ?? 'no-color'} ${card.kind}`;
    case 'wild':
    case 'wildDrawFour':
      return card.declaredColor ? `${card.kind} -> ${card.declaredColor}` : card.kind;
    default:
      return card.kind;
  }
}

export function App(): JSX.Element {
  const [roomId, setRoomId] = useState('room-1');
  const [playerName, setPlayerName] = useState('player');
  const [state, setState] = useState<UnoGameState | null>(null);
  const [selectedCardIndex, setSelectedCardIndex] = useState<number>(0);
  const [declaredColor, setDeclaredColor] = useState<UnoColor>('red');
  const [socketId, setSocketId] = useState<string | undefined>(undefined);

  const client = useMemo(() => new UnoClient(backendUrl), []);

  useEffect(() => {
    const onState = (next: UnoGameState): void => {
      setState(next);
      setSelectedCardIndex(0);
    };
    const onConnect = (): void => {
      setSocketId(client.getSocketId());
    };

    onConnect();
    client.onState(onState);
    client.onConnect(onConnect);

    return () => {
      client.offState(onState);
      client.offConnect(onConnect);
    };
  }, [client]);

  const me = socketId ? state?.players.find((player) => player.id === socketId) : undefined;
  const topCard = state?.discardPile[state.discardPile.length - 1];
  const currentPlayer =
    state && state.players.length > 0 ? state.players[state.currentPlayerIndex] : undefined;

  const selectedCard = me?.hand[selectedCardIndex];
  const isWildSelected =
    selectedCard?.kind === 'wild' || selectedCard?.kind === 'wildDrawFour';
  const isMyTurn = Boolean(me && currentPlayer && me.id === currentPlayer.id);
  const canPlaySelected = Boolean(selectedCard && state?.started && isMyTurn);
  const canDraw = Boolean(state?.started && isMyTurn);
  const canChallenge = Boolean(
    state?.pendingWildDrawFour && isMyTurn && me && state.pendingWildDrawFour.challengerId === me.id,
  );

  return (
    <main className="container">
      <h1>UNO - Transcendence 42</h1>

      <section className="panel">
        <label>
          Room ID
          <input value={roomId} onChange={(event) => setRoomId(event.target.value)} />
        </label>
        <label>
          Player name
          <input value={playerName} onChange={(event) => setPlayerName(event.target.value)} />
        </label>
        <div className="actions">
          <button onClick={() => client.createRoom(roomId)}>Create room</button>
          <button onClick={() => client.joinRoom(roomId, playerName)}>Join room</button>
          <button onClick={() => client.startGame(roomId)}>Start game</button>
          <button
            onClick={() => {
              if (canPlaySelected && selectedCard) {
                const payload: UnoCard = isWildSelected
                  ? { ...selectedCard, declaredColor }
                  : selectedCard;
                client.playCard(roomId, payload);
              }
            }}
            disabled={!canPlaySelected}
          >
            Play selected
          </button>
          <button onClick={() => client.drawCard(roomId)} disabled={!canDraw}>
            Draw card
          </button>
          {state?.pendingWildDrawFour && (
            <button onClick={() => client.challengeWildDrawFour(roomId)} disabled={!canChallenge}>
              Challenge
            </button>
          )}
        </div>
      </section>

      <section className="panel">
        <h2>Table</h2>
        <p>Top card: {topCard ? formatCard(topCard) : 'No card'}</p>
        <p>Current player: {currentPlayer?.name ?? '-'}</p>
        <p>You: {me?.name ?? playerName}</p>
        <p>Status: {state?.started ? 'In game' : 'Lobby / Finished'}</p>
        <p>Winner: {state?.winnerId ?? '-'}</p>
        <p>
          Pending +4 challenge:{' '}
          {state?.pendingWildDrawFour ? state.pendingWildDrawFour.challengerId : '-'}
        </p>
      </section>

      <section className="panel">
        <h2>Players</h2>
        <ul>
          {state?.players.map((player) => (
            <li key={player.id}>
              {player.name} - {player.hand.length} cards
            </li>
          ))}
        </ul>
      </section>

      <section className="panel">
        <h2>My hand ({me?.hand.length ?? 0})</h2>
        {me ? (
          <>
            <select
              value={selectedCardIndex}
              onChange={(event) => setSelectedCardIndex(Number(event.target.value))}
            >
              {me.hand.map((card, index) => (
                <option
                  key={`${card.kind}-${card.color ?? 'none'}-${card.value ?? 'none'}-${index}`}
                  value={index}
                >
                  {formatCard(card)}
                </option>
              ))}
            </select>
            {isWildSelected && (
              <label className="inline-control">
                Declared color
                <select
                  value={declaredColor}
                  onChange={(event) => setDeclaredColor(event.target.value as UnoColor)}
                >
                  <option value="red">red</option>
                  <option value="yellow">yellow</option>
                  <option value="green">green</option>
                  <option value="blue">blue</option>
                </select>
              </label>
            )}
            <p>Selected: {selectedCard ? formatCard(selectedCard) : '-'}</p>
          </>
        ) : (
          <p>Join the room with your player name to see your hand.</p>
        )}
      </section>
    </main>
  );
}
