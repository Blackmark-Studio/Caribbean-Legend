// boal 25/04/04 общий диалог Governor
void ProcessDialogEvent()
{
	ref NPChar;
	aref Link, NextDiag;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

    // вызов диалога по городам -->
    NPChar.FileDialog2 = "DIALOGS\" + LanguageGetLanguage() + "\Governor\" + NationShortName(int(NPChar.nation)) + "_Governor.c";
    if (LoadSegment(NPChar.FileDialog2))
	{
        ProcessCommonDialog(NPChar, Link, NextDiag);
		UnloadSegment(NPChar.FileDialog2);
	}
    // вызов диалога по городам <--
    
    ref offref, sld;
    int i, cn;
    int qty;
    int iSumm;
    string attrLoc;

    /// выкуп колонии
    ref CaptGovenor, FortColony;
    int f, colony_money;

    int k = 1000;
    if (CheckAttribute(Nations[int(NPChar.nation)], "Fort"))
    {
        k = (300 - int(Nations[int(NPChar.nation)].Fort)*10);
    }
	bool ok;
	
	attrLoc = Dialog.CurrentNode;
	if (findsubstr(attrLoc, "CityGive_" , 0) != -1)
 	{
        i = findsubstr(attrLoc, "_" , 0);
	 	NPChar.quest.CityIdx = strcut(attrLoc, i+1, strlen(attrLoc)-1); // индех в конце
 	    Dialog.CurrentNode = "ColonyGive";
 	}
 	
	switch (Dialog.CurrentNode)
	{
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			AddDialogExitQuest("MainHeroFightModeOff");
		break;
		
		case "fight":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			LAi_group_Attack(NPChar, Pchar);
		break;
		
		case "First time":
            NextDiag.TempNode = "First time";
			if (LAi_grp_playeralarm > 0)
			{
       			dialog.text = NPCharRepPhrase(pchar,LinkRandPhrase("Tu oses montrer ton visage au bureau du gouverneur général ?! Tu es vraiment fou...","Comment ces fainéants ont-ils laissé un ennemi s'introduire dans ma résidence? Cela dépasse mon entendement...","Certainement, mes gardes ne valent pas un sou si un vagabond se promène dans ma résidence..."),LinkRandPhrase("De quoi as-tu besoin, "+GetSexPhrase("rampant","puant")+"?! Mes soldats ont déjà été mis sur votre piste, "+GetSexPhrase("pirate sale","puant")+"!",""+GetSexPhrase("Crade","Sale")+" assassin, quitte ma résidence immédiatement ! Gardes !","Je n'ai pas peur de toi, "+GetSexPhrase("coquin","galapiat")+"! Bientôt tu seras pendu dans notre fort, tu n'iras pas loin..."));
				link.l1 = NPCharRepPhrase(pchar,RandPhraseSimple("Les soldats ne valent pas un crottin...","Vous ne m'aurez jamais."),RandPhraseSimple("Tais-toi, camarade, ou j'arracherai cette langue nauséabonde de la tienne !","Je te le dis, camarade : reste tranquille ou je te couperai la tête et la jetterai par cette porte à tes chiens de garde..."));
				link.l1.go = "fight";
				break;
			}
			if (npchar.quest.meeting == "0")
			{
				dialog.text = "J'ai entendu dire que vous insistiez beaucoup pour demander une audience. Mon nom est "+GetFullName(npchar)+". Je suis le gouverneur général des colonies de "+NationNameGenitive(int(NPChar.nation))+", député de la Couronne de "+NationKingsName(npchar)+"dans ces eaux. Maintenant, soyez gentil de me dire, quel est le but de votre visite, "+GetAddress_Form(NPChar)+".";
				link.l1 = "Mon nom est "+GetFullName(pchar)+".";
				link.l1.go = "node_1";
				npchar.quest.meeting = "1";
			}
			else
			{
				dialog.text = RandPhraseSimple("Oh, c'est toi encore? Eh bien, que veux-tu du gouverneur-general de "+NationNameGenitive(int(NPChar.nation))+" cette fois-ci?","Et une fois de plus, vous me détournez des affaires d'Etat importantes? Que voulez-vous, "+GetAddress_Form(NPChar)+"?");
				link.l1 = "Je veux parler avec toi de travailler au nom de la Couronne de "+NationNameGenitive(int(NPChar.nation));
				link.l1.go = "work";
				link.l2 = "J'ai besoin de parler avec vous d'une affaire importante.";
				link.l2.go = "quests"; // файл нации
				//Jason --> Регата
				if (CheckAttribute(pchar, "questTemp.Regata.ToPortRoyal") && NPChar.location == "Portroyal_townhall")
				{
					link.l3 = "Je suis venu sur une invitation à participer à la régate. Voici mon invitation.";
					link.l3.go = "Regata";
				}
				//<-- Регата
				link.l10 = "Je suis désolé, mais j'ai des affaires à faire.";
				link.l10.go = "exit";
			}
		break;
		
		case "node_1":
			dialog.text = "Alors, quelle était la raison pour laquelle vous êtes venu ici et m'avez distrait des affaires importantes de l'état ?";
			link.l1 = "Je voulais vous parler de travailler au nom de la Couronne de "+NationNameGenitive(int(NPChar.nation));
			link.l1.go = "work";
			link.l2 = "J'allais vous parler d'une affaire importante.";
			link.l2.go = "quests";
			//Jason --> Регата
			if (CheckAttribute(pchar, "questTemp.Regata.ToPortRoyal") && NPChar.location == "Portroyal_townhall")
			{
				link.l3 = "Je suis venu ici pour participer à la régate. Voici mon invitation.";
				link.l3.go = "Regata";
			}
			//<-- Регата
			link.l10 = "C'est juste une visite de courtoisie, rien de plus, "+GetAddress_FormToNPC(NPChar);
			link.l10.go = "node_2";
		break;

		case "node_2":
			dialog.text = "Dans ce cas, je vous demanderais de quitter mon bureau et d'arrêter de me distraire de mon travail.";
			link.l1 = "Oui, oui, bien sûr. Désolé de vous déranger.";
			link.l1.go = "exit";
		break;
		
		case "work":
            dialog.text = "Si vous cherchez du travail, parlez avec les gouverneurs des colonies. Ils ont souvent besoin de capitaines intelligents et courageux.";
			link.l1 = "Je vais garder cela à l'esprit. Merci.";
			link.l1.go = "exit";
		break;
		
		//--> Jason регата
		case "Regata":
			dialog.text = "Oh, super, content de vous voir, capitaine! Vous êtes arrivé juste à temps - la régate commence dans quelques jours. Avez-vous lu les règles de la régate dans la lettre qui vous a sûrement été remise par messager?";
			link.l1 = "Oui, monsieur, j'ai fait.";
			link.l1.go = "Regata_1";
			RemoveItems(PChar, "letter_open", 1);//уберем письмо
			TakeNationLicence(HOLLAND);//уберем лицензию
			DeleteAttribute(pchar, "questTemp.Regata.ToPortRoyal"); // patch-5
		break;
		
		case "Regata_1":
			dialog.text = "Et avez-vous préparé 50000 pesos - votre droit d'entrée, qui contribuera au prix?";
			if (int(Pchar.money) >= 50000)
			{
				link.l1 = "Oui, bien sûr. Veuillez accepter mes honoraires.";
				link.l1.go = "Regata_2";
			}
			link.l2 = "Je suis un peu à court d'argent pour le moment. Mais je vais certainement le rapporter aussi vite que je peux.";
			link.l2.go = "Regata_nomoney";
		break;
		
		case "Regata_2":
			dialog.text = "Très bien. Si vous gagnez - votre argent vous reviendra quintuplé. Maintenant, vous devriez savoir comment ne pas enfreindre les règles de la régate.\nDiscutez des détails avec Henry Stevenson, il doit être dans la salle de résidence. Rencontrez-le, il vous expliquera tout.";
			link.l1 = "D'accord. Je ferai comme tu dis.";
			link.l1.go = "exit";
			AddMoneyToCharacter(pchar, -50000);
			pchar.quest.Regata_Guber.win_condition.l1 = "location";
			pchar.quest.Regata_Guber.win_condition.l1.location = "Portroyal_Roomtownhall";
			pchar.quest.Regata_Guber.function = "PrepareToRegataInPortroyal";
			pchar.questTemp.Regata.Begin = "true";
			NextDiag.TempNode = "First time";
		break;
		
		case "Regata_nomoney":
			dialog.text = "D'accord, mais ne prenez pas trop de temps, capitaine. La régate va bientôt commencer.";
			link.l1 = "Je vois. J'essaierai de vous apporter de l'argent avant le début de la régate.";
			link.l1.go = "exit";
			NextDiag.TempNode = "Regata_1";
			pchar.questTemp.Regata.nomoney = "true";
		break;
		
		//регата-финал
		case "Regata_Final":
			dialog.text = "Et voici le vainqueur de la régate! Bonjour, capitaine "+GetFullName(pchar)+"! Permettez-moi de vous féliciter pour ce succès bien mérité ! Les gagnants de la régate sont toujours populaires dans les colonies anglaises, justement populaires.";
			link.l1 = "Merci, monsieur !";
			link.l1.go = "Regata_complete";
		break;
		
		case "Regata_complete":
			dialog.text = "Maintenant, passons à la partie la plus agréable pour vous - la cérémonie de récompense. Le premier prix en argent est de 250000 pesos. Voilà pour vous!";
			link.l1 = "Merci!";
			link.l1.go = "Regata_complete_1";
		break;
		
		case "Regata_complete_1":
			AddMoneyToCharacter(pchar, 250000);
			int iGift;
			string sItem1, sItem2, sItem3, sAdd;
			
			iGift = 3;
			switch (iGift)
			{
				case 0:
					sItem1 = "blade_10";//корд
					sItem2 = "cirass6";
					sItem3 = "bussol";
					sAdd = "cord, duelist's vest and boussole";
				break;
				
				case 1:
					sItem1 = "blade_15";//маринера
					sItem2 = "cirass2";//рейтарский панцирь
					sItem3 = "bussol";
					sAdd = "marinera, reiter's armour and boussole";
				break;
				
				case 2:
					sItem1 = "blade_17";//бретта
					sItem2 = "cirass7";//карацена
					sItem3 = "bussol";
					sAdd = "bretta, karacena and boussole";
				break;
				
				case 3://
					sItem1 = "blade_20";//мадонна
					sItem2 = "cirass2";//офицерская кираса
					sItem3 = "bussol";
					sAdd = "'Madonna', officer's cuirass and boussole";
				break;
			}
			GiveItem2Character(pchar, sItem1);
			GiveItem2Character(pchar, sItem2);
			GiveItem2Character(pchar, sItem3);
			dialog.text = "De plus, vous êtes éligible pour un ensemble de prix précieux : "+sAdd+". Maintenant, tout est à toi.";
			link.l1 = "Je suis très heureux, monsieur! Vraiment, je ne pouvais pas l'attendre.";
			link.l1.go = "Regata_complete_2";
		break;
		
		case "Regata_complete_2":
			dialog.text = "Au nom de toutes les colonies anglaises, je suis heureux de vous remercier pour votre participation à la régate et je vous félicite à nouveau pour votre victoire ! Si vous avez fait un pari, c'est maintenant le moment parfait pour voir Sir Henry Stevenson et récupérer vos gains, si vous ne l'avez pas déjà fait. Bonne chance à vous, capitaine !";
			link.l1 = "Merci pour vos aimables paroles, monsieur! En retour, permettez-moi de vous remercier de m'avoir donné l'opportunité de participer à un événement aussi grandiose. Et maintenant, veuillez me permettre de dire adieu et de partir.";
			link.l1.go = "Regata_complete_3";
		break;
		
		case "Regata_complete_3":
			DialogExit();
			NextDiag.CurrentNode = "First time";
		break;
		//<-- регата
	}
}
