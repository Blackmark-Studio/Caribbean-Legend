// boal 08/04/04 общий диалог торговцев
#include "DIALOGS\%language%\Rumours\Common_rumours.c"  //homo 25/06/06

void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	

	string iDay, iMonth, sTemp, sMoney, attrL;
	
	iDay = environment.date.day;
	iMonth = environment.date.month;
	string lastspeak_date = iday + " " + iMonth;
	
	int iMoney, iQuantityGoods, iTradeGoods, iTmp;
	
	bool  ok;

	int iTest, cn, i;
	iTest = FindColony(NPChar.City); // город магазина
	ref rColony, chref;
	
	if (iTest != -1)
	{
		rColony = GetColonyByIndex(iTest);
	}
	
	int iSeaGoods = LanguageOpenFile("ShipEatGood.txt"); // нужно заменить на GetGoodsNameAlt(idx)

	if(!CheckAttribute(npchar, "quest.trade_date"))
	{
		npchar.quest.trade_date = "";
	}
    
	// вызов диалога по городам -->
	NPChar.FileDialog2 = "DIALOGS\" + LanguageGetLanguage() + "\Store\" + NPChar.City + "_Store.c";
	if(LoadSegment(NPChar.FileDialog2))
	{
		ProcessCommonDialog(NPChar, Link, NextDiag);
		UnloadSegment(NPChar.FileDialog2);
	}
	
	// вызов диалога по городам <--
	ProcessCommonDialogRumors(NPChar, Link, NextDiag);//homo 25/06/06
	
	string attrLoc   = Dialog.CurrentNode;
	
	if(HasSubStr(attrLoc, "TransferGoodsTo_"))
	{
		NPChar.CharToTransferGoodsID = FindStringAfterChar(attrLoc, "_");
		Dialog.CurrentNode = "TransferGoods_Start";
	}
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			if (LAi_grp_playeralarm > 0)
			{
				dialog.text = NPCharRepPhrase(pchar,LinkRandPhrase("L'alarme est déclenchée en ville, et tout le monde vous cherche. Si j'étais vous, je ne resterais pas là.","Tous les gardes de la ville fouillent la ville à ta recherche. Je ne suis pas un imbécile et je ne te parlerai pas !","Courez, "+GetSexPhrase("matelot","fillette")+", avant que les soldats ne te transforment en passoire..."),LinkRandPhrase("Que désirez-vous, "+GetSexPhrase("canaille","vaurien")+"?! Les gardes de la ville ont déjà votre odeur, vous n'irez pas loin, "+GetSexPhrase("sale pirate","ordure meurtrière")+" !","Sale meurtrier, quittez ma maison sur-le-champ ! Gardes !","Je ne te crains pas, "+GetSexPhrase("vermine","pourceau")+" ! Bientôt, tu seras pendu dans notre fort, tu n'iras pas loin..."));
				link.l1 = NPCharRepPhrase(pchar,RandPhraseSimple("Heh, une alarme n'est jamais un problème pour moi...","Ils ne m'auront jamais."),RandPhraseSimple("Ferme ta putain de bouche, "+GetWorkTypeOfMan(npchar,"")+", ou je vais t'arracher ta langue sale!!","Heh, "+GetWorkTypeOfMan(npchar,"")+", et tout le monde là-bas - sont ici pour attraper des pirates ! Voici ce que je te dis, camarade : reste tranquille et tu ne mourras pas..."));
				link.l1.go = "fight";
				break;
			}
			if (sti(pchar.GenQuest.Piratekill) > 20 && sti(npchar.nation) == PIRATE)
			{
				dialog.text = RandPhraseSimple("Hey, salaud ! Tu crois pouvoir prendre tout ce que tu veux ? Certainement pas ! Les gars ! Aux armes ! Tranchez ce cinglé !","Si tu veux quelque chose, achète-le, espèce de bête ! Maintenant je vais te montrer ce qu'il en est ! Les gars, prenez vos armes ! Alerte !");
				link.l1 = RandPhraseSimple("Hein ? Quoi ?","Eh bien, pourquoi fais-tu cela ?");
				link.l1.go = "fight";
				bDisableFastReload = true;//закрыть переход
				pchar.quest.pirate_in_town.win_condition.l1 = "ExitFromLocation";
				pchar.quest.pirate_in_town.win_condition.l1.location = pchar.location;
				pchar.quest.pirate_in_town.function = "TownPirate_battle";
				break;
			}
			//--> Jason Бремя гасконца
			if (CheckAttribute(pchar, "questTemp.Sharlie.Lock"))
			{
				//Jason --> мини-квест Дефицитный товар
				if (CheckAttribute(pchar, "questTemp.Wine.Trader") && NPChar.location == pchar.questTemp.Wine.City + "_store" && !CheckAttribute(pchar, "questTemp.Wine.fail"))
				{
					link.l13 = "Je souhaiterais vous acheter un lot de vin européen - cinquante à soixante bouteilles. On m'a dit que vous en aviez suffisamment en stock."; 
					link.l13.go = "Wine_Trader";
				}
				if (CheckAttribute(pchar, "questTemp.Wine.Repeat2") && NPChar.location == pchar.questTemp.Wine.City + "_store" && CheckCharacterItem(pchar, "letter_1") && !CheckAttribute(pchar, "questTemp.Wine.fail"))
				{
					link.l13 = "Bonjour à nouveau. Veuillez jeter un œil à cette lettre - peut-être réviserez-vous votre position quant à me vendre du vin ?"; 
					link.l13.go = "Wine_Repeat2";
				}
				if (CheckAttribute(pchar, "questTemp.Wine.wait") && NPChar.location == pchar.questTemp.Wine.City + "_store" && !CheckAttribute(pchar, "questTemp.Wine.fail"))
				{
					link.l13 = "C'est moi encore. Pouvons-nous reprendre notre affaire de vin interrompue ? J'ai réussi à rassembler assez d'argent."; 
					link.l13.go = "Wine_Price";
				}
				// <-- мини-квест Дефицитный товар
				dialog.text = "Vouliez-vous acheter quelque chose, monsieur ?";
				Link.l1 = "Bien sûr que je l'ai fait - à quoi servent sinon les magasins ? Montrez-moi vos marchandises.";
				Link.l1.go = "trade_1";
				Link.l2 = "Je viens pour une affaire particulière...";
				Link.l2.go = "quests";
				Link.l3 = "Je suis désolé, mais je dois y aller.";
				Link.l3.go = "exit";
				// туториал Мартиника
				if(NPChar.City == "FortFrance")
				{
					if (!CheckAttribute(npchar, "quest.storehelper") && pchar.questTemp.Sharlie == "ship")
					{
						Link.l2 = "Écoutez, monsieur, je cherche du travail. Pas un travail à plein temps ou un boulot à porter des sacs de cargaison, mais plutôt à faire des courses, si vous voyez ce que je veux dire. Auriez-vous besoin d'assistance par hasard ?";
						Link.l2.go = "Sharlie_storehelper";
					}
					if (CheckAttribute(pchar, "questTemp.Sharlie.Storehelper") && pchar.questTemp.Sharlie.Storehelper == "return")
					{
						Link.l2 = "J'ai terminé votre commission. J'ai trouvé Gralam Lavoie.";
						Link.l2.go = "Sharlie_storehelper_2";
					}
					if (CheckAttribute(pchar, "questTemp.Sharlie.Storehelper") && pchar.questTemp.Sharlie.Storehelper == "choise")
					{
						Link.l2 = "Rencontrez votre nouvel assistant, monsieur.";
						Link.l2.go = "Sharlie_storehelper_11";
					}
					if (CheckAttribute(pchar, "questTemp.Sharlie.Storehelper") && pchar.questTemp.Sharlie.Storehelper == "final")
					{
						Link.l2 = "C'est encore moi, monsieur. Je suis venu pour ma récompense.";
						Link.l2.go = "Sharlie_storehelper_13";
					}
					if (CheckAttribute(pchar, "questTemp.Sharlie.Junglejew") && !CheckAttribute(npchar, "quest.junglejew"))
					{
						link.l4 = "Jetez un œil à ces boucles d'oreilles, monsieur. Je les ai trouvées sur le corps d'un bandit tué dans la jungle. C'est clairement l'œuvre d'un fin bijoutier qui, j'en suis sûr, n'est pas d'ici. Pouvez-vous me dire quelque chose à propos de ces boucles d'oreilles ?";
						link.l4.go = "Sharlie_junglejew";
					}
				}
				break;
			}			
			//<-- Бремя гасконца
			
			// Warship, 29.05.11. Дело чести - трусливый фехтовальщик.
			if(CheckAttribute(PChar, "QuestTemp.AffairOfHonor.CowardFencer.CanTraderTalk"))
			{
				dialog.text = "Capitaine, merci de m'avoir sauvé.";
				Link.l1 = "Oh, vous êtes le bienvenu.";
				Link.l1.go = "exit";
				DeleteAttribute(PChar, "QuestTemp.AffairOfHonor.CowardFencer.CanTraderTalk");
				break;
			}
			// Карибские нравы
			if(CheckAttribute(npchar, "quest.trial_usurer"))
			{
				dialog.text = "Quoi de neuf, capitaine ? Avez-vous perdu quelque chose ? Pourquoi courez-vous comme ça dans ma boutique ?";
				Link.l1 = "Eh bien, imaginez ça - j'ai effectivement réussi ! Où est ce maudit Gerard LeCroix ? J'ai accompli toutes les tâches qui m'ont été confiées par Florian Shoke, et que le requin me dévore tout entier, j'ai eu sacrément du mal à le faire ! Et maintenant, quand je viens récupérer ma récompense, il s'avère que cet oiseau s'est envolé !";
				Link.l1.go = "trial";
				// belamour legendary edition -->
				Link.l2 = "Comment puis-je vous dire... Perdu. Avez-vous vu mon client ? Il s'appelle Gerard LeCroix.";
				Link.l2.go = "trialA";
				//<-- legendary edition
				DelLandQuestMark(npchar);
				break;
			}
			// belamour legendary edition Бесчестный конкурент -->
			if(!CheckAttribute(pchar, "questTemp.Shadowtrader") && sti(npchar.nation) != PIRATE && npchar.location == "baster_store")
			{
				dialog.text = "Capitaine, je veux vous demander une faveur. Me donnerez-vous un coup de main ?";
				link.l1 = "Comment puis-je vous aider ?"; 
				link.l1.go = "Shadowtrader_begin";
				break;
			}
			// <-- legendary edition			
            dialog.Text = GetNatPhrase(npchar,LinkRandPhrase("Enchanté de vous rencontrer, monsieur ! Êtes-vous nouveau dans ces contrées ?","Bienvenue, capitaine ! Ma boutique est à votre service, monsieur.","Monsieur, entrez, je vous prie ! Je suis heureux de vous offrir les meilleures marchandises que vous puissiez acheter sur cet archipel."),LinkRandPhrase("Oh, monsieur capitaine ! Les meilleures marchandises de toutes les colonies françaises - ici et maintenant, exclusivement pour vous !","Quelle belle rencontre, monsieur ! La meilleure boutique offrant les meilleurs produits français - à votre service !","Nous sommes-nous déjà rencontrés, monsieur le capitaine ? Vous savez, ma boutique est aussi belle que les meilleurs magasins de la mère patrie !"),LinkRandPhrase("Oh! Senor capitaine! Je suis si heureux de vous voir dans mon magasin!","Je suis heureux de saluer un caballero aussi brillant dans le meilleur magasin de toutes les colonies espagnoles !","Oh, noble hidalgo ! Le destin lui-même vous a conduit dans ma modeste boutique ! Ici, vous trouverez tout ce que vous pourriez désirer !"),LinkRandPhrase("Bon après-midi, monsieur le capitaine. Est-ce votre première visite ici ?","Bonjour, monseigneur. Est-ce votre première visite ici ? Je vous assure que la qualité de nos marchandises hollandaises vous surprendra agréablement !","Veuillez entrer, monsieur le capitaine ! Les meilleures marchandises aux prix les plus bas - c'est la manière néerlandaise de faire du commerce !"));
			Link.l1 = LinkRandPhrase("Enchanté de vous rencontrer également. Mon nom est "+GetFullName(pchar)+" et je suis plutôt nouveau dans ces contrées. Eh bien, montre-moi les richesses de l'archipel ! ","Enchanté de vous rencontrer également. Je suis "+GetFullName(pchar)+". capitaine du navire '"+pchar.ship.name+"'. Alors, quelles sont les bonnes affaires?","Bonjour, mon ami."+GetFullName(pchar)+", capitaine du navire '"+pchar.ship.name+", heureux de faire votre connaissance. Alors, que pouvez-vous m'offrir ?");
			link.l1.go = "node_1";
			
			if(startHeroType == 4 && NPChar.location == "SantaCatalina_store")
			{
				dialog.text = "Capitaine Helen ! Toujours un plaisir.";
				link.l1 = "Je vous en prie, merci.";
				link.l1.go = "Helen_node_1";
			}
			NextDiag.TempNode = "Second time";
		break;

		case "second time":
			if (LAi_group_GetPlayerAlarm() > 0)
			{
       			dialog.text = NPCharRepPhrase(pchar,LinkRandPhrase("L'alarme est donnée dans la ville, et tout le monde te cherche. Si j'étais toi, je n'y resterais pas.","Tous les gardes de la ville ratissent le bourg à votre recherche. Je ne suis pas un imbécile et je ne vous parlerai pas !","Courez, "+GetSexPhrase("matelot","fillette")+", avant que les soldats ne te transforment en écumoire..."),LinkRandPhrase("Que désirez-vous, "+GetSexPhrase("fripouille","vaurien")+"?! Les gardes de la ville ont déjà ton odeur, tu n'iras pas loin, "+GetSexPhrase("pirate immonde","immondices meurtrières")+" !","Sale meurtrier, quittez ma maison sur-le-champ ! Gardes !","Je ne te crains pas, "+GetSexPhrase("ramper","pourriture")+" ! Bientôt, tu seras pendu dans notre fort, tu n'iras pas loin..."));
				link.l1 = NPCharRepPhrase(pchar,RandPhraseSimple("Heh, une alarme n'est jamais un problème pour moi...","Ils ne m'auront jamais."),RandPhraseSimple("Tais-toi, "+GetWorkTypeOfMan(npchar,"Bonjour, mon ami.")+", ou je vais t'arracher ta langue sale !","Heh, "+GetWorkTypeOfMan(npchar,"")+", et tout le monde là-bas - sont ici pour attraper des pirates ! Voici ce que je te dis, l'ami : reste tranquille et tu ne mourras pas..."));
				link.l1.go = "fight";
				break;
			}
            
			//--> Jason, Сомнительное предложение
			if (CheckAttribute(pchar, "GenQuest.Contraoffer.Trader.busy"))
			{
				dialog.text = "Je vous prie de m'excuser, mais je n'ai pas le temps pour vous maintenant.";
				link.l1 = "Oui, bien sûr. Je passerai une autre fois, alors.";
				link.l1.go = "exit";
				break;
			}
			//<-- Сомнительное предложение
            
			// Warship, 29.05.11. Дело чести - трусливый фехтовальщик.
			if(CheckAttribute(PChar, "QuestTemp.AffairOfHonor.CowardFencer.CanTraderTalk"))
			{
				dialog.text = "Capitaine, merci de m'avoir sauvé.";
				Link.l1 = "Oh, de rien.";
				Link.l1.go = "exit";
				DeleteAttribute(PChar, "QuestTemp.AffairOfHonor.CowardFencer.CanTraderTalk");
				break;
			}
			// Карибские нравы
			if(CheckAttribute(npchar, "quest.trial_usurer"))
			{
				dialog.text = "Quoi de neuf, capitaine ? Auriez-vous perdu quelque chose ? Pourquoi courez-vous ainsi dans ma boutique ?";
				Link.l1 = "Eh bien, imaginez cela - j'ai vraiment réussi! Où est ce maudit Gerard LeCroix? J'ai accompli toutes les tâches que m'a confiées Florian Shoke, et, que le requin me gobe tout entier, j'ai eu un mal de chien à le faire! Et maintenant, quand je viens récupérer ma récompense, il s'avère que cet oiseau s'est envolé!";
				Link.l1.go = "trial";
				// belamour legendary edition -->
				Link.l2 = "Comment vous dire... Perdu. Avez-vous vu mon client ? Il s'appelle Gerard LeCroix.";
				Link.l2.go = "trialA";
				//<-- legendary edition
				DelLandQuestMark(npchar);
				break;
			}
 			// belamour legendary edition Бесчестный конкурент -->
			if(!CheckAttribute(pchar, "questTemp.Shadowtrader") && sti(npchar.nation) != PIRATE && npchar.location == "baster_store")
			{
				dialog.text = "Capitaine, je veux vous demander une faveur. Voulez-vous m'aider ?";
				link.l1 = "Comment puis-je vous aider ?"; 
				link.l1.go = "Shadowtrader_begin";
				break;
			}
			// <-- legendary edition           
			dialog.Text = pcharrepphrase(LinkRandPhrase(LinkRandPhrase("Oh, regardez qui voilà ! Eh bien, comme on dit, l'argent n'a pas d'odeur, alors entrez, capitaine, et faisons du commerce...","Je ne peux pas dire que je suis heureux de te voir, "+GetFullName(pchar)+" ... Mais je peux toujours commercer avec vous.","Hi-hi... Eh bien, je ne vous inviterais pas chez moi, capitaine - mais ma boutique est toujours à votre service."),LinkRandPhrase("Oh, regarde qui voilà ! N'est-ce pas "+GetFullName(pchar)+" ! Vous voulez échanger ou juste prendre des trucs gratuitement ? Hé, je plaisante...","Je ne peux pas dire que je suis content de te voir ici, "+GetAddress_Form(NPChar)+", mais si vous avez de l'argent à dépenser - entrez, entrez...","Voulez-vous commercer, capitaine "+GetFullName(pchar)+"? Si c'est le cas, pourriez-vous vous dépêcher ? Les autres clients vous évitent, et cela nuit à mes affaires,"),LinkRandPhrase("Vous voulez commercer, monseigneur ? Juste une seconde, je vais encaisser - vous savez, il y a des types louches dans les parages... Bien sûr, je ne parle pas de vous, capitaine !","Si je te voyais en pleine mer, "+GetAddress_Form(NPChar)+", je pourrais probablement ordonner d'ajouter des voiles... Mais ici, dans ma boutique, je peux vous proposer de faire du commerce.","Capitaine, je te préviens d'emblée : si le tissu est taché de sang et que le café sent la poudre à canon, je ne le prendrai pas. Sinon, jette un œil et fais ton choix.")),LinkRandPhrase(LinkRandPhrase("Et je suis ravi de vous saluer à nouveau, "+GetAddress_Form(NPChar)+" ! Achat ou vente - je suis toujours heureux de vous aider.","Je vous en prie, "+GetAddress_Form(NPChar)+", entrez ! Je suis toujours heureux de voir mon client préféré ici. Que sera-t-il cette fois - achat ou vente ?","Oh, "+GetAddress_Form(NPChar)+" "+GetFullName(pchar)+"! Je suis si heureux de vous revoir ! Qu'est-ce que ce sera cette fois - acheter ou vendre ?"),LinkRandPhrase("Aimez-vous nos marchandises, "+GetAddress_Form(NPChar)+" "+GetFullName(pchar)+" ? Je suis toujours à votre service - jetez un œil et faites votre choix.","Bonjour, "+GetAddress_Form(NPChar)+" "+GetFullName(pchar)+"Je suis ravi de vous revoir ! Voulez-vous jeter un oeil à l'assortiment de nos marchandises ?","Ravi de vous voir, capitaine ! Je savais que vous apprécieriez nos marchandises de qualité. Voulez-vous jeter un œil à nos nouveautés ?"),LinkRandPhrase("Oh, "+GetAddress_Form(NPChar)+" "+GetFullName(pchar)+"! Je vous en prie, entrez ! Toutes les marchandises rien que pour vous - et avec de grandes remises pour cette occasion !","Capitaine "+GetFullName(pchar)+" , une fois de plus tu m'as ravi par ta visite ! S'il te plaît, choisis ce qui te plaît !","Que désirez-vous cette fois, capitaine ? Je suis heureux que vous vous souveniez encore comment me trouver. Nous avons toutes les marchandises dont vous pourriez avoir besoin - de la toute meilleure qualité !")));
			Link.l1 = pcharrepphrase(RandPhraseSimple(RandPhraseSimple("C'est ainsi que tu m'accueilles, camarade ? Eh bien, je m'en souviendrai si nous nous croisons en mer... Arrête de trembler, je plaisantais. Montre-moi ce que tu as.","D'accord, mon gars. J'ai peut-être besoin de tes marchandises, mais pas de ta langue. Peux-tu la garder ou tu auras besoin d'aide pour ça ? Tais-toi et montre-moi tes marchandises."),RandPhraseSimple("Passons aux affaires, marchand. Je n'ai pas le temps de discuter de questions de morale avec toi, alors marchandons comme des gens civilisés.","Du calme, l'ami. Plaisanter, c'est bien, mais souviens-toi que je peux me fâcher... Alors cesse de m'irriter et montre-moi tes marchandises.")),RandPhraseSimple(RandPhraseSimple(" Toujours heureux de vous rendre visite, l'ami. Qu'avez-vous en stock qui vaudrait mon attention ? ","Toujours un plaisir de te voir, camarade. Alors, quoi de neuf pour les vagabonds des mers qui n'ont pas mis pied à terre depuis des mois ?"),RandPhraseSimple("Et me voilà de nouveau à "+XI_ConvertString("Colony"+npchar.City+"Acc")+" ! Heureusement que je n'étais pas là pour oublier. Mais il reste quelque chose dans vos entrepôts pour moi ? Tout est réglé ?","Comment as-tu pu ne pas venir ? Tu me plais toujours plus que cela. Eh bien, qu'as-tu là ?")));
			link.l1.go = "node_1";
			NextDiag.TempNode = "Second time";
		break;

		case "node_1":
			dialog.text = NPCStringReactionRepeat(NPCharRepPhrase(npchar,pcharrepphrase(RandPhraseSimple("Tous sur le pont ! ","Arrêtez l'inspection ! ")+LinkRandPhrase("Que fait un "+GetSexPhrase("gentilhomme","gentilhomme, oh, pardonnez-moi - une dame")+"de fortune besoin dans mon magasin, hé-hé ?","Quelle surprise pour un pauvre vieux boutiquier ! Hé-hé !","Alors, quel bon vent vous a amené dans ma boutique ?"),LinkRandPhrase("Ouvrez les ports !","Crochets de côté !","Naviguez droit devant !")+RandPhraseSimple(" Ici, vous trouverez"," Mon magasin a")+LinkRandPhrase("les meilleurs prix de toute l'île."," excellent assortiment de marchandises."," marchandises de la meilleure qualité disponible.")+RandPhraseSimple("Je suis à votre service"," Quoi que vous vouliez")+", capitaine !"),pcharrepphrase(RandPhraseSimple("Des marchandises pour "+GetSexPhrase("messieurs","messieurs et mesdames")+" de fortune ! Hé-hé ! Jusqu'à ce qu'ils soient pendus pour sécher au soleil !","Le vent balance les pendus dans le port et emporte le cliquetis des chaînes. Mais l'argent n'a pas d'odeur, n'est-ce pas ?"),"Voudriez-vous "+LinkRandPhrase("acheter les meilleures marchandises de "+NationNameGenitive(sti(NPChar.nation)),"acheter ou vendre votre cargaison","avez-vous un fret lucratif ?")+RandPhraseSimple("? Je suis à votre service !"," ? Mon magasin est à votre service !")+RandPhraseSimple("Ravi de vous voir"," Fais comme bon te semble")+", capitaine!")),NPCharRepPhrase(npchar,pcharrepphrase("Si tu veux mon conseil, capitaine - ne lésine pas sur les mitrailles. Tu sais, les morts sont bien plus faciles à fouiller !","J'ai remarqué tout de suite que vous êtes un "+GetSexPhrase("rusé compagnon","furieuse demoiselle")+". "+RandPhraseSimple("Mais maintenant je vois que vous êtes un vrai "+GetSexPhrase("héros","casse-cou")+".","Tu es jeune, mais "+RandPhraseSimple("gardez votre esprit avec vous.","vous ne pouvez certainement pas être dupé facilement."))),pcharrepphrase("Je suis prêt à vous acheter toute la cargaison des prises capturées. Voulez-vous en argent ou en or ? Ces marchandises sont toujours coûteuses.","La navigation commerciale est une affaire lucrative, capitaine "+GetFullName(pchar)+", n'est-ce pas ?")),NPCharRepPhrase(npchar,RandPhraseSimple("Nous les avons tous enveloppés dans une voile bien serrée Avec vingt tours d'une aussière bien enroulée Et nous les avons lancés par-dessus bord, hors de vue !",RandPhraseSimple("Quinze hommes sur le coffre du mort !","Bois et le diable a fait le reste !")+"Yo ho ho et une bouteille de rhum !")+RandPhraseSimple("Quoi de neuf, capitaine ?","Vous cherchez à acheter quelque chose, capitaine ?"),pcharrepphrase("Je vois que vous êtes un sacré marchand, capitaine "+GetFullName(pchar)+"Puisque vous êtes un client fidèle, je vous propose des prix très avantageux !","D'accord, capitaine "+GetFullName(pchar)+"Par déférence pour vous, je peux offrir un peu plus ! Que désirez-vous ?")),NPCharRepPhrase(npchar,"Je jure, te parler me rend malade. "+LinkRandPhrase("Achetez quelques cacahuètes. Les cochons raffolent de ce truc. ","Vous vous attendez à ce que quelqu'un vous cire les bottes avec du rhum ici ? ",pcharrepphrase("Je connais ton genre. Te remplir de rhum - et directement à la potence.","Je me demande comment ta mère t'a permis de devenir marin ! Un marin ! Tu ferais un bien meilleur tailleur...")),pcharrepphrase(RandPhraseSimple("Je pensais que ","J'espérais que ")+RandPhraseSimple("vous aviez quitté notre île pour de bon.","Je ne pensais jamais te revoir.")+RandPhraseSimple(" Les morts pendent à ton cou comme des meules de moulin...","Combien de marins as-tu laissés pourrir parmi les coraux?!"),"Capitaine "+GetFullName(pchar)+", votre passion pour le commerce a dépassé toutes mes attentes !"+RandPhraseSimple(" Veux-tu faire des achats de dernière minute avant de prendre la mer ?"," Cherchez-vous quelque chose de spécial?"))),"cycle",10,npchar,Dialog.CurrentNode);
			// belamour legendary edition на пару с Акулой -->
			if(CheckAttribute(pchar,"questTemp.SharkGoldFleet") && npchar.location == "caracas_store")
			{
				if(pchar.questTemp.SharkGoldFleet == "start" || pchar.questTemp.SharkGoldFleet == "afterGvik")
				{
					dialog.Text = pcharrepphrase(LinkRandPhrase(LinkRandPhrase("Oh, regardez qui voilà ! Eh bien, comme on dit, l'argent n'a pas d'odeur, alors entrez, capitaine, et commerçons...","Je ne peux pas dire que je suis heureux de te voir, "+GetFullName(pchar)+"... Mais je peux encore échanger avec vous.","He-he... Eh bien, je ne vous inviterais pas chez moi, capitaine - mais ma boutique est toujours à votre service."),LinkRandPhrase("Oh, qui voilà ! N'est-ce pas "+GetFullName(pchar)+" ! Voulez-vous échanger ou juste prendre des trucs gratuitement ? Hé, je plaisante...","Je ne peux pas dire que je suis ravi de te voir ici, "+GetAddress_Form(NPChar)+"Mais si vous avez de l'argent à dépenser - entrez, entrez...","Vous voulez faire du commerce, capitaine "+GetFullName(pchar)+"Si c'est le cas, pourriez-vous vous dépêcher, s'il vous plaît ? Les autres clients vous évitent, et cela nuit à mes affaires,"),LinkRandPhrase("Veux-tu commercer, monseigneur? Juste un instant, je vais encaisser - tu sais, il y a des types douteux dans les parages... Bien sûr, je ne parle pas de vous, capitaine !","Si je vous voyais en haute mer, "+GetAddress_Form(NPChar)+", je pourrais probablement ordonner d'ajouter des voiles... Mais ici, dans ma boutique, je peux vous proposer d'échanger.","Capitaine, je vous avertis tout de suite : si le tissu est taché de sang et que le café pue la poudre à canon, je n'en veux pas. Sinon, jetez un œil et faites votre choix.")),LinkRandPhrase(LinkRandPhrase("Et je suis heureux de vous saluer à nouveau, "+GetAddress_Form(NPChar)+"Que ce soit pour acheter ou vendre, je suis toujours heureux de vous aider.","Je vous en prie, "+GetAddress_Form(NPChar)+", entrez ! Je suis toujours ravi de voir mon client préféré ici. Que sera-ce cette fois - acheter ou vendre ?","Oh, "+GetAddress_Form(NPChar)+" "+GetFullName(pchar)+"! Je suis si heureux de vous revoir ! Que ce sera cette fois - achat ou vente ?"),LinkRandPhrase("Aimez-vous nos marchandises, "+GetAddress_Form(NPChar)+" "+GetFullName(pchar)+" ? Je suis toujours à votre service - jetez un œil et faites votre choix.","Bonjour, "+GetAddress_Form(NPChar)+" "+GetFullName(pchar)+". Je suis ravi de vous revoir ! Voulez-vous jeter un oeil à l'assortiment de nos marchandises ?","Content de vous voir, capitaine ! Je savais que vous aimeriez nos marchandises de qualité. Voulez-vous jeter un œil à nos nouveautés ?"),LinkRandPhrase("Oh, "+GetAddress_Form(NPChar)+" "+GetFullName(pchar)+"! S'il vous plaît, entrez ! Toutes les marchandises rien que pour vous - et avec de grandes réductions pour cette occasion !","Capitaine "+GetFullName(pchar)+", une fois de plus, vous m'avez ravi avec votre visite ! Je vous en prie, faites votre choix, ce qui vous plaît !","Que désirez-vous cette fois, capitaine ? Je suis ravi que vous vous souveniez encore de comment me trouver. Nous avons toutes les marchandises dont vous pourriez avoir besoin - de la meilleure qualité !")));
					link.l14 = "Écoutez, je suis sur le point de partir pour Porto Bello maintenant et j'aimerais vous acheter une cargaison de café et de cacao. Disons, trois cents unités de chaque."; 
					link.l14.go = "SharkGoldFleet";
				}
			}
			if(CheckAttribute(pchar,"questTemp.SharkGoldFleet") && npchar.location == "caracas_store" && pchar.questTemp.SharkGoldFleet == "buyincar")
			{
				dialog.Text = pcharrepphrase(LinkRandPhrase(LinkRandPhrase("Oh, regardez qui voilà ! Eh bien, comme on dit, l'argent n'a pas d'odeur, alors entrez, capitaine, et faisons des affaires...","Je ne peux pas dire que je suis heureux de te voir, "+GetFullName(pchar)+" ... Mais je peux encore commercer avec vous.","Hi-hi... Eh bien, je ne vous inviterais pas chez moi, capitaine - mais ma boutique est toujours à votre service."),LinkRandPhrase("Oh, mais regardez qui voilà ! N'est-ce pas "+GetFullName(pchar)+"Voulez-vous échanger ou simplement prendre des trucs gratuitement ? Hé, je plaisante...","Je ne peux pas dire que je suis content de te voir ici, "+GetAddress_Form(NPChar)+". Mais si vous avez de l'argent à dépenser - entrez, entrez...","Tu veux troquer, capitaine "+GetFullName(pchar)+"? Si c'est le cas, pourriez-vous s'il vous plaît vous dépêcher ? Les autres clients vous évitent, et cela nuit à mon commerce,"),LinkRandPhrase("Voulez-vous commercer, monsieur? Un instant, je vais encaisser - vous savez, il y a des types douteux dans les parages... Bien sûr, je ne parle pas de vous, capitaine !","Si je vous voyais en haute mer, "+GetAddress_Form(NPChar)+", je serais probablement enclin à ajouter des voiles... Mais ici, dans ma boutique, je peux vous proposer un échange.","Capitaine, je vous préviens tout de suite : si le tissu est taché de sang et que le café pue la poudre à canon, je ne le prendrai pas. Sinon, jetez un œil et faites votre choix.")),LinkRandPhrase(LinkRandPhrase("Et je suis ravi de vous saluer à nouveau, "+GetAddress_Form(NPChar)+" ! Acheter ou vendre - je suis toujours heureux de vous aider.","Je vous en prie, "+GetAddress_Form(NPChar)+", entrez ! Je suis toujours ravi de voir mon client préféré ici. Que ce sera cette fois - acheter ou vendre ?","Oh, "+GetAddress_Form(NPChar)+" "+GetFullName(pchar)+"! Je suis si heureux de te revoir ! Que ce soit cette fois - acheter ou vendre ?"),LinkRandPhrase("Aimez-vous nos marchandises, "+GetAddress_Form(NPChar)+" "+GetFullName(pchar)+" ? Je suis toujours à votre service - jetez un œil et faites votre choix.","Bonjour, "+GetAddress_Form(NPChar)+" "+GetFullName(pchar)+". Je suis ravi de vous revoir ! Voulez-vous jeter un coup d'œil à notre assortiment de marchandises ?","Ravi de vous voir, capitaine ! Je savais que vous apprécieriez la qualité de nos marchandises. Voulez-vous jeter un œil à nos nouveautés ?"),LinkRandPhrase("Oh, "+GetAddress_Form(NPChar)+" "+GetFullName(pchar)+"! Entrez, je vous prie ! Toutes les marchandises rien que pour vous - et avec de grandes réductions pour cette occasion !","Capitaine "+GetFullName(pchar)+", encore une fois, tu m'as rendu heureux avec ta visite ! S'il te plaît, fais ton choix, tout ce qui te plaît !","Que désirez-vous cette fois, capitaine ? Je suis heureux que vous vous souveniez encore de comment me trouver. Nous avons toutes les marchandises dont vous pourriez avoir besoin - de la meilleure qualité !")));
				link.l14 = "Je suis ici pour du cafe et du cacao. "; 
				link.l14.go = "SharkGoldFleet_again";
			}
										
			// <-- на пару с Акулой
			link.l1 = HeroStringReactionRepeat(NPCharRepPhrase(npchar,pcharrepphrase("Montre-moi ce que tu as, vieux pirate !","Je voulais juste jeter un oeil à vos marchandises, mon bonhomme."),pcharrepphrase("Je le jure sur la potence, "+GetFullName(npchar)+", je ne te laisserai pas me détourner ! Montre-moi tes marchandises sur-le-champ !","Jetons un oeil à vos marchandises, "+GetAddress_FormToNPC(NPChar)+".")),NPCharRepPhrase(npchar,pcharrepphrase("C'est certain ! Les morts ne mordent pas ! Maintenant, qu'as-tu dans ta cale ?","Tu ferais mieux de t'occuper de tes affaires, mon bonhomme. Quels types de marchandises peux-tu m'offrir ?"),pcharrepphrase("Il viendra un jour où tu deviendras mon prix, hé-hé. Je plaisante. Montre-moi tes marchandises.","Discutons de nos affaires commerciales, "+GetAddress_FormToNPC(NPChar)+" "+GetFullName(npchar)+"")),NPCharRepPhrase(npchar,pcharrepphrase("Que veux-je ? Je veux acheter quelque chose !","Boire te mènera à ta tombe, "+GetFullName(npchar)+"Je veux jeter un coup d'œil à vos marchandises."),pcharrepphrase("Je connais vos remises ! Deux livres de cacao au prix de trois ! Maintenant, montrez-moi vos marchandises.","C'est toujours bien. Marchandons, alors.")),"Montre-moi tes marchandises. Moins on en dit, plus vite c'est réparé. Je suis pressé.",npchar,Dialog.CurrentNode);
			link.l1.go = "market";
			link.l2 = HeroStringReactionRepeat(NPCharRepPhrase(npchar,pcharrepphrase("Oh, j'aimerais vraiment poignarder quelqu'un, D'accord, passons aux affaires.","Passons à d'autres affaires, mon bonhomme."),pcharrepphrase("Caramba ! Je suis ici pour une affaire différente !","Je veux vous parler d'une affaire particulière, "+GetAddress_FormToNPC(NPChar)+" "+GetFullName(npchar)+".")),NPCharRepPhrase(npchar,pcharrepphrase("J'ai affaire à toi, vieux pirate !","Passons aux affaires, camarade!"),pcharrepphrase("Je jure par le diable, tu ne m'entourlouperas pas, vaurien ! J'ai d'autres affaires avec toi !","Je suis absolument d'accord, "+GetAddress_FormToNPC(NPChar)+" "+GetFullName(npchar)+", je voulais discuter d'autres affaires avec vous.")),NPCharRepPhrase(npchar,pcharrepphrase("Déjà chargé ? J'ai des affaires avec vous.","Je ne suis pas venu ici pour commercer, mon bonhomme. J'ai d'autres affaires."),pcharrepphrase("Que le tonnerre te foudroie pour des prix pareils ! J'ai affaire avec vous.","Les rabais sont toujours agréables, "+GetAddress_FormToNPC(NPChar)+" "+GetFullName(npchar)+", mais j'ai d'autres affaires avec vous.")),NPCharRepPhrase(npchar,pcharrepphrase("Tiens ta langue, vieux soûlard, j'ai affaire avec toi","Tu es malade à cause du rhum, je suppose. Pas que je te porte dans mon coeur non plus. Passons aux affaires."),pcharrepphrase("Tu m'as déjà escroqué, vaurien ! J'ai affaire avec toi.","Votre ironie est inappropriée. J'ai d'autres affaires avec vous.")),npchar,Dialog.CurrentNode);
			link.l2.go = "business";
			/*link.l3 = HeroStringReactionRepeat(NPCharRepPhrase(npchar,pcharrepphrase("D'abord les affaires, puis la fête. Je veux vous demander quelque chose.","Pas maintenant. J'ai besoin d'informations."),pcharrepphrase("Au diable avec vos prix ! D'abord, vous allez me dire tout ce dont j'ai besoin."," Avec plaisir. Je voulais demander quelque chose.")),NPCharRepPhrase(npchar,pcharrepphrase("Merci pour le conseil, vieux meurtrier. Je voulais te demander quelque chose.","J'avais une question particulière."),pcharrepphrase("L'or peut attendre. Je voulais te demander quelque chose.","Oui, je suis d'accord. Je voulais vous demander quelque chose.")),NPCharRepPhrase(npchar,pcharrepphrase("Je crois bien que vous savez ce que j'allais demander.","J'espère que vous répondrez à ma question."),pcharrepphrase("Penses-tu à autre chose qu'à tes étiquettes de prix ? Parce que c'est justement ce que j'allais te demander.","Ça ne m'intéresse pas. J'ai besoin d'informations.")),NPCharRepPhrase(npchar,pcharrepphrase("Ne t'emballe pas trop, l'ami ! Je voulais juste te poser une question.","Ne t'emballe pas trop, sinon tu vas faire une attaque. Réponds juste à une question, et je m'en irai."),pcharrepphrase("Je ne m'attends pas à ce que tu dises quelque chose d'intelligent, puisque tu as le cerveau d'un cafard. Mais tu dois sûrement savoir quelque chose.","Je ne vous retarderai pas longtemps. Juste une question.")),npchar,Dialog.CurrentNode);*/
			//link.l3 = "Je suis sur une autre affaire.";
			//link.l3.go = "quests";
			// --> Jason, генер почтового курьера 2 уровня
			if (CheckAttribute(PChar, "questTemp.WPU.Postcureer.LevelUp"))
			{
				if (pchar.questTemp.WPU.Postcureer.TargetPortmanID == npchar.id)
				{
					link.l12 = "Je vous ai apporté une liste de prix de la ville de "+XI_ConvertString("Colony"+pchar.questTemp.WPU.Postcureer.StartCity+"Gen")+".";
					link.l12.go = "Postcureer_LevelUp_ForAll";
				}
			}
			//<--генер почтового курьера 2 уровня	
						
			//Jason --> мини-квест Дефицитный товар
			if (CheckAttribute(pchar, "questTemp.Wine.Trader") && NPChar.location == pchar.questTemp.Wine.City + "_store" && !CheckAttribute(pchar, "questTemp.Wine.fail"))
			{
				link.l13 = "Je voudrais vous acheter un lot de vin européen - cinquante à soixante bouteilles. On m'a dit que vous en aviez suffisamment en stock.."; 
				link.l13.go = "Wine_Trader";
			}
			if (CheckAttribute(pchar, "questTemp.Wine.Repeat2") && NPChar.location == pchar.questTemp.Wine.City + "_store" && CheckCharacterItem(pchar, "letter_1") && !CheckAttribute(pchar, "questTemp.Wine.fail"))
			{
				link.l13 = "Bonjour à nouveau. S'il vous plaît, jetez un œil à cette lettre - peut-être reconsidérerez-vous votre position concernant la vente de vin à moi ?"; 
				link.l13.go = "Wine_Repeat2";
			}
			if (CheckAttribute(pchar, "questTemp.Wine.wait") && NPChar.location == pchar.questTemp.Wine.City + "_store" && !CheckAttribute(pchar, "questTemp.Wine.fail"))
			{
				link.l13 = "C'est encore moi. Pouvons-nous reprendre notre affaire de vin interrompue ? J'ai réussi à réunir assez d'argent."; 
				link.l13.go = "Wine_Price";
			}
			// <-- мини-квест Дефицитный товар
			
			// туториал Мартиника
			if(CheckAttribute(pchar, "questTemp.Sharlie.Lock") && NPChar.City == "FortFrance")
			{
				if (!CheckAttribute(npchar, "quest.storehelper") && pchar.questTemp.Sharlie == "ship")
				{
					Link.l2 = "Ecoutez, monsieur, je cherche un emploi. Pas vraiment un travail à temps plein ou à trimer en portant des sacs de cargaison, mais plutôt à faire des commissions, pour ainsi dire. Auriez-vous besoin d'assistance ?";
					Link.l2.go = "Sharlie_storehelper";
				}
				if (CheckAttribute(pchar, "questTemp.Sharlie.Storehelper") && pchar.questTemp.Sharlie.Storehelper == "return")
				{
					Link.l2 = "J'ai accompli ta commission. J'ai trouvé Gralam Lavoie.";
					Link.l2.go = "Sharlie_storehelper_2";
				}
				if (CheckAttribute(pchar, "questTemp.Sharlie.Storehelper") && pchar.questTemp.Sharlie.Storehelper == "choise")
				{
					Link.l2 = "Rencontrez votre nouvel assistant, monsieur.";
					Link.l2.go = "Sharlie_storehelper_11";
				}
				if (CheckAttribute(pchar, "questTemp.Sharlie.Storehelper") && pchar.questTemp.Sharlie.Storehelper == "final")
				{
					Link.l2 = "C'est encore moi, monsieur. Je suis venu pour ma récompense.";
					Link.l2.go = "Sharlie_storehelper_13";
				}
				if (CheckAttribute(pchar, "questTemp.Sharlie.Junglejew") && !CheckAttribute(npchar, "quest.junglejew"))
				{
					link.l4 = "Regardez ces boucles d'oreilles, monsieur. Je les ai trouvées sur le corps d'un bandit qui a été tué dans la jungle. C'est clairement l'œuvre d'un fin bijoutier qui, j'en suis sûr, n'est pas d'ici. Pouvez-vous dire quelque chose à propos de ces boucles d'oreilles ?";
					link.l4.go = "Sharlie_junglejew";
				}
			}
						
			if(CheckAttribute(pchar,"GenQuest.EncGirl"))
			{
				if(pchar.GenQuest.EncGirl == "toLoverFather" && pchar.GenQuest.EncGirl.LoverFather == "store_keeper" && pchar.GenQuest.EncGirl.LoverCity == npchar.city)
				{
					link.l9 = "Bonjour, je suis venu sur invitation de votre fils."; 
					link.l9.go = "EncGirl_4";
					pchar.quest.EncGirl_GetLoverFather.over = "yes";
				}
				if(pchar.GenQuest.EncGirl == "toParents" || pchar.GenQuest.EncGirl == "FindLover")
				{
					if(pchar.GenQuest.EncGirl.Father == "store_keeper" && npchar.city == pchar.GenQuest.EncGirl.city)
					{
						link.l9 = "C'est à propos de votre fille...";
						link.l9.go = "EncGirl_1";
					}
				}				
			}			
			link.l5 = HeroStringReactionRepeat(NPCharRepPhrase(npchar,pcharrepphrase("À plus tard, vieux soûlard.","Bonne journée, "+GetAddress_FormToNPC(NPChar)+" "+GetFullName(npchar)+"."),pcharrepphrase("Caramba ! Ne pars pas, je reviendrai.","C'était un plaisir de vous avoir ici, "+GetAddress_FormToNPC(NPChar)+" "+GetFullName(npchar)+"Adieu !")),NPCharRepPhrase(npchar,pcharrepphrase("Levez l'ancre !","Adieu, mon brave."),pcharrepphrase("Hé ! Qu'est-ce que tu caches là ? Du rhum ? Non ?! D'accord, je vais aller m'humecter le gosier.","Je suis désolé, mais j'ai des affaires urgentes en ville.")),NPCharRepPhrase(npchar,pcharrepphrase("Hé hé ! Eh bien, à plus tard !","Je dois y aller. Adieu, "+GetAddress_FormToNPC(NPChar)+" "+GetFullName(npchar)+"!"),pcharrepphrase("Et n'ose même pas discuter avec moi ! Je n'ai pas de temps pour ça !","Peut-être devrais-je aller voir ce qui se passe sur mon navire. Adieu, "+GetAddress_FormToNPC(NPChar)+" "+GetFullName(npchar)+" !")),NPCharRepPhrase(npchar,pcharrepphrase("Quoi de neuf, vieux camarade ? C'est moi - "+GetFullName(pchar)+"Va cuver ton vin, je reviendrai plus tard.","Je crains que votre foie ne vous achève avant que j'aie la chance de revenir vous voir."),pcharrepphrase("Continue à compter tes guinées et doublons, vieux renard ! Je reviendrai.","J'étais heureux de te voir, "+GetAddress_FormToNPC(NPChar)+" "+GetFullName(npchar)+" !")),npchar,Dialog.CurrentNode);
			link.l5.go = "exit";
		break;
		
		case "Helen_node_1":
			dialog.text = "Que puis-je faire pour vous ? Approvisionner l'Arc-en-Ciel, vendre quelques butins ? Je doute que vous soyez intéressé par les cargaisons rentables du moment, ha-ha.";
			link.l1 = HeroStringReactionRepeat(NPCharRepPhrase(npchar,pcharrepphrase("Montre-moi ce que tu as, vieux pirate !","Je voulais juste jeter un œil à vos marchandises, mon bonhomme."),pcharrepphrase("Je jure par la potence, "+GetFullName(npchar)+", je ne te laisserai pas me dissuader ! Montre-moi tes marchandises sur-le-champ !","Jetons un coup d'œil à vos marchandises, "+GetAddress_FormToNPC(NPChar)+".")),NPCharRepPhrase(npchar,pcharrepphrase("C'est certain ! Les morts ne mordent pas ! Maintenant, qu'avez-vous dans votre cale ?","Vous feriez mieux de vaquer à vos affaires, mon brave. Quels types de marchandises pouvez-vous m'offrir ?"),pcharrepphrase("Il viendra un jour où tu deviendras mon trophée, hé-hé. Je plaisante. Montre-moi ta marchandise.","Discutons de nos affaires commerciales, "+GetAddress_FormToNPC(NPChar)+" "+GetFullName(npchar)+" ")),NPCharRepPhrase(npchar,pcharrepphrase("Que veux-je? Je veux acheter quelque chose!","Boire te mènera à ta tombe, "+GetFullName(npchar)+"Je veux jeter un oeil à vos marchandises."),pcharrepphrase("Je connais vos rabais ! Deux livres de cacao au prix de trois ! Maintenant, montre-moi tes marchandises.","C'est toujours bon. Marchandons, alors.")),"Montrez-moi vos marchandises. Moins on en dit, mieux c'est. Je suis pressé.",npchar,Dialog.CurrentNode);
			link.l1.go = "market";
			link.l2 = HeroStringReactionRepeat(NPCharRepPhrase(npchar,pcharrepphrase("Oh, j'aimerais vraiment poignarder quelqu'un, D'accord, passons aux affaires.","Passons à d'autres affaires, mon bonhomme."),pcharrepphrase("Caramba ! Je suis ici pour un autre type d'affaires !","Je veux te parler d'une affaire particulière, "+GetAddress_FormToNPC(NPChar)+" "+GetFullName(npchar)+".")),NPCharRepPhrase(npchar,pcharrepphrase("J'ai affaire avec vous, vieux pirate !","Passons aux affaires, l'ami !"),pcharrepphrase("Je jure par le diable, tu ne me tromperas pas, vaurien ! J'ai d'autres affaires avec toi !","Je suis tout à fait d'accord, "+GetAddress_FormToNPC(NPChar)+" "+GetFullName(npchar)+", je voulais discuter d'autres affaires avec vous.")),NPCharRepPhrase(npchar,pcharrepphrase("Déjà chargé ? J'ai des affaires avec vous.","Je ne suis pas venu ici pour commercer, mon bonhomme. J'ai d'autres affaires."),pcharrepphrase("Que le tonnerre te frappe pour des prix pareils ! J'ai des affaires à régler avec toi.","Les rabais sont toujours agréables, "+GetAddress_FormToNPC(NPChar)+" "+GetFullName(npchar)+", mais j'ai d'autres affaires avec vous.")),NPCharRepPhrase(npchar,pcharrepphrase("Tiens ta langue, vieux soûlard, j'ai affaire avec toi","Tu es malade à cause du rhum, je suppose. Pas que je te porte dans mon coeur, non plus. Passons aux affaires."),pcharrepphrase("Tu m'as déjà escroqué, vaurien ! J'ai des affaires avec toi.","Votre ironie est inappropriée. J'ai d'autres affaires à traiter avec vous.")),npchar,Dialog.CurrentNode);
			link.l2.go = "business";
			link.l3 = HeroStringReactionRepeat(NPCharRepPhrase(npchar,pcharrepphrase("D'abord les affaires, puis la réjouissance. Je veux te demander quelque chose.","Pas maintenant. J'ai besoin d'informations."),pcharrepphrase("Au diable tes prix ! D'abord, tu vas me dire tout ce que j'ai besoin de savoir.","C'est un plaisir. Je voulais te demander quelque chose.")),NPCharRepPhrase(npchar,pcharrepphrase("Merci pour le conseil, vieux meurtrier. Je voulais te demander quelque chose.","J'avais une question particulière."),pcharrepphrase("L'or peut attendre. Je voulais te demander quelque chose.","Oui, je suis d'accord. Je voulais vous demander quelque chose.")),NPCharRepPhrase(npchar,pcharrepphrase("Je crois bien que vous savez ce que j'allais demander.","J'espère que vous répondrez à ma question."),pcharrepphrase("Peux-tu penser à autre chose que tes étiquettes de prix ? Parce que c'est justement ce dont je voulais te parler.","Ça ne m'intéresse pas. J'ai besoin d'informations.")),NPCharRepPhrase(npchar,pcharrepphrase("Ne t'emballe pas trop, l'ami ! Je voulais juste te poser une question.","Ne vous emballez pas trop, ou vous aurez une attaque. Répondez à une seule question, et je m'en irai."),pcharrepphrase("Je ne m'attends pas à ce que tu dises quelque chose d'intelligent, puisque tu as le cerveau d'un cafard. Mais tu dois sûrement savoir quelque chose.","Je ne vous retarderai pas longtemps. Juste une question.")),npchar,Dialog.CurrentNode);
			link.l3.go = "quests";
			link.l5 = HeroStringReactionRepeat(NPCharRepPhrase(npchar,pcharrepphrase("À bientôt, vieux soûlard.","Bonne journée, "+GetAddress_FormToNPC(NPChar)+" "+GetFullName(npchar)+"."),pcharrepphrase("Caramba ! Ne partez nulle part, je reviendrai encore.","C'était un plaisir de vous avoir ici, "+GetAddress_FormToNPC(NPChar)+" "+GetFullName(npchar)+"Adieu !")),NPCharRepPhrase(npchar,pcharrepphrase("Levez l'ancre !","Adieu, mon bonhomme."),pcharrepphrase("Hey ! Qu'est-ce que tu caches là ? Du rhum ? Non ?! Très bien, je vais aller m'humecter la gorge.","Je suis désolé, mais j'ai des affaires urgentes en ville.")),NPCharRepPhrase(npchar,pcharrepphrase("Heh! Eh bien, à la prochaine!","Je dois y aller. Adieu, "+GetAddress_FormToNPC(NPChar)+" "+GetFullName(npchar)+" !"),pcharrepphrase("Et ne pense même pas à discuter avec moi ! Je n'ai pas de temps pour ça !","Peut-être devrais-je aller voir ce qui se passe sur mon navire. Adieu, "+GetAddress_FormToNPC(NPChar)+" "+GetFullName(npchar)+"!")),NPCharRepPhrase(npchar,pcharrepphrase("Quoi de neuf, vieux camarade ? C'est moi - "+GetFullName(pchar)+"Va dormir pour décuver, je reviendrai plus tard.","Je crains que votre foie ne vous achève avant que j'aie une chance de revenir vers vous."),pcharrepphrase("Continue de compter tes guinées et doublons, vieux renard ! Je reviendrai.","J'étais heureux de te voir, "+GetAddress_FormToNPC(NPChar)+" "+GetFullName(npchar)+" !")),npchar,Dialog.CurrentNode);
			link.l5.go = "exit";
		break;

		case "market":
