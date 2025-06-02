//Jason общий диалог мещанок
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
    string sTemp, sCity;
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
				    dialog.text = RandPhraseSimple("On dit que vous possédez cette ville, "+GetSexPhrase("monsieur","mademoiselle")+".","Quel agréable rencontre ! Quel agréable rencontre ! Le gouverneur lui-même me parle !");
					link.l1 = RandPhraseSimple("J'ai changé d'avis. Bonne chance !","Je me promène juste en ville. Adieu.");
					link.l1.go = "exit";
					link.l2 = RandPhraseSimple("J'ai une question pour vous.","J'ai besoin de quelques informations.");
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
				    dialog.text = RandPhraseSimple("Que voulez-vous ? Circulez.","Arrête de bloquer mon chemin, va-t'en.");
					link.l1 = RandPhraseSimple("Que fais-tu ?","Calme-toi. Ou je le ferai moi-même.");
					link.l1.go = "exit";
					link.l2 = RandPhraseSimple("Je veux te demander.","Juste une minute de votre attention, s'il vous plaît. Une question.");
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
			}
            if(NPChar.quest.meeting == "0")
			{
				NPChar.quest.meeting = "1";
				dialog.Text = NPCharRepPhrase(npchar,LinkRandPhrase("Je suis","Mon nom est ","Vous pouvez m'appeler ")+GetFullName(npchar)+LinkRandPhrase(" Que veux-tu ?","Je ne vous ai jamais vu auparavant "+", qui es-tu ?","Qui es-tu et que veux-tu de moi ?"),LinkRandPhrase("Salutations, "+GetAddress_Form(NPChar)+". Mon nom est "+GetFullName(npchar)+" Et comment vous appelez-vous ?","Bonjour "+GetAddress_Form(NPChar)+"! Je suis "+GetFullName(npchar)+"Puis-je connaître votre nom ?","Oui, "+GetAddress_Form(NPChar)+". Que veux-tu ? Et d'ailleurs, mon nom est "+GetFullName(npchar)+" Et comment vous appelez-vous ?"));
				Link.l1 = pcharrepphrase(LinkRandPhrase("Que le diable m'emporte !","Sacrebleu ! ","Que le diable t'emporte ! ")+"Oui, je suis le capitaine "+GetFullName(Pchar)+LinkRandPhrase(", n'as-tu jamais entendu parler de moi, salopard ?"," et "+GetSexPhrase("le pirate le plus célèbre","la plus fameuse fille-pirate")+" dans la mer !"," et maudit soit-je si j'ai tort !"),LinkRandPhrase("Je suis "+GetFullName(Pchar)+", capitaine.","Mon nom est "+GetFullName(Pchar)+".","Tu peux m'appeler capitaine "+GetFullName(Pchar)+"."));
				Link.l1.go = "Meeting";
				
				//==> прибыла инспекция на Святом Милосердии
				if (CheckAttribute(pchar, "questTemp.SantaMisericordia.ColonyZapret") && pchar.location == pchar.questTemp.SantaMisericordia.ColonyZapret + "_town")
				{
					dialog.Text = LinkRandPhrase(LinkRandPhrase("La ville entière est sur les nerfs - don Fernando de Alamida, l'inspecteur royal, est arrivé. Vous savez, j'ai vu beaucoup de choses ici, mais ça... Ce n'est pas le chagrin qui change les gens, mais comment ils y font face. On dit qu'il est devenu un homme différent après la mort de son père. Maintenant, vous ne trouverez pas un serviteur de la Couronne plus incorruptible et... impitoyable dans tout l'Archipel.","Regardez juste le 'Sainte Miséricorde' ! Ils disent que le roi lui-même a ordonné sa construction selon des plans spéciaux. Et remarquez - pas une éraflure. Comme si la Vierge Marie elle-même la protégeait. Bien que j'aie entendu des rumeurs... peut-être que ce n'est pas la Vierge du tout.","Tu sais combien de fois ils ont essayé de tuer don Fernando ? Douze attaques en pleine mer - et c'est juste l'année dernière ! Eh bien, avec un équipage aussi loyal et entraîné, et sous la protection du Seigneur - il survivra aussi à la treizième !"),LinkRandPhrase("As-tu entendu ? Don Fernando de Alamida est arrivé dans notre ville, et on dit qu'il est quelque part dans les rues en ce moment. J'aimerais bien le voir de mes propres yeux...","Un homme compliqué, ce don Fernando. Certains disent qu'il est un sauveur, purifiant la Mère Patrie de la vermine. D'autres murmurent que quelque chose s'est brisé en lui après la mort de son père et que bientôt nous pleurerons tous. Mais je vais te dire ceci : ne le crains pas. Crains ceux qui ont fait de lui ce qu'il est.","Un homme si beau, ce don Fernando ! Mais tu sais ce qui est étrange ? C'est comme s'il ne remarquait personne. Tout devoir et service. J'ai entendu dire qu'il y avait une fille... mais après avoir rencontré un certain prêtre, il a complètement rejeté les plaisirs mondains. Comme s'il avait fait un vœu."),RandPhraseSimple(RandPhraseSimple("Maudit inspecteur ! Tant qu'il est là, la ville est comme morte. Pas de commerce, pas de divertissement. Même respirer, on dirait, doit se faire plus discrètement. Et tu sais ce qui est le plus effrayant ? C'est pareil dans chaque port. Comme une horloge. Sa Majesté Royale n'aurait pas pu inventer délibérément cette torture pour nous tous !","Don Fernando a de nouveau visité l'orphelinat. Il fait des dons généreux, prie pendant des heures. Un homme si digne devrait être donné en exemple à ces maudits détourneurs de fonds !"),RandPhraseSimple("Ha ! 'Saint' Fernando a encore fermé tous les bordels. Bah, peu importe, il partira bientôt et ils rouvriront aussitôt.","L'inspect... l'inspecteur est arrivé, voilà quoi ! Don Fernando de Almeyda, ou, comment qu'il s'appelle, Alamida ! Tellement important que le gouverneur lui-même marche sur des oeufs autour de lui. Ils disent qu'il te regarde dans les yeux et voit tous tes péchés tout de suite. Terrifiant !")));
					link.l1 = "...";
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
				link.l1 = "Je voulais juste parler de cette ville.";
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
						link.l3 = RandPhraseSimple("Je veux discuter de questions financières.","A propos des finances...");
						link.l3.go = "LoanForAll";//(перессылка в кредитный генератор)
					}
				}
				//Jason --> генератор Неудачливый вор
				if (CheckAttribute(pchar, "GenQuest.Device.Shipyarder") && NPChar.location == pchar.GenQuest.Device.Shipyarder.City + "_town" && pchar.GenQuest.Device.Shipyarder == "begin" && !CheckAttribute(npchar, "quest.Device"))
				{
					link.l16 = "Ecoutez, j'espère que vous pouvez m'aider. Je veux acheter un "+pchar.GenQuest.Device.Shipyarder.Type+", et on m'a dit que cette chose a été vendue dans votre ville. Eh bien, quelqu'un la vendait sur le marché de rue. Savez-vous quelque chose à ce sujet ?";
					link.l16.go = "Device_Citizen";
				}
				// <-- генератор Неудачливый вор
				
				// Квестовый генератор священника. Квест №2. Warship -->
				if(CheckAttribute(PChar, "GenQuest.ChurchQuest_2.AskPeople") && !CheckAttribute(NPChar, "GenQuest.ChurchQuest_2.AskedPeople") && NPChar.location == PChar.GenQuest.ChurchQuest_2.QuestTown + "_town")
	            {
					link.l5 = LinkRandPhrase("Sais-tu ","Es-tu au courant ","As-tu entendu ")+"que l'église locale a récemment été cambriolée ?");
					link.l5.go = "Citiz_GenQuest_Church_2_1";
				}
				// <-- Квестовый генератор священника. Квест №2.
				
                dialog.Text = NPCharRepPhrase(npchar,PCharRepPhrase(LinkRandPhrase("Ah, c'est toi "+GetFullName(Pchar)+" "+GetSexPhrase(" - vieux camarade !"," - jolie ! ")+"","Je suis ravi de te voir, "+GetSexPhrase("vieux ami !","jolie ! ")+" "+Pchar.name,"Oh, c'est le "+GetSexPhrase("le capitaine lui-même","la capitaine elle-même")+" "+GetFullName(Pchar))+RandPhraseSimple("Je pensais que tu étais mort !",". Et peut-être "+GetSexPhrase("ivre comme toujours.","un peu ivre."))+LinkRandPhrase("Allez-y, que voulez-vous ?"," Qu'est-ce que cette fois-ci ?"," Tu me déranges encore?"),LinkRandPhrase(TimeGreeting()+", capitaine ","Bonne journée à vous, "+GetAddress_Form(NPChar)+" ","Salutation, capitaine ")+GetFullName(Pchar)+LinkRandPhrase(". Comment puis-je vous aider à "+GetSexPhrase("un homme si digne","une fille si digne")+", comme toi ?","Pourquoi es-tu ici ?","Que veux-tu savoir cette fois-ci ?")),PCharRepPhrase(LinkRandPhrase("Bonjour, capitaine ","Salutations, ah, c'est vous "+GetAddress_Form(NPChar)+" ","Ah, capitaine ")+GetFullName(Pchar)+LinkRandPhrase(", je pensais que nous ne nous reverrions jamais, et",", je ne dirai pas que je suis heureux de te voir mais",", je vois que tu es toujours vivant, quel dommage et")+LinkRandPhrase(" que voulez-vous?"," pourquoi es-tu ici ?"," comment puis-je vous aider?"),LinkRandPhrase(TimeGreeting()+", capitaine "+GetFullName(Pchar)+"Comment puis-je vous aider ?","Oh, c'est le capitaine "+GetFullName(Pchar)+"! Comment puis-je vous aider ?","Salutations, "+GetAddress_Form(NPChar)+" "+Pchar.lastname+"Voulez-vous quelque chose ?")));  
	   			link.l6 = PCharRepPhrase(RandPhraseSimple("Tes oreilles te trompent. Je dois partir.","Non, ce n'est rien, j'étais en route pour la taverne."),RandPhraseSimple("Très bien, peu importe. Bonne chance !","Juste se promener dans la ville. Adieu."));
				link.l6.go = "exit";
			}
			NextDiag.TempNode = "First time";
		break;
		
		case "ShipLetters_7":
			dialog.text = "Des questions ?";
			link.l1 = "Le nom sur ces papiers vous dit-il quelque chose ?";
			link.l1.go = "ShipLetters_8";
		break;
		
		case "ShipLetters_8":
			dialog.text = LinkRandPhrase("Je m'en fous d'un papier inconnu et je ne sais pas lire. Va voir l'usurier, on dit qu'il sait lire ces lettres du diable.","Je ne sais pas de quoi vous parlez, demandez aux autres citoyens de la ville, capitaine"+GetFullName(Pchar)+".","Je ne sais même pas comment vous aider, capitaine "+GetFullName(Pchar)+". Essaie de parler avec l'usurier, il pourrait savoir.");
			link.l1 = "Je suivrai ton conseil avec grand plaisir !";
			link.l1.go = "exit";
		break;
		
		case "Meeting":
		    dialog.Text = NPCharRepPhrase(npchar,LinkRandPhrase("Ne serais-tu pas en train de mentir, capitaine "+GetFullName(Pchar)+"?","Et alors"+PChar.name+"?","Je me souviendrai de toi, "+GetFullName(Pchar)+".")+" Maintenant, dis-moi ce que tu veux ?",LinkRandPhrase("Enchanté de vous rencontrer, capitaine "+PChar.name,"Ravi de notre rencontre,"+GetAddress_Form(NPChar)+" "+PChar.lastname,"C'est un plaisir, capitaine "+PChar.name)+". Mais je doute que tu voulais seulement connaître mon nom, n'est-ce pas ?");
            link.l1 = PCharRepPhrase("Je veux juste demander quelque chose à propos de ce trou que vous appelez 'la ville'.","Je veux te demander quelque chose à propos de cette ville.");
			link.l1.go = "new question";
            Link.l2 = RandPhraseSimple("J'ai une question pour vous.","J'ai besoin de renseignements.");
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
					link.l3 = RandPhraseSimple("Je veux discuter de questions financières.","À propos des finances...");
					link.l3.go = "LoanForAll";//(перессылка в кредитный генератор)
				}
			}
			
			//Jason --> генератор Неудачливый вор
			if (CheckAttribute(pchar, "GenQuest.Device.Shipyarder") && NPChar.location == pchar.GenQuest.Device.Shipyarder.City + "_town" && pchar.GenQuest.Device.Shipyarder == "begin" && !CheckAttribute(npchar, "quest.Device"))
			{
   				link.l16 = "Ecoute, j'espère que tu pourras m'aider. Je veux acheter un "+pchar.GenQuest.Device.Shipyarder.Type+" et on m'a dit que cette chose a été vendue dans votre ville. Eh bien, quelqu'un la vendait dans les rues. Savez-vous quelque chose à ce sujet ?";
				link.l16.go = "Device_Citizen";
			}
			// <-- генератор Неудачливый вор

			// Квестовый генератор священника. Квест №2. Warship -->
			if(CheckAttribute(PChar, "GenQuest.ChurchQuest_2.AskPeople") && !CheckAttribute(NPChar, "GenQuest.ChurchQuest_2.AskedPeople") && NPChar.location == PChar.GenQuest.ChurchQuest_2.QuestTown + "_town")
	        {
				link.l5 = RandPhraseSimple("Sais-tu ","Es-tu au courant ","As-tu entendu ")+" que l'église locale a été récemment cambriolée ?");
				link.l5.go = "Citiz_GenQuest_Church_2_1";
			}
			// <-- Квестовый генератор священника. Квест №2.
			Link.l6 = PCharRepPhrase(RandPhraseSimple("Tes oreilles te trompent. Je dois y aller.","Non, ce n'est rien, j'étais en route pour la taverne."),RandPhraseSimple("Eh bien, ce n'est rien, Bonne chance !","Je me promène juste dans la ville. Adieu."));
			Link.l6.go = "exit";
		break;
		
		case "new question":
            dialog.text = NPCharRepPhrase(npchar,PCharRepPhrase(LinkRandPhrase("Oh, et je suis heureux de te voir comme je suis heureux pour une bouteille, demande ce que tu veux.","Tu aimes parler, capitaine ? Moi aussi... Surtout avec une tasse de rhum.","Oui, "+PChar.name+"?"),RandPhraseSimple("Que veux-tu d'autre ?","Je le prends, capitaine "+PChar.name+", que tu aimes bavarder ?")),PCharRepPhrase(LinkRandPhrase("Que veux-tu d'autre "+GetAddress_Form(NPChar)+"?","Je vous écoute, capitaine.","Je dois partir, alors demandez-moi vite, capitaine."),LinkRandPhrase("Je suis toujours ravi d'une compagnie agréable, "+GetAddress_Form(NPChar)+" "+PChar.lastname+"Parle.","Oui, "+GetAddress_Form(NPChar)+"?","Vous aimez parler, capitaine ? Moi aussi... ")));
			link.l1 = LinkRandPhrase("Quelles rumeurs circulent en ville ?","Des nouvelles de ces terres ?","Comment va la vie à terre ?");
			link.l1.go = "rumours_towngirl";
			link.l2 = LinkRandPhrase("Peux-tu me montrer le chemin ?","Je ne trouve pas le chemin vers un endroit...","Aide-moi à atteindre un endroit...");
			link.l2.go = "town";  //(перессылка в файл города)
			link.l3 = RandPhraseSimple("Je veux savoir ce que les gens disent d'une personne.","Sais-tu ce que les gens disent d'une personne ?");
			link.l3.go = "info"; //(перессылка в файл города)
			link.l4 = RandPhraseSimple("Je veux en savoir plus sur les habitants.","Peux-tu me dire quelque chose sur les gens du coin ?");
			link.l4.go = "RumourAboutOwners";
			link.l5 = PCharRepPhrase(RandPhraseSimple("Tes oreilles te trompent. Je dois y aller.","Non, ce n'est rien, j'étais en route pour la taverne."),RandPhraseSimple("Eh bien, ce n'est rien. Bonne chance !","Je me promène simplement en ville. Adieu."));
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
				link.l2 = "Voulez-vous en savoir plus sur le propriétaire de la taverne locale.";
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
			link.l9 = "Ce n'est rien. Oublie ça.";
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
           dialog.text = "Hm, "+pchar.GenQuest.Device.Shipyarder.Type+"? Jamais entendu parler... Je vis ici depuis longtemps et je n'ai jamais vu quelque chose de semblable.";
			link.l1 = "Eh bien, c'est un outil de construction navale, "+pchar.GenQuest.Device.Shipyarder.Describe+"Quelqu'un a-t-il vendu quelque chose de ce genre en ville ? Ou peut-être l'a-t-il transporté et vous l'avez remarqué ?";
			link.l1.go = "Device_Citizen_1";
			npchar.quest.Device = "true";
		break;
		
		case "Device_Citizen_1":
			if (sti(pchar.GenQuest.Device.Shipyarder.Chance1) > 3 && sti(pchar.GenQuest.Device.Shipyarder.Chance1) < 6 && npchar.sex != "woman")
			{
				dialog.text = "Hm... Oui, j'ai vu un homme avec cet objet il y a plusieurs heures. Il se promenait dans les rues. C'était un outil intéressant.";
				link.l1 = "Quelle allure avait-il et où se dirigeait-il ? J'ai vraiment besoin de quelque chose de ce genre.";
				link.l1.go = "Device_Common";
			}
			else
			{
				dialog.text = "Non, je n'ai rien vu de tel.";
				link.l1 = "Je vois. Je continuerai à demander alors.";
				link.l1.go = "exit";
			}
		break;
		
		//=================== ноды квеста священника. поиск грабителей (квест №2)==================
		case "Citiz_GenQuest_Church_2_1":
			if(rand(3) != 1)
			{
				dialog.text = LinkRandPhrase("Non, je ne sais rien à ce sujet.","Non, je devrais y aller.","Je n'en sais rien.");
					link.l1 = LinkRandPhrase("Bien, merci.","Je vois, merci.","D'accord, excusez-moi.");
				link.l1.go = "exit";
			}
			else
			{
				dialog.text = RandPhraseSimple("Je n'en sais rien à ce sujet, mais tu pourrais essayer de demander à certains habitués de la taverne, ils te diront sûrement plus.","Je ne peux rien vous dire, demandez à quelqu'un à la taverne.");
				link.l1 = "Merci pour cela.";
				link.l1.go = "exit";
			}
			NPChar.GenQuest.ChurchQuest_2.AskedPeople = true;
		break;		
		
		//замечение по обнажённому оружию
		case "CitizenNotBlade":
			if (loadedLocation.type == "town")
			{
				dialog.text = NPCharSexPhrase(NPChar,"Ecoutez, en tant que citoyen de cette ville je vous demande de rengainer votre lame.","Ecoutez, en tant que citoyen de cette ville je vous demande de rengainer votre lame.");
				link.l1 = LinkRandPhrase("Bien.","Comme vous le souhaitez.","Comme vous le dites...");
			}
			else
			{
				dialog.text = NPCharSexPhrase(NPChar,"Fais attention en courant avec une arme. Ça peut me rendre nerveux...","Je n'aime pas quand un inconnu marche devant moi avec une arme dégainée. Ça me fait peur...");
				link.l1 = RandPhraseSimple("Je l'ai.","Ne t'inquiète pas.");
			}
			link.l1.go = "exit";
			NextDiag.TempNode = "First Time";
		break;

	}
}
