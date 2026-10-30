# MindMirror app: rebuild guide for Round 2

**Owner:** Pankaj (tech lead), with Kishore on screens and Merel on all words and content.
**Goal by hour 24:** a working web app on the laptop where a student checks in, sees early signs compared with *their own* normal, talks to the companion (typed or through the necklace), and is pointed to the right support. Every number has its proof.

---

## 1. Scope: what to build, and what to leave out

Round 1 promised a lot (8 features, two visual worlds, games, a watch, on-device AI). Rebuilding all of that in 24 hours with two first-timers is how teams end up with ten half-working screens. **My strong recommendation: build five things that fully work, plus the necklace.** Judges score *Functionality* (20%) on whether it works, and *Technical complexity* (25%) on depth, not on screen count. The baseline engine + the necklace already give you depth.

| Priority | Feature | Why |
|---|---|---|
| **Must** (done by hour 12) | Daily check-in (mood, stress, energy, sleep hours, "talked to someone you like?") | the data everything else needs |
| **Must** | Insights: 5 signals vs *your own* baseline, "mind weather", proof for each | the core idea and the innovation |
| **Must** | Support ladder + crisis routing (Tele-MANAS 14416, 112, campus counsellor) | the "find support" half of the problem statement, and safety |
| **Must** | Companion chat (typed), through the hub | AI that explains, never diagnoses |
| **Must** | Necklace voice check-ins appear live in the app | the wow moment |
| **Should** (hours 12 to 18) | Planner: deadlines + hours needed vs hours planned ("PressureMap") | ties academic pressure to well-being; Round 1 judges liked it |
| **Should** | Breathing room (one 4-in 6-out animation) | a calming action after a heavy check-in |
| **Should** | "Explore with sample data" button (3 weeks of a student drifting) | the demo can't wait 2 weeks for real data |
| **Could** | Journal, habits, export/delete all data | only if ahead of time |
| **Cut** | Two visual worlds, ASCII games, smartwatch, on-device LLM, animated characters | beautiful, but each one is a day of work |

**Problem statement → feature map** (Merel uses this in the pitch):

| Problem statement says | Signal | Measured from |
|---|---|---|
| academic pressure | **Pressure** | stress check-ins + planner hours due vs hours planned |
| poor sleep | **Sleep** | sleep hours, last 3 nights vs your usual |
| isolation | **Connection** | "talked to someone you like?" last 4 days vs your usual |
| exhaustion | **Energy** | energy check-ins vs your usual |
| loss of motivation | **Drive** | mood + voice check-in tags ("motivation") vs your usual |
| "without diagnosing" | | we show *changes*, never labels; AI only explains numbers code already calculated |

---

## 2. Stack

Same as Round 1, because it worked and you know it:

| Part | Choice |
|---|---|
| App | **Vite + React + TypeScript** |
| Styling | **Tailwind CSS v4** |
| Animation | **framer-motion** (only for soft fades and the breathing circle) |
| Charts | **Recharts** |
| Storage | **Dexie** (IndexedDB, everything stays in the browser) |
| Tests | **Vitest** (for the signal engine only) |
| AI + voice | the **Hub** (`hub/server.mjs`, see the necklace guide): Groq for speech-to-text and replies, Edge TTS for voice |

The API key lives **only in the hub's `.env`**, never in the React app. The app calls `http://localhost:8787`.

---

## 3. Set up the new repo (Pankaj, first 30 minutes)

```bash
npm create vite@latest mindmirror -- --template react-ts
cd mindmirror
npm install
npm install dexie dexie-react-hooks framer-motion recharts
npm install -D tailwindcss @tailwindcss/vite vitest
```

`vite.config.ts`:

```ts
import { defineConfig } from "vite";
import react from "@vitejs/plugin-react";
import tailwindcss from "@tailwindcss/vite";
export default defineConfig({ plugins: [react(), tailwindcss()] });
```

