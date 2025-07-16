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
				dialog.text = "Je n'ai aucune envie de te parler. Tu attaques les paisibles habitants sans raison et les provoques à se battre. Va-t'en, mécréant !";
				link.l1 = "Comme vous le souhaitez...";
				link.l1.go = "exit";
				break;
			}
			if (pchar.questTemp.LSC == "return" && !CheckAttribute(npchar, "quest.return_isl"))
			{
				dialog.text = "Je ne suis pas surpris que tu aies survécu. Mystérieux sont les chemins du Seigneur. La vie et la mort sont entre Ses mains.";
				link.l1 = "Je suis entièrement d'accord avec toi, frère Julian.";
				link.l1.go = "exit";
				npchar.quest.return_isl = "true";
				break;
			}
			if (npchar.quest.meeting == "0")
			{
				dialog.text = "Bienvenue à la sainte église de notre Île, mon fils. Les portes te sont toujours ouvertes. Je suis frère Julian et je suis heureux de voir tout serviteur de notre grand Seigneur.";
				link.l1 = TimeGreeting()+". Mon nom est "+GetFullName(pchar)+"Enchanté de te rencontrer, frère Julian.";
				link.l1.go = "meeting";
				npchar.quest.meeting = "1";
			}
			else
			{
				dialog.text = "Ah, "+GetFullName(pchar)+"! "+TimeGreeting()+" ! Tu veux quelque chose ?";
				link.l1 = "Je veux te poser quelques questions sur l'île.";
				link.l1.go = "int_quests"; //информационный блок
				link.l2 = "Puis-je vous acheter des potions ?";
				link.l2.go = "potion";
				link.l3 = "As-tu des objets sacrés à vendre ?";
				link.l3.go = "amulet";
				link.l5 = "Je voulais juste prier ici et voir comment tu vas. À bientôt!";
				link.l5.go = "exit";
			}
			NextDiag.TempNode = "First time";
		break;
		
		case "meeting": // первая встреча
			dialog.text = "J'espère que vous visiterez notre église plus souvent. Prenez soin de votre âme, mon fils. Je suis également capable de soigner votre corps, je travaille ici non seulement comme pasteur, mais aussi comme médecin.";
			link.l1 = "Je veux te poser quelques questions sur l'île.";
			link.l1.go = "int_quests"; //информационный блок
			link.l2 = "Puis-je vous acheter des potions ?";
			link.l2.go = "potion";
			link.l3 = "As-tu des objets sacrés à vendre ?";
			link.l3.go = "amulet";
			link.l4 = "Je dois y aller, frère Julian. À plus tard !";
			link.l4.go = "exit";
			NextDiag.TempNode = "First time";
		break;
		
		case "potion":
			dialog.text = "Bien sûr, mon fils. Quelle potion as-tu besoin ?";
			if (!CheckAttribute(npchar, "potion1_date") || GetNpcQuestPastDayParam(npchar, "potion1_date") >= 1)
			{
				link.l1 = "Une simple potion de guérison.";
				link.l1.go = "potion1";
			}
			if (!CheckAttribute(npchar, "potion2_date") || GetNpcQuestPastDayParam(npchar, "potion2_date") >= 1)
			{
				link.l2 = "Un élixir de guérison.";
				link.l2.go = "potion2";
			}
			if (!CheckAttribute(npchar, "potion3_date") || GetNpcQuestPastDayParam(npchar, "potion3_date") >= 1)
			{
				link.l3 = "Un antidote.";
				link.l3.go = "potion3";
			}
			if (!CheckAttribute(npchar, "potion4_date") || GetNpcQuestPastDayParam(npchar, "potion4_date") >= 1)
			{
				link.l4 = "Un mélange d'herbes.";
				link.l4.go = "potion4";
			}
			link.l5 = "Je suis désolé, frère Julian, j'ai changé d'avis.";
			link.l5.go = "exit";
		break;
		
		case "potion1":
			npchar.quest.price = 90;
			npchar.quest.type = 1;
			dialog.text = "Une potion ? 90 pesos, mon fils.";
			if (sti(Pchar.money) >= 90)
			{
				link.l1 = "Prends-les, frère Julian.";
				link.l1.go = "potion_pay";
			}
			else
			{
				link.l1 = "Je n'ai pas assez de pièces maintenant... Je reviendrai plus tard.";
				link.l1.go = "exit";
			}
		break;
		
		case "potion2":
			npchar.quest.price = 500;
			npchar.quest.type = 2;
			dialog.text = "Un élixir ? 500 pesos, mon fils.";
			if (sti(Pchar.money) >= 500)
			{
				link.l1 = "Prends-les, frère Julian.";
				link.l1.go = "potion_pay";
			}
			else
			{
				link.l1 = "Je n'ai pas assez de pièces maintenant... Je reviendrai plus tard.";
				link.l1.go = "exit";
			}
		break;
		
		case "potion3":
			npchar.quest.price = 200;
			npchar.quest.type = 3;
			dialog.text = "Un antidote ? 200 pesos, mon fils.";
			if (sti(Pchar.money) >= 200)
			{
				link.l1 = "Prends-les, frère Julian.";
				link.l1.go = "potion_pay";
			}
			else
			{
				link.l1 = "Je n'ai pas assez de pièces maintenant... Je reviendrai plus tard.";
				link.l1.go = "exit";
			}
		break;
		
		case "potion4":
			npchar.quest.price = 900;
			npchar.quest.type = 4;
			dialog.text = "Un mélange ? 900 pesos, mon fils.";
			if (sti(Pchar.money) >= 900)
			{
				link.l1 = "Prends-les, frère Julian.";
				link.l1.go = "potion_pay";
			}
			else
			{
				link.l1 = "Je n'ai pas assez de pieces maintenant... Je reviendrai plus tard.";
				link.l1.go = "exit";
			}
		break;
		
		case "potion_pay":
			AddMoneyToCharacter(pchar, -sti(npchar.quest.price));
			iTemp = sti(npchar.quest.type);
			GiveItem2Character(pchar, "potion"+iTemp);
			PlaySound("interface\important_item.wav");
			dialog.text = "Tiens. Prends ton remède. Que Dieu te guide !";
			link.l1 = "Merci, frère Julian.";
			link.l1.go = "exit";
			SaveCurrentNpcQuestDateParam(npchar, "potion"+iTemp+"_date");
		break;
		
		case "amulet":
			bool bOK = (!CheckAttribute(npchar, "amulet_date")) || (GetNpcQuestPastDayParam(npchar, "amulet_date") >= 3)
			if (bOk && GetSummonSkillFromName(pchar, SKILL_FORTUNE) > (10+hrand(110)))
			{
				npchar.quest.amulet = SelectLSCChurchAmulet();
				dialog.text = "Oui, je peux vous donner quelques amulettes sacrées qui protègent les gens des blessures et des maladies. Le prix est le même pour toute amulette - dix doublons d'or. Je peux vous offrir "+XI_ConvertString(npchar.quest.amulet)+" aujourd'hui.";
				if (PCharDublonsTotal() >= 10)
				{
					link.l1 = "Oui, je veux acheter cet amulette. Voici votre or.";
					link.l1.go = "amulet_pay";
					link.l2 = "Je n'ai pas besoin de cet amulette, frère Julian. J'attendrai que tu aies ce dont j'ai besoin.";
					link.l2.go = "exit";
					SaveCurrentNpcQuestDateParam(npchar, "amulet_date");
				}
				else
				{
					link.l1 = "Je n'ai pas assez de pièces maintenant... Je reviendrai plus tard.";
					link.l1.go = "exit";
				}
			}
			else
			{
				dialog.text = "Non, mon fils, malheureusement je n'ai rien d'autre. Reviens me voir un autre jour, peut-être trouverai-je quelque chose pour toi.";
				link.l1 = "Marché conclu, frère Julian.";
				link.l1.go = "exit";
			}
		break;
		
		case "amulet_pay":
			RemoveDublonsFromPCharTotal(10);
			GiveItem2Character(pchar, npchar.quest.amulet);
			Log_Info("You have received an amulet");
			PlaySound("interface\important_item.wav");
			dialog.text = "Merci, mon fils. Ton argent sera bien utilisé. Prends ton amulette et que Dieu te bénisse !";
			link.l1 = "Gratitude, frère Julian.";
			link.l1.go = "exit";
		break;
		
