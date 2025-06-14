// аббат Бенуа
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	int rate;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			if (CheckAttribute(pchar, "questTemp.Sharlie.BenuaLoan.Late")) // Addon 2016-1 Jason пиратская линейка 1
			{
				dialog.text = "It`s good to see you, my son.  Are you here to erase your debt?";
				if (PCharDublonsTotal() >= 100 && sti(pchar.money) >= 50000)
				{
					link.l1 = "Yes, father. I am.";
					link.l1.go = "FastStart_7";
				}
				else
				{
					link.l1 = "I am sorry for the delay, but I am not here for that. But I will be soon, don`t you worry.";
					link.l1.go = "exit";
				}
				break;
			}
			if (CheckAttribute(pchar, "questTemp.Sharlie") && pchar.questTemp.Sharlie == "benua_final")
			{
				dialog.text = "Is there anything you need, my son?";
				link.l1 = "Yes, father. I would like to see my brother, Michel de Monper. He said...";
				link.l1.go = "escape";
				break;
			}
			dialog.text = "Is there something you need, my son?";
			if (CheckAttribute(pchar, "questTemp.Sharlie.FastStart") && !CheckAttribute(npchar, "quest.FastStart") && !CheckAttribute(npchar, "quest.meet")) // ещё не виделись
			{
				link.l1 = "Yes, pater. I need your help. My name is "+GetFullName(pchar)+". Michel de Monper advised me to talk to you.";
				link.l1.go = "FastStart";
			}
			if (CheckAttribute(npchar, "quest.help") && !CheckAttribute(npchar, "quest.meet")) // ещё не виделись
			{
				link.l1 = "Yes, father. I need your help. My name is "+GetFullName(pchar)+". I was advised to talk to you by my brother, Michel de Monper.";
				link.l1.go = "meet";
			}
			if (CheckAttribute(pchar, "questTemp.Sharlie.FastStart") && !CheckAttribute(npchar, "quest.FastStart") && CheckAttribute(npchar, "quest.meet"))
			{
				link.l1 = "Yes, pater. I need a ship to help Michel, yet I have just recently arrived to the Caribbean and my wallet is empty. My brother told me you could lend me some money...";
				link.l1.go = "FastStart_2";
			}
			if (CheckAttribute(npchar, "quest.help") && CheckAttribute(npchar, "quest.meet"))
			{
				link.l1 = "Yes, father. I need your help.";
				if (CheckAttribute(npchar, "quest.relation_info")) link.l1.go = "help";
				else link.l1.go = "help_start";
			}
			if (CheckAttribute(pchar, "questTemp.Sharlie.BenuaLoan") && PCharDublonsTotal() >= 100 && sti(pchar.money) >= 50000)
			{
				link.l2 = "Yes, pater. I am.";
				link.l2.go = "FastStart_7";
			}
			link.l9 = "No, nothing, father.";
			link.l9.go = "exit";			
			NextDiag.TempNode = "First time";
		break;
		
		case "Benua_meeting":
			DelLandQuestMark(npchar);
			if(CheckAttribute(pchar, "questTemp.Sharlie.Citcount"))
				DeleteAttribute(pchar, "questTemp.Sharlie.Citcount");
			DelLandQuestMark(characterFromId("FortFrance_Mayor"));
			dialog.text = "What brings you to me, my son?";
			link.l1 = "Hello, father. I was advised to talk to you. My name is Charles de Maure. I am searching for Michel de Monper. As far as I know, he should be somewhere on Martinique. I'm... his brother.";
			link.l1.go = "Benua_meeting_1";			
		break;
		
		case "Benua_meeting_1":
			dialog.text = "Michel de Monper's brother? De Maure? How strange...";
			link.l1 = "I understand your doubts, father. We simply have different surnames. My father is Henri de Monper.";
			link.l1.go = "Benua_meeting_2";			
		break;
		
		case "Benua_meeting_2":
			dialog.text = "A-ah, I see now. I used to know Henri de Monper personally. Turn yourself into the light, young man. Right! You look just like him. The same looks, the same noble features! I am glad to see a son of Henri de Monper in our parish.\nAnd concerning your question I will tell you that Michel is a high ranking officer of the Order of Malta, but he is... in trouble. Fortunately, one of the knights of the Order is currently visiting me. I believe he might agree to accompany you to your unfortunate brother, may the Lord have mercy on his fate...";
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
			dialog.text = "Hello, my son. As promised, the person I mentioned yesterday is already here waiting for you. He's ready to bring you to your brother, who, as I have heard, is miserable. May the Lord have mercy on his soul...";
			link.l1 = "Who is this man, holy father?";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Sharlie_enterMaltie");
			NextDiag.TempNode = "First time";
			npchar.quest.meet = true;
		break; */
		
		case "escape":
			dialog.text = "Yes, Charles, I'm aware of that. But I must disappoint you. Michel is not here.";
			link.l1 = "What do you mean he's not here? He said that he would be waiting for me in your church! Father, what happened? Where's my brother?!";
			link.l1.go = "escape_1";
		break;
		
		case "escape_1":
			dialog.text = "My son, your brother was here and he left my modest tabernacle late last night. Where he went, I don't know. But he has left this letter for you.";
			link.l1 = "I can't believe it... after all I did for him! Give me that letter!";
			link.l1.go = "escape_2";
		break;
		
		case "escape_2":
			dialog.text = "Don't get so enraged, Charles. Here's the letter. Read it and then... then I would like to speak with you. But first, read your brother's message.";
			link.l1 = "I'm burning of impatience!";
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
			dialog.text = "Your brother's actions surprised me as well, Charles. I still feel moments of perplexity. A loyal servant of the Order and the Trinity and he's behaving like a deserter.";
			link.l1 = "Have you got any idea what the reasons for such strange behaviour could be?";
			link.l1.go = "escape_6";
		break;
		
		case "escape_6":
			dialog.text = "Alas, I don't. But I suppose that he has motives of his own, deep motives. Abrogating one's entire past would suggest an extremely significant reason. I can't even imagine what it could be. But I feel, that it involves something extremely bad... even awful.";
			link.l1 = "What could it be, father?";
			link.l1.go = "escape_7";
		break;
		
		case "escape_7":
			dialog.text = "My son, a priest sees not with his eyes, but with his heart. I cannot explain it to you in words, but... you brother has set forth to do something unclean, dirty. I never thought my mouth could utter this. However...";
			link.l1 = "Well, I don't doubt that my brother has planned something dirty. I can even get behind what exactly he's planning to do. This 'something' involves something yellow and makes a nice clink sound.";
			link.l1.go = "escape_8";
		break;
		
		case "escape_8":
			dialog.text = "I don't think the lust for gold is what drives your brother. I would say that he needs something greater.";
			link.l1 = "I have learned a lot from Michel and have grasped his philosophy, so I think I'm able to assume what's important to him and what isn't. But I will keep your valued words in mind, father.";
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
			pchar.questTemp.Sharlie = "escape";
			CloseQuestHeader("Sharlie");
			AddQuestRecord("Guardoftruth", "1");
			pchar.questTemp.Guardoftruth = "begin";
			DeleteAttribute(pchar, "questTemp.GoldenGirl_Block");	// Разрешаем квест Дороже Золота
			// ставим пленного испанца
			sld = GetCharacter(NPC_GenerateCharacter("spa_baseprisoner", "q_spa_off_1", "man", "man", 30, SPAIN, -1, true, "quest"));
			FantomMakeCoolFighter(sld, 30, 80, 80, "blade_13", "pistol1", "bullet", 150);
			sld.dialog.FileName = "Quest\Sharlie\Guardoftruth.c";
			sld.dialog.currentnode = "spa_prisoner";
			RemoveAllCharacterItems(sld, true);
			LAi_SetStayType(sld);
			LAi_SetImmortal(sld, true);
			ChangeCharacterAddressGroup(sld, "Fortfrance_dungeon", "quest", "quest1");
			LAi_CharacterDisableDialog(sld);//запрет диалога
		break;
		
		// уменьшение награды за голову
		case "meet":
			dialog.text = "Michel de Monper's brother? De Maure? How strange...";
			link.l1 = "I understand your doubts, father. We simply have different surnames. My father is Henri de Monper.";
			link.l1.go = "meet_1";			
		break;
		
		case "meet_1":
			dialog.text = "A-ah, I see now. I knew Henri de Monper personally. Turn yourself into the light, young man... Right! You look like him. Same looks, same noble side view! I am glad to see a son of Henri de Monper in our parish.\nI have already heard that Michel was visited by some man, who arrived from Europe, but I couldn't even imagine that it was his own brother. I hope that you will be able to help Michel, he is experiencing a difficult time. Anyway, how can I be of service?";
			link.l1 = "Michel told me that you would be able to help if I ever got into troubles with the authorities.";
			link.l1.go = "help_info";	
			npchar.quest.meet = true;
		break;
		
		case "help_info":
			dialog.text = "That is what Michel told you? I see. Well, I can be of help in such matters. I have some influence within the Holy Roman Church and Dutch colonies. Therefore I might be able to intercede between you and the Spanish as well as Dutch authorities. Surely, I won't be able to do much if your misconduct has become too much - in that case only a small extenuation can be achieved.\nIt will require several intercessions for complete reconciliation. Besides, in any case you will have to supply me with golden doubloons for charities and voyage spendings. Also, I can only help you with one nation at the time. If you find these terms acceptable, don't hesitate to turn to me, and we will see what can be done.";
			link.l1 = "Thank you! I'll keep that in mind.";
			link.l1.go = "exit";
			npchar.quest.relation_info = "true";
		break;
		
		case "help_start":
			dialog.text = "What can I do for you, my son? Speak, I am listening.";
			link.l1 = "Michel told me that you would be able to help if I ever get into troubles with the authorities.";
			link.l1.go = "help_info";
		break;
		
		case "help":
			dialog.text = "How can I help you, my son?";
			if (ChangeCharacterNationReputation(pchar, SPAIN, 0) < 0 && !CheckAttribute(npchar, "quest.relation"))
			{
				link.l1 = "I've got into troubles with the Spanish authorities.";
				link.l1.go = "relation_spa";
			}
			if (ChangeCharacterNationReputation(pchar, HOLLAND, 0) < 0 && !CheckAttribute(npchar, "quest.relation"))
			{
				link.l2 = "I've got into troubles with the Dutch authorities.";
				link.l2.go = "relation_hol";
			}
			link.l9 = "Sorry, I think I'll handle things myself this time.";
			link.l9.go = "exit";
		break;
		
		case "relation_spa": // patch-10
			pchar.GenQuest.BenuaNation = SPAIN;
			dialog.text = "So, the noble senors are eager to put you inside Havana's dungeons...";
			link.l1 = "Exactly so, father...";
			link.l1.go = "relation";
		break;
		
		case "relation_hol":
			pchar.GenQuest.BenuaNation = HOLLAND;
			dialog.text = "So, the smart merchants are eager to put you inside Willemstad's dungeons...";
			link.l1 = "Exactly so, father...";
			link.l1.go = "relation";
		break;
		
		case "relation":
			rate = abs(ChangeCharacterNationReputation(pchar, sti(pchar.GenQuest.BenuaNation), 0));
			if (rate <= 10)
			{
				dialog.text = "Yes, those rumours have reached our church as well. I can help you with your dilemma. It's something that can be solved. I need two hundred fifty gold doubloons to smooth out your predicament.";
				if (PCharDublonsTotal() >= 250) // Sinistra legendary edition
				{
					link.l1 = "Great! Here's the gold.";
					link.l1.go = "agree";
					iTotalTemp = 250;
				}
				link.l2 = "Then it's the right time for me to find the doubloons.";
				link.l2.go = "exit";
			}
			else
			{
				if (rate <= 20)
				{
					dialog.text = "Yes, rumours of your 'feats' have reached our church too. You've tarnished your reputation, my son. You should be more prudent. But I can help you. I need five hundred gold doubloons to smooth out your predicament.";
					if (PCharDublonsTotal() >= 500) // Sinistra legendary edition
					{
						link.l1 = "Great! Here's the gold.";
						link.l1.go = "agree";
						iTotalTemp = 500;
					}
					link.l2 = "Then it's the right time for me to find the doubloons.";
					link.l2.go = "exit";
				}
				else
				{
					dialog.text = "Yes, my son. You're just as desperate as your brother... This is probably a family trait. I can't completely correct the situation, but nevertheless, I believe I can dampen your dismal predicament. And later we can make more offerings if you wish. I need six hundred gold doubloons for now and I will begin solving your dilemma right away.";
					if (PCharDublonsTotal() >= 600) // Sinistra legendary edition
					{
						link.l1 = "Great! Here's the gold.";
						link.l1.go = "agree";
						iTotalTemp = 600;
					}
					link.l2 = "Then it's the right time for me to find the doubloons.";
					link.l2.go = "exit";
				}
			}
		break;
		
		case "agree":
			RemoveDublonsFromPCharTotal(iTotalTemp); // Sinistra legendary edition
			Log_Info("You've given "+iTotalTemp+" doubloons");
			PlaySound("interface\important_item.wav");
			dialog.text = "Now you will have to wait at least two weeks. I think that within this time I will be able to meet and talk with the right people.";
			link.l1 = "Thank you, father! I will be waiting...";
			link.l1.go = "agree_1";
		break;
		
		case "agree_1":
			DialogExit();
            rate = 10 + rand(5);
            rate = GetIntByCondition(HasShipTrait(pchar, "trait23"), rate, rate / 2);
			SetFunctionTimerCondition("ChangeNationRelationFromBenuaComplete", 0, 0, rate, false);
			pchar.GenQuest.BenuaNation.Rate = abs(ChangeCharacterNationReputation(pchar, sti(pchar.GenQuest.BenuaNation), 0));
			npchar.quest.relation = "true";
		break;
		
		// Addon 2016-1 Jason пиратская линейка 1
		case "FastStart":
			dialog.text = "De Maure? And you are a brother of Michel de Monper? Odd...";
			link.l1 = "I understand your doubts, padre. My father is Henri de Monper.";
			link.l1.go = "FastStart_1";			
		break;
		
		case "FastStart_1":
			dialog.text = "A-ah, I see. I knew Henri de Monper personally. Turn into the light, young man. Right! Same eyes, same noble features! I am pleased to see a son of Henri de Monper in my church. I hope you will be able to help your brother out. He had a lot of bad luck recently.";
			link.l1 = "Yes, pater. I need a ship to help Michel, yet I have just recently arrived to the Caribbean and my wallet is empty. My brother told me you could lend me some money...";
			link.l1.go = "FastStart_2";	
			npchar.quest.meet = true;
		break;
		
		case "FastStart_2":
			DelLandQuestMark(npchar);
			dialog.text = "Michel told you so?";
			link.l1 = "Padre, I may not sound very trustworthy, yet it's true. The sooner I get a ship, the sooner I will be able to get my brother out of jail.";
			link.l1.go = "FastStart_3";
		break;
		
		case "FastStart_3":
			dialog.text = "I see, my son. I can hear you are speaking the truth. Well, for the sake of Michel and your father I will help you out. I have some savings, take them. I assume 50 000 pesos and 100 doubloons will suffice.";
			link.l1 = "Thank you, padre. What are the terms?";
			link.l1.go = "FastStart_4";
		break;
		
		case "FastStart_4":
			AddMoneyToCharacter(pchar, 50000);
			TakeNItems(pchar, "gold_dublon", 100);
			dialog.text = "No pressure. Half a year for repayment will be enough.";
			link.l1 = "Very good, holy father. Thank you again!";
			link.l1.go = "FastStart_5";
		break;
		
		case "FastStart_5":
			dialog.text = "Go with my blessings, my son.";
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
			dialog.text = "Splendid, my son. Hope that money did you some good.";
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
			link.l1 = "Bless me, Holy Father, because I come bearing good news - I am getting married, and I would like to see you as the priest of my wedding.";
			link.l1.go = "LH_abbat_1";
		break;
		
		case "LH_abbat_1":
			dialog.text = "My son, this is wonderful! So you received that letter from your father and decided, as usually, to act according to your own understanding? I am sincerely happy for you! But I'm afraid I can't help you unless you decide to get married in this here church.";
			link.l1 = "I understand that your mission is at an impasse, Holy Father? Can I help you with anything? Since the marriage will take place in a Spanish chapel, of course, it is an adventure I would like to undertake, but I am determined to hold the celebration in Martinique. Moderately magnificent, and in the presence of reputable witnesses and honorable guests.";
			link.l1.go = "LH_abbat_2";
		break;
		
		case "LH_abbat_2":
			dialog.text = "I'm sorry, my son, but all your authority is worth nothing against the stubbornness of the highest hierarchs of the Catholic Church, especially in the Spanish colonies. We didn't agree on the question of sharing the influence of the Catholic missions between our countries, and now I'm here, as an honored guest and an honored hostage. The Spaniards are waiting for a better offer from our side. I sent a message to Europe, hopefully the answer will come in two months' time and we will be able to resume the negotiations. If it's not yet here in two months, it will definitely be here in the next six months.\nAnd yes, while the Pope and Mazarin have come to a compromise in the last couple of weeks, it's too early to talk about a real heartwarming relationship. Honestly, I'm not sure that we will ever come to any agreement. It seems to me that Palotti simply keeps me as an argument in his own political power plays. However, I have to say, the inquisitor has got excellent coffee!";
			link.l1 = "I don't have neither six months nor two months! I must fulfill the wish of my father, or he will be forcing me to marry me without my agreement. And his health isn't as good as it used to be, yet I would like to have time to introduce him to my chosen one and the future lady of Monper.";
			link.l1.go = "LH_abbat_3";
		break;
		
		case "LH_abbat_3":
			dialog.text = "I'm afraid you will have to find another priest for your wedding then, my son. Alas, I will stay here for a long time.";
			link.l1 = "What would you say if I part you from the inquisitor's coffee?";
			link.l1.go = "LH_abbat_4";
		break;
		
		case "LH_abbat_4":
			dialog.text = "I would gladly accept your help. I suspect that I wasn't chosen for this mission by chance. In the worst case, they'll just forget about father Benoit. And, although the Lord commanded me to endure, I am burdened with my conclusion, despite all its... blessings. But, I repeat - It's unlikely that father Palotti will listen to your requests.";
			link.l1 = "Then I'm going to save myself some time and I will not try to convince him. We will just leave the church as soon as the service has finished and go over to my ship. Don't hesitate, Holy Father - they saw our meeting and they will recognize me, and it will be much more difficult to help you if I have to get you out of the governor's mansion.";
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
			dialog.text = "My son, I didn't have time to thank you for my release. Apparently, the Spanish bishop and Inquisitior Palotti wanted to disrupt the barely established relations between our cardinal and the Holy See, so you acted completely within the interests of our country. Again. But no one will tell you 'thank you', except me.";
			link.l1 = "Common thing, Holy Father. Glad I managed to help. But, I also have to ask you something, remember?";
			link.l1.go = "LH_abbat_9";
		break;
		
		case "LH_abbat_9":
			dialog.text = "Of course! So let's get to the pleasant business - Charles, how are the preparations for your most important day going?";
			link.l1 = "It's slowly taking shape. I know military campaigns that were prepared easier and faster, but it's worth it!";
			link.l1.go = "LH_abbat_10";
		break;
		
		case "LH_abbat_10":
			dialog.text = "Sure, my son! And, on this occasion, I want to clarify something - how do you see your wedding ceremony?";
			link.l1 = "You mean, how pompous?";
			link.l1.go = "LH_abbat_11";
		break;
		
		case "LH_abbat_11":
			dialog.text = "Of course! Because I must prepare the church, and perhaps, you will want to invite some important people.";
			link.l1 = "Nothing special, Holy Father. Those, whom I consider our friends, will be waiting for us elsewhere. There will only be a few officials, my guys, and some ordinary onlookers present here.";
			link.l1.go = "LH_abbat_12";
		break;
		
		case "LH_abbat_12":
			dialog.text = "Well, then, I think we will manage with a small donation.";
			link.l1 = "That doesn't sound too scary. And how much is such a donation in gold?";
			link.l1.go = "LH_abbat_13";
		break;
		
		case "LH_abbat_13":
			dialog.text = "For the choir, solemn service, and other expenses - one hundred and fifty, not more. Plus, the usual donation from the newlyweds, in total - two hundred doubloons.";
			if (PCharDublonsTotal() >= 200) // Sinistra legendary edition
			{
				link.l1 = "Here you go, Holy Father.";
				link.l1.go = "LH_abbat_15";
			}
			else
			{
				link.l1 = "About those military campaigns... I will have to take a walk to the bank and return.";
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
			dialog.text = "There is still a question that needs to be answered - who will be giving away the bride and testify to the marriage on her part?";
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer"))
			{
				pchar.questTemp.LongHappy.Pater1 = "Svenson";
				link.l1 = "Jan Svensson , from Blueweld. He is an Englishman, but a respected person and attached to Helen as if she was his own daughter, and her adoptive mother is Gladys McArthur.";
			}
			else
			{
				if (CheckAttribute(pchar, "questTemp.Patria.GenGovernor"))
				{
					pchar.questTemp.LongHappy.Pater1 = "Noel";
					link.l1 = "Baron Noel Forget, I'm sure he will do me the honor.";
				}
				else
				{
					pchar.questTemp.LongHappy.Pater1 = "Puancie";
					link.l1 = "Chevalier Philippe de Poincy, I'm sure he will do me the honor.";
				}
			}
			link.l1.go = "LH_abbat_16";
		break;
		
		case "LH_abbat_16":
			dialog.text = "Well, and who will testify for the groom? Remember, this must be a man of noble birth and a worthy reputation.";
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer"))
			{
				if (CheckAttribute(pchar, "questTemp.Patria.GenGovernor"))
				{
					link.l1 = "Baron Noel Forget, I'm sure he will do me the honor.";
					link.l1.go = "LH_abbat_17_1";
				}
				else
				{
					link.l1 = "Chevalier Philippe de Poincy, I'm sure he will do me the honor.";
					link.l1.go = "LH_abbat_17_2";
				}
				link.l2 = "Fadey - a respectable merchant from Guadeloupe. I only need to stock up on his favorite booze.";
				link.l2.go = "LH_abbat_17_3";
			}
			else
			{
				link.l1 = "Fadey - a respectable merchant from Guadeloupe. I only need to stock up on his favorite booze.";
				link.l1.go = "LH_abbat_17_3";
			}
		break;
		
		case "LH_abbat_17_1":
			pchar.questTemp.LongHappy.Pater2 = "Noel";
			dialog.text = "Great, I will send out the invitations, but the guests will need some time to get here. I think everything will be ready in a month, and the indicated persons will have arrived in the city.";
			link.l1 = "Good! Then I have time to run a couple of errands. See you soon, Holy Father and wish me good luck!";
			link.l1.go = "LH_abbat_18";
		break;
		
		case "LH_abbat_17_2":
			pchar.questTemp.LongHappy.Pater2 = "Puancie";
			dialog.text = "Great, I will send out the invitations, but the guests will need some time to get here. I think everything will be ready in a month, and the indicated persons will have arrived in the city.";
			link.l1 = "Good! Then I have time to run a couple of errands. See you soon, Holy Father and wish me good luck!";
			link.l1.go = "LH_abbat_18";
		break;
		
		case "LH_abbat_17_3":
			pchar.questTemp.LongHappy.Pater2 = "Fadey";
			dialog.text = "Great, I will send out the invitations, but the guests will need some time to get here. I think everything will be ready in a month, and the indicated persons will have arrived in the city.";
			link.l1 = "Good! Then I have time to run a couple of errands. See you soon, Holy Father and wish me good luck!";
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
			dialog.text = "So, the day has come, my son! Everything is ready - in a couple of hours we will be able to start. You look pale!";
			link.l1 = "I'm a little nervous, Holy Father.";
			link.l1.go = "LH_abbat_20";
		break;
		
		case "LH_abbat_20":
			dialog.text = "That's common. This is the most important day in your life, and I am sincerely happy for you, like everyone who came. I hope you remember the basic prayers at least - you have never much spoiled the church with your attention, have you? Nevertheless, I will help you in any case.\nAnd one more thing - as far as I understand it, the bride won't change her principles and we will not see her in a dress? Well, high society is about to see another surprise from you - you are full of them. Anyway, go my son, bring yourself to proper form and we will begin.";
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
			dialog.text = "Dearly beloved, we are gathered here together in the sight of God, and in the face of this congregation, to join together this man and woman in holy Matrimony. Beloved "+sld.name+" and Charles, you listened to the word of God, who reminded you of the meaning of human love and matrimony. Now, on behalf of the holy Church, I wish to challenge your intentions.\n"+sld.name+" and Charles, do you have a voluntary and sincere desire to connect with each other by the bond of matrimony, in the face of our Lord?";
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
			dialog.text = "Do you intend to be faithful to each other in health and illness, in happiness and unhappiness, until the end of your life?";
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
			dialog.text = "Do you have the intention to love and accept the children, which our Lord will send you and raise them to Christian faith?";
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
			dialog.text = "Should anyone present here know of any reason why this couple should not be joined together in holy matrimony, so speak now or forever hold your breath.\nIn this case, before the face of the Lord, and the people gathered here, I declare you husband and wife! In nomine Patris, et Filii, et Spiritus Sancti. Amen.";
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
			sld.dialog.currentnode = "LongHappy_31";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 4.0);
		break;
		
		case "LH_abbat_37":
			dialog.text = "My congratulations, son. Your father can be proud of you, and I'm proud too. Be happy and take care of each other in our difficult time.";
			link.l1 = "Thank you, Holy Father. It was a wonderful service and I am glad that it was you who held it.";
			link.l1.go = "LH_abbat_38";
		break;
		
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
