// Хенрик Ведекер. Он же Механик.
#include "DIALOGS\%language%\Rumours\Common_rumours.c"
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	int iTemp;
	string sTemp;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	ProcessCommonDialogRumors(NPChar, Link, NextDiag);
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			if (npchar.quest.meeting == "0")
			{
				dialog.text = "Bonjour, monsieur. Je ne vous ai jamais vu auparavant. Êtes-vous un nouveau venu? Et est-ce la première fois que vous décidez de visiter cette plateforme?";
				link.l1 = TimeGreeting()+". Mon nom est "+GetFullName(pchar)+"Je suis un nouveau venu ici et je regarde juste autour de moi pour faire connaissance avec les gens...";
				link.l1.go = "meeting";
				npchar.quest.meeting = "1";
			}
			else
			{
				if (pchar.questTemp.LSC == "platinum_wait")
				{
					dialog.text = "Écoute, "+pchar.name+", si tu continues de me distraire, je ne finirai jamais les réparations.";
					link.l1 = "Oui, oui, je me souviens de cela. Je suis désolé de vous avoir dérangé !";
					link.l1.go = "exit";
					break;
				}
				// возвращение блудного скафандра
				if (pchar.questTemp.LSC == "return" && !CheckAttribute(npchar, "quest.return_isl"))
				{
					dialog.text = "Ah! Regardez-moi ça ! L'homme noyé est de retour de l'autre monde ! Maintenant, dites-moi, comment avez-vous pu réaliser un tel tour ? Ils ont fait vos funérailles et vous ont enterré en votre absence, au cas où vous ne le sauriez pas...";
					link.l1 = "Hélas, je ne vais pas mourir tout de suite. Le truc est simple - j'ai seulement touché l'idole de Kukulcan au fond. Elle m'a téléporté en Dominique, directement au village des Caraïbes...";
					link.l1.go = "return";
					break;
				}
				
				dialog.text = "Ah, "+GetFullName(pchar)+" ! "+TimeGreeting()+" !";
				// квестовые ветки
				if(pchar.questTemp.LSC == "mechanic")
				{
					link.l4 = "Henrik, j'ai une affaire pour toi. Une affaire très importante. Ole Christiansen m'a parlé de toi. On l'appelle aussi le Garçon Blanc.";
					link.l4.go = "mechanic_1";
				}
				if(pchar.questTemp.LSC == "platinum" && GetCharacterItem(pchar, "jewelry10") >= 11)
				{
					link.l4 = "Henrik, je t'ai apporté assez d' 'argent'. Exactement comme tu l'as demandé : un des tiens plus dix pièces supplémentaires. Tiens, prends-les.";
					link.l4.go = "mechanic_15";
				}
				if(pchar.questTemp.LSC == "underwater_check")
				{
					link.l4 = "Moi encore, Henrik. Comment va votre costume ? Avez-vous pu le réparer ?";
					link.l4.go = "mechanic_20";
				}
				if(pchar.questTemp.LSC == "platinum_add_wait" && GetCharacterItem(pchar, "jewelry10") >= int(pchar.questTemp.LSC.PtAddQty))
				{
					link.l4 = "J'ai assez de métal, celui que tu as demandé. Prends-le.";
					link.l4.go = "mechanic_23";
				}
				if(pchar.questTemp.LSC == "underwater_prepare")
				{
					link.l4 = "Bonne journée, Henrik. Alors, quoi, la combinaison est-elle prête pour une plongée ?";
					link.l4.go = "immersion";
				}
				if(pchar.questTemp.LSC == "underwater_natan" && CheckAttribute(pchar, "questTemp.LSC.NatanTalk"))
				{
					link.l4 = "Tout est fini, j'ai réglé mes problèmes et je suis prêt à plonger. Quand commencerons-nous ?";
					link.l4.go = "immersion_1";
				}
				if(CheckAttribute(pchar, "questTemp.LSC.UW_ready"))
				{
					link.l5 = "Bonjour, Henrik. Alors, quoi, la combinaison est prête pour une plongée ?";
					link.l5.go = "immersion_next";
				}
				if(CheckAttribute(pchar, "questTemp.LSC.UW_end") && CheckCharacterItem(pchar, "underwater"))
				{
					link.l5 = "Je veux rendre votre costume.";
					link.l5.go = "immersion_next_2";
				}
				// квестовые ветки				
				link.l1 = LinkRandPhrase("As-tu quelque chose d'intéressant à dire ?","A-t-il   eu   quelque   chose   de   nouveau   sur   l'île ?","Me raconterez-vous les derniers potins ?");
				link.l1.go = "rumours_LSC";
				link.l3 = "Je voulais juste savoir comment tu te portes.";
				link.l3.go = "exit";
			}
			NextDiag.TempNode = "First time";
		break;
		
		case "meeting": // первая встреча
			dialog.text = "Et je suis Henrik Vedecker. Cependant, la majorité des locaux me connaissent sous le nom de le Mécanicien et c'est en fait une définition très juste.";
			if(pchar.questTemp.LSC == "mechanic")
			{
				link.l1 = "Êtes-vous le Henrik Vedecker ? Heureux de vous rencontrer ! Je vous cherchais.";
				link.l1.go = "mechanic";
			}
			else
			{
				link.l1 = "Vous devez être un homme à tout faire, n'est-ce pas ?";
				link.l1.go = "meeting_1";
			}
			NextDiag.TempNode = "First time";
		break;
		
		case "meeting_1":
			dialog.text = "Oh, oui, les Narvals apprécient vraiment mes compétences. Mes outils leur permettent d'obtenir beaucoup de trésors des navires perdus dans l'anneau extérieur, afin qu'ils puissent acheter des provisions à l'amiral Dodson\nEn fait, la science et les explorations sont ma passion. Donc, je m'excuse si je ne pourrai pas vous consacrer assez de temps - mes expériences prennent presque tout mon temps.";
			link.l1 = "Je vois. Je ne vous importunerai pas sans raison, monsieur Vedecker, je vous l'assure. Je suis très heureux de vous rencontrer !";
			link.l1.go = "exit";
			NextDiag.TempNode = "First time";
		break;
		
		case "mechanic":
			dialog.text = "Vraiment? Et pourquoi?";
			link.l1 = "Ole Christiansen m'a parlé de vous. On l'appelle aussi le Garçon Blanc.";
			link.l1.go = "mechanic_1";
		break;
		
		case "mechanic_1":
			dialog.text = "Ah, ce drôle de gars ! Oui, oui, je le connais. Et que t'a-t-il dit ?";
			link.l1 = "Je suis désolé si ma prochaine question va sembler stupide mais... je vais te la poser quand même. Ole m'a dit que tu pourrais m'apprendre à plonger au fond, sous l'eau. Ne ris pas de moi, s'il te plaît, si c'est juste son imagination.";
			link.l1.go = "mechanic_2";
		break;
		
		case "mechanic_2":
			dialog.text = "C'est vrai. J'ai moi-même touché le fond plusieurs fois. Cependant, je ne plonge plus, le banc est désormais infesté de crabes géants et, évidemment, comme tu peux le voir, je ne suis pas capable de les combattre, je suis un scientifique, je ne peux pas lutter contre ces créatures.\nDe plus, il y avait aussi deux autres hommes, deux Narvals, qui avaient l'habitude de plonger, mais ils ont fini par arrêter - piller les cales des navires de l'anneau extérieur s'est avéré plus sûr que de plonger dans un endroit infesté de crabes géants.\nMaintenant, ils utilisent rarement mon équipement, pas une seule plongée ces derniers mois à cause de la fracture de la combinaison...";
			link.l1 = "Possèdes-tu vraiment un scaphandre avec lequel tu peux plonger jusqu'au fond ? Ai-je mal entendu ?";
			link.l1.go = "mechanic_3";
		break;
		
		case "mechanic_3":
			dialog.text = "Tes oreilles sont bien placées, jeune homme. J'ai inventé et fabriqué la combinaison moi-même. Elle est faite de toile épaisse complètement étanche, de pièces métalliques et d'un casque en acier forgé par moi et Jurgen dans sa forge.\nJ'ai également renforcé la combinaison avec une plaque de poitrine en métal, des genouillères, des plastrons et des bottes pour une meilleure protection contre les crabes et un poids supplémentaire.\nDes réservoirs spéciaux, remplis d'air sous pression, assurent une fonction de survie et la capacité de passer du temps sous l'eau. La combinaison est unique, et j'en suis assez fier.";
			link.l1 = "C'est splendide. Mais avez-vous mentionné que la tenue est endommagée?";
			link.l1.go = "mechanic_4";
		break;
		
		case "mechanic_4":
			dialog.text = "Malheureusement, c'est le cas. Plusieurs parties de la combinaison étaient reliées par des plaques de métal afin de garantir flexibilité et protection supplémentaire, mais l'eau de mer les a gravement affectées. Les plaques ont rouillé après des années d'utilisation et ont perdu leurs capacités de protection contre l'eau.\nIl est bon que j'aie remarqué les dégâts et empêché les gens de mourir. Même la combinaison sèche contenait un peu de sel et d'eau, ils avaient achevé leur sale besogne entièrement.";
			link.l1 = "Eh bien... Mais tu peux réparer la combinaison ! Tu peux remplacer les vieilles pièces rouillées par des nouvelles... N'est-ce pas ?";
			link.l1.go = "mechanic_5";
		break;
		
		case "mechanic_5":
			dialog.text = "Dans quel but ? Pour les remplacer encore une année plus tard ? Sais-tu à quel point ce travail est difficile ? Composer le costume avec des joints flexibles et le rendre étanche ? C'est au moins une semaine de travail sans repos.";
			link.l1 = "Et c'est la raison pour laquelle tu es prêt à jeter ton invention par-dessus bord ?";
			link.l1.go = "mechanic_6";
		break;
		
		case "mechanic_6":
			dialog.text = "Non, bien sûr que non. J'ai une idée. Je dois fabriquer les jointures avec un métal que l'eau et le sel ne peuvent détruire. Et je sais quel métal peut aider...";
			link.l1 = "Alors, quel est le problème ?";
			link.l1.go = "mechanic_7";
		break;
		
		case "mechanic_7":
			dialog.text = "Le problème, c'est que ce métal est très rare. Je n'en ai qu'un seul morceau, ce qui n'est certainement pas suffisant. J'ai besoin d'au moins dix morceaux de plus, voire quinze.";
			link.l1 = "Et quel est ce... métal dont vous parlez?";
			link.l1.go = "mechanic_8";
		break;
		
		case "mechanic_8":
			dialog.text = "Oh, c'est un métal unique, vraiment sous-estimé par beaucoup. Il a une grande durabilité, plasticité et il est absolument immunisé contre l'exposition - ni l'eau, ni le sel ne peuvent l'endommager\nPeut-être avez-vous déjà vu ce métal auparavant. Il est blanc, ressemble à l'argent, c'est pourquoi les Espagnols l'appelaient 'argent'. Ha ! Il est cent fois meilleur que l'argent ! Même meilleur que l'or ! Un jour, ils comprendront cela, mais le bon moment n'est pas encore venu.";
			link.l1 = "Écoute, pourquoi ne peux-tu pas utiliser d'autres types de métal à la place ? Pourquoi n'utilises-tu pas de l'or pour fabriquer ces plaques ? Je n'ai jamais entendu dire que l'or pouvait rouiller ou se détériorer.";
			link.l1.go = "mechanic_9";
		break;
		
		case "mechanic_9":
			dialog.text = "Vous avez un esprit flexible et vivant, jeune homme. C'est bon à savoir. Malheureusement, votre proposition ne fonctionnera pas. L'idée de l'or a été la première chose qui m'est venue à l'esprit. Mais l'or est trop mou pour lier les différentes parties de l'armure. Hélas, le platine est le seul matériau qui conviendra. Je ne fabriquerai des pièces qu'à partir de cela, même si cela prend des années pour en récolter assez. Mais j'ai vu des morceaux de ce métal auparavant sur l'Île - il est souvent mélangé avec de l'argent en raison de son apparence.";
			link.l1 = "Hm. Et si je vous aide à trouver suffisamment de ce... 'argent', me prêterez-vous la combinaison pour que je puisse plonger sous l'eau ?";
			link.l1.go = "mechanic_10";
		break;
		
		case "mechanic_10":
			dialog.text = "Pas besoin de demander ! Bien sûr, je le ferai. Je t'ai déjà dit que je ne plongerais pas là-bas à cause des crabes et personne d'autre ne veut le faire non plus.";
			link.l1 = "Alors montre-moi ce morceau de métal pour m'aider à comprendre ce que je dois trouver.";
			link.l1.go = "mechanic_11";
		break;
		
		case "mechanic_11":
			dialog.text = "Alors, tu vas le chercher ? Excellent. Tiens, prends ce morceau comme exemple. Cherche-le parmi le minerai d'argent et les pépites. Ce ne sera pas facile de le trouver, mais tu y arriveras. Il y a de petites obscurités sur l'argent mais notre métal est clair et bien plus dur que l'argent. Le moyen le plus simple de le tester serait de rayer une pièce d'argent dessus, si la pièce est endommagée, alors tu l'as trouvé.";
			link.l1 = "Très bien. Je vais le chercher immédiatement. As-tu des suggestions sur où je devrais le chercher ?";
			link.l1.go = "mechanic_12";
		break;
		
		case "mechanic_12":
			GiveItem2Character(pchar, "jewelry10");
			PlaySound("interface\important_item.wav");
			Log_Info("You have received a platinum ingot");
			dialog.text = "Hélas, je ne sais pas. Si je savais où le trouver, je le ferais moi-même. Mais je peux te donner un conseil tout de même. Cherche dans les navires des Rivados. Je ne les visite pas, donc il est très probable qu'ils l'aient.";
			link.l1 = "Je vais y réfléchir, Henrik. J'espère que j'aurai de la chance.";
			link.l1.go = "mechanic_13";
		break;
		
		case "mechanic_13":
			dialog.text = "Collectez encore dix pièces. C'est un minimum pour réparer le costume. Bonne chance !";
			link.l1 = "Merci. Adieu, Mécanicien !";
			link.l1.go = "mechanic_14";
		break;
		
		case "mechanic_14":
			DialogExit();
			pchar.questTemp.LSC = "platinum";
			AddQuestRecord("LSC", "7");
			if (GetSummonSkillFromName(pchar, SKILL_FORTUNE) >= 65 || rand(2) == 1) pchar.questTemp.LSC.PtAddQty = 0;
			else pchar.questTemp.LSC.PtAddQty = rand(4);
		break;
		
		case "mechanic_15":
			RemoveItems(pchar, "jewelry10", 11);
			dialog.text = "Eh bien, eh bien, montre-moi... Excellent ! Bravo, jeune homme ! Cela a-t-il été difficile ?";
			link.l1 = "Pas vraiment...";
			link.l1.go = "mechanic_16";
		break;
		
		case "mechanic_16":
			dialog.text = "Eh bien, maintenant je peux commencer les réparations. Je ne perdrai pas de temps et je commencerai demain. Vous avez vraiment hâte de plonger, n'est-ce pas ?";
			link.l1 = "En effet. J'ai vraiment envie d'explorer les fonds marins.";
			link.l1.go = "mechanic_17";
		break;
		
		case "mechanic_17":
			dialog.text = "C'est très bien, car j'aurai une demande à te faire lorsque nous organiserons ta plongée. Mais nous en parlerons plus tard. Viens me voir dans cinq jours, j'espère avoir terminé les réparations.";
			link.l1 = "Très bien. Je vous souhaite bonne chance !";
			link.l1.go = "mechanic_18";
		break;
		
		case "mechanic_18":
			dialog.text = "La chance est nécessaire, certes, mais la réparation de l'armure nécessitera surtout des compétences. De plus, je devrai passer une journée près de la forge avec Jurgen pour fabriquer des plaques à partir du métal que tu m'as apporté.";
			link.l1 = "Alors, je ne vais pas te déranger. À dans cinq jours. Au revoir !";
			link.l1.go = "mechanic_19";
		break;
		
		case "mechanic_19":
			DialogExit();
			pchar.questTemp.LSC = "platinum_wait";
			AddQuestRecord("LSC", "8");
			SetFunctionTimerCondition("LSC_PrepareUnderwater_Check", 0, 0, 5, false); // таймер
			AddCharacterExpToSkill(pchar, "Fortune", 300);
		break;
		
		case "mechanic_20":
			if (int(pchar.questTemp.LSC.PtAddQty) == 0)
			{
				dialog.text = "Oui. Jurgen et moi avons fait un sacré boulot et la quantité de pièces que tu as apportées était suffisante pour le faire. Le costume est réparé et préparé. Je dois juste effectuer quelques tests, mais je suis sûr que tout est en ordre. Viens demain à 10 heures du matin - je remplirai les réservoirs d'air et tu pourras faire ce que tu veux.";
				link.l1 = "Excellent ! J'ai hâte de le faire. À demain, Henrik !";
				link.l1.go = "mechanic_24";
				DeleteAttribute(pchar, "questTemp.LSC.PtAddQty");
				AddCharacterExpToSkill(pchar, "Fortune", 100);
			}
			else
			{
				dialog.text = "Je dois te décevoir, "+pchar.name+". Comme je l'avais supposé, il n'y a pas assez de métal. J'ai besoin de "+FindRussianQtyString(int(pchar.questTemp.LSC.PtAddQty))+" encore des pièces pour terminer la réparation. Je dois te demander de l'aide à nouveau.";
				link.l1 = "Eh bien, je ne m'attendais pas à un tel retournement de situation. Très bien, je vais essayer de trouver les pépites qui vous manquent.";
				link.l1.go = "mechanic_21";
			}
		break;
		
		case "mechanic_21":
			dialog.text = "Je t'attendrai. Tu peux être sûr que cette somme suffira amplement. Apporte-les simplement et je finirai le travail en un jour.";
			link.l1 = "J'espère bien... À bientôt !";
			link.l1.go = "mechanic_22";
		break;
		
		case "mechanic_22":
			DialogExit();
			pchar.questTemp.LSC = "platinum_add_wait";
			AddQuestRecord("LSC", "9");
			AddQuestUserData("LSC", "sQty", FindRussianQtyString(int(pchar.questTemp.LSC.PtAddQty)));
		break;
		
		case "mechanic_23":
			RemoveItems(pchar, "jewelry10", int(pchar.questTemp.LSC.PtAddQty));
			dialog.text = "Splendide ! Maintenant, la combinaison sera restaurée. Je dois seulement effectuer quelques tests, mais je suis sûr que tout va bien. Revenez demain à 10 heures - je remplirai les réservoirs d'air et vous pourrez faire ce que vous voulez.";
			link.l1 = "Excellent ! J'ai hâte d'y être. À demain, Henrik !";
			link.l1.go = "mechanic_24";
		break;
		
		case "mechanic_24":
			DialogExit();
			if (CheckAttribute(pchar, "questTemp.LSC.PtAddQty"))
			{
				iTemp = 2;
				sTemp = "the day after tomorrow";
				DeleteAttribute(pchar, "pchar.questTemp.LSC.PtAddQty");
			}
			else
			{
				iTemp = 1;
				sTemp = "tomorrow";
			}
			if (!CheckAttribute(pchar, "questTemp.LSC.NatanTalk")) string sText = "But I have to find Nathaniel Hawk first before I dive."; //не было разговора с Натаном
			else sText = "";
			AddQuestRecord("LSC", "10");
			AddQuestUserData("LSC", "sText1", sTemp);
			AddQuestUserData("LSC", "sText2", sText);
			pchar.quest.LSC_prepunderwater.win_condition.l1 = "Timer";
			pchar.quest.LSC_prepunderwater.win_condition.l1.date.hour  = 10;
			pchar.quest.LSC_prepunderwater.win_condition.l1.date.day   = GetAddingDataDay(0, 0, iTemp);
			pchar.quest.LSC_prepunderwater.win_condition.l1.date.month = GetAddingDataMonth(0, 0, iTemp);
			pchar.quest.LSC_prepunderwater.win_condition.l1.date.year  = GetAddingDataYear(0, 0, iTemp);
			pchar.quest.LSC_prepunderwater.function = "LSC_PrepareUnderwater";
			pchar.questTemp.LSC = "wait";
		break;
		
		case "immersion":
			dialog.text = "Oui, la combinaison est prête et remplie d'air. Vous pouvez plonger.";
			if (!CheckAttribute(pchar, "questTemp.LSC.NatanTalk")) // не было разговора с Натаном
			{
				link.l1 = "Bien. Mais je ne peux pas plonger maintenant, je dois résoudre un problème concernant mon... ami, Nathan Hawk. Je ne peux pas le trouver. Le scaphandre peut-il attendre un peu ?";
				link.l1.go = "natan";
			}
			else
			{
				link.l1 = "Splendide ! Quand commencerons-nous ? Maintenant ?";
				link.l1.go = "immersion_1";
			}
		break;
		
		case "natan":
			dialog.text = "Bien sûr. Cela peut attendre. Ne chercherez-vous pas votre ami pendant un an ?";
			link.l1 = "Bien sûr, je ne le ferai pas. Peut-être que je le trouverai même aujourd'hui. Je viendrai te voir juste après avoir terminé mes affaires avec lui.";
			link.l1.go = "natan_1";
		break;
		
		case "natan_1":
			dialog.text = "Oui, je vous en prie. Venez quand vous êtes prêt à plonger.";
			link.l1 = "Merci !";
			link.l1.go = "exit";
			pchar.questTemp.LSC = "underwater_natan";
		break;
		
		case "immersion_1":
			dialog.text = "Tout de suite si tu veux. Mais laisse-moi te donner une petite instruction d'abord. Tu commenceras ta plongée depuis la plateforme du 'Phoenix', tu peux y accéder depuis la poupe du San Gabriel. Il y a un treuil qui te mènera au fond et te ramènera. C'est la seule façon de revenir.\nAlors tu ferais mieux de te souvenir de l'emplacement du treuil sous l'eau et de ne pas te perdre. Les réservoirs de la combinaison ont assez d'air pour vingt minutes de plongée. Surveille ton temps ou tu vas suffoquer.\nNe t'éloigne pas trop du treuil ou tu ne pourras pas revenir à temps et que Dieu te garde si tu quittes notre banc - tu seras aplati comme une sole.\nSois prudent et fais attention aux crabes. Si tu t'approches trop près, ils t'attaqueront. Ne prends pas de risques si tu n'y es pas obligé, tu ne pourras pas tuer tout un groupe d'entre eux et fuir rapidement n'est pas une option là-bas.";
			link.l1 = "Je m'occuperai des crabes. J'ai le reste. Ne plonge pas plus profondément, ne t'éloigne pas trop du treuil et n'oublie pas le temps. Quand puis-je plonger ?";
			link.l1.go = "immersion_2";
		break;
		
		case "immersion_2":
			dialog.text = "Quand tu veux, mais seulement de 7 heures à 21 heures. Tu ne verras rien dans l'obscurité.";
			link.l1 = "Compris.";
			link.l1.go = "immersion_4";
		break;
		
		case "immersion_4":
			dialog.text = "Voilà le truc. Prends la combinaison dans la chambre sur la plateforme. Enlève-la après une plongée et apporte-la moi. Je la remplirai à nouveau d'air. Mais ne tente pas de plonger plus d'une fois par jour, même 20 minutes de plongée et respirer de l'air comprimé est mauvais pour ta santé.";
			link.l1 = "Eh bien, je ne plongerai pas plus d'une fois par jour alors.";
			link.l1.go = "immersion_5";
		break;
		
		case "immersion_5":
			dialog.text = "Je suis heureux que vous compreniez. Maintenant, allez et bonne chance !";
			link.l1 = "Merci !";
			link.l1.go = "immersion_6";
		break;
		
		case "immersion_6":
			DialogExit();
			pchar.questTemp.LSC = "first_immersion"; // флаг на первое погружение
			pchar.questTemp.LSC.immersion = "true"; // погружение возможно
			pchar.quest.LSC_takeUnderwater.win_condition.l1 = "locator";
			pchar.quest.LSC_takeUnderwater.win_condition.l1.location = "FenixPlatform";
			pchar.quest.LSC_takeUnderwater.win_condition.l1.locator_group = "item";
			pchar.quest.LSC_takeUnderwater.win_condition.l1.locator = "armor";
			pchar.quest.LSC_takeUnderwater.function = "LSC_takeUnderwater"; // выдача костюма
			pchar.quest.LSC_UnderwaterDolly.win_condition.l1 = "locator";
			pchar.quest.LSC_UnderwaterDolly.win_condition.l1.location = "Underwater";
			pchar.quest.LSC_UnderwaterDolly.win_condition.l1.locator_group = "quest";
			pchar.quest.LSC_UnderwaterDolly.win_condition.l1.locator = "dolly";
			pchar.quest.LSC_UnderwaterDolly.function = "LSC_FindUnderwaterDolly"; // нашли статую
			NextDiag.CurrentNode = "after_first_immersion"; // нода после первого погружения
			AddQuestRecord("LSC", "11");
			QuestPointerToLoc("UnderWater", "quest", "dolly");
		break;
		
		case "after_first_immersion":
			if (CheckAttribute(pchar, "questTemp.LSC.immersion"))
			{
				dialog.text = "Alors, pourquoi es-tu encore ici ? Le costume t'attend.";
				link.l1 = "Oui, oui. Je suis en route.";
				link.l1.go = "exit";
			}
			else
			{
				dialog.text = "Alors, comment s'est passée la première plongée ?";
				if (CheckAttribute(pchar, "questTemp.LSC.FindDolly"))
				{
					link.l1 = "Très bien et je suis satisfait des résultats. J'ai trouvé une idole de pierre dans le galion englouti. J'ai entendu dire que les Rivados avaient fait des offrandes sacrificielles à celle-ci auparavant. Dis-moi, Henrik, connais-tu quelqu'un qui pourrait m'en dire plus à ce sujet ?";
					link.l1.go = "af_immersion_1";
				}
				else
				{
					link.l1 = "D'accord. Je l'ai fait ! C'était vraiment intéressant, bien que légèrement palpitant.";
					link.l1.go = "af_immersion_2";
				}
			}
			NextDiag.TempNode = "after_first_immersion";
		break;
		
		case "af_immersion_1":
			dialog.text = "Tu es intéressé par notre histoire ? Va voir Antonio Betancourt. Il est né ici. Il vit sur la flûte Pluto. S'il n'en sait rien, personne ne le sait.";
			link.l1 = "Excellent ! Je lui rendrai certainement visite.";
			link.l1.go = "af_immersion_2";
			pchar.questTemp.LSC.Betancur = "true";
			AddQuestRecord("LSC", "14");
		break;
		
		case "af_immersion_2":
			dialog.text = "Laisse le costume ici. Reviens demain ou un autre jour, je vais le remplir d'air.";
			if (CheckCharacterItem(pchar, "underwater"))
			{
				link.l1 = "Bien sûr. Voici votre habit. Merci !";
				link.l1.go = "af_immersion_3";
			}
			else
			{
				link.l1 = "Bien sûr. Je l'apporterai tout de suite !";
				link.l1.go = "af_immersion_wait";
			}
		break;
		
		case "af_immersion_wait":
			dialog.text = "Eh bien, m'avez-vous apporté mon équipement ?";
			if (CheckCharacterItem(pchar, "underwater"))
			{
				link.l1 = "Bien sûr. Voici votre costume. Merci !";
				link.l1.go = "af_immersion_3";
			}
			else
			{
				link.l1 = "Je le ferai sur-le-champ !";
				link.l1.go = "exit";
			}
			NextDiag.TempNode = "af_immersion_wait";
		break;
		
		case "af_immersion_3":
			DialogExit();
			RemoveCharacterEquip(pchar, CIRASS_ITEM_TYPE);
			RemoveItems(pchar, "underwater", 1);
			LocatorReloadEnterDisable("SanGabrielMechanic", "reload3", false);
			SetFunctionTimerCondition("LSC_ReadyUnderwater", 0, 0, 1, false);
			NextDiag.CurrentNode = "First time";
			// даем старт мини-квестам с крабикусами
			sld = characterFromId("Carpentero");
			if(!CheckAttribute(sld, "quest.crab")) sld.quest.crab = "begin";
			if (GetCharacterIndex("LSC_Jacklin") != -1)
			{
				sld = characterFromId("LSC_Jacklin");
				sld.quest.crab = "true";
			}
		break;
		
		// блок погружений, за искл. первого
		case "immersion_next":
			if (CheckAttribute(npchar, "quest.guarantee")) // требует залог
			{
				dialog.text = "Oui, bien sûr. Le costume a été testé et rempli d'air. Avez-vous le gage avec vous ? 500 000 pesos ?";
				if (int(pchar.money) >= 500000)
				{
					link.l1 = "Oui, bien sûr. Tenez, prenez-le.";
					link.l1.go = "immersion_next_pay";
				}
				else
				{
					link.l1 = "Oups ! Je l'ai oublié. Je vais l'apporter tout de suite...";
					link.l1.go = "exit";
				}
			}
			else
			{
				dialog.text = "Oui, bien sûr. Le costume a été testé et rempli d'air. Vérifie la plateforme 'Phoenix' comme toujours.";
				link.l1 = "Alors je plongerai. Merci !";
				link.l1.go = "immersion_next_1";
			}
		break;
		
		case "immersion_next_1":
			DialogExit();
			DeleteAttribute(pchar, "questTemp.LSC.UW_ready"); 
			LocatorReloadEnterDisable("LostShipsCity_town", "reload72", false); //открываем вход в Феникс
			pchar.questTemp.LSC.immersion = "true"; // погружение возможно
			pchar.quest.LSC_takeUnderwater.win_condition.l1 = "locator";
			pchar.quest.LSC_takeUnderwater.win_condition.l1.location = "FenixPlatform";
			pchar.quest.LSC_takeUnderwater.win_condition.l1.locator_group = "item";
			pchar.quest.LSC_takeUnderwater.win_condition.l1.locator = "armor";
			pchar.quest.LSC_takeUnderwater.function = "LSC_takeUnderwater"; // выдача костюма
		break;
		
		case "immersion_next_2":
			dialog.text = "Très bien. Revenez demain ou plus tard. Je vais préparer le costume.";
			link.l1 = "Merci, Mécanicien !";
			link.l1.go = "immersion_next_3";
		break;
		
		case "immersion_next_3":
			DialogExit();
			DeleteAttribute(pchar, "questTemp.LSC.UW_end"); 
			RemoveCharacterEquip(pchar, CIRASS_ITEM_TYPE);
			RemoveItems(pchar, "underwater", 1);
			if (CheckAttribute(npchar, "quest.guarantee")) AddMoneyToCharacter(pchar, 500000); // возврат залога
			LocatorReloadEnterDisable("SanGabrielMechanic", "reload3", false);
			SetFunctionTimerCondition("LSC_ReadyUnderwater", 0, 0, 1, false);
		break;
		
		case "immersion_next_pay":
			AddMoneyToCharacter(pchar, -500000);
			dialog.text = "Tu récupéreras ton argent quand tu rendras le costume. Marché équitable.";
			link.l1 = "Merci, Mécanicien ! Je vais plonger maintenant.";
			link.l1.go = "immersion_next_1";
		break;
		// блок погружений
		
	//--------------------------------------вернулся на Остров---------------------------------------------
		case "return":
			dialog.text = "Attendez une seconde s'il vous plaît ! Quelle statue ? A-ah, je comprends maintenant. Vous parlez de cet idole dans le navire coulé 'San-Geronimo', n'est-ce pas ? Alors ces histoires de Rivados sont vraies ?";
			link.l1 = "Exactement ! Et il n'y a pas de contes. Je connais deux autres idoles dans l'archipel qui téléportent les gens qui les touchent de l'une à l'autre, en cercle.";
			link.l1.go = "return_1";
		break;
		
		case "return_1":
			dialog.text = "Je vois, je vois. Je devrai te faire confiance, bien que tes paroles soient du charabia anti-scientifique. Téléporteurs, statues... ha ! Et qui pourrait même y penser, comment de telles choses fonctionnent-elles ?";
			link.l1 = "Faites-moi confiance et ne cherchez pas de logique ici. Je ne mens pas.";
			link.l1.go = "return_2";
		break;
		
		case "return_2":
			dialog.text = "D'accord. Mais j'espère que tu n'as pas perdu ton costume pendant cette téléportation?";
			if(CheckCharacterItem(pchar, "underwater"))
			{
				link.l1 = "Bien sûr, je ne l'ai pas fait. Cela m'a sauvé des Caraïbes, pour ainsi dire. Le voici.";
				link.l1.go = "return_4";
			}
			else
			{
				link.l1 = "Bien sûr, je ne l'ai pas fait. Il m'a sauvé des Caribs pour ainsi dire. Mais je ne l'ai pas avec moi maintenant.";
				link.l1.go = "return_3";
			}
		break;
		
		case "return_3":
			dialog.text = "Alors apporte-le-moi, bon sang ! Nous ne parlerons pas tant que tu ne me l'auras pas rendu, sache-le !";
			link.l1 = "Calme-toi, Mécanicien. Je te le rendrai !";
			link.l1.go = "exit";
			NextDiag.TempNode = "return_underwater";
		break;
		
		case "return_underwater":
			if(CheckCharacterItem(pchar, "underwater"))
			{
				dialog.text = "Ah, tu as vraiment apporté mon costume ! Merci, j'ai commencé à m'inquiéter à ce sujet.";
				link.l1 = "Il n'y avait pas lieu de s'en inquiéter. Je vous ai promis de le rendre.";
				link.l1.go = "return_4";
			}
			else
			{
				dialog.text = "N'approche même pas ici tant que tu n'as pas mon costume.";
				link.l1 = "D'accord, d'accord.";
				link.l1.go = "exit";
			}
			NextDiag.TempNode = "return_underwater";
		break;
		
		case "return_4":
			DeleteAttribute(pchar, "questTemp.LSC.UW_end"); 
			RemoveCharacterEquip(pchar, CIRASS_ITEM_TYPE);
			RemoveItems(pchar, "underwater", 1);
			SetFunctionTimerCondition("LSC_ReadyUnderwater", 0, 0, 1, false);
			dialog.text = "Très bien. J'ai commencé à réfléchir à en fabriquer un nouveau, mais ce serait un travail d'au moins un an... Je suis heureux que vous ayez fait preuve d'une belle économie et que vous ayez rendu ma propriété en un seul morceau. Je vais même vous offrir un cadeau.";
			link.l1 = "Es-tu sérieux ?";
			link.l1.go = "return_5";
		break;
		
		case "return_5":
			dialog.text = "Bien sûr, je le suis ! Tu m'as aidé à réparer la combinaison et tu ne l'as pas jetée à la première occasion. Tu en as pris soin et finalement, tu me l'as rendue. Quoi qu'il en soit, voici une belle boîte à outils. Apprends à t'en servir. Tu pourras fabriquer beaucoup de choses utiles avec son aide.";
			link.l1 = "Et que pouvais-je attendre d'autre du Mécanicien ! Bien sûr, la boîte à outils ! Merci beaucoup, Henrik, je suis touché... Je ne méritais pas un tel cadeau.";
			link.l1.go = "return_6";
		break;
		
		case "return_6":
			GiveItem2Character(pchar, "mechanic_tool");
			Log_Info("You have received a toolbox");
			PlaySound("interface\important_item.wav");
			dialog.text = "Je sais mieux ce que tu méritais et ce que tu ne méritais pas. Prends-le ! Cela te sera utile. Mais je te donnerai à nouveau le costume uniquement si tu engages 500 000 pesos à cause de ton habitude de te téléporter via des idoles.";
			link.l1 = "Ouah ! Eh bien, je comprends cela... les mesures de précaution...";
			link.l1.go = "return_7";
		break;
		
		case "return_7":
			dialog.text = "Bien sûr. Et si un jour tu t'échappes avec ? Alors l'argent sera ma compensation.";
			link.l1 = "Très bien, Henrick. Je suis d'accord. Pour être honnête, je pensais que tu ne me le donnerais plus jamais.";
			link.l1.go = "return_8";
		break;
		
		case "return_8":
			dialog.text = "Pas question. Promets une demi-million et c'est tout à toi.";
			link.l1 = "Marché conclu ! Puis-je l'emporter comme d'habitude pour plonger alors ? Dès demain ?";
			link.l1.go = "return_9";
		break;
		
		case "return_9":
			dialog.text = "Exactement.";
			link.l1 = "Merci ! À bientôt, Henrik !";
			link.l1.go = "return_10";
		break;
		
		case "return_10":
			DialogExit();
			AddQuestRecord("LSC", "26");
			npchar.quest.return_isl = "true";
			npchar.quest.guarantee = "true"; // залог за скафандр
			NextDiag.CurrentNode = "First time";
		break;
