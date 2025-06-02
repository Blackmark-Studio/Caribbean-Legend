// диалог прочих и малозначимых НПС
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	bool bOk;
	int i, n, iTemp;
	string attrL;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	attrL = Dialog.CurrentNode;
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			dialog.text = "Is there something you need?";
			link.l1 = "No, not right now.";
			link.l1.go = "exit";			
			NextDiag.TempNode = "First time";
		break;
		
		// --> матрос на корабле, прибытие в Сен-Пьер
		case "Startsailor":
			dialog.text = "Damn my eyes, land at last! Wake up, Monsieur... whatever your name is... We have arrived!";
			link.l1 = "A-ah! It's morning already? What is this Goddamn heat and humidity?";
			link.l1.go = "Startsailor_1";
			link.l2 = "I say! Charles de Maure! A nobleman, you know. How can you even drink in this heat? I'd rather have some water, for heaven's sake.";
			link.l2.go = "Startsailor_1a";
		break;
		
		case "Startsailor_1":
			dialog.text = "Get used to it, Monsieur. This is the only weather we have here... could always be worse.";
			link.l1 = "How could it get worse!? I'm only wearing a linen shirt and I've got sweat streaming down my back!";
			link.l1.go = "Startsailor_2";			
		break;
		
		case "Startsailor_2":
			dialog.text = "You'll see, haha! Could be hurricane season! Hurry up, monsieur. The longboat isn't going to wait on you. You don't want to swim to Martinique, do you?";
			link.l1 = "Just give me a moment, will you? Where's my sword? Ah, here it is...";
			link.l1.go = "Startsailor_3";			
		break;
		
		case "Startsailor_3":
			dialog.text = "You aren't in Europe anymore... Be careful, Monsieur. These are troubled times. Scuttlebutt says the Company of the American Isles sold the island of Martinique to some religious fanatics, crusaders or some nonsense like that. I still haven't noticed anything unusual, at least looking onto shore from the deck. But since we've been gone for a while, a lot could have changed in my absence.";
			link.l1 = "Crusaders? Nonsense!";
			link.l1.go = "Startsailor_4";			
		break;
		
		case "Startsailor_4":
			dialog.text = "Whether it's nonsense or not, rumors are rampant. We've already enough trouble as it is. Cannibals in the jungle, tropical fever, pirates, bandits in the alleyways, to say nothing of the Spanish and English...";
			link.l1 = "Oh, here we go again... Right now the only kind of trouble that I see is oppressive heat and mosquitos... All right, I'm ready. Shall we go?";
			link.l1.go = "Startsailor_5";			
		break;
		
		case "Startsailor_5":
			dialog.text = "Head topside and step onto the longboat, Monsieur. Welcome to the Caribbean!";
			link.l1 = "";
			link.l1.go = "Startsailor_6";			
		break;
		
		case "Startsailor_1a":
			dialog.text = "There's no other weather here,'Your Lordship'. If anything, it only gets worse.";
			link.l1 = "The weather is unbearable, as has been my company these past months. I hope there are some decent folk on the Archipelago.";
			link.l1.go = "Startsailor_2a";
			AddCharacterExpToSkill(pchar, "Leadership", 10);
		break;
		
		case "Startsailor_2a":
			dialog.text = "Well then, I think we'll all be glad to see you finally leave us, monsieur. The boat is waiting. Don't jump out of your breeches with joy. And don't forget your belongings - the ship's heading further, and you might as well forget them if you don't.";
			link.l1 = "As if I'd leave them for your pleasure. Pesos, sword - seems I haven't been robbed.";
			link.l1.go = "Startsailor_3a";			
		break;
		
		case "Startsailor_3a":
			dialog.text = "We're honest folk, of course, but you're thinking right - always keep an eye on your things, or someone might clean out your pockets. Just like in old Europe. Or anywhere, really. But this place ain't like home. Some fanatics have set up a base here. Word is, they secretly bought the whole island. So, stay sharp and don't draw attention.";
			link.l1 = "What nonsense!";
			link.l1.go = "Startsailor_4a";			
		break;
		
		case "Startsailor_4a":
			dialog.text = "That's the rumor. Be grateful I bothered to share and show concern for your stay here. Otherwise, that delicate Gascon rose of yours might wither under our blazing sun. Nonsense or not, keep your wits about you - we've got plenty of trouble without the fanatics. Bandits in the alleys and the jungle, pirates at sea, and red-skinned cannibals...";
			link.l1 = "Now, now! I'll manage. It might be a bit hot for me now, but I'm sun-hardened back home, unlike, say, those Normans. And if anything can be solved with a sword, you can count on me. But the mosquitoes - now that's pure torment! Well, all my things are accounted for. The boat's ready, you say?";
			link.l1.go = "Startsailor_5a";			
		break;
		
		case "Startsailor_5a":
			dialog.text = "Waiting eagerly. Hope you can make it yourself, monsieur? Head up, and hopefully, you won't get lost from there. Oh, and welcome to the Archipelago, heh-heh.";
			link.l1 = "Yeah, thanks. The only comfort is that I won't be here for long.";
			link.l1.go = "Startsailor_6";
		break;
		
		case "Startsailor_6":
			DialogExit();
			AddDialogExitQuestFunction("SharlieTutorial_StartGameInMartinique");
		break;
		// <-- матрос на корабле, прибытие в Сен-Пьер
		
		// горожанин знает Мишеля
		case "Benuatalker":
			DelLandQuestMark(npchar);
			link.l1 = "Excuse me, "+GetAddress_FormToNPC(NPChar)+", could you tell me where I can find Michel de Monper? He has to be somewhere in your town.";
            link.l1.go = "Benuatalker_1";
		break;
		
		case "Benuatalker_1":
			dialog.text = "Hmm... I see that you've arrived here recently since you fearlessly ask such questions... I advise you to stop it or you'll get in trouble otherwise. And about your question... Talk to the Abbot. You can find him at the church.";
			link.l1 = "Thank you!";
            link.l1.go = "exit";
			LAi_CharacterDisableDialog(npchar);
			npchar.lifeday = 0;
			AddDialogExitQuest("Sharlie_SetBenua");
			QuestPointerToLoc("FortFrance_town", "reload", "reload7_back");
		break;
		
		// --> арест в резиденции
		case "Sharlie_arest":
			dialog.text = "Halt! Yield your weapons at once, Monsieur, and follow us!";
			link.l1 = "What the devil is this?";
			link.l1.go = "Sharlie_arest_1";
			if (CheckCharacterItem(PChar, "knife_03")) pchar.Sharlie.KnifeMonpe = true;
		break;
		
		case "Sharlie_arest_1":
			DialogExit();
			chrDisableReloadToLocation = false;
			DoFunctionReloadToLocation("FortFrance_prison", "goto", "goto9", "Puancie_InJail");
			WaitDate("", 0, 0, 2, 0, 10); //крутим время
			RecalculateJumpTable();
			RemoveAllCharacterItems(PChar, true);
			sld = characterFromId("Puancie");
			sld.dialog.currentnode = "Puancie_Jail"; 
			LAi_SetActorTypeNoGroup(sld);
			ChangeCharacterAddressGroup(sld, "FortFrance_prison", "goto", "goto13");
		break;
		// арест в резиденции
		
		// --> офицер базы
		case "Maltie_officer":
			ref location = &Locations[FindLocation(pchar.location)];
			if (CheckAttribute(pchar, "questTemp.Guardoftruth") && pchar.questTemp.Guardoftruth == "begin")
			{
				dialog.text = "Good to see you, Monsieur de Maure. What's the occasion?";
				link.l1 = TimeGreeting()+", officer. I would like to speak with my brother, Michel de Monper. Off the record of course. I am trying to find out about his service here in the Caribbean.";
				link.l1.go = "spanish";
				break;
			}
			if (CheckAttribute(pchar, "questTemp.Guardoftruth") && pchar.questTemp.Guardoftruth == "think")
			{
				dialog.text = "How did the interrogation go? Did you find anything worthwhile?";
				link.l1 = "Oh yes. So much that I'm taking this Spaniard with me back to my ship. He is an important witness and must be delivered to St. Christopher for further questioning.";
				link.l1.go = "spanish_10";
				break;
			}
			if (!CheckAttribute(location, "first_meeting"))
			{
				dialog.text = "What is your business here, Monsieur?";
				link.l1 = "I have come to see my brother, Michel de Monper.";
				link.l1.go = "Maltie_officer_1";
				location.first_meeting = true;
			}
			else
			{
				dialog.text = "Monsieur, I must gently remind you that you are inside a military cantonment. Behave accordingly.";
				link.l1 = "Yes, sir. Of course.";
				link.l1.go = "exit";
				NextDiag.TempNode = "Maltie_officer";
			}
			
			if (SandBoxMode)
			{
				dialog.text = "Monsieur, I must gently remind you that you are inside a military cantonment. Behave accordingly.";
				link.l1 = "Yes, sir. Of course.";
				link.l1.go = "exit";
				NextDiag.TempNode = "Maltie_officer";
			}
		break;
		
		case "Maltie_officer_1":
			DelLandQuestMark(npchar);
			dialog.text = "Michel de Monper is currently under guard in one of our casemates, held under the personal order of Chevalier Philippe de Poincy. Head downstairs to the lower level. You will find the casemates that we use for storage and cells there. I think you can find your way.";
			link.l1 = "Thank you!";
			link.l1.go = "exit";
			NextDiag.TempNode = "Maltie_officer";
			QuestPointerToLoc("FortFrance_Dungeon", "quest", "quest1");
		break;
		// офицер базы
		
		// --> солдаты базы
		case "Maltie_soldier":
			dialog.text = "Hello, Monsieur. Can I help you with anything?";
			link.l1 = "Thank you, soldier, but no, I'm quite alright. Carry on.";
			link.l1.go = "exit";
			NextDiag.TempNode = "Maltie_soldier";
		break;
		// --> солдаты базы
		
		// --> мальтиец-проводник
		case "Sharlie_maltie":
			dialog.text = "Thank you for waiting, Monsieur. So you are looking for Michel de Monper? You are his brother?";
			link.l1 = "Yes, that's correct. I am his brother Charles. I must see him right away. Is Michel in trouble?";
			link.l1.go = "Sharlie_maltie_1";			
		break;
		
		case "Sharlie_maltie_1":
			dialog.text = "Unfortunately he is, Monsieur. Michel is locked up in one of the casemates below. Chevalier de Poincy, the Governor-General of the French colonies in the New World, personally signed the order for his arrest. All of us were shocked. Your brother is an exemplar of manly virtue, discipline, and courage, the pride of our Order! The worst part is that we, his friends, have to lock him behind bars and guard him as a common criminal! We do everything in our power to make him comfortable, but... prison is still prison.";
			link.l1 = "What is he accused of? Has he committed a crime?";
			link.l1.go = "Sharlie_maltie_1_1";			
		break;
		
		case "Sharlie_maltie_1_1":
			dialog.text = "The Governor-General's office accused Michel of embezzlement! How ridiculous! All of us here are convinced it is politically motivated. I will tell you something in confidence. Michel has been taking part in certain covert actions on behalf of the Order. Perhaps he found out more than he should have. Or worse, angered some powerful men. But stealing money? Nobody believes that. It is a pretense, not a real reason, a cowardly and ignoble pretense! But enough words. Your brother is looking forward to seeing you, I am sure he will tell you everything himself.";
			link.l1 = "Good. Where is your prison located?";
			link.l1.go = "Sharlie_maltie_1_2";
		break;
		
		case "Sharlie_maltie_1_2":
			dialog.text = "In our underground armory, right here in the city. Follow me. I'll show you the way.";
			link.l1 = "...";
			link.l1.go = "Sharlie_maltie_2";
		break;
		
		case "Sharlie_maltie_2":
			DialogExit();
			LAi_ActorGoToLocation(npchar, "reload", "reload1_back", "FortFrance_town", "officers", "reload7_1", "Maltie_GoTown", -1);
		break;
		
		case "Sharlie_maltie_3":
			DelLandQuestMark(npchar);
			AddLandQuestMark(characterFromId("Maltie_officer"), "questmarkmain");
			dialog.text = "Here we are. This is our base of operations - the Caribbean Chapter of the Military Hospitaller Order of Saint John of Jerusalem, of Rhodes and of Malta. The casemates are below us. Go down the hall past the dining room and the chapel. The stairs there will take you to the lower level. Look for a corridor lined with cells. You will find your brother in one near the back.\nGo, Charles, and God be with you. Please help Michel! He is blameless, everyone here is ready to swear on it.";
			link.l1 = "The whole reason I came to this shithole is to see my brother. I hope I'll be able to get him out of this predicament at least.";
			link.l1.go = "Sharlie_maltie_4";
		break;
		
		case "Sharlie_maltie_4":
			DialogExit();
			chrDisableReloadToLocation = false;//открыть локацию
			npchar.lifeday = 0;
			LAi_ActorGoToLocator(npchar, "goto", "goto1", "none", -1);
		break;
		
		//belamour cle -->
		case "Sharlie_maltieA":
			dialog.text = "So you were searching for Michel de Monper? And you are his brother?";
			link.l1 = "Yes, that's correct. I am his brother Charles. I need to see him right away. He's got into trouble, hasn't he?";
			link.l1.go = "Sharlie_maltie_1a";			
		break;
		
		case "Sharlie_maltie_1a":
			dialog.text = "Unfortunately, he has, Monsieur. Michel is under arrest and locked in our prison. Chevalier de Poincy the general-governor of French colonies himself given and signed the orders. All of us were shocked.\nYour brother is an example of manhood, firmness and courage, a pride of our Order! The worst part is that we, his friends, have to lock his cell and guard him as a criminal! We do everything to ease his state, but... prison is a prison.";
			link.l1 = "So what is he being accused of? Has he committed a crime?";
			link.l1.go = "Sharlie_maltie_1_1a";			
		break;
		
		case "Sharlie_maltie_1_1a":
			dialog.text = "Nonsense! A pure nonsense! They have accused Michel of peculation and stealing money of the state. Ridiculous! All of us are sure that it is just a political game. Michel had been taking part in secret operations of the Order, perhaps, he learnt more than he should have.\nOr something else. But stealing money! Nobody believes that. It is just a pretense, not a reason, such a rude and stupid pretense! But enough words. Your brother is looking forward to seeing you, I am sure he will tell you everything himself.";
			link.l1 = "Good. Where is the prison located?";
			link.l1.go = "Sharlie_maltie_1_2a";
		break;
		
		case "Sharlie_maltie_1_2a":
			dialog.text = "It's located in our underground base, here in the city. Follow me. I'll show you the way.";
			link.l1 = "...";
			link.l1.go = "Sharlie_maltie_2a";
		break;
		
		case "Sharlie_maltie_2a":
			DialogExit();
			//LAi_ActorGoToLocation(npchar, "reload", "reloadPr1", "FortFrance_Dungeon", "reload", "reload1", "", -1);
			Pchar.quest.Sharlie_Maltie.win_condition.l1 = "location";
			Pchar.quest.Sharlie_Maltie.win_condition.l1.location = "FortFrance_town";
			Pchar.quest.Sharlie_Maltie.win_condition = "Maltie_GoBasement";
			QuestPointerDelLoc("FortFrance_prison", "reload", "reload1");
		break;
		//<-- cle
		// мальтиец-проводник
		
		// --> найм матросов
		case "Sharlie_sailor":
			DelLandQuestMark(npchar);
			dialog.text = "E poi si è sporgiato fuori bordo e ha vomitato così tanto che perfino i Caraibi sono diventati verdi! Ah ah ah!";
			link.l1 = "Alonso?";
			link.l1.go = "Sharlie_sailor_1";
		break;
		
		case "Sharlie_sailor_1":
			dialog.text = "Oh! Charles, stavo proprio raccontando ai ragazzi delle nostre avventure!";
			link.l1 = "L’ho notato. Ascolta, Alonso. Sono diventato capitano...";
			link.l1.go = "Sharlie_sailor_2";
		break;
		
		case "Sharlie_sailor_2":
			dialog.text = "Già? Pensavo ci volesse almeno un mese, ah ah!";
			link.l1 = "Parlo sul serio!";
			link.l1.go = "Sharlie_sailor_3";
		break;
		
		case "Sharlie_sailor_3":
			dialog.text = "Se fosse solo per me, accetterei subito. Ma ho quaranta uomini della Ulysse con me. Hanno affidato a me il loro futuro; devo essere sicuro che non li deluderai\n"+
			"Che tipo di nave avete?";
			link.l1 = "Una nave come tutte le altre, "+GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(RealShips[sti(pchar.ship.type)].basetype), "Name")))+". È così importante?";
			link.l1.go = "Sharlie_sailor_4";
		break;
		
		case "Sharlie_sailor_4":
			dialog.text = "Sa, dopo la Ulysse preferiremmo non servire su una barca o una tartana qualsiasi. Abbiamo già visto la vostra nave e ai ragazzi piace\n"+
			"Ora, il denaro. Chiediamo 4.800 pesos in anticipo. Poi – come sempre – si divide. Nulla di esagerato, te lo assicuro. Ce la fai?";
			if (sti(Pchar.money) >= 4800)
			{
				link.l1 = "D’accordo! Ecco le vostre monete.";
				link.l1.go = "Sharlie_sailor_5";
			}
			link.l2 = "Unfortunately, I don't have that much money on me right now.";
			link.l2.go = "Sharlie_sailor_nomoney";
		break;
		
		case "Sharlie_sailor_5":
			if (GetSquadronGoods(pchar, GOOD_FOOD) < 20 || GetSquadronGoods(pchar, GOOD_MEDICAMENT) < 30)
			{
				dialog.text = "Do you have victuals in the hold, cap'n? And medicine? No? Well, that's no good. Go out and get the minimum for our voyage and then come back and we'll talk. Go to the store and get what you need.";
				link.l1 = "Hm. You're right. Alright, I'll do that.";
				link.l1.go = "exit";
				NextDiag.TempNode = "Sharlie_sailor_again";
			}
			else
			{
				AddMoneyToCharacter(pchar, -4800);
				dialog.text = "Bah! Congratulazioni... Capitano! Raduno subito i ragazzi e saliamo sulla vostra nave.";
				link.l1 = "Felice di continuare la nostra avventura, Alonso. Prepara la nave per salpare!";
				link.l1.go = "Sharlie_sailor_6";
			}
		break;
		
		case "Sharlie_sailor_6":
			DialogExit();
			LAi_SetStayType(npchar);
			GetCharacterPos(pchar, &locx, &locy, &locz);
			ChangeCharacterAddressGroup(npchar, "Fortfrance_tavern", "goto", LAi_FindNearestFreeLocator("goto", locx, locy, locz));
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1_back", "", "", "", "", 5);
			npchar.lifeday = 0;
			SetCrewQuantityOverMax(PChar, 40);
			pchar.Ship.Crew.Morale = 50;
			pchar.Ship.Crew.Exp.Sailors = 50;
			pchar.Ship.Crew.Exp.Cannoners = 50;
			pchar.Ship.Crew.Exp.Soldiers = 50;
			AddQuestRecord("Sharlie", "7");
			pchar.questTemp.Sharlie = "skiper";
			DeleteAttribute(pchar, "GenQuest.CannotWait");//снимаем запрет, если не был снят раньше
			AddLandQuestMark(characterFromId("FortFrance_tavernkeeper"), "questmarkmain");
		break;
		
		case "Sharlie_sailor_nomoney":
			dialog.text = "Well as soon as you find enough money, come back. You'll find us here in the tavern. Aren't any other ships around anyway. We'll just keep on drinking and whoring our money away, harhar!";
			link.l1 = "I'll try to be back as soon as possible.";
			link.l1.go = "exit";
			NextDiag.TempNode = "Sharlie_sailor_again";
		break;
		
		case "Sharlie_sailor_again":
			dialog.text = "You back, cap'n? Ready to hire me and my messmates? Our purses are starting to feel light, need to feel the sea breeze on our faces again!";
			if (sti(Pchar.money) < 4800)
			{
				link.l1 = "Not yet, I'm still getting everything ready.";
				link.l1.go = "exit";
				NextDiag.TempNode = "Sharlie_sailor_again";
			}
			else
			{
				link.l1 = "Yes. Take your advance. Now you are at my service.";
				link.l1.go = "Sharlie_sailor_5";
			}
		break;
		// найм матросов
		
		// наводчик на штурмана
		case "skipertalker":
			DelLandQuestMark(npchar);
			dialog.text = LinkRandPhrase("Ahoy cap'n! What do you need?","Hello Monsieur. What can I do for you?","Good day. What do you want?");
			link.l1 = RandPhraseSimple("I've got a question for you.", "I need information about this colony.");
			link.l1.go = "skipertalker_1";
			link.l2 = "Just saying hello. Au revoir!";
			link.l2.go = "exit";
			NextDiag.TempNode = "skipertalker";
		break;
		
		case "skipertalker_1":
			dialog.text = RandPhraseSimple("What is it?", "What do you need?");
			link.l1 = "Listen, "+GetAddress_FormToNPC(NPChar)+", here's the thing... I'm looking for a navigator. Perhaps you know somebody fit for the job here in town?";
			link.l1.go = "skipertalker_2";
		break;
		
		case "skipertalker_2":
			dialog.text = "A Navigator? Hm. Well, I know one... There's just one problem - he's in jail, debtor's prison. Poor bastard's been locked up in the casemates for near a month now until he or someone else pays what he owes.";
			link.l1 = "A debtor? Hm... What's his name?";
			link.l1.go = "skipertalker_3";
		break;
		
		case "skipertalker_3":
			dialog.text = "His name's Folke Deluc. Ask the prison commandant if you want to see him. But I don't think they'll let him walk out out of there unless you pay his debt, because he sure isn't, hahaha!";
			link.l1 = "Maybe I will. Thanks for the information, friend.";
			link.l1.go = "exit";
			LAi_CharacterDisableDialog(npchar);
			npchar.lifeday = 0;
			pchar.questTemp.Sharlie = "jailskiper";
			AddQuestRecord("Sharlie", "8");
			LocatorReloadEnterDisable("Fortfrance_town", "reload_jail", false);
			SetFunctionLocationCondition("FortfranceJailOff_AddQuestMark", "fortfrance_prison", false);
		break;
		
		// --> штурман
		case "Folke":
			dialog.text = "To what do I owe such an honor, Monsieur?";
			link.l1 = "Hello, Folke. It's simple, I've got a ship, but no navigator. And I need one. So I've bought out your debt...";
			link.l1.go = "Folke_1";
		break;
		
		case "Folke_1":
			dialog.text = "You're saying that you dragged me out of here to take me on your crew?";
			link.l1 = "Exactly. I think you'll quickly make up for the money I've spent on you. Well... we'll see how it goes.";
			link.l1.go = "Folke_2";
		break;
		
		case "Folke_2":
			dialog.text = "My gratitude, Monsieur. I've grown sick of this rotten, damp cell. It would give me great pleasure to get back aboard once more. Ah, the sea...";
			link.l1 = "I'm glad we've reached an understanding, Folke. One more thing, do you have any other skills besides steering a ship?";
			link.l1.go = "Folke_3";
		break;
		
		case "Folke_3":
			dialog.text = "A little bit of everything, captain. I used to serve aboard a privateer for the Dutch West India Company. I learnt there how to handle cannons, so I can serve as gunnery officer if you need me. Trading and boarding are my weakest suits.";
			link.l1 = "Thank you for sharing, now follow me to the ship. I want you to watch the crew with your experienced eye as they prepare everything for departure. Then, I want to head to Guadeloupe as soon as possible.";
			link.l1.go = "Folke_4";
		break;
		
		case "Folke_4":
			dialog.text = "Aye aye, captain! I'll wait for you in your cabin. *Use the action menu while at sea to access the cabin and other areas of the ship*";
			link.l1 = "Thank you, Folke. See you aboard.";
			link.l1.go = "Folke_5";
			Log_Info("You have received amulet 'Merchant's Rosary'");
			PlaySound("interface\important_item.wav");
			GiveItem2Character(pchar, "obereg_8");
			if(CheckAttribute(pchar,"systeminfo.tutorial.Amulet"))
			{
				DoQuestFunctionDelay("Tutorial_Amulet", 0.1);
			}
		break;
		
		case "Folke_5":
			DialogExit();
			EndQuestMovie();
			chrDisableReloadToLocation = false;//открыть локацию
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);//разрешить драться
			AddQuestRecord("Sharlie", "10");
			LAi_SetActorType(npchar);
			LAi_ActorFollowEverywhere(npchar, "", -1);
			pchar.quest.Sharlie_skiper.win_condition.l1 = "location";
			pchar.quest.Sharlie_skiper.win_condition.l1.location = "My_Cabin_Small";
			pchar.quest.Sharlie_skiper.function = "Sharlie_SkiperTalk";
			//прерывание на засаду пиратов - принудительный квест
			pchar.quest.Sharlie_seabattle.win_condition.l1 = "location";
			pchar.quest.Sharlie_seabattle.win_condition.l1.location = "Fortfrance_town";
			pchar.quest.Sharlie_seabattle.function = "SharlieSeabattle_agent";
			
			pchar.quest.NewGameTip2.win_condition.l1 = "location";
			pchar.quest.NewGameTip2.win_condition.l1.location = "Martinique";
			pchar.quest.NewGameTip2.function = "ShowNewGameTip";
			pchar.quest.NewGameTip2.text = "Your first officer is waiting for you. Use the action menu (ENTER) to go to the cabin.";
		break;
		
		case "Folke_6":
			pchar.GenQuest.StoreGoods.StoreIdx = Fortfrance_STORE;
			pchar.GenQuest.StoreGoods.Starting = true; // заполняем магазин 250912
			dialog.text = "A fine lugger, captain! Quite a decent little ship with fine rigging and sound timbers. With a ship like this we not only will safely reach Guadeloupe, but even cruise the whole Caribbean if we wish.";
			link.l1 = "Excellent. At least I didn't throw my money away on a leaky tub... Do you have any advice before we set sail, Folke?";
			link.l1.go = "Folke_8";
		break;
		
		case "Folke_7":
			dialog.text = "Damn me, this sloop is leaking like a sieve, captain. It'll be a near run thing for us to cross over to Guadeloupe. If you want to arrive at Basse-Terre in one piece she'll have to be put in for repair at the shipyard immediately.";
			link.l1 = "I didn't have a choice, this was the only vessel for sale! And they charged me a pretty penny for her. As you know, we don't have the time to fix her at the moment... Do you have any advice before we set sail?";
			link.l1.go = "Folke_8";
		break;
		
		bOk = (GetSquadronGoods(pchar, GOOD_BALLS) >= 80) && (GetSquadronGoods(pchar, GOOD_GRAPES) >= 80) && (GetSquadronGoods(pchar, GOOD_KNIPPELS) >= 80) && (GetSquadronGoods(pchar, GOOD_BOMBS) >= 80) && (GetSquadronGoods(pchar, GOOD_POWDER) >= 180);
		case "Folke_8":
			if (bOk)
			{
				dialog.text = "Siamo ben forniti di polvere e palle, capitano. Per ora basta; ricordate solo di rifornirvi in tempo.";
				link.l1 = "Well, that goes without saying. Any other comments?";
				link.l1.go = "Folke_10";
				if (CheckCharacterItem(PChar, "BoxOfBalls"))
				{
					link.l2 = "Ah! Grazie per il promemoria. Ho proprio una cassa intera di palle con me!";
					link.l2.go = "Folke_8_1";
				}
			}
			else
			{
				dialog.text = "We don't have enough ammunition in the magazine, captain. We need to have at least one hundred cannon balls, chain shot, and bombs, as well as one hundred bags of grape shot and two hundred barrels of gunpowder. Buy up the necessary materiel, captain. It won't cost much, but it'll save our lives if we get attacked by pirates or the Spanish.";
				link.l1 = "A worthy investment. I'm off to the merchant.";
				link.l1.go = "Folke_9";
			}
		break;
		
		case "Folke_8_1":
			dialog.text = "...E da quanto tempo la portate con voi?";
			link.l1 = "Quasi due settimane.";
			link.l1.go = "Folke_8_2";
			TakeItemFromCharacter(pchar, "BoxOfBalls");
			//AddCharacterGoodsSimple(sld, GOOD_BALLS, 10);
		break;
		
		case "Folke_8_2":
			dialog.text = "Ma perché, capitano?!";
			link.l1 = "Mi piace raccogliere ogni sorta di cose. Non si sa mai cosa può tornare utile.";
			link.l1.go = "Folke_8_3";
		break;
		
		case "Folke_8_3":
			dialog.text = "Peccato per voi. Queste palle non entreranno mai nei nostri cannoni giocattolo. Non ho mai visto palle così grandi. Una sola manderebbe l’Adeline a fondo.";
			link.l1 = "...";
			link.l1.go = "Folke_10";
		break;
		
		case "Folke_9":
			DialogExit();
			NextDiag.CurrentNode = "Folke_goods_1";
			LAi_SetStayType(npchar);
			AddQuestRecord("Sharlie", "12");
		break;
		
		case "Folke_goods_1":
			dialog.text = "Have you finished buying up ammunition, captain?";
			if (bOk)
			{
				link.l1 = "Yes, I have. Any other comments?";
				link.l1.go = "Folke_10";
			}
			else
			{
				link.l1 = "Not right now, I'm still working on it.";
				link.l1.go = "exit";
				NextDiag.TempNode = "Folke_goods_1";
			}
		break;
		
		bOk = (GetSquadronGoods(pchar, GOOD_WEAPON) >= 50);
		case "Folke_10":
			if (bOk)
			{
				dialog.text = "Well done, you have bought enough arms for your crew. If we don't have enough weapons, we'll lose far more men during boarding actions. God protect us from that. Don't forget to frequently check the amount in the cargo hold\nIt's prudent to keep a few more weapons than we'll need. The damn rats like to gnaw on the wooden handles and stocks.";
				link.l1 = "Understood. I see there's still something you want to add?";
				link.l1.go = "Folke_11";
			}
			else
			{
				dialog.text = "We don't have enough weapons on board for crew. If we don't have enough weapons, we'll lose far more men during boarding actions. God protect us from that. As far as I understand, you have forty men in the crew\nBuy enough weapons for each, or even buy a few extra, fifty sets should suffice. It's prudent to keep a few more weapons than we'll need. The damn rats like to gnaw on the wooden handles and stocks.";
				link.l1 = "That's what I'll do. I'll be back soon.";
				link.l1.go = "Folke_10_1";
			}
		break;
		
		case "Folke_10_1":
			DialogExit();
			NextDiag.CurrentNode = "Folke_goods_2";
			LAi_SetStayType(npchar);
			AddQuestRecord("Sharlie", "13");
		break;
		
		case "Folke_goods_2":
			dialog.text = "Have you finished buying the weapons, captain?";
			if (bOk)
			{
				link.l1 = "The weapons are in the hold. I see there's still something you want to add?";
				link.l1.go = "Folke_11";
			}
			else
			{
				link.l1 = "Not right now, I'm still working on it.";
				link.l1.go = "exit";
				NextDiag.TempNode = "Folke_goods_2";
			}
		break;
		
		bOk = (GetSquadronGoods(pchar, GOOD_FOOD) >= 100) && (GetSquadronGoods(pchar, GOOD_RUM) >= 10);
		case "Folke_11":
			if (bOk)
			{
				dialog.text = "No, I think that's it. We have enough food, you've also taken care of rum for the crew. That's wise, since there's no better cure for all ailments as a nice cool jigger of rum after your shift. Sailors love and respect captains who give them their daily rum ration. You never want to hear your men ask: 'Why is the rum gone?'";
				link.l1 = "Can we set sail now?";
				link.l1.go = "Folke_12";
			}
			else
			{
				dialog.text = "Yes. Food and rum. It is disastrous if you don't have enough food on board. Always have more victuals than you think you'll need. You never know how long a voyage will last - a dead calm or a strong gale can ruin any plan. The men will mutiny or die of hunger when the provisions are gone\nThe rum supply is not as critical, but I strongly recommend always keeping some on board, there's no better cure for all ailments as a nice cool jigger of rum after your shift. Sailors love and respect captains who give them their daily rum ration\nSo go and buy the supplies we need - at least a hundred crates of food and ten barrels of rum. You never want to hear your men ask: 'Why is the rum gone?'";
				link.l1 = "I guess you're right. I'll go revisit the merchant.";
				link.l1.go = "Folke_11_1";
			}
		break;
		
		case "Folke_11_1":
			DialogExit();
			NextDiag.CurrentNode = "Folke_goods_3";
			LAi_SetStayType(npchar);
			AddQuestRecord("Sharlie", "14");
		break;
		
		case "Folke_goods_3":
			dialog.text = "Have you finished buying our food and rum, captain?";
			if (bOk)
			{
				link.l1 = "Yes. Can we set sail now?";
				link.l1.go = "Folke_12";
			}
			else
			{
				link.l1 = "No, I'm still working on it.";
				link.l1.go = "exit";
				NextDiag.TempNode = "Folke_goods_3";
			}
		break;
		
		case "Folke_12":
			dialog.text = "Aye, cap. We can raise anchor and head north towards Guadeloupe, as you wanted.";
			// belamour legendary edition -->
			link.l1 = "Great job, Folke. I wouldn't have made it without you.";
			link.l1.go = "Folke_13";
			link.l2 = "All right, let's get to work, let's see if you're worth the money.";
			link.l2.go = "Folke_13a";
		break;
		
		case "Folke_13a":
			Npchar.loyality = makeint(Npchar.loyality) - 5;
			ChangeCharacterComplexReputation(pchar,"authority", 5);
			dialog.text = "Then set me as navigator and I will go to my place on deck.";
			link.l1 = "...";
			link.l1.go = "Folke_14";
		break;
		
		case "Folke_13":
			Npchar.loyality = makeint(Npchar.loyality) + 5;
			AddCharacterExpToSkill(pchar, "Leadership", 150);
			// <-- legendary edition
			dialog.text = "Then set me as navigator and I will go to my place on deck.";
			link.l1 = "...";
			link.l1.go = "Folke_14";
		break;
		
		case "Folke_14":
			DialogExit();
			LAi_SetStayType(npchar);
			LAi_SetImmortal(npchar, false);
			AddQuestRecord("Sharlie", "15");
			pchar.questTemp.Sharlie = "seabattle";//в Ле Франсуа
			DeleteAttribute(pchar, "NoNavyPenalty"); // штрафуем за нехватку навигации
			
			npchar.quest.OfficerPrice = 20;
			npchar.loyality = 30;
			
			// --> копипаста LandEnc_OfficerHired
			AddPassenger(pchar, npchar, false);
			npchar.Payment = true;
			npchar.DontClearDead = true;
			SaveCurrentNpcQuestDateParam(npchar, "HiredDate");
			// <--
			
			pchar.questTemp.HelenDrinking.TakeFolke = true;
			
			DoQuestFunctionDelay("Tutorial_Navigator2", 1.0);
			//DoQuestFunctionDelay("Ngt_FolkeEng", 3.0);
			//NewGameTip("Welcome aboard your new officer! Press F4 to assign him as your Navigator.");
			pchar.questTemp.Sharlie.FolkeWait = true;
			LocatorReloadEnterDisable("My_Cabin_Small", "reload1", true);
			NextDiag.CurrentNode = "Folke_wait";
		break;
		
		case "Folke_wait":
			dialog.text = "Ready to cast off, captain!";
			link.l1 = "...";
			
			if (!CheckAttribute(npchar, "navigator")) {
				dialog.text = "Captain, set me as navigator, otherwise we'll run aground in a hurry.";
				link.l1 = "Got it, I'll do it now.";
			}
			
			link.l1.go = "exit";
			NextDiag.TempNode = "Folke_wait";
		break;
	
		// штурман

	// --> пират-обманщик
		case "Seabattle_pirate":
			dialog.text = "My apologies. "+GetFullName(pchar)+"?";
			link.l1 = "Correct. What do I owe for this occasion, sir?";
			link.l1.go = "Seabattle_pirate_1";
		break;
		
		case "Seabattle_pirate_1":
			dialog.text = "Allow me to introduce myself - "+GetFullName(npchar)+". I've been sent here by Cesar Craig. You must know him. He's the owner of the tavern at Le Francois. As far as he is informed, you are about to depart to Guadeloupe. He would like to offer you some easy money.";
			link.l1 = "Hm... Interesting! And how has Cesar Craig become so well-informed?";
			link.l1.go = "Seabattle_pirate_2";
		break;
		
		case "Seabattle_pirate_2":
			dialog.text = "It's simple, captain. Your ship is the only ship in St. Pierre at the moment, anyone with two ears and an eye knows everything about who you are and where you're going. Out here in the colonies, rumors fly around faster than seagulls. So are you interested in hearing our offer?";
			link.l1 = "Sure. I'm never opposed to making some money.";
			link.l1.go = "Seabattle_pirate_3";
		break;
		
		case "Seabattle_pirate_3":
			dialog.text = "Now we're talking, matey! I can see you have a keen nose for business. Here's the deal. Cesar urgently needs a batch of wine delivered to Guadeloupe. Two hundred barrels, your ship's hold can take that easily. The pay is ten thousand pesos for an easy job - Cesar is in a hurry, and your ship is the only ship in the harbor right now. You must agree, such profitable proposals are rare.";
			link.l1 = "Damn, ten thousand pesos? Well, we have a deal!";
			link.l1.go = "Seabattle_pirate_4";
		break;
		
		case "Seabattle_pirate_4":
			dialog.text = "Head to Le Francois and speak with Cesar. He'll take care of everything. All you'll have to do is anchor in the bay just outside Le Francois. Don't let me down matey, Cesar promised me a thousand pesos if I convinced you...";
			link.l1 = "Don't worry, consider me convinced. As soon as I'm ready to depart, I will sail directly to Le Francois.";
			link.l1.go = "Seabattle_pirate_5";
		break;
		
		case "Seabattle_pirate_5":
			dialog.text = "Hurrah! I'm off to get my thousand. Thanks, matey!";
			link.l1 = "You're welcome...";
			link.l1.go = "Seabattle_pirate_6";
		break;
		
		case "Seabattle_pirate_6":
			DialogExit();
			AddLandQuestMark(characterFromId("LeFransua_tavernkeeper"), "questmarkmain");
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "gate_back", "", "", "", "", -1);
			AddQuestRecord("Sharlie", "11");
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);//разрешить драться
			chrDisableReloadToLocation = false;//открыть локацию
			npchar.location = "None";
		break;
	// пират-обманщик

	// офицер Гриффондора
		case "griffondor_officer":
			dialog.text = "";
			link.l1 = "";
			link.l1.go = "exit";
		break;

	// командир абордажной роты по защите Сен-Пьера
		case "rosetti":
			PlaySound("Voice\English\EvilPirates01.wav");
			dialog.text = "Captain, boarding party is formed and ready! Awaiting your orders!";
			link.l1 = "";
			link.l1.go = "rosetti_1";
		break;
		
		case "rosetti_1":
			DialogExit();
			bDisableCharacterMenu = true;//лоченые интерфейсы
			ChangeShowIntarface();
			LAi_SetActorType(pchar);
			SetMainCharacterIndex(GetCharacterIndex("DefendSP_soldier_0"));
			PChar = GetMainCharacter();			
			LAi_SetPlayerType(PChar);
			sld = characterFromId("Blaze");
			sld.dialog.filename = "MainHero_dialog.c";
			sld.dialog.currentnode = "SP_defend";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 0.5);
		break;
		
		case "rosetti_2":
			PlaySound("interface\abordage_wining.wav");
			dialog.text = "Aye aye, captain! Get ready boys, follow the captain! Hut, one-two-three!";
			link.l1 = "";
			link.l1.go = "rosetti_3";
		break;
		
		case "rosetti_3":
			DialogExit();
			PlaySound("interface\abordage_wining.wav");
			bDisableCharacterMenu = false;//лоченые интерфейсы
			ChangeShowIntarface();
			for (i=0; i<=12; i++)
			{
				sld = CharacterFromID("DefendSP_soldier_"+i);
				LAi_SetActorType(sld);
				LAi_ActorFollowEverywhere(sld, "", -1);
				LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
			}
			// прерывание на джунгли перед выходом из города
			pchar.quest.DefendSP_jungle1.win_condition.l1 = "location";
			pchar.quest.DefendSP_jungle1.win_condition.l1.location = "Martinique_jungle_01";
			pchar.quest.DefendSP_jungle1.function = "DefendSP_SpainPatrol";
		break;
		
		case "spain_patrol":
			dialog.text = "Mierda, French reinforcements! Form ranks! Lorenzo, get to camp and sound the alarm! Die, you fuckers!";
			link.l1 = "...";
			link.l1.go = "spain_patrol_1";
		break;
		
		case "spain_patrol_1":
			DialogExit();
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);//разрешить драться
			for (i=1; i<=4; i++)
			{
				sld = CharacterFromID("DefendSP_spapatrol_"+i);
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "EnemyFight");
				LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
				LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
				LAi_group_SetCheck("EnemyFight", "DefendSP_SpaPatrolDie");
				AddDialogExitQuest("MainHeroFightModeOn");
			}
			sld = CharacterFromID("DefendSP_spapatrol_5");
			LAi_ActorRunToLocation(sld, "reload", "reload2_back", "none", "", "", "DefendSP_GateAlarm", -1);
		break;

	// страж истины
		case "spanish":
			dialog.text = "Do you understand that I am not authorized to disseminate such information?";
			link.l1 = "Do you understand that it's only thanks to my timely interruption that St. Pierre wasn't ravaged by the Spanish? My brother has vanished, abandoning the Order! He must have done that for a reason. I, as a representative of Sir Philippe de Poincy, am authorized to investigate!";
			link.l1.go = "spanish_1";
		break;
		
		case "spanish_1":
			dialog.text = "Alright, alright, Monsieur de Maure. I will answer your questions. Calm yourself down first. Now ask away.";
			link.l1 = "What happened prior to Michel being locked up under guard?";
			link.l1.go = "spanish_2";
		break;
		
		case "spanish_2":
			dialog.text = "Michel de Monper was negotiating with some pirate barons to arrange a regime change on Tortuga.";
			link.l1 = "That I know already. What else?";
			link.l1.go = "spanish_3";
		break;
		
		case "spanish_3":
			dialog.text = "He was also planning a different operation against the Spanish. To be specific - the capture of a Spanish ship with some valuable cargo on board. Michel was supposed to lure the target under the guns of the light frigate 'Gryffondor'. We didn't see hide or hair of him for quite some time while he was planning this.\nBut the plan went awry. The Spanish transport didn't arrive and Michel himself was found by local fishermen washed up on the shores of Le Marin Bay, half-dead. It seems that the operation was a failure.\nWar is war, and things go wrong. It was a miracle Michel survived at all, but Chevalier de Poincy flew into a rage. He accused Michel of embezzling the Order's money and had him imprisoned. Of course, we didn't believe a word of those accusations. Michel is an honest man, a true knight of the Order. Only God knows what set the Governor-General off. Perhaps, Chevalier de Poincy will tell you himself?";
			link.l1 = "Possibly. Is that all you know?";
			link.l1.go = "spanish_4";
		break;
		
		case "spanish_4":
			dialog.text = "Unfortunately, there is nothing more to be said. The details of your brother's operations were known only to himself and Chevalier de Poincy. We are knights of the Order of St. John of Malta. We carry out our orders.";
			link.l1 = "If the Chevalier trusts Michel so much, he must have been successful carrying out his secret plans before. Do you know of any successful actions Michel pulled off?";
			link.l1.go = "spanish_5";
		break;
		
		case "spanish_5":
			dialog.text = "Most definitely. This recent failure by Michel de Monper was also his first failure, which is why we were shocked by the Chevalier's reaction. Not long ago, 'Gryffindor' captured a Spanish treasure galleon packed with silver thanks to Michel's careful planning. That alone should have compensated for dozens of failures in the future. And yet, your brother was arrested.";
			link.l1 = "I see. Do you have any idea why Michel fled St. Pierre?";
			link.l1.go = "spanish_6";
		break;
		
		case "spanish_6":
			dialog.text = "I suspect that an interpersonal conflict between Michel and de Poincy was the reason he was arrested. Obviously, your brother fears that the Chevalier will continue to persecute him even after his release, so he took precautionary measures. And you know what, Monsieur de Maure - nobody here blames him for his decision!\nThe man had been working bravely for the good of the Order and yet they flung him into a fetid cell for his very first failure, while critically wounded! A failure that wasn't even that bad, no one died and no ships sank!\nBy the way, this conversation is strictly off the record and I won't repeat what I have just said even under oath, are we clear on that, Monsieur de Maure?";
			link.l1 = "Yes, sir. I've already forgotten we've had this conversation. Tell me, could the Spanish attack on St. Pierre have been provoked by the Order raiding Spanish shipping? Perhaps that same Spanish galleon with silver that you mentioned? The Castilians were extremely zealous in seeking out your base...";
			link.l1.go = "spanish_7";
		break;
		
		case "spanish_7":
			dialog.text = "Doubt it. Very few people know about the Order's presence in the Caribbean and all of our sorties against the Spanish were carefully planned. Ask the Spanish officer we took prisoner, he is cooling his fiery Castilian temper in our casements right now. We have already interrogated him. The attack of St. Pierre was an ordinary raid, organized by a Spanish grand baron named Ramon de Mendoza y Riba for the purpose of his own profit and to intimidate the French colonies. He also wanted to garner favor with the Escorial.";
			link.l1 = "I will speak to this Spaniard. Where can I find him?";
			link.l1.go = "spanish_8";
		break;
		
		case "spanish_8":
			dialog.text = "Downstairs, in the same cell where your brother was held.";
			link.l1 = "I know the way. I'll be back after I interrogate the Spaniard. I may have some additional questions.";
			link.l1.go = "spanish_9";
		break;
		
		case "spanish_9":
			DialogExit();
			NextDiag.CurrentNode = "Maltie_officer";
			AddQuestRecord("Guardoftruth", "2");
			pchar.questTemp.Guardoftruth = "prisoner";
			sld = characterFromId("spa_baseprisoner");
			LAi_CharacterEnableDialog(sld);
			chrDisableReloadToLocation = true;//закрыть локацию
		break;
		
		case "spanish_10":
			dialog.text = "Well, isn't this something! You understand that I can't release that captive, right? That villain helped lead the attack on St. Pierre!";
			link.l1 = "Officer, this is an important witness. The attack on St. Pierre was not a simple raid looking for booty. Don Ramon Mendosa was looking for something else. We need to get a definitive motive. So will you release this Spaniard to me or will I have to demand permission from de Poincy?";
			link.l1.go = "spanish_11";
		break;
		
		case "spanish_11":
			dialog.text = "By God Almighty... Alright, take him. I was about to hang this bastard anyway in St. Pierre's square like the common pirate he is... Now he's your problem. See to it that he does not escape justice!";
			link.l1 = "Undoubtedly. I will answer for this Spaniard before de Poincy. Have this captive shackled and delivered to my longboat at the town dock.";
			link.l1.go = "spanish_12";
		break;
		
		case "spanish_12":
			dialog.text = "Very well, captain.";
			link.l1 = "One more thing, officer. Does the name Miguel Dichoso ring a bell to you?";
			link.l1.go = "spanish_13";
		break;
		
		case "spanish_13":
			dialog.text = "No. I've never heard it before. Why are you asking?";
			link.l1 = "Are you sure? So you haven't met anyone by that name, neither here in your cantonment, nor in the governor's palace, nor anywhere in St. Pierre?";
			link.l1.go = "spanish_14";
		break;
		
		case "spanish_14":
			dialog.text = "No, I haven't. We don't think too well of Spaniards where I'm from.";
			link.l1 = "Alright. Anyway, that's to be expected. It would have been too easy... Thank you officer! You've been very helpful.";
			link.l1.go = "spanish_15";
		break;
		
		case "spanish_15":
			dialog.text = "You are welcome... What do you think, Monsieur de Maure, where is your brother now?";
			link.l1 = "I would like to know the answer to that question myself. And I will find out... sooner or later. Au revoir!";
			link.l1.go = "spanish_16";
		break;
		
		case "spanish_16":
			DialogExit();
			NextDiag.CurrentNode = "Maltie_officer";
			AddQuestRecord("Guardoftruth", "3");
			pchar.questTemp.Guardoftruth = "toship";
			sld = characterFromId("spa_baseprisoner");
			sld.dialog.currentnode = "spa_prisoner_28";
			LAi_CharacterEnableDialog(sld);
		break;
		
	// монах-посланник от Винсенто
		case "monk_vinsento":
			dialog.text = TimeGreeting()+"! Are you captain "+GetFullName(pchar)+"?";
			link.l1 = "Yes, it is me. What can I do for you?";
			link.l1.go = "monk_vinsento_1";
		break;
		
		case "monk_vinsento_1":
			dialog.text = "Greetings, captain. I've been sent to you by Father Vincento. I have something for you...";
			link.l1 = "Father Vincento? I don't work for His Grace anymore. Not after he sent Alonso de Maldonado, Diego de Montoya's sworn man, to kill me. You can pass this message to the Reverent Father: he failed.";
			link.l1.go = "monk_vinsento_2";
		break;
		
		case "monk_vinsento_2":
			dialog.text = "Wait, captain. Father Vincento expected such a reaction from you and warned me of this. I assure you that His Grace does not wish you any ill. Please, read this letter. It's very, very important.";
			link.l1 = "Father Vincento doesn't wish me any ill? Hm. Maybe he also failed to tell you anything about me and Don de Maldonado? I see why I should believe you.";
			link.l1.go = "monk_vinsento_3";
		break;
		
		case "monk_vinsento_3":
			dialog.text = "Take this letter, captain. Read it and make your own decision. Just know that the fate of all Christendom is in your hands. Do not take this lightly. May God bless you and set your feet on a righteous path!";
			link.l1 = "All right, give me the letter.";
			link.l1.go = "monk_vinsento_4";
		break;
		
		case "monk_vinsento_4":
			GiveItem2Character(pchar, "specialletter"); 
			ChangeItemDescribe("specialletter", "itmdescr_specialletter_vinsento");
			sld = ItemsFromID("specialletter");
			sld.text = "Letter_Vincento_last";
			dialog.text = "Here you go. I pray you will make the right decision. Pax vobiscum.";
			link.l1 = "...";
			link.l1.go = "monk_vinsento_5";
		break;
		
		case "monk_vinsento_5":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload4_back", "none", "", "", "", 30.0);
			ReOpenQuestHeader("Sharlie"); // patch-8
			AddQuestRecord("Sharlie", "40");
			CloseQuestHeader("Ksochitam");
		break;
		
	// падре Адриан
		case "adrian":
			dialog.text = "Greetings, my son. The Lord be with you.";
			link.l1 = "And also with you, Father Adrian. His Grace said that you can provide me with amulets and medicine.";
			link.l1.go = "adrian_1";
		break;
		
		case "adrian_1":
			dialog.text = "Yes, of course. I received a special shipment from Santiago just for you. Here are blessed amulets and healing potions. And to top it all off, a rare, unique Ometochtli tincture which will make you invincible in combat. This is all for you, my son. Take and see that the Lord is good.";
			link.l1 = "Thank you!";
			link.l1.go = "adrian_2";
		break;
		
		case "adrian_2":
			for(i=2; i<=10; i++)
			{
				if (i == 4 || i == 5 || i == 8 || i == 9) continue;
				TakeNItems(pchar, "amulet_"+i, 2);
			}
			TakeNItems(pchar, "potion2", 20);
			TakeNItems(pchar, "potion4", 10);
			TakeNItems(pchar, "potion7", 3);
			TakeNItems(pchar, "berserker_potion", 3);
			dialog.text = "If you do need any more healing herbs, I can provide you a vial of each every day. I will prepare as much of them as you need.";
			link.l1 = "You have my gratitude, Father Adrian. I'll keep that in mind.";
			link.l1.go = "exit";
			link.l2 = "Great. I need some right now.";
			link.l2.go = "potion";
			NextDiag.TempNode = "adrian_3";
		break;
		
		case "adrian_3":
			dialog.text = "God bless you and keep you, my son. What would you like?";
			link.l1 = "I would like to purchase some healing potions.";
			link.l1.go = "potion";
			link.l2 = "Nothing at the moment, I'm preparing for a journey. Just stopped by to say hello and see how you are doing.";
			link.l2.go = "exit";
			NextDiag.TempNode = "adrian_3";
		break;
		
		case "potion":
			dialog.text = "Of course, my son. What medicine do you need?";
			if (!CheckAttribute(npchar, "potion1_date") || GetNpcQuestPastDayParam(npchar, "potion1_date") >= 1)
			{
				link.l1 = "Just a simple remedy.";
				link.l1.go = "potion1";
			}
			if (!CheckAttribute(npchar, "potion2_date") || GetNpcQuestPastDayParam(npchar, "potion2_date") >= 1)
			{
				link.l2 = "A health-giving elixir.";
				link.l2.go = "potion2";
			}
			if (!CheckAttribute(npchar, "potion3_date") || GetNpcQuestPastDayParam(npchar, "potion3_date") >= 1)
			{
				link.l3 = "An antidote.";
				link.l3.go = "potion3";
			}
			if (!CheckAttribute(npchar, "potion4_date") || GetNpcQuestPastDayParam(npchar, "potion4_date") >= 1)
			{
				link.l4 = "An herbal mixture.";
				link.l4.go = "potion4";
			}
			link.l5 = "Sorry to trouble you, father. I've changed my mind.";
			link.l5.go = "exit";
		break;
		
		case "potion1":
			npchar.quest.price = 90;
			npchar.quest.type = 1;
			dialog.text = "A remedial essence? That is 90 pesos, my son. For materials of course.";
			if (sti(Pchar.money) >= 90)
			{
				link.l1 = "Thank you, father.";
				link.l1.go = "potion_pay";
			}
			else
			{
				link.l1 = "Unfortunately, I don't have the money... I'll return later.";
				link.l1.go = "exit";
			}
		break;
		
		case "potion2":
			npchar.quest.price = 500;
			npchar.quest.type = 2;
			dialog.text = "A health-giving elixir? 500 pesos, my son.";
			if (sti(Pchar.money) >= 500)
			{
				link.l1 = "Thank you, father.";
				link.l1.go = "potion_pay";
			}
			else
			{
				link.l1 = "Unfortunately, I don't have the money... I'll return later.";
				link.l1.go = "exit";
			}
		break;
		
		case "potion3":
			npchar.quest.price = 200;
			npchar.quest.type = 3;
			dialog.text = "An antidote? 200 pesos, my son.";
			if (sti(Pchar.money) >= 200)
			{
				link.l1 = "Thank you, father.";
				link.l1.go = "potion_pay";
			}
			else
			{
				link.l1 = "Unfortunately, I don't have the money... I'll return later.";
				link.l1.go = "exit";
			}
		break;
		
		case "potion4":
			npchar.quest.price = 900;
			npchar.quest.type = 4;
			dialog.text = "A herbal mixture? 900 pesos, my son.";
			if (sti(Pchar.money) >= 900)
			{
				link.l1 = "Thank you, father.";
				link.l1.go = "potion_pay";
			}
			else
			{
				link.l1 = "Unfortunately, I don't have the money... I'll return later.";
				link.l1.go = "exit";
			}
		break;
		
		case "potion_pay":
			AddMoneyToCharacter(pchar, -sti(npchar.quest.price));
			iTemp = sti(npchar.quest.type);
			GiveItem2Character(pchar, "potion"+iTemp);
			PlaySound("interface\important_item.wav");
			dialog.text = "'For I will restore health unto thee, and I will heal thee of thy wounds, saith the Lord.' Here is your medicine. Dominus vobiscum!";
			link.l1 = "Thank you, Father Adrian.";
			link.l1.go = "exit";
			SaveCurrentNpcQuestDateParam(npchar, "potion"+iTemp+"_date");
			NextDiag.TempNode = "adrian_3";
		break;
		
	// посланец Дичозо
		case "Dichoso_agent":
			dialog.text = "Captain "+GetFullName(pchar)+"?";
			link.l1 = "Yes, that's me. What do you want?";
			link.l1.go = "Dichoso_agent_1";
		break;
		
		case "Dichoso_agent_1":
			dialog.text = "I have a message for you from Captain Miguel Dichoso. He says you know him.";
			link.l1 = "Yes I've heard of him. Never had the honor to meet him in person.";
			link.l1.go = "Dichoso_agent_2";
		break;
		
		case "Dichoso_agent_2":
			dialog.text = "Captain Dichoso would like to change that. He wants to meet with you face-to-face. He has an offer for you concerning an expedition into the depths of the Spanish Main to the lost Indian city of Tayasal. He told me that your experience paired with his knowledge will produce gratifying results.";
			link.l1 = "Those were his exact words?";
			link.l1.go = "Dichoso_agent_3";
		break;
		
		case "Dichoso_agent_3":
			dialog.text = "Correct. Captain Dichoso will be waiting for you on St. Christopher. He will await you in the large crypt of the Capsterville cemetery, in order to avoid prying eyes and ears.";
			link.l1 = "Hm...";
			link.l1.go = "Dichoso_agent_4";
		break;
		
		case "Dichoso_agent_4":
			dialog.text = "Dichoso warned me that you would hesitate. He told me to offer you guarantees that you will not be harmed during the negotiations no matter your decision. He also adds that what you found on a certain island was just only a tiny hors d'oeuvre considering what you would find in Tayasal.";
			link.l1 = "Is that so... that's very intriguing. But why wouldn't Captain Dichoso pay a visit to me himself? Why did he send a third party?";
			link.l1.go = "Dichoso_agent_5";
		break;
		
		case "Dichoso_agent_5":
			dialog.text = "Don Dichoso first searched for you on Isla Tesoro, then here, and now is off to St. Christopher in hope of finding you there. You are an officer of Philippe de Poincy himself, aren't you? I was supposed to wait for you here in the event that you would arrive in Blueweld.";
			link.l1 = "Then it's all clear. Well, alright. I won't waste any time, I should go to Capsterville.";
			link.l1.go = "Dichoso_agent_6";
		break;
		
		case "Dichoso_agent_6":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload4_back", "none", "", "", "Tieyasal_PrepareDichosoTrap", -1);
		break;
		
	// агент Дичозо
		case "Dichoso_crypt_agent":
			dialog.text = "Well, finally we meet, captain "+GetFullName(pchar)+"...";
			if (CheckAttribute(pchar, "questTemp.Tieyasal.MigelKnow")) 
			{
				link.l1 = "Where is Miguel Dichoso? And don't try to wheedle out of this. I know who he really is and I think you do too.";
				link.l1.go = "Dichoso_crypt_agent_2";
			}
			else
			{
				link.l1 = "I suppose this is Miguel Dichoso in the flesh right in front of me?";
				link.l1.go = "Dichoso_crypt_agent_1";
			}
		break;
		
		case "Dichoso_crypt_agent_1":
			dialog.text = "You suppose correctly, captain. We have been on each other's heels for a long time, haven't we?";
			if (CheckAttribute(pchar, "questTemp.Ksochitam.SQCapBookRead")) // прочел журнал Санта-Квитерии
			{
				link.l1 = "I can tell that you're lying just by looking at you, mate. You're not Dichoso. I've read the log entries of the captain of the 'Santa Quiteria' and asked around about his appearance. You don't look like him. You don't even have a scar on your face from a cavalry sword. Come now, even a pantomime could have at least attempted to draw it on!";
				link.l1.go = "Dichoso_crypt_agent_2";
			}
			else
			{
				link.l1 = "Exactly. As I understand, we are here to talk about the lost city of Tayasal?";
				link.l1.go = "Dichoso_crypt_agent_7";
			}
		break;
		
		case "Dichoso_crypt_agent_2":
			dialog.text = "Ha! No point in continuing this farce then. Miguel warned me that you were a cunning rascal...";
			link.l1 = "Where is Miguel Dichoso?";
			link.l1.go = "Dichoso_crypt_agent_3";
		break;
		
		case "Dichoso_crypt_agent_3":
			dialog.text = "He is not here. I am authorized to meet you and speak with you on his behalf.";
			link.l1 = "I will not speak with a pawn. I'm here for the king. Where is he?!";
			link.l1.go = "Dichoso_crypt_agent_4";
		break;
		
		case "Dichoso_crypt_agent_4":
			dialog.text = "Not being a pleasant conversation partner, captain. You've lost your composure.";
			link.l1 = "Enough games, I get it. It's an ambush again. You boys need to come up with some new tricks.";
			link.l1.go = "Dichoso_crypt_agent_5";
		break;
		
		case "Dichoso_crypt_agent_5":
			dialog.text = "Haha, correct again matey! My men are waiting for you right behind the door down to the catacombs. On top of that, I have musketeers hiding behind each of the gravestones, ready to shoot. There is no escape. So as repetitive as this trick may be, you've climbed right into it! Your desire to see Tayasal has outweighed your common sense!";
			link.l1 = "You've picked a great place for a fight, scum. I won't have to go far to bury you and your brigand friends.";
			link.l1.go = "Dichoso_crypt_agent_6";
		break;
		
		case "Dichoso_crypt_agent_6":
			dialog.text = "Haha! I like your wit! Just like Miguel's! Say whatever you want, you're both cut from the same cloth... I'll do just as he ordered - I'll send you to Hell as fast and painlessly as possible. To arms, boys!";
			link.l1 = "Better men than you have tried. Give my regards to the Devil, scoundrel!";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Tieyasal_StartCryptBattle");
		break;
		
		case "Dichoso_crypt_agent_7":
			dialog.text = "You really want to get to the city? I understand, captain, but I don't think it's a good idea.";
			link.l1 = "Then what are we here to talk about?";
			link.l1.go = "Dichoso_crypt_agent_8";
		break;
		
		case "Dichoso_crypt_agent_8":
			dialog.text = "I'm not looking to enter a long, romantic conversation with you. You're here and that for me is enough.";
			link.l1 = "Enough games, I get it. It's an ambush again. You boys need to come up with some new tricks.";
			link.l1.go = "Dichoso_crypt_agent_5";
		break;
		
	// командир абордажников
		case "newcastle_officer":
			dialog.text = "Awaiting your orders, captain!";
			link.l1 = "We head through the jungle to the Capsterville cemetery. Once we get there, don't enter the cemetery itself. Take up firing positions just outside the gate and listen closely when I go inside. If you hear fighting, rush in at once.";
			link.l1.go = "newcastle_officer_1";
		break;
		
		case "newcastle_officer_0":
			dialog.text = "Awaiting your orders, captain!";
			link.l1 = "We head through the jungle to the Capsterville cemetery. Once we get there, don't enter the cemetery itself. Taking firing positions along the trail, surround the cemetery, and listen closely for when I go inside. This whole scheme reeks of an ambush. As soon as you see the enemy, attack immediately.";
			link.l1.go = "newcastle_officer_1";
		break;
		
		case "newcastle_officer_1":
			dialog.text = "Aye aye, captain!";
			link.l1 = "Alright. Forward!";
			link.l1.go = "newcastle_officer_2";
		break;
		
		case "newcastle_officer_2":
			DialogExit();
			chrDisableReloadToLocation = false;
			locations[FindLocation("Charles_exittown")].DisableEncounters = true; //энкаутеры закрыть
			locations[FindLocation("Charles_CaveEntrance")].DisableEncounters = true; //энкаутеры закрыть
			for(i=2; i<=4; i++)
			{
				locations[FindLocation("Charles_Jungle_0"+i)].DisableEncounters = true; //энкаутеры закрыть
			}
			LocatorReloadEnterDisable("Shore42", "boat", true);
			for(i=1; i<=iTotalTemp; i++)
			{
				sld = characterFromID("Tieyasal_Oursoldier_"+i);
				LAi_SetActorType(sld);
				LAi_ActorFollowEverywhere(sld, "", -1);
				LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
			}
			// на локацию перед кладбищем
			pchar.quest.Tieyasal_newcastle.win_condition.l1 = "location";
			pchar.quest.Tieyasal_newcastle.win_condition.l1.location = "Charles_exittown";
			pchar.quest.Tieyasal_newcastle.function = "Tieyasal_NewcastleGoJungle";
			// на крипту
			pchar.quest.Tieyasal_graveyard.win_condition.l1 = "location";
			pchar.quest.Tieyasal_graveyard.win_condition.l1.location = "Charles_CryptBig2";
			pchar.quest.Tieyasal_graveyard.function = "Tieyasal_InGraveyardCrypt";
		break;

