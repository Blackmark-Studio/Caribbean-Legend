#include "DIALOGS\%language%\Rumours\Common_rumours.c" //Jason
// Jason общий диалог смотрителей маяков
void ProcessDialogEvent()
{
	ref NPChar;
	aref Link, NextDiag;	

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

    // вызов диалога по городам -->
    NPChar.FileDialog2 = "DIALOGS\" + LanguageGetLanguage() + "\Lighthouse\" + NPChar.City + "_Lighthouse.c";
    if (LoadSegment(NPChar.FileDialog2))
	{
        ProcessCommonDialog(NPChar, Link, NextDiag);
		UnloadSegment(NPChar.FileDialog2);
	}
    // вызов диалога по городам <--
	ProcessCommonDialogRumors(NPChar, Link, NextDiag);
	
    int iTest, iTemp;
	string sTemp;
	bool ok;
    iTest = FindColony(NPChar.City); // город
    ref rColony;
	if (iTest != -1)
	{
		rColony = GetColonyByIndex(iTest);
	}
	switch(Dialog.CurrentNode)
	{
		case "First time":
			if (LAi_grp_playeralarm > 0)
			{
       			dialog.text = PCharRepPhrase(LinkRandPhrase("L'alarme est donnée dans la ville. Apparemment, il est temps pour moi aussi de prendre les armes...","Les gardes de la ville ne te courent pas après, par hasard?","Tu ne trouveras pas un abri ici, mais tu pourrais trouver plusieurs pouces d'acier froid sous ta côte!"),LinkRandPhrase("De quoi as-tu besoin, "+GetSexPhrase("canaille","coquin")+"?! Les gardes vous traquent, vous n'irez pas loin, "+GetSexPhrase("sale pirate","puant")+"!",""+GetSexPhrase("Crade","Sale")+" assassin! Gardes!!!","Je ne te crains pas, "+GetSexPhrase("vermine","puant")+"! Bientôt tu seras pendu dans notre fort, tu n'iras pas loin..."));
				link.l1 = PCharRepPhrase(RandPhraseSimple("Je vois que tu es fatigué de vivre...","Alors il semble, il n'y a pas de gens pacifiques dans "+XI_ConvertString("Colonie"+npchar.city+"Gen")+", tout le monde veut être un héros !"),RandPhraseSimple("Va en enfer !","Heh, ce seront les dernières secondes de ta vie..."));
				link.l1.go = PCharRepPhrase("exit_setOwner", "fight");
				break;
			}
			//belamour legendary edtion карибские нравы
			if(npchar.quest.meeting != "0" && CheckAttribute(npchar, "quest.trial_usurer"))
			{
				dialog.text = "Qu'est-ce qui vous amène à moi cette fois?";
				link.l1 = "Je crois que vous connaissez un monsieur nommé Gerard LeCroix? Il aurait dû laisser une récompense pour moi...";
				link.l1.go = "Trial";
				DelLandQuestMark(npchar);
				break;
			}
			// <-- legendary edition
			if (npchar.quest.meeting == "0")
			{
				dialog.text = RandPhraseSimple("Bon après-midi, marin! Mon nom est "+GetFullName(npchar)+", et je suis le gardien de ce phare. Quel vent vous a amené ici?","Salut ! Cela fait un bon moment depuis la dernière fois que j'ai vu de nouveaux visages à mon phare... Permettez-moi de me présenter - "+GetFullName(npchar)+", et ce phare est ma maison et mon travail. Que puis-je faire pour vous?");
				link.l1 = "Bonjour là, "+npchar.name+"! Mon nom est "+GetFullName(pchar)+", je suis un capitaine de navire. Je me promenais autour de cette merveilleuse crique et j'ai décidé de m'arrêter pour voir qui y habite.";
				link.l1.go = "Lightman_meeting";
				npchar.quest.meeting = "1";
			}
			else
			{
				dialog.text = "Oh, mon vieil ami, capitaine "+GetFullName(pchar)+"! Entrez, entrez ! Qu'est-ce qui vous amène ici cette fois ?";
				link.l1 = "Salut à toi, vieux loup de mer ! Ne te lamentes-tu pas dans la solitude ici à ton phare ?";
				link.l1.go = "Lightman_talk";
			}
			NextDiag.TempNode = "First time";
		break;
		
		case "Lightman_meeting":
			dialog.text = "Maintenant tu sais. J'étais un marin, tout comme toi, mais cela fait longtemps que je n'ai pas mis le pied sur le pont d'un navire. Maintenant, ce phare est sous ma garde, et je vends aussi quelques trucs...";
			link.l1 = "Et qu'est-ce que vous vendez exactement?";
			link.l1.go = "trade_info";
			NextDiag.TempNode = "First time";
		break;
		
		case "Lightman_talk":
			dialog.text = "Qu'est-ce qui vous amène ici cette fois-ci?";
			link.l1 = RandPhraseSimple("Pouvez-vous me dire si quelque chose d'intéressant s'est récemment passé dans votre colonie?","Je n'ai pas mis pied à terre depuis un bon bout de temps... Que se passe-t-il ici?");
			link.l1.go = "rumours_lighthouse";
			link.l2 = "Voyons ce que vous avez à vendre.";
			link.l2.go = "Trade_lighthouse";
			if (CheckAttribute(npchar, "artefact"))
			{
				if (CheckAttribute(npchar, "quest.art"))
				{
					link.l3 = "Alors, "+npchar.name+", mon amulette est-elle déjà arrivée?";
					link.l3.go = "Trade_artefact_3";
				}
				else
				{
					link.l3 = ""+npchar.name+", je veux commander un amulet de toi.";
					link.l3.go = "Trade_artefact_1";
				}
				// калеуче
				if (CheckAttribute(pchar, "questTemp.Caleuche") && pchar.questTemp.Caleuche == "amulet" && !CheckAttribute(npchar, "quest.Caleuche"))
				{
					link.l5 = "Écoute, "+npchar.name+", Je sais que vous vous engagez dans la livraison d'amulettes sur commande. Alors, vous devez certainement en savoir beaucoup à leur sujet. Regardez, s'il vous plaît, ce petit truc - que pouvez-vous me dire à son sujet?";
					link.l5.go = "Caleuche";
				}
				if (npchar.id == pchar.questTemp.Caleuche.Amuletmaster && CheckAttribute(pchar, "questTemp.Caleuche") && pchar.questTemp.Caleuche == "mayak")
				{
					link.l5 = "Mon ami, je suis ici encore une fois pour te demander au sujet de ces amulettes étranges";
					link.l5.go = "Caleuche_9";
				}
			}
			link.l4 = "Il y a quelque chose que je voulais te demander...";
			link.l4.go = "quests";
			link.l9 = "Je viens de jeter un coup d'oeil...";
			link.l9.go = "exit";
			NextDiag.TempNode = "First time";
		break;
		
		case "trade_info":
			dialog.text = "Parfois, je vais sur le rivage et je ramasse des coquillages, il y a un joli endroit non loin d'ici, alors vous pouvez toujours m'acheter des perles. Chaque tempête apporte de l'ambre, je le vends aussi, bien que cela vous coûtera cher.\nParfois, les vagues apportent toutes sortes de bibelots intéressants des navires coulés et mes vieux copains m'apportent des objets spéciaux. Les amulettes enchantées m'intéressent, les sages paient une bonne pièce pour cela.\nJ'offre aussi des armes à l'occasion, ne me demandez pas d'où je les sors. Un marchand de la ville achète toute la camelote, je vends moi-même les bonnes choses après les avoir réparées et nettoyées.\nJe suis intéressé par le rhum. Je ne parle pas de la pisse qu'ils servent dans la taverne locale pour deux pesos la chope. Je parle du vrai rhum jamaïcain en bouteille. Il guérit et ressuscite les gens. Je paierai dix fois plus pour chaque bouteille que vous apportez. Pensez-y.";
			link.l1 = "Ecoute, "+npchar.name+", vous avez dit que vous aviez des vieux amis marins, qui vous apportent des amulettes ensorcelées. Est-il possible de commander une certaine amulette de vous? Je la paierai grassement.";
			link.l1.go = "Trade_artefact";
		break;
		
		case "Trade_lighthouse":
			//иногда продает корабельные товары // Addon-2016 Jason
			npchar.quest.goods = GOOD_COFFEE + hrand(sti(GOOD_PAPRIKA - GOOD_COFFEE));
			npchar.quest.goodsqty = 50+hrand(100);
			if (sti(npchar.quest.goods) == GOOD_EBONY || sti(npchar.quest.goods) == GOOD_MAHOGANY) npchar.quest.goodsqty = 25+hrand(50);
			npchar.quest.goodsprice = makeint(sti(Goods[sti(npchar.quest.goods)].Cost)/4);//цена единицы товара
			npchar.quest.goodscost = sti(npchar.quest.goodsprice)*sti(npchar.quest.goodsqty);//стоимость товара
			ok = (!CheckAttribute(npchar, "goods_date")) || (GetNpcQuestPastDayParam(npchar, "goods_date") >= 10)
			if (hrand(4) == 1 && makeint(GetCharacterFreeSpace(pchar, sti(npchar.quest.goods))) > sti(npchar.quest.goodsqty) && sti(pchar.money) >= sti(npchar.quest.goodscost) && ok)
			{
				dialog.text = "Capitaine, une quantité de marchandises a récemment été échouée sur le rivage - "+GetGoodsNameAlt(sti(npchar.quest.goods))+". Certaines parties ont été gâtées par l'eau salée, mais "+FindRussianQtyString(sti(npchar.quest.goodsqty))+" J'ai réussi à sauver en bon état. Tu veux en acheter ? Je les donnerai à bas prix, juste pour "+FindRussianMoneyString(sti(npchar.quest.goodsprice))+" par unité.";
				link.l1 = "Non. Montrez-moi vos récentes trouvailles.";
				link.l1.go = "Trade_lighthouse_double";
				link.l2 = "Hm... Une offre honnête, je suis d'accord. Je suppose que je pourrais le revendre pour réaliser un certain bénéfice. Voyons voir... Cela s'élèvera à "+FindRussianMoneyString(sti(npchar.quest.goodscost))+". Est-ce correct ?";
				link.l2.go = "Trade_goods";
				SaveCurrentNpcQuestDateParam(npchar, "goods_date");
			}
			else
			{
				DialogExit();
				if (!CheckAttribute(npchar, "trade_date") || GetNpcQuestPastDayParam(npchar, "trade_date") >= 10)
				{
					GiveItemToTrader(npchar);
					SaveCurrentNpcQuestDateParam(npchar, "trade_date");
				}
				LaunchItemsTrade(npchar, 0);
			}
		break;
		
		case "Trade_lighthouse_double":
			DialogExit();
			if (!CheckAttribute(npchar, "trade_date") || GetNpcQuestPastDayParam(npchar, "trade_date") >= 10)
			{
				GiveItemToTrader(npchar);
				SaveCurrentNpcQuestDateParam(npchar, "trade_date");
			}
			LaunchItemsTrade(npchar, 0);
		break;
		
		case "Trade_goods":
			AddCharacterGoods(pchar, sti(npchar.quest.goods), sti(npchar.quest.goodsqty));
			AddMoneyToCharacter(pchar, -sti(npchar.quest.goodscost));
			AddMoneyToCharacter(npchar, sti(npchar.quest.goodscost));
			dialog.text = "Vous avez bien compris, capitaine. Une excellente affaire ! Nous avons tous deux fait un bon profit...";
			link.l1 = "D'accord, alors. J'enverrai les marins prendre la cargaison pour mon navire. Montrez-moi maintenant ce que vous avez rassemblé à vendre.";
			link.l1.go = "Trade_lighthouse_double";
		break;
//------------------------------------------------заказ артефактов------------------------------------------------
		case "Trade_artefact":
			if (CheckAttribute(npchar, "artefact")) // Addon-2016 Jason за дублоны
			{
				dialog.text = "Eh bien, pas tous, mais certains bibelots sont apportés plus fréquemment que d'autres, donc je suppose que je pourrais vous aider. Mais je vous préviens: tous les amulettes commandées de cette façon vous coûteront 100 doubloons. Vous devriez comprendre...";
				link.l1 = "Le prix n'est pas un problème. Quels amulettes pouvez-vous livrer?";
				link.l1.go = "Trade_artefact_1";
				link.l2 = "Pff ! On pourrait acheter un navire avec ce genre d'argent. C'est trop cher. Je suppose que je m'en sortirai bien tout seul...";
				link.l2.go = "exit_artefact";
			}
			else
			{
				dialog.text = "Non, capitaine. De telles choses ne peuvent être trouvées que par hasard, il est donc impossible de les commander à l'avance. Et aussi, vous devriez attendre un peu moins que l'éternité...";
				link.l1 = "Eh bien, si c'est le cas, il n'y a rien à faire.";
				link.l1.go = "exit_artefact";
			}
		break;
		
		case "exit_artefact":
			if (CheckAttribute(npchar, "artefact")) dialog.text = "Comme vous voulez. Venez me voir si vous changez d'avis.";
			else dialog.text = "Voulez-vous voir ce que j'ai à vendre aujourd'hui, capitaine? Si vous ne trouvez rien de digne, revenez bientôt - je pourrais avoir autre chose à vendre.";
			// belamour legendary edition карибские нравы -->
			if(CheckAttribute(npchar, "quest.trial_usurer"))
			{
				link.l1 = "Tout cela, bien sûr, est bon, mais voici ce que je voulais demander - je suppose que vous connaissez un monsieur nommé Gerard Lecroix? Il devrait avoir laissé une récompense pour moi...";
				link.l1.go = "Trial";
				DelLandQuestMark(npchar);
				break;
			}
			// <-- legendary edition
			link.l1 = "Montre-moi tes objets.";
			link.l1.go = "Trade_lighthouse";
			link.l2 = "Dites-moi, quels événements intéressants se sont produits dans votre colonie récemment ?";
			link.l2.go = "rumours_lighthouse";
			link.l3 = "Le commerce est le commerce, mais je voulais demander quelque chose.";
			link.l3.go = "quests";
			link.l4 = "Passez une bonne journée, "+npchar.name+"! C'était un plaisir de vous rencontrer! Je passerai une autre fois...";
			link.l4.go = "exit";
		break;
		
		case "Trade_artefact_1":
			dialog.text = "Faites votre choix.";
			iTemp = 1;
			string sArt;
			if (CheckAttribute(npchar, "artefact.indian")) sArt = "indian_";
			if (CheckAttribute(npchar, "artefact.amulet")) sArt = "amulet_";
			if (CheckAttribute(npchar, "artefact.obereg")) sArt = "obereg_";
			for (i=11; i>=1; i--)
			{
				sTemp = "l"+iTemp;
				link.(sTemp) = XI_ConvertString(sArt+i);
				link.(sTemp).go = sArt+i;
				iTemp++;
			}
			link.l12 = "Désolé, rien de cette liste ne m'intéresse pour l'instant.";
			link.l12.go = "exit";
		break;
		
		//группа indian
		case "indian_1":
			dialog.text = "Une poupée vaudou? Tu aimes les armes à feu? Bien...";
			link.l1 = "Quand devrais-je revenir pour récupérer ma commande?";
			link.l1.go = "Trade_artefact_2";
			npchar.quest.art = "indian_1";
		break;
		
		case "indian_2":
			dialog.text = "Un testeur de poudre à canon? Le tir précis est la clé du succès dans n'importe quelle escarmouche. Sympa...";
			link.l1 = "Quand devrais-je revenir pour récupérer ma commande?";
			link.l1.go = "Trade_artefact_2";
			npchar.quest.art = "indian_2";
		break;
		
		case "indian_3":
			dialog.text = "Un couteau rituel ? Tu aimes trancher tes ennemis avec de puissants coups d'une lourde épée large ? C'est pour toi, alors. Bien... ";
			link.l1 = "Quand devrais-je revenir pour récupérer ma commande?";
			link.l1.go = "Trade_artefact_2";
			npchar.quest.art = "indian_3";
		break;
		
		case "indian_4":
			dialog.text = "Une hache d'armes? Un coup descendant d'une énorme hache écrasera tout ennemi! Bon...";
			link.l1 = "Quand devrais-je revenir pour récupérer ma commande?";
			link.l1.go = "Trade_artefact_2";
			npchar.quest.art = "indian_4";
		break;
		
		case "indian_5":
			dialog.text = "Une tsantsa? Maintenant, cette chose peut effrayer même le pirate le plus insouciant. Bon...";
			link.l1 = "Quand devrais-je revenir pour récupérer ma commande?";
			link.l1.go = "Trade_artefact_2";
			npchar.quest.art = "indian_5";
		break;
		
		case "indian_6":
			dialog.text = "Un récif de corail? Le mitraillage de tes canons volera droit vers la cible! Bien...";
			link.l1 = "Quand devrais-je revenir chercher ma commande?";
			link.l1.go = "Trade_artefact_2";
			npchar.quest.art = "indian_6";
		break;
		
		case "indian_7":
			dialog.text = "Bosse? L'endurance est le meilleur ami du guerrier. Bien...";
			link.l1 = "Quand devrais-je revenir pour récupérer ma commande?";
			link.l1.go = "Trade_artefact_2";
			npchar.quest.art = "indian_7";
		break;
		
		case "indian_8":
			dialog.text = "Xiuhtecuhtli? Que la coque du navire ennemi se désintègre en poussière! Bien...";
			link.l1 = "Quand devrais-je revenir chercher ma commande?";
			link.l1.go = "Trade_artefact_2";
			npchar.quest.art = "indian_8";
		break;
		
		case "indian_9":
			dialog.text = "Baldo? Mettez Baldo et tous les boulets de canon voleront droit sur la cible! Bon...";
			link.l1 = "Quand devrais-je revenir pour récupérer ma commande?";
			link.l1.go = "Trade_artefact_2";
			npchar.quest.art = "indian_9";
		break;
		
		case "indian_10":
			dialog.text = "Cascavella? Le venin de serpent est la chose la plus dangereuse. Bon...";
			link.l1 = "Quand devrais-je revenir chercher ma commande?";
			link.l1.go = "Trade_artefact_2";
			npchar.quest.art = "indian_10";
		break;
		
		case "indian_11":
			dialog.text = "Masque de Ngombo? Baisse la vigilance de tes ennemis, ha-ha! Bien...";
			link.l1 = "Quand devrais-je revenir pour récupérer ma commande ?";
			link.l1.go = "Trade_artefact_2";
			npchar.quest.art = "indian_11";
		break;
		
		//группа amulet
		case "amulet_1":
			dialog.text = "Bouclier Ngombo? Si tu n'as pas réussi à esquiver une balle, cet amulette peut sauver ta vie. Bon...";
			link.l1 = "Quand devrais-je revenir pour récupérer ma commande ?";
			link.l1.go = "Trade_artefact_2";
			npchar.quest.art = "amulet_1";
		break;
		
		case "amulet_2":
			dialog.text = "Euchologion? Une bonne prière peut même dévier une balle. Bien...";
			link.l1 = "Quand devrais-je revenir pour récupérer ma commande?";
			link.l1.go = "Trade_artefact_2";
			npchar.quest.art = "amulet_2";
		break;
		
		case "amulet_3":
			dialog.text = "Un crucifix? Celui-ci aidera grandement un Chrétien dans un combat rapproché. Bon...";
			link.l1 = "Quand devrais-je revenir pour chercher ma commande?";
			link.l1.go = "Trade_artefact_2";
			npchar.quest.art = "amulet_3";
		break;
		
		case "amulet_4":
			dialog.text = "El Trozo? Celui-ci transformera une blessure mortelle en simple égratignure. Bien...";
			link.l1 = "Quand devrais-je revenir pour récupérer ma commande?";
			link.l1.go = "Trade_artefact_2";
			npchar.quest.art = "amulet_4";
		break;
		
		case "amulet_5":
			dialog.text = "Sogbo? Et que les canons soient toujours prets pour la bataille! Bon...";
			link.l1 = "Quand devrais-je revenir chercher ma commande ?";
			link.l1.go = "Trade_artefact_2";
			npchar.quest.art = "amulet_5";
		break;
		
		case "amulet_6":
			dialog.text = "Madonna? Le visage de la Très Sainte Vierge possède de puissantes propriétés curatives. Bon...";
			link.l1 = "Quand devrais-je revenir chercher ma commande?";
			link.l1.go = "Trade_artefact_2";
			npchar.quest.art = "amulet_6";
		break;
		
		case "amulet_7":
			dialog.text = "Eau bénite? Même un faible arrosé d'eau bénite deviendra un héros épique! Bon...";
			link.l1 = "Quand devrais-je revenir chercher ma commande?";
			link.l1.go = "Trade_artefact_2";
			npchar.quest.art = "amulet_7";
		break;
		
		case "amulet_8":
			dialog.text = "Une ancre? Et que votre navire reste à flot même sous une volée de boulets de canon, ha-ha! Bien...";
			link.l1 = "Quand devrais-je revenir chercher ma commande ?";
			link.l1.go = "Trade_artefact_2";
			npchar.quest.art = "amulet_8";
		break;
		
		case "amulet_9":
			dialog.text = "Encolpion? Vos voiles ne craindront aucun vent, tant que vous possédez cet amulet. Bien...";
			link.l1 = "Quand devrais-je revenir pour récupérer ma commande?";
			link.l1.go = "Trade_artefact_2";
			npchar.quest.art = "amulet_9";
		break;
		
		case "amulet_10":
			dialog.text = "Miracle? Que le Seigneur veille sur ton équipage à terre et en mer! Bien...";
			link.l1 = "Quand devrais-je revenir chercher ma commande ?";
			link.l1.go = "Trade_artefact_2";
			npchar.quest.art = "amulet_10";
		break;
		
		case "amulet_11":
			dialog.text = "Cimaruta ? Les balles de mousquet voleront au-dessus de votre tête, ne causant aucun mal ! Bon...";
			link.l1 = "Quand devrais-je revenir chercher ma commande?";
			link.l1.go = "Trade_artefact_2";
			npchar.quest.art = "amulet_11";
		break;
		
		//группа obereg
		case "obereg_1":
			dialog.text = "Teredo ? Chaque charpentier de marine rêve de celui-ci. Bon ...";
			link.l1 = "Quand devrais-je revenir chercher ma commande?";
			link.l1.go = "Trade_artefact_2";
			npchar.quest.art = "obereg_1";
		break;
		
		case "obereg_2":
			dialog.text = "Xochipilli? Cela économisera du temps à raccommoder les voiles. Bien...";
			link.l1 = "Quand devrais-je revenir chercher ma commande ?";
			link.l1.go = "Trade_artefact_2";
			npchar.quest.art = "obereg_2";
		break;
		
		case "obereg_3":
			dialog.text = "Un singe? Un mulet de bât, je dirais! Bien...";
			link.l1 = "Quand devrais-je revenir pour récupérer ma commande?";
			link.l1.go = "Trade_artefact_2";
			npchar.quest.art = "obereg_3";
		break;
		
		case "obereg_4":
			dialog.text = "Éventail de gitane? Mets des oeillères aux yeux d'un patrouilleur! Bien...";
			link.l1 = "Quand devrais-je revenir pour récupérer ma commande?";
			link.l1.go = "Trade_artefact_2";
			npchar.quest.art = "obereg_4";
		break;
		
		case "obereg_5":
			dialog.text = "Une tortue de jade? C'est ton as dans un jeu de cartes! Bon...";
			link.l1 = "Quand devrais-je revenir pour récupérer ma commande?";
			link.l1.go = "Trade_artefact_2";
			npchar.quest.art = "obereg_5";
		break;
		
		case "obereg_6":
			dialog.text = "Un poing de singe? Comme ils disent - fais-les te respecter! Bien...";
			link.l1 = "Quand devrais-je revenir pour récupérer ma commande?";
			link.l1.go = "Trade_artefact_2";
			npchar.quest.art = "obereg_6";
		break;
		
		case "obereg_7":
			dialog.text = "Un pêcheur? C'est le rêve de tout navigateur. Bien...";
			link.l1 = "Quand devrais-je revenir pour récupérer ma commande?";
			link.l1.go = "Trade_artefact_2";
			npchar.quest.art = "obereg_7";
		break;
		
		case "obereg_8":
			dialog.text = "Des perles de marchand? L'argent aime être compté, n'est-ce pas? Bien...";
			link.l1 = "Quand devrais-je revenir chercher ma commande?";
			link.l1.go = "Trade_artefact_2";
			npchar.quest.art = "obereg_8";
		break;
		
		case "obereg_9":
			dialog.text = "Ehecatl? N'importe quel vieux tub à faible vitesse volera plus vite que le vent! Bien...";
			link.l1 = "Quand devrais-je revenir chercher ma commande?";
			link.l1.go = "Trade_artefact_2";
			npchar.quest.art = "obereg_9";
		break;
		
		case "obereg_10":
			dialog.text = "Boucle d'oreille de marin? Donne celle-ci à ton timonier! Bon...";
			link.l1 = "Quand devrais-je revenir pour récupérer ma commande?";
			link.l1.go = "Trade_artefact_2";
			npchar.quest.art = "obereg_10";
		break;
		
		case "obereg_11":
			dialog.text = "Pèlerin ? Le vent de face devient vent arrière. Bon...";
			link.l1 = "Quand devrais-je revenir pour récupérer ma commande?";
			link.l1.go = "Trade_artefact_2";
			npchar.quest.art = "obereg_11";
		break;
		
		case "Trade_artefact_2":
			dialog.text = "Dans deux mois, pas avant. Je pense qu'à ce moment-là ils me l'auront apporté. Donc je t'attendrai avec l'argent dans deux mois.";
			link.l1 = "Super! Je serai là! Merci, "+npchar.name+"!";
			link.l1.go = "exit";
			SaveCurrentNpcQuestDateParam(npchar, "art_date");
			npchar.quest.artday = rand(20)+50;
			sTemp = "Amulet_"+npchar.location;
			AddQuestRecord(sTemp, "1");
			ReOpenQuestHeader(sTemp);
			AddQuestUserData(sTemp, "sAml", XI_ConvertString(npchar.quest.art)); // dlc
		break;
		
		case "Trade_artefact_3":
			if (CheckAttribute(npchar, "art_date") && GetNpcQuestPastDayParam(npchar, "art_date") >= sti(npchar.quest.artday))
			{
			dialog.text = "Ouais, je l'ai. Avez-vous préparé 100 doubloons, capitaine?"; // Addon-2016 Jason
				// belamour legendary edition -->
				if(PCharDublonsTotal() >= 100) 
				{
					link.l1 = "Certainement! Voici, comme convenu.";
					link.l1.go = "Trade_artefact_4";
				}
				else
				{
					link.l1 = "Oh, j'ai oublié l'argent sur le navire! Je l'apporterai bientôt.";
					link.l1.go = "exit";
				}
				// <-- legendary edition
			}
			else
			{
			dialog.text = "Pas encore. Venez me voir plus tard. Et ne vous inquiétez pas - votre amulette arrivera sûrement.";
			link.l1 = "D'accord.";
			link.l1.go = "exit";
			}
		break;
		
		case "Trade_artefact_4":
			RemoveItems(pchar, "gold_dublon", 100); // Addon-2016 Jason
			Log_Info("You have given 100 doubloons");
			dialog.text = "Tout semble bien. Voici ton amulette. Bonne chance avec ça!";
			link.l1 = "Merci, "+npchar.name+"!";
			link.l1.go = "Trade_artefact_5";
		break;
		
		case "Trade_artefact_5":
			DialogExit();
			Log_Info("You have received "+XI_ConvertString(npchar.quest.art)+"");
			PlaySound("interface\important_item.wav");
			TakeNItems(pchar, npchar.quest.art, 1);
			DeleteAttribute(npchar, "quest.art");
			sTemp = "Amulet_"+npchar.location;
			AddQuestRecord(sTemp, "2");
			CloseQuestHeader(sTemp);
		break;
		
		// --> калеуче
		case "caleuche":
			PlaySound("interface\important_item.wav");
			dialog.text = "Montre ce que tu as là.";
			link.l1 = "Voici, cela ressemble à un ancien amulette indien. Mais je n'ai aucune idée de comment l'utiliser ou de sa puissance cachée.";
			link.l1.go = "caleuche_1";
			npchar.quest.caleuche = "true";
		break;
		
		case "caleuche_1":
			if (npchar.id == pchar.questTemp.Caleuche.Amuletmaster)
			{
				dialog.text = "Eh bien, eh bien. Tu es la troisième personne qui me montre une telle chose, mon pote. Cet amulette a été apportée ici de la sauvage selva du Sud Principal. Il y a des Indiens non loin de Panama qui portent des bibelots comme celui-ci. Les peaux-rouges disent que c'est un héritage de leurs 'grands ancêtres.'\nJe n'ai aucune idée de qui étaient leurs ancêtres ou quel genre d'héritage ils ont laissé, mais je peux te donner des conseils sur où te renseigner. Intéressé?";
				link.l1 = "Certainement!";
				link.l1.go = "caleuche_2";
				DelLandQuestMark(npchar);
				if (npchar.id == "BasTer_Lightman") DelMapQuestMarkShore("Mayak4");
				if (npchar.id == "Santiago_Lightman") DelMapQuestMarkShore("Mayak9");
			}
			else
			{
				dialog.text = "Hmm... I've held a lot of amulets in my hands, but this one, I see for the first time in the Caribbean. Sorry, mate, I cannot help you; I don't know this kind of stuff. But it is not a simple thing; that's a fact. Ask somebody else. I know for sure that there are other lighthouse keepers like me who know about amulets not any less.";
				link.l1 = "Excusez-moi... Je vais continuer à demander alors.";
				link.l1.go = "exit";
			}
		break;
		
		case "caleuche_2":
			dialog.text = "There is a Carib village on Dominica, and the local chief is named Moknitekuvri. They have a shaman named Tuttuathapak, a highly respected Indian. He's not one of the Caribs; he's from that place about which I've told you already. He can tell you more about this amulet than me. But be careful - Tuttuathapak hates white people. He really hates them. After all, they once enslaved him and took him away from his home...";
			link.l1 = "Je suppose qu'il est arrivé aux Caraïbes de cette manière?";
			link.l1.go = "caleuche_3";
		break;
		
		case "caleuche_3":
			dialog.text = "Oui. C'est une histoire assez intéressante. Le navire, qui transportait des esclaves indiens, a été pris dans un calme plat près de Marie Galante et la moitié de l'équipage est morte de fièvre soudaine. Pourtant, pas un seul Indien n'est tombé malade !\nEnsuite, un capitaine est devenu fou et a mis le feu à son navire. En conséquence, les Indiens emprisonnés ont déclenché une émeute et ont massacré l'équipage. Devinez-vous qui était leur chef?";
			link.l1 = "Je le fais...";
			link.l1.go = "caleuche_4";
		break;
		
		case "caleuche_4":
			dialog.text = "C'est ça. Je parie que c'était un sort de chaman qui a rendu la mer aussi calme qu'un mort, et a infecté l'équipage avec une maladie mortelle. Cet Indien est très intelligent et très dangereux. Si tu vas le voir - comporte-toi poliment et surveille ta langue - sinon il y aura beaucoup d'ennuis pour toi. De plus, il ne parlera même pas avec toi sans une offrande pour lui.";
			link.l1 = "Et quel genre d'offrande pourrait-il exiger ?";
			link.l1.go = "caleuche_5";
		break;
		
		case "caleuche_5":
			dialog.text = "Tu ne le soudoieras pas avec des ordures. D'après ce que je sais, il envoie ses soldats Caribes dans les colonies de blancs pour acheter des armes à feu. Apporte-lui un mousquet en cadeau et alors, je pense, il sera content et te prêtera un peu de son attention.";
			link.l1 = "Merci! Je ferai comme tu dis... Dis, camarade, comment sais-tu tout cela?";
			link.l1.go = "caleuche_6";
		break;
		
		case "caleuche_6":
			dialog.text = "Mon ami était un marin sur le navire malheureux. Heureusement, il a réussi à survivre dans cet enfer... J'ai vu sur lui un amulette comme le vôtre, il semble que le défunt capitaine ait également saisi les biens des Indiens. Je suis sûr que votre amulette provient de sa collection - lorsque le capitaine est devenu fou et a incendié son navire, ses marins l'ont tué puis pillé les coffres dans la cabine.";
			link.l1 = "Compris. Alors je dois juste aller avec un cadeau à la Dominique. Merci pour votre aide et pour l'histoire intéressante!";
			link.l1.go = "caleuche_7";
		break;
		
		case "caleuche_7":
			dialog.text = "Bonne chance, mon ami, et sois prudent avec ce diable à la peau rouge...";
			link.l1 = "...";
			link.l1.go = "caleuche_8";
		break;
		
		case "caleuche_8":
			DialogExit();
			AddQuestRecord("Caleuche", "2");
			pchar.questTemp.Caleuche = "dominica"; 
			Caleuche_CreateShamane();
		break;
		
		case "caleuche_9":
			dialog.text = "Oui? Vous avez eu une conversation avec Tuttuathapak, ai-je raison?";
			link.l1 = "Exactement. Et maintenant je veux trouver deux autres amulettes. Tu as dit que j'étais le troisième, qui t'a montré cet artefact. Et qui étaient les deux autres?";
			link.l1.go = "caleuche_10";
		break;
		
		case "caleuche_10":
			dialog.text = "C'est un de mes amis, le marin de ce navire qui a amené Tuttuathapak aux îles des Caraïbes. Depuis cet incident, il n'a pas posé un pied sur le pont d'un navire. Je ne l'ai pas vu depuis un moment, mais je sais où il vit. Cherche-le à la rue principale de l'Ouest, à Belize - c'est un chasseur qui se promène maintenant dans la jungle. Il s'appelle Fergus Hooper.";
			link.l1 = "D'accord. Et le deuxième?";
			link.l1.go = "caleuche_11";
		break;
		
		case "caleuche_11":
			dialog.text = "Je connais un peu le second. Que son nom soit Jack, ou Jackson, et qu'il soit corsaire, ou petit commerçant, ou simplement aventurier. Il possède une xébèque avec un nom étrange... hmm... son nom est... Zut, j'ai oublié ! Mais le nom est une sorte de démoniaque. Je lui ai demandé ce que cela signifiait, et il a dit que c'était une femme-oiseau, née des dieux de la mer. Pah ! Impie...";
			link.l1 = "Bouffon... Alors tu ne te souviens pas de son nom?";
			link.l1.go = "caleuche_12";
		break;
		
		case "caleuche_12":
			dialog.text = "Non, que le tonnerre me frappe, je ne me souviens pas. Oh, et quand il s'est présenté, il a mentionné qu'il venait de la Barbade.";
			link.l1 = "C'est quelque chose ! D'accord, j'essaierai de trouver cet amoureux des femmes à plumes jusqu'à ce qu'il soit trouvé par quelqu'un d'autre... Merci, camarade, tu m'as beaucoup aidé !";
			link.l1.go = "caleuche_13";
		break;
		
		case "caleuche_13":
			dialog.text = "Vous êtes le bienvenu, cap, passez parfois.";
			link.l1 = "Certainement !";
			link.l1.go = "caleuche_14";
		break;
		
		case "caleuche_14":
			DialogExit();
			AddQuestRecord("Caleuche", "7");
			pchar.questTemp.Caleuche = "hunting"; 
			pchar.questTemp.Caleuche.Belizterms = rand(4)+3;
			pchar.quest.caleuche_prepare_beliz.win_condition.l1 = "location";
			pchar.quest.caleuche_prepare_beliz.win_condition.l1.location = "Beliz";
			pchar.quest.caleuche_prepare_beliz.function = "Caleuche_PrepareBeliz";
		break;
		
		case "fight":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			LAi_group_Attack(NPChar, Pchar);
			if (rand(3) != 1) SetNationRelation2MainCharacter(sti(npchar.nation), RELATION_ENEMY);
			LAi_SetOwnerType(NPChar); // belamour иначе обижается навсегда		   
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
		case "exit_setOwner":
			LAi_SetOwnerTypeNoGroup(npchar);
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
		case "Man_FackYou"://реакция на попытку залезть в сундук
			dialog.text = LinkRandPhrase("Tu es "+GetSexPhrase(" un voleur, ma chère ! Gardes, saisissez-le"," voleuse! Gardes, saisissez-la")+"!!!","Zut ! Je détourne le regard un instant, et te voilà déjà en train de fouiller dans le coffre ! Arrêtez le voleur !","Gardes! Vol! Arrêtez le voleur!");
			link.l1 = "Argh, merde!";
			link.l1.go = "fight";
		break;
		
		// belamour legendary edition карибские нравы
		case "Trial":
			dialog.text = "Ah, donc vous êtes ce capitaine ! Oui, je vous attendais. Gerard aussi vous attendait, mais il devait partir de toute urgence pour une sorte d'expédition, alors il m'a demandé de vous transférer le paiement. Il a dit que vous deviez venir. Il y a ici quatre cents doubloons, si cela vous convient.");
			link.l1 = "Merci! C'est agréable de traiter avec des gens honnêtes.";
			link.l1.go = "Trial_1";
		break;
		
		case "Trial_1":
			DialogExit();
			TakeNItems(pchar, "gold_dublon", 400);
			Log_Info("You have received 400 doubloons");
			PlaySound("interface\important_item.wav");
            NextDiag.CurrentNode = NextDiag.TempNode;
			DeleteAttribute(pchar, "questTemp.Trial");
			DeleteAttribute(npchar, "quest.trial_usurer");
			pchar.questTemp.IslamonaSpaOfficer = true;
			CloseQuestHeader("Trial");
			pchar.questTemp.TrialEnd = true;
		break;
		// <-- legendary edition
	}
}