`src/index.css`: first line `@import "tailwindcss";`

Then create the hub folder: copy `reference/hub/` from the preparation repo into `hub/` and run `npm install` inside it. Add to `.gitignore`: `node_modules`, `.env`, `dist`.

Add Merel and Kishore as collaborators (GitHub → Settings → Collaborators). Push. Everyone clones.

**Disclosure (the rules require it):** put this in the README on hour 1: *"Built during CODE MEET 2026 Round 2. Uses open-source libraries (listed in package.json), Groq and Microsoft Edge TTS APIs, and AI coding assistants (Claude, ChatGPT). Hardware reference code was prepared from our own design before the event."*

### Folder layout

```
mindmirror/
  hub/                    laptop server (necklace + AI)
  firmware/               ESP32 code (from the necklace guide)
  src/
    lib/
      db.ts               Dexie tables
      signals.ts          the engine (pure functions, tested)
      signals.test.ts
      sample.ts           3 weeks of demo data
      hub.ts              chat(), talk(), live events
      support.ts          support ladder + crisis words
    screens/
      Home.tsx  CheckIn.tsx  Insights.tsx  Companion.tsx  Support.tsx  Planner.tsx  Breathe.tsx
    components/           Kishore's buttons, cards, sliders, icons
    content/
      copy.ts             Merel's words: every label, prompt, tip
  README.md
```

---

## 4. Data model (`src/lib/db.ts`)

```ts
import Dexie, { type Table } from "dexie";

export interface CheckIn {
  id?: number;
  date: string;          // "2026-11-01" (one per day; a later one replaces the earlier)
  at: string;            // ISO time
  mood: number;          // 1..5
  stress: number;        // 1..5
  energy: number;        // 1..5
  sleepHours: number;    // 0..12
  connected: boolean;    // talked to someone you like today?
  note?: string;
  source: "tap" | "voice";
}

export interface VoiceTurn {
  id?: number;
  at: string;
  heard: string;         // what the student said
  reply: string;         // what MindMirror said
  mood: "good" | "okay" | "low" | "stressed" | "tired";
  signals: string[];     // "sleep" | "pressure" | "isolation" | "energy" | "motivation"
  source: "necklace" | "web";
}

export interface Task {
  id?: number;
  title: string;
  due: string;           // date
  hoursNeeded: number;
  hoursPlanned: number;
  done: boolean;
}

class DB extends Dexie {
  checkins!: Table<CheckIn, number>;
  voice!: Table<VoiceTurn, number>;
  tasks!: Table<Task, number>;
  constructor() {
    super("mindmirror");
    this.version(1).stores({ checkins: "++id, date", voice: "++id, at", tasks: "++id, due, done" });
  }
}
export const db = new DB();
```

---

## 5. The signal engine (`src/lib/signals.ts`), the heart of the project

Rule: **code calculates, AI only explains.** This file has no AI and no React, so it can be unit tested.

**Personal baseline.** For each measure, the baseline is the **median of days 4 to 17 ago** (14 days, skipping the recent window). Median, not average, so one bad night doesn't move it. Need at least 5 days of baseline data, otherwise the signal says "learning your normal".

**Recent value.** The average of the **last 3 days** (Connection: last 4 days).

**Change → level** (each signal is `steady`, `watch` or `needs care`):

| Signal | Recent vs baseline | watch | needs care |
|---|---|---|---|
| Sleep | hours | 0.75 h less | 1.5 h less |
| Energy | 1..5 | 0.75 lower | 1.25 lower |
| Pressure | stress 1..5, plus planner | stress 0.75 higher, or work due in 3 days > planned hours | stress 1.25 higher, or due > 1.5 × planned |
| Connection | share of days "yes" | 25 points lower | 50 points lower |
| Drive | mood 1..5, plus voice tags "motivation" in last 3 days | mood 0.75 lower | mood 1.25 lower, or 2+ "motivation" tags |

