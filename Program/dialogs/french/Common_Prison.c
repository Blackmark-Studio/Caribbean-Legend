// городские тюрьмы
void ProcessDialogEvent()
{
	int amount, iGunQty, iGunGoods, iGunPrice, iTemp;
	int iTest;
	ref NPChar, sld, location;
	ref arItem;
	ref rColony;
	aref Link, NextDiag;
	string sTemp;
	float locx, locy, locz;
	bool  ok;
	// belamour для ночного приключения -->
	int i;
	int SoldQty = 0;
	int SoldNum[10];
	// <--

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

    // вызов диалога по городам -->
    NPChar.FileDialog2 = "DIALOGS\" + LanguageGetLanguage() + "\Prison\" + NPChar.City + "_Prison.c";
    if (LoadSegment(NPChar.FileDialog2))
	{
        ProcessCommonDialog(NPChar, Link, NextDiag);
		UnloadSegment(NPChar.FileDialog2);
	}
    // вызов диалога по городам <--

	switch(Dialog.CurrentNode)
	{
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	
		case "fight":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			LAi_group_Attack(NPChar, Pchar);
			if (rand(3) != 1) SetNationRelation2MainCharacter(sti(npchar.nation), RELATION_ENEMY);
			AddDialogExitQuest("MainHeroFightModeOn");
		break;

		case "NoMoreTalkExit":
			LAi_CharacterDisableDialog(npchar);
			DialogExit();
		break;
		//---------------- Начальник тюрьмы ------------------
		case "First_officer":
			dialog.text = RandPhraseSimple("Je suis le gardien de la prison. Qu'est-ce que vous avez besoin ici?","De quoi as-tu besoin? Pourquoi es-tu venu à la prison?");
			NextDiag.TempNode = "First_officer";
			if(startHeroType == 4 && NPChar.location == "SantaCatalina_prison" && !CheckAttribute(pchar, "questTemp.HelenSCprison"))
			{
				dialog.text = "Mademoiselle MacArthur? Surpris de vous voir. Nous n'avons arrêté personne de votre équipage ou du Capitaine Swenson, autant que je sache.";
				link.l1 = "Je suis juste ici, monsieur. N'est-ce pas permis? Je ne parlais pas avec les prisonniers derrière votre dos.";
				link.l1.go = "Helen_meeting";
				pchar.questTemp.HelenSCprison = true;
				break;
			}
			// --> Sinistra Длинные тени старых грехов
			if(CheckAttribute(pchar,"questTemp.DTSG_AntiguaTrevoga") && npchar.city == "SentJons")
			{
				dialog.text = "Ah, Charles de Maure... Vous devriez être arrêté et rejoindre votre officier, mais... l'incident à la banque a été considéré comme un malheureux malentendu.";
				link.l1 = "J'aime la façon dont vous avez commencé cette conversation, M. "+GetFullName(NPChar)+". Je peux tout expliquer.";
				link.l1.go = "DTSG_AntiguaTrevoga_2";
				break;
			}
			// <-- Длинные тени старых грехов
			
			//--> Бремя гасконца
			if (CheckAttribute(pchar, "questTemp.Sharlie") && pchar.questTemp.Sharlie == "jailskiper")
			{
				link.l1 = "Officier, j'ai entendu dire qu'il y a un homme nommé Folke Deluc dans votre prison. Y a-t-il quelque chose que je puisse faire pour le libérer?";
                link.l1.go = "Sharlie";
				break;
			}
			if (CheckAttribute(pchar, "questTemp.Sharlie") && pchar.questTemp.Sharlie == "freeskiper")
			{
				link.l1 = "Officier, c'est encore moi au sujet du prisonnier Folke Deluc. J'ai acheté les droits sur sa dette et je veux que cet homme soit libéré et remis à moi. Voici ses papiers de dette, jetez un coup d'oeil.";
                link.l1.go = "Sharlie_3";
				break;
			}	
			//<-- Бремя гасконца
			
			//belamour legendary edition диалоги, если герой имеет звания и заслуги перед отечеством -->
			// Офицер с патентом
			if(IsOfficerFullEquip())
			{
				dialog.text = "Salutations, capitaine. Qu'est-ce qui vous amène ici?";
			}
			// вице-адмирал
			if(isMainCharacterPatented() && sti(Items[sti(pchar.EquipedPatentId)].TitulCur) > 4 && npchar.nation == sti(Items[sti(pchar.EquipedPatentId)].Nation))
			{
				dialog.text = "Salutations, Vice-Amiral ! Comment puis-je vous aider ?";
			}
			// генерал-губернатор
			if(CheckAttribute(pchar, "questTemp.Patria.GenGovernor") && npchar.nation == FRANCE)
			{
				dialog.text = "Votre Excellence, Gouverneur Général! Avez-vous des ordres?";
			}
			// <-- legendary edition
			link.l1 = "Oh, rien de spécial, tu sais, juste en train de visiter la ville, alors je suis venu ici par hasard.";
			link.l1.go = "exit";
			link.l2 = "Je voulais parler de certaines affaires.";
			if (CheckCharacterItem(pchar, "CaptainBook") && !CheckAttribute(pchar, "questTemp.different.GiveShipLetters.speakFort"))
			{
				if((pchar.questTemp.different.GiveShipLetters.city == npchar.city) && CheckAttribute(pchar, "questTemp.different.GiveShipLetters"))
				{
					link.l2.go = "F_ShipLetters_1";
				}
				else
				{
					link.l2.go = "quests";
				}		
			}
			else
			{
				if(CheckAttribute(pchar,"questTemp.ReasonToFast") && !CheckAttribute(pchar,"questTemp.ReasonToFast.SpeakOther") && !CheckAttribute(pchar, "questTemp.ReasonToFast.cantSpeakOther") && (pchar.questTemp.ReasonToFast.city == NPChar.city))
				{
					link.l2.go = "ReasonToFast_Prison1";
				}
				else
				{
					link.l2.go = "quests";
				}	
			}
			if (!sti(pchar.questTemp.jailCanMove))
			{
				link.l4 = "Je veux entrer dans la prison.";
				link.l4.go = "ForGoodMove";		
			}
			if (CheckAttribute(pchar, "questTemp.jailCanMove.City") && npchar.city == pchar.questTemp.jailCanMove.City)
			{
				link.l5 = "Hey, pourriez-vous me dire quel crime le condamné nommé "+GetFullName(characterFromId(pchar.questTemp.jailCanMove.prisonerId))+"est en train de purger une peine pour?";
				link.l5.go = "KnowAboutPrisoner";	
			}
			
			if(CheckAttribute(pchar,"GenQuest.CaptainComission") && (pchar.GenQuest.CaptainComission.variant == "A2") && (pchar.GenQuest.CaptainComission.City == NPChar.city))
			{
				if(!CheckAttribute(pchar,"GenQuest.CaptainComission.PrisonFree"))
				{
					bool zMsm = (CheckAttribute(pchar,"GenQuest.CaptainComission.GetRumour")) && (!CheckAttribute(pchar,"GenQuest.CaptainComission.SpeakMayor"));
					if(pchar.GenQuest.CaptainComission == "MayorTalkBad" || zMsm) //говорил с губером и отказался или узнал слухи, но не говорил с губером
					{
						link.l6 = "J'ai entendu dire que l'ancien capitaine d'une patrouille "+GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.CaptainComission.ShipType),"Nom")+"Acc"))+" "+pchar.GenQuest.CaptainComission.Name+" est detenu ici en garde a vue. Puis-je lui parler?";
						link.l6.go = "CapComission_PrisonBad1";
					}
					if(pchar.GenQuest.CaptainComission == "MayorTalkGood")
					{
						link.l6 = "Je "+GetFullName(pchar)+", agissant au nom et sur ordre du gouverneur "+XI_ConvertString("Colonie"+pchar.GenQuest.CaptainComission.City+"Gen")+"besoin de parler avec l'ancien capitaine "+pchar.GenQuest.CaptainComission.Name+".";
						link.l6.go = "CapComission_PrisonGood1";
					}
				}	
			}
			if(CheckAttribute(pchar,"GenQuest.EncGirl"))
			{
				if(pchar.GenQuest.EncGirl == "toParents" || pchar.GenQuest.EncGirl == "FindLover")
				{
					if(pchar.GenQuest.EncGirl.Father == "fort_keeper"  && npchar.city == pchar.GenQuest.EncGirl.city)
					{
						link.l9 = "C'est à propos de votre fille...";
						link.l9.go = "EncGirl_1";
					}
				}
			}
			
			if (CheckAttribute(pchar, "GenQuest.Marginpassenger") && pchar.GenQuest.Marginpassenger == "begin" && NPChar.location == pchar.GenQuest.Marginpassenger.City + "_prison")
			{
				link.l12 = "J'ai des affaires avec vous, officier. Je crois que cela vous intéresserait car cela est lié à vos devoirs.";
				link.l12.go = "Marginpassenger";
			}
			
			// Warship, 16.05.11. Генер "Justice for sale".
			if(CheckAttribute(PChar, "GenQuest.JusticeOnSale.PrisonWait") && CheckAttribute(PChar, "GenQuest.JusticeOnSale.CityId") && NPChar.location == PChar.GenQuest.JusticeOnSale.CityId + "_prison")
			{
				link.l13 = "Je veux te parler d'un certain homme - "+PChar.GenQuest.JusticeOnSale.SmugglerName+". Il est votre prisonnier, si je ne me trompe pas.";
				link.l13.go = "JusticeOnSale_1";
			}
			
			// --> belamour ночной приключенец
			if(CheckAttribute(pchar,"GenQuest.NightAdventureToJail"))
			{
				link.l14 = "Bonjour officier. Autant que je sache, il y a quelque temps, un citoyen ivre a été arrêté après avoir essayé de se battre avec un garde dans les rues."; 
				link.l14.go = "NightAdventure_CitizenHomie";
			}
			
			if(CheckAttribute(pchar,"GenQuest.NightAdventureToPrisoner"))
			{
				link.l14 = "Officier, j'ai parlé au sentinelle, et il a retiré ses accusations. Voici un bon de lui."; 
				link.l14.go = "NightAdventure_HomieToPrisoner";
			}
			// <-- приключенец
			NextDiag.TempNode = "First_officer";
		break;
		
		// --> Jason Похититель
		case "Marginpassenger":
			dialog.text = "Oui? Qu'est-ce que tu es prêt à me dire?";
			link.l1 = "Récemment, j'ai été arrêté dans la rue par "+pchar.GenQuest.Marginpassenger.Name+" qui m'a proposé d'organiser un sale coup : capturer puis rançonner une personne du nom de "+pchar.GenQuest.Marginpassenger.q1Name+". C'est "+pchar.GenQuest.Marginpassenger.Text+"...";
			link.l1.go = "Marginpassenger_1";
		break;
		
		case "Marginpassenger_1":
			dialog.text = "Hmm... C'est très intrigant - continuez s'il vous plaît!";
			link.l1 = "Il connaissait le nom du navire, sur lequel "+pchar.GenQuest.Marginpassenger.q1Name+" prévoyait de naviguer. C'est "+GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.Marginpassenger.ShipType),"Nom")))+" appelé '"+pchar.GenQuest.Marginpassenger.ShipName+"'. De plus, il m'a dit l'heure à laquelle ce navire était censé appareiller.";
			link.l1.go = "Marginpassenger_2";
		break;
	
		case "Marginpassenger_2":
			dialog.text = "Et il a suggéré que vous capturiez le passager puis demandiez une rançon pour lui?";
			link.l1 = "Exactement. Pour collecter la rançon, je me rendrais à "+XI_ConvertString("Colonie"+pchar.GenQuest.Marginpassenger.Targetcity)+", à une certaine personne du nom de "+pchar.GenQuest.Marginpassenger.q2Name+". J'ai payé pour cette information, mais bien sûr, je n'allais pas kidnapper cette personne.";
			link.l1.go = "Marginpassenger_3";
		break;
		
		case "Marginpassenger_3":
			dialog.text = "Alors vous avez décidé de venir me voir et de me faire savoir?";
			link.l1 = "Exactement. Je suis certain que les actions de ce scélérat menacent les citoyens de votre ville, et j'espère que vous prendrez des mesures adéquates.";
			link.l1.go = "Marginpassenger_4";
		break;
		
		case "Marginpassenger_4":
			dialog.text = "Vous aviez tout à fait raison de venir à moi, "+GetAddress_Form(NPChar)+"! Ce coquin, "+pchar.GenQuest.Marginpassenger.Name+", est depuis longtemps sous notre surveillance. J'enquêterai, et si tout ce que vous avez dit est confirmé, nous jetterons ce salaud derrière les barreaux pour une demi-année. Ça lui apprendra à ne pas monter ce genre de complots contre les citoyens respectés!\nEh bien, pour votre honnêteté et votre volonté de servir une bonne cause, je ne manquerai pas de signaler votre acte à notre gouverneur, ce qui, bien sûr, influera sur son attitude envers vous... vous savez, de manière positive. Merci de votre aide, capitaine!";
			link.l1 = "Hmm... Vous êtes le bienvenu, c'était un plaisir d'aider. Au revoir!";
			link.l1.go = "Marginpassenger_5";
		break;
		
		case "Marginpassenger_5":
			DialogExit();
			NextDiag.CurrentNode = "First_officer";
			AddQuestRecord("Marginpassenger", "20");
			AddQuestUserData("Marginpassenger", "sName", pchar.GenQuest.Marginpassenger.Name);
			CloseQuestHeader("Marginpassenger");
			pchar.quest.Marginpassenger_InWorld.over = "yes"; //снять таймер
			DeleteAttribute(Pchar, "GenQuest.Marginpassenger");
			ChangeCharacterComplexReputation(pchar, "nobility", 3);
			ChangeCharacterNationReputation(pchar, sti(npchar.Nation), 5);
			AddCharacterExpToSkill(pchar, "Leadership", 100);//авторитет
			ChangeContrabandRelation(pchar, -25);
			if (GetCharacterIndex("MarginCap") != -1)
			{
				sld = characterFromId("MarginCap");
				sld.lifeday = 0;
				Map_ReleaseQuestEncounter(sld.id);
				Group_DeleteGroup("Sea_MarginCap1");
			}
		break;
		//<-- Похититель

		case "EncGirl_1":
			dialog.text = "Je suis tout ouïe.";
			link.l1 = "J'ai ramené votre fugitif.";
			link.l1.go = "EncGirl_2";
		break;
		
		case "EncGirl_2":
			dialog.text = "Oh, capitaine, merci beaucoup! Comment va-t-elle? Est-elle blessée? Pourquoi a-t-elle fui? Pourquoi?\nNe comprend-elle pas? Le marié est un homme riche et important! La jeunesse est naïve et insensée... cruelle même. Souvenez-vous de ça!";
			link.l1 = "Eh bien, vous êtes son père et la décision finale est la vôtre, mais je ne me presserais pas avec le mariage...";
			link.l1.go = "EncGirl_3";
		break;
		
		case "EncGirl_3":
			dialog.text = "Que savez-vous? Avez-vous vos propres enfants? Non? Quand vous en aurez un, venez me voir et nous en parlerons.\nJ'ai promis une récompense à quiconque la ramènerait à sa famille.";
			link.l1 = "Merci. Tu devrais la surveiller. J'ai le pressentiment qu'elle ne s'arrêtera pas là.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("EncGirl_ToLoverParentsExit");
		break;
		
		// ------------------------- Повод для спешки -----------------------------
		case "ReasonToFast_Prison1":
			pchar.questTemp.ReasonToFast.SpeakOther = true;
			dialog.text = "Je suis tout ouïe, capitaine.";
			link.l1 = "Je veux vous parler d'une collusion criminelle entre un officier de votre garnison et des pirates (explique l'affaire).";
			if(makeint(pchar.reputation.nobility) < 41)
			{
				link.l1.go = "ReasonToFast_Prison_BadRep";			
			}
			else
			{
				link.l1.go = "ReasonToFast_Prison_GoodRep";	
			}
		break;
		case "ReasonToFast_Prison_GoodRep":
			if(pchar.questTemp.ReasonToFast == "PatrolSuccess_1") 
			{ 
				// вилка_А
				dialog.text = "Merci,"+GetSexPhrase("monsieur","mademoiselle")+"! Je donnerai immédiatement l'ordre d'arrêter le scélérat.\nCependant, vous avez engagé des frais et les coffres municipaux, hélas, sont vides...";
				link.l1 = "Monsieur! Je ne l'ai pas fait pour l'argent...";
				link.l1.go = "ReasonToFast_Prison_GoodRep_11";
				
				if(pchar.questTemp.ReasonToFast.chain == "A0") ReasonToFast_RemoveVictim();
				if(pchar.questTemp.ReasonToFast.chain == "A1") pchar.quest.ReasonToFast_ClearLakey.over = "yes";
			}
			if(pchar.questTemp.ReasonToFast == "PatrolSuccess_2") 
			{ 
				// получена карта
				dialog.text = "Merci, "+GetSexPhrase("monsieur","mademoiselle")+"! Je donnerai immédiatement l'ordre d'arrêter le scélérat.\nPensez-y ! Nous voulions le récompenser avec une arme personnelle pour l'excellent service. Que c'est bien que tout se soit éclairci, et je n'ai rien à regretter !";
				link.l1 = "Toujours heureux de servir la justice.";
				link.l1.go = "ReasonToFast_Prison_GoodRep_21";			
			}
			if(pchar.questTemp.ReasonToFast == "PatrolDied") 
			{ 
				// патруль перебит
				dialog.text = "Mi"+GetSexPhrase("ster","ss")+"! Nous soupçonnions cet officier et ses crapules de méfaits depuis un certain temps, mais je pense que vous avez fait un geste imprudent en vous occupant d'eux sans témoins.";
				link.l1 = "Monsieur! Mais je devais me défendre...";
				link.l1.go = "ReasonToFast_Prison_GoodRep_31";	
				pchar.questTemp.ReasonToFast.speakAfterPatrolDied = true;	
				pchar.quest.ReasonToFast_SpeakMayor.over = "yes";	
			}
		break;
		
		case "ReasonToFast_Prison_BadRep":
			if(pchar.questTemp.ReasonToFast == "PatrolSuccess_1") 
			{ 
				// вилка_А
				dialog.text = "Capitaine, vous rendez-vous compte de ce que vous avez fait ?! Nous avons essayé de mettre en place ce piège pendant plus d'un mois ! Et maintenant, juste pour votre divertissement, vous avez ruiné la rencontre de notre patrouille avec le messager "+GetName(NAMETYPE_MAIN,pchar.questTemp.ReasonToFast.p3,NAME_GEN)+" et maintenant vous venez ici pour vous vanter?! Peut-être, pouvez-vous maintenant me dire comment je dois expliquer toutes les dépenses et les coûts de cette opération?!";
				link.l1 = "Votre Grace! Vous refusez tout simplement de voir le point...";
				link.l1.go = "ReasonToFast_Prison_BadRep1";
				pchar.questTemp.ReasonToFast = "speakSuccess_chain_A";
				
				if(pchar.questTemp.ReasonToFast.chain == "A0") ReasonToFast_RemoveVictim();
				if(pchar.questTemp.ReasonToFast.chain == "A1") pchar.quest.ReasonToFast_ClearLakey.over = "yes";
			}
			if(pchar.questTemp.ReasonToFast == "PatrolSuccess_2") 
			{ 
				// получена карта
				dialog.text = "Laissez-moi regarder cette carte...\nVous plaisantez ? Ce morceau de parchemin en lambeaux est une preuve ?";
				link.l1 = "Votre Grâce! Vous refusez tout simplement de voir le point...";
				link.l1.go = "ReasonToFast_Prison_BadRep1";
				TakeItemFromCharacter(pchar, "mapQuest");	
				pchar.questTemp.ReasonToFast = "speakSuccess_chain_B";	
			}
			if(pchar.questTemp.ReasonToFast == "PatrolDied") 
			{ 
				// патруль перебит
				dialog.text = "Voilà une justification originale de la destruction de tout le groupe de patrouille. Eh bien, au moins en venant ici, vous nous avez épargné la nécessité de chercher le meurtrier.";
				link.l1 = "Votre Grâce! Vous refusez tout simplement de voir le point ...";
				link.l1.go = "ReasonToFast_Prison_BadRep1";			
				pchar.questTemp.ReasonToFast = "speakSuccess_chain_A";
				pchar.quest.ReasonToFast_SpeakMayor.over = "yes";
			}		
		break;
		
		case "ReasonToFast_Prison_GoodRep_11":
			dialog.text = "Nonetheless, I think that your efforts should still be rewarded. Here, take this map; it was found in the belongings of a pirate who has recently gone to the gallows. God willing, perhaps you will actually find that treasure, although I find it quite unlikely...";
			link.l1 = "Merci, c'est très généreux de votre part !";
			link.l1.go = "exit";
			AddQuestRecord("ReasonToFast", "15");
			ChangeCharacterComplexReputation(pchar,"nobility", 1); 
			GiveItem2Character(pchar, "mapQuest"); 
			arItem = ItemsFromID("mapQuest");
			ReasonToFast_GenerateTreasureMap(arItem);
			pchar.questTemp.ReasonToFast.state = "chain_A"; // вилка_А, наводки не генерим
			pchar.questTemp.ReasonToFast = "GetMap";			
			ReasonToFast_SetHunterCoastal();
		break;
		case "ReasonToFast_Prison_GoodRep_21":
			dialog.text = "Votre zèle est louable. S'il vous plaît, acceptez cette lame en récompense - c'est le moins que je puisse faire pour vous. Oh, et vous pouvez garder cette carte pour vous. Je suis certain qu'il y a beaucoup de ces faux sur l'Archipel.";
			link.l1 = "Merci, c'est très généreux de votre part !";
			link.l1.go = "exit";
			AddQuestRecord("ReasonToFast", "14");
			ChangeCharacterComplexReputation(pchar,"nobility", 1); 
			GiveItem2Character(pchar, pchar.questTemp.ReasonToFast.p6);
			pchar.questTemp.ReasonToFast.state = "chain_B"; // была получена карта
			pchar.questTemp.ReasonToFast = "GetMap";			
			ReasonToFast_SetHunterCoastal();
		break;
		case "ReasonToFast_Prison_GoodRep_31":
			dialog.text = "Peut-être, peut-être... Eh bien, disons simplement que cet accord a été décidé par la justice divine et par la volonté de notre Seigneur.";
			link.l1 = "Merci, c'est très généreux de votre part!";
			link.l1.go = "exit";
			ChangeCharacterComplexReputation(pchar,"nobility", 1); 
			AddQuestRecord("ReasonToFast", "16");
			CloseQuestHeader("ReasonToFast");
			DeleteAttribute(pchar,"ReasonToFast");			
		break;
		
		case "ReasonToFast_Prison_BadRep1":
			dialog.text = "N'osez pas me faire la leçon ! Pour moi, il est évident que vous collaborez avec ces canailles ! Gardes, saisissez ce 'bienfaiteur' !";
			link.l1 = "Pas possible !";
			link.l1.go = "fight";
			
			pchar.quest.ReasonToFast_ExitFromTown.win_condition.l1			= "EnterToSea";           	
            pchar.quest.ReasonToFast_ExitFromTown.function    				= "ReasonToFast_ExitFromTownFight";
			pchar.questTemp.ReasonToFast.canSpeakSailor = true;			
			pchar.TownEscape = true;
			Flag_PIRATE();
		break;
		// ------------------------- Повод для спешки -----------------------------
		
		// -------------------------- Операция 'Галеон' ----------------------------
		case "CapComission_PrisonBad1":
			dialog.text = "Et quelles affaires avez-vous avec lui?";
			link.l1 = "J'ai plusieurs affaires privées à discuter.";
			link.l1.go = "CapComission_PrisonBad2";
		break;
		
		case "CapComission_PrisonBad2":
			dialog.text = "Capitaine, j'ai un ordre direct d'arrêter et d'envoyer à la résidence toute personne qui demande à propos de "+pchar.GenQuest.CaptainComission.Name+"pour un interrogatoire plus approfondi.";
			link.l1 = "Belle installation que vous avez ici ! Avoir des prisonniers qui viennent eux-mêmes à vous pour être arrêtés !";
			link.l1.go = "CapComission_PrisonBad3";
		break;
		
		case "CapComission_PrisonBad3":
			dialog.text = "Et pourtant, je vous demanderais de vous rendre vos armes !";
			link.l1 = "Va te faire foutre! Prends-le moi de force, alors!";
			link.l1.go = "fight";
			CaptainComission_GenerateCaptainInPrison(); // данила . на всякий случай ,чтобы сгенерился нормально.
			AddDialogExitQuest("CaptainComission_GenerateCapJail");
		break;
		
		case "CapComission_PrisonGood1":
			dialog.text = "Oui, bien sûr. J'ai des ordres du gouverneur pour vous apporter de l'aide dans cette affaire. Vous pouvez maintenant rendre visite au prisonnier.";
			link.l1 = "Merci...";
			link.l1.go = "exit";
			pchar.questTemp.jailCanMove = true;
			AddDialogExitQuest("CaptainComission_GenerateCapJail");
		break;
		
		case "CapComission_PrisonFree1":
		if(CheckAttribute(pchar,"GenQuest.CaptainComission"))// лесник . разделение диалога если кеп убит или нет
		{
			dialog.text = "Euh, capitaine, je n'ai pas l'autorité pour libérer ce prisonnier de la garde à vue. Vous devez demander une autorisation auprès du gouverneur.";
			link.l1 = "Officier, j'agis pour le bien de l'enquête. Le prisonnier a accepté de coopérer avec les autorités et de révéler la cachette. Le temps est essentiel - les contrebandiers peuvent trouver la précieuse cargaison, et alors elle sera perdue pour le peuple.";
			link.l1.go = "CapComission_PrisonFree2";
		}
         else
		 {
         	dialog.text = "Vous n'auriez pas dû le tuer, capitaine... Cela ne me dérange pas cependant. Nous devrons vous exécuter à la place de lui. Gardes! Saisissez-le!";
            link.l2 = "Tu as choisi le mauvais gars avec qui te foutre!...";
             link.l2.go = "fight";
			 NextDiag.TempNode = "First_officer";
			NextDiag.CurrentNode = NextDiag.TempNode; 
			AddDialogExitQuest("OpenTheDoors");
		 }			 
		break;
		
		case "CapComission_PrisonFree2":
			dialog.text = "Mais je pourrais lui attribuer une escorte.";
			link.l1 = "Il n'y a pas besoin de - J'ai assez de gardes. De plus, je ne voudrais pas que l'emplacement de la cachette soit rendu public.";
			link.l1.go = "CapComission_PrisonFree3";
		break;
		
		case "CapComission_PrisonFree3":
			dialog.text = "Hmm... oh, bien. Mais tu répondras pour lui de ta tête.";
			link.l1 = "Bien sûr.";
			link.l1.go = "exit";
			NextDiag.TempNode = "First_officer";
			NextDiag.CurrentNode = NextDiag.TempNode; 
			AddDialogExitQuest("OpenTheDoors");
		break;
		// -------------------------- Операция 'Галеон' ----------------------------
		
		case "F_ShipLetters_1":
			dialog.text = "Parle maintenant, j'écoute.";
			link.l1 = "J'ai avec moi de la documentation sur un navire. Son propriétaire doit l'avoir perdu, et je pense qu'il pourrait vous intéresser.";
			link.l1.go = "F_ShipLetters_2";
			pchar.questTemp.different.GiveShipLetters.speakFort = true;
		break;
		
		case "F_ShipLetters_2":			
			if(sti(pchar.questTemp.different.GiveShipLetters.variant) == 0)
			{
				dialog.text = "Balivernes ! Ne me dérangez pas pendant que je travaille ! Allez voir les autorités portuaires, si ça vous préoccupe !";
				link.l1 = "Eh bien, merci, je suppose...";
				link.l1.go = "exit";
			}
			else
			{
				if(!CheckAttribute(pchar, "questTemp.different.GiveShipLetters.speakUsurer_1"))
				{
					dialog.text = "Oui, c'est le propriétaire local. Peut-être, un prix de "+sti(pchar.questTemp.different.GiveShipLetters.price2)+" pesos serviront de récompense adéquate pour votre vigilance, capitaine.";
					link.l1 = "Peut-être pas.";
					link.l1.go = "F_ShipLetters_3";	
					link.l2 = "Une offre généreuse. Les documents sont à vous, alors !";
					link.l2.go = "F_ShipLetters_4";
				}
				else
				{
					if(sti(pchar.questTemp.different.GiveShipLetters.variant) == 1)
					{
						dialog.text = "Oh, maintenant c'est vraiment intéressant! Je crois que la trésorerie de la ville vous paiera volontiers "+sti(pchar.questTemp.different.GiveShipLetters.price4)+" pesos pour votre contribution à la lutte contre le commerce illégal.";
						link.l1 = "Peut-être pas.";
						link.l1.go = "F_ShipLetters_3";
						link.l2 = "Une offre généreuse. Les documents sont à toi, alors!";
						link.l2.go = "F_ShipLetters_4";
					}
					if(sti(pchar.questTemp.different.GiveShipLetters.variant) == 2)
					{
						dialog.text = "Oh Seigneur! Quelle bonne chance que vous soyez venu à moi. Je suppose que mon malheureux collègue vous paiera volontiers "+sti(pchar.questTemp.different.GiveShipLetters.price3)+" pesos pour éviter la publicité de cette affaire.";
						link.l1 = "Peut-être pas.";
						link.l1.go = "F_ShipLetters_3";
						link.l2 = "Une offre généreuse. Les documents sont à vous, alors !";
						link.l2.go = "F_ShipLetters_4";
					}
				}
			}
		break;
		
		case "F_ShipLetters_3":
			dialog.text = "C'est ma ville, capitaine.";
			link.l1 = "Je m'en souviendrai.";
			link.l1.go = "exit";
		break;
		
		case "F_ShipLetters_4":
			TakeItemFromCharacter(pchar, "CaptainBook"); 
			if(sti(pchar.questTemp.different.GiveShipLetters.variant) == 1)
			{
				if(!CheckAttribute(pchar, "questTemp.different.GiveShipLetters.speakUsurer_1"))
				{
					addMoneyToCharacter(pchar, sti(pchar.questTemp.different.GiveShipLetters.price2)); 
				}
				else
				{
					addMoneyToCharacter(pchar, sti(pchar.questTemp.different.GiveShipLetters.price4)); 
				}
			}
			if(sti(pchar.questTemp.different.GiveShipLetters.variant) == 2)
			{
				if(!CheckAttribute(pchar, "questTemp.different.GiveShipLetters.speakUsurer_1"))
				{
					addMoneyToCharacter(pchar, sti(pchar.questTemp.different.GiveShipLetters.price2)); 
				}
				else
				{
					addMoneyToCharacter(pchar, sti(pchar.questTemp.different.GiveShipLetters.price3)); 
				}
			}
						
			if((sti(pchar.questTemp.different.GiveShipLetters.variant) == 0) || (sti(pchar.questTemp.different.GiveShipLetters.variant) == 2))
			{	
				ChangeCharacterComplexReputation(pchar,"nobility", -1); 
				OfficersReaction("bad"); 
			}	
			pchar.questTemp.different = "free";
			pchar.quest.GiveShipLetters_null.over = "yes"; //снимаем таймер 
			AddQuestRecord("GiveShipLetters", "8");			
			CloseQuestHeader("GiveShipLetters");
			DeleteAttribute(pchar, "questTemp.different.GiveShipLetters");
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;

		
        case "ForGoodMove":
			//belamour legendary edition диалоги, если герой имеет звания и заслуги перед отечеством -->
			// генерал-губернатор
			if(CheckAttribute(pchar, "questTemp.Patria.GenGovernor") && npchar.nation == FRANCE)
			{
				dialog.text = "Bien sûr, vous pouvez tout voir - J'ai un ordre complet ici !";
				link.l1 = "Eh bien, vérifions cela, lieutenant.";
				link.l1.go = "exit";
				pchar.questTemp.jailCanMove = true;
				break;
			}
			// вице-адмирал
			if(isMainCharacterPatented() && sti(Items[sti(pchar.EquipedPatentId)].TitulCur) > 4 && npchar.nation == sti(Items[sti(pchar.EquipedPatentId)].Nation))
			{
				dialog.text = "Bien sûr, Votre Excellence. Vous pouvez passer.";
				link.l1 = "Merci officier.";
				link.l1.go = "exit";
				pchar.questTemp.jailCanMove = true;
				break;
			}
			// Офицер с патентом
			if(IsOfficerFullEquip() && npchar.nation == sti(Items[sti(pchar.EquipedPatentId)].Nation))
			{
				dialog.text = "Eh bien, je ne vois aucune raison de vous refuser - après tout, vous êtes le capitaine du navire au service de "+NationNameGenitive(sti(npchar.nation))+". Venez dedans."; 
				link.l1 = "Merci, officier.";
				link.l1.go = "exit";
				pchar.questTemp.jailCanMove = true;
				break;
			}
			// <-- legendary edition
			dialog.text = NPCStringReactionRepeat("Mais pourquoi en avez-vous besoin ? Croyez-moi, il n'y a rien d'intéressant, à part les voleurs et les bandits.","Nous avions déjà discuté de ce souhait de vous.","Encore? Nous en avions déjà parlé deux fois!","Hmm, encore...","bloc",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("Néanmoins, j'aimerais me joindre à votre visite des casemates. Je suis très intéressé !","Oui, exactement. Mais je voulais en parler.","Eh bien, peut-être la troisième fois...","J'espère que vos prisonniers ne me quitteront pas.",npchar,Dialog.CurrentNode);
			link.l1.go = "ForGoodMove_1";
		break;
		
        case "ForGoodMove_1":
			pchar.questTemp.jailCanMove.money = 20+hrand(3)*10;
			if (sti(colonies[FindColony(npchar.city)].jail))
			{
				dialog.text = "Eh bien, je ne vois aucune raison de refuser. "+FindRussianDublonString(sti(pchar.questTemp.jailCanMove.money))+" - et jusqu'à ce que vous quittiez la prison, vous pouvez librement vous promener dans les couloirs et même converser avec les détenus.";
				if (PCharDublonsTotal() >= sti(sti(pchar.questTemp.jailCanMove.money)))
				{
					link.l1 = "Je suis d'accord, voici vos pieces!";
					link.l1.go = "ForGoodMove_agree";
				}
				link.l2 = "Cela ne fonctionnera pas. C'est trop pour une errance sans but dans les couloirs.";
				link.l2.go = "exit";
			}
			else
			{
				dialog.text = RandPhraseSimple("Non, c'est strictement interdit par le règlement. Quoi? Vous pensez que nous avons un cirque ici? Dégagez et ne me dérangez pas dans mes devoirs.","Je ne peux pas permettre à des gens étranges de se promener dans ma prison. S'il vous plaît, arrêtez de me déranger!");
				link.l1 = "D'accord, comme tu dis...";
				link.l1.go = "exit";
			}
		break;
		
        case "ForGoodMove_agree":
            dialog.text = "D'accord, tu peux commencer ton excursion maintenant...";
			link.l1 = "Merci, officier.";
			link.l1.go = "exit";
			pchar.questTemp.jailCanMove = true;
			RemoveDublonsFromPCharTotal(sti(pchar.questTemp.jailCanMove.money)));
		break;
		
        case "KnowAboutPrisoner":
			switch (pchar.questTemp.jailCanMove.ownerPrison)
			{
				case "0": sTemp = "For murder."; break;
				case "1": sTemp = "He is accused of piracy."; break;
				case "2": sTemp = "For banditry and robbery."; break;
				case "3": sTemp = "He was caught stealing."; break;
				case "4": sTemp = "For petty theft."; break;
				case "5": sTemp = "For cheating."; break;
				case "6": sTemp = "For vagrancy and begging."; break;
			}
			dialog.text = sTemp;
			// генерал-губернатор
			if(CheckAttribute(pchar, "questTemp.Patria.GenGovernor") && npchar.nation == FRANCE)
			{
				link.l1 = "Je vois... Donnez-le-moi, officier, et ensuite je déciderai moi-même du sort de ce prisonnier.";
				link.l1.go = "KnowAboutPrisoner_gengov";
			DeleteAttribute(pchar, "questTemp.jailCanMove.City");
		break;
			}
			// вице-адмирал
			if(isMainCharacterPatented() && sti(Items[sti(pchar.EquipedPatentId)].TitulCur) > 4 && npchar.nation == sti(Items[sti(pchar.EquipedPatentId)].Nation))
			{
				link.l1 = "Je vois... Donnez-le moi, officier, et alors je déciderai moi-même du sort de ce prisonnier.";
				link.l1.go = "KnowAboutPrisoner_admiral";
				DeleteAttribute(pchar, "questTemp.jailCanMove.City");
				break;
			}
			link.l1 = "Je vois... Et y a-t-il une possibilité de rachat, de caution... ou de le libérer d'une autre manière?";
			link.l1.go = "KnowAboutPrisoner_" + pchar.questTemp.jailCanMove.ownerPrison;
			DeleteAttribute(pchar, "questTemp.jailCanMove.City");
		break;
		
        case "KnowAboutPrisoner_0":
			dialog.text = "Bien sûr que non. Cet oiseau de potence ira droit en enfer. Le gouverneur a sa cause sous contrôle spécial!";
			link.l1 = "Heh, je vois...";
			link.l1.go = "notFree_exit";
		break;	
		
		case "KnowAboutPrisoner_1":
			dialog.text = "Plaisantes-tu? Il a du aller à la potence il y a longtemps! Il épousera sûrement une corde bientôt. Oublie-le simplement.";
			link.l1 = "Compris. Et déjà oublié...";
			link.l1.go = "notFree_exit";
		break;
		
        case "KnowAboutPrisoner_2":
			dialog.text = "Je ne pense pas. Il a cause beaucoup de problemes a nos concitoyens. Alors ne le demandez pas.";
			link.l1 = "Hmm, je vois.";
			link.l1.go = "notFree_exit";
		break;
		
        case "KnowAboutPrisoner_3":
			dialog.text = "Probablement pas. C'est un voleur, et un voleur doit rester en prison.";
			link.l1 = "Oh ! Bien dit, lieutenant !";
			link.l1.go = "notFree_exit";
		break;
		
        case "KnowAboutPrisoner_4":
			dialog.text = "Je ne sais vraiment pas. Il a juste volé une petite chose. Je ne peux pas le libérer, mais le laisser pourrir en prison n'est certainement pas juste.";
			link.l1 = "Eh bien, alors donnez-le-moi, lieutenant. Je paierai sa caution - un montant raisonnable, bien sûr.";
			link.l1.go = "KnowAboutPrisoner_free";
		break;
		
        case "KnowAboutPrisoner_5":
			dialog.text = "Libérer? Cela semble probable. À mon avis, il n'y a aucun intérêt à détenir ce petit escroc ici.";
			link.l1 = "Eh bien, alors donnez-le-moi, lieutenant. Je paierai sa caution - une somme raisonnable, bien sûr.";
			link.l1.go = "KnowAboutPrisoner_free";
		break;
		
		case "KnowAboutPrisoner_6":
			dialog.text = "Hmm... Il y a du sens dans vos paroles. Ce vagabond n'a pas sa place ici - il ne fait que répandre la saleté et les maladies...";
			link.l1 = "Eh bien, donnez-le moi alors, lieutenant. Je paierai sa caution - une somme raisonnable, bien sûr.";
			link.l1.go = "KnowAboutPrisoner_free";
		break;
		
        case "KnowAboutPrisoner_free":
			pchar.questTemp.jailCanMove.ownerPrison.money = 50+hrand(10)*10;
			dialog.text = "D'accord, nous avons un accord. "+FindRussianDublonString(sti(pchar.questTemp.jailCanMove.ownerPrison.money))+"sur le clou, et vous pouvez l'emporter tout de suite.";
			if (PCharDublonsTotal() >= sti(pchar.questTemp.jailCanMove.ownerPrison.money))
			{
				link.l1 = LinkRandPhrase("Excellent ! Je suis d'accord !","Vous avez un marché, officier !","Excellent. Je suis prêt à payer cette contribution.");
				link.l1.go = "KnowAboutPrisoner_agree";
			}
			link.l2 = "Non, c'est trop cher. Je pense que je vais passer.";
			link.l2.go = "KnowAboutPrisoner_exit";
		break;
		
        case "KnowAboutPrisoner_agree":
			dialog.text = "D'accord, vous pouvez aller à sa cellule et emmener ce gamin avec vous.";
			link.l1 = "Merci.";
			link.l1.go = "exit";
			pchar.questTemp.jailCanMove = true;
			RemoveDublonsFromPCharTotal(sti(pchar.questTemp.jailCanMove.ownerPrison.money));
			Log_Info("You have given " + FindRussianDublonString(sti(pchar.questTemp.jailCanMove.ownerPrison.money)) + "");
			DeleteAttribute(pchar, "questTemp.jailCanMove.ownerPrison");
			sld = characterFromId(pchar.questTemp.jailCanMove.prisonerId)
			LAi_CharacterEnableDialog(sld);
			sld.dialog.currentnode = "ToPrisonHead_canMove";
		break;
		
        case "KnowAboutPrisoner_exit":
			dialog.text = "Eh bien, c'est ton choix. Je ne te donne pas une autre chance...";
			link.l1 = "Pas besoin de le faire.";
			link.l1.go = "exit";
			DeleteAttribute(pchar, "questTemp.jailCanMove.ownerPrison");
			sld = characterFromId(pchar.questTemp.jailCanMove.prisonerId);
			LAi_CharacterEnableDialog(sld);
			sld.dialog.currentnode = "ToPrisonHead_expansive";
		break;
		
        case "notFree_exit":
			sld = characterFromId(pchar.questTemp.jailCanMove.prisonerId);
			LAi_CharacterEnableDialog(sld);
			sld.dialog.currentnode = "ToPrisonHead_notFree";
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
		// belamour legendary edition -->
		// генерал-губернатор
		case "KnowAboutPrisoner_gengov":
			dialog.text = "Bien sûr, votre Excellence, si vous le souhaitez, prenez ce malheureux. Soyez juste prudent, c'est toujours un criminel...";
			link.l1 = "C'est super. Ne t'inquiète pas lieutenant, je sais ce que je fais.";
			link.l1.go = "exit";
			pchar.questTemp.jailCanMove = true;
			DeleteAttribute(pchar, "questTemp.jailCanMove.ownerPrison");
			sld = characterFromId(pchar.questTemp.jailCanMove.prisonerId)
			LAi_CharacterEnableDialog(sld);
			sld.dialog.currentnode = "ToPrisonHead_canMove";
		break;
		// вице-адмирал
		case "KnowAboutPrisoner_admiral":
			dialog.text = "Eh bien... Je ne sais même pas... En fait, je ne peux pas simplement laisser partir les prisonniers. Mais tu es toujours un vice-amiral, alors tu as probablement le droit de prendre ce criminel.";
			link.l1 = "C'est génial. Ne t'inquiète pas lieutenant, je sais ce que je fais.";
			link.l1.go = "exit";
			pchar.questTemp.jailCanMove = true;
			DeleteAttribute(pchar, "questTemp.jailCanMove.ownerPrison");
			sld = characterFromId(pchar.questTemp.jailCanMove.prisonerId)
			LAi_CharacterEnableDialog(sld);
			sld.dialog.currentnode = "ToPrisonHead_canMove";
		break;
		// <-- legendary edition
		//---------------- Протектор ------------------
        case "First_protector":
			// генерал-губернатор
			if(CheckAttribute(pchar, "questTemp.Patria.GenGovernor") && npchar.nation == FRANCE)
			{
				dialog.text = "Gouverneur Général, Votre Excellence! Entrez, mais soyez prudent: vous pouvez vous attendre à tout de ces criminels...";
				link.l1 = "Ne t'inquiète pas, soldat, je m'en occuperai si quelque chose arrive.";
				link.l1.go = "exit";
				NextDiag.TempNode = "First_protector";
				break;
			}
			// вице-адмирал
			if(isMainCharacterPatented() && sti(Items[sti(pchar.EquipedPatentId)].TitulCur) > 4 && npchar.nation == sti(Items[sti(pchar.EquipedPatentId)].Nation))
			{
				dialog.text = "Salutations, Vice-Amiral ! Je suis de service ici : je m'assure que personne n'entre ou ne sort sans autorisation. Mais vous, bien sûr, avez le droit de passer librement ici.";
				link.l1 = "Eh bien, c'est merveilleux.";
				link.l1.go = "exit";
				NextDiag.TempNode = "First_protector";
				break;
			}
			if (sti(pchar.questTemp.jailCanMove))
			{
				dialog.text = RandPhraseSimple("Vous pouvez passer, le gardien a donné sa permission.","J'ai reçu une ordonnance du gardien de la prison. Vous pouvez passer librement.");
				link.l1 = "Très bien.";
				link.l1.go = "exit";
				DeleteAttribute(pchar, "questTemp.jailCanMove.ownerPrison.money");
			}
			else
			{
				dialog.text = RandPhraseSimple("Vous ne pouvez pas aller plus loin sans la permission spécifique du gardien de la prison!","Je ne réponds qu'au geôlier! Si vous essayez d'aller plus loin sans sa permission, vous êtes fini!");
				link.l1 = RandPhraseSimple("Je vois","D'accord")+", soldat.";
				link.l1.go = "exit";
			}
			NextDiag.TempNode = "First_protector";
		break;
		//---------------- Солдаты ------------------
        case "First_soldier":
            dialog.text = RandPhraseSimple("Je suis en service, ne me dérange pas.","Passe ton chemin, je n'ai pas le droit de te parler.");
			link.l1 = "D'accord, soldat.";
			link.l1.go = "exit";
			NextDiag.TempNode = "First_soldier";
		break;
		//---------------- Заключенные ------------------
        case "First_prisoner": 
			if (GetNationRelation2MainCharacter(sti(npchar.nation)) == RELATION_ENEMY)
			{
				dialog.text = LinkRandPhrase("Ho-ho, n'est-ce pas un bon moment !","Tranchez-les, "+GetSexPhrase("camarade","lass")+", coupe!!!","Oh, enfer! J'ai perdu tout espoir de voir le cadavre de mon geôlier!");
				link.l1 = RandPhraseSimple("Heh !","Arrgh !");
				link.l1.go = "NoMoreTalkExit";
				if (rand(10) > 6 && !CheckAttribute(pchar, "questTemp.Sharlie.Lock") && !CheckAttribute(pchar, "GenQuest.PrisonQuestLock") && !CheckAttribute(pchar, "quest.GivePrisonFree") && !CheckAttribute(pchar, "quest.GivePrisonFree_Over") && !CheckAttribute(pchar, "quest.DeliverToBander")) // Addon 2016-1 Jason пиратская линейка
				{
					dialog.text = RandPhraseSimple("Attends, "+GetSexPhrase("camarade","lassie")+"!! Libérez-moi !","Écoute, "+GetSexPhrase("camarade","fillette")+", ouvrez gentiment la cellule.");
					link.l1 = "Pour quelle raison?";
					link.l1.go = "Prisoner_1"; // на квест освобождения заключённого
				}
			}
			else
			{
				dialog.text = LinkRandPhrase("Je suis accuse de vol, mais je ne suis pas coupable!","Arrgh, tu es une raclure bien peignée... Aimerais-tu t'asseoir dans ma cellule un peu ?! Kheh-heh-heh...","Je ne suis pas coupable!");
				link.l1 = RandPhraseSimple("Taisez-vous !","Je m'en fous de toi...");
				link.l1.go = "NoMoreTalkExit";
				if (rand(10) > 6 && !CheckAttribute(pchar, "questTemp.Sharlie.Lock") && !CheckAttribute(pchar, "GenQuest.PrisonQuestLock") && !CheckAttribute(pchar, "quest.GivePrisonFree_Over") && !CheckAttribute(pchar, "quest.GivePrisonFree") && !CheckAttribute(pchar, "quest.DeliverToBander") && !sti(colonies[FindColony(npchar.city)].HeroOwn)) // Addon 2016-1 Jason пиратская линейка
				{
					dialog.text = RandPhraseSimple("Attends, "+GetSexPhrase("camarade","lass")+", ne passe pas si vite !","Ne te presse pas, "+GetSexPhrase("camarade","fillette")+", parlons.");
					link.l1 = "Pour quelle raison?";
					if (rand(1))
					{
						link.l1.go = "Prisoner_1"; // на квест освобождения заключённого
					}
					else
					{
						link.l1.go = "Deliver_1"; // на квест передачу весточки
					}
				}
			}
		break;
		// -------------------- освобождение заключённого --------------------
        case "Prisoner_1":
            dialog.text = "Écoute-moi, mon pote. Ne pense pas que je ne suis pas bien et tout. J'ai juste besoin de sortir d'ici...";
			link.l1 = "Quoi?!";
			link.l1.go = "Prisoner_2";
			GetChestPlaceName();
			pchar.questTemp.jailCanMove.prisonerId = npchar.id; //запомним Id
			pchar.questTemp.jailCanMove.IsTrue = rand(4); //вид клада
			pchar.questTemp.jailCanMove.Item1 = GenQuestPrison_GenerateArtefact();
			pchar.questTemp.jailCanMove.Item2 = GenQuestPrison_GenerateBlade();
			pchar.questTemp.jailCanMove.Name = GetFullName(npchar); //имя перца
			npchar.nation = PIRATE;
		break;
        case "Prisoner_2":
            dialog.text = "Ce que tu as entendu ! Aide-moi, et je pourrai te rembourser...";
			link.l1 = "Voilà qui est intéressant. Qui êtes-vous et qu'est-ce que vous pouvez m'offrir?";
			link.l1.go = "Prisoner_3";
		break;
        case "Prisoner_3":
            dialog.text = "Mon nom est "+GetFullName(npchar)+". J'ai des affaires cachées dans un endroit sûr. Sortez-moi simplement d'ici et emmenez-moi à "+XI_ConvertString(pchar.questTemp.jailCanMove.islandId+"Acc")+". Là, dans une grotte, j'ai le trésor. Nous l'obtiendrons et le partagerons !";
			link.l1 = "Et qu'est-ce que tu as dans ta cachette? Et comment puis-je savoir que tu dis la vérité?";
			link.l1.go = "Prisoner_4";
		break;
        case "Prisoner_4":
            dialog.text = "Je jure que je dis la vérité ! Quant au butin - il y a un trésor et de l'argent...";
			link.l1 = "Non, mon pote. Je ne risque pas ma peau pour un butin douteux. Je suis désolé...";
			link.l1.go = "Prisoner_5";
			if (GetNationRelation2MainCharacter(sti(npchar.nation)) != RELATION_ENEMY)
			{			
				// belamour legendary edition адмирал и губернатор может договориться без денег
				bool bAdmiral = isMainCharacterPatented() && sti(Items[sti(pchar.EquipedPatentId)].TitulCur) > 4 && npchar.nation == sti(Items[sti(pchar.EquipedPatentId)].Nation);
				bool bGenGov = CheckAttribute(pchar, "questTemp.Patria.GenGovernor") && npchar.nation == GetBaseHeroNation());
				if(!bAdmiral && !bGenGov)
				{
				link.l2 = "Eh bien, cela pourrait valoir la peine de prendre un risque... Je propose la chose suivante : je peux éliminer les gardes dans la prison et vous emmener à mon navire. Si tout se passe bien, je veux que vous restiez à mes côtés tout le temps jusqu'à ce que nous arrivions à la grotte sur  "+XI_ConvertString(pchar.questTemp.jailCanMove.islandId+"Voc")+". Accord ?"; // belamour gen
				link.l2.go = "Prisoner_agree"; //силовой способ вызволения
				}
				link.l3 = "D'accord, j'essaierai de t'aider. Je parlerai au gardien de la prison. Peut-être, je pourrai te sortir de là.";
				link.l3.go = "ToPrisonHead_agree"; //мирный способ вызволения
			}
			else
			{
				link.l2 = "D'accord, je vais te croire et ouvrir ta cellule. Je veux que tu restes à mes côtés tout le temps jusqu'à ce que nous arrivions à la grotte sur "+XI_ConvertString(pchar.questTemp.jailCanMove.islandId+"Voc")+". Marché conclu?";
				link.l2.go = "Prisoner_agree_3"; //силовой способ вызволения, когда тюремщики убиты
			}
		break;
        case "Prisoner_5":
            dialog.text = RandPhraseSimple("Maudis sois-tu, coquin !","Maudits soyez-vous, vous m'avez déchiré, racaille...");
			link.l1 = RandPhraseSimple("Et tout le meilleur pour toi aussi. Adieu...","La lune n'a pas besoin des aboiements des chiens...");
			link.l1.go = "NoMoreTalkExit";
		break;
        case "Prisoner_agree":
            dialog.text = "D'accord. Je ne suis pas en position de faire la fine bouche.";
			link.l1 = "D'accord. Je vais briser votre verrou maintenant pour vous sortir, et nous allons percer. Êtes-vous prêt?";
			link.l1.go = "Prisoner_agree_1";
		break;
        case "Prisoner_agree_1":
            dialog.text = "Oui, "+GetSexPhrase("camarade","fillette")+", je suis prêt !";
			link.l1 = "Alors, allons-y !";
			link.l1.go = "Prisoner_agree_2";
		break;
        case "Prisoner_agree_2":
			string slai_group = GetNationNameByType(sti(npchar.nation))  + "_citizens";
			LAi_group_AttackGroup(slai_group, LAI_GROUP_PLAYER);
			if (rand(3) != 1) SetNationRelation2MainCharacter(sti(npchar.nation), RELATION_ENEMY);
			ReOpenQuestHeader("GivePrisonFree");
			AddQuestRecord("GivePrisonFree", "1");
            AddQuestUserData("GivePrisonFree", "sCity", XI_ConvertString("Colony"+npchar.city+"Gen"));
            AddQuestUserData("GivePrisonFree", "sName", pchar.questTemp.jailCanMove.Name);
            AddQuestUserData("GivePrisonFree", "sIsland", XI_ConvertString(pchar.questTemp.jailCanMove.islandId+"Voc"));
			pchar.quest.GivePrisonFree_Death.win_condition.l1 = "NPC_Death";
			pchar.quest.GivePrisonFree_Death.win_condition.l1.character = npchar.id;
			pchar.quest.GivePrisonFree_Death.win_condition = "GivePrisonFree_Death";
			Pchar.quest.GivePrisonFree.win_condition.l1 = "location";
			Pchar.quest.GivePrisonFree.win_condition.l1.location = pchar.questTemp.jailCanMove.placeId;
			Pchar.quest.GivePrisonFree.win_condition = "GivePrisonFree";			
			DeleteAttribute(npchar, "LifeDay");
			GiveItem2Character(npchar, "unarmed");
			EquipCharacterbyItem(npchar, "unarmed");
			GetCharacterPos(npchar, &locx, &locy, &locz);	
			ChangeCharacterAddressGroup(npchar, npchar.location, "reload", LAi_FindNearestFreeLocator("reload", locx, locy, locz));
			LAi_SetActorType(npchar);
			LAi_group_Register("DeliveQuest_Prison");
			LAi_group_SetRelation("DeliveQuest_Prison", LAI_GROUP_PLAYER, LAI_GROUP_FRIEND);
			//LAi_group_SetAlarmReaction(LAI_GROUP_PLAYER, "DeliveQuest_Prison", LAI_GROUP_ENEMY, LAI_GROUP_FRIEND);
			LAi_group_MoveCharacter(npchar, "DeliveQuest_Prison");
			LAi_ActorFollowEverywhere(npchar, "", -1);
			DialogExit();
			AddDialogExitQuest("MainHeroFightModeOn");
		break;

        case "Prisoner_agree_3":
            dialog.text = "D'accord. Je ne suis pas en position de faire le difficile.";
			link.l1 = "D'accord. Suivez-moi aussi vite que vous le pouvez - nous devons encore arriver à mon navire. Ne tardez pas!";
			link.l1.go = "Prisoner_agree_4";
		break;
        case "Prisoner_agree_4":
			ReOpenQuestHeader("GivePrisonFree");
			AddQuestRecord("GivePrisonFree", "1");
            AddQuestUserData("GivePrisonFree", "sCity", XI_ConvertString("Colony"+npchar.city+"Gen"));
            AddQuestUserData("GivePrisonFree", "sName", pchar.questTemp.jailCanMove.Name);
            AddQuestUserData("GivePrisonFree", "sIsland", XI_ConvertString(pchar.questTemp.jailCanMove.islandId+"Voc"));
			pchar.quest.GivePrisonFree_Death.win_condition.l1 = "NPC_Death";
			pchar.quest.GivePrisonFree_Death.win_condition.l1.character = npchar.id;
			pchar.quest.GivePrisonFree_Death.win_condition = "GivePrisonFree_Death";
			Pchar.quest.GivePrisonFree.win_condition.l1 = "location";
			Pchar.quest.GivePrisonFree.win_condition.l1.location = pchar.questTemp.jailCanMove.placeId;
			Pchar.quest.GivePrisonFree.win_condition = "GivePrisonFree";
			DeleteAttribute(npchar, "LifeDay");
			GiveItem2Character(npchar, "unarmed");
			EquipCharacterbyItem(npchar, "unarmed");
			GetCharacterPos(npchar, &locx, &locy, &locz);	
			ChangeCharacterAddressGroup(npchar, npchar.location, "reload", LAi_FindNearestFreeLocator("reload", locx, locy, locz));
			LAi_SetActorType(npchar);
			LAi_group_Register("DeliveQuest_Prison");
			LAi_group_SetRelation("DeliveQuest_Prison", LAI_GROUP_PLAYER, LAI_GROUP_FRIEND);
			//LAi_group_SetAlarmReaction(LAI_GROUP_PLAYER, "DeliveQuest_Prison", LAI_GROUP_ENEMY, LAI_GROUP_FRIEND);
			LAi_group_MoveCharacter(npchar, "DeliveQuest_Prison");
			LAi_ActorFollowEverywhere(npchar, "", -1);
			DialogExit();
		break;

        case "ToPrisonHead_agree":
            dialog.text = "Eh bien, vous pouvez essayer. Espérons que nous nous en sortirons! Mais ne perdez pas de temps - dans quelques jours, je serai parti d'ici...";
			link.l1 = "Attends ici, je vais tout arranger.";
			link.l1.go = "NoMoreTalkExit";
			pchar.questTemp.jailCanMove.City = npchar.City; //город
			pchar.questTemp.jailCanMove.ownerPrison = rand(6); //характер преступления
			SetTimerCondition("GivePrisonFree_Over", 0, 0, 2, false);
			AddQuestRecord("GivePrisonFree", "5");
			AddQuestUserData("GivePrisonFree", "sSex", GetSexPhrase("",""));
            AddQuestUserData("GivePrisonFree", "sCity", XI_ConvertString("Colony"+npchar.city+"Gen"));
            AddQuestUserData("GivePrisonFree", "sName", pchar.questTemp.jailCanMove.Name);
		break;

        case "ToPrisonHead_canMove":
            dialog.text = "Eh bien, que dites-vous, "+GetSexPhrase("camarade","lass")+"?";
			link.l1 = "Tout a été arrangé, et je peux vous emmener d'ici.";
			link.l1.go = "ToPrisonHead_canMove_1";
		break;
        case "ToPrisonHead_canMove_1":
            dialog.text = "Alors sortons d'ici ! Oh, Seigneur, comme je suis heureux !";
			link.l1 = "Résumons. Je veux que tu restes à mes côtés tout le temps jusqu'à ce que nous arrivions à la grotte sur "+XI_ConvertString(pchar.questTemp.jailCanMove.islandId+"Cela")+", vous ne resterez pas plus loin qu'un seul pas. Juste au cas où. Êtes-vous d'accord?";
			link.l1.go = "ToPrisonHead_canMove_2";
		break;
        case "ToPrisonHead_canMove_2":
            dialog.text = "Bien sûr, je suis d'accord! D'autant plus que je ne suis pas en position de choisir.";
			link.l1 = "Alors tu es libre.";
			link.l1.go = "ToPrisonHead_canMove_exit";
		break;
        case "ToPrisonHead_canMove_exit":
			pchar.quest.GivePrisonFree_Over.over = "yes";
			ReOpenQuestHeader("GivePrisonFree");
			AddQuestRecord("GivePrisonFree", "1");
            AddQuestUserData("GivePrisonFree", "sCity", XI_ConvertString("Colony"+npchar.city+"Gen"));
            AddQuestUserData("GivePrisonFree", "sName", pchar.questTemp.jailCanMove.Name);
            AddQuestUserData("GivePrisonFree", "sIsland", XI_ConvertString(pchar.questTemp.jailCanMove.islandId+"Voc"));
			pchar.quest.GivePrisonFree_Death.win_condition.l1 = "NPC_Death";
			pchar.quest.GivePrisonFree_Death.win_condition.l1.character = npchar.id;
			pchar.quest.GivePrisonFree_Death.win_condition = "GivePrisonFree_Death";
			Pchar.quest.GivePrisonFree.win_condition.l1 = "location";
			Pchar.quest.GivePrisonFree.win_condition.l1.location = pchar.questTemp.jailCanMove.placeId;
			Pchar.quest.GivePrisonFree.win_condition = "GivePrisonFree";			
			DeleteAttribute(npchar, "LifeDay");
			GiveItem2Character(npchar, "unarmed");
			EquipCharacterbyItem(npchar, "unarmed");
			GetCharacterPos(npchar, &locx, &locy, &locz);	
			ChangeCharacterAddressGroup(npchar, npchar.location, "reload", LAi_FindNearestFreeLocator("reload", locx, locy, locz));
			LAi_SetActorType(npchar);
			LAi_group_Register("DeliveQuest_Prison");
			LAi_group_SetRelation("DeliveQuest_Prison", LAI_GROUP_PLAYER, LAI_GROUP_FRIEND);
			//LAi_group_SetAlarmReaction(LAI_GROUP_PLAYER, "DeliveQuest_Prison", LAI_GROUP_ENEMY, LAI_GROUP_FRIEND);
			LAi_group_MoveCharacter(npchar, "DeliveQuest_Prison");
			LAi_ActorFollowEverywhere(npchar, "", -1);
			DialogExit();
		break;

        case "ToPrisonHead_notFree":
			switch (pchar.questTemp.jailCanMove.ownerPrison)
			{
				case "0": sTemp = "murder"; break;
				case "1": sTemp = "piracy"; break;
				case "2": sTemp = "brigandry"; break;
				case "3": sTemp = "thievery"; break;
			}
            dialog.text = "Eh bien, qu'en dites-vous, "+GetSexPhrase("camarade","jeune fille")+"?";
			link.l1 = "Je n'ai pas pu organiser votre libération. Vous êtes accusé de "+sTemp+", donc tu ne peux pas être libéré sous caution.";
			link.l1.go = "ToPrisonHead_notFree_1";
			DeleteAttribute(pchar, "questTemp.jailCanMove.ownerPrison");
		break;
		
        case "ToPrisonHead_notFree_1":
            dialog.text = "Mais j'ai été calomnié! Oh diable! Et que vais-je faire maintenant? Je vais pourrir ici vivant!";
			link.l1 = "Je suis désolé, mon pote, mais il n'y a rien que je puisse faire pour toi.";
			link.l1.go = "ToPrisonHead_notFree_2";
			link.l2 = "Il ne reste qu'une seule chance - te libérer par la force. Je vais briser ta serrure maintenant pour te sortir, et nous percerons. Es-tu prêt?";
			link.l2.go = "Prisoner_agree_1";
			pchar.quest.GivePrisonFree_Over.over = "yes";
		break;
		
        case "ToPrisonHead_notFree_2":
            dialog.text = RandPhraseSimple("Maudit sois-tu !","Sacrebleu, tu m'as arnaque, garce...");
			link.l1 = "Et tout le meilleur pour toi aussi. Adieu...";
			link.l1.go = "NoMoreTalkExit";
			AddQuestRecord("GivePrisonFree", "7");
            AddQuestUserData("GivePrisonFree", "sName", pchar.questTemp.jailCanMove.Name);
			DeleteAttribute(pchar, "questTemp.jailCanMove.islandId");	
			DeleteAttribute(pchar, "questTemp.jailCanMove.placeId");
			DeleteAttribute(pchar, "questTemp.jailCanMove.prisonerId");
			DeleteAttribute(pchar, "questTemp.jailCanMove.IsTrue");
			DeleteAttribute(pchar, "questTemp.jailCanMove.Sum");
			DeleteAttribute(pchar, "questTemp.jailCanMove.Name");
		break;

        case "ToPrisonHead_expansive":
			dialog.text = "Alors, de bonnes nouvelles, "+GetSexPhrase("camarade","lass")+"?";
			link.l1 = "La caution pour ta libération est trop haute, je n'ai pas autant d'argent. Je dois arrêter de t'aider.";
			link.l1.go = "ToPrisonHead_notFree_2";
			pchar.quest.GivePrisonFree_Over.over = "yes";
		break;
		//==> в месте, где клад припрятан
        case "PrisonerInPlace":
			switch (sti(pchar.questTemp.jailCanMove.IsTrue))
			{
				case 0:
					dialog.text = "Écoute, j'ai tout vérifié, mais je n'ai trouvé aucun trésor. C'est dommage que cela se soit passé ainsi. Quelqu'un a dû le déterrer avant nous.";
					link.l1 = "Et comment cela peut-il être?!";
					link.l1.go = "PrisonerInPlace_1";
				break;
				case 1:
					dialog.text = "Je l'ai trouvé! Le trésor est toujours où je l'avais laissé.";
					link.l1 = "Excellent. Alors, on se sépare, non ?";
					link.l1.go = "Node_1";
				break;
				case 2:
					dialog.text = "Eh bien, voici, mon cache. Ce n'est pas grand-chose, mais c'est tout ce que j'ai. Comme convenu, la moitié est à toi.";
					link.l1 = "Ouais, le trésor est modeste, en effet. Eh bien, c'est toujours mieux que rien.";
					link.l1.go = "Node_2";
				break;
				case 3:
					dialog.text = "Capitaine, je suis désolé, mais... Il n'y a pas de trésor.";
					link.l1 = "Quoi?! Tu m'as trompé, espèce de vaurien! Je t'ai emmené sur cette île - et pour quoi? Tu ne t'en sortiras pas comme ça!";
					link.l1.go = "Node_3";
				break;
				case 4:
                    ok = GetCharacterItem(pchar, "map_full") == 0 && GetCharacterItem(PChar, "map_part2") == 0;
                    if(GetCharacterItem(PChar, "map_part1") > 0 && !ok) // Первая половинка есть, но вторую дать нельзя
                    {
                        dialog.text = "Écoute, j'ai tout vérifié, mais je n'ai trouvé aucun trésor. C'est dommage que cela se soit passé ainsi. Quelqu'un a dû le déterrer avant nous.";
                        link.l1 = "Et comment cela peut-il être?!";
                        link.l1.go = "PrisonerInPlace_1";
                    }
                    else
                    {
                        dialog.text = "Sacrebleu... Comment cela peut-il être? Cela ne peut pas être!";
                        link.l1 = "Qu'est-ce qui se passe, mon pote? Où est le trésor? Ne me dis pas qu'il n'y en a pas!";
                        link.l1.go = "Node_4";
                    }
				break;
			}
		break;
			
		case "Node_1":
			dialog.text = "Bien sûr, comme convenu. La moitié du trésor est à toi.";
			link.l1 = "Sacre Seigneur, il y a sûrement beaucoup de choses précieuses!";
			link.l1.go = "PrisonerInPlace_3";
			Log_Info("You have received your share of the treasure");
			PlaySound("interface\important_item.wav");
			TakeNItems(pchar, "icollection", 1+hrand(1));
			TakeNItems(pchar, "chest", 4+hrand(4));
			TakeNItems(pchar, "jewelry1", 70+rand(15));
			TakeNItems(pchar, "jewelry2", 50+rand(15));
			TakeNItems(pchar, "jewelry3", 60+rand(15));
			TakeNItems(pchar, "jewelry4", 40+rand(10));
			TakeNItems(pchar, "jewelry5", 10+rand(10));
			TakeNItems(pchar, "jewelry46", 60+rand(20));
			TakeNItems(pchar, "jewelry47", 40+rand(15));
			TakeNItems(pchar, "jewelry40", 60+rand(20));
			AddQuestRecord("GivePrisonFree", "3_1");
			AddQuestUserData("GivePrisonFree", "sName", pchar.questTemp.jailCanMove.Name);
			CloseQuestHeader("GivePrisonFree");
			DeleteAttribute(pchar, "questTemp.jailCanMove.Item1");
			DeleteAttribute(pchar, "questTemp.jailCanMove.Item2");
		break;
			
		case "Node_2":
			dialog.text = "Capitaine, il y a aussi cet objet indien parmi d'autres choses. Vous pouvez l'avoir en plus de votre part.";
			link.l1 = "Eh bien, au moins quelque chose de précieux pour ta libération ! Donne-le moi.";
			link.l1.go = "PrisonerInPlace_3";
			Log_Info("You have received your share of the treasure");
			PlaySound("interface\important_item.wav");
			sTemp = pchar.questTemp.jailCanMove.Item1;
			TakeNItems(pchar, sTemp, 1);
			TakeNItems(pchar, "jewelry5", 40+rand(10));
			TakeNItems(pchar, "jewelry6", 20+rand(20));
			TakeNItems(pchar, "jewelry17", 80+rand(20));
			TakeNItems(pchar, "jewelry13", 10+rand(10));
			TakeNItems(pchar, "jewelry10", 20+rand(20));
			TakeNItems(pchar, "jewelry12", 50+rand(20));
			TakeNItems(pchar, "jewelry11", rand(2)+1);
			AddQuestRecord("GivePrisonFree", "3_2");
			AddQuestUserData("GivePrisonFree", "sName", pchar.questTemp.jailCanMove.Name);
			CloseQuestHeader("GivePrisonFree");
			DeleteAttribute(pchar, "questTemp.jailCanMove.Item1");
			DeleteAttribute(pchar, "questTemp.jailCanMove.Item2");
		break;
			
		case "Node_3":
			dialog.text = "Attendez, Capitaine, ne vous énervez pas, laissez-moi parler. Je suis aussi un marin, tout comme vous. J'ai été jeté en prison par erreur, je vous le jure. Vous étiez ma seule chance de m'échapper, et j'ai dû vous mentir au sujet du trésor.\nIl n'y a pas de trésor, mais j'ai caché une bonne chose là-bas. Prenez-le, et laissez-moi partir en paix. Peut-être, un jour dans une bataille, cela vous aidera à survivre.";
			link.l1 = "D'accord, je n'attendais pas grand-chose de toi de toute façon. Grâce à Dieu que je ne garde pas de rancunes.";
			link.l1.go = "PrisonerInPlace_3";
			Log_Info("You have received equipment");
			PlaySound("interface\important_item.wav");
			sTemp = pchar.questTemp.jailCanMove.Item2;
			TakeNItems(pchar, sTemp, 1);
			AddQuestRecord("GivePrisonFree", "3_3");
			AddQuestUserData("GivePrisonFree", "sName", pchar.questTemp.jailCanMove.Name);
			CloseQuestHeader("GivePrisonFree");
			DeleteAttribute(pchar, "questTemp.jailCanMove.Item1");
			DeleteAttribute(pchar, "questTemp.jailCanMove.Item2");
		break;
			
		case "Node_4":
			dialog.text = "Non!!! Ce n'est pas là! Sacré morceau de papier... Capitaine, j'étais absolument sûr de le trouver ici! Mais, apparemment, je me suis trompé! Quelque chose sur ce bout de papier était vraiment peu clair...";
			link.l1 = "Eh bien... Tu es dans une sacrée panade, mon pote. Mais j'aimerais quand même écouter ton explication.";
			link.l1.go = "Node_4_1";
		break;
			
		case "Node_4_1":
			dialog.text = "J'avais un bout de la carte. C'était une vraie carte, je le jure! Mais c'est très difficile de dire, quelle île était montrée dessus... Je pensais que c'était ici... Mais, comme tu peux le voir maintenant, je me suis trompé.";
			link.l1 = "Quel bout de papier? Donne-le-moi tout de suite!";
			link.l1.go = "Node_4_2";
		break;
			
		case "Node_4_2":
			AddMapPart();
			dialog.text = "Bien sûr, prenez-le. Capitaine, libérez-moi... s'il vous plaît? Je croyais vraiment que le trésor était là. Peut-être, vous comprendrez, où il est, et le prendrez pour vous. Je vous en supplie.";
			link.l1 = "Je vois... En effet, il est difficile de comprendre quoi que ce soit avec ce bout de papier. Il faut une seconde moitié de la carte. Bon, dégage. Je vois maintenant que ce n'était pas de ta faute.";
			link.l1.go = "PrisonerInPlace_4";
		break;
			
		case "PrisonerInPlace_1":
			dialog.text = "Très simple, "+GetSexPhrase("camarade","fillette")+". Tout arrive dans la vie.\nEh bien, tu es ici - si tu veux : reste, cherche plus. Eh bien, je dois y aller !\nAdieu, "+GetSexPhrase("mon ami","jeune fille")+", merci de m'avoir sauvé la vie. Je me souviendrai toujours de toi!";
			link.l1 = "Gredin ! Tu penses que je vais te laisser t'en tirer comme ça ?! Hé ! Attends, lâche !";
			link.l1.go = "PrisonerInPlace_2";
			AddQuestRecord("GivePrisonFree", "4");
			AddQuestUserData("GivePrisonFree", "sName", pchar.questTemp.jailCanMove.Name);
			CloseQuestHeader("GivePrisonFree");
			DeleteAttribute(pchar, "questTemp.jailCanMove.Item1");
			DeleteAttribute(pchar, "questTemp.jailCanMove.Item2");
		break;
			
        case "PrisonerInPlace_2":
			LAi_group_Delete("EnemyFight");
			DeleteAttribute(pchar, "questTemp.jailCanMove.islandId");	
			DeleteAttribute(pchar, "questTemp.jailCanMove.placeId");
			DeleteAttribute(pchar, "questTemp.jailCanMove.prisonerId");
			DeleteAttribute(pchar, "questTemp.jailCanMove.IsTrue");
			DeleteAttribute(pchar, "questTemp.jailCanMove.Sum");
			DeleteAttribute(pchar, "questTemp.jailCanMove.Name");
			chrDisableReloadToLocation = false;
			LAi_LocationDisableMonstersGen(pchar.location, false);
			npchar.lifeDay = 0;
			LAi_group_MoveCharacter(npchar, "EnemyFight");
			LAi_SetActorType(npchar);
            LAi_ActorRunToLocation(NPChar, "reload", "reload1_back", "none", "", "", "", -1);
			DialogExit();

            Pchar.quest.DeletePrisonGroup.win_condition.l1 = "ExitFromLocation";
            Pchar.quest.DeletePrisonGroup.win_condition.l1.location = pchar.location;
            Pchar.quest.DeletePrisonGroup.win_condition = "DeletePrisonGroup";
		break;
		
        case "PrisonerInPlace_3":
			dialog.text = "Voici pour vous. Merci!";
			link.l1 = "Adieu...";
			link.l1.go = "PrisonerInPlace_2";
		break;
		
        case "PrisonerInPlace_4":
			dialog.text = "Merci, capitaine! Je prierai pour vous jusqu'à la fin de mes jours!";
			link.l1 = "Oh, tais-toi! Va en paix...";
			link.l1.go = "PrisonerInPlace_2";
			AddQuestRecord("GivePrisonFree", "3_4");
            AddQuestUserData("GivePrisonFree", "sName", pchar.questTemp.jailCanMove.Name);
			AddQuestUserData("GivePrisonFree", "sSex", GetSexPhrase("",""));
			CloseQuestHeader("GivePrisonFree");
			DeleteAttribute(pchar, "questTemp.jailCanMove.Item1");
			DeleteAttribute(pchar, "questTemp.jailCanMove.Item2");
		break;
        
		// -------------------- освобождение заключённого --------------------
		// ------------------------ передать маляву --------------------------
        case "Deliver_1":
			dialog.text = "Je suis appelé "+GetFullName(npchar)+". J'ai une demande à vous faire, he-he...";
			link.l1 = "Quoi de neuf ?";
			link.l1.go = "Deliver_2";
		break;
        case "Deliver_2":
			dialog.text = "J'ai besoin qu'un message soit envoyé hors de prison. Le ferez-vous ?";
			link.l1 = "Et qu'est-ce que j'y gagne?";
			link.l1.go = "Deliver_3";
		break;
        case "Deliver_3":
			dialog.text = "Les copains ne te décevront pas, promis... Alors? Tu es dedans?";
			link.l1 = "Non, je ne suis pas intéressé.";
			link.l1.go = "Prisoner_5";
			link.l2 = "Eh bien, si cela ne nécessite pas trop d'effort de ma part, je peux le faire.";
			link.l2.go = "Deliver_agree";
		break;
        case "Deliver_agree":
			dialog.text = "D'accord. Maintenant, écoute-moi attentivement. Deux compagnons attendent ma missive dans une maison, pour qu'ils ne soient pas pris pendant une descente. Mais je n'ai aucune idée de quelle maison il s'agit exactement. Tu devras chercher.";
			link.l1 = "Que voulez-vous dire - chercher?";
			link.l1.go = "Deliver_4";
		break;
        case "Deliver_4":
			dialog.text = "Cherchez comme dans chercher. Vous courrez dans la ville, regarderez dans les maisons. Quand vous arriverez au bon endroit, ils ne vous laisseront pas partir sans parler. Mais gardez à l'esprit que je resterais là au plus deux jours de plus. Alors ne tardez pas.";
			link.l1 = "Je vois. Eh bien, donnez votre missive, alors.";
			link.l1.go = "Deliver_5";
		break;
        case "Deliver_5":
			pchar.questTemp.jailCanMove.Deliver.locationId = GetBanderLocation(npchar); //Id коммона
			if (pchar.questTemp.jailCanMove.Deliver.locationId == "none")
			{
				dialog.text = "Hmm, tu sais, je ne t'aime tout simplement pas. J'ai changé d'avis. Allez, ne reste pas là !";
				link.l1 = "Regardez-vous! Eh bien, comme vous le souhaitez...";
				link.l1.go = "NoMoreTalkExit";
				DeleteAttribute(pchar, "questTemp.jailCanMove.Deliver");
			}
			else
			{
				dialog.text = "Ici. Merci, "+GetSexPhrase("camarade","demoiselle")+"!";
				link.l1 = "Pas du tout.";
				link.l1.go = "NoMoreTalkExit";
				GiveItem2Character(Pchar, "Malyava");
				pchar.questTemp.jailCanMove.Deliver.Id = npchar.id; //Id зэка
				pchar.questTemp.jailCanMove.Deliver.name = GetFullName(npchar); //имя зэка
				pchar.questTemp.jailCanMove.Deliver.City = npchar.city; //город (Id колонии)
				pchar.questTemp.jailCanMove.Deliver.good = rand(3); //опрокинут или нет
				pchar.questTemp.jailCanMove.Deliver.price = rand(6)*500+500; //цена услуги
				pchar.quest.DeliverToBander.win_condition.l1 = "location";
				pchar.quest.DeliverToBander.win_condition.l1.location = pchar.questTemp.jailCanMove.Deliver.locationId;
				pchar.quest.DeliverToBander.win_condition = "DeliverToBander";
				pchar.quest.DeliverToBander.again = true; 
				SetTimerCondition("DeliverToBander_over", 0, 0, 2, false);
				ReOpenQuestHeader("GivePrisonFree");
				AddQuestRecord("GivePrisonFree", "8");
				AddQuestUserData("GivePrisonFree", "sSex", GetSexPhrase("",""));
				AddQuestUserData("GivePrisonFree", "sCity", XI_ConvertString("Colony"+npchar.city+"Gen"));
				AddQuestUserData("GivePrisonFree", "sName", pchar.questTemp.jailCanMove.Deliver.name);
			}
		break;
		
		// Warship, 16.05.11. Генер "Justice for sale".
		case "JusticeOnSale_1":
			dialog.text = "Oui, il a été arrêté pour contrebande. Mais pourquoi vous souciez-vous de ce gibier de potence, "+GetAddress_Form(NPChar)+"?";
			link.l1 = "Sa bande prévoit d'organiser son évasion et de continuer leurs méfaits sales.";
			link.l1.go = "JusticeOnSale_2";
			link.l2 = "J'ai entendu dire qu'il était innocent.";
			link.l2.go = "JusticeOnSale_3";
			
			DeleteAttribute(PChar, "GenQuest.JusticeOnSale.PrisonWait");
		break;
		
		case "JusticeOnSale_2":
			dialog.text = "Vous devez notifier le gouverneur, "+GetAddress_Form(NPChar)+", ces canailles doivent toutes être attrapées!";
			link.l1 = "Je ferai exactement cela.";
			link.l1.go = "exit";
			NextDiag.TempNode = "First_officer";
		break;
		
		case "JusticeOnSale_3":
			dialog.text = "Écoute, "+GetFullName(PChar)+", ce gars a été arrêté en train d'essayer de vendre des marchandises interdites, en plein dans la ville! Comment pouvez-vous prétendre qu'il n'est pas coupable?";
			link.l1 = "J'ai entendu dire que l'accusation était infondée et que vous n'avez aucune preuve, n'est-ce pas vrai? Vous ne pouvez pas simplement détenir un homme qui a été lésé.";
			link.l1.go = "JusticeOnSale_4";
		break;
		
		case "JusticeOnSale_4":
			dialog.text = "Nous n'avons ni témoins ni marchandises, mais cela ne change rien, capitaine "+GetFullName(PChar)+"! Cette personne est certainement coupable - et peut-être pas seulement de commerce illégal. De toute façon - pourquoi vous soucieriez-vous du prisonnier?";
			link.l1 = "Peut-être, ma parole peut-elle être la caution pour ce prisonnier malheureux?";
			link.l1.go = "JusticeOnSale_5_WithoutMoney";
			
			if(sti(PChar.money) >= 5000)
			{
				link.l2 = "Peut-être, ces 5000 pesos peuvent-ils être la caution pour ce prisonnier malheureux?";
				link.l2.go = "JusticeOnSale_5";
			}
		break;
		
		case "JusticeOnSale_5_WithoutMoney":
			if(GetCharacterSkill(PChar, SKILL_LEADERSHIP) > hrand(100) || sti(PChar.money) < 5000)
			{
				dialog.text = "D'accord, "+GetAddress_Form(NPChar)+", emmène ce vaurien et pars, avant que je ne change d'avis.";
				link.l1 = "C'est formidable de voir le triomphe de la justice, ne pensez-vous pas?";
				link.l1.go = "JusticeOnSale_6";
			}
			else
			{
				dialog.text = "Non, "+GetAddress_Form(NPChar)+", cela ne conviendra pas.";
				link.l1 = "Alors, peut-être, ces 5000 pesos peuvent être l'argument le plus convaincant ?";
				link.l1.go = "JusticeOnSale_5";
			}
		break;
		
		case "JusticeOnSale_5":
			dialog.text = "D'accord, "+GetAddress_Form(NPChar)+", prenez ce vaurien et partez, avant que je ne change d'avis.";
			link.l1 = "C'est merveilleux de voir le triomphe de la justice, ne pensez-vous pas?";
			link.l1.go = "JusticeOnSale_6";
			AddMoneyToCharacter(PChar, -5000);
			PChar.GenQuest.JusticeOnSale.PrisonMoney = true;
		break;
		
		case "JusticeOnSale_6":
			DialogExit();
			sld = GetCharacter(NPC_GenerateCharacter("JusticeOnSale_Smuggler", "mercen_"+(rand(9)+1), "man", "man", sti(PChar.rank)+5, PIRATE, -1, true, "marginal"));
			SetFantomParamFromRank(sld, sti(PChar.rank)+5, true);
			sld.name = PChar.GenQuest.JusticeOnSale.SmugglerName;
			sld.lastName = "";
			sld.dialog.filename = "GenQuests_Dialog.c";
			sld.dialog.currentnode = "First time";
			sld.greeting = "Enc_Raiders"; 
			AddPassenger(PChar, sld, false);
			SetCharacterRemovable(sld, false);
			PChar.GenQuest.JusticeOnSale.SmugglerModel = sld.model;
			DeleteAttribute(PChar, "GenQuest.JusticeOnSale.MayorWait");
			sld = &Locations[FindLocation(PChar.GenQuest.JusticeOnSale.ShoreId)];
			sld.DisableEncounters = true;
			PChar.Quest.JusticeOnSale_ShoreEnterWithSmuggler.win_condition.l1  = "location";
			PChar.Quest.JusticeOnSale_ShoreEnterWithSmuggler.win_condition.l1.location = PChar.GenQuest.JusticeOnSale.ShoreId;
			PChar.Quest.JusticeOnSale_ShoreEnterWithSmuggler.function = "JusticeOnSale_ShoreEnterWithSmuggler";
			Log_Info("Smuggler's captain on a board");
			PlaySound("interface\notebook.wav");
			LAi_Fade("", "");
			WaitDate("",0,0,0,0,60); // 280313 // лесник. прокрутка времени было так WaitDate("",0,0,0,2,5);
		break;
		// --> belamour ночной приключенец
		case "NightAdventure_CitizenHomie":
			dialog.text = "Oui, il y avait un tel violent. Il a été grossier envers une sentinelle, puis il s'est battu. Rien de plus: il restera derrière les barreaux pendant plusieurs jours - il se dégrisera. Pourquoi vous souciez-vous de lui? Vous semblez être un capitaine, et ce poivrot ne ressemble pas à un marin.";
			link.l1 = "Oui, c'est vrai, je suis un capitaine. Le fait est que ce ivrogne est un vieil ami à moi. Ne parlez à personne de cela, s'il vous plaît. Si j'ai bien compris, il n'a même pas pris d'arme. Peut-être le relâcheriez-vous cette fois à ma demande?";
			link.l1.go = "NightAdventure_CitizenHomie_1";
		break;
		
		case "NightAdventure_CitizenHomie_1":
			if(pchar.GenQuest.NightAdventureVar == "NightAdventure_CitizenHomie") // отпустил под честное слово
			{
				dialog.text = "Ouais, bon ami à moi. Ne t'inquiète pas, je ne dirai à personne. En fait, il ne pouvait même pas frapper correctement, c'était juste une tentative - c'est pourquoi ils l'ont mis en prison. Puisque tu demandes, par respect pour toi, je vais le libérer. Dis-lui simplement de se contrôler la prochaine fois. Ou mieux encore, fais-le boire moins.";
				link.l1 = "Merci, officier.";
				link.l1.go = "NightAdventure_CitizenHomieOK";
			}
			
			if(pchar.GenQuest.NightAdventureVar == "NightAdventure_CitizenHomieSolderNM" || pchar.GenQuest.NightAdventureVar == "NightAdventure_CitizenHomieSolderGM") // поговорить с солдатом
			{
				dialog.text = "Ouais, bon ami. Ne t'inquiète pas, je ne dirai à personne. Seulement, il a réussi à frapper le sentinelle au visage avant qu'ils ne le ligotent. Alors je ne peux pas le libérer. À moins bien sûr, que le sentinelle accepte de retirer ses plaintes. Tu peux lui parler toi-même, il est en patrouille autour de la ville aujourd'hui.";
				link.l1 = "Non, j'ai peur que s'il a frappé le garde, alors je ne peux pas l'aider. Il va devoir s'asseoir pendant quelques jours. Je suis désolé de vous déranger, officier.";
				link.l1.go = "CitizenHomieEnd";
				link.l2 = "D'accord, je vais essayer de négocier avec le sentinelle.";
				link.l2.go = "NightAdventure_CitizenHomieSolder";
			}
			
			if(pchar.GenQuest.NightAdventureVar == "NightAdventure_CitizenHomieOfficer") // выплата офицеру
			{
				dialog.text = "Oui, bon ami. Ne t'inquiète pas, je ne dirai à personne. Le fait est que, attaquer un membre des forces armées en service est un crime. Je peux te rencontrer à mi-chemin et le libérer, mais seulement sous caution.";
				link.l1 = "Et combien dois-je payer pour cela?";
				link.l1.go = "NightAdventure_CitizenHomieOfficer";
			}
		break;
		
		case "NightAdventure_CitizenHomieOK":
			DialogExit();
			DeleteAttribute(pchar,"GenQuest.NightAdventureToJail");
			SetFunctionLocationCondition("NightAdventure_CitizenHomieOK", npchar.City+"_town", false);
		break;
		
		case "NightAdventure_CitizenHomieEnd":
			DialogExit();
			DeleteAttribute(pchar,"GenQuest.NightAdventureToJail");
			pchar.quest.NightAdventure_SeaExit.over = "yes";
			pchar.quest.NightAdventure_JungleExit.over = "yes";
			SetFunctionExitFromLocationCondition("NightAdventure_KillPhant", pchar.location, false);
		break;
		
		case "NightAdventure_CitizenHomieSolder":
			DialogExit();
			DeleteAttribute(pchar,"GenQuest.NightAdventureToJail");
			for(i=0; i<MAX_CHARACTERS; i++)
			{
				if(Characters[i].location != npchar.City+"_town") continue;
				if(Characters[i].chr_ai.type != "patrol") continue;
				while(SoldQty < 10) // на всякий случай, чтобы не было выхода за границы массива
				{                   // генерируется 7 солдат + 3 мушкетера
					SoldNum[SoldQty] = Characters[i].index;
					SoldQty++;
				}
			}
			iTemp = rand(SoldQty);
			pchar.GenQuest.NightAdventureSolNum = SoldNum[iTemp];
		break;
		
		case "NightAdventure_HomieToPrisoner":
			DeleteAttribute(pchar,"GenQuest.NightAdventureToPrisoner");
			pchar.quest.NightAdventure_SeaExit.over = "yes";
			pchar.quest.NightAdventure_JungleExit.over = "yes";
			SetFunctionLocationCondition("NightAdventure_CitizenHomieOK", npchar.City+"_town", false);
			dialog.text = "*lit* Alors... alors... Eh bien, puisque le guet n'a pas de plaintes, moi non plus. Vous pouvez prendre votre ami. Dites-lui juste de se contrôler la prochaine fois. Mieux encore, faites-le boire moins.";
			link.l1 = "Merci, officier.";
			link.l1.go = "exit";
		break;
		
		case "NightAdventure_CitizenHomieOfficer":
			dialog.text = "Eh bien, étant donné qu'il n'a pas pris d'arme, ce n'est que 1500 pesos.";
			link.l1 = "J'ai peur de ne pas être prêt à donner autant. Eh bien, considérant qu'il n'est ici que pour quelques jours, je suppose que ça ne lui fera pas de mal. Peut-être qu'il boira moins.";
			link.l1.go = "NightAdventure_CitizenHomieEnd";
			if(sti(pchar.money) >= 1500)
			{
				link.l2 = "D'accord, je suis prêt à payer la caution.";
				link.l2.go = "NightAdventure_CitizenHomieOfficer_1";
			}
		break;
		
		case "NightAdventure_CitizenHomieOfficer_1":
			AddMoneyToCharacter(pchar, -1500);
			DeleteAttribute(pchar,"GenQuest.NightAdventureToJail");
			pchar.quest.NightAdventure_SeaExit.over = "yes";
			pchar.quest.NightAdventure_JungleExit.over = "yes";
			SetFunctionLocationCondition("NightAdventure_CitizenHomieOK", npchar.City+"_town", false);
			dialog.text = "Vous pouvez récupérer votre ami. Dites-lui juste de se contrôler la prochaine fois. Ou encore mieux, faites-lui boire moins.";
			link.l1 = "Merci officier.";
			link.l1.go = "exit";
		break;
		// <-- ночной приключенец
		
		// --> Sinistra Путеводная звезда
		case "PZ_BasTer_ComendantDialog":
			if (CheckAttribute(pchar, "questTemp.PZ_BasTerOpozdal"))
			{
				dialog.text = "Merci d'avoir accepté de venir plutôt que de commencer un massacre. Au moins quelqu'un est raisonnable ces jours-ci.";
				link.l1 = "Alors, à quoi dois-je cette attention, Monsieur l'Officier? Cela a-t-il quelque chose à voir avec le fait que je cherche un homme chinois?";
				link.l1.go = "PZ_BasTer_ComendantDialog_Opozdal_1";
			}
			else
			{
				dialog.text = "C'est une bonne chose que vous soyez venu à nous de votre plein gré. Nous en avons assez des voyous dernièrement.";
				link.l1 = "Eh bien, comme vous pouvez le voir, je ne suis pas l'un des violents. Cependant... pourquoi suis-je ici, officier? J'ai déjà demandé à vos hommes, mais je n'ai pas obtenu de réponse - est-ce parce que je cherche un certain Chinois en ville?";
				link.l1.go = "PZ_BasTer_ComendantDialog_1";
			}
			DeleteQuestCondition("PZ_BasTerPeshera");
			npchar.Dialog.Filename = "Common_Prison.c";
			npchar.Dialog.CurrentNode = "First_officer";
		break;
		// <-- Путеводная звезда
		case "Helen_meeting":
			dialog.text = "Pourquoi, bien sûr que non! S'il vous plaît, entrez. Vous êtes toujours le bienvenu dans nos cachots. Euh, je veux dire ça d'une bonne manière, bien sûr. Alors, de quoi avez-vous besoin ici?";
			link.l1 = "Oh, rien de spécial, tu sais, juste à flâner dans la ville, alors je suis venu ici par hasard.";
			link.l1.go = "exit";
			link.l2 = "Je voulais parler de certaines affaires.";
			link.l2.go = "quests";
			if (!sti(pchar.questTemp.jailCanMove))
			{
				link.l4 = "Je veux entrer dans la prison.";
				link.l4.go = "ForGoodMove";		
			}
			NextDiag.TempNode = "First_officer";
		break;
	}
}