//navy -->
			//занят ПГГ
			if (CheckFreeServiceForNPC(NPChar, "Store") != -1)	 // to_do имя сунуть
			{
				dialog.text = "Désolé, mais je suis trop occupé en ce moment. Tant de clients ! Revenez demain.";
				link.l1 = "Oh, vraiment ? Eh bien, je reviendrai plus tard, alors.";
				link.l1.go = "exit";
				break;
			}
//navy <--
			dialog.text = RandPhraseSimple("J'ai des boulets ronds, de la toile à voile, des médicaments, du bois précieux et d'autres marchandises ! Qu'est-ce qui vous intéresse ?","Voulez-vous acheter du sucre et des épices ? Ou, peut-être, du rhum et de la poudre à canon ?");
			link.l1 = pcharrepphrase(LinkRandPhrase("J'ai beaucoup de butin dans ma cale ! L'argent n'a pas d'odeur, n'est-ce pas ?","Je dois larguer le butin dans ma cale et la remplir de ton or. Ha-ha !","Oh, je sais que tu vendrais ta mère pour un sac de doublons bien pesés ! Mais j'ai juste besoin de réapprovisionner mes stocks."),LinkRandPhrase("Je veux vendre ma cargaison et renflouer mes provisions.","Je veux acheter des marchandises à vendre.","Montrez-moi les boulets de canon, les bombes et ce genre de choses."));
			link.l1.go = "trade_1";

			if(CheckFunctionalTreasurer() && CheckAttribute(PChar, "TransferGoods.Enable")) // Автозакупка товаров
			{
				link.l5 = "Mon intendant fera tous les achats nécessaires...";
				link.l5.go = "TransferGoods";
			}
			
			link.l3 = pcharrepphrase(RandPhraseSimple("Je pars sans faire de commerce. A bientôt !","Je vais aller m'humecter le gosier. Reste là !"),RandPhraseSimple("Non, je n'ai pas le temps de commercer pour l'instant. Adieu.","Je suis désolé, j'ai des affaires urgentes à régler. Au revoir !"));
			link.l3.go = "exit";
		break;
		
		case "EncGirl_1":
			dialog.text = "Je suis tout ouïe.";
			link.l1 = "J'ai amené ton fugitif.";
			link.l1.go = "EncGirl_2";
		break;
		
		case "EncGirl_2":
			dialog.text = "Oh, capitaine, merci beaucoup ! Comment va-t-elle ? Est-elle blessée ? Cela fait un jour qu'elle s'est enfuie, vilaine fille. Est-ce que j'ai l'air de lui vouloir du mal ? Je lui ai trouvé un mari. Un mariage arrangé. Un fiancé riche et jeune. Il peut être mal dégrossi, mais qui se soucie des traits du visage. Non ! Elle essaie toujours de tout obtenir à sa manière. Comme sa mère l'a toujours fait, diantre !\nBien qu'elle ne serait pas née si sa mère ne s'était pas enfuie avec un idiot prometteur il y a longtemps... enfin, peu importe... La jeunesse est naïve, stupide et cruelle.";
			link.l1 = "Bien sûr, vous êtes le père et c'est à vous de décider, mais je ne me presserais pas avec le mariage...";
			link.l1.go = "EncGirl_3";
		break;
		
		case "EncGirl_3":
			dialog.text = "Qu'est-ce que tu sais ? As-tu des enfants toi-même ? Non ? Parle-moi quand tu en auras...\nOui... J'ai promis une récompense à l'homme qui la ramènera, tiens, prends-la.";
			link.l1 = "Merci. Et garde un oeil sur elle. J'ai le pressentiment qu'elle ne s'arrêtera pas là.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("EncGirl_ToLoverParentsExit");
		break;
		
		case "EncGirl_4":
			if(sti(pchar.GenQuest.EncGirl.LoverFatherAngry) == 0)
			{
				dialog.text = "Oh, alors vous êtes "+GetSexPhrase("ce capitaine, qui a apporté","cette demoiselle, qui a apporté")+"mon fils prodigue avec une jeune mariée ?";
				link.l1 = "Oui, je les ai aidés à s'échapper.";
				link.l1.go = "EncGirl_5";
			}
			else
			{
				dialog.text = "Oh, là "+GetSexPhrase("il est, notre bienfaiteur","elle est, notre bienfaitrice")+"J'attends une récompense, je suppose ?";
				link.l1 = "Eh bien, je me passerai de récompense, mais vos remerciements suffiraient.";
				link.l1.go = "EncGirl_6";			
			}
		break;
		
		case "EncGirl_5":
			dialog.text = "Je vous suis très reconnaissant de ne pas avoir abandonné mon enfant dans une situation désespérée et de l'avoir aidé à trouver une issue à une situation délicate. Permettez-moi de vous remercier et acceptez cette modeste somme ainsi qu'un cadeau de ma part.";
			link.l1 = "Merci. Aider ce jeune couple fut un plaisir.";
			link.l1.go = "EncGirl_5_1";
		break;
		
		case "EncGirl_6":
			dialog.text = "Merci ? Quels mercis ?! Cet imbécile traîne sans emploi depuis six mois - et regardez-le, il a assez de temps pour ses amourettes ! Quand j'avais son âge, je menais déjà mes propres affaires ! Pff ! Un gouverneur a une fille à marier - et ce crétin a ramené une traînée sans foi ni loi chez moi et a osé demander ma bénédiction !";
			link.l1 = "Hmm... Apparemment, vous ne croyez pas aux sentiments sincères ?";
			link.l1.go = "EncGirl_6_1";		
		break;
		
		case "EncGirl_5_1":
			AddMoneyToCharacter(pchar, sti(pchar.GenQuest.EncGirl.sum));
			GiveItem2Character(pchar, pchar.GenQuest.EncGirl.item);
			AddQuestRecord("JungleGirl", "18");
			CloseQuestHeader("JungleGirl");
			DeleteAttribute(pchar, "GenQuest.EncGirl");
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
		case "EncGirl_6_1":
			dialog.text = "Quels sentiments ? De quels genres de sentiments parlez-vous ? Sentiments... comment peut-on être si léger d'esprit à votre âge ?! Honte à vous de céder aux caprices des jeunes et de vous comporter comme un entremetteur ! Non seulement vous avez pris une fille de sa maison, mais vous avez aussi ruiné la vie de mon novice. Il n'y aura pas de remerciements pour vous. Adieu.";
			link.l1 = "D'accord, et la même chose pour vous...";
			link.l1.go = "EncGirl_6_2";
		break;
		
		case "EncGirl_6_2":
			ChangeCharacterComplexReputation(pchar,"nobility", -1);
			AddQuestRecord("JungleGirl", "19");
			AddQuestUserData("JungleGirl", "sSex", GetSexPhrase("",""));
			AddQuestUserData("JungleGirl", "sSex1", GetSexPhrase("",""));
			CloseQuestHeader("JungleGirl");
			DeleteAttribute(pchar, "GenQuest.EncGirl");
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();		
		break;
		
		// Warship. Автозакупка товаров -->
		case "TransferGoods":
			ok = (rColony.from_sea == "") || (Pchar.location.from_sea == rColony.from_sea);
			
			if(sti(Pchar.Ship.Type) != SHIP_NOTUSED && ok)
			{
				dialog.text = LinkRandPhrase(" ...Deja fait. Maintenant, il ne reste plus qu'à decider, quel navire charger.","Votre trésorier s'en est déjà chargé. Décidons maintenant quel navire doit être chargé.","Oui, "+PChar.name+", je sais. Il m'a déjà rendu visite. Alors, quel navire allons-nous charger?");
					
				for(i=0; i<COMPANION_MAX; i++)
				{
					cn = GetCompanionIndex(PChar, i);
					if(cn > 0)
					{
						chref = GetCharacter(cn);
						if(!GetRemovable(chref)) continue;
						
						attrL = "l"+i;
						Link.(attrL)    = "It will be " + XI_ConvertString(RealShips[sti(chref.Ship.Type)].BaseName) + " '" + chref.Ship.Name + "'.";
						Link.(attrL).go = "TransferGoodsTo_" + chref.id;
					}
				}
				
				Link.l99 = "J'y ai réfléchi, rien ne me manque.";
				Link.l99.go = "exit";
			}
			else // Корабля нету
			{
				dialog.text = NPCharRepPhrase(npchar,pcharrepphrase("Tu te moques de moi ? Où est ton navire ? Je ne le vois pas à quai !","Je jure par le diable, tu ne me tromperas pas ! Ton navire n'est pas à quai !"),pcharrepphrase("Je ne vois pas votre navire dans le port, capitaine "+GetFullName(pchar)+"J'espère qu'elle n'est pas le 'Hollandais Volant' ?","Capitaine, c'est bien plus facile de charger la cargaison depuis le quai. Et je préfère procéder ainsi. Amène vite ton navire et reviens."));
				link.l1 = NPCharRepPhrase(npchar,pcharrepphrase(""+RandSwear()+"Quel tracas ! D'accord, vieux filou, à bientôt !","Je ne voulais pas te tromper, "+GetFullName(npchar)+", un navire est de l'autre côté de l'île."),pcharrepphrase("Non. Mon navire s'appelle le 'Black Pearl'. Pourquoi avez-vous pâli? Haha! Je plaisante seulement!","Merci pour le conseil, je l'utiliserai forcément."));
				link.l1.go = "exit";
			}
			break;
			
		case "TransferGoods_2": // Тут уже не проверяем, есть корабль или нету (выбрали корабль, в который груз не помещается)
			dialog.text = LinkRandPhrase("Alors, capitaine, quel navire allons-nous charger ?","Alors, quel navire doit être chargé, hein?",PChar.name+", quelle cale de navire devons-nous charger avec les marchandises ?");
				
			for(i=0; i<COMPANION_MAX; i++)
			{
				cn = GetCompanionIndex(PChar, i);
				if(cn > 0)
				{
					chref = GetCharacter(cn);
					if(!GetRemovable(chref)) continue; // Если квестовый - пропускаем
					
					attrL = "l"+i;
					Link.(attrL)    = "It will be " + XI_ConvertString(RealShips[sti(chref.Ship.Type)].BaseName) + " '" + chref.Ship.Name + "'.";
					Link.(attrL).go = "TransferGoodsTo_" + chref.id;
				}
			}
			
			Link.l99 = "J'ai changé d'avis, je n'ai besoin de rien.";
			Link.l99.go = "exit";
			break;
			
		case "TransferGoods_Start":
			chref = CharacterFromID(NPChar.CharToTransferGoodsID);
			
			iQuantityGoods = TransferGoods_CalculateWeight(chref);
			
			if(GetCargoFreeSpace(chref) >= iQuantityGoods)
			{
				if(TransferGoods_StartTransfer(chref, NPChar.City) != 0)
				{
					dialog.text = LinkRandPhrase("Tout est prêt ! Le chargement du navire sélectionné a commencé.","D'accord, le chargement des marchandises sur le navire sélectionné a commencé.","Capitaine, le chargement des marchandises sur le navire sélectionné a commencé.");
					link.l1 = "Merci. C'est un plaisir de faire affaire avec vous.";
					link.l1.go = "exit";
          SetPriceListByStoreMan(rColony); // mitrokosta обновляем список цен
					WaitDate("", 0, 0, 0, 1, 0); // Крутим время
				}
				else
				{
					dialog.text = LinkRandPhrase("Capitaine, toutes les marchandises demandées par votre trésorier sont déjà présentes à bord du navire que vous avez indiqué !","Capitaine, toutes les marchandises sont déjà à bord du navire que vous avez indiqué !","Capitaine, ce navire n'a pas besoin de service, car toutes les marchandises sont déjà là.");
					link.l1 = "Ouais, c'est ça.";
					link.l1.go = "exit";
					link.l2 = "Je suppose que je devrai choisir un autre navire, alors.";
					link.l2.go = "TransferGoods_2";
				}
			}
			else
			{
				dialog.text = LinkRandPhrase("Je crains qu'un navire de ce type ne puisse tout simplement pas contenir autant.","Capitaine, votre navire ne pourra pas contenir autant de cargaison !","Capitaine, la cale de votre navire ne peut pas prendre autant de cargaison !");
				link.l1 = "Ouais, tu as raison. Je devrai choisir un autre navire.";
				link.l1.go = "TransferGoods_2";
				link.l2 = "J'ai réfléchi... Je n'ai pas besoin d'acheter quoi que ce soit.";
				link.l2.go = "exit";
			}
			break;
		// <-- Автозакупка товаров

		case "trade_1":
            ok = (rColony.from_sea == "") || (Pchar.location.from_sea == rColony.from_sea);
		    if (sti(Pchar.Ship.Type) != SHIP_NOTUSED && ok)
			{
			    NextDiag.CurrentNode = NextDiag.TempNode;
			    DialogExit();
			    Pchar.PriceList.StoreManIdx = rColony.index; // boal 27.02.05
			    LaunchStore(sti(rColony.StoreNum));
			}
			else
			{
			    dialog.text = NPCharRepPhrase(npchar,pcharrepphrase("Tu te moques de moi ? Où est ton navire ? Je ne le vois pas à la jetée !","Je jure par le diable, tu ne me duperas pas ! Ton navire n'est pas à quai !"),pcharrepphrase("Je ne vois pas votre navire dans le port, capitaine "+GetFullName(pchar)+" Je n'espère pas qu'elle soit le 'Hollandais Volant' ?","Capitaine, c'est bien plus facile de charger la cargaison depuis le quai. Amenez votre navire rapidement et revenez."));
				link.l1 = NPCharRepPhrase(npchar,pcharrepphrase(""+RandSwear()+"Quel tracas ! D'accord, vieux roublard, à bientôt !","Je ne voulais pas te tromper, "+GetFullName(npchar)+", un navire est de l'autre côté de l'île."),pcharrepphrase("Non. Mon navire s'appelle la 'Perle Noire'. Pourquoi es-tu devenu pâle ? Haha ! Je plaisante !","Merci pour le conseil, ils l'utiliseront."));
			    link.l1.go = "exit";//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
			}
		break;

		case "storage_0":
			NPChar.MoneyForStorage = GetNpcQuestPastMonthParam(NPChar, "Storage.Date") * sti(NPChar.Storage.MoneyForStorage); 
			if(sti(NPChar.MoneyForStorage) > 0) 
			{
				dialog.text = "Quant au loyer, tu me dois toujours "+FindRussianMoneyString(sti(NPChar.MoneyForStorage))+".";
				if(sti(pchar.money) >= sti(NPChar.MoneyForStorage))
				{
					link.l1 = "D'accord, je paierai le loyer maintenant.";
					link.l1.go = "storage_3";
				}
				else
				{
					link.l1 = "Je reviendrai plus tard.";
					link.l1.go = "exit";
				}
			}		
			else
			{
				dialog.text = "Viens.";
				link.l1 = "Merci.";
				link.l1.go = "storage_2";
			}
			link.l2 = "Non, j'ai changé d'avis.";
			link.l2.go = "exit"; 						
		break;
		
		case "storage_01":
			NPChar.MoneyForStorage = GetStoragePriceExt(NPChar, pchar); 
			dialog.text = "Ouais, j'ai un entrepôt dans le port - il peut contenir 50000 quintaux de cargaison. Pour "+FindRussianMoneyString(sti(NPChar.MoneyForStorage))+"  par mois, je peux assurer la garde de vos marchandises. "+"Cela inclut la garde, la protection contre l'inondation et la lutte contre les rats. Qu'en dites-vous ? Aussi... Je vais avoir besoin d'un mois de paiement d'avance.";	
			link.l1 = "Costume. Puis-je y jeter un œil ? Avez-vous beaucoup de rats là-bas ?";
			link.l1.go = "storage_1";
			link.l2 = "Non, je demande juste. Je peux l'utiliser quand c'est nécessaire...";
			link.l2.go = "exit";
		break;
		
		case "storage_1":
			NPChar.MoneyForStorage = GetStoragePriceExt(NPChar, pchar); 
			dialog.text = "Comme je l'ai dit, j'exige un paiement pour un mois à l'avance. Et pas de rats !";
			if(sti(pchar.money) >= sti(NPChar.MoneyForStorage))
			{
				link.l1 = "Vous êtes... plutôt mercantile, je dois dire. Voici votre argent - je louerai ce hangar.";
				link.l1.go = "storage_11";
			}
			else
			{
				link.l1 = "Vous êtes... plutôt mercantile, je dois dire. D'accord, je reviendrai bientôt avec l'argent.";
				link.l1.go = "exit";
			}
		break;
		
		case "storage_11":
			AddMoneyToCharacter(pchar, -makeint(NPChar.MoneyForStorage)); 
			NPChar.Storage.MoneyForStorage = NPChar.MoneyForStorage;
			NPChar.Storage.Activate = true;
			Achievment_Set("ach_67"); // ugeen 2016
			SaveCurrentNpcQuestDateParam(NPChar, "Storage.Date");
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			LaunchStorage(sti(rColony.StoreNum));			
		break;
				
		case "storage_2":			
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			LaunchStorage(sti(rColony.StoreNum));			
		break;
		
		case "storage_3":			
			AddMoneyToCharacter(pchar, -sti(NPChar.MoneyForStorage)); 
			NPChar.MoneyForStorage = GetStoragePriceExt(NPChar, pchar);
			NPChar.Storage.MoneyForStorage = NPChar.MoneyForStorage;
			SaveCurrentNpcQuestDateParam(NPChar, "Storage.Date");
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			LaunchStorage(sti(rColony.StoreNum));			
		break;		

		case "storage_04":
			dialog.text = "Vous partez déjà ? Quel dommage - c'est vraiment un endroit excellent avec de très bonnes conditions. Je vous assure que vous ne trouverez nulle part ailleurs dans les Caraïbes une offre comme celle-ci.";
			link.l1 = "J'ai dit - absoudre. Ou suggérez-vous que je paie pour stocker de l'air ? Cherchez un autre locataire.";
			link.l1.go = "storage_4";
			link.l2 = "Nulle part dans les Caraïbes, dites-vous ? Très bien, je vais le mettre de côté pour un moment, alors.";
			link.l2.go = "exit";
		break;
		
		case "storage_4":
			NPChar.MoneyForStorage = GetNpcQuestPastMonthParam(NPChar,"Storage.Date") * sti(NPChar.Storage.MoneyForStorage); 
			if(sti(NPChar.MoneyForStorage) > 0) 			
			{
				dialog.text = "Et pour le loyer, tu me dois encore "+FindRussianMoneyString(sti(NPChar.MoneyForStorage))+".";
				if(sti(pchar.money) >= sti(NPChar.MoneyForStorage))			
				{
					link.l1 = "D'accord.";
					link.l1.go = "storage_5";
				}
			}
			else
			{
				dialog.text = "Rassemblez vos marchandises, et je fermerai l'entrepôt.";
				link.l1 = "Bien.";
				link.l1.go = "storage_6";
			}
		break;
		
		case "storage_5":
			SetStorageGoodsToShip(&stores[sti(rColony.StoreNum)]);
			AddMoneyToCharacter(pchar, -sti(NPChar.MoneyForStorage)); 
			NPChar.Storage.NoActivate = true;
			DeleteAttribute(NPChar,"Storage.Activate");
			DialogExit();
		break;
		
		case "storage_6":
			SetStorageGoodsToShip(&stores[sti(rColony.StoreNum)]);
			DeleteAttribute(NPChar,"Storage.Activate");
			NPChar.Storage.NoActivate = true;
			DialogExit();
		break;		

		case "business":
			iTest = 0;			
	
	
			//Jason --> генератор Сомнительное предложение
			/*if (hrand(3) == 1 && !CheckAttribute(pchar, "GenQuest.Contraoffer.Trader") && !CheckAttribute(pchar, "GenQuest.Contraoffer.Slaves.Yes") && sti(npchar.nation) != PIRATE && 7-sti(RealShips[sti(pchar.ship.type)].Class) > 0) 
			{
				if (!CheckAttribute(npchar, "Contraoffer") || GetNpcQuestPastDayParam(npchar, "Contraoffer") >= 30) 
				{
					dialog.text = "Oh! Vous arrivez juste à temps, capitaine. J'aimerais vous demander de me rendre un service.";
					link.l1 = "Écoutons."; 
					link.l1.go = "Contraoffer";
					break;
				}
			}
		
			if (CheckAttribute(pchar, "GenQuest.Contraoffer.Trader") && NPChar.location == pchar.GenQuest.Contraoffer.Trader.City + "_store") 
			{
				dialog.text = "Je suis tout ouïe, capitaine.";
				link.l5 = "J'ai apporté votre commande."; 
				link.l5.go = "Contraoffer_check";
			}
			
			if (!CheckAttribute(pchar, "GenQuest.Contraoffer.Slaves") && sti(npchar.quest.Contraoffer.chance) == 2 && GetNpcQuestPastDayParam(npchar, "Contraoffer") >= 30) //единичный вариант за всю игру, ака 'пасхалка'
			{
				dialog.text = "Oh ! Vous arrivez juste à temps, capitaine. J'ai besoin d'une faveur spéciale.";
				link.l5 = "Écoutons."; 
				link.l5.go = "Contraoffer_slaves";
				break;
			}
			
			if (CheckAttribute(pchar, "GenQuest.Contraoffer.Slaves.Yes") && NPChar.location == pchar.GenQuest.Contraoffer.Slaves.City + "_store") 
			{
				dialog.text = "Je suis tout ouïe, capitaine.";
				link.l5 = "Je vous ai apporté les esclaves."; 
				link.l5.go = "Contraoffer_slaves_check";
			}*/
			// <-- генератор Сомнительное предложение
	
			//Jason --> генератор Неудачливый вор
			if (CheckAttribute(pchar, "GenQuest.Device.Shipyarder") && NPChar.location == pchar.GenQuest.Device.Shipyarder.City + "_store" && pchar.GenQuest.Device.Shipyarder == "begin" && !CheckAttribute(npchar, "quest.Device"))
			{
   				link.l16 = "Ecoutez, vous traitez toutes sortes de marchandises... Hier ou aujourd'hui - quelqu'un vous a-t-il proposé d'acheter "+pchar.GenQuest.Device.Shipyarder.Type+"?";
				link.l16.go = "Device_Trader";
			}
			// <-- генератор Неудачливый вор
			
			//Jason --> генератор Место под солнцем
			// belamour legendary edition втречается чаще
			if (!CheckAttribute(pchar, "GenQuest.Sunplace.Trader") && !CheckAttribute(npchar, "quest.Sunplace") && sti(npchar.nation) != PIRATE && sti(pchar.rank) < 20 && hrand(2) == 2 && !CheckAttribute(pchar, "questTemp.Shadowtrader_Block")) 
			{
				dialog.text = "Capitaine, je voudrais vous demander une faveur, et je suis prêt à vous payer généreusement si vous acceptez.";
				link.l1 = "Intéressant. Eh bien, quel est le problème ?"; 
				link.l1.go = "Sunplace_begin";
				break;
			}
			
			if (CheckAttribute(pchar, "GenQuest.Sunplace.Trader") && pchar.GenQuest.Sunplace.Trader == "complete" && npchar.location == pchar.GenQuest.Sunplace.Trader.City + "_store") 
			{
				dialog.text = "Capitaine, je suis ravi de vous voir. Je sais déjà que vous avez satisfait ma demande concernant "+pchar.GenQuest.Sunplace.Trader.Enemyname+".";
				link.l1 = "Heh ! Ça c'est sûr. "+GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.Sunplace.Trader.ShipType),"Nom")))+" "+pchar.GenQuest.Sunplace.Trader.ShipName+" et la cargaison - "+GetGoodsNameAlt(sti(pchar.GenQuest.Sunplace.Trader.Goods))+", n'appartiennent plus à votre rival."; 
				link.l1.go = "Sunplace_complete";
				break;
			}
			
			if (CheckAttribute(pchar, "GenQuest.Sunplace.Trader") && pchar.GenQuest.Sunplace.Trader == "complete_murder" && npchar.location == pchar.GenQuest.Sunplace.Trader.City + "_store") 
			{
				dialog.text = "Mon Seigneur, capitaine... Pourquoi l'avez-vous tué? Je vous ai seulement demandé de couler son navire! Sainte Vierge, j'ai maintenant le sang d'un innocent sur les mains...";
				link.l1 = "Hé ! Qu'est-ce qui t'arrive, "+npchar.name+"? Qui s'en soucie - il ne vous importunera plus jamais, et c'est ce qui compte !"; 
				link.l1.go = "Sunplace_complete_murder";
				break;
			}
			// <-- генератор Место под солнцем
			
