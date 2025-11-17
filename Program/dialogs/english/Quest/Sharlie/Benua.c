int iBenuaPseudoGlobal;

// аббат Бенуа
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	int rate;
    bool bOk;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			if (CheckAttribute(pchar, "questTemp.Sharlie.BenuaLoan.Late")) // Addon 2016-1 Jason пиратская линейка 1
			{
				dialog.text = "It's good to see you, my son.  Are you here to settle your debt?";
				if (PCharDublonsTotal() >= 100 && sti(pchar.money) >= 50000)
				{
					link.l1 = "Yes, father. I am.";
					link.l1.go = "FastStart_7";
				}
				else
				{
					link.l1 = "I am sorry for the delay, but I am not here for that. But I will be soon, don’t you worry.";
					link.l1.go = "exit";
				}
				break;
			}
			if (CheckAttribute(pchar, "questTemp.Sharlie") && pchar.questTemp.Sharlie == "benua_final")
			{
				dialog.text = "Is there anything you need, my son?";
				link.l1 = "Yes, father. I would like to see my brother, Michel de Montper. He said...";
				link.l1.go = "escape";
				break;
			}
			dialog.text = "Is there something you need, my son?";
			if (CheckAttribute(pchar, "questTemp.Sharlie.FastStart") && !CheckAttribute(npchar, "quest.FastStart") && !CheckAttribute(npchar, "quest.meet")) // ещё не виделись
			{
				link.l1 = "Yes, Father. I need your help. My name is "+GetFullName(pchar)+". Michel de Montper advised me to speak with you.";
				link.l1.go = "FastStart";
			}
			if (CheckAttribute(npchar, "quest.help") && !CheckAttribute(npchar, "quest.meet")) // ещё не виделись
			{
				link.l1 = "Yes, father. I need your help. My name is "+GetFullName(pchar)+". I was advised to speak with you by my brother, Michel de Monper.";
				link.l1.go = "meet";
			}
			if (CheckAttribute(pchar, "questTemp.Sharlie.FastStart") && !CheckAttribute(npchar, "quest.FastStart") && CheckAttribute(npchar, "quest.meet"))
			{
				link.l1 = "Yes, pater. I need a ship to help Michel, yet I have only just arrived in the Caribbean and my wallet is empty. My brother told me you could lend me some money...";
				link.l1.go = "FastStart_2";
			}
			//--> Дикая Роза
			if (CheckAttribute(pchar, "questTemp.WildRose_Etap3_Benua"))
			{
				link.l1 = "Greetings, Father. We need your help – in a rather unusual matter.";
				link.l1.go = "WildRose_Abb_2";
				break;
			}
			if (CheckAttribute(pchar, "questTemp.WildRose_Etap3_Benua_2") && PCharDublonsTotal() >= 800)
			{
				link.l3 = "Father, I have gathered the required sum. Eight hundred in gold.";
				link.l3.go = "WildRose_Abb_14_pay";
			}
			if (CheckAttribute(pchar, "questTemp.WildRose_Etap3_Benua_3"))
			{
				dialog.text = "Greetings, my son. I suppose you have come to hear the results of your... ahem, your affair?";
				link.l1 = "As perceptive as ever, Father. Do not keep me waiting – tell me, what has your man discovered?";
				link.l1.go = "WildRose_Abb_16";
				break;
			}
			//<-- Дикая Роза
			if (CheckAttribute(npchar, "quest.help") && CheckAttribute(npchar, "quest.meet"))
			{
				link.l1 = "Yes, father. I need your help.";
				if (CheckAttribute(npchar, "quest.relation_info")) link.l1.go = "help";
				else link.l1.go = "help_start";
			}
			if (CheckAttribute(pchar, "questTemp.Sharlie.BenuaLoan") && PCharDublonsTotal() >= 100 && sti(pchar.money) >= 50000)
			{
				link.l2 = "Yes, Father. I am.";
				link.l2.go = "FastStart_7";
			}
			link.l9 = "No, nothing, Father.";
			link.l9.go = "exit";			
			NextDiag.TempNode = "First time";
		break;
		
		case "Benua_meeting":
			DelLandQuestMark(npchar);
			if(CheckAttribute(pchar, "questTemp.Sharlie.Citcount"))
				DeleteAttribute(pchar, "questTemp.Sharlie.Citcount");
			DelLandQuestMark(characterFromId("FortFrance_Mayor"));
			dialog.text = "What brings you to me, my son?";
			link.l1 = "Hello, Father. I was told to speak with you. My name is Charles de Maure. I am looking for Michel de Monper. As far as I know, he should be somewhere on Martinique. I'm... his brother.";
			link.l1.go = "Benua_meeting_1";			
		break;
		
		case "Benua_meeting_1":
			dialog.text = "Michel de Monper's brother? De Maure? How strange...";
			link.l1 = "I understand your doubts, father. We simply have different surnames. My father is Henri de Montper.";
			link.l1.go = "Benua_meeting_2";			
		break;
		
		case "Benua_meeting_2":
			dialog.text = "A-ah, I see now. I used to know Henri de Monper personally. Turn towards the light, young man. Yes! You look just like him. The same appearance, the same noble features! I am glad to see a son of Henri de Monper in our parish.\nAs for your question, I can tell you that Michel is a high-ranking officer of the Order of Malta, but he is... in trouble. Fortunately, one of the knights of the Order is currently visiting me. I believe he might agree to accompany you to your unfortunate brother—may the Lord have mercy on his fate...";
			link.l1 = "Who is this man, holy father?";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Sharlie_enterMaltie");
			NextDiag.TempNode = "First time";
			npchar.quest.meet = true;		
			if (GetCharacterIndex("SharlieKnown") != -1)
			{
				sld = characterFromId("SharlieKnown");
				sld.lifeday = 0;
			}			
		break;
		
		case "Benua_meeting_3":
			DialogExit();
			NextDiag.CurrentNode = "Benua_meeting_repeat";
			AddQuestRecord("Sharlie", "4");
			pchar.quest.Sharlie_Benua.win_condition.l1 = "Timer";
			pchar.quest.Sharlie_Benua.win_condition.l1.date.hour  = 6;
			pchar.quest.Sharlie_Benua.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 1);
			pchar.quest.Sharlie_Benua.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 1);
			pchar.quest.Sharlie_Benua.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 1);
			pchar.quest.Sharlie_Benua.function = "Sharlie_BenuaMaltie";
		break;
		
		case "Benua_meeting_repeat":
			dialog.text = "My son, come back tomorrow morning. At the moment, I have nothing more to tell you.";
			link.l1 = "All right.";
			link.l1.go = "exit";	
			NextDiag.TempNode = "Benua_meeting_repeat";
		break;
		
		/* case "Benua_maltie":
			dialog.text = "Hello, my son. As promised, the person I mentioned yesterday is already here waiting for you. He's ready to take you to your brother, who, as I have heard, is in a wretched state. May the Lord have mercy on his soul...";
			link.l1 = "Who is this man, holy father?";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Sharlie_enterMaltie");
			NextDiag.TempNode = "First time";
			npchar.quest.meet = true;
		break; */
		
		case "escape":
			dialog.text = "Yes, Charles, I'm aware of that. But I must disappoint you. Michel is not here.";
			link.l1 = "What do you mean he's not here? He said he would be waiting for me in your church! Father, what happened? Where's my brother?!";
			link.l1.go = "escape_1";
		break;
		
		case "escape_1":
			dialog.text = "My son, your brother was here and he left my modest abode late last night. Where he went, I don't know. But he has left this letter for you.";
			link.l1 = "I can't believe it... after all I've done for him! Give me that letter!";
			link.l1.go = "escape_2";
		break;
		
		case "escape_2":
			dialog.text = "Don't get so enraged, Charles. Here's the letter. Read it and then... then I would like to speak with you. But first, read your brother's message.";
			link.l1 = "I'm burning with impatience!";
			link.l1.go = "escape_3";
		break;
		
		case "escape_3":
			DialogExit();
			GiveItem2Character(pchar, "specialletter");
			ChangeItemDescribe("specialletter", "itmdescr_specialletter_mishelle");
			sld = ItemsFromID("specialletter");
			sld.text = "Letter_Mishelle";
			NextDiag.CurrentNode = "escape_4";
			LocatorReloadEnterDisable("FortFrance_town", "reload91", false); // лесник открыл входы
			LocatorReloadEnterDisable("FortFrance_town", "reload_jail", false);
		break;
		
		case "escape_4":
			if (CheckAttribute(pchar, "GenQuest.specialletter.read") && pchar.GenQuest.specialletter.read == "Letter_Mishelle")
			{
				dialog.text = "I see you've read the letter. Now, I would like to tell you something, Charles...";
				link.l1 = "But... how can that be? What kind of balderdash is this? I know my brother is peculiar, but he's not a madman!";
				link.l1.go = "escape_5";
			}
			else
			{
				dialog.text = "My son, read the letter. We'll speak later.";
				link.l1 = "Yes, father...";
				link.l1.go = "exit";
				NextDiag.TempNode = "escape_4";
			}
		break;
		
		case "escape_5":
			dialog.text = "Your brother's actions surprised me as well, Charles. I still feel moments of perplexity. A loyal servant of the Order and the Trinity, and yet he's behaving like a deserter.";
			link.l1 = "Have you any idea what the reasons for such strange behaviour could be?";
			link.l1.go = "escape_6";
		break;
		
		case "escape_6":
			dialog.text = "Alas, I don't. But I suppose he has motives of his own, deep motives. Abrogating one's entire past would suggest an extremely significant reason. I can't even imagine what it could be. But I feel that it involves something extremely bad... even awful.";
			link.l1 = "What could it be, father?";
			link.l1.go = "escape_7";
		break;
		
		case "escape_7":
			dialog.text = "My son, a priest sees not with his eyes, but with his heart. I cannot explain it to you in words, but... your brother has set forth to do something unclean, something foul. I never thought my mouth could utter this. However...";
			link.l1 = "Well, I don't doubt that my brother has planned something underhanded. I can even guess what exactly he's planning to do. This 'something' is yellow and makes a pleasant clinking sound.";
			link.l1.go = "escape_8";
		break;
		
		case "escape_8":
			dialog.text = "I don't think the lust for gold is what drives your brother. I would say that he needs something greater.";
			link.l1 = "I have learned a lot from Michel and have grasped his philosophy, so I think I'm able to discern what's important to him and what isn't. But I will keep your valued words in mind, father.";
			link.l1.go = "escape_9";
		break;
		
		case "escape_9":
			dialog.text = "God bless you, my son. Go, go now. May the Lord watch over you!";
			link.l1 = "Thank you, father. Goodbye!";
			link.l1.go = "escape_10";
		break;
		
		case "escape_10":
			DialogExit();
			NextDiag.CurrentNode = "first time";
			AddDialogExitQuestFunction("Sharlie_Benua_BrotherEscape");
		break;
		
		// уменьшение награды за голову
		case "meet":
			dialog.text = "Michel de Monper's brother? De Maure? How strange...";
			link.l1 = "I understand your doubts, father. We simply have different surnames. My father is Henri de Montper.";
			link.l1.go = "meet_1";			
		break;
		
		case "meet_1":
			dialog.text = "A-ah, I see now. I knew Henri de Monper personally. Turn towards the light, young man... Right! You look just like him. Same features, same noble profile! I am glad to see a son of Henri de Monper in our parish.\nI had already heard that Michel was visited by a man who arrived from Europe, but I could never have imagined it was his own brother. I hope you will be able to help Michel, he is going through a difficult time. Anyway, how can I be of service?";
			link.l1 = "Michel told me that you would be able to help if I ever got into trouble with the authorities.";
			link.l1.go = "help_info";	
			npchar.quest.meet = true;
		break;
		
		case "help_info":
			dialog.text = "That is what Michel told you? I see. Well, I can be of help in such matters. I have some influence within the Holy Roman Church and the Dutch colonies. Therefore, I might be able to intercede between you and the Spanish as well as Dutch authorities. Of course, I won't be able to do much if your misconduct has become too serious – in that case, only a slight mitigation can be achieved.  It will require several intercessions for complete reconciliation. Besides, in any case, you will have to supply me with golden doubloons for charities and voyage expenses. Also, I can only help you with one nation at a time. If you find these terms acceptable, don't hesitate to turn to me, and we will see what can be done.";
			link.l1 = "Thank you! I'll keep that in mind.";
			link.l1.go = "exit";
			npchar.quest.relation_info = "true";
		break;
		
		case "help_start":
			dialog.text = "What can I do for you, my son? Speak, I am listening.";
			link.l1 = "Michel told me that you would be able to help if I ever got into trouble with the authorities.";
			link.l1.go = "help_info";
		break;
		
		case "help":
			dialog.text = "How can I help you, my son?";
			if (ChangeCharacterNationReputation(pchar, SPAIN, 0) < 0 && !CheckAttribute(npchar, "quest.relation"))
			{
				link.l1 = "I've got into trouble with the Spanish authorities.";
				link.l1.go = "relation_spa";
			}
			if (ChangeCharacterNationReputation(pchar, HOLLAND, 0) < 0 && !CheckAttribute(npchar, "quest.relation"))
			{
				link.l2 = "I've got into trouble with the Dutch authorities.";
				link.l2.go = "relation_hol";
			}
			link.l9 = "Sorry, I think I'll handle things myself this time.";
			link.l9.go = "exit";
		break;
		
		case "relation_spa": // patch-10
			pchar.GenQuest.BenuaNation = SPAIN;
			dialog.text = "So, the noble señores are eager to put you inside Havana's dungeons...";
			link.l1 = "Exactly so, father...";
			link.l1.go = "relation";
		break;
		
		case "relation_hol":
			pchar.GenQuest.BenuaNation = HOLLAND;
			dialog.text = "So, the clever merchants are eager to throw you into Willemstad's dungeons...";
			link.l1 = "Exactly so, father...";
			link.l1.go = "relation";
		break;
		
		case "relation":
			rate = wdmGetNationThreat(sti(pchar.GenQuest.BenuaNation));
			iBenuaPseudoGlobal = DiplomatDublonPayment(rate, "Benua", false);
			sTemp = FindRussianDublonString(iBenuaPseudoGlobal);
			if (rate < 2)
			{
				dialog.text = "Yes, those rumours have reached our church as well. I can help you with your dilemma. It's something that can be resolved. I need " + sTemp + " to smooth out your predicament.";
				if (PCharDublonsTotal() >= iBenuaPseudoGlobal) // Sinistra legendary edition
				{
					link.l1 = "Great! Here's the gold.";
					link.l1.go = "agree";
				}
				link.l2 = "Then it's the right time for me to find the doubloons.";
				link.l2.go = "exit";
			}
			else
			{
				if (rate < 4)
				{
					dialog.text = "Yes, rumours of your 'feats' have reached our church too. You've tarnished your reputation, my son. You should be more prudent. But I can help you. I need " + sTemp + " to smooth over your predicament.";
					if (PCharDublonsTotal() >= iBenuaPseudoGlobal) // Sinistra legendary edition
					{
						link.l1 = "Great! Here's the gold.";
						link.l1.go = "agree";
					}
					link.l2 = "Then it's the right time for me to find the doubloons.";
					link.l2.go = "exit";
				}
				else
				{
					dialog.text = "Yes, my son. You're just as desperate as your brother... This is probably a family trait. I can't completely correct the situation, but nevertheless, I believe I can alleviate your dismal predicament. And later we can make more offerings if you wish. I need " + sTemp + " for now and I will begin solving your dilemma right away.";
					if (PCharDublonsTotal() >= iBenuaPseudoGlobal) // Sinistra legendary edition
					{
						link.l1 = "Great! Here's the gold.";
						link.l1.go = "agree";
					}
					link.l2 = "Then it's the right time for me to find the doubloons.";
					link.l2.go = "exit";
				}
			}
		break;
		
		case "agree":
			RemoveDublonsFromPCharTotal(iBenuaPseudoGlobal); // Sinistra legendary edition
			PlaySound("interface\important_item.wav");
			dialog.text = "Now you will have to wait at least two weeks. I think that within this time I will be able to meet and speak with the right people.";
			link.l1 = "Thank you, father! I will be waiting...";
			link.l1.go = "agree_1";
		break;
		
		case "agree_1":
			DialogExit();
            bOk = HasShipTrait(pchar, "trait23");
            rate = 10 + hrand(5);
            rate = GetIntByCondition(bOk, rate, rate / 2);
			SetFunctionTimerCondition("ChangeNationRelationFromBenuaComplete", 0, 0, rate, false);
			pchar.GenQuest.BenuaNation.Rate = GetDiplomatRate(bOk, sti(pchar.GenQuest.BenuaNation));
			npchar.quest.relation = "true";
		break;
		
		// Addon 2016-1 Jason пиратская линейка 1
		case "FastStart":
			dialog.text = "De Maure? And you are a brother of Michel de Monper? Odd...";
			link.l1 = "I understand your doubts, padre. My father is Henri de Montper.";
			link.l1.go = "FastStart_1";			
		break;
		
		case "FastStart_1":
			dialog.text = "A-ah, I see. I knew Henri de Monper personally. Step into the light, young man. Right! Same eyes, same noble features! I am pleased to see a son of Henri de Monper in my church. I hope you will be able to help your brother. He has had a lot of bad luck recently.";
			link.l1 = "Yes, pater. I need a ship to help Michel, yet I have only just arrived in the Caribbean and my wallet is empty. My brother told me you could lend me some money...";
			link.l1.go = "FastStart_2";	
			npchar.quest.meet = true;
		break;
		
		case "FastStart_2":
			DelLandQuestMark(npchar);
			dialog.text = "Michel told you that?";
			link.l1 = "Padre, I may not sound very trustworthy, yet it's true. The sooner I get a ship, the sooner I'll be able to get my brother out of jail.";
			link.l1.go = "FastStart_3";
		break;
		
		case "FastStart_3":
			dialog.text = "I see, my son. I can tell you are speaking the truth. Well, for the sake of Michel and your father, I will help you. I have some savings, take them. I assume 50,000 pesos and 100 doubloons will suffice.";
			link.l1 = "Thank you, padre. What are the terms?";
			link.l1.go = "FastStart_4";
		break;
		
		case "FastStart_4":
			AddMoneyToCharacter(pchar, 50000);
			TakeNItems(pchar, "gold_dublon", 100);
			dialog.text = "No pressure. Half a year to repay will be enough.";
			link.l1 = "Very good, holy father. Thank you again!";
			link.l1.go = "FastStart_5";
		break;
		
		case "FastStart_5":
			dialog.text = "Go with my blessing, my son.";
			link.l1 = "...";
			link.l1.go = "FastStart_6";
		break;
		
		case "FastStart_6":
			DialogExit();
			NextDiag.CurrentNode = "first time";
			npchar.quest.FastStart = "true";
			pchar.questTemp.Sharlie.BenuaLoan = "true";
			SetFunctionTimerCondition("Sharlie_BenuaLoanTime", 0, 0, 180, false);
			AddQuestRecord("Sharlie", "5-2");
		break;
		
		case "FastStart_7":
			dialog.text = "Splendid, my son. I hope that money did you some good.";
			link.l1 = "Indeed, it did! Thank you!";
			link.l1.go = "FastStart_8";
		break;
		
		case "FastStart_8":
			DialogExit();
			NextDiag.CurrentNode = "first time";
			AddMoneyToCharacter(pchar, -50000);
			RemoveDublonsFromPCharTotal(100);
			pchar.quest.Sharlie_BenuaLoanTime.over = "yes";
			DeleteAttribute(pchar, "questTemp.Sharlie.BenuaLoan");
			AddQuestRecord("Sharlie", "5-3");
		break;
		
		// Jason Долго и счастливо
		case "LH_abbat":
			dialog.text = "Charles, I can't believe my eyes! What brings you here?!";
			link.l1 = "Bless me, Holy Father, for I come bearing good news - I am getting married, and I would like you to be the priest at my wedding.";
			link.l1.go = "LH_abbat_1";
		break;
		
		case "LH_abbat_1":
			dialog.text = "My son, this is wonderful! So you received that letter from your father and decided, as usual, to act according to your own understanding? I am sincerely happy for you! But I'm afraid I can't help you unless you decide to get married in this church.";
			link.l1 = "I understand that your mission is at an impasse, Holy Father. Can I help you with anything? Since the marriage will take place in a Spanish chapel, of course, it is an adventure I would like to undertake, but I am determined to hold the celebration in Martinique. Moderately magnificent, and in the presence of reputable witnesses and honourable guests.";
			link.l1.go = "LH_abbat_2";
		break;
		
		case "LH_abbat_2":
			dialog.text = "I'm sorry, my son, but all your authority is worth nothing against the stubbornness of the highest hierarchs of the Catholic Church, especially in the Spanish colonies. We haven't agreed on the question of sharing the influence of the Catholic missions between our countries, and now I'm here, as an honoured guest and an honoured hostage. The Spaniards are waiting for a better offer from our side. I have sent a message to Europe; hopefully the answer will come in two months' time and we will be able to resume negotiations. If it doesn't arrive in two months, it will certainly be here within the next six months.\nAnd yes, while the Pope and Mazarin have reached a compromise in the last couple of weeks, it's too early to talk about a truly warm relationship. Honestly, I'm not sure that we will ever come to any agreement. It seems to me that Palotti simply keeps me as a bargaining chip in his own political power plays. However, I have to say, the inquisitor has excellent coffee!";
			link.l1 = "I have neither six months nor two months! I must fulfil my father's wish, or he will force me to marry against my will. And his health isn't what it used to be, yet I would like to have time to introduce him to my chosen one and the future lady of Monper.";
			link.l1.go = "LH_abbat_3";
		break;
		
		case "LH_abbat_3":
			dialog.text = "I'm afraid you will have to find another priest for your wedding then, my son. Alas, I shall be staying here for a long time.";
			link.l1 = "What would you say if I took you away from the inquisitor's coffee?";
			link.l1.go = "LH_abbat_4";
		break;
		
		case "LH_abbat_4":
			dialog.text = "I would gladly accept your help. I suspect that I wasn't chosen for this mission by chance. In the worst case, they'll simply forget about Father Benoit. And, although the Lord commanded me to endure, I am burdened by my conclusion, despite all its... blessings. But, I repeat - it's unlikely that Father Palotti will listen to your requests.";
			link.l1 = "Then I'll save myself some time and won't try to convince him. We'll just leave the church as soon as the service is over and go straight to my ship. Don't hesitate, Holy Father – they've seen our meeting and will recognise me, and it will be much harder to help you if I have to get you out of the governor's mansion.";
			link.l1.go = "LH_abbat_5";
		break;
		
		case "LH_abbat_5":
			dialog.text = "It's risky, my son, very risky. A group of guards is waiting outside to escort me to the mansion, and the city is full of soldiers.";
			link.l1 = "We will go with the element of surprise, Father Benoit. You just have to trust me and everything will be fine. I have some... experience in these matters.";
			link.l1.go = "LH_abbat_6";
		break;
		
		case "LH_abbat_6":
			dialog.text = "As you wish. But please, do it without unnecessary bloodshed! I have had some experiences of this kind too... Lead us, my son. I'm right behind you. But I won't take up a weapon, so don't even ask.";
			link.l1 = "Didn't even think about it, Father. I can handle it. Follow me, but be careful, they might shoot at us.";
			link.l1.go = "LH_abbat_7";
		break;
		
		case "LH_abbat_7":
			DialogExit();
			LongHappy_SantiagoBenuaEscape();
		break;
		
		case "LH_abbat_8":
			LocatorReloadEnterDisable("FortFrance_town", "reload1_back", false);
			LocatorReloadEnterDisable("FortFrance_town", "reload2_back", false);
			LocatorReloadEnterDisable("FortFrance_town", "gate_back", false);
			dialog.text = "My son, I didn't have time to thank you for my release. Apparently, the Spanish bishop and Inquisitor Palotti wanted to disrupt the newly established relations between our cardinal and the Holy See, so you acted entirely in the interests of our country. Again. But no one will say 'thank you', except me.";
			link.l1 = "Common thing, Holy Father. Glad I managed to help. But I also have to ask you something, remember?";
			link.l1.go = "LH_abbat_9";
		break;
		
		case "LH_abbat_9":
			dialog.text = "Of course! So let's get to the pleasant business - Charles, how are the preparations for your most important day coming along?";
			link.l1 = "It's slowly taking shape. I've known military campaigns that were prepared more easily and quickly, but it's worth it!";
			link.l1.go = "LH_abbat_10";
		break;
		
		case "LH_abbat_10":
			dialog.text = "Of course, my son! And on this occasion, I want to clarify something – how do you envision your wedding ceremony?";
			link.l1 = "You mean, how pompous?";
			link.l1.go = "LH_abbat_11";
		break;
		
		case "LH_abbat_11":
			dialog.text = "Of course! I need to prepare the church, and perhaps you will want to invite some important people.";
			link.l1 = "Nothing special, Holy Father. Those whom I consider our friends will be waiting for us elsewhere. There will only be a few officials, my men, and some ordinary onlookers present here.";
			link.l1.go = "LH_abbat_12";
		break;
		
		case "LH_abbat_12":
			dialog.text = "Well, then, I think we can manage with a small donation.";
			link.l1 = "That doesn't sound too frightening. And how much is such a donation in gold?";
			link.l1.go = "LH_abbat_13";
		break;
		
		case "LH_abbat_13":
			dialog.text = "For the choir, solemn service, and other expenses - one hundred and fifty, no more. Plus, the usual donation from the newlyweds, in total - two hundred doubloons.";
			if (PCharDublonsTotal() >= 200) // Sinistra legendary edition
			{
				link.l1 = "Here you go, Holy Father.";
				link.l1.go = "LH_abbat_15";
			}
			else
			{
				link.l1 = "About those military campaigns... I shall have to walk to the bank and return.";
				link.l1.go = "LH_abbat_14";
			}
		break;
		
		case "LH_abbat_14":
			DialogExit();
			npchar.dialog.currentnode = "LH_abbat_14_1";
		break;
		
		case "LH_abbat_14_1":
			dialog.text = "What about your donation, my son?";
			if (PCharDublonsTotal() >= 200) // Sinistra legendary edition
			{
				link.l1 = "Here you go, Holy Father.";
				link.l1.go = "LH_abbat_15";
			}
			else
			{
				link.l1 = "Yes, yes, I will bring it soon...";
				link.l1.go = "LH_abbat_14";
			}
		break;
		
		case "LH_abbat_15":
			RemoveDublonsFromPCharTotal(200); // Sinistra legendary edition
			dialog.text = "There is still one question that needs to be answered - who will give away the bride and bear witness to the marriage on her behalf?";
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer"))
			{
				pchar.questTemp.LongHappy.Pater1 = "Svenson";
				link.l1 = "Jan Svensson, from Blueweld. He is English, but a respected man and attached to Helen as if she were his own daughter, and her adoptive mother is Gladys McArthur.";
			}
			else
			{
				if (CheckAttribute(pchar, "questTemp.Patria.GenGovernor"))
				{
					pchar.questTemp.LongHappy.Pater1 = "Noel";
					link.l1 = "Baron Noël Forget, I'm sure he will do me the honour.";
				}
				else
				{
					pchar.questTemp.LongHappy.Pater1 = "Puancie";
					link.l1 = "Chevalier Philippe de Poincy, I'm sure he will do me the honour.";
				}
			}
			link.l1.go = "LH_abbat_16";
		break;
		
		case "LH_abbat_16":
			dialog.text = "Well, and who will testify for the groom? Remember, it must be a man of noble birth and worthy reputation.";
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer"))
			{
				if (CheckAttribute(pchar, "questTemp.Patria.GenGovernor"))
				{
					link.l1 = "Baron Noël Forget, I'm sure he will do me the honour.";
					link.l1.go = "LH_abbat_17_1";
				}
				else
				{
					link.l1 = "Chevalier Philippe de Poincy, I am sure he will do me the honour.";
					link.l1.go = "LH_abbat_17_2";
				}
				link.l2 = "Fadey is a respectable merchant from Guadeloupe. I just need to stock up on his favourite drink.";
				link.l2.go = "LH_abbat_17_3";
			}
			else
			{
				link.l1 = "Fadey is a respectable merchant from Guadeloupe. I just need to stock up on his favourite drink.";
				link.l1.go = "LH_abbat_17_3";
			}
		break;
		
		case "LH_abbat_17_1":
			pchar.questTemp.LongHappy.Pater2 = "Noel";
			dialog.text = "Great, I will send out the invitations, but the guests will need some time to arrive. I believe everything will be ready in a month, and the designated persons will have arrived in the city.";
			link.l1 = "Good! Then I have time to run a couple of errands. See you soon, Holy Father, and wish me luck!";
			link.l1.go = "LH_abbat_18";
		break;
		
		case "LH_abbat_17_2":
			pchar.questTemp.LongHappy.Pater2 = "Puancie";
			dialog.text = "Great, I will send out the invitations, but the guests will need some time to arrive. I think everything will be ready in a month, and the invited persons will have arrived in the city.";
			link.l1 = "Good! Then I have time to run a couple of errands. See you soon, Holy Father, and wish me luck!";
			link.l1.go = "LH_abbat_18";
		break;
		
		case "LH_abbat_17_3":
			pchar.questTemp.LongHappy.Pater2 = "Fadey";
			dialog.text = "Great, I will send out the invitations, but the guests will need some time to get here. I think everything will be ready in a month, and the indicated persons will have arrived in the city.";
			link.l1 = "Good! Then I have time to run a couple of errands. See you soon, Holy Father, and wish me luck!";
			link.l1.go = "LH_abbat_18";
		break;
		
		case "LH_abbat_18":
			DialogExit();
			AddQuestRecord("LongHappy", "11");
			SetFunctionTimerCondition("LongHappy_SenPierreGuests", 0, 0, 31, false); // таймер
			if (!CheckAttribute(pchar, "questTemp.LongHappy.MarryRum"))
			{
			pchar.questTemp.LongHappy = "toIslaTesoro";
			LocatorReloadEnterDisable("Pirates_town", "reload4_back", true);//закрыть таверну Исла-Тесоро
			}
			npchar.dialog.currentnode = "First time";
		break;
		
		case "LH_abbat_19":
			dialog.text = "So, the day has come, my son! Everything is ready – in a couple of hours we will be able to start. You look pale!";
			link.l1 = "I'm a little nervous, Holy Father.";
			link.l1.go = "LH_abbat_20";
		break;
		
		case "LH_abbat_20":
			dialog.text = "That's common. This is the most important day of your life, and I am sincerely happy for you, as is everyone who has come. I hope you at least remember the basic prayers – you've never exactly graced the church with your attention, have you? Nevertheless, I will help you in any case.\nAnd one more thing – as far as I understand, the bride won't change her principles and we will not see her in a dress? Well, high society is about to witness yet another surprise from you – you are full of them. Anyway, go, my son, make yourself presentable and we will begin.";
			link.l1 = "Yes, Holy Father. Let's do it.";
			link.l1.go = "LH_abbat_21";
		break;
		
		case "LH_abbat_21":
			DialogExit();
			chrDisableReloadToLocation = true;
			WaitDate("", 0, 0, 0, 2, 0);
			DoQuestReloadToLocation("FortFrance_church", "reload", "reload1", "LongHappy_MarryInit");
		break;
		
		case "LH_abbat_22":
			pchar.questTemp.LongHappy.Mistake = 0;
			dialog.text = "Pater noster, qui es in caelis, sanctificetur nomen tuum, ad...";
			link.l1 = "...adveniat regnum tuum";
			link.l1.go = "LH_abbat_23_1";
			link.l2 = "...requiem aeternam dona eis";
			link.l2.go = "LH_abbat_23_2";
		break;
		
		case "LH_abbat_23_1":
			dialog.text = "...fiat voluntas tua, sicut in caelo et in terra. Panem nostrum quotidianum da nobis hodie, et dimitte nobis debita nostra si...";
			link.l1 = "...sicut et nos dimittimus debitoribus nostris";
			link.l1.go = "LH_abbat_24_1";
			link.l2 = "...sicut erat in principio, et nunc et semper, et in saecula saeculorum. Amen";
			link.l2.go = "LH_abbat_24_2";
		break;
		
		case "LH_abbat_23_2":
			pchar.questTemp.LongHappy.Mistake = sti(pchar.questTemp.LongHappy.Mistake)+1;
			dialog.text = "E-e... Hm...";
			link.l1 = "";
			link.l1.go = "LH_abbat_23_1";
		break;
		
		case "LH_abbat_24_2":
			pchar.questTemp.LongHappy.Mistake = sti(pchar.questTemp.LongHappy.Mistake)+1;
			dialog.text = "E-e... Hm...";
			link.l1 = "";
			link.l1.go = "LH_abbat_24_1";
		break;
		
		case "LH_abbat_24_1":
			dialog.text = "et ne nos inducas in tentationem; sed libera nos a malo. Amen.";
			link.l1 = "Amen.";
			link.l1.go = "LH_abbat_25";
		break;
		
		case "LH_abbat_25":
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer")) sld = characterFromId("Helena");
			else sld = characterFromId("Mary");
			dialog.text = "Dearly beloved, we are gathered here together in the sight of God, and in the presence of this congregation, to join together this man and woman in holy Matrimony. Beloved "+sld.name+" and Charles, you listened to the word of God, who reminded you of the meaning of human love and matrimony. Now, on behalf of the Holy Church, I wish to challenge your intentions.\n"+sld.name+" and Charles, do you have a voluntary and sincere desire to join together in matrimony, before our Lord?";
			link.l1 = "Yes.";
			link.l1.go = "LH_abbat_26";
		break;
		
		case "LH_abbat_26":
			DialogExit();
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer")) sld = characterFromId("Helena");
			else sld = characterFromId("Mary");
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
		break;
		
		case "LH_abbat_27":
			dialog.text = "Do you intend to remain faithful to each other in health and in sickness, in happiness and in sorrow, until the end of your days?";
			link.l1 = "Yes.";
			link.l1.go = "LH_abbat_28";
		break;
		
		case "LH_abbat_28":
			DialogExit();
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer")) sld = characterFromId("Helena");
			else sld = characterFromId("Mary");
			sld.dialog.currentnode = "LongHappy_22";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
		break;
		
		case "LH_abbat_29":
			dialog.text = "Do you intend to love and accept the children whom our Lord will send you, and raise them in the Christian faith?";
			link.l1 = "Yes.";
			link.l1.go = "LH_abbat_30";
		break;
		
		case "LH_abbat_30":
			DialogExit();
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer")) sld = characterFromId("Helena");
			else sld = characterFromId("Mary");
			sld.dialog.currentnode = "LongHappy_24";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
		break;
		
		case "LH_abbat_31":
			dialog.text = "Well, turn to each other and make a vow.";
			link.l1 = "";
			link.l1.go = "LH_abbat_32";
		break;
		
		case "LH_abbat_32":
			DialogExit();
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer")) sld = characterFromId("Helena");
			else sld = characterFromId("Mary");
			sld.dialog.currentnode = "LongHappy_26";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
		break;
		
		case "LH_abbat_33":
			dialog.text = "Should anyone present here know of any reason why this couple should not be joined together in holy matrimony, speak now or forever hold your peace.\nIn this case, before the face of the Lord, and the people gathered here, I declare you husband and wife! In nomine Patris, et Filii, et Spiritus Sancti. Amen.";
			link.l1 = "Amen.";
			link.l1.go = "LH_abbat_34";
		break;
		
		case "LH_abbat_34":
			DialogExit();
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer")) sld = characterFromId("Helena");
			else sld = characterFromId("Mary");
			sld.dialog.currentnode = "LongHappy_29";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
		break;
		
		case "LH_abbat_35":
			string sTemp;
			if (sti(pchar.questTemp.LongHappy.Mistake) > 1) sTemp = "(Whispering) Charles, my son, just move your lips, I beg you - don't try to make any sound...";
			else sTemp = "";
			dialog.text = "Newlyweds, kneel down and pray together. Oratio fidelium. "+sTemp+"";
			link.l1 = "";
			link.l1.go = "LH_abbat_36";
		break;
		
		case "LH_abbat_36":
			DialogExit();
			SetLaunchFrameFormParam("Some time has passed...", "", 0.1, 3.0);
			LaunchFrameForm();
			WaitDate("", 0, 0, 0, 1, 0);
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer")) sld = characterFromId("Helena");
			else sld = characterFromId("Mary");
			sld.lastname = "de Maure";
			sld.SpecialRole = "wife";
			sld.dialog.currentnode = "LongHappy_31";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 4.0);
		break;
		
		case "LH_abbat_37":
			dialog.text = "My congratulations, son. Your father would be proud of you, and I am proud too. Be happy and take care of each other in these difficult times.";
			link.l1 = "Thank you, Holy Father. It was a wonderful service and I am glad that it was you who led it.";
			link.l1.go = "LH_abbat_38";
		break;
		
		//--> Дикая Роза
		case "WildRose_Abb_2":
			dialog.text = "So you have come to me for counsel, my children? Well then, I am all ears.";
			link.l1 = "Rather for assistance, Father. Assistance from a man who has connections and knows all manner of people...";
			link.l1.go = "WildRose_Abb_3";
			DelLandQuestMark(npchar);
			DeleteAttribute(pchar, "questTemp.WildRose_Etap3_Benua");
		break;

		case "WildRose_Abb_3":
			dialog.text = "Forgive me for interrupting you, my son, but I must remind you that I am but a humble abbot, not some secret agent.";
			link.l1 = "Yet a humble abbot might know a secret agent, might he not? Or at least suggest how one might reach him?";
			link.l1.go = "WildRose_Abb_4_fortune";
			link.l2 = "The matter that brought us here truly concerns certain long-forgotten secrets... We are only trying to drag them back into the light.";
			link.l2.go = "WildRose_Abb_4_stealth";
		break;

		case "WildRose_Abb_4_fortune":
			AddCharacterExpToSkill(pchar, "Fortune", 100);
			dialog.text = "Now, young man, this I do not like. Get to the point, and then we shall see how – or if – I may help you.";
			link.l1 = "Yes, Father. I shall try to be brief...";
			link.l1.go = "WildRose_Abb_5";
		break;

		case "WildRose_Abb_4_stealth":
			AddCharacterExpToSkill(pchar, "Sneak", 100);
			dialog.text = ""+pchar.name+", do not speak in riddles – it is, I confess, wearisome.";
			link.l1 = "Yes, Father. I shall try to be brief...";
			link.l1.go = "WildRose_Abb_5";
		break;

		case "WildRose_Abb_5":
			dialog.text = "Go on, my son.";
			link.l1 = "My companion, Mary Casper, is seeking her father – or at least some scrap of information about him. We have discovered that he was an officer in the English Navy and served aboard the brig 'Wrangler', which wrecked at Cape Catoche in 1638.";
			link.l1.go = "WildRose_Abb_6";
		break;

		case "WildRose_Abb_6":
			dialog.text = "And you hope that he yet lives? After so many years?";
			link.l1 = "Even if he did not survive the wreck, Mary wishes to know where her father came from, what manner of man he was, the life he led... Official papers are sparse in detail – yet even in them one may find something of value, do you not agree, Father?";
			link.l1.go = "WildRose_Abb_7";
		break;

		case "WildRose_Abb_7":
			dialog.text = "You are right in your reasoning, my son. Yours is a good and godly endeavor. But I still fail to grasp what exactly you expect of me.";
			link.l1 = "You have long dwelt in the Archipelago, Father. Perhaps you know someone with access to colonial archives concerning officers of the English Navy?";
			link.l1.go = "WildRose_Abb_8_stealth";
			link.l2 = "We need a man with access to the colonial archives where records of English naval officers are kept. Surely you know of such a one, Father.";
			link.l2.go = "WildRose_Abb_8_charisma";
		break;

		case "WildRose_Abb_8_stealth":
			AddCharacterExpToSkill(pchar, "Sneak", 100);
			dialog.text = "Do you understand what you are asking, my son? The point is not merely that such information may be a military secret...";
			link.l1 = "And what else then, Father? I shall speak plainly...";
			link.l1.go = "WildRose_Abb_9";
		break;

		case "WildRose_Abb_8_charisma":
			AddCharacterExpToSkill(pchar, "Leadership", 100);
			dialog.text = "Do you understand what you are asking, my son? The point is not merely that such information may be a military secret...";
			link.l1 = "And what else then, Father? I shall speak plainly...";
			link.l1.go = "WildRose_Abb_9";
		break;

		case "WildRose_Abb_9":
			dialog.text = "The problem lies with those very colonial archives. Twenty years ago Jamaica was under the Spaniards, and St. John’s and Bridgetown under constant threat of raids. It is unlikely any Royal Navy ships were stationed there...";
			link.l1 = "You mean the Admiralty archives in London, Father?";
			link.l1.go = "WildRose_Abb_10";
		break;

		case "WildRose_Abb_10":
			dialog.text = "Perhaps. The papers should have been sent to the Admiralty. To obtain them will not be easy.";
			link.l1 = "But it can be done, can it not, Father?";
			link.l1.go = "WildRose_Abb_11";
		break;

		case "WildRose_Abb_11":
			dialog.text = "Nothing is impossible, my son. But it will require effort... and payment.";
			link.l1 = "Of course, Father. Shall I give the money to you, or must I meet with someone else?";
			link.l1.go = "WildRose_Abb_12";
		break;

		case "WildRose_Abb_12":
			dialog.text = "I will meet someone else myself, my son. What I need from you is... eight hundred doubloons.";
			link.l1 = "Very well, Father. How long will it take?";
			link.l1.go = "WildRose_Abb_13";
		break;

		case "WildRose_Abb_13":
			dialog.text = "I reckon two months. And, by the way, you have not told me the name of the one you seek.";
			link.l1 = "That man’s name is Joshua Casper.";
			link.l1.go = "WildRose_Abb_14";
		break;

		case "WildRose_Abb_14":
			dialog.text = "I shall remember it. If you are ready to give me the full sum now — I will send word as soon as tomorrow.";
			if (PCharDublonsTotal() >= 800)
			{
				link.l1 = "Of course, Father. Here, take it. Eight hundred in gold.";
				link.l1.go = "WildRose_Abb_14_pay";
			}
			link.l2 = "No, Father, I do not have such money on me. But I shall return soon and bring it.";
			link.l2.go = "WildRose_Abb_14_nopay";
		break;

		case "WildRose_Abb_14_pay":
			RemoveDublonsFromPCharTotal(800);
			dialog.text = "Very well, "+pchar.name+". Return in two months – I am certain by then I shall have one answer or another for you.";
			link.l1 = "Thank you, Father. Until we meet again!";
			link.l1.go = "exit";
			NextDiag.TempNode = "First time";
			AddDialogExitQuestFunction("WildRose_Etap3_Paperwork_1");
			DeleteAttribute(pchar, "questTemp.WildRose_Etap3_Benua_2");
		break;

		case "WildRose_Abb_14_nopay":
			dialog.text = "As you say, my son.";
			link.l1 = "I will return soon.";
			link.l1.go = "exit";
			NextDiag.TempNode = "First time";
			pchar.questTemp.WildRose_Etap3_Benua_2 = true;
		break;
		
		case "WildRose_Abb_16":
			dialog.text = "He learned both of Joshua Casper and of his ship – which, however, was not the 'Wrangler'. No brig of that name ever belonged to the Royal Navy.";
			link.l1 = "Hm... I am absolutely certain the vessel Joshua Casper served on bore that name. And what of Joshua himself?";
			link.l1.go = "WildRose_Abb_17";
			DelLandQuestMark(npchar);
			DeleteAttribute(pchar, "questTemp.WildRose_Etap3_Benua_3");
		break;

		case "WildRose_Abb_17":
			dialog.text = "That man was a fine officer with many merits and awards – all recorded in his personal file. Though he did not belong to the true faith, he was a worthy captain. Mademoiselle may well be proud of such roots.";
			link.l1 = "That is good news, Father. But if you permit, let us return to the ship. If it was not the 'Wrangler', then what was its name?";
			link.l1.go = "WildRose_Abb_19";
			AddQuestRecordInfo("WildRose_Records_3", "1");
		break;

		case "WildRose_Abb_19":
			dialog.text = "'Cornwall'. He left Plymouth in January of 1638 with orders to deliver wages to the garrisons of Antigua and Providence.";
			link.l1 = "Incredible...";
			link.l1.go = "WildRose_Abb_20";
			AddQuestRecordInfo("WildRose_Records_4", "1");
		break;

		case "WildRose_Abb_20":
			dialog.text = "Whether the ship reached its final destination, I do not know. But it did put in at St. John’s. In the port office there remains a report by Captain Casper dated June 2 of that year.";
			link.l1 = "I knew you were not as simple as you try to appear, Father! This document, I presume, contains some important details?";
			link.l1.go = "WildRose_Abb_21_charisma";
			link.l2 = "We are forever in your debt, Father. Since you mentioned this document – it must contain something important, then?";
			link.l2.go = "WildRose_Abb_21_honor";
			AddQuestRecordInfo("WildRose_Records_5", "1");
		break;

		case "WildRose_Abb_21_charisma":
			AddCharacterExpToSkill(pchar, "Leadership", 100);
			dialog.text = "Only a report of a battle with the Spanish galleon 'Toro' near the Azores, in which a third of the crew perished – read the report, it tells all.";
			link.l1 = "One more question: since you had access to the records of Antigua’s port authority, did you by chance come across Joshua Casper’s name anywhere else?";
			link.l1.go = "WildRose_Abb_22";
		break;

		case "WildRose_Abb_21_honor":
			AddComplexSelfExpToScill(100, 100, 100, 100);
			dialog.text = "Only a report of a battle with the Spanish galleon 'Toro' near the Azores, in which a third of the crew perished – read the report, it tells all.";
			link.l1 = "One more question: since you had access to the records of Antigua’s port authority, did you by chance come across Joshua Casper’s name anywhere else?";
			link.l1.go = "WildRose_Abb_22";
		break;

		case "WildRose_Abb_22":
			dialog.text = "You ask much of me, my son. If you mean to suggest that he may have survived that shipwreck and later returned to the fleet – I very much doubt it.";
			link.l1 = "The Lord works in mysterious ways, Father.";
			link.l1.go = "WildRose_Abb_23";
		break;

		case "WildRose_Abb_23":
			dialog.text = "Indeed, my son. But you see, his personal file states that Joshua Casper was born in 1586...";
			link.l1 = "Perhaps you are right, Father.";
			link.l1.go = "WildRose_Abb_24_fortune";
			link.l2 = "You know, Father, in my years in the Caribbean I have seen such things that I could believe even the most unlikely of tales.";
			link.l2.go = "WildRose_Abb_24_charisma";
		break;

		case "WildRose_Abb_24_fortune":
			AddCharacterExpToSkill(pchar, "Fortune", 100);
			dialog.text = "Surely such an officer was worthy of dying in battle. But if one is to speak philosophically, in a sense that too was a battle...";
			link.l1 = "I am no philosopher, Father. But thank you for everything...";
			link.l1.go = "WildRose_Abb_25";
		break;

		case "WildRose_Abb_24_charisma":
			AddCharacterExpToSkill(pchar, "Leadership", 100);
			dialog.text = "Surely such an officer was worthy of dying in battle. But if one is to speak philosophically, in a sense that too was a battle...";
			link.l1 = "I am no philosopher, Father. But thank you for everything...";
			link.l1.go = "WildRose_Abb_25";
		break;

		case "WildRose_Abb_25":
			dialog.text = "The Lord leads you on this path, my children, and to aid you is my humble duty. But I fear there is nothing more I can do for you in this matter...";
			link.l1 = "I understand, Father. Well then, allow us to take our leave.";
			link.l1.go = "exit";
			NextDiag.TempNode = "First time";
			AddDialogExitQuestFunction("WildRose_Etap3_Paperwork_5");
		break;
		//<-- Дикая Роза
		
		case "LH_abbat_38":
			DialogExit();
			LAi_CharacterDisableDialog(npchar);
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}