void GetChestPlaceName()
{
	string islandId;
	int iTemp = rand(3);
	switch (iTemp)
	{
		case 0: 
			pchar.questTemp.jailCanMove.islandId = "Bermudes";
			pchar.questTemp.jailCanMove.placeId = "Bermudes_Cavern";
		break;
		case 1: 
			pchar.questTemp.jailCanMove.islandId = "Caiman";
			pchar.questTemp.jailCanMove.placeId = "Caiman_Grot";
		break;
		case 2: 
			pchar.questTemp.jailCanMove.islandId = "Dominica";
			pchar.questTemp.jailCanMove.placeId = "Dominica_Grot";
		break;
		case 3: 
			pchar.questTemp.jailCanMove.islandId = "Terks";
			pchar.questTemp.jailCanMove.placeId = "Terks_Grot";
		break;
	}
}

string GetBanderLocation(ref npchar)
{
    aref	arCommon, arRld, arRld2;
    int	i, n, Qty, Qty2;
	string LocId; 
	string	storeArray [50];
	int howStore = 0;
    makearef(arRld, Locations[FindLocation(npchar.city + "_town")].reload);
	Qty = GetAttributesNum(arRld);
    if (CheckAttribute(pchar, "GenQuest.SeekSpy.Location")) //если взят квест мэра по поиску шпиона
	{
		for (i=0; i<Qty; i++)
		{
    		arCommon = GetAttributeN(arRld, i);
			LocId = arCommon.go;
    		if (findsubstr(LocId, "Common" , 0) != -1 && LocId != pchar.GenQuest.SeekSpy.Location)
    		{			
				storeArray[howStore] = LocId;
				howStore++; 
			}
			if (arCommon.label != "Sea")
			{	
				makearef(arRld2, Locations[FindLocation(LocId)].reload);
				Qty2 = GetAttributesNum(arRld2);
				for (n=0; n<Qty2; n++)
				{
    				arCommon = GetAttributeN(arRld2, n);
					LocId = arCommon.go;
					if (findsubstr(LocId, "Common" , 0) != -1 && LocId != pchar.GenQuest.SeekSpy.Location && arCommon.name != "reload1") // mitrokosta fix
    				{
						storeArray[howStore] = LocId;
						howStore++; 					
					}
				}
			}	
		}
	}
	else
	{
		for (i=0; i<Qty; i++)
		{
    		arCommon = GetAttributeN(arRld, i);
			LocId = arCommon.go;
    		if (findsubstr(LocId, "Common" , 0) != -1)
    		{			
				storeArray[howStore] = LocId;
				howStore++; 
			}
			if (arCommon.label != "Sea")
			{	
				makearef(arRld2, Locations[FindLocation(LocId)].reload);
				Qty2 = GetAttributesNum(arRld2);
				for (n=0; n<Qty2; n++)
				{
    				arCommon = GetAttributeN(arRld2, n);
					LocId = arCommon.go;
					if (findsubstr(LocId, "Common" , 0) != -1 && arCommon.name != "reload1") // mitrokosta fix
    				{
						storeArray[howStore] = LocId;
						howStore++; 
					}
				}
			}	
		}
	}
	if (howStore == 0) return "none";
	LocId = storeArray[rand(howStore-1)];
	SetOpenDoorCommonLoc(npchar.city, LocId); //открываем дверь
	for(n=0; n<MAX_CHARACTERS; n++)
	{
		if (CheckAttribute(&characters[n], "locations") && characters[n].locations == LocId) 
		{			
			characters[n].lifeDay = 0;
		}
	}
	return LocId;
}

