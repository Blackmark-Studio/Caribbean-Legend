//Jason общий диалог мещан
#include "DIALOGS\%language%\Rumours\Common_rumours.c"
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

    // вызов диалога по городам -->
    NPChar.FileDialog2 = "DIALOGS\" + LanguageGetLanguage() + "\Citizen\" + NPChar.City + "_Citizen.c";
    if (LoadSegment(NPChar.FileDialog2))
	{
        ProcessCommonDialog(NPChar, Link, NextDiag);
		UnloadSegment(NPChar.FileDialog2);
	}
    // вызов диалога по городам <--
    ProcessCommonDialogRumors(NPChar, Link, NextDiag);
    int iTest, iTemp;
    iTest = FindColony(NPChar.City);
    ref rColony;
    string sTemp, sCity, sTitle;
	if (iTest != -1)
	{
		rColony = GetColonyByIndex(iTest);
	}
	
	String attrLoc = Dialog.CurrentNode;
	
	if(HasSubStr(attrLoc, "RumourAboutOwners_"))
	{
		NPChar.RumourOwnerType = FindStringAfterChar(attrLoc, "_");
		Dialog.CurrentNode = "RumourAboutOwners_TakeRumour";
	}
	
	switch(Dialog.CurrentNode)
	{
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
		case "fight":
            LAi_group_Attack(NPChar, Pchar);
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
		case "First time":
			if (sti(NPChar.nation) == PIRATE)
			{
				if (sti(rColony.HeroOwn) == true) // наш горожанин
				{
				    dialog.text = RandPhraseSimple("On dit que tu possèdes cette ville, "+GetSexPhrase("monsieur","mademoiselle")+".","Quelle agréable rencontre, "+GetSexPhrase("sieur","mademoiselle")+" !");
					link.l1 = RandPhraseSimple("J'ai changé d'avis. Bonne chance !","Je me promène simplement en ville. Adieu.");
					link.l1.go = "exit";
					link.l2 = RandPhraseSimple("J'ai une question pour vous.","J'ai besoin d'informations.");
					link.l2.go = "quests";//(перессылка в файл города)
					if (CheckAttribute(pchar, "GenQuest.Loan.FindCitizen") && !CheckAttribute(pchar, "GenQuest.Loan.FindCitizenDone") && !CheckAttribute(pchar, "GenQuest.Loan.FindCitizenFalied"))
		            {
		                if (Characters[sti(pchar.GenQuest.Loan.FindCitizenIdx)].id == Npchar.id)
		                {
							link.l3 = RandPhraseSimple("Je veux discuter de questions financières.","À propos des finances...");
							link.l3.go = "LoanForAll";//(перессылка в кредитный генератор)
						}
					}
					break;
				}
				else
				{ // пираты, не наши
					if (sti(pchar.GenQuest.Piratekill) > 20)
					{
						dialog.text = RandPhraseSimple("Alarme ! Un fou armé est ici ! Aux armes !","Aux armes ! Un fou furieux armé est ici !");
						link.l1 = RandPhraseSimple("Quoi?!","Que fais-tu?!");
						link.l1.go = "pirate_fight";
					}
					else
					{
						dialog.text = RandPhraseSimple("Que veux-tu ? Circule.","Arrête de bloquer mon chemin, dégage.");
						link.l1 = RandPhraseSimple("Tu sais quoi ? Ne jappe pas !","Calmez-vous. Ou je le ferai moi-même !");
						link.l1.go = "exit";
						link.l2 = RandPhraseSimple("Je veux te poser une question.","Juste une minute de votre attention, s'il vous plaît. Une question.");
						link.l2.go = "quests";//(перессылка в файл города)
						if (CheckAttribute(pchar, "GenQuest.Loan.FindCitizen") && !CheckAttribute(pchar, "GenQuest.Loan.FindCitizenDone") && !CheckAttribute(pchar, "GenQuest.Loan.FindCitizenFalied"))
						{
							if (Characters[sti(pchar.GenQuest.Loan.FindCitizenIdx)].id == Npchar.id)
							{
								link.l3 = RandPhraseSimple("Je veux discuter de questions financières.","À propos des finances...");
								link.l3.go = "LoanForAll";//(перессылка в кредитный генератор)
							}
						}
					}
				}
				break;
			}
            if(NPChar.quest.meeting == "0")
			{
				NPChar.quest.meeting = "1";
				// проверка наличия корабля в порту
				bool ok = (rColony.from_sea == "") || (Pchar.location.from_sea == rColony.from_sea);
				if(sti(Pchar.Ship.Type) != SHIP_NOTUSED && 4-sti(RealShips[sti(Pchar.Ship.Type)].Class) > 0 && or(IsWarShipType(pchar), IsRaiderShipType(pchar))) ok = false;
				if (ok && sti(Pchar.Ship.Type) != SHIP_NOTUSED && CheckAttribute(npchar, "quest.passenger") && !CheckAttribute(pchar, "GenQuest.Townpassenger") && 7-sti(RealShips[sti(Pchar.Ship.Type)].Class) > 0)//горожанин-пассажир
				{
					dialog.text = "Bonne journée, "+GetAddress_Form(NPChar)+". Je vois que vous êtes capitaine de votre propre navire. Je voudrais vous demander une faveur...";
					link.l1 = "Je t'écoute, "+GetAddress_FormToNPC(NPChar)+". Que veux-tu?";
					link.l1.go = "passenger";
					link.l2 = "Je suis désolé, "+GetAddress_FormToNPC(NPChar)+", mais je suis pressé.";
					link.l2.go = "exit";
					npchar.quest.meeting = "1";
					DeleteAttribute(npchar, "talker"); //снимаем говорилку
					break;
				}

                // homo 05/08/06
				dialog.Text = NPCharRepPhrase(npchar,LinkRandPhrase("Je suis ","Mon nom est ","Vous pouvez m'appeler ")+GetFullName(npchar)+LinkRandPhrase("Que veux-tu ?","Je ne vous ai pas vu auparavant. Qui êtes-vous ?","Qui es-tu et que veux-tu de moi ?"),LinkRandPhrase("Salutations, "+GetAddress_Form(NPChar)+". Mon nom est "+GetFullName(npchar)+" Et comment vous appelez-vous ?","Bonjour, "+GetAddress_Form(NPChar)+"! Je suis "+GetFullName(npchar)+"Puis-je connaître votre nom ?","Oui, "+GetAddress_Form(NPChar)+". Que veux-tu ? Et d'ailleurs, mon nom est "+GetFullName(npchar)+" Et comment vous appelez-vous?"));

				Link.l1 = pcharrepphrase(LinkRandPhrase("Que le diable m'emporte ! ","Nom de Dieu ! ","Que le diable t'emporte ! ")+"Oui, je suis le capitaine "+GetFullName(Pchar)+LinkRandPhrase(", n'avez-vous jamais entendu "+NPCharSexPhrase(NPChar,", salaud?","?")," et "+GetSexPhrase("le pirate le plus célèbre","la plus célèbre fille-pirate")+" dans la mer !","et que le diable m'emporte si j'ai tort !"),LinkRandPhrase("Je suis "+GetFullName(Pchar)+", capitaine.","Mon nom est "+GetFullName(Pchar)+".","Vous pouvez m'appeler capitaine "+GetFullName(Pchar)+"."));
				Link.l1.go = "Meeting";
				
				//==> прибыла инспекция на Святом Милосердии
				if (CheckAttribute(pchar, "questTemp.SantaMisericordia.ColonyZapret") && pchar.location == pchar.questTemp.SantaMisericordia.ColonyZapret + "_town")
				{
					dialog.Text = LinkRandPhrase(LinkRandPhrase("La ville entière est en ébullition - don Fernando de Alamida, l'inspecteur royal, est arrivé. Tu sais, j'en ai vu beaucoup ici, mais ça... Ce n'est pas le chagrin qui change les gens, mais la manière dont ils y font face. On dit qu'il est devenu un autre homme après la mort de son père. Maintenant, tu ne trouveras pas de serviteur de la Couronne plus incorruptible et... impitoyable dans tout l'Archipel.","Regarde juste le 'Sainte Miséricorde' ! Ils disent que le roi lui-même a ordonné sa construction selon des plans spéciaux. Et remarque - pas une seule égratignure. Comme si la Vierge Marie elle-même la protégeait. Bien que j'aie entendu des rumeurs... peut-être que ce n'est pas la Vierge du tout.","Tu sais combien de fois ils ont essayé de tuer don Fernando ? Douze attaques en haute mer - et c'est rien que l'année dernière ! Eh bien, avec un équipage aussi loyal et entraîné, et sous la protection du Seigneur - il survivra à la treizième aussi !"),LinkRandPhrase("As-tu entendu ? Don Fernando de Alamida est arrivé dans notre ville, et on dit qu'il est quelque part dans les rues en ce moment. J'aimerais bien le voir de mes propres yeux...","Un homme compliqué, ce don Fernando. Certains disent qu'il est un sauveur, purifiant la Mère Patrie de l'immondice. D'autres murmurent que quelque chose s'est brisé en lui après la mort de son père et que bientôt nous pleurerons tous. Mais je vais te dire ceci : ne le crains pas. Crains ceux qui l'ont fait tel qu'il est.","Un homme si beau, ce don Fernando ! Mais tu sais ce qui est étrange ? C'est comme s'il ne remarquait personne. Tout est devoir et service. J'ai entendu dire qu'il y avait une fille... mais après avoir rencontré un prêtre, il a complètement rejeté les plaisirs mondains. Comme s'il avait fait un vœu."),RandPhraseSimple(RandPhraseSimple("Maudit inspecteur ! Tant qu'il est là, la ville est comme morte. Pas de commerce, pas d'amusement. Même respirer, il semble, doit être plus silencieux. Et tu sais ce qui est le plus effrayant ? C'est pareil dans chaque port. Comme une horloge. Sa Majesté Royale n'aurait pas pu inventer délibérément ce supplice pour nous tous !","Don Fernando a de nouveau visité l'orphelinat. Il fait des dons généreux, prie pendant des heures. Un homme aussi digne devrait être pris comme exemple pour ces maudits détourneurs de fonds !"),RandPhraseSimple("Ha ! 'Saint' Fernando a encore fermé tous les bordels. Eh bien, peu importe, il partira bientôt et ils rouvriront aussitôt.","L'ins... l'inspecteur est arrivé, voilà quoi ! Don Fernando de Almeyda, ou, comment il s'appelle, Alamida ! Tellement important que le gouverneur lui-même marche sur la pointe des pieds autour de lui. On dit qu'il te regarde dans les yeux et voit tous tes péchés immédiatement. Terrifiant !")));
					link.l1 = "... ";
					link.l1.go = "exit";
				}
				//<== прибыла инспекция на Святом Милосердии
				//==> Леди Бет в порту города
				if (CheckAttribute(pchar, "questTemp.LadyBeth.CaptainInColony") && pchar.location == pchar.questTemp.LadyBeth.CaptainInColony + "_town")
				{
					dialog.Text = findLedyBethRumour(npchar);
					link.l1 = "...";
					link.l1.go = "exit";
				}
				//<== Леди Бет в порту города
			}
			else
			{
				link.l1 = PCharRepPhrase("Je veux juste te poser une question sur ce trou que tu appelles 'la ville'.","Je veux te demander quelque chose à propos de cette ville.");
				link.l1.go = "new question";
 				link.l2 = RandPhraseSimple("J'ai une question pour vous.","J'ai besoin de quelques informations.");
				if (CheckCharacterItem(pchar, "CaptainBook"))				
				{
					if((pchar.questTemp.different.GiveShipLetters.city == npchar.city) && CheckAttribute(pchar, "questTemp.different.GiveShipLetters"))
					{
						link.l2.go = "ShipLetters_7";// генератор  "Найденные документы"
					}
					else
					{
						link.l2.go = "quests";
					}	
				}
				else
				{
					link.l2.go = "quests";//(перессылка в файл города)
				}	
				if (CheckAttribute(pchar, "GenQuest.Loan.FindCitizen") && !CheckAttribute(pchar, "GenQuest.Loan.FindCitizenDone") && !CheckAttribute(pchar, "GenQuest.Loan.FindCitizenFalied"))
	            {
	                if (Characters[sti(pchar.GenQuest.Loan.FindCitizenIdx)].id == Npchar.id)
	                {
						link.l3 = RandPhraseSimple("Je veux discuter de questions financières.","À propos des finances...");
						link.l3.go = "LoanForAll";//(перессылка в кредитный генератор)
					}
				}
				
				//Jason --> генератор Неудачливый вор
				if (CheckAttribute(pchar, "GenQuest.Device.Shipyarder") && NPChar.location == pchar.GenQuest.Device.Shipyarder.City + "_town" && pchar.GenQuest.Device.Shipyarder == "begin" && !CheckAttribute(npchar, "quest.Device"))
				{
					link.l16 = "Écoutez, j'espère que vous pouvez m'aider. Je veux acheter un "+pchar.GenQuest.Device.Shipyarder.Type+", et on m'a dit que cette chose avait été vendue dans votre ville. Eh bien, quelqu'un la vendait dans les rues. Savez-vous quelque chose ?";
					link.l16.go = "Device_Citizen";
				}
				// <-- генератор Неудачливый вор
				
				// Квестовый генератор священника. Квест №2. Warship -->
				if(CheckAttribute(PChar, "GenQuest.ChurchQuest_2.AskPeople") && !CheckAttribute(NPChar, "GenQuest.ChurchQuest_2.AskedPeople") && NPChar.location == PChar.GenQuest.ChurchQuest_2.QuestTown + "_town")
	            {
					link.l5 = LinkRandPhrase("Savez-vous ","Es-tu au courant ","As-tu entendu ")+" que l'église locale a été récemment cambriolée ?";
					link.l5.go = "Citiz_GenQuest_Church_2_1";
				}
				// <-- Квестовый генератор священника. Квест №2.
				
				dialog.Text = NPCharRepPhrase(npchar,PCharRepPhrase(LinkRandPhrase("Ah, c'est vous "+GetFullName(Pchar)+" "+GetSexPhrase(" - vieil ami !"," - jolie !")+"","Je suis heureux de te voir, "+GetSexPhrase("vieux ami !","belle !")+" "+Pchar.name,"Oh, c'est le "+GetSexPhrase("le capitaine lui-même","le capitaine elle-même")+" "+GetFullName(Pchar))+RandPhraseSimple("Je pensais que tu étais mort !",". Et peut-être "+GetSexPhrase("ivre comme toujours.","un peu ivre."))+LinkRandPhrase(" Allez-y, de quoi avez-vous besoin ?"," Qu'est-ce cette fois-ci?"," Tu m'importunes encore ?"),LinkRandPhrase(TimeGreeting()+", capitaine ","Bonne journée à vous, "+GetAddress_Form(NPChar)+" ","Salutations, capitaine ")+GetFullName(Pchar)+LinkRandPhrase(". Comment puis-je aider  "+GetSexPhrase("un homme si digne","une fille si digne")+", comme toi ?","Pourquoi es-tu ici ?","Que veux-tu savoir cette fois-ci ?")),PCharRepPhrase(LinkRandPhrase("Bonjour, capitaine ","Salutations, ah, c'est vous "+GetAddress_Form(NPChar)+" ","Ah, capitaine ")+GetFullName(Pchar)+LinkRandPhrase(", je pensais que nous ne nous reverrions jamais, et",", je ne dirai pas que je suis content de te voir mais",", je vois que tu es toujours en vie, quel dommage et")+LinkRandPhrase(" que voulez-vous?"," pourquoi êtes-vous ici ?"," comment puis-je vous aider?"),LinkRandPhrase(TimeGreeting()+", capitaine "+GetFullName(Pchar)+" Comment puis-je vous aider ? ","Oh, c'est le capitaine "+GetFullName(Pchar)+"! Comment puis-je vous aider ?","Salutations, "+GetAddress_Form(NPChar)+" "+Pchar.lastname+"Voulez-vous quelque chose ?")));  
	   			link.l6 = PCharRepPhrase(RandPhraseSimple("Vos oreilles vous trompent. Je dois y aller.","Non, ce n'est rien, j'étais en route pour la taverne."),RandPhraseSimple("Très bien, comme tu veux. Bonne chance !","Je me promène juste dans la ville. Adieu."));
				link.l6.go = "exit";
			}
			NextDiag.TempNode = "First time";
		break;
		
		case "ShipLetters_7":
			dialog.text = "Des questions?";
			link.l1 = "Ce nom sur ces papiers vous dit-il quelque chose?";
			link.l1.go = "ShipLetters_8";
		break;
		
		case "ShipLetters_8":
			dialog.text = LinkRandPhrase("Je m'en fous d'un fichu bout de papier et en plus, je ne sais pas lire. Va voir l'usurier, on dit qu'il sait faire des trucs avec les lettres, ha !","Je ne sais pas de quoi vous parlez, demandez à quelqu'un d'autre, capitaine"+GetFullName(Pchar)+".","Je ne sais pas comment vous aider, capitaine "+GetFullName(Pchar)+"Essaye de parler avec l'usurier, il pourrait savoir.");
			link.l1 = "Merci.";
			link.l1.go = "exit";
		break;
		
		case "Meeting":
		    dialog.Text = NPCharRepPhrase(npchar,LinkRandPhrase("Ne mentez-vous pas, capitaine "+GetFullName(Pchar)+"?","Et alors "+PChar.name+"?","Je me souviendrai de vous, "+GetFullName(Pchar)+".")+" Maintenant, dis-moi ce que tu veux ?",LinkRandPhrase("Enchanté de vous rencontrer, capitaine "+PChar.name,"Ravi de notre rencontre, "+GetAddress_Form(NPChar)+" "+PChar.lastname,"C'est un plaisir, capitaine "+PChar.name)+" . Mais je doute que vous vouliez seulement connaître mon nom, n'est-ce pas ?");
            link.l1 = PCharRepPhrase("Je veux juste demander quelque chose à propos de ce trou à rats que vous appelez 'ville'.","Je veux te poser une question sur cette ville.");
			link.l1.go = "new question";
            Link.l2 = RandPhraseSimple("J'ai une question pour vous.","J'ai besoin de quelques informations.");
			if (CheckCharacterItem(pchar, "CaptainBook"))				
			{
				if((pchar.questTemp.different.GiveShipLetters.city == npchar.city) && CheckAttribute(pchar, "questTemp.different.GiveShipLetters"))
				{
					link.l2.go = "ShipLetters_7";// генератор  "Найденные документы"
				}
				else
				{
					Link.l2.go = "quests";
				}	
			}
			else
			{
					link.l2.go = "quests";//(перессылка в файл города)
			}			
			if (CheckAttribute(pchar, "GenQuest.Loan.FindCitizen") && !CheckAttribute(pchar, "GenQuest.Loan.FindCitizenDone") && !CheckAttribute(pchar, "GenQuest.Loan.FindCitizenFalied"))
            {
                if (Characters[sti(pchar.GenQuest.Loan.FindCitizenIdx)].id == Npchar.id)
                {
					link.l3 = RandPhraseSimple("Je veux discuter des questions financières.","Concernant les finances...");
					link.l3.go = "LoanForAll";//(перессылка в кредитный генератор)
				}
			}
			
			//Jason --> генератор Неудачливый вор
			if (CheckAttribute(pchar, "GenQuest.Device.Shipyarder") && NPChar.location == pchar.GenQuest.Device.Shipyarder.City + "_town" && pchar.GenQuest.Device.Shipyarder == "begin" && !CheckAttribute(npchar, "quest.Device"))
			{
   				link.l16 = "Écoute, j'espère que tu peux m'aider. Je veux acheter un "+pchar.GenQuest.Device.Shipyarder.Type+", et on m'a dit que cette chose a été vendue dans votre ville. Eh bien, quelqu'un la vendait dans les rues. Savez-vous quelque chose à ce sujet ?";
				link.l16.go = "Device_Citizen";
			}
			// <-- генератор Неудачливый вор
			
			// Квестовый генератор священника. Квест №2. Warship -->
			if(CheckAttribute(PChar, "GenQuest.ChurchQuest_2.AskPeople") && !CheckAttribute(NPChar, "GenQuest.ChurchQuest_2.AskedPeople") && NPChar.location == PChar.GenQuest.ChurchQuest_2.QuestTown + "_town")
	        {
				link.l5 = LinkRandPhrase("Sais-tu ","Es-tu conscient ","As-tu entendu ")+" que l'église locale a été cambriolée récemment ?";
				link.l5.go = "Citiz_GenQuest_Church_2_1";
			}
			// <-- Квестовый генератор священника. Квест №2.
			
			Link.l6 = PCharRepPhrase(RandPhraseSimple("Tes oreilles te trompent. Je dois y aller.","Non, ce n'est rien, j'étais en route pour la taverne."),RandPhraseSimple("Eh bien, ce n'est rien, bonne chance !","Je me promène juste dans la ville. Adieu."));
			Link.l6.go = "exit";
		break;
		
		case "new question":
            dialog.text = NPCharRepPhrase(npchar,PCharRepPhrase(LinkRandPhrase("Oh, et je suis heureux de te voir comme je suis heureux pour une gnôle, demande ce que tu veux.","Vous aimez parler, capitaine ? Moi aussi... Surtout avec une tasse de rhum.","Oui, "+PChar.name+"?"),LinkRandPhrase("Que veux-tu d'autre ?","Je le prends, capitaine "+PChar.name+", que vous aimez bavarder ?")),PCharRepPhrase(LinkRandPhrase("Que veux-tu d'autre, "+GetAddress_Form(NPChar)+"?","Je vous écoute, capitaine.","Je dois partir, alors demandez-moi vite, capitaine."),LinkRandPhrase("Je suis toujours heureux d'avoir une compagnie agréable, "+GetAddress_Form(NPChar)+" "+PChar.lastname+"Parle.","Oui, "+GetAddress_Form(NPChar)+"?","Aimez-vous parler, capitaine? Moi aussi... ")));
			link.l1 = LinkRandPhrase("Quelles rumeurs circulent en ville ?","Des nouvelles de cette contrée ?","Comment va la vie à terre ?");
			link.l1.go = "rumours_townman";
			link.l2 = LinkRandPhrase("Peux-tu me montrer le chemin?","Je ne trouve pas le chemin vers un endroit...","Aidez-moi à atteindre un endroit...");
			link.l2.go = "town";  //(перессылка в файл города)
			link.l3 = RandPhraseSimple("Je veux savoir ce que les gens disent à propos d'une personne.","Sais-tu ce que les gens disent d'une personne?");
			link.l3.go = "info"; //(перессылка в файл города)
			link.l4 = RandPhraseSimple("Je veux en savoir plus sur les habitants.","Peux-tu me dire quelque chose sur les habitants ?");
			link.l4.go = "RumourAboutOwners";
			link.l5 = PCharRepPhrase(RandPhraseSimple("Tes oreilles te trompent. Je dois partir.","Non, ce n'est rien, je suis en route pour la taverne."),RandPhraseSimple("Eh bien, ce n'est rien. Bonne chance !","Je me promène juste en ville. Au revoir."));
			link.l5.go = "exit";
		break;
		
		case "RumourAboutOwners":
			Dialog.Text = "Qui vous intéresse ?";
			if(GetCharacterIndex(NPChar.city + "_Mayor") != -1)
			{
				link.l1 = "Je veux en savoir plus sur le gouverneur.";
				link.l1.go = "RumourAboutOwners_Mayor";
			}
			if(GetCharacterIndex(NPChar.city + "_TavernKeeper") != -1)
			{
				link.l2 = "Vous voulez en savoir plus sur le propriétaire de la taverne locale.";
				link.l2.go = "RumourAboutOwners_TavernKeeper";
			}
			if(GetCharacterIndex(NPChar.city + "_ShipYarder") != -1)
			{
				link.l3 = "Je veux en savoir plus sur le maître du chantier naval local.";
				link.l3.go = "RumourAboutOwners_ShipYarder";
			}
			if(GetCharacterIndex(NPChar.city + "_Trader") != -1)
			{
				link.l4 = "Je veux en savoir plus sur le propriétaire du magasin local.";
				link.l4.go = "RumourAboutOwners_Trader";
			}
			link.l9 = "Ce n'est rien. Oubliez ça.";
			link.l9.go = "exit";
			break;
			
		case "RumourAboutOwners_TakeRumour":
			sTemp = sRumourAboutOwners_CityRumour(NPChar.City, NPChar.RumourOwnerType);
			Dialog.Text = sTemp;
			link.l1 = "Merci.";
			link.l1.go = "exit";
			// Здесь можно делать проверка по квестам, какой слух выпал
			DeleteAttribute(PChar, "QuestTemp.RumoursAboutOwners");
		break;
		
		//Jason --> генератор Неудачливый вор
		case "Device_Citizen":
           dialog.text = "Hm, "+pchar.GenQuest.Device.Shipyarder.Type+"? Jamais entendu parler... Je vis ici depuis longtemps et je n'ai jamais vu quelque chose comme ça.";
			link.l1 = "Eh bien, c'est un outil de construction navale, "+pchar.GenQuest.Device.Shipyarder.Describe+"Quelqu'un a-t-il vendu quelque chose de ce genre en ville ? Ou peut-être l'a-t-il transporté et vous l'avez remarqué ?";
			link.l1.go = "Device_Citizen_1";
			npchar.quest.Device = "true";
		break;
		
		case "Device_Citizen_1":
			if (sti(pchar.GenQuest.Device.Shipyarder.Chance1) > 3 && sti(pchar.GenQuest.Device.Shipyarder.Chance1) < 6 && npchar.sex != "woman")
			{
				dialog.text = "Hm... Oui, j'ai vu un homme avec cet objet il y a plusieurs heures. Il se promenait dans les rues. C'était un outil intéressant.";
				link.l1 = "Comment avait-il l'air et où se dirigeait-il ? J'ai vraiment besoin de quelque chose comme ça.";
				link.l1.go = "Device_Common";
			}
			else
			{
				dialog.text = "Non, je n'ai rien vu de tel.";
				link.l1 = "Je vois. Je vais continuer à demander alors.";
				link.l1.go = "exit";
			}
		break;
		
		//=================== ноды квеста священника. поиск грабителей (квест №2)==================
		case "Citiz_GenQuest_Church_2_1":
			if(rand(3) != 1)
			{
				dialog.text = LinkRandPhrase("Non, je ne sais rien à ce sujet.","Non, je devrais y aller.","Je ne sais rien.");
					link.l1 = LinkRandPhrase("Bien, merci.","Je vois, merci.","D'accord, excusez-moi.");
				link.l1.go = "exit";
			}
			else
			{
				dialog.text = LinkRandPhrase("Je ne sais rien à ce sujet, mais vous pouvez essayer de demander aux habitués de la taverne, ils vous en diront certainement plus.","Je ne peux rien te dire, demande à quelqu'un à la taverne.");
				link.l1 = "Merci pour cela.";
				link.l1.go = "exit";
			}
			
			NPChar.GenQuest.ChurchQuest_2.AskedPeople = true;
		break;		
		
		//-------------------------------горожанин-пассажир----------------------------------------------
		case "passenger":
			if (hrand(19) > 9) SetPassengerParameter("Townpassenger", false);
			else SetPassengerParameter("Townpassenger", true);
			if (!CheckAttribute(pchar, "GenQuest.Townpassenger.Enemycity"))
			{
				dialog.text = "Capitaine, j'ai besoin d'aller à la colonie nommée "+XI_ConvertString("Colonie"+pchar.GenQuest.Townpassenger.City)+", dès que possible, c'est sur "+XI_ConvertString(GetIslandByCityName(pchar.GenQuest.Townpassenger.City)+"Ça")+", dans "+FindRussianDaysString(sti(pchar.GenQuest.Townpassenger.DaysQty))+". Votre navire a l'air solide comparé à la majorité de ces petites embarcations qui naviguent ici. Je peux vous payer "+FindRussianMoneyString(sti(pchar.GenQuest.Townpassenger.Money))+"Que dis-tu ?";
			}
			else
			{
				dialog.text = "Capitaine, il me faut aller à la colonie "+XI_ConvertString("Colony"+pchar.GenQuest.Townpassenger.City)+", c'est sur un "+XI_ConvertString(GetIslandByCityName(pchar.GenQuest.Townpassenger.City)+"Voc")+", dans un "+FindRussianDaysString(sti(pchar.GenQuest.Townpassenger.DaysQty))+"Je sais que cela semble extrêmement risqué, mais peut-être "+FindRussianDublonString(sti(pchar.GenQuest.Townpassenger.Money))+" serait un bon coup de pouce pour vous ?";
			}
			link.l1 = "Hm. Je me dirige également par ici, donc je suis prêt à vous prendre à bord à ces conditions.";
			link.l1.go = "passenger_1";
			link.l2 = "Je suis désolé,  "+GetAddress_FormToNPC(NPChar)+", mais je navigue dans une direction différente. Je ne peux pas vous aider.";
			link.l2.go = "passenger_exit";
		break;
		
		case "passenger_exit":
			dialog.text = "Dommage. Eh bien, j'attendrai un autre navire. Adieu.";
			link.l1 = "À bientôt.";
			link.l1.go = "exit";
			DeleteAttribute(pchar, "GenQuest.Townpassenger");
		break;
		
		case "passenger_1":
			dialog.text = "Parfait, parce que je suis fatigué d'attendre. Vous recevrez votre paiement quand nous y serons.";
			link.l1 = "Va à mon navire, "+GetAddress_FormToNPC(NPChar)+"  Nous partons bientôt.";
			link.l1.go = "passenger_2";
		break;
		
		case "passenger_2":
			DialogExit();
			pchar.GenQuest.Townpassenger.id = npchar.id;
			LAi_SetImmortal(npchar, true);
			DeleteAttribute(npchar, "LifeDay");
			LAi_RemoveLoginTime(npchar);
			DeleteAttribute(npchar, "CityType");//удалить признак фантома, иначе - пустые города
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1_back", "none", "", "", "", 20.0);
			AddPassenger(pchar, npchar, false);
			SetCharacterRemovable(npchar, false);
			sTitle = npchar.index+"Citizpassenger";

// LDH 13Sep17 - do not add to an existing Citizpassenger record -->
// "Rename" the quest record by copying it to a new name and deleting the old record
			if (CheckAttribute(pchar, "questinfo."+sTitle))
			{
				string sTempLDH = frand(1);
				sTempLDH = strcut(sTempLDH, 2, 5);    // 4 random digits
				string sTitle1 = sTitle+sTempLDH;

				aref arTo, arFrom;
				makearef(arFrom, pchar.questinfo.(sTitle));
				makearef(arTo,   pchar.questinfo.(sTitle1));
				CopyAttributes(arTo, arFrom);
				pchar.questinfo.(sTitle1) = "";

				DeleteAttribute(pchar, "questinfo."+sTitle);

				Trace("Duplicate Citizpassenger record "+sTitle+" copied to "+sTitle1+" **");
			}
// <--

			AddQuestRecordEx(sTitle, "Citizpassenger", "1");
			AddQuestUserDataForTitle(sTitle, "sType", "citizen");
			AddQuestUserDataForTitle(sTitle, "sName", GetFullName(npchar));
			sTemp = XI_ConvertString("Colony" +pchar.GenQuest.Townpassenger.City) + ", which is on " + XI_ConvertString(GetIslandByCityName(pchar.GenQuest.Townpassenger.City)+"Voc")+"."; // belamour gen
			AddQuestUserDataForTitle(sTitle, "sCity", sTemp);
			AddQuestUserData(sTitle, "sName", GetFullName(npchar));
			AddQuestUserData(sTitle, "sCity", sTemp);
			AddQuestUserData(sTitle, "sDays", FindRussianDaysString(sti(pchar.GenQuest.Townpassenger.DaysQty)));
			AddQuestUserData(sTitle, "sSex", GetSexPhrase("",""));
            if (!CheckAttribute(pchar, "GenQuest.Townpassenger.Enemycity")) AddQuestUserData(sTitle, "sMoney", FindRussianMoneyString(sti(pchar.GenQuest.Townpassenger.Money)));
			else AddQuestUserData(sTitle, "sMoney", FindRussianDublonString(sti(pchar.GenQuest.Townpassenger.Money)));
			pchar.quest.Townpassenger.win_condition.l1 = "location";
			pchar.quest.Townpassenger.win_condition.l1.location = pchar.GenQuest.Townpassenger.City+"_town";
			pchar.quest.Townpassenger.function = "Townpassenger_complete";
			SetFunctionTimerCondition("Townpassenger_Over", 0, 0, sti(pchar.GenQuest.Townpassenger.DaysQty), false);
		break;
		
		case "passenger_3":
			pchar.quest.Townpassenger_Over.over = "yes"; //снять таймер
			dialog.text = "Nous y voilà, excellent ! Ce voyage sur votre navire fut fort satisfaisant. Mes remerciements. Prenez votre argent, monsieur.";
			link.l1 = "Bonne chance, "+GetAddress_FormToNPC(NPChar)+"Adieu, matelot.";
			link.l1.go = "passenger_4";
		break;
		
		case "passenger_4":
			chrDisableReloadToLocation = false;//открыть локацию
			DialogExit();
			npchar.lifeday = 0;
			RemovePassenger(Pchar, npchar);
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload4_back", "none", "", "", "", 20.0);
			ChangeCharacterComplexReputation(pchar, "nobility", 1);
			ChangeCharacterComplexReputation(pchar, "fame", 1);
			OfficersReaction("good");				
			AddCharacterExpToSkill(pchar, "Sailing", 80);
			AddCharacterExpToSkill(pchar, "Leadership", 20);
			if (CheckAttribute(pchar, "GenQuest.Townpassenger.Enemycity"))
			{
				AddCharacterExpToSkill(pchar, "Sneak", 50);
				TakeNItems(pchar, "gold_dublon", sti(pchar.GenQuest.Townpassenger.Money));
			}
			else AddMoneyToCharacter(pchar, sti(pchar.GenQuest.Townpassenger.Money));
			sTitle = npchar.index+"Citizpassenger";
			AddQuestRecordEx(sTitle, "Citizpassenger", "3");
			CloseQuestHeader(sTitle);
			DeleteAttribute(Pchar, "GenQuest.Townpassenger");
		break;
//<-- горожанин-пассажир
		
		//замечение по обнажённому оружию
		case "CitizenNotBlade":
			if (loadedLocation.type == "town")
			{
				dialog.text = NPCharSexPhrase(NPChar,"Ecoutez, en tant que citoyen de cette ville je vous demande de rengainer votre lame.","Ecoutez, en tant que citoyen de cette ville, je vous demande de rengainer votre lame.");
				link.l1 = LinkRandPhrase("Bien.","Comme vous le souhaitez.","Comme vous dites...");
			}
			else
			{
				dialog.text = NPCharSexPhrase(NPChar,"Sois prudent en courant avec une arme. Je pourrais devenir nerveux...","Je n'aime pas quand un étranger se promène devant moi avec une épée nue...");
				link.l1 = RandPhraseSimple("Je l'ai.","Ne t'inquiète pas.");
			}
			link.l1.go = "exit";
			NextDiag.TempNode = "First Time";
		break;

		case "pirate_fight":
			DialogExit();
			SetNationRelation2MainCharacter(sti(npchar.nation), RELATION_ENEMY);
			LAi_group_Attack(NPChar, Pchar);
			DoQuestFunctionDelay("TownPirate_battle", 0.5);
		break;

	}
}
