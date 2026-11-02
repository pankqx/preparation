# The necklace in the live preview

When you hold the necklace button and speak, your words appear in the live preview at https://pankqx.github.io/preparation/. Each turn is saved as a check-in, a journal note and a chat line, and the laptop speaks the reply (the necklace has no speaker now).

```
necklace (mic + button) ──Wi-Fi──▶ hub on the laptop ──/events──▶ live preview in Chrome on the same laptop
                                   speech to text, reply, voice    "Necklace heard you", saved, reply played
```

## Before the demo (5 minutes)

1. **Laptop and necklace on the same hotspot.**
2. **Start the hub** on the laptop, from the MindMirror repo:
   ```
   cd hub
   npm install          (first time only)
   npm start
   ```
   `hub/.env` holds `GROQ_API_KEY=...`. With no internet, add the line `MOCK_AI=1` to `.env` and run `npm run mock`. Every turn then gets a fixed sample sentence and reply.
3. **Power the necklace.** It finds the hub by itself (the hub announces itself on the hotspot every 2 s). The hub window prints `[talk] ...` when it hears you.
4. **Open the app on the same laptop in Chrome or Edge**, with the hub address in the link:
   ```
   https://pankqx.github.io/preparation/?hub=http://localhost:8787
   ```
   If Chrome asks to let the page reach devices on your local network, click **Allow**. The app remembers the address and the necklace setting after this.

## On stage

1. The app opens with "Calm the sea". Tap the five balls, or tap Skip.
2. Pick **Voice mode**. The top right says **Necklace on**.
3. Hold the necklace button, speak, and let go. The orb says "Your necklace heard you. Thinking…". Then your words and the reply appear, and the laptop speaks the reply.
4. Open **Today** or **Insights**. The turn is now part of today's check-ins, so the signals move.
5. You don't have to be in Voice mode: on any screen a "Necklace heard you" card slides in from the top.

## If something goes wrong

| You see | Do this |
|---|---|
| "Looking…" or "Necklace off" at the top of Voice mode | The hub isn't running, or the address is wrong. Tap the small **laptop hub:** line at the bottom of Voice mode and type `http://localhost:8787`. |
| The necklace beeps sadly | The hub got no audio or no reply. Check the hub window for `[error]`. Hold the button a little longer while you speak. |
| No necklace at all | In Voice mode, hold the big mic button, or hold the **space bar** on the laptop. It goes through the same hub. |
| No hub, no internet | Voice mode still works: Whisper runs inside the browser (it downloads about 40 MB the first time), and the built-in companion replies. |

Only the laptop works with the GitHub Pages copy. A phone can't reach the laptop from an https page. To demo on a phone, use the Round 2 app that the laptop serves (`npm run phone` in the MindMirror repo).

## How it is wired (for the judges)

- The hub (`hub/server.mjs` in pankqx/MindMirror) already sends every voice turn on `GET /events` (Server-Sent Events): `{"type":"thinking"}` when audio arrives, then `{"type":"turn","heard","reply","mood","signals","audio"}`.
- The preview listens there (`src/lib/hub.ts` in pankqx/checking). Each turn becomes:
  - a check-in. The mood comes from the hub's `mood`, and the tags come from its `signals` (sleep → tired, pressure → deadlines, isolation → alone).
  - a journal note.
  - two chat lines.
- The preview then plays `/audio/<id>` on the laptop.
- Voice mode sends the phone or laptop mic recording to `POST /talk?src=web`.
