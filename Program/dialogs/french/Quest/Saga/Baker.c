// Раймонд Бейкер - палач Сент-Джонса и возможный офицер
void ProcessDialogEvent()
{
	ref NPChar, sld, rItm, rItem;
	aref Link, NextDiag, rType;
	int i;
	string 	sAttr, sGun, sBullet, attrL;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	sAttr = Dialog.CurrentNode;
	if (findsubstr(sAttr, "SetGunBullets1_" , 0) != -1)
 	{
        i = findsubstr(sAttr, "_" , 0);
	 	NPChar.SetGunBullets = strcut(sAttr, i + 1, strlen(sAttr) - 1); // индекс в конце
 	    Dialog.CurrentNode = "SetGunBullets2";
 	}
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			dialog.text = "Tu veux quelque chose ?";
			link.l1 = "Non, c'est rien.";
			link.l1.go = "exit";			
			NextDiag.TempNode = "First time";
		break;
		
		case "baker":
			dialog.text = "Merci, Capitaine ! Je n'ose imaginer ce que j'aurais fait sans vous...";
			link.l1 = "Je peux imaginer. Tu serais mort de faim ou aurais fini dans l'estomac d'un sauvage de la Dominique. Mais tu as une chance de me rendre la pareille.";
			link.l1.go = "baker_1";
		break;
		
		case "baker_1":
			dialog.text = "Comment puis-je vous aider, Capitaine?";
			link.l1 = "Je veux en savoir plus sur un homme. Il est notre ami commun, pour ainsi dire. Un très proche ami à vous en fait. Je veux dire le capitaine Butcher. Oui, celui que vous avez pendu il y a vingt ans. Seigneur, pourquoi êtes-vous si pâle ? Voulez-vous une gorgée de rhum ?";
			link.l1.go = "baker_2";
		break;
		
		case "baker_2":
			dialog.text = "Est-ce que... est-ce que c'est lui qui vous a envoyé ?";
			link.l1 = "Balivernes ! Comment pourrais-je être 'envoyé par lui' s'il est mort ! Ce qui m'intéresse davantage, ce sont les choses qu'il a laissées plutôt que le Boucher lui-même. Des lettres, des documents, des choses de ce genre. Peut-être avez-vous trouvé quelque chose dans ses poches... Attendez ! Je ne comprends pas. Pensez-vous vraiment que le Boucher est vivant ? Vous l'avez exécuté vous-même !";
			link.l1.go = "baker_3";
		break;
		
		case "baker_3":
			dialog.text = "Merde ! Tu n'as pas la moindre idée. Cela signifie que tu n'as pas été envoyé par le Boucher comme je le pensais...";
			link.l1 = "Eh bien, eh bien. Cela devient de plus en plus intéressant. Il semble qu'Henry avait toutes les raisons d'avoir peur de Boucher et c'est pour cela qu'il est mort d'une crise cardiaque... Est-ce que Boucher est vivant ?";
			link.l1.go = "baker_4";
		break;
		
		case "baker_4":
			dialog.text = "Il l'est, Capitaine... Et ils me cherchent.";
			link.l1 = "Raymond, ils m'ont dit que tu n'es pas un imbécile. Ne joue pas avec moi. Tu es à l'abri de toute menace ici. Dis-moi tout ce que tu sais et je trouverai une solution pour t'aider. Peut-être que nous avons des ennemis communs. Commençons par Boucher.";
			link.l1.go = "baker_5";
		break;
		
		case "baker_5":
			dialog.text = "Il est vivant, mais son nom est différent maintenant ! Ses hommes m'ont rendu visite la nuit de l'exécution. Jackman et un autre homme avec un surnom étrange. Autant que je me souvienne, c'était 'l'Homme noyé'.";
			link.l1 = "Bourreau. Henry le Bourreau.";
			link.l1.go = "baker_6";
		break;
		
		case "baker_6":
			dialog.text = "D'accord ! Ils m'ont offert un marché simple - mourir de la manière la plus douloureuse ou sauver leur capitaine. J'ai donc dû simuler l'exécution avec un équipement spécial que j'avais créé pendant mon temps libre. Vous voyez, une telle construction de sangles et de pinces peut répartir le poids du corps. \nTout ce que j'avais à faire était de la relier à un crochet secret dans la boucle. Le 'cadavre' devait bien jouer son rôle cependant. Je dois dire que le jeu de Lawrence était des plus crédibles, il a fait tout correctement, sauf qu'il a refusé de se pisser dessus, à cause de...";
			link.l1 = "As-tu   appelé   le Boucher   'Lawrence' ?";
			link.l1.go = "baker_7";
		break;
		
		case "baker_7":
			dialog.text = "C'est son vrai nom. Je vous ai dit qu'il s'appelle Lawrence Beltrope. Je suis agité depuis qu'il est revenu aux Caraïbes il y a un an. Et quand j'ai découvert que des personnes malintentionnées me recherchent...\nJ'ai même rédigé une confession pour les autorités au cas où. Je la garde toujours avec moi car j'ai trop peur de la remettre. Ils pourraient penser que j'étais un complice volontaire. S'il vous plaît, laissez-moi rester avec votre équipage. Je vous le jure, je suis un excellent médecin et je peux vous être d'une grande aide.";
			link.l1 = "D'accord. Et qu'en est-il des objets personnels du Boucher... euh, de Beltrope? Est-il lié à Thomas Beltrope?";
			link.l1.go = "baker_8";
		break;
		
		case "baker_8":
			dialog.text = "Aucune idée. Je n'ai rien de spécial venant de Beltrope lui-même. Mais je vais te donner tout ce que j'ai, tu es libre d'en faire ce que tu veux. Tous les papiers liés au sujet sont dans mon sac. J'ai tout gardé juste au cas où et je les garde près de moi.\nTiens, jette un œil... c'est la légende du capitaine Boucher, c'est ma confession... Ce sont des choses qui appartenaient à Joshua Leadbeater...";
			link.l1 = "Arrête ! Leadbeater ? Qui est-ce ?";
			link.l1.go = "baker_9";
		break;
		
		case "baker_9":
			dialog.text = "Oh ! C'était un homme très spécial. C'est lui qui a pourchassé Boucher en personne. Les gens se souvenaient de lui comme de 'l'homme masqué'. Il a été assassiné peu de temps après l'exécution de Boucher. Quelqu'un lui a tranché la gorge avec une dent de requin ! Une coupe et c'était fini pour lui. Quand il était encore en vie, il a dû beaucoup souffrir.\nSi tu avais vu son visage sous le masque, ce n'était que de la chair ! Il avait cette page de journal dans sa poche quand il est mort. Elle devait provenir des écrits de Jessica Rose. Histoire effrayante ! Lis-la, cela rendra les choses beaucoup plus compréhensibles.\nEt voici la dent elle-même. Peux-tu voir les lettres ? S.D.... Quoi que cela signifie. Il y a aussi quelques traces de sang restantes.";
			link.l1 = "Assez ! Je dois tout lire attentivement et y réfléchir. Et tu seras mon passager ou médecin de bord jusqu'à ce que je règle tout cela. Tu peux respirer librement, Raymond, tu es en sécurité sur mon navire.";
			link.l1.go = "baker_10";
		break;
		
		case "baker_10":
			DialogExit();
			sld = characterFromId("Baker_Cap");
			LAi_SetImmortal(sld, false);
			sld.lifeday = 0;
			//sld.ship.hp = 0;
			//sld.SinkTenPercent = true;
			bQuestDisableMapEnter = false;
			GiveItem2Character(pchar, "shark_teeth");
			GiveItem2Character(pchar, "letter_jess");
			GiveItem2Character(pchar, "letter_baker"); // показания бейкера
			ChangeItemDescribe("letter_baker", "itmdescr_letter_baker"); // Addon-2016 Jason
			AddQuestRecordInfo("Legend_CapBucher", "1");
			AddQuestRecordInfo("Letter_jess", "1");
			AddQuestRecord("Shadows", "5");
			pchar.questTemp.Saga.Shadows = "islatesoro";
			// в офицеры
			npchar.quest.OfficerPrice = sti(pchar.rank)*500;
			npchar.OfficerWantToGo.DontGo = true; //не пытаться уйти
			npchar.CompanionDisable = true; //нельзя в компаньоны
			npchar.loyality = MAX_LOYALITY;
			AddPassenger(pchar, npchar, false);
			SetCharacterRemovable(npchar, true);
			npchar.Payment = true;
			npchar.DontClearDead = true;
			NextDiag.CurrentNode = "Baker_officer";
			npchar.OfficerImmortal = true;
			npchar.Health.HP       = 60.0; 
			npchar.Health.maxHP    = 60.0;
		
			LAi_group_MoveCharacter(npchar, LAI_GROUP_PLAYER);
			SaveCurrentNpcQuestDateParam(npchar, "HiredDate");
			AddCharacterExpToSkill(pchar, "Sailing", 50);
			AddCharacterExpToSkill(pchar, "Fortune", 100);
		break;
		
		//--> ----------------------------------- офицерский блок ------------------------------------------
		case "Baker_officer":
			dialog.text = "Oui, capitaine ?";
			Link.l1 = "Ecoutez mon ordre !";
            Link.l1.go = "stay_follow";
			if (CheckAttribute(pchar, "questTemp.SharlieEpilog_FarewellOfficers") && !CheckAttribute(npchar, "quest.SharlieEpilog_FarewellOfficers"))
			{
				dialog.text = "Capitaine, vous semblez un peu préoccupé. Et votre visage est assez pâle... En d'autres circonstances, je vous proposerais une de mes potions, mais...";
				Link.l1 = "Je vois que tu t'y connais un peu en médecine, "+npchar.name+". Merci, ça va. Je dois juste faire un pas que je n’aurais peut-être pas osé dans d’autres conditions.";
				Link.l1.go = "SharlieEpilog_Baker_1";
				break;
			}
			
			////////////////////////казначей///////////////////////////////////////////////////////////
           	// boal отчёт о корабле
			if(CheckAttribute(NPChar, "treasurer") && NPChar.treasurer == 1)
			{
			    Link.l11 = "Raymond, donne-moi un rapport complet du navire.";
			    Link.l11.go = "QMASTER_1";

			    // Warship. Автозакупка товара
				Link.l12 = "Je veux que tu achètes certaines marchandises chaque fois que nous sommes à quai.";
				Link.l12.go = "QMASTER_2";
			}
			
			link.l2 = "C'est rien. Dispensé!";
			link.l2.go = "exit";
			NextDiag.TempNode = "Baker_officer";
		break;
		
		/////////////////////////// ответы для казначея ///////////////////////////////////
        case "QMASTER_1":
			dialog.Text = "Allez, Capitaine, je suis médecin, pas commissaire de bord. Quoique, dans le passé, je travaillais dans une autre capacité... peu importe. Je ne fais vraiment pas de comptabilité, désolé.";
			Link.l1 = "Très bien, ainsi soit-il. Vous êtes mon médecin - comme nous l'avons convenu après que vous ayez rejoint mon équipage.";
			Link.l1.go = "exit";
		break;	

		case "QMASTER_2":
			dialog.text = "Capitaine, pour être tout à fait honnête, je n'ai jamais acquis beaucoup d'expérience dans le commerce. Jamais marchandé, jamais suivi les étiquettes de prix. Aussi... je préférerais rester sur le navire si cela ne vous dérange pas. Certains de ces marchands pourraient me reconnaître et avant que vous ne le sachiez - des hommes masqués arrivent rapidement.";
			link.l1 = "Alors, tu continueras à vivre dans la crainte de ton passé... Bien, souffle, je le ferai moi-même.";
			Link.l1.go = "exit";
        break;
		
		case "stay_follow":
            dialog.Text = "Ordres ?";
            Link.l1 = "Tiens-toi ici !";
            Link.l1.go = "Boal_Stay";
            Link.l2 = "Suis-moi et ne traîne pas !";
            Link.l2.go = "Boal_Follow";
			sGun = GetCharacterEquipByGroup(NPChar, GUN_ITEM_TYPE);
			if(sGun != "")
			{
				rItm = ItemsFromID(sGun);
				if(CheckAttribute(NPChar, "chr_ai.gun.bulletNum") && sti(NPChar.chr_ai.gun.bulletNum) > 1)
				{
					Link.l3 = "Changez le type de munition pour votre arme à feu.";
					Link.l3.go = "SetGunBullets";
				}	
			}		
		break;
		
		case "SetGunBullets":
			Dialog.Text = "Choisir le type de munition :";
			sGun = GetCharacterEquipByGroup(NPChar, GUN_ITEM_TYPE);
			rItm = ItemsFromID(sGun);
			makearef(rType, rItm.type);	
			for (i = 0; i < sti(NPChar.chr_ai.gun.bulletNum); i++)
			{
				sAttr = GetAttributeName(GetAttributeN(rType, i));
				sBullet = rItm.type.(sAttr).bullet;
				rItem = ItemsFromID(sBullet);								
				attrL = "l" + i;
				Link.(attrL) = GetItemName(rItem);
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
			NextDiag.CurrentNode = NextDiag.TempNode;
			rItem = ItemsFromID(sBullet);
			notification(GetFullName(NPChar)+" "+XI_ConvertString("AmmoSelectNotif")+GetItemName(rItem)+"", "AmmoSelect");
			DeleteAttribute(NPChar,"SetGunBullets");
			DialogExit();
		break;		
		
        case "Boal_Stay":
            Pchar.questTemp.HiringOfficerIDX = GetCharacterIndex(Npchar.id);
            AddDialogExitQuestFunction("LandEnc_OfficerStay");
            dialog.Text = "Il y a un changement de disposition !";
            Link.l1 = "Congédié.";
            Link.l1.go = "Exit";
            Npchar.chr_ai.tmpl = LAI_TMPL_STAY;
        break;
        
        case "Boal_Follow":
            SetCharacterTask_FollowCharacter(Npchar, PChar);
            dialog.Text = "Il y a un changement de disposition !";
            Link.l1 = "Congédié.";
            Link.l1.go = "Exit";
        break;
		
		// Эпилог
		case "SharlieEpilog_Baker_1":
			dialog.text = "Hmm... On dirait que quelque chose m’échappe. Je pensais que la nouvelle à venir vous réjouirait.";
			link.l1 = "De quoi parles-tu ?";
			link.l1.go = "SharlieEpilog_Baker_2";
		break;

		case "SharlieEpilog_Baker_2":
			dialog.text = "Hum... Pardonnez-moi. Je ne sais pas ce qui m’a pris. Peut-être un coup de soleil. En vérité, je voulais vous parler, capitaine.";
			link.l1 = "Ah oui ? Et de quoi donc ?";
			link.l1.go = "SharlieEpilog_Baker_3";
		break;
		
		case "SharlieEpilog_Baker_3":
			dialog.text = "Je suis devenu trop vieux pour ces batailles navales sans fin, même si je n’y participe que de loin. J’ai mis un peu d’argent de côté, et j’aimerais m’installer à terre. Ouvrir un cabinet privé. J’espère que cela ne vous dérange pas ?";
			link.l1 = "Bien sûr que non, "+npchar.name+". Évidemment, tu me manqueras en tant qu’officier compétent. Mais je comprends et respecte ta décision. Bonne chance à toi. Je suis sûr que tu deviendras rapidement un médecin reconnu et respecté.";
			link.l1.go = "SharlieEpilog_Baker_nothing";
			link.l2 = "C’est une décision sage, et je n’y vois évidemment aucun inconvénient. Je vais faire en sorte que tu reçoives un mois de solde supplémentaire — ça ne sera pas de trop. Que dire de plus… bonne chance dans ta nouvelle vie.";
			link.l2.go = "SharlieEpilog_Baker_salary";
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") || CheckAttribute(pchar, "questTemp.LSC.Mary_officer")) // только если есть жена
			{
				link.l3 = "Ha ha, bien sûr que je ne vais pas m’y opposer, cher "+npchar.name+". En fait, je te comprends mieux que jamais en ce moment. Tiens, prends ça. Trois mois de solde. J’espère que tout se passera au mieux pour toi.";
				link.l3.go = "SharlieEpilog_Baker_salary_X3";
			}
		break;
		
		case "SharlieEpilog_Baker_nothing":
			DialogExit();
			AddDialogExitQuestFunction("SharlieEpilog_Baker_exit");
		break;
		
		case "SharlieEpilog_Baker_salary":
			DialogExit();
			AddDialogExitQuestFunction("SharlieEpilog_Baker_exit");
			//
			AddMoneyToCharacter(pchar, - sti(npchar.quest.OfficerPrice));
		break;
		
		case "SharlieEpilog_Baker_salary_X3":
			dialog.text = "Merci, capitaine. Je pense que vous devriez aussi envisager de chercher une petite maison confortable pour vous et votre épouse. Après tout, le roulis du navire n’est pas idéal pour certains processus dans le ventre...";
			link.l1 = "Dans le ventre ? Je ne comprends pas. Personne ne souffre du mal de mer, à ma connaissance.";
			link.l1.go = "SharlieEpilog_Baker_salary_X3_2";
			//
			AddMoneyToCharacter(pchar, -sti(npchar.quest.OfficerPrice) * 3);
		break;
		
		case "SharlieEpilog_Baker_salary_X3_2":
			dialog.text = "Juste une pensée à voix haute, capitaine, ne vous en souciez pas. Prenez soin de votre épouse — et de vous-même.";
			link.l1 = "Toi aussi, prends soin de toi, "+npchar.name+". Quand tu seras installé, fais-moi parvenir des nouvelles via l’abbé Benoît. Tu le trouveras à l’église Saint-Pierre.";
			link.l1.go = "SharlieEpilog_Baker_salary_X3_3";
		break;
		
		case "SharlieEpilog_Baker_salary_X3_3":
			DialogExit();
			AddDialogExitQuestFunction("SharlieEpilog_Baker_exit");
		break;
	
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}
