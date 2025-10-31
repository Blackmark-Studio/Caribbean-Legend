// диалог прочих НПС по квесту Саги
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	int i, iTemp;
	string sTemp;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			dialog.text = "Want something?";
			link.l1 = "No, nothing.";
			link.l1.go = "exit";			
			NextDiag.TempNode = "First time";
		break;
		
//---------------------------------------------Джимми в доме в Марун-Тауне------------------------------------
		case "Jimmy":
			dialog.text = "What do you want? Can't you see that I am in mourning! Get lost before I kick you down the stairs!";
			link.l1 = "Well, buy yourself a bigger house with stairs for that. Then we'll talk about kicking people down the stairs, hero...";
			link.l1.go = "Jimmy_1_1";
			link.l2 = "Why are you so upset, Jimmy? No rum for me for the rest of my damn life if it hasn't got to do with some beautiful woman! Only a woman could make an old sea wolf like you threaten your old friends...";
			link.l2.go = "Jimmy_1_2";
		break;
		
		case "Jimmy_1_1":
			dialog.text = "I hate fastidious people like you! You always get the best pieces of the cake. They didn't let me kill one upstart, so I'll take out my anger on you!";
			link.l1 = "...";
			link.l1.go = "Jimmy_fight";
		break;
		
		case "Jimmy_fight":
			DialogExit();
			AddDialogExitQuestFunction("Saga_Jimmy_fight");
		break;
		
		case "Jimmy_1_2":
			dialog.text = "Yeah?! Do I know you? I don't remember you, goddamn it...";
			link.l1 = "It is I, "+pchar.name+"! We had a fine time in Blueweld after you nearly disembowelled that insolent fellow in the coat. What was his name again? I have forgotten... Anyway, I wouldn't give a damn about the cannons on his corvette if I ever meet him at sea!";
			link.l1.go = "Jimmy_2";
		break;
		
		case "Jimmy_2":
			dialog.text = "His name was Arthur! Arthur Donovan, captain of the 'Arbutus' corvette! Filthy bastard! So you agree that I was close to sending him to the devil?";
			link.l1 = "Of course! He had absolutely no chance, but your pals interfered. Forgive them, they didn't want you to be hanged for the murder of a naval officer.";
			link.l1.go = "Jimmy_3";
		break;
		
		case "Jimmy_3":
			dialog.text = "Argh! If only I had a ship! That bastard can easily be tracked near Antigua... ha! I owe you one if you send him to the bottom!";
			link.l1 = "Deal, ha-ha! By the way, is Rumba really worth all your suffering?";
			link.l1.go = "Jimmy_4";
		break;
		
		case "Jimmy_4":
			dialog.text = "By all means! I have never met anyone better than her. But she just laughs at me. Everybody wants that mermaid. Some sailors secretly told me that our Jacob is looking for a girl who looks just like my Rumba. He wants her too! How can I follow his orders now?";
			link.l1 = "Keep quiet, pal! Walls have ears... And why do you think Jackman is looking for Rumba?";
			link.l1.go = "Jimmy_5";
		break;
		
		case "Jimmy_5":
			dialog.text = "He is, for sure! He is looking for some Henry the Hangman and a twenty-year-old lass with blonde hair and blue eyes. Some Gladys Chandler from Belize must be her caretaker.";
			link.l1 = "Wait! Gladys has a different surname. And she is her mother!";
			link.l1.go = "Jimmy_6";
		break;
		
		case "Jimmy_6":
			dialog.text = "Jackman is cunning! You can't catch him unprepared! I've been courting Rumba for a while and found out that Gladys married Sean McArthur exactly twenty years ago. And before that, she lived in Belize. Her first husband was called Pete Chandler.\nPoor Pete was killed in a drunken fight. They say that McArthur himself was responsible, as he had feelings for plump Gladys back then. She became a widow with a baby on her hands. The child didn't outlive its daddy by much and died of a fever soon after.\nAnd just a couple of months later, Gladys and Sean showed up with a girl, said to be McArthur's daughter, in Blueweld. So, how could Gladys give birth to another baby that soon? Do you follow?";
			link.l1 = "Have you told anyone else about this?";
			link.l1.go = "Jimmy_7";
		break;
		
		case "Jimmy_7":
			dialog.text = "Not yet. Keep your mouth shut or... well, you know me!";
			link.l1 = "Yes, I do. You've got a rotten tongue that tells everyone its secrets. Rumba was right to send you away, blabbermouth...";
			link.l1.go = "Jimmy_8_1";
			link.l2 = "Sure! I'll keep my mouth shut! And now I have to go. Farewell, Jimmy.";
			link.l2.go = "Jimmy_8_2";
		break;
		
		case "Jimmy_8_1":
			dialog.text = "What... what did you say?!";
			link.l1 = "You won't be able to tell anyone else...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Saga_KillToJimmy_kino");
		break;
		
		case "Jimmy_8_2":
			DialogExit();
			AddDialogExitQuestFunction("Saga_Jimmy_DlgExit");
		break;
// <-- Джимми 
		
