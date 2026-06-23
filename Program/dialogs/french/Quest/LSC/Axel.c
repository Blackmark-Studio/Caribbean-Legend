// торговец Аксель Йост
#include "DIALOGS\%language%\Rumours\Common_rumours.c"
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	ProcessCommonDialogRumors(NPChar, Link, NextDiag);
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			if (pchar.questTemp.LSC == "return" && !CheckAttribute(npchar, "quest.return_isl"))
			{
				dialog.text = "Regardez-moi ça..."+GetFullName(pchar)+"! Es-tu de retour de l'au-delà ? Comment est-ce possible ?";
				link.l1 = "Les gens ne reviennent pas de l'au-delà, Axel. C'est simple - je n'ai pas été mort, ha-ha !";
				link.l1.go = "exit";
				npchar.quest.return_isl = "true";
				break;
			}
			if (CheckAttribute(pchar, "GenQuest.NarvalConflict"))
			{
				dialog.text = "Heh, l'ami, je ne ferai pas affaire avec toi avant que tu ne règles les choses avec les Narvals. Je ne veux pas de problèmes. Va voir Fazio, il peut s'en occuper.";
				link.l1 = "D'accord, je vais le faire immédiatement.";
				link.l1.go = "exit";
				break;
			}
			if (CheckAttribute(pchar, "GenQuest.CitizenConflict") && int(pchar.GenQuest.CitizenConflict) > 3)
			{
				dialog.text = "Je ne veux pas te parler. Tu attaques les gens paisibles sans raison et tu les provoques à se battre. Déguerpis !";
				link.l1 = "Hm...";
				link.l1.go = "exit";
				break;
			}
			if (npchar.quest.meeting == "0")
			{
				dialog.text = "« Oh ! Un nouveau visage ! Qu'est-ce qui vous amène ici ? Bien que cela ne me regarde pas. Permettez-moi de me présenter : je m'appelle Axel Yost et je suis le propriétaire de cette boutique. Voyez-vous quelque chose qui vous plaît ? »";
				link.l1 = TimeGreeting()+". Mon nom est "+GetFullName(pchar)+"Quels types de marchandises avez-vous?";
				link.l1.go = "meeting";
				npchar.quest.meeting = "1";
			}
			else
			{
				dialog.text = "Ah, "+pchar.name+"Ravi de vous voir ! Voulez-vous acheter ou vendre quelque chose ?";
				// квестовые ветки
				if (CheckAttribute(pchar, "questTemp.Saga.SharkHunt") && pchar.questTemp.Saga.SharkHunt == "search_mush_1")
				{
					link.l4 = "Ecoute, Axel, as-tu un bon mousquet à vendre ? Pas un pistolet de soldat ordinaire, mais quelque chose de précis et de longue portée ?";
					link.l4.go = "adolf";
				}
				if (CheckAttribute(pchar, "questTemp.Saga.SharkHunt") && pchar.questTemp.Saga.SharkHunt == "trader_whiskey")
				{
					link.l4 = "Ecoute, Axel, est-ce que Chad Kapper t'a demandé de lui apporter un tonneau de whisky ? ";
					link.l4.go = "whiskey";
				}
				if (CheckAttribute(npchar, "quest.ole_pearl"))
				{
					link.l5 = "Ecoute, Axel, tu as dû entendre ma conversation avec cet idiot local. Quelle perle a-t-il demandée ? Je ne comprends pas.";
					link.l5.go = "ole_pearl";
				}
				link.l1 = "Oui. Faisons du troc, Axel !";
				link.l1.go = "Trade_items";
				link.l2 = LinkRandPhrase("As-tu quelque chose d'intéressant à raconter ?","Qu'est-ce qui s'est passé récemment sur L'Île Justice ?","Des potins ?");
				link.l2.go = "rumours_LSC";
				link.l3 = "Pas encore. Je voulais juste vous saluer.";
				link.l3.go = "exit";
			}
			NextDiag.TempNode = "First time";
		break;
		
		case "meeting":
			dialog.text = "De toutes sortes de choses. Mélanges, lames, armes à feu, munitions, cuirasses, gemmes et minéraux. Amulettes et talismans enchantés. Déchets et objets du quotidien. Les gens m'apportent tout ce qu'ils trouvent sur les navires échoués, des choses dont ils n'ont pas besoin eux-mêmes\nAlors n'hésitez pas à faire de même. Je dois vous avertir cependant. Je ne propose pas de provisions ni de marchandises pour navires.";
			link.l1 = "D'accord, Axel. Voyons voir tes marchandises.";
			link.l1.go = "Trade_items";
			link.l2 = "Merci, Axel. Je garderai cela à l'esprit. Je viendrai te voir dès que j'aurai besoin de tes services.";
			link.l2.go = "exit";
			NextDiag.TempNode = "First time";
		break;
		
		case "Trade_items":
			DialogExit();
			if (!CheckAttribute(npchar, "trade_date") || GetNpcQuestPastDayParam(npchar, "trade_date") >= 5)
			{
				GiveItemToTrader(npchar);
				SaveCurrentNpcQuestDateParam(npchar, "trade_date");
			}
			LaunchItemsTrade(npchar, 0);
		break;
		
		// наводка на Адольфа
		case "adolf":
			dialog.text = "Ça doit être une sorte de plaisanterie. Vous êtes la troisième personne à demander. Je ne transporte pas ce genre d'armement ici. Mais il y a plusieurs mois, Adolf Barbier a essayé de me vendre son stutzen de chasse avec lunette. Une arme merveilleuse, je vous le dis. Exactement ce que vous cherchez.\nMais Barbier a demandé un prix fou pour cela. Alors, j'ai dû refuser son offre.";
			link.l1 = "Intéressant ! Et où puis-je trouver Barbier ?";
			link.l1.go = "adolf_1";
		break;
		
		case "adolf_1":
			dialog.text = "Je n'en ai aucune idée. Il erre probablement quelque part. Il visite souvent la taverne de Sancho, il aime boire un verre chaque soir.";
			link.l1 = "Merci ! Je pense que je le trouverai là-bas. Dis-moi, Axel, qui d'autre t'a interrogé sur le fusil ? Tu as mentionné d'autres personnes intéressées, qui pourraient-elles être ?";
			link.l1.go = "adolf_2";
		break;
		
		case "adolf_2":
			dialog.text = "Mary Casper et Marcello, également connu sous le nom de Cyclope. Je n'ai aucune idée pourquoi la fille aurait besoin d'un fusil, mais notre Mary la Rouge est une folle bien connue. Il y a un an, elle a acheté des tonnes de poudre à canon pour fabriquer des mines, pour étourdir les crabes, disait-elle. Dieu merci, on ne l'a pas laissée faire\nEt Marcello voulait acheter un fusil pour chasser les oiseaux, l'homme en avait assez du bœuf salé. Je les ai tous deux envoyés vers Adolf, je ne sais pas s'ils ont acheté le fusil chez lui ou non\nAussi, ce chien rusé Giuseppe Fazio s'est récemment renseigné sur Adolf. Peut-être veut-il acheter ce stutzen, lui aussi.";
			link.l1 = "Heh, j'ai beaucoup de concurrents. Bon, je vais chercher Adolf - j'espère qu'il n'a pas encore vendu le pistolet.";
			link.l1.go = "adolf_3";
		break;
		
		case "adolf_3":
			DialogExit();
			pchar.questTemp.Saga.SharkHunt = "search_mush_2"; //флаг на таверну
			AddQuestRecord("SharkHunt", "12");
			sld = characterFromId("LSC_Adolf");
			sld.lifeday = 0; // убираем настоящего Адольфа
		break;
		
		// бусинка для Белого Мальчика - просто инфа
		case "ole_pearl":
			dialog.text = "Tout le monde sait ça, monsieur ! Il demande à tout le monde ces perles, c'est ainsi qu'il appelle les grosses perles. Donnez-lui-en une, et vous serez son meilleur ami.";
			link.l1 = "Maintenant je comprends. Merci, Axel, je n'aurais jamais deviné moi-même.";
			link.l1.go = "exit";
			DeleteAttribute(npchar, "quest.ole_pearl");
		break;
		
		// виски для Акулы
		case "whiskey":
			dialog.text = "Oui, l'ami, il l'a fait. Mais je vais te décevoir si tu veux aussi acheter un tonneau de Bushmills. Je n'en avais qu'un seul et Chad l'a acheté. Je peux te proposer du whisky écossais - c'est aussi bon que l'irlandais et, à vrai dire, je préfère de loin son goût.";
			link.l1 = "Peut-être, plus tard. Chad vous a-t-il acheté autre chose ?";
			link.l1.go = "whiskey_1";
		break;
		
		case "whiskey_1":
			dialog.text = "Non. Il s'intéressait à l'arsenic, il a dit qu'il y a trop de rats au Tartarus et qu'il veut les exterminer. Je n'ai pas eu besoin d'arsenic depuis que j'ai engagé cet idiot d'Olle pour nettoyer ma boutique, tous les rats sont allés à la taverne du pauvre Sancho. Je ne sais pas pourquoi les rats ont si peur d'Olle...";
			link.l1 = "Peut-être qu'il a des chats dans sa famille...";
			link.l1.go = "whiskey_2";
		break;
		
		case "whiskey_2":
			dialog.text = "Ha-ha! Peut-être... Sancho a de l'arsenic - ça c'est sûr.";
			link.l1 = "Je vois. Merci pour l'information, alors !";
			link.l1.go = "whiskey_3";
		break;
		
		case "whiskey_3":
			DialogExit();
			AddQuestRecord("SharkHunt", "36");
			pchar.questTemp.Saga.SharkHunt = "barmen_whiskey"; // флаг на таверну - поиск мышьяка
		break;
		
		case "":
			dialog.text = "Bonjour, monami.";
			link.l1 = "Bonjour, mon ami.";
			link.l1.go = "";
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
	}
}