//navy -->
			//занят ПГГ
			iTmp = CheckAvailableTaskForNPC(NPChar, PGG_TASK_WORKONSTORE);
			if (iTmp != -1)
			{
				dialog.text = "J'avais un travail, mais "+GetFullName(&Characters[iTmp])+"a déjà entrepris de le faire pour moi.";
				link.l1 = "Oh, vraiment ? Eh bien, je reviendrai plus tard, alors.";
				link.l1.go = "exit";
				break;
			}
//navy <--
			dialog.text = NPCharRepPhrase(npchar,"Quelle affaire?! Dis-moi tout!","Je vous écoute. Quelle est cette affaire dont vous parlez ?");
            ok = (rColony.from_sea == "") || (Pchar.location.from_sea == rColony.from_sea);
            if (sti(Pchar.Ship.Type) != SHIP_NOTUSED && ok)
			{
    			if (CheckQuestAttribute("generate_trade_quest_progress", "begin") || CheckQuestAttribute("generate_trade_quest_progress",  "failed"))
    			{
    				if (pchar.CargoQuest.TraderID == npchar.id )
    				{
    					link.l1 = RandPhraseSimple("J'ai un lot de marchandises pour votre magasin dans la cale de mon navire.","Mon navire a été affrété pour livrer les marchandises à votre magasin. Les produits sont en cours de déchargement.");
    					link.l1.go = "generate_quest_2";
    				}
    				else
    				{
                        if (!CheckQuestAttribute("generate_trade_quest_progress",  "failed") && pchar.CargoQuest.GiveTraderID == npchar.id && GetNationRelation2MainCharacter(sti(characters[GetCharacterIndex(pchar.CargoQuest.TraderID)].nation)) == RELATION_ENEMY)
                        {
                            link.l1 = "Malheureusement, je suis contraint d'abandonner leurs engagements. La situation politique ne me permet pas de livrer les marchandises.";
            				link.l1.go = "generate_quest_cannot_done";
                        }
                        else
                        {
                            if (rand(1) == 1)
                            {
                                link.l1 = RandPhraseSimple("Je peux vous proposer d'affréter mon navire pour transporter des marchandises.","J'ai un grand navire et je peux livrer n'importe quelle cargaison où que vous en ayez besoin.");
            				    link.l1.go = "generate_quest_not_closed";
        				    }
    				    }
    				}
    			}
    			else
    			{
    				link.l1 = "Souhaiteriez-vous affréter un navire, "+GetAddress_FormToNPC(NPChar)+" ? J'ai un navire fiable et un équipage expérimenté.";
    				link.l1.go = "generate_quest";
    			}
				link.l22 = "Je suis sur une autre affaire.";
				link.l22.go = "quests";
    			// --> на кредитный генератор
    			if (CheckAttribute(pchar, "GenQuest.LoanChest.TakeChest") && sti(pchar.GenQuest.LoanChest.TargetIdx) == sti(NPChar.index))
    			{
	                link.l3 = pcharrepphrase(RandPhraseSimple("Oh, j'étais vraiment épuisé en mer... Eh bien, l'ami, l'argent est un vrai problème pour moi en ce moment.","D'accord, vieux renard, discutons de nos affaires financières."),RandPhraseSimple("Je souhaiterais discuter des questions financières avec vous.","Discutons des affaires financières, nous devons en parler."));,
	
	                link.l3.go = "LoanForAll";
                }
				//квест мэра - на связь с нашим шпионом
  				if (CheckAttribute(pchar, "GenQuest.Intelligence") && pchar.GenQuest.Intelligence.SpyId == npchar.id && pchar.GenQuest.Intelligence == "") 
				{
					link.l4 = RandPhraseSimple("Je suis ici à la demande d'un homme. Son nom est gouverneur "+GetFullName(characterFromId(pchar.GenQuest.Intelligence.MayorId))+".",GetFullName(characterFromId(pchar.GenQuest.Intelligence.MayorId))+" m'a envoyé vers vous. Je suis censé récupérer quelque chose...");
					link.l4.go = "IntelligenceForAll";
				}	
				
				//homo 25/06/06 слухи
                link.l6 = pcharrepphrase(RandPhraseSimple("Peux-tu me raconter les derniers potins ? De toute façon, tu traînes ici toute la journée.","Ne fais pas d'histoires, vieux filou - mieux vaut me dire ce qu'il y a de nouveau sur la terre ferme ?"),RandPhraseSimple("Il me semble que j'ai passé une éternité en mer. Quelles sont les nouvelles dans votre région ?","Vous connaissez probablement toutes les dernières nouvelles ? Qu'est-ce qui s'est passé d'important ?"));,

    		    link.l6.go = "rumours_trader";

				// ugeen --> склад товаров для ГГ
				if(CheckAttribute(NPChar,"Storage") && Pchar.location.from_sea == "Pirates_town")
				{
					if(CheckAttribute(NPChar,"Storage.Activate"))
					{
						link.l7 = "Emmenez-moi à l'entrepôt. Je veux voir dans quel état il est.";
						link.l7.go = "storage_0";
						link.l8 = "J'ai décidé de libérer l'entrepôt. Je n'en ai pas besoin pour le moment.";
						link.l8.go = "storage_04";
					}
					else
					{
						if(!CheckAttribute(NPChar,"Storage.NoActivate"))
						{
							link.l7 = "Excusez-moi, mon bonhomme - ne louez-vous pas des entrepôts, par hasard ?";
							link.l7.go = "storage_01";
						}	
					}
				}				
				// <-- ugeen
				// Jason --> квест губера на поиск дезертира
				if(CheckAttribute(pchar, "GenQuest.FindFugitive") && sti(NPChar.nation) == PIRATE)
				{
					link.l8 = "Voyez-vous, j'essaie de retrouver mon compagnon, "+pchar.GenQuest.FindFugitive.Name+" est son nom. À Port-Royal, les gens à la taverne m'ont dit qu'il se dirigeait vers votre colonie. L'avez-vous rencontré, par hasard ?";
					link.l8.go = "FindFugitiveSt";
				}
				//<-- поиск дезертира
				
				// <-- homo
				link.l99 = "Mais il n'y a pas le temps pour bavarder maintenant.";
    			link.l99.go = "no_quests";
			}
			else
			{
                link.l1 = NPCharRepPhrase(npchar,pcharrepphrase(" "+RandSwear()+"J'ai laissé le navire de l'autre côté de l'île. Je reviendrai plus tard !","Je vous prie de m'excuser, "+GetFullName(npchar)+", je viendrai plus tard. Mon navire n'a pas encore approché le quai."),pcharrepphrase("Diable ! Ces idiots n'ont pas préparé le navire pour le chargement ! Je reviendrai plus tard !","Excusez-moi, je dois donner des ordres pour amarrer mon navire au quai !"));
                link.l1.go = "exit";
				link.l22 = "Je suis sur une autre affaire.";
				link.l22.go = "quests";
    			// --> на кредитный генератор
    			if (CheckAttribute(pchar, "GenQuest.LoanChest.TakeChest") && sti(pchar.GenQuest.LoanChest.TargetIdx) == sti(NPChar.index))
    			{
	                link.l3 = pcharrepphrase(RandPhraseSimple("Oh, j'étais vraiment lessivé en mer... Eh bien, camarade, l'argent est un vrai problème pour moi en ce moment.","D'accord, vieux renard, discutons de nos affaires financières."),RandPhraseSimple("J'aimerais discuter avec vous des questions financières.","Discutons des affaires financières, nous devons en parler."));,
	
	                link.l3.go = "LoanForAll";
                }
				//квест мэра - на связь с нашим шпионом
  				if (CheckAttribute(pchar, "GenQuest.Intelligence") && pchar.GenQuest.Intelligence.SpyId == npchar.id && pchar.GenQuest.Intelligence == "") 
				{
					link.l7 = RandPhraseSimple("Je suis ici à la demande d'un homme. Son nom est gouverneur "+GetFullName(characterFromId(pchar.GenQuest.Intelligence.MayorId))+".",GetFullName(characterFromId(pchar.GenQuest.Intelligence.MayorId))+" m'a envoyé vers vous. Je suis censé récupérer quelque chose...");
					link.l7.go = "IntelligenceForAll";
				}
				// Jason --> квест губера на поиск дезертира
				if(CheckAttribute(pchar, "GenQuest.FindFugitive") && sti(NPChar.nation) == PIRATE)
				{
					link.l8 = "Voyez-vous, j'essaie de trouver mon compagnon, "+pchar.GenQuest.FindFugitive.Name+"c'est son nom. A Port-Royal, les gens de la taverne m'ont dit qu'il se dirigeait vers votre colonie. L'avez-vous rencontré, par hasard?";
					link.l8.go = "FindFugitiveSt";
				}
				//<-- поиск дезертира
			}
		break;
		
		case "generate_quest":
			if (npchar.quest.trade_date != lastspeak_date || bBettaTestMode)
			{
				npchar.quest.trade_date = lastspeak_date;
				//проверка враждебности нам страны торговца
				if (sti(NPChar.nation) != PIRATE && GetNationRelation2MainCharacter(sti(NPChar.nation)) == RELATION_ENEMY)
				{
					dialog.text = "Non, je n'ai pas besoin de vos services ! Du moins, tant que vous êtes ennemis avec "+NationNameAblative(sti(NPChar.nation))+".";
					link.l1 = "Dans ce cas, adieu.";
					link.l1.go = "exit";
				}
				else
				{
                    // проверка на проф пригодность -->
                    if (isBadReputation(pchar, 42))
                    {
                        dialog.text = RandSwear()+"Vous êtes "+GetFullName(pchar)+", n'est-ce pas ? On dit que "+RandPhraseSimple("beaucoup de choses effrayantes à votre sujet","beaucoup de vilaines choses à ton sujet")+", et je ne veux pas traiter avec vous.";
						link.l1 = RandPhraseSimple("Bien sûr - il suffit d'une erreur, et tout le monde est prêt à vous cracher dessus.",RandSwear()+"Eh bien, il y a de meilleures choses à faire en mer, "+GetFullName(npchar)+".");
						link.l1.go = "exit";
                        break;
                    }
                    // проверка на проф пригодность <--
                    int iTradeNation = GenerateNationTrade(sti(NPChar.nation));

					if (iTradeNation < 0)
					{
						dialog.text = NPCharRepPhrase(npchar,"Heh, "+GetAddress_Form(NPChar)+", je n'ai pas le temps pour les cargaisons aujourd'hui. Reviens demain.","Revenez demain. Peut-être vous ferai-je une offre avantageuse.");
						link.l1 = "Très bien, je reviendrai demain.";
						link.l1.go = "exit";
					}
					else
					{
                        int storeMan = findStoreMan(NPChar, iTradeNation);
                        if (storeMan > 0)
                        {
                            //проверяем импорт/экспорт
							iTradeGoods = GOOD_COFFEE + hrand(sti(GOOD_PAPRIKA - GOOD_COFFEE)); //Jason
    						//проверяем свободное место (при этом должно вмещаться по меньшей мере 100 единиц выбранного груза
    						RecalculateSquadronCargoLoad(pchar); // fix неверное место
    						iQuantityGoods = GetSquadronFreeSpace(pchar, iTradeGoods);
							if (sti(Goods[iTradeGoods].Weight)/sti(Goods[iTradeGoods].Units)*sti(iQuantityGoods) > 1500) iQuantityGoods = makeint(1500/(sti(Goods[iTradeGoods].Weight)/sti(Goods[iTradeGoods].Units))); //Jason: больше 1500 массы не дадим - большие фрахты только через ПУ
    						if (iQuantityGoods < 100)// это в шт. товара
    						{
    							dialog.text = NPCharRepPhrase(npchar,"Votre misérable vieille barque ne peut pas contenir tout le lot, donc il n'y aura pas de marché aujourd'hui.","Malheureusement, capitaine "+GetFullName(pchar)+", j'aurai besoin d'un navire plus spacieux pour ma livraison.");
    							link.l1 = NPCharRepPhrase(npchar,"Mon navire est correct, mais je saisis votre point de vue. Adieu.","Je comprends votre point de vue, les affaires sont les affaires. Adieu.");
    							link.l1.go = "exit";
    						}
    						else
    						{
    							iQuantityGoods = iQuantityGoods - rand(makeint(iQuantityGoods/3)) - 10;
    							iMoney = makeint((iQuantityGoods * sti(Goods[iTradeGoods].Weight) / sti(Goods[iTradeGoods].Units)) * (4+rand(3) + GetSummonSkillFromNameToOld(pchar, SKILL_COMMERCE)) + 0.5);

    							pchar.CargoQuest.iTradeGoods = iTradeGoods;
    							pchar.CargoQuest.iQuantityGoods = iQuantityGoods;
    							pchar.CargoQuest.iMoney = iMoney;
    							pchar.CargoQuest.iTradeNation = iTradeNation;
    							pchar.CargoQuest.iDaysExpired = 25 + rand(5);
    							
    							pchar.CargoQuest.iTradeColony = Characters[storeMan].city;
    							pchar.CargoQuest.iTradeIsland = GetIslandByCityName(Characters[storeMan].city);
    							pchar.CargoQuest.TraderID     = Characters[storeMan].id;
    							pchar.CargoQuest.GiveTraderID = NPChar.id;
                                SaveCurrentQuestDateParam("CargoQuest");
    							string sNation = XI_ConvertString("Colony"+Characters[storeMan].city);
                                sTemp = "";
                                if (pchar.CargoQuest.iTradeIsland != Characters[storeMan].city)
								{
                                    sTemp = ", which is on " + XI_ConvertString(pchar.CargoQuest.iTradeIsland+"Dat");
                                }
                                dialog.text = "Oh ! J'allais justement te demander une faveur. Tu vois, j'ai besoin de livrer la cargaison de "+GetGoodsNameAlt(iTradeGoods)+" en quantité de "+FindRussianQtyString(iQuantityGoods)+" à la ville de "+sNation+sTemp+", et le plus tôt sera le mieux. Si tu parviens à le faire pour "+FindRussianDaysString(makeint(pchar.CargoQuest.iDaysExpired))+", puis à l'arrivée vous recevrez "+FindRussianMoneyString(iMoney)+" comme votre récompense. Que dites-vous?";
    							link.l1 = "Je pense que je suis d'accord.";
    							link.l1.go = "exit_trade";
    							link.l2 = "Ce n'est probablement pas pour moi.";
    							link.l2.go = "exit";
    						}
                        }
                        else
                        {
                            dialog.text = "Les réalités politiques dans l'archipel ne me permettent pas de commercer. "+XI_ConvertString(NationShortName(sti(NPChar.nation))+"chasseur")+" est en hostilité avec tout le monde et m'a laissé seul dans le magasin.";
    						link.l1 = "Oh ! Je suis désolé. Bonne chance.";
    						link.l1.go = "exit";
                        }
					}
				}
			}
			else
			{
				dialog.text = NPCharRepPhrase(npchar,"Va-t'en, je n'ai pas de temps pour bavarder!","Je t'ai déjà dit que je n'ai rien pour toi.");
				link.l1 = NPCharRepPhrase(npchar,"Tu dois être courtois, ou je t'apprendrai à être poli !","Oh, je suis désolé !");
				link.l1.go = "exit";
			}
		break;

		case "exit_trade":
			AddDialogExitQuest("trade_quest_open");
			Nextdiag.CurrentNode = Nextdiag.TempNode;
			DialogExit();
		break;

		case "generate_quest_2":
			if (pchar.quest.generate_trade_quest_progress == "failed")
			{
				dialog.text = RandSwear()+"Ne pensez-vous pas que vous vous êtes souvenu de cet accord un peu trop tard ? J'ai dû commander les marchandises à nouveau. Adieu.";
				link.l1 = "Veuillez me pardonner, mais j'étais pressé. Peut-être que si je couvre vos pertes, ma réputation sera rétablie ?";
				link.l1.go = "generate_quest_failed";
				link.l9 = "Tout le meilleur.";
				link.l9.go = "exit";
				ChangeCharacterComplexReputation(pchar,"nobility", -1);
			}
			else
			{
                iTradeGoods    =  makeint(pchar.CargoQuest.iTradeGoods);
                iQuantityGoods =  makeint(pchar.CargoQuest.iQuantityGoods);
                
                dialog.text = "En effet ! Je l'attends depuis un bon moment. Vous devez me livrer une cargaison de "+GetGoodsNameAlt(iTradeGoods)+"en quantité de "+FindRussianQtyString(iQuantityGoods)+" et recevez pour cela "+FindRussianMoneyString(sti(pchar.CargoQuest.iMoney))+".";
				link.l1 = "Exactement.";
				link.l1.go = "generate_quest_ready";
			}
		break;
		
		case "generate_quest_ready":
            iTradeGoods    =  makeint(pchar.CargoQuest.iTradeGoods);
            iQuantityGoods =  makeint(pchar.CargoQuest.iQuantityGoods);
            // блок кидалова нас на бабки -->
            if (rand(8) == 1 && sti(Goods[iTradeGoods].Cost) <= 44 && GetQuestPastDayParam("CargoQuest") > 5)
            {
                dialog.text = RandSwear()+"Je dois vous présenter mes excuses, "+GetAddress_Form(NPChar)+"  Vous voyez, le problème est que j'étais "+RandPhraseSimple("dans une situation embarrassante et je ne pourrai pas vous payer","j'ai déjà acheté cette cargaison à un autre vendeur pour un meilleur prix")+"Comme paiement pour votre charte, je vous propose de garder toute la cargaison que vous livriez.";
				link.l1 = RandSwear()+RandPhraseSimple("Et j'ai protégé cette maudite cargaison de tous les dangers ! J'ai tué deux cents rats à cause de ça !","Vous m'avez mis dans une impasse, et je vais devoir accepter.");
				link.l1.go = "exit";
				ChangeCharacterComplexReputation(pchar,"nobility", 2);
				AddCharacterExpToSkill(pchar, "Sailing", 60);
				AddCharacterExpToSkill(pchar, "Leadership", 20);
				AddCharacterExpToSkill(pchar, "COMMERCE", 15);

				pchar.quest.generate_trade_quest_progress = "";
				pchar.quest.generate_trade_quest.over = "yes";
                
                AddQuestRecord("DELIVERY_TRADE_QUEST", "4");
                AddQuestUserData("DELIVERY_TRADE_QUEST", "sGoodGen", GetGoodsNameAlt(iTradeGoods));
			    AddQuestUserData("DELIVERY_TRADE_QUEST", "sTargetColony",XI_ConvertString("Colony"+pchar.CargoQuest.iTradeColony+"Gen")); // belamour gen
                CloseQuestHeader("DELIVERY_TRADE_QUEST");
                break;
            }
            // блок кидалова нас на бабки <--
			if (GetSquadronGoods(pchar, iTradeGoods) < iQuantityGoods)
			{
                iTmp = iQuantityGoods - GetSquadronGoods(pchar, iTradeGoods);
                dialog.text = "Ce n'est pas tout le lot ! Selon notre accord, j'ai besoin de "+FindRussianQtyString(iTmp)+" unités de plus.";
				link.l9 = RandPhraseSimple("Oui, en effet. Je devrai compenser la pénurie alors. À plus tard.",RandSwear()+"Ces maudits rats ont gâché la cargaison. Je compenserai le manque et reviendrai.");
				link.l9.go = "exit";
                AddQuestRecord("DELIVERY_TRADE_QUEST", "8");
                AddQuestUserData("DELIVERY_TRADE_QUEST", "sHaveNotQty", iTmp);
                AddQuestUserData("DELIVERY_TRADE_QUEST", "sGoodGen", GetGoodsNameAlt(iTradeGoods));
			}
			else
			{
                dialog.text = "Excellent ! Voici votre récompense, capitaine "+GetFullName(pchar)+".";
				link.l1 = "C'était un plaisir de travailler avec vous.";
				link.l1.go = "exit";
				ChangeCharacterComplexReputation(pchar,"nobility", 3);
				AddCharacterExpToSkill(pchar, "Sailing", 100);
				AddCharacterExpToSkill(pchar, "Leadership", 30);
				AddCharacterExpToSkill(pchar, "COMMERCE", 100);

				AddMoneyToCharacter(pchar, makeint(pchar.CargoQuest.iMoney));
				pchar.quest.generate_trade_quest_progress = "";
				pchar.quest.generate_trade_quest.over = "yes";
				RemoveCharacterGoods(pchar, makeint(pchar.CargoQuest.iTradeGoods), makeint(pchar.CargoQuest.iQuantityGoods));
				
                OfficersReaction("good");
                
                AddQuestRecord("DELIVERY_TRADE_QUEST", "2");
                AddQuestUserData("DELIVERY_TRADE_QUEST", "sGoodGen", GetGoodsNameAlt(iTradeGoods));
			    AddQuestUserData("DELIVERY_TRADE_QUEST", "sTargetColony",XI_ConvertString("Colony"+pchar.CargoQuest.iTradeColony+"Gen"));
                CloseQuestHeader("DELIVERY_TRADE_QUEST");
			}
		break;
		
		case "generate_quest_failed":
            iTradeGoods    =  makeint(pchar.CargoQuest.iTradeGoods);
            iQuantityGoods =  makeint(pchar.CargoQuest.iQuantityGoods);
            iMoney =  3*makeint(iQuantityGoods * sti(Goods[iTradeGoods].Cost) / sti(Goods[iTradeGoods].Units));
			dialog.text = "D'accord... La somme de "+FindRussianMoneyString(iMoney)+" couvrira tout juste les dommages causés par la violation des termes de notre accord.";
			link.l1 = "Parbleu ! Non, ça ne va pas du tout ! Plus jamais je ne livrerai de cargaison ! Il y a assez de cette foutaise en mer !";
			link.l1.go = "exit";
            if (sti(pchar.Money) >= iMoney)
            {
    			link.l2 = "Voici le montant requis";
    			link.l2.go = "generate_quest_failed_2";
			}
            else
            {
                AddQuestRecord("DELIVERY_TRADE_QUEST", "7");
                AddQuestUserData("DELIVERY_TRADE_QUEST", "sMoney", FindRussianMoneyString(iMoney));
    		    AddQuestUserData("DELIVERY_TRADE_QUEST", "sTargetColony",XI_ConvertString("Colony"+pchar.CargoQuest.iTradeColony+"Gen"));
            }
		break;
		
		case "generate_quest_failed_2":
            iTradeGoods    =  makeint(pchar.CargoQuest.iTradeGoods);
            iQuantityGoods =  makeint(pchar.CargoQuest.iQuantityGoods);
            iMoney =  3*makeint(iQuantityGoods * sti(Goods[iTradeGoods].Cost) / sti(Goods[iTradeGoods].Units));
			dialog.text = "Excellent. Maintenant, je peux dire à mes collègues que vous êtes toujours raisonnable dans vos transactions.";
			link.l1 = "Merci ! Je ne vous décevrai plus.";
			link.l1.go = "exit";
			ChangeCharacterComplexReputation(pchar,"nobility", 10);
			AddCharacterExpToSkill(pchar, "Sailing", -100);
			AddCharacterExpToSkill(pchar, "Leadership", -50);
			AddCharacterExpToSkill(pchar, "COMMERCE", -100);

			AddMoneyToCharacter(pchar, -iMoney);
			pchar.quest.generate_trade_quest_progress = "";
			pchar.quest.generate_trade_quest.over = "yes";

            AddQuestRecord("DELIVERY_TRADE_QUEST", "5");
            AddQuestUserData("DELIVERY_TRADE_QUEST", "sMoney", FindRussianMoneyString(iMoney));
            AddQuestUserData("DELIVERY_TRADE_QUEST", "sGoodGen", GetGoodsNameAlt(iTradeGoods));
		    AddQuestUserData("DELIVERY_TRADE_QUEST", "sTargetColony",XI_ConvertString("Colony"+pchar.CargoQuest.iTradeColony+"Gen"));
            CloseQuestHeader("DELIVERY_TRADE_QUEST");
		break;
		
		case "generate_quest_not_closed":
            iTradeGoods    =  makeint(pchar.CargoQuest.iTradeGoods);
            iQuantityGoods =  makeint(pchar.CargoQuest.iQuantityGoods);

            dialog.text = "Hmm. J'ai entendu dire que vous n'avez pas rempli vos obligations stipulées dans le contrat précédent - et vous en demandez un autre ? Vous deviez livrer la cargaison de "+LanguageConvertString(iSeaGoods,"seg_"+Goods[iTradeGoods].Name)+" à "+XI_ConvertString("Colony"+pchar.CargoQuest.iTradeColony)+".";
			link.l1 = "Oui, en effet ! Vous avez raison !";
			link.l1.go = "exit";
		break;
		
		case "generate_quest_cannot_done":
            dialog.text = RandSwear()+GetAddress_Form(NPChar)+", tu me déçois!!! Peut-être feras-tu quelque chose pour résoudre ce problème ?";
			link.l1 = "D'accord. Je ferai de mon mieux pour livrer la cargaison.";
			link.l1.go = "exit";
			link.l2 = "Non, je ne peux pas. Je suis désolé";
			link.l2.go = "generate_quest_cannot_done_2";
			
		break;
		
		case "generate_quest_cannot_done_2":
		    iTradeGoods    =  makeint(pchar.CargoQuest.iTradeGoods);
            iQuantityGoods =  makeint(pchar.CargoQuest.iQuantityGoods);
            if (GetSquadronGoods(pchar, iTradeGoods) < iQuantityGoods)
			{
				dialog.text = "Attends ! Il n'y a pas assez de marchandises à bord de ton navire ! Tu n'as pas "+FindRussianQtyString(iQuantityGoods - GetSquadronGoods(pchar,iTradeGoods))+" unités de cargaison.";
				link.l9 = RandPhraseSimple("Oui, en effet. Je vais devoir compenser la pénurie alors.",RandSwear()+"Les rats ont gâté la cargaison. J'achèterai la quantité manquante et je reviendrai.");
				link.l9.go = "exit";
			}
			else
			{
                dialog.text = "Je vois, je vois... J'accepterai le retour de la cargaison.";
    			link.l1 = "Merci ! Je ne te laisserai pas tomber à nouveau !";
    			link.l1.go = "exit";
    			ChangeCharacterComplexReputation(pchar,"nobility", -3);

				pchar.quest.generate_trade_quest_progress = "";
				pchar.quest.generate_trade_quest.over = "yes";
				RemoveCharacterGoods(pchar, makeint(pchar.CargoQuest.iTradeGoods), makeint(pchar.CargoQuest.iQuantityGoods));
                
                AddQuestRecord("DELIVERY_TRADE_QUEST", "6");
                AddQuestUserData("DELIVERY_TRADE_QUEST", "sGoodQty", FindRussianQtyString(sti(pchar.CargoQuest.iQuantityGoods)));
                AddQuestUserData("DELIVERY_TRADE_QUEST", "sGoodGen", GetGoodsNameAlt(iTradeGoods));
    		    AddQuestUserData("DELIVERY_TRADE_QUEST", "sTargetColony",XI_ConvertString("Colony"+pchar.CargoQuest.iTradeColony+"Gen")); // belamour gen
                CloseQuestHeader("DELIVERY_TRADE_QUEST");
            }
		break;
	