//-------------------------------------------корвет Донована, абордаж-----------------------------------------
		//Донован
		case "Donovan_abordage":
			PlaySound("Voice\English\saga\Artur Donovan.wav");
			dialog.text = "Argh, you monster!";
			link.l1 = "Are you talking to yourself, Mister?! Where is Rumba?";
			link.l1.go = "Donovan_abordage_1";
		break;
		
		case "Donovan_abordage_1":
			dialog.text = "What Rumba? I don't have scum with nicknames on my ship. This is an English naval vessel!";
			link.l1 = "Don't play dumb with me, Donovan. You know perfectly well who I'm talking about. Where is the girl? Where is Helen? Answer me, you filthy bastard...";
			link.l1.go = "Donovan_abordage_2";
		break;
		
		case "Donovan_abordage_2":
			dialog.text = "Helen? There are no land whores on my ship, you piece of shit!";
			link.l1 = "No land whores? Hard to believe, since one of them is standing right in front of me at this very moment... I take it there is no point in continuing our conversation. Die, you pathetic worm!";
			link.l1.go = "Donovan_abordage_3";
		break;
		
		case "Donovan_abordage_3":
			chrDisableReloadToLocation = true;//закрыть локацию
			DialogExit();
			LAi_SetCurHPMax(npchar);
			QuestAboardCabinDialogFree();
			LAi_group_SetRelation(LAI_GROUP_BRDENEMY, LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups(LAI_GROUP_BRDENEMY, LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck(LAI_GROUP_BRDENEMY, "Saga_AfterDonovanBoarding");
			AddDialogExitQuest("MainHeroFightModeOn");
			pchar.questTemp.Saga.Takehelen = "true";//признак, что абордировали судно
		break;
		
		//наш матрос
		case "Tempsailor":
			dialog.text = "Captain, we have searched all the cabins and the cargo hold as you instructed. We found a chained girl in the cargo hold...";
			link.l1 = "What a bastard! Just as I thought... Have you unchained the girl?";
			link.l1.go = "Tempsailor_1";
		break;
		
		case "Tempsailor_1":
			dialog.text = "Certainly, Captain. She has been safely brought aboard your ship.";
			link.l1 = "Well done! Take her to my cabin, I want to speak with her once we have finished here.";
			link.l1.go = "Tempsailor_2";
		break;
		
		case "Tempsailor_2":
			dialog.text = "Aye aye, Captain!";
			link.l1 = "...";
			link.l1.go = "Tempsailor_3";
		break;
		
		case "Tempsailor_3":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "OpenTheDoors", 10.0);
		break;
		//<-- абордаж корвета Донована
		
//----------------------------------------поиск Энрике Гонсалеса, Картахена----------------------------------
		//фальшивый Гонсалес №1, дом
		case "GonsalesA":
			dialog.text = "Want something?";
			link.l1 = "Hello, Hangman! Captain Butcher sends his regards.";
			link.l1.go = "GonsalesA_1_1";
			link.l2 = "My name is Charles de Maure. I am looking for Enrique, the son of señora Gonzales, on behalf of her old friend. I believe you are him...";
			link.l2.go = "GonsalesA_2_1";
		break;
		
		case "GonsalesA_1_1":
			dialog.text = "What the hell! I don't know any Butcher!";
			link.l1 = "Come on, Henry. Tell me why Jackman's pirates are after you and I won't hurt you.";
			link.l1.go = "GonsalesA_1_2";
		break;
		
		case "GonsalesA_1_2":
			dialog.text = "Help! Pirates! Murder!";
			link.l1 = "Shut up, idiot! Half the town will come running here because of your shouting. Ah, is that what you want?!";
			link.l1.go = "GonsalesA_1_fight";
		break;
		
		case "GonsalesA_1_fight":
			DialogExit();
			SetNationRelation2MainCharacter(sti(npchar.nation), RELATION_ENEMY);
			LAi_group_MoveCharacter(NPChar, "EnemyFight");
			LAi_group_Attack(NPChar, Pchar);
			LAi_group_SetCheck("EnemyFight", "Saga_KillGonsalesA");
			AddDialogExitQuest("MainHeroFightModeOn");
			pchar.questTemp.Saga.Trap = "true";
		break;
		
		case "GonsalesA_2_1":
			dialog.text = "Hm... Sir, you must be mistaken. I grew up in a foreign family, I don't remember my birth mother. I have taken on the surname of my caretaker. I don't know my mother's name, but I doubt that it was Gonzales. You can make inquiries about me and any old resident will confirm my words. My stepfather was a famous man, he didn't have children of his own so I inherited this house and...";
			link.l1 = "I am sorry. It seems I was mistaken. Farewell.";
			if(CheckAttribute(pchar,"questTemp.Mtraxx.Cartahena.Gold")) link.l1.go = "GonsalesA_3_1";
			else link.l1.go = "GonsalesA_2_2";
		break;
		
		case "GonsalesA_2_2":
			DialogExit();
			LAi_CharacterDisableDialog(npchar);
			chrDisableReloadToLocation = false;//открыть локацию
			AddQuestRecord("Saga", "17");
		break;
		
		// belamour участвовал в событиях Картахены -->
		case "GonsalesA_3_1":
			dialog.text = "I don't think so.";
			link.l1 = "Excuse me?";
			link.l1.go = "GonsalesA_3_2";
		break;
		
		case "GonsalesA_3_2":
			dialog.text = "You know, recently our colony was viciously attacked by pirates. I believe you've heard about it? As a result of this attack, countless people suffered. I was unharmed, but my inherited business is going through tough times now. And the culprit behind all this calamity is the leader of these pirates, a scoundrel named Charlie Prince.";
			link.l1 = "I'm very sorry, but what does that have to do with me?";
			link.l1.go = "GonsalesA_3_3";
		break;
		
		case "GonsalesA_3_3":
			dialog.text = "Ha-ha, just look at this innocent lamb! I suggest you cover my losses, since you are the one responsible for them. I'll be satisfied with a sum of fifteen thousand pesos. And I'll pretend you were never in my house.";
			if (sti(pchar.money) >= 15000)
			{
				link.l1 = "How vindictive you all are... Here's your money. And remember, if anyone finds out I was in this town, I'll come back for you.";
				link.l1.go = "GonsalesA_3_4";
			}
			link.l2 = "Fifteen thousand? Hm... I don't think your life is worth that much. So, I suppose it's cheaper to just cut you down to keep you from blabbering.";
			link.l2.go = "GonsalesA_3_5";
		break;
		
		case "GonsalesA_3_4":
			DialogExit();
			LAi_CharacterDisableDialog(npchar);
			chrDisableReloadToLocation = false;//открыть локацию
			AddQuestRecord("Saga", "171");
		break;
		
		case "GonsalesA_3_5":
			dialog.text = "Guards! Pirates! Murder!";
			link.l1 = "Shut up, you idiot!";
			link.l1.go = "GonsalesA_3_6";
		break;
		
		case "GonsalesA_3_6":
			DialogExit();
			iTemp = sti(pchar.rank) + MOD_SKILL_ENEMY_RATE - 2;
			for (i=1; i<=2; i++)
			{
				sld = GetCharacter(NPC_GenerateCharacter("SpSold"+i, "sold_" + NationShortName(SPAIN) + "_" + (rand(1) + 1), "man", "man", iTemp, SPAIN, 0, true, "soldier"));
				SetFantomParamFromRank(sld, iTemp, true);         
				LAi_SetWarriorType(sld); 
				LAi_warrior_DialogEnable(sld, false);
				LAi_group_MoveCharacter(sld, "EnemyFight");
				ChangeCharacterAddressGroup(sld, pchar.location, "reload",  "reload1");
			}
			sld = GetCharacter(NPC_GenerateCharacter("SpOfficer", "off_" + NationShortName(SPAIN) + "_" + (rand(1) + 1), "man", "man", iTemp, SPAIN, 0, true, "quest"));
			FantomMakeCoolFighter(sld, 25, 100, 100, "blade_13", "pistol6", "bullet", 150);
			ChangeCharacterAddressGroup(sld, pchar.location, "reload",  "reload1");
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, "EnemyFight");
			LAi_group_MoveCharacter(NPChar, "EnemyFight");
			LAi_group_Attack(NPChar, Pchar);
			LAi_group_SetCheck("EnemyFight", "Saga_KillGonsalesAK");
			AddDialogExitQuest("MainHeroFightModeOn");
			pchar.questTemp.Saga.Trap = "true";
		break;
		// <-- участвовал в событиях Картахены
		
		// фальшивый Гонсалес №2, улицы
		case "GonsalesB":
			PlaySound("Voice\English\citizen\Pirati v Gorode-08.wav");
			dialog.text = "I see that you like my cutlass. I can sell it to you if you want. I won't ask for much, I'm dying for a drink of rum and my pockets are empty.";
			link.l1 = "And why the hell would I need it? The Forest Devil asked me to give you his regards.";
			link.l1.go = "GonsalesB_1_1";
			if (sti(pchar.money) >= 1000)
			{
				link.l2 = "Well, yes. You have got a fine cutlass indeed. How much?";
				link.l2.go = "GonsalesB_2_1";
			}
		break;
		
		case "GonsalesB_1_1":
			dialog.text = "He would have done better to give me a couple of hundred pesos instead!";
			link.l1 = "So you know Svenson?";
			link.l1.go = "GonsalesB_1_2";
		break;
		
		case "GonsalesB_1_2":
			dialog.text = "Fuck you and fuck your Svenson, send him to the devil. To the forest devil or the sea devil, I don't give a damn. If you aren't willing to help a sick man by buying his cutlass, then I will shove it right up your arse for free.";
			link.l1 = "Really? Let's see how you're going to do that, fuck-face!";
			link.l1.go = "GonsalesB_1_fight";
		break;
		
		case "GonsalesB_1_fight":
			chrDisableReloadToLocation = true;
			DialogExit();
			LAi_group_MoveCharacter(NPChar, "EnemyFight");
			LAi_group_Attack(NPChar, Pchar);
			LAi_group_SetCheck("EnemyFight", "Saga_KillGonsalesB");
			AddDialogExitQuest("MainHeroFightModeOn");
			pchar.questTemp.Saga.Trap = "true";
		break;
		
		case "GonsalesB_2_1":
			dialog.text = "I see you are a man of experience! One thousand pesos and it's yours.";
			link.l1 = "Deal!";
			link.l1.go = "GonsalesB_2_2";
		break;
		
		case "GonsalesB_2_2":
			AddMoneyToCharacter(pchar, -1000);
			GiveItem2Character(pchar, "blade_10");
			RemoveCharacterEquip(npchar, BLADE_ITEM_TYPE);
			dialog.text = "There are only two cutlasses like this in Cartagena - mine and old Alvares' from the lighthouse. But he won't sell his. He's a hypocrite, I can smell a former pirate from a mile away. The blade is some sort of talisman for him.\nIt seems the poor soul laments things he wishes he could forget. That must be why he goes to church every month, tormented by sins that won't let him sleep.";
			link.l1 = "And I see that you also have some history. It must be you Svenson was talking about. He said to give you his best regards in case I meet you in Cartagena.";
			link.l1.go = "GonsalesB_2_3";
		break;
		
		case "GonsalesB_2_3":
			dialog.text = "Svenson? Never heard of him. My name is Enrique Gallardo. But if your Svenson has a bottle of rum for me, I'm willing to be Henry for him. Call me what you like, just don't call me late for dinner. So, are we going?";
			link.l1 = "Not today. Svenson is far away, but the tavern is nearby. Your pockets aren't empty anymore, so take care, Enrique.";
			if(CheckAttribute(pchar,"questTemp.Mtraxx.Cartahena.Gold")) link.l1.go = "GonsalesB_3_1";
			else link.l1.go = "GonsalesB_2_4";
		break;
		
		case "GonsalesB_2_4":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload4_back", "none", "", "", "", 20.0);
			npchar.lifeday = 0;
			AddQuestRecord("Saga", "19");
			pchar.questTemp.Saga = "ortega";
			Saga_SetOrtega();
		break;
		
		// belamour участвовал в событиях Картахены -->
		case "GonsalesB_3_1":
			dialog.text = "They aren't completely full, though. I want more. And you will pay me.";
			link.l1 = "I'm baffled... Don't you value your life? You plan to rob me in the middle of the city? And this after you just sold me your weapon yourself?";
			link.l1.go = "GonsalesB_3_2";
		break;
		
		case "GonsalesB_3_2":
			dialog.text = "No, you will pay me yourself. And you know why?";
			link.l1 = "Curious to hear.";
			link.l1.go = "GonsalesB_3_3";
		break;
		
		case "GonsalesB_3_3":
			dialog.text = "I recognised you. I was in the dungeons for a drunken brawl in the tavern when your men burst into the prison and cut down all the guards. I managed to reach the corpse of the guard with the keys and got out onto the streets. The city was on fire, corpses, blood, and gunpowder smoke everywhere... Just like during a boarding! And through that smoke, I saw you coming out of the governor's residence. Poetic, isn't it? Yo-ho-ho, hello, Charlie Prince!";
			link.l1 = "Stop yelling like that! Knowing what you know, you especially shouldn't try to squeeze money out of me. Do you even realise what I can do to you?";
			link.l1.go = "GonsalesB_3_4";
		break;
		
		case "GonsalesB_3_4":
			dialog.text = "In the middle of the city you once robbed? You can't do anything. So, to conclude... we will do it this way: you give me... let's say, ten thousand pesos right now. I think that will be enough for a month. And you go your way! Whether to your beloved Henry, to Svenson, or to any other devil of your choice... And if you don't, I just need to shout, and they will drag you into a specially prepared personal chamber filled with torture tools.";
			if (sti(pchar.money) >= 10000)
			{
				link.l1 = "Damn it, take your ten thousand and get out of my sight! And, God forbid I see you again.";
				link.l1.go = "GonsalesB_3_5";
			}
			link.l2 = "That's it, I've had enough of this. Your weapon is mine, so you don't stand a chance, scum.";
			link.l2.go = "GonsalesB_3_7";
			link.l3 = "Haha, you're good! You know what? I would have slit anyone else from belly to throat by now. But people like you, I need. How about this: I give you ten thousand pesos, return your 'Hanged Man', and throw in an extra three thousand every month - should be enough for booze - and you'll become a boarder on my ship.";
			link.l3.go = "GonsalesB_3_9";
		break;
		
		case "GonsalesB_3_5":
			dialog.text = "Alright, alright, I'm already going! Good luck with your search, Charlie Prince!";
			link.l1 = "...";
			link.l1.go = "GonsalesB_3_6";
		break;
		
		case "GonsalesB_3_6":
			AddMoneyToCharacter(pchar, -10000);
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload4_back", "none", "", "", "", 20.0);
			npchar.lifeday = 0;
			AddQuestRecord("Saga", "191");
			pchar.questTemp.Saga = "ortega";
			Saga_SetOrtega();
		break;
		
		case "GonsalesB_3_7":
			dialog.text = "Guards! Guards!!! It's Charlie Prince!!!";
			link.l1 = "You bastard!";
			link.l1.go = "GonsalesB_3_8";
		break;
		
		case "GonsalesB_3_8":
			DialogExit();
			LAi_SetActorTypeNoGroup(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload4_back", "none", "", "", "", 20.0);
			LAi_group_AttackGroup("Spain_citizens", LAI_GROUP_PLAYER);
			npchar.lifeday = 0;
			AddQuestRecord("Saga", "192");
			pchar.questTemp.Saga = "ortega";
			Saga_SetOrtega(); 
		break;
		
		case "GonsalesB_3_9":
			dialog.text = "Are you suggesting that I join your crew?";
			link.l1 = "Exactly. But this is a one-time offer. So, what do you say? Agree, or I'll spill your guts. You don't really think you can blackmail Charlie Prince that easily, do you?";
			link.l1.go = "GonsalesB_3_10";
		break;
		
		case "GonsalesB_3_10":
			if(GetSummonSkillFromName(pchar, SKILL_LEADERSHIP) > 34 && makeint(pchar.reputation.nobility) < 48)
			{
				dialog.text = "Devil! Charlie Prince himself is offering me a place in his crew! Damn you, I agree! Give me back my blade and ten thousand pesos. Never thought it would turn out this way!";
				link.l1 = "Here. And keep your mouth shut: no one in this city needs to know who I am, understood?";
				link.l1.go = "GonsalesB_3_11";
				break;
			}
			if(makeint(pchar.reputation.nobility) > 47)
			{
				dialog.text = "Nope. You may be a decent captain, but it seems to me you're a bit too uptight. Yes, you taught the Spaniards to fear you once, by pulling off a daring raid on Cartagena – but all that was only with the help of Marcus Tyrex. You don't have the guts to do honest pillaging on your own. So, fork over the dough!";
			}
			if(GetSummonSkillFromName(pchar, SKILL_LEADERSHIP) < 35)
			{
				dialog.text = "No. You're certainly a notorious pirate, but as a captain, you don't seem that impressive. You only managed to plunder the colony with the help of Marcus Tyrex – you wouldn't even dare to board a dilapidated sloop on your own. So, fork over the dough!";
			}
			if (sti(pchar.money) >= 10000)
			{
				link.l1 = "Damn it, take your ten thousand and get out of my sight! And, God forbid, I see you again.";
				link.l1.go = "GonsalesB_3_5";
			}
			link.l2 = "That's it, I've had enough of this. Your weapon is mine, so you don't stand a chance, scum.";
			link.l2.go = "GonsalesB_3_7";
		break;
		
		case "GonsalesB_3_11":
			dialog.text = "Understood, I'm not a fool.";
			link.l1 = "Good.";
			link.l1.go = "GonsalesB_3_12";
		break;
		
		case "GonsalesB_3_12":
			DialogExit();
			AddMoneyToCharacter(pchar, -10000);
			LAi_RemoveLoginTime(npchar);
			npchar.quest.OfficerPrice = 3000;
			npchar.reputation.nobility = 30;
			npchar.dialog.FileName = "Enc_Officer_dialog.c";
			npchar.loyality = MAX_LOYALITY;
			GiveItem2Character(npchar, "blade_10");
			EquipCharacterByItem(npchar, "blade_10");
			TakeItemFromCharacter(pchar, "blade_10");
			Pchar.questTemp.HiringOfficerIDX = GetCharacterIndex(npchar.id);
			AddQuestRecord("Saga", "193");
			pchar.questTemp.Saga = "ortega";
			Saga_SetOrtega(); 
			AddDialogExitQuestFunction("LandEnc_OfficerHired");
		break;
		// <-- участвовал в событиях Картахены
		
		//настоящий Гонсалес - Ортега, маяк
		case "Ortega":
			dialog.text = "I am not expecting any guests, not today nor any other day. What do you want?";
			link.l1 = "Hello, Hangman. The Forest Devil sent me. It's fortunate I found you before Jackman's lads. His men are searching for you all over the Caribbean. Lucky for you, Henry, only Svenson knows where you were born. He asked me to warn you.";
			link.l1.go = "Ortega_1";
		break;
		
		case "Ortega_1":
			dialog.text = "I see now... So, it seems that Svenson is still alive and hasn't forgotten about his old friend. A lot of blood has flowed since I first saw him as a rookie standing aboard a damaged brig... Life has gone by too fast and I don't have much time left\nI wanted to die of natural causes on this wasteland, away from mankind and close to the sea. But if Jackman is back in the Caribbean, he won't leave me alone. It was not my fault, but I owe his master. Anyway, who will believe me now.\nI am afraid not of death, but of pain. And Jackman knows a lot about pain. The thought of it alone makes my heart stop and everything is going dark.";
			link.l1 = "Butcher was hanged twenty years ago, so you don't have to repay your debts to anyone. You can pass your debt to me if you're afraid of Jackman. I think you'll meet him sooner or later anyway.";
			link.l1.go = "Ortega_2";
		break;
		
		case "Ortega_2":
			dialog.text = "It is not easy to hang people like Butcher. The former executioner of St. John's could tell you many interesting stories about the dead who returned from hell. And Jacob was well taught by his captain, so I am not sure whom I fear most.";
			link.l1 = "Why does Jackman need you?";
			link.l1.go = "Ortega_3";
		break;
		
		case "Ortega_3":
			dialog.text = "I had to deliver gold to a widow as payment for keeping Butcher's daughter safe. Why are you looking at me like that? Yes, she was born not long before the 'Neptune' was sunk. He couldn't come back for her in time, so he sent me to take care of the baby and her caretaker.";
			link.l1 = "Was Gladys Chandler the caretaker's name?";
			link.l1.go = "Ortega_4";
		break;
		
		case "Ortega_4":
			dialog.text = "Don't play the fool. If Jackman is looking for me, then it's because he needs the Butcher's daughter. You must already know that he is searching for a woman from Belize named Gladys and her foster child. Be honest with me and I might trust you.";
			link.l1 = "What were you supposed to tell Gladys?";
			link.l1.go = "Ortega_5";
		break;
		
		case "Ortega_5":
			dialog.text = "Nothing. I was supposed to show her Butcher's ring, that's how she would know I was a courier sent by the captain. I also had to give her a chest of doubloons for the baby's needs. I had to kill a bastard to take the ring. It made me prolong my stay on Antigua by another month.\nAnd when I finally reached Belize, Gladys was already gone and the city had been burnt and plundered by the Spanish. She managed to sell her house and run away with her new lover and baby Helen. I hope she took care of her and didn't sell the girl to the gypsies or to a brothel.";
			link.l1 = "The Butcher's daughter's name was Helen, right?";
			link.l1.go = "Ortega_6";
		break;
		
		case "Ortega_6":
			dialog.text = "Exactly. In honour of Butcher's mother. If you aren't afraid of the living dead and pirates staring at you with dead eyes, then I can give you the ring and gold. I never touched it. I was dying of starvation, but I didn't touch it. Do with them what you will. And in return I ask y...";
			link.l1 = "What is happening, Henry?!";
			link.l1.go = "Ortega_7";
		break;
		
		case "Ortega_7":
			dialog.text = "You... y... I as...k.... oh!";
			link.l1 = "No!";
			link.l1.go = "Ortega_8";
		break;
		
		case "Ortega_8":
			DialogExit();
			LAi_SetImmortal(npchar, false);
			LAi_KillCharacter(npchar);
			AddQuestRecord("Saga", "20");
			pchar.questTemp.Saga = "svenson1";
			PlaySound("interface\important_item.wav");
			GiveItem2Character(pchar, "chest");
			GiveItem2Character(pchar, "bucher_ring"); //перстень Бучера
			//таймер на возврат смотрителя
			SetFunctionTimerCondition("Saga_LightmanReturn", 0, 0, 10, false);
			//ставим прерывания, если ГГ наследил в городе
			if (CheckAttribute(pchar, "questTemp.Saga.Trap"))
			{
				pchar.quest.Saga_Trap.win_condition.l1 = "location";
				pchar.quest.Saga_Trap.win_condition.l1.location = "Mayak11";
				pchar.quest.Saga_Trap.function = "Saga_CreateTrapBandos";
				TraderHunterOnMap(true);
			}
			AddCharacterExpToSkill(pchar, "Sneak", 50);//скрытность
			
			DeleteAttribute(pchar, "questTemp.HelenDrinking.Dialogs");
			//pchar.questTemp.HelenDrinking = "end_henry";
		break;
		
		//бандиты в поисках Гонсалеса, маяк
		case "saga_trap":
			dialog.text = "A-ah, there is our curious friend! Have you found Gonzales at last? Well done, you have brought us to him... we don't need you anymore. Lads, kill this jester!";
			link.l1 = "Time to die, crab giblets!";
			link.l1.go = "saga_trap_1";
		break;
		
		case "saga_trap_1":
			DialogExit();
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);//разрешить драться
			int n = makeint(MOD_SKILL_ENEMY_RATE/3);
			for (i=1; i<=3+n; i++)
			{	
				sld = characterFromId("sagatrap_sold_"+i);
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "EnemyFight");
			}
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("EnemyFight", "OpenTheDoors");
			AddDialogExitQuest("MainHeroFightModeOn");	
		break;
		//<-- поиск Гонсалеса, Картахена
		
