// Натаниэль Хоук - пиратский барон Марун-Тауна
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			dialog.text = "Want something?";
			link.l1 = "No, it's nothing.";
			link.l1.go = "exit";			
			NextDiag.TempNode = "First time";
		break;
		
		case "diffindoor":
			PlaySound("Voice\English\saga\Nataniel Hawk-02.wav");
			dialog.text = "Ah... who are you, damn it?.. Khe... (severe cough with hoarseness) Damn weakness...";
			link.l1 = "Greetings, Nathaniel. You are Nathaniel Hawk, aren't you?";
			link.l1.go = "diffindoor_1";
		break;
		
		case "diffindoor_1":
			dialog.text = "Yes, it's me, if I can still call myself by that name. I was once Nathaniel Hawk, but now I am just a sad-looking bag of shit. Damn that statue! It has sucked all the life out of me.";
			link.l1 = "I am familiar with the feeling...";
			link.l1.go = "diffindoor_2";
		break;
		
		case "diffindoor_2":
			dialog.text = "How could you, lad, if you don't even realise what I'm talking about? A-kha... Do you know what it's like to suddenly become a half-dead old man, when just a minute ago I was healthy and strong?\nI've seen a lot in my time. I thought that ancient Indian temple I visited in my youth had killed my ability to be surprised, but this... why didn't I see it coming! That blasted statue looked just like the old idol that opened the door to the temple!";
			link.l1 = "Fine, Nathan, let's talk. Allow me to introduce myself, I am "+GetFullName(pchar)+". First, I understand you very well, because I came here the same way you did – through the Kukulcan portal.";
			link.l1.go = "diffindoor_3";
		break;
		
		case "diffindoor_3":
			dialog.text = "Really?! Then why do you look just fine? Or has that... Kukulcan harmed only me?";
			link.l1 = "Snake Eye, the Miskito shaman who helped you escape, has given me a very strong potion. I drank it as soon as I woke up in San Augustine. It completely healed me. I am sure that Snake Eye can help you too. We just need to get you to him.";
			link.l1.go = "diffindoor_4";
		break;
		
		case "diffindoor_4":
			dialog.text = "Ah, that Indian! A potion? And why didn't he give one to me as well?";
			link.l1 = "He said there was no time. You were being chased, and the only thing he could do was show you the way to escape – the portal.";
			link.l1.go = "diffindoor_5";
		break;
		
		case "diffindoor_5":
			PlaySound("Voice\English\saga\Nataniel Hawk-01.wav");
			dialog.text = "Escape? Oh... Can't you see the state I'm in? I can't even hold a sabre. How can you call this an escape? Thank God, there are still good people in this world. Ole, God bless him... Do you know Ole?";
			link.l1 = "Yes. Actually, he was the one who told me about you, he told me how he fed you rats and how you keep drinking, bottle after bottle...";
			link.l1.go = "diffindoor_6";
		break;
		
		case "diffindoor_6":
			dialog.text = "I will die faster than a lit candle if I don't drink rum. It is the only thing keeping me alive. Rum...";
			link.l1 = "Are you still feeling that bad? The same as after teleportation?";
			link.l1.go = "diffindoor_7";
		break;
		
		case "diffindoor_7":
			dialog.text = "Well, I am not feeling quite the same... But also not really better. Pal, tell me, why did you need to see old Nathan? Why the hell did you come here, onto this old, rotten tub? To chat with me?";
			link.l1 = "Actually, yes. You won't believe me, but the reason I went through all that trouble with teleportation was to find you. I work for the Brethren of the Coast and I represent Jan Svenson.";
			link.l1.go = "diffindoor_8";
		break;
		
		case "diffindoor_8":
			dialog.text = "Damn it... the Forest Devil? Argh... Did you come here to finish me off? Actually, you didn't? You're too talkative for an assassin. Please - don't torture me. If you were ordered to get something out of me - I'll tell you everything myself, I've got nothing to hide.";
			link.l1 = "What do you mean? A-ah, I see. You, just like Danielle, think that Svenson was the one who arranged that ambush on your life in the selva. I can assure you that Jan didn't do it. On the contrary, he is on your side and is very worried about your disappearance.";
			link.l1.go = "diffindoor_9";
		break;
		
		case "diffindoor_9":
			dialog.text = "Really? I am damn glad to hear that. And I have already been thinking... but who did it? My detachment was destroyed in minutes. They were waiting for us. They even had ship's cannons! They mowed down half of my men with grapeshot and then finished us off with their muskets...";
			link.l1 = "To be honest, I don't know the details, but I am sure that Jackman is behind all of this. Too many coincidences, first Blaze, then you... Jackman wants to seize power and eliminates everyone who stands in his way. He rules Maroon Town now instead of you.";
			link.l1.go = "diffindoor_10";
		break;
		
		case "diffindoor_10":
			dialog.text = "Jackman? Bastard! Eh... the Brethren have become divided in the last couple of years, it was all different before. Zachariah has gone mad with his religious obsessions, Tyrex doesn't give a damn about anything, and Barbazon is only interested in doubloons. It was all different twenty years ago...";
			link.l1 = "How did they capture you? Tell me more.";
			link.l1.go = "diffindoor_11";
		break;
		
		case "diffindoor_11":
			dialog.text = "There is nothing interesting to tell! As I said, those bandits planned the whole thing. They acted with precision, coordinated and clearly following someone's orders. They could have killed me a hundred times, but they didn't. They wanted me alive. They took me to an abandoned mine and locked me inside one of the huts. 'Until the boss arrives', they said.\nI thought that Svenson was the boss, but it seems that Jackman is in charge. I don't know what he could have wanted from me, though, but I am sure I wouldn't have lived long after chatting with him.";
			link.l1 = "I have no doubt about that. Svenson is sure that Jackman killed Blaze Sharp... How did you manage to escape?";
			link.l1.go = "diffindoor_12";
		break;
		
		case "diffindoor_12":
			dialog.text = "That Indian Snake Eye somehow managed to sneak into the mine. As far as I understand, the Miskito don't like bandits. Anyway, Snake Eye arranged my escape for some reason. He dug a tunnel to me, got inside, cut my ropes, and we ran away into the jungle.\nHe wanted to take me to his village, to the Miskito. But it seems Jackman wanted me badly, as a big hunt was organised. They were close on our heels. Snake Eye did his best to fool them, but they always managed to find our trail. They had good pathfinders, no doubt.\nWe were close to Snake Eye's village when they finally found us. By that point, my stomach had been empty for two days and I was completely spent, as I had also badly injured my leg. It was midnight, and I still remember how bright the star over the statue was... Snake Eye said that my only chance was to make it to the idol and touch it.\nI thought the man was mad, but you know what they say about clutching at straws. I hobbled to the statue, touched it... and then crazy things started to happen!";
			link.l1 = "You don't need to continue, I know what happened afterwards.";
			link.l1.go = "diffindoor_13";
		break;
		
		case "diffindoor_13":
			dialog.text = "I found myself in the damp hold of a wrecked ship. I was half dead. Couldn't walk, only crawl. With every minute, my condition worsened. Ole showed up just in time. He poured some Caribbean concoction that tasted foul into me, a mix of antidote and healing essence. Then he gave me rum.\nI felt better immediately. Then he found an old log and used it to move me here. I've been living here for some time now, though I can't say exactly how long—I've lost track of time.";
			link.l1 = "It will be alright, Nathan. Svenson and I have great plans, and your role in them is very significant. You must return to your position in Maroon Town and we will deal with that scum Jackman.";
			link.l1.go = "diffindoor_14";
		break;
		
		case "diffindoor_14":
			dialog.text = "Maroon Town? And how exactly do you imagine this will work? Look at me, I am a rum-soaked wreck! Worthless... No, my years of authority over Maroon Town are gone forever. I am trapped in this bloody ship cemetery. How long will I last? A month, two, a year?\nAnd then I will end up lying on these rotten planks and Ole will throw what is left of Nathaniel Hawk into the sea. The worst part is that I won't see my Dannie again. Eh, it's over, pal.";
			link.l1 = "Don't be so pessimistic. I will get you out of here.";
			link.l1.go = "diffindoor_15";
		break;
		
		case "diffindoor_15":
			dialog.text = "How will you get me out of here? And how are we going to leave this place? There are no ships. Do you want to build a raft?";
			link.l1 = "No. I will leave this place the same way I came here. I know where the statue is... well, roughly. I will find it and then I will be back for you and Shark Dodson. We will get you to Snake Eye after that. He will heal you.";
			link.l1.go = "diffindoor_16";
		break;
		
		case "diffindoor_16":
			dialog.text = "What did you say? Shark Dodson? Is Steve here as well? Such a strange place...";
			link.l1 = "Yes, he is here. He is the 'governor' of this island, so to speak. I have asked him about you, but he doesn't know a thing.";
			link.l1.go = "diffindoor_17";
		break;
		
		case "diffindoor_17":
			dialog.text = "And he shouldn't. I don't want him to see me in this condition. You said that the shaman would heal me... I can hardly believe it. You mentioned Dannie too... Did you see her?";
			link.l1 = "Yes. She found me herself in Blueweld. She eavesdropped on my conversation with Svenson and realised that Jan had no intention of killing you and that he is working against Jackman. She joined my ship as an officer to help me find you.";
			link.l1.go = "diffindoor_18";
		break;
		
		case "diffindoor_18":
			dialog.text = "Eh, my dear Dannie! She hasn't changed... as reckless as she was in her youth... You can't even imagine how much I want to see and embrace her now! I've done a lot of thinking while lying here. You see, mate, you start to look at things differently when you're close to death. I've spent so little time with my wife! Sea raids, Brethren's official business, ruling Maroon Town. And she always supported me in everything: stayed alone for weeks, quarrelled with other pirates while I was away, commanded our ship... My Dannie is the finest woman in the world! And I... I should have told her more often that I love her! I remember the day we decided to be together! In fact, that was the day I first encountered and fought supernatural things. It all happened because of that blasted idol that looked just like the statues. You don't mind hearing a story, do you? It's quite interesting.";
			link.l1 = "Not at all! Tell me!";
			link.l1.go = "story";
			link.l2 = "Nathan, we don't have time for pleasant memories. Tell me about it later, when we're sitting in the Miskito village with a bottle of wine.";
			link.l2.go = "diffindoor_19";
		break;
		
		case "story":
			dialog.text = "It was twenty-five years ago... I was young, ardent and restless. The Caribbean was my playground. I already knew Dannie back then. I liked her, I truly did, and the feeling was mutual. But we often fought, quarrelled and jibed at each other. Foolish youth... I believe we were great entertainment for the respected sailors back then! Anyway, somehow Dannie and I became involved in the same story. We had found a map of Khael Roa, and were told it was THE place to find Indian gold. We had also discovered a strange-looking golden idol, a smaller copy of the top part of the statues. The idol was dangerous; it drained vitality from those who carried it. But we needed that cursed item in order to reach the treasury inside the temple. The only problem was that we had no idea how to properly use it. Dannie and I sailed to the island. There was an ancient temple, overgrown with grass and trees. Once we entered, we found ourselves inside a huge labyrinth. We managed to find the right path and reached the central part of the labyrinth. We thought it was a dead end, but when desperation began to overtake us, we saw a strange platform with a small socket and a picture on it. I put the idol into the socket and...";
			link.l1 = "...";
			link.l1.go = "exit";
			pchar.questTemp.LSC.Natanstory = "idol";
			AddDialogExitQuest("Video_story");
			NextDiag.TempNode = "story_1";
		break;
		
		case "story_1":
			dialog.text = "The stone platform sank a few inches, and one of the walls turned out to be a secret passage. The idol was left inside the platform; I failed to pull it back out. Finally, we reached a giant hall. Such a beautiful sight!   The most magnificent structure I've ever seen. Carvings on the walls, huge statues... We searched the whole hall, but found no sign of treasure.";
			link.l1 = "Heh, that does happen quite often to people like us. A lot of effort and no result in the end...";
			link.l1.go = "story_2";
		break;
		
		case "story_2":
			dialog.text = "It wasn't for nothing. After all, we entered a throne hall with a giant statue of a bird at the end of it. There was a mystical light near the statue, it looked just like the light above the idol at midnight. We went closer and saw a beautiful floating sphere. I swear, I am telling you the honest truth!\nIt was real, but at the same time it felt as if it wasn't. While I was thinking, Dannie – oh, that reckless devil – touched the sphere. It started to glow even brighter and finally turned into a small item in her hands...";
			link.l1 = "...";
			link.l1.go = "exit";
			pchar.questTemp.LSC.Natanstory = "temple";
			AddDialogExitQuest("Video_story");
			NextDiag.TempNode = "story_3";
		break;
		
		case "story_3":
			dialog.text = "It seemed that we had committed a sacrilege. The temple came alive: everything around us started moving, the walls were shaking and everything was crumbling. It was as if we had awakened all the Indian demons and they were unleashing all their fury upon us...";
			link.l1 = "Shiver me timbers!";
			link.l1.go = "story_4";
		break;
		
		case "story_4":
			dialog.text = "It is hard to believe, I know. But...";
			link.l1 = "I would have called you a liar half a year ago. But I've been living in the Caribbean long enough to know that I have no reason to mistrust you. Go on. How did you survive?";
			link.l1.go = "story_5";
		break;
		
		case "story_5":
			dialog.text = "We ran out of the temple and were lucky enough to get aboard our ship in time. I ordered the anchor to be raised; we wanted to sail away from that place as soon as possible.";
			link.l1 = "Heh! So, in the end, you only found some odd artefact instead of treasures? What a nice and equivalent replacement, he-he... And did you find out how to use it? Or was it useless?";
			link.l1.go = "story_6";
		break;
		
		case "story_6":
			dialog.text = "Wait a moment. The story isn't over yet. Dannie had the artefact and as soon as we decided to go to the cabin to study it, the sky went dark and a ship appeared. Oh God! It was...";
			link.l1 = "...";
			link.l1.go = "exit";
			pchar.questTemp.LSC.Natanstory = "blackpearl";
			AddDialogExitQuest("Video_story");
			NextDiag.TempNode = "story_7";
		break;
		
		// вот тут делаем развилку, в зависимости прошёл ли игрок Калеуче
		case "story_7":
			dialog.text = "... Van der Decken himself!!";
			if (CheckAttribute(pchar, "questTemp.KhaelRoa"))
			{
				link.l1 = "Van der Decken? Hm...";
				link.l1.go = "story_8_1";
			}
			else
			{
				link.l1 = "And who is he?";
				link.l1.go = "story_8";
			}
		break;
		
		case "story_8":
			dialog.text = "Haven't you ever heard of the Flying Dutchman?";
			link.l1 = "Who hasn't heard of the Flying Dutchman! I've already met one Dutchman and sent his captain to the bottom of the sea. He was just an ordinary pirate who decorated his ship with masquerade rubbish like algae and torn sails.";
			link.l1.go = "story_9";
		break;
		
		case "story_8_1":
			dialog.text = "Yes, but this was Van der Decken himself, the captain of the Flying Dutchman!";
			link.l1 = "Interesting. Please, go on. How did you manage to pull through?";
			link.l1.go = "story_11";
		break;
		
		case "story_9":
			dialog.text = "Eh-heh, friend... You sank some jester, but I'm talking about the real Flying Dutchman. A huge warship. God save you from ever meeting her on the open sea. Her captain, Van der Decken, and his crew were once cursed to sail the seas restlessly forever.\nI remember her tattered black sails, the crew of dead men standing on deck with their blades drawn, and the captain himself - a ghastly skeleton wearing a black cocked hat... Jesus...";
			link.l1 = "Are you telling the truth?";
			link.l1.go = "story_10";
		break;
		
		case "story_10":
			dialog.text = "I can swear on the Bible that I am not lying... A meeting with the 'Flying Dutchman' only means certain death. She's powerful, very powerful; one volley from her guns can sink even a heavy frigate and its crew... but even worse, how are you supposed to fight the undead?";
			link.l1 = "But you survived this nightmare!";
			link.l1.go = "story_11";
		break;
		
		case "story_11":
			dialog.text = "It is all thanks to my lovely Dannie and the Indian artefact that we took from the temple. I had ordered everyone to prepare to fight, but I knew it was the end of the line. The 'Flying Dutchman' was sailing towards us, and I could see her dreadful crew and Van der Decken himself on deck. The ship began to aim her cannons at us, but...";
			link.l1 = "...";
			link.l1.go = "exit";
			pchar.questTemp.LSC.Natanstory = "artefact";
			AddDialogExitQuest("Video_story");
			NextDiag.TempNode = "story_12";
		break;
		
		case "story_12":
			dialog.text = "Dannie raised the artifact and let it fly. I had no idea why she would do that. She said something about her female intuition... The artifact turned back into a glowing sphere and exploded, critically damaging the ghost ship and demoralising its crew. I gave the order to open fire on the Dutchman.\nThe first volley made them shudder. We attacked again and struck their rotten hull a second time, just before they could recover from the artifact's influence and began returning fire...";
			link.l1 = "So, you had to fight them anyway?";
			link.l1.go = "story_13";
		break;
		
		case "story_13":
			dialog.text = "Indeed. And I swear it was the toughest fight of my life. Their damn tub was barely staying afloat, yet they still managed to destroy half my hull before we sent them flying sky-high by blowing up their damn powder chamber.";
			link.l1 = "So did you sink it? Did you sink the Flying Dutchman?";
			link.l1.go = "story_14";
		break;
		
		case "story_14":
			dialog.text = "Yes, damn it! I did!..";
			link.l1 = "...";
			link.l1.go = "exit";
			pchar.questTemp.LSC.Natanstory = "ending";
			AddDialogExitQuest("Video_story");
			NextDiag.TempNode = "story_15";
		break;
		
		case "story_15":
			dialog.text = "That damned ship went down. The sun started shining again and the sky cleared. And we finally began to feel happy... oh, you can't even imagine how happy we were. We had cheated death itself. Moments like that bring people together. And we did what we should have done long before that encounter - we embraced, kissed, confessed our love for each other, and swore to stay together forever.";
			link.l1 = "And you are still together...";
			link.l1.go = "story_16";
		break;
		
		case "story_16":
			dialog.text = "Yes, we are. Dannie and I got married and I have never regretted it. You won't find a better wife or comrade-in-arms.";
			if (CheckAttribute(pchar, "questTemp.KhaelRoa"))
			{
				link.l1 = "So, now I finally know who that mysterious captain who managed to sink the 'Flying Dutchman' really is... You are a true hero!";
				link.l1.go = "story_17_1";
			}
			else
			{
				link.l1 = "So, you two are real heroes then? You managed to sink the famous ghost ship. Wait! You said that the 'Flying Dutchman' is still afloat... How can that be possible if she is lying at the bottom of the sea?";
				link.l1.go = "story_17";
			}
		break;
		
		case "story_17":
			dialog.text = "Eh, pal, you don't know a thing... You can sink Van der Decken, but you can't kill him. The curse upon him and his crew is too strong, much stronger than death...";
			link.l1 = "...";
			link.l1.go = "exit";
			pchar.questTemp.LSC.Natanstory = "VDDrepair";
			AddDialogExitQuest("Video_story");
			NextDiag.TempNode = "story_18";
		break;
		
		case "story_17_1":
			dialog.text = "A hero I might be, but Van der Decken cannot be killed. The curse hanging over him, his crew, and his ship is stronger than death...";
			link.l1 = "...";
			link.l1.go = "exit";
			pchar.questTemp.LSC.Natanstory = "VDDrepair";
			AddDialogExitQuest("Video_story");
			NextDiag.TempNode = "story_18";
		break;
		
		case "story_18":
			dialog.text = "Every time you sink the ship, her crew repair her, patch her up and continue their eternal voyage.";
			if (CheckAttribute(pchar, "questTemp.KhaelRoa"))
			{
				link.l1 = "I know, Nathaniel, I know. Still, the Flying Dutchman will trouble no one anymore.";
				link.l1.go = "story_22";
			}
			else
			{
				link.l1 = "Well, you know, this sounds like a fable. To repair a ship that's been broken up and scuttled...";
				link.l1.go = "story_19";
			}
		break;
		
		case "story_19":
			dialog.text = "People have seen the ship many times after we sank it... You decide whether to believe the sightings.";
			link.l1 = "And where is that island with the temple, the one where you found the artefact?";
			link.l1.go = "story_20";
		break;
		
		case "story_20":
			dialog.text = "It is uncharted and located somewhere in the east of the Caribbean Sea. I left a map of the island in Maroon Town but as you very well know I can't sail there now. And to be honest I don't want to. The only thing I remember is its name - Khael Roa...";
			link.l1 = "Such an interesting story. I would like to find that island!";
			link.l1.go = "story_21";
		break;
		
		case "story_21":
			dialog.text = "Oh, I wouldn't recommend that... I'm not going to pay it another visit, that's for sure.";
			link.l1 = "I'd like to visit it anyway... Fine, thank you for your fascinating story! Now I know more about your wife. You are both living legends!";
			link.l1.go = "diffindoor_19";
			DeleteAttribute(pchar, "questTemp.LSC.Natanstory");
			pchar.questTemp.NatanStory = "true";
		break;
		
		case "story_22":
			dialog.text = "What are you implying, mate? Didn't I just tell you he can't be killed?";
			link.l1 = "Nathaniel, I sailed to Khael Roa. And I visited the temple of the Chavins, where you, Danielle, and some old man had been a quarter of a century ago. The artefact you took from the temple back then was called the 'orb of the rising sun'. That artefact was what drew the attention of the 'Flying Dutchman' to you. Its captain was fond of Chavin artefacts.";
			link.l1.go = "story_23";
		break;
		
		case "story_23":
			dialog.text = "You have been to Khael Roa? But that just can't be! Are you telling me the truth?";
			link.l1 = "I swear. When you told me about the labyrinth and the statue of the giant bird, I immediately realised where that place was. The Caribbean shaman Tuttuathapak told me about your adventures. It was he who directed me to that island. It is located to the east of St. Christopher. It's very small, shaped like a ring. There are rocks all around it and a small cove inside. And there is just one overgrown path leading to a temple, which is built in the form of a pyramid.";
			link.l1.go = "story_24";
		break;
		
		case "story_24":
			dialog.text = "Yes! This is Khael Roa. But why did you go there?";
			link.l1 = "To lift the curse of the Caleuche... well, of the 'Flying Dutchman'. Actually, her name was 'Flying Heart', and her captain was 'Balthazar de Cordes'. Fifty years ago, he was cursed by Yum Cimil, an Indian God of Death. I took the jade skull of Yum Cimil, which had been stolen from the temple by Balthazar some time ago, and placed it back on the pedestal in front of that condor statue...";
			link.l1.go = "story_25";
		break;
		
		case "story_25":
			dialog.text = "";
			link.l1 = "...by returning the skull I lifted the curse of the Caleuche. And since I had two other Chavin amulets with me, she attacked me near the island, just like what happened to you back then. But without the curse, Balthazar was no longer immortal, just as Tuttuathapak said. So... the 'Flying Dutchman' is no more. I personally took care of her.";
			link.l1.go = "story_26";
		break;
		
		case "story_26":
			dialog.text = "Thunder and lightning! I am astounded! You... You're not kidding old Nathan, are you? No, I can see in your eyes that you are telling the truth! You're a real hero!";
			link.l1 = "A hero or not, but I've seen my fair share of adventures, just like you have. Well, I'm sure we'll talk about the past many more times, since now we have a common subject.";
			link.l1.go = "diffindoor_19";
			DeleteAttribute(pchar, "questTemp.LSC.Natanstory");
		break;
		
		case "diffindoor_19":
			dialog.text = "Are you going to leave me now, friend?";
			link.l1 = "Yes, Nathan. Please, hold on until my return. Take care. And most importantly, stay alive until I am back and everything will be all right. The Brethren of the Coast need you, Danielle needs you.";
			link.l1.go = "diffindoor_20";
		break;
		
		case "diffindoor_20":
			dialog.text = "Is Dannie in your crew now? I beg you, watch over her. She hasn't changed a bit since her youth, she is still a daredevil and will not hesitate to go through hell. Tell her that I love her very much...";
			link.l1 = "Of course I will. We'll come back for you together, I promise you that, Nathan. Hold on, and keep your head up. Ole will take care of you. See you soon!";
			link.l1.go = "diffindoor_21";
		break;
		
		case "diffindoor_21":
			DialogExit();
			LAi_SetGroundSitTypeNoGroup(npchar);
			NextDiag.CurrentNode = "diffindoor_wait";
			pchar.questTemp.LSC.NatanTalk = "true"; // атрибут - разговор с Натаном состоялся
			AddQuestRecord("BaronReturn", "10");
			npchar.greeting = "nathaniel_1";
		break;
		
		case "diffindoor_wait":
			dialog.text = "Ah, it's you, "+pchar.name+". Haven't left the island yet?";
			link.l1 = "Don't worry, Nathan, everything is going according to plan. Rest now.";
			link.l1.go = "exit";
			NextDiag.TempNode = "diffindoor_wait";
		break;
		
		case "danny":
			PlaySound("Voice\English\saga\Nataniel Hawk-03.wav");
			dialog.text = "Danielle!.. Dannie! My Dannie!..";
			link.l1 = "...";
			link.l1.go = "danny_1";
		break;
		
		case "danny_1": // перекидываем pchar
			DialogExit();
			LAi_SetActorType(pchar);
			SetMainCharacterIndex(GetCharacterIndex("Nathaniel"));
			PChar = GetMainCharacter();			
			LAi_SetPlayerType(PChar);
			sld = characterFromId("Danielle");
			sld.dialog.currentnode = "nathaniel_6";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
			NextDiag.CurrentNode = "danny_2";
		break;
		
		case "danny_2":
			dialog.text = "Thank you, my friend. Thank you for everything, and especially for my Dannie...";
			link.l1 = "You are welcome, Nathan.";
			link.l1.go = "exit";
			NextDiag.TempNode = "danny_2";
		break;
		
		// в Марун-Тауне
		case "marun_town":
			dialog.text = "Look who has just dropped in! It's "+GetFullName(pchar)+"  himself! Come in, come in, my friend! How are you?";
			link.l1 = "I am fine. And you, Nathan? I see there is no gloom left. You are looking well. Snake Eye has done really well!";
			link.l1.go = "marun_town_1";
		break;
		
		case "marun_town_1":
			ChangeCharacterComplexReputation(pchar, "fame", 3);
			dialog.text = "Yes, your shaman is a miracle-worker. I feel even better than I did before that damn teleportation! I feel as if I am ten years younger! "+pchar.name+", I owe you a great deal. And I am impressed: you helped a complete stranger, went through the cursed portal, snatched me from death's hands, and brought me back to my wife!\nAnd even more! You have returned our ship and home to us. You are now our dearest friend. Forever. If you ever need anything - you know who to ask! Maroon Town will always offer you protection, support, and sanctuary should you require it.\nThe whole village will fight for you if you are in danger. In peaceful times, you will find friendship here, the finest rum, a soft bed, and a good place to rest. Dannie and I will make sure of it.";
			link.l1 = "Thank you, Baron! I am sincerely glad to see you in good health and... with Dannie.";
			link.l1.go = "marun_town_2";
		break;
		
		case "marun_town_2":
			dialog.text = "I've been expecting your visit, "+pchar.name+", and I have prepared a gift - a rare and powerful weapon. Perhaps, one day you will need to take down numerous enemies in a single shot, and this hand mortar will help you do just that. The 'Sclopetta' fires special grenades, so I've also prepared instructions on how to make them. Here, take it.";
			link.l1 = "What an excellent weapon! Thank you!";
			link.l1.go = "marun_town_3";
		break;
		
		case "marun_town_3":
			GiveItem2Character(pchar, "grape_mushket"); 
			GiveItem2Character(pchar, "recipe_grenade"); 
			Log_Info("You have received a hand mortar");
			Log_Info("You have received a grenade instruction");
			PlaySound("interface\important_item.wav");
			dialog.text = "Come and see us more often, "+pchar.name+"! Dannie and I will always be glad to see you at any time.";
			link.l1 = "It will be a pleasure. Expect to see me soon!";
			link.l1.go = "exit";
			NextDiag.TempNode = "marun_town_4";
		break;
		
		case "marun_town_4":
			dialog.text = "Ah, my friend "+GetFullName(pchar)+"! Come in, come in, Captain! How are you? Do you need any help?";
			// калеуче
			if (CheckAttribute(pchar, "questTemp.Caleuche.NatanInfo"))
			{
				link.l2 = "Nathan, I've come to you on very important business. Do you remember when you told me on the Island of Abandoned Ships that you and Dannie sneaked into an Indian temple and sank the 'Flying Dutchman'?";
				link.l2.go = "caleuche";
			}
			link.l1 = "Thanks, I'm fine. Just wanted to see you both.";
			link.l1.go = "exit";
			NextDiag.TempNode = "marun_town_4";
		break;
		
		case "caleuche":
			dialog.text = "Of course, I do.";
			link.l1 = "I need to get to that island with the temple. I need to find it desperately. You said you had a map of it. Can you tell me the coordinates?";
			link.l1.go = "caleuche_1";
		break;
		
		case "caleuche_1":
			dialog.text = "Oh, friend, this is a very dangerous undertaking, you know... the temple of Khael Roa is cursed. If you only knew who dwells in its corridors...";
			link.l1 = "At the moment, it is inhabited by monsters far more terrifying than those you saw back then. And yet I will still go there.";
			link.l1.go = "caleuche_2";
		break;
		
		case "caleuche_2":
			dialog.text = "I will never forgive myself if you perish there. "+pchar.name+", I beg you: abandon this venture! Besides, it's where the 'Flying Dutchman' is most often seen...";
			link.l1 = "I have already encountered it, and I know how to outrun it. Nathan, please, give me the coordinates of Khael Roa and tell me everything you know about that temple, apart from the fact that it's inhabited by undead Indians.";
			link.l1.go = "caleuche_3";
		break;
		
		case "caleuche_3":
			dialog.text = "Oh well... I cannot turn you down, but... you have no idea what Dannie and I experienced there! Khael Roa is located east of Antigua. I found its map right when I got back to Maroon Town, it's at... (looking) the coordinates: 19 degrees 32' North, 62 degrees 25' West.";
			link.l1 = "I'll write its location down in my journal... Thank you, Nathan!";
			link.l1.go = "caleuche_4";
		break;
		
		case "caleuche_4":
			dialog.text = "You can thank me later. Now the details. The island of Khael Roa is a ring of rocks with a cove inside. Seek for the passage between the crags - it's fairly deep there. In the cove, you should cast anchor and disembark at the beach. Look for an old path heading deeper into the island - there's only one there. It will lead you to an Indian pyramid - this is the temple you seek.\nThe island itself is quiet, but the temple is crawling with abominations of all sorts. The entrance is located at the top of the pyramid. There will be three passages inside; you should take the middle one. Then you walk down the corridor and you will find a platform with four entrances or exits. This is where the temple creatures attacked me for the first time, so you should be careful.\nThen there is a labyrinth. It's very complex, and I, for the life of me, can't remember the right route. There is a multitude of foul creatures in the labyrinth. You must kill them all, then walk up to a hall with two entrances, six columns and a platform with nine stone slabs. This is the vestibule of the sanctuary. Its stone wall is closed, and I have no idea how you're going to open it.\nThere is some kind of mechanism, but I swear to God that I have no clue how it functions! I used an idol as a key. I inserted it into the central slab, and the door opened. But you don't have such an idol, so you'll have to figure out how this mechanism functions.";
			link.l1 = "Alright, I'll do my best to figure it out. What about the sanctuary?";
			link.l1.go = "caleuche_5";
		break;
		
		case "caleuche_5":
			dialog.text = "The sanctuary is a vast hall with a very high ceiling and large stone stairs. You cannot use them – they are mostly too old and have collapsed. But the builders of the temple, it seems, were also great sorcerers. There are portals, like those of Kukulcan, and they will take you from one place to another.\nYou will recognise them easily – they look like coloured swirls. There will be two portals on the first floor, but one of them is a trap, so be careful! The correct portal will take you to the second floor. There you must find another portal to go even higher, and then straight to the heart of the temple!\nThere, at the great statue of the bird, was placed that magical artefact which Dannie and I had taken with us. And I have already told you what happened next.";
			link.l1 = "I will remember what you have just told me. Thank you, Nathaniel. You have helped me greatly.";
			link.l1.go = "caleuche_6";
		break;
		
		case "caleuche_6":
			dialog.text = "Take care, "+pchar.name+". The labyrinth and the temple halls are full of dangers. Just one wrong move and you're sure to stay in there forever.";
			link.l1 = "Praemonitus praemunitus, friend. I was forewarned, that means I am forearmed. I have to go now. See you!";
			link.l1.go = "caleuche_7";
		break;
		
		case "caleuche_7":
			dialog.text = "Good luck, "+pchar.name+"!";
			link.l1 = "Thanks!";
			link.l1.go = "caleuche_8";
		break;
		
		case "caleuche_8":
			DialogExit();
			DeleteAttribute(pchar, "questTemp.NatanStory");
			DeleteAttribute(pchar, "questTemp.Caleuche.NatanInfo");
			AddQuestRecord("Caleuche", "35");
			NextDiag.CurrentNode = "marun_town_4";
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}
