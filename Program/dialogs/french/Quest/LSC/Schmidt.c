// Юрген Шмидт - оружейник
#include "DIALOGS\%language%\Rumours\Common_rumours.c"
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	int iTemp, iRem;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	ProcessCommonDialogRumors(NPChar, Link, NextDiag);
	
	string NodeName = Dialog.CurrentNode;
	string NodePrevName = "";
	if (CheckAttribute(NextDiag, "PrevNode")) NodePrevName = NextDiag.PrevNode;
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			if (CheckAttribute(pchar, "GenQuest.NarvalConflict"))
			{
				dialog.text = "Ecoute, monsieur, pourquoi as-tu laissé tes poings parler, hein ? Tu n'as rien à faire dans mon atelier tant que tu es notre ennemi. Dehors !";
				link.l1 = "Hm...";
				link.l1.go = "exit";
				break;
			}
			if (npchar.quest.meeting == "0")
			{
				if (CheckAttribute(pchar, "questTemp.LSC.nrv_friend")) // стал другом нарвалов
				{
					dialog.text = "Ah, "+GetFullName(pchar)+" ! J'ai entendu parler de tes exploits. Il est bon que tu sois devenu l'ami de Donald et notre allié. Les Narvals savent apprécier l'amitié, je peux te l'assurer.";
					link.l1 = "J'espère bien. Puis-je compter sur vos services maintenant ?";
					link.l1.go = "friend";
				}
				else
				{
					dialog.text = "Alors ? Que veux-tu ?";
					link.l1 = TimeGreeting()+". Mon nom est "+GetFullName(pchar)+"Et je me promène juste, fais connaissance avec les gens. Est-ce que je te dérange ?";
				link.l1.go = "meeting";
				}
				npchar.quest.meeting = "1";
			}
			else
			{
				if (CheckAttribute(pchar, "questTemp.LSC.nrv_friend")) // стал другом нарвалов
				{
					dialog.text = "Ah, "+GetFullName(pchar)+"J'ai entendu parler de tes exploits. C'est bien que tu sois devenu l'ami de Donald et notre allié. Les Narvals savent apprécier l'amitié, je peux te l'assurer.";
					link.l1 = "J'espère bien. Puis-je compter sur vos services maintenant ?";
					link.l1.go = "friend";
				}
				else
				{
					dialog.text = "Ah, "+GetFullName(pchar)+"! Tu veux encore parler ? Je dois te décevoir, je n'ai ni le temps ni l'envie pour ça.";
					link.l1 = "D'accord, je ne te dérangerai pas.";
					link.l1.go = "exit";
				}
			}
			NextDiag.TempNode = "First time";
		break;
		
		case "meeting": // первая встреча
			dialog.text = "Exactement ! Vous me dérangez, monsieur. Je suis Jurgen Schmidt, armurier et forgeron du clan Narval. Je fournis des armes à notre peuple. Mais il faut du temps pour fabriquer une bonne lame, une clé, une serrure ou pour réparer le mécanisme d'un mousqueton de tour. Cela prend beaucoup de temps, de patience et d'attention. C'est pourquoi je n'aime pas quand les gens me dérangent.";
			link.l1 = "Fabriquez-vous des armes ? Puis-je vous commander quelque chose ?";
			link.l1.go = "meeting_1";
		break;
		
		case "meeting_1":
			dialog.text = "Non. Je fabrique des armes uniquement pour les membres du clan des Narvals. C'est mon principe et je le maintiendrai. Alors n'y comptez même pas, monsieur. Rejoignez notre clan ou au moins devenez notre allié, et dans ce cas nous pourrons discuter.";
			link.l1 = "Très bien. Je te laisse alors. Désolé de t'avoir dérangé !";
			link.l1.go = "exit";
			NextDiag.TempNode = "First time";
		break;
		
		case "friend":
			dialog.text = "Tu peux. L'ami des Narvals est aussi mon ami, alors je t'écoute.";
			link.l1 = "Je voudrais commander une lame.";
			link.l1.go = "blade";
			if (CheckAttribute(npchar, "quest.narval_blade") && pchar.questTemp.LSC.Mary == "alive")
			{
				link.l2 = "J'ai entendu dire que vous aviez forgé une lame spéciale pour feu Alan Milrow. J'ai vu cette épée large, c'est une arme formidable. Puis-je commander quelque chose de similaire ?";
				link.l2.go = "narval";
			}
			link.l3 = "Je n'ai pas encore d'idées. Je vais y réfléchir et ensuite je reviendrai !";
			link.l3.go = "exit";
			NextDiag.TempNode = "Jurgen";
		break;
		
		case "Jurgen":
			if (pchar.questTemp.LSC == "return" && !CheckAttribute(npchar, "quest.return_isl"))
			{
				dialog.text = "Ha, "+GetFullName(pchar)+" ! Alors tu n'as pas noyé ? N'est-ce pas quelque chose ! Es-tu vraiment en vie ?";
				link.l1 = "Ne t'inquiète pas, Jurgen. Je suis vivant ! Je n'allais pas me noyer...";
				link.l1.go = "exit";
				npchar.quest.return_isl = "true";
				NextDiag.TempNode = "Jurgen";
				break;
			}
			dialog.text = "Ah, "+GetFullName(pchar)+" ! Que veux-tu ?";
			if (CheckAttribute(npchar, "quest.narval_blade") && npchar.quest.narval_blade == "ferrum")
			{
				if (GetCharacterItem(pchar, "jewelry11") >= 3)
				{
					link.l4 = "J'ai apporté vos trois morceaux du fer spécial comme vous l'avez demandé. Regardez, est-ce bien ce que vous voulez ?";
					link.l4.go = "narval_7";
				}
				if (CheckCharacterItem(pchar, "meteorite"))
				{
					link.l5 = "Regarde, Jurgen. J'ai trouvé un lingot de fer intéressant au fond, mais il pèse bien plus que tu ne l'avais demandé. Pas moins de cinq livres.";
					link.l5.go = "narval_7_1";
				}
			}
			if (!CheckAttribute(npchar, "quest.blade_done"))
			{
				link.l1 = "J'aimerais commander une lame.";
				if (!CheckAttribute(npchar, "quest.blade_rules")) link.l1.go = "blade";
				else link.l1.go = "blade_4";
			}
			if (CheckAttribute(npchar, "quest.blade_payseek"))
			{
				link.l1 = "Je t'ai apporté plus de doublons en paiement pour la lame.";
				link.l1.go = "blade_3";
			}
			if (CheckAttribute(npchar, "quest.narval_blade") && pchar.questTemp.LSC.Mary == "alive" && npchar.quest.narval_blade == "begin" && pchar.questTemp.LSC != "return") // patch-9
			{
				link.l2 = "J'ai entendu dire que tu as forgé une lame spéciale pour feu Alan Milrow. J'ai vu cette épée large, c'est une arme formidable. Puis-je commander quelque chose de similaire ?";
				link.l2.go = "narval";
			}
			if (CheckAttribute(npchar, "blade_date") && GetNpcQuestPastDayParam(npchar, "blade_date") >= 20)
			{
				link.l1 = "Je suis ici pour ma commande. Elle doit être déjà prête, ai-je raison?";
				link.l1.go = "blade_done_2";
			}
			link.l3 = "Non, ce n'est rien, je voulais juste te saluer.";
			link.l3.go = "exit";
			NextDiag.TempNode = "Jurgen";
		break;
		
		// --> заказ клинков
		case "blade":
			dialog.text = "D'accord. Mais j'ai quelques exigences particulières pour toute commande, alors écoutez attentivement d'abord.";
			link.l1 = "Je suis tout ouïe.";
			link.l1.go = "blade_1";
		break;
		
		case "blade_1":
			dialog.text = "Vous ne pouvez commander qu'une seule lame de ma part, et une seule fois. Je ne fabrique pas d'arme spécifique, vous pouvez seulement nommer le type - rapière, sabre ou épée large. Réfléchissez bien avant de faire votre choix, les caractéristiques finales et la qualité de la lame dépendront des matériaux que je possède en ce moment\nMaintenant. Il me faudra vingt jours pour fabriquer votre commande. J'accepte uniquement les doublons. Mille pièces. L'argent à l'avance.";
			link.l1 = "Vraiment! Cher...";
			link.l1.go = "blade_2";
		break;
		
		case "blade_2":
			dialog.text = "C'est cher. Mais je fabrique d'excellentes lames, donc le prix est juste. C'est à vous de décider de toute façon, pas de pression.";
			link.l1 = "Je l'ai compris, Jurgen. Oui, je veux passer une commande.";
			link.l1.go = "blade_3";
			link.l2 = "Hm. J'ai besoin de temps pour réfléchir avant de te commander quoi que ce soit. Nous en parlerons plus tard !";
			link.l2.go = "exit";
			NextDiag.TempNode = "Jurgen";
			npchar.quest.blade_rules = "true";
			npchar.quest.blade_dublon = 1000;
			AddQuestRecord("LSC", "17");
		break;
		
		case "blade_3":
			dialog.text = "Très bien. Donnez-moi vos doublons alors.";
			if (PCharDublonsTotal() > 0)
			{
				npchar.quest.blade_pay = PCharDublonsTotal();
				link.l1 = "Voici, je vous en prie. J'ai "+FindRussianQtyString(sti(npchar.quest.blade_pay))+".";
				link.l1.go = "blade_pay";
			}
			link.l2 = "Hm. Malheureusement, je n'en ai pas avec moi maintenant. Mais je vous les apporterai certainement et nous continuerons notre conversation.";
			link.l2.go = "exit";
			NextDiag.TempNode = "Jurgen";
		break;
		
		case "blade_4":
			dialog.text = "Alors, est-ce ton choix final ? Es-tu sûr ?";
			link.l1 = "Oui, je le suis.";
			link.l1.go = "blade_3";
		break;
		
		case "blade_pay": // оплата
			if (sti(npchar.quest.blade_dublon) < sti(npchar.quest.blade_pay)) // полная сумма
			{
				npchar.quest.blade_pay = sti(npchar.quest.blade_dublon);
				iTemp = 0;
			}
			else iTemp = sti(npchar.quest.blade_dublon)-sti(npchar.quest.blade_pay);
			npchar.quest.blade_dublon = iTemp; // запоминаем остаток
			RemoveDublonsFromPCharTotal(sti(npchar.quest.blade_pay));
			Log_Info("You have given "+sti(npchar.quest.blade_pay)+" doubloons");
			PlaySound("interface\important_item.wav");
			if (iTemp == 0)
			{
				dialog.text = "Splendide. Vous m'avez payé pour mon travail et mes matériaux, donc je peux commencer maintenant.";
				link.l1 = "Puis-je passer une commande ?";
				link.l1.go = "blade_done";
			}
			else
			{
				dialog.text = "D'accord. J'accepte tes doublons. Tu dois m'apporter "+FindRussianQtyString(sti(npchar.quest.blade_dublon))+" plus.";
				link.l1 = "Je te les apporterai quand je les aurai.";
				link.l1.go = "exit";
				npchar.quest.blade_payseek = "true";
			}
		break;
		
		case "blade_done":
			DeleteAttribute(npchar, "quest.blade_payseek");
			dialog.text = "Bien sûr ! Quel type préférez-vous ? Rapières, sabres ou épées larges ?";
			link.l1 = "Rapières. J'aime les armes élégantes et légères.";
			link.l1.go = "rapier";
			link.l2 = "Sabres. Ils sont optimaux à mon avis.";
			link.l2.go = "sabre";
			link.l3 = "Des épées larges pour sûr ! Tranche et coupe !";
			link.l3.go = "palash";
		break;
		
		case "rapier":
			npchar.quest.blade_done = SelectJurgenBladeDone("rapier");
			dialog.text = "Comme vous le souhaitez. Revenez pour votre commande dans vingt jours, pas avant.";
			link.l1 = "Merci ! Je te verrai dans vingt jours. Adieu, Jurgen.";
			link.l1.go = "blade_done_1";
		break;
		
		case "sabre":
			npchar.quest.blade_done = SelectJurgenBladeDone("sabre");
			dialog.text = "Comme vous voulez. Revenez chercher votre commande dans vingt jours, pas avant.";
			link.l1 = "Merci ! Je te verrai dans vingt jours. Adieu, Jurgen.";
			link.l1.go = "blade_done_1";
		break;
		
		case "palash":
			npchar.quest.blade_done = SelectJurgenBladeDone("palash");
			dialog.text = "Comme vous voulez. Revenez chercher votre commande dans vingt jours, pas avant.";
			link.l1 = "Merci ! Je te reverrai dans vingt jours. Adieu, Jurgen.";
			link.l1.go = "blade_done_1";
		break;
		
		case "blade_done_1":
			DialogExit();
			SaveCurrentNpcQuestDateParam(npchar, "blade_date");
			NextDiag.CurrentNode = "Jurgen";
			AddQuestRecord("LSC", "18");
		break;
		
		case "blade_done_2":
			dialog.text = "Oui. Votre lame est prête. S'il vous plaît, prenez-la et utilisez-la. Vous comprendrez qu'elle vaut son prix dès que vous la toucherez.";
			link.l1 = "Merci, Jurgen.";
			link.l1.go = "blade_done_3";
		break;
		
		case "blade_done_3":
			DialogExit();
			NextDiag.CurrentNode = "Jurgen";
			GiveItem2Character(pchar, npchar.quest.blade_done);
			PlaySound("interface\important_item.wav");
			DeleteAttribute(npchar, "blade_date");
		break;
		
		// заказ палаша Нарвал для Мэри
		case "narval":
			dialog.text = "Hélas, mon ami, je dois refuser pour deux raisons. Premièrement, je ne ferai une telle épée qu'à un membre du clan Narval et seulement pour quelqu'un de spécial. Deuxièmement, je n'ai pas les matériaux pour cela.";
			link.l1 = "Et quel est ce fer spécial dont tu as besoin ? J'ai entendu dire qu'ils l'ont obtenu du fond...";
			link.l1.go = "narval_1";
		break;
		
		case "narval_1":
			dialog.text = "Exactement. Il y a des morceaux de ce métal éparpillés tout autour de notre banc. Je ne sais pas comment ils sont arrivés là. Mais le fer est unique, il ne rouille jamais et les lames fabriquées à partir de celui-ci ne s'émoussent jamais. Donc, si vous parvenez à obtenir le fer, nous pourrions résoudre le problème. Mais il y a encore un problème, vous n'êtes pas un Narval...";
			link.l1 = "Hm. Cela a-t-il vraiment de l'importance ?";
			link.l1.go = "narval_2";
		break;
		
		case "narval_2":
			dialog.text = "Oui. Tu peux considérer cela comme ma lubie, mais je ne fabriquerai une telle épée large que pour Narval.";
			link.l1 = "Eh bien... D'accord, j'accepte cela. Mais j'ai une idée. Puis-je commander cette lame pour le membre du clan Narval ?";
			link.l1.go = "narval_3";
		break;
		
		case "narval_3":
			dialog.text = "Hum. Je suppose que tu peux, à condition que tu m'apportes le fer. Cela ne violera pas mes principes... Et pour qui veux-tu que je forge le sabre?";
			link.l1 = "Pour la Marie Rouge. Elle est du clan Narval et mérite de posséder une arme aussi excellente.";
			link.l1.go = "narval_4";
		break;
		
		case "narval_4":
			dialog.text = "Ha ! J'aurais pu le deviner moi-même. Je deviens trop vieux... Eh bien, je suis d'accord. Mary sera vraiment ravie de recevoir un tel cadeau, j'en suis sûr... Apporte-moi le fer et je fabriquerai l'épée large. Je prendrai pour la lame... ah, peu importe, je le ferai gratuitement. Ce sera un présent non seulement de ta part, mais de nous deux.";
			link.l1 = "Merci ! Combien de fer auras-tu besoin ?";
			link.l1.go = "narval_5";
		break;
		
		case "narval_5":
			dialog.text = "Ces pièces que nous avons trouvées au fond étaient assez semblables - une livre chacune. J'ai besoin de trois pièces comme celles-là.";
			link.l1 = "Bien. Je vais essayer de les trouver. Et nous parlerons à nouveau.";
			link.l1.go = "narval_6";
		break;
		
		case "narval_6":
			DialogExit();
			npchar.quest.narval_blade = "ferrum";
			NextDiag.CurrentNode = "Jurgen";
			// кладем гигантский кусок метеорита на дно
			sld = ItemsFromID("meteorite");
			sld.shown = true;
			sld.startLocation = "underwater";
			sld.startLocator = "item"+(rand(7)+1);
			Log_TestInfo("Meteorite in the locator " + sld.startLocator);
			pchar.quest.LSC_narval_ferrum.win_condition.l1 = "item";
			pchar.quest.LSC_narval_ferrum.win_condition.l1.item = "meteorite";
			pchar.quest.LSC_narval_ferrum.function = "LSC_NarvalFerrum";
			AddQuestRecord("LSC", "19");
		break;
		
		case "narval_7":
			RemoveItems(pchar, "jewelry11", 3);
			PlaySound("interface\important_item.wav");
			dialog.text = "Voyons voir... Oui, c'est ça ! Cela a-t-il été difficile de trouver de si petits morceaux au fond ?";
			link.l1 = "Eh bien, que puis-je dire... Mary vaut bien de tels ennuis, n'est-ce pas ?";
			link.l1.go = "narval_8";
			pchar.quest.LSC_narval_ferrum.over = "yes"; //снять прерывание
		break;
		
		case "narval_7_1":
			RemoveItems(pchar, "meteorite", 1);
			PlaySound("interface\important_item.wav");
			dialog.text = "Laisse-moi voir... N'est-ce pas incroyable ! Oui, c'est du fer de fond, mais je n'ai jamais vu d'aussi gros morceaux auparavant. Celui-ci suffira pour fabriquer le sabre. A-t-il été difficile à trouver ?";
			link.l1 = "Eh bien, que puis-je dire... Marie vaut bien de tels ennuis, n'est-ce pas ?";
			link.l1.go = "narval_8";
		break;
		
		case "narval_8":
			dialog.text = "Je t'aime de plus en plus, "+pchar.name+"... Très bien alors. Maintenant, c'est mon tour de travailler pour notre belle Amazone. Il faudra deux jours pour fabriquer l'épée large, je mettrai de côté les autres commandes\nAmène-moi Mary après-demain. Ne lui dis pas, c'est une surprise. Elle sera heureuse comme un enfant.";
			link.l1 = "Très bien, Jurgen. Marché conclu ! À après-demain !";
			link.l1.go = "narval_9";
		break;
		
		case "narval_9":
			DialogExit();
			npchar.quest.narval_blade = "work";
			NextDiag.CurrentNode = "narval_10";
			SetFunctionTimerCondition("LSC_NarvalBladeForMary", 0, 0, 2, false); // таймер
			AddQuestRecord("LSC", "21");
		break;
		
		case "narval_10":
			dialog.text = ""+pchar.name+", ne me dérange pas. Tu veux que je termine l'épée large à temps, n'est-ce pas ?";
			link.l1 = "Oui, bien sûr. Je m'en vais.";
			link.l1.go = "exit";
			NextDiag.TempNode = "narval_10";
		break;
		
