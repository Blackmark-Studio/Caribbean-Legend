// BOAL новый диалог офицера и компаньона 21/06/06
void ProcessDialogEvent()
{
	ref NPChar, d;
	aref Link, Diag;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makeref(d, Dialog);
	makearef(Diag, NPChar.Dialog);
	
	ref    	sld, rItm, rItem;
	string 	attr, attrLoc, sGun, sBullet, attrL, sAttr;
	int    	iTemp, iTax, iFortValue, i;
	aref 	rType;
	
	sAttr = Dialog.CurrentNode;
	if (findsubstr(sAttr, "SetGunBullets1_" , 0) != -1)
 	{
        i = findsubstr(sAttr, "_" , 0);
	 	NPChar.SetGunBullets = strcut(sAttr, i + 1, strlen(sAttr) - 1); // индекс в конце
 	    Dialog.CurrentNode = "SetGunBullets2";
 	}
	if (findsubstr(sAttr, "SetMusketBullets1_" , 0) != -1)
 	{
        i = findsubstr(sAttr, "_" , 0);
	 	NPChar.SetMusketBullets = strcut(sAttr, i + 1, strlen(sAttr) - 1); // индекс в конце
 	    Dialog.CurrentNode = "SetMusketBullets2";
 	}
	
	switch(Dialog.CurrentNode)
	{
        case "First time":
			if (LAi_grp_playeralarm > 0)
			{
       			dialog.text = RandPhraseSimple("Heh, capitaine, la moitié de la garnison est après vous en ce moment. Sûrement ce n'est pas le meilleur moment pour être embauché dans votre équipage!","Et se battre pour atteindre le navire? Non, cap, une autre fois...");
				link.l1 = RandPhraseSimple("Comme vous voulez...","En fait, je n'avais pas l'intention de vous embaucher."); 
				link.l1.go = "exit";
				break;
			}
			Diag.TempNode = "OnceAgain";
			dialog.text = "Avez-vous besoin d'un officier, capitaine?";
			if (FindFreeRandomOfficer() > 0)
			{
    			Link.l1 = "Un officier? Et qu'est-ce que tu sais faire?";
    			Link.l1.go = "Node_2";
			}
			Link.l2 = "Non, j'ai l'ensemble complet.";
			Link.l2.go = "Exit";			
		break;
		
		case "CitizenNotBlade":
			dialog.text = "Capitaine, que faites-vous? Rangez votre arme, avant de causer beaucoup de problèmes!";
			link.l1 = LinkRandPhrase("Bien.","D'accord.","Ne t'inquiète pas, je le range...");
			link.l1.go = "exit";
		break;
		
		case "hired":
			Diag.TempNode = "Hired";
			// только наняли -->
			if (IsCompanion(NPChar))
			{
				Dialog.text = "Aujourd'hui, nous mettons enfin les voiles !";
				link.l2 = "Ouais... Je suis content.";
				link.l2.go = "Exit";
				break;
			}
			if (Npchar.location.group == "sit" && !isShipInside(pchar.location))
			{
				dialog.text = "Je finirai juste mon verre, capitaine, puis j'irai au navire. Ne t'inquiète pas - je serai là à temps.";
				Link.l1 = "D'accord. Si tu es en retard, je te ferai laver le pont!";
				Link.l1.go = "Exit";
				break;
			}
			// только наняли <--
   			dialog.text = "Que voulez-vous, capitaine?";
			// диалог компаньона на корабле.
			if (CheckAttribute(NPChar, "IsCompanionClone"))
			{
				Link.l2 = "J'ai besoin de vous donner plusieurs ordres.";
				Link.l2.go = "Companion_Tasks";
				break;
			}
			
			// на Тайясаль
			if (CheckAttribute(pchar, "questTemp.Dolly_Tieyasal") && !CheckAttribute(npchar, "quest.Tieyasal"))
			{
				Link.l66 = ""+npchar.name+", je vais dans une ancienne ville indienne de Tayasal. Ce sera un voyage dangereux et inhabituel - à travers une idole de téléportation. Me joindrez-vous?";
				if(npchar.id == "Folke")
				{
					Link.l66 = ""+npchar.name+", J'ai une demande sérieuse pour toi - une vraie affaire, suicidaire mais sacrément rentable. J'ai besoin d'un homme loyal pour une quête vers une ancienne ville indienne. Tu es avec moi?";
				}
				if(npchar.id == "Duran")
				{
					Link.l66 = "Claude, tu te plaignais autrefois que les mercenaires sont sous-payés.";
				}
				Link.l66.go = "tieyasal";
			}
			
			if (isOfficer(Npchar)) // проверка для кампуса, где слотовые офы
			{
				Link.l2 = "Maintenant, écoutez mon ordre!";
				Link.l2.go = "stay_follow";
			}

           		// boal отчёт о корабле
			if(CheckAttribute(NPChar, "treasurer") && NPChar.treasurer == 1)
			{
			    Link.l8 = "Donne-moi un rapport complet du navire, "+GetStrSmallRegister(XI_ConvertString("trésorier"))+".";
			    Link.l8.go = "QMASTER_1";
			        
			    // Warship. Автозакупка товара
			    if(!CheckAttribute(PChar, "TransferGoods.Enable"))
			    {
				    Link.l11 = "Je veux que vous achetiez des marchandises pendant que nous restons dans la colonie.";
				    Link.l11.go = "TransferGoodsEnable";
			    }
			    else
			    {
				    Link.l11 = "Tu sais, nous n'avons plus besoin d'acheter des marchandises dans les colonies.";
				    Link.l11.go = "TransferGoodsDisable";
			    }
			}
			
			if (pchar.location != "My_Campus") // patch-5
			{
			Link.l4 = "Officier, vos services ne sont plus nécessaires.";
			Link.l4.go = "AsYouWish";
			}
			
			
			// по тек локации определим можно ли тут приказать  -->
			if(IsEntity(&loadedLocation))
			{
				if(CheckAttribute(loadedLocation, "fastreload"))
				{
					iTemp = FindColony(loadedLocation.fastreload);
					if(iTemp != -1)
					{
						sld = GetColonyByIndex(iTemp);
						if(sti(sld.HeroOwn) == true && !CheckAttribute(sld, "OfficerIdx"))
						{
							NPChar.ColonyIdx = iTemp;
							Link.l7 = "Je te fais adjoint de cette ville !";
							Link.l7.go = "Gover_Hire";
						}
					}
				}
			}
			
			Link.l9 = "Rien. Repos!";
			Link.l9.go = "Exit";
		break;
		
		// Тайясаль
		case "tieyasal":
			if(npchar.id == "Folke")
			{
				dialog.text = "Sacrebleu, Cap'taine! Je pensais que tu te débarrasserais de moi dès que tu en aurais l'occasion, mais tu m'as surpris, comme toujours. Bien sûr que je suis avec toi, et merci de donner à cet imbécile la vraie vie d'un loup de mer!";
				Link.l1 = "Bien joué, "+npchar.name+"!";
				Link.l1.go = "folke_tieyasal";
				break;
			}
			if(npchar.id == "Duran")
			{
				dialog.text = "Hein? Ai-je vraiment dit cela?";
				Link.l1 = "Tu l'as fait. Je t'ai écouté attentivement à l'époque, et je suis prêt à corriger l'injustice.";
				Link.l1.go = "Duran_tieyasal";
				break;
			}
			dialog.text = LinkRandPhrase("Désolé, cap, mais ce n'est pas pour ça que j'ai signé. Ne pensez pas que je suis un lâche, mais je ne suis pas prêt à aller affronter une mort certaine. Je n'en ai pas encore assez de vivre - pas encore. Vous pouvez me virer si vous voulez.","Capitaine, je vous demande pardon, mais - non. Les mers, l'abordage, les villes ennemies - c'est parfaitement bien, mais je ne veux pas me mêler de cette sorcellerie indienne. Si vous êtes contrarié par ma réponse, vous pouvez annuler notre contrat.","Vous voulez l'impossible, capitaine, et vous le réalisez. Personne ne reviendra vivant, y compris vous, donc je passe. Si vous considérez mon refus comme une violation des termes du contrat, vous pouvez l'annuler.");
			link.l1 = LinkRandPhrase("Je ne vous blâme pas, officier. Je comprends parfaitement.","Dommage, mais je peux vous comprendre. C'est pourquoi je vous en ai parlé à l'avance.","Je comptais sur toi... Mais je peux comprendre ta position, officier.");
			link.l1.go = "tieyasal_1";
		break;
		
		case "Duran_tieyasal":
			dialog.text = "Heh ! Alors, augmenteras-tu mon salaire ?";
			Link.l1 = "Impossible! Je vais dans une ancienne ville indienne. La mission est suicidaire, mais il y aura de l'or là-bas...";
			Link.l1.go = "Duran_tieyasal_2";
		break;
		
		case "Duran_tieyasal_2":
			dialog.text = "Je ne suis pas intéressé par l'or. Ce serait un honneur de vous aider, Cap, comme vous m'avez aidé autrefois. Quand partons-nous?";
			Link.l1 = "Bien dit, Claude ! Sois prêt en tout - ça ne sera pas long maintenant.";
			Link.l1.go = "Duran_tieyasal_3";
		break;
		
		case "Duran_tieyasal_3":
			DialogExit();
			npchar.quest.Tieyasal = "teleport";
		break;
		
		case "folke_tieyasal":
			Achievment_Set("ach_CL_108");
			DialogExit();
			npchar.quest.Tieyasal = "teleport";
		break;
		
		case "tieyasal_1":
			DialogExit();
			npchar.quest.Tieyasal = "true";
		break;
		
		case "TransferGoodsEnable":
			if(sti(PChar.Ship.Type) == SHIP_NOTUSED)
	        {
				dialog.text = "Capitaine, quelles marchandises? Nous devons d'abord nous trouver un navire !";
				Link.l1 = "Oui, tu as raison.";
				Link.l1.go = "Exit";
				Diag.TempNode = "Hired";
				break;
	        }
	        	
			PChar.TransferGoods.Enable = true;
		//	PChar.TransferGoods.TreasurerID = NPChar.id;
			Dialog.text = "Cela sera fait, "+GetSexPhrase("monsieur","mademoiselle")+" capitaine!";
			Link.l1 = "A l'aise.";
			Link.l1.go = "TransferGoodsEnable_2";
        break;
        	
		case "TransferGoodsEnable_2":
			Diag.CurrentNode = "Hired";
			DialogExit();
			LaunchTransferGoodsScreen(); // Интерфейс автозакупки товаров
		break;
		
		case "TransferGoodsDisable":
			DeleteAttribute(PChar, "TransferGoods.Enable");
			Dialog.text = "Ce sera fait, "+GetSexPhrase("monsieur","mademoiselle")+" capitaine!";
			Link.l1 = "Au repos.";
			Link.l1.go = "exit";
			Diag.TempNode = "Hired";
		break;
        
		case "ShowParam_exit":
			Diag.CurrentNode = "OnceAgain";
			NPChar.quest.meeting = true;
			DialogExit();
			
			PChar.SystemInfo.OnlyShowCharacter = true;
            LaunchCharacter(NPChar);
		break;
		
		case "exit":
			Diag.CurrentNode = Diag.TempNode;
			NPChar.quest.meeting = true;
			DialogExit();			
		break;

		case "exit_hire":
			Pchar.questTemp.HiringOfficerIDX = GetCharacterIndex(Npchar.id);
			AddDialogExitQuestFunction("LandEnc_OfficerHired");
			Diag.CurrentNode = Diag.TempNode;
			NPChar.quest.meeting = true;
			DialogExit();
			if(CheckAttribute(pchar,"systeminfo.tutorial.Fighter") && Npchar.quest.officertype == "fighter")
			{
				DeleteAttribute(pchar,"systeminfo.tutorial.Fighter");
				LaunchTutorial("Fighter", 1);
			}
		break;

		case "exit_fire":
			//navy -->
			if (CheckAttribute(NPChar, "PGGAi"))
			{
				pchar.questTemp.FiringOfficerIDX = NPChar.index;
				AddDialogExitQuestFunction("PGG_FireOfficer");
				DialogExit();			
				break;
			}
			//navy <--
			Diag.TempNode = "Fired";
			Pchar.questTemp.FiringOfficerIDX = GetCharacterIndex(Npchar.id);
			AddDialogExitQuestFunction("LandEnc_OfficerFired");

			Diag.CurrentNode = Diag.TempNode;
			NPChar.quest.meeting = true;

			DialogExit();			
		break;
		
		// boal 29.05.04 офицер хочет свалить -->
        case "WantToGo":
			if (npchar.id == "Duran" && !CheckAttribute(pchar, "questTemp.SKD_SobytieKlodDuran"))
			{
				SetTimerCondition("SKD_DuranTavern", 0, 0, 30, false);
				pchar.questTemp.SKD_SobytieKlodDuran = true;
			}
			chrDisableReloadToLocation = false;
			Diag.TempNode = "Hired";
			dialog.text = LinkRandPhrase(LinkRandPhrase("Capitaine, vous savez, je... Eh bien, je vous demanderais de me soulager. Il est temps pour moi de m'installer, de me marier et de faire quelques enfants. Je n'ai toujours pas de chez moi, quand je serai vieux il n'y aura personne pour m'apporter un verre d'eau.","Capitaine, s'il vous plaît, laissez-moi démissionner. Pendant toutes ces années, j'ai vadrouillé autour du monde, et je n'ai toujours pas vraiment vu grand-chose. Je veux juste vivre une nouvelle vie, jeter l'ancre et voir le monde sous un angle différent.","Capitaine, le service naval est sûrement une belle chose, il y a un bon profit et de l'aventure, mais le temps est venu pour moi de penser à moi-même. Vous savez, jeter l'ancre dans un port tranquille, acheter une maison, avoir des enfants. S'il vous plaît, laissez-moi partir."),LinkRandPhrase("Capitaine, vous savez, je suis vraiment désolé, mais j'en ai assez de toutes ces tâches, gardes et discipline. Vous savez, je veux juste vivre une vie libre au moins pour un moment, mais je réalise que vous ne m'attendrez pas, alors... Pourriez-vous me libérer?","Capitaine, vous savez... Il y a un petit navire que je peux me permettre, donc... Je pense que c'est probablement le moment pour moi de commencer ma propre affaire. S'il vous plaît, pourriez-vous me laisser partir?","Capitaine, on m'a juste proposé un poste au port. En fait, j'ai hâte de jeter l'ancre et de m'installer dans une vie de couple depuis un certain temps déjà. S'il vous plaît, permettez-moi de partir. Je ne peux vraiment pas manquer une telle opportunité."),LinkRandPhrase("Capitaine, je suis vraiment malade en mer. Les docteurs continuent à me dire que c'est une idiosyncrasie. S'il vous plaît, pour l'amour de Dieu, laissez-moi partir, ou je vais simplement sauter par-dessus bord à un moment donné.","Capitaine, je pense qu'il est temps pour moi de m'installer et de me trouver un endroit plus tranquille. Vous savez, j'ai peur. Peur des balles perdues, peur de mourir pendant un abordage. Je prie le Seigneur de me garder en vie, et quand je ferme les yeux, je vois toutes les âmes innocentes que j'ai tuées. Ils me supplient de les épargner... S'il vous plaît, montrez un peu de compassion, et laissez-moi partir.","Capitaine, mes vieilles blessures me font mal, et la récente contusion se rappelle à moi chaque jour. Bientôt vous me renverrez, et qui m'embauchera après ça? S'il vous plaît, laissez-moi partir, je me soignerai et trouverai un endroit plus calme."));
			Link.l1 = RandPhraseSimple(LinkRandPhrase("Ils partent tous finalement. Très bien, tu es libre de partir.","Je peux comprendre votre raisonnement. Tôt ou tard, toutes les choses prennent fin. Eh bien, allez alors... et ne gardez aucune rancune si jamais je vous ai offensé.","Ceci encore? Tu as choisi exprès le moment le plus inopportun pour me quitter, n'est-ce pas? Peu importe. Adieu."),LinkRandPhrase("Difficile de croire ce que tu me dis... Bien, fais tes bagages et pars.","Vous? Je ne m'y attendais pas... Après tout ce temps passé à combattre côte à côte... Eh bien, je ne vous arrête pas. Que Dieu vous accompagne.","Tu sembles sérieux. Eh bien, je te souhaite bonne chance, sache que tu me manqueras."));				
			Link.l1.go = "WantToGo_free";
			if (sti(Pchar.money) >= sti(NPChar.rank)*250)
			{
				Link.l2 = LinkRandPhrase("Je vois... C'est donc ça, hein ? Et je comptais sur toi... Eh bien, si tu as déjà pris ta décision alors séparons-nous. Prends "+sti(NPChar.rank)*250+" pesos pour ton service loyal. Et ne garde aucune rancune si jamais je t'ai offensé.","Eh bien, je ne garde aucune rancune et ne me souviens d'aucun mal. Si c'est ce que tu as décidé, alors va. Et prends "+sti(NPChar.rank)*250+" pesos pour prendre un nouveau depart, cela sera certainement utile.","Je vois... Eh bien, tôt ou tard cela devait arriver. Je vais vous donner "+sti(NPChar.rank)*250+" pesos pour régler ta vie. Et prends soin de ta santé aussi, le service naval est plein de difficultés..."); 
				Link.l2.go = "Im_kind_A2_1";
			}
			Link.l3 = LinkRandPhrase("Alors tu dis... Ne te rends-tu pas compte qu'en partant maintenant, tu ne fais que me poignarder dans le dos? Je ne peux pas te laisser partir maintenant, n'y pense même pas.","Voilà une nouvelle! Tu sais, les gens sont censés me prévenir de ce genre de choses à l'avance! Alors oublie ta vie privée pour un moment. Quand le temps viendra, je te suggérerai quand prendre ta retraite.","Aucune démission. J'ai tout le monde en compte. Je ne peux pas laisser tout le monde partir juste à cause de leur souhait personnel. Servez, pendant que je considère si vous méritez un congé.");	
			Link.l3.go = "WantToGo_Stay";
		break;
		
		case "Im_kind_A2_1":
			AddMoneyToCharacter(Pchar, -(makeint(sti(NPChar.rank)*250)));
			ChangeOfficersLoyality("good_all", 1);
			ChangeCharacterComplexReputation(pchar,"nobility", 1);
			ChangeCharacterComplexReputation(pchar,"authority", 0.5);
			dialog.text = "Merci, capitaine ! Une générosité vraiment inattendue... Vous savez, j'ai encore quelques-unes de vos affaires, peut-être aimeriez-vous les récupérer ?";
			Link.l1 = "Peut-être... Trouver une bonne lame n'est pas si facile ces jours-ci.";
			Link.l1.go = "Get_out_А2_chang";
			Link.l2 = "Oh, ne vous embêtez pas. Gardez-les en souvenir de votre service.";
			Link.l2.go = "WantToGo_free";
		break;
		
		case "WantToGo_Stay":
			dialog.text = RandPhraseSimple("Mais comment, capitaine? Même les esclaves sont finalement envoyés à la rive. Et je ne suis pas un esclave, donc je peux décider de mon sort par moi-même!","Capitaine, je vous ai servi fidèlement tout ce temps. N'ai-je pas mérité le droit de décider de mon sort par moi-même?");
			Link.l1 = LinkRandPhrase("Je vois que je ne peux pas te garder comme ça. Très bien, que dirais-tu d'un peu de soutien financier? Cela ne fait jamais de mal, tu peux utiliser cet argent pour te construire un nid douillet dans un port tranquille ou prendre soin de ta santé.","D'accord, disons-le comme ça. Quelle somme pourrait éventuellement vous faire reconsidérer votre décision?","Tu as raison. Mais et si je te proposais une allocation monétaire unique, cela changerait-il d'avis?");
			Link.l1.go = "WantToGo_Stay_2";
			Link.l2 = PCharRepPhrase(RandPhraseSimple("Oh, non, mon ami, ici tu te trompes... Pendant que tu gaspillais ton temps dans les tavernes à courir après les jupons après les verres, tu pouvais décider par toi-même, mais une fois que tu as mis le pied à bord de mon navire, alors tu as remis ton sort entre mes mains.","Hmm. Maintenant, c'est une déclaration sérieuse. Apparemment, tu as oublié comment je t'ai trouvé, dans une taverne puante sans un sou en poche. On ne peut même pas te montrer une seule pièce d'or, car tu la transformeras immédiatement en rhum. 'Décide de mon sort...' Pfff! Quelle plaisanterie!"),LinkRandPhrase("Tant que vous êtes à mon service, c'est moi qui prends les décisions. Et maintenant, veuillez retourner à vos devoirs, avant de me mettre trop en colère !","Hmm. Maintenant, c'est une déclaration sérieuse. Mais tu n'as pas encore remboursé tout l'argent qui t'a été versé en avance. Donc ta démarche peut être considérée comme une tentative d'extorsion, n'est-ce pas?","Oh, je vois... Que disent à nouveau les réglements du navire? Ici, paragraphe deux: 'Quiconque tente de partir sans permission sera débarqué sur une rive déserte avec un seul sac de poudre, une flasque d'eau, un pistolet et une seule balle.' Alors, comment trouvez-vous cela?"));	
			Link.l2.go = "WantToGo_Stay_force";
		break;
		
	case "WantToGo_Stay_2":
		dialog.text = LinkRandPhrase("Eh bien, c'est une autre histoire. "+sti(NPChar.rank)*500+" pesos sur l'ongle, et je resterai avec toi.","Eh bien, peut-être pour "+sti(NPChar.rank)*500+" pesos je pourrais rester, je suppose.","Eh bien, si tu le mets de cette façon, pour "+sti(NPChar.rank)*500+" pesos je pourrais continuer mon service.");
		if (sti(Pchar.money) >= sti(NPChar.rank)*500)
		{
			Link.l1 = RandPhraseSimple("D'accord, convenu.","D'accord. Bien que vous pourriez demander moins.","Tu as un sacré appétit je vois ! Mais, je t'ai fait une promesse n'est-ce pas, et je resterai fidèle à ma parole.");	
			Link.l1.go = "WantToGo_Stay_ForMoney";
		}
		Link.l2 = LinkRandPhrase("C'est vraiment trop. Je pourrais embaucher deux officiers pour un tel prix. Peut-être, il est plus simple de simplement te laisser partir.","Eh bien, tu as certainement une haute opinion de toi-même. D'accord, je te laisse partir. Mais tu verras par toi-même, une fois que tu es libre, que ta vie ne sera pas aussi sereine que tu l'attendais.","Je ne vais pas payer une telle somme. Tu peux partir, mais ne demande même pas à revenir, je ne pardonne pas la trahison.");				
		Link.l2.go = "WantToGo_free";
	break;
	
	case "WantToGo_Stay_force":
		Npchar.loyality = makeint(Npchar.loyality) - 2;
		dialog.text = "D'accord, si tu le dis de cette façon, je vais rester. Mais sache que ce faisant, je vais à l'encontre de ma propre volonté.";
		Link.l1 = LinkRandPhrase("Très bien. Retournez à vos devoirs, et nous continuerons cette conversation plus tard.","Retourne au navire. Et la prochaine fois, réfléchis à deux fois avant de demander la retraite.","En effet. Le devoir est le devoir, et tu ne devrais pas te livrer à tes fantasmes tout de suite.");
		Link.l1.go = "exit";
	break;
	
	case "WantToGo_Stay_ForMoney":
		Diag.TempNode = "Hired";
		NPChar.greeting = "Gr_Officer";
		if(NPChar.id == "Duran") NPChar.greeting = "Duran_officer";
		ChangeCharacterComplexReputation(pchar,"authority", 0.2);
		AddMoneyToCharacter(Pchar, -(makeint(sti(NPChar.rank)*500)));
		Npchar.loyality = makeint(Npchar.loyality) + 1;    
		Diag.CurrentNode = Diag.TempNode;
		NPChar.quest.meeting = true;
		DialogExit();
		NPChar.location = "none";
		LAi_SetOfficerType(NPChar);
	break;
	
	case "WantToGo_free":
		//navy -->
		if (CheckAttribute(NPChar, "PGGAi"))
		{	
			pchar.questTemp.FiringOfficerIDX = NPChar.index;
			AddDialogExitQuestFunction("PGG_FireOfficer");
			Diag.CurrentNode = Diag.TempNode;
			DialogExit();	
			break;
		}
		//navy <--
		Diag.TempNode = "WantToGo_free_Yet";
		Pchar.questTemp.FiringOfficerIDX = GetCharacterIndex(Npchar.id);
		AddDialogExitQuestFunction("LandEnc_OfficerFired");
		Diag.CurrentNode = Diag.TempNode;
		NPChar.quest.meeting = true;
		DialogExit();
	break;
	
	case "WantToGo_free_Yet":
		Diag.TempNode = "WantToGo_free_Yet";
		dialog.text = LinkRandPhrase("Je n'y crois pas! Merci Capitaine, c'est un tel poids en moins dans mon esprit.","Merci, capitaine, de ne pas essayer de me retenir. Vous savez, je veux vraiment essayer d'autres choses dans la vie.","Heh, maintenant je vais devoir m'habituer à ma nouvelle liberté. Ce n'est que maintenant que je commence à réaliser combien j'en avais assez de tout ce service de flotte.");	
		Link.l1 = RandPhraseSimple("Eh bien, bonne chance à toi.","Vous êtes libre maintenant. Votre service est terminé.");
		Link.l1.go = "exit";
	break;
	// boal 29.05.04 офицер хочет свалить <--
		
	// пассажир возмущен игроком и сваливает -->
	case "WantToRemove":
		if (npchar.id == "Duran" && !CheckAttribute(pchar, "questTemp.SKD_SobytieKlodDuran"))
		{
			SetTimerCondition("SKD_DuranTavern", 0, 0, 30, false);
			pchar.questTemp.SKD_SobytieKlodDuran = true;
		}
        chrDisableReloadToLocation = false;
		if (Npchar.alignment == "good")
		{
			dialog.text = RandPhraseSimple(LinkRandPhrase("Capitaine, je ne veux pas agir contre ma conscience et participer à la brigandage.","Capitaine, je ne souhaite plus participer à vos émeutes. Je suis un officier, pas un boucher.","Capitaine, vos manières de bandit rendent mon séjour dans votre équipage impossible."),LinkRandPhrase("Capitaine, je dois admettre que mon emploi avec vous était une erreur décevante. Je ne suis pas prêt à sacrifier ma réputation pour de l'argent.","Capitaine, vous avez rassemblé sur votre navire tous les plus vils coupe-jarrets du Nouveau Monde. Il est dégoûtant pour un homme décent de les regarder. Je ne veux plus servir avec un tel équipage.","Capitaine, vous avez engagé une équipe complète de coquins, il n'y a pas un seul homme décent avec qui discuter. Je méprise un tel service."))+" Adieu.";
			Link.l1 = "Quoi?! C'est un navire militaire, pas une école de finition! Tu peux aller en enfer alors!";
			Link.l1.go = "exit_fire_1";
			if (sti(Pchar.money) >= sti(NPChar.rank)*500)
			{
				Link.l2 = "Je savais que tu partirais bientôt... ce service n'est pas pour toi. Mais ne m'accuse de rien. Voici "+sti(NPChar.rank)*500+" pesos, vous les trouverez utiles pendant que vous cherchez un travail à votre goût.";
				Link.l2.go = "Im_kind_A2";
			}
			Link.l3 = LinkRandPhrase("Oh, alors c'est le refrain que tu chantes maintenant. Et qu'en est-il de ta part de chaque pillage, cela te brûle-t-il les mains? Ou tu prévois de te retirer dans un monastère pour prier pour le pardon de tes péchés? Mets aussi un mot pour nous alors! Ha-ha-ha-ha-ha!","Hmm. Maintenant, c'est une déclaration sérieuse. Et où regardait ta conscience innocente, pendant que nous dévalisions ensemble des marchands? Comment vas-tu la laver propre? Ou vas-tu nous dénoncer, pour que nous pendions sur la potence en bonne compagnie?","Oh, bravo! Apparemment, vous avez oublié comment je vous ai trouvé, dans une taverne puante sans un sou en poche. Pour votre information, en tant qu'officier vous ne valez pas un liard. Vous ne valez rien!");
			Link.l3.go = "WantToGo_stop";
		}
		else
		{
            dialog.text = RandPhraseSimple(LinkRandPhrase("Capitaine, je n'aime vraiment pas vos jeux nobles et je ne vais pas abandonner mes habitudes pour le bien de votre sérénité. Adieu.","Capitaine, je ne peux plus rester à votre service. J'ai déjà perdu tant de temps. Être un simple corsaire me rapporterait déjà une fortune. Je pars.","Capitaine, vos hommes me dégoûtent. Pas un seul homme décent, seulement des fanfarons, aucun pour faire une compagnie pour boire avec. Je pars."),LinkRandPhrase("Capitaine, je suis un officier vétéran, et votre navire ressemble plus à une barge de fret. Je n'aime pas tel service. Adieu.","Capitaine, tout votre équipage est tout guindé, il n'y a pas un seul homme avec qui boire ou parler. J'ai une forte aversion pour un tel service. Adieu.","Capitaine, je pensais servir sous un véritable corsaire, mais tout ce que nous faisons, c'est de la charité ! Je ne veux plus perdre mon temps. Je m'en vais."));
			Link.l1 = RandPhraseSimple("Je vois. Compte tenu de ton attitude, cela aurait dû arriver tôt ou tard. Très bien, je ne te retiendrai pas.","Votre déclaration n'était pas inattendue. Franchement, je suis insatisfait de votre attitude depuis un certain temps.")+"Meilleure des chances.";
			Link.l1.go = "exit_fire_1";
			if (sti(Pchar.money) >= sti(NPChar.rank)*500)
			{
				Link.l2 = "Je savais que tu partirais bientôt... ce service n'est pas pour toi. Mais ne m'accuse de rien. Voici "+sti(NPChar.rank)*500+" pesos, ils seront utiles pendant que tu cherches un nouveau travail.";
				Link.l2.go = "Im_kind_A2";
			}
			Link.l3 = RandPhraseSimple("Hmm. Maintenant, c'est une déclaration sérieuse. Mais vous n'avez pas encore remboursé tout l'argent qui vous a été versé à l'avance. Donc, votre démarche peut être considérée comme une tentative d'extorsion, n'est-ce pas?","Oh, je vois... Que disent les règlements du navire? Ici, paragraphe deux: 'Celui qui tente de partir sans permission sera débarqué sur une rive déserte avec un seul sac de poudre, une flasque d'eau, un pistolet et une seule balle.' Alors, comment ça te plairait?");
			Link.l3.go = "WantToGo_stop";
		}
		break;
		
		case "WantToGo_stop":
			if (Npchar.alignment == "good")
			{
				dialog.text = LinkRandPhrase("Ne tente même pas de m'insulter! Je travaille pour de l'argent, mais j'ai toujours le droit de choisir un travail à mon goût!","Je suis un homme libre! Et j'ai le droit de prendre un nouvel emploi quand je veux!","Je ne suis pas un esclave pour travailler pour de la nourriture, donc ma conscience est claire ! Mais je ne participerai plus aux vols !");
				Link.l1 = "Eh bien, en fait, vous vous trompez... Pendant que vous buviez à la taverne, vous pouviez choisir le travail que vous vouliez... Mais dès que vous avez mis le pied sur mon navire, votre seul moyen de retour est devenu un boulet de canon qui brise votre cou... Et avec votre langue arrachée, pour que vous ne révéliez rien dans l'autre monde...";
				if (makeint(Pchar.Rank) > makeint(NPchar.Rank))
				{
					Link.l1.go = "WantToGo_stop_stay";
				}
				else
				{
					Link.l1.go = "WantToGo_stop_fight";	
				}
				Link.l2 = "D'accord. Tu peux partir... Mais Dieu t'interdise de me rencontrer en mer ouverte. Je jure, tu regretteras le moment où tu as décidé de ne pas rester à mes côtés.";
				Link.l2.go = "exit_fire_5";
			}
			else
			{
				dialog.text = LinkRandPhrase("Ne tente même pas de m'intimider ! Je travaille pour de l'argent, mais j'ai toujours le droit de choisir un travail à mon goût !","Je suis un homme libre ! Et j'ai le droit de prendre un nouvel emploi quand je le veux !","Je ne suis pas votre esclave! Et je ne vais pas continuer à mener une vie misérable sur votre vieille baignoire!");
				Link.l1 = "Eh bien, en fait, vous vous trompez... Pendant que vous buviez à la taverne, vous pouviez choisir le travail que vous vouliez... Mais dès que vous avez mis le pied sur mon navire, votre seul moyen de retour est devenu un boulet de canon qui brise votre cou... Et avec une langue arrachée, pour que vous ne divulgâchiez rien dans l'autre monde...";
				// belamour legendary edition можно запугать офицера -->
				//if (makeint(Pchar.Rank) > makeint(NPchar.Rank) || CheckCharacterPerk(pchar, "IronWill"))
				if (makeint(Pchar.Rank) > makeint(NPchar.Rank))
				{
					Link.l1.go = "WantToGo_stop_stay";
				}
				else
				{
					Link.l1.go = "WantToGo_stop_fight";	
				}
				Link.l2 = "D'accord. Tu peux partir... Mais Dieu t'interdise de me rencontrer en mer ouverte. Je jure, tu regretteras le moment où tu as décidé de ne pas rester à mes côtés.";
				Link.l2.go = "exit_fire_5";
			}
		break;
		
		case "WantToGo_stop_stay":
			dialog.text = RandPhraseSimple("Si tu le mets de cette façon, je resterai, je n'ai simplement pas d'autre choix. Mais garde à l'esprit que je ne fais pas ça de mon plein gré...","D'accord, si tu le dis comme ça, je resterai. Mais sache que ce faisant, je vais contre ma propre volonté.");
			Link.l1 = RandPhraseSimple("C'est d'accord... Sers jusqu'à ce que je décide quand te laisser partir.","C'est bien. Continue à servir... Je déciderai quand te laisser partir.");
			Link.l1.go = "WantToGo_Munity"; //этот линк ведет к бегству
		break;
		
		case "WantToGo_stop_fight":
			dialog.text = NPCharRepPhrase(NPChar,"Vous ne me forcerez jamais à reconsidérer ! Vous n'avez aucun droit de me garder comme un esclave ! Je vais partir, restez à l'écart ou vous êtes foutu.","Vous pensez que vous pouvez effrayer un officier vétéran?! Plus d'une fois, j'ai été à un cheveu de la mort. Et si vous le mettez de cette façon, il est bien mieux de mourir dans une bataille juste plutôt que pendant un pillage sanglant!");
			Link.l1 = NPCharRepPhrase(NPChar,"Eh bien... chacun choisit son propre destin. J'espère que tu as dit tes prières avant de venir à moi.","Si je savais ce qui se passerait quand je t'ai ramassé à la taverne, je t'aurais laissé pendre à la potence à la place. Et il n'est pas trop tard pour arranger ça...");
			Link.l1.go = "WantToGo_stop_fight_1";
			Link.l2 = NPCharRepPhrase(NPChar,"Eh bien, tu peux partir si tu as tant besoin de ta liberté. Mais je ne te donne aucune recommandation.","D'accord. Tu peux partir... Mais Dieu te garde de me rencontrer en pleine mer. Je jure, tu regretteras le moment où tu as décidé de ne pas rester à mes côtés.");
			Link.l2.go = "exit_fire_5";	
		break;
		
		case "WantToGo_stop_fight_1":
			ChangeOfficersLoyality("bad_all", 1);
			ChangeCharacterComplexReputation(pchar,"nobility", -1);
			ChangeCharacterComplexReputation(pchar,"authority", -1);
			dialog.text = NPCharRepPhrase(NPChar,"Arrêtez de m'intimider déjà ! Lequel de vos larbins osera se dresser contre moi ? Si j'étais capitaine, ils rouleraient dans l'argent maintenant ! Et après vous être engagé dans toute cette charité, vous craignez que votre équipage prenne mon parti ?!","Laisse tomber tes manières, tu ne me feras pas peur! Adieu.");
			Link.l1 = NPCharRepPhrase(NPChar,"Non, mate, tu ne vivras pas assez longtemps pour arriver à la potence. Un tel luxe n'est pas pour toi...","Pas si vite, mon pote, nous ne sommes toujours pas quittes, tu me dois quelque chose.");
			Link.l1.go = "Get_out_fight";
		break;	
		///////////////////////////////////////////////////////////////////////////////////
		case "WantToGo_Munity":	//zagolski. отыгрыш бегство офицера
			Diag.TempNode = "Hired";
			// belamour legendary edition в ближайшее время не подойдет от страха
			/* if(CheckCharacterPerk(pchar, "IronWill"))
			{
				Npchar.loyality = makeint(Npchar.loyality) + 3 + hrand(sti(GetSummonSkillFromNameToOld(pchar,SKILL_FORTUNE)+GetSummonSkillFromNameToOld(pchar,SKILL_LEADERSHIP)));
				log_info(GetFullName(Npchar)+" increased his loyalty");
				log_testinfo("Loyalty has become: " + Npchar.loyality + " of " + MAX_LOYALITY);
			}
			else
			{ */
				if (!CheckAttribute(pchar, "questTemp.MutinyOfficerIDX"))
				{
					pchar.questTemp.MutinyOfficerIDX = npchar.index;
					npchar.quest.Mutiny = true; // mitrokosta доп защита от багов
					SetFunctionTimerCondition("mOfficer_fc", 0, 0, 1, false);
				}
			//}
			Diag.CurrentNode = Diag.TempNode;
			NPChar.quest.meeting = true;
			NPChar.location = "none";
			LAi_SetOfficerType(NPChar);
			DialogExit();
		break;
		////////////////////////////////////////////////////////////////////
		// пассажир возмущен игроком и сваливает <--
		
		case "Node_2":
			dialog.text = NPCharRepPhrase(Npchar,RandSwear()+"Je suis le meilleur "+XI_ConvertString(Npchar.quest.officertype)+" dans ces eaux. "+Npchar.quest.officertype_2+"Et je suis prêt à vous rendre service et à servir sous vos ordres.","Eh bien, ils disent que je ne suis pas mauvais "+XI_ConvertString(Npchar.quest.officertype)+". "+Npchar.quest.officertype_2+"Vous pouvez me prendre sur votre navire, capitaine, et voir par vous-même.");
			Link.l1 = "Et combien voulez-vous ?";
			Link.l1.go = "price";
			Link.l2 = "Et quel genre de spécialiste êtes-vous ?";
			Link.l2.go = "ShowParam_exit";
			Link.l3 = "Hélas, j'ai déjà un "+XI_ConvertString(Npchar.quest.officertype)+".";
			Link.l3.go = "Exit";
		break;

		case "OnceAgain":
			if (LAi_grp_playeralarm > 0)
			{
       			dialog.text = RandPhraseSimple("Heh, capitaine, la moitié de la garnison est après vous en ce moment. Sûrement ce n'est pas le meilleur moment pour être embauché dans votre équipage !","Et se battre pour atteindre le navire ? Non, cap, une autre fois...");
				link.l1 = RandPhraseSimple("Comme vous voulez...","En fait, je n'avais pas l'intention de vous embaucher."); 
				link.l1.go = "exit";
				break;
			}
			Diag.TempNode = "OnceAgain";
			dialog.text = "Avez-vous changé d'avis, capitaine? Déterminé qu'un nouveau "+XI_ConvertString(Npchar.quest.officertype)+" ne ferait pas mal ?";
			// boal -->
			if (FindFreeRandomOfficer() > 0)
			{
                Link.l1 = "Quelque chose comme ça. Combien en voulez-vous?";
                Link.l1.go = "price";
			}
			Link.l2 = "Et de quoi êtes-vous capable ?";
			Link.l2.go = "ShowParam_exit";
			// boal <--
			Link.l3 = "J'ai un jeu complet. A bientôt.";
			Link.l3.go = "exit";
		break;

		case "price":
			dialog.text = "Je pense que nous pouvons nous mettre d'accord sur "+Npchar.quest.OfficerPrice+" pesos.";
			if(Npchar.rank >= 15)
			{
				dialog.text = "Je pense que nous pouvons tomber d'accord sur "+(makeint(Npchar.quest.OfficerPrice)/ 100+30)+" doublons.";
			}	
			Link.l1 = "N'est-ce pas un peu trop ?";
			Link.l1.go = "trade";
			Link.l2 = "Je suis d'accord. Considère-toi comme faisant partie de l'équipage.";
			Link.l2.go = "hire";
			Link.l3 = "Tu ne vaux pas cet argent.";
			Link.l3.go = "exit";
		break;

		case "trade":
			if (GetSummonSkillFromNameToOld(pchar, SKILL_COMMERCE) >= Rand(12) && (sti(Npchar.quest.OfficerPrice) - GetCharacterSkillToOld(Pchar, "commerce")*100) >= sti(Npchar.quest.OfficerLowPrice))// bug fix
			{
				Npchar.quest.OfficerPrice = makeint(makeint(Npchar.quest.OfficerPrice) - GetCharacterSkillToOld(Pchar, "commerce")*100); // пусть будет коммерция перса голой
				dialog.text = "D'accord... Je suppose que je pourrais même être d'accord sur "+Npchar.quest.OfficerPrice+" pesos. Que dites-vous?";
				if(Npchar.rank >= 15)
				{
					dialog.text = "Je suppose que je pourrais même être d'accord sur "+(makeint(Npchar.quest.OfficerPrice)/ 100+30)+" des doublons. Que dites-vous?";
				}
				Link.l1 = "Voilà qui est mieux. Tu es dedans.";
				Link.l1.go = "hire";				
				Link.l2 = "Je pense toujours que c'est un peu trop. Au revoir.";
				Link.l2.go = "exit";
			}
			else
			{
				dialog.text = "Je suis désolé, capitaine, mais je vaux exactement ce que j'ai demandé. Si c'est trop pour vous, alors allez trouver quelqu'un d'autre.";
				Link.l1 = "D'accord, je suis d'accord. Je vais t'emmener.";
				Link.l1.go = "hire";				
				Link.l2 = "C'est ce que je vais faire. Adieu.";
				Link.l2.go = "exit";
			}
		break;

		case "hire":
			dialog.text = "Je vois que vous manquez d'argent, capitaine! Je suis désolé, mais je ne travaille pas à crédit.";
			Link.l1 = "Oh, diable!";
			Link.l1.go = "Exit";
			if(Npchar.rank < 15 && makeint(Pchar.money) >= makeint(Npchar.quest.OfficerPrice))
			{
				AddMoneyToCharacter(Pchar, -(makeint(Npchar.quest.OfficerPrice)));
				Diag.TempNode = "OnboardSoon";
				dialog.text = "Merci, capitaine. Vous ne regretterez pas votre choix.";
				Link.l1 = "J'espère bien.";
				Link.l1.go = "Exit_hire";								
			}
			if(Npchar.rank >= 15 && PCharDublonsTotal() >= makeint((makeint(Npchar.quest.OfficerPrice) / 100 + 30)))
			{
				RemoveDublonsFromPCharTotal(makeint((makeint(Npchar.quest.OfficerPrice) / 100 + 30)));
				Diag.TempNode = "OnboardSoon";
				dialog.text = "Merci, capitaine. Vous ne regretterez pas votre choix.";
				Link.l1 = "J'espère bien.";
				Link.l1.go = "Exit_hire";								
			}
		break;

		case "OnboardSoon":			
			Diag.TempNode = "OnboardSoon";
			dialog.text = "Je vais juste finir mon verre, capitaine, et ensuite j'irai au navire. Ne vous inquiétez pas, je serai là à temps.";
			Link.l1 = "D'accord. Si tu es en retard, je te ferai nettoyer le pont!";
			Link.l1.go = "Exit";											
		break;
        
		case "QMASTER_1":
			if(sti(PChar.Ship.Type) == SHIP_NOTUSED)
			{
				dialog.text = "Capitaine, mais vous n'avez pas de navire!";
				Link.l1 = "Merci de me le rappeler...";
				Link.l1.go = "Exit";
				Diag.TempNode = "Hired";
				break;
			}
			// Rebbebion, добавил фикс отображения знака процента
			dialog.text = "Activité maximale des rats en voyage "+FloatToString(50.0 /(2.0+GetSummonSkillFromNameToOld(PChar,SKILL_REPAIR)+GetSummonSkillFromNameToOld(PChar,SKILL_SNEAK)),1)+"%% de la quantité totale de cargaison. Pour "+GetCrewQuantity(PChar)+" des marins nous aurons besoin "+makeint((GetCrewQuantity(PChar)+6)/ 10)+" nourriture par jour. Cela sans tenir compte des esclaves en cours de transport.";
			Link.l1 = "Merci.";
			Link.l1.go = "Exit";
			Diag.TempNode = "Hired";
		break;
        
        // boal 05.09.03 offecer need to go to abordage -->
        case "stay_follow":
            dialog.text = "Quels sont vos ordres?";
            Link.l1 = "Reste ici !";
            Link.l1.go = "Boal_Stay";
            Link.l2 = "Suivez-moi et ne restez pas à la traîne!";
            Link.l2.go = "Boal_Follow";
            // boal 05.09.03 offecer need to go to abordage <--
			if (npchar.id == "OffMushketer")
			{
				Link.l3 = "Je veux que tu restes à une certaine distance de la cible.";
				Link.l3.go = "TargetDistance";
			}
			
			if(CheckAttribute(NPChar, "equip.gun"))
			{
				if(CheckAttribute(NPChar, "chr_ai.gun.bulletNum") && sti(NPChar.chr_ai.gun.bulletNum) > 1)
				{
					Link.l4 = "Nous devons changer le type de munitions pour votre arme à feu.";
					Link.l4.go = "SetGunBullets";
				}	
			}
			if(CheckAttribute(NPChar, "equip.musket"))
			{
				if(CheckAttribute(NPChar, "chr_ai.musket.bulletNum") && sti(NPChar.chr_ai.musket.bulletNum) > 1)
				{
					Link.l5 = "Nous devons changer le type de munitions pour votre mousquet.";
					Link.l5.go = "SetMusketBullets";
				}
					Link.l6 = "Nous devons changer votre arme prioritaire pour le combat.";
					Link.l6.go = "SetPriorityMode";
			}
		break;

		case "SetGunBullets":
			Dialog.Text = "Sélectionnez le type de munitions:";
			sGun = GetCharacterEquipByGroup(NPChar, GUN_ITEM_TYPE);
			rItm = ItemsFromID(sGun);
			makearef(rType, rItm.type);	
			for (i = 0; i < sti(NPChar.chr_ai.gun.bulletNum); i++)
			{
				sAttr = GetAttributeName(GetAttributeN(rType, i));
				sBullet = rItm.type.(sAttr).bullet;
				rItem = ItemsFromID(sBullet);								
				attrL = "l" + i;
				Link.(attrL) = GetConvertStr(rItem.name, "ItemsDescribe.txt");
				Link.(attrL).go = "SetGunBullets1_" + i;
			}
		break;	

		case "SetGunBullets2":
			i = sti(NPChar.SetGunBullets) + 1; 
			sGun = GetCharacterEquipByGroup(NPChar, GUN_ITEM_TYPE);
			rItm = ItemsFromID(sGun);
			sAttr = "t" + i;
			sBullet = rItm.type.(sAttr).bullet;
			LAi_SetCharacterUseBullet(NPChar, GUN_ITEM_TYPE, sBullet);
			LAi_GunSetUnload(NPChar, GUN_ITEM_TYPE);
			Diag.CurrentNode = Diag.TempNode;
			rItem = ItemsFromID(sBullet);
			notification(GetFullName(NPChar)+" "+XI_ConvertString("AmmoSelectNotif")+GetConvertStr(rItem.name, "ItemsDescribe.txt")+"", "AmmoSelect");
			DeleteAttribute(NPChar,"SetGunBullets");
			DialogExit();
		break;
		
		case "SetMusketBullets":
			Dialog.Text = "Sélectionnez le type de munitions:";
			sGun = GetCharacterEquipByGroup(NPChar, MUSKET_ITEM_TYPE);
			rItm = ItemsFromID(sGun);
			makearef(rType, rItm.type);	
			for (i = 0; i < sti(NPChar.chr_ai.musket.bulletNum); i++)
			{
				sAttr = GetAttributeName(GetAttributeN(rType, i));
				sBullet = rItm.type.(sAttr).bullet;
				rItem = ItemsFromID(sBullet);								
				attrL = "l" + i;
				Link.(attrL) = GetConvertStr(rItem.name, "ItemsDescribe.txt");
				Link.(attrL).go = "SetMusketBullets1_" + i;
			}
		break;	

		case "SetMusketBullets2":
			i = sti(NPChar.SetMusketBullets) + 1; 
			sGun = GetCharacterEquipByGroup(NPChar, MUSKET_ITEM_TYPE);
			rItm = ItemsFromID(sGun);
			sAttr = "t" + i;
			sBullet = rItm.type.(sAttr).bullet;
			LAi_SetCharacterUseBullet(NPChar, MUSKET_ITEM_TYPE, sBullet);
			LAi_GunSetUnload(NPChar, MUSKET_ITEM_TYPE);
			Diag.CurrentNode = Diag.TempNode;
			rItem = ItemsFromID(sBullet);
			notification(GetFullName(NPChar)+" "+XI_ConvertString("AmmoSelectNotif")+GetConvertStr(rItem.name, "ItemsDescribe.txt")+"", "AmmoSelect");
			DeleteAttribute(NPChar,"SetMusketBullets");
			DialogExit();
		break;
		
		case "SetPriorityMode":
			Dialog.Text = "Au début du combat, vous utiliserez:";
			Link.l1 = "Lame";
			Link.l1.go = "BladePriorityMode";
			Link.l2 = "Mousquet";
			Link.l2.go = "MusketPriorityMode";
		break;
		
		case "BladePriorityMode":
            SetPriorityMode(NPChar, 1);
			DialogExit();
		break;
		
		case "MusketPriorityMode":
			SetPriorityMode(NPChar, 2);
			DialogExit();
		break;
		
		case "TargetDistance":
			dialog.text = "Quelle distance exactement, capitaine ? Indiquez en pas, mais pas plus de 20.";
			link.l1 = "";
			Link.l1.edit = 3;
			link.l1.go = "TargetDistance_1";			
		break;
		case "TargetDistance_1":
			iTemp = sti(dialogEditStrings[3]);
			if (iTemp < 0)
			{
				dialog.text = "Capitaine, êtes-vous bien?";
				link.l1 = "Je suis désolé, ma faute...";
				link.l1.go = "exit";
				break;
			}
			if (iTemp == 0)
			{
				dialog.text = "Je resterai sur place sans bouger. Est-ce que c'est ce que vous voulez de moi, capitaine?";
				link.l1 = "Oui. C'est exactement ce qu'on attend de vous.";
				link.l1.go = "exit";
				npchar.MusketerDistance = 0;
				break;
			}
			if (iTemp > 20)
			{
				dialog.text = "Je crois que je t'ai dit que je ne peux pas être à plus de 20 pas de la cible.";
				link.l1 = "D'accord, garde une distance de 20 mètres.";
				link.l1.go = "exit";
				npchar.MusketerDistance = 20.0;
				break;
			}
			dialog.text = "Compris et pris en compte.";
			link.l1 = "D'accord.";
			link.l1.go = "exit";
			npchar.MusketerDistance = iTemp;
		break;

		case "AsYouWish":
			// проверка на море -->
			if (bSeaActive)
			{
				attr = Sea_FindNearColony();
				if (attr == "none")
				{
					dialog.text = "Capitaine, bien que je ne comprenne vraiment pas votre raisonnement, pourrions-nous en discuter sur la rive? Ou avez-vous décidé de simplement me jeter par-dessus bord?";
					Link.l1 = "Hmm... Non, ce n'est pas ce que je voulais dire. Reste ici jusqu'à ce que nous arrivions au port.";
					Link.l1.go = "Exit";	
					break;	
				}
			}
			// проверка на море <--
			if (makeint(PChar.reputation.nobility) >= 41 && makeint(NPChar.reputation) < 41) //герой против злодея
			{
				dialog.text = RandPhraseSimple(LinkRandPhrase("Maintenant, c'est du nouveau !","Pourquoi, au nom du ciel?","Quelle est la raison?!"),RandPhraseSimple("Capitaine, êtes-vous fou? Annoncer une telle nouvelle sans crier gare!","Wow ! Et qu'est-ce que j'ai fait pour vous déplaire ?"));
				Link.l1 = RandPhraseSimple(LinkRandPhrase("J'ai décidé de mettre de l'ordre dans l'équipage. Et je n'aime pas vos relations avec vos collègues","Vos avantages n'étaient pas aussi bons que discuté lors de l'embauche. Alors,","Les voyous et les vauriens dans mon équipe ne resteront pas ! Alors,"),LinkRandPhrase("Il est venu à ma connaissance que tu voles du rhum, habituant secrètement mon équipage à boire dur et abaissant ainsi son moral. Par conséquent,","J'en ai assez de vos manières de bandit et je ne vais pas le tolérer. Alors,","Passez constamment votre temps dans la cabine centrale pour une partie de cartes ou de dés, distrayant les autres officiers de l'exécution du devoir. Ceci ne peut pas continuer indéfiniment. Donc,"))+"range tes affaires et quitte le navire.";
				if (makeint(Pchar.Rank) > makeint(NPchar.Rank))
				{
					Link.l1.go = "Get_out_A1_peace";
				}
				else
				{
					Link.l1.go = "Get_out_A1_strife";
				}
				break;	
			}
			if (makeint(PChar.reputation.nobility) >= 41 && makeint(NPChar.reputation) >= 41) // герой против героя
			{
				dialog.text = RandPhraseSimple(RandPhraseSimple("Puis-je connaître la raison d'une telle décision?","De toute évidence, une telle décision est bien fondée?"),RandPhraseSimple("Expliquez-vous, capitaine","C'est assez inattendu. Mais j'aimerais toujours connaître la raison."));
				Link.l1 = RandPhraseSimple(LinkRandPhrase("Je suis totalement insatisfait de votre attitude envers vos devoirs.","Malheureusement, tu n'as pas fait un bon officier et tu ne le seras probablement jamais...","Tu es un bon officier et ton service a été juste, mais maintenant nos chemins se sont séparés. Ne me demande pas pourquoi."),LinkRandPhrase("Je t'ai prévenu que ta passion pour le rhum te détruirait. Comment puis-je faire confiance à un homme dans un combat qui n'est même pas capable de ranger son épée dans son fourreau?","Vous êtes un marin et un officier terrible... Je pense, vous serez sur la plage plus que dans la mer.","Je ne suis pas satisfait de vos qualifications, mais maintenant j'ai enfin trouvé un remplacement décent."));
				Link.l1.go = "Get_out_A2";
				break;	
			}
			if (makeint(PChar.reputation.nobility) < 41 && makeint(NPChar.reputation) >= 41) // злодей против героя 
			{		
				dialog.text = RandPhraseSimple(RandPhraseSimple("Hmm... Puis-je connaître la raison?","C'est une déclaration sérieuse. Puis-je savoir avec quoi en particulier vous êtes insatisfait?"),RandPhraseSimple("Expliquez-vous, capitaine.","De toute évidence, une telle déclaration est bien fondée?"));
				Link.l1 = RandPhraseSimple(LinkRandPhrase("Je suis totalement insatisfait de votre qualification, donc","Malheureusement, tu ne t'es pas montré un officier décent. Alors,","J'en ai assez de tes manières nobles. Je ne vais pas les tolérer indéfiniment, alors"),LinkRandPhrase("J'ai appris que vous incitez l'équipage à la désobéissance. Il n'y aura pas de troubles sur mon navire ! Et ne me remerciez pas de ne pas vous avoir jeté avant. Alors","Vos nobles principes vous honorent, mais ils sont contraires à la vie de brigand d'un corsaire libre. Alors","Je n'aime pas votre rapport à vos devoirs. Alors"))+" emballe tes affaires et quitte le navire.";
				if (makeint(Pchar.Rank) > makeint(NPchar.Rank))
				{
					Link.l1.go = "Get_out_A3_peace";
				}
				else
				{
					Link.l1.go = "Get_out_A3_strife";
				}	
				break;
	
			}
			if (makeint(PChar.reputation.nobility) < 41 && makeint(NPChar.reputation) < 41) // злодей против злодея
			{	
				dialog.text = RandPhraseSimple(LinkRandPhrase("Capitaine, je ne m'y attendais vraiment pas ! Peut-être pourriez-vous expliquer ce qui se passe ?","Capitaine, qu'est-ce qui te ronge?!","Que voulez-vous dire par là, capitaine?!"),RandPhraseSimple("Que diable, capitaine?! Tout semblait bien hier, et maintenant nous voici, que s'est-il passé?","Wow ! Peut-être, pourriez-vous vous expliquer ?"));
				Link.l1 = RandPhraseSimple(LinkRandPhrase("Tu es un fainéant total et un idiot inutile même un mousse sur un caboteur ferait mieux. J'ai trop souffert à cause de toi. Alors","Je pensais à te virer depuis un moment, et maintenant j'ai enfin trouvé un remplaçant convenable. Donc","Il est venu à ma connaissance que tu voles du rhum, habituant secrètement mon équipage à boire dur et abaissant ainsi son moral. Par conséquent"),LinkRandPhrase("Quand je vous embauchais, vous vous vantiez d'être le meilleur officier de toute la flotte, mais il s'est avéré que vous n'étiez qu'un fainéant, alors","Je t'ai prévenu que ton habitude de boire finirait mal. Pourquoi devrais-je garder un ivrogne inutile sur mon navire? Alors","Au lieu de servir, tu es constamment en train de vagabonder quelque part ou de jouer aux cartes ou aux dés. J'espère que tu ne pensais pas que cela pourrait durer éternellement? Alors"))+" emballe tes affaires et quitte le navire.";
				Link.l1.go = "Get_out_A4";
				break;
			}
		break;
	
		case "Get_out_A1_peace":
			dialog.text = RandPhraseSimple(LinkRandPhrase("Alors comment tu parles maintenant ! Très bien, comme tu veux. Mais sois assuré : je ne reviendrai pas vers toi, même si je meurs de faim !","Franchement, je n'aime pas beaucoup vos jeux nobles non plus. Alors au revoir...","Oh, va en enfer! Reste avec tes lèche-bottes. Un 'héros', en effet!"),LinkRandPhrase("En réalité, je n'ai jamais aimé vous servir ... Vous avez une péniche de cargaison là, pas un navire décent. Une école de finition, plus probablement ...","Vous savez, j'en ai assez de votre équipage, tous ces pantalons fantaisie, juste des petits enfants, pas un seul homme véritable...","D'accord, capitaine, comme vous dites. Mais Dieu sait, je faisais bien mon travail..."));
			Link.l1 = "Attends. Pour le moment, je ne peux pas quitter le navire sans un officier. Mais plus tard, nous reviendrons à cette conversation.";
			Link.l1.go = "exit_bad";
			Link.l2 = "Alors, va en paix.";
			Link.l2.go = "Exit_Fire_1";
			if (sti(Pchar.money) >= sti(NPChar.rank)*500)
			{
				Link.l3 = "Ne te fâche pas. J'ai préparé pour toi une indemnité de départ - "+sti(NPChar.rank)*500+" pesos. J'espère que cela éliminera toutes les questions.";
				Link.l3.go = "Get_out_А1_ForMoney";
			}
		break;

		case "Get_out_A1_strife":
			dialog.text = LinkRandPhrase("Excusez-moi ! Que voulez-vous dire par 'quitter le navire'?! Je n'ai pas exposé ma tête au mitraillage juste pour que vous puissiez me jeter quand bon vous semble!","Ha ! 'Quitter le navire' ! Penses-tu sérieusement que je te permettrai de me jeter comme un chaton ?!","Doucement, capitaine, les gens sérieux ne règlent pas les choses de cette façon. Je ne serai pas traité comme un novice.");
			Link.l1 = "D'accord, tu peux rester pour l'instant - mais seulement jusqu'à ce que je trouve un substitut convenable.";
			Link.l1.go = "exit_bad";
			Link.l2 = "Je répète, votre service est terminé. Vous pouvez emballer vos affaires.";
			Link.l2.go = "Get_out_A1_strife_1";
			if (sti(Pchar.money) >= sti(NPChar.rank)*500)
			{
				Link.l3 = "Ne te fâche pas. J'ai préparé "+sti(NPChar.rank)*500+"des pesos pour toi. J'espère que cela éliminera toutes les questions.";
				Link.l3.go = "Get_out_А1_ForMoney";
			}
		break;

		case "Get_out_A1_strife_1":
			dialog.text = RandPhraseSimple("En fait, je ne brûle pas d'envie de rester ici. Mais je ne partirai pas non plus sans compensation !","Maintenant, je ne resterai certainement pas sur cette vieille baignoire à vous, mais d'abord vous allez me dédommager !")+" "+sti(NPChar.rank)*1000+" pesos, et nous nous oublierons l'un l'autre.";
			Link.l1 = "Je me suis un peu emporté... S'il vous plaît, acceptez mes excuses et retournez à vos devoirs.";
			Link.l1.go = "exit_bad1";
			Link.l2 = "De quel argent parles-tu si tu as toujours reçu ta juste part? Ça ressemble à de l'extorsion pour moi!";
			Link.l2.go = "Get_out_А1_strife_battle";
			if (sti(Pchar.money) >= sti(NPChar.rank)*1000)
			{
				Link.l3 = "D'accord. Rends l'équipement, et alors tu auras ce que tu as demandé.";
				Link.l3.go = "Get_out_А1_chang";
			}
		break;

		case "Get_out_А1_ForMoney":
			AddMoneyToCharacter(Pchar, -(makeint(sti(NPChar.rank)*500)));
			ChangeCharacterComplexReputation(pchar,"nobility", 1);
			ChangeCharacterComplexReputation(pchar,"authority", 0.5);
			dialog.text = "C'est une autre histoire. Adieu !";
			Link.l1 = "J'espère que nos chemins ne se croiseront plus jamais.";
			Link.l1.go = "Exit_Fire_1";
		break;

		case "Get_out_А1_strife_battle":
			dialog.text = LinkRandPhrase("Considérez cela comme une compensation pour le préjudice moral. Je ne tolérerai pas un tel traitement, et quiconque ose me traiter ainsi le regrettera!","Ceci n'est pas une extorsion, mais plutôt une compensation pour cette stupide perte de mon temps ! Et je l'obtiendrai, quel qu'en soit le coût !","J'ai perdu trop de temps à servir sous un mollasson comme toi. Je pourrais faire fortune en pillant des navires marchands. Alors je veux juste compenser mon profit perdu.");
			if (sti(Pchar.money) >= sti(NPChar.rank)*1000)
			{
				Link.l1 = "D'accord. Voici ton argent... Et maintenant fiche le camp!";
				Link.l1.go = "Get_out_А1_ForMoney_angry";
			}
			Link.l2 = "On dirait que tu oublies qui tu es! Je ne permettrai pas à des imbéciles comme toi de me crier dessus!";
			Link.l2.go = "Get_out_А1_strife_death";
		break;

		case "Get_out_А1_strife_death":
			ChangeCharacterComplexReputation(pchar,"nobility", 1);
			ChangeCharacterComplexReputation(pchar,"authority", -1);
			OfficersReaction("good");
			dialog.text = "Allez-y, capitaine! Montrez-vous!";
			Link.l1 = "Dieu le sait, je ne le voulais pas !";
			Link.l1.go = "Get_out_fight";
		break;
	
		case "Get_out_А1_ForMoney_angry":
			AddMoneyToCharacter(Pchar, -(makeint(sti(NPChar.rank)*1000)));
			ChangeCharacterComplexReputation(pchar,"nobility", -1);
			ChangeCharacterComplexReputation(pchar,"authority", 0.5);
			OfficersReaction("bad");
			dialog.text = "C'est une autre histoire. Adieu!";
			Link.l1 = "J'espère que nos chemins ne se croiseront plus jamais.";
			Link.l1.go = "Exit_Fire_1";
		break;

		case "Get_out_A2":
			dialog.text = RandPhraseSimple(LinkRandPhrase("Eh bien, c'est décidé, alors. Adieu, capitaine, et ne gardez aucune rancune...","Dommage, capitaine. Mais Dieu le sait, j'ai essayé. Adieu.","Eh bien, capitaine, vous êtes certainement difficile à satisfaire! Bon, bonne chance à vous."),LinkRandPhrase("Dommage, capitaine. Vous savez, j'aimais travailler pour vous.","Ouais, des choses arrivent... Mais je ne garde pas rancune. Adieu.","Vous êtes injuste envers moi, capitaine. Pourtant, je respecte votre décision. Adieu."));
			Link.l1 = "Attends, j'ai changé d'avis. Reparlons de cela plus tard.";
			Link.l1.go = "exit_good";
			Link.l2 = "Ne sois pas fâché. Bonne chance à toi...";
			Link.l2.go = "exit_fire_2";
			Link.l3 = "Attends... Je t'ai bien équipé. Rends-les, je ne vais pas équiper une horde...";
			Link.l3.go = "Return_items_A2";
			if (sti(Pchar.money) >= sti(NPChar.rank)*500)
			{
				Link.l4 = "Attends... Je ne veux pas te laisser partir les mains vides. Tiens, prends "+sti(NPChar.rank)*500+" pesos. Cela vous sera utile pendant que vous cherchez un nouvel emploi.";
			}
			Link.l4.go = "Im_kind_A2";
		break;

		case "Return_items_A2":
			ChangeOfficersLoyality("bad_all", 1);
			dialog.text = "Oh, bien sûr, reprends tout...";
			Link.l1 = "Je sais que tu me comprends, n'est-ce pas...";
			Link.l1.go = "Get_out_А2_chang";
		break;

		case "Im_kind_A2":
			AddMoneyToCharacter(Pchar, -(makeint(sti(NPChar.rank)*500)));
			ChangeOfficersLoyality("good_all", 1);
			ChangeCharacterComplexReputation(pchar,"nobility", 1);
			ChangeCharacterComplexReputation(pchar,"authority", 0.5);
			dialog.text = "Merci, capitaine! Une générosité vraiment inattendue... Vous savez, j'ai encore quelques-unes de vos affaires, peut-être aimeriez-vous les récupérer?";
			Link.l1 = "Peut-être... Trouver une bonne lame n'est pas si facile ces jours-ci...";
			Link.l1.go = "Get_out_А2_chang";
			Link.l2 = "Oh, ne t'inquiète pas. Garde-les en souvenir de ton service.";
			Link.l2.go = "exit_fire_2";
		break;

		case "Get_out_A3_peace":
			dialog.text = RandPhraseSimple(LinkRandPhrase("D'accord, comme tu veux. Mais sois sûr : je ne reviendrai pas vers toi, même si je meurs de faim !!","Capitaine, vos manières de bandit en affaires me rendent également malade. Tôt ou tard, cela devait arriver. Et il n'y a pas besoin d'inventer des raisons.","Reste avec tes coupe-jarrets, alors. Un homme décent ne montrerait même pas son visage dans la salle des officiers de ton navire. Quel bordel tu as ici, Dieu me pardonne !"),LinkRandPhrase("Franchement, je n'aimais pas non plus mon service sous vos ordres. Vous avez engagé une équipe entière de coquins, pas un seul homme décent avec qui discuter.","Ouais, si tu continues avec cette attitude envers ton équipage, tu te retrouveras bientôt tout seul et il n'y aura plus besoin de chercher des excuses.","Notre inimitié est mutuelle, et cela me réconforte. Au revoir."));
			Link.l1 = "Attends. Maintenant ce n'est pas le meilleur moment pour ta retraite. Mais toutes les revendications restent.";
			Link.l1.go = "exit_bad";
			Link.l2 = "Allez, allez. Je m'en sortirai très bien sans vos leçons.";
			Link.l2.go = "exit_fire_3";
			if (sti(Pchar.money) >= sti(NPChar.rank)*500)
			{
				Link.l3 = "Attendez. Je vais vous donner "+sti(NPChar.rank)*500+" pesos. Je ne veux pas que tu meures dans le caniveau, pour que je me sente coupable de ça.";
				Link.l3.go = "Get_out_А3_ForMoney";
			}
		break;

		case "Get_out_А3_ForMoney":
			AddMoneyToCharacter(Pchar, -(makeint(sti(NPChar.rank)*500)));
			ChangeCharacterComplexReputation(pchar,"nobility", 1);
			ChangeCharacterComplexReputation(pchar,"authority", 0.5);
			ChangeOfficersLoyality("good_all", 1);
			dialog.text = LinkRandPhrase("Eh bien, merci. Au revoir...","Merci pour votre comprehension. Bonne chance.","Maintenant nous avons fini. Meilleure des chances...");
			Link.l1 = "Je sais que tu me comprends bien.";
			Link.l1.go = "exit_fire_3";
		break;
	
		case "Get_out_A3_strife":
			dialog.text = LinkRandPhrase("Mais capitaine, dans ce cas, je suis laissé à l'échouage. Êtes-vous vraiment prêt à m'envoyer du navire directement au parvis?","Vous êtes injuste envers moi, capitaine. Mais je ne tiendrai pas rancune si je reçois une compensation convenable.","Et c'est ta gratitude pour toutes mes blessures de combat? Eh bien, je suppose que je ne peux pas me passer de compensation monétaire.");
			Link.l1 = "D'accord, j'ai changé d'avis. Tu peux rester, mais nous reviendrons à cette conversation.";
			Link.l1.go = "exit_bad";
			if (sti(Pchar.money) >= sti(NPChar.rank)*500)
			{
				Link.l2 = "Oh, ne vous inquiétez pas pour ça. Tenez - "+sti(NPChar.rank)*500+" pesos. Cela compensera votre temps sur mon navire.";
				Link.l2.go = "Get_out_А3_ForMoney";
				Link.l3 = "Je te donnerai l'argent. Cependant, tu as été bien équipé grâce à moi, et je suppose qu'il est approprié de me rendre les choses.";
				Link.l3.go = "Return_items_A3";
			}
			Link.l4 = "Oh, vraiment ? Et qu'en est-il de ta part, que tu recevais régulièrement ?! Je savais que tout finirait par des plaintes et des demandes de prime.";
			Link.l4.go = "Get_out_A3_strife_1";
		break;

		case "Return_items_A3":
			dialog.text = "Je savais que vous diriez cela, mais vous ne récupérerez votre équipement que lorsque je recevrai "+sti(NPChar.rank)*1000+" pesos. Sinon, tu ne l'auras que sur mon cadavre !";
			Link.l1 = "D'accord, prenez votre argent, alors.";
			Link.l1.go = "Get_out_А3_chang";
			Link.l2 = "Êtes-vous fou ou quoi ?! Exiger une telle somme pour ce qui vous a été donné gratuitement ?! Je vois maintenant que votre avidité a clairement triomphé de votre bien-faisance feinte.";
			Link.l2.go = "Get_out_A3_strife_1";
		break;

		case "Get_out_A3_strife_1":
			dialog.text = "Ne vous avisez pas de m'insulter ! Je ne suis peut-être pas le meilleur de la Marine, mais je reste un officier de combat. Et je serai respecté, même par un rustre comme vous !";
			Link.l1 = "Si tu ne l'as pas encore compris, je vais le répéter une fois de plus : arrête de mendier, tu n'obtiendras rien de moi.";
			Link.l1.go = "Get_out_А3_strife_death";
		break;

		case "Get_out_А3_strife_death":
			ChangeCharacterComplexReputation(pchar,"nobility", -1);
			ChangeCharacterComplexReputation(pchar,"authority", -1);
			OfficersReaction("bad");
			dialog.text = "Eh bien, j'obtiendrai tout de même une satisfaction !";
			Link.l1 = "Oh, donc c'est un défi, n'est-ce pas? Comme vous voulez alors...";
			Link.l1.go = "Get_out_fight";
		break;

		case "Get_out_A4":
			dialog.text = RandPhraseSimple(LinkRandPhrase("C'est ma chance! J'ai mis mon coeur et mon âme au service juste pour être viré sans même une indemnité de service!","Quelle malchance?! Je suis embauché et ensuite je suis presque immédiatement renvoyé. Je n'ai aucune idée à quel saint allumer une bougie ces jours-ci...","Sapristi! Viré pour la troisième fois cette année, tous les lundis. Peut-être, je ne devrais pas me présenter devant le capitaine, quand j'ai la gueule de bois."),LinkRandPhrase("Eh bien, comme vous voulez. Priez pour que nous ne nous rencontrions jamais à nouveau.","Comme vous voulez. N'oubliez pas, cependant, que vous ne trouverez jamais un meilleur officier.","D'accord, capitaine, comme vous dites. Mais Dieu le sait, je faisais bien mon travail..."));
			Link.l1 = "Attends. Ce n'est pas le meilleur moment pour ta retraite. Mais toutes les réclamations sont en vigueur.";
			Link.l1.go = "exit_good";
			Link.l2 = RandPhraseSimple("Dégage maintenant. Et remercie Dieu que je sois de bonne humeur aujourd'hui.","Va-t'en maintenant. Tu es aussi bon officier que la merde est bonne pour faire des balles.");
			Link.l2.go = "exit_fire_4";
			if (sti(Pchar.money) >= sti(NPChar.rank)*500)
			{
				Link.l3 = "Attendez. Je vais vous donner "+sti(NPChar.rank)*500+" pesos. Je ne veux pas que tu meures dans le caniveau, pour que je me sente coupable de cela.";
				Link.l3.go = "Get_out_А4_ForMoney";
			}
			Link.l4 = "Attends... Je t'ai bien équipé, rends-moi mes affaires.";
			Link.l4.go = "Return_items_A4";
		break;

		case "Get_out_А4_ForMoney":
			AddMoneyToCharacter(Pchar, -(makeint(sti(NPChar.rank)*500)));
			ChangeCharacterComplexReputation(pchar,"nobility", 1);
			ChangeCharacterComplexReputation(pchar,"authority", 0.5);
			ChangeOfficersLoyality("good_all", 1);
			dialog.text = LinkRandPhrase("Oh, merci, capitaine! C'est vraiment gentil de votre part...","Merci pour votre compréhension. Bonne chance.","Maintenant, nous avons fini. Bonne chance...");
			Link.l1 = "Bonne chance. J'espère que tu ne la gaspilleras pas toute dans la première taverne.";
			Link.l1.go = "exit_fire_4";
		break;

		case "Return_items_A4":
			if (makeint(Pchar.Rank) > makeint(NPchar.Rank))
			{
				dialog.text = LinkRandPhrase("Et maintenant tu prends mon équipement! Oh, mon Dieu, au diable tout ça! Je vais pêcher, je le jure...","Je vois que vous avez décidé de me nettoyer complètement. Eh bien. Il ne me reste qu'une seule voie, vers le parvis...","Oh, merci beaucoup ! Maintenant, tu as décidé de me voler. Oh, quel sort cruel... Prends-le donc, prends-le ! Que puis-je faire de toute façon...");
				Link.l1 = "Dégage maintenant. Tu es aussi bon officier que la merde est bonne pour faire des balles.";
				Link.l1.go = "Get_out_А4_chang_1";
			}
			else	
			{
				dialog.text = RandPhraseSimple("Comme vous le souhaitez, capitaine, mais d'abord veuillez avoir la gentillesse de me donner "+sti(NPChar.rank)*1000+" pesos. Que cela soit une compensation pour le dommage moral.","D'accord. Mais je veux toujours recevoir "+sti(NPChar.rank)*1000+" pesos en compensation de mon service dur et fidèle.");
				if (sti(Pchar.money) >= sti(NPChar.rank)*1000)
				{
					Link.l1 = "Quel scélérat ! D'accord, voici votre argent.";
					Link.l1.go = "Get_out_А4_chang";
				}
				Link.l2 = "N'êtes-vous pas fou?! Osez-vous demander autant d'argent pour ce que je vous ai donné moi-même!";
				Link.l2.go = "Get_out_A4_strife";
				Link.l3 = "Ah-ha ! Je plaisantais ! Comment pourrais-je chasser un vieil ami, aussi troué soit son chapeau !";
				Link.l3.go = "exit_bad1";
			}
		break;

		case "Get_out_A4_strife":
			ChangeCharacterComplexReputation(pchar,"nobility", -1);
			ChangeCharacterComplexReputation(pchar,"authority", -1);
			ChangeOfficersLoyality("bad_all", 1);
			dialog.text = "Eh bien, alors tu n'auras rien! Je ne ferai pas un pas avant d'entendre le tintement de mon argent!";
			Link.l1 = RandPhraseSimple("Vous entendrez bientôt le tintement de mon épée!","Alors tu seras emporté les pieds devant !");
			Link.l1.go = "Get_out_fight";
		break;

		case "Get_out_fight":
			CheckForReleaseOfficer(GetCharacterIndex(Npchar.id));
			RemovePassenger(Pchar, Npchar);
			LAi_CharacterDisableDialog(NPChar);
			LAi_SetWarriorType(Npchar);
			LAi_group_MoveCharacter(Npchar, "TmpEnemy");
			LAi_group_SetHearRadius("TmpEnemy", 100.0);
			LAi_group_FightGroupsEx("TmpEnemy", LAI_GROUP_PLAYER, true, Pchar, -1, false, false);
			if (PChar.location == Get_My_Cabin() || findsubstr(PChar.location, "_tavern" , 0) != -1 || findsubstr(PChar.location, "_store" , 0) != -1)
            {
				LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
				LAi_group_SetCheck("TmpEnemy", "CannotFightCurLocation");
				LAi_group_SetCheck("TmpEnemy", "MainHeroFightModeOff");
            }
			DialogExit();
			AddDialogExitQuest("MainHeroFightModeOn");
		break;

	    case "Get_out_А1_chang": // интерфейс обмена
			Diag.TempNode = "Fired_1";
			LAi_CharacterDisableDialog(NPChar);
			AddMoneyToCharacter(Pchar, -(makeint(sti(NPChar.rank)*1000)));
			ChangeCharacterComplexReputation(pchar,"nobility", -1);
			Pchar.questTemp.FiringOfficerIDX = GetCharacterIndex(Npchar.id);
			AddDialogExitQuestFunction("LandEnc_OfficerFired");
			Diag.CurrentNode = Diag.TempNode;
			NPChar.quest.meeting = true;
			NPChar.rank = 0;	
			DialogExit();
			LaunchCharacterItemChange(npchar);
			RemovePassenger(Pchar, npchar);
		break;

		case "Get_out_А2_chang": // интерфейс обмена
			Diag.TempNode = "Fired_2";
			LAi_CharacterDisableDialog(NPChar);
			Pchar.questTemp.FiringOfficerIDX = GetCharacterIndex(Npchar.id);
			AddDialogExitQuestFunction("LandEnc_OfficerFired");
			Diag.CurrentNode = Diag.TempNode;
			NPChar.quest.meeting = true;
			NPChar.rank = 0;
			DialogExit();
			LaunchCharacterItemChange(npchar);
			RemovePassenger(Pchar, npchar);
		break;

		case "Get_out_А3_chang": // интерфейс обмена
			Diag.TempNode = "Fired_3";
			LAi_CharacterDisableDialog(NPChar);
			AddMoneyToCharacter(Pchar, -(makeint(sti(NPChar.rank)*1000)));
			ChangeCharacterComplexReputation(pchar,"nobility", 1);
			Pchar.questTemp.FiringOfficerIDX = GetCharacterIndex(Npchar.id);
			AddDialogExitQuestFunction("LandEnc_OfficerFired");
			Diag.CurrentNode = Diag.TempNode;
			NPChar.quest.meeting = true;
			NPChar.rank = 0;
			DialogExit();
			LaunchCharacterItemChange(npchar);
			RemovePassenger(Pchar, npchar);
		break;

		case "Get_out_А4_chang_1": // интерфейс обмена
			Diag.TempNode = "Fired_4";
			LAi_CharacterDisableDialog(NPChar);
			ChangeCharacterComplexReputation(pchar,"nobility", -1);
			Pchar.questTemp.FiringOfficerIDX = GetCharacterIndex(Npchar.id);
			AddDialogExitQuestFunction("LandEnc_OfficerFired");
			Diag.CurrentNode = Diag.TempNode;
			NPChar.quest.meeting = true;
			NPChar.rank = 0;	
			DialogExit();
			LaunchCharacterItemChange(npchar);
			RemovePassenger(Pchar, npchar);
		break;

		case "Get_out_А4_chang": // интерфейс обмена
			Diag.TempNode = "Fired_4";
			LAi_CharacterDisableDialog(NPChar);
			AddMoneyToCharacter(Pchar, -(makeint(sti(NPChar.rank)*1000)));
			ChangeCharacterComplexReputation(pchar,"nobility", 1);
			ChangeCharacterComplexReputation(pchar,"authority", 0.5);
			Pchar.questTemp.FiringOfficerIDX = GetCharacterIndex(Npchar.id);
			AddDialogExitQuestFunction("LandEnc_OfficerFired");
			Diag.CurrentNode = Diag.TempNode;
			NPChar.quest.meeting = true;
			NPChar.rank = 0;	
			DialogExit();
			LaunchCharacterItemChange(npchar);
			RemovePassenger(Pchar, npchar);
		break;

	    case "exit_bad":
			Npchar.loyality = makeint(Npchar.loyality) - 3;
			Diag.CurrentNode = Diag.TempNode;
			NPChar.quest.meeting = true;
			DialogExit();
		break;

		case "exit_bad1":
			Npchar.loyality = makeint(Npchar.loyality) - 2;
			ChangeOfficersLoyality("bad_all", 1);
			ChangeCharacterComplexReputation(pchar,"nobility", -1);
			ChangeCharacterComplexReputation(pchar,"authority", -1);
			Diag.CurrentNode = Diag.TempNode;			
			NPChar.quest.meeting = true;
			DialogExit();
		break;

		case "exit_good":
			Npchar.loyality = makeint(Npchar.loyality) - 1;
			Diag.CurrentNode = Diag.TempNode;
			NPChar.quest.meeting = true;
			DialogExit();
		break;

		case "exit_fire_1":	//navy -->			
			if (CheckAttribute(NPChar, "PGGAi"))
			{				
				pchar.questTemp.FiringOfficerIDX = NPChar.index;
				AddDialogExitQuestFunction("PGG_FireOfficer");
				DialogExit();
				break;
			}	//navy <--		
			Diag.TempNode = "Fired_1";
			Pchar.questTemp.FiringOfficerIDX = GetCharacterIndex(Npchar.id);
			AddDialogExitQuestFunction("LandEnc_OfficerFired");			
			Diag.CurrentNode = Diag.TempNode;
			NPChar.quest.meeting = true;
			DialogExit();	
		break;

		case "exit_fire_2":	//navy -->		
			if (CheckAttribute(NPChar, "PGGAi"))
			{				
				pchar.questTemp.FiringOfficerIDX = NPChar.index;
				AddDialogExitQuestFunction("PGG_FireOfficer");	
				DialogExit();
				break;
			}	//navy <--	
			Diag.TempNode = "Fired_2";
			Pchar.questTemp.FiringOfficerIDX = GetCharacterIndex(Npchar.id);
			AddDialogExitQuestFunction("LandEnc_OfficerFired");			
			Diag.CurrentNode = Diag.TempNode;
			NPChar.quest.meeting = true;
			DialogExit();	
		break;

		case "exit_fire_3":	//navy -->		
			if (CheckAttribute(NPChar, "PGGAi"))
			{				
				pchar.questTemp.FiringOfficerIDX = NPChar.index;
				AddDialogExitQuestFunction("PGG_FireOfficer");
				DialogExit();
				break;
			}	//navy <--	
			Diag.TempNode = "Fired_3";
			Pchar.questTemp.FiringOfficerIDX = GetCharacterIndex(Npchar.id);
			AddDialogExitQuestFunction("LandEnc_OfficerFired");			
			Diag.CurrentNode = Diag.TempNode;
			NPChar.quest.meeting = true;
			DialogExit();	
		break;

		case "exit_fire_4":	//navy -->		
			if (CheckAttribute(NPChar, "PGGAi"))
			{				
				pchar.questTemp.FiringOfficerIDX = NPChar.index;
				AddDialogExitQuestFunction("PGG_FireOfficer");	
				DialogExit();
				break;
			}	//navy <--		
			Diag.TempNode = "Fired_4";
			Pchar.questTemp.FiringOfficerIDX = GetCharacterIndex(Npchar.id);
			AddDialogExitQuestFunction("LandEnc_OfficerFired");			
			Diag.CurrentNode = Diag.TempNode;
			NPChar.quest.meeting = true;
			DialogExit();	
		break;

		case "exit_fire_5":	//navy -->		
			if (CheckAttribute(NPChar, "PGGAi"))
			{				
				pchar.questTemp.FiringOfficerIDX = NPChar.index;
				AddDialogExitQuestFunction("PGG_FireOfficer");
				DialogExit();
				break;
			}	//navy <--	
			Diag.TempNode = "Fired_1";
			OfficersReaction("good");
			Pchar.questTemp.FiringOfficerIDX = GetCharacterIndex(Npchar.id);
			AddDialogExitQuestFunction("LandEnc_OfficerFired");			
			Diag.CurrentNode = Diag.TempNode;
			NPChar.quest.meeting = true;
			DialogExit();	
		break;

		case "Fired_1":
			Diag.TempNode = "Fired_1";      
			dialog.text = "Quoi maintenant?! Nous avons déjà parlé de tout! Plus jamais je ne mettrai les pieds sur votre navire.";
			Link.l1 = RandPhraseSimple("Dégage maintenant. Pas une grande perte, après tout.","D'accord, vas-y alors. Je ne te retiendrai pas.");	
			Link.l1.go = "Exit";
		break;

		case "Fired_2":
			Diag.TempNode = "Fired_2"; 
			dialog.text = "Quelque chose d'autre, capitaine? Je pensais que nous avions déjà tout discuté...";
			Link.l1 = "Non, rien. Je voulais juste dire au revoir...";	 
			Link.l1.go = "Exit";
		break;

		case "Fired_3":
			Diag.TempNode = "Fired_3"; 
			dialog.text = "Capitaine, nous avons tout discuté et exprimé nos revendications. Vous n'allez pas dire que vous avez changé d'avis, n'est-ce pas?";
			Link.l1 = "D'accord, va-t'en alors. Pas une grande perte, après tout.";	 
			Link.l1.go = "Exit";
		break;

		case "Fired_4":
			Diag.TempNode = "Fired_4"; 
			dialog.text = "Capitaine, quelles autres questions pourraient-il y avoir? Je vous le dis, je suis très offensé et je n'ai aucune envie de revenir...";
			Link.l1 = "D'accord, va donc. Pas que j'avais tant besoin de toi.";	 
			Link.l1.go = "Exit";
		break;
		
		// boal 05.09.03 offecer need to go to abordage -->
	    case "Boal_Stay":
            //SetCharacterTask_Stay(Characters[Npchar.index]); // it's a mistic but here doesn't work :(
            //Log_SetStringToLog(Npchar.id +" "+Npchar.index);
            Pchar.questTemp.HiringOfficerIDX = GetCharacterIndex(Npchar.id);
            AddDialogExitQuestFunction("LandEnc_OfficerStay");
		    Diag.TempNode = "Hired";
		    dialog.text = "A vos ordres, Capitaine!";
		    Link.l1 = "A l'aise.";
		    Link.l1.go = "Exit";
		    Npchar.chr_ai.tmpl = LAI_TMPL_STAY;
	    break;
		
	    case "Boal_Follow":
		    SetCharacterTask_FollowCharacter(Npchar, PChar); // it works here!!!
		    Diag.TempNode = "Hired";
		    dialog.text = "A vos ordres, Capitaine!";
		    Link.l1 = "A votre aise.";
		    Link.l1.go = "Exit";
	    break;
        // boal 05.09.03 offecer need to go to abordage <--

		//////////////////////////////    офицер-наместник -->
		case "Gover_Hire":
            dialog.Text = "Capitaine! Ce serait un honneur!";
            Link.l1 = "Maintenez l'ordre et faites prospérer la ville, et je viendrai de temps en temps pour collecter les tarifs.";
			Link.l1.go = "Exit_Gover_Hire";
            Link.l2 = "J'ai changé d'avis.";
            Link.l2.go = "Exit";
            Diag.TempNode = "Hired";
        break;

        case "Exit_Gover_Hire":
            sld = GetColonyByIndex(sti(NPChar.ColonyIdx));
            attr = sld.id + "_townhall";

            // снимем пассажира -->
			CheckForReleaseOfficer(sti(NPChar.index));
			RemovePassenger(pchar, NPChar);
			// снимем пассажира <--
		    sld.OfficerIdx = sti(NPChar.index);
			ChangeCharacterAddressGroup(NPChar, attr, "sit", "sit1");
			LAi_SetHuberTypeNoGroup(NPChar);
            SaveCurrentNpcQuestDateParam(NPChar, "StartTaxDate");
            SaveCurrentNpcQuestDateParam(NPChar, "GoverTalkDate");
            LAi_LoginInCaptureTown(NPChar, true);
			//  СЖ -->
			ReOpenQuestHeader("Gen_CityCapture");
            AddQuestRecordInfo("Gen_CityCapture", "t3_1");
			AddQuestUserData("Gen_CityCapture", "sSex", GetSexPhrase("",""));
			AddQuestUserData("Gen_CityCapture", "sCity", XI_ConvertString("colony" + sld.id));
			AddQuestUserData("Gen_CityCapture", "sName", GetFullName(NPChar));
			//  СЖ <--
			Diag.CurrentNode = "Gover_Main";
            DialogExit();
        break;

        case "Gover_Main":
            iTemp = GetNpcQuestPastDayParam(NPChar, "GoverTalkDate");
            if (iTemp > 0)
            {
				dialog.Text = "Quels sont vos ordres? La dernière fois que vous m'avez rendu visite "+FindRussianDaysString(iTemp)+" il y a.";
			}
			else
			{
			    dialog.Text = "Quels sont vos ordres ?";
			}

            Link.l1 = "Combien d'argent d'impôts avez-vous "+NPCharSexPhrase(NPChar,"collecté","recueilli")+" à ce stade?";
        	Link.l1.go = "Gover_Tax";
            Link.l8 = "Vous êtes nécessaire sur le navire, je vous libère de votre tâche en ville.";
            Link.l8.go = "Gover_Fire";
			Link.l9 = "Tout le meilleur.";
            Link.l9.go = "Exit";
            Diag.TempNode = "Gover_Main";
            SaveCurrentNpcQuestDateParam(NPChar, "GoverTalkDate");
        break;

        case "Gover_Tax":
            iTemp = GetNpcQuestPastDayParam(NPChar, "StartTaxDate");
            iTax  = makeint((GetCharacterSkillSimple(NPChar, SKILL_COMMERCE) + GetCharacterSkillSimple(NPChar, SKILL_LEADERSHIP)) / 2);
            sld = GetColonyByIndex(sti(NPChar.ColonyIdx));
			if (CheckAttribute(sld, "FortValue"))
			{
			    iFortValue = sti(sld.FortValue);
			}
			else
			{
			    iFortValue = 20;
			}
			NPChar.Gover_Tax_Sum = iFortValue*iTax*iTemp;
			dialog.Text = "Mes compétences me permettent de collecter "+FindRussianMoneyString(iFortValue*iTax)+" Par jour. Plus "+FindRussianDaysString(iTemp)+" Je "+NPCharSexPhrase(NPChar,"recueilli","collecté")+" "+FindRussianMoneyString(sti(NPChar.Gover_Tax_Sum))+".";
			if (sti(NPChar.Gover_Tax_Sum) > 0)
			{
			    Link.l1 = "Je veux prendre tout l'argent des taxes collectées.";
            	Link.l1.go = "Gover_Tax_Get";
			}
			Link.l2 = "Merci pour le service !";
            Link.l2.go = "Exit";
        break;

        case "Gover_Tax_Get":
            SaveCurrentNpcQuestDateParam(NPChar, "StartTaxDate");
            AddMoneyToCharacter(Pchar, sti(NPChar.Gover_Tax_Sum));

			Diag.CurrentNode = "Gover_Main";
            DialogExit();
        break;

        case "Gover_Fire":
            dialog.Text = "Génial! Je ne suis pas un terrien, tu sais.";
            Link.l8 = "C'est bien.";
            Link.l8.go = "exit_hire";
            Diag.TempNode = "Hired";
            sld = GetColonyByIndex(sti(NPChar.ColonyIdx));
            DeleteAttribute(sld, "OfficerIdx");
            //  СЖ -->
			ReOpenQuestHeader("Gen_CityCapture");
            AddQuestRecordInfo("Gen_CityCapture", "t3_2");
			AddQuestUserData("Gen_CityCapture", "sCity", XI_ConvertString("colony" + sld.id));
			AddQuestUserData("Gen_CityCapture", "sName", GetFullName(NPChar));
			//  СЖ <--
        break;
        //////////////////////////////    офицер-наместник <--

		//Указания для компаньона 19.02.08 -->
		case "Companion_Tasks":
			dialog.Text = "Je vous écoute.";
			Link.l1 = "C'est à propos de l'abordage.";
			Link.l1.go = "Companion_TaskBoarding";
			Link.l2 = "C'est à propos de votre navire.";
			Link.l2.go = "Companion_TaskChange";
			if(bBettaTestMode) // Только при бета-тесте
			{
			    Link.l3 = "Je veux que tu quittes mon escadron pour un moment et cherches fortune de ton côté.";
			    Link.l3.go = "CompanionTravel";
			}
			Link.l8 = "Rien jusqu'à présent.";
			Link.l8.go = "exit";
		break;
		
		case "Companion_TaskBoarding":
			dialog.Text = "Alors, quel est ton souhait.";
			Link.l1 = "Ne montez pas à bord des navires ennemis. Prenez soin de vous et de l'équipage.";
			Link.l1.go = "Companion_TaskBoardingNo";
			Link.l2 = "Je veux que vous abordiez les navires ennemis.";
			Link.l2.go = "Companion_TaskBoardingYes";
		break;
		
		case "Companion_TaskChange":
			dialog.Text = "Alors, quel est ton souhait.";
			Link.l1 = "Je voudrais que vous ne troquiez pas votre navire pour un autre après l'abordage. Il est trop précieux.";
			Link.l1.go = "Companion_TaskChangeNo";
			Link.l2 = "Quand vous abordez des navires ennemis, vous pouvez les prendre pour vous-même, s'ils se trouvent être décents.";
			Link.l2.go = "Companion_TaskChangeYes";
		break;
		
		case "Companion_TaskBoardingNo":
			dialog.Text = "Aye-aye Capitaine.";
			Link.l1 = "Au repos.";
			Link.l1.go = "exit";
			NPChar.Tasks.CanBoarding = false;
		break;
		
		case "Companion_TaskBoardingYes":
			dialog.Text = "Ce sera fait, Capitaine.";
			Link.l1 = "A l'aise.";
			Link.l1.go = "exit";
			NPChar.Tasks.CanBoarding = true;
		break;
		
		case "Companion_TaskChangeNo":
			dialog.Text = "Aye-aye Capitaine.";
			Link.l1 = "Au repos.";
			Link.l1.go = "exit";
			NPChar.Tasks.CanChangeShipAfterBoarding = false;
		break;
		
		case "Companion_TaskChangeYes":
			dialog.Text = "Cela sera fait, Capitaine.";
			Link.l1 = "A votre aise.";
			Link.l1.go = "exit";
			NPChar.Tasks.CanChangeShipAfterBoarding = true;
		break;
		//<--
	
		// Самостоятельное плавание компаньона -->
		case "CompanionTravel":
			if(GetAttrValue(PChar, "CompanionTravel") == 3) // Если уже троих отпустил
			{
				dialog.Text = "Capitaine, je ne quitterai pas votre escadron, car vous avez déjà renvoyé trois navires.";
					Link.l1 = "Oui, peut-être, vous avez raison.";
					Link.l1.go = "exit";
				break;
			}
		
			dialog.Text = "Aucun problème, cap. Dans quelle ville devons-nous nous rencontrer?";
			for(iTemp=0; iTemp<MAX_COLONIES; iTemp++)
			{
				sld = &colonies[iTemp];
				attr = sld.ID;
				if(sld.nation == "none" || sld.nation == PIRATE || attr == "Panama" || attr == "FortOrange") continue;
				attrLoc = "l" + iTemp;
				Link.(attrLoc) = "In the " + XI_ConvertString("Colony" + attr + "Dat");
				Link.(attrLoc).go = "CompanionTravelToColony_" + attr;
			}
				Link.l99 = "J'ai changé d'avis.";
				Link.l99.go = "exit";
		break;
			
		case "CompanionTravel_EnemyColony":
			dialog.Text = "Capitaine, mais je ne peux pas vous attendre dans la colonie, qui est hostile à nous !";
				Link.l1 = "Tu sais, oublie tous ces voyages...";
				Link.l1.go = "exit";
		break;
			
		case "CompanionTravel_NoCrew":
			dialog.Text = "Capitaine, nous avons presque pas de marins dans l'équipage ! De quel voyage parles-tu ?!";
				Link.l1 = "C'est vrai, nous manquons vraiment de marins...";
				Link.l1.go = "exit";
		break;
			
		case "CompanionTravel_NoFood":
			dialog.Text = "Capitaine, je n'ai pas assez de provisions à bord pour un tel voyage.";
				Link.l1 = "Oui, tu as raison. Le voyage peut attendre...";
				Link.l1.go = "exit";
		break;
			
		case "CompanionTravel_NoHP":
			dialog.Text = "Capitaine, mais mon navire est en mauvais état. Il serait imprudent de ma part de prendre la mer seul dans de telles circonstances!";
				Link.l1 = "Oui, vous avez raison. Votre navire a besoin de réparation.";
				Link.l1.go = "exit";
		break;
		
		case "CompanionTravel_PrepareStart":
			dialog.Text = "Je vois. Jusqu'à "+XI_ConvertString("Colonie"+characters[sti(NPChar.realcompanionidx)].CompanionTravel.ToColonyID+"Gén")+" à aller "+sti(characters[sti(NPChar.realcompanionidx)].CompanionTravel.Days)+" jours, que dois-je faire à mon arrivée?";
				Link.l1 = "Restez au large du port de la colonie pendant un mois.";
				Link.l1.go = "CompanionTravel_PrepareStart_2";
				Link.l2 = "Tu sais, j'ai changé d'avis. Reste avec moi...";
				Link.l2.go = "exit";
		break;
		
		case "CompanionTravel_PrepareStart_2":
			dialog.Text = "Je vois, capitaine. Je partirai tout de suite.";
				Link.l1 = "Oui, s'il vous plaît, faites-le.";
				Link.l1.go = "CompanionTravel_Start";
		break;
			
		case "CompanionTravel_Start":
			Diag.CurrentNode = "CompanionTravel_LastNode";
			NPChar.quest.meeting = true;
			CompanionTravel_SetTraveller(NPChar);
			DialogExit();
		break;
			
		case "CompanionTravel_LastNode":
			Dialog.text = RandPhraseSimple("Aujourd'hui, je prends la mer de nouveau...","N'oubliez pas notre rendez-vous à "+XI_ConvertString("Colonie"+characters[sti(NPChar.realcompanionidx)].CompanionTravel.ToColonyID+"Cela")+".");
				link.l2 = "..., ami.";
				link.l2.go = "Exit";
				Diag.TempNode = "CompanionTravel_LastNode";
		break;
			
		case "CompanionTravel_ToSquadron":
			if(GetCompanionQuantity(PChar) < COMPANION_MAX)
			{
				dialog.text = "Je l'aimerais aussi. Désormais, mon navire est de nouveau sous ton commandement, cap.";
					Link.l1 = "D'accord.";
					Link.l1.go = "exit";
					Diag.TempNode = "hired";
					CompanionTravel_DeleteSpecialShipAttributes(NPChar);
					Group_DeleteAtEnd(NPChar.CompanionTravel.GroupID); // Потрем группу
					SetCompanionIndex(PChar, -1, sti(NPChar.index));
					PChar.CompanionTravel = sti(PChar.CompanionTravel) - 1; // Этого компаньона взяли обратно в эскадру
					DeleteAttribute(NPChar, "CompanionTravel");
			}
			else
			{
				dialog.text = "Capitaine, vous avez déjà cinq navires dans votre escadron - que comptez-vous faire du sixième ? Eh bien, je pense que je préfère vous attendre ici sur mon navire. Vos nouveaux compagnons ne me semblent pas fiables. Leurs navires vont bientôt couler, et vous reviendrez me chercher.";
					Link.l1 = "Eh bien, n'es-tu pas intelligent? Tu devrais être un amiral, pas seulement un capitaine!";
					Link.l1.go = "exit";
					Diag.TempNode = "CompanionTravel_ToSquadron_2";
					NPChar.DeckDialogNode = "CompanionTravel_ToSquadron_2"; // ставим снова эту ноду
			}
		break;
			
		case "CompanionTravel_ToSquadron_2":
			dialog.text = "Oh, capitaine, vous êtes revenu, comme je l'ai dit. Alors, y a-t-il maintenant une place vacante dans votre escadron?";
			if(GetCompanionQuantity(PChar) < COMPANION_MAX)
			{
				Link.l1 = "Oui, "+NPChar.name+", il y en a un. Bienvenue dans l'escadron.";
				Link.l1.go = "exit";
				Diag.TempNode = "hired";
				CompanionTravel_DeleteSpecialShipAttributes(NPChar);
				Group_DeleteAtEnd(NPChar.CompanionTravel.GroupID);
				SetCompanionIndex(PChar, -1, sti(NPChar.index));
				PChar.CompanionTravel = sti(PChar.CompanionTravel) - 1; // Этого компаньона взяли обратно в эскадру
				DeleteAttribute(NPChar, "CompanionTravel");
			}
			else
			{
				Link.l1 = "Pas encore, malheureusement.";
				Link.l1.go = "exit";
				Diag.TempNode = "CompanionTravel_ToSquadron_2";
				NPChar.DeckDialogNode = "CompanionTravel_ToSquadron_2";
			}
		break;
		// <-- Самостоятельное плавание компаньона
		
		case "tonzag_after_boarding":
			dialog.text = "Capitaine, les choses sont merde! L'ennemi nous tient fermement, j'ai peur qu'ils ne lâchent pas jusqu'à ce que nous soyons morts! Nos gens sont en réel danger en ce moment, et la plupart des équipages de canon sont hors de combat!";
			link.l1 = "Je vais les aider. Prends le commandement et sors-nous d'ici !";
			link.l1.go = "tonzag_after_boarding_1";
			DelLandQuestMark(npchar);
		break;
		
		case "tonzag_after_boarding_1":
			dialog.text = "Oui, monsieur !";
			link.l1 = "";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("Tonzag_GoToGunDeck");
		break;
		
		case "tonzag_after_victory":
			dialog.text = "Victoire, Capitaine! Le groupe de débarquement a été détruit, l'ennemi a choisi de se retirer et s'est dirigé vers le sud. L'état du navire est acceptable. Équipage vivant : "+GetCrewQuantity(pchar)+" gens. Rapport termine!";
			link.l1 = "Merci ! Du rhum pour tout le monde et renforcez la vigie jusqu'à ce que nous atteignions le port !";
			link.l1.go = "tonzag_after_victory_1";
		break;
		
		case "tonzag_after_victory_1":
			dialog.text = "Hurrah! Oui oui!";
			link.l1 = "";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("Tonzag_AlonsoBoardingDialog");
		break;
	}
}
