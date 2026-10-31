# Merel's guide

You have three jobs in this hackathon:

1. **Developer:** you build the **Play room** (three calm games) and the **Support screen**, and you write every word the app says (`copy.ts`). That's your code in GitHub, under your name.
2. **Researcher:** you talk to real students on Sunday morning, and their words go into the app and the slides.
3. **Presenter:** you lead the final presentation on Monday at 10:00 and the demo video.

This guide explains the whole project in plain words first, so you can answer any question about it, not only about your part. Then it walks you through your code step by step.

---

## Part 1. MindMirror in plain words

### The problem (from the official problem statement "Mind Check")

Stress and burnout build up **slowly**: academic pressure, poor sleep, isolation, exhaustion, loss of motivation. Each single day looks fine. Students don't notice until it hurts their studies, relationships or daily life. We need technology that helps people **notice early signs, understand their patterns, and find support**, **without diagnosing** them.

### Our answer

MindMirror is a **web app** plus an **AI necklace**.

- Every day, the student does a **30-second check-in**: mood, stress, energy, hours of sleep, and "did you talk to someone you like today?". Or they hold the necklace's button and just *say* how they feel.
- The app compares the last few days with **the student's own normal** (their "baseline"). Not with a rule like "everyone needs 8 hours", but with *them*.
- It shows **five signals**, each with its **proof**: "You slept 5.4 hours on average the last 3 nights; your usual is 7.0 hours (−1.6 h)."
- The signals add up to a **mind weather**: ☀️ Clear skies, ⛅ Passing clouds, 🌧 Soft rain, ⛈ Heavy skies.
- The weather picks a step on the **support ladder**: look after yourself → one small step today → reach out to a friend → talk to someone trained (campus counsellor, Tele-MANAS 14416).
- **Calm tools** help right away: your **Play room** games, a breathing exercise, and a companion you can chat with.

### The five signals (memorise this table)

| Problem statement says | Our signal | How we measure it |
|---|---|---|
| academic pressure | **Pressure** | stress in check-ins + hours of work due vs hours planned |
| poor sleep | **Sleep** | hours slept, last 3 nights vs usual |
| isolation | **Connection** | "talked to someone you like?" last 4 days vs usual |
| exhaustion | **Energy** | energy in check-ins vs usual |
| loss of motivation | **Drive** | mood + what the student says to the necklace |

### What "baseline" means, simply

Imagine Asha usually sleeps 7 hours. This week she sleeps 5.5, 5.4 and 5.3. No single night is shocking, and 5.4 might be normal for her roommate. But for *Asha* it's 1.6 hours less than usual. That's the **drift** MindMirror notices. We use the **median** (the middle value) of her last two weeks as "usual", so one bad night doesn't change what normal means.

### The necklace, simply

The necklace has a tiny computer (ESP32), a microphone, a small amplifier and a speaker. You hold the button and talk. It sends your voice over Wi-Fi to a small program on our laptop (the "hub"). The hub:
1. turns your voice into text (an AI called Whisper),
2. writes a short, kind reply (a language model),
3. turns the reply into a voice (a text-to-speech service),

and sends the voice back to the necklace, which speaks it. At the same moment, the conversation appears in the app. It takes about 2 to 4 seconds.

### Safety, simply (you'll be asked about this most)

- **We never diagnose.** We never say "depressed" or "disorder". We say "changes", "your usual", "needs care".
- **Code calculates, AI only explains.** The numbers come from normal code that we tested. The AI only phrases them kindly.
- **Crisis words skip the AI.** If someone says "I want to die" or "hurt myself", the app and necklace give a fixed message: Tele-MANAS **14416** (free, 24×7) and **112**.
- **Privacy:** check-ins and history stay in the student's own browser. There are no accounts and no server database. Voice goes to the AI service to be understood, and we don't store it.

### Who built what (say this proudly)

- **Pankaj:** the signal engine, the hub, the necklace firmware, joining everything together.
- **Merel (you):** user research, every word in the app, the Play room games, the Support screen, the presentation.
- **Kishore:** the design, the UI components, the check-in and breathing screens, the hardware tests and the necklace's case.

---

## Part 2. Get ready before Sunday (1 hour)

1. Install **VS Code**, **Node.js 22 LTS** (nodejs.org), **GitHub Desktop** (sign in with *your* GitHub account), **Chrome**.
2. Read [JUDGE_QA.md](JUDGE_QA.md) twice. Read the deck's speaker notes aloud three times.

### React warm-up (20 minutes, on Saturday)

So Sunday isn't your first time. In a terminal:

