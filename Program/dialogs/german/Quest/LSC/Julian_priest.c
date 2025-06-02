// брат Юлиан - священник
#include "DIALOGS\%language%\Rumours\Common_rumours.c"
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	int iTemp;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	ProcessCommonDialogRumors(NPChar, Link, NextDiag);
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			if (CheckAttribute(pchar, "GenQuest.CitizenConflict") && sti(pchar.GenQuest.CitizenConflict) > 3)
			{
				dialog.text = "Ich habe keine Lust, mit dir zu reden. Du greifst friedliche Einheimische ohne Grund an und provozierst sie zum Kampf. Verschwinde, Atheist!";
				link.l1 = "Wie du wünschst...";
				link.l1.go = "exit";
				break;
			}
			if (pchar.questTemp.LSC == "return" && !CheckAttribute(npchar, "quest.return_isl"))
			{
				dialog.text = "Ich bin nicht überrascht, dass du überlebt hast. Mysteriös sind die Wege des Herrn. Leben und Tod liegen in Seinen Händen.";
				link.l1 = "Ich stimme dir vollkommen zu, Bruder Julian.";
				link.l1.go = "exit";
				npchar.quest.return_isl = "true";
				break;
			}
			if (npchar.quest.meeting == "0")
			{
				dialog.text = "Willkommen in der heiligen Kirche unserer Insel, mein Sohn. Die Türen stehen dir immer offen. Ich bin Bruder Julian und freue mich, jeden Diener unseres großen Herrn zu sehen.";
				link.l1 = TimeGreeting()+". Mein Name ist "+GetFullName(pchar)+". Freut mich, dich zu treffen, Bruder Julian.";
				link.l1.go = "meeting";
				npchar.quest.meeting = "1";
			}
			else
			{
				dialog.text = "Ach, "+GetFullName(pchar)+"! "+TimeGreeting()+"! Willst du etwas?";
				link.l1 = "Ich möchte Ihnen ein paar Fragen über die Insel stellen.";
				link.l1.go = "int_quests"; //информационный блок
				link.l2 = "Kann ich bei Ihnen einige Tränke kaufen?";
				link.l2.go = "potion";
				link.l3 = "Haben Sie irgendwelche heiligen Gegenstände zu verkaufen?";
				link.l3.go = "amulet";
				link.l5 = "Nur hierher gekommen, um zu beten und zu sehen, wie es dir geht. Bis dann!";
				link.l5.go = "exit";
			}
			NextDiag.TempNode = "First time";
		break;
		
		case "meeting": // первая встреча
			dialog.text = "Ich hoffe, dass Sie unsere Kirche öfter besuchen werden. Kümmern Sie sich um Ihre Seele, mein Sohn. Ich kann auch Ihren Körper heilen, ich arbeite hier nicht nur als Pastor, sondern auch als Arzt.";
			link.l1 = "Ich möchte Ihnen einige Fragen zur Insel stellen.";
			link.l1.go = "int_quests"; //информационный блок
			link.l2 = "Kann ich bei Ihnen einige Tränke kaufen?";
			link.l2.go = "potion";
			link.l3 = "Haben Sie irgendwelche heiligen Gegenstände zu verkaufen?";
			link.l3.go = "amulet";
			link.l4 = "Ich muss gehen, Bruder Julian. Bis dann!";
			link.l4.go = "exit";
			NextDiag.TempNode = "First time";
		break;
		
		case "potion":
			dialog.text = "Sicher, mein Sohn. Welchen Trank brauchst du?";
			if (!CheckAttribute(npchar, "potion1_date") || GetNpcQuestPastDayParam(npchar, "potion1_date") >= 1)
			{
				link.l1 = "Ein einfacher Heiltrank.";
				link.l1.go = "potion1";
			}
			if (!CheckAttribute(npchar, "potion2_date") || GetNpcQuestPastDayParam(npchar, "potion2_date") >= 1)
			{
				link.l2 = "Ein Heilelixier.";
				link.l2.go = "potion2";
			}
			if (!CheckAttribute(npchar, "potion3_date") || GetNpcQuestPastDayParam(npchar, "potion3_date") >= 1)
			{
				link.l3 = "Ein Gegengift.";
				link.l3.go = "potion3";
			}
			if (!CheckAttribute(npchar, "potion4_date") || GetNpcQuestPastDayParam(npchar, "potion4_date") >= 1)
			{
				link.l4 = "Eine Kräutermischung.";
				link.l4.go = "potion4";
			}
			link.l5 = "Es tut mir leid, Bruder Julian, ich habe meine Meinung geändert.";
			link.l5.go = "exit";
		break;
		
		case "potion1":
			npchar.quest.price = 90;
			npchar.quest.type = 1;
			dialog.text = "Ein Trank? 90 Pesos, mein Sohn.";
			if (sti(Pchar.money) >= 90)
			{
				link.l1 = "Nimm sie, Bruder Julian.";
				link.l1.go = "potion_pay";
			}
			else
			{
				link.l1 = "Ich habe jetzt nicht genug Münzen... Ich komme später wieder.";
				link.l1.go = "exit";
			}
		break;
		
		case "potion2":
			npchar.quest.price = 500;
			npchar.quest.type = 2;
			dialog.text = "Ein Elixier? 500 Pesos, mein Sohn.";
			if (sti(Pchar.money) >= 500)
			{
				link.l1 = "Nimm sie, Bruder Julian.";
				link.l1.go = "potion_pay";
			}
			else
			{
				link.l1 = "Ich habe jetzt nicht genug Münzen... Ich komme später wieder.";
				link.l1.go = "exit";
			}
		break;
		
		case "potion3":
			npchar.quest.price = 200;
			npchar.quest.type = 3;
			dialog.text = "Ein Gegengift? 200 Pesos, mein Sohn.";
			if (sti(Pchar.money) >= 200)
			{
				link.l1 = "Nimm sie, Bruder Julian.";
				link.l1.go = "potion_pay";
			}
			else
			{
				link.l1 = "Ich habe jetzt nicht genug Münzen... Ich komme später zurück.";
				link.l1.go = "exit";
			}
		break;
		
		case "potion4":
			npchar.quest.price = 900;
			npchar.quest.type = 4;
			dialog.text = "Eine Mischung? 900 Pesos, mein Sohn.";
			if (sti(Pchar.money) >= 900)
			{
				link.l1 = "Nimm sie, Bruder Julian.";
				link.l1.go = "potion_pay";
			}
			else
			{
				link.l1 = "Ich habe jetzt nicht genug Münzen... Ich komme später wieder.";
				link.l1.go = "exit";
			}
		break;
		
		case "potion_pay":
			AddMoneyToCharacter(pchar, -sti(npchar.quest.price));
			iTemp = sti(npchar.quest.type);
			GiveItem2Character(pchar, "potion"+iTemp);
			PlaySound("interface\important_item.wav");
			dialog.text = "Hier. Nimm deine Medizin. Möge Gott dich leiten!";
			link.l1 = "Danke dir, Bruder Julian.";
			link.l1.go = "exit";
			SaveCurrentNpcQuestDateParam(npchar, "potion"+iTemp+"_date");
		break;
		
		case "amulet":
			bool bOK = (!CheckAttribute(npchar, "amulet_date")) || (GetNpcQuestPastDayParam(npchar, "amulet_date") >= 3)
			if (bOk && GetSummonSkillFromName(pchar, SKILL_FORTUNE) > (10+hrand(110)))
			{
				npchar.quest.amulet = SelectLSCChurchAmulet();
				dialog.text = "Ja, ich kann Ihnen einige heilige Amulette geben, die Menschen vor Wunden und Krankheiten schützen. Der Preis ist für jedes Amulett gleich - zehn goldene Dublonen. Ich kann Ihnen anbieten "+XI_ConvertString(npchar.quest.amulet)+" heute.";
				if (PCharDublonsTotal() >= 10)
				{
					link.l1 = "Ja, ich möchte dieses Amulett kaufen. Hier ist dein Gold.";
					link.l1.go = "amulet_pay";
					link.l2 = "Ich brauche dieses Amulett nicht, Bruder Julian. Ich werde warten, bis du hast, was ich brauche.";
					link.l2.go = "exit";
					SaveCurrentNpcQuestDateParam(npchar, "amulet_date");
				}
				else
				{
					link.l1 = "Ich habe jetzt nicht genug Münzen... Ich komme später wieder.";
					link.l1.go = "exit";
				}
			}
			else
			{
				dialog.text = "Nein, mein Sohn, leider habe ich nichts anderes. Komm an einem anderen Tag vorbei, vielleicht finde ich etwas für dich.";
				link.l1 = "Abgemacht, Bruder Julian.";
				link.l1.go = "exit";
			}
		break;
		
		case "amulet_pay":
			RemoveDublonsFromPCharTotal(10);
			GiveItem2Character(pchar, npchar.quest.amulet);
			Log_Info("You have received an amulet");
			PlaySound("interface\important_item.wav");
			dialog.text = "Danke dir, mein Sohn. Dein Geld wird gut dienen. Nimm dein Amulett und möge Gott dich segnen!";
			link.l1 = "Dankbarkeit, Bruder Julian.";
			link.l1.go = "exit";
		break;
		
