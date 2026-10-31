# Team HTTP Dino: who does what, hour by hour

**Round 2, CODE MEET 2026, COE-Lab, Srinivas University.**
Starts **Sunday 1 Nov, 10:00 AM**. Building ends about **Monday 2 Nov, 10:00 AM**, then the **final presentation**. Winners announced 2 Nov.

**Confirm at the registration desk on Sunday morning:** the exact submission deadline, where to submit, how long the final presentation is, whether there's a projector and whether a live demo is allowed, and the demo-video length. Write the answers at the top of this file and push.

---

## 1. The three roles

Everyone owns real code in the repo, under their own GitHub account. That's what "team collaboration" (10% of the score) looks like in the commit history, and it's what lets each of you answer "what did *you* build?" with confidence.

| | **Pankaj** (Claude Pro) | **Merel** (ChatGPT Go) | **Kishore** (ChatGPT Go) |
|---|---|---|---|
| Role | **Tech lead + IoT** | **Product, content + Play room developer + presenter** | **Design + UI developer + hardware maker** |
| Owns in GitHub | `hub/`, `firmware/mindmirror_necklace/`, `src/lib/` (database, signal engine, hub link), final integration | `src/games/` (3 calm games), `src/screens/Play.tsx`, `src/screens/Support.tsx`, `src/content/copy.ts`, `docs/research.md`, `README.md` story sections | `src/components/` (buttons, cards, weather, signal card, chat), `src/screens/CheckIn.tsx`, `src/screens/Breathe.tsx`, `firmware/tests/` (hardware tests 1 to 4), `docs/hardware-photos/` |
| Off-screen | unblocks the others fast | user interviews, slides, demo video, leads the final presentation | wiring with Pankaj, the pendant enclosure, screenshots |
| Personal guide | [APP_BUILD_GUIDE.md](APP_BUILD_GUIDE.md), [NECKLACE_GUIDE.md](NECKLACE_GUIDE.md) | [MEREL_GUIDE.md](MEREL_GUIDE.md) | [KISHORE_GUIDE.md](KISHORE_GUIDE.md) |
| Everyone reads | [JUDGE_QA.md](JUDGE_QA.md) and the deck's speaker notes | | |

### Pankaj's 2 AM pass: integrate, don't replace

At around 2 AM Pankaj uses Claude to finish and connect the app. **Tell Claude to keep Merel's and Kishore's files and build around them** (the prompt is in the app guide, section 11). If Claude rewrites their files, the commit history stops showing their work, and a judge who asks Merel "show me your game's code" gets an awkward moment. Fix *bugs* in their files, keep their structure and their names in the history.

### Working rules

1. **One repo, one branch per person** (`merel/play`, `kishore/ui`, `pankaj/core`). Only Pankaj merges into `main`.
2. **Each person commits under their own GitHub account** (GitHub Desktop, signed in as yourself). Small commits, often, with clear messages: "Add bubble wrap game", not "update".
3. **Push at least every hour.** Laptops die.
4. **Stuck for 20 minutes? Say so.** It's a team, not an exam.
5. **Sync for 10 minutes** at the times in the plan: what's done, what's next, what's blocking.
6. **Eat when food comes.** Sleep in the slots below. Tired people break working code.

### Git for Merel and Kishore (GitHub Desktop)

1. Install **GitHub Desktop** and **VS Code**. Sign in to GitHub Desktop with **your own** account.
2. File → Clone repository → `mindmirror`.
3. Current branch → New branch → `merel/play` (or `kishore/ui`).
4. Edit in VS Code. In GitHub Desktop: tick the changed files, write a summary, **Commit to merel/play**, then **Push origin**.
5. Click **Create Pull Request** (opens GitHub in the browser) → Create. Tell Pankaj. He reviews and merges.
6. Before new work: **Fetch origin**, then Branch → **Update from main**.

---

## 2. Before the event (30 to 31 Oct)

Preparing is allowed; the project itself is built during the 24 hours.

| Who | Task | Done |
|---|---|---|
| All | GitHub account; tell Pankaj the username | ☐ |
| All | Install VS Code, Node.js 22, GitHub Desktop, Chrome; run `node -v` | ☐ |
| All | Read your guide once, and [JUDGE_QA.md](JUDGE_QA.md) twice | ☐ |
| Pankaj | Create the empty `mindmirror` repo, add Merel + Kishore as collaborators | ☐ |
| Pankaj | Groq API key; Merel makes a backup key on her account | ☐ |
| Pankaj + Kishore | Solder headers on the mic and amp; install Arduino IDE + ESP32 core 3.x; pass hardware tests 1 to 4 | ☐ |
| Pankaj | Run the hub with the real key on home Wi-Fi and on the phone hotspot (2.4 GHz, name `MindMirror`) | ☐ |
| Merel | Practise the deck aloud 3 times with the speaker notes. Time it. | ☐ |
| Merel | Do the "React in 20 minutes" warm-up in your guide, so Sunday isn't your first time | ☐ |
| Kishore | Pick 10 calm reference screenshots; do the same warm-up in your guide | ☐ |
| All | Pack: laptops + chargers, **extension board** (rules say bring your own), power bank, 2 USB cables, hardware box, soldering kit, insulation tape, hot glue, cardboard, scissors, college IDs | ☐ |
| All | Sleep well on Saturday night | ☐ |

---

## 3. Hour by hour

### Sunday 10:00 to 16:00: the observed hours