//--------------------------------------- блок вопросов и ответов ---------------------------------------------
		case "int_quests":
			dialog.text = "Je t'écoute.";
			if (!CheckAttribute(npchar, "quest.answer_1"))
			{
				link.l1 = "Comment es-tu arrivé ici, frère Julian ?";
				link.l1.go = "ansewer_1";
			}
			if (!CheckAttribute(npchar, "quest.answer_2"))
			{
				link.l2 = "Combien de personnes y a-t-il dans votre paroisse ?";
				link.l2.go = "ansewer_2";
			}
			if (!CheckAttribute(npchar, "quest.answer_3"))
			{
				link.l3 = "Qui vend des choses ici?";
				link.l3.go = "ansewer_3";
			}
			if (!CheckAttribute(npchar, "quest.answer_4"))
			{
				link.l4 = "Y a-t-il un risque de destruction pour l'Île ? Des tempêtes, peut-être ?";
				link.l4.go = "ansewer_4";
			}
			link.l10 = "Pas de questions. Je suis désolé...";
			link.l10.go = "exit";
		break;
		
		case "ansewer_1":
			dialog.text = "De la même manière que beaucoup de locaux, mon fils. Mon navire a sombré lors d'une tempête pendant mon voyage de La Havane vers la Nouvelle-Espagne. Dieu merci, j'ai survécu et maintenant je Le sers ici, aidant les pauvres âmes à trouver leur vrai chemin.";
			link.l1 = "Je vois...";
			link.l1.go = "int_quests";
			npchar.quest.answer_1 = "true";
		break;
		
		case "ansewer_2":
			dialog.text = "Moins que je ne le voudrais. La plupart des Narvals préfèrent la violence à la clémence et les Rivados sont de pauvres brebis égarées. Ils accomplissent aveuglément leurs rituels païens, mettant leurs âmes immortelles en péril. Il y a un sorcier dangereux parmi eux et il doit être purifié par la Sainte Inquisition.";
			link.l1 = "Je vois...";
			link.l1.go = "int_quests";
			npchar.quest.answer_2 = "true";
		break;
		
		case "ansewer_3":
			dialog.text = "Sancho Carpentero possède une taverne sur le Fleron, vous pouvez y trouver de la nourriture, des boissons et un lit chaleureux. Axel Yost vend une grande variété de marchandises sur l'Esmeralda. Demandez aux gens dans les rues, mon fils, beaucoup d'entre eux trouvent des choses intéressantes sur l'anneau extérieur.";
			link.l1 = "Merci !";
			link.l1.go = "int_quests";
			npchar.quest.answer_3 = "true";
		break;
		
		case "ansewer_4":
			dialog.text = "Tout est entre les mains de notre Seigneur, mon fils. Nous croyons en Lui et nous lui faisons confiance. Les graves problèmes ont toujours évité notre Île - les tempêtes se produisent souvent à l'extérieur, mais ici, c'est toujours calme.";
			link.l1 = "Merci. Tu m'as rassuré.";
			link.l1.go = "int_quests";
			npchar.quest.answer_4 = "true";
		break;
