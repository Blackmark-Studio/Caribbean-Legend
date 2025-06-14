#include "DIALOGS\%language%\Rumours\Common_rumours.c"  //homo 25/06/06
#include "interface\ship.c"
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
    // вызов диалога по городам -->
    NPChar.FileDialog2 = "DIALOGS\" + LanguageGetLanguage() + "\Tavern\" + NPChar.City + "_Tavern.c";
    if (LoadSegment(NPChar.FileDialog2))
	{
        ProcessCommonDialog(NPChar, Link, NextDiag);
		UnloadSegment(NPChar.FileDialog2);
	}
    // вызов диалога по городам <--
	ProcessCommonDialogRumors(NPChar, Link, NextDiag);//homo 25/06/06
	
	int iTest, iTemp;
	string sTemp;
	string NPCCity = NPChar.City;
    iTest = FindColony(NPChar.City); // город 
    ref rColony;
	if (iTest != -1)
	{
		rColony = GetColonyByIndex(iTest);
	}
	bool ok;
	
	if(!CheckAttribute(pchar, "questTemp.TavernVisit."+(NPCCity) )) 
	{
		pchar.questTemp.TavernVisit.(NPCCity) = true;
		pchar.questTemp.TavernVisit.counter = sti(pchar.questTemp.TavernVisit.counter) + 1;
		notification("Première visite à la taverne " + XI_ConvertString(NPCCity + "TavernName"), "Drunk");
		AddCharacterExpToSkill(pchar, SKILL_LEADERSHIP, 10.0);
	}	
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			NextDiag.TempNode = "First time";
			if (LAi_grp_playeralarm > 0)
			{
       			dialog.text = NPCharRepPhrase(pchar,LinkRandPhrase("L'alarme est déclenchée dans la ville, et tout le monde vous cherche. Si j'étais toi, je ne resterais pas ici.","Tous les gardes de la ville fouillent la ville à ta recherche. Je ne suis pas un imbécile et je ne te parlerai pas!","Cours, "+GetSexPhrase("camarade","lass")+", avant que les soldats ne te transforment en hachis..."),LinkRandPhrase("De quoi as-tu besoin, "+GetSexPhrase("canaille","puant")+"?! Les gardes de la ville ont ton odeur, tu n'iras pas loin"+GetSexPhrase(", sale pirate !","")+"","Assassin, quitte ma place tout de suite! Gardes!","Je n'ai pas peur de toi, "+GetSexPhrase("coquin","souris")+"! Bientôt tu seras pendu dans notre fort, tu n'iras pas loin..."));
				link.l1 = NPCharRepPhrase(pchar,RandPhraseSimple("Heh, une alarme n'est jamais un problème pour moi...","Ils ne m'attraperont jamais."),RandPhraseSimple("Ferme ta gueule, "+GetWorkTypeOfMan(npchar,"")+", ou je vais arracher ta langue!","Heh, "+GetWorkTypeOfMan(npchar,"")+", et tous là-bas - pour attraper les pirates! Voilà ce que je te dis, camarade: reste tranquille et tu ne mourras pas..."));
				link.l1.go = "exit";
				break;
			}
			if (sti(pchar.GenQuest.Piratekill) > 20 && sti(npchar.nation) == PIRATE)
			{
				dialog.text = RandPhraseSimple("Et c'est toi, salaud ! Tu penses qu'on te verse du rhum ici ? Certainement pas ! Les gars ! Aux armes ! Tuez ce scélérat !","Tu veux un verre, pirate? Ha! Non! Maintenant, on va te montrer de quel bois on se chauffe! Les gars, sortez vos lames!");
				link.l1 = RandPhraseSimple("Hein? Quoi ?","Arrêtez!");
				link.l1.go = "fight";
				bDisableFastReload = true;//закрыть переход
				pchar.quest.pirate_in_town.win_condition.l1 = "ExitFromLocation";
				pchar.quest.pirate_in_town.win_condition.l1.location = pchar.location;
				pchar.quest.pirate_in_town.function = "TownPirate_battle";
				break;
			}
			//Jason, Бремя гасконца
			if(NPChar.City == "FortFrance")
			{
				if (!CheckAttribute(npchar, "quest.Rum") && CheckAttribute(pchar, "questTemp.Sharlie.Lock") && pchar.questTemp.Sharlie == "ship" && makeint(environment.time) > 5.0 && makeint(environment.time) < 19.0)
				{
					link.l1 = "Monsieur, je cherche du travail. Avez-vous des emplois?";
					link.l1.go = "Sharlie_rum";
					break;
				}
				if (CheckAttribute(pchar, "questTemp.Sharlie.Rum") && pchar.questTemp.Sharlie.Rum == "regard")
				{
					link.l1 = "J'ai accompli votre mission. La chaloupe avec le rhum a été livrée à la baie de Le Francois et remise à vos gens.";
					link.l1.go = "Sharlie_rum_5";
					break;
				}
			}
			if (CheckAttribute(pchar, "questTemp.Sharlie") && pchar.questTemp.Sharlie == "crew" && npchar.city == "FortFrance")
			{
				DelLandQuestMark(npchar);
				dialog.text = "Vouliez-vous quelque chose, monsieur ?";
				Link.l1 = "Bonjour aubergiste, j'ai besoin d'embaucher un équipage pour mon navire. Pouvez-vous m'aider avec ça?";
				Link.l1.go = "Sharlie_crew";
				break;
			}
			
			if (CheckAttribute(pchar, "questTemp.Sharlie") && pchar.questTemp.Sharlie == "skiper" && npchar.city == "FortFrance")
			{
				DelLandQuestMark(npchar);
				dialog.text = "Bonjour à nouveau. Qu'est-ce que c'est cette fois, monsieur?";
				Link.l1 = ""+npchar.name+", Je comprends que je vous dérange, mais juste une question de plus. J'ai besoin d'un navigateur - une idée d'où je pourrais en trouver un?";
				Link.l1.go = "Sharlie_skiper";
				break;
			}
			if (CheckAttribute(pchar, "questTemp.Sharlie.Lock"))
			{
    			dialog.text = "Qu'est-ce que vous voulez, monsieur?";
				Link.l1 = "J'espérais que tu pourrais répondre à quelques questions.";
				Link.l1.go = "quests";
				if(!CheckAttribute(pchar,"questTemp.TimeLock"))
				{
					link.l2 = "Je voudrais louer une chambre.";
					link.l2.go = "room";
				}
				break;
			}			
			//Бремя гасконца
			// Addon 2016-1 Jason пиратская линейка
			if (CheckAttribute(pchar, "questTemp.Mtraxx.Retribution") && pchar.questTemp.Mtraxx.Retribution == "tavern" && npchar.city == "Tortuga")
			{
				dialog.text = "Je suis ravi de vous voir monsieur ! Comment puis-je vous être utile ? Rhum, cognac, whisky écossais ?";
				Link.l1 = "Je voudrais une bouteille de votre meilleur vin français et une clé de chambre.";
				Link.l1.go = "mtraxx_tortuga";
				break;
			}
			if (CheckAttribute(pchar, "questTemp.Mtraxx.Retribution") && pchar.questTemp.Mtraxx.Retribution == "room" && npchar.city == "Tortuga")
			{
				dialog.text = "Vous avez déjà payé monsieur, votre chambre est à l'étage.";
				Link.l1 = "Merci.";
				Link.l1.go = "exit";
				break;
			}
			
			// Sinistra - Квест "Длинные тени старых грехов" ==>	
			if (CheckAttribute(pchar, "questTemp.DTSG_BasTerTavern") && npchar.city == "BasTer")
			{
				dialog.text = "Comment puis-je vous servir, Capitaine? Vous voulez probablement boire un coup après ce qui s'est passé.";
				Link.l1 = "Cela peut attendre. Je veux en fait discuter de ce qui s'est passé.";
				Link.l1.go = "DTSG_BasTerTavern_1";
				DelLandQuestMark(npchar);
				break;
			}
			// <== Квест "Длинные тени старых грехов" - Sinistra
			
			//--> Торговля по закону
			if (CheckAttribute(pchar, "questTemp.TPZ_Start") && !CheckAttribute(pchar, "questTemp.TPZ_Tavern_1") && npchar.city == "BasTer")
			{
				dialog.text = "Je suis désolé, "+GetAddress_Form(NPChar)+", mais je ne peux pas vous offrir une seule goutte d’alcool aujourd’hui.";
				Link.l1 = "Vraiment ? Quelle sorte de taverne est-ce donc, où l’on ne peut même pas verser une goutte de rhum ? Ai-je manqué"+GetSexPhrase("","e")+" une grande fête qui a vidé vos réserves ?";
				Link.l1.go = "TPZ_Tavern_1";
				pchar.questTemp.TPZ_Tavern_1 = true;
				DelLandQuestMark(npchar);
				break;
			}
			//<-- Торговля по закону
			
			if(NPChar.quest.meeting == "0")
			{
				dialog.Text = GetNatPhrase(npchar,LinkRandPhrase("Bienvenue dans ma modeste taverne '"+XI_ConvertString(NPChar.City+"TavernName")+"', monsieur. Je suis heureux de vous voir.","A votre service, monsieur ! Dans notre taverne '"+XI_ConvertString(NPChar.City+"TavernName")+"' nous sommes toujours heureux d'accueillir de nouveaux visiteurs.","Première fois ici, monsieur? N'hésitez pas, ici à '"+XI_ConvertString(NPChar.City+"TavernName")+"' vous vous sentez toujours comme chez vous!"),LinkRandPhrase("Entrez, monsieur le capitaine. Je ne vous reconnais pas, donc ce doit être votre première fois chez '"+XI_ConvertString(NPChar.City+"TavernName")+"'.","Je ne vous ai jamais rencontré auparavant, monsieur. Faisons connaissance : je suis "+GetFullName(npchar)+", le tenancier de '"+XI_ConvertString(NPChar.City+"TavernName")+"'.'","Heureux d'accueillir notre nouvel invité, Monsieur le Capitaine! Dans ma taverne '"+XI_ConvertString(NPChar.City+"TavernName")+"' premier verre est toujours offert par la maison! Je suis le propriétaire de cet endroit, "+GetFullName(npchar)+", vous accueille."),LinkRandPhrase("Seigneur Capitaine! Bienvenue à la taverne '"+XI_ConvertString(NPChar.City+"TavernName")+"'!","Oh, quel brillant hidalgo a visité notre taverne '"+XI_ConvertString(NPChar.City+"TavernName")+"'! Est-ce votre première fois ici, monsieur?","Bon jour, monsieur ! Je suis "+GetFullName(npchar)+", humble proprietaire de '"+XI_ConvertString(NPChar.City+"TavernName")+"', nous sommes ravis de vous accueillir ici !"),LinkRandPhrase("Bonjour, monsieur le capitaine. Je suis le propriétaire de la taverne '"+XI_ConvertString(NPChar.City+"TavernName")+"'. C'est votre premier séjour chez nous?","Bon après-midi, monsieur. Bienvenue à la taverne '"+XI_ConvertString(NPChar.City+"TavernName")+"'.'","Très bon de vous voir monsieur le capitaine ! Notre propre taverne '"+XI_ConvertString(NPChar.City+"TavernName")+"' vous salue! Rhum, vin, ou si je peux vous tenter, nous avons un nouveau petit esprit coquin hollandais appelé gin?"));
				Link.l1 = LinkRandPhrase("Un endroit douillet que vous avez ici... Permettez-moi de me présenter - "+GetFullName(pchar)+", c'est un plaisir de vous rencontrer.",""+GetFullName(pchar)+", c'est un plaisir de vous rencontrer. Alors, qu'est-ce que vous pouvez m'offrir ?","Mon nom est "+GetFullName(pchar)+" et je suis nouveau dans ce port. Dites-moi, pour quoi cette taverne est-elle la plus connue?");
				Link.l1.go = "meeting";
				NPChar.quest.meeting = "1";
				if(startHeroType == 4 && NPChar.location == "SantaCatalina_tavern")
				{
					dialog.text = "Ahoy, Rumba ! De retour d'un voyage, ou en partance pour un nouveau ?";
					link.l1 = "Bonjour, "+npchar.name+". Juste décidé de passer.";
					Link.l1.go = "Helen_meeting";
					NPChar.quest.meeting = "1";
					break;
				}
				NPChar.quest.meeting = "1";
			}
			else
			{
				// Квестовый генератор священника. Квест №1. Warship -->
				if(CheckAttribute(PChar, "GenQuest.ChurchQuest_1.NeedToDialogWithBarmen") && PChar.location == PChar.GenQuest.ChurchQuest_1.CurPortManColony + "_tavern")
		        {
		            if(CheckAttribute(PChar, "GenQuest.ChurchQuest_1.NoMoneyToBarmen"))
		            {
		            	iTemp = sti(PChar.GenQuest.ChurchQuest_1.MoneyToBarmen);
		            	dialog.Text = "Alors, cap'taine, m'avez-vous apporté "+FindRussianMoneyString(iTemp)+".";
		            	if(sti(PChar.Money) >= iTemp)
		            	{
							link.l1 = "Oui, je les ai. Les voici...";
							link.l1.go = "Tavern_ChurchGenQuest1_Node_4_1";
						}
						else
						{
							link.l1 = "Non, je ne l'ai pas encore fait...";
							link.l1.go = "exit";
						}
		            }
		            else
		            {
		            	dialog.Text = "Que voulez-vous, mon bon "+GetSexPhrase("monsieur","madame")+"?";
						link.l1 = "Une bouteille de rhum pour mon pote à cette table là-bas.";
						link.l1.go = "Tavern_ChurchGenQuest1_Node_1";
					}
					break;
				}
				// <-- Квестовый генератор священника. Квест №1.
				dialog.Text = pcharrepphrase(LinkRandPhrase(LinkRandPhrase("Oh, honorables invités ! Hé, toi - bouge et fais de la place pour un capitaine galant ! Et fais-le vite, avant que je ne te jette dehors, haha !","Dieu miséricordieux là-haut! Si ce n'est pas "+GetFullName(pchar)+"! Je viens de recevoir un nouvel envoi des meilleurs vins, entrez donc !","Oh, "+GetAddress_Form(NPChar)+", avez-vous des ennuis ? Permettez-moi de vous traiter ? Cette bouteille est de la maison. Croyez-moi, c'est le meilleur vin aux alentours..."),LinkRandPhrase("Oh, c'est le Capitaine "+GetFullName(pchar)+"! Hé, toi ! Montre un peu de respect au bon capitaine ! Ce n'est pas une grange ! Excusez-moi, cap'n, leurs mères ne leur ont visiblement jamais appris les bonnes manières.","Eh bien, eh bien, "+GetAddress_Form(NPChar)+" "+GetFullName(pchar)+"! Nous sommes partis pour une longue nuit, haha! Les filles, vous feriez mieux d'avoir vos plus belles robes!","Bon après-midi, "+GetFullName(pchar)+", Je suis ravi de vous voir! S'il vous plaît, monsieur, j'ai une demande. Je viens d'acheter de nouvelles tables, alors s'il vous plaît pas de bagarre ce soir."),LinkRandPhrase("Bonjour, capitaine. Fais comme chez toi, mais garde à l'esprit que même le Capitaine Sharp lui-même surveille ses manières dans mon établissement.","O-ho-ho! Regarde qui est ici? C'est "+GetFullName(pchar)+" lui-même ! Et nous commencions tout juste à nous ennuyer en ton absence ! Que dirais-tu de régaler les gars avec une aventure pendant que j'ouvre un nouveau tonneau de rhum, cap'taine ?","O-ho-ho ! C'est "+GetFullName(pchar)+" lui-même! J'espère que tu ne vas pas encore dérober mes clients vers les hautes mers avec tes histoires de tes grandes aventures?")),LinkRandPhrase(LinkRandPhrase(""+GetFullName(pchar)+"! Ce vieux loup de mer est toujours heureux de vous voir dans son établissement! S'il vous plaît monsieur, prenez un siège et les filles s'occuperont de vous!","S'il vous plaît capitaine, mettez-vous à l'aise! Toujours heureux d'accueillir mon invité préféré. Quel est ton poison?","Heureux de te revoir, "+GetFullName(pchar)+"! Voulez-vous une table pour vous-même? Ou préférez-vous vous asseoir au bar?"),LinkRandPhrase("Bon après-midi, capitaine. Il y a un froid dans l'air, laissez-moi vous offrir un excellent vin chaud que je viens de faire, c'est pour la maison!","Bonjour, capitaine "+GetFullName(pchar)+"! Je suis ravi que tu sois venu me rendre visite à nouveau. Que désires-tu ?","Je suis heureux de vous avoir, "+GetAddress_Form(NPChar)+" "+GetFullName(pchar)+"! Je suis ravi que vous patroniez mon pauvre etablissement ! Nous faisons tout ce que nous pouvons pour plaire."),LinkRandPhrase("Capitaine! Bienvenue, bienvenue! J'ai obtenu du magnifique d'Anjou digne du Roi Louis lui-même et l'ai gardé spécialement pour vous!",""+GetFullName(pchar)+"! Je suis tellement content que vous soyez venu. Dois-je chasser tous ces rats de mer ou préférez-vous qu'ils restent ? Croyez-moi, je viderais volontiers toute la taverne pour vous !","Mon Dieu, voici le Capitaine "+GetFullName(pchar)+"! Hé, dragueurs - apportez la meilleure nappe à la table du capitaine !")));
				Link.l1 = pcharrepphrase(RandPhraseSimple(RandPhraseSimple("Oh, je vois que l'on se souvient de moi ici... Hourra, remplis mon verre mate, pendant que je jette un coup d'oeil autour de moi...","Calme-toi, mon pote, aujourd'hui je suis de bonne humeur. Commençons par du rhum, d'accord?..."),RandPhraseSimple("Oh ... tu n'es pas trop content de m'avoir ici ? J'espère que je t'ai mal entendu, ha !","Ahoy. J'espère que ton vin est meilleur que ton accueil? Sinon je peux me fâcher, tu sais...")),RandPhraseSimple(RandPhraseSimple("Toujours ravi de te rendre visite, camarade. Qu'as-tu pour réchauffer un vieux loup de mer?","Ahoy l'ami, ton établissement s'améliore de jour en jour! Venir ici est toujours un plaisir..."),RandPhraseSimple("Tu n'as pas oublié un vieux vagabond? Je suis flatté, mon pote.","Heureux de revoir un vieil ami... Il te reste encore du rhum?")));
				Link.l1.go = "step_node";
			}
			break;
				
			case "step_node":
				dialog.Text = LinkRandPhrase("Je vous écoute, capitaine.","Mon auberge '"+XI_ConvertString(NPChar.City+"TavernName")+"' a votre service, Capitaine!","Tout ouïe, Cap'n! Qu'aimeriez-vous aujourd'hui?");
				Link.l1 = "Sont-il des gars sur l'île prêts à tenter leur chance sur les mers?";
				Link.l1.go = "crew hire";
				Link.l2 = "J'espérais que vous pourriez répondre à quelques questions.";
				Link.l2.go = "int_quests";
				if (CheckAttribute(pchar, "GenQuest.LoanChest.TakeChest") && sti(pchar.GenQuest.LoanChest.TargetIdx) == sti(NPChar.index))
				{
					link.l21 = "Je voudrais discuter des affaires financières.";
					link.l21.go = "LoanForAll";//(перессылка в кредитный генератор)
				}
				
				// Квестовый генератор священника. Квест №2. Warship -->
				if(CheckAttribute(PChar, "GenQuest.ChurchQuest_2.AskBarmen") && PChar.location == PChar.GenQuest.ChurchQuest_2.QuestTown + "_tavern")
		            	{
					link.l10 = LinkRandPhrase("Pouvez-vous me dire quelque chose sur le récent vol dans l'église?","Que savez-vous du récent vol dans l'église?","Avez-vous entendu parler du récent vol à l'église?");
					link.l10.go = "Tavern_GenQuest_Church_2_1";
				}
				// <-- Квестовый генератор священника. Квест №2.
				
				//Jason --> генератор Неудачливый вор
				if (CheckAttribute(pchar, "GenQuest.Device.Shipyarder") && NPChar.location == pchar.GenQuest.Device.Shipyarder.City + "_tavern" && pchar.GenQuest.Device.Shipyarder == "begin" && !CheckAttribute(npchar, "quest.Device"))
				{
					link.l16 = "Les gens disent que tu sais a peu pres tout dans cette colonie. Je veux acheter "+pchar.GenQuest.Device.Shipyarder.Type+", et on m'a dit qu'il avait été vendu dans votre ville. Eh bien, quelqu'un le vendait sur le marché de rue. Pouvez-vous me dire quelque chose à ce sujet?";
					link.l16.go = "Device_Tavern";
				}
				// <-- генератор Неудачливый вор
			
				//Jason --> генератор Место под солнцем
				if (CheckAttribute(pchar, "GenQuest.Sunplace.Trader") && pchar.GenQuest.Sunplace.Trader == "continue" && NPChar.location == pchar.GenQuest.Sunplace.Trader.CityT + "_tavern")
				{
					link.l17 = "Vous cherchez un racketteur du nom de "+pchar.GenQuest.Sunplace.Trader.Enemyname+". Ou puis-je le trouver?";
					link.l17.go = "Sunplace_Tavern";
				}
				// <-- генератор Место под солнцем
			
				// --> Голландский гамбит
				if (CheckAttribute(pchar, "questTemp.HWIC.Holl") && pchar.questTemp.HWIC.Holl == "JacobOnMain" && NPChar.location == pchar.questTemp.HWIC.Holl.JacobCity + "_tavern")
				{
					link.l18 = "Bonjour, "+npchar.name+". J'ai besoin de trouver Jacob van Berg - où est-il? Je ne le vois pas dans votre taverne...";
					link.l18.go = "HWICHollJacob_Tavern";
				}
				if (CheckAttribute(pchar, "questTemp.HWIC.Self") && pchar.questTemp.HWIC.Self == "start" && NPChar.nation == SPAIN && !CheckAttribute(npchar, "quest.HWICTalked"))
				{
					link.l18 = "Bonjour, "+npchar.name+". Je cherche un caballero du nom de Fernando Rodriguez. Est-il apparu dans votre ville?";
					link.l18.go = "HWICSelfFernando_Tavern";
				}
				// <-- Голландский гамбит
			
				//Jason --> гонки на гидропланах
				if (CheckAttribute(pchar, "GenQuest.Racing.Go.Advantage") && NPChar.location == pchar.GenQuest.Racing.Go.StartCity + "_tavern")
				{
					link.l19 = "Je suis venu récupérer mes gains, que vous avez gardés en sécurité pour moi. "+npchar.name+".";
					link.l19.go = "Race_Advantage";
				}
				// <-- гонки на гидропланах
			
				//Jason --> захват пассажиров
				if (CheckAttribute(pchar, "GenQuest.Marginpassenger") && pchar.GenQuest.Marginpassenger == "take" && NPChar.location == pchar.GenQuest.Marginpassenger.Targetcity+"_tavern")
				{
					link.l20 = "Je me demandais où je pourrais trouver un homme du nom de "+pchar.GenQuest.Marginpassenger.q2Name+"? Il habite dans ta ville.";
					link.l20.go = "Marginpassenger";
				}
				// <-- захват пассажиров
				if(!CheckAttribute(pchar,"questTemp.TimeLock"))
				{
					link.l3 = pcharrepphrase("Tu as une chambre libre, mon pote?","Vous avez une chambre libre, je resterais ici pendant un moment.");
					link.l3.go = "room";
				}
				Link.l4 = "Hélas, je pars déjà, "+NPChar.name+". A bientot.";
				Link.l4.go = "exit";
		break;
		
		case "Helen_meeting":
			dialog.Text = "Ah, bien, entrez, entrez. Vous êtes toujours le bienvenu ici.";
			link.l1 = "Oui, merci. C'était bon de te voir. Adieu.";
			link.l1.go = "exit";
			Link.l2 = "J'aurais besoin de nouvelles mains. Assure-toi simplement qu'elles soient capables, d'accord?";
			Link.l2.go = "crew hire";
			link.l3 = "J'aimerais me reposer sur la terre ferme et rassembler mes pensées, pas quand ma mère s'agite dans la maison.";
			link.l3.go = "Helen_room";
			Link.l4 = "Puis-je vous demander quelque chose ? ";
			Link.l4.go = "quests";
			link.l5 = " J'ai une affaire à discuter avec toi, "+NPChar.name+".";
			link.l5.go = "Helen_rumours_tavern";
		break;
		
		case "Meeting":
			// Квестовый генератор священника. Квест №1. Warship -->
			if(CheckAttribute(PChar, "GenQuest.ChurchQuest_1.NeedToDialogWithBarmen") && PChar.location == PChar.GenQuest.ChurchQuest_1.CurPortManColony + "_tavern")
	        {
	            dialog.Text = "Que souhaitez-vous, gracieux "+GetSexPhrase("monsieur","madame")+"?";
				link.l1 = "Une bouteille de rhum pour mon camarade à cette table là-bas.";
				link.l1.go = "Tavern_ChurchGenQuest1_Node_1";
				break;
			}
			// <-- Квестовый генератор священника. Квест №1.
			dialog.Text = LinkRandPhrase("Je vous écoute, capitaine.","Que puis-je vous offrir, capitaine?","Alors capitaine, ce sera quoi?");
			Link.l1 = "J'ai besoin d'un équipage, "+NPChar.name+".";
			Link.l1.go = "crew hire";
			Link.l2 = NPChar.name+", allons discuter...";
			Link.l2.go = "int_quests";
			if (CheckAttribute(pchar, "GenQuest.LoanChest.TakeChest") && sti(pchar.GenQuest.LoanChest.TargetIdx) == sti(NPChar.index))
			{
				link.l21 = "Je voudrais parler d'affaires financières.";
				link.l21.go = "LoanForAll";//(перессылка в кредитный генератор)
			}
			// Квестовый генератор священника. Квест №2. Warship -->
			if(CheckAttribute(PChar, "GenQuest.ChurchQuest_2.AskBarmen") && PChar.location == PChar.GenQuest.ChurchQuest_2.QuestTown + "_tavern")
	        {
				link.l10 = LinkRandPhrase("Pouvez-vous me dire quelque chose sur le récent vol dans l'église?","Que savez-vous du récent vol dans l'église?","Avez-vous entendu parler du récent vol dans l'église?");
				link.l10.go = "Tavern_GenQuest_Church_2_1";
			}
			// <-- Квестовый генератор священника. Квест №2.
			
			//Jason --> генератор Неудачливый вор
			if (CheckAttribute(pchar, "GenQuest.Device.Shipyarder") && NPChar.location == pchar.GenQuest.Device.Shipyarder.City + "_tavern" && pchar.GenQuest.Device.Shipyarder == "begin" && !CheckAttribute(npchar, "quest.Device"))
			{
   				link.l16 = "Les gens disent que tu sais à peu près tout dans cette colonie. Je veux acheter "+pchar.GenQuest.Device.Shipyarder.Type+", et on m'a dit qu'il avait été vendu dans votre ville. Eh bien, quelqu'un le vendait dans les rues. Pouvez-vous me dire quelque chose à ce sujet?";
				link.l16.go = "Device_Tavern";
			}
			// <-- генератор Неудачливый вор
			
			//Jason --> генератор Место под солнцем
			if (CheckAttribute(pchar, "GenQuest.Sunplace.Trader") && pchar.GenQuest.Sunplace.Trader == "continue" && NPChar.location == pchar.GenQuest.Sunplace.Trader.CityT + "_tavern")
			{
   				link.l17 = "Parlez-moi d'un racketteur du nom de "+pchar.GenQuest.Sunplace.Trader.Enemyname+". Où puis-je le trouver?";
				link.l17.go = "Sunplace_Tavern";
			}
			// <-- генератор Место под солнцем
			
			//--> Голландский гамбит
			if (CheckAttribute(pchar, "questTemp.HWIC.Holl") && pchar.questTemp.HWIC.Holl == "JacobOnMain" && NPChar.location == pchar.questTemp.HWIC.Holl.JacobCity + "_tavern")
				{
					link.l18 = "Bonjour, "+npchar.name+". J'ai besoin de trouver Jacob van Berg - où est-il ? Je ne le vois pas dans votre taverne...";
					link.l18.go = "HWICHollJacob_Tavern";
				}
				if (CheckAttribute(pchar, "questTemp.HWIC.Self") && pchar.questTemp.HWIC.Self == "start" && NPChar.nation == SPAIN && !CheckAttribute(npchar, "quest.HWICTalked"))
				{
					link.l18 = "Bonjour, "+npchar.name+". Je cherche un caballero du nom de Fernando Rodriguez. Est-ce qu'il est apparu dans votre ville?";
					link.l18.go = "HWICSelfFernando_Tavern";
				}
				//<-- Голландский гамбит
				
				//Jason --> гонки на гидропланах
				if (CheckAttribute(pchar, "GenQuest.Racing.Go.Advantage") && NPChar.location == pchar.GenQuest.Racing.Go.StartCity + "_tavern")
				{
					link.l19 = "Je suis venu chercher mes gains, qui sont bien gardés chez vous."+npchar.name+".";
					link.l19.go = "Race_Advantage";
				}
				// <-- гонки на гидропланах
				//Jason --> захват пассажиров
				if (CheckAttribute(pchar, "GenQuest.Marginpassenger") && pchar.GenQuest.Marginpassenger == "take" && NPChar.location == pchar.GenQuest.Marginpassenger.Targetcity+"_tavern")
				{
					link.l20 = "Je me demandais où je peux trouver un homme du nom de "+pchar.GenQuest.Marginpassenger.q2Name+"? Il habite dans votre ville.";
					link.l20.go = "Marginpassenger";
				}
				// <-- захват пассажиров
			if(!CheckAttribute(pchar,"questTemp.TimeLock"))
			{
				link.l3 = pcharrepphrase("Tu as une chambre libre, mon pote?","Vous avez une chambre libre, je resterais ici pendant un moment.");
				link.l3.go = "room";
			}
			Link.l4 = "Je suppose que je reviendrai plus tard.";
			Link.l4.go = "exit";
		break;
		
		case "crew hire":
			ok = (rColony.from_sea == "") || (Pchar.location.from_sea == rColony.from_sea);
			ok = sti(Pchar.Ship.Type) != SHIP_NOTUSED && ok;
			
			if (!ok)
			{
				Dialog.text = "Et pourquoi auriez-vous besoin de marins, capitaine? Je ne vois pas votre navire dans le port.";
				link.l1 = RandPhraseSimple("Exactement... J'avais amarré au mauvais endroit.","J'ai oublié d'entrer dans le port...");
				link.l1.go = "exit";
				break;
			}
			
            if (makeint(environment.time) > 22.0 || makeint(environment.time) < 7.0)
			{
				Dialog.text = "D'habitude, il y a beaucoup d'hommes qui cherchent à devenir marins, mais il est trop tard maintenant - ils commenceront à se montrer le matin. Peut-être aimeriez-vous louer une chambre et les attendre?";
				link.l1 = "D'accord. Avez-vous des chambres libres?";
				link.l1.go = "room";
				link.l2 = "Je ne suis pas intéressé par une chambre pour le moment. A bientôt.";
				link.l2.go = "exit";
			}
			else
			{
                if (GetNationRelation2MainCharacter(sti(NPChar.nation)) == RELATION_ENEMY && sti(NPChar.nation) != PIRATE)
                {
                    Dialog.text = "Tu crois que nous servons des criminels recherchés ici? Sois reconnaissant que je n'appelle pas les gardes.";
					link.l1 = "Merci.";
					link.l1.go = "exit";
                }
                else
                {
					if (pchar.location == pchar.questTemp.LadyBeth.CaptainInColony + "_tavern") // Блеквуд в городе
					{
						Dialog.text = "Capitaine, il n’y a pas âme qui vive à la taverne aujourd’hui. Tous ceux qui le voulaient sont partis avec le capitaine Blackwood.";
						link.l1 = "C'est dommage !";
						link.l1.go = "exit";
						break;
					}
					if (CheckAttribute(NPChar, "CrewHired.PGGId") && GetNpcQuestPastDayParam(NPChar, "CrewHired") < 3 && GetCrewQuantity(rColony) == 0)
					{
						Dialog.text = "Ah, désolé capitaine, vous êtes juste un peu trop tard. Tous les gars qui voulaient partir viennent juste de prendre la mer avec le vaillant capitaine "+GetFullName(CharacterFromID(NPChar.CrewHired.PGGId))+".";
						link.l1 = "C'est dommage !";
						link.l1.go = "exit_crew";
					}
					else
					{						
						if(bPartitionSet)
						{		
							if(GetPartitionAmount("CrewPayment") > 0)
							{
								if(IsEquipCharacterByArtefact(pchar, "totem_07"))
								{
									DeleteAttribute(NPChar, "CrewHired"); //на всяк случай.
									NextDiag.CurrentNode =  NextDiag.TempNode;
									DialogExit();
									LaunchHireCrew();							
								}
								else
								{
									dialog.text = "Capitaine, les gens disent que vous êtes assez avare. Nous n'avons personne ici qui aimerait rejoindre votre équipage.";
									link.l1 = "Je vois...";
									link.l1.go = "exit";
								}
							}
							else
							{
								DeleteAttribute(NPChar, "CrewHired"); //на всяк случай.
								NextDiag.CurrentNode =  NextDiag.TempNode;
								DialogExit();
								LaunchHireCrew();	
							}
						}	
						else
						{
							DeleteAttribute(NPChar, "CrewHired"); //на всяк случай.
							NextDiag.CurrentNode =  NextDiag.TempNode;
							DialogExit();
							LaunchHireCrew();							
						}						
					}
				}
			}
		break;
		
		case "exit_crew" :
			DeleteAttribute(NPChar, "CrewHired"); //на всяк случай.
			NextDiag.CurrentNode =  NextDiag.TempNode;
			DialogExit();
			LaunchHireCrew();
		break;
	////////////////////////////////////////////////////////=============================================///////////////////////////////////////////////////////	
        case "int_quests":
			dialog.text = "Je suis tout ouïe.";
			//link.l1 = "Je cherche du travail. Pouvez-vous m'aider?";
			//link.l1.go = "work";
			//homo 15/06/06 слухи
			link.l2 = LinkRandPhrase("Pouvez-vous me dire les dernières nouvelles?","Qu'est-ce qui se passe dans ces terres?","Quoi de neuf sur terre?");
			link.l2.go = "rumours_tavern";
			//homo
			link.l3 = "Je suis venu pour une affaire différente.";
			link.l3.go = "quests";
			if(CheckAttribute(pchar,"GenQuest.EncGirl"))
			{
				if(pchar.GenQuest.EncGirl == "EncGirlFack_fighted")
				{
					link.l5 = "Savez-vous où je peux trouver "+pchar.GenQuest.EncGirl.name+"?";
					link.l5.go = "EncGirl_1";
				}	
				if(pchar.GenQuest.EncGirl == "toParents" || pchar.GenQuest.EncGirl == "FindLover")
				{
					link.l6 = "Pouvez-vous me dire où je pourrais chercher "+pchar.GenQuest.EncGirl.sLoverId+"?";
					link.l6.go = "EncGirl_3";
				}
				if(pchar.GenQuest.EncGirl == "toLoverFather" && pchar.GenQuest.EncGirl.LoverFather == "tavern_keeper" && pchar.GenQuest.EncGirl.LoverCity == npchar.city)
				{
					link.l7 = "Ahoy, je suis venu à l'invitation de votre fils."; 
					link.l7.go = "EncGirl_4";
					pchar.quest.EncGirl_GetLoverFather.over = "yes";
				}
			}
			if(CheckAttribute(pchar,"GenQuest.CaptainComission") && NPChar.city == pchar.GenQuest.CaptainComission.City && CheckAttribute(pchar,"GenQuest.CaptainComission.Speak_Tavern"))
			{
				if(pchar.GenQuest.CaptainComission.variant == "A0")
				{												
					if(pchar.GenQuest.CaptainComission.Speak_Tavern == true)
					{
						link.l9 = "Alors, avez-vous vu  "+pchar.GenQuest.CaptainComission.Name+"?";
						link.l9.go = "CaptainComission_3";
					}
					else
					{
						link.l9 = "Pouvez-vous me dire où je devrais chercher  "+pchar.GenQuest.CaptainComission.Name+"?";
						link.l9.go = "CaptainComission_1";
					}
				}	

				if(pchar.GenQuest.CaptainComission.variant == "A2" && pchar.GenQuest.CaptainComission == "Begin_1")
				{
					link.l9 = "Savez-vous où je peux trouver le capitaine d'une patrouille "+GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.CaptainComission.ShipType),"Nom")+"Acc"))+" "+pchar.GenQuest.CaptainComission.Name+"?";
					link.l9.go = "CaptainComission_Tavern7";					
				}				
				if(pchar.GenQuest.CaptainComission.variant == "A3" && pchar.GenQuest.CaptainComission == "Begin_1")
				{
					if(pchar.GenQuest.CaptainComission.Speak_Tavern == true)
					{
						link.l9 = "Alors, avez-vous vu "+GetName(NAMETYPE_ORIG,pchar.GenQuest.CaptainComission.CanoneerName,NAME_NOM)+"?";
						link.l9.go = "CaptainComission_3";
					}
					else
					{					
						link.l9 = "Savez-vous quelque chose sur le capitaine d'une patrouille "+GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.CaptainComission.ShipType),"Nom")+"Acc"))+" "+pchar.GenQuest.CaptainComission.Name+"?";
						link.l9.go = "CaptainComission_Tavern1";
						if(!CheckAttribute(pchar,"GenQuest.CaptainComission.GetRumour"))
						{
							pchar.GenQuest.CaptainComission.GetRumour = true;
							SaveCurrentQuestDateParam("GenQuest.CaptainComission.GetRumour");
						}	
					}	
				}					
			}
			if(CheckAttribute(pchar,"GenQuest.Hold_GenQuest") && NPChar.city == pchar.GenQuest.Hold_GenQuest.City && pchar.GenQuest.Hold_GenQuest.Speak_Tavern == false )
			{
				link.l10 = "Pouvez-vous me dire où je peux trouver un homme appelé "+pchar.GenQuest.Hold_GenQuest.Name+"?";
				link.l10.go = "hold_genquest1";
			}
			if (CheckCharacterItem(pchar, "CaptainBook") && CheckAttribute(pchar, "questTemp.different.GiveShipLetters") && !CheckAttribute(pchar, "questTemp.different.GiveShipLetters.speakTavern") && (pchar.questTemp.different.GiveShipLetters.city == npchar.city))
			{
				link.l11 = "J'ai trouvé par hasard non loin d'ici quelques documents de navire....";
				link.l11.go = "ShipLetters_4";			
			}

			// Jason --> квест губера на поиск дезертира
			if(CheckAttribute(pchar, "GenQuest.FindFugitive") && pchar.GenQuest.FindFugitive != "Late" && sti(NPChar.nation) == PIRATE)
			{
				link.l12 = "Ecoute, je cherche un vieil ami à moi, "+pchar.GenQuest.FindFugitive.Name+" est son nom. Un camarade capitaine m'a dit qu'il se dirigeait vers votre établissement. L'avez-vous rencontré par hasard?";
				link.l12.go = "FindFugitiveTav";
			}
			//<-- поиск дезертира

			link.l15 = "Rien, merci, .";
			link.l15.go = "exit";
		break;
		
		case "hold_genquest1":
			switch(sti(pchar.GenQuest.Hold_GenQuest.TavernVariant))
			{
				case 0:
					dialog.text = LinkRandPhrase("Qu'est-ce que tu as dit?"+pchar.GenQuest.Hold_GenQuest.Name+"? Hmm... Jamais entendu parler de lui.","Es-tu certain qu'il vient de notre ville? Je n'ai jamais entendu parler d'une telle personne.","Il n'y avait personne de ce genre dans notre petite colonie. Jamais entendu parler de lui pendant tout mon temps ici.");
					link.l1 = "Êtes-vous sûr ?";
					link.l1.go = "hold_genquest2";					
				break;
				
				case 1: 
					switch (hrand(3))
					{
						case 0:
							pchar.GenQuest.Hold_GenQuest.foundStr = "the church";						
							pchar.GenQuest.Hold_GenQuest.found = "church";
						break;
						case 1:
							if (npchar.city != "Panama")
							{
							pchar.GenQuest.Hold_GenQuest.foundStr = "the shipyard";						
							pchar.GenQuest.Hold_GenQuest.found = "shipyard";
							}
							else
							{
								pchar.GenQuest.Hold_GenQuest.foundStr = "the church";						
								pchar.GenQuest.Hold_GenQuest.found = "church";
							}
						break;
						case 2:
							pchar.GenQuest.Hold_GenQuest.foundStr = "the usurer";												
							pchar.GenQuest.Hold_GenQuest.found = "bank";
						break;
						case 3:
							pchar.GenQuest.Hold_GenQuest.foundStr = "the shop";						
							pchar.GenQuest.Hold_GenQuest.found = "store";
						break;
					} 
					dialog.text = "Regarde "+pchar.GenQuest.Hold_GenQuest.foundStr+", il peut être trouvé là assez souvent.";
					link.l1 = "Merci, je vais faire exactement cela.";
					link.l1.go = "hold_genquest3";				
				break;
				
				case 2:
					dialog.text = LinkRandPhrase(RandPhraseSimple("Qu'est-ce que tu as dit ? "+pchar.GenQuest.Hold_GenQuest.Name+"? Hmm... Jamais entendu parler de lui. Etes-vous certain qu'il vient de notre village ? Je n'ai jamais entendu parler d'une telle personne.","He-he... Eh bien, maintenant seul le Seigneur Lui-même sait où le chercher - en enfer ou au paradis. Il est mort il y a plus d'un an, mais les gens demandent encore de ses nouvelles... Pas de repos pour le pauvre bougre..."),RandPhraseSimple("Vous ne le trouverez pas là - dans le pays des vivants du moins. Il est mort il n'y a pas si longtemps - la fièvre jaune... Que Dieu repose son âme... Quel homme robuste il était! Quand il était jeune, c'était un grand aventurier! Mais quand la mort vient après vous, il n'y a pas grand-chose que vous pouvez faire...","Oh, l'avez-vous manqué? Il a quitté ces endroits il y a longtemps. Personne ne sait où il est allé - peut-être dans les colonies nord-américaines, peut-être chez lui en Europe. Il a simplement rassemblé ses affaires et s'est enfui."),"Oh, tu cherches ça "+pchar.GenQuest.Hold_GenQuest.Name+" qui s'est enrichi et s'est acheté une maison en Nouvelle-Angleterre? Tu sais, il y avait des moments où je lui vendais du rhum à crédit - il me doit encore. Les gens sont si ingrats, tu sais.");
					link.l1 = "Je vois. Eh bien, merci quand même.";	
					link.l1.go = "hold_genquest4";
				break;
				
				case 3:
					dialog.text = "Eh bien, où d'autre le chercher, sinon la taverne? Il est un visiteur fréquent là-bas - noie ses péchés dans le vin, he-he. Reviens un peu plus tard - s'il se présente, je lui dirai de t'attendre.";	
					link.l1 = "Merci, je vais faire ça.";
					link.l1.go = "hold_genquest5";
				break;
			}
			pchar.GenQuest.Hold_GenQuest.Speak_Tavern = true;
		break;
		
		case "hold_genquest2":
			dialog.text = "Comment ne puis-je pas être sûr si je connais personnellement tout le monde ici. Ce n'est pas la première année que je tiens la taverne ici. "+"Je les ai tous vus dans toutes les conditions possibles. Parfois, une femme venait chercher son mari, parfois ils partaient seuls, et à certaines occasions, je devais les jeter dehors. 'Suis-je sûr?!' Bien sûr que je le suis!";
			link.l1 = "Eh bien, merci quand même...";	
			link.l1.go = "exit";
			pchar.GenQuest.Hold_GenQuest = "prisoner_escaped";
			AddQuestRecord("HoldQuest", "7");
			AddQuestUserData("HoldQuest", "sName", pchar.GenQuest.Hold_GenQuest.CapName);
			AddDialogExitQuestFunction("Hold_GenQuest_PrisonerEscaped");
		break;
		
		case "hold_genquest3":
			Hold_GenQuest_GenerateChar();		
			AddQuestRecord("HoldQuest", "8");
			AddQuestUserData("HoldQuest", "sCity", XI_ConvertString("Colony" + pchar.GenQuest.Hold_GenQuest.City + "Gen")); 			
			AddQuestUserData("HoldQuest", "sFoundChar", pchar.GenQuest.Hold_GenQuest.foundStr);
			AddQuestUserData("HoldQuest", "sName", pchar.GenQuest.Hold_GenQuest.Name);
			SetFunctionTimerConditionParam("Hold_GenQuest_FindCharTimeIsOver", 0, 0, 1, MakeInt(24 - GetHour()), false);
			DialogExit();
		break;
		
		case "hold_genquest4":
			AddQuestRecord("HoldQuest", "13");
			AddQuestUserData("HoldQuest", "sName", pchar.GenQuest.Hold_GenQuest.CapName);
			AddQuestUserData("HoldQuest", "sNameChar", pchar.GenQuest.Hold_GenQuest.Name);
			AddQuestUserData("HoldQuest", "sSex", GetSexPhrase("",""));
			CloseQuestHeader("HoldQuest");
			DeleteAttribute(pchar,"GenQuest.Hold_GenQuest");			
			DialogExit();
		break;
		
		case "hold_genquest5":
			SetFunctionTimerConditionParam("Hold_GenQuest_GetMapTimeIsOver", 0, 0, 1, MakeInt(24 - GetHour()), false);
			DialogExit();
			AddDialogExitQuestFunction("Hold_GenQuest_GenerateMapChar");			
		break;
		
		case "CaptainComission_1":
			dialog.text = LinkRandPhrase("Il est un visiteur fréquent ici, mais pour l'instant il n'est pas là. Revenez de temps en temps - je lui dirai d'attendre ici pour vous s'il se présente.","Il vient ici souvent. Si vous revenez plus tard, vous êtes sûr de le trouver là.","Revenez de temps en temps - il est un visiteur fréquent ici. Je lui dirai que vous le cherchiez.");
			link.l1 = "Merci, je reviendrai plus tard...";
			link.l1.go = "CaptainComission_2";
			pchar.GenQuest.CaptainComission.Speak_Tavern = true;
		break;
		
		case "CaptainComission_2":
			pchar.quest.CapComission_ExitFromTavern.win_condition.l1 = "ExitFromLocation";
			pchar.quest.CapComission_ExitFromTavern.win_condition.l1.location = pchar.location;
			pchar.quest.CapComission_ExitFromTavern.function = "CaptainComission_GenerateChar";

			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
		case "CaptainComission_3":
			dialog.text = "Il est déjà venu ici, donc il doit être quelque part autour...";
			link.l1 = "Merci.";
			link.l1.go = "exit";
			DeleteAttribute(pchar,"GenQuest.CaptainComission.Speak_Tavern");
		break;
		
		case "CaptainComission_Tavern1":
			pchar.GenQuest.CaptainComission.Speak_Tavern = true;
			dialog.text = "Y a-t-il un homme qui ne le connaît pas? Toute la colonie parle de lui depuis plusieurs jours déjà.";
			link.l1 = "Pourriez-vous m'en dire plus?";
			link.l1.go = "CaptainComission_Tavern2";
		break;
		
		case "CaptainComission_Tavern2":
			dialog.text = "Un peu, le capitaine a été exécuté, on peut dire la même chose de certains de ses équipiers. Le reste a été dispersé à travers les Caraïbes, déchu de rang et de position... Pour quoi ? Selon un juge, il avait coulé un pirate lors d'une patrouille et caché le butin pour lui-même\n"+"Voici la chose, ni le propriétaire de ce navire ou des marchandises n'ont été trouvés ... ils ont peigné les baies et les criques locales à leur recherche mais en vain.";
			link.l1 = "Quoi, aucun de l'équipage n'a révélé l'emplacement du trésor?";	
			link.l1.go = "CaptainComission_Tavern3";	
		break;
		
		case "CaptainComission_Tavern3":
			dialog.text = "Pas un seul ! Même sous la torture ! Je ne comprends toujours pas, pourquoi le gouverneur croirait si avidement à ces calomnies. Capitaine "+pchar.GenQuest.CaptainComission.Name+" avait une bonne réputation, et son équipage était bien formé et discipliné, de quoi faire envier n'importe quel amiral.";
			link.l1 = "Et où devrais-je chercher les membres d'équipage survivants?";
			link.l1.go = "CaptainComission_Tavern4";
		break;
		
		case "CaptainComission_Tavern4":
			dialog.text = "Je ne sais pas - ils se sont dispersés aux quatre vents... Bien que... il en reste encore un, mais je doute que tu apprennes grand chose de lui. Il a été gravement commotionné. Tu sais, il a servi comme canonnier sous "+pchar.GenQuest.CaptainComission.Name+". Il a été trouvé inconscient dans une crique deux jours après cet accident. D'abord, il a été envoyé à l'hôpital et traité comme un héros, mais alors que l'intrigue s'épaississait, ils l'ont jeté dans le donjon et ont essayé de l'interroger, mais ont ensuite décidé qu'il devrait d'abord être médicalement traité, de toute façon.";
			link.l1 = "Il est toujours ici?";
			link.l1.go = "CaptainComission_Tavern5";
		break;
		
		case "CaptainComission_Tavern5":
			pchar.GenQuest.CaptainComission.CanoneerName = "l" + rand(GetNamesCount(NAMETYPE_ORIG) - 1);
			dialog.text = "Oui, "+GetName(NAMETYPE_ORIG,pchar.GenQuest.CaptainComission.CanoneerName,NAME_NOM)+" c'est son nom. Il passe de temps en temps, dépense les sous qu'il gagne en mendiant sur le rhum. Pauvre âme. Si je le vois, je lui dirai de t'attendre ici.";
			link.l1 = "Merci, je reviendrai plus tard.";
			link.l1.go = "CaptainComission_Tavern6";
		break;
		
		case "CaptainComission_Tavern6":
			AddQuestRecord("CaptainComission2", "39");
			AddQuestUserData("CaptainComission2", "sShipType", GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.CaptainComission.ShipType),"Name") + "Gen"))); 
			AddQuestUserData("CaptainComission2", "sName", pchar.GenQuest.CaptainComission.Name);
			AddQuestUserData("CaptainComission2", "sCharName", GetName( NAMETYPE_ORIG, pchar.GenQuest.CaptainComission.CanoneerName, NAME_ABL));
			AddQuestUserData("CaptainComission2", "sShipName", pchar.GenQuest.CaptainComission.ShipTypeName);			
			SetFunctionExitFromLocationCondition("CaptainComission_GenerateCanoneer", pchar.location, false);
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
		case "CaptainComission_Tavern7":
			DeleteAttribute(pchar,"GenQuest.CaptainComission.Speak_Tavern");
			dialog.text = "Est-ce que je le connais? Bien sûr, je le connais. Et pourquoi en avez-vous besoin?";
			link.l1 = "J'ai des affaires avec lui...";
			link.l1.go = "CaptainComission_Tavern8";
		break;
		
		case "CaptainComission_Tavern8":
			dialog.text = ""+GetAddress_Form(pchar)+", vous devriez être prudent avec cette 'affaire'. "+pchar.GenQuest.CaptainComission.Name+" est détenu sous suspicion de piraterie, et les hommes du gouverneur fouillent maintenant l'île à la recherche de ses complices.";
			link.l1 = "Tu ne dis pas! Et qu'a-t-il fait?";
			link.l1.go = "CaptainComission_Tavern9";
		break;
		
		case "CaptainComission_Tavern9":
			dialog.text = "Je ne sais pas si c'est vrai ou non, mais ils disent qu'il avait cache la cargaison confisquee d'un navire pirate de passage et ne l'a pas remise. Et personne n'a encore trouve ni ce pirate, ni la cargaison. Je ne comprends toujours pas, pourquoi le gouverneur croirait si avidement a cette calomnie. Capitaine "+pchar.GenQuest.CaptainComission.CapName+"  avait une bonne réputation, et c'était un excellent soldat, tu peux me croire, "+GetAddress_Form(pchar)+".";
			link.l1 = "Eh bien, merci pour l'avertissement. A bientot.";
			link.l1.go = "CaptainComission_Tavern10";
		break;
		
		case "CaptainComission_Tavern10":
			if(!CheckAttribute(pchar,"GenQuest.CaptainComission.GetRumour"))
			{
				pchar.GenQuest.CaptainComission.GetRumour = true;
				SaveCurrentQuestDateParam("GenQuest.CaptainComission.GetRumour");
				SetFunctionTimerConditionParam("CaptainComission_TimeIsOver", 0, 0, 2, MakeInt(24 - GetHour()), false);
				AddQuestRecord("CaptainComission2", "19");
				AddQuestUserData("CaptainComission2", "sShipType", GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.CaptainComission.ShipType),"Name") + "Gen"))); // лесник окончание
				AddQuestUserData("CaptainComission2", "sName", pchar.GenQuest.CaptainComission.Name);
			}			
			DialogExit();
		break;
				
		case "EncGirl_1":
			dialog.text = "Et pourquoi en avez-vous besoin, d'elle ?";
			link.l1 = "J'ai des affaires avec elle...";
			link.l1.go = "EncGirl_2";
		break;
		
		case "EncGirl_2":
			dialog.text = "La moitié des hommes de notre colonie semblent avoir des affaires avec elle. Si nos femmes l'avaient attrapée, elles l'auraient jetée hors des portes de la ville, nue.";
			link.l1 = "Eh bien... "+GetSexPhrase("Il semble que je me suis retrouvé dans une longue file, alors. Eh bien, si quelqu'un d'autre vient poser des questions sur elle, dites-lui de se mettre en ligne derrière moi.","Je vois")+"Bonjour, monami.";
			link.l1.go = "exit";
			pchar.quest.EncGirl_SpeakTavernKeeper.over = "yes";
			DeleteAttribute(pchar, "GenQuest.EncGirl");
		break;
		
		case "EncGirl_3":
			dialog.text = "Il est un visiteur fréquent ici - il vient généralement à la recherche d'un emploi, mais pour l'instant il n'est pas là. Revenez de temps en temps - je lui dirai de vous attendre ici s'il se montre.";
			link.l1 = "Merci, je reviendrai plus tard...";
			link.l1.go = "exit";
			pchar.GenQuest.EncGirl = "FindingLover";
			pchar.quest.EncGirl_ExitTavern.win_condition.l1 = "ExitFromLocation";
			pchar.quest.EncGirl_ExitTavern.win_condition.l1.location = pchar.location;
			pchar.quest.EncGirl_ExitTavern.function = "EncGirl_GenerateLover";
		break;
		
		case "EncGirl_4":
			if(sti(pchar.GenQuest.EncGirl.LoverFatherAngry) == 0)
			{
				dialog.text = "Oh, donc tu es "+GetSexPhrase("ce capitaine, qui a apporté","cette demoiselle, qui a apporté")+" mon fils prodigue avec une jeune mariée?";
				link.l1 = "Oui, c'était moi qui avais aidé.";
				link.l1.go = "EncGirl_5";
			}
			else
			{
				dialog.text = "Ah, voila "+GetSexPhrase("c'est lui, notre bienfaiteur","elle est, notre bienfaitrice")+". J'imagine que tu attends une récompense, n'est-ce pas?";
				link.l1 = "Eh bien, je vais bien sans récompense, mais simplement vos remerciements suffiraient.";
				link.l1.go = "EncGirl_6";			
			}
		break;
		
		case "EncGirl_5":
			dialog.text = "Je vous suis très reconnaissant de ne pas avoir abandonné mon fils dans une situation désespérée et de l'avoir aidé à trouver une issue à une situation délicate. Permettez-moi de vous remercier et veuillez accepter cette modeste somme et un cadeau de ma part personnelle.";
			link.l1 = "Merci. Aider ce jeune couple a été mon plaisir.";
			link.l1.go = "EncGirl_5_1";
		break;
		
		case "EncGirl_6":
			dialog.text = "Des remerciements? Quels remerciements?! Cela fait un demi-année que ce crétin traîne sans emploi - et regardez-le, il a suffisamment de temps pour une liaison! Quand j'avais son âge, je dirigeais déjà ma propre entreprise! Pfft! Un gouverneur a une fille à marier - et ce nigaud a amené une coquine sans famille ni parenté dans ma maison et a osé demander ma bénédiction!";
			link.l1 = "Je suppose que tu ne crois pas en l'amour au premier regard?";
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
			dialog.text = "L'amour? L'amour !? Te moques-tu de moi ou es-tu stupide? Honte à toi d'indulger les jeunes dans leurs caprices et d'agir comme un proxénète! Non seulement tu as pris une fille de chez elle, mais tu as aussi ruiné la vie de mon garçon. Il n'y aura pas de merci pour toi. Adieu.";
			link.l1 = "Pareil pour toi alors.";
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
				
		case "ShipLetters_4":
			pchar.questTemp.different.GiveShipLetters.speakTavern = true;
			if(sti(pchar.questTemp.different.GiveShipLetters.variant) == 0)
			{
				dialog.text = "Laissez-moi y jeter un coup d'oeil! Hmm... Mais vous êtes vous-même un capitaine. Je pense que vous devriez voir cela avec le maître de port.";
				link.l1 = "Merci pour ton conseil.";
				link.l1.go = "exit";
			}
			else
			{
				dialog.text = "Laissez-moi jeter un coup d'oeil! Oh! En jugeant par le nom, cela appartient à l'un de mes clients, un monsieur assez respecté. Je peux moi-même remettre ces documents au propriétaire. Allez-vous me les donner?";
				link.l1 = "À la réflexion...";
				link.l1.go = "exit";
				link.l2 = "Prenez-les. Je suis ravi de pouvoir rendre service.";
				link.l2.go = "ShipLetters_end";				
			}	
		break;
		
		case "ShipLetters_end":
			TakeItemFromCharacter(pchar, "CaptainBook"); 
			pchar.questTemp.different = "free";
			pchar.quest.GiveShipLetters_null.over = "yes"; //снимаем таймер 
			AddQuestRecord("GiveShipLetters", "3");			
			CloseQuestHeader("GiveShipLetters");
			DeleteAttribute(pchar, "questTemp.different.GiveShipLetters"); 
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
		//zagolski. переделка
		case "work":
			if (sti(NPChar.nation) != PIRATE && GetNationRelation2MainCharacter(sti(NPChar.nation)) == RELATION_ENEMY)
			{
				dialog.text = RandPhraseSimple("Je ne me soucie pas de qui servir puisque l'argent n'a pas de nationalité. Mais je ne vous aiderai pas puisque vous êtes venu sous le drapeau de "+NationNameGenitive(sti(pchar.nation))+".","Je suis juste un simple propriétaire de taverne, mais la collaboration avec "+NationNameAblative(sti(pchar.nation))+" ne me semble pas attrayant.");
				link.l1 = RandPhraseSimple("Eh bien, comme vous voulez...","Eh bien, comme tu veux...");
				link.l1.go = "exit";
				break;
			}
			if (isBadReputation(pchar, 40))
			{
				dialog.text = RandPhraseSimple("Nous avons généralement beaucoup de passagers ici. Pourtant, je ne pense pas qu'il y aurait même un imbécile parmi eux, qui pourrait accepter de voyager sur votre navire. Votre mauvaise réputation vous précède, seul un fou embarquerait avec un tel vaurien.","Je suis assez souvent approché par des marchands qui ont besoin d'escorte. Mais votre mauvaise réputation vous précède, et je ne vous recommanderai à personne. Je me soucie de ma propre réputation, vous savez. Personne ne veut engager un loup pour garder leurs moutons.");
				link.l1 = RandPhraseSimple("Oh, vraiment, tu ne devrais pas croire toutes ces commérages...","Je vois. C'est difficile de faire taire tout le monde.","Les gens sont tout simplement trop doux ces jours-ci...");
				link.l1.go = "exit";
				break;
			}
			if (sti(Pchar.Ship.Type) == SHIP_NOTUSED)
        	{
				dialog.text = "Et où est ton navire ? Ou comptes-tu porter les passagers sur ton dos et nager ?";
				link.l1 = "Hey, tu as raison...";
				link.l1.go = "exit";
				break;
			}
			dialog.text = "Je pourrais avoir un travail si tu n'as pas peur de venir dans les colonies de pirates ou dans les ports des nations ennemies. Tu cherches quelque chose en particulier?";
			link.l1 = "Cela ne devrait pas être un problème. Je suppose que je pourrais fournir une escorte.";
			link.l1.go = "work_1";
			link.l2 = "Avez-vous des passagers ? Je peux les emmener où ils veulent, s'ils paient pour cela.";
			link.l2.go = "work_2";
			link.l3 = "Non, ce travail n'est pas pour moi. Merci.";
			link.l3.go = "exit";
		break;

		case "work_1":
				dialog.text = "Ils ne me demandent généralement pas pour une escorte. Demandez aux marchands dans la taverne - peut-être qu'ils auraient besoin de vos services.";
				link.l1 = "D'accord, comme tu dis.";
                link.l1.go = "exit";
		break;

		case "work_2":
			if (!CheckAttribute(npchar, "work_date") || GetNpcQuestPastDayParam(npchar, "work_date") >= 2 || bBettaTestMode)
    		{					
				if (GetSummonSkillFromName(pchar, SKILL_LEADERSHIP) < 5)//при низком авторитете не даем
				{
					dialog.text = "Je suis désolé, mais je n'ai personne qui souhaite voyager avec vous.";
					link.l1 = "Je vois.";
					link.l1.go = "exit";
					break;
				}
		         // пассажир
				if (hrand(6) > 1)
				{
					dialog.Text = "Il y a un homme, qui vient d'entrer - il se renseignait récemment sur un navire de passage. Vous pouvez lui parler, si vous le souhaitez.";
					link.l1 = RandPhraseSimple("Qui est-il ? Peut-être est-il un coquin ? Ou, pire encore, un pirate recherché ?","Et qui est-il ? Y aura-t-il des ennuis avec lui ?");
					Link.l1.go = "PassangerAreYouSure";
				}
				else
				{
					dialog.text = "Non, aujourd'hui personne n'a demandé à ce sujet. Peut-être, un autre jour.";
					link.l1 = RandPhraseSimple("Eh bien, si ce n'est pas là, ce n'est pas...","Juste ma chance... Eh bien, à plus, alors.");
					link.l1.go = "exit";
				}
            }
    		else
    		{
				dialog.text = "Il n'y a personne pour aujourd'hui. Reviens dans quelques jours.";
				link.l1 = "D'accord, comme tu dis.";
                link.l1.go = "exit";
    		}
        break;

        case "ConvoyAreYouSure":
		    dialog.text = LinkRandPhrase("Qui pourrait savoir? Tu as demandé - j'ai répondu.","Eh bien, c'est à toi de résoudre ça. Je ne me porterais pas garant pour personne là-bas.","Toutes sortes de gens viennent ici. C'est une taverne, cap'taine, pas le manoir du gouverneur.");
			Link.l1 = "Merci, nous marchanderons, alors.";
			Link.l1.go = "exit";
			pchar.quest.destination = findTraderCity(npchar);
			pchar.ConvoyQuest.City = npchar.city;
			AddDialogExitQuest("prepare_for_convoy_quest");
			SaveCurrentNpcQuestDateParam(npchar, "work_date");
        break;

        case "PassangerAreYouSure":
		    dialog.text = LinkRandPhrase("Qui pourrait savoir ? Tu as demandé - j'ai répondu.","Eh bien, c'est à vous de résoudre cela. Je ne me porterais garant pour personne là-bas.","Tout le monde vient ici. C'est une taverne, cap'tain, pas le manoir du gouverneur.");
			Link.l1 = "Je vois. Découvrons qui est cet homme...";
			Link.l1.go = "exit";
			sGlobalTemp = findPassangerCity(npchar);
			pchar.GenQuest.GetPassenger_City = npchar.city;
			AddDialogExitQuest("prepare_for_passenger_quest");
			SaveCurrentNpcQuestDateParam(npchar, "work_date");
        break;

		 case "fight":
			DialogExit();
            NextDiag.CurrentNode = NextDiag.TempNode;
			LAi_group_Attack(NPChar, Pchar);
		break;

		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
		case "Helen_room":
			dialog.text = "Bien sûr, Hélène. Combien de temps restez-vous? Et quoi, avez-vous eu une dispute avec la vieille Gladys?";
			if(!isDay())
			{
				link.l1 = "Juste pour dormir jusqu'au matin. Si je rentre maintenant, je vais sûrement la réveiller.";
				link.l1.go = "Helen_room_day";
			}
			else
			{
				link.l1 = "Non, non, j'ai juste besoin de prendre la mer la nuit, et je ne veux pas la réveiller.";
				link.l1.go = "Helen_room_night";
				link.l2 = "Je veux une bonne, longue nuit de sommeil et prendre mon temps pour me lever. Je prendrai une chambre pour un jour.";
				link.l2.go = "Helen_room_day_next";
			}
		break;

		case "room":
   			if (chrDisableReloadToLocation || CheckAttribute(pchar, "GenQuest.TavernClose")) //кто-то должен подойти к ГГ.
			{
				dialog.text = "La chambre est occupée, "+GetAddress_Form(NPChar)+", il n'y a rien que je puisse faire pour toi.";
				link.l1 = "Eh bien, c'est dommage...";
				link.l1.go = "exit";
				break;
			}
			// суп из черепахи
			if (CheckAttribute(pchar, "questTemp.Terrapin.Room_close") && npchar.location == "Tortuga_tavern")
			{
				dialog.text = "Monsieur Henri Thibaut loue la chambre en ce moment, et il a payé pour un mois à l'avance, donc il n'y a rien que je puisse faire pour vous, capitaine.";
				link.l1 = "Eh bien, c'est dommage...";
				link.l1.go = "exit";
				break;
			}
			if (CheckAttribute(pchar, "questTemp.Terrapin") && pchar.questTemp.Terrapin == "cave" && npchar.location == "Tortuga_tavern")
			{
				dialog.text = "La chambre est occupée, "+GetAddress_Form(NPChar)+", il n'y a rien que je puisse faire pour toi.";
				link.l1 = "Eh bien, c'est dommage...";
				link.l1.go = "exit";
				break;
			}
			if (CheckAttribute(pchar, "questTemp.Guardoftruth") && pchar.questTemp.Guardoftruth == "shore" && npchar.location == "Baster_tavern") // 070712
			{
				dialog.text = "La chambre est occupée, "+GetAddress_Form(NPChar)+", il n'y a rien que je puisse faire pour vous.";
				link.l1 = "Eh bien, c'est dommage...";
				link.l1.go = "exit";
				break;
			}
			if (pchar.location == pchar.questTemp.LadyBeth.CaptainInColony + "_tavern") // Блеквуд в городе
			{
				Dialog.text = "Hélas, non, capitaine. Toutes les chambres sont occupées par Blackwood et ses hommes.";
				if (CheckAttribute(pchar, "questTemp.LadyBeth_TavernRoomDialog"))
				{
					link.l1 = "Eh, dommage !";
					link.l1.go = "exit";
				}
				else
				{
					link.l1 = "Toutes les chambres ? Il y a plus d'une chambre ici ?";
					link.l1.go = "LadyBeth_Room";
				}
				break;
			}
			//-->> квест официантки
			if (pchar.questTemp.different == "FackWaitress_toRoom")
			{
				dialog.text = "Vous voulez louer une chambre? Pas de problème. 100 pièces de huit et elle est à vous.";
				if (sti(pchar.money) >= 100)
				{
					link.l1 = "Voici ton argent.";
					link.l1.go = "exit";
					AddMoneyToCharacter(pchar, -100);
					LocatorReloadEnterDisable(npchar.city + "_tavern", "reload2_back", false);
					pchar.questTemp.different = "FackWaitress_toRoomUp";
				}
				else
				{
					link.l1 = "Hmm... Je suppose que je reviendrai plus tard...";
					link.l1.go = "exit";
				}
				break;
			}
			if (pchar.questTemp.different == "FackWaitress_toRoomUp")//квест официантки
			{
				dialog.text = "La chambre est toute à vous. Entrez et détendez-vous.";
				link.l1 = "Merci, mon pote.";
				link.l1.go = "exit";
				break;
			}
			//<<-- квест официантки
			// --> квест "A damsel in the jungle"
			if(CheckAttribute(pchar,"GenQuest.EncGirl") && npchar.city == pchar.GenQuest.EncGirl.city)
			{
				if(pchar.GenQuest.EncGirl == "EncGirl_ToTavern")
				{
					dialog.text = "Vous voulez louer une chambre? Pas de problème. 100 pièces de huit et elle est à vous.";
					if (sti(pchar.money) >= 100)
					{
						link.l1 = "Voici ton argent.";
						link.l1.go = "exit";
						AddMoneyToCharacter(pchar, -100);
						LocatorReloadEnterDisable(npchar.city + "_tavern", "reload2_back", false);
						pchar.GenQuest.EncGirl = "EncGirl_toRoomUp";
					}
					else
					{
						link.l1 = "Hmm... Je suppose que je reviendrai plus tard...";
						link.l1.go = "exit";
					}
					break;
				}
				if (pchar.GenQuest.EncGirl == "EncGirl_toRoomUp")//квест  по спасению тетки в пампасах
				{
					dialog.text = "La chambre est toute à vous. Entrez et détendez-vous.";
					link.l1 = "Merci, camarade.";
					link.l1.go = "exit";
					break;
				}
			}
			// <-- квест "A damsel in the jungle"

			// belamour постоялец -->
			if (CheckAttribute(pchar, "GenQuest.Unwantedpostor") && !CheckAttribute(pchar, "questTemp.Sharlie.Lock") && abs(50-sti(pchar.reputation.nobility)) > 20)
			{
				if(pchar.GenQuest.Unwantedpostor == "start")
				{
					SetFunctionTimerCondition("Unwantedpostor_OneDay", 0, 0, 1, false);
					pchar.GenQuest.Unwantedpostor = "timer";
				}
				dialog.text = "Excusez-moi, capitaine, malheureusement il n'y a pas de chambre disponible. L'invité ne partira pas. Et ne m'a toujours pas payé...";
				link.l1 = "On dirait qu'on devra passer la nuit dans la salle commune...";
				link.l1.go = "Unwantedpostor_hall_day_wait";
				link.l2 = "Désolé. Parlons d'autre chose.";
				link.l2.go = "int_quests";
				if(pchar.GenQuest.Unwantedpostor != "Lose")
				{
					link.l3 = "Alors appelle les gardes. Quel genre d'invité est-ce: il ne paye pas d'argent, il ne veut pas partir...";
					link.l3.go = "Unwantedpostor";
				}
				break;
			}
			//<-- постоялец

			dialog.text = "Combien de temps comptez-vous rester ici?";
			if(!isDay())
			{
				link.l1 = "Jusqu'au matin.";
				link.l1.go = "room_day";
			}
			else
			{
				link.l1 = "Jusqu'à la nuit.";
				link.l1.go = "room_night";
				link.l2 = "Jusqu'au matin suivant.";
				link.l2.go = "room_day_next";
			}
			
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1)
			{
				pchar.questTemp.MarySexBlock = true;
				SetTimerFunction("Mary_DeleteSexBlock", 0, 0, 1);
			}
		break;

		case "room_day":
			dialog.text = "Cela vous coûtera 5 pièces de huit.";
			if (makeint(pchar.money) >= 5)
			{
				link.l1 = "Marché conclu. Voilà pour toi.";
				link.l1.go = "room_day_wait";
			}
			link.l2 = pcharrepphrase("A ce prix ? Vous louez des chambres royales ? Je préfère rester dans la salle commune gratuitement.","Hélas, le luxe de dormir dans un lit dépasse mes moyens actuels, il semble. Je suppose que je vais devoir dormir dans la salle commune sur un banc.");
			link.l2.go = "hall_day_wait";
			if (!CheckAttribute(pchar, "questTemp.Sharlie.Lock"))
			{
				link.l3 = "Non tout de suite. Changeons de sujet.";
				link.l3.go = "int_quests";
			}
		break;

		case "room_day_next":
			dialog.text = "Cela vous coûtera 10 pièces de huit.";
			if (makeint(pchar.money) >= 10)
			{
				link.l1 = "Marché conclu. Voilà pour toi.";
				link.l1.go = "room_day_wait_next";
			}
			link.l2 = pcharrepphrase("A ce prix ? Tu loues des chambres royales ? Je préférerais rester dans la salle commune gratuitement.","Hélas, le luxe de dormir dans un lit dépasse mes moyens actuels, il semble. Je suppose que je vais devoir dormir dans la salle commune sur un banc.");
			link.l2.go = "hall_day_wait";
			if (!CheckAttribute(pchar, "questTemp.Sharlie.Lock"))
			{
				link.l3 = "Non pour le moment. Changeons de sujet.";
				link.l3.go = "int_quests";
			}
		break;

		case "room_night":
			dialog.text = "Cela vous coûtera 5 pièces de huit.";
			if (makeint(pchar.money) >= 5)
			{
				link.l1 = "Marché conclu. Voici pour toi.";
				link.l1.go = "room_night_wait";
			}
			link.l2 = pcharrepphrase("A ce prix-là? Vous louez des chambres royales? Je préfère rester dans la salle commune gratuitement.","Hélas, le luxe de dormir dans un lit est au-delà de mes moyens actuels, il semble. Je suppose que je devrai dormir dans la salle commune sur un banc.");
			link.l2.go = "hall_night_wait";
			if (!CheckAttribute(pchar, "questTemp.Sharlie.Lock"))
			{
				link.l3 = "Non pas maintenant. Changeons de sujet.";
				link.l3.go = "int_quests";
			}
		break;

		case "room_night_wait":
			// belamour прерывание ночной приключенец -->
			if(CheckAttribute(pchar,"GenQuest.NightAdventureId"))
			{
				if(GetCharacterIndex(pchar.GenQuest.NightAdventureId) != -1)
				{
					sld = characterFromId(pchar.GenQuest.NightAdventureId);
					ChangeCharacterAddressGroup(sld, "none", "", "");
				}
				SetFunctionTimerCondition("NightAdventure_KillPhant", 0, 0, 0, false);
			}
			// <-- прерывание ночного приключенца 
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			AddMoneyToCharacter(pchar, -5);
			AddDialogExitQuest("sleep_in_tavern");
			TavernWaitDate("wait_night");
		break;

		case "hall_night_wait":
			if (hRand(3) == 1)
            {
                dialog.text = "Dégage d'ici, espèce de vaurien ! La salle commune est libre, mais nous attendons un comportement décent !";
				link.l1 = "D'accord, d'accord, je pars.";
				link.l1.go = "exit";
            }
            else
            {
				DialogExit();
				NextDiag.CurrentNode = NextDiag.TempNode;
				TavernWaitDate("wait_night");
			}
		break;

		case "room_day_wait":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			AddMoneyToCharacter(pchar, -5);
			AddDialogExitQuest("sleep_in_tavern");
			// belamour прерывание ночной приключенец -->
			if(CheckAttribute(pchar,"GenQuest.NightAdventureId"))
			{
				if(GetCharacterIndex(pchar.GenQuest.NightAdventureId) != -1)
				{
					sld = characterFromId(pchar.GenQuest.NightAdventureId);
					ChangeCharacterAddressGroup(sld, "none", "", "");
				}
				SetFunctionTimerCondition("NightAdventure_KillPhant", 0, 0, 0, false);
			}
			// <-- прерывание ночного приключенца 
			if (CheckAttribute(pchar, "GenQuest.LigaAttack") && hrand(1) == 1)
			{
				TavernWaitDate("wait_night");
				pchar.GenQuest.LigaAttack.Go = "true"; //атака киллеров
			}
			else TavernWaitDate("wait_day");
		break;

		case "room_day_wait_next":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			AddMoneyToCharacter(pchar, -10);
			AddDialogExitQuest("sleep_in_tavern");
			// belamour прерывание ночной приключенец -->
			if(CheckAttribute(pchar,"GenQuest.NightAdventureId"))
			{
				if(GetCharacterIndex(pchar.GenQuest.NightAdventureId) != -1)
				{
					sld = characterFromId(pchar.GenQuest.NightAdventureId);
					ChangeCharacterAddressGroup(sld, "none", "", "");
				}
				SetFunctionTimerCondition("NightAdventure_KillPhant", 0, 0, 0, false);
			}
			// <-- прерывание ночного приключенца 
			if (CheckAttribute(pchar, "GenQuest.LigaAttack") && hrand(1) == 1)
			{
				TavernWaitDate("wait_night");
				pchar.GenQuest.LigaAttack.Go = "true"; //атака киллеров
			}
			else TavernWaitDate("wait_day");
		break;

		case "hall_day_wait":
			if (hrand(1) == 1)
            {
                dialog.text = "Dégage d'ici, espèce de vaurien! La salle commune peut être libre, mais nous attendons un comportement décent!";
				link.l1 = "D'accord, d'accord, je m'en vais.";
				link.l1.go = "exit";
            }
            else
            {
				// belamour прерывание ночной приключенец -->
				if(CheckAttribute(pchar,"GenQuest.NightAdventureId"))
				{
					sld = characterFromId(pchar.GenQuest.NightAdventureId);
					ChangeCharacterAddressGroup(sld, "none", "", "");
					SetFunctionTimerCondition("NightAdventure_KillPhant", 0, 0, 0, false);
				}
				// <-- прерывание ночного приключенца
				DialogExit();
				NextDiag.CurrentNode = NextDiag.TempNode;
				TavernWaitDate("wait_day");
			}
		break;
		
		case "tavern_keeper":
			NextDiag.TempNode = "First time";

			dialog.text = "Arrêtez ce comportement scandaleux dans ma taverne à l'instant ou j'appelle les gardes !";
			link.l1 = "D'accord, d'accord, je m'en vais.";
			link.l1.go = "exit_sit";
		break;

		case "exit_sit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			AddDialogExitQuest("exit_sit");
		break;
		
		//******************* ноды квеста священника. поиск грабителей (квест № 2)**********************
		case "Tavern_GenQuest_Church_2_1":
			dialog.text = "Je n'en sais pas beaucoup à ce sujet... Tu ferais mieux de demander aux clients.";
			link.l1 = "Je vois, merci.";
			link.l1.go = "exit";
			DeleteAttribute(PChar, "GenQuest.ChurchQuest_2.AskBarmen");
		break;
			
		//******************* ноды квеста священника. вернуть рукописи (квест № 1)**********************
		case "Tavern_ChurchGenQuest1_Node_1":
			dialog.text = "Nous ne fournissons pas de services à crédit, "+GetSexPhrase("monsieur","mademoiselle")+".";
			link.l1 = "Je paie en bonne monnaie. N'acceptez-vous plus l'or ou l'argent?";
			link.l1.go = "Tavern_ChurchGenQuest1_Node_2";
		break;
			
		case "Tavern_ChurchGenQuest1_Node_2":
			dialog.text = "Je suis désolé, "+GetSexPhrase("monsieur","mademoiselle")+"capitaine, mais votre ami avait une dette, et je pensais...";
			link.l1 = "Pense moins et travaille plus vite, camarade. Maintenant, combien doit mon ami vaillant vous?";
			link.l1.go = "Tavern_ChurchGenQuest1_Node_3";
		break;
			
		case "Tavern_ChurchGenQuest1_Node_3":
			iTemp = (rand(3)+1)*100;
			PChar.GenQuest.ChurchQuest_1.MoneyToBarmen = iTemp;
			if(rand(1) == 0) // "If he's a simple one and pays right away"
			{
				dialog.text = FindRussianMoneyString(iTemp)+", manque"+GetSexPhrase("ter","s")+" capitaine, et il a aussi mis en gage quelques livres d'église - c'est tout ce qu'il avait sur lui, qui avait une certaine valeur.";
				if(sti(PChar.money) >= iTemp)
				{
					link.l1 = "Voici tes pièces. Donne les manuscrits. Et fais attention à eux - ce n'est pas un livre de gravures obscènes, mais la Sainte Ecriture!";
					link.l1.go = "Tavern_ChurchGenQuest1_Node_4_1";
				}
				else
				{
					link.l1 = "Attends un peu... Je reviendrai avec l'argent";
					link.l1.go = "exit";
					PChar.GenQuest.ChurchQuest_1.NoMoneyToBarmen = true;
				}
			}
			else // "If he's not a simple one"
			{
				dialog.text = FindRussianMoneyString(iTemp)+", mes"+GetSexPhrase("ter","s")+" capitaine.";
				link.l1 = "Je paierai sa dette et prendrai tout ce qu'il a laissé pour la garantir.";
				link.l1.go = "Tavern_ChurchGenQuest1_Node_4_2";
			}
		break;
			
		case "Tavern_ChurchGenQuest1_Node_4_1":
			DialogExit();
			AddMoneyToCharacter(PChar, -sti(PChar.GenQuest.ChurchQuest_1.MoneyToBarmen));
			AddItems(PChar, "Bible", 1);	// Даем рукописи
			items[FindItem("Bible")].Name = "itmname_ChurchGenQuest1Bible";	// Меняем имя. Потом поменять обратно!
			ChangeItemDescribe("Bible", "itmdescr_ChurchGenQuest1Bible"); // Меняем дескрайб. Потом поменять обратно!
			items[FindItem("Bible")].City = XI_ConvertString("Colony" + PChar.GenQuest.ChurchQuest_1.QuestTown + "Gen"); // Переменная. Потом удалить!
			DeleteAttribute(PChar, "GenQuest.ChurchQuest_1.NeedToDialogWithBarmen");
			sQuestTitle = PChar.GenQuest.ChurchQuest_1.QuestTown + "ChurchGenQuest1";
			AddQuestRecordEx(sQuestTitle, "ChurchGenQuest1", "8");
			AddQuestUserData(sQuestTitle, "sColony", XI_ConvertString("Colony" + PChar.GenQuest.ChurchQuest_1.QuestTown + "Gen"));
			AddQuestUserData(sQuestTitle, "sName", GetFullName(CharacterFromID("ChurchGenQuest1_Cap")));
			PChar.GenQuest.ChurchQuest_1.Complete = true; // Квест выполнен
			SetFunctionTimerCondition("Church_GenQuest1_DeleteCapitan", 0, 0, 2, false);
		break;
			
		case "Tavern_ChurchGenQuest1_Node_4_2":
			dialog.text = "Non, monsieur"+GetSexPhrase("ter","s")+", cela ne marchera pas comme ça.";
			link.l1 = "Que voulez-vous dire par 'cela ne marchera pas comme ça'? Une dette de capitaine est payée - il est bon. Vous avez votre argent en retour - vous êtes bon. Je prends son engagement - je suis bon. Tout le monde est bon - alors pourquoi 'cela ne marchera pas comme ça'?";
			link.l1.go = "Tavern_ChurchGenQuest1_Node_4_2_1";
		break;
			
		case "Tavern_ChurchGenQuest1_Node_4_2_1":
			dialog.text = "Parce que, mademoiselle"+GetSexPhrase("ter","s")+" capitaine, je n'ai pas besoin de l'argent. Parce que je connais trop bien ce capitaine, alors je n'ai jamais vraiment espéré qu'il me rembourse et prenne ces manuscrits de moi.";
			link.l1 = "Que voulez-vous dire - vous n'avez pas besoin d'argent? Alors vous aviez prévu de garder ces livres dès le départ? Mais pourquoi, au nom de Dieu?!";
			link.l1.go = "Tavern_ChurchGenQuest1_Node_4_2_2";
		break;
			
		case "Tavern_ChurchGenQuest1_Node_4_2_2":
			dialog.text = "Au nom de Dieu - exactement, c'est pourquoi, madame"+GetSexPhrase("ter","s")+". Mon petit garçon était très malade, et moi et ma femme avons fait le vœu de faire un don à l'Église si notre Seigneur Béni guérissait l'enfant de la fièvre. La miséricorde de notre Seigneur est sans fin, mon garçon est vivant et en bonne santé, et maintenant nous devons tenir notre vœu. Et juste à temps capitaine "+PChar.GenQuest.ChurchQuest_1.CapFullName+" se présente et gage ces livres d'église. Je ne pouvais pas permettre une telle obscénité - payer des verres avec la Parole - et donc j'ai décidé de remettre ces livres au pasteur de notre paroisse.";
			link.l1 = "Eh bien, certainement c'est une bonne action, mais tu devrais aussi savoir que ces livres appartiennent en réalité à un autre prêtre - en fait, pas seulement à un prêtre, mais à un évêque et mon guide spirituel. Et il pourrait se fâcher et même maudire ceux qui oseraient donner des biens d'église volés. J'aimerais les acheter de toi et les ramener en sécurité chez eux. Tu peux donner l'argent à ta paroisse, je suis sûr que Dieu l'appréciera tout autant.";
			link.l1.go = "Tavern_ChurchGenQuest1_Node_4_2_3";
		break;
			
		case "Tavern_ChurchGenQuest1_Node_4_2_3":
			dialog.text = "Raté"+GetSexPhrase("ter","s")+"... Manqué"+GetSexPhrase("ter","s")+" capitaine... Bien sûr, je n'avais aucune idée ! Je les rendrai, et je ne demanderai pas d'argent en retour. Vous n'avez qu'à dire un mot pour nous au évêque - peut-être, pourrait-il nous bénir et nous soulager de notre voeu...";
			link.l1 = "Bien sûr que votre serment sera considéré comme tenu ! Après tout, vous avez abandonné votre profit pour rendre les livres à leur véritable propriétaire. L'église particulière n'a pas d'importance, car il n'y a qu'un seul Dieu et une seule Sainte Église Catholique Apostolique, n'est-ce pas ? Très bien, donnez-les-moi, et bonne chance à vous...";
			link.l1.go = "Tavern_ChurchGenQuest1_Node_4_2_4";
		break;
			
		case "Tavern_ChurchGenQuest1_Node_4_2_4":
			DialogExit();
			AddItems(PChar, "Bible", 1);	// Даем рукописи
			items[FindItem("Bible")].Name = "itmname_ChurchGenQuest1Bible";	// Меняем имя. Потом поменять обратно!
			ChangeItemDescribe("Bible", "itmdescr_ChurchGenQuest1Bible"); // Меняем дескрайб. Потом поменять обратно!
			items[FindItem("Bible")].City = XI_ConvertString("Colony" + PChar.GenQuest.ChurchQuest_1.QuestTown + "Gen"); // Переменная. Потом удалить!
			AddMoneyToCharacter(PChar, -sti(PChar.GenQuest.ChurchQuest_1.MoneyToBarmen));
			DeleteAttribute(PChar, "GenQuest.ChurchQuest_1.NeedToDialogWithBarmen");
			sQuestTitle = PChar.GenQuest.ChurchQuest_1.QuestTown + "ChurchGenQuest1";
			AddQuestRecordEx(sQuestTitle, "ChurchGenQuest1", "9");
			AddQuestUserData(sQuestTitle, "sColony", XI_ConvertString("Colony" + PChar.GenQuest.ChurchQuest_1.QuestTown)); // belamour gen
			PChar.GenQuest.ChurchQuest_1.Complete = true; // Квест выполнен
			SetFunctionTimerCondition("Church_GenQuest1_DeleteCapitan", 0, 0, 2, false);
		break;
		
		//Jason --> генератор Неудачливый вор
		case "Device_Tavern":
			dialog.text = "Hmm, "+pchar.GenQuest.Device.Shipyarder.Type+"? Jamais entendu parler avant... C'est quoi, en fait? Je n'ai jamais entendu parler d'une telle chose de toute ma vie.";
			link.l1 = "Eh bien, c'est un outil de charpentier de marine, "+pchar.GenQuest.Device.Shipyarder.Describe+". Quelqu'un t'a-t-il proposé quelque chose comme ça?";
			link.l1.go = "Device_Trader_1";
			npchar.quest.Device = "true";
		break;
		
		case "Device_Trader_1":
			if (sti(pchar.GenQuest.Device.Shipyarder.Chance1) == 6)
			{
				dialog.text = "Hmm... Oui, un drôle de gars m'a effectivement apporté cette chose. Il ne m'a pas dit ce que c'était, cependant - il a juste essayé de l'échanger contre de l'alcool. Bien sûr, j'ai refusé - je n'avais pas besoin de ce bibelot.";
				link.l1 = "Et à quoi ressemblait-il et où est-il allé ? J'ai grandement besoin de cet instrument.";
				link.l1.go = "Device_Common";
			}
			else
			{
				dialog.text = "Non, rien de tel. Désolé, je ne peux pas t'aider. Demande autour de toi.";
				link.l1 = "Je vois. Eh bien - il est temps de poser des questions!";
				link.l1.go = "exit";
			}
		break;
		// <-- генератор Неудачливый вор
		
		//Jason --> генератор Место под солнцем
		case "Sunplace_Tavern":
			if (makeint(environment.time) > 12.0 && makeint(environment.time) < 17.0)//в магазине
			{
				dialog.text = ""+pchar.GenQuest.Sunplace.Trader.Enemyname+"? Il était là récemment, et maintenant il devrait être chez son compagnon - le commerçant. Essayez de le chercher dans la boutique - sûrement il doit y être.";
				link.l1 = "Merci! Tu m'as beaucoup aidé!";
				link.l1.go = "Sunplace_Tavern_1";
			}
			else//ушел на рыбалку
			{
				dialog.text = ""+pchar.GenQuest.Sunplace.Trader.Enemyname+"? Aujourd'hui, tôt le matin, il est parti en mer sur son chalutier. Je parie qu'il est maintenant au parapet, admirant la vue. Si vous avez besoin de lui, vous pouvez essayer de le trouver en mer ou attendre qu'il revienne dans quelques jours...";
				link.l1 = "Merci! Je pense que je ne vais pas attendre - ce sera plus facile de le trouver en mer. Bonne chance!";
				link.l1.go = "Sunplace_Tavern_2";
			}
		break;
		
		case "Sunplace_Tavern_1"://магазин
			pchar.quest.Sunplace_Store.win_condition.l1 = "location";
			pchar.quest.Sunplace_Store.win_condition.l1.location = pchar.GenQuest.Sunplace.Trader.CityT + "_store";
			pchar.quest.Sunplace_Store.function = "Sunplace_CreateTrader";
			AddQuestRecord("Sunplace", "6");
			AddQuestUserData("Sunplace", "sName", pchar.GenQuest.Sunplace.Trader.Enemyname);
			AddQuestUserData("Sunplace", "sCity", XI_ConvertString("Colony"+pchar.GenQuest.Sunplace.Trader.CityT+"Gen"));
			DialogExit();
			pchar.GenQuest.Sunplace.Trader = "hunt";
		break;
		
		case "Sunplace_Tavern_2"://рыбалка
			pchar.GenQuest.Sunplace.Trader.IslandID = GetCharacterCurrentIslandId(npchar);
			pchar.GenQuest.Sunplace.Trader.EnemyNation = npchar.nation;
			pchar.quest.Sunplace_Sea.win_condition.l1 = "location";
			pchar.quest.Sunplace_Sea.win_condition.l1.location = pchar.GenQuest.Sunplace.Trader.IslandID;
			pchar.quest.Sunplace_Sea.function = "Sunplace_CreateTraderLugger";
			AddQuestRecord("Sunplace", "7");
			AddQuestUserData("Sunplace", "sName", pchar.GenQuest.Sunplace.Trader.Enemyname);
			AddQuestUserData("Sunplace", "sCity", XI_ConvertString("Colony"+pchar.GenQuest.Sunplace.Trader.CityT+"Gen"));
			DialogExit();
			pchar.GenQuest.Sunplace.Trader = "hunt";
		break;
		// <-- генератор Место под солнцем	
		
		// Jason --> Голландский гамбит
		case "HWICHollJacob_Tavern":
			dialog.text = "Psssst... Pourquoi tu cries? Il t'attend depuis un bon moment. Il a déjà bu un litre complet de rhum. Monte à la pièce, tu le trouveras là.";
			link.l1 = "Oh, je vois. Espérons qu'il soit encore éveillé.";
			link.l1.go = "exit";
			LocatorReloadEnterDisable(pchar.questTemp.HWIC.Holl.JacobCity+"_tavern", "reload2_back", false);
			pchar.questTemp.HWIC.Holl = "JacobInRoom";
			AddDialogExitQuestFunction("Create_JacobVanBerg");
			DelLandQuestMark(npchar);
		break;
		
		case "HWICSelfFernando_Tavern":
			if (NPChar.location == pchar.questTemp.HWIC.Self.SpainCity +"_tavern")
			{
				//DelMapTonzagAllQM();
				dialog.text = "Oui, je connais ce monsieur. Il devrait être quelque part en ville - je l'ai juste récemment vu passer devant ma fenêtre.";
				link.l1 = "Merci! Je vais aller le chercher!";
				link.l1.go = "Fernando_Land";
				/* if (makeint(environment.time) > 10.0 && makeint(environment.time) < 18.0)//на улице
				{
					dialog.text = "Oui, je connais ce monsieur. Il devrait être quelque part en ville - je l'ai juste récemment vu passer devant ma fenêtre.";
					link.l1 = "Merci! Je vais aller le chercher!";
					link.l1.go = "Fernando_Land";
				}
				else //в море
				{
					dialog.text = "Oui, il visite actuellement notre ville. Il n'est pas ici pour le moment - il a navigué sur sa brigantine. Il n'est probablement pas loin d'ici, dans les eaux de notre île.";
					link.l1 = "Merci, mon pote! Tu m'as beaucoup aidé!";
					link.l1.go = "Fernando_Sea";
				} */
				pchar.questTemp.HWIC.Self = "KillFernando";
			}
			else
			{
				dialog.text = "Fernando Rodriguez? Jamais entendu parler de lui. Non, je ne sais rien de cet homme.";
				link.l1 = "Je vois... Eh bien, la recherche continue....";
				link.l1.go = "exit";
			}
			npchar.quest.HWICTalked = "true";
		break;
		
		case "Fernando_Land":
			pchar.quest.HWIC_Fernando.win_condition.l1 = "location";
			pchar.quest.HWIC_Fernando.win_condition.l1.location = pchar.questTemp.HWIC.Self.SpainCity +"_town";
			pchar.quest.HWIC_Fernando.function = "CreateFernandoOnLand";
			AddQuestRecord("Holl_Gambit", "3-2");
			DialogExit();
		break;
		
		case "Fernando_Sea":
			pchar.questTemp.HWIC.Self.FernandoIslandID = GetCharacterCurrentIslandId(npchar);
			pchar.quest.HWIC_Fernando.win_condition.l1 = "location";
			pchar.quest.HWIC_Fernando.win_condition.l1.location = pchar.questTemp.HWIC.Self.FernandoIslandID;
			pchar.quest.HWIC_Fernando.function = "CreateFernandoOnSea";
			AddQuestRecord("Holl_Gambit", "3-3");
			DialogExit();
		break;
		//<-- Голландский гамбит
		
		//Jason --> гонки на гидропланах
		case "Race_Advantage":
			dialog.text = "Oui, bien sûr. Félicitations capitaine. Je suis déjà au courant de votre victoire. Voici votre argent.";
			link.l1 = "Merci, "+npchar.name+".";
			link.l1.go = "Race_Advantage_1";
		break;
		
		case "Race_Advantage_1":
			DialogExit();
			AddMoneyToCharacter(pchar, sti(pchar.GenQuest.Racing.Go.Money)*2);
			AddQuestRecord("Racing", "4");
			AddQuestUserData("Racing", "sStartCity", XI_ConvertString("Colony"+pchar.GenQuest.Racing.Go.StartCity+"Gen"));
			CloseQuestHeader("Racing");
			DeleteAttribute(pchar, "GenQuest.Racing.Go");
		break;
		//<-- гонки на гидропланах
		
		//Jason --> захват пассажиров
		case "Marginpassenger":
			if (CheckAttribute(pchar, "GenQuest.Marginpassenger.lose"))
			{
				dialog.text = "Euh, monsieur, "+pchar.GenQuest.Marginpassenger.q2Name+" est mort environ "+LinkRandPhrase("un mois","trois semaines","deux mois")+" il y a. "+LinkRandPhrase("Soudainement succombé à la fièvre","Il a été poignardé aux portes de la ville - des bandits ou ces sauvages à la peau rouge","Il a été tué dans un duel")+". Que Dieu repose son âme...";
				link.l1 = "Sacrebleu!.. Et que suis-je censé faire avec son... Enfin, peu importe. Merci pour l'information. A la revoyure, "+npchar.name+".";
				link.l1.go = "Marginpassenger_1";
			}
			else
			{
				dialog.text = ""+pchar.GenQuest.Marginpassenger.q2Name+"? Ouais, il devrait être quelque part en ville. Cherchez-le dans les rues. Mais n'oubliez pas que chaque jour jusqu'à midi, il est au bureau du gouverneur, et après neuf heures du soir, il se cloître dans sa maison.";
				link.l1 = "Merci! Je vais le chercher...";
				link.l1.go = "Marginpassenger_2";
			}
		break;
		
		case "Marginpassenger_1":
			DialogExit();
			AddQuestRecord("Marginpassenger", "7");
			AddQuestUserData("Marginpassenger", "sName2", pchar.GenQuest.Marginpassenger.q2Name);
			AddQuestUserData("Marginpassenger", "sCity", XI_ConvertString("Colony"+pchar.GenQuest.Marginpassenger.City));
			// belamour gen: Добряку недолго осталось -->
			if(CheckAttribute(pchar, "questTemp.LongHappy"))
			{
				AddQuestUserData("Marginpassenger", "sBaron", "to Puerto Principe, to the Black Pastor");
			}
			else
			{
				AddQuestUserData("Marginpassenger", "sBaron", "to Le Francois, to Kindly Jacques");
			}
			// <-- belamour gen
			pchar.GenQuest.Marginpassenger = "cabin";
		break;
		
		case "Marginpassenger_2":
			DialogExit();
			AddQuestRecord("Marginpassenger", "8");
			AddQuestUserData("Marginpassenger", "sName2", pchar.GenQuest.Marginpassenger.q2Name);
			pchar.GenQuest.Marginpassenger = "street";
		break;
		//<-- захват пассажиров
		
		//Jason --> поиск дезертира
		case "FindFugitiveTav":
			if (NPChar.city == pchar.GenQuest.FindFugitive.City && sti(pchar.GenQuest.FindFugitive.Chance) == 0)
			{
				dialog.text = NPCStringReactionRepeat("Il semble que votre capitaine disait la vérité. "+pchar.GenQuest.FindFugitive.Name+" est en effet récemment arrivé dans notre colonie. Cherchez-le dans les rues pendant la journée - il passe généralement son temps à traînasser.","Vous m'avez déjà demandé à propos de cet homme, et je vous ai dit tout ce que je savais!","Tu te moques de moi ou tu es vraiment un idiot ?! Tu poses la même question pour la troisième fois déjà !","Juste à penser, comment un tel idiot pourrait devenir capitaine...","bloc",1,npchar,Dialog.CurrentNode);
				link.l1 = HeroStringReactionRepeat("Merci, mon ami, tu m'as beaucoup aidé !","Ouais, ouais, d'accord.","Eh bien, eh bien, ne te réjouis pas tant. J'ai simplement oublié.","Eh bien, il l'a fait, comme tu peux le voir...",npchar,Dialog.CurrentNode); 
				link.l1.go = DialogGoNodeRepeat("FindFugitiveTav_1", "exit", "", "", npchar, Dialog.CurrentNode);
			}
			else
			{
				dialog.text = NPCStringReactionRepeat("Non, mon pote, je n'ai jamais entendu ce nom auparavant. Demande autour - peut-être que quelqu'un le connaît...","Vous m'avez déjà demandé à propos de cet homme, et je vous ai dit : Je ne sais pas !","Tu te moques de moi ou tu es vraiment un idiot?! Tu poses la même question pour la troisième fois déjà!","Juste à penser, comment un tel idiot pourrait devenir capitaine...","bloc",1,npchar,Dialog.CurrentNode);
				link.l1 = HeroStringReactionRepeat("Je vois. Eh bien, merci quand même.","Ouais, ouais, d'accord.","Wow, Wow, ne t'excite pas comme ça. J'ai juste oublié.","Eh bien, il l'a fait, comme vous pouvez le voir...",npchar,Dialog.CurrentNode); 
				link.l1.go = DialogGoNodeRepeat("exit", "", "", "", npchar, Dialog.CurrentNode);	
			}
		break;
		
		case "FindFugitiveTav_1":
			DialogExit();
			AddQuestRecord("MayorsQuestsList", "12-1");
			sld = characterFromId("Fugitive");
			LAi_SetWarriorType(sld);
			LAi_warrior_DialogEnable(sld, true);
			sld.dialog.currentnode = "Fugitive_city";
			LAi_SetLoginTime(sld, 11.0, 18.0);
			ChangeCharacterAddressGroup(sld, pchar.GenQuest.FindFugitive.City+"_town", "goto", "goto"+(rand(9)+1));
		break;
		//<-- поиск дезертира
		
		//--> Бремя гасконца
		case "Sharlie_crew":
			dialog.text = "Malheureusement, je ne peux pas vous aider maintenant - personne parmi les gens que je connais ne servirait sous vos ordres. Mais je peux vous donner un conseil - parlez à ce marin qui vient de prendre la table juste derrière vous. Lui et ses copains viennent de quitter un navire marchand. Peut-être, ils accepteront de venir avec vous.";
			link.l1 = "D'accord, je vais faire exactement ça! Merci beaucoup!";
			link.l1.go = "exit";
			pchar.questTemp.Sharlie = "sailor";
			//усадим матроса Алонсо
			sld = GetCharacter(NPC_GenerateCharacter("SharlieSailor" , "Alonso", "man", "man", 10, FRANCE, -1, true, "quest"));
			sld.name 	= StringFromKey("HollandGambit_23");
			sld.lastname = "";
			FantomMakeCoolFighter(sld, 10, 20, 20, "blade_05", "", "", 10);
			sld.Dialog.Filename = "Quest\Sharlie\OtherNPC.c";
			sld.dialog.currentnode = "Sharlie_sailor";
			sld.greeting = "town_sailor";
			AddLandQuestMark(sld, "questmarkmain");
			LAi_SetSitType(sld);
			LAi_SetImmortal(sld, true);
			FreeSitLocator("FortFrance_tavern", "sit7");
			ChangeCharacterAddressGroup(sld, "FortFrance_tavern", "sit", "sit7");
			AddQuestRecord("Sharlie", "6-1"); // mitrokosta
		break;
		
		case "Sharlie_skiper":
			dialog.text = "Je ne peux rien te dire de spécifique, mon ami. En ce moment, aucun navigateur ne fréquente ma place. Essaye de te renseigner dans le port - peut-être, les gens en sauraient plus.";
			link.l1 = "Je vois. D'accord, je vais parler aux gens.";
			link.l1.go = "exit";
			pchar.questTemp.Sharlie = "findskiper";
			//сгенерим наводчика
			sld = GetCharacter(NPC_GenerateCharacter("SharlieSkiperTalker", "citiz_"+(rand(19)+21), "man", "man", 10, FRANCE, -1, true, "marginal"));
			FantomMakeCoolFighter(sld, 10, 20, 20, RandPhraseSimple("blade_04","blade_06"), "", "", 10);
			sld.Dialog.Filename = "Quest\Sharlie\OtherNPC.c";
			sld.dialog.currentnode = "skipertalker";
			sld.greeting = "marginal";
			LAi_SetWarriorType(sld);
			LAi_SetImmortal(sld, true);
			LAi_group_MoveCharacter(sld, "FRANCE_CITIZENS");
			ChangeCharacterAddressGroup(sld, "FortFrance_town", "patrol", "patrol"+(rand(13)+1));
			LAi_SetLoginTime(sld, 6.0, 21.99);
			AddLandQuestMark(sld, "questmarkmain");
		break;
		//<-- Бремя гасконца
		
		// Addon 2016-1 Jason пиратская линейка
		case "mtraxx_tortuga":
			sld = characterFromId("Tortuga_waitress");
            dialog.text = "Tout de suite, monsieur !.. Le meilleur vin français ! "+sld.name+"! Allez préparer la meilleure chambre d'hôte! Ce sera 1000 pesos, monsieur.";
			link.l1 = "Ici.";
			link.l1.go = "mtraxx_tortuga_1";
		break;
		
		case "mtraxx_tortuga_1":
			AddMoneyToCharacter(pchar, -1000);
            DialogExit();
			pchar.questTemp.Mtraxx.Retribution = "room";
			pchar.quest.mtraxx_retribution_room.win_condition.l1 = "locator";
			pchar.quest.mtraxx_retribution_room.win_condition.l1.location = "Tortuga_tavern";
			pchar.quest.mtraxx_retribution_room.win_condition.l1.locator_group = "reload";
			pchar.quest.mtraxx_retribution_room.win_condition.l1.locator = "reload2_back";
			pchar.quest.mtraxx_retribution_room.function = "Mtraxx_RetributionToRoom";
		break;
		// belamour постоялец -->
		case "Unwantedpostor_hall_day_wait":
			if (hrand(1) == 1)
            {
                Dialog.text = "Sors, maraud ! Tu prends de la place précieuse pour les clients qui paient !";
				link.l1 = "D'accord, très bien... Je m'en vais.";
				link.l1.go = "exit";
            }
            else
            {
				DialogExit();
				NextDiag.CurrentNode = NextDiag.TempNode;
				TavernWaitDate("wait_day");
			}
		break;
		
		case "Unwantedpostor":
				dialog.text = "Ouais - et effrayer tous mes clients avec le fait que mes gardes traînent les gens hors de la taverne? Et certains de mes clients n'aiment pas être autour des soldats. Ça les rend nerveux, tu vois? Je ne veux pas ruiner ma réputation...";
				link.l1 = "Hmm, et si je résous ton problème ?";
				link.l1.go = "Unwantedpostor_1";
		break;
		
		case "Unwantedpostor_1":
				dialog.text = "Vous avez fait votre choix ? Il est armé, c'est une sorte de mercenaire professionnel...";
				link.l1 = "Hmm, tu as raison, je n'ai pas envie de me disputer avec un mercenaire armé...";
				link.l1.go = "Exit";
				link.l2 = "Eh bien, je ne suis pas non plus une nonne cloîtrée... Et je veux toujours louer une chambre.";
				link.l2.go = "Unwantedpostor_2";
		break;
		
		case "Unwantedpostor_2":
				dialog.text = "Eh bien, si vous pouvez, hum... le convaincre de déguerpir, alors la chambre est à vous jusqu'au matin. Gratuitement, bien sûr.";
				link.l1 = "Tu sais, j'ai changé d'avis. Je n'ai pas envie de convaincre qui que ce soit.";
				link.l1.go = "Exit";
				link.l2 = "Vous voudrez regarder ça. Votre invité indésirable est sur le point de se faire éjecter de votre taverne comme un grand goéland.";
				link.l2.go = "Unwantedpostor_kikcoff";
		break;
		
		case "Unwantedpostor_kikcoff":
				DialogExit();
				chrDisableReloadToLocation = true; //закрыть локацию
				LAi_LocationFightDisable(&Locations[FindLocation(pchar.location+"_upstairs")], true); //запретить драться
				iTemp = sti(pchar.rank) + rand(5);
				sld = GetCharacter(NPC_GenerateCharacter("Berglar_Unwantedpostor", "citiz_5"+(rand(3)+1), "man", "man", iTemp, PIRATE, -1, true, "quest")); // "mercen_"+(rand(14)+14)
				FantomMakeCoolFighter(sld, iTemp, 50 + rand(30), 50 + rand(30), "topor_04", "", "bullet", 50);
				sld.dialog.filename = "GenQuests_Dialog.c";
				sld.dialog.currentnode = "Unwantedpostor_room";	
				sld.greeting = "Enc_Raiders"; 
				if (findsubstr(locations[FindLocation(pchar.location)].id, "tavern_upstairs" , 0) == -1)
				{
					DoQuestReloadToLocation(pchar.location+"_upstairs", "quest", "quest4", "");
					ChangeCharacterAddressGroup(sld, pchar.location+"_upstairs", "quest", "quest3");
				} 
				LAi_SetActorType(sld);
				LAi_ActorDialogDelay(sld, pchar, "", 1.5);
		break;
		// <-- belamour постоялец
		
		case "Helen_room_night":
			dialog.text = "Je vois. Ce sera cinq argent.";
			if (makeint(pchar.money) >= 5)
			{
				link.l1 = "Bien sûr, voici pour toi.";
				link.l1.go = "room_night_wait";
			}
			link.l2 = "En fait, tu sais quoi... Peut-être une autre fois. Je passerai le reste de la journée sur mes pieds.";
			link.l2.go = "Helen_night_exit";
		break;
		
		case "Helen_room_day":
			dialog.text = "Sage décision. Ça fera cinq argent, et bonne nuit à toi.";
			if (makeint(pchar.money) >= 5)
			{
				link.l1 = "Voici pour vous, et merci - bonne nuit.";
				link.l1.go = "room_day_wait";
			}
			link.l2 = "En y repensant, je n'ai pas envie de dormir. Je vais me promener en ville, respirer un peu d'air nocturne.";
			link.l2.go = "Helen_day_exit";
		break;
		
		case "Helen_room_day_next":
			dialog.text = "Bien sûr, Helen. Ça fera dix pesos.";
			if (makeint(pchar.money) >= 10)
			{
				link.l1 = "Bien sûr, voici pour vous.";
				link.l1.go = "room_day_wait_next";
			}
			link.l2 = "En fait... Je pourrais faire quelque chose d'utile avec une journée entière. Peut-être une autre fois.";
			link.l2.go = "Helen_Next_day_exit";
		break;
		
		case "Helen_night_exit":
			dialog.text = "Comme vous voulez, Helen.";
			link.l1 = "Mhm.";
			link.l1.go = "exit";
		break;
		
		case "Helen_day_exit":
			dialog.text = "Vous pourriez même vous trouver somnolent après une bonne marche.";
			link.l1 = "Ha-ha, peut-être.";
			link.l1.go = "exit";
		break;
		
		case "Helen_next_day_exit":
			dialog.text = "Comme vous l'entendez.";
			link.l1 = "Eh bien, jusqu'à la prochaine fois.";
			link.l1.go = "exit";
		break;
		
		case "Helen_rumours_tavern":
			dialog.text = "Bien sûr, Helen, je suis tout ouïe.";
			link.l1 = "Quelles sont les dernières nouvelles ou rumeurs intéressantes en ville?";
			link.l1.go = "rumours_tavern";
		break;
		
		// Леди Бет -->
		case "LadyBeth_Room":
			dialog.text = "Il paie le triple du prix habituel, alors... vous comprenez. Et je vous déconseille de lui dire non - il a un caractère difficile. Surtout ces derniers temps.";
			link.l1 = "Qu'est-ce qu'il lui arrive ?";
			link.l1.go = "LadyBeth_Room_2";
		break;
		
		case "LadyBeth_Room_2":
			dialog.text = "Une obsession, voilà ce que c'est. Au début, c'était un gars généreux et gentil. Ses marins dépensaient sans compter dans les tavernes, offraient des cadeaux aux filles. C'était la fête quand la 'Lady Beth' arrivait au port. Et maintenant ? Maintenant, ils n'achètent que des provisions et recrutent n'importe qui. Comme s'ils avaient besoin de bras, pas de marins. Mais vous pouvez lui parler vous-même.";
			link.l1 = "Je passerai peut-être. Merci.";
			link.l1.go = "exit";
			pchar.questTemp.LadyBeth_TavernRoomDialog = true;
		break;
		// Леди Бет <--
	}
}

