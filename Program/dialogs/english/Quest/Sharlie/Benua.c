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
			//--> Эпилог
			if (CheckAttribute(pchar, "questTemp.SharlieEpilog_Benua"))
			{
				dialog.text = "Hello, my child. I’m glad you came. I wanted to speak with you.";
				link.l1 = ""+TimeGreeting()+", Father. I'm listening.";
				link.l1.go = "SharlieEpilog_Benua_1";
				DelLandQuestMark(npchar);
				break;
			}
			if (CheckAttribute(pchar, "questTemp.SharlieEpilog_Benua_back"))
			{
				link.l99 = "I’d like to talk about my father.";
				link.l99.go = "SharlieEpilog_Benua_3";
			}
			//<-- Эпилог
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
			//--> Эпилог
			if (CheckAttribute(pchar, "questTemp.SharlieEpilog_Benua_DublonsLater"))
			{
				link.l1 = "Let's return to the matter of payment for delivering the orders.";
				link.l1.go = "SharlieEpilog_Benua_DublonsLater_2";
			}
			if (CheckAttribute(npchar, "SharlieEpilog_BenuaRazgovor_2"))
			{
				link.l1 = "I want to send an order...";
				link.l1.go = "SharlieEpilog_Benua_Delivery";
			}
			//<-- Эпилог
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
		
		//--> Эпилог
		case "SharlieEpilog_Benua_1":
			dialog.text = "I am deeply concerned about your father's condition. I don't know if he told you in his letter, but in his message to me, he admitted that his strength is failing him, and he fears he won't last much longer.";
			link.l1 = "He did mention that his illness wasn't subsiding... But it seems he kept his fears to himself.";
			link.l1.go = "SharlieEpilog_Benua_2";
			DeleteAttribute(pchar, "questTemp.SharlieEpilog_Benua");
		break;

		case "SharlieEpilog_Benua_2":
			dialog.text = "There is nothing more I can tell you – that is all he shared. But one thing is clear: he fears facing the Lord without seeing you again.";
			link.l1 = "He spoke of this. To be honest, I myself have thought about visiting him... But...";
			link.l1.go = "SharlieEpilog_Benua_3";
		break;

		case "SharlieEpilog_Benua_3":
			if (!CheckAttribute(npchar, "SharlieEpilog_BenuaRazgovor_1"))
			{
				dialog.text = "My son, only the Lord knows how much time is granted to each of us. Don't delay your visit: sometimes one embrace can give peace to a soul more than a thousand prayers ever could.";
				npchar.SharlieEpilog_BenuaRazgovor_1 = true;
			}
			else
			{
				dialog.text = ""+pchar.name+", I hope you won't postpone your visit any longer? Remember, time is not on your side...";
			}
			link.l1 = "You're right, Abbot. I'll begin preparations for the voyage immediately. Given my current status, it might take some time to get everything in order...";
			link.l1.go = "SharlieEpilog_Benua_5";
			link.l2 = "I understand your concern, holy father, and I promise to think about it. But right now I have urgent matters that cannot wait. Let's return to this conversation later.";
			link.l2.go = "SharlieEpilog_Benua_4_exit";
		break;
		
		case "SharlieEpilog_Benua_4_exit":
			DialogExit();
			AddDialogExitQuestFunction("SharlieEpilog_Benua_DlgExit_2");
		break;
		
		case "SharlieEpilog_Benua_5":
			dialog.text = "If you have debts, my son, I would recommend settling them first. Moneylenders are vengeful people: they can severely damage your reputation and the good name of your entire family, even in the Old World.\n"+
			"As for the rest — in the name of my friendship with your father and for the glory of the Lord — I will give you all the support I can. You may write your orders, and I will ensure they reach the right recipients on time. All you need to do is pay for the courier service. I believe two hundred doubloons should suffice for the delivery of all the letters.";
			if (PCharDublonsTotal() >= 200)
			{
				link.l1 = "Thank you, holy father. Your help is most timely. Here, take it.";
				link.l1.go = "SharlieEpilog_Benua_6";
			}
			link.l2 = "Thank you for your concern, holy father. Unfortunately, I do not have the necessary amount right now. Let’s return to this matter a bit later.";
			link.l2.go = "SharlieEpilog_Benua_DublonsLater";
			SharlieEpilog_Benua_Dlg_1();
		break;
		
		case "SharlieEpilog_Benua_DublonsLater":
			DialogExit();
			AddDialogExitQuestFunction("SharlieEpilog_Benua_DlgExit_3");
		break;
		
		case "SharlieEpilog_Benua_DublonsLater_2":
			dialog.text = "Of course, "+pchar.name+". I take it you've brought the two hundred doubloons?";
			if (PCharDublonsTotal() >= 200)
			{
				link.l1 = "Naturally. Here you go.";
				link.l1.go = "SharlieEpilog_Benua_6";
			}
			link.l2 = "Unfortunately, I still don’t have the amount needed.";
			link.l2.go = "exit";
		break;
		
		case "SharlieEpilog_Benua_6":
			dialog.text = "Excellent, my son.";
			link.l1 = "...";
			link.l1.go = "SharlieEpilog_Benua_Delivery";
			RemoveDublonsFromPCharTotal(200);
			DeleteAttribute(pchar, "questTemp.SharlieEpilog_Benua_DublonsLater");
		break;
		
		case "SharlieEpilog_Benua_Delivery":
			if (!CheckAttribute(npchar, "SharlieEpilog_BenuaRazgovor_2"))
			{
				dialog.text = "So, where would you prefer to begin?";
				npchar.SharlieEpilog_BenuaRazgovor_2 = true;
			}
			else
			{
				dialog.text = "Whom do you wish to notify, and about what?";
			}
			if (CheckAttribute(pchar, "questTemp.IslaMona.Plantation") && !CheckAttribute(pchar, "questTemp.SharlieEpilog_IslaMona"))
			{
				link.l1 = "Once, I discovered an island that isn’t marked on any maps. It was already home to a few settlers, and I took them under my protection. Now that I'm leaving, they’ll need a new 'governor'.";
				link.l1.go = "SharlieEpilog_Benua_IslaMona";
			}
			if (CheckAttribute(pchar, "questTemp.LongHappy.Baron") && !CheckAttribute(pchar, "questTemp.SharlieEpilog_Baron"))
			{
				link.l2 = "I want to send a letter to Marcus Tirax of La Vega. It’s not of great importance, but it must be delivered on time.";
				link.l2.go = "SharlieEpilog_Benua_Baron";
			}
			if (CheckCharacterItem(PChar, "patent_fra") && !CheckAttribute(pchar, "questTemp.SharlieEpilog_Patent"))
			{
				link.l3 = "I hold a valid French letter of marque – I’d like to notify the Capsterville office of my decision.";
				link.l3.go = "SharlieEpilog_Benua_Patent";
			}
			if (!CheckAttribute(pchar, "questTemp.SharlieEpilog_Money"))
			{
				link.l4 = "Holy father, during the years I've spent in these lands, I’ve managed to amass a considerable fortune. But before it becomes my family’s inheritance, I would like to purify it. To wash away any blood it might be tied to. I want to leave this land not as a brigand with loot, but as a man whose conscience and reputation are clean in the eyes of society.";
				link.l4.go = "SharlieEpilog_Benua_Money";
			}
			if (!CheckAttribute(pchar, "questTemp.SharlieEpilog_Svenson") && CheckAttribute(pchar, "questTemp.SharlieEpilog_IslaMona_France"))
			{
				link.l5 = "I’d like to inform Jan Svenson of Blueveld of my departure. It would be rude to leave the archipelago without telling him.";
				link.l5.go = "SharlieEpilog_Benua_Svenson";
			}
			if (!CheckAttribute(pchar, "questTemp.SharlieEpilog_Houk"))
			{
				link.l6 = "I want to notify the Houk family in Maroon Town of my journey.";
				link.l6.go = "SharlieEpilog_Benua_Houk";
			}
			if (!CheckAttribute(pchar, "questTemp.SharlieEpilog_Jino"))
			{
				link.l7 = "I want to inform Gino Guinelli of Saint John's about my departure for the Old World.";
				link.l7.go = "SharlieEpilog_Benua_Jino";
			}
			if (CheckAttribute(pchar, "questTemp.SharlieEpilog_gold_S") || CheckAttribute(pchar, "questTemp.SharlieEpilog_gold_M") || CheckAttribute(pchar, "questTemp.SharlieEpilog_gold_L"))
			{
				link.l85 = "That’s all, father... It seems I’m ready to depart.";
				link.l85.go = "SharlieEpilog_Benua_TimeToGoHome";
			}
			link.l99 = "Forgive me, holy father, I must be going.";
			link.l99.go = "SharlieEpilog_exit";
		break;
		
		case "SharlieEpilog_exit":
			DialogExit();
			LAi_SetStayType(npchar);
			NextDiag.CurrentNode = "First time";
		break;
		
		case "SharlieEpilog_Benua_Jino":
			dialog.text = "Of course, my son.";
			link.l1 = "...";
			link.l1.go = "SharlieEpilog_Benua_Jino_2";
			pchar.questTemp.SharlieEpilog_Jino = true;
		break;

		case "SharlieEpilog_Benua_Jino_2":
			DialogExit();
			AddDialogExitQuestFunction("SharlieEpilog_Benua_TimeLater_1");
			NextDiag.CurrentNode = "SharlieEpilog_Benua_Jino_3";
			AddQuestRecord("SharlieEpilog", "8_1");
		break;

		case "SharlieEpilog_Benua_Jino_3":
			dialog.text = "...";
			link.l1 = "Done. You may send it.";
			link.l1.go = "SharlieEpilog_Benua_Delivery";
		break;

		case "SharlieEpilog_Benua_Houk":
			dialog.text = "Of course, my son.";
			link.l1 = "...";
			link.l1.go = "SharlieEpilog_Benua_Houk_2";
			pchar.questTemp.SharlieEpilog_Houk = true;
		break;

		case "SharlieEpilog_Benua_Houk_2":
			DialogExit();
			AddDialogExitQuestFunction("SharlieEpilog_Benua_TimeLater_1");
			NextDiag.CurrentNode = "SharlieEpilog_Benua_Houk_3";
			AddQuestRecord("SharlieEpilog", "8");
		break;

		case "SharlieEpilog_Benua_Houk_3":
			dialog.text = "...";
			link.l1 = "Done. You may send it.";
			link.l1.go = "SharlieEpilog_Benua_Delivery";
		break;

		case "SharlieEpilog_Benua_Svenson":
			dialog.text = "Jan Svenson from Blueveld... I'll remember. Hand me the letter – it will set out today.";
			link.l1 = "...";
			link.l1.go = "SharlieEpilog_Benua_Svenson_2";
			pchar.questTemp.SharlieEpilog_Svenson = true;
		break;
		
		case "SharlieEpilog_Benua_Svenson_2":
			DialogExit();
			AddDialogExitQuestFunction("SharlieEpilog_Benua_TimeLater_1");
			NextDiag.CurrentNode = "SharlieEpilog_Benua_Svenson_3";
			AddQuestRecord("SharlieEpilog", "7");
		break;
		
		case "SharlieEpilog_Benua_Svenson_3":
			dialog.text = "...";
			link.l1 = "Jan’s house is easy to find. Just ask any local — there’s hardly anyone in Blueveld who doesn’t know who he is and where he lives.";
			link.l1.go = "SharlieEpilog_Benua_Svenson_4";
		break;

		case "SharlieEpilog_Benua_Svenson_4":
			dialog.text = "Don’t worry, my son. Our people are well-versed in their duties. The letter will be delivered properly and on time.";
			link.l1 = "...";
			link.l1.go = "SharlieEpilog_Benua_Delivery";
		break;

		case "SharlieEpilog_Benua_Money":
			dialog.text = "You wish for the Church to bless gold obtained through criminal means?";
			link.l1 = "Let’s say it was earned in the service of France and His Majesty.";
			link.l1.go = "SharlieEpilog_Benua_Money_2";
		break;

		case "SharlieEpilog_Benua_Money_2":
			dialog.text = "I understand, my son. I could say that the Church cannot purify money or undo how it was acquired. But would that help, if the hungry remain unfed, the homeless sleep in the streets, and the sick die without aid? I am willing to grant my blessing — in exchange for a small portion of the funds to go not to you, but to those in need.";
			link.l1 = "Of course, holy father. I'm ready to donate however much you say.";
			link.l1.go = "SharlieEpilog_Benua_Money_3";
		break;

		case "SharlieEpilog_Benua_Money_3":
			dialog.text = "So then, how much money do you intend to take with you?";
			link.l1 = "Ten million pesos.";
			link.l1.go = "SharlieEpilog_Benua_Money_4";
			if (sti(pchar.Money) >= 250000)
			{
				link.l2 = "Twenty-five million pesos.";
				link.l2.go = "SharlieEpilog_Benua_Money_5";
			}
			if (sti(pchar.Money) >= 500000)
			{
				link.l3 = "Fifty million pesos.";
				link.l3.go = "SharlieEpilog_Benua_Money_6";
			}
		break;

		case "SharlieEpilog_Benua_Money_4":
			dialog.text = "In that case, a donation of one hundred thousand pesos will suffice. With that amount, we can organize meals for the needy for many months. Are you ready to give this amount right now, my son?";
			link.l1 = "Of course. Here you go. I'm glad to help those truly in need, and I trust you will put this money to good use and honor.";
			link.l1.go = "SharlieEpilog_Benua_Money_4_1";
			link.l2 = "Forgive me, I need to think it over once more.";
			link.l2.go = "SharlieEpilog_Benua_Delivery";
		break;

		case "SharlieEpilog_Benua_Money_5":
			dialog.text = "Then your donation should amount to two hundred fifty thousand pesos. These funds will allow us to build an orphanage, which will bear your name and be sustained for some time. Are you ready to give this amount right now, my son?";
			link.l1 = "Of course. Here you go. I'm glad to help those truly in need, and I trust you will put this money to good use and honor.";
			link.l1.go = "SharlieEpilog_Benua_Money_5_1";
			link.l2 = "Forgive me, I need to think it over once more.";
			link.l2.go = "SharlieEpilog_Benua_Delivery";
		break;

		case "SharlieEpilog_Benua_Money_6":
			dialog.text = "Well, it seems you’ve made good use of your time, "+pchar.name+". I believe a donation of five hundred thousand pesos will be more than enough. With that contribution, we can build a hospital and equip it for many years to come. Are you ready to give this amount right now, my son?";
			link.l1 = "Of course. Here you go. I'm glad to help those truly in need, and I trust you will put this money to good use and honor.";
			link.l1.go = "SharlieEpilog_Benua_Money_6_1";
			link.l2 = "Forgive me, I need to think it over once more.";
			link.l2.go = "SharlieEpilog_Benua_Delivery";
		break;

		case "SharlieEpilog_Benua_Money_4_1":
			dialog.text = "Excellent, my son.";
			link.l1 = "...";
			link.l1.go = "SharlieEpilog_Benua_Delivery";
			AddMoneyToCharacter(pchar, -100000);
			AddQuestRecord("SharlieEpilog", "6");
			AddQuestUserData("SharlieEpilog", "sSum", "10000000");
			AddQuestUserData("SharlieEpilog", "tSum", "100000");
			pchar.questTemp.SharlieEpilog_gold_S = true;
			pchar.questTemp.SharlieEpilog_Money = true;
		break;
		
		case "SharlieEpilog_Benua_Money_5_1":
			dialog.text = "Excellent, my son.";
			link.l1 = "...";
			link.l1.go = "SharlieEpilog_Benua_Delivery";
			AddMoneyToCharacter(pchar, -250000);
			AddQuestRecord("SharlieEpilog", "6");
			AddQuestUserData("SharlieEpilog", "sSum", "25000000");
			AddQuestUserData("SharlieEpilog", "tSum", "250000");
			pchar.questTemp.SharlieEpilog_gold_M = true;
			pchar.questTemp.SharlieEpilog_Money = true;
		break;

		case "SharlieEpilog_Benua_Money_6_1":
			dialog.text = "Excellent, my son.";
			link.l1 = "...";
			link.l1.go = "SharlieEpilog_Benua_Delivery";
			AddMoneyToCharacter(pchar, -500000);
			AddQuestRecord("SharlieEpilog", "6");
			AddQuestUserData("SharlieEpilog", "sSum", "50000000");
			AddQuestUserData("SharlieEpilog", "tSum", "500000");
			pchar.questTemp.SharlieEpilog_gold_L = true;
			pchar.questTemp.SharlieEpilog_Money = true;
			Achievment_Set("ach_CL_205");
		break;

		case "SharlieEpilog_Benua_Patent":
			dialog.text = "And what shall it be, my son?";
			link.l1 = "Despite the long journey ahead, I would like to keep the patent — and my loyalty to France and the King.";
			link.l1.go = "SharlieEpilog_Benua_Patent_2";
			link.l2 = "I’ve decided to give up the patent. A long road awaits me, and I don’t know when I’ll return. It seems wiser not to carry the burden of duties and rules I may no longer be able to follow.";
			link.l2.go = "SharlieEpilog_Benua_Patent_6";
			pchar.questTemp.SharlieEpilog_Patent = true;
		break;

		case "SharlieEpilog_Benua_Patent_2":
			dialog.text = "I’m glad you came to this decision, my son. Now more than ever, our nation needs strong and courageous knights. But tell me, "+pchar.name+", haven’t you considered settling down, finding a home, and no longer risking your life every hour? A man is not meant to be tested by fire for eternity.";
			link.l1 = "I’m not sure I can simply sit idle, holy father. But as the Scriptures say: 'Even the Lord’s warriors are granted rest once their labor is done.' I may be far from the end of my journey, but I hope to choose the day when I sheath my sword for good.";
			link.l1.go = "SharlieEpilog_Benua_Patent_3";
		break;

		case "SharlieEpilog_Benua_Patent_3":
			DialogExit();
			AddDialogExitQuestFunction("SharlieEpilog_Benua_TimeLater_1");
			NextDiag.CurrentNode = "SharlieEpilog_Benua_Patent_4";
			AddQuestRecord("SharlieEpilog", "5_2");
		break;

		case "SharlieEpilog_Benua_Patent_4":
			dialog.text = "Excellent, my son. I believe His Majesty will not overlook your loyalty and devotion.";
			link.l1 = "Right now, my thoughts are elsewhere... I hope my father won’t insist I stay in our estate. I don’t think I’m ready for that. But luckily, I’ll have plenty of time to consider it.";
			link.l1.go = "SharlieEpilog_Benua_Patent_5";
		break;

		case "SharlieEpilog_Benua_Patent_5":
			dialog.text = "...";
			link.l1 = "Well then, let’s return to more worldly matters.";
			link.l1.go = "SharlieEpilog_Benua_Delivery";
		break;

		case "SharlieEpilog_Benua_Patent_6":
			dialog.text = "That’s a reasonable decision. However, I must say — your departure will greatly weaken France’s strength in these waters.";
			link.l1 = "I’m sure His Majesty has plenty of capable captains to maintain France’s glory.";
			link.l1.go = "SharlieEpilog_Benua_Patent_7";
		break;

		case "SharlieEpilog_Benua_Patent_7":
			DialogExit();
			AddDialogExitQuestFunction("SharlieEpilog_Benua_TimeLater_1");
			NextDiag.CurrentNode = "SharlieEpilog_Benua_Patent_8";
			AddQuestRecord("SharlieEpilog", "5_1");
		break;

		case "SharlieEpilog_Benua_Patent_8":
			dialog.text = "...";
			link.l1 = "That’s it, then. Like a weight lifted off my shoulders. Honestly, I’d forgotten who I even was when I arrived in the Caribbean... So much has happened.";
			link.l1.go = "SharlieEpilog_Benua_Patent_9";
		break;

		case "SharlieEpilog_Benua_Patent_9":
			dialog.text = "Perhaps you've heard it before, my son: the Lord works in mysterious ways. All that was destined for you, you have faced with honor. But I believe your trials are not over yet, and perhaps your glory is still rising toward its peak.";
			link.l1 = "Glory is a burden, holy father. Not everyone who seeks it can bear its weight... or knows when to stop.";
			link.l1.go = "SharlieEpilog_Benua_Patent_10";
		break;

		case "SharlieEpilog_Benua_Patent_10":
			dialog.text = "...";
			link.l1 = "Well then, let’s return to more worldly matters.";
			link.l1.go = "SharlieEpilog_Benua_Delivery";
		break;

		case "SharlieEpilog_Benua_Baron":
			dialog.text = "My son, do you have business with the head of the pirates?";
			link.l1 = "Are you familiar with the Keeper of the Code?";
			link.l1.go = "SharlieEpilog_Benua_Baron_2";
			pchar.questTemp.SharlieEpilog_Baron = true;
		break;

		case "SharlieEpilog_Benua_Baron_2":
			dialog.text = "The Keeper of the Code? No, I don’t know him. I know Marcus Tirax — an executioner with so much blood on his hands, even centuries of prayer would not be enough to earn the Lord’s forgiveness. And yet... are you truly dealing with him?";
			link.l1 = "I had to win his favor... to get Michel out of prison. But I now see it was a mistake, and I have no intention of continuing that connection. With this letter, I intend to sever the last tie that binds us.";
			link.l1.go = "SharlieEpilog_Benua_Baron_3";
			link.l2 = "It doesn’t matter now. I’m leaving the archipelago, and our paths will part on their own, holy father.";
			link.l2.go = "SharlieEpilog_Benua_Baron_7";
		break;
		
		case "SharlieEpilog_Benua_Baron_3":
			dialog.text = "And what tie is that, my son? I hope it is not stained with the blood of the innocent?";
			link.l1 = "I was formally considered the head of the pirate settlement of Le Francois. In truth, someone else held the reins. Today, I renounce the title of pirate baron—once and for all.";
			link.l1.go = "SharlieEpilog_Benua_Baron_4";
		break;

		case "SharlieEpilog_Benua_Baron_4":
			dialog.text = "I’m glad you've chosen the righteous path, my son, and I shall pray for the salvation of your soul. Anyone can stumble, but the Lord forgives only those whose repentance is sincere.";
			link.l1 = "...";
			link.l1.go = "SharlieEpilog_Benua_Baron_5";
		break;

		case "SharlieEpilog_Benua_Baron_5":
			DialogExit();
			AddDialogExitQuestFunction("SharlieEpilog_Benua_TimeLater_1");
			NextDiag.CurrentNode = "SharlieEpilog_Benua_Baron_6";
			AddQuestRecord("SharlieEpilog", "4_1");
		break;

		case "SharlieEpilog_Benua_Baron_6":
			dialog.text = "Excellent, "+pchar.name+". Hand me the letter—I’ll make sure it reaches its destination. And don’t forget to pray, my son. Only repentance and prayer can cleanse even the gravest sins from the soul.";
			link.l1 = "Thank you, holy father. Perhaps not all is lost for me yet.";
			link.l1.go = "SharlieEpilog_Benua_Delivery";
		break;

		case "SharlieEpilog_Benua_Baron_7":
			dialog.text = "No matter how great the sin, my son, the doors of forgiveness are always open. Repentance, prayer, and good deeds cleanse the soul as rain washes dust from stone.";
			link.l1 = "All in due time, holy father. For now, I must attend to worldly matters.";
			link.l1.go = "SharlieEpilog_Benua_Baron_8";
		break;

		case "SharlieEpilog_Benua_Baron_8":
			DialogExit();
			AddDialogExitQuestFunction("SharlieEpilog_Benua_TimeLater_1");
			NextDiag.CurrentNode = "SharlieEpilog_Benua_Baron_9";
			AddQuestRecord("SharlieEpilog", "4_2");
		break;

		case "SharlieEpilog_Benua_Baron_9":
			dialog.text = "...";
			link.l1 = "Here you go.";
			link.l1.go = "SharlieEpilog_Benua_Delivery";
		break;

		case "SharlieEpilog_Benua_IslaMona":
			dialog.text = "It is good, my son, that you decided to care for those people and haven’t forgotten them. To whom do you wish to entrust the island?";
			link.l1 = "I believe it should be placed under the French flag. Sooner or later, the island will be discovered, and other nations might try to seize it. I can't allow that.";
			link.l1.go = "SharlieEpilog_Benua_IslaMona_France";
			link.l2 = "That island and its inhabitants deserve to live freely, not under the shadow of royal authority. I intend to send a letter to my friend, Jan Svenson from Blueveld. I trust he will agree to watch over that land. But please, holy father, keep this conversation secret—for their safety and well-being.";
			link.l2.go = "SharlieEpilog_Benua_IslaMona_Pirate";
			pchar.questTemp.SharlieEpilog_IslaMona = true;
		break;

		case "SharlieEpilog_Benua_IslaMona_France":
			dialog.text = "You are wise to do so, "+pchar.name+". Under the protection of the King, the island will find order and safety.";
			link.l1 = "I’ll send an appropriate letter to the Capsterville chancery and to the people on the island. I’ll write the coordinates on the envelope.";
			link.l1.go = "SharlieEpilog_Benua_IslaMona_France_2";
		break;
		
		case "SharlieEpilog_Benua_IslaMona_France_2":
			DialogExit();
			AddDialogExitQuestFunction("SharlieEpilog_Benua_TimeLater_1");
			NextDiag.CurrentNode = "SharlieEpilog_Benua_IslaMona_France_3";
			pchar.questTemp.SharlieEpilog_IslaMona_France = true;
			AddQuestRecord("SharlieEpilog", "3_1");
		break;
		
		case "SharlieEpilog_Benua_IslaMona_France_3":
			dialog.text = "...";
			link.l1 = "Here you go. I hope your people can locate the island before His Majesty’s fleet arrives.";
			link.l1.go = "SharlieEpilog_Benua_IslaMona_France_4";
		break;

		case "SharlieEpilog_Benua_IslaMona_France_4":
			dialog.text = "Do not worry, my son. I will entrust the delivery of these letters to our finest couriers.";
			link.l1 = "...";
			link.l1.go = "SharlieEpilog_Benua_Delivery";
		break;

		case "SharlieEpilog_Benua_IslaMona_Pirate":
			dialog.text = "It is not for me to judge whether your path is righteous, my son. Sooner or later someone will discover that island, and one of the nations will seek to claim it. It’s only a matter of time. But if this is your decision, then it must be God’s will. Do not worry—I will not endanger those people and will offer a prayer for them.";
			link.l1 = "...";
			link.l1.go = "SharlieEpilog_Benua_IslaMona_Pirate_2";
		break;

		case "SharlieEpilog_Benua_IslaMona_Pirate_2":
			DialogExit();
			AddDialogExitQuestFunction("SharlieEpilog_Benua_TimeLater_1");
			NextDiag.CurrentNode = "SharlieEpilog_Benua_IslaMona_Pirate_3";
			pchar.questTemp.SharlieEpilog_IslaMona_Pirate = true;
			AddQuestRecord("SharlieEpilog", "3_2");
		break;

		case "SharlieEpilog_Benua_IslaMona_Pirate_3":
			dialog.text = "Jan Svenson of Blueveld, correct?";
			link.l1 = "Exactly, holy father. And the second letter should go directly to the island. The coordinates are written on the envelope.";
			link.l1.go = "SharlieEpilog_Benua_Delivery";
		break;

		case "SharlieEpilog_Benua_TimeToGoHome":
			dialog.text = "Excellent, my son. If I’m not mistaken, you arrived here on the pinnace '"+GetShipName("Ulysse")+"'?";
			link.l1 = "That's right. But why do you ask?";
			link.l1.go = "SharlieEpilog_Benua_TimeToGoHome_2";
		break;

		case "SharlieEpilog_Benua_TimeToGoHome_2":
			dialog.text = "Because that ship was recently put up for auction. And you, Charles, have the chance to return home on the same vessel—only this time, as its captain.";
			link.l1 = "Hmm... I must admit, it's a tempting offer. Perhaps I should pay a visit to the port authority. Thank you, holy father.";
			link.l1.go = "SharlieEpilog_Benua_TimeToGoHome_3";
		break;
		
		case "SharlieEpilog_Benua_TimeToGoHome_3":
			DialogExit();
			NextDiag.CurrentNode = "First Time";
			AddDialogExitQuestFunction("SharlieEpilog_PU_Ulysse_1");
		break;
		//<-- Эпилог
		
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
