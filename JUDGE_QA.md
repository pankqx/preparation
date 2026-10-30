# Judge questions and answers (for all three of us)

Everyone learns **all** of this, not only their own part. If someone freezes, the next person picks it up: "Can I add to that?" is a team move, not a rescue.

Each question shows who answers first (**Lead**) and who backs them up (**Backup**). P = Pankaj, M = Merel, K = Kishore.

---

## 0. How to answer

1. **Two or three sentences, then stop.** Judges ask follow-ups if they want more.
2. **Start with the answer, then the reason.** "Yes, because…", "No, we chose X because…".
3. **Be honest about limits.** "We haven't tested that with real students yet; here's how we would" beats a confident guess. Judges are experts and spot bluffing instantly.
4. **Use the words "your own normal", "proof" and "we never diagnose".** They're the heart of MindMirror.
5. **Don't know?** "Good question. I don't know the exact number. Pankaj, do you?" or "We'd measure that by…". Never invent numbers.
6. **Hand over by name** when a question belongs to someone else: "Kishore wired that, he'll explain."
7. Look at the judge, not the laptop. Smile. Slow down.

---

## 1. Lines everyone memorises

**The 30-second pitch**
> Stress and burnout build slowly: a bit less sleep, a few more deadlines, fewer friends. Students don't notice until it hurts. MindMirror notices for them. You check in for 30 seconds a day, or just talk to our necklace. We compare you with *your own* normal, not with a generic rule, and show the proof: "you slept 1.6 hours less than usual this week". Then we suggest one small step, and if it gets heavy, we point you to real people. We never diagnose.

**One line each**
- *What is it?* "A well-being companion app plus an AI necklace that helps students notice early signs of stress, without diagnosing."
- *What's new?* "It compares you with your own baseline and shows the proof for every insight."
- *Why the necklace?* "For the moments you won't open an app. Hold, talk, hear a calm reply."
- *Is it safe?* "It never diagnoses, data stays on your device, and crisis words go straight to Tele-MANAS 14416 and 112."

---

## 2. When a judge walks up during the day (Sunday 10:00 to 16:00)

Whoever is nearest stands or turns, smiles, and says:

> "Hi! We're HTTP Dino, MindMirror. It's an app plus a talking necklace that helps students notice early signs of stress compared with their own normal. Right now I'm building ___."

Then each person's "right now" line:

- **Pankaj:** "…the signal engine: the code that compares this week with your usual and writes the proof sentence. Or the laptop hub that turns the necklace's voice into a reply."
- **Merel:** "…the Play room: three calm games for releasing pressure, like bubble wrap. And I interviewed students here this morning; can I show you what they said?"
- **Kishore:** "…the interface: calm colours, the check-in cards. And with Pankaj I'm wiring the necklace: this is the microphone, this is the amplifier."

Show, don't tell: turn the laptop so they can see what's running. If they ask about someone else's part, hand over by name. Before they leave: "Would you like to try a check-in or pop some bubbles?"

---

## 3. Problem and idea

**Q: What problem are you solving?**
Lead M · Backup K
> Students slide into stress and burnout slowly, through less sleep, more pressure, isolation and lower energy. Each day looks fine, so nobody notices until grades or relationships suffer. MindMirror spots the slow drift early and points to help.

**Q: Why students?**
Lead M · Backup P
> Students have the most predictable pressure cycles, like exams and submissions, and the least support in noticing their own patterns. It's also what the problem statement asks for, and we're students, so we know the problem first hand.

**Q: What did real students tell you?**
Lead M · Backup K
> We interviewed ___ students here on Sunday morning. [Merel: fill in your best quote and your "X of Y" number from research.md.] That's why the check-in takes under a minute and why there's a necklace: people won't open another app when they're already tired.

**Q: Isn't this just a mood tracker?**
Lead P · Backup M
> A mood tracker shows you what you typed. MindMirror compares you with your own baseline across five signals (sleep, pressure, connection, energy and drive) and tells you what *changed*, with the proof. It also links well-being to workload, and it tells you what to do next.