Judges and volunteers walk around. They want to see **three people each clearly working on their own part, talking to each other, with a plan on the table**. That's exactly what this block is, so it's not acting: it's the real work.

Keep a printed or on-screen copy of the roles table (section 1) on the desk. When a judge stops by, whoever is nearest says one sentence about the project and one about what they're doing right now, then hands over to the owner of whatever the judge points at. Scripts are in JUDGE_QA.md, "When a judge walks up".

| Time | Pankaj | Merel | Kishore |
|---|---|---|---|
| **10:00–10:30** | All: confirm rules at the desk, set up table + power, read the plan together | | |
| **10:30–11:30** | Create Vite app + `hub/`, README disclosure, push `main`. Help both clone and run | Clone, run, create `merel/play`. **Interview 4 to 6 students** at the venue (questions in your guide) | Clone, run, create `kishore/ui`. Tailwind colours + font. Start `ui.tsx` |
| **11:30–13:00** | `db.ts`, sample data, check-in saving | `copy.ts` (all app words) → **first commit + PR** | `ui.tsx` (Button, Card, Slider, Toggle, Screen) → **first PR** |
| **13:00–13:30** | **Sync 1** + lunch. Pankaj merges both PRs | | |
| **13:30–16:00** | `signals.ts` + tests | **Game 1: Bubble wrap** → PR. Then `research.md` from interviews | `CheckIn.tsx` → PR. Then `Weather.tsx` |
| **16:00** | **Sync 2.** Pankaj merges. Show each other what's on screen | | |

### Sunday 16:00 to Monday 02:00: deep work

| Time | Pankaj | Merel | Kishore |
|---|---|---|---|
| **16:00–19:30** | IoT with Kishore: breadboard, tests 1 to 4 again, firmware ↔ hub, first full voice turn | **Game 2: Worry shredder** → PR. Then `Play.tsx` (the room with 3 game cards) | IoT with Pankaj: read pin table aloud, tick wires; commit `firmware/tests/` + photos |
| **19:30–20:00** | Dinner + **Sync 3** | | |
| **20:00–23:00** | Insights + live necklace turns in app (`hub.ts`) | **Game 3: Ripples pond** → PR | `SignalCard.tsx`, `Chat.tsx` → PR. Then `Breathe.tsx` |
| **23:00–02:00** | Necklace polish (volume, LED, error sounds) | `Support.tsx` (ladder + Tele-MANAS) → PR. Then 😴 **sleep 00:30–04:30** | Pendant enclosure (female-female jumpers, box, holes). 😴 **sleep 01:00–05:00** |

### Monday 02:00 to 10:00: finish, freeze, present

| Time | Pankaj | Merel | Kishore |
|---|---|---|---|
| **02:00–05:00** | **Claude pass:** connect every screen, fix bugs, integrate Merel's and Kishore's files (don't replace them) | 😴 | 😴 |
| **05:00–06:00** | 😴 **sleep 05:00–07:00** (alarm!) | Wake 04:30. Test every screen as a new user, write issues | Wake 05:00. Fix UI issues Merel logs in your own files |
| **06:00–07:00** | 😴 | Update deck numbers/screenshots if anything changed | Screenshots + necklace photos/video for slides |
| **07:00** | **Feature freeze. Sync 4** + breakfast. Tag `v-demo` | | |
| **07:00–08:30** | Final fixes only; README run steps | **Record demo video** (2 to 3 min) | Film necklace close-ups for the video |
| **08:30–09:30** | Submit (repo, video, slides). Check the repo runs on Kishore's laptop | **Full rehearsal ×2** with live demo, timed | Rehearsal: run the necklace part of the demo |
| **09:30–10:00** | All: Q&A drill from JUDGE_QA.md, 10 random questions each | | |
| **10:00** | **Final presentation** | | |

If something slips, cut in this order: Ripples pond → Breathe → planner. **Never cut** the support screen, the necklace demo, or the rehearsal.

---

## 4. Who presents what (final presentation)

**Merel speaks for the whole presentation.** Pankaj and Kishore help with their hands and step in only if a judge asks them directly.

| Part | Who |
|---|---|
| Every slide, opening to closing | **Merel** speaks |
| Live demo: app | **Merel** drives the laptop and talks |
| Live demo: necklace | **Kishore** hands Merel the necklace; Merel speaks into it. **Pankaj** keeps the hub log on screen |
| Technical questions | Merel gives the one-line answer, then may hand to **Pankaj** for details |

The full script is in [PITCH_SCRIPT.md](PITCH_SCRIPT.md).

---

## 5. How this earns points

| Criterion (weight) | What earns it | Owner |
|---|---|---|
| Innovation & creativity (20%) | personal baseline instead of generic rules; a necklace you talk to; proof under every insight; calm games instead of "tips" | all |
| Technical complexity (25%) | tested signal engine; ESP32 with two I2S audio streams over Wi-Fi; hub pipeline (speech → AI → voice); live events into the app | Pankaj, Kishore (hardware) |
| Functionality & usability (20%) | the full flow works on stage; check-in under 60 s; calm, readable UI | Kishore (UI), Merel (games, testing) |
| Presentation & communication (15%) | real interview quotes, tight story, clean live demo | Merel |
| Impact & practicality (10%) | maps 1:1 to the problem statement; crisis routing to Tele-MANAS; next steps | Merel |
| Team collaboration (10%) | roles table, branches and PRs from three accounts, everyone answers questions | all |
