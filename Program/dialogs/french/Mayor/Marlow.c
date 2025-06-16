// Захария Марлоу, Чёрный Пастор, Пуэрто-Принсипе, Куба
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	string sLoc;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

// ------------------------------------------блок angry-----------------------------------------------
    if (CheckAttribute(npchar, "angry") && !CheckAttribute(npchar, "angry.ok"))
    {
        npchar.angry.ok = 1;
        if (!CheckAttribute(npchar, "angry.first")) //ловушка первого срабатывания
        {
            NextDiag.TempNode = NextDiag.CurrentNode;
            Dialog.CurrentNode = "AngryExitAgain";
            npchar.angry.first = 1;
        }
        else
        {
            switch (npchar.angry.kind) //сюда расписываем реакцию ангри. В npchar.angry.name пробелы удалены!!!
            {
                case "repeat":
                    if (npchar.angry.name == "Firsttime") Dialog.CurrentNode = "AngryRepeat_1";
                    if (npchar.angry.name == "I_know_you_good") Dialog.CurrentNode = "AngryRepeat_2";
                break;
            }
        }
    } //<-- блок angry

	switch(Dialog.CurrentNode)
	{
		case "First time":
            dialog.text = NPCStringReactionRepeat("As-tu une affaire avec moi ? Si ce n'est pas le cas, alors dégage d'ici !","Je pense que je me suis bien fait comprendre.","Bien que je me sois expliqué, tu continues à m'agacer !","D'accord, je commence à en avoir marre de cette impolitesse.","répéter",3,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("Je pars déjà.","Bien sûr, Pasteur.","Je suis désolé, Pasteur.","Oups...",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
			NextDiag.TempNode = "First time";
			
			if (sti(pchar.GenQuest.Piratekill) > 20)
			{
				dialog.text = RandPhraseSimple("Es-tu fou ? Tu voulais jouer au boucher ? Tous les pirates sont en colère contre toi, garçon, tu ferais mieux de quitter cet endroit.","Il semble que tu sois devenu fou, garçon. Voulais-tu dégourdir un peu tes mains ? Sans vouloir t'offenser, mais tu n'as rien à faire ici. Déguerpis !");
				link.l1 = RandPhraseSimple("Écoute, je veux arranger la situation...","Aidez-moi à résoudre ce problème...");
				link.l1.go = "pirate_town";
				break;
			}
			
			//--> Сага
			if(CheckAttribute(pchar, "questTemp.Saga.SharkHunt") && !CheckAttribute(npchar, "quest.sharkbegin"))
			{
				link.l1 = "J'essaie de trouver Shark Dodson. On dit que vous êtes le dernier homme qui l'a vu. Pouvez-vous m'aider avec ça ?";
				link.l1.go = "Shark";
			}
			if (CheckAttribute(pchar, "questTemp.Saga.BarbTemptation") && pchar.questTemp.Saga.BarbTemptation == "terrax" && CheckCharacterItem(pchar, "witches_hammer"))
			{
				link.l1 = "Pourquoi es-tu si grossier ? Ou bien cela ne t'intéresse pas d'obtenir le livre que tu désires de ma part ?";
				link.l1.go = "book";
			}
			//<-- Сага
			//поручение капитана - выкуп
			if (CheckAttribute(pchar, "GenQuest.CaptainComission") && NPChar.city == pchar.GenQuest.CaptainComission.PiratesCity)
			{
				if(CheckAttribute(pchar,"GenQuest.CaptainComission.toMayor"))
				{
					link.l1 = "Je veux parler de ton prisonnier.";
					link.l1.go = "CapComission1";
					DeleteAttribute(pchar,"GenQuest.CaptainComission.toMayor");
				}	
				if (pchar.GenQuest.CaptainComission.PirateShips == "died" || pchar.GenQuest.CaptainComission.PirateShips == "goaway") // лесник. новая проверка. искл. возможность сразу сдать задание,минуя 15 дней.
				{
					link.l1 = "Bonjour, Pasteur. Je veux parler de votre mission.";
					link.l1.go = "CapComission3";
				}
				if(CheckAttribute(pchar,"GenQuest.CaptainComission.RepeatSpeak") && !CheckAttribute(pchar,"GenQuest.CaptainComission.vikupzaplatil")) 
				{ // лесник . второй диалог с проверкой ,если ГГ ещё не принес деньги за выкуп.
					link.l1 = "Je veux parler de votre prisonnier.";
					link.l1.go = "CapComission6";
				}
			}
		break;
		
		case "shark":
			dialog.text = "Steven Dodson ? Je ne sais pas en quoi mon histoire pourrait t'aider, car Shark a disparu ces derniers mois et personne ne l'a vu. Ce n'est pas surprenant, cependant, il a tué Blaze Sharp et a discrédité son propre nom par cette action insensée. Il s'est fait quelques puissants corsaires comme ennemis.";
			link.l1 = "J'ai toutes les raisons de penser que Shark est innocent de la mort de Sharp. Je ne peux pas le prouver, peut-être que Shark peut le faire lui-même. Vas-tu me dire quelque chose à son sujet ?";
			link.l1.go = "shark_1";
		break;
		
		case "shark_1":
			dialog.text = "Il y a quelques mois, Steven est venu me voir et m'a proposé un marché très étrange : il a laissé sa frégate 'Fortune' en gage pour un mois en échange d'un brigantin chargé à ras bord de provisions. Ensuite, il doit soit me retourner le brigantin avec l'argent des provisions, soit je garde sa frégate. Un mois s'est écoulé - pas de signe ni de Shark, ni de mon brigantin, ni d'argent. \nEn plus, j'ai entendu des rumeurs disant que Blaze a été assassiné et que Shark était le suspect. Que pouvais-je penser ? Correct ! J'ai pensé que Steven avait échappé au pire. J'ai vendu sa frégate à un Anglais nommé William Patterson, il était très content et a payé une belle pile de doublons pour le navire. \nAinsi, j'ai complètement compensé mes dépenses et je ne lui en veux pas. Je me moque de la mort de Sharp, j'ai mes propres problèmes à régler.";
			link.l1 = "Ne penses-tu pas que s'il voulait s'échapper, il n'aurait pas besoin de ta brigantine ? Il avait son propre navire, cent fois meilleur que n'importe quelle brigantine. On dirait que Shark avait un plan, mais quelque chose a mal tourné et il n'est pas revenu à temps.";
			link.l1.go = "shark_2";
		break;
		
		case "shark_2":
			dialog.text = "Comme je te l'ai déjà dit, je me fiche des problèmes de Dodson. J'ai rempli ma part du marché. Concernant le navire, tu ferais mieux de lui demander pourquoi il avait besoin de ce foutu brigantin. Je ne l'ai pas forcé à le prendre.";
			link.l1 = "D'accord, n'en parlons plus. Tu as raison, bien sûr. Dis-moi, sais-tu où Steven se dirigeait sur ton brigantin ?";
			link.l1.go = "shark_3";
		break;
		
		case "shark_3":
			dialog.text = "Qui sait vraiment. Mais j'ai quelques suppositions. Il a navigué vers le nord-ouest en direction du continent. Donc c'est soit la Baie du Péril, connue pour ses Indiens hostiles, soit la Nouvelle-Espagne, connue pour ses papistes et l'Inquisition.\nJe doute qu'il se rende dans l'un de ces endroits. Mais on dit qu'il y a un lieu étrange appelé 'Cité des Navires Abandonnés' situé au nord-ouest de Cuba. Beaucoup de gens considèrent cela comme un mythe, mais pas moi. Pas parce que je suis une personne si romantique, mais parce qu'il y a de vraies personnes qui y naviguent sur leurs chaloupes. Du moins, ils le faisaient autrefois.";
			link.l1 = "Et qui sont-ils ?";
			link.l1.go = "shark_4";
		break;
		
		case "shark_4":
			dialog.text = "Flibustiers de Cuba. Ils chargeaient leurs barques de carcasses de taureau et mettaient le cap au nord-ouest. Ils revenaient toujours un peu plus tard avec les poches remplies d'argent ou de biens rares et précieux.";
			link.l1 = "Intriguant ! Où puis-je trouver ces flibustiers ?";
			link.l1.go = "shark_5";
		break;
		
		case "shark_5":
			dialog.text = "Pourquoi me demandes-tu ? Cherche dans les bois de Cuba. Même si tu les trouves, ils ne te diront rien, pourquoi devraient-ils révéler la source de leur bonne vie ? Alors ne perds pas ton temps, personne ne les a vus le refaire depuis longtemps.\nDe plus, j'ai entendu parler de quelques notes écrites par le marin espagnol Alvarado qui a lui-même visité l'île. Alors je suis curieux, peut-être que Steven y a navigué après tout.";
			link.l1 = "L'île inconnue qui n'est pas sur les cartes... Eh bien. Ce n'est pas une information prometteuse.";
			link.l1.go = "shark_6";
		break;
		
		case "shark_6":
			dialog.text = "Je t'ai dit dès le début que mon histoire ne t'aiderait pas. Et pourquoi as-tu besoin de Dodson?";
			link.l1 = "Moi et le Diable de la Forêt voulons l'élire comme chef des Frères de la Côte. Comme je te l'ai déjà dit, il y a de sérieuses raisons de penser que Blaze a été assassiné par quelqu'un d'autre.";
			link.l1.go = "shark_7";
		break;
		
		case "shark_7":
			dialog.text = "Heh ! J'imagine que Jan se porte garant pour lui ? Eh bien, tu connais la loi - Dodson devra obtenir un vote de chaque baron.";
			link.l1 = "Je connais la loi. Ma deuxième question alors. Voterez-vous pour Dodson à l'élection ?";
			link.l1.go = "shark_8";
		break;
		
		case "shark_8":
			dialog.text = "Eh bien, il devrait revenir d'abord. En fait, je me fiche de qui dirigera les Frères tant qu'il fait bien son travail et ne me dérange pas. Comme je l'ai dit, j'ai mes propres problèmes. Sais-tu combien de sorcières et de mages se trouvent sur notre île ? Non ? Je vais te le dire : une légion ! En plus, il y a aussi beaucoup de papistes à Santiago et à La Havane.\nEn parlant de mages. Il y a un livre appelé 'Marteau des Sorcières'. Je veux vraiment l'obtenir, mais seulement en anglais, je n'ai pas besoin de traductions en latin, allemand ou espagnol, je ne connais pas ces langues. Apporte-moi le livre et je voterai pour Dodson.\nSache que Jackman m'a aussi promis de le trouver, donc s'il réussit en premier... ne m'en veux pas alors.";
			link.l1 = "D'accord, je vais y réfléchir. Merci pour votre temps. À bientôt.";
			link.l1.go = "shark_9";
		break;
		
		case "shark_9":
			DialogExit();
			pchar.questTemp.Saga.SharkHunt = "after_marlow";
			npchar.quest.sharkbegin = "true";
			AddQuestRecord("SharkHunt", "2");
		break;
		
		case "book":
			dialog.text = "Le livre ? Je suppose que tu parles du 'Marteau des Sorcières' ?";
			link.l1 = "Bien sûr. J'ai pu le trouver pour vous. Il est en anglais comme vous l'avez demandé.";
			link.l1.go = "book_1";
		break;
		
		case "book_1":
			dialog.text = "Ha, désolé pour cet accueil brutal, camarade. Ça ne se reproduira plus... Laisse-moi voir cette merveille !";
			link.l1 = "Bien sûr, jette un oeil.";
			link.l1.go = "book_2";
		break;
		
		case "book_2":
			RemoveItems(pchar, "witches_hammer", 1); // удалить трактат
			dialog.text = "Enfin! Tremblez maintenant, serviteurs de l'Enfer! Je ne vous laisserai pas tranquilles tant que ma main pourra encore frapper...";
			link.l1 = "Je suis content pour vous, Pasteur. Alors, qu'en est-il de votre vote ?";
			link.l1.go = "book_3";
		break;
		
		case "book_3":
			dialog.text = "Comme je te l'ai dit 'Je m'en fiche de qui deviendra le chef'. Je suis sûr que Svenson ne choisira pas un homme indigne. Alors prends mon vote. Fais-en ce que tu veux. Voici mon éclat.";
			link.l1 = "Merci, Zechariah. À bientôt là-bas !";
			link.l1.go = "book_4";
		break;
		
		case "book_4":
			GiveItem2Character(pchar, "splinter_zm"); // дать осколок
			DialogExit();
			NextDiag.CurrentNode = "I_know_you_good";
			AddQuestRecord("BarbTemptation", "27");
			if (CheckCharacterItem(pchar, "splinter_mt") && CheckCharacterItem(pchar, "splinter_jb") && CheckCharacterItem(pchar, "splinter_zm")) Saga_GiveCalendar();
			ChangeCharacterComplexReputation(pchar, "fame", 1);
		break;

 		case "Exit":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
		break;

        case "I_know_you_good":
            dialog.text = NPCStringReactionRepeat(GetFullName(pchar)+", je suis content de te voir ! Que veux-tu ?","Que veux-tu d'autre ?","Encore ? Ne dérange pas les gens si tu n'as rien à faire !","Tu es un "+GetSexPhrase("bon corsaire","bonne fille")+", donc tu peux vivre pour l'instant. Mais je ne veux plus te parler.","répéter",10,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("Je ne fais que rendre visite.","Rien...","D'accord, Pasteur, je suis désolé...","Merde, ma faute !",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
			NextDiag.TempNode = "I_know_you_good";
			
			if (sti(pchar.GenQuest.Piratekill) > 20)
			{
				dialog.text = RandPhraseSimple("Es-tu fou? Tu voulais jouer au boucher? Tous les pirates sont en colère contre toi, garçon, alors tu ferais mieux de quitter cet endroit...","On dirait que tu es devenu fou, garçon. Tu voulais te dégourdir un peu ? Sans vouloir t'offenser, mais tu n'as rien à faire ici. Dégage !");
				link.l1 = RandPhraseSimple("Ecoute, je veux arranger la situation...","Aide-moi à résoudre ce problème...");
				link.l1.go = "pirate_town";
				break;
			}
			//поручение капитана - выкуп
			if (CheckAttribute(pchar, "GenQuest.CaptainComission") && CheckAttribute(pchar,"GenQuest.CaptainComission.toMayor"))
			{
				link.l1 = "C'est à propos de votre prisonnier.";
				link.l1.go = "CapComission1";
				DeleteAttribute(pchar,"GenQuest.CaptainComission.toMayor");
			}		
			if (CheckAttribute(pchar, "GenQuest.CaptainComission") && CheckAttribute(pchar,"GenQuest.CaptainComission.toMayor"))
			{
				link.l1 = "C'est à propos de votre prisonnier.";
				link.l1.go = "CapComission1";
				DeleteAttribute(pchar,"GenQuest.CaptainComission.toMayor");
			}	
			if (pchar.GenQuest.CaptainComission.PirateShips == "died" || pchar.GenQuest.CaptainComission.PirateShips == "goaway")//  правка лесник,новая проверка ,исключающая тут же сдачу задания
			{
				link.l1 = "Bonjour, Pasteur, je suis ici à propos de votre mission.";
				link.l1.go = "CapComission3";
			}
			if (CheckAttribute(pchar, "GenQuest.Marginpassenger") && pchar.GenQuest.Marginpassenger == "cabin" && CheckAttribute(pchar, "questTemp.LongHappy"))
			{ // лесник . похититель  ( после ДЛС ДиС ,когда барбазона уже нет)
				link.l1 = "J'ai entendu dire que vous êtes impliqué dans des affaires concernant des prisonniers...";
				link.l1.go = "Marginpassenger";
			}
		break;
		
	//-----------------------------------Поручение капитана - Выкуп-------------------------------------------------
		case "CapComission1":
			dialog.text = "Ha-ha. Penses-tu que je n'ai qu'un seul prisonnier ici ? Nomme-le.";
			link.l1 = pchar.GenQuest.CaptainComission.SlaveName+"Est-il ici ?";
			link.l1.go = "CapComission2";
			DeleteAttribute(pchar,"GenQuest.CaptainComission.toMayor");
		break;

		case "CapComission2":
			if(CheckAttribute(pchar,"GenQuest.CaptainComission.DaysLeft"))
			{
				dialog.text = "Il l'était. Je l'ai vendu à ce propriétaire de plantation de la Barbade - le colonel Bishop, quand il était ici il y a une semaine.";
				link.l1 = "Merde...";
				link.l1.go = "CapComission2_1";
			}
			else
			{
				dialog.text = "Ah, enfin. Je pensais le vendre à ce propriétaire de plantation de la Barbade, il sera là dans une semaine ou deux... As-tu une rançon ?";
				link.l1 = "Écoute, il y a un petit problème... En fait, je n'ai pas tant d'argent. Mais je suis prêt à travailler.";
				link.l1.go = "CapComission2_2";
				if(makeint(pchar.money) > 150000)
				{
					link.l2 = "C'est bien que tu ne l'aies pas vendu. Voici tes pièces - 150.000 pesos. Où puis-je le récupérer ?"link.l2.go ="CapComission2_3";
				}	
			}
		break;
		
		case "CapComission2_1":
			dialog.text = "Tu étais trop lent... Et pourquoi t'en soucies-tu ? Je n'ai négocié qu'avec ses proches.";
			link.l1 = "Ils m'ont demandé de venir ici.";
			link.l1.go = "CapComission2_11";
		break;
		
		case "CapComission2_11":
			dialog.text = "Eh bien, tu es en retard. Je ne peux rien faire.";
			link.l1 = "Ecoute, pour combien l'as-tu vendu si ce n'est pas un secret ?"; 
			link.l1.go = "CapComission2_12";
		break;
		
		case "CapComission2_12":
			dialog.text = "Eh, ce n'est pas. Mais je ne te le dirai pas... tu riras si je le fais. Ha-ha-ha-ha ! Adieu.";
			link.l1 = "À plus tard.";
			link.l1.go = "exit";
			AddQuestRecord("CaptainComission1", "10");
			AddQuestUserData("CaptainComission1", "sName", "Zachary Marlow");//правка лесник.  в СЖ запись ниже не работает																																				  
			//AddQuestUserData("CaptainComission1", "sName", ChangeNameCase(NAMETYPE_MAIN, pchar.GenQuest.CaptainComission.PirateName, NAME_NOM));																															 
			CaptainComission_GenerateManager();
		break;
		
		case "CapComission2_2":
			if(rand(3) == 1)
			{
				dialog.text = "Eh bien, "+pchar.name+", tu sais, ça ne fonctionne pas comme ça. Reviens avec de l'argent et tu auras ton faible, ha-ha.";
				link.l1 = "Très bien. À plus tard.";
				link.l1.go = "CapComission2_4";
			}
			else
			{
				dialog.text = "Eh bien, eh bien... J'ai une affaire... Je ne sais même pas par où commencer. Je dois couler un pirate qui a dépassé les bornes.";
				link.l1 = "Ne peut-il pas simplement être tué dans la jungle ?";
				link.l1.go = "CapComission2_2_1";
			}
		break;

		case "CapComission2_2_1":
			dialog.text = "Ce n'est pas comme ça que les affaires fonctionnent, tu sais... Je n'ai pas besoin de sa mort, j'ai besoin d'apprendre à certains à éviter de prendre ma part du butin. Mais je ne regretterai pas sa mort.";
			link.l1 = "Pourquoi n'envoies-tu pas tes propres hommes le chercher ?";
			link.l1.go = "CapComission2_2_2";
		break;
		
		case "CapComission2_2_2":
			CaptainComission_GetRandomShore();
			pchar.GenQuest.CaptainComission.ShipName1 = GenerateRandomNameToShip(sti(NPChar.nation));
			pchar.GenQuest.CaptainComission.ShipName2 = GenerateRandomNameToShip(sti(NPChar.nation));
			pchar.GenQuest.CaptainComission.UnknownPirateName = "l" + rand(GetNamesCount(NAMETYPE_ORIG) - 1);
			sLoc = XI_ConvertString(pchar.GenQuest.CaptainComission.Island + "Dat"); // belamour gen
			dialog.text = "Hm... Eh bien, "+GetName(NAMETYPE_ORIG,pchar.GenQuest.CaptainComission.UnknownPirateName,NAME_NOM)+"a convaincu certains pirates que leur part du butin est gardée dans notre cachette non loin de "+XI_ConvertString(pchar.GenQuest.CaptainComission.Island.Shore+"Gén")+". Leurs deux navires '"+pchar.GenQuest.CaptainComission.ShipName1+"' et '"+pchar.GenQuest.CaptainComission.ShipName2+"' levé l'ancre il n'y a pas longtemps et a navigué vers "+sLoc+"Maintenant tu vois pourquoi je ne peux pas faire confiance à mes hommes pour ce boulot?";
			link.l1 = "Je le fais. Combien de temps ai-je ?";
			link.l1.go = "CapComission2_2_3";
		break;
		
		case "CapComission2_2_3":
			dialog.text = "12 à 15 jours, pas plus, c'est important pour moi s'ils n'atteignent pas la cachette, sinon ce serait absurde de les couler avec une cargaison précieuse. Dans ce cas, il vaudrait mieux qu'ils l'apportent ici...";
			link.l1 = "Très bien, j'en suis. Je vais essayer de les attraper.";
			link.l1.go = "CapComission2_2_4";
		break;
		
		case "CapComission2_2_4":
			AddQuestRecord("CaptainComission1", "24");
			AddQuestUserData("CaptainComission1", "sName", "Zachary Marlow");//правка																			   
			//AddQuestUserData("CaptainComission1", "sName", ChangeNameCase(NAMETYPE_MAIN, pchar.GenQuest.CaptainComission.PirateName, NAME_NOM));
			AddQuestUserData("CaptainComission1", "sShipName1", pchar.GenQuest.CaptainComission.ShipName1);
			AddQuestUserData("CaptainComission1", "sShipName2", pchar.GenQuest.CaptainComission.ShipName2);
			AddQuestUserData("CaptainComission1", "sShoreName", XI_ConvertString(pchar.GenQuest.CaptainComission.Island.Shore + "Dat")); // belamour gen
			AddQuestUserData("CaptainComission1", "sShoreType", XI_ConvertString(GetIslandByArealName(pchar.GenQuest.CaptainComission.Island) + "Voc")); // belamour gen
			pchar.quest.CapComission_PirateAttack.win_condition.l1 = "location";
            pchar.quest.CapComission_PirateAttack.win_condition.l1.location = pchar.GenQuest.CaptainComission.Island;
            pchar.quest.CapComission_PirateAttack.function = "CaptainComission_GeneratePirateShips"; 
			SetFunctionTimerCondition("CaptainComission_PirateShipsOver", 0, 0, 15, false);
			//pchar.GenQuest.CaptainComission.PirateShips = "sdatkwest";	// лесник - заменил проверку для сдачи сразу.
			DialogExit();
		break;
		
		case "CapComission2_3":
			dialog.text = "Ne t'inquiète pas. Mes hommes le livreront à ton navire. Et pourquoi t'en soucies-tu?";
			link.l1 = "Je ne le fais pas. Ses proches m'ont demandé de le livrer.";
			link.l1.go = "CapComission2_31";
		break;
		
		case "CapComission2_31":
			dialog.text = "Ah, c'est bien. J'avais presque des remords de proposer un si bas prix pour ton homme. Ha-ha-ha-ha. Adieu.";
			link.l1 = "À bientôt.";
			link.l1.go = "CapComission2_32";
		break;
		
		case "CapComission2_32":
			AddQuestRecord("CaptainComission1", "9");
			AddQuestUserData("CaptainComission1", "sSex", GetSexPhrase("",""));
			AddQuestUserData("CaptainComission1", "sCharName", pchar.GenQuest.CaptainComission.Name);
			AddQuestUserData("CaptainComission1", "sCity", XI_ConvertString("Colony" + pchar.GenQuest.CaptainComission.City + "Acc"));	// belamour gen	
			addMoneyToCharacter(pchar, -150000);
			pchar.GenQuest.CaptainComission.vikupzaplatil = true; // новая проверка ,если шарль заплатил выкуп за пленника. лесник																																																			
			DialogExit();
			AddDialogExitQuestFunction("CaptainComission_GeneratePassengerSlave");	
		break;
		
		case "CapComission2_4":
			if(!CheckAttribute(pchar,"GenQuest.CaptainComission.RepeatSpeak"))
			{
				AddQuestRecord("CaptainComission1", "31");
				AddQuestUserData("CaptainComission1", "sName", "Zachary Marlow");		// лесник																											 
				//AddQuestUserData("CaptainComission1", "sName", ChangeNameCase(NAMETYPE_MAIN, pchar.GenQuest.CaptainComission.PirateName, NAME_NOM));// в СЖ не работает
			}	
			pchar.GenQuest.CaptainComission.RepeatSpeak = true;		
			DialogExit();
		break;
		
		case "CapComission3":
			dialog.text = "Alors,  "+GetFullName(pchar)+", as-tu coulé mes potes? Hé-hé-hé...";
			if(pchar.GenQuest.CaptainComission.PirateShips == "goaway")
			{
				link.l1 = "Non. Je n'ai pas réussi à les attraper. Et je ne les ai pas rencontrés à leur retour.";
				link.l1.go = "CapComission4";
			}
			if(pchar.GenQuest.CaptainComission.PirateShips == "died")	
			{
				link.l1 = "Je l'ai fait. Je les ai envoyés nourrir les requins.";
				link.l1.go = "CapComission5";
			}
			DeleteAttribute(pchar,"GenQuest.CaptainComission.PirateShips");
		break;
		
		case "CapComission4":
			dialog.text = "Bon sang ! Que je les aie rencontrés ou non, ça n'a plus d'importance maintenant ! Et quelle sera ta prochaine suggestion ?";
			link.l1 = "Peut-être que tu as un boulot plus simple pour moi ?";
			link.l1.go = "CapComission4_1";
			link.l2 = "Ecoute, "+NPChar.name+", fais baisser le prix pour le prisonnier...";
			link.l2.go = "CapComission4_2";
		break;
		
		case "CapComission4_1":
			dialog.text = "Non.";
			link.l1 = "Adieu alors...";
			link.l1.go = "CapComission4_3";
		break;
		
		case "CapComission4_2":
			dialog.text = "Faire baisser le prix ?! Je viens de perdre mon trésor à cause de ton incompétence ! Et maintenant je peux augmenter le prix ! Tu peux le prendre pour 200 000 pesos si tu veux, ou tu peux foutre le camp d'ici.";
			link.l1 = "C'est trop cher... Adieu...";
			link.l1.go = "CapComission4_4";
			if(sti(pchar.money) >= 200000)
			{
				link.l2 = "Merde, prends tes pièces.";
				link.l2.go = "CapComission4_5";
			}	
		break;
		
		case "CapComission4_3":
			ChangeCharacterComplexReputation(pchar,"nobility", -2);
			AddQuestRecord("CaptainComission1", "27");
			AddQuestUserData("CaptainComission1", "sSex", GetSexPhrase("",""));
			AddQuestUserData("CaptainComission1", "sName", "Marlow");		// лесник																								   
			//AddQuestUserData("CaptainComission1", "sName", ChangeNameCase(NAMETYPE_MAIN, pchar.GenQuest.CaptainComission.PirateName, NAME_DAT));
			AddQuestUserData("CaptainComission1", "sCity", XI_ConvertString("Colony" + pchar.GenQuest.CaptainComission.City + "Acc"));
			AddQuestUserData("CaptainComission1", "sCharName", pchar.GenQuest.CaptainComission.Name);
			DeleteAttribute(pchar,"GenQuest.CaptainComission.PirateShips");
			DialogExit();
		break;
		
		case "CapComission4_4":
			ChangeCharacterComplexReputation(pchar,"nobility", -2);
			AddQuestRecord("CaptainComission1", "28");
			AddQuestUserData("CaptainComission1", "sSex", GetSexPhrase("",""));
			AddQuestUserData("CaptainComission1", "sName", "Marlow"); // правка	// лесник																											 
			//AddQuestUserData("CaptainComission1", "sName", ChangeNameCase(NAMETYPE_MAIN, pchar.GenQuest.CaptainComission.PirateName, NAME_NOM));
			AddQuestUserData("CaptainComission1", "sCity", XI_ConvertString("Colony" + pchar.GenQuest.CaptainComission.City + "Acc"));
			AddQuestUserData("CaptainComission1", "sCharName", pchar.GenQuest.CaptainComission.Name);
			DeleteAttribute(pchar,"GenQuest.CaptainComission.PirateShips");
			DialogExit();		
		break;
		
		case "CapComission4_5":
			dialog.text = "Tu peux prendre ce faible...";
			link.l1 = "Adieu.";
			link.l1.go = "CapComission4_6";
		break;
		
		case "CapComission4_6":
			addMoneyToCharacter(pchar, -200000);
			AddQuestRecord("CaptainComission1", "29");
			AddQuestUserData("CaptainComission1", "sName", "Marlow"); // правки имени в сж лесник																										  
			AddQuestUserData("CaptainComission1", "sName", ChangeNameCase(NAMETYPE_MAIN, pchar.GenQuest.CaptainComission.PirateName, NAME_NOM));// в сж не работает
			AddQuestUserData("CaptainComission1", "sCity", XI_ConvertString("Colony" + pchar.GenQuest.CaptainComission.City + "Acc"));
			AddQuestUserData("CaptainComission1", "sCharName", pchar.GenQuest.CaptainComission.Name);
			DeleteAttribute(pchar,"GenQuest.CaptainComission.PirateShips");
			pchar.GenQuest.CaptainComission.SlaveAddMoney = true;
			DialogExit();	
			AddDialogExitQuestFunction("CaptainComission_GeneratePassengerSlave");	
		break;
		
		case "CapComission5":
			dialog.text = "Ho-ho ! Bien joué ! Prends ton faible et bonne chance.";
			link.l1 = "Merci. Adieu.";
			link.l1.go = "CapComission5_1";
		break;
		
		case "CapComission5_1":
			AddQuestRecord("CaptainComission1", "34");
			AddQuestUserData("CaptainComission1", "sName", pchar.GenQuest.CaptainComission.SlaveName);
			AddQuestUserData("CaptainComission1", "sCity", XI_ConvertString("Colony" + pchar.GenQuest.CaptainComission.City + "Acc"));
			AddQuestUserData("CaptainComission1", "sCharName", pchar.GenQuest.CaptainComission.Name);
			DeleteAttribute(pchar,"GenQuest.CaptainComission.PirateShips");
			DialogExit();		
			AddDialogExitQuestFunction("CaptainComission_GeneratePassengerSlave");	
		break;
		
			/*case "CapComission6":    // ЕСЛИ В ПЕРВЫЙ РАЗ ОТКАЗАЛ В ЗАДАНИИ ,ТО ПУСТЬ БАБКИ ИЩЕТ
		     ИНАЧЕ ПОВТОРНАЯ ДАЧА ЗАДАНИЯ ПРЕВРАЩАЕТ КВЕСТ В КАШУ.. лесник
			dialog.text = "As-tu apporté la rançon"+GetSexPhrase("","ла")+"? Car je ne plaisantais pas quand j'ai dit que je le vendrais aux planteurs.";			
			link.l1 = "Écoute, "+NPChar.name+", euh, il y a un problème... En fait, je n'ai pas une telle somme. Mais je suis prêt"+GetSexPhrase("","а")+"travailler.";
			link.l1.go = "CapComission2_2";
			if(makeint(pchar.money) > 150000)
			{
				link.l2 = "Il est bon que tu ne l'aies pas vendu. Voici tes pièces - 150000 pesos. Où puis-je le trouver ?"link.l2.go ="CapComission2_3";
			}			
		break;*/
		  case "CapComission6":                        // лесник . пусть шарль бабло ищет,или забить на пленника.
			dialog.text = "As-tu apporté l'argent? Je ne plaisantais pas au sujet de la vente de cet homme à la plantation.";			
			link.l1 = "Je n'ai pas l'argent, "+NPChar.name+", mais j'y travaille.";
			link.l1.go = "exit";
			if(makeint(pchar.money) > 150000)
			{
				link.l2 = "C'est bien que tu ne l'aies pas vendu. Voici tes pièces - 150.000 pesos. Où puis-je le trouver ?"link.l2.go ="CapComission2_3";
			}			
		break;

																																				 																																													  																																															
//--------------------------------------------Похититель------------------------------------------------------
		case "Marginpassenger":
			dialog.text = "Et pourquoi te soucies-tu de ce que je fais? Tu sais, tu ferais mieux de t'en aller...";
			link.l1 = "Tshh, calme-toi. J'ai une affaire avec toi. C'est à propos de ton prisonnier.";
			link.l1.go = "Marginpassenger_1";
		break;
		
		case "Marginpassenger_1":
			dialog.text = "Ah, très bien. Qui veux-tu rançonner ?";
			link.l1 = "Attends. Je ne suis pas ici pour payer une rançon, je suis ici pour t'offrir d'acheter un prisonnier. Eh bien, et tu auras l'occasion d'obtenir une rançon pour lui.";
			link.l1.go = "Marginpassenger_2";
		break;
		
		case "Marginpassenger_2":
			dialog.text = "Hm. Et pourquoi avez-vous besoin de mes services ? Pourquoi ne voulez-vous pas obtenir de l'argent directement pour vous-même ?";
			link.l1 = "C'est assez risqué pour moi. Je pourrais avoir des ennuis avec les autorités.";
			link.l1.go = "Marginpassenger_3";
		break;
		
		case "Marginpassenger_3":
			dialog.text = "Ha-h... bien alors. Voyons voir. Qui est votre prisonnier ?";
			link.l1 = "C'est "+pchar.GenQuest.Marginpassenger.Text+" "+XI_ConvertString("Colony"+pchar.GenQuest.Marginpassenger.City+"Gen")+".";
			link.l1.go = "Marginpassenger_4";
		break;
		
		case "Marginpassenger_4":
			int iTemp = makeint(sti(pchar.GenQuest.Marginpassenger.Dublon)*2*stf(pchar.GenQuest.Marginpassenger.Chance))*100;
			dialog.text = "Je vois... ce serait un bon marché si tu ne mens pas. Je suppose que je peux te payer pour cet homme "+iTemp+" pesos ou donne des informations intéressantes à la place. C'est ton choix.";
			link.l1 = "Je ferais mieux de prendre des pesos. J'en ai assez de cette affaire...";
			link.l1.go = "Marginpassenger_money";
			link.l2 = "Ha ! Dis-m'en plus. Je suis sûr que tu as quelque chose d'intéressant à me raconter.";
			link.l2.go = "Marginpassenger_offer";
		break;
		
		case "Marginpassenger_money":
			dialog.text = "L'argent alors. Prends-les. Maintenant, ce n'est plus ton problème. Livre le sujet de la vente ici.";
			link.l1 = "Il doit déjà être près des portes de la ville. Merci ! Tu m'as vraiment aidé.";
			link.l1.go = "Marginpassenger_money_1";
		break;
		
		case "Marginpassenger_money_1":
			iTemp = makeint(sti(pchar.GenQuest.Marginpassenger.Dublon)*2*stf(pchar.GenQuest.Marginpassenger.Chance))*100;
			dialog.text = "Je t'en prie, apporte-m'en plus... À la prochaine !";
			link.l1 = "Bonne chance...";
			link.l1.go = "exit";
			AddMoneyToCharacter(pchar, iTemp);
			sld = characterFromId("MarginPass");
			RemovePassenger(Pchar, sld);
			sld.lifeday = 0;
			AddQuestRecord("Marginpassenger", "12");
			AddQuestUserData("Marginpassenger", "sSum", iTemp);
			CloseQuestHeader("Marginpassenger");
			DeleteAttribute(Pchar, "GenQuest.Marginpassenger");
		break;
		
		case "Marginpassenger_offer":
			pchar.GenQuest.Marginpassenger.Goods = GetRandomGood(FLAG_GOODS_TYPE_EXPORT, FLAG_GOODS_VALUABLE_WOOD);
			pchar.GenQuest.Marginpassenger.GoodsQty = 200+rand(10)*10;
			switch (hrand(1))
			{
				case 0: //бухта на южном мейне
					SelectSouthshore();
					while (!isLocationFreeForQuests(pchar.GenQuest.Marginpassenger.Shore)) SelectSouthshore();
					dialog.text = "C'est bon de faire affaire avec un homme intelligent. Maintenant écoute : dans quelques jours à "+XI_ConvertString(pchar.GenQuest.Marginpassenger.Shore+"Ca")+" une expédition espagnole arrivera du continent, chargée de marchandises précieuses. Ils attendront un navire censé prendre la cargaison. Si tu arrives là-bas en une semaine, tu auras une chance de prendre la cargaison pour toi.\nSi j'étais toi, je serais déjà en train de me diriger vers mon navire. Et amène le prisonnier ici.";
					link.l1 = "Merci ! Les marchandises seront une belle compensation pour mes ennuis. Et mon passager doit déjà être près des portes de la ville. Il vous sera amené.";
					link.l1.go = "Marginpassenger_offer_1";
				break;
				
				case 1: //просто кораблик
					SelectSouthcity();
					pchar.GenQuest.Marginpassenger.ShipName1 = GenerateRandomNameToShip(SPAIN);
					dialog.text = "C'est bon de faire affaire avec un homme intelligent. Maintenant écoute : dans environ une semaine un brigantin espagnol '"+pchar.GenQuest.Marginpassenger.ShipName1+" chargé de marchandises précieuses partira de "+XI_ConvertString("Colony"+pchar.GenQuest.Marginpassenger.Southcity+"Gen")+" à "+XI_ConvertString("Colony"+pchar.GenQuest.Marginpassenger.Southcity1+"Gen")+". Si tu te dépêches, tu l'attraperas facilement.\nTu es encore là ? Si j'étais toi, je serais déjà en route vers mon navire. Et amène le prisonnier ici.";
					link.l1 = "Merci ! Les marchandises seront une belle compensation pour mes ennuis. Et mon passager doit déjà être près des portes de la ville. Il vous sera amené.";
					link.l1.go = "Marginpassenger_offer_2";
				break;
			}
			sld = characterFromId("MarginPass");
			RemovePassenger(Pchar, sld);
			sld.lifeday = 0;
			pchar.GenQuest.Marginpassenger = "final";
		break;
		
		case "Marginpassenger_offer_1":
			DialogExit();
			AddQuestRecord("Marginpassenger", "13");
			AddQuestUserData("Marginpassenger", "sShore", XI_ConvertString(pchar.GenQuest.Marginpassenger.Shore+"Dat"));//лесник - окончание в СЖ // belamour gen: Abl - это к Залив"ом", нужен дательный
			AddQuestUserData("Marginpassenger", "sName", "Zachary Marlow")); // belamour gen : как-то странно, наводку даёт Захар, а в сж Добряк дефолтом
			SetFunctionTimerCondition("Marginpassenger_SouthshoreOver", 0, 0, 7, false);
			pchar.quest.Marginpassenger.win_condition.l1 = "location";
			pchar.quest.Marginpassenger.win_condition.l1.location = pchar.GenQuest.Marginpassenger.Shore;
			pchar.quest.Marginpassenger.function = "Marginpassenger_Southshore";
		break;
		
		case "Marginpassenger_offer_2":
			DialogExit();
			AddQuestRecord("Marginpassenger", "16");
			AddQuestUserData("Marginpassenger", "sName", "Zachary Marlow")); // belamour gen 
			AddQuestUserData("Marginpassenger", "sCity", XI_ConvertString("Colony"+pchar.GenQuest.Marginpassenger.Southcity+"Gen"));
			AddQuestUserData("Marginpassenger", "sCity1", XI_ConvertString("Colony"+pchar.GenQuest.Marginpassenger.Southcity1+"Acc")); // лесник - окончание в СЖ
			AddQuestUserData("Marginpassenger", "sShipName", pchar.GenQuest.Marginpassenger.ShipName1);
			SetFunctionTimerCondition("Marginpassenger_SouthshipInWorld", 0, 0, 5+rand(2), false);
		break;
		
		// ============== Грабеж среди бела дня, попытка залезть в сундуки =========================
		case "Man_FackYou":
			dialog.text = LinkRandPhrase("Vol !!! C'est inacceptable ! Prépare-toi, "+GetSexPhrase("garçon","fille")+"...","Hé, qu'est-ce que tu fous là ?! Tu pensais pouvoir me voler ? T'es foutu...","Attends, quoi diable ? Enlevez vos mains ! Il s'avère que tu es un voleur ! Fin de la route, salaud...");
			link.l1 = LinkRandPhrase("Merde !","Carramba!!","Merde !!");
			link.l1.go = "PL_Q3_fight";
		break;
					
		// ======================== блок нод angry ===============>>>>>>>>>>>>>>>
		case "AngryRepeat_1":
            dialog.text = RandPhraseSimple(""+GetSexPhrase("Va-t'en ","Va-t'en")+" d'ici !","Sors de chez moi !");
			link.l1 = "Oups...";
		    link.l1.go = "AngryExitAgainWithOut";
            if (CheckAttribute(npchar, "angry.terms")) //примиряемся через 10 дней.
            {
                if (GetNpcQuestPastDayParam(npchar, "angry.terms") > sti(npchar.angry.terms))
                {
         			dialog.text = "Ne m'importune pas avec tes bavardages bon marché. La prochaine fois, tu n'aimeras pas le résultat...";
        			link.l1 = "Je l'ai.";
        			link.l1.go = NextDiag.TempNode;
        			CharacterDelAngry(npchar);
                }
            }
    	break;
		
		case "AngryRepeat_2":
            dialog.text = RandPhraseSimple("C'est fini, pas de bavardage.","Je ne veux plus te parler, alors tu ferais mieux de ne pas me déranger.");
			link.l1 = RandPhraseSimple("Comme tu veux...","Hm, très bien alors...");
		    link.l1.go = "AngryExitAgain";
            if (CheckAttribute(npchar, "angry.terms")) //примиряемся через 10 дней.
            {
                if (GetNpcQuestPastDayParam(npchar, "angry.terms") > sti(npchar.angry.terms))
                {
         			dialog.text = "J'espère que tu montreras plus de respect et cesseras d'être impoli ?";
        			link.l1 = "Soyez-en sûr, Pasteur, je le ferai.";
        			link.l1.go = NextDiag.TempNode;
        			CharacterDelAngry(npchar);
                }
            }
    	break;
		
		case "AngryExitAgain":
            DialogExit();
            DeleteAttribute(npchar, "angry.ok");
		break;
		
		case "AngryExitAgainWithOut":
            DialogExit();
            DeleteAttribute(npchar, "angry.ok");
            DoReloadCharacterToLocation("Puertoprincipe_town","reload","reload6");
		break;
		// <<<<<<<<<<<<============= блок нод angry =============================
		case "pirate_town":
            dialog.text = "Résoudre le problème ? As-tu la moindre idée de ce que tu as fait ? Quoi qu'il en soit, apporte-moi un million de pesos et je persuaderai les gars d'oublier ton acte. Si tu n'aimes pas l'idée, alors va au diable.";
			if (sti(Pchar.money) >= 1000000)
			{
				link.l1 = "D'accord, je suis prêt à payer.";
				link.l1.go = "pirate_town_pay";
			}
			link.l2 = "Compris. Je m'en vais.";
			link.l2.go = "pirate_town_exit";
		break;
		
		case "pirate_town_exit":
			DialogExit();
            bDisableFastReload = true;//закрыть переход
			pchar.quest.pirate_in_town.win_condition.l1 = "ExitFromLocation";
			pchar.quest.pirate_in_town.win_condition.l1.location = pchar.location;
			pchar.quest.pirate_in_town.function = "TownPirate_battle";
		break;
		
		case "pirate_town_pay":
            dialog.text = "Bien ! Considérez-vous lavé de vos péchés. Mais j'espère que vous ne ferez plus jamais de telles horreurs.";
			link.l1 = "Je ne le ferai pas. Bien trop cher pour moi. Adieu...";
			link.l1.go = "exit";
			AddMoneyToCharacter(pchar, -1000000);
			pchar.GenQuest.Piratekill = 0;
		break;
	}
}

void SelectSouthshore()
{
	switch (rand(6))
	{
		case 0: pchar.GenQuest.Marginpassenger.Shore = "shore37"; break;
		case 1: pchar.GenQuest.Marginpassenger.Shore = "shore47"; break;
		case 2: pchar.GenQuest.Marginpassenger.Shore = "shore48"; break;
		case 3: pchar.GenQuest.Marginpassenger.Shore = "shore25"; break;
		case 4: pchar.GenQuest.Marginpassenger.Shore = "shore21"; break;
		case 5: pchar.GenQuest.Marginpassenger.Shore = "shore20"; break;
		case 6: pchar.GenQuest.Marginpassenger.Shore = "shore19"; break;
	}
}

void SelectSouthcity()
{
	switch (hrand(2))
	{
		case 0: 
			pchar.GenQuest.Marginpassenger.Southcity = "Maracaibo";
			pchar.GenQuest.Marginpassenger.Southcity1 = "Havana"; 
		break;
		
		case 1:
			pchar.GenQuest.Marginpassenger.Southcity = "Cartahena";
			pchar.GenQuest.Marginpassenger.Southcity1 = "Santiago"; 
		break;
		
		case 2:
			pchar.GenQuest.Marginpassenger.Southcity = "Portobello";
			pchar.GenQuest.Marginpassenger.Southcity1 = "Santodomingo"; 
		break;
	}
}