**Q: Who are your competitors?**
Lead M · Backup P
> Wysa, Headspace, Calm and phone screen-time reports. Meditation apps help *after* you know you're stressed. Chatbots talk, but don't track change over weeks. Screen-time apps count minutes, not well-being. We're the early-warning layer: notice, understand, then reach out.

---

## 4. How it works (the engine)

**Q: What is a "personal baseline"?**
Lead P · Backup K
> It's your own normal. For each measure, we take the median of your last two weeks, skipping the last three days. Then we compare your last three days against it. If you usually sleep 7 hours and now sleep 5.4, that's a change of 1.6 hours, even though 5.4 might be normal for someone else.

**Q: Why the median and not the average?**
Lead P · Backup K
> One bad night shouldn't change what "normal" means. The median ignores single outliers, so the baseline stays stable and we only flag real drifts.

**Q: What are the five signals?**
Lead K · Backup M
> They map one-to-one to the problem statement. Academic pressure → **Pressure** (stress check-ins and hours of work due vs planned). Poor sleep → **Sleep**. Isolation → **Connection** ("did you talk to someone you like?"). Exhaustion → **Energy**. Loss of motivation → **Drive** (mood, and what you say to the necklace).

**Q: How do you decide when to warn someone?**
Lead P · Backup K
> Each signal has two thresholds. For sleep, 0.75 hours below your usual is "watch" and 1.5 hours below is "needs care". We add the signals into a "mind weather": clear skies, passing clouds, soft rain or heavy skies. The weather picks a step on the support ladder.

**Q: Where do those thresholds come from? Are they clinically validated?**
Lead P · Backup M
> No, and we say so. They're sensible starting points we chose for a prototype, written as code with tests so they're easy to tune. In a real rollout we'd tune them with a campus counsellor and student data, with consent.

**Q: What's the support ladder?**
Lead M · Backup K
> Four steps: look after yourself, take one small step today, reach out to a friend or mentor, and talk to someone trained (campus counsellor or Tele-MANAS 14416). The app shows where you are and the next step up. It's always one small action, never a lecture.

**Q: How do you know your numbers are right?**
Lead P · Backup K
> The engine is plain code with no AI in it, and it has unit tests: for example, three short nights after two normal weeks must give "needs care" and the exact difference. Every insight on screen shows the numbers it came from, so the student can check too.

**Q: What if someone has only used it for two days?**
Lead P · Backup M
> Then there's no baseline yet, and the app says "learning your normal" instead of guessing. It needs at least five days. For the demo we use three weeks of sample data, and we say that it's sample data.

**Q: Why should a student check in every day?**
Lead M · Backup K
> It takes under a minute, it can be a voice note to the necklace, and they get something back right away: the weather, a proof, a small step, or a game. We'd add gentle reminders at the student's chosen time.

---

## 5. AI and safety

**Q: Where exactly is AI used?**
Lead P · Backup K
> Three places, all in the laptop hub. Whisper turns speech into text. A language model writes a short, warm reply. A text-to-speech voice reads it out. The numbers and the warnings are never AI: plain code calculates them, and the AI only explains them.

**Q: Which models?**
Lead P · Backup K
> Whisper large-v3-turbo for speech, an open-weight GPT-OSS 20B model for replies (both served by Groq), and Microsoft's Edge neural voice, Indian English, for speech.

**Q: How do you stop the AI from saying something harmful?**
Lead P · Backup M
> Three layers. First, crisis words like "I want to die" never reach the AI: the code answers with a fixed message giving Tele-MANAS 14416 and 112. Second, the AI's instructions forbid diagnosing, naming disorders or giving medical advice, and limit it to two short sentences. Third, it only gets the facts the engine has already calculated, so it can't invent your data.

**Q: What happens if someone types or says they want to end their life?**
Lead M · Backup P
> The app shows the urgent help card straight away: Tele-MANAS 14416, free, 24×7, and 112. The necklace says the same thing out loud and asks them to tell someone near them. That reply is fixed in code, so it's the same every time. *(Offer to show it. It's the strongest safety demo you have.)*

**Q: Can't someone in crisis avoid your keywords?**
Lead P · Backup M
> Yes. A keyword list can't catch everything, which is exactly why we don't claim to detect crises. The ladder, the weather and the always-visible Support screen are there for everyone. A next step is a classifier-based check, reviewed with professionals.