//Jason --> мини-квест Дефицитный товар
		case "Wine_Trader":
			dialog.text = "De quoi parlez-vous ? Clairement, vous avez été induit en erreur - je n'ai jamais traité de vin européen en de telles quantités. Une-deux bouteilles, pas plus. Mais le vin local, c'est une autre histoire - j'en ai suffisamment, et il est vendu par demi-jauge, pas par bouteilles !";
			link.l1 = "Saperlipopette ! Mais on m'avait dit...";
			link.l1.go = "Wine_Trader_1";
		break;
		
		case "Wine_Trader_1":
			dialog.text = "Je n'ai aucune idée de ce qu'on vous a dit, mais je vais le répéter : je n'ai pas de vin européen en stock. C'est tout ce que j'ai à dire à ce sujet.";
			link.l1 = "D'accord... Je vais m'en occuper alors, alors !";
			link.l1.go = "exit";
			AddQuestRecord("Wine", "5");
			AddQuestUserData("Wine", "sName", pchar.questTemp.Wine.Name);
			DeleteAttribute(pchar, "questTemp.Wine.Trader");
			pchar.questTemp.Wine.Repeat1 = "true";
		break;
		
		case "Wine_Repeat2":
			RemoveItems(PChar, "letter_1", 1);
			PlaySound("interface\important_item.wav");
			dialog.text = "Maintenant, c'est une autre histoire. Vous savez, divers types viennent ici, posant des questions inutiles. Alors, marchandons, non ?";
			link.l1 = "Bien sûr !";
			link.l1.go = "Wine_Price";
			pchar.questTemp.Wine.wait = "true";
			DeleteAttribute(pchar, "questTemp.Wine.Repeat2");
			SetFunctionTimerCondition("Wine_wait", 0, 0, 7, false);
			DelLandQuestMark(npchar);
			AddLandQuestMark(characterFromId(pchar.questTemp.Wine.ItemTraderID), "questmarkmain");
		break;
		
		case "Wine_Price":
			dialog.text = "Combien de bouteilles tu as besoin ? Le prix d'une bouteille est de 500 pesos, et le lot minimum est de 20 bouteilles.";
			link.l1 = "";
			Link.l1.edit = 4;
			link.l1.go = "Wine_Qty";
			link.l2 = "Je n'ai pas assez d'argent pour le moment. Je reviendrai plus tard.";
			link.l2.go = "Wine_Qty_exit";
		break;
		
		case "Wine_Qty":
			int iQty = sti(dialogEditStrings[4]);
			pchar.questTemp.Wine.Qty = sti(iQty);
			if (iQty < 20)
			{
				dialog.text = "Je ne suis pas un colporteur, capitaine. Si je me souviens bien, vous parliez d'une cargaison plus importante ?";
				link.l1 = "Je suis désolé... Reconsidérons alors le montant.";
				link.l1.go = "Wine_Price";
				break;
			}
			if (iQty > 70)
			{
				dialog.text = "Malheureusement, je n'ai pas autant.";
				link.l1 = "Hélas... Réexaminons alors le montant.";
				link.l1.go = "Wine_Price";
				break;
			}
			pchar.questTemp.Wine.Summ = sti(iQty)*500;
			dialog.text = ""+sti(iQty)+" Des bouteilles ? Fort bien. Cela vous coûtera "+FindRussianMoneyString(sti(pchar.questTemp.Wine.Summ))".";
			if (makeint(Pchar.money) >= sti(pchar.questTemp.Wine.Summ))
			{
				link.l1 = "Voilà.";
				link.l1.go = "Wine_Qty_1";
			}
			link.l2 = "Je n'ai pas assez d'argent en ce moment. Je reviendrai plus tard.";
			link.l2.go = "Wine_Qty_exit";
		break;
		
		case "Wine_Qty_exit":
			dialog.text = "C'est bon, mais essayez de ne pas prendre trop de temps. Ces marchandises sont très prisées ici.";
			link.l1 = "Je reviendrai bientôt !";
			link.l1.go = "exit";
		break;
		
		case "Wine_Qty_1":
			AddMoneyToCharacter(pchar, -sti(pchar.questTemp.Wine.Summ));
			dialog.text = "Voyons voir... Tout semble en ordre. Vous pouvez récupérer votre achat.";
			link.l1 = "Merci ! Bonne chance !";
			link.l1.go = "Wine_Qty_2";
		break;
		
		case "Wine_Qty_2":
			pchar.quest.Wine_wait.over = "yes";//снять прерывание
			DeleteAttribute(pchar, "questTemp.Wine.wait");
			TakeNItems(pchar, "potionwine", sti(pchar.questTemp.Wine.Qty));
			PlaySound("interface\important_item.wav");
			Log_Info ("You have received wine");
			AddQuestRecord("Wine", "8");
			DelLandQuestMark(npchar);
			DialogExit();
		break;
		// <-- мини-квест Дефицитный товар
		