```bash
npm create vite@latest practice -- --template react-ts
cd practice
npm install
npm run dev
```

Open the link it prints (http://localhost:5173). Now open `practice/src/App.tsx` in VS Code, delete everything, and paste:

```tsx
import { useState } from "react";

export default function App() {
  const [count, setCount] = useState(0);
  return (
    <div style={{ padding: 40, fontFamily: "sans-serif" }}>
      <h1>Hello Merel</h1>
      <button onClick={() => setCount(count + 1)}>Popped {count} bubbles</button>
    </div>
  );
}
```

Save, and the browser updates by itself. Click the button. That's React. Five ideas cover almost everything you'll do:

| Idea | In the code above | Meaning |
|---|---|---|
| **Component** | `function App()` | a function that returns what to show. Every game is one component. |
| **JSX** | `<h1>…</h1>` | HTML-like code inside TypeScript |
| **State** | `useState(0)` | a value the component remembers. Changing it redraws the screen. |
| **Event** | `onClick={…}` | what happens on a tap or click |
| **Props** | (not used here) | values passed *into* a component, like `<Game title="Bubble wrap" />` |

Try it: change "Hello Merel" and save. Change `+ 1` to `+ 2`. Break something on purpose (delete a `}`) and read the red error. Then fix it. You're ready.

---

## Part 3. Your code on Sunday

**Every time you start a ChatGPT chat for code, paste this context first:**

> I'm building part of a React + TypeScript + Tailwind CSS v4 web app called MindMirror, a calm well-being app for college students. I'm a beginner, so give me complete files I can paste, and explain anything new in one or two lines. Style: soft indigo (#4F5BD5), sage green (#8FB9A8), warm cream background (#FBF7F0), coral (#E8836B), red only for emergency buttons. Font Nunito. Rounded corners (rounded-2xl), soft shadows, lots of space, calm and gentle, never clinical. Mobile first (max width 480px, centred). Only Tailwind classes and framer-motion (already installed). No other libraries.

**The loop for every file:** paste the prompt → copy the code into the file → save → look at the browser → if there's an error, copy the *whole* red message to ChatGPT with "fix this" → when it works, **commit** in GitHub Desktop with a clear message → **push** → **pull request**. If it's still broken after two tries, ask Pankaj or Kishore.

**How to see your game while you build it:** Pankaj will add a Play link in the app. Until then, temporarily show it in `src/App.tsx`: `import BubbleWrap from "./games/BubbleWrap";` and put `<BubbleWrap />` inside the return. Don't commit that change to `App.tsx` (untick it in GitHub Desktop).

### 3.1 `src/content/copy.ts`: every word the app says (11:30, first commit)

> Write the text for MindMirror, a calm student well-being app. Tone: warm, short, Indian college context, never clinical. Never use the words symptom, disorder, depressed, diagnosis or patient. Return a TypeScript file that exports one object `copy` with:
> (a) `checkin`: 5 questions with short answer labels (mood with 5 levels, stress 1 to 5, energy 1 to 5, sleep hours, "did you talk to someone you like today?"), plus a thank-you line;
> (b) `weather`: a title and one friendly line for "clear", "clouds", "rain", "storm" (Clear skies, Passing clouds, Soft rain, Heavy skies);
> (c) `tips`: 3 small action tips for each of sleep, pressure, connection, energy, drive;
> (d) `ladder`: 4 steps, each with a title and one line: look after yourself, one small step today, reach out to a friend or mentor, talk to someone trained (campus counsellor, Tele-MANAS 14416 free 24×7, emergency 112);
> (e) `games`: a title and one-line description for Bubble wrap, Worry shredder, Ripples pond;
> (f) `disclaimer`: "MindMirror is not a medical device and does not diagnose."

Read every line. Change anything that doesn't sound like a kind friend. **Commit:** "Add app copy". This file is used by everyone, so push it early.

### 3.2 Game 1: Bubble wrap (`src/games/BubbleWrap.tsx`) (13:30)

**What it is:** a sheet of bubbles. Tap one: it pops with a soft sound and a little squish. "Wrap a new sheet" resets. No score, no timer.

**How it works:** the component keeps an array of 48 true/false values in **state** (popped or not). Each bubble is a button. Tapping sets its value to `true`, which redraws it as flat. The sound is made with the browser's **Web Audio API** (a short noise burst), so there's no sound file to download.

> Make a React component `BubbleWrap` (default export) in `src/games/BubbleWrap.tsx`. A 6 × 8 grid of round bubbles on a soft sage card. Keep an array of 48 booleans in useState. Tapping an unpopped bubble marks it popped: it shrinks slightly and goes flat and lighter (use framer-motion for a quick squish), and plays a short soft pop made with the Web Audio API (a 40 ms burst of filtered noise; create the AudioContext on the first tap). A gentle line at the top: "Pop slowly. Breathe out with each one." When all are popped, show "All popped. Lighter?" and a button "Wrap a new sheet" that resets. Also a small "Reset" button. Big touch targets (at least 44 px). No score, no timer.

**Check before committing:** every bubble pops once; sound plays; reset works; it looks good at phone width (Chrome → F12 → phone icon).
**Commit:** "Add bubble wrap game".

**What to say if a judge asks about your code:** "Each bubble is a button. The component remembers which are popped in state. A tap updates that and React redraws it. The pop sound is generated live with the Web Audio API."

### 3.3 Game 2: Worry shredder (`src/games/WorryShredder.tsx`) (16:00)

**What it is:** type a worry ("lab record due tomorrow"), press **Shred**. The note slides into a shredder, comes out as strips that fall and fade, and a calm line appears: "It's still real, but it's lighter in your hands now."

**How it works:** the text is in state. On Shred, the component switches to "shredding" mode and draws the text as 8 strips, each a narrow slice of the same note (using CSS `clip-path`), and framer-motion moves each strip down while it fades, with slightly different timing. After the animation it switches to "done" mode. The worry is **not saved anywhere**: tell judges that's on purpose.

> Make a React component `WorryShredder` (default export) in `src/games/WorryShredder.tsx`. A paper-like card with a textarea "What's weighing on you?" (max 140 characters) and a button "Shred it". On Shred: the note card slides down into a simple shredder slot (a rounded dark-indigo bar), then appears below it as 8 vertical strips. Each strip shows the same note clipped to its own slice using clip-path inset. The strips fall 120 px, rotate slightly and fade out over 1.5 s with staggered delays (framer-motion). Then show "It's still real, but it's lighter in your hands now." and a button "Write another". Use a phase state: "write" | "shredding" | "done". Never store the text anywhere.

**Check:** long text wraps; the empty note can't be shredded; "Write another" resets.
**Commit:** "Add worry shredder game".

### 3.4 Game 3: Ripples pond (`src/games/Ripples.tsx`) (20:00)

**What it is:** a dark-blue pond. Tap or drag anywhere: soft rings spread from your finger and fade. A "Rain" toggle drops gentle rings by itself.

**How it works:** this one uses a **canvas** (a drawing area). We keep a list of ripples, each with a position and an age. About 60 times a second (`requestAnimationFrame`) we clear the canvas, draw each ripple as a circle whose size grows with its age and whose colour fades, and remove old ones. Taps add new ripples to the list. **Ask Pankaj for 10 minutes of help** if this one fights you; it's the hardest of the three.

> Make a React component `Ripples` (default export) in `src/games/Ripples.tsx`. A full-width canvas (height 70vh) with a deep night-blue background. Keep a list of ripples in a useRef (not state): {x, y, born}. On pointerdown and pointermove (while pressed, max one ripple per 80 ms), add a ripple. Use requestAnimationFrame to redraw: for each ripple draw 2 concentric circles, radius growing to about 120 px over 2.5 s, stroke colour soft white-blue with opacity fading to 0, then remove it. Handle devicePixelRatio so it's sharp on phones, and resize with the window. Add a "Gentle rain" toggle that adds a ripple at a random spot every 700 ms. Clean up the animation frame and interval on unmount. A small caption: "Tap the water. Watch it settle."

**Check:** smooth on your laptop; works by touch in phone view; leaving the screen doesn't leave it running (no errors in the console).
**Commit:** "Add ripples pond game".

### 3.5 The Play room (`src/screens/Play.tsx`) (after game 2)

> Make a `Play` screen (default export) in `src/screens/Play.tsx`. It shows a title "Play room" and a subtitle "No scores. No timers. No way to lose." and three large cards (Bubble wrap, Worry shredder, Ripples pond), each with an emoji, title and one-line description from `copy.games` (import { copy } from "../content/copy"). Tapping a card opens that game full screen (keep `open` in state), with a "← Back to Play room" button. Import the games from "../games/BubbleWrap", "../games/WorryShredder", "../games/Ripples".

**Commit:** "Add Play room".

### 3.6 Support screen (`src/screens/Support.tsx`) (23:00)

This is the most important screen ethically. Take care with it.

> Make a `Support` screen (default export) in `src/screens/Support.tsx` with a prop `current: 0 | 1 | 2 | 3` (the ladder step). Show the 4 ladder steps from `copy.ladder` as stepping stones going up (vertical on mobile), the current step highlighted in sage with "You are here", and the next step softly marked "A gentle next step". Below: three big buttons: "Call Tele-MANAS 14416" (link tel:14416, red urgent style), "Emergency 112" (tel:112, red), and "Campus counsellor" (soft style, opens a small card saying "Add your college counsellor's number here"). At the bottom, `copy.disclaimer` in small grey text. Use semantic HTML (a list for the steps, real links for phone numbers).

**Check:** on a phone, tapping 14416 offers to call.
**Commit:** "Add support screen".

### 3.7 `docs/research.md` (after interviews)

Write it yourself (or ask ChatGPT to tidy your notes). Template:

```markdown
# What students told us (CODE MEET Round 2, 1 Nov)
We spoke to N students from ___ courses, 5 minutes each, anonymous.

## Quotes
- "..."
## What we learned
1. ...
## What we changed because of it
- ...
```

This is gold in the Q&A: "We changed X because a student told us Y."

---

## Part 4. The interviews (Sunday 10:30 to 11:30)

Ask 4 to 6 students at the venue (other teams, volunteers). Say: "We're building a wellness app for students; could I ask 5 quick questions? It's anonymous." Write their words as exactly as you can.

1. When exams or submissions pile up, what's the first thing that changes for you: sleep, food, mood, friends?
2. How do you usually notice you're getting stressed? Or do other people notice first?
3. Have you ever used a wellness or mood app? Why did you stop?
4. If something told you "you've slept 1.5 hours less than usual this week", would that help or annoy you?
5. Would you press a button on a small necklace and say how you feel, if it answered kindly? Where would you use it?
6. Who would you trust to see your data? (Expect: nobody. That's our privacy point.)

Afterwards, ask ChatGPT:
> Here are my notes from N student interviews: [paste]. Give me (1) three short quotes for a slide, keeping their words, anonymous, (2) three insights about what students need, (3) one honest number like "4 of 5 said…". Don't invent anything that isn't in my notes.

Then fill in the blanks (___) in [JUDGE_QA.md](JUDGE_QA.md), and add a quote to slide 2 of the deck.

---

## Part 5. The presentation and demo

You present the whole thing. Your script is **[PITCH_SCRIPT.md](PITCH_SCRIPT.md)**: every slide in simple English, all spoken by you, plus hook points, Q&A and a cue card. (It replaces the deck's speaker notes where those give slides to Pankaj or Kishore.) Practise it aloud until you can say it while looking at the audience, not the screen. Aim for about 8 minutes including a 3-minute live demo, unless the organisers give a different time (adjust then).

**Practise like this:**
1. Saturday: read the notes aloud 3 times. Time yourself.
2. Sunday night (before sleeping): once, with Pankaj and Kishore listening.
3. Monday 08:30: twice with the live demo, timed. Then a 10-question Q&A drill.

**Demo script** (inside slide 9's notes too):
1. **Home** with sample data: "This is Asha after three weeks. Her weather says Soft rain."
2. **Insights:** point at the Sleep card's proof. "No single night looks bad. The drift does."
3. **Necklace:** Kishore holds the button and says "I only slept four hours and I have two assignments tomorrow." It answers. Point at the laptop: the turn appeared live. Pankaj shows the hub log.
4. **Play room:** pop three bubbles, or shred a worry. "When you're stressed, doing beats reading."
5. **Support:** "We never diagnose. We point to people." Show Tele-MANAS 14416.

**If something breaks on stage:** smile, say "Live hardware!", use the app's Hold-to-talk button instead, and keep going. Practise saying that line once so it comes naturally.

### The demo video (Monday 07:00 to 08:30)

The rules ask for a "brief presentation video". 2 to 3 minutes:
- **0:00–0:15** you on camera or voice: the problem in one sentence.
- **0:15–2:15** screen recording following the demo script, with the necklace part filmed on a phone (Kishore films).
- **2:15–2:45** the safety and privacy lines, and "Team HTTP Dino, MindMirror."

Record the screen with Windows **Win + Alt + R** (Xbox Game Bar), or Mac **Cmd + Shift + 5**. Do 2 takes, keep the better one. Don't spend more than 90 minutes.

---

## Part 6. If a judge asks you anything

Read [JUDGE_QA.md](JUDGE_QA.md); the questions marked **Lead M** are yours first. Your strongest topics: the problem, the students' words, safety, privacy, games, impact, team. For deep technical questions, say "Pankaj built that, he'll explain the details" after giving the one-line version. That's not weakness; it shows the team works.