**Q: Isn't this diagnosing?**
Lead M · Backup P
> No. We never name a condition and never say "you are depressed". We show changes against *your own* normal ("you slept less than usual") and suggest small steps or people to talk to. The footer of the app says it's not a medical device.

**Q: What if the AI is wrong?**
Lead P · Backup K
> The AI can only phrase things. The facts come from tested code and are shown with their numbers. If the reply sounds off, the proof is still there and correct.

---

## 6. Privacy and data

**Q: Where is the data stored?**
Lead P · Backup M
> In the student's own browser (IndexedDB). There's no account and no database server. Check-ins, insights, chat history and games all stay on the device.

**Q: But the voice goes to the cloud?**
Lead P · Backup M
> Yes, for transcription and the reply, and we're upfront about it. Our hub doesn't save the audio; it's processed and thrown away. In Round 1 we built a fully on-device version, with Whisper and a small language model in the browser; that's the production path. For a 24-hour build we chose reliability.

**Q: Could a college or parent see a student's data?**
Lead M · Backup P
> No. There's nothing to see, because it never leaves the device. In future, a student could *choose* to share a summary with a counsellor, but only they decide.

**Q: Can I delete my data?**
Lead P · Backup K
> Yes, everything is local, so one button clears it. *(If the button wasn't built, say: "That's one line of code, `db.delete()`, and it's next on our list.")*

**Q: What about the API key?**
Lead P · Backup K
> It stays in the hub's `.env` file on the laptop, never in the web app and never in GitHub.

---

## 7. The AI necklace (hardware)

**Q: What's inside it?**
Lead K · Backup P
> An ESP32 board (the brain, with Wi-Fi), an INMP441 digital microphone, a MAX98357A amplifier, an 8-ohm half-watt speaker, and a push button. It's powered by USB from a power bank.

**Q: How does it work, step by step?**
Lead K · Backup P
> You hold the button and the ESP32 reads the mic 16,000 times a second. It streams that sound over Wi-Fi to the hub on the laptop while you're still talking. When you let go, the hub turns speech into text, writes a reply and turns it into speech. It sends the audio back, and the ESP32 plays it through the amplifier and speaker. The app shows the conversation at the same moment.

**Q: What's I2S?**
Lead K · Backup P
> It's a simple way to send digital sound between chips using three wires: a clock (bit clock), a "left or right" signal (word select), and the data. The ESP32 has two I2S engines, so we use one for the mic and one for the amplifier at the same time.

**Q: Why do you need an amplifier?**
Lead K · Backup P
> An ESP32 pin can't power a speaker; it gives tiny currents. The MAX98357A takes the digital sound and drives the speaker directly. It even converts digital to analog inside, so we don't need a separate DAC.

**Q: Why Wi-Fi and not Bluetooth?**
Lead P · Backup K
> Bluetooth would need a custom audio protocol and compression. In Round 1 we designed exactly that, and it's complex. Wi-Fi gives plain HTTP: simple, fast enough, and easy to debug in 24 hours. The cost is power, which is why it's on a power bank for now.

**Q: How does it find the laptop?**
Lead P · Backup K
> The hub broadcasts "I'm here" on the hotspot every two seconds over UDP. The necklace listens for that and learns the laptop's address, so nobody types IP addresses.

**Q: How long does a reply take?**
Lead P · Backup K
> About two to four seconds on a good connection. Speech-to-text and the reply take under a second each on Groq; the voice takes about a second. *(Pankaj: after real testing on Sunday, replace this with your measured numbers; the hub log prints them.)*

**Q: How long does the battery last?**
Lead K · Backup P
> Right now it runs from a USB power bank, so many hours. A built-in battery is next: the ESP32 draws roughly 100 to 250 mA when talking, so a 1000 mAh cell would last a few hours of real use.

**Q: Can it work without internet?**
Lead P · Backup K
> Not for the AI replies in this version. Without the hub, it plays an error sound, so it never fails silently. The app works fully offline. The on-device path we built in Round 1 removes the internet dependency.

**Q: Isn't a speaking necklace awkward in public?**
Lead M · Backup K
> It's quiet, about as loud as a phone speaker held close, and you choose when to press. Many students already talk to voice assistants. In our interviews, ___ out of ___ said they'd try it. *(Merel: fill in.)*

**Q: Why not just use a phone?**
Lead M · Backup P
> You can: the app has the same "hold to talk" button. The necklace is for moments when you won't unlock your phone, like walking back from class or lying in bed. One press and you're heard, with no screens and no notifications pulling you in.

**Q: What did it cost?**
Lead K · Backup P
> Roughly ₹___ for all the parts. *(Pankaj: fill in the real total.)* At scale, a custom board would be much cheaper.

**Q: Did you build the hardware or buy a kit?**
Lead K · Backup P
> We bought separate parts, soldered the headers, wired them ourselves using our own pin plan, tested each part with four small test programs, and made the pendant case by hand.

---

## 8. Software and architecture

**Q: What's your tech stack?**
Lead P · Backup K
> React, TypeScript and Vite for the app, Tailwind for styling, framer-motion for gentle animation, Recharts for charts, and Dexie for local storage. The hub is Node.js. The firmware is Arduino C++ on the ESP32.

**Q: Draw the architecture.**
Lead P · Backup K
> Three parts. The necklace talks to the hub over Wi-Fi. The hub talks to the AI services and pushes each conversation to the web app using Server-Sent Events. The web app stores everything locally and runs the signal engine. *(Point to the architecture slide.)*

**Q: Why a web app and not Android?**
Lead P · Backup M
> A web app runs on any laptop or phone without installing, and it was fastest to build in 24 hours. It can be installed like an app (a PWA). A native Android version is the next step, mainly for reminders and background use.

**Q: What was the hardest technical problem?**
Lead P · Backup K
> Streaming audio both ways on a small chip with little memory. We can't hold a long recording in RAM, so the necklace streams it in small pieces while you talk, with a one-second buffer so Wi-Fi hiccups don't lose words. *(Or name whatever was actually hardest on the day; a real story is better.)*

**Q: What did you build during the hackathon and what was ready before?**
Lead P · Backup M
> We came with the idea, the design and the guides from Round 1, the hardware bought and soldered, and reference code for the necklace and hub that we prepared and disclosed in the README. Everything in the new repository, the app, games, engine and integration, was built in these 24 hours. The commit history shows who built what and when.

**Q: Did you use AI to code?**
Lead P · Backup M
> Yes, the rules allow it, and we disclosed it in the README. Pankaj used Claude; Merel and Kishore used ChatGPT. We used it like a fast teammate. We decided the design, the logic and the safety rules, and we tested what it wrote.

---

## 9. Games, design and usability

**Q: Why games in a mental-wellness app?**
Lead M · Backup K
> Because when you're stressed, reading tips doesn't help; doing something with your hands does. Our games have no scores, no timers and no way to lose. Bubble wrap releases tension. Worry shredder lets you type a worry and watch it shred and fade. Ripples pond is calm: you tap the water and watch rings spread.

**Q: How did you build the games?**
Lead M · Backup P
> Each game is its own React component. Bubble wrap is a grid of buttons that remember if they're popped, with a soft sound. Worry shredder takes your text and animates it into strips that fall and fade. Ripples draws expanding circles on a canvas wherever you tap. *(Merel: open your file and show it.)*

**Q: Why these colours?**
Lead K · Backup M
> We chose calm, not clinical. Soft indigo, sage green and warm cream lower the energy of the screen. Red is used only for urgent help, so it means something when it appears. A signal that needs care is a soft coral, so it's noticed without alarm.

**Q: How long does a check-in take?**
Lead K · Backup M
> Under 60 seconds: five taps, one question per card, and an optional note. Or ten seconds by voice on the necklace.

**Q: Is it accessible?**
Lead K · Backup M
> We kept big tap targets, high-contrast text, one question at a time and a voice option, which helps people who don't like typing. Full screen-reader testing is on our next-steps list.

---

## 10. Team and process

**Q: How did you divide the work?**
Lead K · Backup M
> By ownership. Pankaj led the tech, the AI engine and the necklace firmware. Merel did user research, all the words in the app, the games, the support screen and the presentation. I did the design, the interface components, the check-in and breathing screens, the hardware tests, and the necklace's case. Each of us worked on our own branch and Pankaj merged them.

**Q: How did you coordinate?**
Lead M · Backup K
> A written plan with roles and an hour-by-hour schedule, and a ten-minute sync every three hours. Each person had their own branch and pull requests, and the commit history shows all three of us contributing.

**Q: What would you do differently?**
Lead P · Backup M
> Test the hardware with real users earlier. And tune the thresholds with a counsellor. *(Add a real lesson from the day.)*

**Q: What did you learn?** (often asked to first-timers)
Lead K, then M
> *Kishore:* "How sound actually travels from a microphone to a speaker as numbers. And how much a calm interface changes how an app feels."
> *Merel:* "That students' real words make the best product decisions, and how to turn an idea into a working React component."

---

## 11. Impact, scale, business

**Q: Who would use this and how would it reach them?**
Lead M · Backup P
> College students first, through campus wellness cells and student clubs. The app is free and runs in a browser, so a college can share a link at orientation. The necklace is optional.

**Q: How would you make money?**
Lead M · Backup P
> Free for students. Colleges could pay for a campus edition with their own counsellor contacts and opt-in, anonymous, aggregated trends (for example "exam weeks raise stress"). It would never show individual data. The necklace could be sold at cost or lent through the wellness cell.

**Q: How does it scale?**
Lead P · Backup M
> The app scales almost for free: it's a static website and all the computing happens on the student's device. Only voice uses a server, and that moves on-device in the production version.

**Q: How would you measure impact?**
Lead M · Backup P
> Opt-in surveys: did students notice changes earlier, did they take a step, did more of them reach out to a counsellor before exams? And retention: do they still check in after a month?

**Q: What's next?**
Lead M · Backup P
> Smartwatch sleep and heart-rate data, a battery-powered necklace, fully on-device AI, an Android app with gentle reminders, and a pilot with our college's counselling cell.

---

## 12. Tough and tricky questions

**Q: Your thresholds are made up. Why should I trust it?**
Lead P
> They're starting points, not medical claims, and the app never claims to diagnose. What we trust is the *method*: comparing you with yourself and showing the proof. The thresholds are one line of code each and are covered by tests, so they're easy to tune with professionals.

**Q: Students lie in check-ins.**
Lead M · Backup P
> Sometimes. But they're lying only to themselves, since nobody else sees it. And we look for *changes* in their own answers over days, which is more robust than any one answer. Voice helps too: people say more than they'd type.

**Q: What if the student doesn't want to be told they're struggling?**
Lead M
> We don't tell them they're struggling. We show what changed and offer a small step. The tone is a friend's, not a doctor's. They can ignore it, play a game, or just breathe.

**Q: The demo uses sample data. Does it really work?**
Lead P · Backup K
> The engine is the same code on real and sample data, and it's tested. Sample data is there because a baseline takes two weeks to build. *(Then do a live check-in to show it updating.)*

**Q: This already exists.**
Lead M · Backup P
> Parts of it exist separately. Nobody combines personal-baseline signals, workload, proof for every insight and a voice wearable into one student-first tool, with privacy by design.

**Q: The necklace fails during the demo. (It might!)**
Whoever is holding it:
> "Live hardware! The same pipeline is in the app: here's Hold to talk." *(Use the web button, keep smiling, move on. Pankaj checks the hub log quietly.)*

---

## 13. Numbers to know

| Fact | Value |
|---|---|
| Check-in time | under 60 s |
| Signals | 5 (sleep, pressure, connection, energy, drive) |
| Baseline | median of days 4 to 17 ago; needs ≥ 5 days |
| Recent window | last 3 days (connection: 4) |
| Sleep thresholds | −0.75 h watch, −1.5 h needs care |
| Mic sampling | 16,000 samples per second, 16-bit |
| Reply time | about 2 to 4 s *(replace with measured)* |
| Helplines | Tele-MANAS **14416** (free, 24×7), emergency **112** |
| Parts | ESP32-WROOM-32 DevKit, INMP441, MAX98357A, 8 Ω 0.5 W speaker, push button |
| Parts cost | ₹___ *(fill in)* |
| Students interviewed | ___ *(fill in on Sunday)* |