**Mind weather** from the five levels (count `needs care` as 2, `watch` as 1):

| Score | Weather | Support ladder rung |
|---|---|---|
| 0 to 1 | ☀️ Clear skies | look after yourself (keep doing what works) |
| 2 to 3 | ⛅ Passing clouds | small step today (breathe, sleep earlier, move one task) |
| 4 to 5 | 🌧 Soft rain | reach out (message a friend, mentor) |
| 6+ | ⛈ Heavy skies | talk to someone trained (campus counsellor; Tele-MANAS 14416) |

**Crisis words override everything**: any check-in note, chat or voice turn with crisis words shows the urgent help card immediately (Tele-MANAS **14416**, **112**), regardless of the weather.

**Every signal returns its proof**, e.g. `{ level: "needs care", text: "You slept 5.4 h on average the last 3 nights; your usual is 7.0 h (−1.6 h).", recent: 5.4, baseline: 7.0 }`. The Insights screen shows that sentence under each signal. That sentence is what judges remember.

**Tests (`signals.test.ts`)**: write at least these, then run `npx vitest run`:
1. Fewer than 5 baseline days → "learning your normal".
2. Steady sleep 7 h, then 3 nights at 5.4 h → Sleep `needs care`, text mentions −1.6 h.
3. One bad night alone → Sleep stays `steady` (median protects it).
4. Five signals at `needs care` → Heavy skies.
5. Note "I want to die" → crisis = true.

**Prompt for Claude (Pankaj):**
> Write `src/lib/signals.ts` in TypeScript for this spec: [paste section 5]. Pure functions only, no React, no Dexie imports. Input: arrays of CheckIn, VoiceTurn and Task (types: [paste section 4]) and a `today` date. Output: five signals with level, proof sentence, recent and baseline values, plus weather and ladder rung. Then write `signals.test.ts` with Vitest covering the five tests listed.

---

## 6. Screens

| Screen | What's on it | Owner |
|---|---|---|
| **Home** | greeting, today's mind weather (big, soft illustration), "Check in" button, last necklace message, 3 shortcut cards (Insights, Companion, Breathe) | Kishore builds, Pankaj wires |
| **Check-in** | 5 questions, one per card: mood (5 faces), stress, energy (sliders), sleep hours (stepper), "talked to someone you like?" (yes/no). Optional note. Under 60 s. | Kishore |
| **Insights** | weather at top; 5 signal cards (icon, level colour, proof sentence); one Recharts line: sleep last 21 days with a dashed baseline line | Pankaj (data), Kishore (cards) |
| **Companion** | chat bubbles; text box; "Hold to talk" mic button (web version of the necklace); list of necklace turns | Pankaj |
| **Support** | the ladder as 4 steps, current rung highlighted; buttons: call 14416, call 112, campus counsellor; "not a medical device" line | Merel writes, Kishore builds |
| **Planner** (should) | add task (title, due, hours needed, hours planned); a warning card when the next 3 days are overloaded, with "move to tomorrow" | Pankaj |
| **Breathe** (should) | one circle that grows for 4 s and shrinks for 6 s, 1-minute timer | Kishore |

**Design rules** (Kishore): calm, not clinical. Soft indigo, sage green, warm cream background, rounded cards, lots of space, one font (e.g. "Nunito" or "Poppins" from Google Fonts). **Red only for urgent help.** A signal that needs care is a soft coral, not red. Every screen readable on a phone width (the judges may try it on a phone).

**Words** (Merel): never "symptom", "disorder", "depressed", "diagnosis". Use "signs", "changes", "your usual", "needs care". Every tip is one small action.

---

## 7. Talking to the hub (`src/lib/hub.ts`)