//----------------------------------------- специальные реакции -----------------------------------------------
		//обнаружение ГГ в сундуках
		case "Man_FackYou":
			dialog.text = LinkRandPhrase("Que fais-tu là, hein? Voleur!","Regarde-moi ça ! Aussitôt que je me laissais aller à la contemplation, tu as décidé de fouiller mon coffre !","Tu as décidé de fouiller dans mes coffres ? Tu ne t'en tireras pas comme ça !");
			link.l1 = "Merde !";
			link.l1.go = "fight";
		break;
		
		case "fight":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			LAi_SetOwnerTypeNoGroup(npchar);
			LAi_group_Attack(NPChar, Pchar);
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		
		//замечание по обнажённому оружию
		case "LSCNotBlade":
			dialog.text = LinkRandPhrase("Écoute, tu ferais mieux de ranger ton arme. Ça me rend nerveux.","Tu sais, courir avec une lame n'est pas toléré ici. Range-la.","Écoute, ne fais pas le chevalier médiéval courant avec une épée. Range-la, cela ne te convient pas...");
			link.l1 = LinkRandPhrase("D'accord.","Très bien.","Comme vous dites...");
			link.l1.go = "exit";
			NextDiag.TempNode = "First Time";
		break;	
		
		case "CitizenNotBlade":
			if (loadedLocation.type == "town")
			{
				dialog.text = NPCharSexPhrase(NPChar,"Écoutez, je suis citoyen de la ville et je vous demande de rengainer votre lame.","Écoutez, je suis citoyen de la ville et je vous demanderais de rengainer votre lame.");
				link.l1 = LinkRandPhrase("D'accord.","D'accord.","Comme vous dites...");
			}
			else
			{
				dialog.text = NPCharSexPhrase(NPChar,"Sois prudent, l'ami, en courant avec une arme. Je pourrais devenir nerveux...","Je n'aime pas quand les hommes marchent devant moi avec leur arme prête. Ça me fait peur...");
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

string SelectJurgenBladeDone(string _sType)
{
	string sBlade;
	switch (_sType)
	{
		case "rapier":
			if (sti(pchar.rank) > 15) sBlade = "q_blade_18"; 
			else sBlade = "q_blade_16";
		break;
		
		case "sabre":
			if (sti(pchar.rank) > 15) sBlade = "q_blade_19"; 
			else sBlade = "q_blade_10";
		break;
		
		case "palash":
			if (sti(pchar.rank) > 15) sBlade = "q_blade_21"; 
			else sBlade = "q_blade_13";
		break;
	}
	return sBlade;
}