string GenQuestPrison_GenerateArtefact() // артефакты
{
	string itemID;
	switch(rand(7))
	{
		case 0:
			itemID = "indian_5";
		break;
		case 1:
			itemID = "indian_7"; 
		break;
		case 2:
			itemID = "indian_8"; 
		break;
		case 3:
			itemID = "indian_9"; 
		break;
		case 4:
			itemID = "indian_10"; 
		break;
		case 5:
			itemID = "indian_11"; 
		break;
		case 6:
			itemID = "indian_3"; 
		break;
		case 7:
			itemID = "indian_6"; 
		break;
	}
	return itemID;
}

string GenQuestPrison_GenerateBlade() // клинки и другое
{
	string itemID;
	switch(rand(8))
	{
		case 0:
			itemID = GetGeneratedItem("blade_16");
		break;
		case 1:
			itemID = GetGeneratedItem("blade_15"); 
		break;
		case 2:
			itemID = GetGeneratedItem("blade_13"); 
		break;
		case 3:
			itemID = "cirass2"; 
		break;
		case 4:
			itemID = GetGeneratedItem("blade_10"); 
		break;
		case 5:
			itemID = "spyglass3"; 
		break;
		case 6:
			itemID = "cirass6"; 
		break;
		case 7:
			itemID = "cirass7"; 
		break;
		case 8:
			itemID = "cirass1"; 
		break;	
		
	}
	return itemID;
}