//----------------------------------------- специальные реакции -----------------------------------------------
		//обнаружение ГГ в сундуках
		case "Man_FackYou":
			dialog.text = LinkRandPhrase("Que fais-tu là, hein ? Voleur !","Regarde-moi ça ! À peine étais-je perdu dans mes pensées que tu as décidé de fouiller mon coffre !","Décidé à fouiller mes coffres ? Tu ne t'en sortiras pas comme ça !");
			link.l1 = "Sacrebleu !";
			link.l1.go = "fight";
		break;
		
		case "Woman_FackYou":
			dialog.text = "Quoi ?! Tu as décidé de fouiller dans mes coffres ? Tu ne t'en sortiras pas comme ça !";
			link.l1 = "Folle fille !...";
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
			dialog.text = LinkRandPhrase("Écoute, tu ferais mieux de ranger ton arme. Ça me rend nerveux.","Tu sais, courir avec une lame n'est pas toléré ici. Range-la.","Écoute, ne fais pas le chevalier médiéval courant avec une épée. Range-la, cela ne te va pas...");
			link.l1 = LinkRandPhrase("Bien.","Bien sûr.","Comme vous dites...");
			link.l1.go = "exit";
			NextDiag.TempNode = "First Time";
		break;	
		
		case "CitizenNotBlade":
			if (loadedLocation.type == "town")
			{
				dialog.text = NPCharSexPhrase(NPChar,"Écoutez, je suis citoyen de la ville et je vous demanderais de rengainer votre lame.","Ecoute, je suis citoyen de la ville et je te demanderais de rengainer ta lame");
				link.l1 = LinkRandPhrase("Bien.","D'accord.","Comme vous le dites...");
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
