# Team HTTP Dino: who does what, hour by hour

**Round 2, CODE MEET 2026, COE-Lab, Srinivas University.** Starts **Sat 1 Nov, 10:00 AM**. Runs 24 hours (until about **Sun 2 Nov, 10:00 AM**). Winners announced 2 Nov.

**Confirm at the registration desk on day 1:** the exact submission deadline, the submission form/link, the demo-video length and format, and when judges come round. Write them on the whiteboard of this plan. If the deadline is earlier than 10:00, shift the last block earlier.

---

## The three roles

| | **Pankaj** (Claude Pro) | **Merel** (ChatGPT Go) | **Kishore** (ChatGPT Go) |
|---|---|---|---|
| Role | **Tech lead** | **Product, research and pitch lead** | **Design and hardware maker** |
| Owns | repo, hub, signal engine, AI, wiring everything together, final merges | user interviews, every word in the app, safety content, README, slides, demo script, demo video, judge Q&A | look and feel, screen components, icons/illustrations, necklace wiring tests (with Pankaj), the pendant enclosure, screenshots |
| Judged on | Technical complexity 25%, Functionality 20% | Presentation 15%, Impact 10%, Innovation 20% (the story) | Usability (inside Functionality 20%), Innovation (how it looks and feels) |
| Never does | stop to make slides | write code alone at 3 AM | push to `main` |

**Team collaboration is 10% of the score**: judges check "clear delegation and roles". Put this table on a slide and say it out loud.

### Rules for working together

1. **One repo, branches per person.** Only Pankaj merges into `main`.
2. **Sync every 3 hours, 10 minutes, standing up** (times in the plan): what's done, what's next, what's blocking.
3. **If stuck for more than 20 minutes, say so.** A first hackathon is not the time to suffer quietly.
4. **Push to GitHub at least every hour.** Laptops die.
5. **Sleep in shifts.** Nobody codes well after 20 hours awake. Shifts are in the plan.
6. **Eat when food comes** (lunch, snacks, dinner on day 1; breakfast day 2 are provided).

### Git for Merel and Kishore (the easy way)

Install **GitHub Desktop** (desktop.github.com) and **VS Code**.
1. File → Clone repository → `mindmirror`.
2. Current branch → New branch → `kishore/ui` (or `merel/content`).
3. Edit files in VS Code. Back in GitHub Desktop: write a short summary ("Add check-in card styles"), **Commit**, then **Push origin**.
4. Tell Pankaj "pushed". He merges it.
5. Before you start new work: **Fetch origin**, then Branch → "Update from main".

---

## Before the event (today and tomorrow, 30 to 31 Oct)

Preparation is allowed; building the actual project happens during the 24 hours. Do these now so hour 0 isn't spent on installs.

| Who | Task | Done |
|---|---|---|
| All | GitHub account; tell Pankaj the username | ☐ |
| All | Install VS Code, Node.js 22, Git / GitHub Desktop, Chrome | ☐ |
| Pankaj | Create the empty `mindmirror` repo, add Merel + Kishore as collaborators | ☐ |
| Pankaj | Get a Groq API key (console.groq.com); Merel creates a backup key on her account | ☐ |
| Pankaj + Kishore | **Solder header pins** onto the mic and amp | ☐ |
| Pankaj + Kishore | Install Arduino IDE + ESP32 core 3.x; run hardware **tests 1 to 4** from the necklace guide | ☐ |
| Pankaj | Run the hub once with the real key from home Wi-Fi and with the phone hotspot | ☐ |
| Pankaj | Set phone hotspot to **2.4 GHz**, name `MindMirror` | ☐ |
| Merel | Read the problem statement and the Round 1 deck twice. Draft 6 interview questions (prompt M1 below) | ☐ |
| Kishore | Pick a colour palette and font; collect 10 calm reference screenshots (Pinterest/Dribbble "calm wellness app") | ☐ |
| All | Pack: laptops + chargers, **extension board** (the rules say bring your own), power bank, 2 USB cables, the hardware in a box, insulation tape, hot glue gun, cardboard, scissors, college ID | ☐ |
| All | Sleep well on 31 Oct. Seriously. | ☐ |

---

## Hour by hour

Times are Saturday 1 Nov unless marked. 😴 = sleep shift.