case "Europe":
			PlaySound("Voice\English\military01.wav");
			dialog.text = "Captain Hobart! According to our spy's information, rebels are hiding out in this estate. There are five dragoons at your disposal. Search the building and seize anybody hanging out inside there! Don't handle these scum with kid gloves. You're acting in the name of the King!";
			link.l1 = "Yes, sir!";
			link.l1.go = "Europe_1";
		break;
		
		case "Europe_1":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_SetActorType(pchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "Europe_SharlieFinal_1", 5);
		break;
		
		//Индеец по квесту "Знакомство с индейцами"
		case "ZsI_ListKakao":
			dialog.text = "Tsk! Son of the Sea!";
			link.l1 = "Eh... what? Are you addressing me?";
			link.l1.go = "ZsI_ListKakao_1";
			sld = characterFromId("Tichingitu");
			LAi_SetActorType(sld);
			LAi_ActorFollow(sld, pchar, "", -1);
		break;
		
		case "ZsI_ListKakao_1":
			dialog.text = "Right. I'm Cocoa Leaf. I have business with you, Son of the Sea.";
			link.l1 = "I don't know what cocoa looks like, or why you're named after it. But fine, tell me what you need, quickly.";
			link.l1.go = "ZsI_ListKakao_2";
		break;
		
		case "ZsI_ListKakao_2":
			dialog.text = "Tsk! You go to town. Buy two pistols and two ten powder and bullets. Give them to me. There's a reward. The Son of the Sea will be pleased.";
			link.l1 = "Two pistols and twenty shots? That's all? Why don't you buy them yourself then?";
			link.l1.go = "ZsI_ListKakao_3";
		break;
		
		case "ZsI_ListKakao_3":
			dialog.text = "Don't you get it, paleface? Who would sell me a fire weapon?!";
			if (CheckAttribute(pchar, "questTemp.ZsI_Cannibals"))		//Sinistra Только если проходил квест "Каннибалы"
			{
				link.l1 = "You know, I've encountered your kind in Martinique before... Cannibals. They kidnapped a girl and two men. Roasted and ate one of the men. If either of them had a gun, we wouldn't be having this conversation.";
				link.l1.go = "ZsI_ListKakao_3_1";
			}
			else
			{
				link.l1 = "And why do you need a firearm, Cocoa Leaf? Do you want to kill someone?";
				link.l1.go = "ZsI_ListKakao_3_2";
			}
		break;
		
		case "ZsI_ListKakao_3_1":
			dialog.text = "Goo-oo! Cocoa Leaf is not a brigand, my fight is only for warriors of your tribe. Palefaces come to our land, make us slaves. Cocoa Leaf himself fights. Take a slave. Not good, not bad. That's how it goes. Indian, white, no difference. Fire weapons make a difference.";
			link.l1 = "And why do you need a firearm, Cocoa Leaf? Do you want to kill someone?";
			link.l1.go = "ZsI_ListKakao_3_2";
		break;
		
		case "ZsI_ListKakao_3_2":
			dialog.text = "To fight. But on equal terms. Palefaces have fire weapons, Indians don't. That's unfair. And to have a fire weapon for an Indian - it's a protection against unjust treatment, humiliation, or insult by palefaces.";
			link.l1 = "";
			link.l1.go = "ZsI_ListKakao_4";
		break;
		
		case "ZsI_ListKakao_4":
			StartInstantDialog("Tichingitu", "ZsI_ListKakao_5", "Quest\Sharlie\OtherNPC.c");
		break;
		
		case "ZsI_ListKakao_5":
			dialog.text = "Right, Captain. The pale-faces look down on us.";
			link.l1 = "I've noticed. Back in Europe, they preach about teaching Indians the true faith, and how we all work together peacefully on plantations...";
			link.l1.go = "ZsI_ListKakao_7";
		break;
		
		case "ZsI_ListKakao_7":
			dialog.text = "Tichingitu may not understand the captain, but he understands Cocoa Leaf. He seeks revenge.";
			link.l1 = "Seems that way... Don't you want revenge too, against our recent captors?";
			link.l1.go = "ZsI_ListKakao_8";
		break;
		
		case "ZsI_ListKakao_8":
			dialog.text = "Perhaps. But Tichingitu won't resort to that. Tichingitu is with you now. And Tichingitu uses his own head. There'll be too much bloodshed. White blood. Indian blood. Too much suffering. That's not right.";
			link.l1 = "Yes, it's already bad, and helping Cocoa Leaf get guns will only make it worse... But he does have a point. And I still have a crew to pay soon.";
			link.l1.go = "ZsI_ListKakao_9";
		break;
		
		case "ZsI_ListKakao_9":
			dialog.text = "Use your own head, Captain.";
			link.l1 = "";
			link.l1.go = "ZsI_ListKakao_10";
		break;
		
		case "ZsI_ListKakao_10":
			StartInstantDialog("ListKakao", "ZsI_ListKakao_11", "Quest\Sharlie\OtherNPC.c");
		break;
		
		case "ZsI_ListKakao_11":
			dialog.text = "The Son of the Sea talks a lot. Looks like a squaw with a mustache.";
			link.l1 = "Who? Explain this to me, Cocoa Leaf. I'm a paleface too and you're asking me for weapons to fight palefaces. Isn't that contradictory? Why approach me?";
			link.l1.go = "ZsI_ListKakao_12";
		break;
		
		case "ZsI_ListKakao_12":
			dialog.text = "I overheard your conversation with that strangely dressed Indian. You're not like the other palefaces. You understand Tichingitu. And you understand Cocoa Leaf, I'm sure.";
			link.l1 = "Oh... What will you offer for weapons, Cocoa Leaf?";
			link.l1.go = "ZsI_ListKakao_13";
		break;
		
		case "ZsI_ListKakao_13":
			dialog.text = "The tears of the gods. You call them pearls. Many pearls.";
			link.l1 = "I've made my decision, Cocoa Leaf. Wait here, I'm going to the arms merchant. I'll buy what I need and come back.";
			link.l1.go = "ZsI_ListKakao_Soglasen_5";
			if (sti(pchar.items.pistol1) >= 2 && sti(pchar.items.GunPowder) >= 20 && sti(pchar.items.bullet) >= 20)
			{
				link.l2 = "I've made my decision, Cocoa Leaf. I happen to already have what you need. Here you go.";
				link.l2.go = "ZsI_ListKakao_Soglasen_2";
			}
			link.l3 = "I've made my decision, Cocoa Leaf. I don't want to invite unnecessary trouble. You won't get firearms from me. Move along.";
			link.l3.go = "ZsI_ListKakao_Otkaz";
			npchar.LifeDay = 1;
			SaveCurrentNpcQuestDateParam(npchar, "LifeTimeCreate");
		break;
		
		case "ZsI_ListKakao_Otkaz":
			dialog.text = "Tsk!";
			link.l1 = "";
			link.l1.go = "ZsI_ListKakao_Otkaz_2";
		break;
		
		case "ZsI_ListKakao_Otkaz_2":
			DialogExit();
			
			ChangeIndianRelation(-3.0);
			ChangeCharacterComplexReputation(pchar, "authority", -1);
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "ZsI_Mir", -1);
			LAi_SetImmortal(npchar, false);
			LAi_SetHP(npchar, 1.0, 1.0);
			npchar.lifeday = 0;
			PChar.quest.ZsI_Draka.win_condition.l1 = "NPC_Death";
			PChar.quest.ZsI_Draka.win_condition.l1.character = "ListKakao";
			PChar.quest.ZsI_Draka.win_condition = "ZsI_Draka";
			PChar.quest.ZsI_Mir.win_condition.l1 = "ExitFromLocation";
			PChar.quest.ZsI_Mir.win_condition.l1.location = PChar.location;
			PChar.quest.ZsI_Mir.win_condition = "ZsI_Mir";
			bDisableFastReload = false;
			chrDisableReloadToLocation = false;
			sld = characterFromId("Tichingitu");
			LAi_SetOfficerType(sld);
			sld.Dialog.Filename = "Quest\Sharlie\Tichingitu.c";
			sld.Dialog.CurrentNode = "Tichingitu_officer";
			LaunchTutorial("Fighter", 1);
		break;
		
		case "ZsI_ListKakao_Soglasen_2":
			dialog.text = "Uh-oh! Does the Son of the Sea have a musket? Pay a high price for a musket!";
			link.l1 = "No, but will a cannon from my ship do? Leave now, Cocoa Leaf, before we're spotted and arrested.";
			link.l1.go = "ZsI_ListKakao_Soglasen_3";
			AddCharacterExpToSkill(pchar, "Commerce", 50);
			ChangeIndianRelation(3.0);
			AddItems(pchar, "jewelry53", 180);
			Log_Info("You have received 180 small pearls");
			PlaySound("Interface\important_item.wav");
			DeleteAttribute(pchar, "questTemp.ZsI_PokupaemPistolety");
			if (sti(pchar.items.pistol1) >= 2 && sti(pchar.items.GunPowder) >= 20 && sti(pchar.items.bullet) >= 20)
			{
				RemoveCharacterEquip(PChar, GUN_ITEM_TYPE);
				RemoveItems(PChar, "pistol1", 2);
				RemoveItems(PChar, "GunPowder", 20);
				RemoveItems(PChar, "bullet", 20);
			}
		break;
		
		case "ZsI_ListKakao_Soglasen_3":
			dialog.text = "Good deal! Son of the Sea, if you go into the selva, take a fire weapon. Meet an Indian, be a bargain.";
			link.l1 = "I'll remember that. Goodbye, Cocoa Leaf.";
			link.l1.go = "ZsI_ListKakao_Soglasen_4";
		break;
		
		case "ZsI_ListKakao_Soglasen_4":
			DialogExit();
			
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1", "none", "", "", "", -1);
			npchar.lifeday = 0;
			bDisableFastReload = false;
			chrDisableReloadToLocation = false;
			
			Return_TichingituOfficer();
			LaunchTutorial("Fighter", 1);
		break;
		
		case "ZsI_ListKakao_Soglasen_5":
			dialog.text = "Cocoa Leaf will wait.";
			link.l1 = "";
			link.l1.go = "ZsI_ListKakao_Soglasen_6";
		break;
		
		case "ZsI_ListKakao_Soglasen_6":
			DoQuestReloadToLocation("BasTer_town", "reload", "gate_back", "ZsI_TPvGorod");
		break;

		case "ZsI_officer":
			sld = CharacterFromID("Tichingitu");
			if (sld.location == pchar.location && !LAi_IsDead(sld))
			{
				dialog.text = "Bah, looks like we have a gathering of natives here!\nYou want to go back to prison, dog?\nWhat are you doing here, Monsieur?";
			}
			else
			{
				dialog.text = "Halt! What are you doing here, Monsieur?";
			}
			link.l1 = "";
			link.l1.go = "ZsI_officer_2";
			sld = CharacterFromID("ListKakao");
			LAi_CharacterEnableDialog(sld);
			EndBattleLandInterface();
		break;
		
		case "ZsI_officer_2":
			LAi_SetActorType(npchar);
			LAi_ActorTurnToCharacter(npchar, CharacterFromID("ListKakao"));
			dialog.text = "Hey, scum, were you waiting for this upstanding citizen?";
			link.l1 = "";
			link.l1.go = "ZsI_officer_3";
		break;
		
		case "ZsI_officer_3":
			DialogExit();
			StartInstantDialog("ListKakao", "ZsI_officer_4", "Quest\Sharlie\OtherNPC.c");
		break;
		
		case "ZsI_officer_4":
			LAi_SetActorType(npchar);
			LAi_ActorTurnToCharacter(npchar, CharacterFromID("ZsI_Patrul_off"));
			dialog.text = "All palefaces look the same to me. But I have never seen this one. You, warrior, do what you must with me. It's getting tiresome. Cocoa Leaf is ready to face the spirits of the forest.";
			link.l1 = "";
			link.l1.go = "ZsI_officer_5";
		break;
		
		case "ZsI_officer_5":
			DialogExit();
			StartInstantDialog("ZsI_Patrul_off", "ZsI_officer_6", "Quest\Sharlie\OtherNPC.c");
		break;
		
		case "ZsI_officer_6":
			LAi_SetActorType(npchar);
			LAi_ActorTurnToCharacter(npchar, CharacterFromID("ListKakao"));
			dialog.text = "Hell awaits you, not the spirits of the forest.";
			link.l1 = "";
			link.l1.go = "ZsI_officer_7";
		break;
		
		case "ZsI_officer_7":
			LAi_SetActorType(npchar);
			LAi_ActorTurnToCharacter(npchar, pchar);
			dialog.text = "Captain, you're dismissed. Stay out of my way. Protecting the city is serious business.";
			link.l1 = "I see... But what about this Indian?";
			link.l1.go = "ZsI_officer_8";
		break;
		
		case "ZsI_officer_8":
			dialog.text = "What's your interest in Indians, Monsieur? Although... well, yes, you're fresh from Europe\nHow's Paris? Do they still squish city rats, or have they started inviting them to communion? You see, we have natives instead of rats. They do business with buccaneers, attack loggers, they eat people, damn it\nThree days ago some bright individual had already sold a musket to the likes of this one. And guess what? Those bastards killed all the soldiers in the patrol, lead, by the way, by my friend and comrade. We found the traitor-colonist and strung him up to dry in the sun, to set an example. Giving firearms to Indians! That's treason! Treason against France! We've been tracking that colored monkey for a while as he's already become a familiar face at various events\nWell, now he'll meet his swift and deserved end. You can move on, Captain. Don't get involved in matters that don't concern you. You're not part of this war... Not yet... Or are you?!";
			if (IsCharacterPerkOn(Pchar, "Trustworthy"))
			{
				notification("Trustworthy", "Trustworthy");
				link.l1 = "(Trustworthy) You see, officer... I'm Captain Charles de Maure, a guest of Fadey Muscovite. We have a certain interest in this Indian... so let's not interfere with each other's duties. Agreed, Lieutenant?";
				link.l1.go = "ZsI_officer_Mir";
			}
			link.l2 = "Attitudes towards newcomers, attitudes towards natives... Colonists, natives... I don't understand this whole thing much yet, but at this moment, Lieutenant, the comparison doesn't favor you... To battle!";
			link.l2.go = "ZsI_officer_Draka";
			link.l3 = "You're right, Lieutenant, I'm not. Goodbye.";
			link.l3.go = "ZsI_officerKIll";
			StartBattleLandInterface();
		break;
		
		case "ZsI_officer_Mir":
			dialog.text = "Ahem! Understood, Captain. Please convey my regards to Monsieur Fadey. Squad, resume patrolling!";
			link.l1 = "";
			link.l1.go = "ZsI_officer_Mir_2";
		break;
		
		case "ZsI_officer_Mir_2":
			DialogExit();
			
			DeleteAttribute(pchar, "questTemp.CameraDialogMode");
			sld = CharacterFromID("ZsI_Patrul_off");
			LAi_SetActorType(sld);
			sld.lifeday = 0;
			LAi_SetImmortal(sld, true);
			LAi_ActorGoToLocation(sld, "reload", "reload4", "none", "", "", "", -1);
			
			for (i=1; i<=2; i++)
			{
				sld = CharacterFromID("ZsI_Patrul_"+i);
				LAi_SetActorType(sld);
				sld.lifeday = 0;
				LAi_SetImmortal(sld, true);
				LAi_ActorGoToLocation(sld, "reload", "reload4", "none", "", "", "", -1);
			}
			sld = CharacterFromID("ListKakao");
			sld.dialog.filename = "Quest\Sharlie\OtherNPC.c";
			sld.dialog.currentnode = "ZsI_MirFinal";
			LAi_SetActorType(sld);
			LAi_SetActorType(pchar);
			SetActorDialogAny2Pchar(sld.id, "", 0.0, 0.0);
			LAi_ActorFollow(pchar, sld, "ActorDialog_Any2Pchar", 2.0);
			LAi_ActorFollow(sld, pchar, "ActorDialog_Any2Pchar", 2.0);
			
			AddCharacterExpToSkill(pchar, "Leadership", 30);
			AddCharacterExpToSkill(pchar, "Fortune", 30);
		break;
		
		case "ZsI_MirFinal":
			dialog.text = "Uh-oh!";
			link.l1 = "Yeah, well, even I'm surprised that worked. Here are your goods, Cocoa Leaf.";
			link.l1.go = "ZsI_MirFinal_2";
		break;
		
		case "ZsI_MirFinal_2":
			dialog.text = "The Son of the Sea speaks well. Saving an Indian is a big deal! Big reward!";
			link.l1 = "Wow, that's quite a haul... And a stone with a hole in it, and some kind of amulet.";
			link.l1.go = "ZsI_MirFinal_3";
			AddItems(pchar, "jewelry53", 180);
			AddItems(pchar, "cannabis1", 3);
			GiveItem2Character(pchar, "indian_10");
			GiveItem2Character(pchar, "talisman11");
			Log_Info("You have received 180 small pearls");
			Log_info("You have received Amulet 'Cascavella'}");
			Log_info("You have received Ward 'Adder stone'");
			Log_info("You have received 3 Datura herbs");
			PlaySound("Interface\important_item.wav");
		break;
		
		case "ZsI_MirFinal_3":
			dialog.text = "Does the Son of the Sea have a musket? Pay a high price for a musket!";
			link.l1 = "No, but will a cannon from my ship do? Leave now, Cocoa Leaf, before we're spotted and arrested.";
			link.l1.go = "ZsI_MirFinal_4";
		break;
		
		case "ZsI_MirFinal_4":
			dialog.text = "Good deal! Son of the Sea, if you go into the selva, take a fire weapon. Meet an Indian, be a bargain.";
			link.l1 = "I'll remember that. Goodbye, Cocoa Leaf.";
			link.l1.go = "ZsI_MirFinal_5";
		break;
		
		case "ZsI_MirFinal_5":
			DialogExit();
			
			LAi_ActorRunToLocation(npchar, "reload", "reload1", "none", "", "", "", -1);
			npchar.lifeday = 0;
			LAi_LocationFightDisable(&Locations[FindLocation("BasTer_ExitTown")], false);
			LAi_SetPlayerType(pchar);
			bDisableFastReload = false;
			chrDisableReloadToLocation = false;
		break;
		
		case "ZsI_officer_Draka":
			DialogExit();
			
			DeleteAttribute(pchar, "questTemp.CameraDialogMode");
			LAi_LocationFightDisable(&Locations[FindLocation("BasTer_ExitTown")], false);
			LAi_SetFightMode(pchar, true);
			ChangeCharacterComplexReputation(pchar, "nobility", -1);
			ChangeCharacterComplexReputation(pchar, "authority", -2);	
			ChangeIndianRelation(5.0);
			ChangeCharacterNationReputation(pchar, FRANCE, -10);
			sld = CharacterFromID("ListKakao");
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
			LAi_SetImmortal(sld, false);
			for (i=1; i<=2; i++)
			{
				sld = CharacterFromID("ZsI_Patrul_"+i);
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "EnemyFight");
			}
			sld = CharacterFromID("ZsI_Patrul_off");
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, "EnemyFight");
			
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, false);
			LAi_group_SetCheck("EnemyFight", "ZsI_officer_Draka_3");
		break;
		
		case "ZsI_Final":
			ChangeIndianRelation(5.0);
			dialog.text = "Uh-oh! Bad decision, Son of the Sea. Why would you do that?";
			link.l1 = "Ugh... Five minutes ago it seemed right... Now I'm not so sure anymore.... I killed my own after all. What am I supposed to do now? What if they find out? Shit! Shit!";
			link.l1.go = "ZsI_Final_2";
		break;
		
		case "ZsI_Final_2":
			dialog.text = "Now there'll be a raid. Soldiers kill everyone. Two patrols not to forgive. Cocoa Leaf run. And you, Son of the Sea... why. Cocoa Leaf die anyway. The spirits want it that way.";
			link.l1 = "Oh... Is our deal still on the table?";
			link.l1.go = "ZsI_Final_3";
		break;
		
		case "ZsI_Final_3":
			dialog.text = "Bad decision, Son of the Sea. But thank you. Big reward.";
			link.l1 = "Not so big, all things considered...";
			link.l1.go = "ZsI_Final_4";
			AddItems(pchar, "jewelry53", 180);
			AddItems(pchar, "cannabis1", 3);
			GiveItem2Character(pchar, "indian_10");
			GiveItem2Character(pchar, "talisman11");
			Log_Info("You have received 180 small pearls");
			Log_info("You have received Amulet 'Cascavella'}");
			Log_info("You have received Ward 'Adder stone'");
			Log_info("You have received 3 Datura herbs");
			PlaySound("Interface\important_item.wav");
		break;
		
		case "ZsI_Final_4":
			dialog.text = "Son of the Sea, if you survive and then go to the selva, take a fire weapon. Meet an Indian, be a bargain.";
			link.l1 = "I'll keep that in mind for the future. Goodbye, Cocoa Leaf.";
			link.l1.go = "ZsI_Final_5";
		break;
		
		case "ZsI_Final_5":
			DialogExit();
			
			LAi_ActorRunToLocation(npchar, "reload", "reload1", "none", "", "", "", -1);
			LAi_SetImmortal(npchar, true);
			npchar.lifeday = 0;
		break;
		
		case "ZsI_officerKIll":
			DialogExit();
			
			DeleteAttribute(pchar, "questTemp.CameraDialogMode");
			sld = CharacterFromID("ZsI_Patrul_off");
			LAi_SetActorType(sld);
			LAi_ActorTurnToCharacter(sld, CharacterFromID("ListKakao"));
			LAi_SetActorType(pchar);
			DoQuestCheckDelay("ZsI_officerKIll_1", 0.1);
			DoQuestCheckDelay("ZsI_officerKIll_2", 1.3);
			AddItems(pchar, "pistol1", 2);
			AddItems(pchar, "GunPowder", 20);
			AddItems(pchar, "bullet", 20);
		break;
		
		//Торговец Барбье по квесту "Деньги на деревьях"
		case "MOT_Barbie":
			dialog.text = "Greetings, Captain Charles de Maure. My name is Charles Barbier. Might I have a moment of your time?";
			link.l1 = "Captain de Maure... Indeed, that's me! Please go on, Monsieur Barbier.";
			link.l1.go = "MOT_Barbie_2";
		break;
		
		case "MOT_Barbie_2":
			dialog.text = "Always a pleasure to meet a colleague, especially one with whom I share a name! I have a proposition for you, Captain. You see, I require an escort to St. Pierre, and...";
			link.l1 = "I know St. Pierre! But that's only a two-day journey! And I must confess, I'm still fairly green for the role of an escort. I've only assumed command of this ship a week ago.";
			link.l1.go = "MOT_Barbie_3";
		break;
		
		case "MOT_Barbie_3":
			dialog.text = "Your honesty is appreciated, Captain. Charles, forgive my informality, but you are precisely the person I need.";
			link.l1 = "Hmm... I recall a similar proposition not long ago. It led to a pirate ambush near Le Francois.";
			link.l1.go = "MOT_Barbie_4";
		break;
		
		case "MOT_Barbie_4":
			dialog.text = "I've heard of that incident, which is why I sought you out\nFirstly, I'm carrying a rather valuable cargo, and there are always predators lurking. However, your recent triumph over those pirates near Le Francois will give the scoundrels there pause\nSecondly, your association with Fadey Muscovite is a strong endorsement.";
			link.l1 = "A compelling argument, Monsieur. And what compensation do you propose for this favor?";
			link.l1.go = "MOT_Barbie_5";
		break;
		
		case "MOT_Barbie_5":
			dialog.text = "It's not a favor, Captain, but a mutually beneficial venture! I will pay you forty gold pieces to escort me to St. Pierre in a timely manner.";
			if (IsCharacterPerkOn(Pchar, "Trustworthy"))
			{
				notification("Trustworthy", "Trustworthy");
				link.l1 = "(Trustworthy) Since I'm headed in the opposite direction, Monsieur, I'll require payment upfront.";
				link.l1.go = "MOT_Barbie_Torg";
			}
			link.l2 = "Not a bad proposition - I'm headed in that direction anyway. Deal!";
			link.l2.go = "MOT_Barbie_Soglasen";
			link.l3 = "Valuable cargo, you say? Regrettably, Monsieur, I've had my fill of adventures for the time being.";
			link.l3.go = "MOT_Barbie_Otkaz";
		break;
		
		case "MOT_Barbie_Torg":
			dialog.text = "Hard to refuse such a serious young man, Captain. Here are your forty doubloons. Shall we set sail without delay? Time is money.";
			link.l1 = "We won't tarry long, Monsieur. We'll be setting sail shortly.";
			link.l1.go = "MOT_Barbie_Escadra";
			
			AddItems(pchar, "gold_dublon", 40);
			Log_info("You've received 40 doubloons");
			PlaySound("Interface\important_item.wav");
			AddCharacterExpToSkill(pchar, "Leadership", 20);
			AddCharacterExpToSkill(pchar, "Commerce", 20);
		break;
		
		case "MOT_Barbie_Soglasen":
			dialog.text = "Excellent! I'll prepare for departure immediately!";
			link.l3 = "";
			link.l3.go = "MOT_Barbie_Escadra";
		break;
		
		case "MOT_Barbie_Otkaz":
			dialog.text = "I understand, Captain. I won't impose. Farewell, and good day.";
			link.l3 = "";
			link.l3.go = "MOT_Barbie_Otkaz_2";
		break;
		
		case "MOT_Barbie_Otkaz_2":
			DialogExit();
			
			LAi_SetActorType(npchar);
			npchar.lifeday = 0;
			LAi_ActorRunToLocation(npchar, "reload", "reload6_back", "none", "", "", "", -1);
			
			bDisableFastReload = false;
			chrDisableReloadToLocation = false;
		break;
		
		case "MOT_Barbie_Escadra":
			DialogExit();
			
			SetQuestHeader("MoneyOnTrees");
			AddQuestRecord("MoneyOnTrees", "1");
			
			FantomMakeCoolSailor(npchar, SHIP_BARKENTINE, "Charles", CANNON_TYPE_CANNON_LBS3, 40, 33, 20);
			npchar.Ship.Mode = "trade";
			SetCharacterRemovable(npchar, false);
			SetCompanionIndex(pchar, -1, sti(npchar.index));
			npchar.CompanionEnemyEnable = true;
			SetCrewQuantity(npchar, 35);
			SetCharacterGoods(npchar, GOOD_ROPES, 30);
			LAi_SetImmortal(npchar, false);
			
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1_back", "", "", "", "", -1);
			LAi_group_MoveCharacter(npchar, LAI_GROUP_PLAYER);
			
			bDisableFastReload = false;
			chrDisableReloadToLocation = false;
			SetTimerCondition("MOT_ZadanieProvaleno", 0, 0, 14, false);
			PChar.quest.MOT_Zahvatili.win_condition.l1 = "NPC_Death";
			PChar.quest.MOT_Zahvatili.win_condition.l1.character = "SharlieBarbie";
			PChar.quest.MOT_Zahvatili.win_condition = "MOT_Zahvatili";
			PChar.quest.MOT_Dostavili.win_condition.l1 = "location";
			PChar.quest.MOT_Dostavili.win_condition.l1.location = "FortFrance_town";
			PChar.quest.MOT_Dostavili.win_condition = "MOT_Dostavili";
		break;
		
		case "MOT_Barbie_101":
			if (IsCharacterPerkOn(Pchar, "Trustworthy"))
			{
				dialog.text = "Thank you for your exemplary escort, Captain. I'm pleased we encountered no incidents.";
				link.l1 = "A pleasure doing business with you, Monsieur. Now if you'll excuse me, I have much to attend to.";
			}
			else
			{	
				dialog.text = "Thank you for your exemplary escort, Captain. I'm pleased we encountered no incidents. Here is your payment - forty doubloons in full.";
				link.l1 = "A pleasure doing business with you, Monsieur. Now if you'll excuse me, I have much to attend to.";
				AddItems(pchar, "gold_dublon", 40);
				Log_info("You've received 40 doubloons");
				PlaySound("Interface\important_item.wav");
			}
			link.l1.go = "MOT_Barbie_102";
		break;
		
		case "MOT_Barbie_102":
			dialog.text = "Charles...";
			link.l1 = "Yes, Charles? You seem troubled. Is something amiss?";
			link.l1.go = "MOT_Barbie_103";
			RemoveCharacterCompanion(pchar, npchar);
			npchar.lifeday = 0;
		break;
		
		case "MOT_Barbie_103":
			dialog.text = "Well, since you're a dependable individual, and acquainted with Fadey... Look, commerce is a risky affair, correct?";
			link.l1 = "If you say so.";
			link.l1.go = "MOT_Barbie_104";
		break;
		
		case "MOT_Barbie_104":
			dialog.text = "I managed to acquire a batch of ropes at a bargain on Guadeloupe from... you know. I intended to swiftly sell them in St. Pierre and use the proceeds to purchase coffee for resale in Willemstad. It seemed like a sound plan.";
			link.l1 = "I don't question your integrity, Monsieur, but this all sounds rather dubious. You speak of your cargo as though it were gold. Meanwhile, my ship is stocked with these ropes and they are dirt cheap.";
			link.l1.go = "MOT_Barbie_106";
		break;
		
		case "MOT_Barbie_106":
			dialog.text = "Charles, these ropes are of the finest quality, crafted from superior hemp and woven at the Moscow Tsar's factories. They serve strategic purposes and are utilized in the rigging of warships. The English monopolize trade routes with Muscovy, prohibiting the free commerce of such ropes. Other nations vie intensely to secure the entirety of the available supply for their shipyards in Europe as well.";
			link.l1 = "So, this is smuggling?";
			link.l1.go = "MOT_Barbie_107";
		break;
		
		case "MOT_Barbie_107":
			dialog.text = "Yes. Unfortunately, I had a falling out with Santiago smugglers last year. I had nearly forgotten about it, but these individuals maintain close connections and long memories. Here's a piece of advice: avoid incensing them and reneging on deals; it's a situation you won't rectify later.";
			link.l1 = "Thank you, but smuggling isn't of interest to me.";
			link.l1.go = "MOT_Barbie_108";
		break;
		
		case "MOT_Barbie_108":
			dialog.text = "Pity! Honest trade can bring you a handsome profit, but you'll never amass substantial wealth. Nevertheless, I didn't initiate this rather precarious conversation with you without reason. I propose you purchase a shipment of ropes from me. Local smugglers frequent the tavern, and they'll be eager buyers for this cargo. Think of it! You'll reap considerable profit today without venturing onto the open sea.";
			link.l1 = "How much do you ask for the cargo?";
			link.l1.go = "MOT_Barbie_109";
		break;
		
		case "MOT_Barbie_109":
			dialog.text = "Ten thousand pesos. It's a modest sum, and reselling the ropes to smugglers will yield substantial returns.";
			if (sti(pchar.Money) >= 10000)
			{
				link.l1 = "I'd never forgive myself if I passed up an opportunity like this. Take the silver and ensure the goods are promptly delivered to my vessel.";
				link.l1.go = "MOT_Barbie_ContraSoglasen";
			}
			if (sti(pchar.Money) >= 7000)
			{
				link.l2 = "This is a precarious endeavor, my friend. Let's meet each other halfway, shall we? I'll accept your ropes for seven thousand.";
				link.l2.go = "MOT_Barbie_ContraTorg";
			}
			link.l3 = "That's a considerable sum, Monsieur. I sympathize with your predicament, but I cannot accept such risk.";
			link.l3.go = "MOT_Barbie_ContraOtkaz";
		break;
		
		case "MOT_Barbie_ContraSoglasen":
			dialog.text = "My gratitude, Charles! You've spared me from financial ruin! The goods shall be dispatched quickly and with utmost caution\nAllow me to offer you one piece of advice as a fellow merchant: once you hired a decent purser, procure coffee in Saint-Pierre and sell it for profit in Willemstad. Local capitals pay handsomely for colonial goods, exporting them to Europe for substantial profits. Best of luck in your ventures, friend!";
			link.l1 = "Farewell, Monsieur.";
			link.l1.go = "MOT_Barbie_ContraSoglasen_2";
			AddCharacterGoodsSimple(pchar, GOOD_ROPES, 30);
			AddMoneyToCharacter(pchar, -10000);
			Log_info("You've received 30 ropes");
			PlaySound("Interface\important_item.wav");
		break;
		
		case "MOT_Barbie_ContraSoglasen_2":
			DialogExit();
			
			AddQuestRecord("MoneyOnTrees", "5");
			CloseQuestHeader("MoneyOnTrees");
			ChangeCharacterComplexReputation(pchar, "nobility", -1);
			
			sld = CharacterFromID("SharlieBarbie");
			sld.lifeday = 0;
			LAi_SetCitizenType(sld);
			LAi_CharacterDisableDialog(sld);
			
			bDisableFastReload = false;
			chrDisableReloadToLocation = false;
		break;
		
		case "MOT_Barbie_ContraTorg":
			if (GetSummonSkillFromName(pchar, SKILL_COMMERCE) > 30)
			{
				notification("Skill Check Passed", SKILL_COMMERCE);
				dialog.text = "My gratitude, Charles! You've spared me from financial ruin! The goods shall be dispatched quickly and with utmost caution\nAllow me to offer you one piece of advice as a fellow merchant: once you hired a decent purser, procure coffee in Saint-Pierre and sell it for profit in Willemstad. Local capitals pay handsomely for colonial goods, exporting them to Europe for substantial profits. Best of luck in your ventures, friend!";
				link.l1 = "Farewell, Monsieur.";
				link.l1.go = "MOT_Barbie_ContraSoglasen_2";
				AddCharacterGoodsSimple(pchar, GOOD_ROPES, 30);
				AddMoneyToCharacter(pchar, -7000);
				Log_info("You've received 30 ropes");
				PlaySound("Interface\important_item.wav");
			}
			else
			{
				notification("Skill Check Failed (31)", SKILL_COMMERCE); 
				dialog.text = "I can't, Captain. My merchandise is serious and warrants serious treatment. Most free captains dare not trade in strategic goods. Regrettably, bargaining is unwarranted here.";
				if (sti(pchar.Money) >= 10000)
				{
					link.l1 = "I'd never forgive myself if I passed up an opportunity like this. Take the silver and ensure the goods are promptly delivered to my vessel.";
					link.l1.go = "MOT_Barbie_ContraSoglasen";
				}
				link.l2 = "That's a considerable sum, Monsieur. I sympathize with your predicament, but I cannot accept such risk.";
				link.l2.go = "MOT_Barbie_ContraOtkaz";
			}
		break;
		
		case "MOT_Barbie_ContraOtkaz":
			dialog.text = "A pity! Farewell, Captain.";
			link.l1 = "";
			link.l1.go = "MOT_Barbie_ContraOtkaz_2";
		break;
		
		case "MOT_Barbie_ContraOtkaz_2":
			DialogExit();
			
			AddQuestRecord("MoneyOnTrees", "4");
			CloseQuestHeader("MoneyOnTrees");
			ChangeCharacterComplexReputation(pchar, "nobility", 1);
			
			sld = CharacterFromID("SharlieBarbie");
			sld.lifeday = 0;
			LAi_SetCitizenType(sld);
			LAi_CharacterDisableDialog(sld);
			
			bDisableFastReload = false;
			chrDisableReloadToLocation = false;
		break;
		
		//Миниквест "Делюк"
		//Матрос Алонсо
		case "Del_Alonso":
			dialog.text = "Guai, capitano.";
			link.l1 = "E allora?";
			link.l1.go = "Del_Alonso_2";
		break;
		
		case "Del_Alonso_2":
			dialog.text = "Our navigator has been arrested and taken to the local dungeons. Debt issue they say.";
			link.l1 = "What, again?!";
			link.l1.go = "Del_Alonso_3";
		break;
		
		case "Del_Alonso_3":
			dialog.text = "He's a mischief bugger, Captain.";
			link.l1 = "What a terrible timing! Without a navigator, we're stranded here. I'll have to bail him out again! I'll speak with the commandant...";
			link.l1.go = "Del_Alonso_4";
		break;
		
		case "Del_Alonso_4":
			dialog.text = "Permission to speak, Captain?";
			link.l1 = "Go ahead.";
			link.l1.go = "Del_Alonso_5";
		break;
		
		case "Del_Alonso_5":
			dialog.text = "Why go through all this trouble? A man like him will only bring trouble to the ship.";
			link.l1 = "Do I have a choice? There are hardly any other navigators available, so my options are rather limited.";
			link.l1.go = "Del_Alonso_6";
		break;
		
		case "Del_Alonso_6":
			dialog.text = "True, a top-notch navigator is hard to come by, but you don't need a master yet, just a competent one. Your situation changed over the past week, you know this right? No need to scrape the bottom of a barrel to find men for your crew anymore. People now talk about how you defeated that pirate and the connections you have. The crew is behind you too, Captain, we like you.";
			link.l1 = "That's reassuring, Alonso. And what's the crew's opinion on Deluc?";
			link.l1.go = "Del_Alonso_7";
		break;
		
		case "Del_Alonso_7":
			dialog.text = "Imparate in fretta, capitano. L’equipaggio dice che, pur essendo un buon ufficiale e trattandoci bene, non vale la pena. Un grosso mercantile ha appena licenziato i suoi ufficiali – forse cercate in taverna? Lì troverete la persona giusta. E dimenticate Deluc; è il parere dei ragazzi.";
			link.l1 = "Grazie per il consiglio, Alonso. Sapevo di poter contare su di te. Torna sulla nave e prendi il turno mentre risolvo la questione.";
			link.l1.go = "Del_Alonso_8";
		break;
		
		case "Del_Alonso_8":
			dialog.text = "Ai vostri ordini!";
			link.l1 = "...";
			link.l1.go = "Del_Alonso_9";
		break;
		
		case "Del_Alonso_9":
			DialogExit();
			SetQuestHeader("FolkeDeluc");
			AddQuestRecord("FolkeDeluc", "1");
			
			npchar.lifeday = 0;
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1", "none", "", "", "", -1);
			SetFunctionLocationCondition("FortfranceJailOff_AddQuestMark", "fortfrance_prison", false);
			QuestCloseSeaExit();
			sld = CharacterFromID("Folke");
			sld.Dialog.Filename = "Quest\Sharlie\OtherNPC.c";
			sld.dialog.currentnode = "Del_Folke_1";
			RemovePassenger(pchar, sld);
			LAi_SetStayType(sld);
			ChangeCharacterAddressGroup(sld, "FortFrance_prison", "goto", "goto9");
			bDisableFastReload = false;
			chrDisableReloadToLocation = false;
			pchar.questTemp.Del_Deluck = true;
			
			sld = GetCharacter(NPC_GenerateCharacter("Del_shturman", "mercen_4", "man", "man", 5, FRANCE, 3, false, "quest"));
			GiveItem2Character(sld, "blade_03");
			EquipCharacterByItem(sld, "blade_03");
			sld.Dialog.Filename = "Quest\Sharlie\OtherNPC.c";
			sld.dialog.currentnode = "Del_shturman";
			LAi_SetSitType(sld);
			sld.greeting = "officer_hire";
			SetSelfSkill(sld, 21, 23, 18, 33, 25);
			SetShipSkill(sld, 25, 10, 8, 6, 35, 11, 13, 25, 14);
			SetSPECIAL(sld, 7, 10, 6, 8, 7, 8, 4);
			sld.rank = 5;
			SetCharacterPerk(sld, "ShipSpeedUp");
			SetCharacterPerk(sld, "HullDamageUp");
			SetCharacterPerk(sld, "BasicDefense");
			//sld.quest.officertype = "navigator";
			FreeSitLocator("FortFrance_tavern", "sit4");
			ChangeCharacterAddressGroup(sld, "FortFrance_tavern", "sit", "sit4");
			AddLandQuestMark(characterFromId("Del_shturman"), "questmarkmain");
		break;
		
		//Делюк
		case "Del_Folke_1":
			DelLandQuestMark(npchar);
			dialog.text = "Cap...";
			link.l1 = "I have a million of questions, but I'll ask just this one: how did you manage to accumulate new debts while you have been with me this whole time, teaching me seamanship!";
			link.l1.go = "Del_Folke_2";
		break;
		
		case "Del_Folke_2":
			dialog.text = "I'm ashamed to admit it, Captain, but I've been borrowing from various lenders long before I joined your crew. My plan was to lay low and work on your ship until I earned enough to pay off all my debts. But I made the mistake of leaving the ship here to get involved with a certain woman here in St. Pierre, and the soldiers apprehended me right from under her. I didn't accrue any new debts in Martinique, since you have paid for my last one, I swear!";
			link.l1 = "You're an imbecile, Deluc, and you've made me the laughingstock of St. Pierre!";
			link.l1.go = "Del_Folke_3a";
			link.l2 = "Impressive, Folke. Thanks for the anecdote.";
			link.l2.go = "Del_Folke_3b";
		break;
		
		case "Del_Folke_3a":
			AddComplexSelfExpToScill(10, 10, 10, 10);
			dialog.text = "What will you do, Captain? Can you bail me out again? Finding a new navigator won't be easy, you know...";
			link.l1 = "Stay put for now. I'll make a decision. I may visit the banker again.";
			link.l1.go = "Del_Folke_4";
		break;
		
		case "Del_Folke_3b":
			AddCharacterExpToSkill(pchar, "Sailing", 10);//навигация
			AddCharacterExpToSkill(pchar, "Commerce", 10);//торговля
			dialog.text = "What will you do, Captain? Can you bail me out again? Finding a new navigator won't be easy, you know...";
			link.l1 = "Stay put for now. I'll make a decision. I may visit the banker again.";
			link.l1.go = "Del_Folke_4";
		break;
		
		case "Del_Folke_4":
			dialog.text = "It's not like I have anywhere to go...";
			link.l1 = "...";
			link.l1.go = "Del_Folke_5";
		break;
		
		case "Del_Folke_5":
			DialogExit();
			
			pchar.questTemp.Del_Rostovshik = true;
			LAi_CharacterDisableDialog(npchar);
			AddLandQuestMark(characterFromId("FortFrance_usurer"), "questmarkmain");
		break;
		
		case "Del_Folke_10":
			dialog.text = "Captain, thank you. You've settled my debts, but now I owe you an even greater debt - my life. And I'm truly grateful for it! I assure you, you won't find a more loyal man anywhere in this world!";
			link.l1 = "I suppose some debts can only be repaid by incurring others. Let's get back to work, Folke. There's plenty to be done at sea.";
			link.l1.go = "Del_Folke_11a";
			link.l2 = "Don't forget that, Deluc. Next time I'll just shoot you.";
			link.l2.go = "Del_Folke_11b";
			
			chrDisableReloadToLocation = false;
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
			QuestOpenSeaExit()
			sld = CharacterFromID("Del_shturman");
			sld.lifeday = 0;
			
			sld = CharacterFromID("Del_Ohranik");
			LAi_SetActorType(sld);
			LAi_ActorGoToLocation(sld, "reload", "reload3", "none", "", "", "", -1);
		break;
		
		case "Del_Folke_11a":
			AddCharacterExpToSkill(pchar, "Sailing", 10);//навигация
			AddCharacterExpToSkill(pchar, "Commerce", 10);//торговля
			dialog.text = "Aye aye, Captain!";
			link.l1 = "...";
			link.l1.go = "Del_Folke_12";
		break;
		
		case "Del_Folke_11b":
			AddComplexSelfExpToScill(10, 10, 10, 10);
			dialog.text = "Aye aye, Captain!";
			link.l1 = "...";
			link.l1.go = "Del_Folke_12";
		break;
		
		case "Del_Folke_12":
			DialogExit();
			EndQuestMovie();
			AddQuestRecord("FolkeDeluc", "3");
			CloseQuestHeader("FolkeDeluc");
			
			ChangeCharacterComplexReputation(pchar, "authority", -2);
			AddCrewMorale(Pchar, -30);
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "", "", "", "", -1);
			npchar.Dialog.Filename = "Enc_Officer_dialog.c";
			npchar.quest.meeting = true;
			Pchar.questTemp.HiringOfficerIDX = GetCharacterIndex(npchar.id);
			npchar.OfficerWantToGo.DontGo = true;
			npchar.loyality = MAX_LOYALITY;
			AddPassenger(pchar, npchar, false);
			npchar.OfficerImmortal = true;
			npchar.Health.HP       = 60.0; 
			npchar.Health.maxHP    = 60.0;
			SetCharacterPerk(npchar, "ShipEscape");
			npchar.location = "None";
			npchar.Dialog.CurrentNode = "hired";
			npchar.Payment = true;
			SetCharacterPerk(npchar, "ByWorker");
			DeleteAttribute(npchar, "CompanionDisable");
		break;
		
		//Штурман из таверны. Стандартный диалог, но с некоторыми изменениями (обучение найма для новичков)
		case "Del_shturman":
			dialog.text = "Do you need an officer, captain?";
    		Link.l1 = "An officer? And what are you good at?";
    		Link.l1.go = "Del_Node_2";
			Link.l2 = "No, I've got full set.";
			Link.l2.go = "Exit";
			NextDiag.TempNode = "Del_OnceAgain";
		break;		
		case "Del_Node_2":
			dialog.text = "I am the best navigator within these waters. I still know a little about medicine. And I am ready to do you a favor and serve under you.";
			Link.l1 = "And how much do you want?";
			Link.l1.go = "Del_price";
			Link.l2 = "And what kind of specialist are you?";
			Link.l2.go = "Del_ShowParam_exit";
			Link.l3 = "Alas, I already have a navigator.";
			Link.l3.go = "Exit";
		break;		
		case "Del_price":
			dialog.text = "I think we can agree on 4000 pesos.";
			Link.l1 = "Isn't that a bit much?";
			Link.l1.go = "Del_trade";
			Link.l2 = "I agree. Consider yourself a part of the crew.";
			Link.l2.go = "Del_hire";
			Link.l3 = "You're not worth this money.";
			Link.l3.go = "exit";
		break;	
		case "Del_ShowParam_exit":
			NextDiag.TempNode = "Del_OnceAgain";
			NPChar.quest.meeting = true;
			DialogExit();
			
			PChar.SystemInfo.OnlyShowCharacter = true;
            LaunchCharacter(NPChar);
		break;		
		case "Del_OnceAgain":
			NextDiag.TempNode = "Del_OnceAgain";
			dialog.text = "Have you changed your mind, captain? Decided that a new navigator wouldn't hurt?";
			// boal -->
			if (FindFreeRandomOfficer() > 0)
			{
                Link.l1 = "Something like that. How much do you want?";
                Link.l1.go = "Del_price";
			}
			Link.l2 = "And what are you capable of?";
			Link.l2.go = "Del_ShowParam_exit";
			// boal <--
			Link.l3 = "I have a full set. See you.";
			Link.l3.go = "exit";
		break;		
		case "Del_trade":
			if (GetSummonSkillFromName(pchar, SKILL_COMMERCE) > 25)
			{
				dialog.text = "Alright... I guess I could agree even on 2500 pesos. What do you say?";
				Link.l1 = "Now that's better. You're in.";
				Link.l1.go = "Del_hire";
				pchar.questTemp.Del_SniziliTsenu = true;
			}
			else
			{
				dialog.text = "I am sorry, captain, but I am worth exactly as mush as I asked for. If it's too much for you then go find someone else.";
				Link.l1 = "Alright, I agree. I'll take you.";
				Link.l1.go = "Del_hire";				
				Link.l2 = "That's what I am going to do. Farewell.";
				Link.l2.go = "exit";
			}
		break;		
		case "Del_hire":
			if (CheckAttribute(pchar, "questTemp.Del_SniziliTsenu"))
			{
				if (sti(pchar.Money) >= 2500)
				{
					AddMoneyToCharacter(pchar, -2500);
					NextDiag.TempNode = "OnboardSoon";
					dialog.text = "Thank you, captain. You will not regret your choice.";
					Link.l1 = "I hope so.";
					Link.l1.go = "Del_Exit_hire";
					DeleteAttribute(pchar, "questTemp.Del_SniziliTsenu");
				}
				else
				{
					dialog.text = "I see you're short of cash, captain! I am sorry, but I don't work in credit.";
					Link.l1 = "Oh, devil!";
					Link.l1.go = "Exit";								
				}
			}
			else
			{
				if (sti(pchar.Money) >= 4000)
				{
					AddMoneyToCharacter(pchar, -4000);
					NextDiag.TempNode = "Del_OnboardSoon";
					dialog.text = "Thank you, captain. You will not regret your choice.";
					Link.l1 = "I hope so.";
					Link.l1.go = "Del_Exit_hire";
				}
				else
				{
					dialog.text = "I see you're short of cash, captain! I am sorry, but I don't work in credit.";
					Link.l1 = "Oh, devil!";
					Link.l1.go = "Exit";								
				}
			}
		break;
		case "Del_OnboardSoon":			
			NextDiag.TempNode = "Del_OnboardSoon";
			dialog.text = "I'll just finish my drink, captain, and then will go to the ship. Don't worry, I will be there in time.";
			Link.l1 = "Alright. If you're late, I'll make you swab the deck!";
			Link.l1.go = "Exit";											
		break;
		case "Del_exit_hire":
			npchar.Dialog.Filename = "Enc_Officer_dialog.c";
			npchar.Dialog.CurrentNode = "hired";
			Pchar.questTemp.HiringOfficerIDX = GetCharacterIndex(Npchar.id);
			AddDialogExitQuestFunction("LandEnc_OfficerHired");
			NPChar.quest.meeting = true;
			npchar.loyality = 18;
			
			ChangeCharacterComplexReputation(pchar, "authority", 2);
			AddCrewMorale(Pchar, 30);
			QuestOpenSeaExit();
			DelLandQuestMark(npchar);
			pchar.quest.FortfranceJailOff_AddQuestMark.over = "yes";
			if (GetCharacterIndex("FortFranceJailOff") != -1)
			{
				DelLandQuestMark(characterFromId("FortFranceJailOff"));
			}
			sld = CharacterFromID("Folke");
			LAi_CharacterDisableDialog(sld);
			DeleteAttribute(pchar, "questTemp.Del_Deluck");
			DeleteAttribute(pchar, "questTemp.Del_DeluckSvoboda");
			DeleteAttribute(pchar, "questTemp.Del_Rostovshik");
			DeleteAttribute(pchar, "questTemp.Del_Rostovshik_repeat");
			pchar.questTemp.Del_DeluckSiditTurma = true;
			AddQuestRecord("FolkeDeluc", "4");
			CloseQuestHeader("FolkeDeluc");
			DialogExit();
		break;
		
		//Квест "Травля крысы"
		//Капитан корабля Хейтер
		case "TK_Kapitan":
			dialog.text = "Alright, alright! I surrender, damn it!";
			link.l1 = "You're now my prisoner, but you'll soon find yourself in St. Pierre facing the gallows.";
			link.l1.go = "TK_Kapitan_1";
			PChar.quest.TK_Potopil.over = "yes";
		break;
		
		case "TK_Kapitan_1":
			dialog.text = "This is it then... How did you know where to find me?";
			link.l1 = "The Governor personally briefed me on the situation.";
			link.l1.go = "TK_Kapitan_2";
		break;
		
		case "TK_Kapitan_2":
			dialog.text = "What a twat! He must have become aware of my plans and decided to openly fuck me right in front of his den to set an example for other crews!";
			link.l1 = "One more insult to his Excellency, and your journey to St. Pierre will be swift and unforgettable.";
			link.l1.go = "TK_Kapitan_3";
		break;
		
		case "TK_Kapitan_3":
			dialog.text = "Eh? I'm not talking about your excellency, mate. I'm talking about Jacques the Goodman\nDamn, the rumors were true! Barbazon realized I was becoming a threat, so he handed me over to the governor to keep me out of his way. This is why you had my exact location - and caught me with my pants down, ha ha!";
			link.l1 = "You're delusional. The Governor of Martinique wouldn't stoop to dealing with a pirate leader!";
			link.l1.go = "TK_Kapitan_4";
		break;
		
		case "TK_Kapitan_4":
			dialog.text = "Yeah, right. Maybe not directly, but I think he made a deal with Barbazon. It's convenient for him: a dangerous pirate is hanged, reports looking nice and the 'expenses for the military operation' are justified. I've served you know? So I know how it goes there. And you? Do you serve in garrison?";
			link.l1 = "I serve my country, and this conversation is over. Welcome to the brig.";
			link.l1.go = "TK_Kapitan_5";
		break;
		
		case "TK_Kapitan_5":
			dialog.text = "Hold on, mate. I'm not Castilian, and I wasn't out at sea today to plunder Fench merchants. I have principles, damn it! Let's make a deal, shall we?";
			link.l1 = "You're wasting your breath, pirate. Into the brig with you.";
			link.l1.go = "TK_Kapitan_7_1";
			link.l2 = "Trying to avoid the noose?";
			link.l2.go = "TK_Kapitan_6";
		break;
		
		case "TK_Kapitan_6":
			dialog.text = "I had a solid lead here, and I'll cut you in if you let me go. My life is only worth a couple of thousand in silver, but I can make you much more - and tax-free.";
			if (CheckAttribute(pchar, "questTemp.MOT_SharlyBad"))
			{
				link.l1 = "That's a tempting offer... Though piracy isn't exactly my forte.";
				link.l1.go = "TK_Kapitan_7";
			}
			else
			{
				link.l1 = "I'm not a pirate!";
				link.l1.go = "TK_Kapitan_7";
			}
		break;
		
		case "TK_Kapitan_7":
			dialog.text = "It's up to you, mate. Whether you want to be a man of fortune or a penniless captain with principles. If you want real money and freedom, you'll have to dabble in a bit of everything. Seize any opportunity.";
			link.l1 = "You certainly have a way with words...";
			link.l1.go = "TK_Kapitan_8";
			link.l2 = "Ahem... I suppose I'll take you to St. Pierre. That seems to be the right thing to do.";
			link.l2.go = "TK_Kapitan_7_1";
		break;
		
		case "TK_Kapitan_7_1":
			dialog.text = "Fuck you then!";
			link.l1 = "...";
			link.l1.go = "TK_Kapitan_Plen";
		break;
		
		case "TK_Kapitan_8":
			dialog.text = "So, do we have a deal?";
			link.l1 = "Yes. Tell me who your lead is, and you're free to go.";
			link.l1.go = "TK_Kapitan_9";
		break;
		
		case "TK_Kapitan_9":
			dialog.text = "There's a smartass Englishman of the Henry, a barque. He is about to finish his little trading voyage, getting goods from French plantations to Willemstad for a hefty profit. He's leaving Martinique for Curacao soon. It's an easy job - no escort, and the barque is loaded with valuables at the expense of its defenses. He is taking too long so rumors are spreading. My advice, mate? Don't be shy at the tavern. A few drinks for the locals, and they'll spill some secrets.";
			link.l1 = "Why no escort?";
			link.l1.go = "TK_Kapitan_10";
		break;
		
		case "TK_Kapitan_10":
			dialog.text = "How else would an Englishman conduct his business quietly in Curacao? It's an open war between England and the Netherlands, and getting a trade license is a hassle and it's expensive.";
			link.l1 = "But there's no war between France and England. What are the consequences if I attack a neutral vessel?";
			link.l1.go = "TK_Kapitan_11";
		break;
		
		case "TK_Kapitan_11":
			dialog.text = "None if you're discreet. The crew will definitely boast about your heroics at the nearest port, but as long as you're not regularly preying on English or Dutch ships, you should be fine. Approach the Henry under French colors. Load your cannons with grapeshot, close the distance, let fly the Black, fire a few volleys, and board the bitch. It's simple, mate.";
			link.l1 = "We'll see about that. I'll honor my word and release you. Don't don't give me a reason to regret it.";
			link.l1.go = "TK_Kapitan_12";
		break;
		
		case "TK_Kapitan_12":
			dialog.text = "I won't. Good hunting, mate.";
			link.l1 = "...";
			link.l1.go = "TK_Kapitan_Otpustil";
		break;
		
		case "TK_Kapitan_Plen":
			DialogExit();
			ChangeCharacterComplexReputation(pchar, "nobility", 1);
			sld = &Characters[sti(pchar.GenQuest.QuestAboardCabinDialogIdx)];
			sld.DontRansackCaptain = true;
			Lai_SetPlayerType(pchar);
			LAi_RemoveCheckMinHP(sld);
			LAi_SetImmortal(sld, true);
			LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
			
			sld = GetCharacter(NPC_GenerateCharacter("TK_Heiter2", "mercen_8", "man", "man", sti(PChar.rank), PIRATE, -1, false, "pirate"));
			sld.name = "Daniel";
			sld.lastname = "Montbars";
			AddPassenger(pchar, sld, false);
			SetCharacterRemovable(sld, false);
			ChangeCharacterAddressGroup(sld, "My_Deck", "goto", "goto7");
			LAi_SetGroundSitType(sld);
			LAi_CharacterDisableDialog(sld);
			DoQuestCheckDelay("TK_KapitanSidit_1", 0.8);
		break;
		
		case "TK_Kapitan_Otpustil":
			DialogExit();
			ChangeCharacterComplexReputation(pchar, "nobility", -1);
			sld = &Characters[sti(pchar.GenQuest.QuestAboardCabinDialogIdx)];
			Lai_SetPlayerType(pchar);
			LAi_RemoveCheckMinHP(sld);
			LAi_SetImmortal(sld, true);
			sld.ShipEnemyDisable  = true;
			LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
			LAi_SetCitizenType(sld);
			sld.lifeday = 0;
			LAi_EnableReload();
			Log_SetActiveAction("Reload");
			pchar.questTemp.TK_Otpustil = true;
			AddQuestRecord("TravlyaKrys", "4");
			
			SetTimerCondition("TK_GenrihSpawn", 0, 0, 1, false);	
		break;
		
		//Диего и Гийом за столиком по квесту "Встреча с Диего"
		case "VsD_DiegoAndErnat":
			dialog.text = "... I'll handle your gambling issues. Hey! Hold it together, man! Either pull yourself together, or I'll shake some sense into you myself.";
			link.l1 = "";
			link.l1.go = "VsD_DiegoAndErnat_2";
			sld = CharacterFromID("GiumDyubua");
			LAi_CharacterEnableDialog(sld);
		break;
		
		case "VsD_DiegoAndErnat_2":
			DialogExit();
			StartInstantDialogNoType("GiumDyubua", "VsD_DiegoAndErnat_3", "Quest\Sharlie\OtherNPC.c");
		break;
		
		case "VsD_DiegoAndErnat_3":
			dialog.text = "Monsieur, my apologies, but you're being a bit of a bother.";
			link.l1 = "Yes, of course. Have a pleasant day, gentlemen.";
			link.l1.go = "VsD_DiegoAndErnat_4";
		break;
		
		case "VsD_DiegoAndErnat_4":
			DialogExit();
			sld = CharacterFromID("Diego");
			LAi_CharacterDisableDialog(sld);
			sld = CharacterFromID("GiumDyubua");
			LAi_CharacterDisableDialog(sld);
		break;
		
		//Гийом Дюбуа по квесту "Встреча с Диего"
		case "VsD_GiumDyubua":
			dialog.text = "Captain de Maure! Wait!";
			link.l1 = "Yes, Lieutenant?";
			link.l1.go = "VsD_GiumDyubua_2";
			DelLandQuestMark(npchar);
		break;
		
		case "VsD_GiumDyubua_2":
			dialog.text = "I could barely keep up with you. There's been... a slight hiccup, Captain. What a mess!";
			link.l1 = "Take a breath and calm down, please.";
			link.l1.go = "VsD_GiumDyubua_3";
		break;
		
		case "VsD_GiumDyubua_3":
			dialog.text = "Right, right. Listen, after we've loaded the cannons, is there still space in the hold?";
			link.l1 = "I'm still new to this, so not entirely sure, but I assume there should be.";
			link.l1.go = "VsD_GiumDyubua_4";
		break;
		
		case "VsD_GiumDyubua_4":
			dialog.text = "Excellent! The Command wants to support the operation at Porto Bello in any way possible, so they've ordered an additional two hundred measures of gunpowder to be delivered to the Warlike. It might not seem like much, but a few extra salvos could turn the tide of battle!";
			link.l1 = "Very well, Lieutenant. I am ready to do my part. Load the powder - I don't mind it at all.";
			link.l1.go = "VsD_GiumDyubua_5";
		break;
		
		case "VsD_GiumDyubua_5":
			dialog.text = "Thank you, Captain. I'll inform our loading crew right away. Thankfully, they haven't finished with the '" + PChar.Ship.Name + "' yet. Good luck on your mission!";
			link.l1 = "Thanks, although it's been quite chaotic so far. Farewell, Lieutenant.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("VsD_GoToCity");
		break;
		
		//Фульк или Алонсо по квесту "Встреча с Диего"
		case "VsD_FolkeAlonso":
			dialog.text = "Jesus, Captain! Thank the heavens you're unharmed!";
			link.l1 = "The fuck's happened?! What's happened to my ship?!";
			link.l1.go = "VsD_FolkeAlonso_2";
		break;
		
		case "VsD_FolkeAlonso_2":
			dialog.text = "I don't know, Captain! I was just saying goodbye to a local woman I met recently... Oh shit! Eugenie!";
			link.l1 = "She's dead, "+npchar.name+". I'm sorry, but we need to focus and see if any of our crew is harmed.";
			link.l1.go = "VsD_FolkeAlonso_3";
		break;
		
		case "VsD_FolkeAlonso_3":
			dialog.text = "We barely knew each other... Aaah! Fuck! Reporting, Captain: most of the crew were ashore when the explosion occurred - fortunately. The boys were taking advantage of some shore leave before our next big voyage. But the ship's watch... I fear there are no survivors. Just look around! The debris injured or killed people even here, on this pier! It's a miracle the two of us are unharmed.";
			link.l1 = "What about the ship? Is she all right?!";
			link.l1.go = "VsD_FolkeAlonso_4";
		break;
		
		case "VsD_FolkeAlonso_4":
			dialog.text = "Is she?! My apologies, Captain. It's hard to say for sure, but it seems the explosion happened on the upper deck, not below. I don't see any active fires, and it looks like we've escaped major damage.";
			link.l1 = "...";
			link.l1.go = "VsD_FolkeAlonso_5";
			sld = GetCharacter(CreateCharacterClone(CharacterFromID("PortPaxAmmoOff"), 0));
			sld.id = "PortPaxAmmoOff_clone";
			LAi_LoginInCaptureTown(sld, true);
			ChangeCharacterAddressGroup(sld, "PortPax_town", "quest", "quest1");
			LAi_SetActorType(sld);
			LAi_ActorFollow(sld, pchar, "", -1);
		break;
		
		case "VsD_FolkeAlonso_5":
			DialogExit();
			LAi_SetStayType(pchar);
			sld = CharacterFromID("PortPaxAmmoOff_clone");
			sld.dialog.filename = "Quest\Sharlie\OtherNPC.c";
			sld.dialog.currentnode = "VsD_Komendant";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", 3, 0);
		break;
		
		case "VsD_Komendant":
			dialog.text = "What in the devil's name, Captain?!";
			link.l1 = "I'm asking the same thing, Colonel!";
			link.l1.go = "VsD_Komendant_1";
			sld = CharacterFromID("Tichingitu");
			if (sld.location == pchar.location && !LAi_IsDead(sld))
			{
				LAi_SetActorType(sld);
				LAi_ActorGoToLocator(sld, "reload", "reload1", "", -1);
			}
		break;
		
		case "VsD_Komendant_1":
			dialog.text = "Watch yourself, de Maure! You accepted this job from the Navy, you took on heavy cannons - property of the Crown, of strategic importance! Do you understand the significance of these cannons for the entire operation?! Your negligence has put almost four hundred men and a French warship in jeopardy! You are facing a trial for treason here!";
			link.l1 = "Calm down, Colonel! Miraculously, it appears my ship survived, and your precious cargo is mostly intact... mostly.";
			link.l1.go = "VsD_Komendant_2";
		break;
		
		case "VsD_Komendant_2":
			dialog.text = "What do you mean, mostly?!";
			link.l1 = "I can't guarantee that the two hundred measures of gunpowder, loaded at the last minute by one of your lieutenants, weren't damaged. They were meant to be loaded last, and they likely were the ones that exploded.";
			link.l1.go = "VsD_Komendant_3";
		break;
		
		case "VsD_Komendant_3":
			dialog.text = "What is this nonsense, Charles? What lieutenant? What gunpowder? I didn't issue such an order!";
			link.l1 = "This lieutenant must have been from your garrison. I didn't inquire about his name, but he seemed to be aware of the operation.";
			link.l1.go = "VsD_Komendant_4";
		break;
		
		case "VsD_Komendant_4":
			dialog.text = "Ah, shit! Seems the Castilians are inclined to play dirty too... I'll handle this unfortunate situation, Captain. You however still have a job to do: are you certain your ship is seaworthy?";
			link.l1 = "She's afloat, but she definitely needs significant repairs.";
			link.l1.go = "VsD_Komendant_5";
			SetMusic("classic_fra_music_day");
		break;
		
		case "VsD_Komendant_5":
			dialog.text = "No time for that, Captain. Set sail immediately and complete the mission. The stakes are too high to delay.";
			link.l1 = "Can't we have at least a day, for heaven's sake? The local shipyard could make the necessary repairs! And what about my crew?! There are surely casualties!";
			link.l1.go = "VsD_Komendant_6";
			sld = CharacterFromID("Tichingitu");
			if (sld.location == pchar.location && !LAi_IsDead(sld))
			{
				LAi_SetOfficerType(sld);
				sld.Dialog.Filename = "Quest\Sharlie\Tichingitu.c";
				sld.Dialog.CurrentNode = "Tichingitu_officer";
			}
			if (GetCharacterIndex("Folke") != -1 && CheckPassengerInCharacter(pchar, "Folke"))
			{
				sld = CharacterFromID("Folke");
				ChangeCharacterAddressGroup(sld, "none", "", "");
				sld.Dialog.Filename = "Enc_Officer_dialog.c";
				sld.Dialog.CurrentNode = "hired";
			}
			else
			{
				sld = CharacterFromID("Alonso");
				ChangeCharacterAddressGroup(sld, "none", "", "");
			}
		break;
		
		case "VsD_Komendant_6":
			dialog.text = "In case you hadn't noticed, the shipyard is ablaze. We're still determining if it's deliberate or a side result of the explosion. I can only promise you that your wounded will receive medical care, and the Crown will bear the cost of burying the dead.";
			link.l1 = "Are you serious? That's the best you can offer?";
			link.l1.go = "VsD_Komendant_7";
			sld = CharacterFromID("VsD_Tsyganka");
			ChangeCharacterAddressGroup(sld, "PortPax_town", "reload", "reload5_back");
			LAi_CharacterEnableDialog(sld);
			LAi_SetActorType(sld);
			LAi_ActorFollow(sld, pchar, "", -1);
		break;
		
		case "VsD_Komendant_7":
			dialog.text = "Captain, France needs your assistance urgently. I'll provide you with planks, and if you play your cards smart, your ship will be nearly fully repaired by the time you reach Jamaica.";
			link.l1 = "Pardon me, but what planks? And why Jamaica?";
			link.l1.go = "VsD_Komendant_8";
			pchar.ship.HP = sti(pchar.ship.HP) / 2;
			pchar.Ship.Crew.Quantity = sti(pchar.ship.Crew.Quantity) - sti(pchar.ship.Crew.Quantity) / 7;
			AddCharacterGoodsSimple(pchar, GOOD_PLANKS, 100);
		break;
		
		case "VsD_Komendant_8":
			dialog.text = "Your crew can perform emergency repairs at sea with the planks - a primary repair material. And Jamaica is rather close to one of the routes you can take to Porto Bello. If you don't waste time, you can finish repairs and recruit a full crew there.";
			link.l1 = "Very well, then. I'll set sail immediately, Colonel.";
			link.l1.go = "VsD_Komendant_9";
			
			sld = CharacterFromID("PortRoyal_shipyarder");
			sld.TrialDelQuestMark = true;
			AddLandQuestMark(sld, "questmarkmain");
			AddMapQuestMarkCity("PortRoyal", false);
		break;
		
		case "VsD_Komendant_9":
			DialogExit();
			LAi_SetStayType(pchar);
			
			sld = CharacterFromID("VsD_Tsyganka");
			sld.dialog.filename = "Quest\Sharlie\OtherNPC.c";
			sld.dialog.currentnode = "VsD_Tsyganka";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", 3, 0);
			
			sld = CharacterFromID("PortPaxAmmoOff_clone");
			sld.lifeday = 0;
			LAi_SetActorType(sld);
			LAi_ActorGoToLocation(sld, "reload", "gate_back", "none", "", "", "", -1);
		break;
		
		case "VsD_Tsyganka":
			dialog.text = "Why the rush, dear?";
			link.l1 = "Darling, I don't have time for this right now. Can't you see what's happening?";
			link.l1.go = "VsD_Tsyganka_1";
		break;
		
		case "VsD_Tsyganka_1":
			dialog.text = "Oh, the current troubles are dire, but I can tell from your hand that there are more arising on the horizon.";
			link.l1 = "Anyone can see that even without looking at my hand, which I might add, is in a glove. Fine, I'll play along: what's the price for averting disaster these days?";
			link.l1.go = "VsD_Tsyganka_2";
		break;
		
		case "VsD_Tsyganka_2":
			dialog.text = "I don't have that power, handsome. And even if I did, I wouldn't be able to affort it. But I can still help you out... with your ship. The girl is in a sorry state, my dear.";
			link.l1 = "I've never known your gypsy lot to have ambitions in carpentry.";
			link.l1.go = "VsD_Tsyganka_3";
			
			for (i=3; i<=8; i++)
			{				
				sld = CharacterFromID("VsD_MirnyeMan_"+i);
				LAi_SetCitizenType(sld);
			}
			for (i=3; i<=6; i++)
			{				
				sld = CharacterFromID("VsD_MirnyeWoman_"+i);
				LAi_SetCitizenType(sld);
			}
			for (i=1; i<=6; i++)
			{				
				sld = CharacterFromID("VsD_Sold_"+i);
				LAi_SetCitizenType(sld);
			}
			//Возвращаем всё обратно
			chrDisableReloadToLocation = false;
			bDisableFastReload = false;
			bDisableCharacterMenu = false;
			SetLocationCapturedState("PortPax_town", false);
			Locations[FindLocation("PortPax_town")].locators_radius.quest.quest1 = 1.0;
			Locations[FindLocation("PortPax_town")].locators_radius.patrol.patrol14 = 0.5;
			LocatorReloadEnterDisable("PortPax_ExitTown", "reload2_back", false);
			LocatorReloadEnterDisable("PortPax_ExitTown", "reload1_back", false);
			LAi_LocationFightDisable(&Locations[FindLocation("PortPax_town")], false);
			LAi_LocationFightDisable(&Locations[FindLocation("PortPax_Fort")], false);
			
			for (i=1; i<=5; i++)
			{
				sld = CharacterFromID("VsD_Guard_"+i);
				sld.lifeday = 0;
			}
			//Диего исчезает
			sld = CharacterFromID("Diego");
			LAi_CharacterEnableDialog(sld);
			sld.location = "None";
			//Верфь закрывается
			LocatorReloadEnterDisable("PortPax_Town", "reload5_back", true);
			SetTimerCondition("VsD_VerfOtkryt", 0, 0, 7, false);
			//Труп предателя в джунглях
			PChar.quest.VsD_TrupPredatelya.win_condition.l1 = "location";
			PChar.quest.VsD_TrupPredatelya.win_condition.l1.location = "PortPax_ExitTown";
			PChar.quest.VsD_TrupPredatelya.win_condition = "VsD_TrupPredatelya";
			SetTimerCondition("VsD_TrupPredatelya_3", 0, 0, 60, false);
		break;
		
		case "VsD_Tsyganka_3":
			dialog.text = "You, dear, are hardly a carpenter yourself. Do you think planks alone will repair the ship? They'll only weigh you down unless you have a master carpenter...";
			link.l1 = "Or?";
			link.l1.go = "VsD_Tsyganka_4";
		break;
		
		case "VsD_Tsyganka_4":
			dialog.text = "There's a potent amulet, revered by the locals. Wood bends to its will, and even those unfamiliar with carpentry find themselves skilled once they wear it. It's yours for a mere thousand pesos, dear.";
			if (sti(pchar.Money) >= 1000)
			{
				link.l1 = "Very well, you have a deal. I need all the help I can get.";
				link.l1.go = "VsD_Tsyganka_Da";
			}
			link.l2 = "I don't have time for your sorcery. Go in peace, witch, and don't meddle.";
			link.l2.go = "VsD_Tsyganka_Net";
			npchar.lifeday = 0;
		break;
		
		case "VsD_Tsyganka_Net":
			DialogExit();
			LAi_SetPlayerType(pchar);
			AddQuestRecord("Trial", "7_1");
			LAi_SetCitizenType(npchar);
			LAi_CharacterDisableDialog(npchar);
		break;
		
		case "VsD_Tsyganka_Da":
			DialogExit();
			LAi_SetPlayerType(pchar);
			AddQuestRecord("Trial", "7_1");
			AddCharacterExpToSkill(pchar, "Repair", 20);
			AddMoneyToCharacter(pchar, -1000);
			GiveItem2Character(PChar, "obereg_1");
			Log_info("You have received Amulet 'Teredo'");
			LAi_SetCitizenType(npchar);
			LAi_CharacterDisableDialog(npchar);
		break;
		
		//замечание по обнажённому оружию от персонажей типа citizen
		case "CitizenNotBlade":
			dialog.text = NPCharSexPhrase(NPChar, "Listen you, I am a law abiding citizen of this city. I must ask you not to walk around with your blade exposed like a robber.", "Sir please, the law is clear that men may not go about with weapons drawn within the city walls.");
			link.l1 = LinkRandPhrase("Alright.", "Fine.", "As you wish...");
			link.l1.go = "exit";
			NextDiag.TempNode = "First time";
			if (npchar.id == "GigoloMan") NextDiag.TempNode = "GigoloMan";
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}