// Jason --> -------------------------генератор Сомнительное предложение----------------------------------------
		int iCGood, amount;
		case "Contraoffer":
			pchar.GenQuest.Contraoffer.Trader.Goods = SelectContrabandGoods(pchar);
			while (sti(pchar.GenQuest.Contraoffer.Trader.Goods) == -1)
			{
				pchar.GenQuest.Contraoffer.Trader.Goods = SelectContrabandGoods(pchar);
			}
			iCGood = sti(pchar.GenQuest.Contraoffer.Trader.Goods);
			pchar.GenQuest.Contraoffer.Trader.Qty = makeint(15*(sti(pchar.rank)+30)/(sti(Goods[iCGood].Weight)/sti(Goods[iCGood].Units))*(8-sti(RealShips[sti(pchar.ship.type)].Class)));//количество
			pchar.GenQuest.Contraoffer.Trader.Price = sti(Goods[iCGood].Cost)/sti(Goods[iCGood].Units)*3;//цена единицы товара
			pchar.GenQuest.Contraoffer.Trader.Summ = sti(pchar.GenQuest.Contraoffer.Trader.Price)*sti(pchar.GenQuest.Contraoffer.Trader.Qty);//сумма
			pchar.GenQuest.Contraoffer.Trader.Days = 30+hrand(20);//срок
			pchar.GenQuest.Contraoffer.Trader.Chance = rand(5);//17% вероятности, что патруль накроет
			dialog.text = "Je comptais conclure une bonne affaire, mais il me manque encore une marchandise particulière pour cela - "+GetGoodsNameAlt(iCGood)+". Le problème est que cette marchandise est une contrebande dans notre colonie, donc je ne peux pas compter sur l'acheter auprès des capitaines marchands\nTout ce dont j'ai besoin est "+FindRussianQtyString(sti(pchar.GenQuest.Contraoffer.Trader.Qty))+"unités de celle-ci. Peut-être pourriez-vous me la livrer ? Je vous paierai bien, "+FindRussianMoneyString(sti(pchar.GenQuest.Contraoffer.Trader.Price))+" par unité, ce qui s'élèvera à "+FindRussianMoneyString(sti(pchar.GenQuest.Contraoffer.Trader.Summ))+". Oh, et je le besoin pas plus tard que dans "+FindRussianDaysString(sti(pchar.GenQuest.Contraoffer.Trader.Days))+"Alors, m'aideras-tu ?";
			link.l1 = "Hmm... Cela semble intéressant. J'accepte !";
			link.l1.go = "Contraoffer_1";
			link.l2 = "Livrer des marchandises de contrebande ? Désolé, pas intéressé.";
			link.l2.go = "exit";
			SaveCurrentNpcQuestDateParam(npchar, "Contraoffer");
		break;
		
		case "Contraoffer_1":
			dialog.text = "Excellent. Je suis ravi que vous ayez accepté. Donc, j'attendrai votre retour avec les marchandises.";
			link.l1 = "Je reviendrai bientôt !";
			link.l1.go = "exit";
			rColony = GetColonyByIndex(FindColony(npchar.city));
			SetNull2StoreGood(rColony, sti(pchar.GenQuest.Contraoffer.Trader.Goods));//нулим товар
			pchar.GenQuest.Contraoffer = "begin";
			pchar.GenQuest.Contraoffer.Trader = "true";
			pchar.GenQuest.Contraoffer.Trader.City = npchar.city;
			pchar.GenQuest.Contraoffer.Trader.Nation = npchar.nation;
			iCGood = pchar.GenQuest.Contraoffer.Trader.Goods;
			ReOpenQuestHeader("Contraoffer");
			AddQuestRecord("Contraoffer", "1");
			AddQuestUserData("Contraoffer", "sGoods", GetGoodsNameAlt(iCGood));
			AddQuestUserData("Contraoffer", "sGoodQty", FindRussianQtyString(sti(pchar.GenQuest.Contraoffer.Trader.Qty)));
			AddQuestUserData("Contraoffer", "sMoney", FindRussianMoneyString(sti(pchar.GenQuest.Contraoffer.Trader.Summ)));
			AddQuestUserData("Contraoffer", "sCity", XI_ConvertString("Colony"+pchar.GenQuest.Contraoffer.Trader.City+"Gen"));
			AddQuestUserData("Contraoffer", "sDays", FindRussianDaysString(sti(pchar.GenQuest.Contraoffer.Trader.Days)));
			SetFunctionTimerCondition("Contraoffer_Over", 0, 0, sti(pchar.GenQuest.Contraoffer.Trader.Days), false);
		break;
		
		case "Contraoffer_check":
			iCGood = sti(pchar.GenQuest.Contraoffer.Trader.Goods);
			amount = sti(pchar.GenQuest.Contraoffer.Trader.Qty) - GetSquadronGoods(pchar, sti(pchar.GenQuest.Contraoffer.Trader.Goods));
			if (amount > 0)
			{
				dialog.text = "Vous plaisantez ? Vous n'avez pas la quantité totale de marchandises dont j'ai besoin !";
				link.l1 = "Je suis désolé, ma faute...";
				link.l1.go = "exit";
			}
			else
			{
				dialog.text = "Voyons voir, alors. Vous deviez livrer une cargaison de "+GetGoodsNameAlt(iCGood)+" en quantité de "+FindRussianQtyString(pchar.GenQuest.Contraoffer.Trader.Qty)+". Correct?";
				link.l1 = "Exactement, "+GetAddress_FormToNPC(NPChar)+".";
				link.l1.go = "Contraoffer_pay";
			}
		break;
		
		case "Contraoffer_pay":
			dialog.text = "Merci pour votre travail. S'il vous plaît, prenez votre paiement - "+FindRussianMoneyString(sti(pchar.GenQuest.Contraoffer.Trader.Summ))+".";
		link.l1 = "Merci! C'est un plaisir de faire affaires avec vous.";
		link.l1.go = "Contraoffer_complete";
		break;
		
		case "Contraoffer_complete":
			pchar.quest.Contraoffer_Over.over = "yes";
			RemoveCharacterGoods(pchar, sti(pchar.GenQuest.Contraoffer.Trader.Goods), sti(pchar.GenQuest.Contraoffer.Trader.Qty));
			AddMoneyToCharacter(pchar, sti(pchar.GenQuest.Contraoffer.Trader.Summ));
			SaveCurrentNpcQuestDateParam(npchar, "Contraoffer");
			npchar.quest.Contraoffer.chance = rand(2);//личный шанс торговца для 'пасхалки'
			AddCharacterExpToSkill(pchar, "Sailing", 100);//навигация
			AddCharacterExpToSkill(pchar, "Commerce", 100);//торговля
			AddCharacterExpToSkill(pchar, "Leadership", 50);//авторитет
			AddCharacterExpToSkill(pchar, "Fortune", 100);//везение
			ChangeCharacterComplexReputation(pchar,"nobility", -1);
			if (pchar.GenQuest.Contraoffer.Trader.Chance == 3)
			{
				dialog.text = "Oups... Capitaine, il semble que nous ayons un problème ici...";
				link.l1 = "Qu'est-ce que c'est encore ?";
				link.l1.go = "exit";
				AddDialogExitQuestFunction("Contraoffer_Patrol");
				pchar.GenQuest.Contraoffer.Trader.busy = "true";
				pchar.quest.Contraoffer_busy.win_condition.l1 = "ExitFromLocation";
				pchar.quest.Contraoffer_busy.win_condition.l1.location = pchar.location;
				pchar.quest.Contraoffer_busy.function = "Trader_free";
			}
			else
			{
				DialogExit();
				AddQuestRecord("Contraoffer", "3");
				CloseQuestHeader("Contraoffer");
				DeleteAttribute(pchar, "GenQuest.Contraoffer.Trader");
			}
		break;
		
		case "Contraoffer_slaves"://единичный вариант за всю игру, ака 'пасхалка'
			pchar.GenQuest.Contraoffer.Slaves.Name = GetFullName(npchar);
			pchar.GenQuest.Contraoffer.Slaves.Price = 300;//цена на рабов, пока фиксированная, можно подставить формулу
			pchar.GenQuest.Contraoffer.Slaves.Qty = 300+rand(50);//количество
			pchar.GenQuest.Contraoffer.Slaves.Days = 14+rand(6);//срок
			pchar.GenQuest.Contraoffer.Slaves.Money = sti(pchar.GenQuest.Contraoffer.Slaves.Qty)*sti(pchar.GenQuest.Contraoffer.Slaves.Price);
			dialog.text = "J'ai urgemment besoin d'un lot d'esclaves - "+sti(pchar.GenQuest.Contraoffer.Slaves.Qty)+" têtes. Je suis prêt à payer "+sti(pchar.GenQuest.Contraoffer.Slaves.Price)+"pieces par âme, ce qui fera"+sti(pchar.GenQuest.Contraoffer.Slaves.Money)+" pesos in total; term - "+FindRussianDaysString(sti(pchar.GenQuest.Contraoffer.Slaves.Days))+".";
			link.l1 = "Je pense que je vais accepter. C'est une affaire gênante, mais très lucrative.";
			link.l1.go = "Contraoffer_slaves_1";
			link.l2 = "Je ne suis pas intéressé.";
			link.l2.go = "exit";
			pchar.GenQuest.Contraoffer.Slaves = "begin";
		break;
		
		case "Contraoffer_slaves_1":
			dialog.text = "Exactement - c'est en effet très rentable. Eh bien, je vais attendre votre retour avec mes esclaves.";
			link.l1 = "Je ne vous ferai pas attendre longtemps. À bientôt !";
			link.l1.go = "exit";
			pchar.GenQuest.Contraoffer.Slaves.Yes = "begin";
			pchar.GenQuest.Contraoffer.Slaves.City = npchar.city;
			ReOpenQuestHeader("Contraoffer");
			AddQuestRecord("Contraoffer", "4");
			AddQuestUserData("Contraoffer", "sDays", FindRussianDaysString(sti(pchar.GenQuest.Contraoffer.Slaves.Days)));
			AddQuestUserData("Contraoffer", "sGoodQty", FindRussianQtyString(sti(pchar.GenQuest.Contraoffer.Slaves.Qty)));
			AddQuestUserData("Contraoffer", "sMoney", FindRussianMoneyString(sti(pchar.GenQuest.Contraoffer.Slaves.Money)));
			AddQuestUserData("Contraoffer", "sCity", XI_ConvertString("Colony"+pchar.GenQuest.Contraoffer.Slaves.City+"Gen"));
			SetFunctionTimerCondition("Contraoffer_Over", 0, 0, sti(pchar.GenQuest.Contraoffer.Slaves.Days), false);
		break;
		
		case "Contraoffer_slaves_check":
			amount = sti(pchar.GenQuest.Contraoffer.Slaves.Qty) - GetSquadronGoods(pchar, GOOD_SLAVES);
			if (amount > 0)
			{
				dialog.text = "Vous plaisantez ? Vous n'avez pas tous les esclaves dont j'ai besoin !";
				link.l1 = "Je suis désolé, ma faute...";
				link.l1.go = "exit";
			}
			else
			{
				dialog.text = "Voyons voir, alors. Vous alliez me livrer un lot d'esclaves d'un montant de "+FindRussianQtyString(pchar.GenQuest.Contraoffer.Slaves.Qty)+". Correct?";
				link.l1 = "Exactement, "+GetAddress_FormToNPC(NPChar)+".";
				link.l1.go = "Contraoffer_slaves_pay";
			}
		break;
		
		case "Contraoffer_slaves_pay":
			dialog.text = "Merci pour votre travail. Veuillez accepter votre paiement - "+FindRussianMoneyString(sti(pchar.GenQuest.Contraoffer.Slaves.Money))+". Aussi, veuillez accepter ceci. Je suis certain que vous le trouverez utile.";
			link.l1 = "Merci! C'est un plaisir de faire affaire avec vous.";
			link.l1.go = "Contraoffer_slaves_complete";
		break;
		
		case "Contraoffer_slaves_complete":
			DialogExit();
			pchar.quest.Contraoffer_Over.over = "yes";
			RemoveCharacterGoods(pchar, GOOD_SLAVES, sti(pchar.GenQuest.Contraoffer.Slaves.Qty));
			AddMoneyToCharacter(pchar, sti(pchar.GenQuest.Contraoffer.Slaves.Money));
			AddQuestRecord("Contraoffer", "5");
			CloseQuestHeader("Contraoffer");
			SaveCurrentNpcQuestDateParam(npchar, "Contraoffer");
			AddCharacterExpToSkill(pchar, "Sailing", 150);//навигация
			AddCharacterExpToSkill(pchar, "Commerce", 200);//торговля
			AddCharacterExpToSkill(pchar, "Leadership", 50);//авторитет
			AddCharacterExpToSkill(pchar, "Fortune", 150);//везение
			TakeNItems(pchar, "cirass3", 1);
			ChangeCharacterComplexReputation(pchar,"nobility", -3);
			DeleteAttribute(pchar, "GenQuest.Contraoffer.Slaves.Yes");
		break;
		// <-- генератор Сомнительное предложение
		
		//Jason --> генератор Неудачливый вор
		case "Device_Trader":
			dialog.text = "Hmm, "+pchar.GenQuest.Device.Shipyarder.Type+"? Jamais entendu parler auparavant... Qu'est-ce donc, en fait ? Je n'ai jamais entendu parler d'une telle chose de toute ma vie.";
			link.l1 = "Eh bien, c'est un outil de charpentier naval, "+pchar.GenQuest.Device.Shipyarder.Describe+"Quelqu'un vous a-t-il offert quelque chose de ce genre ?";
			link.l1.go = "Device_Trader_1";
			npchar.quest.Device = "true";
		break;
		
		case "Device_Trader_1":
			if (sti(pchar.GenQuest.Device.Shipyarder.Chance1) == 0)
			{
				dialog.text = "Hmm... Oui, il y avait un type étrange. Mais il ne m'a pas dit ce que c'était, il a juste essayé de me le vendre. Mais à quoi cela me servirait-il, si je n'ai aucune idée de son utilité ? Comment pourrais-je le revendre ? Alors, j'ai simplement refusé.";
				link.l1 = "Et à quoi ressemblait-il et où est-il allé? J'ai grand besoin de cet instrument.";
				link.l1.go = "Device_Common";
			}
			else
			{
				dialog.text = "Non, rien de tel. Désolé, je ne peux pas vous aider. Renseignez-vous auprès des autres.";
				link.l1 = "Je vois. Eh bien - il est temps de me renseigner !";
				link.l1.go = "exit";
			}
		break;
		// <-- генератор Неудачливый вор

		//Jason --> генератор Место под солнцем
		case "Sunplace_begin":
			dialog.text = "La concurrence... Il n'y a pas de commerce sans elle. Des salauds avides qui cherchent à s'immiscer dans ton commerce confortable et utilisent toutes sortes de méthodes infâmes pour attirer la clientèle vers eux\nMais ce sont les paroles. Et en fait, je voudrais te demander de m'aider à me débarrasser de l'un de ces concurrents. Non, le tuer n'est pas nécessaire. Il suffit de capturer ou de couler son navire avec la cargaison.";
			link.l1 = "Hmm... eh bien, si vous payez bien, je peux arranger cela.";
			link.l1.go = "Sunplace_1";
			link.l2 = "Non, je ne m'immisce pas dans vos querelles mercantiles. Allez couler votre rival sans mon aide.";
			link.l2.go = "Sunplace_exit";
		break;
		
		case "Sunplace_exit"://если отказал - этот непись больше никогда не даст
			npchar.quest.Sunplace = "true";
			DialogExit();
		break;
		
		case "Sunplace_1":
			GetSunplaceShore();//бухта и остров
			pchar.GenQuest.Sunplace.Trader.Enemyname = GenerateRandomName_Generator(sti(npchar.nation), "man");//имя конкурента
			pchar.GenQuest.Sunplace.Trader.Nation = npchar.nation;//нация общая для торговца и конкурента
			pchar.GenQuest.Sunplace.Trader.City = npchar.City;//город квестодателя
			pchar.GenQuest.Sunplace.Trader.CityT = findSunplaceCity(NPChar);//город конкурента
			pchar.GenQuest.Sunplace.Trader.Shiptype = Sunplace_Shiptype();//тип корабля
			pchar.GenQuest.Sunplace.Trader.ShipName = GenerateRandomNameToShip(sti(NPChar.nation));//имя корабля
			pchar.GenQuest.Sunplace.Trader.DaysQty = 5 + hrand(5);//дни
			pchar.GenQuest.Sunplace.Trader.Money = sti(pchar.GenQuest.Sunplace.Trader.Shiptype)*3000;//оплата
			pchar.GenQuest.Sunplace.Trader.Goods = GOOD_COFFEE + hrand(sti(GOOD_PAPRIKA - GOOD_COFFEE));//товар
			dialog.text = "Très bien. Donc, le nom de votre homme est "+pchar.GenQuest.Sunplace.Trader.Enemyname+". Récemment, il avait envoyé "+GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.Sunplace.Trader.ShipType),"Nom")+"Acc"))+" '"+pchar.GenQuest.Sunplace.Trader.ShipName+"avec une cargaison de "+GetGoodsNameAlt(sti(pchar.GenQuest.Sunplace.Trader.Goods))+"Il a payé une somme assez décente pour cette cargaison, donc la perdre sera un sacré coup pour sa bourse.";
			link.l1 = "Et pourriez-vous me dire, où exactement chercher cet 'ami' à vous ?";
			link.l1.go = "Sunplace_2";
		break;
		
		case "Sunplace_2":
			dialog.text = "Mon 'ami' est actuellement chez lui à "+XI_ConvertString("Colony"+pchar.GenQuest.Sunplace.Trader.CityT+"Voc")+". Vous n'avez pas besoin de lui - vous avez besoin de son navire, ce que j'ai découvert après environ "+FindRussianDaysString(sti(pchar.GenQuest.Sunplace.Trader.DaysQty))+" passera près "+XI_ConvertString(pchar.GenQuest.Sunplace.Trader.Shore+"Gen")+". Vous pouvez le couler, le prendre à l'abordage - peu importe. L'essentiel est de s'assurer que le navire et la cargaison ne sont plus la propriété de "+pchar.GenQuest.Sunplace.Trader.Enemyname+". Et je m'en moque, que ce soit toi ou la mer qui le réclame. Pour ce travail, je te paierai "+FindRussianMoneyString(sti(pchar.GenQuest.Sunplace.Trader.Money))".";
			link.l1 = "Je l'ai compris. Eh bien, il est temps de partir alors !";
			link.l1.go = "Sunplace_3";
		break;
		
		case "Sunplace_3":
			DialogExit();
			pchar.GenQuest.Sunplace.Trader = "true";
			if (sti(pchar.GenQuest.Sunplace.Chance) == 1 && sti(pchar.rank) > 9) pchar.GenQuest.Sunplace.Bonus = "true";
			ReOpenQuestHeader("Sunplace");
			AddQuestRecord("Sunplace", "1");
			AddQuestUserData("Sunplace", "sGoods", GetGoodsNameAlt(sti(pchar.GenQuest.Sunplace.Trader.Goods)));
			AddQuestUserData("Sunplace", "sDay", FindRussianDaysString(sti(pchar.GenQuest.Sunplace.Trader.DaysQty)));
			AddQuestUserData("Sunplace", "sMoney", FindRussianMoneyString(sti(pchar.GenQuest.Sunplace.Trader.Money)));
			AddQuestUserData("Sunplace", "sCity", XI_ConvertString("Colony"+pchar.GenQuest.Sunplace.Trader.City+"Gen"));
			AddQuestUserData("Sunplace", "sType", GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.Sunplace.Trader.ShipType), "Name") + "Acc")));
			AddQuestUserData("Sunplace", "sSName", pchar.GenQuest.Sunplace.Trader.ShipName);
			AddQuestUserData("Sunplace", "sName", GetFullName(npchar));
			AddQuestUserData("Sunplace", "sShore", XI_ConvertString(pchar.GenQuest.Sunplace.Trader.Shore+"Gen"));
			SetFunctionTimerCondition("Sunplace_Over", 0, 0, sti(pchar.GenQuest.Sunplace.Trader.DaysQty), false);
			pchar.quest.Sunplace_Trader.win_condition.l1 = "location";
			pchar.quest.Sunplace_Trader.win_condition.l1.location = pchar.GenQuest.Sunplace.Trader.Island;
			pchar.quest.Sunplace_Trader.win_condition.l2 = "Timer";
			pchar.quest.Sunplace_Trader.win_condition.l2.date.hour  = sti(GetTime());
			pchar.quest.Sunplace_Trader.win_condition.l2.date.day   = GetAddingDataDay(0, 0, makeint(sti(pchar.GenQuest.Sunplace.Trader.DaysQty)-2));
			pchar.quest.Sunplace_Trader.win_condition.l2.date.month = GetAddingDataMonth(0, 0, makeint(sti(pchar.GenQuest.Sunplace.Trader.DaysQty)-2));
			pchar.quest.Sunplace_Trader.win_condition.l2.date.year  = GetAddingDataYear(0, 0, makeint(sti(pchar.GenQuest.Sunplace.Trader.DaysQty)-2));
			pchar.quest.Sunplace_Trader.function = "Sunplace_CreateTraderShip";
		break;
		
		case "Sunplace_complete":
			dialog.text = "Excellent ! Je savais que je pouvais compter sur vous. Je suppose que je ne demanderai pas où se trouvent ce navire et cette cargaison. Ce n'est pas mes affaires, après tout. Et mon ami aura besoin de pas mal de temps pour se remettre d'un tel coup, hé-hé. Tenez, veuillez prendre votre argent - et merci pour ce travail formidable.";
			link.l1 = "Je vous en prie... À bientôt, "+npchar.name+" !";
			link.l1.go = "Sunplace_complete_1";
		break;
		
		case "Sunplace_complete_1":
			AddMoneyToCharacter(pchar, sti(pchar.GenQuest.Sunplace.Trader.Money));
			AddQuestRecord("Sunplace", "12");
			CloseQuestHeader("Sunplace");
			pchar.GenQuest.Sunplace.Chance = rand(2);
			AddComplexSeaExpToScill(50, 50, 50, 50, 50, 0, 0);
			AddComplexSelfExpToScill(20, 20, 20, 20);
			AddCharacterExpToSkill(pchar, "Fortune", 100);//везение
			DeleteAttribute(pchar, "GenQuest.Sunplace.Trader");
			DialogExit();
		break;
		
		case "Sunplace_complete_murder":
			dialog.text = "Pauvre "+pchar.GenQuest.Sunplace.Trader.Enemyname+", quelle fin horrible ! Et bien que ce soit indirect, je suis la cause de sa disparition ! Vous ne comprenez pas, capitaine ! Vous ai-je demandé de le tuer ? J'avais prévu qu'après la perte d'argent dépensé pour la cargaison, il devrait à nouveau... enfin, peu importe... Vous...";
			link.l1 = "Hé, écoute - arrête de te plaindre, d'accord ? Tu m'as demandé de te débarrasser d'un rival - je l'ai fait. Encore mieux - ayant perdu la cargaison, il aurait pu redevenir riche et continuer à nuire à ton commerce. Maintenant, il ne peut pas faire grand-chose en étant mort.";
			link.l1.go = "Sunplace_complete_murder_1";
		break;
		
		case "Sunplace_complete_murder_1":
			dialog.text = "C'est tout! Assez! Je ne veux plus entendre ces discours blasphématoires! Prends ton argent maudit et quitte ma boutique sur-le-champ!";
			link.l1 = "Eh, "+npchar.name+", calme-toi, veux-tu? Ou je vais refroidir ton humeur moi-même - mon sabre est toujours à mes côtés! D'accord, ne t'effraie pas, je plaisantais juste. Écoute, je suis désolé que ça se soit passé comme ça - mais c'est toi qui m'as induit en erreur au départ. Adieu.";
			link.l1.go = "Sunplace_complete_murder_2";
		break;
		
		case "Sunplace_complete_murder_2":
			AddMoneyToCharacter(pchar, sti(pchar.GenQuest.Sunplace.Trader.Money));
			AddQuestRecord("Sunplace", "13");
			AddQuestUserData("Sunplace", "sName", GetFullName(npchar));
			CloseQuestHeader("Sunplace");
			npchar.quest.Sunplace = "true";//этот непись повторно квест больше не даст
			AddComplexSeaExpToScill(50, 50, 50, 50, 50, 0, 0);
			AddComplexSelfExpToScill(30, 30, 30, 30);
			AddCharacterExpToSkill(pchar, "Fortune", 50);//везение
			DeleteAttribute(pchar, "GenQuest.Sunplace.Trader");
			DialogExit();
		break;
		
		//Jason --> поиск дезертира
		case "FindFugitiveSt":
			if (NPChar.city == pchar.GenQuest.FindFugitive.City && sti(pchar.GenQuest.FindFugitive.Chance) == 1)
			{
				dialog.text = NPCStringReactionRepeat(""+pchar.GenQuest.FindFugitive.Name+" ? Oui, je le connais. Il a acheté des provisions pour sa chaloupe chez moi. Pendant la journée, il pêche généralement dans des criques isolées, mais chaque soir, on peut le trouver à la taverne.","Tu m'as déjà interrogé sur cet homme, et je t'ai dit tout ce que je savais !","Te moques-tu de moi ou es-tu vraiment un idiot?! Tu poses déjà toutes les mêmes questions pour la troisième fois!","Rien que d'y penser, comment un tel idiot est devenu capitaine...","block",1,npchar,Dialog.CurrentNode);
				link.l1 = HeroStringReactionRepeat("Merci, vous m'avez aidé immensément !","Oui, oui, d'accord.","Doucement, doucement, ne t'excite pas tant. J'ai juste oublié.","Eh bien, il l'a fait, comme tu peux le voir...",npchar,Dialog.CurrentNode); 
				link.l1.go = DialogGoNodeRepeat("FindFugitiveSt_1", "exit", "", "", npchar, Dialog.CurrentNode);
			}
			else
			{
				dialog.text = NPCStringReactionRepeat("Je ne sais pas ce que les gens disaient à la taverne de Port Royal, mais je n'ai jamais rencontré cet homme dans ma boutique. En fait, je ne l'ai jamais vu nulle part. Demandez autour du village - peut-être que quelqu'un vous dira...","Vous m'avez déjà demandé à propos de cet homme, et je vous ai dit : je ne sais pas !","Tu te moques de moi ou es-tu vraiment un imbécile ?! Tu poses toutes les mêmes questions pour la troisième fois déjà !","Penser qu'un tel imbécile est devenu capitaine...","block",1,npchar,Dialog.CurrentNode);
				link.l1 = HeroStringReactionRepeat("Je vois. Eh bien, merci quand même.","Oui, oui, d'accord.","Allons, allons, ne vous emballez pas. J'ai juste oublié.","Eh bien, il l'a fait, comme tu peux le voir...",npchar,Dialog.CurrentNode); 
				link.l1.go = DialogGoNodeRepeat("exit", "", "", "", npchar, Dialog.CurrentNode);	
			}
		break;
		
		case "FindFugitiveSt_1":
			DialogExit();
			AddQuestRecord("MayorsQuestsList", "12-2");
			sld = characterFromId("Fugitive");
			LAi_SetSitType(sld);
			sld.dialog.currentnode = "Fugitive_tavern";
			LAi_SetLoginTime(sld, 20.0, 23.99);
			FreeSitLocator(pchar.GenQuest.FindFugitive.City + "_tavern", "sit_front1");
			ChangeCharacterAddressGroup(sld, pchar.GenQuest.FindFugitive.City+"_tavern", "sit", "sit_front1");
		break;
		//<-- поиск дезертира
		
		// --> Карибские нравы - временное завершение
		// belamour legendary edition -->
		case "trial":
			dialog.text = "Mon Seigneur, que vous arrive-t-il, jeune homme ! S'il vous plaît, soyez plus réservé et choisissez vos mots avec soin en parlant des gens respectés ! Gerard LeCroix a quitté la Guadeloupe pour une expédition sur le continent, mais il a laissé votre récompense ici pour vous. Êtes-vous satisfait maintenant ?";
			link.l1 = "Hm... S'il vous plaît, excusez-moi, monsieur. Je me suis un peu emporté...";
			link.l1.go = "trial_1";
		break;
		
		case "trial_1":
			dialog.text = "Très bien. M. Lecroix a laissé votre récompense au gardien du phare local - ce sont de vieux amis. Vous n'avez qu'à lui rendre visite et récupérer le paiement dû. Monsieur Lecroix est un homme honnête, donc je pense que vous serez satisfait de votre récompense.";
			link.l1 = "Compris, merci ! Alors je vais voir le gardien du phare. Maintenant, laissez-moi faire une pause.";
			link.l1.go = "trial_2";
		break;
		
		case "trial_2":
			//TakeNItems(pchar, "gold_dublon", 400);
			link.l1 = "...";
			link.l1.go = "trial_3";
		break;
		
		case "trial_3":
			DialogExit();
			AddQuestRecord("Trial", "22");
			ChangeCharacterComplexReputation(pchar, "nobility", -1);
			AddCharacterExpToSkill(pchar, "FencingL", 20);
			AddCharacterExpToSkill(pchar, "FencingS", 20);
			AddCharacterExpToSkill(pchar, "FencingH", 20);
			AddCharacterExpToSkill(pchar, "Pistol", 20);
            NextDiag.CurrentNode = NextDiag.TempNode;
			DeleteAttribute(pchar, "questTemp.Trial");
			DeleteAttribute(npchar, "quest.trial_usurer");
			sld = characterFromId("BasTer_Lightman");
			sld.quest.trial_usurer = true;
			AddLandQuestMark(sld, "questmarkmain");
		break;
		
		case "trialA":
			dialog.text = "Oui, il était ici, vous attendant. Mais, probablement, la tâche qu'il vous a confiée s'est avérée plus difficile que prévu initialement, donc il n'a pas attendu et est parti en expédition sur le continent. Il a laissé votre récompense à une personne de confiance.";
			link.l1 = "Oui, j'ai vraiment eu des circonstances imprévues, mais j'ai réussi à accomplir la tâche. Heureux d'entendre que mon paiement m'attend. De qui puis-je le recevoir ?";
			link.l1.go = "trialA_1";
		break;
		
		case "trialA_1":
			dialog.text = "Monsieur Lecroix a laissé votre récompense au gardien du phare local - ce sont de vieux amis. Vous n'avez qu'à lui rendre visite et récupérer le paiement dû. Monsieur Lecroix est un homme honnête, donc je pense que vous serez satisfait de votre récompense.";
			link.l1 = "Compris, merci ! Je vais alors voir le gardien du phare. Maintenant, laissez-moi prendre une pause.";
			link.l1.go = "trialA_2";
		break;
		
		case "trialA_2":
			dialog.text = "Bonne chance, monsieur.";
			link.l1 = "...";
			link.l1.go = "trialA_3";
		break;
		
		case "trialA_3":
			DialogExit();
			AddQuestRecord("Trial", "22");
			ChangeCharacterComplexReputation(pchar, "nobility", 1);
			AddCharacterExpToSkill(pchar, "Commerce", 80);
            NextDiag.CurrentNode = NextDiag.TempNode;
			DeleteAttribute(pchar, "questTemp.Trial");
			DeleteAttribute(npchar, "quest.trial_usurer");
			sld = characterFromId("BasTer_Lightman");
			sld.quest.trial_usurer = true;
			AddLandQuestMark(sld, "questmarkmain");
		break;
		// <-- legendary edition
		/*case "trial":
			dialog.text = "Bon sang, pourquoi es-tu si bruyant, jeune homme ! Calme-toi, et surveille ton langage en parlant de personnes respectées ! Gerard LeCroix a quitté la Guadeloupe avec une expédition vers le continent, mais il t'a laissé un message.\nT'es-tu calmé, monsieur ? Prêt à m'écouter ?";
			link.l1 = "Hm... Je vous prie de m'excuser, monsieur. Je me suis un peu emporté. Je vous écoute.";
			link.l1.go = "trial_1";
		break;
		
		case "trial_1":
			dialog.text = "Très bien. La prochaine fois, essayez de demander d'abord, puis criez fort. D'accord... Connaissez-vous un homme du nom de Simon Maurois ?";
			link.l1 = "Ha ! Tout le monde a entendu parler de Simon Maurois ! Bien sûr que je le connais.";
			link.l1.go = "trial_2";
			link.l2 = "Jamais entendu parler de lui. Qui est-ce ?";
			link.l2.go = "trial_3";
		break;
		
		case "trial_2":
			dialog.text = "Excellent. Allez le voir, alors. C'est lui qui a financé l'expédition de monsieur Shoke, donc vous pouvez récupérer votre récompense auprès de lui. Alors, était-il vraiment nécessaire de s'échauffer autant ?";
			link.l1 = "Encore une fois, je vous prie de m'excuser... Merci pour votre aide, monsieur. Je vais voir monsieur Maurois sur-le-champ !";
			link.l1.go = "trial_exit";
		break;
		
		case "trial_3":
			dialog.text = "Il est le propriétaire de la maison bancaire Maurois et le chef de la succursale à Capsterville. Vous devrez donc aller à Saint-Christopher et visiter la banque de Capsterville. C'est monsieur Maurois qui a financé l'expédition de monsieur Shoke, donc vous pouvez récupérer votre récompense auprès de lui. Alors, était-ce vraiment nécessaire de vous échauffer autant ?";
			link.l1 = "Encore une fois, je vous prie de m'excuser... Merci pour votre aide, monsieur. Je vais voir monsieur Maurois immédiatement !";
			link.l1.go = "trial_exit";
		break;
		
		case "trial_exit":
			DialogExit();
            NextDiag.CurrentNode = NextDiag.TempNode;
			DeleteAttribute(npchar, "quest.trial_usurer");
			pchar.questTemp.Trial = "usurer";
			AddQuestRecord("Trial", "22");
		break;*/
		
		// belamour legendary edition на пару с Акулой -->
		case "SharkGoldFleet":
			dialog.text = "Ah, le marchand entreprenant ! On voit tout de suite l'approche commerciale. Je le respecte. Bien sûr, j'ai la marchandise qu'il vous faut.";
			link.l1 = "Je suis sûr que je peux le vendre pour un bon profit. Autant que je sache, il y a une bonne demande pour cette marchandise à Porto Bello. Combien cela va-t-il me coûter ?";
			link.l1.go = "SharkGoldFleet_01";
		break;
		
		case "SharkGoldFleet_01":
			pchar.questTemp.SharkGoldFleet = "buyincar";
			dialog.text = "Comme ci, comme ça... Alors, trois cents unités de café... Et la même quantité de cacao... Cela vous coûtera..."+sti(GetStoreGoodsPrice(&stores[sti(rColony.StoreNum)],GOOD_COFFEE,PRICE_TYPE_BUY,pchar,300)+GetStoreGoodsPrice(&stores[sti(rColony.StoreNum)],GOOD_CHOCOLATE,PRICE_TYPE_BUY,pchar,300))+" pesos !";
			if(pchar.money < sti(GetStoreGoodsPrice(&stores[sti(rColony.StoreNum)], GOOD_COFFEE, PRICE_TYPE_BUY, pchar, 300) + GetStoreGoodsPrice(&stores[sti(rColony.StoreNum)], GOOD_CHOCOLATE, PRICE_TYPE_BUY, pchar, 300)))
			{
				link.l1 = "Hmm... Excusez-moi, je n'ai pas l'air d'avoir assez d'argent. Attendez, s'il vous plaît : je cours au navire chercher de l'argent maintenant - et je reviens tout de suite !";
				link.l1.go = "exit";
			}
			else
			{
				link.l1 = "Voilà.";
				link.l1.go = "SharkGoldFleet_02";
			}
		break;
		
		case "SharkGoldFleet_02":
			if(GetCargoFreeSpace(pchar) < 1200)
			{
				dialog.text = "Attendez un instant, señor. Il semble que vous n'ayez pas assez de place sur votre navire pour une telle fête. Videz la cale et revenez.";
				link.l1 = "Oh, j'ai oublié de décharger ! Attendez une minute - j'arrive tout de suite !";
				link.l1.go = "exit";
			}
			else
			{
				dialog.text = "Superbe ! Je donnerai immédiatement l'ordre que les marchandises soient chargées à bord de votre navire. C'est un plaisir de faire affaire avec vous !";
				link.l1 = "Mutuellement, señor ! Et maintenant, permettez-moi de prendre congé : les affaires n'attendent pas.";
				link.l1.go = "SharkGoldFleet_03";
			}
		break;
		
		case "SharkGoldFleet_03":
			DialogExit();
			AddMoneyToCharacter(pchar, -sti(GetStoreGoodsPrice(&stores[sti(rColony.StoreNum)], GOOD_COFFEE, PRICE_TYPE_BUY, pchar, 300) + GetStoreGoodsPrice(&stores[sti(rColony.StoreNum)], GOOD_CHOCOLATE, PRICE_TYPE_BUY, pchar, 300)))
			SetCharacterGoods(pchar, GOOD_COFFEE, GetCargoGoods(pchar, GOOD_COFFEE)+300);
			SetCharacterGoods(pchar, GOOD_CHOCOLATE, GetCargoGoods(pchar, GOOD_CHOCOLATE)+300);
			AddQuestRecord("SharkGoldFleet", "4");
			pchar.questTemp.SharkGoldFleet = "toCarPortOffice";
		break;
		
		case "SharkGoldFleet_again":
			dialog.text = "Les marchandises vous attendent. Avez-vous apporté de l'argent ?";
			if(pchar.money < sti(GetStoreGoodsPrice(&stores[sti(rColony.StoreNum)], GOOD_COFFEE, PRICE_TYPE_BUY, pchar, 300) + GetStoreGoodsPrice(&stores[sti(rColony.StoreNum)], GOOD_CHOCOLATE, PRICE_TYPE_BUY, pchar, 300)))
			{
				link.l1 = "Pas encore. Je voulais juste m'assurer que votre offre tient toujours. Et l'argent viendra bientôt.";
				link.l1.go = "exit";
			}
			else
			{
				link.l1 = "Voilà pour vous.";
				link.l1.go = "SharkGoldFleet_02";
			}
		break;
		//<-- на пару с Акулой
		case "no_quests":
			dialog.text = "Pour le moment, je n'ai pas besoin de vos services.";
			link.l1 = "C'est dommage. Changeons de sujet.";
			link.l1.go = "node_1";
		break;
		
        case "fight":
			DialogExit();
            NextDiag.CurrentNode = NextDiag.TempNode;
			LAi_group_Attack(NPChar, Pchar);
		break;
		
		case "Exit":			
			Nextdiag.CurrentNode = Nextdiag.TempNode;
			DialogExit();			
		break;
	}
	LanguageCloseFile(iSeaGoods);
}

