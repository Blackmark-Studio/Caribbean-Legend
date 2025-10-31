// Глэдис МакАртур - приемная мать Элен
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
			if(pchar.questTemp.Saga == "helena1")
			{
				dialog.text = "Ah, Captain! You know, I have told Helen everything. You can't imagine what a weight has been lifted from my mind!";
				link.l1 = "You have done everything right, Miss McArthur. The girl needs to know the truth. And I am here because of her.";
				link.l1.go = "Helena_hire";
			}
			else
			{
				dialog.text = "Greetings, "+pchar.name+"! I'm glad to see you! Want some rum?";
				link.l1 = "Thank you, Miss McArthur, but I am too busy right now.";
				link.l1.go = "exit";			
			}
			NextDiag.TempNode = "First time";
		break;
		
		case "FindHelena":
			dialog.text = "What do you want, sir?";
			link.l1 = "Are you Gladys McArthur?";
			link.l1.go = "FindHelena_1";
		break;
		
		case "FindHelena_1":
			dialog.text = "I am. I don't remember you, young man. So, would you care to explain what you want from me?";
			link.l1 = "I am interested in the story of your daughter's disappearance, Miss McArthur. What made you think that she disappeared? I have heard that Helen had a very skilful crew...";
			link.l1.go = "FindHelena_2";
		break;
		
		case "FindHelena_2":
			dialog.text = "Ah, I am absolutely certain! Look, my late husband's death anniversary was five days ago. Helen loved her father and she would never miss this date. She had only left for a few days to receive a shipment of redwood from the friendly Miskito people.\nThe Indians respect and fear our patron Jan Svenson; they would never harm her. Señor Svenson has already spoken to them. The wood was loaded on the same day. No one has seen Helen since.";
			link.l1 = "Perhaps the pirates attacked her?";
			link.l1.go = "FindHelena_3";
		break;
		
		case "FindHelena_3":
			dialog.text = "Nonsense! You must already know that Mister Svenson is one of the five pirate barons and a member of the Council of the Brethren of the Coast. No pirates are allowed to hunt here without his permission. It could be a newcomer though...";
			link.l1 = "And what about the Spanish? Could she have encountered a Spanish patrol?";
			link.l1.go = "FindHelena_4";
		break;
		
		case "FindHelena_4":
			dialog.text = "I am not good with politics, but they say that the local gold and silver mines are completely depleted, not many treasures left to risk the lives of noble hidalgos for. So they are rare guests here. Besides, the Indian people are hostile towards them.\nA random encounter with a Spanish patrol couldn't have ended badly for Helen, she hadn't done anything illegal from their point of view. 'Rainbow' was flying a Dutch flag and all of Helen's papers were in order, including a trade licence.";
			link.l1 = "Did anything unusual happen before her most recent journey? Perhaps some strange event you might have overlooked?";
			link.l1.go = "FindHelena_5";
		break;
		
		case "FindHelena_5":
			dialog.text = "Ah, no! Thank God, we are living peaceful lives here. However, a few weeks ago Helen received a letter from another unwanted admirer begging for a date. She is a pretty girl, but not a rich one.\nSo she has plenty of admirers, though she doesn't like any of them and she doesn't want to get married. She has already fooled a lot of people this way. So frivolous, just like her mother was!";
			link.l1 = "You don't look like that type of woman, Miss McArthur...";
			link.l1.go = "FindHelena_6";
		break;
		
		case "FindHelena_6":
			dialog.text = "What? Ah, whatever, I'm heartbroken. What was I saying? Ah, yes, the letter. Anyway, that letter was written by Jimmy Higgins. He's one of Jackman's men and lives in Maroon Town. He visits our town quite often. Jackman is a pirate baron too, but Mister Svenson doesn't like him, I don't know why.";
			link.l1 = "And Helen?";
			link.l1.go = "FindHelena_7";
		break;
		
		case "FindHelena_7":
			dialog.text = "Oh, she was laughing out loud. She had received a proposal from the captain of an English corvette a day earlier, and she rejected even him. And now this common boatswain from a pirate's old tub... Not a chance, the daughter of Sean McArthur demands a more imposing husband!";
			link.l1 = "And what was the name of that English captain?";
			link.l1.go = "FindHelena_8";
		break;
		
		case "FindHelena_8":
			dialog.text = "Oh, how should I know? Real gentlemen are rare guests here. I'm sorry, I didn't mean to offend you. Ask that Higgins. He must remember his name. Jimmy was trying to duel that captain over Helen. His pals barely managed to stop him from doing it. But both of them left Blueweld a few days before Helen sailed off.";
			link.l1 = "Well, thank you for your story. I will try to find your loved one. If I learn anything, I will tell you or Mister Svenson. I hope to find your daughter alive and in one piece.";
			link.l1.go = "FindHelena_9";
		break;
		
		case "FindHelena_9":
			dialog.text = "Are you going to look for her? God be with you, may He guide you and strengthen your hand! I will be praying for you! Tell me your name, honourable man?";
			link.l1 = ""+pchar.name+". "+GetFullName(pchar)+". I hope to return with good news soon, Miss McArthur. Farewell!";
			link.l1.go = "FindHelena_10";
		break;
		
		case "FindHelena_10":
			DialogExit();
			NextDiag.CurrentNode = "FindHelena_wait";
			AddQuestRecord("Saga", "1");
			pchar.questTemp.Saga = "maruntown";//идем к Джекману
			SetFunctionTimerCondition("Gladis_SetHome", 0, 0, 1, false);
			int iTime = 25-MOD_SKILL_ENEMY_RATE;
			if(bImCasual)
			{
				NewGameTip("Exploration mode: quest duration doubled");
				SetFunctionTimerCondition("Helena_AntiguaOver", 0, 0, iTime*2, false);
			}
			else SetFunctionTimerCondition("Helena_AntiguaOver", 0, 0, iTime, false);
		break;
		
		case "FindHelena_wait":
			dialog.text = "Have you any new information about my poor daughter, "+pchar.name+"?";
			link.l1 = "I am sorry, Miss McArthur, I have nothing new to tell you so far, but don't despair. I'll continue my search. The lack of bad news is good news in itself.";
			link.l1.go = "exit";
			NextDiag.TempNode = "FindHelena_wait";
		break;
		
		case "Helena_die":
			dialog.text = "You were too late, Captain. The body of my poor daughter was found on the shores of Antigua. Lord, how they tortured her before her death! I have failed to protect my beautiful girl...";
			link.l1 = "I am sorry. There was nothing I could do...";
			link.l1.go = "exit";
			NextDiag.TempNode = "Gladis_exit";
		break;
		
		case "Gladis_exit":
			dialog.text = "Ah, young man, please, leave me alone with my grief...";
			link.l1 = "...";
			link.l1.go = "exit";
			NextDiag.TempNode = "Gladis_exit";
		break;
		
		case "Gladis_regard":
			dialog.text = "I don't even know how to thank you, Captain, for saving my daughter. She has told me everything and I admire your bravery and honour. Here, take these golden doubloons. It is not much, but I offer them in all sincerity. And don't even think of refusing!";
			link.l1 = "Fine, Gladys, I won't. But I did not save your daughter for money, and I hope you know that.";
			link.l1.go = "Gladis_regard_1";
			link.l2 = "Keep this money for yourself, Gladys. You need it more than I do.";
			link.l2.go = "Gladis_regard_2";
			sld = characterFromId("Helena");
			LAi_SetStayType(sld);
			AddCharacterExpToSkill(pchar, "Leadership", 50);
			// открыть город
			LocatorReloadEnterDisable("SantaCatalina_town", "reload1_back", false);
			LocatorReloadEnterDisable("SantaCatalina_town", "reload2_back", false);
			LocatorReloadEnterDisable("SantaCatalina_town", "gate_back", false);
		break;
		
		case "Gladis_regard_1":
			TakeNItems(pchar, "gold_dublon", 100);
			dialog.text = "I am glad that I was able to repay you in some way for your honourable deed. The doors of my home are always open to you. Helen and I will be glad to see you at any time.";
			link.l1 = "Thank you, Miss McArthur. I shall visit you and Helen when the opportunity arises.";
			link.l1.go = "exit";
			NextDiag.TempNode = "Gladis_wait";
		break;
		
		case "Gladis_regard_2":
			dialog.text = "Ah, please... I just wanted to repay you for your honourable deed. Know that the doors of my home are always open to you. Helen and I will be glad to see you any time.";
			link.l1 = "Thank you, Miss McArthur. I will visit you and Helen when the opportunity arises.";
			link.l1.go = "exit";
			NextDiag.TempNode = "Gladis_wait";
			pchar.questTemp.Saga.Helena_friend = "true";//атрибут поведения Элен в будущем
		break;
		
		case "Gladis_wait":
			if (CheckAttribute(pchar, "questTemp.HelenDrinking.Dialogs.Gladys")) {
				dialog.text = "Captain, you are always welcome in our home! Are you here for Helen? I'm afraid she's locked herself in her room - she must be exhausted after the last few days. Don't worry, it happens to her sometimes.";
				link.l1 = "Really? Are you sure she is alright?";
				link.l1.go = "after_drinking";
				
				DeleteAttribute(pchar, "questTemp.HelenDrinking.Dialogs.Gladys");
				break;
			}
		
			dialog.text = "Ah, Monsieur de Maure! I am always glad to see the saviour of my daughter in my house. Do you want to see Helen? She is upstairs in her room. After the loss of the 'Rainbow' and her remarkable rescue, she avoids going out. It's the first time I have seen her in such a state of confusion...";
			link.l1 = "Thank you, Miss McArthur.";
			link.l1.go = "exit";
			NextDiag.TempNode = "Gladis_wait";
		break;
		
		case "Gladis_history":
			dialog.text = "Ah, Monsieur de Maure! I am always glad to see the saviour of my daughter in my house. Do you wish to see Helen?";
			link.l1 = "No. I want to ask you a few questions and I really hope for your candour. Helen's safety depends on it. Is this ring familiar to you?";
			link.l1.go = "Gladis_history_1";
		break;
		
		case "Gladis_history_1":
			RemoveItems(pchar, "bucher_ring", 1);
			PlaySound("interface\important_item.wav");
			dialog.text = "Good Lord! This is... her father's ring!";
			link.l1 = "Mister McArthur's?";
			link.l1.go = "Gladis_history_2";
		break;
		
		case "Gladis_history_2":
			dialog.text = "No. Helen is our stepdaughter, but she doesn't know that. Her parents died, so I decided to take her in as my own child. Sean adopted her, but even he didn't know she is not my daughter.";
			link.l1 = "So who are her real parents?";
			link.l1.go = "Gladis_history_3";
		break;
		
		case "Gladis_history_3":
			dialog.text = "I know her father was a pirate called 'Butcher' on the frigate 'Neptune'. I only saw him twice. And her mother was a beautiful young woman, red-haired, dressed in men's clothes. That's pretty much all I can tell you about her, except that she was a bad mother.\nI'd never have left such a baby in the hands of strangers. Both of them died tragically. And the promised courier has appeared twenty years later and turned out to be you. Did Butcher send you? Is he alive?";
			link.l1 = "Calm down, Miss Gladys! There is no reason to suspect that the Butcher has returned, though you are the second person to have this idea. I recently met a man who was supposed to show you this ring...";
			link.l1.go = "Gladis_history_4";
		break;
		
		case "Gladis_history_4":
			dialog.text = "...";
			link.l1 = "A simple incident had prevented him from doing so in time, and he suffered all his life because he had failed his captain's last order. He died not long ago and... well, enough sad news. Tell me, Gladys, did Helen's mother leave any token for her child in her memory? Some little thing, perhaps?";
			link.l1.go = "Gladis_history_5";
		break;
		
		case "Gladis_history_5":
			dialog.text = "She left me a strange piece of an old map. She joked that it was her legacy. What good could that scrap of paper do? I believe it was nothing more than a poor joke. She was overexcited and a bit out of her mind. But I kept this 'gift'.\nWho knows... If you want, I can give it to you if you promise to tell me the whole story one day.";
			link.l1 = "Absolutely, Miss McArthur. I will take this scrap with me for a while. I need to talk to Mister Svenson.";
			link.l1.go = "Gladis_history_6";
		break;
		
		case "Gladis_history_6":
			GiveItem2Character(pchar, "map_half_beatriss"); //половинка карты
			PlaySound("interface\important_item.wav");
			dialog.text = "You have helped us once again, Monsieur de Maure! And I have no idea how to thank you. Please, take my husband's pistol, at least. He was always proud of it and told me it was very rare. It has just been lying here for a long time. Let it serve you! Take it, please, take it!";
			link.l1 = "Thank you, Gladys. This pistol is truly excellent. Thank you, and farewell.";
			link.l1.go = "Gladis_history_7";
			if (CheckCharacterItem(pchar, "chest"))
			{
				link.l2 = "Let this pistol serve Helen. I have enough weapons.";
				link.l2.go = "Gladis_history_8_1";
			}
		break;
		
		case "Gladis_history_7":
			DialogExit();
			PlaySound("interface\important_item.wav");
			GiveItem2Character(pchar, "pistol5");
			pchar.questTemp.Saga = "svenson2";
			NextDiag.CurrentNode = "First time";
			DeleteAttribute(pchar, "questTemp.Saga.Helena_friend");
			AddQuestRecord("Saga", "22");
			AddCharacterExpToSkill(pchar, "Leadership", 50);
		break;
		
		case "Gladis_history_8_1":
			dialog.text = "But why do you keep refusing my gifts? You make me upset...";
			link.l1 = "I believe I can make you happy now. I am going to return the gold that the courier was meant to deliver to you for the safe keeping of Captain Butcher's daughter. Of course, these doubloons won't repay all your love and loyalty, but they are yours by right. You may do with them as you wish.";
			link.l1.go = "Gladis_history_8";
		break;
		
		case "Gladis_history_8":
			dialog.text = "Ah, Captain! I don't know what to say... I couldn't imagine that such... honourable men even exist! Go to my daughter and tell her the good news!";
			link.l1 = "I am on my way, Miss McArthur.";
			link.l1.go = "Gladis_history_9";
		break;
		
		case "Gladis_history_9":
			DialogExit();
			RemoveItems(pchar, "chest", 1);
			pchar.questTemp.Saga = "svenson2";
			NextDiag.CurrentNode = "First time";
			AddQuestRecord("Saga", "22");
			sld = characterFromId("Helena");
			GiveItem2Character(sld, "pistol5");
			EquipCharacterbyItem(sld, "pistol5");
			ChangeCharacterComplexReputation(pchar, "nobility", 5);
			AddCharacterExpToSkill(pchar, "Leadership", 100);
			
			pchar.questTemp.Saga.HelenRelation = sti(pchar.questTemp.Saga.HelenRelation) + 1;
		break;
		
		case "Helena_hire":
			dialog.text = "Are you serious? What do you mean?";
			link.l1 = "According to the request of Mister Svenson, I am going to employ Helen on my ship as an officer. She is in great danger. Helen will need solid protection while Jan and I are dealing with this matter. I hope that I will be able to provide such protection.";
			link.l1.go = "Helena_hire_1";
		break;
		
		case "Helena_hire_1":
			dialog.text = "Ah, that is so good! I wouldn't have dared to ask you for this myself. It will be the very best protection for my girl. Helen will be so glad to sail again!";
			link.l1 = "Thank you for your compliment, Miss McArthur. And now I must see your... stepdaughter.";
			link.l1.go = "exit";
			LocatorReloadEnterDisable("SantaCatalina_houseSp3", "reload2", false);//открыть спальню Элен
			sld = characterFromId("Helena");
			sld.dialog.currentnode = "Helena_hire";
			pchar.questTemp.Saga = "helena2";
		break;
		
		case "saw_sex":
			dialog.text = "Oh, God! My little girl!";
			link.l1 = "Gladys, don't you know how to knock?!";
			link.l1.go = "saw_sex_1";
		break;
		
		case "saw_sex_1":
			dialog.text = "Oh, forgive me, young people! I'm leaving! Helen, remember what I told you!";
			link.l1 = "";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_AfterCaveGladysTalk");
		break;
		
		case "after_drinking":
			dialog.text = "I think this time she just overworked herself. She told me everything, Captain! Thank you for helping her choose a new ship yesterday!";
			link.l1 = "Huh? Hm, you're welcome. Goodbye, Mrs MacArthur.";
			link.l1.go = "exit";
			
			NextDiag.TempNode = "Gladis_wait";
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
	}
}