//--------------------------------------------НПС по квесту Возвращение барона---------------------------------
		
		// доминиканский вождь
		case "DominicaHead":
			dialog.text = "U-ah! U-ah! Great Kukulcan demands a new victim! O-eh! The spirit of a mighty warrior from the past has come to our village to be sacrificed to great Kukulcan! O-eh! All bow to the mighty warrior spirit!";
			link.l1 = "(faintly) What the hell, where am I?";
			link.l1.go = "DominicaHead_1";
			NextDiag.TempNode = "DominicaHead";
			if (CheckCharacterItem(pchar, "Ultimate_potion"))
			{
				pchar.systeminfo.NoNotifications = true;
				RemoveItems(pchar, "Ultimate_potion", 1);
				DeleteAttribute(pchar,"systeminfo.NoNotifications");
				notification("A Comanche potion is used", "None");
				LAi_SetCurHPMax(PChar);
				AddCharacterHealth(pchar, 50);
				DeleteAttribute(pchar, "chr_ai.poison");
				notification("You are feeling that your health is restored!", "None");
				//Log_Info("A Comanche potion is used");
				//Log_Info("You are feeling that your health is restored!");
				//PlaySound("Ambient\Tavern\glotok_001.wav");
				PlaySound("Ambient\Horror\Fear_breath_01.wav");
			}
		break;
		
		case "DominicaHead_1":
			dialog.text = "O-eh! Great warrior wishes to be devoured by great Kukulcan! Sun rising, shadows shorten! Great Kukulcan will soon awaken! We bring you to him, oh mighty warrior, and you shall continue passing through the land of the ancestors!";
			link.l1 = "(faintly) Nonsense... Kukulcan again? Hey, chief, I come in peace! I am here to...";
			link.l1.go = "DominicaHead_2";
		break;
		
		case "DominicaHead_2":
			dialog.text = "O-eh! The great warrior says he wishes to be sacrificed to Kukulcan at once. Oh, great warrior! We go to Kukulcan now and await his coming! Warriors! It is a great honour for us to bring the ancestor's spirit to Kukulcan!";
			link.l1 = "(faintly) Idiot... Fine, I have to go with them. It's good that they haven't attacked me yet, I wouldn't be able to defend myself in this thing...";
			link.l1.go = "DominicaHead_3";
		break;
		
		case "DominicaHead_3":
			DialogExit();
			LAi_SetActorType(pchar);
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocator(npchar, "reload", "reload1_back", "Saga_DominicaDollyReload", -1);
			LAi_ActorFollow(pchar, npchar, "", -1);
			for (i=2; i<=10; i++)
			{
				sld = characterFromId("Dominica_ind_"+i);
				LAi_SetActorType(sld);
				LAi_ActorFollow(sld, npchar, "", -1);
			}
		break;
		
		case "DominicaHead_4":
			dialog.text = "We come to Kukulcan, great ancestral spirit. Soon the sun will go down, shadows will grow, and Kukulcan will visit us. Wait, great warrior...";
			link.l1 = "(faintly) Now I see, Indian war chief...";
			link.l1.go = "DominicaHead_5";
		break;
		
		case "DominicaHead_5":
			DialogExit();
			bDisableCharacterMenu = true;//лочим Ф2
			AddQuestRecord("BaronReturn", "7");
			LAi_SetActorType(pchar);
			DoQuestCheckDelay("Saga_DominicaDollyWait", 5.0);
			pchar.questTemp.Saga.BaronReturn = "third_teleport";
		break;
		
		case "DominicaHead_6":
			dialog.text = "Kukulcan lives! Kukulcan is with us! The great warrior can be sacrificed to Kukulcan! Warriors, bow before the great ancestral spirit!";
			link.l1 = "(faintly) Stay away, Chief. I'll do it myself. It's not my first time...";
			link.l1.go = "DominicaHead_7";
		break;
		
		case "DominicaHead_7":
			DialogExit();
			bDisableCharacterMenu = false;//разлочим Ф2
			AddQuestRecord("BaronReturn", "8");
			for (i=2; i<=10; i++)
			{
				sld = characterFromId("Dominica_ind_"+i);
				LAi_SetActorType(sld);
			}
		break;
		
