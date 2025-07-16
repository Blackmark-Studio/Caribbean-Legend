//Jason общий диалог дворянок
#include "DIALOGS\%language%\Rumours\Common_rumours.c"
void ProcessDialogEvent()
{
	ref NPChar;
	aref Link, NextDiag;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	// вызов диалога по городам -->
    NPChar.FileDialog2 = "DIALOGS\" + LanguageGetLanguage() + "\Citizen\" + NPChar.City + "_Citizen.c";
    if (LoadSegment(NPChar.FileDialog2))
	{
        ProcessCommonDialog(NPChar, Link, NextDiag);
		UnloadSegment(NPChar.FileDialog2);
	}
    // вызов диалога по городам <--
	
	ProcessCommonDialogRumors(NPChar, Link, NextDiag);
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			//первая встреча
            if(NPChar.quest.meeting == "0")
			{
				if (sti(NPChar.nation) != PIRATE && GetNationRelation2MainCharacter(sti(NPChar.nation)) == RELATION_ENEMY)//проверка межнациональных отношений
				{
					dialog.text = "Hm. You are sailing under the flag of "+NationNameGenitive(sti(pchar.nation))+", captain. I have no wish to talk with the enemy of my country. Hmph!";
					link.l1 = "Ah, yes. A true patriot...";
					link.l1.go = "exit";
				}
				else
				{
					dialog.text = RandPhraseSimple("What do you want from me, "+GetAddress_Form(NPChar)+"? It's not appropriate for a common sailor to talk with a noble lady, but I am listening to you.", "Oh, and what does such a brave captain want from me?");
					link.l1 = TimeGreeting()+", "+GetAddress_FormToNPC(NPChar)+". I won't take much of your time, just want to ask...";
					link.l1.go = "question";
					link.l2 = RandPhraseSimple("I need to know what is going on in your colony.", "I need some information.");
					link.l2.go = "quests";//(перессылка в файл города)
				}
				npchar.quest.meeting = "1";
				
				//==> прибыла инспекция на Святом Милосердии
				if (CheckAttribute(pchar, "questTemp.SantaMisericordia.ColonyZapret") && pchar.location == pchar.questTemp.SantaMisericordia.ColonyZapret + "_town")
				{
					dialog.Text = LinkRandPhrase(LinkRandPhrase("The whole city is on edge - don Fernando de Alamida, the royal inspector, has arrived. You know, I've seen a lot here, but this... It's not grief that changes people, but how they deal with it. They say he became a different man after his father's death. Now you won't find a more incorruptible and... merciless servant of the Crown in the entire Archipelago.", "Just look at the 'Holy Mercy'! They say the king himself ordered it built according to special designs. And notice - not a single scratch. As if the Virgin Mary herself protects it. Though I've heard rumors... maybe it's not the Virgin at all.", "You know how many times they've tried to kill don Fernando? Twelve attacks in open waters - and that's just in the last year! Well, with such a loyal and trained crew, and under the Lord's protection - he'll survive the thirteenth too!"), LinkRandPhrase("Have you heard? Don Fernando de Alamida has arrived in our city, and they say he's somewhere in the streets right now. Would love to see him with my own eyes...", "A complicated man, this don Fernando. Some say he's a savior, cleansing the Motherland of filth. Others whisper that something broke in him after his father's death and soon we'll all be weeping. But I'll tell you this: don't fear him. Fear those who made him what he is.", "Such a handsome man, this don Fernando! But you know what's strange? It's like he doesn't notice anyone. All duty and service. I heard there was a girl... but after meeting with some priest, he completely rejected worldly pleasures. As if he took a vow."), RandPhraseSimple(RandPhraseSimple("Damn inspector! While he's here - the city's like dead. No trade, no fun. Even breathing, it seems, must be quieter. And you know what's most frightening? It's the same in every port. Like clockwork. His Royal Majesty couldn't have deliberately invented this torture for all of us!", "Don Fernando visited the orphanage again. Donates generously, prays for hours. Such a worthy man should be held up as an example to those cursed embezzlers!"), RandPhraseSimple("Ha! 'Saint' Fernando closed all the brothels again. Well, never mind, he'll sail away soon and they'll open right back up.", "The insp... inspector has arrived, that's what! Don Fernando de Almeyda, or, what's his name, Alamida! So important that the governor himself tiptoes around him. They say he looks into your eyes and sees all your sins right away. Terrifying!")));
					link.l1 = "...";
					link.l1.go = "exit";
					DeleteAttribute(link, "l2");
				}
				//<== прибыла инспекция на Святом Милосердии
				//==> Леди Бет в порту города
				if (CheckAttribute(pchar, "questTemp.LadyBeth.CaptainInColony") && pchar.location == pchar.questTemp.LadyBeth.CaptainInColony + "_town")
				{
					dialog.Text = findLedyBethRumour(npchar);
					link.l1 = "...";
					link.l1.go = "exit";
					DeleteAttribute(link, "l2");
				}
				//<== Леди Бет в порту города
			}
			else
			{
				//повторные обращения
				if (sti(NPChar.nation) != PIRATE && GetNationRelation2MainCharacter(sti(NPChar.nation)) == RELATION_ENEMY)
				{
					dialog.text = "Should I repeat myself? I don't want to be suspected as a friend of "+NationNameAblative(sti(pchar.nation))+"! Leave or I will call the guards! They would be glad to talk with you.";
					link.l1 = "Fine, fine, calm down. I am leaving.";
					link.l1.go = "exit";
				}
				else
				{
				dialog.text = NPCStringReactionRepeat("What? You again? Look for someone else to talk. There are a lot of commmoners walking around, they're more your type. I have to go now, there will be a banquet tonight in the governor's residence and my pompadour is not ready yet!", 
					"No, now you are being really annoying! Don't you not get it? Or are you slow minded?", 
					"Sir, I am beginning to suspect that you are not just an idiot but a scoundrel and a boor. I warn you that I will call my husband if you don't stop bothering me with your stupid questions!",
					"One more word and I'll tell the commandant to do something with you!", "block", 1, npchar, Dialog.CurrentNode);
				link.l1 = HeroStringReactionRepeat("I see. Farewell.", 
					"Yes-yes, I remember, just forgot to ask...",
					"You got me wrong...", 
					"Calm down, lady, I am leaving already...", npchar, Dialog.CurrentNode);
				link.l1.go = DialogGoNodeRepeat("exit", "", "", "", npchar, Dialog.CurrentNode);
				}
			}
			NextDiag.TempNode = "First time";
		break;

		//сюда вставляем любые проверки и направления на квесты
		case "question":
			dialog.text = LinkRandPhrase("Alright, let's listen.","Oh, fine. What do you want?","Questions? Fine, sailor, I am listening.");
			link.l1 = LinkRandPhrase("Can you tell me the last gossip of this town?","Have anything interesting happened here recently?","Any news from the Caribbean, my lady?");
			link.l1.go = "rumours_noblegirl";
			NextDiag.TempNode = "First time";
		break;

		//замечание по обнажённому оружию от персонажей типа citizen
		case "CitizenNotBlade":
			dialog.text = NPCharSexPhrase(NPChar, "Are you insane?! You scare me! Sheathe your weapon or I will tell the commendant to hang you in the fort!", "Are you insane?! You scare me! Sheathe your weapon or I will tell the commendant to hang you in the fort!");
			link.l1 = LinkRandPhrase("Fine.", "As you wish.", "Fine.");
			link.l1.go = "exit";
		break;

		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}
