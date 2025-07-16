// boal 25/04/04 общий диалог горожан
#include "DIALOGS\%language%\Rumours\Common_rumours.c"  //homo 25/06/06
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
    ProcessCommonDialogRumors(NPChar, Link, NextDiag);//homo 16/06/06
    int iTest, iTemp;
    iTest = FindColony(NPChar.City); // город
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
            /*if (GetNationRelation2MainCharacter(sti(NPChar.nation)) == RELATION_ENEMY && sti(NPChar.nation) != PIRATE)
			{
				dialog.text = RandPhraseSimple("Un espion ? Gardes !","Alarme ! Il y a un intrus !");
				link.l1 = "Taisez-vous. Je m'en vais.";
				link.l1.go = "fight";
				break;
			}*/
			
			if (sti(NPChar.nation) == PIRATE)
			{
				if (sti(rColony.HeroOwn) == true) // наш горожанин
				{
				    dialog.text = RandPhraseSimple("On dit que vous êtes celui qui gouverne cette ville, "+GetSexPhrase("monsieur","mademoiselle")+".","Quelle agréable rencontre, le dirigeant de la ville m'a interpellé en me posant une question.");
					link.l1 = RandPhraseSimple("J'ai changé d'avis.","Je suis simplement en train d'explorer cette ville. Au revoir.");
					link.l1.go = "exit";
					link.l2 = RandPhraseSimple("J'ai une question pour vous.","J'ai besoin d'informations."); 
					link.l2.go = "quests";//(перессылка в файл города)
					if (CheckAttribute(pchar, "GenQuest.Loan.FindCitizen") && !CheckAttribute(pchar, "GenQuest.Loan.FindCitizenDone") && !CheckAttribute(pchar, "GenQuest.Loan.FindCitizenFalied"))
		            {
		                if (Characters[sti(pchar.GenQuest.Loan.FindCitizenIdx)].id == Npchar.id)
		                {
							link.l3 = RandPhraseSimple("Je veux discuter affaires.","Concernant les finances...");
							link.l3.go = "LoanForAll";//(перессылка в кредитный генератор)
						}
					}
					break;
				}
				else
				{ // пираты, не наши
				    dialog.text = RandPhraseSimple("Que voulez-vous ? Passez votre chemin.","Ne restez pas dans le chemin, allez vous en !");
					link.l1 = RandPhraseSimple("Eh, arrêtez d'aboyer, voulez-vous ?","Calmez-vous, ou vous pourriez le regretter !");
					link.l1.go = "exit";
					link.l2 = RandPhraseSimple("J'ai une question pour vous.","Un moment de votre attention, s'il vous plaît. J'ai une question.");
					link.l2.go = "quests";//(перессылка в файл города)
					if (CheckAttribute(pchar, "GenQuest.Loan.FindCitizen") && !CheckAttribute(pchar, "GenQuest.Loan.FindCitizenDone") && !CheckAttribute(pchar, "GenQuest.Loan.FindCitizenFalied"))
		            {
		                if (Characters[sti(pchar.GenQuest.Loan.FindCitizenIdx)].id == Npchar.id)
		                {
							link.l3 = RandPhraseSimple("Je veux discuter affaires.","Concernant les finances...");
							link.l3.go = "LoanForAll";//(перессылка в кредитный генератор)
						}
					}
					break;
				}
			}
            if(NPChar.quest.meeting == "0")
			{
				NPChar.quest.meeting = "1";

                // homo 05/08/06
				dialog.Text =NPCharRepPhrase(npchar,
								LinkRandPhrase("Mon nom est ","Mon nom est ","Vous pouvez m'appeler ")
								+GetFullName(npchar)
								+LinkRandPhrase(". De quoi avez-vous besoin ?",". Je ne "
								+NPCharSexPhrase(NPChar,"vous ai jamais vu ici auparavant","vous ai jamais vu là-bas auparavant")
								+", qui êtes-vous?",". Qui êtes-vous et que voulez-vous de moi?"),

								LinkRandPhrase("Salutations, "+GetAddress_Form(NPChar)+". Mon nom est "+GetFullName(npchar)+". Quel est le vôtre ?",
								"Bonjour, "+GetAddress_Form(NPChar)+"! Je suis "+GetFullName(npchar)+". Puis-je avoir votre nom ?",
								"Oui, "+GetAddress_Form(NPChar)+". Que voulez-vous ? Au fait, mon nom est "+GetFullName(npchar)+". Et vous êtes ?"));

				Link.l1 = pcharrepphrase(
								LinkRandPhrase("Par le tonnerre ! ","par les cloches de l'enfer ! ","Mauvaise peste sur vous ! ")+"Oui, je suis le Capitaine "+GetFullName(Pchar)+LinkRandPhrase(", vous n'avez vraiment pas entendu parler de moi"+NPCharSexPhrase(NPChar,", canaille ?","?")," et "+GetSexPhrase("le pirate le plus notoire","la femme pirate la plus notoire")+" dans ces eaux ! "," et que je brûle en Enfer si ce n'est pas vrai !"),
								LinkRandPhrase("Je suis le Capitaine"+GetFullName(Pchar)+".","Mon nom est "+GetFullName(Pchar)+".","Vous pouvez m'appeler Capitaine "+GetFullName(Pchar)));

                //LinkRandPhrase("I am Captain" + GetFullName(Pchar) + ".", "My name is " + GetFullName(Pchar) + ".", "You may call me Captain " + GetFullName(Pchar));
				Link.l1.go = "Meeting";
			}
			else
			{
				if(rand(5) == 1 && NPChar.sex == "woman" && !CheckAttribute(NPChar, "CitizenFindItem.NoQuest") && !CheckAttribute(PChar, "GenQuest.CitizenFindItem.StartQuest") && CheckAttribute(NPChar, "City"))
				{
					dialog.Text = "Capitaine, pourriez-vous m'aider, s'il vous plaît ?";
					link.l1 = LinkRandPhrase("Désolé, non. J'ai peu de temps à perdre.","Désolé, je ne peux pas. Trop occupé.","Non, je ne peux pas. J'ai des affaires urgentes qui requièrent mon attention.");
					link.l1.go = "CitizenFindItem_NoQuest";
					link.l2 = LinkRandPhrase("Bien sûr que je peux. Quel est le problème?","Oui, je vais vous aider. Dites m'en plus sur votre affaire.","Parlez-moi davantage de votre affaire...");
					link.l2.go = "CitizenFindItem_1";
					NextDiag.TempNode = "First time";
					break;
				}
				
				if(CheckAttribute(PChar, "GenQuest.CitizenFindItem.CitizenID") && PChar.GenQuest.CitizenFindItem.CitizenID == NPChar.ID && CheckCharacterItem(PChar, "DOjeronRing"))
				{
					dialog.Text = "Oui, Capitaine, je vous écoute.";
					link.l1 = NPChar.name+", j'ai trouvé votre bague de mariage.";
					link.l1.go = "CitizenFindItem_Complete_1";
					break;
				}
			
				link.l1 = PCharRepPhrase("Je veux en savoir plus sur cette ville.","Parlez-moi de cette ville.");
				link.l1.go = "new question";
 				link.l2 = RandPhraseSimple("J'ai une question pour vous.","J'ai besoin d'informations.");
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
						link.l3 = RandPhraseSimple("Je veux discuter affaires.","Concernant les finances...");
						link.l3.go = "LoanForAll";//(перессылка в кредитный генератор)
					}
				}
				// --> квестовый генератор мэра, поиск шпиёна на улице. eddy
				if (CheckAttribute(pchar, "GenQuest.SeekSpy.City") && pchar.location == (npchar.city + "_town"))
	            {
					link.l4 = NPCharSexPhrase(npchar,LinkRandPhrase("Attendez ! Dites-moi qui vous êtes - tout de suite ! Je recherche un espion ennemi à la demande du gouverneur de "+XI_ConvertString("Colony"+characters[GetCharacterIndex(pchar.GenQuest.SeekSpy.MayorId)].city+"Gen")+"!",
					"Halte ! J'agis dans l'intérêt de la ville "+XI_ConvertString("Colony"+characters[GetCharacterIndex(pchar.GenQuest.SeekSpy.MayorId)].city+"Gen")+" par ordre du gouverneur. Je fouille la ville à la recherche d'un agent hostile.",
					"Stop, l'ami ! Le gouverneur local "+characters[GetCharacterIndex(pchar.GenQuest.SeekSpy.MayorId)].lastname+" veut trouver un espion dans la ville."),
					LinkRandPhrase("Attendez, madame ! Dites-moi qui vous êtes - tout de suite ! Je recherche un espion ennemi à la demande du gouverneur de "+XI_ConvertString("Colony"+characters[GetCharacterIndex(pchar.GenQuest.SeekSpy.MayorId)].city+"Gen")+"!",
					"Femme, je dois vous retenir ! J'agis dans l'intérêt de la ville "+XI_ConvertString("Colony"+characters[GetCharacterIndex(pchar.GenQuest.SeekSpy.MayorId)].city+"Gen")+" par ordre du gouverneur. Je fouille la ville à la recherche d'un agent hostile",
					"Ne bougez pas, beauté ! Un gouverneur local "+characters[GetCharacterIndex(pchar.GenQuest.SeekSpy.MayorId)].lastname+" veut trouver un espion dans la ville..."));
					link.l4.go = "SitySpy";
				}
				// <-- квестовый генератор мэра, поиск шпиёна на улице
				
				//Jason --> генератор Неудачливый вор
				if (CheckAttribute(pchar, "GenQuest.Device.Shipyarder") && NPChar.location == pchar.GenQuest.Device.Shipyarder.City + "_town" && pchar.GenQuest.Device.Shipyarder == "begin" && !CheckAttribute(npchar, "quest.Device"))
				{
					link.l16 = "Peut-être pouvez-vous me donner des conseils. Je veux acheter "+pchar.GenQuest.Device.Shipyarder.Type+", et on m'a dit qu'il était vendu dans votre ville. Eh bien, quelqu'un le vendait dans les rues. Savez-vous quelque chose à ce sujet ?";
					link.l16.go = "Device_Citizen";
				}
				// <-- генератор Неудачливый вор
				
				// Квестовый генератор священника. Квест №2. Warship -->
				if(CheckAttribute(PChar, "GenQuest.ChurchQuest_2.AskPeople") && !CheckAttribute(NPChar, "GenQuest.ChurchQuest_2.AskedPeople") && NPChar.location == PChar.GenQuest.ChurchQuest_2.QuestTown + "_town")
	            {
					link.l5 = LinkRandPhrase("Êtes-vous au courant","Saviez-vous","Avez-vous entendu")+" qu'une église locale a été pillée récemment?");
					link.l5.go = "Citiz_GenQuest_Church_2_1";
				}
				// <-- Квестовый генератор священника. Квест №2.
				
                dialog.Text = NPCharRepPhrase(npchar,
						PCharRepPhrase(LinkRandPhrase("Oh, c'est vous, "+GetFullName(Pchar)
						+" "+GetSexPhrase(", vieux scélérat","- dame audacieuse")+"","Heureux de vous revoir, "+GetSexPhrase("vieux camarade","beauté")+" "
						+Pchar.name,"Oh, c'est "+GetSexPhrase("le bon vieux Capitaine","la bonne vieille demoiselle")+" "
						+GetFullName(Pchar))
										+LinkRandPhrase(". Je pensais que vous étiez mort !",". Et, certainement, "+GetSexPhrase("ivre comme d'habitude.","déjà sous le mauvais temps.")+"",". Et, comme je vois, toujours en liberté !")
										+LinkRandPhrase(" Alors, dites ce que vous pensez - de quoi avez-vous besoin ?"," De quoi avez-vous besoin cette fois ?"," Vous me dérangez encore pour rien ?"),
										LinkRandPhrase(TimeGreeting()+", Capitaine ","Bonjour, "+GetAddress_Form(NPChar)+" ","Je vous salue, Capitaine ")+GetFullName(Pchar)
										+LinkRandPhrase(". Qu'est-ce que pourrait bien vouloir "+GetSexPhrase("un si galant gentilhomme","une si fringante dame")+" ? Pourriez-vous éventuellement avoir besoin de quelque chose de ma part ?",". Pourquoi êtes-vous venu ?",". Que voulez-vous savoir cette fois-ci ?")

										),

						PCharRepPhrase(LinkRandPhrase("Bonjour, Capitaine ","Bonjour. Oh, c'est vous "+GetAddress_Form(NPChar)+" ","Oh, Capitaine ")
										+GetFullName(Pchar)
										+LinkRandPhrase(", je pensais"+NPCharSexPhrase(NPChar," "," ")+"que nous ne nous reverrions jamais,",
														 ", je ne peux pas dire que je suis ravi"+NPCharSexPhrase(NPChar," "," ")+"de vous voir, mais",", Je vois, vous êtes toujours en vie. Regrettable. Alors,")
										+LinkRandPhrase(" de quoi avez-vous besoin ?","Pourquoi êtes-vous venu ?"," que puis-je "+NPCharSexPhrase(NPChar,"faire pour vous ?","faire pour vous ?")),
										LinkRandPhrase(TimeGreeting()+", Capitaine "+GetFullName(Pchar)+". En quoi puis-je vous aider ?",
										"Oh, si ce n'est pas"+GetSexPhrase("","")+" Capitaine "+GetFullName(Pchar)+" ! Qu'aimeriez-vous savoir cette fois-ci ?",
										"Bonjour, "+GetAddress_Form(NPChar)+" "+Pchar.lastname+". Vouliez-vous quelque chose ?"))
										);                         
	   			link.l6 = PCharRepPhrase(RandPhraseSimple("Non, vous entendez des choses. Je vais y aller maintenant.","Non, rien - je me rendais juste"+GetSexPhrase("","")+" à la taverne."),
										RandPhraseSimple("Non, rien. Bonne chance à vous !","Juste en train de regarder autour. Au revoir."));
				link.l6.go = "exit";
			}
			NextDiag.TempNode = "First time";
		break;
		
		case "ShipLetters_7":
			dialog.text = "Quelles questions ?";
			link.l1 = "Le nom qui figure dans ces documents vous dit-il quelque chose ?";
			link.l1.go = "ShipLetters_8";
		break;
		
		case "ShipLetters_8":
			dialog.text = LinkRandPhrase("Je me soucie pas des papiers inconnus. De plus, je ne sais pas lire. Allez voir l'usurier, ce diable sait sûrement lire et écrire.",
										"Je n'ai aucune idée de ce dont vous parlez. Demandez aux habitants de la ville, Capitaine "+GetFullName(Pchar)+".",
										"Je n'ai vraiment aucune idée de comment vous aider, Capitaine "+GetFullName(Pchar)+". Essayez de demander à l'usurier - peut-être qu'il pourrait savoir.");
			link.l1 = "Je suivrai volontiers votre conseil !";
			link.l1.go = "exit";
		break;
		
		case "Meeting":
		    dialog.Text = NPCharRepPhrase(npchar,LinkRandPhrase("Mais ne mentez-vous pas, Capitaine "+GetFullName(Pchar)+" ?",
																	"Et alors, "+PChar.name+" ?",
																	"Je me souviendrai de vous, "+GetFullName(Pchar)+".")
																	 +"Et maintenant, de quoi avez-vous besoin ?",
												   LinkRandPhrase("Un plaisir de vous rencontrer, Capitaine "+PChar.name,
												   					"Heureux"+NPCharSexPhrase(NPChar," "," ")+" de vous rencontrer, "+GetAddress_Form(NPChar)+" "+PChar.lastname,
																	 "Ravi de vous rencontrer, Capitaine "+PChar.name)+". Mais, je suppose, vous êtes venu ici pour plus que simplement apprendre mon nom ?");

            link.l1 = PCharRepPhrase("Je voulais"+GetSexPhrase("","")+" savoir quelque chose sur ce trou que vous appelez la ville !","Je voulais"+GetSexPhrase("","")+" savoir quelque chose sur cette ville.");
			link.l1.go = "new question";
            Link.l2 = RandPhraseSimple("J'ai une question pour vous.","J'ai besoin d'informations.");
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
					link.l3 = RandPhraseSimple("Je veux discuter affaires.","Concernant les finances...");
					link.l3.go = "LoanForAll";//(перессылка в кредитный генератор)
				}
			}
			
			//Jason --> генератор Неудачливый вор
			if (CheckAttribute(pchar, "GenQuest.Device.Shipyarder") && NPChar.location == pchar.GenQuest.Device.Shipyarder.City + "_town" && pchar.GenQuest.Device.Shipyarder == "begin" && !CheckAttribute(npchar, "quest.Device"))
			{
   				link.l16 = "Peut-être pouvez-vous me donner des conseils. Je veux acheter "+pchar.GenQuest.Device.Shipyarder.Type+", et on m'a dit qu'il était vendu dans votre ville. Eh bien, quelqu'un le vendait dans les rues. Savez-vous quelque chose à ce sujet ?";
				link.l16.go = "Device_Citizen";
			}
			// <-- генератор Неудачливый вор
			
			// --> квестовый генератор мэра, поиск шпиёна на улице. eddy
			if (CheckAttribute(pchar, "GenQuest.SeekSpy.City") && pchar.location == (npchar.city + "_town"))
	        {
				link.l4 = NPCharSexPhrase(npchar,LinkRandPhrase("Attendez ! Dites-moi qui vous êtes - tout de suite ! Je cherche un espion ennemi à la demande du gouverneur de "+XI_ConvertString("Colony"+characters[GetCharacterIndex(pchar.GenQuest.SeekSpy.MayorId)].city+"Gen")+" !",
					"Halte ! J'agis dans l'intérêt de"+XI_ConvertString("Colony"+characters[GetCharacterIndex(pchar.GenQuest.SeekSpy.MayorId)].city+"Gen")+"par ordre du gouverneur. Je fouille la ville à la recherche d'un agent hostile.",
					"Stop, l'ami ! Le gouverneur local "+characters[GetCharacterIndex(pchar.GenQuest.SeekSpy.MayorId)].lastname+" veut trouver un espion dans la ville."),
					LinkRandPhrase("Attendez, madame ! Dites-moi qui vous êtes - tout de suite! Je recherche un espion ennemi à la demande du gouverneur de "+XI_ConvertString("Colony"+characters[GetCharacterIndex(pchar.GenQuest.SeekSpy.MayorId)].city+"Gen")+"!",
					"Femme, je dois vous retenir ! J'agis dans l'intérêt de la ville "+XI_ConvertString("Colony"+characters[GetCharacterIndex(pchar.GenQuest.SeekSpy.MayorId)].city+"Gen")+" par ordre du gouverneur. Je fouille la ville à la recherche d'un agent hostile.",
					"Arrêtez, belle femme ! Le gouverneur local "+characters[GetCharacterIndex(pchar.GenQuest.SeekSpy.MayorId)].lastname+" veut trouver un espion dans la ville..."));
				link.l4.go = "SitySpy";
			}
			// <-- квестовый генератор мэра, поиск шпиёна на улице
			// Квестовый генератор священника. Квест №2. Warship -->
			if(CheckAttribute(PChar, "GenQuest.ChurchQuest_2.AskPeople") && !CheckAttribute(NPChar, "GenQuest.ChurchQuest_2.AskedPeople") && NPChar.location == PChar.GenQuest.ChurchQuest_2.QuestTown + "_town")
	        {
				link.l5 = LinkRandPhrase("Êtes-vous au courant","Vous avez entendu","Avez-vous entendu")+" qu'une église locale a été récemment pillée ?");
				link.l5.go = "Citiz_GenQuest_Church_2_1";
			}
			// <-- Квестовый генератор священника. Квест №2.
			
			Link.l6 = PCharRepPhrase(RandPhraseSimple("Non, vous entendez des choses. Je vais y aller maintenant.","Non, rien - je me dirigeais juste vers la taverne."),
										RandPhraseSimple("Non, rien. Bonne chance à vous !","Juste en train de regarder autour. Au revoir."));
			Link.l6.go = "exit";
		break;
		
		case "new question":
            dialog.text = NPCharRepPhrase(npchar,
						PCharRepPhrase(LinkRandPhrase("Oh oui, je suis presque aussi content"+NPCharSexPhrase(NPChar," "," ")+" de vous voir qu'un verre d'alcool. Demandez ce que vous voulez.","Vous aimez parler, Capitaine ? Eh bien, moi aussi... Surtout autour d'un verre de rhum.","Oui, "+PChar.name+" ?"),
										LinkRandPhrase("De quoi avez-vous besoin ?","Je vois, Capitaine "+PChar.name+". Vous êtes"+GetSexPhrase("","")+" assez bavard. ","Vous m'avez épuisé"+GetSexPhrase("","")+" avec vos questions, Capitaine. Mieux vaut m'aider avec le rhum.")),
						PCharRepPhrase(LinkRandPhrase("Que voulez-vous savoir "+GetAddress_Form(NPChar)+"?","Je vous écoute, Capitaine.","Je dois partir, alors faites vite, Capitaine."),
										LinkRandPhrase("Toujours heureux"+NPCharSexPhrase(NPChar," "," ")+"  d'être en bonne compagnie, "+GetAddress_Form(NPChar)+" "+PChar.lastname+". Dites ce que vous pensez.",
														"Oui, "+GetAddress_Form(NPChar)+" ?",
														"Vous aimez bavarder, Capitaine ? Eh bien, moi aussi..."))
							);

            // homo 25/06/06
			link.l1 = LinkRandPhrase("Quels sont les ragots les plus populaires dans la taverne locale ?",
									"Que se passe-t-il dans ces contrées ?",
									"Quoi de neuf à terre ici ?");
			link.l1.go = "rumours_citizen";
			link.l2 = LinkRandPhrase("Pouvez-vous m'y orienter ?","Je ne parviens pas à trouver le chemin d'un certain endroit...","Pourriez-vous me montrer le chemin... ?");
			link.l2.go = "town";  //(перессылка в файл города)
			if(Rand(1)==0)
			{
				link.l3 = LinkRandPhrase("Je veux savoir ce que les gens disent à propos d'une certaine personne.","Ne savez-vous pas ce que les gens disent à propos d'une certaine personne ?","J'aimerais apprendre quelque chose sur les habitants.");
				if(rand(1) == 0 || PChar.location == "LaVega_Town" || PChar.location == "PuertoPrincipe_town"
				|| PChar.location == "Pirates_town" || PChar.location == "Panama_town" || !CheckAttribute(NPChar, "City"))
				{
					link.l3.go = "info"; //(перессылка в файл города)
				}
				else
				{
					link.l3.go = "RumourAboutOwners"; // Warship. Сделал по-другому - у жителя каждого города будет свой диалог.
				}
			}
			else
			{
				link.l3 = "S'il vous plaît, parlez-moi davantage de votre colonie.";
				link.l3.go = "colony";
			}
            link.l4 = RandPhraseSimple("J'ai des affaires importantes !","J'ai affaire à vous.");
			link.l4.go = "quests";  //(перессылка в файл города)
			link.l5 = PCharRepPhrase(RandPhraseSimple("Non, vous entendez des choses. Je vais y aller maintenant.","Non, rien - je me dirigeais juste vers la taverne."),
										RandPhraseSimple("Non, rien. Bonne chance à vous !","Juste en train de regarder autour. Au revoir."));
			link.l5.go = "exit";
		break;
		
		case "RumourAboutOwners":
			Dialog.Text = "Sur qui voulez-vous en savoir plus ?";
			if(GetCharacterIndex(NPChar.city + "_Mayor") != -1)
			{
				link.l1 = "À propos du gouverneur.";
				link.l1.go = "RumourAboutOwners_Mayor";
			}
			if(GetCharacterIndex(NPChar.city + "_TavernKeeper") != -1)
			{
				link.l2 = "À propos du propriétaire de la taverne locale.";
				link.l2.go = "RumourAboutOwners_TavernKeeper";
			}
			if(GetCharacterIndex(NPChar.city + "_ShipYarder") != -1)
			{
				link.l3 = "À propos du capitaine de port.";
				link.l3.go = "RumourAboutOwners_ShipYarder";
			}
			if(GetCharacterIndex(NPChar.city + "_Trader") != -1)
			{
				link.l4 = "À propos du propriétaire du magasin local.";
				link.l4.go = "RumourAboutOwners_Trader";
			}
			link.l9 = "Peu importe, oubliez ça.";
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
		
		case "colony":
			dialog.text = LinkRandPhrase("Honnêtement, je n'en sais pas grand-chose, mais je peux quand même vous en dire un mot ou deux.",
							"Et qu'est-ce qui vous intéresse dans notre colonie ?","Bien sûr. Que voulez-vous savoir ?");
            switch(Rand(1))
			{
				case 0:
					link.l1 = "Quel genre de ville est-ce ?";
					link.l1.go = "colony_town";
				break;

				case 1:
					link.l1 = "Que savez-vous sur le fort qui défend la ville ?";
					link.l1.go = "fort";
				break;
            }
			link.l2 = "Changeons de sujet.";
			link.l2.go = "new question";
		break;
	  // to_do
		case "colony_town":
            dialog.text = "Vous plaisantez ? Ou vous blaguez ? Regardez sur le côté droit de votre écran.";
			link.l1 = "Ouais, j'ai rien dit.";
		    link.l1.go = "exit";
		break;
		
		case "fort":
            dialog.text = "Je ne sais rien à ce sujet.";
			link.l1 = "Dommage.";
		    link.l1.go = "exit";
		break;
		
		//Jason --> генератор Неудачливый вор
		case "Device_Citizen":
           dialog.text = "Hmm, "+pchar.GenQuest.Device.Shipyarder.Type+" ? Jamais entendu parler auparavant... Qu'est-ce que c'est, en fait ? Je n'ai jamais entendu parler d'une telle chose de toute ma vie"+NPCharSexPhrase(npchar,"","")+".";
			link.l1 = "Eh bien, c'est un outil de charpentier de marine, "+pchar.GenQuest.Device.Shipyarder.Describe+". Quelqu'un aurait-il vendu une telle chose en ville ? Peut-être. Vous avez remarqué que quelqu'un avait une telle chose sur lui ?";
			link.l1.go = "Device_Citizen_1";
			npchar.quest.Device = "true";
		break;
		
		case "Device_Citizen_1":
			if (sti(pchar.GenQuest.Device.Shipyarder.Chance1) > 3 && sti(pchar.GenQuest.Device.Shipyarder.Chance1) < 6 && npchar.sex != "woman")
			{
				dialog.text = "Hmm... Oui, je crois que j'ai déjà vu une personne avec un objet similaire. Il s'y promenait avec cet objet il y a quelques heures. Un appareil intéressant, en tout cas.";
				link.l1 = "Et à quoi ressemblait-il et où est-il allé ? J'ai vraiment besoin de cet instrument.";
				link.l1.go = "Device_Common";
			}
			else
			{
				dialog.text = "Non, je n'ai rien vu de tel.";
				link.l1 = "Je vois. Eh bien, il est temps de se renseigner !";
				link.l1.go = "exit";
			}
		break;
		
		//============================ Генератор мэра. Квест по розыску шпиона на улице ============================
		case "SitySpy":
			dialog.text = NPCStringReactionRepeat(NPCharSexPhrase(npchar,"Et qu'est-ce que ça a à voir avec moi ? Je suis du coin !","Eh bien, pourquoi me dérangez-vous avec ça ? Je vis dans cette ville et je ne sais rien de telles choses !"),
				NPCharSexPhrase(npchar,"Que voulez-vous de moi encore ? N'ai-je pas déjà dit que je ne suis pas l'espion ?!","Ne vous ai-je pas déjà dit que je suis du coin ?!"),
				NPCharSexPhrase(npchar,"Mon cher, c'est vous encore ! Laissez-moi tranquille - Je suis du coin !","Pourquoi me dérangez-vous encore avec vos questions stupides ?"),
				NPCharSexPhrase(npchar,"Encore ! Là, c'est un scandale !","Écoutez, laissez-moi tranquille, d'accord ? S'il vous plaît !"),"block",0,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("Qui peut confirmer votre déclaration ?","Oh, je suis désolé - Je vous avais déjà demandé...",
						"Je suis désolé, il y a tellement de gens...","D'accord, d'accord...",npchar,Dialog.CurrentNode);
		    link.l1.go = DialogGoNodeRepeat("SitySpy_1", "exit", "exit", "exit", npchar, Dialog.CurrentNode);
			// ==> выбираем подтверждателя
			int num = FindNearCharacters(npchar, 20.0, -1.0, -1.0, 1.0, false, true);
			if(num > 0)
			{
				for(i = 0; i < num; i++)
				{
					iTemp = chrFindNearCharacters[i].index;
					if (CheckAttribute(&characters[iTemp], "CityType"))
					{
						if(characters[iTemp].CityType == "soldier" || characters[iTemp].CityType == "citizen")
						{
							break;
						}
					}
				}
				pchar.GenQuest.SeekSpy.Idx = chrFindNearCharacters[i].index; //индекс выбранного
				pchar.GenQuest.SeekSpy.Type = characters[sti(pchar.GenQuest.SeekSpy.Idx)].chr_ai.type; //тип кто помог
				pchar.GenQuest.SeekSpy.BaseIdx = npchar.index; //индекс
			}
		break;
		case "SitySpy_1":
			if (sti(pchar.GenQuest.SeekSpy.Idx) == -1 || sti(pchar.GenQuest.SeekSpy.Idx) == 1) //на всякий случай
			{
				dialog.text = "Tout le monde peut ! Ecoutez, pourquoi continuez-vous à me harceler ? ! Si vous avez un problème, allez voir le gouverneur et réglez-le !",
				link.l1 ="Hmm... Il est probablement préférable de ne pas le déranger pour une si petite chose. Je vous crois.";
				link.l1.go = "exit";
				break;
			}
			dialog.text = "N'importe qui dans cette ville ! "+NPCharSexPhrase(npchar,GetFullName(&characters[sti(pchar.GenQuest.SeekSpy.Idx)])+" peut le faire, par exemple, maintenant qu'"+NPCharSexPhrase(&characters[sti(pchar.GenQuest.SeekSpy.Idx)],"il","elle")+" est juste là.",
				"Oh, Seigneur, eh bien, par exemple, "+NPCharSexPhrase(&characters[sti(pchar.GenQuest.SeekSpy.Idx)],GetAddress_FormToNPC(NPChar)+" "+characters[sti(pchar.GenQuest.SeekSpy.Idx)].lastname,GetFullName(&characters[sti(pchar.GenQuest.SeekSpy.Idx)]))+" peut le faire.");				
			link.l1 = "D'accord, voyons voir, alors.";
		    link.l1.go = "SitySpy_2";
			sld = &characters[sti(pchar.GenQuest.SeekSpy.Idx)];
			sld.dialog.currentnode = "SeekSpy_Checking";
			pchar.GenQuest.SeekSpy.time = 4.0; //время на подбежать
			if (sld.chr_ai.type == "merchant") pchar.GenQuest.SeekSpy.time = 0.0; //мерчант базарит сразу
            LAi_SetActorTypeNoGroup(sld);
		break;
		case "SitySpy_2":
			sld = &characters[sti(pchar.GenQuest.SeekSpy.Idx)];
			LAi_SetActorTypeNoGroup(npchar);
			LAi_ActorTurnToCharacter(npchar, sld);
			LAi_ActorDialog(sld, pchar, "", stf(pchar.GenQuest.SeekSpy.time), 0); 
			DialogExit();
		break;
		//=================== ноды квеста мэра. поиск шпиона на улице, опрос свидетеля ==================
		case "SeekSpy_Checking":
			dialog.text = "Oui, "+NPCharSexPhrase(&characters[sti(pchar.GenQuest.SeekSpy.BaseIdx)]," est bien une personne du coin.","elle est bien une personne du coin.");
			link.l1 = RandPhraseSimple("Je vois"+GetSexPhrase("","")+". Merci pour l'aide.","Tout est clair. Merci pour l'aide.");
			link.l1.go = "SeekSpy_Checking_1";
		break;
		case "SeekSpy_Checking_1":
			switch (pchar.GenQuest.SeekSpy.Type)
			{
				case "guardian": LAi_SetGuardianTypeNoGroup(npchar); break;
				case "patrol":   LAi_SetPatrolTypeNoGroup(npchar);   break;
				case "citizen":  LAi_SetCitizenTypeNoGroup(npchar);  break;
				case "merchant": LAi_SetMerchantTypeNoGroup(npchar); break;
			}
			LAi_SetCitizenTypeNoGroup(&characters[sti(pchar.GenQuest.SeekSpy.BaseIdx)]);
			NextDiag.CurrentNode = "First Time";
			DialogExit();
		break;
		
		// Мини квест на поиск обручального кольца -->
		case "CitizenFindItem_1":
			dialog.text = "Vous voyez, hier, j'étais hors de la ville, faisant une promenade, et j'ai perdu mon alliance..."+GetSexPhrase("Capitaine, pourriez-vous s'il vous plaît la chercher ?","Madame, s'il vous plaît, aidez-moi à la retrouver !")+"";
			link.l1 = "Bien sûr "+GetSexPhrase("Je peux ! Pour une fille aussi belle que vous, je peux tout faire !","Je vais vous aider. L'Église nous enseigne à aider ceux qui sont dans le besoin.")+"";
			link.l1.go = "CitizenFindItem_2";
			link.l2 = LinkRandPhrase("Non, je ne peux pas. Je suis désolé. J'ai trop à faire.","Je suis désolé, je ne peux pas. Je viens de me souvenir"+GetSexPhrase("","")+", que j'ai encore des affaires inachevées...","Je n'ai que très peu de temps, donc je ne peux pas vous aider avec quoi que ce soit...");
			link.l2.go = "CitizenFindItem_NoQuest";
			break;
			
		case "CitizenFindItem_2":
			dialog.text = ""+GetSexPhrase("Capitaine","Madame")+", c'est vraiment génial ! S'il vous plaît, trouvez cette bague pour moi, mon mari arrive dans seulement "+sti(NPChar.LifeDay)+" jours, et je ne voudrais pas qu'il me voie sans ma bague de mariage.";
			link.l1 = RandPhraseSimple("Où l'avez-vous perdue, dites-vous ?","Alors, où l'avez-vous exactement perdu ?");
			link.l1.go = "CitizenFindItem_3";
		break;
			
		case "CitizenFindItem_3":
			dialog.text = "Juste après les portes de la ville...";
			link.l1 = "Dans ce cas, je pars à sa recherche...";
			link.l1.go = "CitizenFindItem_4";
		break;
			
		case "CitizenFindItem_4":
			dialog.text = "Oui, s'il vous plaît. Et dépêchez-vous - rappelez-vous que vous avez seulement "+sti(NPChar.LifeDay)+" jours.";
			link.l1 = "Je me souviens.";
			link.l1.go = "exit";
			PChar.GenQuest.CitizenFindItem.StartQuest = true;
			PChar.GenQuest.CitizenFindItem.City = NPChar.City;
			PChar.GenQuest.CitizenFindItem.CitizenID = NPChar.ID;
				
			sCity = NPChar.City + "_ExitTown";
				
			//sTemp = "randitem" + (rand(1)+1); // Т.е. может получиться, что его вовсе найти не удастся. И это гуд.
			sTemp = "randitem1";
			Log_TestInfo("The ring shall be in the locator - " + sTemp);
			PChar.GenQuest.CitizenFindItem.ItemLocator = sTemp;
			ChangeItemDescribe("DOjeronRing", "itmdescr_WeddingRing");			
			items[FindItem("DOjeronRing")].Name = "itmname_WeddingRing";
			items[FindItem("DOjeronRing")].City = XI_ConvertString("Colony" + NPChar.City + "Gen");
			SetFunctionTimerCondition("CitizenFindItemMiniQuest_Timer", 0, 0, sti(NPChar.LifeDay), false);
			PChar.GenQuestRandItem.(sCity).(sTemp) = "DOjeronRing";
			SetGameModeCondition("CitizenFindItemMiniQuest_CheckItem");			
		break;
			
		case "CitizenFindItem_NoQuest":
			DialogExit();
			NextDiag.CurrentNode = "First time";
			NPChar.CitizenFindItem.NoQuest = true; // Эта девушка квест больше не даст
		break;
			
		case "CitizenFindItem_Complete_1":
			dialog.text = ""+GetSexPhrase("Capitaine","jeune dame")+"! Je suis si heureuse ! Comment puis-je vous remercier ?";
			link.l1 = "Oh, pas de remerciements nécessaires - je l'ai fait de manière tout à fait désintéressée.";
			link.l1.go = "CitizenFindItem_Complete_2";
			link.l2 = "Quelques centaines de pesos ne feraient certainement pas de mal...";
			link.l2.go = "CitizenFindItem_Complete_3";
			RemoveItems(PChar, "DOjeronRing", 1);
			DeleteAttribute(PChar, "GenQuest.CitizenFindItem");
			NPChar.CitizenFindItem.NoQuest = true;
			PChar.Quest.CitizenFindItemMiniQuest_Timer.over = "yes";
			BackItemDescribe("DOjeronRing");
			items[FindItem("DOjeronRing")].Name = "itmname_DOjeronRing";
			DeleteAttribute(&items[FindItem("DOjeronRing")], "City");
		break;
			
		case "CitizenFindItem_Complete_2":
			dialog.text = "Oh, "+GetSexPhrase("Capitaine, vous êtes une personne si noble","madame, vous êtes si noble")+"! Je prierai certainement pour vous à l'église ! Adieu...";
			link.l1 = "Adieu, "+NPChar.name+".";
			link.l1.go = "exit";
			ChangeCharacterComplexReputation(PChar,"nobility" ,1);
			AddCharacterExpToSkill(PChar, "Leadership", 10);
			AddCharacterExpToSkill(PChar, "Fortune", 10);
		break;
			
		case "CitizenFindItem_Complete_3":
			iTemp = (rand(3)+1)*50;
			dialog.text = "Oh, mais bien sûr. Voici -"+FindRussianMoneyString(iTemp)+". C'est tout ce que j'ai. Prenez cet argent s'il vous plaît... Et adieu.";
			link.l1 = "Au revoir, "+GetFullName(NPChar)+".";
			link.l1.go = "exit";
			AddMoneyToCharacter(PChar, iTemp);
		break;
		// <-- Мини квест на поиск обручального кольца
		
		//=================== ноды квеста священника. поиск грабителей (квест №2)==================
		case "Citiz_GenQuest_Church_2_1":
			if(rand(3) != 1)
			{
				dialog.text = LinkRandPhrase("Non, je ne sais rien à ce sujet.","Je ne sais rien à cet égard.","Je ne sais rien.");
					link.l1 = LinkRandPhrase("D'accord, merci.","Je vois, merci.","Très bien, veuillez m'excuser.");
				link.l1.go = "exit";
			}
			else
			{
				dialog.text = LinkRandPhrase("Je ne sais rien à ce sujet, mais vous pouvez demander aux clients de la taverne - ils vous diront sûrement une chose ou deux.","Je ne peux rien vous dire. Renseignez-vous à la taverne.","Je ne sais rien de particulier, mais j'ai entendu dire qu'il y avait des ragots à la taverne.");
				link.l1 = "Eh bien, c'est quelque chose au moins.";
				link.l1.go = "exit";
			}
			
			NPChar.GenQuest.ChurchQuest_2.AskedPeople = true;
		break;		
		
		//замечение по обнажённому оружию
		case "CitizenNotBlade":
			if (loadedLocation.type == "town")
			{
				dialog.text = NPCharSexPhrase(NPChar,"Écoutez - en tant que citoyen de cette ville, je dois vous demander de vous abstenir de vous promener avec une lame dégainée.","Écoutez - en tant que citoyen de cette ville, je dois vous demander de ne pas vous promener avec une lame dégainée.");
				link.l1 = LinkRandPhrase("D'accord.","D'accord.","Comme vous dites...");
			}
			else
			{
				dialog.text = NPCharSexPhrase(NPChar,"Tout doux "+GetSexPhrase("camarade","madame")+" quand vous vous promenez avec une arme à la main. Ça me rend nerveux...","Je n'aime pas quand "+GetSexPhrase("des hommes","quelqu'un")+" se promènent avec des armes prêtes à l'emploi. Cela me fait peur...");
				link.l1 = RandPhraseSimple("Compris.","Je la rangerai.");
			}
			link.l1.go = "exit";
			NextDiag.TempNode = "First Time";
		break;

	}
}