| Time | Pankaj | Merel | Kishore |
|---|---|---|---|
| **10:00–10:30** | Kickoff together: read this plan, confirm deadline + submission rules at the desk, set up the table and power | (same) | (same) |
| **10:30–11:30** | Vite app + hub in the new repo, README disclosure, push. Help both others clone and run | Interview 4 to 6 students at the venue (5 min each): sleep, deadlines, who they talk to, would they wear it | Clone, run app. Set up Tailwind colours + font in `index.css`. Start the button, card, slider components |
| **11:30–13:30** | `db.ts`, check-in saving, `sample.ts` (21 days of a student drifting) | Turn interviews into 3 quotes + 3 insights. Write `content/copy.ts`: every question, label, tip, support text | Check-in screen: 5 question cards (mood faces, sliders, sleep stepper, yes/no) |
| 13:00 | **Sync 1** + lunch | | |
| **13:30–16:00** | `signals.ts` + tests (the engine) | Support screen content (ladder steps, Tele-MANAS, counsellor wording, "not a medical device"). Review Kishore's screens with fresh eyes | Home screen + mind weather illustrations (4 weathers). Signal card component |
| **16:00–17:00** | Hardware on the breadboard with Kishore: re-run test 4, then the necklace firmware against the hub | Start slides: title, problem (with interview quotes), solution | Wiring with Pankaj (follow the pin table, double-check each wire) |
| 16:00 | **Sync 2** | | |
| **17:00–19:30** | Insights screen with real proof sentences + sleep chart | Slides: how it works, privacy, team roles. Write the demo script v1 | Insights layout + Support screen build from Merel's copy |
| **19:30–20:00** | Dinner | Dinner | Dinner |
| **20:00–22:00** | Companion chat + live necklace turns in the app. **Goal: full flow works = MVP** | Test the MVP as a new user, write down every confusing thing (GitHub issues or a shared note) | Companion screen bubbles + "Hold to talk" button style |
| 22:00 | **Sync 3. Tag `v-mvp`.** Decide: Planner and Breathe, yes or no | | |
| **22:00–00:30** | Planner + PressureMap (if yes) | 😴 **Sleep 22:30–02:30** | Breathe screen (growing circle), then start the pendant box |
| **Sun 00:30–02:30** | Fix the issues Merel logged; polish | 😴 | 😴 **Sleep 00:30–04:30** |
| **02:30–04:30** | 😴 **Sleep 02:30–06:00** (set an alarm, Merel wakes you) | Practise the pitch out loud; finalize slides; record voice-over draft | 😴 |
| **04:30–06:00** | 😴 | Bug bash: every screen, phone width too | Pendant enclosure: move to female-female jumpers, box, speaker holes, decorate |
| **06:00–07:00** | **Feature freeze.** Only fixes. Tag `v-demo`. | Demo rehearsal 1 with the real necklace (time it) | Screenshots + a 10 s close-up video of the necklace for the slides |
| 06:30 | **Sync 4** + breakfast | | |
| **07:00–08:30** | Final fixes from the rehearsal; README with setup steps and screenshots | **Record the demo video** (screen recording + necklace on camera + voice-over) | Help with the video: hold the necklace, film the close-ups |
| **08:30–09:30** | Submit: repo link, video, slides. Check everything opens on another laptop | Rehearsal 2 + judge Q&A practice (prompt M5) | Pack the demo table: necklace charged, laptop charged, hotspot on |
| **09:30–10:00** | Buffer. Breathe. | Buffer | Buffer |

If the official deadline is earlier, keep the same order and cut from the "should" features, never from the video or rehearsal.

---

## Merel: your guide (ChatGPT prompts to copy)

You're the voice of the team. Judges remember the story, the real quotes and the calm confidence. You're also the team's "first user": if something confuses you, it will confuse the judges.

**M1. Interview questions** (before the event)
> I'm on a college hackathon team building MindMirror, an app plus a wearable that helps students notice early signs of stress and burnout (poor sleep, deadline pressure, isolation, low energy, low motivation) without diagnosing them. Write 6 short, friendly interview questions I can ask other students in 5 minutes. Don't ask about mental illness directly. Include one question about whether they would wear a small talking necklace, and one about privacy.

**M2. Turn interviews into insights** (hour 2)
> Here are my notes from 5 student interviews: [paste]. Give me (1) three short real-sounding quotes I can put on a slide (keep their words, anonymous), (2) three insights about what students need, (3) one number I can honestly say, like "4 of 5 students said…".

**M3. App words** (hours 2 to 5)
> Write the text for a calm student well-being app. Tone: warm, short, Indian college context, never clinical. Never use the words symptom, disorder, depressed, diagnosis or patient. I need: (a) 5 check-in questions with short answer labels (mood, stress, energy, sleep hours, "did you talk to someone you like today"), (b) a friendly line for each of 4 "mind weather" states: Clear skies, Passing clouds, Soft rain, Heavy skies, (c) 3 small action tips for each of these signals: sleep, pressure, connection, energy, drive, (d) a 4-step support ladder from "look after yourself" to "talk to someone trained", including Tele-MANAS 14416 (free, 24×7) and 112. Give it as a TypeScript object I can paste into copy.ts.