//----------------------------------------НПС по квесту Искушение Барбазона----------------------------------
		// капитан рыболовного баркаса, стыривший шелк, море
		case "BarbCapBarkas":
			dialog.text = "How can I help you, Mynheer?";
			link.l1 = "Well, well...  tell me, pal, what are you doing here?";
			link.l1.go = "BarbCapBarkas_1";
		break;
		
		case "BarbCapBarkas_1":
			dialog.text = "What am I doing here? I am a fisherman and I am fishing here. And why the hell are you interrogating me in such a tone of voice?";
			link.l1 = "Don't lie to me, pal. Perhaps you really are a fisherman, but you haven't been fishing here. Valuable ship silk was thrown into the sea, right at this spot. And your presence alone looks quite suspicious to me.";
			link.l1.go = "BarbCapBarkas_2";
		break;
		
		case "BarbCapBarkas_2":
			dialog.text = "What nonsense? What silk are you even talking about?";
			link.l1 = "What silk? The Chinese one... Don't play the fool! Listen to me now: either you immediately fetch the silk from your cargo hold and hand it over to me, or I will take it myself. But first, my boarding party will deal with you and your crew. So? Shall I call my men?";
			link.l1.go = "BarbCapBarkas_3";
		break;
		
		case "BarbCapBarkas_3":
			dialog.text = "No! Mynheer, I didn't know... Those bales were just floating around, so I decided...";
			link.l1 = "Bring the silk to my ship. Make haste!";
			link.l1.go = "BarbCapBarkas_4";
		break;
		
		case "BarbCapBarkas_4":
			dialog.text = "Yes, yes, of course. We'll do that at once, just don't take my boat!";
			link.l1 = "Move your arse! I don't have much time...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Saga_BarbBarkasSilk");
		break;
		
		case "BarbCapBarkas_5":
			dialog.text = "Here, we've brought everything we found - all nine bales. This is everything, I swear...";
			link.l1 = "Fine. You can continue your fishing, but don't set your sights on other people's belongings in the future!";
			link.l1.go = "BarbCapBarkas_6";
		break;
		
		case "BarbCapBarkas_6":
			DialogExit();
			npchar.DontDeskTalk = true;
			npchar.lifeday = 0;
			LAi_SetStayType(npchar);
			pchar.quest.BarbBarkas_Sink.over = "yes"; //снять прерывание
			pchar.quest.BarbBarkas_Abordage.over = "yes"; //снять прерывание
			NextDiag.CurrentNode = "BarbCapBarkas_7";
			AddQuestRecord("BarbTemptation", "6");
			pchar.questTemp.Saga.BarbTemptation = "give_silk";
			AddCharacterExpToSkill(pchar, "Fortune", 100);//везение
			AddCharacterExpToSkill(pchar, "Sneak", 50);//скрытность
		break;
		
		case "BarbCapBarkas_7":
			dialog.text = "You have already got what you wanted. I don't have anything left! What more do you want?";
			link.l1 = "Relax, mate. I'm leaving.";
			link.l1.go = "exit";
			NextDiag.TempNode = "BarbCapBarkas_7";
		break;
		
		// Моррель, капитан потопленного судна, тюрьма
		case "Morelle":
			dialog.text = "If you are sent by Barbazon, then tell him that I don't want to leave the prison myself. I'd rather wait for the trial. Even Dutch hemp around my neck is better than his kindness.";
			link.l1 = "Don't get ahead of yourself. Your navigator told Jacques that you are dead. He sent me to find the silk you've thrown into the sea. How much of it was on your brigantine?";
			link.l1.go = "Morelle_1";
		break;
		
		case "Morelle_1":
			dialog.text = "It was my fault, damn it. The courier brought nine bales of silk for Barbazon. I ordered him to be tracked down. He made a fuss, so we had to cut his throat. He had an extra three bales in his stash, which I took for myself and hid in my own stash. But it seems we attracted unwanted attention.\nThey found us quickly, and a Dutch patrol was waiting for the 'Salt Dog' in open waters. We failed to escape. You can take the silk for yourself if you don't tell Barbazon about me. The stash is at Grand Case Beach, between the stones near the dead end. It's unlikely I'll need it again.";
			link.l1 = "Fine. I won't tell Barbazon that you are still alive. If what they say about him is true, then it's better for you to be hanged by the Dutch. Or perhaps you'll be lucky and they'll condemn you to penal servitude.";
			link.l1.go = "Morelle_2";
		break;
		
		case "Morelle_2":
			DialogExit();
			LAi_CharacterDisableDialog(npchar);
			npchar.lifeday = 0;
			// тайник - модель
			//int m = Findlocation("Shore40");
			//locations[m].models.always.Roll = "Roll_of_rolls";
			//Locations[m].models.always.Roll.locator.group = "quest";
			//Locations[m].models.always.Roll.locator.name = "quest1";
			pchar.quest.Saga_MorelGoods.win_condition.l1 = "locator";
			pchar.quest.Saga_MorelGoods.win_condition.l1.location = "Shore40";
			pchar.quest.Saga_MorelGoods.win_condition.l1.locator_group = "quest";
			pchar.quest.Saga_MorelGoods.win_condition.l1.locator = "quest1";
			pchar.quest.Saga_MorelGoods.function = "Saga_SetMorelGoods";
			AddCharacterExpToSkill(pchar, "Fortune", 200);//везение
			AddCharacterExpToSkill(pchar, "Sneak", 200);//скрытность
		break;
		
		// Валет, брат Джекмана в Капстервиле
		case "valet":
			dialog.text = "I am waiting for the man who knows when the hunt for the white shark will begin.";
			link.l1 = "The hunt has begun.";
			link.l1.go = "valet_1";
		break;
		
		case "valet_1":
			dialog.text = "Finally! Now listen carefully. You will have to visit Marcus Tyrex in La Vega and tell him that the brigantine 'Separator' was attacked near Turks Island and is now hiding at the Southern Bay. Her captain is gravely wounded and the crew is waiting for help. You have picked up a sailor from the 'Separator' and he told you all about it. He is dead now. That is all you know. Got it?";
			link.l1 = "And why do you need me for that? I waited too long just for that...";
			link.l1.go = "valet_2";
		break;
		
		case "valet_2":
			dialog.text = "You are being paid to do your work and not to ask questions. You are right, though. I have to warn you that Tyrex won't let you go until he is sure you are telling the truth. But once he finds out everything, he will pay you well. If he is able to do that...";
			link.l1 = "You pull the wool over my eyes, Mister... Why don't you want to receive his thanks yourself?";
			link.l1.go = "valet_3";
		break;
		
		case "valet_3":
			dialog.text = "Caramba! I don't like your curiosity! Your babble will lead you straight to an early grave one day.";
			link.l1 = "Yeah, sometimes I am unbearable. Especially when I see that someone is about to pull a fast one on me. No, pal, now we are going to play by my rules. Who is your master, god damn it? Answer, or I will make you!";
			link.l1.go = "valet_4";
		break;
		
		case "valet_4":
			dialog.text = "You... bastard! Barbazon will pay for this, and your life is going to end, shit-eater!";
			link.l1 = "Ha! I expected this. Get ready, scoundrel!";
			link.l1.go = "valet_5";
		break;
		
		case "valet_5":
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);//разрешить драться
			chrDisableReloadToLocation = true;//закрыть локацию
			DialogExit();
			LAi_SetWarriorType(npchar);
			LAi_group_MoveCharacter(npchar, "EnemyFight");
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("EnemyFight", "Saga_ValetDie");
			AddDialogExitQuest("MainHeroFightModeOn");	
		break;
		
		case "vensan":
			// Addon 2016-1 Jason пиратская линейка патч 17/1
			if (CheckAttribute(pchar, "questTemp.Mtraxx") && pchar.questTemp.Mtraxx == "full_complete_end")
			{
				dialog.text = "Charlie Prince? What are you doing here? A-argh, damn it, it was you! This is all your doing!";
				link.l1 = "Relax, Bernie. I am on your side. The ambush has been eliminated, you and your vessel are safe.";
				link.l1.go = "vensan_8";
			}
			else
			{
				dialog.text = "Who are you, damn it? How did you get here? Leave now, my ship is rigged with explosives and the bastards on the shore can blow it up with a single shot.";
				link.l1 = "Don't worry, Mister. The ambush on the shore has been dealt with. Your ship is safe now, as long as you don't light a pipe on deck, of course. What is your name?";
				link.l1.go = "vensan_1";
			}
		break;
		
		case "vensan_1":
			dialog.text = "Vincent. Bernard Vincent. And what's your name?";
			link.l1 = "Captain "+GetFullName(pchar)+". I will cut those ropes and set you free...";
			link.l1.go = "vensan_2";
		break;
		
		case "vensan_2":
			LAi_SetStayType(npchar);
			dialog.text = "Oh... my gratitude. How can I ever thank you?";
			link.l1 = "It is not over yet, sir. Is anyone from your crew still alive?";
			link.l1.go = "vensan_3";
		break;
		
		case "vensan_3":
			dialog.text = "Three dozen of my men are locked in the cargo hold...";
			link.l1 = "Release them and get away from here immediately. ";
			link.l1.go = "vensan_4";
		break;
		
		case "vensan_4":
			dialog.text = "But...";
			link.l1 = "Don't waste time, Bernard. You can thank me later in La Vega... Tyrex might thank me as well.";
			link.l1.go = "vensan_5";
		break;
		
		case "vensan_5":
			dialog.text = "So, you aren't here by accident? You knew everything?";
			link.l1 = "Yes, I knew. I managed to uncover Jackman's scheme and his plans to kill Marcus. Oh, ask Tyrex to sit still, his meddling might scare Jackman off.";
			link.l1.go = "vensan_6";
		break;
		
		case "vensan_6":
			dialog.text = "I will tell him for sure! Are you leaving now?";
			link.l1 = "Yes. And you should hurry up as well.";
			link.l1.go = "vensan_7";
		break;
		
		case "vensan_7":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "goto", "goto2", "none", "", "", "", 5.0);
			Ship_SetTaskRunaway(SECONDARY_TASK, GetCharacterIndex("Cap_Vensan"), GetMainCharacterIndex());
			pchar.questTemp.Saga.BarbTemptation.Vensan_free = "true";
			if (!CheckAttribute(pchar, "questTemp.Saga.BarbTemptation.vensan_attack"))
			{
				if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1) sld = characterFromId("Mary");
				else sld = characterFromId("Helena");
				sld.dialog.currentnode = "sea_bomb"; 
				LAi_SetActorType(sld);
				ChangeCharacterAddressGroup(sld, pchar.location, "goto", "goto6");
				LAi_ActorDialog(sld, pchar, "", -1, 0);
			}
			AddCharacterExpToSkill(pchar, "Leadership", 100);//авторитет
			AddCharacterExpToSkill(pchar, "Fortune", 100);//везение
			AddCharacterExpToSkill(pchar, "Sneak", 50);//скрытность
			sld = characterFromId("Cap_Vensan");
			sld.lifeday = 1;
			sld.DontDeskTalk = true;
		break;
		
		// Addon 2016-1 Jason пиратская линейка патч 17/1
		case "vensan_8":
			dialog.text = "Really? Look, I'm sorry, brother...";
			link.l1 = "Forget it. Just let me cut the ropes and set you free.";
			link.l1.go = "vensan_9";
		break;
		
		case "vensan_9":
			LAi_SetStayType(npchar);
			dialog.text = "Fuck... I can't feel my hands...";
			link.l1 = "Bernie, are there any more survivors on the ship?";
			link.l1.go = "vensan_10";
		break;
		
		case "vensan_10":
			dialog.text = "Thirty men are locked in the cargo hold...";
			link.l1 = "Release them and get the hell out of here. Now!";
			link.l1.go = "vensan_11";
		break;
		
		case "vensan_11":
			dialog.text = "But...";
			link.l1 = "Sail to La Vega at once. Tell Marcus everything about this mess in full detail.";
			link.l1.go = "vensan_12";
		break;
		
		case "vensan_12":
			dialog.text = "Did Marcus send you?";
			link.l1 = "He didn't. I managed to uncover one bastard's plot. He planned to eliminate Marcus through this intrigue. Ask him to stay put and not interfere for now... I will explain everything to him myself, later. And please tell him to stop being angry with me.";
			link.l1.go = "vensan_7";
		break;
		
 //--------------------------------------НПС по Завещанию Шарпа--------------------------------------------------
		// Устрица, Поль Моллиган
		case "molligan":
			dialog.text = "What do you want on my ship, sir?";
			link.l1 = "Good day, Paul. Your name is Paul Molligan, isn't it?";
			link.l1.go = "molligan_0";
		break;
		
		case "molligan_0":
			dialog.text = "Yes, that's me. How can I help you?";
			link.l1 = "My name is "+GetFullName(pchar)+" and Jan Svenson has sent me.";
			link.l1.go = "molligan_1";
		break;
		
		case "molligan_1":
			dialog.text = "Jan? A-ah, I remember you. Of course! You've been visiting his house quite often lately. So, what does Jan want from me?";
			link.l1 = "You were in such a rush to sail away from Blueweld. Jan wanted to load your ship with an extra two hundred centners of mahogany to deliver them to Lord Willoughby at Bridgetown. Get your vessel ready, my men will put the mahogany into your cargo hold.";
			link.l1.go = "molligan_2";
		break;
		
		case "molligan_2":
			dialog.text = "Mahogany? Did Jan say that? Hm. And why won't you deliver it to Barbados yourself? Why me?";
			link.l1 = "Because you are sailing there and I am not. I have an urgent assignment from Svenson, so I can't waste my time sailing to Bridgetown as well. Besides, Jan doesn't trust me to do business with Lord Willoughby and he wants you to handle it. I'm sorry. Now let's get on with the loading, I have to go.";
			link.l1.go = "molligan_3";
		break;
		
		case "molligan_3":
			dialog.text = "Listen, I haven't got any free space in my cargo hold. I won't be able to do what Jan asks of me, though I'd like to.";
			link.l1 = "No room? Strange... Jan told me you had some free space.";
			link.l1.go = "molligan_4";
		break;
		
		case "molligan_4":
			dialog.text = "It's true, but Jan didn't know that I've equipped the 'Oyster' with heavier cannons. I can't load any more cargo than I already have. So deliver the wood to Barbados yourself, eh pal? Tell Jan that I couldn't do it. Dealing with Willoughby is easy: just see him, give him the cargo and take your receipt. Easy enough.";
			link.l1 = "Hm. This wasn't my plan... Let's check your cargo hold, shall we? My quartermaster is very skilled at packing things, he'll be able to fit the goods into your hold and even leave you with some free space...";
			link.l1.go = "molligan_5";
		break;
		
		case "molligan_5":
			dialog.text = "Pal, I can't take on any more goods. Do you want me to throw away my cannons and leave the 'Oyster' unprotected?";
			link.l1 = "Well, if you're this sure... But Jan won't like it, bear that in mind!";
			link.l1.go = "molligan_6";
		break;
		
		case "molligan_6":
			dialog.text = "I'll explain it to Svenson, don't worry. After all, it's his fault—he didn't ask me about my ship's tonnage.";
			link.l1 = "Eh, now I'll have to sail with those logs all the way to Barbados, damn it... Farewell, pal.";
			link.l1.go = "molligan_7";
		break;
		
		case "molligan_7":
			DialogExit();
			// ставим проверку скрытности
			if (GetSummonSkillFromName(pchar, SKILL_SNEAK) > (10+hrand(50)))
			{
				pchar.questTemp.Saga.Molligan.friend = "true"; // будет шанс критического залпа картечью
				sTemp = "The scoundrel is still not suspecting a thing. I should get closer and shoot at him with grapeshot. A sudden strike will always win in any battle. ";
				log_Testinfo("Friends");
				AddCharacterExpToSkill(pchar, "Fortune", 200);//везение
				AddCharacterExpToSkill(pchar, "Sneak", 300);//скрытность
			}
			else
			{
				pchar.questTemp.Saga.Molligan.enemy = "true"; // нападет
				sTemp = "";
				log_Testinfo("Enemies");
				AddCharacterExpToSkill(pchar, "Sneak", 150);//скрытность
			}
			AddQuestRecord("Testament", "7");
			AddQuestUserData("Saga", "sText", sTemp);
			NextDiag.CurrentNode = "molligan_8";
			npchar.DontDeskTalk = true; // patch-5
		break;
		
		case "molligan_8":
			dialog.text = "We are clear, aren't we?";
			link.l1 = "Yes, yes. I am going to my ship.";
			link.l1.go = "exit";
			NextDiag.TempNode = "molligan_8";
		break;
		
	//-----------------------------------------НПС по Теням прошлого--------------------------------------------
		// Джим Бенсон, плешивая мэгги
		case "benson":
			dialog.text = "What do you want from me? I don't care for gossip or gambling. And I drink my rum alone. Besides, I'm in a foul mood after my last voyage.";
			link.l1 = "And what remarkable thing happened during your last voyage?";
			link.l1.go = "benson_1";
		break;
		
		case "benson_1":
			dialog.text = "One good man trusted me and I threw him overboard because my crew demanded it.";
			link.l1 = "And what was his crime?";
			link.l1.go = "benson_2";
		break;
		
		case "benson_2":
			dialog.text = "I am a newcomer and don't know many people here. That's why I hired that good-hearted fat man as a surgeon without knowing about his past. Pirates have been chasing us since we left Barbados. Why would they want my eggshell?\nWe barely managed to escape, thanks to a strong gale. Had a drink to mark the occasion. And the fat fool could think of nothing better than to tell everyone that the pirates were most likely after him because he is a former executioner and knows things he ought not to know.\nOf course, my crew got really angry. I mean, really?! An executioner on board, serving as a surgeon! And no one wanted to tangle with pirates either... So I had to put the poor soul ashore. It's all his fault, he just had to open his mouth. But I feel sorry for the bumpkin, he was an excellent physician. It took him only a minute to cure my hangover.";
			link.l1 = "Damn it! Your doctor's name was Raymond Baker, right?";
			link.l1.go = "benson_3";
		break;
		
		case "benson_3":
			dialog.text = "Yes. Exactly. And how do you know? Were you following me?";
			link.l1 = "No, that wasn't me. I just need that man, he is a great doctor. Where did you put him ashore?";
			link.l1.go = "benson_4";
		break;
		
		case "benson_4":
			dialog.text = "Latitude 15 degrees 28' north, longitude 63 degrees 28' west. Hurry up, Mister! He must still be alive and you will take the blame off me if you save him!";
			link.l1 = "I am raising my anchors already!";
			link.l1.go = "benson_5";
		break;
		
		case "benson_5":
			DialogExit();
			NextDiag.CurrentNode = "benson_6";
			AddQuestRecord("Shadows", "3");
			npchar.lifeday = 0;
			bQuestDisableMapEnter = false;
			pchar.quest.Saga_Shadows_Baker.win_condition.l1 = "location";
			pchar.quest.Saga_Shadows_Baker.win_condition.l1.location = "Dominica";
			pchar.quest.Saga_Shadows_Baker.function = "Saga_SetBakerBoat";
			DeleteAttribute(pchar, "Cheats.SeaTeleport");
		break;
		
		case "benson_6":
			dialog.text = "Captain, hurry up! He must still be alive!";
			link.l1 = "Yes, yes, I am on my way...";
			link.l1.go = "exit";
			NextDiag.TempNode = "benson_6";
		break;
		
	//---------------------------------------бандиты у джекмановского рудника-------------------------------
		case "mine_bandit":
			locCameraFromToPos(6.21, 2.31, 8.46, true, -2.26, -1.10, 4.99);
			if (CheckAttribute(pchar, "questTemp.Saga.MineAttack"))
			{
				dialog.text = "Hey! Stay right there! Don't move. This territory is secured!";
				link.l1 = "Don't be too harsh, mate! Friends! Jackman sent us. We need to get to the mine. Master's orders...";
				link.l1.go = "mine_attack";
				break;
			}
			if (npchar.quest.meeting == "0")
			{
				dialog.text = "Hey! Stay right there! Don't move. This territory is secured!";
				link.l1 = "Hm. But I want to go through... Why the hell are you stopping me?";
				link.l1.go = "mine_bandit_1";
				npchar.quest.meeting = "1";
			}
			else
			{
				dialog.text = "A-ah, you again? I see you don't get it... Lads, fire!!";
				link.l1 = "...";
				link.l1.go = "mine_bandit_fire";
			}
		break;
		
		case "mine_bandit_0":
			dialog.text = "Come on, move along!";
			link.l1 = "Fine...";
			link.l1.go = "exit";
			NextDiag.TempNode = "mine_bandit_0";
		break;
		
		case "mine_bandit_1":
			dialog.text = "Because the mine behind me is private property and I am here to stop any stranger like you from passing. You'd better turn around and leave this place, stranger. Our cannons are loaded with grapeshot; just one more step and you'll be turned into a wet puddle.";
			link.l1 = "Heh, I see. Your mine is well guarded. Fine, I am leaving.";
			link.l1.go = "mine_bandit_exit";
			link.l2 = "You bastard! Well, we'll see who ends up as a puddle!";
			link.l2.go = "mine_bandit_2";
		break;
		
		case "mine_bandit_exit":
			DialogExit();
			LAi_SetGuardianType(npchar);
			LAi_group_MoveCharacter(npchar, "PIRATE_CITIZENS");
			chrDisableReloadToLocation = false;//открыть локацию
			DoQuestReloadToLocation("Mine_02", "reload", "reload3", "");
		break;
		
		case "mine_bandit_2":
			dialog.text = "I gave you a chance... Lads, fire!!";
			link.l1 = "...";
			link.l1.go = "mine_bandit_fire";
		break;
		
		case "mine_bandit_fire":
			DialogExit();
			DoQuestCheckDelay("Saga_MineBanditsFire", 1.5);
		break;
		
		case "mine_banditx":
			locCameraFromToPos(6.21, 2.31, 8.46, true, -2.26, -1.10, 4.99);
			if (CheckAttribute(pchar, "questTemp.Saga.MineAttack"))
			{
				dialog.text = "Hey! Get lost! This area is secured!";
				link.l1 = "Hey, relax, pal! Jackman sent us. We need to get to the mine. Master's orders...";
				link.l1.go = "mine_attackx";
				break;
			}
			if (npchar.quest.meeting == "0")
			{
				dialog.text = "Hey! Get lost! This territory is secured!";
				link.l1 = "Hm. And what is there?";
				link.l1.go = "mine_banditx_1";
				npchar.quest.meeting = "1";
			}
			else
			{
				dialog.text = "A-ah, you again? I see you don't get it... Lads, fire!!";
				link.l1 = "...";
				link.l1.go = "mine_banditx_fire";
			}
		break;
		
		case "mine_banditx_1":
			dialog.text = "None of your business. Get lost or we'll shoot you, I swear!";
			link.l1 = "Calm down. I am leaving.";
			link.l1.go = "mine_banditx_exit";
			link.l2 = "You bastard! Well, we'll see who shoots whom!";
			link.l2.go = "mine_banditx_2";
		break;
		
		case "mine_banditx_exit":
			DialogExit();
			LAi_SetGuardianType(npchar);
			LAi_group_MoveCharacter(npchar, "PIRATE_CITIZENS");
			DoQuestReloadToLocation("Mine_04", "reload", "reload3", "");
		break;
		
		case "mine_banditx_2":
			dialog.text = "I gave you a chance... Muskets ready! Fire!!";
			link.l1 = "...";
			link.l1.go = "mine_banditx_fire";
		break;
		
		case "mine_banditx_fire":
			DialogExit();
			DoQuestCheckDelay("Saga_MineBanditsxFire", 0.6);
		break;
		
		case "mine_attackx":
			dialog.text = "Really? You must know the password then. Speak up, but you'll regret it if you're lying...";
			link.l1 = "Triton";
			link.l1.go = "mine_wrongx_password";
			link.l2 = "Neptune";
			link.l2.go = "mine_attackx_1";
			link.l3 = "Centurion";
			link.l3.go = "mine_wrongx_password";
			link.l4 = "Harpoon";
			link.l4.go = "mine_wrongx_password";
		break;
		
		case "mine_attackx_1":
			dialog.text = "Correct. But you, mate, have come here from the wrong side. Didn't they warn you? Go back and take the left path from the dry well. Then walk around the hill and there you will see the main gate.";
			link.l1 = "Can't I come in here?";
			link.l1.go = "mine_attackx_2";
		break;
		
		case "mine_wrongx_password":
			dialog.text = "Guys, we've got a sleuth! Muskets ready! Fire!!";
			link.l1 = "...";
			link.l1.go = "mine_banditx_fire";
		break;
		
		case "mine_attackx_2":
			dialog.text = "No. Only through the central entrance.";
			link.l1 = "All right, pal... Hey! Look! What the hell is that on top of the palisade?";
			link.l1.go = "mine_attackx_3";
		break;
		
		case "mine_attackx_3":
			DialogExit();
			for (i=1; i<=4; i++)
			{
				sld = characterFromId("Mine_banditx_"+i);
				LAi_RemoveCheckMinHP(sld);
			}
			sld = characterFromId("Svensons_sold_12");
			LAi_SetActorType(sld);
			LAi_ActorTurnToLocator(sld, "soldiers", "soldier1");
			LAi_ActorAnimation(sld, "shot", "Saga_MineBanditxDie", 1.0);
		break;
		
		case "mine_attack":
			dialog.text = "Really? You should know the password then. Speak up and say it so I can hear it. And if you try to fool me, that will be the last joke you ever play on anyone in your life.";
			link.l1 = "Triton";
			link.l1.go = "mine_wrong_password";
			link.l2 = "Neptune";
			link.l2.go = "mine_attack_1";
			link.l3 = "Centurion";
			link.l3.go = "mine_wrong_password";
			link.l4 = "Harpoon";
			link.l4.go = "mine_wrong_password";
		break;
		
		case "mine_attack_1":
			dialog.text = "Correct. Move along. The head of the camp is in the house to the left of the entrance to the mine. Go and see him.";
			link.l1 = "Fine, pal...";
			link.l1.go = "mine_attack_2";
		break;
		
		case "mine_wrong_password":
			dialog.text = "Guys, we've got a sleuth! Cannons, open fire!!";
			link.l1 = "...";
			link.l1.go = "mine_bandit_fire";
		break;
		
		case "mine_attack_2":
			DialogExit();
			locCameraFollowEx(true);
			NextDiag.CurrentNode = "mine_attack_3";
			LAi_SetActorType(pchar);
			LAi_ActorFollow(pchar, npchar, "ActorDialog_Any2Pchar", -1);
			LAi_ActorTurnToCharacter(npchar, pchar);
			SetActorDialogAny2Pchar(npchar.id, "", 0.0, 0.0);
		break;
		
		case "mine_attack_3":
			dialog.text = "What else? Have you forgotten anything?";
			link.l1 = "Yes. I was asked to give you the very best regards.";
			link.l1.go = "mine_attack_4";
		break;
		
		case "mine_attack_4":
			dialog.text = "To me? Ha-ha! From whom?";
			link.l1 = "Jan Svenson, you bastard!";
			link.l1.go = "mine_attack_5";
		break;
		
		case "mine_attack_5":
			DialogExit();
			AddDialogExitQuestFunction("Saga_MineAttack");
		break;
		
	// ----------------------------- диалоги НПС при штурме бандитского рудника -------------------------------
		case "Svensons_off":
			dialog.text = LinkRandPhrase("We will tear those bastards apart!","I am looking forward to beating those scum!","Jackman's minions have no right to be at the Western Main! We will drive them away from here!");
			link.l1 = "...";
			link.l1.go = "exit";
			NextDiag.TempNode = "Svensons_off";
		break;
		
		case "Svensons_sold":
			dialog.text = LinkRandPhrase("We are ready to fight!","We'll show them!","They don't even know who they're messing with!");
			link.l1 = "...";
			link.l1.go = "exit";
			NextDiag.TempNode = "Svensons_sold";
		break;
		
		case "gunner":
			PlaySound("Voice\English\evilpirates01.wav");
			dialog.text = "Commander, the cannon is ready. It's loaded with a bomb, just as you ordered.";
			link.l1 = "I take it no one is expecting us here... Time to introduce ourselves. Jan told me their camp is behind this hill. Will you be able to reach it?";
			link.l1.go = "gunner_0_1";
		break;
		
		case "gunner_0_1":
			dialog.text = "Easy enough, Commander. Let's raise the barrel a bit, that should do it... done.\nGet ready!.. Fire!!";
			link.l1 = "...";
			link.l1.go = "gunner_0_2";
			npchar.quest.canonada = "1";
		break;
		
		case "gunner_0_2":
			DialogExit();
			LAi_SetActorType(pchar);
			DoQuestCheckDelay("Saga_Gunfire", 3.0);
			LAi_ActorTurnToLocator(npchar, "goto", "goto14");
		break;
		
		case "gunner_1":
			dialog.text = "";
			link.l1 = "Hm. Randolf, do you think we hit something? I'd like to hear your opinion.";
			link.l1.go = "gunner_1_1";
		break;
		
		case "gunner_1_1":
			PlaySound("interface\" + LanguageGetLanguage() + "\_bombs_npc.wav");
			dialog.text = "Commander, we did hit something or someone, but I can't be more specific... this blasted hill is blocking the view. I'll change the angle.\nReady! Fire!";
			link.l1 = "...";
			link.l1.go = "gunner_0_2";
			npchar.quest.canonada = "2";
		break;
		
		case "gunner_2":
			PlaySound("interface\abordage_wining.wav");
			PlaySound("types\warrior03.wav");
			dialog.text = "Ha! Look, Commander! There's smoke! Damn, we must have hit some bandit's barn! Hurrah-ah!";
			link.l1 = "Yes, I see the smoke... An epic victory already, no doubt. Reload the gun and aim it at the path, it looks like our guests are coming. We will greet them appropriately!";
			link.l1.go = "gunner_2_1";
		break;
		
		case "gunner_2_1":
			PlaySound("interface\" + LanguageGetLanguage() + "\_bombs_npc.wav");
			dialog.text = "Aye-aye, Commander! Load the bomb! Gun crew at the ready! Fuse ready! Fire at my command!";
			link.l1 = "...";
			link.l1.go = "gunner_2_2";
			npchar.quest.canonada = "3";
		break;
		
		case "gunner_2_2":
			DialogExit();
			LAi_SetActorType(pchar);
			DoQuestCheckDelay("Saga_LoginBandos_01", 6.0);
			LAi_ActorTurnToLocator(pchar, "goto", "goto14");
			LAi_ActorTurnToLocator(npchar, "goto", "goto14");
		break;
		
		case "gunner_3":
			PlaySound("interface\abordage_wining.wav");
			PlaySound("types\warrior03.wav");
			PlaySound("Voice\English\evilpirates05.wav");
			dialog.text = "Ha-ha, that's got to hurt!";
			link.l1 = "Don't relax yet! Load the gun! I don't think they've had enough. More are coming!";
			link.l1.go = "gunner_3_1";
		break;
		
		case "gunner_3_1":
			PlaySound("interface\" + LanguageGetLanguage() + "\_bombs_npc.wav");//
			dialog.text = "Aye-aye, Commander! Load a bomb! Ready! Fire on my command!";
			link.l1 = "...";
			link.l1.go = "gunner_3_2";
			npchar.quest.canonada = "4";
		break;
		
		case "gunner_3_2":
			DialogExit();
			LAi_SetActorType(pchar);
			DoQuestCheckDelay("Saga_LoginBandos_02", 5.0);
			LAi_ActorTurnToLocator(pchar, "goto", "goto14");
			LAi_ActorTurnToLocator(npchar, "goto", "goto14");
		break;
		
		case "gunner_5":
			PlaySound("types\warrior04.wav");
			PlaySound("Voice\English\evilpirates06.wav");
			dialog.text = "Ha-ha-ha, the bastards have shown us their backs! Dog's meat! Grapeshot is tearing them apart at this range! Looks like they are not brave enough to attack us again!";
			link.l1 = "Now it's our turn. Randolph, you will stay here by the cannon. Fire at the path a few times, then aim at the smoke – burn their lair! Just don't shoot us.";
			link.l1.go = "gunner_5_1";
		break;
		
		case "gunner_5_1":
			PlaySound("interface\" + LanguageGetLanguage() + "\_bombs_npc.wav");
			dialog.text = "Aye-aye, Commander! Ready the cannon! Load a shell!";
			link.l1 = "Men! To arms! Follow me, attack! Hurrah!!";
			link.l1.go = "attack";
		break;
		
		case "attack":
			DialogExit();
			n = Findlocation("mine");
			Locations[n].hidden_fire = true;
			PlaySound("interface\abordage_wining.wav");
			PlaySound("interface\abordage_wining.wav");
			LAi_ActorTurnToLocator(npchar, "goto", "goto14");
			LAi_group_MoveCharacter(npchar, "TMP_FRIEND");
			if (GetCharacterIndex("Svensons_sold_12") != -1 && pchar.questTemp.Saga.MineAttack == "soldiers")
			{
				sld = characterFromId("Svensons_sold_12");
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
			}
			for (i=1; i<=8; i++)
			{
				if (GetCharacterIndex("Ourmine_sold_"+i) != -1)
				{
					sld = characterFromId("Ourmine_sold_"+i);
					if (i == 1) sld.MusketerDistance = 10; 
					LAi_SetWarriorType(sld);
					LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
				}
			}
			LAi_group_SetRelation("EnemyFight", "TMP_FRIEND", LAI_GROUP_NEITRAL);
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("EnemyFight", "Saga_MineBandos_05Die");
			AddDialogExitQuest("MainHeroFightModeOn");	
			DoQuestCheckDelay("Saga_MineSetMusic", 0.3);
			// запускаем автобабахалку на 10 выстрелов
			iTotalTemp = 0;
			DoQuestCheckDelay("Saga_GunAutoFire", 7.0);
			bDisableCharacterMenu = false;//разлочим интерфейсы
			InterfaceStates.Buttons.Save.enable = true;//разрешим сохраняться
		break;
		
		case "convict":
			if (LAi_grp_playeralarm > 0)
			{
				dialog.text = LinkRandPhrase("Don't hurt me, I'm not one of them! Kill the bandits!","Free us, pal! And kill them all!","Cut them, friend, cut them! Make them dead!");
				link.l1 = "Ha! Don't worry, that's exactly what we're doing right now.";
				link.l1.go = "exit";
			}
			else
			{
				dialog.text = LinkRandPhrase("Is our slavery over? Will you set us free?","Heh, have I really managed to survive to see this day?","Bastards have drained all the blood from us....");
				link.l1 = "I think you'll be able to enjoy your freedom soon, pal...";
				link.l1.go = "exit";
			}
			NextDiag.TempNode = "convict";
		break;
		
		// жена Яна Свенсона
		case "js_girl":
			if (LAi_grp_playeralarm > 0)
			{
				dialog.text = "You'd better leave this place, Sir. We don't harbour criminals and we don't need any conflicts with the authorities of the colony.";
				link.l1 = "Fine, I am leaving...";
				link.l1.go = "exit";
				NextDiag.TempNode = "js_girl";
				break;
			}
			if(NPChar.quest.meeting == "0")
			{
				// Первый диалог с Элен
				if(startHeroType == 4)
				{
					dialog.text = "Ah, Helen. You could have dressed a bit more decently before coming to see Jan, rather than showing him what you're really like. It's a pity he doesn't believe me.";
					link.l1 = "And what exactly am I like? He's helped raise me since childhood and knows me better than anyone. I have no secrets from him. I've suffered from this heat since I was a child, so I had to deal with it in my own way, that's all.";
					link.l1.go = "js_helen_ft";
					NextDiag.TempNode = "js_girl";
					NPChar.quest.meeting = "1";
					break;
				}
				dialog.text = TimeGreeting()+", Sir. Would you like to see Jan?";
				link.l1 = "Good day. It was nice meeting you, Miss?.. ";
				link.l1.go = "js_girl_1";
			}
			else
			{
				// заглушка элен
				if(startHeroType == 4)
				{
					dialog.text = "Jan is inside. Go ahead, nothing to see here, and you're getting on my nerves.";
					link.l1 = "Wasn't really in the mood anyway.";
					link.l1.go = "exit";
					NextDiag.TempNode = "js_girl";
					break;
				}
				if (CheckAttribute(pchar, "questTemp.HelenDrinking.Dialogs.Joan")) {
					dialog.text = "Grr!";
					link.l1 = "And good health to you too, Mrs. Svensson.";
					link.l1.go = "exit";
					break;
				}
				
				if (CheckAttribute(pchar, "questTemp.Saga") && pchar.questTemp.Saga == "blueveld")
				{
					dialog.text = TimeGreeting()+", Captain "+GetFullName(pchar)+". If you are here for Jan, then I have to disappoint you – he is not here. He is off attending to some important business.";
					link.l1 = "Damn it! And I need him! Tell me, Mrs Svenson, did he tell you when he was going to be back?";
					link.l1.go = "js_girl_3";
					break;
				}
				dialog.text = "A-ah, you again, Captain "+GetFullName(pchar)+"... move along, Jan is upstairs as usual.";
				link.l1 = "Thank you, Mrs Svenson...";
				link.l1.go = "exit";
			}
			NextDiag.TempNode = "js_girl";
		break;
		
		case "js_girl_1":
			dialog.text = "Mrs., Mrs. Johanna Svenson.";
			link.l1 = "Captain "+GetFullName(pchar)+".";
			link.l1.go = "js_girl_2";
		break;
		
		case "js_girl_2":
			if (CheckAttribute(pchar, "questTemp.Saga") && pchar.questTemp.Saga == "blueveld")
			{
				dialog.text = "Captain? Well, I am glad to welcome you to my house. But if you are here for Jan, then I have to disappoint you - he is not here. He is off conducting some important business.";
				link.l1 = "Damn it! And I need him! Tell me, Mrs Svenson, did he tell you when he would be back?";
				link.l1.go = "js_girl_3";
				break;
			}
			dialog.text = "Captain? Well, I am glad to welcome you to my house. My husband is on the second floor in his office. Go upstairs.";
			link.l1 = "I understand, Mrs. Svenson...";
			link.l1.go = "exit";
			NPChar.quest.meeting = "1";
			NextDiag.TempNode = "js_girl";
		break;
		
		case "js_girl_3":
			dialog.text = "No. He didn't even tell me the exact date of his return, because he doesn't know himself how long the search will last.";
			link.l1 = "I am sorry for interfering, but I really need him... What search is he conducting?";
			link.l1.go = "js_girl_4";
		break;
		
		case "js_girl_4":
			dialog.text = "I'll tell you. The lovely Helen, also known as Rumba, daughter of his late friend Sean McArthur, has disappeared. Jan treats the young devil as if she were his own daughter. She reminds him of his old love, who had the same reckless temper. At least, that is the reason for his attraction, I believe.\nAnyway, the girl disappeared a week ago along with her schooner, 'Rainbow', and her entire crew. Sean McArthur taught her seamanship, and the 'Rainbow' was passed on to her by his will. And now she pretends to be a captain...";
			link.l1 = "What could have happened to her?";
			link.l1.go = "js_girl_5";
		break;
		
		case "js_girl_5":
			dialog.text = "Who knows... A week is not that long, but McArthur's widow is convinced that something has happened to her daughter, and she managed to persuade Jan of it as well. He gathered his men and started searching for her himself, but so far without success. Personally, I think Helen is fine and Jan is just tormenting himself for no reason.\nHe listened too much to that old, fat woman's nonsense and panicked. The girl is most likely having fun with another boyfriend at this very moment, far from prying eyes in some safe place. She will come back as soon as her hunger is sated.";
			link.l1 = "Johanna, where can I find Gladys? I want to talk to her...";
			link.l1.go = "js_girl_6";
		break;
		
		case "js_girl_6":
			dialog.text = "Her house is near the pier, on the left. But she likely isn't there. She wastes every day standing on the walls of the fort, looking for her precious daughter.";
			link.l1 = "I see. Thank you very much for your information!";
			link.l1.go = "js_girl_7";
		break;
		
		case "js_girl_7":
			DialogExit();
			NextDiag.CurrentNode = "js_girl_8";
			sld = characterFromId("Gladis"); //устанавливаем Глэдис на форт
			ChangeCharacterAddressGroup(sld, "SantaCatalina_fort", "goto", "goto53");
			LAi_SetStayType(sld);
			sld.dialog.currentnode = "FindHelena";
			pchar.questTemp.Saga = "gladis";
			DelLandQuestMark(npchar);
			DelLandQuestMark(characterFromId("SantaCatalina_tavernkeeper"));
			DelMapQuestMarkCity("SantaCatalina");
		break;
		
		case "js_girl_8":
			dialog.text = "Jan is not here yet, Captain, so come back later.";
			link.l1 = "I see...";
			link.l1.go = "exit";
			NextDiag.TempNode = "js_girl_8";
		break;
		
		case "js_helen_ft":
			dialog.text = "You're always in heat, I'd say. You should go to church; I've barely ever seen you there.";
			link.l1 = "My conscience is clear - I have nothing to beg forgiveness for. Still bitter that he helped supply my ship instead of buying you another dress, Joanna?";
			link.l1.go = "js_helen_ft_1";
		break;
		
		case "js_helen_ft_1":
			dialog.text = "Me? Bitter? You're not worth it. It's just that everything comes too easily for you, and you don't deserve it.";
			link.l1 = "But as soon as I got that ship, I started earning on my own. And since he picked you up like a stray cat, you haven't worked a day. So who's really living off him?";
			link.l1.go = "js_helen_ft_2";
		break;
		
		case "js_helen_ft_2":
			dialog.text = "You keep talking like that, and one day you'll get what's coming to you. Jan and Gladys should have taught you some manners. Fine, go on, say what you came to say - and get out of my sight, Helen. He's inside.";
			link.l1 = "Stupid hen. Sure, will do.";
			link.l1.go = "exit";
		break;
		
		// хронометр Алекса
		case "Alexs_bandos":
			dialog.text = "Hey! What are you doing here?";
			link.l1 = "I'd like to ask you the same – what are you and your pals doing here, in my dungeon?";
			link.l1.go = "Alexs_bandos_1";
		break;
		
		case "Alexs_bandos_1":
			dialog.text = "Ha! Your dungeon? And when did it become yours, you wretch?";
			link.l1 = "The day your father made the mistake of fucking your mother.";
			link.l1.go = "Alexs_bandos_2";
		break;
		
		case "Alexs_bandos_2":
			dialog.text = "Are you looking for trouble?";
			link.l1 = "Listen, pal, I'm giving you one last chance to leave this place. This is my dungeon and I won't let anyone just waltz in here, you got that? I only need to whistle once, and half the pirates of Isla Tesoro will be here within a minute.";
			link.l1.go = "Alexs_bandos_3";
		break;
		
		case "Alexs_bandos_3":
			dialog.text = "Well, we'll try to shut your mouth then!";
			link.l1 = "Ha-ha! You are pathetic, scum!";
			link.l1.go = "Alexs_bandos_4";
		break;
		
		case "Alexs_bandos_4":
			DialogExit();
			LAi_LocationFightDisable(&Locations[FindLocation("Bermudes_Dungeon")], false);
			for (i=1; i<=4; i++)
			{
				sld = characterFromId("Alexs_bandos_"+i);
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "EnemyFight");
			}
			int iRank = sti(pchar.rank)+MOD_SKILL_ENEMY_RATE+5;
			int iScl = 25+2*sti(pchar.rank);
			sld = GetCharacter(NPC_GenerateCharacter("Alexs_bandos_5", "mush_ctz_8", "man", "mushketer", iRank, PIRATE, -1, false, "soldier"));
			FantomMakeCoolFighter(sld, iRank, iScl, iScl, "", "mushket1", "bullet", iScl*2+50);
			ChangeCharacterAddressGroup(sld, "Bermudes_Dungeon", "monsters", "monster8");
			LAi_group_MoveCharacter(sld, "EnemyFight");
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("EnemyFight", "AlexClock_BandosDie");
			AddDialogExitQuest("MainHeroFightModeOn");	
		break;
		
		case "helendrinking_gypsy":
			dialog.text = "Hold on a moment, falcon!";
			link.l1 = "Not the best timing, sweetheart.";
			link.l1.go = "helendrinking_gypsy_1";
		break;
		
		case "helendrinking_gypsy_1":
			dialog.text = "Oh, you're mistaken, handsome. This girl likes you, and I can see the feeling is mutual.";
			link.l1 = "Not the best recommendation... Alright, what is it you want? A handout?";
			link.l1.go = "helendrinking_gypsy_2";
		break;
		
		case "helendrinking_gypsy_2":
			dialog.text = "I want to offer you support in your challenging endeavour. Look here! A magic mug and a forbidden ointment. The mug will help you with drinking, and the ointment - with matters of love. What will you choose? Only two thousand!";
			link.l1 = "I don't need anything - I've already given a whole heap of silver to your kind.";
			link.l1.go = "helendrinking_gypsy_refuse";
			if (sti(pchar.money) >= 2000) {
				link.l2 = "Forbidden ointment, you say? Well, I'm no saint, I admit. Give it here.";
				link.l2.go = "helendrinking_gypsy_fuck";
				link.l3 = "A mug? Do I look like a drunkard? Well, who am I kidding... I'll take it!";
				link.l3.go = "helendrinking_gypsy_drink";
			}
			
			AddDialogExitQuestFunction("HelenDrinking_TalkedToGypsy");
		break;
		
		case "helendrinking_gypsy_refuse":
			dialog.text = "Handsome but foolish. Fly away then, falcon.";
			link.l1 = "";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_TalkedToGypsy");
		break;
		
		case "helendrinking_gypsy_drink":
			dialog.text = "Oh, don't hide it in your bottomless pockets! Fly away, falcon, and don't sin!";
			link.l1 = "";
			link.l1.go = "exit";
			
			AddMoneyToCharacter(pchar, -2000);
			GiveItem2Character(pchar, "totem_01");
			Log_Info("Talisman 'Throat of cast iron' acquired!");
			PlaySound("interface\important_item.wav");
			
			AddDialogExitQuestFunction("HelenDrinking_TalkedToGypsy");
		break;
		
		case "helendrinking_gypsy_fuck":
			dialog.text = "Oh, don't hide it in your bottomless pockets! Fly away, falcon, and don't sin!";
			link.l1 = "";
			link.l1.go = "exit";
			
			AddMoneyToCharacter(pchar, -2000);
			GiveItem2Character(pchar, "totem_03");
			Log_Info("Talisman 'Cupid's Balm' acquired!");
			PlaySound("interface\important_item.wav");
			pchar.questTemp.Saga.HelenRelation = sti(pchar.questTemp.Saga.HelenRelation) - 1;
			Notification_Approve(false, "Helena");
			
			AddDialogExitQuestFunction("HelenDrinking_TalkedToGypsy");
		break;
		
		case "helendrinking_joan":
			dialog.text = "Ah! Get out of here, you scoundrel! How many times have I told you not to sneak into my house! And who is this?";
			link.l1 = "Ma'am, we're already acquainted.";
			link.l1.go = "helendrinking_joan_1";
		break;
		
		case "helendrinking_joan_1":
			dialog.text = "Monsieur de Maure? Well, that's just lovely! Is this how you conduct business with my husband?! I knew it! I warned Jan: someday this hussy would start leading her men astray! And what do you have in your hands?";
			link.l1 = "";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_JoanDialog1");
		break;
		
		case "helendrinking_joan_2":
			dialog.text = "Wha-a-a-at?! How dare you, wretch?! You're not going anywhere; my husband will be here any moment now and he'll teach you how to talk to the elders!";
			link.l1 = "";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_JoanDialog3");
		break;
		
		case "helendrinking_fort_officer":
			dialog.text = "What's happening here? Miss MacArthur! I had great respect for your father, and Mr. Svensson is our friend... But don't you remember how it all ended last time?\nIt's disappointing, officer's word, disappointing! You could have invited us!";
			link.l1 = "";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_FortDialog");
		break;
		
		case "helendrinking_fort_officer_1":
			dialog.text = "Thank you for your hospitality, Miss MacArthur. Let me say that we are all very glad to see you back. What happened is a great mystery, but it's not surprising that the town knows about it. Still, I can assure you that no one will gossip. I offer my sincere apologies for the recent behaviour of one of our captains. And I want to thank you specifically, Mr de Maure.";
			link.l1 = "";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_FortDialog3");
		break;
		
		case "helendrinking_fort_officer_2":
			dialog.text = "Everything will be fine, Miss. Mr de Maure, I'll be frank – despite Donovan behaving like a true scoundrel and bandit, the fleet will never openly condemn him. More likely, they'll even defend him. Your little expedition made it into the reports and has significantly complicated relations between our countries. Nevertheless, considering Mr Svensson's influence, as well as the remarkable concessions made to you by Capsterville, you have nothing to fear.";
			link.l1 = "That's splendid. I say we drink to that!";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_FortDialog1");
		break;
		
		case "helendrinking_poorman":
			dialog.text = "Excuse me, kindly, so what about the job?";
			link.l1 = "Are you still here?";
			link.l1.go = "helendrinking_poorman_1";
		break;
		
		case "helendrinking_poorman_1":
			dialog.text = "Dear sir, where else could I go? I just went to relieve myself, overheard your sentimental conversation, and got a bit warmed up. Emotionally, I mean!";
			if (CheckAttribute(pchar, "questTemp.HelenDrinking.BoughtRainbow")) {
				link.l1 = "Good Lord! Well, since I gave you my word, it can't be helped. Go, take command.";
				link.l1.go = "helendrinking_poorman_bought";
			} else {
				link.l1 = "I have no work for you, sir.";
				link.l1.go = "helendrinking_poorman_notbought";
			}
		break;
		
		case "helendrinking_poorman_bought":
			dialog.text = "Aye aye, Captain!";
			link.l1 = "";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_AddRainbow");
			AddDialogExitQuestFunction("HelenDrinking_LightsOut1NoArg");
		break;
		
		case "helendrinking_poorman_notbought":
			dialog.text = "Too bad! Anyway, thanks for the treat, Captain!";
			link.l1 = "";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_AddRainbow");
			AddDialogExitQuestFunction("HelenDrinking_LightsOut1NoArg");
		break;
		
		case "helensleep_amelia_mary":
			dialog.text = "In nomine Patris et Filii et Spiritus Sancti... come in, my son.";
			if (HelenSleep_TalkedToAmelia()) {
				link.l1 = "Hello, Mother Amelia. Are you going to shout at me too?";
				link.l1.go = "helensleep_amelia_mary_know";
			} else {
				link.l1 = "Disappear! What kind of nightmare is this? What is happening? Am I dreaming?";
				link.l1.go = "helensleep_amelia_mary_notknow";
			}
		break;
		
		case "helensleep_amelia_mary_know":
			dialog.text = "No, my little falcon. And forgive Jan – the poor man got worked up. But yes, I do want to scold you. Why did you come to the church? To repent for your sins? Or were you after the red-haired one?";
			link.l1 = "I don't know myself...";
			link.l1.go = "helensleep_amelia";
			link.l2 = "Did you see her too? She caught my eye.";
			link.l2.go = "helensleep_amelia";
		break;
		
		case "helensleep_amelia_mary_notknow":
			dialog.text = "Disappear. We should have met already, but you're dragging everything out. Why did you come to the church? To repent for your sins? Or were you after the red-haired one?";
			link.l1 = "I don't know myself...";
			link.l1.go = "helensleep_amelia";
			link.l2 = "Did you see her too? She caught my eye.";
			link.l2.go = "helensleep_amelia";
		break;
		
		case "helensleep_amelia_helen":
			dialog.text = "Good morning, my falcon. The reception has not started yet, please wait in line.";
			if (HelenSleep_TalkedToAmelia()) {
				link.l1 = "Hello, Your Excellency. Are you going to shout at me as well?";
				link.l1.go = "helensleep_amelia_helen_know";
			} else {
				link.l1 = "Disappear! What kind of nightmare is this? What is happening? Am I dreaming?";
				link.l1.go = "helensleep_amelia_helen_notknow";
			}
		break;
		
		case "helensleep_amelia_helen_know":
			dialog.text = "No, my falcon. And forgive Jan, the poor man got worked up. No need to scold you; you did everything right - didn't go after the red-haired one to the church. Good boy!";
			link.l1 = "Getting praised is nice. Especially when it's clear what for.";
			link.l1.go = "helensleep_amelia";
			link.l2 = "Did you see her too? She caught my eye.";
			link.l2.go = "helensleep_amelia";
		break;
		
		case "helensleep_amelia_helen_notknow":
			dialog.text = "Disappear. We should have met already, but you're dragging everything out. Come here, I'll praise you – you didn't chase after the red-haired one to the church. Good boy!";
			link.l1 = "Getting praised is nice. Especially when it's clear what for.";
			link.l1.go = "helensleep_amelia";
			link.l2 = "Did you see her too? She caught my eye.";
			link.l2.go = "helensleep_amelia";
		break;
		
		case "helensleep_amelia":
			dialog.text = "I won't trouble you with the details, silly, but I'll tell you this: you are destined to be a great person. You will bring about much evil, yet far more good. But happiness is not guaranteed to you. Happiness, my falcon, is granted only to those who walk their path and do not stray. And a faithful woman will help you not to stray.\nYou will have two of them, and both will bring happiness, but you must choose the fair-haired one.";
			link.l1 = "Why would that be? I'll decide for myself!";
			link.l1.go = "helensleep_amelia_1";
		break;
		
		case "helensleep_amelia_1":
			dialog.text = "Of course, choose for yourself, but the fair-haired one is better. We've decided it that way.";
			link.l1 = "Who are we?";
			link.l1.go = "helensleep_amelia_2";
		break;
		
		case "helensleep_amelia_2":
			dialog.text = "The unfortunate one doesn't even know her true name. Speak it, and she'll be yours. So it is said.";
			link.l1 = "I don't understand anything anymore.";
			link.l1.go = "helensleep_amelia_3";
		break;
		
		case "helensleep_amelia_3":
			dialog.text = "Hear that knocking? Open up, and make no mistake.";
			link.l1 = "Indeed, someone is knocking... Come in!";
			link.l1.go = "exit";
			
			PlaySound("interface\knock.wav");
			
			AddDialogExitQuestFunction("HelenSleep_WakeUp");
		break;
		
		case "helendrinking_notifier":
			dialog.text = "Monsieur, Mr Svensson requested that you spare a bit of your time for him.";
			link.l1 = "Damn, this doesn't bode well. I'll try, but no promises.";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_End");
		break;
		
		case "islatesoro_pirate1":
			dialog.text = "Lucky day, lads! Told you she'd come here sooner or later, didn't I? Alright, sweetheart, hand over the weapons and come with us.";
			link.l1 = "You've got it wrong, lads. She's with me.";
			link.l1.go = "islatesoro_pirate1_1";
		break;
		
		case "islatesoro_pirate1_1":
			dialog.text = "Stay out of this, or I'll shoot you like a dog. There's a good sum offered for the girl, and we're hungry men, lacking in principles.";
			link.l1 = "Keep talking to me in that tone, and I'll solve your hunger problem permanently.";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_IslaTesoroSpawnSecond");
		break;
		
		case "islatesoro_pirate1_2":
			dialog.text = "Have you gone completely mad, Lucky? We found her first! You'd better have a good reason for running your foolish mouth at me!";
			link.l1 = "";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_IslaTesoroPirateDialog1");
		break;
		
		case "islatesoro_pirate1_3":
			dialog.text = "You're the rat here! We had just torn a big fat Spaniard apart; we can sit on our asses for a year!";
			link.l1 = "";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_IslaTesoroPirateDialog3");
		break;
		
		case "islatesoro_pirate2":
			dialog.text = "Well, look who we have here. Alright, everyone else, clear out, and you, madam, come with us.";
			link.l1 = "";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_IslaTesoroPirateDialog");
		break;
		
		case "islatesoro_pirate2_1":
			dialog.text = "We outnumber you, and we're tougher, Dane. What other reason do you need, you bilge rat? It's been six months since you've seen a decent haul, and you've been eating bread crumbs off Vuazie's table!";
			link.l1 = "";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_IslaTesoroPirateDialog2");
		break;
		
		case "islatesoro_pirate2_2":
			dialog.text = "";
			link.l1 = "Looks like there won't be a peaceful resolution here.";
			link.l1.go = "islatesoro_pirate_a";
			if (!CheckAttribute(pchar, "questTemp.HelenDrinking.IslaTesoroAmbush.TriedB")) {
				link.l2 = "What did you say? Lucky? I heard a rumour that he and Vuazie conspired to give you dodgy tips. That explains your streak of bad luck at sea.";
				link.l2.go = "islatesoro_pirate_b";
			}
			bOk = (!CheckAttribute(pchar, "questTemp.Mtraxx.Retribution.Choice")) || (pchar.questTemp.Mtraxx.Retribution.Choice == "bad");
			if (!CheckAttribute(pchar, "questTemp.HelenDrinking.IslaTesoroAmbush.TriedC") && CheckAttribute(pchar,"questTemp.Mtraxx.Cartahena.Gold") && bOk) {
				link.l3 = "I'm tired of this farce. Isla Tesoro, listen to me! Who was with me in Cartagena?! Who burned Mérida with me?! These rats dare to come at Charlie Prince himself! Let's show 'em, lads!";
				link.l3.go = "islatesoro_pirate_c";
			}
		break;
		
		case "islatesoro_pirate_a":
			dialog.text = "You're still here, jellyfish? Alright, lads, let's go: strap the captain down, and we'll deal with the girl later, got it?";
			link.l1 = "";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_IslaTesoroPirateDialog4");
		break;
		
		case "islatesoro_pirate_a_1":
			dialog.text = "Sure, let's spill some blood at least. Hehe.";
			link.l1 = "";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_IslaTesoroA");
		break;
		
		case "islatesoro_pirate_b":
			pchar.questTemp.HelenDrinking.IslaTesoroAmbush.TriedB = true;
		
			if (GetSummonSkillFromName(pchar, SKILL_LEADERSHIP) > 60) {
				dialog.text = "What?! Damn it, I knew you were colluding with that bespectacled scoundrel! Cut them all down, lads, and we'll pick up the girl later!";
				link.l1 = "";
				link.l1.go = "exit";
				AddDialogExitQuestFunction("HelenDrinking_IslaTesoroB");
			} else {
				dialog.text = "What are you yapping about, Captain? Get lost while respectable people are discussing business.";
				link.l1 = "";
				link.l1.go = "islatesoro_pirate2_2";
			}
			
			AddCharacterExpToSkill(pchar, "Leadership", 100);
		break;
		
		case "islatesoro_pirate_c":
			pchar.questTemp.HelenDrinking.IslaTesoroAmbush.TriedC = true;
		
			if (GetSummonSkillFromName(pchar, SKILL_LEADERSHIP) > 50) {
				DialogExit();
				AddDialogExitQuestFunction("HelenDrinking_IslaTesoroC");
			} else {
				dialog.text = "What are you yapping about, Captain? I've seen Charlie Prince, and you don't measure up to him. Get lost while the respectable people are discussing business.";
				link.l1 = "";
				link.l1.go = "islatesoro_pirate2_2";
			}
			
			AddCharacterExpToSkill(pchar, "Leadership", 100);
		break;
		
		case "francois":
			dialog.text = "Charles de Maure? Son of Henri de Monpe?";
			link.l1 = "That's correct, monsieur. And who are you?";
			link.l1.go = "francois_1";
		break;
		
		case "francois_1":
			dialog.text = "Colonel Francois de Tavanne. You may consider this a direct challenge, monsieur; the gauntlet for the duel has been laid. I don't even wish to dirty my hands with you, but I swear, my blade will taste your blood!";
			link.l1 = "A duel? In that case, you'll have to try much harder, Colonel. Right now, you could only be mistaken for a bandit, and in these parts, the conversation with their kind is brief! Explain yourself!";
			link.l1.go = "francois_2";
		break;
		
		case "francois_2":
			dialog.text = "You seduced my wife, monsieur! While I spilled blood for king and country, you... you were enjoying yourself with my wife!";
			link.l1 = "";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_AmbushDialog");
		break;
		
		case "francois_3":
			dialog.text = "Silence, madam. Your audacious attire disgraces the honour of any woman, although you seem quite fitting next to this unworthy seducer of a noblewoman!";
			link.l1 = "Still not enough reason for a duel, Colonel. And may I point out that you conduct yourself just as unworthily here.";
			link.l1.go = "francois_4";
		break;
		
		case "francois_4":
			dialog.text = "Is that not sufficient? I've inquired – in my place now could be a dozen noble husbands, sir. But if you want the details, then to my shame, I confess that one of your passions was Lulu de Tavann, the most beautiful and honest of women!";
			link.l1 = "Lulu, you say... And how is she?";
			link.l1.go = "francois_5";
		break;
		
		case "francois_5":
			dialog.text = "Silence! My wife, unable to endure the torment you inflicted, has recently passed away! I've spent almost a year and a fortune to find you, scoundrel! Enough words! Either accept the challenge, or I'll kill you like a dog. Richard! Be my witness!";
			link.l1 = "";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_AmbushDialog2");
		break;
		
		case "francois_6":
			dialog.text = "Silence, sir! Accept the challenge or lose whatever remnants of honour you may still possess!";
			if (pchar.HeroParam.HeroType == "HeroType_1") {
				link.l1 = "A duel is a duel. Not going to lie, I enjoy these. Captain, relay to the Colonel that it's time for him to order a suitable coffin.";
			} else {
				link.l1 = "Want a fight? You'll get one! Captain, relay to the Colonel that it's time for him to order a suitable coffin.";
			}
			link.l1.go = "francois_duel";
			link.l2 = "This is not Europe, Colonel. Honour in the Caribbean is harder to earn, but also not so easy to lose. I refuse your duel because I simply don't want it.";
			link.l2.go = "francois_refuse";
		break;
		
		case "francois_7":
			dialog.text = "Your father is already one step away from the grave, you scum! And I'll make sure he knows of your cowardice!";
			link.l1 = "";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_AmbushDialog7");
		break;
		
		case "richard":
			dialog.text = "Colonel, I confirm your right to a duel, but I won't allow mere banditry! Monsieur de Maure, I am Captain Richard Small. Are you willing to give satisfaction to Colonel de Tavannes?";
			link.l1 = "One moment, Captain. I knew Lulu well... and she... was inclined to change admirers frequently, and her health was better than mine... How did she die, Colonel? Before or after your return home?";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_AmbushDialog3");
		break;
		
		case "richard_1":
			dialog.text = "Please, François, allow me. Monsieur de Maure, you've been challenged. The officers' society of Blueweld acknowledges that Colonel de Tavannes' demand for satisfaction is justified. Accept the challenge or lose your honour.";
			link.l1 = "";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_AmbushDialog5");
		break;
		
		case "richard_2":
			dialog.text = "Charles, please, we're gentlemen here. It's not appropriate. The Colonel has travelled this far to meet you! It's a scandal!";
			link.l1 = "";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_AmbushDialog8");
		break;
		
		case "richard_3":
			dialog.text = "Y-yes, of course, miss. But I will...";
			link.l1 = "";
			link.l1.go = "exit";
			CharacterTurnToLoc(npchar, "quest", "helen");
			
			AddDialogExitQuestFunction("HelenDrinking_AfterFrancoisDeath1");
		break;
		
		case "richard_4":
			dialog.text = "Captain de Maure, the day is yours! Not the most proper fight, but you have defended your honour today.";
			link.l1 = "Did you say something, Captain? I might be able to squeeze another duel into today's schedule.";
			link.l1.go = "richard_5";
		break;
		
		case "richard_5":
			dialog.text = "My apologies, Captain. It's just nerves!";
			link.l1 = "I think your presence here is no longer necessary.";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_DuelVictory");
		break;
		
		case "richard_duel":
			dialog.text = "A fair decision! Even if it wasn't put in the most dignified way... Gentlemen! Let's begin!";
			link.l1 = "";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_SetupDuel");
		break;
		
		case "alonso":
			dialog.text = "Captain, I might not catch all the fancy words these dignitaries are throwing around, but you see, if someone gets called a coward, you usually don't let them off the hook. Hit the man, Captain, or our crew will start to worry.";
			link.l1 = "You want blood? Life too dull, no excitement? You'll get your blood, you animals!";
			link.l1.go = "francois_duel";
			link.l2 = "Boo-hoo, I'm so scared. Are you done here, gentlemen? I've got places to be.";
			link.l2.go = "alonso_refuse";
		break;
		
		case "alonso_1":
			dialog.text = "It won't look good if our captain backs down from a public challenge. Just give that nobleman a good whack; we know you're great with a sword!";
			link.l1 = "";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_AmbushDialog9");
		break;
		
		case "alonso_refuse":
			DialogExit();
			
			AddDialogExitQuestFunction("HelenDrinking_AmbushDialog6");
		break;
		
		case "francois_refuse":
			dialog.text = "Coward! Libertine! Rat! Are you afraid, scoundrel? Did you all see this?! Richard, I'll kill him anyway!";
			link.l1 = "";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_AmbushDialog4");
		break;
		
		case "francois_duel":
			DialogExit();
			
			AddDialogExitQuestFunction("HelenDrinking_SetupDuelDialog");
		break;
		
		case "francois_sit":
			dialog.text = "Y-you scoundrel! This is fine, I'm used to injuries. I'll recover, and...";
			link.l1 = "Sounds like a threat, Colonel. And I don't take threats kindly.";
			link.l1.go = "francois_sit_kill";
			link.l2 = "Once you've recovered, don't forget to boast about the circumstances of your injury to the officers' community.";
			link.l2.go = "francois_sit_taunt";
		break;
		
		case "francois_sit_kill":
			DialogExit();
			
			pchar.questTemp.Saga.HelenRelation = sti(pchar.questTemp.Saga.HelenRelation) - 1;
			Notification_Approve(false, "Helena");
			
			AddDialogExitQuestFunction("HelenDrinking_FinishFrancois");
		break;
		
		case "francois_sit_taunt":
			DialogExit();
			
			pchar.questTemp.Saga.HelenRelation = sti(pchar.questTemp.Saga.HelenRelation) + 1;
			Notification_Approve(true, "Helena");
			AddCharacterExpToSkill(pchar, SKILL_LEADERSHIP, 300);
			AddCharacterExpToSkill(pchar, SKILL_FORTUNE, 300);
			
			AddDialogExitQuestFunction("HelenDrinking_SpareFrancois");
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
	}
}

bool HelenSleep_TalkedToAmelia() {
	if (GetCharacterIndex("Amelia") < 0) {
		return false;
	}
	
	sld = CharacterFromID("Amelia");
	if (sld.dialog.currentnode == "amelia") {
		return false;
	}
	
	return true;
}