// <-- блок вопросов и ответов
		
//----------------------------------------- специальные реакции -----------------------------------------------
		//обнаружение ГГ в сундуках
		case "Man_FackYou":
			dialog.text = LinkRandPhrase("Que fais-tu là, hein ? Voleur !","Regardez-moi ça ! Dès que j'étais perdu dans mes pensées, vous avez décidé de fouiller mes coffres !","Décidé à fouiller dans mes coffres? Tu ne t'en tireras pas comme ça!");
			link.l1 = "Merde !";
			link.l1.go = "fight";
		break;
		
		case "Woman_FackYou":
			dialog.text = "Quoi ?! Décidé de fouiller dans mes coffres ? Tu ne t'en sortiras pas comme ça !";
			link.l1 = "Fille insensée !";
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
			dialog.text = LinkRandPhrase("Écoute, tu ferais mieux de ranger ton arme. Ça me rend nerveux.","Tu sais, courir avec une lame n'est pas toléré ici. Range-la.","Écoute, ne joue pas au chevalier médiéval courant avec une épée. Range-la, cela ne te va pas...");
			link.l1 = LinkRandPhrase("D'accord.","D'accord.","Comme vous dites...");
			link.l1.go = "exit";
			NextDiag.TempNode = "First Time";
		break;	
		
		case "CitizenNotBlade":
			if (loadedLocation.type == "town")
			{
				dialog.text = NPCharSexPhrase(NPChar,"Écoute, je suis citoyen de cette ville et je te demanderais de rengainer ton épée.","Écoutez, je suis citoyen de cette ville et je vous demanderais de rengainer votre épée.");
				link.l1 = LinkRandPhrase("D'accord.","D'accord.","Comme tu dis...");
			}
			else
			{
				dialog.text = NPCharSexPhrase(NPChar,"Sois prudent, l'ami, en courant avec une arme. Je pourrais devenir nerveux...","Je n'aime pas quand les gens marchent devant moi avec leur arme prête. Ça me fait peur...");
				link.l1 = RandPhraseSimple("Compris.","Je l'emporte.");
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
