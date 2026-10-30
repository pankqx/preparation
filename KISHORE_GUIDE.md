# Kishore's guide

Welcome to your first hackathon. You have three jobs:

1. **UI developer:** you build the app's look: the shared components (buttons, cards, sliders, the weather picture, signal cards, chat bubbles) and two screens (Check-in and Breathe). That's your code in GitHub, under your name.
2. **Hardware maker:** with Pankaj you wire and test the AI necklace, commit the hardware test programs, and build the pendant case.
3. **Team voice:** in the final presentation you run the necklace demo and answer "how did you work as a team?".

This guide first explains the whole project in plain words, then the hardware in depth (you'll be asked about it), then your code step by step.

---

## Part 1. MindMirror in plain words

**The problem** ("Mind Check"): stress and burnout grow slowly through academic pressure, poor sleep, isolation, exhaustion and loss of motivation. Students don't notice until it hurts. We must help them **notice early, understand their patterns and find support, without diagnosing**.

**Our answer:** a web app + an AI necklace.
- A **30-second daily check-in** (or a voice note to the necklace).
- The app compares the last 3 days with **the student's own normal** (median of the 2 weeks before).
- **Five signals** with proof: Sleep, Pressure, Connection, Energy, Drive. Example proof: "You slept 5.4 h on average the last 3 nights; your usual is 7.0 h (−1.6 h)."
- They combine into a **mind weather** (☀️ Clear skies → ⛅ Passing clouds → 🌧 Soft rain → ⛈ Heavy skies), which picks a step on the **support ladder** (look after yourself → small step → reach out to a friend → talk to someone trained, like Tele-MANAS 14416).
- **Calm tools:** Merel's Play room games, your Breathe screen, the companion chat.
- **Safety:** we never diagnose; code calculates and AI only explains; crisis words skip the AI and show Tele-MANAS 14416 and 112; data stays in the student's browser.

**Who built what:** Pankaj (engine, hub, firmware, integration), Merel (research, words, games, support screen, presentation), you (design, UI components, check-in, breathe, hardware tests, pendant case).

---

## Part 2. The necklace, deeply (you'll be asked)

### The parts and what each does

| Part | Job | One-line explanation for a judge |
|---|---|---|
| **ESP32-WROOM-32 DevKit** | the brain | "A small computer with Wi-Fi. It reads the button and mic, sends the sound to the laptop and plays the reply." |
| **INMP441** | microphone | "A digital mic: it sends sound as numbers, so there's no noise from analog wires." |
| **MAX98357A** | amplifier | "Takes digital sound from the ESP32 and powers the speaker. An ESP32 pin is far too weak to drive a speaker." |
| **8 Ω 0.5 W speaker** | talks | "Small speaker. We keep the volume at half in software so we never overload its half-watt rating." |
| **Push button** | talk button | "Hold to talk, release to send." |
| **Power bank + USB cable** | power | "Battery version is next; for now, a power bank in the pocket." |

### How sound becomes numbers (the core idea)

Sound is air pressure going up and down. The mic measures that pressure **16,000 times every second** (the *sample rate*, 16 kHz). Each measurement is a number (a *sample*). One second of voice = 16,000 numbers. 16 kHz is enough for speech, which is why phone calls sound fine at even lower rates.

### I2S, the three-wire sound cable

I2S ("eye-squared-ess") is how chips send sound to each other. Three wires:

| Wire | Name on our modules | What it carries |
|---|---|---|
| **Bit clock** | SCK (mic), BCLK (amp) | a tick for every bit sent |
| **Word select** | WS (mic), LRC (amp) | says "this sample is left channel" or "right channel" |
| **Data** | SD (mic), DIN (amp) | the actual sound bits |

The ESP32 has **two** I2S engines, so one listens to the mic and the other talks to the amp **at the same time**. That's why the mic and the amp have separate wires.

The mic's **L/R** pin picks whether it speaks on the left or right channel. We tie it to GND = left. (Test 3 tells us which side the ESP32 actually hears.)

### The pin table (you read this aloud while Pankaj wires)

| From | To ESP32 |
|---|---|
| Mic VDD | **3V3** (never 5V: the mic is a 3.3-volt part) |
| Mic GND, Mic L/R | **GND** |
| Mic SCK | **D32** |
| Mic WS | **D25** |
| Mic SD | **D33** |
| Amp VIN | **VIN** (5 V from USB) |
| Amp GND | **GND** |
| Amp BCLK | **D26** |
| Amp LRC | **D27** |
| Amp DIN | **D22** |
| Button | **D13** and **GND** (diagonal legs) |
| Speaker | amp's screw terminal |

**Why these pins:** some ESP32 pins (0, 2, 5, 12, 15) affect how it starts up, so we avoid them. Pins 34 to 39 can only read, so we keep them free.

### What happens when you press the button

1. The ESP32 opens a connection to the laptop hub and beeps once.
2. While you hold the button, a separate task reads the mic, cleans the sound (removes a constant offset the mic has), and puts it in a **one-second waiting area** (a buffer). The main loop sends it to the laptop in small pieces **while you're still talking**. That's called *streaming*, using HTTP "chunked" upload. Why? The ESP32 has only about 300 KB of memory, and 10 seconds of voice is 320 KB, so we can't store it all.
3. You let go. The hub turns speech into text, writes a reply and makes it into speech (about 2 to 4 s).
4. The hub sends back raw sound numbers. The ESP32 plays them through the amp as they arrive.
5. The app on the laptop shows the conversation at the same moment.

**How the necklace finds the laptop:** every 2 seconds the hub shouts "MINDMIRROR_HUB 8787" to everyone on the hotspot (a UDP *broadcast*). The necklace hears it and learns the laptop's address. Nobody types IP addresses.

**Why Wi-Fi, not Bluetooth:** Wi-Fi is fast and uses plain web requests, which are easy to test and debug in 24 hours. Bluetooth would need a custom audio protocol (we designed that in Round 1, and it's much more complex).

**What the LED means:** slow blink = finding Wi-Fi; solid = ready; fast blink = listening; short blips = thinking/speaking.

### Your hardware jobs

1. **Saturday:** help solder the header pins (watch a "how to solder header pins" video first). Then run tests 1 to 4 with Pankaj ([NECKLACE_GUIDE.md](NECKLACE_GUIDE.md), Part 4).
2. **Sunday 16:00:** wire it again on the breadboard with Pankaj. You read each row of the pin table aloud, he plugs it in, you tick it. Then swap and check again.
3. **Commit the tests**: copy the four test sketches into the new repo under `firmware/tests/` (01_blink_button, 02_speaker_tone, 03_mic_level, 04_echo), plus a short `firmware/tests/README.md` with what each test proves and what you saw ("Test 3: side0 moves when I clap"). **Commit:** "Add hardware test sketches and results".
4. **Photos:** take clear photos of the breadboard wiring and the finished pendant; add them to `docs/hardware-photos/`. **Commit:** "Add hardware photos".
5. **Pendant case:** NECKLACE_GUIDE.md, Part 8. Prompt for ChatGPT:
   > I'm making a small pendant box (about 6 × 4 × 2.5 cm) from mount board for a wearable prototype containing a circuit board (5.2 × 2.8 cm), a small round speaker, a microphone module and a push button. Give me a cutting template with exact measurements, where to cut holes for the speaker grille, the mic and the button, how to route a USB cable out of the bottom, and how to make it look calm and premium (indigo, sage, cream) with paper, paint and fabric.

---

## Part 3. Your app code

### Before Sunday: React warm-up (20 minutes)

```bash
npm create vite@latest practice -- --template react-ts
cd practice
npm install
npm run dev
```

Open http://localhost:5173. In VS Code, replace `src/App.tsx` with:

```tsx
import { useState } from "react";

export default function App() {
  const [mood, setMood] = useState(3);
  return (
    <div style={{ padding: 40, fontFamily: "sans-serif" }}>
      <h1>Mood: {mood}</h1>
      <input type="range" min={1} max={5} value={mood} onChange={(e) => setMood(Number(e.target.value))} />
    </div>
  );
}
```

Move the slider: the number changes. That's **state** (`useState`), an **event** (`onChange`) and **JSX** (the HTML-like code). Components are functions that return JSX. **Props** are values passed in, like `<Slider label="Energy" />`. That's 90% of what you need.

### The ChatGPT context (paste first in every new chat)

> I'm building part of a React + TypeScript + Tailwind CSS v4 web app called MindMirror, a calm well-being app for college students. I'm a beginner, so give me complete files I can paste and explain anything new in one or two lines. Style: soft indigo (#4F5BD5), sage green (#8FB9A8), warm cream background (#FBF7F0), coral for "needs care" (#E8836B), red ONLY for emergency buttons. Font Nunito. Rounded corners (rounded-2xl), soft shadows, lots of white space, gentle and never clinical. Mobile first (max width 480px, centred on desktop). Only Tailwind classes and framer-motion (installed). No other UI libraries.

**The loop:** prompt → paste into the file → save → check the browser → error? paste the whole red text to ChatGPT with "fix this" → works? **commit** (clear message) → **push** → **pull request** → tell Pankaj. Stuck after two tries: ask.

### Your design job first (10:30)

In `src/index.css`, after `@import "tailwindcss";`, add the theme so everyone uses the same colours:

> Write a Tailwind CSS v4 `@theme` block for src/index.css that defines colours indigo #4F5BD5, sage #8FB9A8, cream #FBF7F0, coral #E8836B, ink #2B2D42, and font Nunito (with the Google Fonts @import line), and sets the body background to cream and text to ink.

**Commit:** "Add MindMirror colours and font".

### K1. `src/components/ui.tsx` (first PR, by 13:00)

> Make `src/components/ui.tsx` exporting: `Button` (props: variant "primary" | "soft" | "urgent", onClick, children; primary = indigo, soft = white with indigo text, urgent = red), `Card` (white, rounded-2xl, soft shadow, padding), `Slider` (props label, value 1 to 5, onChange, leftEmoji, rightEmoji; a big friendly range input), `Toggle` (props value boolean, onChange, yesLabel, noLabel; two pill buttons), `Screen` (props title, onBack optional, children; page wrapper with cream background, max width 480px, back arrow when onBack is set). Touch targets at least 44px.

**Commit:** "Add base UI components".

### K2. `src/screens/CheckIn.tsx` (13:30)

> Make a `CheckIn` screen (default export) in `src/screens/CheckIn.tsx` with prop `onSave(data)` where data = {mood, stress, energy, sleepHours, connected, note}. Show one question card at a time with a progress bar (5 steps), using components from "../components/ui" and question text from `copy.checkin` (import { copy } from "../content/copy"). Mood: 5 face emojis to tap. Stress and energy: Slider. Sleep: minus/plus stepper 0 to 12 in 0.5 steps, default 7. Connected: Toggle. Then an optional note box and Save. Animate between cards with framer-motion (fade + slide 20px). A Back button on each step.

**Check:** you can go back and change answers; Save gives all six values (Pankaj will connect it to the database).
**Commit:** "Add check-in screen".

### K3. `src/components/Weather.tsx` (15:00)

> Make a `Weather` component with props kind: "clear" | "clouds" | "rain" | "storm", title, message. Draw a soft illustration with inline SVG inside a rounded arch-shaped window frame: clear = warm sun; clouds = sun behind two clouds; rain = clouds with gentle falling rain lines; storm = darker clouds and heavier rain (no lightning, keep it calm). Animate gently with CSS keyframes (clouds drift slowly, rain falls slowly, sun glows softly). Respect prefers-reduced-motion. Title and message below.

**Commit:** "Add mind weather illustration".

### K4. `src/components/SignalCard.tsx` and K5. `src/components/Chat.tsx` (20:00)

> Make a `SignalCard` with props name, icon (emoji), level ("steady" | "watch" | "needs care" | "learning"), proof (sentence). Level is a small pill: steady = sage, watch = amber, needs care = coral, learning = grey "learning your normal". Proof under the name in smaller grey text.

> Make a `Chat` component with props messages: {from: "me" | "mindmirror", text, via?: "necklace" | "web"}[], onSend(text), onHoldStart(), onHoldEnd(). My bubbles on the right in indigo with white text; MindMirror's on the left in white with a small 🌿 avatar. If via is "necklace", show a tiny "🎙 from necklace" label. Auto-scroll to the newest. Text input + Send at the bottom, and a round "Hold to talk" button (pointerdown → onHoldStart, pointerup/leave → onHoldEnd) that pulses while held.

**Commits:** "Add signal card", "Add chat component".

### K6. `src/screens/Breathe.tsx` (22:00)

> Make a `Breathe` screen: a large soft circle that grows for 4 seconds ("Breathe in") and shrinks for 6 seconds ("Breathe out"), repeating, with framer-motion and a sage-to-indigo look. A 1-minute session with Start/Stop and a gentle "Well done" at the end. Respect prefers-reduced-motion (then just change the words).

**Commit:** "Add breathing screen".

### Screenshots (Monday 06:00)

Chrome → F12 → device toolbar → "iPhone 12 Pro" → screenshot Home, Check-in, Insights, Play, Support (three-dot menu in DevTools → "Capture screenshot"). Send to Merel for the slides.

---

## Part 4. Questions you'll answer

Read [JUDGE_QA.md](JUDGE_QA.md); questions marked **Lead K** are yours first: the five signals, the necklace parts, how it works step by step, I2S, why an amplifier, the colours, check-in time, "how did you divide the work?", and "what did you learn?".

Practise saying these out loud until they're natural:

- *"How does the necklace work?"* → "You hold the button and the ESP32 streams your voice over Wi-Fi to our laptop hub. The hub turns it into text, writes a short kind reply and turns that into speech. The necklace plays it through the amplifier and speaker. About 2 to 4 seconds."
- *"What did you build?"* → "The interface: the colours, components, check-in and breathing screens. On hardware, I wired and tested the necklace with Pankaj and built its case. My commits are in the repo."
- *"How did you work as a team?"* → "We had a written plan with roles and a schedule. Each of us had our own branch and made pull requests, and we synced every three hours. Merel's interview findings changed the check-in; my components are used on every screen; Pankaj connected it all."

If you don't know an answer: "Good question, Pankaj built that part, he'll explain." Then listen, so you can answer it next time.
