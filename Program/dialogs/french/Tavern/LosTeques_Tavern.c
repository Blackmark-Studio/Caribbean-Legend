#include "DIALOGS\%language%\Rumours\Common_rumours.c"
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	string sLoc;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	ProcessCommonDialogRumors(NPChar, Link, NextDiag);
	
	bool bLock = (CheckAttribute(pchar, "GenQuest.BrothelLock")) && (GetCharacterIndex("Mary") != -1);
	bool bLock1 = (CheckAttribute(pchar, "questTemp.Saga.Helena_officer")) && (IsOfficer(characterFromId("Helena")));

	switch(Dialog.CurrentNode)
	{
		case "First time":
			if (LAi_grp_playeralarm > 0)
			{
       			dialog.text = NPCharRepPhrase(pchar,LinkRandPhrase("Une alarme a été déclenchée dans la ville. Tout le monde te cherche ! Je ne traînerais pas ici trop longtemps si j'étais toi.","La garde entière fouille la ville pour te trouver. Je ne suis pas un idiot et je ne suis pas prêt à te parler !","Fuis, matelot, avant que les soldats ne te réduisent en bouillie..."),LinkRandPhrase("Que veux-tu, vaurien ?! La garde de la ville est déjà à tes trousses. Tu n'iras pas loin, pirate !","Sale meurtrier, sors de chez moi ! Gardes !!","Je n'ai pas peur de toi, chien! La potence t'appelle, tu n'iras pas loin..."));
				link.l1 = NPCharRepPhrase(pchar,RandPhraseSimple("Heh, je ne m'inquiète pas pour l'alarme...","Ils n'ont aucune chance de me rattraper."),RandPhraseSimple("Ferme ta bouche, "+GetWorkTypeOfMan(npchar,"")+", ou je te couperai la putain de langue.","Heh, "+GetWorkTypeOfMan(npchar," ")+", toi aussi tu veux chasser un pirate ? Ecoute, l'ami, reste calme et tu pourrais survivre..."));
				link.l1.go = "exit";
				break;
			}
			if (npchar.quest.meeting == "0")
			{
				dialog.text = TimeGreeting()+"! Bienvenue, "+GetAddress_Form(NPChar)+" à la taverne de la mine de Los-Teques. Nourriture, boissons et filles, tout à des prix abordables ! Mon nom est "+GetFullName(npchar)+" et je suis toujours à votre service.";
				Link.l1 = "Voyons voir... Je suis "+GetFullName(pchar)+"Enchanté de vous rencontrer, "+npchar.name+".";
				Link.l1.go = "meeting";
				npchar.quest.meeting = "1";
			}
			else
			{
				dialog.text = "Aha, c'est mon vieil ami, capitaine "+GetFullName(pchar)+"! Heureux de te voir, vieux loup de mer ! Rhum, filles ?";
				if (makeint(pchar.money) >= 5)
				{
					link.l1 = "Sers-moi du rhum, "+npchar.name+".";
					link.l1.go = "drink";
				}
				link.l2 = "Je voudrais fermer l'oeil un moment. Avez-vous une chambre libre ?";
				link.l2.go = "room";
				link.l3 = LinkRandPhrase("Avez-vous des nouvelles récentes ?","Quoi de neuf par ici ?","Comment va la vie sur la terre ferme ?");
				link.l3.go = "rumours_tavern";
				link.l4 = "Non, je n'ai besoin de rien, "+npchar.name+". Je suis juste passé pour te dire bonjour.";
				link.l4.go = "exit";
			}
			NextDiag.TempNode = "First time";
		break;
		
		case "meeting":
			dialog.text = "Oh, je suis tellement heureux ! Les nouvelles têtes sont rares dans notre ville. Que diriez-vous que je vous verse du rhum et que nous bavardions un peu...";
			link.l1 = "C'est ma première fois ici et j'aimerais en savoir un peu plus sur cette colonie.";
			link.l1.go = "info";
			if (makeint(pchar.money) >= 5)
			{
				link.l2 = "Verse-moi du rhum, "+npchar.name+".";
				link.l2.go = "drink";
			}
			link.l3 = "J'aimerais fermer l'oeil. Avez-vous une chambre libre ?";
			link.l3.go = "room";
		break;
		
		case "info":
			dialog.text = "Rien d'intéressant à raconter. Même affaire chaque jour : ennui, soleil et poussière. Seuls des soldats, des nègres et des Indiens vivent ici. On peut aussi trouver quelques aventuriers et bandits affamés d'or\nParfois des messieurs, des capitaines comme vous, nous rendent visite pour vendre des esclaves contre des lingots et acheter des métaux précieux. Notre marchand est un homme assez intéressant, il vend non seulement des pépites d'or et d'argent, mais aussi des pierres semi-précieuses\nIl prétend que les gens avec des connaissances spéciales peuvent trouver ces cailloux très utiles. Alors, allez voir notre magasin. La mine elle-même est située plus loin sous la montagne. Vous pouvez la visiter si vous le souhaitez, mais je vous recommande d'éviter de contrarier les gardes\nNe parlez pas aux bagnards et que Dieu vous garde de voler. Quoi qu'il en soit, le meilleur endroit dans cet établissement est ma taverne, le meilleur endroit pour se reposer de cet enfer brûlant !";
			link.l1 = "Merci pour l'information !";			
			link.l1.go = "exit";
		break;
		
		case "drink":
			if (CheckAttribute(pchar, "questTemp.Rum") && sti(pchar.questTemp.Rum) > 3)
			{
				dialog.text = "Capitaine, je pense que vous feriez mieux de vous arrêter. Que Dieu vous préserve de semer le chaos sous l'influence de l'alcool. Nous sommes vraiment stricts à ce sujet ici. Même votre autorité ne vous aidera pas.";
				link.l1 = "Hm... Je suppose que tu as raison - j'en ai déjà assez eu. Merci de t'en soucier !";			
				link.l1.go = "exit";
			}
			else
			{
				AddMoneyToCharacter(pchar, -5);
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
				
				dialog.text = "Vous êtes le bienvenu, capitaine. Juste cinq pièces de huit pour une pinte de mon meilleur rhum jamaïcain noir !";
				link.l1 = RandPhraseSimple(LinkRandPhrase("D'accord, à votre santé et à la prospérité de votre établissement, matelot !","D'accord, à ceux en mer !","D'accord, à la prospérité de votre ville !"),LinkRandPhrase("D'accord, aux vents de la production, à une rafale de chance, que nous vivions tous plus légers et riches !","Très bien, que le vent souffle toujours dans notre dos dans toutes les affaires !","Très bien, à la joie, la chance, le bonheur et aux donzelles !"));		
				link.l1.go = "drink_1";
			}
		break;
		
		case "drink_1":
			DialogExit();
			LAi_Fade("", "");
			if (CheckAttribute(pchar, "questTemp.Rum"))
			{
				DeleteAttribute(pchar, "chr_ai.drunk");
				if (sti(pchar.questTemp.Rum) < 3) LAi_AlcoholSetDrunk(pchar, 51, 5600);
				else
				{
					LAi_AlcoholSetDrunk(pchar, 71, sti(pchar.questTemp.Rum)*2800);
					Pchar.GenQuest.CamShuttle = makeint(sti(pchar.questTemp.Rum)/2); // Jason
				}
			}
		break;
		
		case "room":
			if (CheckAttribute(pchar, "GenQuest.LosTequesSex"))
			{
				dialog.text = "Señor, vous avez payé pour une chambre et une fille. Montez donc à l'étage, elle vous attend depuis un moment.";
				link.l1 = "D'accord.";
				link.l1.go = "exit";
				break;
			}
			dialog.text = "Nous avons des chambres. Combien de temps comptiez-vous rester ?";
			if(!isDay())
			{
				link.l1 = "Jusqu'au matin.";
				link.l1.go = "room_day";
			}
			else
			{
				link.l1 = "Jusqu'à la nuit.";
				link.l1.go = "room_night";
				link.l2 = "Jusqu'au lendemain matin.";
				link.l2.go = "room_day_next";
			}
		break;

		case "room_day":
			dialog.text = "Ce sera dix piastres. Voulez-vous une fille pour la chambre avec cela ? Seulement mille pesos pour la donzelle.";
			if (makeint(pchar.money) >= 10)
			{
				link.l1 = "Non, je n'ai pas besoin d'une fille. Tenez, prenez ça pour la chambre.";
				link.l1.go = "room_day_wait";
			}
			if (makeint(pchar.money) >= 1010)
			{
				if (IsOfficer(characterFromId("Mary")) || !bLock || !bLock1)
				{
					link.l2 = "Oui, je prendrai la chambre et la fille. Voici l'argent.";
					link.l2.go = "room_girl";
					sTotalTemp = "wait_day";
				}
			}
			link.l3 = "Hélas, je ne peux pas me permettre la chambre.";
			link.l3.go = "exit";
		break;

		case "room_day_next":
			dialog.text = "Ce sera dix pièces de huit. Voulez-vous une fille pour la chambre avec ça ? Seulement mille pesos pour la donzelle.";
			if (makeint(pchar.money) >= 10)
			{
				link.l1 = "Non, je n'ai pas besoin d'une fille. Tenez, prenez ça pour la chambre.";
				link.l1.go = "room_day_wait_next";
			}
			if (makeint(pchar.money) >= 1010)
			{
				if (IsOfficer(characterFromId("Mary")) || !bLock || !bLock1)
				{
					link.l2 = "D'accord. Prenons la chambre et la fille. Voici l'argent.";
					link.l2.go = "room_girl";
					sTotalTemp = "wait_day";
				}
			}
			link.l3 = "Hélas, je ne peux pas me permettre la chambre.";
			link.l3.go = "exit";
		break;

		case "room_night":
			dialog.text = "Ce sera dix pièces de huit. Voulez-vous une fille pour la chambre avec ça ? Seulement mille pesos pour la fille de joie.";
			if (makeint(pchar.money) >= 10)
			{
				link.l1 = "Non, je n'ai pas besoin d'une fille. Tenez, prenez ceci pour la chambre.";
				link.l1.go = "room_night_wait";
			}
			if (makeint(pchar.money) >= 1010)
			{
				if (IsOfficer(characterFromId("Mary")) || !bLock || !bLock1)
				{
					link.l2 = "Très bien. Prenons la chambre et la fille. Voici l'argent.";
					link.l2.go = "room_girl";
					sTotalTemp = "wait_night";
				}
			}
			link.l3 = "Hélas, je ne peux pas me permettre la chambre.";
			link.l3.go = "exit";
		break;

		case "room_night_wait":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			AddMoneyToCharacter(pchar, -10);
			AddDialogExitQuest("sleep_in_tavern");
			TavernWaitDate("wait_night");
		break;

		case "room_day_wait":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			AddMoneyToCharacter(pchar, -10);
			AddDialogExitQuest("sleep_in_tavern");
			TavernWaitDate("wait_day");
		break;

		case "room_day_wait_next":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			AddMoneyToCharacter(pchar, -20);
			AddDialogExitQuest("sleep_in_tavern");
			TavernWaitDate("wait_day");
		break;
		
		case "room_girl":
			AddMoneyToCharacter(pchar, -1010);
			dialog.text = "Montez à l'étage, señor. La fille vous attendra. Passez un bon séjour !";
			link.l1 = "Merci, l'ami...";
			link.l1.go = "room_girl_1";
		break;
		
		case "room_girl_1":
			DialogExit();
			pchar.GenQuest.CannotWait = true;
			pchar.GenQuest.LosTequesSex = "true";
			LocatorReloadEnterDisable("LosTeques_tavern", "reload1_back", true); //закрыть таверну
			LocatorReloadEnterDisable("LosTeques_tavern", "reload2_back", false); //открыть комнату
			bDisableFastReload = true;//закрыть переход
			sld = GetCharacter(NPC_GenerateCharacter("MineFuckGirl" , "squaw_"+(rand(2)+1), "woman", "woman_B", 1, SPAIN, 1, true, "quest"));
			sld.dialog.FileName = "Tavern\LosTeques_Tavern.c";
			sld.dialog.currentnode = "MineFuckGirl";
			//sld.greeting = "";
			sld.name = GetIndianName(WOMAN);
			sld.lastname = "";
			LAi_SetStayType(sld);
			ChangeCharacterAddressGroup(sld, "LosTeques_tavern_upstairs", "goto", "goto1");
		break;
		
		case "MineFuckGirl":
			dialog.text = "Comment, maître blanc. Ne regarde pas "+npchar.name+" comme ça, "+npchar.name+" sait faire tout mieux qu'une squaw blanche de bordel. Ah, señor, vous êtes si beau... Promettez, cette squaw vous aimera longtemps.";
			link.l1 = "Ça me va, montre-moi tes meilleurs charmes indiens. Je n'aurai pas besoin d'une danse de pluie pour te mouiller...";
			link.l1.go = "MineFuckGirl_sex";
		break;
		
		case "MineFuckGirl_sex":
			DialogExit();
			DoQuestCheckDelay("PlaySex_1", 0.1);
		break;

 		case "Exit":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
		break;

		// ============== Грабеж среди бела дня, попытка залезть в сундуки =========================
		case "Man_FackYou":
			dialog.text = LinkRandPhrase("Vol en plein jour !!! Que se passe-t-il ici ?! Attends, attends, l'ami...","Hé, que fais-tu là ?! Tu essaies de me voler ? Maintenant tu es foutu...","Attends, que diable fais-tu ? Il s'avère que tu es un voleur ! Considère cela comme la fin de la route, connard...");
			link.l1 = LinkRandPhrase("Diable !","Merde !","Ah, merde");
			link.l1.go = "PL_Q3_fight";
		break;
		
		case "fight":
            Pchar.quest.ArestInResidenceEnd.win_condition.l1          = "ExitFromLocation";
		    Pchar.quest.ArestInResidenceEnd.win_condition.l1.location = Pchar.location;
		    Pchar.quest.ArestInResidenceEnd.win_condition             = "ArestInResidenceEnd";
		    Pchar.quest.ArestInResidenceEnd.ResidenceLocation = Pchar.location;
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;

			LAi_LockFightMode(Pchar, true); // ножками путь убегает
		    LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
		    LAi_group_Attack(NPChar, Pchar); // не работает на бессмертного мера :(
			i = GetCharIDXByParam("CityType", "location", Pchar.location); // фантом солдат
			if (i != -1)
			{
			    LAi_group_Attack(&Characters[i], Pchar);
			}
		break;
	}
}