string findTraderCity(ref NPChar)
{
	int n, nation;
    int storeArray[2];
	SetArraySize(&storeArray, MAX_COLONIES); 
    int howStore = 0;

	for(n=0; n<MAX_COLONIES; n++)
	{
		nation = GetNationRelation(sti(npchar.nation), sti(colonies[n].nation));
		if (colonies[n].id != "Panama" && colonies[n].nation != "none" && GetIslandByCityName(npchar.city) != colonies[n].islandLable) //не на свой остров
		{
			if (nation == RELATION_ENEMY || sti(npchar.nation) == PIRATE)
			{
				storeArray[howStore] = n;
				howStore++;
			}
		}
	}
	if (howStore == 0) return "none";
	nation = storeArray[hRand(howStore-1)];
	return colonies[nation].id;
}

string findPassangerCity(ref NPChar)
{
	int n, nation;
    int storeArray[2];
	SetArraySize(&storeArray, MAX_COLONIES);
    int howStore = 0;

	for(n=0; n<MAX_COLONIES; n++)
	{
		nation = GetNationRelation(sti(npchar.nation), sti(colonies[n].nation));
		if (colonies[n].nation != "none" && colonies[n].id != "Panama" && GetIslandByCityName(npchar.city) != colonies[n].islandLable) //не на свой остров
		{
			if (nation == RELATION_ENEMY || sti(npchar.nation) == PIRATE)
			{
			storeArray[howStore] = n;
			howStore++;
		}
	}
	}
	if (howStore == 0) return "none";
	nation = storeArray[hRand(howStore-1)];
	return colonies[nation].id;
}
