// НПС по квесту Суп из черепахи
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	int i;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			dialog.text = "What do you need?";
			link.l1 = "No, nothing.";
			link.l1.go = "exit";			
			NextDiag.TempNode = "First time";
		break;
		
		// денщик Фокса - Бенджамин Джонс
		case "BenjaminJons":
			if (CheckAttribute(PChar, "questTemp.Terrapin.Benjamin") && pchar.questTemp.Terrapin == "baster")
			{
				dialog.text = "The lord colonel is out in the field on a military exercise at the moment. What do you want from him, captain?";
				link.l1 = "This time, Ben, it's you I need. I have bad news about your sister Molly. That beautiful girl is apparently in some trouble. She's been captured by the pirates of Tortuga. She needs help and has asked me to warn you. The man who took it upon himself to deliver the message was killed, but before his death, he managed to tell me about your sister.";
				link.l1.go = "sister";
				break;
			}
			sld = characterFromId("Fox");
			if (sld.location == pchar.location)
			{
				dialog.text = "If you're on your way to Colonel Fox, then turn around and walk away. He's not receiving guests.";
				link.l1 = "Very well then.";
				link.l1.go = "exit";
			}
			else
			{
				dialog.text = "The colonel is not here. Come by later.";
				link.l1 = "All right...";
				link.l1.go = "exit";
			}
			NextDiag.TempNode = "BenjaminJons";
		break;
		
		case "sister":
			dialog.text = "Ha! You are the very first man who ever called my sister 'beautiful'. God gave her the body of a grenadier and the horn of Jericho instead of a voice. Our Molly can fight for herself But our Lord's creativity didn't just stop at everything below her chin. No, no, the finest thing He did was to stick the hairy, pockmarked face of our deceased father above her breasts. And I must say, sir, my old man's face used to make horses fall down in a faint.";
			link.l1 = "I see you're not particularly upset...";
			link.l1.go = "sister_1";
		break;
		
		case "sister_1":
			dialog.text = "And why would she show up in Tortuga? Molly is a servant of Catherine Fox, the daughter of our brave colonel. Catherine was coming from Europe to visit her father on his birthday. But the squadron her ship was sailing with has been delayed\nIf you want to see the real Molly Jones and her mistress, who is very beautiful by the way, come here in a month. Not a day earlier.";
			link.l1 = "It turns out that your sister Molly Jones has been serving Ms Fox and at the present moment resides on the other side of the Atlantic?";
			link.l1.go = "sister_2";
		break;
		
		case "sister_2":
			dialog.text = "Exactly so! The last courier informed us that a navy squadron dispatched by Lord Protector Cromwell himself was supposed to leave London only a month ago. The brig 'Albatross', with Catherine aboard, was to accompany them. We shall learn if this is truly the case from the next mail packet boat. Although the ships haven't arrived yet, and the colonel had strictly forbidden the 'Albatross' to sail alone.\nDid you know that his beloved wife died during an attack by French corsairs? It was not easy for the colonel, and he still dreads the dangers of the high seas... So I can't help you with Molly Jones, captain! There are a lot of colonist girls named Molly! Besides, having the surname Jones in Britain is as good as having no surname at all!\nEvery sea dog at Antigua knows me and my commander. I'm not surprised that some poor girl who got into trouble wants my help. I'd like to, but I haven't the coin for a ransom. The colonel owes me three months' wages; my salary, along with everyone else's, arrives with the 'Albatross'.";
			link.l1 = "Apparently I was mistaken then. But thanks anyway for the clarification.";
			link.l1.go = "sister_3";
		break;
		
		case "sister_3":
			dialog.text = "Not at all, captain.";
			link.l1 = "...";
			link.l1.go = "sister_4";
		break;
		
		case "sister_4":
			DialogExit();
			AddQuestRecord("Terrapin", "3");
			pchar.questTemp.Terrapin.Catherina = "take"; // возможен вариант с Кати
			DeleteAttribute(pchar, "questTemp.Terrapin.Benjamin");
		break;
		
		// Робер Мартэн
		case "Rober":
			PlaySound("Voice\English\sharlie\Rober Marten-01.wav");
			dialog.text = "What do you want?! I don't want to talk.";
			if (CheckAttribute(PChar, "questTemp.Terrapin") && pchar.questTemp.Terrapin == "rober")
			{
				link.l1 = "I've got some business for you, captain. I see you're not in a cheerful mood, so perhaps my proposition will lift your spirits a little.";
				link.l1.go = "rober_1";
			}
			else
			{
				link.l1 = "Quiet down, have some rum. My mistake, sorry.";
				link.l1.go = "exit";
			}
			NextDiag.TempNode = "Rober";
		break;
		
		case "rober_1":
			DelMapQuestMarkCity("BasTer");
			pchar.quest.Terrapin_LateBaster.over = "yes"; //снять таймер
			dialog.text = "The sound of it is quite appealing! And your face looks like I've seen it somewhere before... I just can't remember where I saw you. Go on, tell me!";
			link.l1 = "I'm aware of your business with Thibaut... Relax, mate! You don't have to fear me. I've got a deal to propose to you.";
			link.l1.go = "rober_2";
		break;
		
		case "rober_2":
			dialog.text = "Damn it to hell! Damn that drunken swine!... I didn't manage to...";
			link.l1 = "You've got that right. Your sailor had a big mouth, but his rumours haven't gone anywhere beyond me. And those rumours won't get any further, since you're the one who has taken care of it, haven't you?";
			link.l1.go = "rober_3";
		break;
		
		case "rober_3":
			dialog.text = "Caramba! I recognise you now! You're the man who made a hash of Colonel Doiley and took his whole island! You were involved in some big business with the Dutch West India Company, you're rubbing elbows with a West Main baron.... Your name is... "+GetFullName(pchar)+", right?";
			link.l1 = "You have some accurate information. Yes, it's me. But could you calm down for a moment, Robert?";
			link.l1.go = "rober_4";
		break;
		
		case "rober_4":
			PlaySound("Voice\English\sharlie\Rober Marten-02.wav");
			dialog.text = "Argh! Well, how can I calm down when one of the most famous sea dogs in the archipelago has taken an interest in me, and not only that, he's found out about my business too! What the hell got into me to attack that brig! What do you want from me?";
			link.l1 = "Shut your mouth and listen to me. It seems to me that we both want Levasseur's head on a plate. That pompous braggart has grown too big for his breeches and angered some serious people. I intend to alter the balance of power on the island and put de Poincy in his place, but I don't want to spill any more blood of men from my homeland, especially over some filthy thief. You can help me. And I can help you and Thibaut keep your privileges.";
			link.l1.go = "rober_5";
		break;
		
		case "rober_5":
			dialog.text = "Wait, wait! I cannot believe my ears! Fortuna smiles on me today. You are right, we share the same goals. With you, things could get much more interesting... Thibaut is a good fencer, but he doesn't have the guts to cut his uncle's throat... But a cunning shark like you could do it. Your fame is well known\nI don't need your guarantees, but I will help you in return for the girl. I need her as my hostage until I finish my business in the Caribbean. Soon, English frigates will start hounding me. What the devil possessed me to attack that brig! It looked like such easy prey, separated from the squadron...";
			link.l1 = "What was so special about her? The girl you were hiding from Levasseur?";
			link.l1.go = "rober_6";
		break;
		
		case "rober_6":
			dialog.text = "Yes. You must convince Thibaut to part ways with the girl. I asked him to look after her while I found out who the devil she was, but this 'Miss Jones', or whatever her name is, has completely turned his head and now Henry is even hiding her from me! Bring that bewitching siren to me and I'll arrange a meeting for you with Levasseur outside of town. At that point, you'll have an opportunity to ambush him. I'll be waiting at Fisheye Beach.";
			link.l1 = "Deal. Now tell me how to catch Thibaut.";
			link.l1.go = "rober_7";
		break;
		
		case "rober_7":
			dialog.text = "Folks at the tavern can show you the way to his house. Henri is quite a noteworthy fellow. Threaten him with exposure and make him bring the girl to me. That same day I will let Levasseur know that his nephew is hiding a rare beauty in the city dungeon\nMy courier will find you in the tavern. After he fails to find Henri, the governor will go to the dungeon with a small squad and you will have a nice opportunity to chat with him.";
			link.l1 = "Where should I deliver the girl?";
			link.l1.go = "rober_8";
		break;
		
		case "rober_8":
			dialog.text = "Tell him to bring her to the beach himself. I'll have a word or two with him while I'm at it...";
			link.l1 = "All right. Consider it a deal. See you on Tortuga!";
			link.l1.go = "rober_9";
		break;
		
		case "rober_9":
			dialog.text = "If everything goes as planned, we'll never see each other again. I hope so, at least. Farewell!";
			link.l1 = "...";
			link.l1.go = "rober_10";
		break;
		
		case "rober_10":
			chrDisableReloadToLocation = true;//закрыть локацию
			DialogExit();
			LAi_SetActorType(npchar);
			ChangeCharacterAddressGroup(npchar, "Baster_tavern", "goto", "goto2");
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "OpenTheDoors", -1);
			if(CheckAttribute(pchar, "questTemp.Terrapin.Catherina")) AddQuestRecord("Terrapin", "6");
			else AddQuestRecord("Terrapin", "5");
			pchar.questTemp.Terrapin = "tortuga";
			// создаем Тибо
			float fMft = MOD_SKILL_ENEMY_RATE/10;
			sld = GetCharacter(NPC_GenerateCharacter("Tibo", "Tibo", "man", "man", 35, FRANCE, -1, true, "quest"));
			FantomMakeCoolFighter(sld, 35, 100, 100, "blade_18", "pistol4", "bullet", 250);
			GiveItem2Character(sld, "cirass7");
			EquipCharacterbyItem(sld, "cirass7");
			sld.name = "Henry";
			sld.lastname = "Thibaut";
			sld.dialog.FileName = "Quest\Sharlie\Terrapin.c";
			sld.dialog.currentnode = "tibo";
			sld.greeting = "Tibo";
			sld.SaveItemsForDead = true;
			sld.DontClearDead = true;
			TakeNItems(sld, "potion2", 8);
			TakeNItems(sld, "potion3", 5);
			SetCharacterPerk(sld, "Energaiser");
			SetCharacterPerk(sld, "BasicDefense");
			SetCharacterPerk(sld, "BasicDefense");
			SetCharacterPerk(sld, "AdvancedDefense");
			SetCharacterPerk(sld, "CriticalHit");
			SetCharacterPerk(sld, "Tireless");
			SetCharacterPerk(sld, "HardHitter");
			SetCharacterPerk(sld, "Sliding");
			SetCharacterPerk(sld, "BladeDancer");
		
			SetCharacterPerk(sld, "Gunman");
			SetCharacterPerk(sld, "GunProfessional");
			sld.MultiFighter = 1.0+fMft; // мультифайтер
			if(bImCasual)
			{
				NewGameTip("Exploration mode: quest duration doubled");
				SetFunctionTimerCondition("Terrapin_LateTortuga", 0, 0, 40, false); // таймер
			}
			else SetFunctionTimerCondition("Terrapin_LateTortuga", 0, 0, 20, false); // таймер
			SetFunctionLocationCondition("Tonzag_AtTortuga", "Tortuga_town", false);
		break;
		
		case "rober_abordage":
			dialog.text = "Argh! I didn't see it coming... You've come for my soul, haven't you? I did everything as agreed! What the hell?!";
			link.l1 = "You have a sentence upon you, Robert. The sentence was given to me to carry out. So I'm fulfilling my assignment.";
			link.l1.go = "rober_abordage_1";
		break;
		
		case "rober_abordage_1":
			dialog.text = "You devil! This is impossible! He couldn't have found everything out so quickly! And how did he even find it out?!";
			link.l1 = "You mean Fox? No. He didn't send me. The colonel still doesn't even know you cut his daughter down. Your old mate Henry Thibaut is the one who wants you dead. He hired me.";
			link.l1.go = "rober_abordage_2";
		break;
		
		case "rober_abordage_2":
			dialog.text = "That goddamn catamite! I should have fed him to the crabs while he was on the 'Voltigeur'... How much did that bastard promise you?";
			link.l1 = "It's not every day that a man gets to learn the price on his head, is it Robert? Thibaut priced you at a quarter million, but I convinced him that you were worth more. You're worth three hundred thousand silver pesos, my friend. Aren't you glad?";
			link.l1.go = "rober_abordage_3";
		break;
		
		case "rober_abordage_3":
			dialog.text = "Wait a second... Let's make a deal! I'll pay you more!";
			link.l1 = "With what money, Robert? I'm absolutely sure you're lying. You don't have as much money as Henry promised me. And that's not the main thing anyway. If it weren't for one fact, I would have refused his proposition to hunt you down and end your dirty business with Thibaut.";
			link.l1.go = "rober_abordage_4";
		break;
		
		case "rober_abordage_4":
			dialog.text = "What fact is that?";
			link.l1 = "You killed Catherine Fox. That poor girl's only guilt was being born Colonel Fox's daughter. I hate contemptible cowards like you who put defenceless women to death! I'm not making any deal with you. I won't even consider it. Don't waste your breath.";
			link.l1.go = "rober_abordage_5";
		break;
		
		case "rober_abordage_5":
			PlaySound("Voice\English\sharlie\Rober Marten-03.wav");
			dialog.text = "Fuck! What else could I do?! I couldn't let her live and hide her away endlessly on the boat! And who are you... you rascal, you bastard, you assassin, to lecture me about morals! Take a look at yourself! At your 'methods'! You're no better than me!";
			link.l1 = "Enough. Martene, draw your blade! It's time we finished this.";
			link.l1.go = "rober_abordage_6";
		break;
		
		case "rober_abordage_6":
			dialog.text = "I'll see you in hell!";
			link.l1 = "...";
			link.l1.go = "rober_abordage_7";
		break;
		
		case "rober_abordage_7":
			DialogExit();
			QuestAboardCabinDialogFree();
			LAi_group_SetRelation(LAI_GROUP_BRDENEMY, LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups(LAI_GROUP_BRDENEMY, LAI_GROUP_PLAYER, true);
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		
		// Тибо, вариант без Кати
		case "tibo":
			pchar.quest.Terrapin_LateTortuga.over = "yes"; //снять таймер
			PlaySound("Voice\English\sharlie\Henry Thibault-02.wav");
			dialog.text = "What are you doing in my home, sir?";
			link.l1 = TimeGreeting()+", Monsieur Thibaut. I am here on behalf of a man you know, Captain Robert Martene.";
			link.l1.go = "tibo_1";
		break;
		
		case "tibo_1":
			dialog.text = "Hm. And? So?";
			link.l1 = "Captain Martene requests the pleasure of your company right now on Fisheye Beach. But not alone. He would also appreciate seeing Molly Jones with you. Do you understand what I mean?";
			link.l1.go = "tibo_2";
		break;
		
		case "tibo_2":
			PlaySound("Voice\English\sharlie\Henry Thibault-01.wav");
			dialog.text = "Alas, sir, I don't. I've never heard of any Molly Jones, and Robert has never had any reason to send a... plenipotentiary to me whom I've never seen before. For your information, monsieur, I am the second man on this island after my uncle, the governor, so...";
			link.l1 = "Life is an unpredictable beast, Henry... Right now you are the second man on the island, and in a couple of hours you could be in shackles in the casemates... All for the life of someone who wouldn't give you a single peso. You have disobeyed your uncle's order, haven't you, monsieur Thibaut? What's more important to you: a wanton girl or your life?";
			link.l1.go = "tibo_3";
		break;
		
		case "tibo_3":
			dialog.text = "Why you... You're lying! You're talking through your hat!";
			link.l1 = "You, just like anyone else, must know how fiery your uncle's temper can be. Levasseur will find out that you are hiding the girl before the sun sets. Don't ask me how Robert found that out, just heed my words: he's scared to death and ready to weigh anchor at once. He didn't even dare to enter the town and paid me a hefty sum to deliver this message to you instead.";
			link.l1.go = "tibo_4";
		break;
		
		case "tibo_4":
			dialog.text = "Damn... It can't be!";
			link.l1 = "It's up to you, sir. Martene will not wait for you any longer than two hours. He values the head on his own shoulders. It's only as a sign of his friendship that he's still lingering on the Tortuga shore and not hiding somewhere with the Dutch.";
			link.l1.go = "tibo_5";
		break;
		
		case "tibo_5":
			dialog.text = "Caramba! How did my uncle find that out?";
			link.l1 = "Tongues, Henry. Wagging tongues. Even I know that you and Robert nabbed the beauty that came off the English brig seized by your mate. Hid her from Levasseur...tsk tsk. Do you really doubt that I'm the only one informed about this story?";
			link.l1.go = "tibo_6";
		break;
		
		case "tibo_6":
			dialog.text = "Looks like you're telling the truth, sir. Tell Martene...";
			link.l1 = "I don't think you understand, Henry. Martene isn't going to wait for you. Your only hope is to get that girl out of here, the reason both you and Robert have nooses around your necks. Run over there where you're hiding her, take her by her pretty little hands, and bring her over to the Voltigeur. Find her quickly, and bring her even faster. Your uncle won't hear a word of it from me.";
			link.l1.go = "tibo_7";
		break;
		
		case "tibo_7":
			dialog.text = "All right. We'll do that then. Thank you for your kindness, sir!";
			link.l1 = "No need to thank me, monsieur. My work is paid for... I just want you to get out of the soup before you're cooked.";
			link.l1.go = "tibo_8";
		break;
		
		case "tibo_8":
			chrDisableReloadToLocation = true;//закрыть локацию
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1", "none", "", "", "OpenTheDoors", -1);
			pchar.quest.Terrapin_wait.win_condition.l1 = "Timer";
			pchar.quest.Terrapin_wait.win_condition.l1.date.hour  = sti(GetTime()+3);
			pchar.quest.Terrapin_wait.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 0);
			pchar.quest.Terrapin_wait.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 0);
			pchar.quest.Terrapin_wait.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 0);
			pchar.quest.Terrapin_wait.win_condition.l2 = "location";
			pchar.quest.Terrapin_wait.win_condition.l2.location = "Tortuga_tavern";
			pchar.quest.Terrapin_wait.function = "Terrapin_SetEnvoy";
			pchar.questTemp.Terrapin = "cave";
			AddQuestRecord("Terrapin", "8");
			SetFunctionTimerCondition("Terrapin_ReturnTibo", 0, 0, 10, false);
			if(bImCasual)
			{
				NewGameTip("Exploration mode: quest duration doubled");
				SetFunctionTimerCondition("Terrapin_LateDungeon", 0, 0, 4, false);
			} 
			else SetFunctionTimerCondition("Terrapin_LateDungeon", 0, 0, 2, false);
		break;
		
		// вариант с Кати
		case "tibo_9":
			pchar.quest.Terrapin_LateTortuga.over = "yes"; //снять таймер
			PlaySound("Voice\English\sharlie\Henry Thibault-02.wav");
			dialog.text = "What are you doing here, sir? I didn't invite you here.";
			link.l1 = TimeGreeting()+", Monsieur Thibaut. I have come on behalf of a man you know. His name is Captain Robert Martene.";
			link.l1.go = "tibo_10";
		break;
		
		case "tibo_10":
			dialog.text = "Hm. And? So?";
			link.l1 = "Captain Martene requests the pleasure of your company right now on Fisheye Beach. But not alone. He would also appreciate seeing Molly Jones accompany you. Do you understand what I mean?";
			link.l1.go = "tibo_11";
		break;
		
		case "tibo_11":
			dialog.text = "Alas, sir, I don't.";
			link.l1 = "That's what I was expecting you to say. Of course, I doubt you could have previously been introduced to Colonel Fox's daughter; you know Colonel Fox, of course, commander of the notorious Sea Foxes... the terror of England's enemies in the Caribbean? You and Robert have stirred up such a hornet's nest it's a miracle you haven't been stung yet! The girl Molly Jones that you captured from the English brig, that you've been concealing from Levasseur, is the daughter of Colonel Fox, Catherine Fox!";
			link.l1.go = "tibo_12";
		break;
		
		case "tibo_12":
			dialog.text = "W-what?";
			link.l1 = "You've turned quite pale, sir. Now listen to me closely, Henry, and pay attention: you and your mate Robert are up to your necks in trouble. Any day now, Cromwell's naval squadron will arrive in the Caribbean. They'll be hunting you. Its flagship alone is capable of turning your vaunted La Roche and crew to splinters and mincemeat in a couple of hours. What do you think? Was the attack on that English brig and the captivity of Fox's daughter worth it?";
			link.l1.go = "tibo_13";
		break;
		
		case "tibo_13":
			dialog.text = "";
			link.l1 = "But that's not all. Your schemes have become known not only to me. Your dear uncle, the governor, will find out that you're defying his strict orders and concealed a girl from him that the old lecher would certainly have wanted to take for himself. What do you think, Henry? What will your uncle do to you? You must know better than anyone how fiery his temper is...";
			link.l1.go = "tibo_14";
		break;
		
		case "tibo_14":
			dialog.text = "All lies!";
			link.l1 = "Is it? My dear Henry, you can ask your friend Martene. He was the one who sent me. Levasseur will find out that you are hiding the girl before the sun sets. Don't ask me how Robert found that out, just heed my words: he's scared witless and ready to weigh anchor and cast off at once. He didn't even dare come into the town. That's why he asked me to deliver this message to you.";
			link.l1.go = "tibo_15";
		break;
		
		case "tibo_15":
			dialog.text = "";
			link.l1 = "Martene will not wait for you any longer than two hours. He values the head on his own shoulders. It's only as a sign of your friendship that he's still lingering on the Tortuga shore and not hiding somewhere with the Dutch. However, that poor fellow Robert doesn't even suspect who Molly Jones really is. You know, you two truly amaze me with your remarkable ignorance of women's fashion and appearance! You couldn't even distinguish a noblewoman from her servant!";
			link.l1.go = "tibo_16";
		break;
		
		case "tibo_16":
			dialog.text = "What do you want?";
			link.l1 = "Finally, some wise words from the young upstart! All right, Thibaut: make your way over to where you're hiding her right now, take her gently by her lily-white hands, and walk quickly with her down to Fisheye Beach where Martene's Voltigeur is. Tell him your plans have changed...";
			link.l1.go = "tibo_17";
		break;
		
		case "tibo_17":
			dialog.text = "";
			link.l1 = "Martene must fulfil his promise to me, he shouldn't even try to take the girl onto his own ship. She will stay on the beach and wait for me. Tell Robert that if he doesn't fulfil his obligations, or takes away Catherine, or if one hair falls from her pretty little head, I will spend the rest of my life searching for her. And when I find her, I will deliver her to Colonel Fox... alive. But as for you two... I'll bring you back in pieces. Yes, by the way, that includes you as well, Thibaut.";
			link.l1.go = "tibo_18";
		break;
		
		case "tibo_18":
			dialog.text = "";
			link.l1 = "Who I am and what my opportunities are, you can ask Robert about. He's well aware. If you both do as I say, then we all win. Robert will be able to continue his pirate business and you will keep all your privileges and receive your dear old uncle's inheritance when he croaks his last. As for me... I won't come out a loser either. Is that all clear?";
			link.l1.go = "tibo_19";
		break;
		
		case "tibo_19":
			PlaySound("Voice\English\sharlie\Henry Thibault-03.wav");
			dialog.text = "I'd rather burn in eternal hellfire than do your bidding... "+GetFullName(pchar)+"! How did I not recognise you from the start? You butcher! You're not planning to leave me or Robert alive! Your 'methods' are well known! There's no way I'm giving up Molly... or Catherine, for that matter, to filth like you! You won't leave Tortuga alive, bastard!";
			link.l1 = "...";
			link.l1.go = "tibo_20";
		break;
		
		case "tibo_20":
			dialog.text = "";
			link.l1 = "Stop, coward!";
			link.l1.go = "tibo_21"; // patch
		break;
		
		case "tibo_21":
			chrDisableReloadToLocation = true;//закрыть локацию
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload_window", "none", "", "", "Terrapin_LevasserRoomEnter", 5); // patch
			LAi_SetActorType(pchar);
			LAi_ActorTurnToLocator(pchar, "reload", "reload_window");
			LAi_RemoveLoginTime(npchar);
		break;
		
		case "tibo_22":
			pchar.quest.Terrapin_TiboCallOver.over = "yes"; //снять прерывание
			pchar.quest.Terrapin_tibo_call.over = "yes"; //снять прерывание
			PlaySound("Voice\English\sharlie\Henry Thibault-04.wav");
			dialog.text = "Well, finally! Captain "+GetFullName(pchar)+", I'm very pleased you've come. Come in, have a seat. Would you like something to drink? I've got quite a lucrative business proposition for you, my friend...";
			link.l1 = "Well, aren't you in the most courteous of moods today, Monsieur Thibaut... Let's not sit around. Let's get right to the crux of the matter.";
			link.l1.go = "tibo_23";
		break;
		
		case "tibo_23":
			dialog.text = "The proposition concerns my former friend and companion whom you know as Robert Martene, former captain of the galleon 'Voltigeur'...";
			link.l1 = "So, you and Robert are no longer friends? A fascinating development.";
			link.l1.go = "tibo_24";
		break;
		
		case "tibo_24":
			dialog.text = "Captain, please, hear my reasons for seeking your assistance and it will all become clear. As you know, Martene grappled with an English brig and captured as a prisoner an Englishwoman, a servant named Molly Jones, the whole reason why all this trouble ended up being stirred.";
			link.l1 = "Of course, I know. As I understand it, you have followed my recommendations and brought the girl to Martene's ship?";
			link.l1.go = "tibo_25";
		break;
		
		case "tibo_25":
			dialog.text = "Yes, I did it. But I regret it every day. I'll have you know that Molly is a very charming and beautiful girl, I have never met anyone like her before. I must admit, I fell in love with her. She liked me too, she said so herself! I couldn't let my uncle take her\nWhen I was escorting her to the 'Voltigeur' I hoped that my uncle would settle down as soon as he found out that no one was hiding girls from him, the old lecher. Then Robert would take her back to Tortuga, so I could safely move her to my place. Anyway, that was the deal I made with Martene. But it turned out differently\nWhen I learnt that my uncle had been killed, there was no point in hiding Molly away, so I waited patiently for 'Voltigeur' to arrive with Molly aboard.";
			link.l1 = "Did she arrive?";
			link.l1.go = "tibo_26";
		break;
		
		case "tibo_26":
			dialog.text = "Yes. Unfortunately, Molly wasn't on the ship. Robert was shaken, as if he'd butted heads with Lucifer himself. During his short-lived expedition, he somehow discovered one terrible detail: the girl, Molly, was not Molly Jones at all, but Catherine Fox! Colonel Fox's own daughter, commander of the Sea Foxes, the elite English marine regiment! You know what that means!";
			link.l1 = "Damn my eyes, how about that! Undoubtedly, then, Robert has something to be afraid of. But how could it have turned out that way?";
			link.l1.go = "tibo_27";
		break;
		
		case "tibo_27":
			dialog.text = "When Catherine was taken captive, she deliberately concealed her identity, pretending to be Molly Jones, a servant girl who died during the boarding. She was afraid that Martene would discover who she really was. And she managed to deceive him. But during the last voyage, Robert somehow found out the truth about her. He said he had found some of her letters, or papers...";
			link.l1 = "And where is the girl now if she didn't board the 'Voltigeur'?";
			link.l1.go = "tibo_28";
		break;
		
		case "tibo_28":
			dialog.text = "She's dead. Frightened by the imminent punishment from Fox for attacking the English brig, Martene decided to hide the only remaining evidence in the water. She was the last witness to his attack on the 'Albatross'.";
			link.l1 = "Then he might as well have murdered all his sailors... Like Fernand Luc. Otherwise, they'll get drunk one day and let their tongues wag a little too much at the tavern...";
			link.l1.go = "tibo_29";
		break;
		
		case "tibo_29":
			dialog.text = "He believes his entire crew is bound to him by blood. Perhaps he's partly right. But I know Colonel Fox! He'll keep searching until his dying day to discover who kidnapped his daughter!";
			link.l1 = "I don't doubt that. Especially after a French pirate killed his wife. Now his daughter too... By the way, are you absolutely sure, monsieur, that Catherine is truly dead? Perhaps Robert has hidden her from you somewhere.";
			link.l1.go = "tibo_30";
		break;
		
		case "tibo_30":
			dialog.text = "I'm sure. I spoke with a sailor from the 'Voltigeur'. I believed him. He saw with his own eyes how they slit the girl's throat, then tied a cannonball to her feet and threw her overboard.";
			link.l1 = "God in heaven! That poor woman... what do you want from me, Henry?";
			link.l1.go = "tibo_31";
		break;
		
		case "tibo_31":
			dialog.text = "I haven't been able to sleep at night since that day. I see Molly before my eyes all the time... Catherine, rather. I led her to her death, "+GetFullName(pchar)+"! I can't forgive myself for that. On top of that, I don't entertain any illusions about Fox. That man is not complacent and I don't think he even sleeps. Sooner or later, he'll get on Martene's trail, make somebody talk, and when he finds out who killed his daughter, all hell's going to break loose. It'll go hard on anybody who was in any way connected to the whole story.";
			link.l1 = "That includes me.";
			link.l1.go = "tibo_32";
		break;
		
		case "tibo_32":
			dialog.text = "Aye, me as well. That is why I want you to find Martene before Fox does. Find that bastard and kill him. And make him suffer first if you can. For poor Catherine. When it's done, cut that fat ring he wears on his hand off with the finger inside and bring it to me as proof\nI know his crooked finger and that ring well. If you do that, I will pay you a quarter of a million in silver.";
			link.l1 = "Looks like you've received a large inheritance from your dear old uncle, may he rest in peace, huh? Tell me, Henry, why did you decide to ask me to help with this matter?";
			link.l1.go = "tibo_33";
		break;
		
		case "tibo_33":
			dialog.text = "Because I have learned a few things about you too, "+GetFullName(pchar)+". It was easy, you are a famous man. It is unknown whom you are really working for though, whether for de Poincy, the Dutch, the English, or Baron Jan Svenson... But one thing is clear: you take delicate, discreet jobs and get them done. Then you are paid handsomely for them. And best of all, you are not connected to the Spanish\nAfter all, you also took part in the events after which I inherited my uncle's fortune. Don't deny it... A quarter of a million is good money. I will tell you where to find Martene. You only have to intercept his ship and board her.";
			link.l1 = "Another hundred thousand and I'll take care of Martene for you.";
			link.l1.go = "tibo_34";
			link.l2 = "Alas, Monsieur Thibaut, you'll have to take care of your problem with Martene and Colonel Fox without my participation. I, for my part, promise you that I will not send any word to the colonel about the fate of his daughter and those who are guilty of her death. All the best, sir.";
			link.l2.go = "tibo_exit";
		break;
		
		case "tibo_exit":
			DialogExit();
			AddQuestRecord("Sharlie", "26");
			NextDiag.CurrentNode = "tibo_over";
		break;
		
		case "tibo_34":
			dialog.text = "Sir, for God's sake... I don't have millions stashed away in treasure chests, believe me! I understand that your services cost money, which is why I offered you two hundred and fifty thousand straight away... Fine... Alright, how about I add another fifty thousand in gold. I can't offer you any more!";
			link.l1 = "Fine. You've got yourself a deal. Where was the last place you saw Martene?";
			link.l1.go = "tibo_35";
		break;
		
		case "tibo_35":
			dialog.text = "He sailed south to the Spanish Main in Caracas and managed to secure an audience with Don Diego Francisco de Kerres, the governor. It seems that he bribed him somehow, because Don Diego granted Robert the protection of the Spanish crown. He sold the 'Voltigeur' and now he is the captain of the heavy galleon 'Infanta'. He must have had really good savings, since he could afford to bribe the governor and to buy and equip a large military ship like that\nSo, next he will sail from Caracas to Santo Domingo on his new ship as part of a Spanish squadron. That is all my agent managed to find out. The only opportunity to get Martene is to catch up to that Spanish squadron\nIf they reach Santo Domingo, it is over. No clue where Robert will go next. He'll be gone to ground like a rabbit in a warren and we'll never find him.";
			link.l1 = "Got it. I'll intercept them.";
			link.l1.go = "tibo_36";
		break;
		
		case "tibo_36":
			dialog.text = "And don't forget the finger with the ring! That's an essential condition of our agreement! I want to be absolutely sure that Robert is dead!";
			link.l1 = "All right. Let's not waste any time, I'll set sail at once!";
			link.l1.go = "tibo_37";
		break;
		
		case "tibo_37":
			DialogExit();
			AddQuestRecord("Sharlie", "27");
			Terrapin_CreateRoberConvoy();
			if(bImCasual) NewGameTip("Exploration mode: timer is not disabled. Meet the deadline!");
			NextDiag.CurrentNode = "tibo_time";
		break;
		
		case "tibo_time":
			dialog.text = "Is Martene still stinking up the Caribbean with his presence, captain?";
			link.l1 = "He hasn't got long!";
			link.l1.go = "exit";
			NextDiag.TempNode = "tibo_time";
		break;
		
		case "tibo_38":
			dialog.text = "Is Martene stinking up the Caribbean with his presence, captain?";
			link.l1 = "Not anymore. You need not fear Colonel Fox any longer, and your Catherine is avenged. Here is your proof.";
			link.l1.go = "tibo_39";
		break;
		
		case "tibo_39":
			RemoveItems(pchar, "finger", 1);
			dialog.text = "Yes... That is Martene's finger, without a doubt. You never cease to impress, Captain "+GetFullName(pchar)+"! You truly deserve the reputation you've earned.";
			link.l1 = "Let's get to the payment, shall we, Thibaut?";
			link.l1.go = "tibo_40";
		break;
		
		case "tibo_40":
			AddMoneyToCharacter(pchar, 250000);
			TakeNItems(pchar, "gold_dublon", 500);
			Log_Info("You've received 500 doubloons");
			PlaySound("interface\important_item.wav");
			dialog.text = "It's all ready. Here, take your reward.";
			link.l1 = "My gratitude. I'm glad you were able to get that ready ahead of time. Well, Henry, I hope that you do not fall into further scrapes like this and that you choose better friends in the future. All the best!";
			link.l1.go = "tibo_41";
		break;
		
		case "tibo_41":
			dialog.text = "Thank you for your help, Captain! I'll recommend you to all my friends. Good luck!";
			link.l1 = "...";
			link.l1.go = "tibo_42";
		break;
		
		case "tibo_42":
			DialogExit();
			AddQuestRecord("Sharlie", "31");
			NextDiag.CurrentNode = "tibo_stop";
		break;
		
		case "tibo_stop":
			dialog.text = "Yes, monsieur "+GetFullName(pchar)+"? Do you have business with me?";
			link.l1 = "No, Monsieur Thibaut. Just decided to stop by for a moment. Goodbye!";
			link.l1.go = "exit";
			NextDiag.TempNode = "tibo_stop";
		break;
		
		case "tibo_late":
			dialog.text = "Ah, "+GetFullName(pchar)+"...Come on, what's taking you so long! Now, who the hell knows where Robert Martene is?! If Colonel Fox manages to find everything out, I think I'll be in deep trouble...";
			link.l1 = "I see. I was too late. My apologies, Monsieur Thibaut, but I was delayed by some very pressing matters. I'm not going to waste your time. Goodbye.";
			link.l1.go = "exit";
			NextDiag.TempNode = "tibo_over";
		break;
		
		case "tibo_over":
			dialog.text = "What do you want, "+GetFullName(pchar)+"? I don't have time to chat. I've got bigger fish to fry. I must find Martene before Fox does...";
			link.l1 = "Yes, yes. I'm on my way.";
			link.l1.go = "exit";
			NextDiag.TempNode = "tibo_over";
		break;
		
		// посланник от Мартэна
		case "envoy":
			dialog.text = "Are you the Captain "+GetFullName(pchar)+"?";
			link.l1 = "You've come to the right man, mate. I'm all ears.";
			link.l1.go = "envoy_1";
		break;
		
		case "envoy_1":
			dialog.text = "Your debtor has asked me to tell you that the deed is done and the fish will swim into the net in less than an hour. So make haste.";
			link.l1 = "I understand. Thank you!";
			link.l1.go = "envoy_2";
		break;
		
		case "envoy_2":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1", "none", "", "", "OpenTheDoors", -1);
			AddQuestRecord("Terrapin", "9");
			pchar.quest.Terrapin_cave.win_condition.l1 = "Timer";
			pchar.quest.Terrapin_cave.win_condition.l1.date.hour  = sti(GetTime()+1);
			pchar.quest.Terrapin_cave.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 0);
			pchar.quest.Terrapin_cave.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 0);
			pchar.quest.Terrapin_cave.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 0);
			pchar.quest.Terrapin_cave.win_condition.l2 = "location";
			pchar.quest.Terrapin_cave.win_condition.l2.location = "Tortuga_cave";
			pchar.quest.Terrapin_cave.function = "Terrapin_LevasserInCave";
		break;
		
		// Левассер в пещере
		case "levasser_cave":
			pchar.quest.Terrapin_LateDungeon.over = "yes"; //снять таймер
			dialog.text = "Why the hell are you wandering around here? Who are you? Answer me now!";
			link.l1 = "Who the hell are you and why are you asking me such stupid questions?";
			link.l1.go = "levasser_cave_1";
		break;
		
		case "levasser_cave_1":
			dialog.text = "What?! You snot-nosed pissant! Who am I? I'm the governor of this island, François Levasseur, Señor de Renet de Boidouflet de Lettre! And everything on this island is under my jurisdiction! That includes you while you're on my turf, pup!";
			link.l1 = "Well well... The big bad wolf himself, eh? You're a little lost, Levasseur, Señor de Renet de whatever it was. Your time is up. By order of Governor-General François Longvilliers de Poincy, you've been removed from your post and sentenced to immediate death! I am your judge and your executioner in one! Any last words?";
			link.l1.go = "levasser_cave_2";
		break;
		
		case "levasser_cave_2":
			dialog.text = "";
			link.l1 = "I suppose you're not going to give up, and asking me for mercy won't avail you, so go on and draw steel!";
			link.l1.go = "levasser_cave_3";
		break;
		
		case "levasser_cave_3":
			dialog.text = "Blast! It's an agent of de Poincy! Draw your swords! Kill him!";
			link.l1 = "Let us dance.";
			link.l1.go = "levasser_cave_4";
		break;
		
		case "levasser_cave_4":
			LAi_LocationFightDisable(&Locations[FindLocation("Tortuga_cave")], false);//разрешить драться
			DialogExit();
			LAi_SetWarriorType(npchar);
			LAi_group_MoveCharacter(npchar, "EnemyFight");
			for (i=2; i<=4; i++)
			{
				sld = characterFromId("TerrapinGuard"+i);
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "EnemyFight");
			}
			// подкрепление
			int iRank = sti(pchar.rank)+MOD_SKILL_ENEMY_RATE+7;
			int iScl = 30 + 2*sti(pchar.rank);
			for (i=5; i<=9; i++)
			{		
				sld = GetCharacter(NPC_GenerateCharacter("TerrapinGuard"+i, "citiz_5"+i, "man", "man", iRank, PIRATE, -1, true, "quest"));
				FantomMakeCoolFighter(sld, iRank, iScl, iScl, "blade_19", "pistol5", "bullet", iScl*2+50);
				ChangeCharacterAddressGroup(sld, "Tortuga_cave", "goto", "goto"+i);
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "EnemyFight");
			}
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("EnemyFight", "Terrapin_LevasserCaveDied");
			AddDialogExitQuest("MainHeroFightModeOn");	
		break;
		
		// Левассер в комнате таверны
		case "levasser_room":
			dialog.text = "What the hell are you doing here? Who are you? Answer me, now!";
			link.l1 = "How about that! Didn't see that coming... Monsieur Levasseur himself, I presume?";
			link.l1.go = "levasser_room_1";
		break;
		
		case "levasser_room_1":
			dialog.text = "Yes, I'm the governor of this island, François Levasseur, Seigneur de Renet de Boidouflet de Lettre! And everything on this island is under my jurisdiction! That includes you while you're walking on my turf, you scoundrel! Answer the questions! Sergeant, lock this door. This man is up to no good!";
			link.l1 = "You are incredibly insightful, monsieur Levasseur, Seigneur de Renet de whatever. My presence here won't come as a delight to you. By order of Governor-General François Longvilliers de Poincy, you've been removed from your post and sentenced to immediate death! I am your judge and your executioner in one!";
			link.l1.go = "levasser_room_2";
		break;
		
		case "levasser_room_2":
			dialog.text = "";
			link.l1 = "I suppose you're not going to give up, and asking me for mercy won't avail you, so go on and draw steel! You are my job, nothing personal. Just serving the Crown, ha! Sergeant, I don't advise you to interfere while I carry out the governor-general's orders!";
			link.l1.go = "levasser_room_3";
		break;
		
		case "levasser_room_3":
			dialog.text = "Don't listen to him, sergeant! He's a Spanish agent! Kill him! Guards, help! There are Spaniards here!";
			link.l1 = "Never been to Spain, actually, just Narbonne.";
			link.l1.go = "levasser_room_4";
		break;
		
		case "levasser_room_4":
			LAi_LocationFightDisable(&Locations[FindLocation("Tortuga_tavern_upstairs")], false);//разрешить драться
			DialogExit();
			LAi_SetWarriorType(npchar);
			LAi_group_MoveCharacter(npchar, "EnemyFight");
			for (i=1; i<=2; i++)
			{
				sld = characterFromId("TerrapinGuard"+i);
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "EnemyFight");
			}
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("EnemyFight", "Terrapin_LevasserRoomDied");
			AddDialogExitQuest("MainHeroFightModeOn");	
		break;
		
		// девушка на балконе
		case "roof_girl":
			dialog.text = "Ouch! Help me! Soldiers!";
			link.l1 = "Quiet down, you fool! If you don't scream, I won't do anything to you!";
			link.l1.go = "roof_girl_1";
		break;
		
		case "roof_girl_1":
			dialog.text = "Don't kill me!";
			link.l1 = "Don't be ridiculous! A man just ran by here ten minutes ago. A well-dressed nobleman. Where is he hiding? And don't even think about telling me you didn't see him!";
			link.l1.go = "roof_girl_2";
		break;
		
		case "roof_girl_2":
			dialog.text = "Monsieur Thibaut?";
			link.l1 = "Well then, so you know him! Where did he run off to? Are you going to answer, or should I give your head a good shake to get it working?";
			link.l1.go = "roof_girl_3";
		break;
		
		case "roof_girl_3":
			dialog.text = "Oh no, please don't hurt me! Monsieur Thibaut ran away, that way towards the sea. And he jumped off the hoist, right into the water. He probably died, it's so high up...";
			link.l1 = "I don't think so. He's not the type who would commit suicide. You should go inside. It's dangerous to be out here tonight.";
			link.l1.go = "roof_girl_4";
		break;
		
		case "roof_girl_4":
			dialog.text = "Ouch! Ouch! Don't shoot!";
			link.l1 = "What?!";
			link.l1.go = "roof_girl_5";
		break;
		
		case "roof_girl_5":
			DialogExit();
			LAi_SetActorType(pchar);
			PlaySound("People Fight\MushketShot.wav");
			DoQuestCheckDelay("Terrapin_GirlShot", 1.0);
		break;
		
		// Кати
		case "kathy":
			PlaySound("Voice\English\Armo02.wav");
			dialog.text = "Who are you? Have you come to kill me or... worse?";
			link.l1 = "Nothing of the sort, madam. I will be returning you, Catherine Fox, to your father in St. John's. If he gives you a lashing after that for disobeying his orders, then my guilt will be repeated. However, I do hope that the colonel will be happy to see his daughter alive in spite of all the worry she has put him through.";
			link.l1.go = "kathy_1";
		break;
		
		case "kathy_1":
			dialog.text = "Thank God! I must be dreaming! Don't you know who I am? You are a Frenchman and a Catholic, and yet you have decided to come here to save me from the hands of my own countrymen? You've risked your life just for Colonel Fox's daughter?";
			link.l1 = "My original reason for being here on Tortuga was quite different. But I couldn't leave a beautiful lady in the hands of a band of thieves and robbers either.";
			link.l1.go = "kathy_2";
		break;
		
		case "kathy_2":
			dialog.text = "You are a noble gentleman! What is your name, monsieur?";
			link.l1 = ""+GetFullName(pchar)+". Captain "+GetFullName(pchar)+".";
			link.l1.go = "kathy_3";
		break;
		
		case "kathy_3":
			dialog.text = "Tell me, Captain, are you really going to take me to my father in St. John's?";
			link.l1 = "Yes, although he doesn't take kindly to Frenchmen. Well, I'll remind him that there are Englishmen who are scoundrels as well, including English officers! I was a witness to at least one of them... Richard Fleetwood was his name.";
			link.l1.go = "kathy_4";
		break;
		
		case "kathy_4":
			dialog.text = "If we make it to Antigua, I'll do everything I can to convince my father that there are true knights among the French.";
			link.l1 = "I would quite appreciate that... All right, I hope that my guardian angels have watched over my path along the city rooftops and are already awaiting our return.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Terrapin_OwrInGrot");
		break;
		
		case "kathy_5":
			PlaySound("Voice\English\Armo01.wav");
			dialog.text = "I couldn't believe you would keep your promise until now! So many dreadful and vile things have happened to me lately... I thank you, captain, for restoring my faith in people and chivalry. You should visit my father when you can!\nHe respects men like you. And it doesn't matter that you are French. I will do everything I can to persuade my father to reconsider his attitude towards your nation.";
			link.l1 = "Thank you, Catherine. Perhaps I shall take advantage of your courteous offer.";
			link.l1.go = "kathy_6";
		break;
		
		case "kathy_6":
			dialog.text = "I do hope you will, captain. A huge thank you once again for what you've done for me. I'll never forget it.";
			link.l1 = "Go on, hurry along to your father. He'll be delighted to see you. Perhaps he's already returned from the field. Well, anyway, it's time for me to go. Goodbye!";
			link.l1.go = "kathy_7";
		break;
		
		case "kathy_7":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload3_back", "none", "", "", "OpenTheDoors", 10.0);
			npchar.lifeday = 0;
			SetFunctionTimerCondition("Terrapin_ReturnFox", 0, 0, 3, false); // Фокса на место
			pchar.questTemp.Terrapin_KathyReward = "true"; // награда за спасение Кати 160912
		break;
		
		// наш матрос
		case "terrapin_grot":
			dialog.text = "There you are, Cap! You had us worried sick! A dash like that along the tiled rooftops and a leap like that from such a gut-wrenching height was a sight to behold! God as our witness, we were concerned you wouldn't make it... Welcome back on board, Cap, the longboat's ready!";
			link.l1 = "Great. Catherine, follow me!";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Terrapin_GotoShip");
		break;
		
		case "tibo_sailor":
			dialog.text = "Hello, monsieur. Are you the captain "+GetFullName(pchar)+"?";
			link.l1 = "Aye, that's me. What's going on?";
			link.l1.go = "tibo_sailor_1";
		break;
		
		case "tibo_sailor_1":
			dialog.text = "Phew, I barely caught up with you... I've come to you on behalf of a gentleman you know by the name of Henry Thibaut.";
			link.l1 = "Henry? And what does he want? To share his joy at his inheritance unexpectedly falling into his lap after the death of his late dear uncle?";
			link.l1.go = "tibo_sailor_2";
		break;
		
		case "tibo_sailor_2":
			dialog.text = "Monsieur Thibaut has urgently requested that you visit him at his mansion on Tortuga as soon as possible. He has well-paid work for you. He also told me to mention one name to you: Robert Martene. That should spark your interest.";
			link.l1 = "Is that so? And what gave Henry that idea?";
			link.l1.go = "tibo_sailor_3";
		break;
		
		case "tibo_sailor_3":
			dialog.text = "Also, if that didn't convince you to come visit him already, he further requested that I add the following: 'Robert Martene must die'.";
			link.l1 = "Alright, alright... Now it's getting interesting. Two sworn friends have just got into an argument... As you say, I'll try to visit Henry when I get the chance.";
			link.l1.go = "tibo_sailor_4";
		break;
		
		case "tibo_sailor_4":
			dialog.text = "Monsieur Thibaut has asked you not to delay your visit. 'The fish will swim out of the net in ten days' were his exact words...";
			link.l1 = "He and Robert speak in the same manner. All right, I'll pay Henry a visit.";
			link.l1.go = "tibo_sailor_5";
		break;
		
		case "tibo_sailor_5":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1_back", "none", "", "", "OpenTheDoors", 10.0);
			if(bImCasual) NewGameTip("Exploration mode: timer is not disabled. Meet the deadline!");
			SetFunctionTimerCondition("Terrapin_TiboCallOver", 0, 0, 10, false);
			AddQuestRecord("Sharlie", "25");
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}