int findStoreMan(ref NPChar, int iTradeNation)
{
    ref ch;
	int n;
    int storeArray[30];
    int howStore = 0;

	for(n=0; n<MAX_CHARACTERS; n++)
	{
		makeref(ch,Characters[n]);
        if (CheckAttribute(ch, "Dialog.Filename") && ch.Dialog.Filename == "Common_Store.c") // магазин
		{
            if (sti(ch.nation) !=  iTradeNation) continue;
            if (NPChar.id == ch.id) continue;
            if (NPChar.id == "Panama_trader" || ch.id == "Panama_trader") continue; //нельзя доплыть
			if (NPChar.id == "SanAndres_trader" || ch.id == "SanAndres_trader") continue; // fix 2016-03-07
            if (ch.location == "none") continue; // фикс для новых, невидимых до поры островов
            if (GetIslandByCityName(ch.city) == GetIslandByCityName(NPChar.city)) continue; // хрен вам, а не читы!
            storeArray[howStore] = n;
            howStore++;
		}
    }
    if (howStore == 0)
    {
        return -1;
    }
    else
    {
        return storeArray[rand(howStore-1)];
    }
}

int Sunplace_Shiptype() // new
{
	int i;
	
	if (sti(pchar.rank) >= 1 && sti(pchar.rank) < 6) i = SHIP_SCHOONER;
	if (sti(pchar.rank) >= 6 && sti(pchar.rank) < 11) i = SHIP_FLEUT;
	if (sti(pchar.rank) >= 11 && sti(pchar.rank) < 18) i = SHIP_PINNACE;
	if (sti(pchar.rank) >= 18) i = SHIP_GALEON_L;
	
	return i;
}

string findSunplaceCity(ref NPChar) // new
{
	int n, nation;
    int storeArray[2];
	SetArraySize(&storeArray, MAX_COLONIES);
    int howStore = 0;

	for(n=0; n<MAX_COLONIES; n++)
	{
		nation = GetNationRelation(sti(pchar.nation), sti(colonies[n].nation));
		if (nation != RELATION_ENEMY && colonies[n].id != "Panama" && colonies[n].id != "LosTeques" && colonies[n].id != "SanAndres" && colonies[n].nation != "none" && GetIslandByCityName(npchar.city) != colonies[n].islandLable) //на свой остров
		{
			storeArray[howStore] = n;
			howStore++;
		}
	}
	if (howStore == 0) return "none";
	nation = storeArray[hrand(howStore-1)];
	return colonies[nation].id;
}