//--------------------------------------- блок вопросов и ответов ---------------------------------------------
		case "int_quests":
			dialog.text = "Ich höre zu.";
			if (!CheckAttribute(npchar, "quest.answer_1"))
			{
				link.l1 = "Wie bist du hierher gekommen, Bruder Julian?";
				link.l1.go = "ansewer_1";
			}
			if (!CheckAttribute(npchar, "quest.answer_2"))
			{
				link.l2 = "Wie viele Menschen sind in Ihrer Gemeinde?";
				link.l2.go = "ansewer_2";
			}
			if (!CheckAttribute(npchar, "quest.answer_3"))
			{
				link.l3 = "Wer verkauft hier Sachen?";
				link.l3.go = "ansewer_3";
			}
			if (!CheckAttribute(npchar, "quest.answer_4"))
			{
				link.l4 = "Gibt es eine Gefahr der Zerstörung für die Insel? Stürme, vielleicht?";
				link.l4.go = "ansewer_4";
			}
			link.l10 = "Keine Fragen. Es tut mir leid...";
			link.l10.go = "exit";
		break;
		
		case "ansewer_1":
			dialog.text = "Genauso wie viele Einheimische, mein Sohn. Mein Schiff wurde während meiner Reise von Havanna nach Neuspanien von einem Sturm versenkt. Gott sei Dank, habe ich es überlebt und diene Ihm jetzt hier, indem ich armen Seelen helfe, ihren wahren Weg zu finden.";
			link.l1 = "Ich sehe...";
			link.l1.go = "int_quests";
			npchar.quest.answer_1 = "true";
		break;
		
		case "ansewer_2":
			dialog.text = "Weniger als ich möchte. Die meisten Narwale bevorzugen Gewalt vor Gnade und die Rivados sind arme und verlorene Schafe. Sie führen blind ihre heidnischen Rituale aus und setzen ihre unsterblichen Seelen aufs Spiel. Unter ihnen ist ein gefährlicher Zauberer und er muss von der Heiligen Inquisition geläutert werden.";
			link.l1 = "Ich sehe...";
			link.l1.go = "int_quests";
			npchar.quest.answer_2 = "true";
		break;
		
		case "ansewer_3":
			dialog.text = "Sancho Carpentero besitzt eine Taverne auf der Fleron, dort findest du Essen, Getränke und ein warmes Bett. Axel Yost verkauft eine große Vielfalt an Waren auf der 'Esmeralda'. Frag die Leute auf der Straße, mein Sohn, viele von ihnen finden interessante Dinge am äußeren Ring.";
			link.l1 = "Danke dir!";
			link.l1.go = "int_quests";
			npchar.quest.answer_3 = "true";
		break;
		
		case "ansewer_4":
			dialog.text = "Alles liegt in der Hand unseres Herrn, mein Sohn. Wir glauben an Ihn und wir vertrauen Ihm. Schweren Ärger haben immer von unserer Insel ferngehalten - Stürme passieren oft draußen, aber hier ist es immer ruhig.";
			link.l1 = "Danke. Du hast mich beruhigt.";
			link.l1.go = "int_quests";
			npchar.quest.answer_4 = "true";
		break;
