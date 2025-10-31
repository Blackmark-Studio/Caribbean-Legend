// Санчо Карпентеро - бармен
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
			if (CheckAttribute(pchar, "GenQuest.CitizenConflict") && sti(pchar.GenQuest.CitizenConflict) > 3)
			{
				dialog.text = "Je ne veux pas te parler. Tu attaques des gens paisibles sans raison et tu les provoques à se battre. Va-t'en de ma taverne !";
				link.l1 = "Hm...";
				link.l1.go = "exit";
				break;
			}
			if (pchar.questTemp.LSC == "return" && !CheckAttribute(npchar, "quest.return_isl"))
			{
				dialog.text = "Bonjour, monami."+pchar.name+" ! Je suis si heureux de te voir ! Je savais, je savais que les ragots étaient des mensonges ! Nom d'un chien, il faut absolument boire à ça maintenant !";
				link.l1 = "Eh bien, buvons, camarade ! Je suis aussi foutrement content de te voir !";
				link.l1.go = "exit";
				npchar.quest.return_isl = "true";
				break;
			}
			// пей до дна
			if (CheckAttribute(npchar, "quest.drink") && npchar.quest.drink == "fail")
			{
				dialog.text = ""+pchar.name+", Je suis désolé pour ton échec. Peu de gens peuvent boire plus que le gros homme. Comment va ta tête?";
				link.l1 = "Ouais, mon pote, t'as du bon rhum fort là. Je te dois pour les boissons... combien ?";
				link.l1.go = "drunk_fail";
				break;
			}
			if (CheckAttribute(npchar, "quest.drink") && npchar.quest.drink == "win")
			{
				dialog.text = "Tu as battu Fazio, "+pchar.name+"Je suis surpris, peu ont pu le battre à la boisson. Tenez, prenez vos deux cents doublons.";
				link.l1 = "Merci pour tes paroles aimables, l'ami !";
				link.l1.go = "drunk_win";
				break;
			}
			// крабовый салат
			if (CheckAttribute(npchar, "quest.crab") && npchar.quest.crab == "begin")
			{
				dialog.text = "Понял. Пожалуйста, предоставьте текст для перевода."+pchar.name+"? On dit que tu as plongé au fond dans une combinaison fabriquée par un mécanicien Narval. Est-ce vrai ou n'est-ce que des rumeurs, comme d'habitude ?";
				link.l1 = "C'est vrai, mon ami. J'y ai plongé pour de bon.";
				link.l1.go = "crab";
				break;
			}
			if (npchar.quest.meeting == "0")
			{
				dialog.text = "Salutations au nouvel homme dans ma taverne ! Bienvenue ! Vous trouverez toujours des boissons dans ma taverne, mes caves à vin sont pleines, je ne peux pas en dire autant de la nourriture, ha-ha... Je plaisante. Mon nom est Sancho Carpentero et je suis le propriétaire de cet endroit.";
				link.l1 = TimeGreeting()+", Sancho. Mon nom est "+GetFullName(pchar)+"Enchanté de faire votre connaissance.";
				link.l1.go = "meeting";
				npchar.quest.meeting = "1";
			}
			else
			{
				dialog.text = "Ah, mon ami "+pchar.name+"Ravi de te voir dans ma taverne ! Tu veux boire quelque chose ?";
				// квестовые ветки
				if (CheckAttribute(pchar, "questTemp.Saga.SharkHunt") && pchar.questTemp.Saga.SharkHunt == "search_mush_1" && !CheckAttribute(npchar, "quest.mushket"))
				{
					link.l6 = "Ecoute, Sancho, sais-tu où je peux trouver un bon mousquet ? Pas une arme banale de soldat, mais quelque chose de précis, pour la chasse peut-être ?";
					link.l6.go = "mushket";
				}
				if (CheckAttribute(pchar, "questTemp.Saga.SharkHunt") && pchar.questTemp.Saga.SharkHunt == "search_mush_2")
				{
					link.l6 = "Ecoute, Sancho, j'ai quelques questions pour toi. Je cherche un homme nommé Adolf Barbier. On dit qu'il fréquente souvent cet endroit...";
					link.l6.go = "adolf";
				}
				if (CheckAttribute(pchar, "questTemp.Saga.SharkHunt") && pchar.questTemp.Saga.SharkHunt == "barmen_whiskey")
				{
					link.l6 = "Écoute, Sancho, on dit que Chad Kapper t'a acheté de l'arsenic...";
					link.l6.go = "whiskey";
				}
				if (CheckCharacterItem(pchar, "talisman1") && CheckAttribute(npchar, "quest.rat"))
				{
					link.l7 = "Sancho, veux-tu que je te montre quelque chose d'intéressant ? Est-ce le masque de chauve-souris que tu voulais tant avoir ?";
					link.l7.go = "rat";
				}
				if (CheckCharacterItem(pchar, "talisman1") && CheckAttribute(npchar, "quest.ratmoney") && PCharDublonsTotal() >= 1)
				{
					if (PCharDublonsTotal() >= sti(npchar.quest.ratmoney))
					{
						if(!CheckAttribute(npchar, "quest.ratmoneyagain")) ChangeCharacterComplexReputation(pchar, "fame", 5);
						link.l7 = "Sancho, je suis venu pour ma cuirasse. Voici l'argent.";
						link.l7.go = "rat_3";
					}
					else
					{
						npchar.quest.ratmoneyagain = true;
						link.l7 = "Sancho, je suis venu chercher ma cuirasse. Voici l'argent.";
						link.l7.go = "rat_take_money_not_all";
					}
				}
				if (makeint(pchar.money) >= 25)
				{
					link.l1 = "Servez-moi du rhum, Sancho.";
					link.l1.go = "drink";
				}
				if (makeint(pchar.money) >= 20)
				{
					link.l2 = "Je veux rester ici.";
					link.l2.go = "room";
				}
				if (stf(environment.time) >= 6.0 && stf(environment.time) <= 18.0 && makeint(pchar.money) >= 300)
				{
					link.l9 = "Ennuyé... Sancho, je veux passer du temps ici avec une bouteille de vin jusqu'au soir...";
					link.l9.go = "drink_sit";
				}
				link.l3 = LinkRandPhrase("Tu as quelque chose d'intéressant à raconter ?","Que s'est-il passé récemment sur l'île ?","Des potins?");
				link.l3.go = "rumours_LSC";
				if (CheckAttribute(npchar, "quest.crab") && npchar.quest.crab == "current" && CheckCharacterItem(pchar, "crab_pincers"))
				{
					link.l10 = "Sancho, je veux te vendre des pinces de crabe.";
					link.l10.go = "crab_trade";
				}
				link.l4 = "Sancho, je veux te demander quelque chose à propos de l'Île.";
				link.l4.go = "int_quests"; //информационный блок
				link.l5 = "Non, l'ami. Je voulais juste voir comment tu te débrouilles ici.";
				link.l5.go = "exit";
			}
			NextDiag.TempNode = "First time";
		break;
		
		case "meeting":
			dialog.text = "Moi aussi. J'espère vous voir au moins tous les deux jours ou même chaque soir, ha-ha ! Je suis sincèrement heureux d'avoir des visiteurs dans ma taverne.";
			if (makeint(pchar.money) >= 25)
			{
				link.l1 = "Sers-moi du rhum, Sancho.";
				link.l1.go = "drink";
			}
			if (makeint(pchar.money) >= 20)
			{
				link.l2 = "Je veux rester ici.";
				link.l2.go = "room";
			}
			link.l3 = "Sancho, je veux te demander quelque chose à propos de l'île.";
			link.l3.go = "int_quests"; //информационный блок
			link.l4 = "À bientôt, Sancho!";
			link.l4.go = "exit";
			NextDiag.TempNode = "First time";
		break;
		
		case "mushket":
			dialog.text = "Non, mon ami, je ne peux pas t'aider. Tu sais, je suis un spécialiste des verres de bière et des bouteilles de vin - mais pas des mousquets, ha-ha ! Va à la boutique, j'ai entendu dire qu'Axel vend parfois des armes intéressantes. Tu pourrais y trouver ce dont tu as besoin.";
			link.l1 = "Merci pour le conseil.";
			link.l1.go = "exit";
			npchar.quest.mushket = "true";
		break;
		
		case "adolf":
			dialog.text = "Adolf ? Oui, il me rend visite de temps en temps, bien que je ne l'aie pas vu ces derniers jours. Il a disparu depuis qu'il a eu une conversation avec ce gros homme Giuseppe.";
			link.l1 = "Giuseppe? Vous voulez dire Giuseppe Fazio ?";
			link.l1.go = "adolf_1";
		break;
		
		case "adolf_1":
			dialog.text = "Ha, mon ami, il n'y a qu'un seul Giuseppe sur l'Île - Giuseppe Fazio. Aye, c'est lui. Ils étaient assis pendant quelques heures à boire du rhum, ayant une conversation très animée.";
			link.l1 = "Se disputaient-ils ?";
			link.l1.go = "adolf_2";
		break;
		
		case "adolf_2":
			dialog.text = "Non. On aurait dit qu'ils étaient de vieux copains. Écoute, va voir Fazio à la 'Caroline' et demande-lui à propos d'Adolf.";
			link.l1 = "D'accord, je vais le faire.";
			link.l1.go = "adolf_3";
		break;
		
		case "adolf_3":
			dialog.text = "Est-ce tout ? Vous avez dit que vous aviez quelques questions...";
			link.l1 = "Oui. Dis-moi, qui est Mary la Rouge et Cyclope Marcello ?";
			link.l1.go = "adolf_4";
		break;
		
		case "adolf_4":
			dialog.text = "Red Mary est l'une des Narvals. Jeune et belle fille, mais elle est complètement sauvage, oui. Elle sait manier sa lame et un pistolet aussi bien qu'un homme. Elle était la petite amie d'Alan Milrow, un ancien chef du clan Narval, avant que l'amiral ne le tue\nLa mort d'Alan l'a beaucoup affectée, la plupart du temps elle pleure et maudit Shark dans sa cabine sur le 'Ceres Smithy'... Mais elle s'en remettra, la vie continue après tout\nJe ne sais pas grand-chose sur Marcello, je ne l'ai vu que quelques fois. Un type suspect. On dit qu'il était un chasseur royal, qu'il a perdu un œil dans un combat et qu'il est devenu officier de bord\nIl déteste les pirates, on dirait qu'il leur en veut. Pas étonnant, étant donné son ancien service dans les équipes d'abordage des navires marchands.";
			link.l1 = "Je vois. Merci beaucoup, Sancho, tu as beaucoup aidé !";
			link.l1.go = "adolf_5";
		break;
		
		case "adolf_5":
			dialog.text = "Tu es le bienvenu, camarade, reviens me voir, et nous partagerons une bière ensemble...";
			link.l1 = "Bien sûr !";
			link.l1.go = "adolf_6";
		break;
		
		case "adolf_6":
			DialogExit();
			pchar.questTemp.Saga.SharkHunt = "search_mush_3"; //флаг на Джузеппе
			AddQuestRecord("SharkHunt", "13");
		break;
		
		// виски для Акулы
		case "whiskey":
			dialog.text = "Kapper ? Non. Il n'a pas visité la taverne récemment. Marcello Cyclops a acheté une fiole d'arsenic il y a seulement quinze minutes - il est aussi tourmenté par les rats. Je le comprends parfaitement... Fichus rats.";
			link.l1 = "Marcello Cyclope?!";
			link.l1.go = "whiskey_1";
		break;
		
		case "whiskey_1":
			dialog.text = "Eh bien, oui. Est-ce étrange ?";
			link.l1 = "Non, bien sûr que non ! Je le cherche depuis quelques jours et il s'avère qu'il a été ici récemment. Pourriez-vous me dire où il est allé ?";
			link.l1.go = "whiskey_2";
		break;
		
		case "whiskey_2":
			dialog.text = "Il était avec Adolf Barbier qui habite à la 'Santa Florentina'. Peut-être qu'ils s'y dirigeaient.";
			link.l1 = "Merci !";
			link.l1.go = "whiskey_3";
		break;
		
		case "whiskey_3":
			dialog.text = "Si tu as besoin d'arsenic, je peux te vendre une fiole pour vingt doublons.";
			link.l1 = "D'accord. Nous en parlerons plus tard, Sancho. À bientôt !";
			link.l1.go = "whiskey_4";
		break;
		
		case "whiskey_4":
			DialogExit();
			pchar.questTemp.Saga.SharkHunt = "whiskey_poison"; // флаг - виски травят
			AddQuestRecord("SharkHunt", "37");
			sld = CharacterFromID("LSC_Adolf");
			LAi_SetActorType(sld);
			ChangeCharacterAddressGroup(sld, "SantaFlorentinaShipInside4", "goto", "goto2");
			sld = CharacterFromID("Dodson");
			sld.dialog.currentnode = "whiskey"; // ноду Акуле
			// важный момент! От дальнейшего поведения геймера зависит результат
			pchar.quest.LSC_Whiskeypoison_SF.win_condition.l1 = "location";
			pchar.quest.LSC_Whiskeypoison_SF.win_condition.l1.location = "SantaFlorentinaShipInside4";
			pchar.quest.LSC_Whiskeypoison_SF.function = "LSC_WhiskeyPoison_SF"; // прерывание на Санта-Флорентину
			pchar.quest.LSC_Whiskeypoison_AE.win_condition.l1 = "location";
			pchar.quest.LSC_Whiskeypoison_AE.win_condition.l1.location = "AvaShipInside3";
			pchar.quest.LSC_Whiskeypoison_AE.function = "LSC_WhiskeyPoison_AE"; // прерывание на Эву
			pchar.quest.LSC_Whiskeypoison_exit.win_condition.l1 = "location";
			pchar.quest.LSC_Whiskeypoison_exit.win_condition.l1.location = "LostShipsCity_town";
			pchar.quest.LSC_Whiskeypoison_exit.function = "LSC_Whiskeypoison_exit"; // прерывание на выход из таверны
			// закрываем вход к Фацио
			LocatorReloadEnterDisable("LostShipsCity_town", "reload20", true);
			LocatorReloadEnterDisable("LostShipsCity_town", "reload24", true);
		break;
		
		// пей до дна
		case "drunk_fail":
			dialog.text = "Allez, l'ami ! Tu ne me dois rien. Tu as déjà perdu cent doublons. C'était une erreur de traiter avec Fazio...";
			if (sti(pchar.money) >= 500)
			{
				link.l1 = "Non-non, Sancho ! Merci et prends ces cinq cents pesos. Cela devrait couvrir le coût des boissons autant que je me souvienne. Je ne veux pas être en dette envers toi.";
				AddMoneyToCharacter(pchar, -500);
			}
			else link.l1 = "Eh, merci, Sancho. Tu as raison.";
			link.l1.go = "exit";
			DeleteAttribute(npchar, "quest.drink");
		break;
		
		case "drunk_win":
			DialogExit();
			TakeNItems(pchar, "gold_dublon", 200);
			Log_Info("You have received 200 doubloons");
			PlaySound("interface\important_item.wav");
			DeleteAttribute(npchar, "quest.drink");
		break;
		
		// крабовый салат
		case "crab":
			dialog.text = "Hm... alors, j'ai une proposition pour vous. Avez-vous vu des crabes géants là-bas ?";
			link.l1 = "Ai-je vu des crabes? Il y en avait des hordes! Et de quelle proposition parlez-vous?";
			link.l1.go = "crab_1";
		break;
		
		case "crab_1":
			dialog.text = "Si tu tues quelques crabes, assure-toi de m'apporter les pinces. Je te paierai bien en doublons - cinq pièces pour chaque. Axel Yost ne paiera pas autant, crois-moi. Je ne te demande pas de chasser les crabes pour cette tâche - mais si tu en rencontres, garde cela à l'esprit...";
			link.l1 = "Pourquoi les pinces? Qu'en est-il des autres parties d'un crabe? Que fais-tu avec celles-là?";
			link.l1.go = "crab_2";
		break;
		
		case "crab_2":
			dialog.text = "Pourquoi les pinces ? Parce que la plupart de la chair se trouve dessus. Les crabes n'ont pas beaucoup de chair sur leurs pattes et leurs corps sont recouverts d'une carapace solide. La chair de crabe est un mets délicat ici, elle a un goût exquis et est très nourrissante.\nJ'ai aussi une recette unique pour cela, donc je te paierai cinq doublons pour chaque pince.";
			link.l1 = "D'accord. Je garderai cela à l'esprit.";
			link.l1.go = "crab_3";
		break;
		
		case "crab_3":
			DialogExit();
			npchar.quest.crab = "current";
		break;
		
		case "crab_trade":
			iTotalTemp = GetCharacterItem(pchar, "crab_pincers")
			dialog.text = "Splendide ! Combien en avez-vous ?";
			link.l1 = "Bonjour, mon ami."+FindRussianQtyString(iTotalTemp)+".";
			link.l1.go = "crab_trade_1";
			link.l2 = "J'ai changé d'avis.";
			link.l2.go = "exit";
		break;
		
		case "crab_trade_1":
			dialog.text = "Marché conclu. Tenez, prenez vos doublons - "+FindRussianQtyString(iTotalTemp*5)+"Merci, mon ami, si tu en trouves d'autres, apporte-les-moi.";
			link.l1 = "Bien sûr, ami.";
			link.l1.go = "crab_trade_2";
		break;
		
		case "crab_trade_2":
			DialogExit();
			RemoveItems(pchar, "crab_pincers", iTotalTemp);
			TakeNItems(pchar, "gold_dublon", iTotalTemp*5);
			PlaySound("interface\important_item.wav");
			Log_Info("You have received "+iTotalTemp*5+" doubloons");
		break;
		
		// крыс
		case "rat":
			dialog.text = "Quoi ?! Montre-moi ! Laisse-moi voir ça !";
			link.l1 = "Bien sûr.";
			link.l1.go = "rat_1";
		break;
		
		case "rat_1":
			PlaySound("interface\important_item.wav");
			dialog.text = "C'est ça... C'est vraiment ça ! C'est exactement le même que sur le dessin que m'a fait un marin ! Ami, il doit y avoir une raison pour laquelle tu m'as apporté ça, que veux-tu en échange ? Combien ?";
			link.l1 = "Bien sûr, je te l'ai apporté pour une raison. Mais quant à la récompense, que peux-tu offrir ? Autant que je me souvienne, tu m'as promis une récompense royale pour cette chose...";
			link.l1.go = "rat_2";
			link.l2 = "Désolé, l'ami, ce n'est pas à vendre. J'en ai besoin pour moi-même. Je voulais juste m'assurer que c'est bien le talisman dont tu parlais.";
			link.l2.go = "rat_exit";
		break;
		
		case "rat_exit":
			PlaySound("interface\important_item.wav");
			dialog.text = "Eh, quel dommage... Oui, garçon, c'est exactement ce talisman. Sacré veinard ! Maintenant, les rats ne te causeront plus de soucis. Et moi, je devrai continuer à les exterminer avec de l'arsenic...";
			link.l1 = "Je suis désolé de t'avoir taquiné, Sancho. Je ne l'avais jamais vu auparavant, alors j'avais besoin d'une consultation. Je suis désolé.";
			link.l1.go = "exit";
			DeleteAttribute(npchar, "quest.rat");
		break;
		
		case "rat_2":
			dialog.text = "Pour cela,"+pchar.name+", je vous offre la chance d'acheter l'objet le plus rare et précieux que je possède. Ce serait un excellent échange pour ce charme, surtout pour un brave guerrier comme vous. Laissez-moi vous l'apporter.\nRegardez : voici un magnifique Cuirasse de Milan, unique, méticuleusement façonné ! Il offre une protection exceptionnelle en combat, permettant un mouvement sans restriction, et il est léger et confortable. Une armure de cette qualité est rare tant dans les Caraïbes qu'en Europe.\nJ'ai découvert cette cuirasse dans la cabine du capitaine d'un navire de guerre espagnol il y a plusieurs années et je l'ai gardée précisément pour une occasion comme celle-ci. Je suis prêt à vous la vendre pour deux mille pièces d'or et le Dieu Rat !";
			link.l1 = "Hmm... C'EST une excellente cuirasse ! Je pense que cet échange me convient. Je vais régler cette affaire de rat, mais trouver une autre cuirasse comme celle-ci serait presque impossible. Je n'en ai jamais vu de semblable auparavant. Vraiment, c'est une pièce d'armure unique.";
			link.l1.go = "rat_yes";
			link.l2 = "Combien ? Sancho, tes rats t'ont-ils déjà mordu plusieurs fois ce matin ? Que veux-tu dire, deux mille ? Sais-tu seulement ce qu'il m'a fallu pour te procurer cet idole ? Baisse le prix immédiatement !";
			link.l2.go = "rat_torg";
			link.l3 = "Combien ?! Tu es un requin, tu le sais, Sancho ? 'Offrir une chance d'acheter !' Ha ! Pour ce genre de somme, je pourrais me commander une armure sur le continent qui dévierait les balles et me guérirait en prime ! Et pourquoi aurais-tu besoin de tant d'or ? Pour faire couler une statue de toi-même par Jurgen et l'exposer en pleine hauteur sur 'San Agustin' ?";
			link.l3.go = "rat_no";
		break;
		
		case "rat_yes":
			dialog.text = "Je suis heureux que tu sois des nôtres, mon ami. Merci de ne pas avoir oublié mon problème ! Alors, j'attendrai mes doublons. L'armure t'attendra.";
			link.l1 = "Je les amènerai sous peu !";
			link.l1.go = "rat_yes_1";
		break;
		
		case "rat_yes_1":
			DialogExit();
			DeleteAttribute(npchar, "quest.rat");
			npchar.quest.ratmoney = 2000;
		break;
		
		case "rat_torg":
			if(GetSummonSkillFromName(pchar, SKILL_COMMERCE) < 60)
			{
				Notification_Skill(false, 60, SKILL_COMMERCE);
				dialog.text = "Bonjour, mon ami."+pchar.name+", dans d'autres circonstances, j'exigerais cinq mille. L'amiral lui-même a montré de l'intérêt, et il n'est pas seul, croyez-moi. Prenez votre temps pour décider. L'armure vous attendra aussi longtemps que vous en aurez besoin. Je ne la vendrai qu'à vous.";
				link.l1 = "Je vais y réfléchir, Sancho. Je vais y réfléchir longuement et sérieusement.";
				link.l1.go = "rat_yes_1";
				AddCharacterExpToSkill(pchar, "Commerce", 400);
			}
			else
			{
				Notification_Skill(true, 60, SKILL_COMMERCE);
				dialog.text = "Bonjour, mon ami."+pchar.name+", dans d'autres circonstances, j'exigerais cinq mille. L'amiral lui-même a manifesté de l'intérêt, et il n'est pas seul, croyez-moi. Très bien, je vais réduire de cinq cents, étant donné que vous ne m'avez pas oublié, moi et mon problème. Il semble qu'il y ait eu quelques aventures en chemin.";
				link.l1 = "C'est mieux. Mais je ne comprends toujours pas pourquoi je devrais payer un supplément dans cet échange d'objets tout aussi uniques. Peut-être que c'est toi qui devrais me payer, hein Sancho ?";
				link.l1.go = "rat_yes_1500";
				AddCharacterExpToSkill(pchar, "Commerce", 100);
			}
		break;
		
		case "rat_yes_1500":
			if(GetSummonSkillFromName(pchar, SKILL_COMMERCE) < 90)
			{
				Notification_Skill(false, 90, SKILL_COMMERCE);
				dialog.text = "Non, "+pchar.name+", ça ne va pas arriver. Je peux me débarrasser des rats avec du poison, mais cette armure pourrait te sauver la vie un jour. Et tu auras l'air d'un duc italien en la portant. Mille cinq cents, c'est mon offre finale. Prends ton temps pour y réfléchir, et fais-le moi savoir. L'armure t'attendra aussi longtemps que tu en auras besoin, je ne la vendrai qu'à toi.";
				link.l1 = "Sancho, si tu n'étais pas le seul tavernier de ce cimetière lugubre... Je réfléchirai à ta proposition.";
				link.l1.go = "rat_yes_1500exit";
				AddCharacterExpToSkill(pchar, "Commerce", 600);
			}
			else
			{
				Notification_Skill(true, 60, SKILL_COMMERCE);
				dialog.text = "Pour un capitaine militaire et un pirate, tu sais vraiment comment négocier ! Tu te souviens de Jost ? Il a réussi à acheter tout mon arsenic à prix réduit, alors que les rats me tourmentaient déjà. Très bien, "+pchar.name+", tu gagnes. Je te fais une remise de cinq cents de plus ! Mais c'est ma dernière offre !";
				link.l1 = "This still feels like a rip-off, but at least now I won't feel like a typical damsel in distress in the jungle. Wait for the money; I'll bring it soon.";
				link.l1.go = "rat_yes_1000exit";
				AddCharacterExpToSkill(pchar, "Commerce", 200);
			}
		break;
		
		case "rat_no":
			dialog.text = "Calme-toi, "+pchar.name+" . De quelqu'un d'autre, j'exigerais cinq mille ! L'amiral lui-même a montré de l'intérêt, et il n'est pas seul, crois-moi. L'armure t'attendra aussi longtemps que nécessaire. C'est également inclus dans le prix de l'idole.";
			link.l1 = "Quel honneur ! Continue de nettoyer tes verres, et je vais y aller. Deux mille !";
			link.l1.go = "rat_yes_1";
		break;
		
		case "rat_yes_1500exit":
			DialogExit();
			DeleteAttribute(npchar, "quest.rat");
			npchar.quest.ratmoney = 1500;
		break;
		
		case "rat_yes_1000exit":
			Achievment_SetStat(106, 1);
			DialogExit();
			DeleteAttribute(npchar, "quest.rat");
			npchar.quest.ratmoney = 1000;
		break;
		case "rat_3":
			dialog.text = "Fait ! Je suis heureux que tu aies accepté, camarade. Merci de ne pas avoir oublié mon problème ! Prends la cuirasse, et qu'elle te serve bien au combat.";
			link.l1 = "Tiens, prends aussi ton talisman - on dirait que des jours sombres s'annoncent pour les rats dans ta taverne !";
			link.l1.go = "rat_4";
		break;
		
		case "rat_4":
			DialogExit();
			GiveItem2Character(pchar, "cirass4");
			RemoveItems(pchar, "talisman1", 1);
			RemoveDublonsFromPCharTotal(sti(npchar.quest.ratmoney));
			Log_Info("You have given away the talisman 'God of rats'");
			Log_Info("You have received a Milanese armor");
			Log_Info("You gave "+FindRussianDublonString(sti(npchar.quest.ratmoney))+"");
			PlaySound("interface\important_item.wav");
			DeleteAttribute(npchar, "quest.ratmoney");
			if(CheckAttribute(npchar, "quest.ratmoneyagain"))
				DeleteAttribute(npchar, "quest.ratmoneyagain");
		break;
		
		case "rat_take_money_not_all":
			npchar.quest.ratmoney = sti(npchar.quest.ratmoney) - PCharDublonsTotal();
			Log_Info("You gave "+FindRussianDublonString(PCharDublonsTotal())+"");
			RemoveDublonsFromPCharTotal(PCharDublonsTotal());
			PlaySound("interface\important_item.wav");
			dialog.text = "Tu m'impressionnes toujours "+FindRussianDublonString(sti(npchar.quest.ratmoney))+", "+pchar.name+".";
			link.l1 = "N'en parle pas !";
			link.l1.go = "exit";
		break;
		
		//--> информационный блок
		case "int_quests":
			dialog.text = "Je t'écoute.";
			if (!CheckAttribute(npchar, "quest.answer_1"))
			{
				link.l1 = "Quel est cet endroit? Peux-tu m'en dire plus à son sujet?";
				link.l1.go = "ansewer_1";
			}
			if (!CheckAttribute(npchar, "quest.answer_2"))
			{
				link.l2 = "Comment puis-je quitter l'Île ?";
				link.l2.go = "ansewer_2";
			}
			if (!CheckAttribute(npchar, "quest.answer_3"))
			{
				link.l3 = "Que devrais-je savoir sur l'Île Justice ?";
				link.l3.go = "ansewer_3";
			}
			if (!CheckAttribute(npchar, "quest.answer_4"))
			{
				link.l4 = "Et comment allez-vous ici ? Comment va votre taverne ?";
				link.l4.go = "ansewer_4";
			}
			link.l10 = "Je n'ai pas de questions, peu importe...";
			link.l10.go = "exit";
		break;
		
		case "ansewer_1":
			dialog.text = "Cet endroit ? Eh bien, ils l'appellent L'Île Justice, l'Île des Navires Abandonnés, ou la Cité des Navires Abandonnés - mais nous l'appelons simplement l'Île. Elle est formée d'épaves de navires, échouées sur un banc de sable parmi les récifs. La partie centrale de l'Île est une zone habitée et l'anneau extérieur est inhabité. Il n'y a eu aucune connexion avec le monde extérieur depuis dix ans.";
			link.l1 = "Compris...";
			link.l1.go = "int_quests";
			npchar.quest.answer_1 = "true";
		break;
		
		case "ansewer_2":
			dialog.text = "Construisez une longue barque ou un radeau. Mais cela ne finira pas bien pour vous. Il y a une zone de tempête d'anomalie autour de l'Île, vous ne passerez pas l'anneau extérieur sans risquer votre vie. De plus, l'Île est entourée par un fort courant.\nVous avez besoin d'une équipe pour avoir ne serait-ce qu'une mince chance de survie. Et très peu d'habitants sont prêts à quitter cet endroit. Encore moins sont prêts à prendre des risques. Les gens aiment leur mode de vie ici. Renseignez-vous si vous ne me croyez pas.";
			link.l1 = "Je vois...";
			link.l1.go = "int_quests";
			npchar.quest.answer_2 = "true";
		break;
		
		case "ansewer_3":
			dialog.text = "Tout d'abord, vous devez vous rappeler qu'il y a plusieurs zones restreintes sur L'Île Justice. Deux clans - les Narvals et les Rivados, ils vivent ici depuis longtemps, se combattant et protégeant sans crainte les territoires qu'ils considèrent comme les leurs. Essayez de leur rendre visite sans y être invité et vous êtes un homme mort\nVous devez connaître le mot de passe actuel si vous voulez entrer sur leur territoire. Ne vous inquiétez pas d'y arriver par accident, les gardes vous donneront plusieurs avertissements avant de commencer à tirer.";
			link.l1 = "Je vais garder cela à l'esprit...";
			link.l1.go = "int_quests";
			npchar.quest.answer_3 = "true";
		break;
		
		case "ansewer_4":
			dialog.text = "You know, my friend, it's fine. I used to work with food and drinks: I worked as a cook a long time ago in Europe, as an intendant in a garrison, a tavern keeper, and a cook on a ship; so the first thing I did here was establishing a tavern\nI like my job and my life is oddly satisfying. Folks are friendly here, mostly. At least they don't kill each other frequently. Clans don't interfere with my activities. All in all, this the best place I've had my life. I'm free here and no one tells me what to do\nThe only thing driving me mad are rats. They torture me, eating my provisions and ruining my tableware. I have trouble getting rid of them.";
			link.l1 = "Des rats ? Ouais, ils sont le souci de tout le monde...";
			link.l1.go = "ansewer_4_1";
		break;
		
		case "ansewer_4_1":
			dialog.text = "Hélas, je suis la personne la plus infortunée ici quand il s'agit de rats. Les autres navires ne sont pas autant terrorisés par les rats et Axel Yost a réussi d'une manière ou d'une autre à s'en débarrasser une fois pour toutes. Quant à moi, j'ai des armées de rats qui rampent ici. Eh, ils m'ont dit qu'il existe un amulette spéciale appelée le Dieu Rat.\nElle ressemble à un masque de visage de chauve-souris. On dit que cet amulette effraie les rats à en chier dans leur froc. Je suppose que quelqu'un a vendu cet amulette à Axel, il achète et revend chaque morceau de camelote qu'ils trouvent sur l'anneau extérieur.\nJe souhaite que quelqu'un me rapporte l'amulette, j'offre à cette personne une récompense royale !";
			link.l1 = "Intéressant...";
			link.l1.go = "int_quests";
			npchar.quest.answer_4 = "true";
			npchar.quest.rat = "true";
		break;
		//<-- информационный блок
		
		//--> выпивка
		case "drink":
			if (CheckAttribute(pchar, "questTemp.Rum") && sti(pchar.questTemp.Rum) > 4)
			{
				dialog.text = "Bonjour, l'ami."+pchar.name+", je pense que tu devrais arrêter. Dieu nous en préserve que tu te retrouves en difficulté ou que tu tombes par-dessus bord pour devenir le repas des crabes... Ce n'est pas une bonne idée de trop boire ici, beaucoup de personnes sont mortes à cause de cela.";
				link.l1 = "Hm... Je suppose que tu as raison, Sancho - j'en ai déjà assez. Merci de t'en soucier !";			
				link.l1.go = "exit";
			}
			else
			{
				AddMoneyToCharacter(pchar, -25);
				if(!IsEquipCharacterByArtefact(pchar, "totem_01"))
				{
					if (CheckAttribute(pchar, "questTemp.Rum"))
					{
						pchar.questTemp.Rum = sti(pchar.questTemp.Rum) + 1;
					}
					else pchar.questTemp.Rum = 1;
				}
				else 
				{
					if(CheckAttribute(pchar, "questTemp.Rum")) DeleteAttribute(pchar, "questTemp.Rum");
				}				
				WaitDate("",0,0,0, 0, 30);
				
				dialog.text = "Tu es le bienvenu, camarade. Seulement vingt-cinq pesos pour la pinte de mon meilleur rhum !";
				link.l1 = RandPhraseSimple(LinkRandPhrase("Eh bien, à ta santé et à la prospérité de ta taverne, l'ami !","Eh bien, à ceux qui sont en mer !","Eh bien, aux habitants de votre Île!"),LinkRandPhrase("Eh bien, à l'Île, et qu'elle dure à jamais !","Eh bien, que le vent nous soit toujours favorable dans toutes nos actions !","Eh bien, à la chance, au bonheur et... aux femmes !"));		
				link.l1.go = "drink_1";
			}
		break;
		
		case "drink_1":
			DialogExit();
			LAi_Fade("", "");
			if (CheckAttribute(pchar, "questTemp.Rum"))
			{
				if (sti(pchar.questTemp.Rum) < 3) LAi_AlcoholSetDrunk(pchar, 51, 5600);
				else LAi_AlcoholSetDrunk(pchar, 71, sti(pchar.questTemp.Rum)*2800);
			}
		break;
		
		case "drink_sit":
			if (chrDisableReloadToLocation || pchar.questTemp.Saga.SharkHunt == "barmen_whiskey" || pchar.questTemp.Saga.SharkHunt == "whiskey_poison") //идёт квест
			{
				dialog.text = "Je ne pense pas que ce soit une bonne idée que tu boives maintenant. Fais-moi confiance...";
				link.l1 = "Très bien.";
				link.l1.go = "exit";
				break;
			}
			if (CheckAttribute(pchar, "questTemp.LSC.MaryBye") || CheckAttribute(pchar, "questTemp.LSC.MaryWait")) // подружился с Мэри
			{
				dialog.text = "Heh, tu es un homme étrange... N'as-tu personne avec qui passer le temps ici, sur l'Île ? Compagnon, Mary me tuera si je te laisse rester ici et te saouler seul. Viens ici le soir avec quelqu'un et amuse-toi jusqu'à l'aube, si tu le souhaites.";
				link.l1 = "Très bien...";
				link.l1.go = "exit";
			}
			else
			{
				dialog.text = "Aucun problème, l'ami. Pour seulement trois cents pesos, tu auras une belle bouteille de "+LinkRandPhrase("Espagnol","Italien","Français")+" du vin - et amusez-vous tant que vous voulez.";
				link.l1 = "Merci !";
				link.l1.go = "drink_sit_1";
			}
		break;
		
		case "drink_sit_1":
			DialogExit();
			sld = ItemsFromID("potionrum");
			sld.shown = true;
			sld.startLocation = "FleuronTavern";
			sld.startLocator = "bottle";
			DoQuestReloadToLocation("FleuronTavern", "quest", "sit2", "LSC_DrinkSit");
		break;
		//<-- выпивка
		
		//--> сон в таверне
		case "room":
   			if (chrDisableReloadToLocation || pchar.questTemp.Saga.SharkHunt == "barmen_whiskey" || pchar.questTemp.Saga.SharkHunt == "whiskey_poison") //идёт квест
			{
				dialog.text = "Je ne pense pas que tu devrais dormir maintenant. Fais-moi confiance...";
				link.l1 = "Très bien.";
				link.l1.go = "exit";
				break;
			}
			if (CheckAttribute(pchar, "questTemp.LSC.MaryBye") || CheckAttribute(pchar, "questTemp.LSC.MaryWait")) // подружился с Мэри
			{
				if(!isDay())
				{
					dialog.text = "Je n'ai jamais rencontré un homme aussi étrange. Il y a une belle fille qui l'attend à la 'Forge de Cérès' et il va passer la nuit à la taverne. Ne pense même pas que je te laisserai dormir ici. Mary me tuerait pour ça.";
					link.l1 = "D'accord...";
					link.l1.go = "exit";
				}
				else
				{
					dialog.text = "Tu peux te reposer à l'étage jusqu'au soir. Mais je ne te laisserai pas passer la nuit ici - Mary me tuerait pour ça. Je suis désolé...";
					link.l1 = "D'accord. Je resterai ici jusqu'au soir...";
					link.l1.go = "hall_night_wait";
					link.l2 = "D'accord... Je me débrouillerai sans dormir.";
					link.l2.go = "exit";
				}
				break;
			}
			dialog.text = "Tu peux dormir dans le lit à l'étage pour seulement vingt pesos. Quand dois-je te réveiller ?";
			if(!isDay())
			{
				link.l1 = "Le matin.";
				link.l1.go = "hall_day_wait";
			}
			else
			{
				link.l1 = "Avant la tombée de la nuit.";
				link.l1.go = "hall_night_wait";
				link.l2 = "Le lendemain matin.";
				link.l2.go = "hall_day_wait";
			}
			link.l3 = "J'ai changé d'avis. Je ne veux pas dormir.";
			link.l3.go = "exit";
		break;
		
		case "hall_night_wait":
			AddMoneyToCharacter(pchar, -20);
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			TavernWaitDate_LSC("wait_night");
		break;
		
		case "hall_day_wait":
			AddMoneyToCharacter(pchar, -20);
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			TavernWaitDate_LSC("wait_day");
		break;
		//<-- сон в таверне
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
	}
}