```ts
const HUB = "http://localhost:8787";

export async function chat(text: string, context = "") {
  const r = await fetch(`${HUB}/chat`, {
    method: "POST",
    headers: { "Content-Type": "application/json" },
    body: JSON.stringify({ text, context }),
  });
  return (await r.json()) as { reply: string; mood: string; signals: string[]; crisis?: boolean };
}

// Live necklace turns. Call once in App.tsx; save each turn to Dexie.
export function onVoiceTurn(cb: (t: any) => void) {
  const es = new EventSource(`${HUB}/events`);
  es.onmessage = (e) => cb(JSON.parse(e.data));
  return () => es.close();
}

// "Hold to talk" in the browser: same hub, same AI, reply plays in the browser
export async function startTalk() {
  const stream = await navigator.mediaDevices.getUserMedia({ audio: true });
  const rec = new MediaRecorder(stream, { mimeType: "audio/webm" });
  const parts: Blob[] = [];
  rec.ondataavailable = (e) => parts.push(e.data);
  rec.start();
  return async function stop() {
    rec.stop();
    await new Promise((r) => (rec.onstop = r));
    stream.getTracks().forEach((t) => t.stop());
    const r = await fetch(`${HUB}/talk?src=web`, {
      method: "POST",
      headers: { "Content-Type": "audio/webm" },
      body: new Blob(parts, { type: "audio/webm" }),
    });
    new Audio(URL.createObjectURL(await r.blob())).play();
  };
}
```

The browser turn also arrives through `/events`, so one listener saves both necklace and web turns.

**Context for the companion:** when calling `chat()`, pass the proof sentences of signals that are `watch` or `needs care` as `context`. Then the AI can say "your sleep has been lower than usual this week" without inventing anything.

---

## 8. Privacy and safety (say this exactly, it's true)

- Check-ins, insights, tasks and chat history are stored **only in the browser** (IndexedDB). No accounts, no database server.
- Voice is sent to Groq to be turned into text and to write the reply, then discarded by us; we don't store audio anywhere. Replies are spoken by Microsoft's Edge voice service. A fully on-device version (which we built in Round 1) is the production path.
- MindMirror **never diagnoses**. It shows changes against your own normal and suggests small steps.
- Crisis words go straight to human help (Tele-MANAS 14416, 112), without asking the AI.
- One button deletes everything (`db.delete()`), if there's time.

---

## 9. Build order and checkpoints

| By hour | Done means |
|---|---|
| 1 | repo up, everyone can run `npm run dev`; hub runs with `/health` ok |
| 4 | Dexie + check-in screen saves a check-in; sample data button fills 21 days |
| 7 | `signals.ts` + 5 passing tests; Insights shows real proof sentences |
| 10 | Companion chat works through the hub; Support screen; crisis card |
| 12 | **Necklace turn appears live in the app.** Full flow demo-able. Commit and tag `v-mvp`. |
| 16 | Planner + Breathe; Kishore's final styling merged |
| 19 | bug bash: Merel tests every screen as a new user, writes issues |
| 20 | **Feature freeze.** Only fixes after this. Tag `v-demo`. |
| 24 | submitted |

If you're behind at hour 12, cut Planner and Breathe. Never cut the support/crisis screen.

---

## 10. Plan B list (things that can go wrong on the day)

| If | Then |
|---|---|
| Venue Wi-Fi blocks Groq | laptop on phone hotspot data |
| Groq rate-limited | create a second free key (another teammate's account) and swap in `.env` |
| Edge voice fails | in `server.mjs`, switch TTS to Groq's `canopylabs/orpheus-v1-english` (`/openai/v1/audio/speech`, `response_format: "wav"`, accept its terms in the Groq console first) and convert with the same ffmpeg step; ask Claude to make the change |
| No internet at all | run the hub with `MOCK_AI=1`: fixed transcript and reply; the app still logs the turn. Say so honestly if you have to demo this way. |
| Necklace dies | "Hold to talk" button in the Companion screen |
| Laptop dies | push to GitHub every hour; the second laptop can run everything |