// <-- блок вопросов и ответов
		
//----------------------------------------- специальные реакции -----------------------------------------------
		//обнаружение ГГ в сундуках
		case "Man_FackYou":
			dialog.text = LinkRandPhrase("Was machst du da, hm? Dieb!","Schau dir das an! Kaum bin ich in Gedanken versunken, hast du dich entschieden, meine Truhen zu durchsuchen!","Du hast dich entschieden, meine Truhen zu überprüfen? Damit kommst du nicht durch!");
			link.l1 = "Scheiße!";
			link.l1.go = "fight";
		break;
		
		case "Woman_FackYou":
			dialog.text = "Was?! Hast du beschlossen, meine Truhen zu durchsuchen? Das wirst du nicht ungestraft tun!";
			link.l1 = "Dummes Mädchen!";
			link.l1.go = "exit_setOwner";
			LAi_group_Attack(NPChar, Pchar);
		break;
		
		case "fight":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			LAi_SetOwnerTypeNoGroup(npchar);
			LAi_group_Attack(NPChar, Pchar);
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		
		case "exit_setOwner":
			LAi_SetOwnerTypeNoGroup(npchar);
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
		//замечание по обнажённому оружию
		case "LSCNotBlade":
			dialog.text = LinkRandPhrase("Hör zu, du solltest besser deine Waffe weglegen. Es macht mich nervös.","Weißt du, hier wird es nicht toleriert, mit einer Klinge herumzulaufen. Nimm sie weg.","Hör zu, spiel nicht den mittelalterlichen Ritter, der mit einem Schwert herumläuft. Leg es weg, es steht dir nicht...");
			link.l1 = LinkRandPhrase("Gut.","In Ordnung.","Wie Sie sagen...");
			link.l1.go = "exit";
			NextDiag.TempNode = "First Time";
		break;	
		
		case "CitizenNotBlade":
			if (loadedLocation.type == "town")
			{
				dialog.text = NPCharSexPhrase(NPChar,"Hör zu, ich bin Bürger dieser Stadt und ich würde dich bitten, deine Klinge zu scheiden.","Hör zu, ich bin Bürger dieser Stadt und ich würde dich bitten, dein Schwert zu scheiden.");
				link.l1 = LinkRandPhrase("Gut.","In Ordnung.","Wie du sagst...");
			}
			else
			{
				dialog.text = NPCharSexPhrase(NPChar,"Sei vorsichtig, Kumpel, beim Laufen mit einer Waffe. Ich kann nervös werden...","Ich mag es nicht, wenn Leute mit gezogener Waffe vor mir herlaufen. Es macht mir Angst...");
				link.l1 = RandPhraseSimple("Verstanden.","Ich nehme es weg.");
			}
			link.l1.go = "exit";
			NextDiag.TempNode = "First Time";
		break;
// <-- специальные реакции
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}

string SelectLSCChurchAmulet();
{
	string sAmulet;
	switch (hrand(3))
	{
		case 0: sAmulet = "amulet_2"; break;
		case 1: sAmulet = "amulet_3"; break;
		case 2: sAmulet = "amulet_6"; break;
		case 3: sAmulet = "amulet_7"; break;
	}
	return sAmulet;
}