Paste the result into `src/content/copy.ts` and push. Pankaj and Kishore use it everywhere.

**M4. Slides** (hours 6 to 16). Keep it to 6 to 8 slides:
1. Team, college, problem "Mind Check"
2. The problem in students' words (your interview quotes)
3. MindMirror: app + necklace in one picture
4. How it works: check-in → your own baseline → 5 signals with proof → support ladder (show the real Insights screen)
5. The necklace (photo + "hold, talk, hear")
6. Trust and safety: no diagnosis, data stays on the device, crisis goes to humans
7. Team roles and how we built it in 24 h
8. Impact and next steps (battery necklace, fully on-device AI, campus counsellor integration)

> Prompt: Here is our project summary: [paste section 1 of the app guide + the privacy section]. Write speaker notes for an 8-slide, 5-minute pitch for hackathon judges, following this outline: [paste]. Each slide: 2 to 3 sentences, simple English, confident, no jargon.

**Demo script** (the order to show, about 3 minutes):
1. Home: "This is Asha's MindMirror after 3 weeks" (sample data). Weather says Soft rain.
2. Insights: point at the Sleep card's proof sentence. "No single night looks bad. The drift does."
3. Necklace: Kishore or you hold the button and say "I only slept four hours and I have two assignments tomorrow". It answers. Turn to the laptop: the turn appeared live.
4. Companion: type "why do I feel so tired?". It explains using her own numbers.
5. Support: show the ladder and crisis routing. "We never diagnose. We point to people."

**M5. Judge Q&A practice** (hour 22)
> Act as a strict hackathon judge (industry expert). Our project: [paste summary]. Ask me 10 hard questions one at a time about privacy, accuracy, "isn't this diagnosing?", why a necklace, what happens in a crisis, scalability, and what we built in 24 hours versus before. After each of my answers, tell me how to make it shorter and stronger.

Answers to have ready: "We don't diagnose: we compare you with your own normal and show the proof." "Voice is transcribed by an API and not stored; everything else stays in the browser; Round 1 we built a fully on-device version, that's the production path." "The necklace is for moments when you won't open an app."

**Demo video** (the rules require a "brief presentation video"): 2 to 3 minutes. Phone screen-record or OBS on the laptop. Script = the demo script above, with a 15 s intro (problem) and 15 s outro (impact). Record the necklace part with a phone camera. Do 2 takes, pick the better one. Don't spend more than 90 minutes on it.

---

## Kishore: your guide (ChatGPT prompts to copy)

You're the reason judges will say "this looks lovely". You also build the necklace's body. Work in small pieces: one component, check it in the browser, commit, next.

