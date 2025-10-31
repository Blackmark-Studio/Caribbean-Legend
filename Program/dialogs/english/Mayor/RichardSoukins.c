// Соукинс в Пуэрто-Принсипе
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
		// ----------------------------------- Диалог первый - первая встреча
		case "First time":
            dialog.text = "Do you have any business with me? No? Then get out!";
			link.l1 = "I am leaving already.";
			link.l1.go = "exit";
			NextDiag.TempNode = "First time";


					if (npchar.city == sti(pchar.HeroParam.Location))
					{
						if(!CheckAttribute(PChar, "questTemp.pirateStartQuest"))
						{
							link.l2 = "Do you have any work for me?";
							link.l2.go = "pirateStartQuest";
						}
						else
						{
							if(pchar.questTemp.pirateStartQuest == "3" && !CheckAttribute(PChar, "questTemp.pirateStartQuest.many"))
							{
								link.l2 = "I picked up the trail, but I need some coins – 30,000 pesos to lure the rat from his hole.";
								link.l2.go = "pirateStartQuest_many";	
							}
							if(pchar.questTemp.pirateStartQuest == "3" && GetCharacterItem(pchar, "letter_open") > 0)
							{
								link.l2 = "Here, look at this letter I found on the smuggler's corpse";
								link.l2.go = "pirateStartQuest_info_1";	
							}
							if(pchar.questTemp.pirateStartQuest == "5")
							{
								link.l2 = "It's done. Norman Vigo and his ship are gone to the sea devil.";
								link.l2.go = "pirateStartQuest_final";	
							}
						}
					}
		break;

 		case "Exit":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
		break;

		case "fight":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			LAi_group_Attack(NPChar, Pchar);
			AddDialogExitQuest("MainHeroFightModeOn");
		break;

		//zagolski. начальный квест за пирата ===================================
		case "pirateStartQuest":
			dialog.text = "Hm... work, you say? Actually, it's good that you asked me. I need someone from outside. I want to find something out in the nearest town, but my men are known there. Can't promise you much, but you'll get something.";
			link.l1 = "Nice! What's the mission?";
			link.l1.go = "pirateStartQuest_1";
			link.l2 = "Sorry, but I won't risk it for a few scraps. Farewell.";
			link.l2.go = "exit";
			pchar.questTemp.pirateStartQuest = "0";
		break;
		case "pirateStartQuest_1":
			dialog.text = "Then listen, I made a deal to deliver 200 slaves a month ago with the captain of the schooner 'Saintblue'. I intended to sell them to the local plantation owner. The time has passed and the client has started to worry, but yesterday I was told that the schooner was seen not far from the island. But! The captain didn't show up. Today, my client demanded that I return his advance and said he was offered to buy slaves from another seller. More expensive, but the whole lot of slaves and all at once.";
			link.l1 = "And? I have to find 200 slaves in a few days to save you from losing an advance? For a few coins?";
			link.l1.go = "pirateStartQuest_2";
		break;
		case "pirateStartQuest_2":
			dialog.text = "Of course not. Do I look like an idiot? I won't return his advance anyway. But I need proof that the slaves offered to him are mine. Find those who offered him a new deal and you will get your 10,000 pesos. Deal?";
			link.l1 = "I'm in. Do you have any suspicions? Who could have done that?";
			link.l1.go = "pirateStartQuest_3";
			link.l2 = "Not a chance. Look for someone else. Only 10,000? Sorry, but that won't do.";
			link.l2.go = "exit";
		break;
		case "pirateStartQuest_3":
			dialog.text = "If I had any ideas, I would never use your services. Those men would be dead already. But I am eager to know how they found out about the 'Saintblue's' cargo and my client. It seems it was quite easy for them. See now?";
			link.l1 = "Yes, someone has betrayed you.";
			link.l1.go = "pirateStartQuest_4";

			pchar.questTemp.pirateStartQuest = "1";
			pchar.questTemp.pirateStartQuest.City = npchar.city;
			pchar.questTemp.pirateStartQuest.Areal = GetArealByCityName(pchar.questTemp.pirateStartQuest.City);
			pchar.questTemp.pirateStartQuest.Name = GetFullName(npchar);

			AddQuestRecord("pSQ", "1");
			AddQuestUserData("pSQ", "sCity", XI_ConvertString("Colony" + pchar.questTemp.pirateStartQuest.City + "Gen"));
			AddQuestUserData("pSQ", "sName", pchar.questTemp.pirateStartQuest.Name);
		break;
		case "pirateStartQuest_4":
			dialog.text = "Exactly! I am looking for him. Killing my competitors and returning my slaves are not your priority. I need that rat—actually, his head on a skewer, to be honest. See now why my men shouldn't know a thing about your mission? I will suspect everyone until I find out who is selling the information. And I don't really want that...";
			link.l1 = "I see. Then I'll keep a low profile. I am on my way.";
			link.l1.go = "exit";
		break;

		case "pirateStartQuest_many":
			dialog.text = "Thirty thousand, you say? That's a large sum... I can only give you 5,000 pesos, that's all I have now. And don't even think about running off with the money or I'll find you and hang you from the nearest fence! Got it?";
			link.l1 = "Fine, give me five thousand then...";
			link.l1.go = "pirateStartQuest_many_1";
		break;
		case "pirateStartQuest_many_1":
			dialog.text = "Take it. I am waiting for the result of your search.";
			link.l1 = "It will all be fine.";
			link.l1.go = "exit";
			AddMoneyToCharacter(pchar, 5000);
			pchar.questTemp.pirateStartQuest.many = "";
		break;

		//------------------------------------
		case "pirateStartQuest_info_1":
			dialog.text = "Ha! Excellent news! I was sure you'd make it. I've got some intriguing information.";
			link.l1 = "I've done my work and I want my ten thousand.";
			link.l1.go = "pirateStartQuest_info_2";
			TakeItemFromCharacter(pchar, "letter_open");
		break;
		case "pirateStartQuest_info_2":
			dialog.text = "Sure, here is your reward. But don't run away, I have one more assignment for you.\nPfaifer is a crewman of Norman Vigo, of the lugger 'Septima'. I am sure that Norman Vigo is the rat, even if he is one of us. He has been recently seen in the waters near the island. Your job is to send this rat to the sea devil. You didn't fail me the first time, so I want to ask you to handle this matter as well. I will pay you 15,000 pesos. Deal?";
			link.l1 = "I am on it! Consider the traitor Norman Vigo dead.";
			link.l1.go = "pirateStartQuest_info_3";
			link.l2 = "You know, I don't want to take part in it... I have no time anyway. Sorry, but I'm off.";
			link.l2.go = "pirateStartQuest_info_noex";
			AddMoneyToCharacter(pchar, 10000);
		break;
		case "pirateStartQuest_info_noex":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			pchar.questTemp.pirateStartQuest = "0";
			CloseQuestHeader("pSQ");
		break;
		case "pirateStartQuest_info_3":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			pchar.questTemp.pirateStartQuest = "4";

			AddQuestRecord("pSQ", "7");
			AddQuestUserData("pSQ", "sName", pchar.questTemp.pirateStartQuest.Name);

			pchar.quest.zpq_seaBattle.win_condition.l1 = "location";
			pchar.quest.zpq_seaBattle.win_condition.l1.location = pchar.questTemp.pirateStartQuest.Areal;
			pchar.quest.zpq_seaBattle.function = "pirateStartQuest_seaBattle";
		break;

		case "pirateStartQuest_final":
			dialog.text = "I know, I know. My men were watching the battle and have already reported your flawless victory. Fine, you've done your job well. Here are the 15,000 pesos I promised. And thank you, you have helped me a great deal.";
			link.l1 = "It's fine, I was glad to help! But I have to go now, I've been here too long and I've got a lot of things to do. Farewell!";
			link.l1.go = "exit";
			AddMoneyToCharacter(pchar, 15000);
			pchar.questTemp.pirateStartQuest = "0";
			CloseQuestHeader("pSQ");
			group_DeleteGroup("pirateStartQuest_Smuggler_group");
		break;


	}
}