**How to use the prompts:** copy the whole prompt, paste into ChatGPT, copy the code it gives you into the file named, save, look at the browser (`npm run dev`, then open http://localhost:5173). If it errors, copy the **whole red error** back into ChatGPT with "fix this". If still broken after 2 tries, call Pankaj.

**Always start a ChatGPT chat with this context:**
> I'm building a React + TypeScript + Tailwind CSS v4 web app called MindMirror, a calm well-being app for college students. Style: soft indigo (#4F5BD5), sage green (#8FB9A8), warm cream background (#FBF7F0), coral for "needs care" (#E8836B), red ONLY for emergency buttons. Font: Nunito. Rounded corners (rounded-2xl), soft shadows, lots of white space, gentle and not clinical. Mobile first (max width 480px, centred on desktop). Give me complete files I can paste. Use only Tailwind classes, no other CSS libraries.

Then one of these:

**K1. Base components** → `src/components/ui.tsx`
> Make a file ui.tsx exporting these React components: Button (variants primary, soft, urgent), Card (rounded white card with padding), Slider (1 to 5 with a label and emoji at each end), Toggle (Yes/No pill), Screen (page wrapper with a title, a back arrow, and the cream background).

**K2. Check-in screen** → `src/screens/CheckIn.tsx`
> Make a CheckIn screen that shows one question card at a time with a progress bar (5 steps): mood (5 face emojis to tap), stress (Slider), energy (Slider), sleep hours (minus/plus stepper from 0 to 12 in 0.5 steps), "Did you talk to someone you like today?" (Toggle), then an optional note box and a Save button. It takes a prop onSave(data) with {mood, stress, energy, sleepHours, connected, note}. Use the components from ./components/ui. Animate between cards with framer-motion (fade and slide 20px).

**K3. Mind weather illustration** → `src/components/Weather.tsx`
> Make a Weather component with a prop kind: "clear" | "clouds" | "rain" | "storm". Draw a soft illustration using inline SVG: a rounded window frame with sky inside; clear = sun, clouds = sun behind 2 clouds, rain = clouds and gentle rain lines, storm = darker clouds and rain (no lightning, keep it calm). Animate gently with CSS (clouds drift slowly, rain falls slowly). Below it show a title and a one-line message passed as props.

**K4. Signal card** → `src/components/SignalCard.tsx`
> Make a SignalCard with props: name, icon (emoji), level ("steady" | "watch" | "needs care" | "learning"), proof (a sentence). Level shows as a small pill: steady = sage, watch = amber, needs care = coral, learning = grey. The proof sentence is under the name in smaller grey text.

**K5. Support ladder** → `src/screens/Support.tsx`
> Make a Support screen showing 4 steps as stepping stones going up (vertical on mobile), with the current step highlighted (prop current: 0 to 3). Below: three big buttons: "Call Tele-MANAS 14416" (href tel:14416, urgent red style), "Emergency 112" (tel:112, urgent), "Campus counsellor" (soft style). Footer: "MindMirror is not a medical device and does not diagnose." Text comes from a prop so Merel's words can be used.

**K6. Breathe** → `src/screens/Breathe.tsx`
> Make a Breathe screen: a large soft circle that grows for 4 seconds ("Breathe in") and shrinks for 6 seconds ("Breathe out"), repeating, using framer-motion. A 1-minute timer with Start/Stop. Calm sage-to-indigo gradient.

**K7. Chat bubbles** → `src/components/Chat.tsx`
> Make a Chat component: list of messages {from: "me" | "mindmirror", text, via?: "necklace"}. My bubbles right in indigo with white text; MindMirror's left in white with a small leaf avatar. If via is "necklace", show a tiny "🎙 from necklace" label. A text input with Send at the bottom, and a round "Hold to talk" button that calls onHoldStart/onHoldEnd props.

**Hardware with Pankaj (hours 6 to 7)**: you hold the necklace guide open and read each row of the pin table aloud; Pankaj plugs the wire; you tick it. Then swap: Pankaj reads, you check. Two people checking catches almost every mistake.

**Pendant enclosure (hours 18 to 20)**: follow Part 8 of the necklace guide.
> Prompt: I'm making a small pendant box (about 6 × 4 × 2.5 cm) from mount board for a wearable prototype containing a circuit board, a small speaker, a mic and a button. Give me a cutting template with exact measurements, where to cut holes for the speaker, mic and button, and how to make it look calm and premium (colours: indigo, sage, cream), using only cardboard, glue, paint and fabric.

**Screenshots for the slides (hour 20)**: Chrome → F12 → toggle device toolbar → "iPhone 12 Pro" → take screenshots of Home, Check-in, Insights, Support. Send them to Merel.

---

## Pankaj: your guide

You hold the technical thread. Your job is also to **unblock the other two fast**: a 2-minute answer from you saves them 40 minutes.

- Follow the build order in the app guide (section 9). Hit the hour-12 MVP no matter what.
- Use Claude for the engine and integration (prompts in the app guide). Paste the specs from the guides; they were written to be pasted.
- Review and merge Merel's and Kishore's branches at every sync, not at the end.
- Keep the hub log visible on screen during the demo; it shows judges the real pipeline (STT ms, AI ms, TTS ms).
- At 06:00, freeze. New ideas after that go into "next steps" on the slides.

---

## How this plan earns points

| Criterion (weight) | What earns it | Owner |
|---|---|---|
| Innovation & creativity (20%) | personal baseline instead of generic rules; a wearable you talk to; proof under every insight | Pankaj + Merel |
| Technical complexity (25%) | signal engine with tests; ESP32 two-I2S audio streaming; hub pipeline (STT → AI → TTS); live events into the app | Pankaj |
| Functionality & usability (20%) | full flow works on stage; check-in under 60 s; calm, readable UI | all, Kishore on UI |
| Presentation & communication (15%) | real interview quotes; tight 5-minute story; clean demo | Merel |
| Impact & practicality (10%) | maps 1:1 to the problem statement; safety routing to Tele-MANAS; next steps | Merel |
| Team collaboration (10%) | the roles table on a slide; branches per person; visible handoffs | all |
