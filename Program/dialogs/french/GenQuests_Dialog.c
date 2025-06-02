void ProcessDialogEvent()
{
	ref NPChar;
	aref Link, NextDiag;
	
	DeleteAttribute(&Dialog,"Links");
	
	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	ref rItem, rChar, sld, MerPrm;
	aref arTemp1, arTemp2;
	bool bTemp;
	int iBanditsCount, i, iMoney, iNation, iTmp, iGoods, iRank, iScl;
	String sTitle, sGroup, sTemp, sText; // belamour 
	float locx, locy, locz;
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			dialog.text = "C'est un bug. Contactez les développeurs et faites-leur savoir comment et où vous l'avez trouvé";
					link.l1 = RandSwear()+"Je leur ferai savoir !";
					link.l1.go = "exit";
					
			if(HasSubStr(NPChar.id, "ContraMeetManQuest_Soldier_")) // Солдеры по квесту "встреча в бухте"
			{
				dialog.text = "Je ne suis pas autorisé à traiter avec vous. Parlez à notre officier.";
					link.l1 = LinkRandPhrase("Bien sûr...","Je vois.","Certainement !");
					link.l1.go = "exit";
				break;
			}
			
			if(HasSubStr(NPChar.id, "ContraMeetManQuest_Officer_")) // Офицер по квесту "встреча в бухте"
			{
				dialog.text = "Présente-toi ! Je veux savoir à qui j'ai affaire !";
					link.l1 = "Mon nom est "+GetFullName(PChar)+"Qu'est-ce qu'il se passe ici ?";
					link.l1.go = "ContraMeetManQuest_Sold_1";
				break;
			}
					
			if(NPChar.id == "ContraMeetManQuest_QuestMan" && PChar.location == PChar.GenQuest.ContraMeetMan.ShoreID) // Квестовый чел по генеру "meeting in the cove" 
			{
				dialog.text = "Capitaine, ton nom est "+GetFullName(PChar)+"N'est-ce pas ?";
					link.l1 = "Oui, tu as raison.";
					link.l1.go = "ContraMeetManQuest_1";
					link.l2 = "Non. Vous m'avez pris pour quelqu'un d'autre.";
					link.l2.go = "exit";
					break;
			}
			
			if(NPChar.id == "ContraMeetManQuest_QuestMan" && CheckAttribute(PChar, "GenQuest.ContraMeetMan.ContraIsDead")) // В комнате таверны после убицства контриков
			{
				LAi_LocationFightDisable(LoadedLocation, false);
				dialog.text = PChar.name+", merci beaucoup ! Si ce n'était pas vous, mon sort serait bien peu enviable... Comment puis-je vous remercier ?";
					link.l1 = "Je n'ai besoin de rien...";
					link.l1.go = "ContraMeetManQuest_7";
					link.l2 = "Je ne refuserais pas une petite récompense.";
					link.l2.go = "ContraMeetManQuest_8";
					break;
			}
			
			if(NPChar.id == "ContraMeetManQuest_Contrick_0") // Контрик в комнате по квесту "встреча в бухте"
			{
				iMoney = (rand(3)+2)*500;
				PChar.GenQuest.ContraMeetMan.Money = iMoney;
				if(!CheckAttribute(PChar, "GenQuest.ContraMeetMan.ManIsTraitor")) // Просто платят деньги
				{
					dialog.text = "...Hmm, c'est bien lui... Merci, "+GetSexPhrase("compagnon","fillette")+", sans ton aide nous aurions eu du mal, il n'y a aucun moyen pour nous de quitter la ville. Tiens, prends "+FindRussianMoneyString(iMoney)+" et vous pouvez vous perdre. Et nous allons avoir une 'discussion' avec notre ami...";
						link.l1 = "...";
						link.l1.go = "ContraMeetManQuest_3";
				}
				else
				{
					dialog.text = "...Hmm, c'est bien lui... Merci, "+GetSexPhrase("compagnon","lass")+", sans ton aide nous aurions eu du mal, il n'y a aucun moyen pour nous de sortir de la ville. Tiens, prends "+FindRussianMoneyString(iMoney)+" et tu peux te perdre. Nous allons éventrer ce sale traître maintenant !";
						link.l1 = "Bien sûr. Jusqu'à notre prochaine rencontre, messieurs...";
						link.l1.go = "ContraMeetManQuest_4";
						link.l2 = "Quoi ?! Non, je ne te laisserai pas assassiner un homme, peu importe qui il est... Et je n'ai pas besoin de ton fichu argent !";
						link.l2.go = "ContraMeetManQuest_5";
				}
					break;
			}
			
			if(NPChar.id == "ContraDeliverQuest_Soldier_0") // Солдер в комнате
			{
				dialog.text = "Alors... Qu'avons-nous ici ? Des pirates ?! Vous devrez nous accompagner au bureau du commandant pour une enquête...";
					link.l1 = "Nous ne sommes pas du tout des pirates ! Je ne connais même pas cet homme ! Il vient juste de louer et d'emménager dans cette chambre, et je n'ai pas eu le temps de faire mes bagages et de partir !";
					link.l1.go = "ContraDeliverQuest_Sold1";
					break;
			}
				
			if(CheckAttribute(PChar, "GenQuest.ContraDeliver.WaitOnRoom") && NPChar.id == "ContraDeliverQuest_Contra_1")
			{
				dialog.text = "Alors, que disiez-vous ? Vous avez un message pour moi ?! J'attends !";
					link.l1 = "Voilà...";
					link.l1.go = "ContraDeliverQuest_1";
					DeleteAttribute(PChar, "GenQuest.ContraDeliver.WaitOnRoom");
					DeleteAttribute(PChar, "GenQuest.ContraDeliver.GoToTavern");
					break;
			}
			
			if(CheckAttribute(PChar, "GenQuest.ChurchQuest_2.BanditsInShore") && NPChar.id == "Church_GenQuest2_Bandit_0")
			{
				dialog.text = "Hé, toi ! Oui, toi. Je vois que tu es un homme décent et fortuné.";
					link.l1 = "Je ne peux pas en dire autant de toi.";
					link.l1.go = "Church_GenQuest_2_ShoreBandit_1";
					break;
			}
					
			if(CheckAttribute(PChar, "GenQuest.ChurchQuest_2.WayOfShortVariant") && NPChar.id == "Church_GenQuest2_Bandit_0")
			{
				dialog.text = "Attends! Hé, "+GetSexPhrase("matelot","fillette")+", montre-nous juste à quel point ta bourse est lourde !";
					link.l1 = "Alors, as-tu déjà gaspillé tout l'argent de l'église ?";
					link.l1.go = "Church_GenQuest_2_1";
					break;
			}
			
			if(NPChar.id == "ReasonToFast_Hunter")
			{
				if(GetSummonSkillFromName(pchar, SKILL_LEADERSHIP) > sti(pchar.questTemp.ReasonToFast.p2))
				{
					dialog.text = "Hé, sur un bateau ! Hic... Dégagez le chenal - je dois parler aux gars...";
					link.l1 = "N'es-tu pas un peu étourdi, l'ami? Va dormir ça.";
					link.l1.go = "ReasonToFast_Hunter1";
				}
				else
				{
					dialog.text = "Hé, cap ! Jette l'ancre !";
					link.l1 = "Et pourquoi diable devrais-je...";
					link.l1.go = "ReasonToFast_Hunter2";
				}
				link.l2 = "N'êtes-vous pas un peu trop grossier !?";
				link.l2.go = "ReasonToFast_Hunter3";	
			}
			
			if(NPChar.id == "PirateOnUninhabited_0")
			{
				dialog.text = RandPhraseSimple("Salut à vous ! Enfin, le Seigneur a exaucé nos prières et a envoyé un capitaine vaillant sur cette rive abandonnée !","Merci la Providence ! Maintenant, les charognards locaux ne se repaîtront pas de nos os pourris !");
				link.l1 = "Bonjour, bonhomme, je suis capitaine "+GetFullName(PChar)+"Je vois que vous êtes dans un sacré pétrin ici.";
				link.l1.go = "PiratesOnUninhabited_3";
				link.l2 = "Bon homme, j'ai mes propres affaires à régler et je n'ai pas le temps de m'occuper de tes soucis.";
				link.l2.go = "PiratesOnUninhabited_1";
			}
			
			if(NPChar.id == "ShipWreck_0")
			{
				dialog.text = RandPhraseSimple("Oh, capitaine ! C'est une sacrée chance que Dieu vous ait envoyé un vent favorable et vous ait mené à cet endroit désert !","Capitaine ! Remercie la Providence que tu aies décidé de jeter l'ancre sur cette rive déserte !");
				link.l1 = "Bonjour, bonhomme, je suis capitaine "+GetFullName(pchar)+"Je vois que tu es dans un sacré pétrin ici.";	
				link.l1.go = "ShipWreck_2";
				link.l2 = "Homme de bien, j'ai mes propres affaires à régler et je n'ai pas de temps à perdre avec tes ennuis.";
				link.l2.go = "ShipWreck_1";
			}
			
			if(NPChar.id == "Convict_0")
			{
				dialog.text = LinkRandPhrase("Attends, "+GetAddress_Form(pchar)+"! Pourriez-vous nous accorder une minute de votre précieux temps ?","Serait-ce une erreur noble"+GetSexPhrase("ter","s")+" écoutez une humble requête de ces hommes indignes?","Noble echec"+GetSexPhrase("ter","s")+", je vous prie, accordez un peu de votre précieux temps pour parler avec le malheureux.");
				link.l1 = LinkRandPhrase("Je n'ai pas le temps pour ça.","Va-t'en, j'ai bien des affaires sans toi.","Laisse-moi tranquille, je n'ai pas de temps pour toi.");
				link.l1.go = "Convict_0End";
				link.l2 = LinkRandPhrase("Que veux-tu?","Que vous faut-il ?","Quel est le problème ?");
				link.l2.go = "Convict_Begin";
			}
			
			// Warship, 15.05.11. Генер "Justice for sale".
			if(HasSubStr(NPChar.id, "JusticeOnSale_Jungle_"))
			{
				dialog.text = "Salut, capitaine ! Es-tu intéressé par des babioles indiennes et des marchandises qu'on ne trouve pas dans les magasins ordinaires ? Ou peut-être par du cash ?";
					link.l1 = "Des va-nu-pieds comme toi exigent d'habitude - ils n'offrent rien. Pourquoi es-tu si étrangement courtois ?";
					link.l1.go = "JusticeOnSale_1";
					link.l2 = "Mon pistolet parle d'habitude aux salauds comme toi !";
					link.l2.go = "JusticeOnSale_2";
			}
		break;
		
		// Генератор "Situation in the hold - Ransom"
		case "Hold_GenQuest1":
			pchar.quest.Hold_GenQuest_FindCharTimeIsOver.over = "yes";
			dialog.text = "Je vous écoute, capitaine. Êtes-vous ici pour affaires ?";
			link.l1 = "Je cherche monsieur "+pchar.GenQuest.Hold_GenQuest.Name+"?";
			link.l1.go = "Hold_GenQuest2";
		break;
		
		case "Hold_GenQuest2":
			dialog.text = RandPhraseSimple("Je suis monsieur "+pchar.GenQuest.Hold_GenQuest.Name+"À qui dois-je l'honneur ?","Vous l'avez trouvé. Que puis-je faire pour vous ?");
			link.l1 = "Je suis capitaine "+GetFullName(pchar)+", je voulais te parler à propos de "+pchar.GenQuest.Hold_GenQuest.CapName+".";
			link.l1.go = "Hold_GenQuest3";
		break;
		
		case "Hold_GenQuest3":
			sld = characterFromId(pchar.GenQuest.Hold_GenQuest.CapId);
			pchar.GenQuest.Hold_GenQuest.RansomSum = makeint(3 * sti(sld.rank) * (800 + GetCharacterSPECIALSimple(NPChar, SPECIAL_L) * 100) + GetCharacterSkillToOld(sld, "Leadership")*500 + GetCharacterSkillToOld(pchar, "commerce")*500); 
						
			switch(hrand(3))
			{
				case 0:
					dialog.text = "Et qui est-ce?";
					link.l1 = "Attends... Tu es "+pchar.GenQuest.Hold_GenQuest.Name+", et tu ne sais rien de "+pchar.GenQuest.Hold_GenQuest.CapName+"?";
					link.l1.go = "Hold_GenQuest40";
				break;
				case 1:
					dialog.text = "Ouah ! Cela fait un bon moment que je n'ai pas entendu parler de ce vieux renard. Qu'est-il arrivé à lui cette fois ?";
					link.l1 = "Cette fois, il est dans un sacré pétrin... Il est retenu captif, et il a besoin de ton aide.";
					link.l1.go = "Hold_GenQuest50";
				break;
				case 2:
					dialog.text = "Très bien, je suis tout ouïe.";
					link.l1 = "Son navire a été attaqué par les pirates, et il est maintenant retenu captif. Il m’a conseillé de vous voir au sujet de la rançon.";
					link.l1.go = "Hold_GenQuest60";
				break;
				case 3:
					dialog.text = "Oui, je suis heureux d'entendre parler d'un vieil ami. Comment va-t-il?";
					link.l1 = "Sa situation est si désespérée qu'il est difficile même de l'imaginer.";
					link.l1.go = "Hold_GenQuest70";
				break;				
			}	
		break;
		
		case "Hold_GenQuest40":
			// dialog.text = "En effet, je suis "+pchar.GenQuest.Hold_GenQuest.Name+"! Mais pourquoi devrais-je savoir quoi que ce soit à ce sujet "+pchar.GenQuest.Hold_GenQuest.CapName+"?! ";
			dialog.text = "C'est exact, je suis "+pchar.GenQuest.Hold_GenQuest.Name+"! Mais nom "+pchar.GenQuest.Hold_GenQuest.CapName+" ne me dit rien."; // belamour gen
			link.l1 = "Je suis désolé. Peut-être que je me suis trompé...";
			link.l1.go = "Hold_GenQuest41";
		break;
		
		case "Hold_GenQuest41":
			AddQuestRecord("HoldQuest", "10");
			AddQuestUserData("HoldQuest", "sName", pchar.GenQuest.Hold_GenQuest.CapName);
			pchar.GenQuest.Hold_GenQuest = "prisoner_escaped";
			LAi_CharacterDisableDialog(NPChar);
			NPChar.LifeDay = 0;
			DialogExit();
			AddDialogExitQuestFunction("Hold_GenQuest_PrisonerEscaped");
		break;
		
		case "Hold_GenQuest50":
			dialog.text = "Wow ! Et comment suis-je censé l'aider ? En le libérant en tuant tous ses ennemis ou quoi ? Ha-ha-ha !";
			link.l1 = "Non-non, ce n'est pas nécessaire. Vous n'avez qu'à remettre "+pchar.GenQuest.Hold_GenQuest.RansomSum+" pesos comme rançon.";
			link.l1.go = "Hold_GenQuest51";
		break;		
		
		case "Hold_GenQuest51":
			dialog.text = "Quelle impudence ! Et pourquoi devrais-je payer une rançon pour lui ?! Il n'est ni mon parent ni mon ami !";
			link.l1 = "Hmm... Il m'a dit que vous étiez son seul espoir. Et il a aussi mentionné une certaine dette que vous avez...";
			link.l1.go = "Hold_GenQuest52";
		break;		
		
		case "Hold_GenQuest52":
			dialog.text = LinkRandPhrase("Quel insolent ! C'est lui qui me doit de l'argent, pour votre information ! Mais ce n'est pas une raison pour moi de le rançonner dans l'espoir qu'il rembourse les deux dettes.","Quel scélérat ! Il m'a escroqué lors du partage de notre affaire, et maintenant il a le culot de me demander de payer une rançon pour lui !","Voilà une surprise ! Pourquoi devrais-je payer une rançon pour lui ?! Nous ne sommes pas si proches.");
			link.l1 = "Alors, je peux lui dire que vous avez refusé de payer sa rançon et n'avez pas reconnu votre dette ?";	
			link.l1.go = "Hold_GenQuest53";
		break;
		
		case "Hold_GenQuest53":
			dialog.text = "Parbleu ! De quelle dette parlez-vous ? Je vous ai déjà tout expliqué ! Et si vous n'avez pas d'autres questions en dehors de cette histoire absurde, alors permettez-moi de prendre congé.";
			link.l1 = "Je vois. Eh bien, je n'ai plus de questions pour toi, mais j'en ai quelques-unes pour ton camarade.";
			link.l1.go = "Hold_GenQuest54";
		break;
		
		case "Hold_GenQuest54":
			AddQuestRecord("HoldQuest", "10");
			//AddQuestUserData("HoldQuest", "sName", GetFullName(NPChar)); // НПС вешать собрались? )))
			AddQuestUserData("HoldQuest", "sName", pchar.GenQuest.Hold_GenQuest.CapName); // belamour gen				
			pchar.GenQuest.Hold_GenQuest = "prisoner_escaped";
			LAi_CharacterDisableDialog(NPChar);
			NPChar.LifeDay = 0;
			DialogExit();
			AddDialogExitQuestFunction("Hold_GenQuest_PrisonerEscaped");
		break;
		
		case "Hold_GenQuest60":
			dialog.text = "Hmm... Et toi, si je ne m'abuse, tu es celui qui le retient... Bon, je suppose que je vais l'aider.";
			link.l1 = "Très bien. La rançon sera "+pchar.GenQuest.Hold_GenQuest.RansomSum+"pesos.";
			link.l1.go = "Hold_GenQuest61";
		break;
		
		case "Hold_GenQuest61":
			dialog.text = "Vous m'avez mal compris : je suis membre du conseil municipal. Nous veillons au respect de la charte.\n"+"Gardes !!! Gardes ! Arrêtez-le pour suspicion de traite d'esclaves et de pillage de navires de "+NationNameGenitive(sti(pchar.GenQuest.Hold_GenQuest.Nation))+" !";
			link.l1 = "Eh bien, 'matelot', laisse-moi juste te rejoindre...";
			link.l1.go = "Hold_GenQuest62";
		break;
		
		case "Hold_GenQuest62":
			LAi_SetImmortal(NPChar, false);
			AddQuestRecord("HoldQuest", "10");
			//AddQuestUserData("HoldQuest", "sName", GetFullName(NPChar));
			AddQuestUserData("HoldQuest", "sName", pchar.GenQuest.Hold_GenQuest.CapName); // belamour gen	
			pchar.GenQuest.Hold_GenQuest = "prisoner_escaped";
			LAi_SetWarriorTypeNoGroup(NPChar);
   	        LAi_warrior_DialogEnable(NPChar, false);
            LAi_group_MoveCharacter(NPChar, "TmpEnemy");			
			LAi_group_Attack(NPChar, Pchar);
			LAi_group_SetRelation("TmpEnemy", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_SetCheckFunction("TmpEnemy", "Hold_GenQuest_AfterBattle");
			chrDisableReloadToLocation = true; 
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);  
			AddDialogExitQuest("MainHeroFightModeOn"); 
			AddDialogExitQuestFunction("Hold_GenQuest_PrisonerEscaped");
			DialogExit();
		break;
		
		case "Hold_GenQuest70":
			dialog.text = "Que dis-tu ?! Et comment puis-je l'aider ?";
			link.l1 = "Il est retenu captif et il m'a demandé de vous parler à propos de sa rançon.";
			link.l1.go = "Hold_GenQuest71";
		break;		
		
		case "Hold_GenQuest71":
			dialog.text = "Bien sûr, bien sûr. Je ferai tout ce que je peux. Où les retiennent-ils ? Et quel est le montant de la rançon ?";
			link.l1 = "Les pirates exigent "+pchar.GenQuest.Hold_GenQuest.RansomSum+" pesos. Je dois livrer l'argent au port, et ensuite votre ami sera libéré.";
			link.l1.go = "Hold_GenQuest72";
		break;
		
		case "Hold_GenQuest72":
			dialog.text = "Voici l'argent. Heureusement, j'en avais assez sur moi.";
			link.l1 = "Oui, c'est vraiment de la veine. Va au port, alors, et bientôt tu reverras ton camarade.";
			link.l1.go = "Hold_GenQuest73";
		break;
		
		case "Hold_GenQuest73":
			addMoneyToCharacter(pchar, sti(pchar.GenQuest.Hold_GenQuest.RansomSum));
			AddQuestRecord("HoldQuest", "11");
			AddQuestUserData("HoldQuest", "sNameChar", GetFullName(NPChar)); // belamour gen 
			AddQuestUserData("HoldQuest", "sName", NPChar.Hold_GenQuest.Name); // belamour gen
			AddQuestUserData("HoldQuest", "sSum", pchar.GenQuest.Hold_GenQuest.RansomSum);
			pchar.GenQuest.Hold_GenQuest = "prisoner_ransom";
			LAi_CharacterDisableDialog(NPChar);
			NPChar.LifeDay = 0;
			DialogExit();
			AddDialogExitQuestFunction("Hold_GenQuest_PrisonerEscaped");
		break;				
		// Генератор "Situation in the hold - Ransom"
		
		// Генератор "Situation in the hold - Partner in crime"
		case "Hold_GenQuest80":
			dialog.text = "Bonjour, capitaine, désolé de ne pas avoir eu l'honneur de faire votre connaissance. Ils ont dit que vous me cherchiez.";
			link.l1 = "En effet, si vous êtes monsieur "+pchar.GenQuest.Hold_GenQuest.Name+". Je suis capitaine "+GetFullName(pchar)+", je voulais te parler.";
			link.l1.go = "Hold_GenQuest81";
		break;
		
		case "Hold_GenQuest81":
			dialog.text = "Et quel genre d'affaires est-ce, capitaine "+GetFullName(pchar)+"?";
			link.l1 = "J'ai entendu dire que tu possèdes quelque chose dont tu ne te soucierais pas de te séparer.";
			link.l1.go = "Hold_GenQuest82";
		break;
		
		case "Hold_GenQuest82":
			dialog.text = "Que veux-tu insinuer, exactement ?";
			link.l1 = "Ne sois pas si têtu, mon bonhomme, je connais très bien ton passé obscur, et cette carte de fortune, sur laquelle se trouve l'emplacement du trésor"+GetName(NAMETYPE_VIP,pchar.GenQuest.Hold_GenQuest.PirateName,NAME_ACC)+"est indiqué.";
			link.l1.go = "Hold_GenQuest83";
		break;
		
		case "Hold_GenQuest83":
			dialog.text = "Bon sang ! J'ai toujours su que ce scélérat"+pchar.GenQuest.Hold_GenQuest.CapName+" finirait par révéler cela tôt ou tard ! Qu'est-ce qui m'est passé par la tête quand je lui ai proposé cet accord ?";
			link.l1 = "Arrête de te plaindre. Je ne te veux aucun mal... Vends-moi juste cette carte et vis la vie à laquelle tu es habitué.";
			link.l1.go = "Hold_GenQuest84";
		break;
		
		case "Hold_GenQuest84":
			dialog.text = "Si seulement je pouvais en être si sûr... Et combien vas-tu m'offrir pour cela ? Tu dois sûrement savoir qu'il y avait beaucoup d'or dans le coffre. Il était porté par quatre hommes, que le Seigneur repose leurs âmes...";
			link.l1 = "Mais "+GetName(NAMETYPE_VIP,pchar.GenQuest.Hold_GenQuest.PirateName,NAME_NOM)+" aurait déjà pu revendiquer son trésor...";
			link.l1.go = "Hold_GenQuest85";
		break;
		
		case "Hold_GenQuest85":
			dialog.text = "Ainsi soit-il... Très bien, je suis prêt à vous le vendre pour "+pchar.GenQuest.Hold_GenQuest.Sum+"pesos. Je n'oserai de toute façon pas troubler les morts.";
			if(sti(pchar.money) >= sti(pchar.GenQuest.Hold_GenQuest.Sum) && !CheckCharacterItem(pchar,"mapQuest") && !CheckCharacterItem(pchar,"map_full"))
			{
				link.l1 = "D'accord. Vous avez un accord.";
				link.l1.go = "Hold_GenQuest86";
			}	
			link.l2 = "Non, mon bonhomme, ce bout de papier ne vaut pas cet argent. Adieu...";
			link.l2.go = "Hold_GenQuest87";
			pchar.quest.Hold_GenQuest_GetMapTimeIsOver.over = "yes";
		break;
		
		case "Hold_GenQuest86":		
			AddMoneyToCharacter(pchar, -sti(pchar.GenQuest.Hold_GenQuest.Sum));
			GiveItem2Character(pchar, "mapQuest"); 
			rItem = ItemsFromID("mapQuest");
			Hold_GenQuest_GenerateTreasureMap(rItem);
			AddQuestRecord("HoldQuest", "15");
			AddQuestUserData("HoldQuest", "sPirateName", GetName( NAMETYPE_VIP, pchar.GenQuest.Hold_GenQuest.PirateName, NAME_ACC));
			AddQuestUserData("HoldQuest", "sSex", GetSexPhrase("",""));
			AddQuestUserData("HoldQuest", "sSum", pchar.GenQuest.Hold_GenQuest.Sum);						
			NPChar.LifeDay = 0;
			LAi_CharacterDisableDialog(NPChar);			
			DialogExit();
			AddDialogExitQuest("OpenTheDoors");
		break;	
		
		case "Hold_GenQuest87":
			NPChar.LifeDay = 0;
			LAi_CharacterDisableDialog(NPChar);
			AddQuestRecord("HoldQuest", "16");
			AddQuestUserData("HoldQuest", "sSex", GetSexPhrase("",""));
			AddQuestUserData("HoldQuest", "sPirateName", GetName( NAMETYPE_VIP, pchar.GenQuest.Hold_GenQuest.PirateName, NAME_GEN)); // belamour gen
			AddQuestUserData("HoldQuest", "sSum", pchar.GenQuest.Hold_GenQuest.Sum);			
			CloseQuestHeader("HoldQuest");
			DeleteAttribute(pchar,"GenQuest.Hold_GenQuest");				
			DialogExit();
			AddDialogExitQuest("OpenTheDoors");
		break;
		// Генератор "Situation in the hold - Partner in crime"
		
		// Генератор "Shipwrecked"
		case "ShipWreck_1":
			dialog.text = "Comment cela peut-il être possible, capitaine ?! Dieu ne vous pardonnera jamais un tel péché.";
			link.l1 = "C'est à Lui de décider.";
			link.l1.go = "exit";
			ChangeCharacterComplexReputation(pchar,"nobility", -1);
			AddDialogExitQuestFunction("ShipWreck_DialogDisable");
		break;
		
		case "ShipWreck_2":
			pchar.GenQuest.ShipWreck.StartShipType = PiratesOnUninhabited_GenerateShipType(); 		
			pchar.GenQuest.ShipWreck.ShipTypeName = GenerateRandomNameToShip(sti(pchar.GenQuest.ShipWreck.Nation));			
			
			if(rand(1) == 0)
			{
				dialog.text = RandPhraseSimple("Bonjour, je suis "+pchar.GenQuest.ShipWreck.Name+", capitaine du "+GetStrSmallRegister(XI_ConvertString(ShipsTypes[sti(pchar.GenQuest.ShipWreck.StartShipType)].Name+"Acc"))+" ' "+pchar.GenQuest.ShipWreck.ShipTypeName+", mon navire s'est écrasé sur les récifs non loin de la côte."+"Seuls quelques marins de tout l'équipage ont réussi à survivre. La marée nous a échoués sur cette rive désolée. Nous étions affamés et assoiffés de "+(5+hrand(7))+" semaines maintenant","Bonjour, je suis "+pchar.GenQuest.ShipWreck.Name+", capitaine du "+GetStrSmallRegister(XI_ConvertString(ShipsTypes[sti(pchar.GenQuest.ShipWreck.StartShipType)].Name+"Gén"))+" '"+pchar.GenQuest.ShipWreck.ShipTypeName+". Notre navire s'est écrasé non loin d'ici."+"Nous avons réussi à atteindre cette rive sur les épaves, mais cet endroit semble inhabité. Nous avons été forcés de survivre avec des coquillages et des fruits de palmier pendant "+(5+hrand(7))+"semaines maintenant.");
				link.l1 = RandPhraseSimple("Et combien d'entre vous reste-t-il ?","Et combien d'entre vous ont réussi à survivre?");
				link.l1.go = "ShipWreck_3";
			}
			else
			{						
				pchar.GenQuest.ShipWreck.Mutiny = "true"; // belamour gen кавычки
				pchar.GenQuest.ShipWreck.BadName = GenerateRandomName_Generator(sti(pchar.GenQuest.ShipWreck.Nation), "man");
				pchar.GenQuest.ShipWreck.City = GetQuestNationsCity(sti(pchar.GenQuest.ShipWreck.Nation));
				dialog.text = "Oh, capitaine, nos pertes sont vraiment terribles... Bonjour, je suis "+pchar.GenQuest.ShipWreck.Name+", capitaine et propriétaire de "+GetStrSmallRegister(XI_ConvertString(ShipsTypes[sti(pchar.GenQuest.ShipWreck.StartShipType)].Name+"Gen"))+" ' "+pchar.GenQuest.ShipWreck.ShipTypeName+". Ou, devrais-je dire, ancien capitaine et propriétaire. "+"Ce salaud "+pchar.GenQuest.ShipWreck.BadName+" que j'ai engagé en "+XI_ConvertString("Colony"+pchar.GenQuest.ShipWreck.City+"Voc")+"avait provoqué la mutinerie de mon équipage. Finalement, nous avons débarqué en cet endroit perdu. Cela s'est passé "+(5+hrand(7))+" semaines auparavant.";
				link.l1 = "Et ensuite ? Tout ton équipage a rejoint les mutins ?";
				link.l1.go = "ShipWreck_4";			
			}
		break;
		
		case "ShipWreck_3":
			dialog.text = RandPhraseSimple("De tout l'équipage, seul "+ShipWreck_GetStringQty(sti(pchar.GenQuest.ShipWreck.Qty))+" survived. Other's have perished; several of them died already here of wounds and fever",
				"Only " + ShipWreck_GetStringQty(sti(pchar.GenQuest.ShipWreck.Qty)) + " were lucky enough. Others have met their end... either in the deep or in the dunes of this coast.");
			link.l1 = LinkRandPhrase("Oui, c'est un destin peu enviable. Mais tel est le sort du marin - n'importe qui pourrait se retrouver à ta place.","Je vois... Dieu tient chaque vie, c'est juste qu'il est trop occupé pour se souvenir de tout le monde.","En effet. L'homme propose, mais Dieu dispose.");
			link.l1.go = "ShipWreck_5";	
		break;
		
		case "ShipWreck_4":
			dialog.text = "Bien sûr que non ! Ceux qui ont refusé de rejoindre les mutins étaient nombreux, mais ces scélérats ont capturé l'arsenal, et c'est bien que nous n'ayons pas opposé de résistance, sinon nous aurions été tués sur-le-champ. Beaucoup ont déjà succombé ici à la fièvre et au poison des insectes venimeux, seulement "+ShipWreck_GetStringQty(sti(pchar.GenQuest.ShipWreck.Qty))+" survécu. Dieu merci, nos épreuves sont enfin terminées.";
			link.l1 = RandPhraseSimple("Oui, c'était vraiment un coup de malchance.","Eh bien, bien des choses étranges peuvent se produire dans ces lieux oubliés de Dieu.");
			link.l1.go = "ShipWreck_5";			
			link.l2 = "Attends, l'ami. Et comment devrais-je savoir que tu n'as pas été débarqué comme l'instigateur d'une mutinerie ?";
			link.l2.go = "ShipWreck_6";			
		break;
		
		case "ShipWreck_5":
			dialog.text = RandPhraseSimple("Capitaine, j'espère que vous avez plusieurs coffres vides sur votre navire. Nous avons tous des familles, et elles pleurent probablement notre perte pendant que nous parlons. Nous vous serions très reconnaissants.","Capitaine, nous sommes complètement désespérés, vous êtes notre seul espoir. Je vous en prie, ne nous refusez pas votre aide, sortez-nous de cette terre maudite.");
			if(GetFreeCrewQuantity(pchar) >= sti(pchar.GenQuest.ShipWreck.Qty) && GetPassengersQuantity(pchar) < PASSENGERS_MAX)
			{
				link.l1 = "Ohh... et où voudrais-tu que je t'emmène ?";
				link.l1.go = "ShipWreck_7";			
			}
			link.l2 = RandPhraseSimple(RandPhraseSimple("Je suis vraiment désolé, mais il n'y a même pas un seul hamac libre, sans parler des cabines. Les marins dorment sur le pont, ils ne peuvent même pas prendre un bon repos nocturne après leur quart...","Je détesterais vraiment te décevoir, mais le navire est surchargé, et les gens doivent dormir dans le mauvais temps. S'il y a une épidémie de maladie, je perdrai la moitié de l'équipage."),RandPhraseSimple("Je suis vraiment désolé, mais il n'y a absolument aucun espace libre pour l'équipage sur mon navire. Je ne peux pas embarquer plus de passagers.","Je dois te décevoir, mais mon navire est surchargé. Je crains l'épidémie."));
			link.l2.go = "ShipWreck_8";	
			if(stf(pchar.reputation.nobility) <= REPUTATION_NEUTRAL)
			{
				link.l3 = "Vous êtes un marin chevronné et vous devriez savoir que la présence de quelqu'un qui a subi un naufrage est un très mauvais présage. Mes marins vous jetteront tous par-dessus bord.";
				link.l3.go = "ShipWreck_9";
			}
		break;
		
		case "ShipWreck_6":
			dialog.text = "Que dis-tu, "+GetAddress_Form(npchar)+" "+pchar.lastname+"?! Ayez pitié ! Je suis un négociant, bien connu dans les Caraïbes ! Eh bien... Je suppose que je l'étais autrefois. Pas maintenant, sans navire ni argent...";
			link.l1 = "Comment cela... Je parie que vous étiez les véritables instigateurs de la mutinerie, et maintenant vous avez ce que vous méritez.";
			link.l1.go = "ShipWreck_18";
			if(GetPassengersQuantity(pchar) < PASSENGERS_MAX)
			{
				link.l2 = "Mais quel scélérat est-ce là "+pchar.GenQuest.ShipWreck.BadName+"! Vraiment, vas-tu le laisser s'en tirer comme ça et te soumettre à ton destin ?";
				link.l2.go = "ShipWreck_19";
			}	
		break;		
		
		case "ShipWreck_7":
			if(rand(1) == 0)
			{
				if(rand(100) < 90)
				{
					pchar.GenQuest.ShipWreck.variant = "1";
					dialog.text = "À tout établissement de "+NationNameGenitive(sti(pchar.GenQuest.ShipWreck.Nation))+".";
					link.l1 = "Eh bien, j'ai assez de coffres et de hamacs libres. Monte à bord du bateau.";
					link.l1.go = "ShipWreck_10";
					link.l2 = "Hmm... Nous avons des batailles devant nous, et je ne sais pas où tu seras plus en sécurité, à bord de mon navire ou dans cette crique douillette.";
					link.l2.go = "ShipWreck_11";
				}
				else
				{				
					dialog.text = "À Dunkerque ! Ma mère y habite...";
					link.l1 = "Es-tu fou ou quoi ?! Je suppose que tu as pris trop de coups sur la tête...";
					link.l1.go = "ShipWreck_12";					
					pchar.GenQuest.ShipWreck.Crazy = true; // получите психа на борт :-)
					
				}				
			}
			else
			{
				pchar.GenQuest.ShipWreck.variant = "2";
				dialog.text = "Où que tu veuilles, ça nous est égal. Nous n'avons rien pour te payer, de toute façon...";
				link.l1 = "Eh bien, j'ai assez de coffres et de hamacs libres. Monte à bord.";
				link.l1.go = "ShipWreck_10_1";
				link.l2 = "Hmm... Nous avons des batailles devant nous, et je ne sais pas où tu seras plus en sécurité, à bord de mon navire ou dans cette crique confortable.";
				link.l2.go = "ShipWreck_11";		
			}						
		break;		

		case "ShipWreck_8":
			pchar.GenQuest.ShipWreck.FoodQty = sti(pchar.GenQuest.ShipWreck.Qty) * 10 + rand(10);
			pchar.GenQuest.ShipWreck.MedicamentQty = sti(pchar.GenQuest.ShipWreck.Qty) * 5 + rand(10);
			pchar.GenQuest.ShipWreck.AmunitionQty = sti(pchar.GenQuest.ShipWreck.Qty) * 3 + rand(5);
			pchar.GenQuest.ShipWreck.RumQty = sti(pchar.GenQuest.ShipWreck.Qty) * 7 + rand(10);
			if(GetFreeCrewQuantity(pchar) < sti(pchar.GenQuest.ShipWreck.Qty))
			{
				if(GetSquadronGoods(pchar, GOOD_FOOD) < sti(pchar.GenQuest.ShipWreck.FoodQty) || GetSquadronGoods(pchar, GOOD_MEDICAMENT) < sti(pchar.GenQuest.ShipWreck.MedicamentQty))
				{
					dialog.text = "Mais en refusant, vous nous condamnerez certainement à la mort ! Eh bien, nous essaierons de nous frayer un chemin jusqu'au navire, même si cela nous coûte la vie !";
					link.l1 = "Quoi ? Regardez-vous, vous tenez à peine debout...";
					link.l1.go = "ShipWreck_8_1";
					link.l2 = "Tu peux essayer...";
					link.l2.go = "ShipWreck_16";
				}
				else
				{
					dialog.text = "Mais vous ne pouvez pas simplement nous laisser ici ! Sans votre aide, nous allons tous bientôt périr !";
					if(GetSquadronGoods(pchar, GOOD_WEAPON) < sti(pchar.GenQuest.ShipWreck.AmunitionQty) || GetSquadronGoods(pchar, GOOD_RUM) < sti(pchar.GenQuest.ShipWreck.RumQty))
					{			
						link.l1 = "La seule chose que je peux faire pour vous, c'est vous laisser suffisamment de provisions et de médicaments, et vous donner un bateau. Au moins, vous ne mourrez pas de faim et de soif. Quant à la navigation, je n'ai pas besoin de vous l'enseigner.";
						link.l1.go = "ShipWreck_8_2";
					}
					else
					{
						if(rand(1) == 0)
						{
							link.l1 = "Tout ce que je peux faire pour toi, c'est te laisser assez de provisions et de médicaments et te donner un bateau. Au moins, tu ne mourras pas de faim et de soif. Quant à la navigation, je n'ai pas besoin de t'apprendre cela.";
							link.l1.go = "ShipWreck_8_2";
						}
						else
						{
							link.l1 = "Je peux te laisser assez de médicaments, de munitions, de rhum et de provisions pour un mois. Je reviendrai moi-même ou enverrai quelqu'un te chercher.";
							link.l1.go = "ShipWreck_8_4";
						}
					}
				}
			}
			else
			{
				if(stf(pchar.reputation.nobility) <= REPUTATION_NEUTRAL) // плохиш
				{
					if(GetSquadronGoods(pchar, GOOD_FOOD) < sti(pchar.GenQuest.ShipWreck.FoodQty) || GetSquadronGoods(pchar, GOOD_MEDICAMENT) < sti(pchar.GenQuest.ShipWreck.MedicamentQty))				
					{
						dialog.text = "Mais en refusant, vous nous condamnez certainement à la mort! Eh bien, nous essayerons de nous frayer un chemin jusqu'au navire, même si cela nous coûte la vie!";
						link.l1 = "Quoi ? Regardez-vous, vous tenez à peine debout...";
						link.l1.go = "ShipWreck_8_1";
						link.l2 = "Tu peux essayer...";
						link.l2.go = "ShipWreck_16";					
					}
					else
					{
						link.l1 = "The only thing I can do for you is leave you enough provisions and medicines and give you a boat. At least you are not going to die of starvation and thirst; as for seafaring, I need not teach you that.";
						link.l1.go = "ShipWreck_8_2";					
					}
				}
				else // кибальчиш
				{
					if(GetSquadronGoods(pchar, GOOD_FOOD) < sti(pchar.GenQuest.ShipWreck.FoodQty) || GetSquadronGoods(pchar, GOOD_MEDICAMENT) < sti(pchar.GenQuest.ShipWreck.MedicamentQty))				
					{
						if(rand(1) == 0)
						{
							dialog.text = "Mais en refusant, vous nous condamnez certainement à la mort ! Eh bien, nous essayerons de nous frayer un chemin jusqu'au navire, même si cela nous coûte la vie !";
							link.l1 = "Quoi ? Regardez-vous, vous tenez à peine debout...";
							link.l1.go = "ShipWreck_8_1";
							link.l2 = "Tu peux essayer...";
							link.l2.go = "ShipWreck_16";						
						}
						else
						{
							dialog.text = "Comment as-tu pu nous faire ça ?!.. Non seulement tu as ignoré le Code de la Mer, mais tu as aussi terni ton honneur !";
							link.l1 = "Sûrement tu n'es pas celui qui doit parler de mon honneur, crevette !";
							link.l1.go = "ShipWreck_16";
						}	
					}
					else
					{
						link.l1 = "La seule chose que je peux faire pour toi, c'est te laisser assez de provisions et de médicaments et te donner un bateau. Au moins, tu ne mourras pas de faim et de soif. Quant à la navigation, je n'ai pas besoin de t'enseigner cela.";
						link.l1.go = "ShipWreck_8_2";											
					}						
				}
			}			
		break;				
	
		case "ShipWreck_8_1":
			dialog.text = "Tu as raison, nous n'avons aucune chance. Très bien, que Dieu soit ton juge, et que chacun reçoive ce qui lui est dû.";
			link.l1 = "Eh bien, je peux m'en occuper...";
			link.l1.go = "exit";
			ChangeCharacterComplexReputation(pchar,"nobility", -5);
			AddDialogExitQuestFunction("ShipWreck_DialogDisable");
		break;
	
		case "ShipWreck_8_2":
			dialog.text = "Eh bien... Tu ne nous laisses pas le choix... Nous prierons pour que les tempêtes et la soif ne nous prennent pas la vie avant que nous n'atteignions des lieux habités...";
			link.l1 = "Adieu. Que le Seigneur veille sur vous...";
			link.l1.go = "ShipWreck_8_3";
		break;
		
		case "ShipWreck_8_3":
			ChangeCharacterComplexReputation(pchar,"nobility", -2);
			AddCharacterExpToSkill(pchar, "Leadership", 25);
			RemoveCharacterGoods(pchar, GOOD_FOOD, sti(pchar.GenQuest.ShipWreck.FoodQty));
			RemoveCharacterGoods(pchar, GOOD_MEDICAMENT, sti(pchar.GenQuest.ShipWreck.MedicamentQty));			
			Log_SetStringToLog("You have spent " + pchar.GenQuest.ShipWreck.FoodQty + " units of provision.");
			Log_SetStringToLog("You have spent " + pchar.GenQuest.ShipWreck.MedicamentQty + "units of medicine.");
			DialogExit();
			NextDiag.TempNode = "ShipWreck_8_7";
			NextDiag.CurrentNode = NextDiag.TempNode;			
		break;
	
		case "ShipWreck_8_4":	
			dialog.text = "Apparemment, nous n'avons pas le choix... Mais je vous en prie capitaine, revenez dès que possible ou envoyez-nous un navire expéditionnaire.";
			link.l1 = "Je vais trouver quelque chose. Attends un peu.";
			link.l1.go = "ShipWreck_8_5";
		break;
	
		case "ShipWreck_8_5":		
			pchar.quest.ShipWreck_LocationExit.over = "yes";
			AddCharacterExpToSkill(pchar, "Leadership", 50); 
			RemoveCharacterGoods(pchar, GOOD_FOOD, sti(pchar.GenQuest.ShipWreck.FoodQty));
			RemoveCharacterGoods(pchar, GOOD_MEDICAMENT, sti(pchar.GenQuest.ShipWreck.MedicamentQty));			
			RemoveCharacterGoods(pchar, GOOD_WEAPON, sti(pchar.GenQuest.ShipWreck.AmunitionQty));
			RemoveCharacterGoods(pchar, GOOD_RUM, sti(pchar.GenQuest.ShipWreck.RumQty));			
			Log_SetStringToLog("You have spent " + pchar.GenQuest.ShipWreck.FoodQty + " units of provision.");
			Log_SetStringToLog("You have spent " + pchar.GenQuest.ShipWreck.MedicamentQty + "units of medicine.");		
			Log_SetStringToLog("You have spent " + pchar.GenQuest.ShipWreck.AmunitionQty + " units of arms.");
			Log_SetStringToLog("You have spent " + pchar.GenQuest.ShipWreck.RumQty + " units of rum");	
			ReOpenQuestHeader("ShipWrecked");
			if(CheckAttribute(pchar, "GenQuest.ShipWreck.Mutiny"))
			{
				AddQuestRecord("ShipWrecked", "11");
				AddQuestUserData("ShipWrecked", "sSex", GetSexPhrase("",""));
				AddQuestUserData("ShipWrecked", "ShoreName", UpperFirst(XI_ConvertString(pchar.location + "Gen"))); // belamour gen
				AddQuestUserData("ShipWrecked", "sBadName", pchar.GenQuest.ShipWreck.BadName);			
				AddQuestUserData("ShipWrecked", "sNation", NationNameGenitive(sti(pchar.GenQuest.ShipWreck.Nation)));
			}
			else
			{
				AddQuestRecord("ShipWrecked", "10");
				AddQuestUserData("ShipWrecked", "sSex", GetSexPhrase("",""));
				AddQuestUserData("ShipWrecked", "ShoreName", UpperFirst(XI_ConvertString(pchar.location + "Gen"))); // belamour gen
				AddQuestUserData("ShipWrecked", "sNation", NationNameGenitive(sti(pchar.GenQuest.ShipWreck.Nation)));
			}
			DialogExit();
			NextDiag.TempNode = "ShipWreck_8_6";
			NextDiag.CurrentNode = NextDiag.TempNode;	
			pchar.GenQuest.ShipWreck = "SailorsOnShore";
			SetFunctionTimerCondition("ShipWreck_SaveSailors", 0, 0, 30, false);
			pchar.GenQuest.ShipWreck.Shore = pchar.location;
			SaveCurrentQuestDateParam("GenQuest.ShipWreck");
			SetFunctionLocationCondition("ShipWreck_MeetInShore", pchar.GenQuest.ShipWreck.Shore, true);
		break;
	
		case "ShipWreck_8_6":			
			dialog.text = RandPhraseSimple("Capitaine, s'il vous plaît, souvenez-vous que vous êtes notre seul espoir...","Pourquoi traînes-tu ? Chaque minute passée ici est insupportable pour nous...");
			link.l1 = "Je ferai tout ce que je peux. Adieu...";
			link.l1.go = "exit";
			NextDiag.TempNode = "ShipWreck_8_6";		
		break;

		case "ShipWreck_8_7":			
			dialog.text = RandPhraseSimple("Adieu, capitaine... Nous devons nous préparer pour le voyage.","Adieu... Et allumez les bougies pour sauver nos âmes...");
			link.l1 = "Adieu. Que le Seigneur veille sur vous...";
			link.l1.go = "exit";
			NextDiag.TempNode = "ShipWreck_8_7";		
		break;
		
		case "ShipWreck_9":
			pchar.GenQuest.ShipWreck = "SailorsOnShoreFight"; // belamour gen
			dialog.text = "Comment as-tu pu nous faire cela ?! Non seulement tu as ignoré le Code de la Mer, mais tu as aussi terni ton honneur !";
			link.l1 = "Tu n'es sûrement pas celui qui doit parler de mon honneur, crevette !";
			link.l1.go = "ShipWreck_16";
		break;					
		
		case "ShipWreck_10":
			dialog.text = "Merci, capitaine ! Le chargement ne devrait pas prendre trop de temps. Mon Dieu, comme nous avions prié pour que ce moment arrive !";
			link.l1 = "C'est formidable. J'espère que tes épreuves seront bientôt terminées.";
			link.l1.go = "ShipWreck_13";
			pchar.quest.ShipWreck_DeliveToCity.win_condition.l1 = "Nation_City";
			pchar.quest.ShipWreck_DeliveToCity.win_condition.l1.nation = sti(pchar.GenQuest.ShipWreck.Nation);
			pchar.quest.ShipWreck_DeliveToCity.function = "ShipWreck_DeliveToCity";
			ReOpenQuestHeader("ShipWrecked");
			if(CheckAttribute(pchar, "GenQuest.ShipWreck.Mutiny"))
			{
				AddQuestRecord("ShipWrecked", "2");
				AddQuestUserData("ShipWrecked", "ShoreName", UpperFirst(XI_ConvertString(pchar.location + "Gen"))); // belamour gen
				// --> belamour окончание по количеству персон
				if(sti(pchar.GenQuest.ShipWreck.Qty) >= 5)
				{
					AddQuestUserData("ShipWrecked", "count", pchar.GenQuest.ShipWreck.Qty + " sailors");
				}
				else
				{
					AddQuestUserData("ShipWrecked", "count", pchar.GenQuest.ShipWreck.Qty + " sailor");
				}
				// <-- belamour
				AddQuestUserData("ShipWrecked", "sBadName", pchar.GenQuest.ShipWreck.BadName);
				AddQuestUserData("ShipWrecked", "sNation", NationNameGenitive(sti(pchar.GenQuest.ShipWreck.Nation)));
			}
			else
			{
				AddQuestRecord("ShipWrecked", "1");
				AddQuestUserData("ShipWrecked", "ShoreName", UpperFirst(XI_ConvertString(pchar.location + "Gen"))); // belamour gen
				// --> belamour окончание по количеству персон
				if(sti(pchar.GenQuest.ShipWreck.Qty) >= 5)
				{
					AddQuestUserData("ShipWrecked", "count", pchar.GenQuest.ShipWreck.Qty + " sailors");
				}
				else
				{
					AddQuestUserData("ShipWrecked", "count", pchar.GenQuest.ShipWreck.Qty + " sailor");
				}
				// <-- belamour
				AddQuestUserData("ShipWrecked", "ShipType", GetStrSmallRegister(XI_ConvertString(ShipsTypes[sti(pchar.GenQuest.ShipWreck.StartShipType)].Name + "Gen"))); // belamour gen
				AddQuestUserData("ShipWrecked", "ShipName", pchar.GenQuest.ShipWreck.ShipTypeName);
				AddQuestUserData("ShipWrecked", "sNation", NationNameGenitive(sti(pchar.GenQuest.ShipWreck.Nation)));
				// --> belamour: нужно разделить, иначе получается с потерпевшего крушение бригантины 
				if(ShipsTypes[sti(pchar.GenQuest.ShipWreck.StartShipType)].name == "SHIP_BRIGANTINE" || ShipsTypes[sti(pchar.GenQuest.ShipWreck.StartShipType)].name == "SHIP_SCHOONER_W")
				{
					AddQuestUserData("ShipWrecked", "sText", "wrecked");
				}
				else
				{
					AddQuestUserData("ShipWrecked", "sText", "wrecked");
				}
				// <-- belamour
			}
			
		break;							

		case "ShipWreck_10_1":
			dialog.text = "Merci, capitaine ! Le chargement ne devrait pas prendre trop de temps. Dieu, comme nous avions prié pour que ce moment arrive !";
			link.l1 = "C'est formidable. J'espère que vos épreuves seront bientôt terminées.";
			link.l1.go = "ShipWreck_13";
			pchar.quest.ShipWreck_DeliveToCity.win_condition.l1 = "Location_Type";
			pchar.quest.ShipWreck_DeliveToCity.win_condition.l1.location_type = "town";
			pchar.quest.ShipWreck_DeliveToCity.function = "ShipWreck_DeliveToCity";
			ReOpenQuestHeader("ShipWrecked");
			if(CheckAttribute(pchar,"GenQuest.ShipWreck.Mutiny"))
			{
				AddQuestRecord("ShipWrecked", "4");
				AddQuestUserData("ShipWrecked", "ShoreName", UpperFirst(XI_ConvertString(pchar.location + "Gen"))); // belamour gen
				AddQuestUserData("ShipWrecked", "sBadName", pchar.GenQuest.ShipWreck.BadName);
				// --> belamour окончание по количеству персон
				if(sti(pchar.GenQuest.ShipWreck.Qty) >= 5)
				{
					AddQuestUserData("ShipWrecked", "count", pchar.GenQuest.ShipWreck.Qty + " sailors");
				}
				else
				{
					AddQuestUserData("ShipWrecked", "count", pchar.GenQuest.ShipWreck.Qty + " sailor");
				}
				// <-- belamour
			}
			else
			{
				AddQuestRecord("ShipWrecked", "3");
				AddQuestUserData("ShipWrecked", "ShoreName", UpperFirst(XI_ConvertString(pchar.location + "Gen"))); // belamour gen
				// --> belamour окончание по количеству персон
				if(sti(pchar.GenQuest.ShipWreck.Qty) >= 5)
				{
					AddQuestUserData("ShipWrecked", "count", pchar.GenQuest.ShipWreck.Qty + " sailors");
				}
				else
				{
					AddQuestUserData("ShipWrecked", "count", pchar.GenQuest.ShipWreck.Qty + " sailor");
				}
				// <-- belamour
				AddQuestUserData("ShipWrecked", "ShipType", GetStrSmallRegister(XI_ConvertString(ShipsTypes[sti(pchar.GenQuest.ShipWreck.StartShipType)].Name + "Gen"))); // belamour gen
				AddQuestUserData("ShipWrecked", "ShipName", pchar.GenQuest.ShipWreck.ShipTypeName);
				// --> belamour: нужно разделить, иначе получается с потерпевшего крушение бригантины 
				if(ShipsTypes[sti(pchar.GenQuest.ShipWreck.StartShipType)].name == "SHIP_BRIGANTINE" || ShipsTypes[sti(pchar.GenQuest.ShipWreck.StartShipType)].name == "SHIP_SCHOONER_W")
				{
					AddQuestUserData("ShipWrecked", "sText", "wrecked");
				}
				else
				{
					AddQuestUserData("ShipWrecked", "sText", "wrecked");
				}
				// <-- belamour
			}			
		break;							
				
		case "ShipWreck_11":
			dialog.text = "Allez ! Vraiment, capitaine ?! Avons-nous peur de la mort ?! Nous l'avons déjà bernée une fois, nous pouvons le refaire. Nous ne voulons juste pas perdre nos vies comme ça. Pourrir ici, seuls\nNous serions ravis de rejoindre votre équipage et de combattre bravement sous votre pavillon. Ne nous laissez pas ici...";
			link.l1 = "Je vois que vous êtes prêts à tout pour sortir d'ici. Mais regardez-vous, quel genre de marins pouvez-vous être ?";
			link.l1.go = "ShipWreck_14";
			if(GetFreeCrewQuantity(pchar) >= sti(pchar.GenQuest.ShipWreck.Qty))
			{
				link.l2 = "C'est une bonne idée. Je suppose que je peux t'engager.";
				link.l2.go = "ShipWreck_15";
			}	
		break;									
		
		case "ShipWreck_12":
			dialog.text = "Non-non, je ne plaisante pas ! S'il te plaît, emmène-moi loin de cet abattoir caribéen... hors de cet enfer ! Tu sais, je suis un homme riche... un homme très riche. Même le Pape lui-même n'a pas vu autant d'or de toute sa vie. Je te couvrirai d'or...";
			link.l1 = "Oh là là... D'accord, monte dans le bateau...";
			link.l1.go = "ShipWreck_13";
			pchar.quest.ShipWreck_DeliveToCity.win_condition.l1 = "Location_Type";
			pchar.quest.ShipWreck_DeliveToCity.win_condition.l1.location_type = "town";
			pchar.quest.ShipWreck_DeliveToCity.function = "ShipWreck_DeliveToCity";			
			ChangeOfficersLoyality("bad_all", 1);
			ReOpenQuestHeader("ShipWrecked");
			AddQuestRecord("ShipWrecked", "5");
			AddQuestUserData("ShipWrecked", "sSex", GetSexPhrase("",""));
			AddQuestUserData("ShipWrecked", "ShoreName", UpperFirst(XI_ConvertString(pchar.location + "Gen"))); // belamour gen
			AddQuestUserData("ShipWrecked", "count", pchar.GenQuest.ShipWreck.Qty);
			AddQuestUserData("ShipWrecked", "ShipType", GetStrSmallRegister(XI_ConvertString(ShipsTypes[sti(pchar.GenQuest.ShipWreck.StartShipType)].Name + "Gen"))); // belamour gen
			AddQuestUserData("ShipWrecked", "ShipName", pchar.GenQuest.ShipWreck.ShipTypeName);	
			// --> belamour: нужно разделить, иначе получается с потерпевшего крушение бригантины
			if(ShipsTypes[sti(pchar.GenQuest.ShipWreck.StartShipType)].name == "SHIP_BRIGANTINE" || ShipsTypes[sti(pchar.GenQuest.ShipWreck.StartShipType)].name == "SHIP_SCHOONER_W")
			{
				AddQuestUserData("ShipWrecked", "sText", "wrecked");
			}
			else
			{
				AddQuestUserData("ShipWrecked", "sText", "wrecked");
			}
			// <-- belamour
		break;							

		case "ShipWreck_13": // берем пассажирами
			pchar.GenQuest.ShipWreck = "SailorsSaved";
			//Achievment_SetStat(29, sti(pchar.GenQuest.ShipWreck.Qty));
			if(CheckAttribute(pchar,"GenQuest.ShipWreck.variant"))
			{
				if(pchar.GenQuest.ShipWreck.variant == "1") ChangeCharacterComplexReputation(pchar,"nobility", 1);			
				if(pchar.GenQuest.ShipWreck.variant == "2") ChangeCharacterComplexReputation(pchar,"nobility", 2);			
			}	
			for(i = 0; i < sti(pchar.GenQuest.ShipWreck.Qty); i++)
			{
				rChar = CharacterFromID("ShipWreck_" + i);
				if(i == 0) 
				{
					AddPassenger(pchar, rChar, false);
					SetCharacterRemovable(rChar, false);	
				}
				LAi_SetWarriorTypeNoGroup(rChar);
				rChar.Dialog.currentnode = "ShipWreck_13_again";
			}
			DialogExit();
		break;
		
		case "ShipWreck_13_again":
			dialog.text = LinkRandPhrase("Pourquoi traînez-vous, capitaine ? Ordonnez de lever l'ancre.","Nous sommes désolés, capitaine, mais nous devons nous préparer à lever l'ancre.","Nous avons tellement de chance que vous ayez décidé de venir ici!");
			link.l1 = "Dépêche-toi. Le navire n'attendra personne.";
			link.l1.go = "exit";
			NextDiag.TempNode = "ShipWreck_13_again";		
		break;
		
		case "ShipWreck_14":
			dialog.text = "Capitaine, nous n'avons rien à perdre. La mort nous suit déjà à la trace... Nous préférons mourir dans un combat loyal plutôt que d'être dévorés par des coyotes puants...";
			link.l1 = "Oh, c'est un défi, alors ?! Très bien, réglons nos différends"+GetSexPhrase("comme des hommes","")+"!";
			link.l1.go = "ShipWreck_16";
			AddDialogExitQuest("MainHeroFightModeOn"); 
		break;		
		
		case "ShipWreck_15":
			dialog.text = "Je le jure, capitaine, vous ne le regretterez pas. Nous serons les meilleurs marins de tout l'archipel.";
			link.l1 = "Super ! Monte dans la barque...";
			link.l1.go = "ShipWreck_17";			
		break;				
		
		case "ShipWreck_16":
			ChangeCharacterComplexReputation(pchar,"nobility", -3);
			for(i = 0; i < sti(pchar.GenQuest.ShipWreck.Qty); i++)
			{
				rChar = CharacterFromID("ShipWreck_" + i);
				LAi_SetImmortal(rChar, false);
				if(CheckPassengerInCharacter(pchar, "ShipWreck_" + i)) 
				{
					RemovePassenger(pchar, rChar);
				}
				LAi_SetWarriorType(rChar);
				LAi_group_MoveCharacter(rChar, "ShipWreckGroup");
			}

			LAi_Group_SetRelation("ShipWreckGroup", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_Group_FightGroups("ShipWreckGroup", LAI_GROUP_PLAYER, true);
			if(pchar.GenQuest.ShipWreck == "fight" || pchar.GenQuest.ShipWreck == "SailorsOnShoreFight") // belamour gen
			{
				LAi_group_SetCheck("ShipWreckGroup", "OpenTheDoors"); 
				LAi_group_SetCheckFunction("ShipWreckGroup", "ShipWreck_AfterBattle");
			}	
			DialogExit();		
		break;
		
		case "ShipWreck_17": // принимаем в команду
			if(pchar.GenQuest.ShipWreck.variant == "1") ChangeCharacterComplexReputation(pchar,"nobility", 1);			
			if(pchar.GenQuest.ShipWreck.variant == "2") ChangeCharacterComplexReputation(pchar,"nobility", 2);			
			for(i = 0; i < sti(pchar.GenQuest.ShipWreck.Qty); i++)
			{
				rChar = CharacterFromID("ShipWreck_" + i);
				LAi_SetWarriorTypeNoGroup(rChar);
				rChar.LifeDay = 0;			
				rChar.Dialog.currentnode = "ShipWreck_17_again";
			}
			AddCharacterCrew(pchar, sti(pchar.GenQuest.ShipWreck.Qty));
			// --> belamour gen по количеству персон
			if(sti(pchar.GenQuest.ShipWreck.Qty) >= 5) sText = "";	
			else sText = "";
			Log_Info("Your team has increased by " + pchar.GenQuest.ShipWreck.Qty + " man" + sText + ".");
			// <-- belamour gen 
			Achievment_SetStat(29, sti(pchar.GenQuest.ShipWreck.Qty));
			pchar.quest.ShipWreck_LocExit.over = "yes"; // Снимаем прерывание на выход из локации			
			DeleteAttribute(pchar, "GenQuest.ShipWreck");			
			AddCharacterExpToSkill(pchar, "Leadership", 50); 			
			DialogExit();
		break;

		case "ShipWreck_17_again":
			dialog.text = LinkRandPhrase("Je te le jure, capitaine, tu ne le regretteras pas.","Vous avez fait le bon choix, capitaine.","Capitaine, soyez assuré que vous avez eu autant de chance que nous !");
			link.l1 = RandPhraseSimple("J'espère bien.","Dépêche-toi. Le navire n'attendra personne.");
			link.l1.go = "exit";
			NextDiag.TempNode = "ShipWreck_17_again";
		break;
		
		case "ShipWreck_18":
			dialog.text = "Capitaine, pourquoi offenseriez-vous des gens honnêtes avec une telle méfiance ? Regardez juste leurs visages, pensez-vous vraiment qu'ils pourraient être des mutins ?";
			link.l1 = "D'accord, mais que suis-je censé faire de toi maintenant ?";
			link.l1.go = "ShipWreck_20";
		break;
		
		case "ShipWreck_19":
			dialog.text = "Et que puis-je faire ? Au moins maintenant, je suis en vie... et je remercie Dieu de m'en être sorti ! Mais si tu m'aides à récupérer mon navire et à me venger de mon humiliation, je suis prêt à te donner tout ce que cet infâme aura volé et caché dans la cale.";
			link.l1 = "D'accord, c'est un marché.";
			link.l1.go = "ShipWreck_13";
			ShipWreck_SetCapToMap();
			SetFunctionTimerCondition("prosralisrok", 0, 0, 180, false); // таймер лесник тамймер на поиск корабля 																																   
			ReOpenQuestHeader("ShipWrecked");
			AddQuestRecord("ShipWrecked", "16");
			AddQuestUserData("ShipWrecked", "ShoreName", UpperFirst(XI_ConvertString(pchar.location + "Gen"))); // belamour gen
			AddQuestUserData("ShipWrecked", "sName", pchar.GenQuest.ShipWreck.Name);
			// --> belamour окончание по количеству персон
			if(sti(pchar.GenQuest.ShipWreck.Qty) >= 5)
			{
				AddQuestUserData("ShipWrecked", "count", pchar.GenQuest.ShipWreck.Qty + " his sailors");
			}
			else
			{
				AddQuestUserData("ShipWrecked", "count", pchar.GenQuest.ShipWreck.Qty + " his sailor");
			}
			// <-- belamour
			AddQuestUserData("ShipWrecked", "sBadName", pchar.GenQuest.ShipWreck.BadName);
			AddQuestUserData("ShipWrecked", "ShipName", pchar.GenQuest.ShipWreck.ShipTypeName);	
		break;
		
		case "ShipWreck_20":
			dialog.text = "Nous ne sommes pas en position de donner des ordres. C'est à vous de décider, emmenez-nous dans n'importe quelle colonie ou acceptez-nous dans votre équipage.";
			if(GetFreeCrewQuantity(pchar) >= sti(pchar.GenQuest.ShipWreck.Qty))
			{
				link.l1 = "D'accord, je te prends dans mon équipage. Mais pas de bêtises ! J'ai une discipline stricte sur mon navire !";
				link.l1.go = "ShipWreck_17";
			}
			link.l2 = "Je ne t'emmène nulle part. J'ai déjà assez de brutes dans mon équipage.";	
			link.l2.go = "ShipWreck_22";
			link.l3 = "D'accord, monte dans le bateau, je t'emmène quelque part.";
			link.l3.go = "ShipWreck_10_1";
		break;		
		
		case "ShipWreck_22":
			dialog.text = "Eh bien... Tu ne nous laisses pas le choix... Nous prierons pour que la Providence nous montre sa clémence et nous permette de sortir de cet endroit périlleux. Si Dieu le veut, nous pourrions encore atteindre la terre habitée...";
			link.l1 = "Adieu. Que le Seigneur veille sur vous...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("ShipWreck_DialogDisable");
		break;		
		
		case "ShipWreck_30":
			if(pchar.GenQuest.ShipWreck == "SailorsSaved")
			{
				dialog.text = "Merci beaucoup, capitaine "+GetFullName(pchar)+"! Vous avez fait tant pour nous qu'aucune gratitude ne pourrait être suffisante pour vous rembourser. Et bien que toutes nos possessions ne valent pas un sou, permettez-moi de vous offrir cet amulette. Elle serait très utile pour un capitaine souvent engagé dans des batailles navales.";
				link.l1 = "Merci pour ton cadeau ! Ce bibelot est fort utile, en effet ! Adieu, capitaine "+pchar.GenQuest.ShipWreck.Name+" et bonne chance à vous dans vos voyages.";
				link.l1.go = "ShipWreck_47";
			}
			else
			{
				dialog.text = "Capitaine, merci beaucoup. Vous avez fait beaucoup pour nous, et toute récompense serait inférieure à notre reconnaissance. S'il vous plaît, acceptez ce modeste cadeau en signe de notre gratitude.";
				link.l1 = "Vraiment, tu n'aurais pas dû te donner cette peine... Tu as bien plus besoin d'argent que moi. Mais c'est très gentil de ta part. Merci, et adieu.";
				link.l1.go = "ShipWreck_31";
			}	
		break;
		
		case "ShipWreck_31":
			//addMoneyToCharacter(pchar, sti(pchar.rank) * 200 + rand(2000));
			AddCharacterExpToSkill(pchar, "Commerce", 50);
			AddCharacterExpToSkill(pchar, "Sailing", 100);
			TakeNItems(pchar, "jewelry2", 15+hrand(10));
			AddQuestRecord("ShipWrecked", "6");
			AddQuestUserData("ShipWrecked", "sSex", GetSexPhrase("",""));
			AddQuestUserData("ShipWrecked", "sName", pchar.GenQuest.ShipWreck.Name);
			AddQuestUserData("ShipWrecked", "sCity", XI_ConvertString("Colony"+ Locations[FindLocation(PChar.location)].townsack + "Acc"));
			CloseQuestHeader("ShipWrecked");
			DialogExit();
			AddDialogExitQuestFunction("ShipWreck_GoOut");
		break;
		
		case "ShipWreck_32":	
			dialog.text = "Capitaine, sachez qu'il y a des gens qui iraient aux confins du monde pour vous, désormais. C'est dommage que je n'ai rien pour vous remercier. Pourtant... S'il vous plaît, acceptez ce bibelot, je l'ai trouvé dans cette crique maudite. J'espère qu'il vous portera chance.";
			link.l1 = "Tout le monde aurait fait de même à ma place. Adieu.";
			link.l1.go = "ShipWreck_33";
		break;
		
		case "ShipWreck_33":
			GiveItem2Character(pchar, pchar.GenQuest.ShipWreck.Prize);
			AddCharacterExpToSkill(pchar, "Fortune", 100);
			AddCharacterExpToSkill(pchar, "Sailing", 100);
			AddQuestRecord("ShipWrecked", "6");
			AddQuestUserData("ShipWrecked", "sSex", GetSexPhrase("",""));
			AddQuestUserData("ShipWrecked", "sName", pchar.GenQuest.ShipWreck.Name);
			AddQuestUserData("ShipWrecked", "sCity", XI_ConvertString("Colony" + Locations[FindLocation(PChar.location)].townsack + "Acc")); // belamour gen: просто pchar.location ничего не даст
			CloseQuestHeader("ShipWrecked");		
			DialogExit();
			AddDialogExitQuestFunction("ShipWreck_GoOut");
		break;
		
		case "ShipWreck_34":
			dialog.text = RandPhraseSimple(RandPhraseSimple("Capitaine, est-ce déjà Dunkerque ?","Sommes-nous vraiment à Dunkerque, capitaine ?"),RandPhraseSimple("Capitaine, est-ce l'Europe?","Avons-nous navigué vers l'Europe si vite?"));
			bTemp = !GetCharacterItem(pchar, "map_full") && !GetCharacterItem(pchar, "map_part2");
			bTemp = !GetCharacterItem(pchar, "map_part1") || bTemp;
			if(rand(100) > 75 && !isDay() && bTemp)
			{
				link.l1 = "Ah-ha...";
				link.l1.go = "ShipWreck_40";
			}
			else
			{
				link.l1 = LinkRandPhrase("Pas encore...","Quel Dunkerque? Quelle Europe? Regarde autour!","Oh mon Dieu !");
				link.l1.go = "ShipWreck_35";
			}
		break;
		
		case "ShipWreck_35":
			dialog.text = LinkRandPhrase("Mais, capitaine, tu as fait une promesse !","Comment as-tu pu manquer à ta parole, capitaine ?","Et quand arrivons-nous en Europe ?");
			if(rand(100) < 70)
			{
				link.l1 = "D'accord. Monsieur, rassemblez vos hommes et vos affaires et allez où bon vous semble.";
				link.l1.go = "ShipWreck_36";
			}
			link.l2 = RandPhraseSimple(LinkRandPhrase("Es-tu certain que nous devons vraiment nous rendre à Dunkerque ?","Tu sais, mon navire n'est pas fait pour naviguer à travers l'océan.","Capitaine, et qu'est-ce qui ne va pas avec les Caraïbes ?"),LinkRandPhrase("Mais j'avais d'autres projets...","Pourquoi veux-tu aller en Europe en premier lieu...","Pense à toutes ces séduisantes mulâtresses ! Tu ne les rencontreras jamais en Europe..."));
			link.l2.go = "ShipWreck_37";	
		break;
		
		case "ShipWreck_36":
			pchar.quest.ShipWreck_DeliveToCity.over = "yes";
			pchar.GenQuest.ShipWreck = "fight";
			dialog.text = "Mais comment?.. Comment oses-tu?! Quelle sorte de trahison est-ce?! Je vais t'apprendre à rester fidèle à ta parole!";
			link.l1 = "Eh bien, tu l'as cherché...";
			link.l1.go = "ShipWreck_16";
			AddCharacterExpToSkill(pchar, "Sneak", 100);
			AddDialogExitQuest("MainHeroFightModeOn"); 
		break;
		
		case "ShipWreck_37":
			dialog.text = LinkRandPhrase(RandPhraseSimple("Non ! Je dois me rendre à Dunkerque !","Au lieu de m'enseigner la géographie, tu devrais plutôt remplir ton obligation !"),RandPhraseSimple("Je ne veux rien entendre à ce sujet ! Tu m'as promis de m'emmener en Europe !","Non, capitaine, cela ne va pas. Nous naviguons vers l'Europe."),"Je ne vais pas mener une vie misérable pour le reste de mes jours dans ce trou !");
			link.l1 = "Oh, je ne sais pas si cela va se terminer...";
			link.l1.go = "ShipWreck_38";
		break;		
		
		case "ShipWreck_38":
			chrDisableReloadToLocation = false;			
			SetFunctionExitFromLocationCondition("ShipWreck_ExitFromTown", pchar.location, false);				
			if(!CheckAttribute(pchar,"GenQuest.ShipWreck.CrazyRec")) // mitrokosta исправлена блокировка поручения капитана
			{
				pchar.GenQuest.ShipWreck.CrazyRec = true;
				AddQuestRecord("ShipWrecked", "7");
			}
			DialogExit();
		break;
		
		case "ShipWreck_40":
			pchar.quest.ShipWreck_DeliveToCity.over = "yes";
			dialog.text = "Voyez! Voilà un homme décent! L'Europe! Sacrée vieille Europe! Oui-oui-oui!\nOh, oui! Vous avez rempli votre part du marché et je ferai de même. Tenez, prenez cette moitié de la carte. L'autre moitié, mon partenaire l'avait. Repose en paix, ou repose en mer? Peu importe. C'est lui qui m'a convaincu de participer à cette aventure.";
			link.l1 = "Attends, donc tu n'es pas marin ? Ton camarade était capitaine ?";
			link.l1.go = "ShipWreck_41";
		break;
		
		case "ShipWreck_41":
			dialog.text = "Oh là là!.. Bien sûr que non! Eh bien, oui, je ne suis pas marin. Et il a été emporté par-dessus bord par une énorme vague, quand il a décidé de naviguer plus loin de la côte. Ensuite, j'ai pris le commandement et ordonné de naviguer dans la crique... Et nous avons bien fait de nous frayer un chemin à travers les récifs, jusqu'à ce que tout soit décidé par un accident fatal. Le navire a heurté un fragment de rocher et a coulé...";
			link.l1 = "Voilà une vraie démonstration d'incompétence...";
			link.l1.go = "ShipWreck_42";
		break;
		
		case "ShipWreck_42":
			dialog.text = "Ecoute, est-ce vraiment Dunkerque ? Réfléchis-y, cela ne fait que six mois et tout l'endroit a changé.\nTiens, prends la carte, ou plutôt une partie de celle-ci, pour être précis. Le trésor se trouve à l'intérieur d'une grotte ! Aucune idée de quelle île il s'agit, mais tu es un marin expérimenté, tu trouveras l'emplacement exact un jour... Je te garantis qu'il y a d'innombrables richesses du pirate nommé aaarrrrrhg...";
			link.l1 = "Merci, mon brave. Même s'il n'y a aucun trésor, je ne serai pas trop contrarié. Adieu, et j'espère que nous ne nous reverrons jamais...";
			link.l1.go = "ShipWreck_43";
		break;
		
		case "ShipWreck_43":
			sld = CharacterFromID("ShipWreck_0");
			RemovePassenger(pchar, sld);
			AddCharacterExpToSkill(pchar, "Fortune", 200);
			AddMapPart();
			AddQuestRecord("ShipWrecked", "9");
			AddQuestUserData("ShipWrecked", "sSex", GetSexPhrase("",""));
			CloseQuestHeader("ShipWrecked");	
			AddSimpleRumourCity(LinkRandPhrase(RandPhraseSimple("They say some loony recently showed up on the island. He is telling everyone that he had lost his documents, and no he's attempting to apply for a captain on a ship to Dunkirk.",
				"They say some maniac recently showed up on the island. He stole a spade at the local shop and now is digging a pit past the town gates..."),
				RandPhraseSimple("Just imagine, recently some visiting European in worn and dirty clothes attempted to get an audience with the governor! He claimed that he needed to see the governor of Dunkirk ass soon as possible.",
				"There was a scandal at the town hall recently. Some vagrant was caught, he claimed that he personally knew the governor of Dunkirk."),
				"Some psycho was looking for you recently. He claimed that you owed him money..."), pchar.location, 5, 3,"");
			DialogExit();
			AddDialogExitQuestFunction("ShipWreck_GoOut");
		break;
		
		case "ShipWreck_44":
			dialog.text = RandPhraseSimple("Capitaine, c'est formidable que vous ne nous ayez pas oubliés ! Nous avons tous prié pour vous !","Capitaine, notre salut est-il proche ? Que nous avions prié pour qu'il vienne ! Certains ont déjà commencé à désespérer...");
			link.l1 = "Salutations, "+pchar.GenQuest.ShipWreck.Name+"! Comment pourrais-je laisser mes collègues dans un tel état ? Où aller ?";
			link.l1.go = "ShipWreck_45";
			link.l2 = "Salutations, "+pchar.GenQuest.ShipWreck.Name+"! J'ai bien peur d'avoir de mauvaises nouvelles pour vous. Il y a eu un changement de plan, et je ne pourrai pas vous embarquer.";
			link.l2.go = "ShipWreck_9";
		break;
		
		case "ShipWreck_45":
			dialog.text = "Peu nous importe où aller, tant que c'est loin de cet endroit maudit... Nous permettriez-vous de commencer à nous embarquer ?";
			link.l1 = "Oui, vas-y avec ça. Bientôt tes épreuves seront terminées.";
			link.l1.go = "ShipWreck_46";
		break;

		case "ShipWreck_46":
			ChangeCharacterComplexReputation(pchar,"nobility", 4);			
			for(i = 0; i < sti(pchar.GenQuest.ShipWreck.Qty); i++)
			{
				rChar = CharacterFromID("ShipWreck_" + i);
				if(i == 0) 
				{
					AddPassenger(pchar, rChar, false);
					SetCharacterRemovable(rChar, false);	
				}
				LAi_SetWarriorTypeNoGroup(rChar);
				rChar.dialog.currentnode = "ShipWreck_13_again";
			}			
			pchar.quest.ShipWreck_SaveSailors.over = "yes"; // belamour gen снять таймер на 30 дней	 
			pchar.quest.ShipWreck_DeliveToCity.win_condition.l1 = "Location_Type";
			pchar.quest.ShipWreck_DeliveToCity.win_condition.l1.location_type = "town";
			pchar.quest.ShipWreck_DeliveToCity.function = "ShipWreck_DeliveToCity";			
			pchar.GenQuest.ShipWreck = "SailorsSaved";
			if(CheckAttribute(pchar,"GenQuest.ShipWreck.Mutiny")) DeleteAttribute(pchar,"GenQuest.ShipWreck.Mutiny"));
			SetFunctionExitFromLocationCondition("ShipWreck_LocationExit", pchar.location, false);				
			DialogExit();			
		break;

		case "ShipWreck_47":
			AddCharacterExpToSkill(pchar, "Fortune", 50);
			AddCharacterExpToSkill(pchar, "Sailing", 100);
			GiveItem2Character(pchar, "indian_10");
			AddQuestRecord("ShipWrecked", "15");
			AddQuestUserData("ShipWrecked", "sSex", GetSexPhrase("",""));
			AddQuestUserData("ShipWrecked", "sName", pchar.GenQuest.ShipWreck.Name);
			CloseQuestHeader("ShipWrecked");				
			DialogExit();
			AddDialogExitQuestFunction("ShipWreck_GoOut");
		break;
		
		case "ShipWreck_48":
			dialog.text = "Merci, capitaine. Nous commencions à désespérer, mais vous nous avez littéralement ramenés à la vie.";
			link.l1 = "Ce n'était rien... Adieu.";
			link.l1.go = "ShipWreck_49";
		break;
		
		case "ShipWreck_49":
			AddQuestRecord("ShipWrecked", "17");
			AddQuestUserData("ShipWrecked", "sSex", GetSexPhrase("",""));
			CloseQuestHeader("ShipWrecked");								
			DialogExit();
			AddDialogExitQuestFunction("ShipWreck_GoOut");
		break;
		
		case "ShipWreck_50":
			dialog.text = "Que diable veux-tu de moi ?";
			link.l1 = "Je suis venu"+GetSexPhrase("","")+" pour te transmettre les salutations d'une personne nommée"+pchar.GenQuest.ShipWreck.Name+"Sais-tu qui c'est?"; // belamour gen
			link.l1.go = "ShipWreck_51";
		break;
		
		case "ShipWreck_51":
			dialog.text = "C'est dommage que je n'aie pas étranglé ce vaurien plus tôt. Eh bien, alors, je suppose que le moment est venu de payer pour ma bienveillance...";
			link.l1 = "En effet... Et le temps vient juste de s'écouler...";
			link.l1.go = "ShipWreck_52";
		break;
		
		case "ShipWreck_52":
			LAi_SetCurHPMax(NPChar);
			LAi_GetCharacterMaxEnergy(NPChar);			
			QuestAboardCabinDialogFree(); // важный метод
			LAi_group_SetRelation(LAI_GROUP_BRDENEMY, LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups(LAI_GROUP_BRDENEMY, LAI_GROUP_PLAYER, true);
			LAi_group_SetCheckFunction(LAI_GROUP_BRDENEMY, "ShipWreck_afterCabinFight");
			DialogExit();	
			AddDialogExitQuest("MainHeroFightModeOn");				
		break;

		case "ShipWreck_53":
			AddCharacterExpToSkill(pchar, "Leadership", 100);
			pchar.quest.ShipWreck_ShipSink.over = "yes";
			dialog.text = "Excellent travail, capitaine ! Tout comme convenu, alors ? Nous prenons le navire et vous prenez la cargaison ?";
			link.l1 = "Bien sûr. Prenez le navire et faites-en bon usage.";
			link.l1.go = "exit";

			NextDiag.TempNode = "ShipWreck_53_again";		
			AddDialogExitQuestFunction("ShipWreck_SetShipNew");
		break;
		
		case "ShipWreck_53_again":
			dialog.text = "Je vous salue, capitaine "+GetFullName(pchar)+".";
			link.l1 = "Alors, comment aimes-tu ton navire?";
			link.l1.go = "ShipWreck_53_again1";
		break;
		
		case "ShipWreck_53_again1":
			dialog.text = "Heh, ça grince et ça craque, tout comme moi. Je pense que nous n'avons pas beaucoup de temps à naviguer sur les mers hautes...";
			link.l1 = "Bonne chance, alors...";
			link.l1.go = "exit";
			NextDiag.TempNode = "ShipWreck_53_again";		
		break;
		// Генератор "Shipwrecked"
		
		// Генератор "State convicts"
		case "Convict_0End":
			DialogExit();
			pchar.GenQuest.Convict = "close";
			chrDisableReloadToLocation = false;
			ChangeCharacterComplexReputation(pchar,"nobility", -1);
			AddDialogExitQuestFunction("Convict_DialogDisable");
		break;
		
		case "Convict_Begin":					
			switch(sti(pchar.GenQuest.Convict.var))
			{
				case 0:
					dialog.text = "Capitaine, aidez-nous, je vous en prie, à trouver un navire ou une chaloupe, une tartane, n'importe quoi, cela importe peu. Nous sommes dans une telle situation que nous devons fuir cet endroit inhospitalier, mais nous ne pouvons pas nous montrer dans l'établissement.";
					link.l1 = "Et quelles sont donc ces circonstances-là?";
					link.l1.go = "Convict_11";
				break;
				case 1:
					dialog.text = "Capitaine, pourriez-vous nous prêter quelques centaines de pesos? Nous ne demanderions pas, mais nous sommes vraiment dans le besoin.";
					link.l1 = "Dans le besoin désespéré, dites-vous? Je parie que vous êtes juste à court de rhum et c'est sûrement un besoin désespéré.";
					link.l1.go = "Convict_12";			
				break;
				case 2:
					pchar.GenQuest.Convict.ToCity = FindColonyWithMayakExceptIsland(GetCharacterCurrentIslandId(pchar));	
					pchar.GenQuest.Convict.Mayak = GetMayakByCityName(pchar.GenQuest.Convict.ToCity);
					dialog.text = "Capitaine, pourriez-vous avoir l'amabilité de conduire notre humble compagnie jusqu'au phare de "+XI_ConvertString("Colony"+pchar.GenQuest.Convict.ToCity+"Gen")+".";
					link.l1 = "En te regardant, je ne dirais pas que tu es trop humble.";
					link.l1.go = "Convict_13";								
				break;
			}						
			link.l2 = LinkRandPhrase("Je ne fais pas l'aumône les vendredis.","Je n'ai pas le temps pour ces balivernes.","Je n'aide pas les gens étranges.");
			link.l2.go = "Convict_14";
			Convict_GetMineType();
			pchar.GenQuest.Convict.ShoreLocation = SelectQuestShoreLocation();
		break;
		
		case "Convict_11":
			dialog.text = "Nous sommes des fugitifs... de "+GetStrSmallRegister(XI_ConvertString("TypeDeMine"+pchar.GenQuest.Convict.MineType+"Ca"))+"Bientôt, l'ancien maître s'en apercevra... et alors nous sommes foutus, c'est certain.";
			if(GetFreeCrewQuantity(pchar) >= sti(pchar.GenQuest.Convict.ConvictQty))
			{
				link.l1 = "Alors, tu sais comment gérer les voiles ?";
				link.l1.go = "Convict_11_1";
			}	
			link.l2 = "Et avec quoi comptes-tu payer ?";
			link.l2.go = "Convict_11_2";
		break;
		
		case "Convict_12":
			dialog.text = "Ce n'est pas le moment pour nous de penser au rhum. Cela fait une semaine que nous avons échappé, maintenant nous nous cachons dans la jungle et mourons de faim.";
			if(sti(pchar.money) >= 3000)
			{
				link.l1 = "Eh bien, supposons que je puisse te donner de l'argent... et ensuite quoi ? Tu vas rester caché, jusqu'à ce qu'une patrouille te découvre finalement ?";
				link.l1.go = "Convict_12_1";		
				link.l2 = "D'accord, combien as-tu besoin ?";
				link.l2.go = "Convict_12_2";
			}	
			link.l3 = "Je n'ai qu'une courte conversation avec des gens comme toi, têtes sur le billot du bourreau, et c'est tout !";
			link.l3.go = "Convict_12_3";
		break;		
		
		case "Convict_12_1":
			if(hrand(1) == 0 && GetFreeCrewQuantity(pchar) >= sti(pchar.GenQuest.Convict.ConvictQty))
			{
				dialog.text = "Et que pouvons-nous faire d'autre ? Nous serions ravis de trouver un emploi de marins, mais étant donné que nous sommes des fugitifs, qui va nous embaucher ?";
				link.l1 = "Je t'engagerai si tu sais te débrouiller avec les voiles et si tu ne montres aucun signe de lâcheté.";
				link.l1.go = "Convict_12_1_1";
			}
			else
			{
				dialog.text = "Nous avons déjà conclu un accord avec les marins locaux. Pour sortir d'ici, il nous manque seulement trois mille.";
				link.l1 = "Eh bien, voici vos trois mille, si cela va vraiment vous aider.";
				link.l1.go = "Convict_12_1_2";
			}
			link.l2 = "Eh bien, je ne sais pas... Ce sont tes propres problemes, et je ne vais pas t'aider a les resoudre.";
			link.l2.go = "Convict_12_1_End"; // выход из локи с закрытием квеста
		break;
		
		case "Convict_12_1_1":
			pchar.GenQuest.Convict.PirateName = "l" + rand(GetNamesCount(NAMETYPE_NICK) - 1);
			dialog.text = "S'il vous plaît, capitaine, embauchez-nous, vous ne le regretterez sûrement pas ! Nous avions fait de la piraterie avec "+GetName(NAMETYPE_NICK,pchar.GenQuest.Convict.PirateName,NAME_ABL)+" en Adriatique, jusqu'à ce qu'il soit finalement pendu et nous, "+pchar.GenQuest.Convict.ConvictQty+" hommes, ont été bannis en ce lieu.";
			link.l1 = "D'accord. Il y a un endroit proche, connu sous le nom de "+XI_ConvertString(pchar.GenQuest.Convict.ShoreLocation)+"Vers minuit, je viendrai te chercher là-bas. J'espère bien que tu ne vas pas te perdre.";
			link.l1.go = "Convict_11_6";
			pchar.GenQuest.Convict = "ToShore";		
		break;

		case "Convict_12_1_2":
			addMoneyToCharacter(pchar, -3000);
			AddCharacterExpToSkill(pchar, "Leadership", 30);
			AddCharacterExpToSkill(pchar, "Commerce", 60);
			iTmp = hrand(3);
			if(iTmp <= 1)
			{
				dialog.text = "Bien sûr, cela va nous aider grandement ! Nous mettrons les voiles aujourd'hui, si le vent est favorable et que les pêcheurs ne nous déçoivent pas. Merci, capitaine, et que Dieu vous aide...";
				link.l1 = "Bonne chance à toi aussi.";
				link.l1.go = "exit";
				pchar.GenQuest.Convict = "close";
				AddDialogExitQuestFunction("Convict_DialogDisable");
				AddDialogExitQuest("OpenTheDoors");
			}
			if(iTmp == 2)
			{
				dialog.text = "Maintenant, c'est un coup de chance ! Nous n'espérions même pas récupérer l'argent aussi rapidement. Capitaine, permettez-moi de vous offrir un bibelot que nous avons pris à notre ancien patron. Peut-être vous portera-t-il chance, à vous aussi.";
				link.l1 = "Merci, c'est une chose decente, c'est sur. Bonne chance a toi.";
				link.l1.go = "exit";
				pchar.GenQuest.Convict = "close";
				GiveItem2Character(pchar, pchar.GenQuest.Convict.Item);
				AddDialogExitQuestFunction("Convict_DialogDisable");
				AddDialogExitQuest("OpenTheDoors");
				AddCharacterExpToSkill(pchar, "Fortune", 30);
			}
			if(iTmp == 3)
			{
				pchar.GenQuest.Find_Merchant.lastspeak_date = LastSpeakDate();
				GenerateMerchant();
				makeref(MerPrm, MerchantParam);
				dialog.text = "Maintenant, voilà un homme généreux qui n'a pas peur de dépenser sa monnaie, parce qu'il sait comment la gagner !\nLa nuit dernière, nous avons vu les contrebandiers locaux charger "+MerPrm.QuestGoodsIdx+". Il faisait noir, mais nous avons réussi à discerner le nom du navire sur le côté de l'un des bateaux, '"+MerPrm.ShipName+"... et ce navire navigue sous le pavillon de "+MerPrm.nation+"Peut-être que tu trouveras cette information utile, hé-hé.";			
				link.l1 = "Hmm... Eh bien, peut-être que je le ferai. Adieu à vous, pisteurs.";
				link.l1.go = "exit";
				pchar.GenQuest.Convict = "close";
				AddQuestRecord("Convict", "7");
				AddQuestUserData("Convict", "sShipName", MerPrm.ShipName);
				AddQuestUserData("Convict", "sGoodName", MerPrm.QuestGoodsIdx);
				CloseQuestHeader("Convict");
				SetFunctionExitFromLocationCondition("Convict_LocExit", pchar.location, false);
				AddDialogExitQuestFunction("Convict_DialogDisable");			
				AddDialogExitQuest("OpenTheDoors");
				AddCharacterExpToSkill(pchar, "Sneak", 30);
			}
		break;
		
		case "Convict_12_2":
			dialog.text = "Oh là là, nous ne sommes pas en position de faire des exigences. Tout ce que tu peux épargner, nous serons reconnaissants pour n'importe quoi.";
			link.l1 = "300 pesos.";
			link.l1.go = "Convict_12_2_1";
			link.l2 = "1000 pesos.";
			link.l2.go = "Convict_12_2_2";
			link.l3 = "3000 pesos.";
			link.l3.go = "Convict_12_2_3";
		break;
		
		case "Convict_12_2_1":
			addMoneyToCharacter(pchar, -300);
			AddCharacterExpToSkill(pchar, "Leadership", 30);
			AddCharacterExpToSkill(pchar, "Commerce", 20);
			dialog.text = "Merci, capitaine, et que Dieu veille sur vous...";
			link.l1 = "Bonne chance à toi aussi.";
			link.l1.go = "exit";
			pchar.GenQuest.Convict = "close";
			AddDialogExitQuestFunction("Convict_DialogDisable");
			AddDialogExitQuest("OpenTheDoors");
		break;

		case "Convict_12_2_2":
			addMoneyToCharacter(pchar, -1000);
			AddCharacterExpToSkill(pchar, "Leadership", 30);
			AddCharacterExpToSkill(pchar, "Commerce", 40);
			if(hrand(1) == 0)
			{
				GiveItem2Character(pchar, pchar.GenQuest.Convict.Item);
				dialog.text = "Alors, ça c'est un coup de chance ! Nous n'espérions même pas obtenir l'argent si vite. Capitaine, permettez-moi de vous offrir un bibelot que nous avons pris à notre ancien patron. Peut-être vous portera-t-il aussi bonheur.";
				link.l1 = "Merci, c'est une chose décente, c'est sûr. Bonne chance à toi.";
				AddCharacterExpToSkill(pchar, SKILL_FORTUNE, 20);
			}
			else
			{
				dialog.text = "Merci, capitaine, et que Dieu veille sur vous...";
				link.l1 = "Bonne chance à vous aussi.";
			}
			link.l1.go = "exit";
			pchar.GenQuest.Convict = "close";
			AddDialogExitQuestFunction("Convict_DialogDisable");
			AddDialogExitQuest("OpenTheDoors");
		break;

		case "Convict_12_2_3":
			addMoneyToCharacter(pchar, -3000);
			AddCharacterExpToSkill(pchar, "Leadership", 30);
			AddCharacterExpToSkill(pchar, "Commerce", 60);
			if(hrand(1) == 0)
			{
				dialog.text = "Alors là, c'est un coup de chance ! Nous n'espérions même pas obtenir l'argent si rapidement. Capitaine, permettez-moi de vous offrir un bibelot que nous avons pris à notre ancien patron. Peut-être vous portera-t-il aussi bonheur.";
				link.l1 = "Merci, c'est une chose décente, c'est sûr. Bonne chance à toi.";
				link.l1.go = "exit";
				pchar.GenQuest.Convict = "close";
				GiveItem2Character(pchar, pchar.GenQuest.Convict.Item);
				AddDialogExitQuestFunction("Convict_DialogDisable");
				AddDialogExitQuest("OpenTheDoors");
				AddCharacterExpToSkill(pchar, "Fortune", 30);
			}
			else
			{
				pchar.GenQuest.Find_Merchant.lastspeak_date = LastSpeakDate();
				GenerateMerchant();
				makeref(MerPrm, MerchantParam);
				dialog.text = "Maintenant, voilà un homme généreux qui n'hésite pas à dépenser sa piastre, car il sait comment la gagner !\nLa nuit dernière, nous avons vu les contrebandiers locaux charger "+MerPrm.QuestGoodsIdx+". Il faisait sombre, mais nous avons réussi à discerner le nom du navire sur le côté de l'un des bateaux '"+MerPrm.ShipName+"... et ce navire navigue sous le pavillon de "+MerPrm.nation+"Peut-être que vous trouverez cette information utile, hé-hé.";
				link.l1 = "Hmm... Eh bien, peut-être que je le ferai. Adieu à vous, pisteurs.";
				link.l1.go = "exit";
				pchar.GenQuest.Convict = "close";
				AddQuestRecord("Convict", "7");
				AddQuestUserData("Convict", "sShipName", MerPrm.ShipName);
				AddQuestUserData("Convict", "sGoodName", MerPrm.QuestGoodsIdx);				
				CloseQuestHeader("Convict");
				SetFunctionExitFromLocationCondition("Convict_LocExit", pchar.location, false);
				AddDialogExitQuestFunction("Convict_DialogDisable");
				AddDialogExitQuest("OpenTheDoors");
				AddCharacterExpToSkill(pchar, "Sneak", 30);
			}			
		break;
		
		case "Convict_12_1_End":
			ChangeCharacterComplexReputation(pchar,"nobility", -2);
			OfficersReaction("bad");	
			pchar.GenQuest.Convict = "close";
			DialogExit();
			AddDialogExitQuestFunction("Convict_DialogDisable");
			AddDialogExitQuest("OpenTheDoors");
		break;
		
		case "Convict_12_3":
			if(hrand(1) == 0)
			{
				dialog.text = "Ne nous condamnez pas, capitaine ! Nous avons un bibelot décent, acceptez-le, je vous prie, comme rançon et laissez-nous partir...";
				link.l1 = "Donne-le, alors, et fous le camp, tant que tu le peux encore.";
				link.l1.go = "exit";
				pchar.GenQuest.Convict = "close";
				GiveItem2Character(pchar, pchar.GenQuest.Convict.Item);
				AddDialogExitQuestFunction("Convict_DialogDisable");
				AddDialogExitQuest("OpenTheDoors");
			}
			else
			{
				dialog.text = "Maintenant, nous n'avons pas d'autre choix, un homme ne mourra pas deux fois. À la dernière bataille, garçons !";
				link.l1 = "Ah, c'est une autre histoire !";
				link.l1.go = "Convict_Fight";
			}			
		break;
		
		case "Convict_13":
			dialog.text = "Eh bien, nous ne sommes certainement pas des saints, mais nous ne cherchons pas querelle pour rien... Nous sommes des fugitifs, et nous devons sortir d'ici dès que possible.";
			link.l1 = "As-tu quelque chose pour payer le passage ?";
			link.l1.go = "Convict_13_1";		
			link.l2 = "Oh, je vois... Non, je ne ternirai pas ma réputation à cause de toi. Adieu.";
			link.l2.go = "Convict_11_5";
		break;
		
		case "Convict_11_1":
			pchar.GenQuest.Convict.PirateName = "l" + rand(GetNamesCount(NAMETYPE_NICK) - 1);
			dialog.text = "Bien sûr ! Nous sommes bien habitués aux abordages et tout ça. Pendant presque deux ans, nous et feu "+GetName(NAMETYPE_NICK,pchar.GenQuest.Convict.PirateName,NAME_ABL)+" terrorisaient les marchands locaux, mais hélas ! Il fut pendu, et "+pchar.GenQuest.Convict.ConvictQty+" des hommes d'entre nous furent condamnés aux travaux forcés.";
			link.l1 = "Que dirais-tu de rejoindre mon équipage ? Je suis généreux"+GetSexPhrase("","")+", mais je ne te promets pas une vie paisible.";
			link.l1.go = "Convict_11_3";			
		break;
		
		case "Convict_11_2":
			dialog.text = "Oui, nous avons attrape quelque chose avec "+GetStrSmallRegister(XI_ConvertString("TypeDeMine"+pchar.GenQuest.Convict.MineType+"Gen"))+", donc nous pouvons payer le double. ALORS je suppose que le prix est convenu. Et n'osez pas amener des gardes. Nous ne pardonnons pas la trahison..."; // belamour gen
			link.l1 = "Très bien, attends-moi sur la plage "+XI_ConvertString(pchar.GenQuest.Convict.ShoreLocation+"Gen")+". Plus proche de minuit, il y aura un bateau pour toi ... Et je ne veux voir aucun tour !"; // belamour gen
			link.l1.go = "Convict_11_4";
			link.l2 = "Non, mes amis. Que se passera-t-il si je vous donne le navire et que vous me poignardez dans le dos ? Non, je ne vous aiderai pas dans cette affaire.";
			link.l2.go = "Convict_11_5";
		break;
		
		case "Convict_11_3":
			dialog.text = "Avec grand plaisir, "+GetSexPhrase("monsieur","mademoiselle")+" capitaine. Nous sommes bien familiers avec cela, et nous ne serons certainement pas admis dans la Marine avec de telles recommandations de toute façon, hé-hé.";
			link.l1 = "D'accord. Il y a un endroit tout proche, connu sous le nom de "+XI_ConvertString(pchar.GenQuest.Convict.ShoreLocation)+"Après minuit, je viendrai te chercher là-bas. J'espère que tu ne vas pas te perdre.";
			link.l1.go = "Convict_11_6";
		break;
		
		case "Convict_11_4":
			dialog.text = "Mais, "+GetSexPhrase("Monsieur","mademoiselle")+" capitaine, prenons-nous encore un plus grand risque ? Et si vous décidez de nous livrer au commandant ?";
			link.l1 = "C'est vrai... D'accord, si je ne suis pas là au lever du jour, alors l'affaire est annulée.";
			link.l1.go = "Convict_11_7";			
		break;
		
		case "Convict_11_5":
			if(makeint(pchar.reputation.nobility) < 11 || makeint(pchar.reputation.nobility) > 79) //макс. репутатция 90
			{
				dialog.text = "Oh, capitaine, nous comptions sur vous...";
				link.l1 = "Pas de souci. Si tu as de l'argent, tu trouveras un passage. Adieu.";
				link.l1.go = "exit";
				pchar.GenQuest.Convict = "close";
				ChangeCharacterComplexReputation(pchar,"nobility", -2);
				AddDialogExitQuestFunction("Convict_DialogDisable");
				AddDialogExitQuest("OpenTheDoors");
			}
			else
			{
				dialog.text = "Vous êtes un malin, capitaine, comme je le vois. Je suis sûr que vous allez courir directement chez le commandant, n'est-ce pas? Et vous pensez vous en sortir comme ça?";
				link.l1 = "Et tu comptes m'arrêter, à ce que je vois?! Alors tu auras ce que tu mérites!";
				link.l1.go = "Convict_Fight";
				pchar.GenQuest.Convict = "fight";
			}	
		break;
		
		case "Convict_11_6":
			pchar.GenQuest.Convict = "ToShore";
			ReOpenQuestHeader("Convict");
			AddQuestRecord("Convict", "1");
			AddQuestUserData("Convict", "sSex", GetSexPhrase("",""));
			AddQuestUserData("Convict", "sIslandType", XI_ConvertString(GetIslandByCityName(pchar.GenQuest.Convict.city) + "Gen"));
			AddQuestUserData("Convict", "sConvictNum", Convict_GetStringNum(sti(pchar.GenQuest.Convict.ConvictQty))); // belamour gen колво прописью
			AddQuestUserData("Convict", "sShoreName", XI_ConvertString(pchar.GenQuest.Convict.ShoreLocation + "Gen"));	// belamour gen	
			SetFunctionTimerCondition("Convict_SetTimerMeet", 0, 0, 1, false);	
			locations[FindLocation(pchar.GenQuest.Convict.ShoreLocation)].DisableEncounters = true;			
			DialogExit();
			AddDialogExitQuestFunction("Convict_DialogDisable");
			AddDialogExitQuest("OpenTheDoors");
		break;
		
		case "Convict_11_7":
			pchar.GenQuest.Convict = "GetShip";
			ReOpenQuestHeader("Convict");
			AddQuestRecord("Convict", "2");		
			AddQuestUserData("Convict", "sSex", GetSexPhrase("",""));		
			AddQuestUserData("Convict", "sIslandType", XI_ConvertString(GetIslandByCityName(pchar.GenQuest.Convict.city) + "Gen"));
			AddQuestUserData("Convict", "sShoreName", XI_ConvertString(pchar.GenQuest.Convict.ShoreLocation + "Acc"));					
			SetFunctionTimerCondition("Convict_SetTimerMeet", 0, 0, 1, false);
			locations[FindLocation(pchar.GenQuest.Convict.ShoreLocation)].DisableEncounters = true;			
			DialogExit();		
			AddDialogExitQuestFunction("Convict_DialogDisable");		
			AddDialogExitQuest("OpenTheDoors");
		break;
		
		case "Convict_13_1":
			pchar.GenQuest.Convict.Sum = (sti(pchar.rank)+10)*100+1000;
			dialog.text = "Il y a quelque chose. Nous avons fouillé dans les coffres de notre patron, mais ensuite il y a eu une embrouille à ce sujet, et nous avons dû nous frayer un chemin en combattant. Seulement "+PChar.GenQuest.Convict.ConvictQty+" les hommes ont réussi à survivre.";
			link.l1 = "Compte tenu des circonstances, je ne vous offrirai pas le passage à moins de "+FindRussianMoneyString(sti(pchar.GenQuest.Convict.Sum))+"pesos par personne.";
			link.l1.go = "Convict_13_2";
			if(GetFreeCrewQuantity(pchar) >= sti(pchar.GenQuest.Convict.ConvictQty) && GetPassengersQuantity(pchar) < PASSENGERS_MAX)
			{
				link.l2 = "Je vois que vous n'êtes pas des lâches. Voulez-vous rejoindre mon équipage ?";
				link.l2.go = "Convict_13_3";
			}
		break;
		
		case "Convict_13_2":
			dialog.text = "Et avons-nous le choix ? Très bien, "+FindRussianMoneyString(sti(pchar.GenQuest.Convict.Sum))+"...";
			link.l1 = "Alors va à "+XI_ConvertString(pchar.GenQuest.Convict.ShoreLocation+"ça")+". Je t'enverrai un canot après minuit."; // belamour gen 
			link.l1.go = "Convict_13_4";
			pchar.GenQuest.Convict = "ToMayak";
			pchar.GenQuest.Convict.Sum = sti(pchar.GenQuest.Convict.Sum) * sti(pchar.GenQuest.Convict.ConvictQty);
		break;
		
		case "Convict_13_3":
			pchar.GenQuest.Convict.PirateName = "l" + rand(GetNamesCount(NAMETYPE_NICK) - 1);
			dialog.text = "Et pourquoi pas? Nous connaissons ce truc, nous avons été pirates avec "+GetName(NAMETYPE_NICK,pchar.GenQuest.Convict.PirateName,NAME_ABL)+" dans "+RandPhraseSimple("Gibraltar","Canal anglais")+" avant que nous ne soyons coincés ici.";
			link.l1 = "D'accord. Il y a un endroit à proximité, connu sous le nom de "+XI_ConvertString(pchar.GenQuest.Convict.ShoreLocation)+"Vers minuit, je viendrai te chercher là-bas. J'espère que tu ne vas pas te perdre.";
			link.l1.go = "Convict_11_6";
			pchar.GenQuest.Convict = "ToShore";
		break;
		
		case "Convict_13_4":
			ReOpenQuestHeader("Convict");
			AddQuestRecord("Convict", "8");					
			AddQuestUserData("Convict", "sSex", GetSexPhrase("",""));		
			AddQuestUserData("Convict", "sIslandType", XI_ConvertString(GetIslandByCityName(pchar.GenQuest.Convict.city) + "Gen"));
			AddQuestUserData("Convict", "sConvictNum", Convict_GetStringNum(sti(pchar.GenQuest.Convict.ConvictQty))); // belamour gen колво прописью
			AddQuestUserData("Convict", "sCity", XI_ConvertString("Colony" + pchar.GenQuest.Convict.ToCity + "Gen"));
			AddQuestUserData("Convict", "sSum", pchar.GenQuest.Convict.Sum);
			AddQuestUserData("Convict", "sShoreName", XI_ConvertString(pchar.GenQuest.Convict.ShoreLocation + "Dat"));	// belamour gen	 	
			SetFunctionTimerCondition("Convict_SetTimerMeet", 0, 0, 1, false);
			locations[FindLocation(pchar.GenQuest.Convict.ShoreLocation)].DisableEncounters = true;			
			DialogExit();
			AddDialogExitQuestFunction("Convict_DialogDisable");
			AddDialogExitQuest("OpenTheDoors");
		break;
				
		case "Convict_14":
			dialog.text = RandPhraseSimple(RandPhraseSimple("Eh, capitaine, vous avez aussi été pauvre autrefois, vous aviez les poches vides. Et maintenant vous méprisez le petit peuple comme nous."),RandPhraseSimple("Heh, les gens deviennent vraiment trop égoïstes de nos jours. Tu vis comme si tu avais encore deux siècles devant toi.","Oh, je vois que tu viens d'arriver d'Europe, tu n'as pas encore senti la puanteur de notre dépotoir tropical."));
			link.l1 = LinkRandPhrase("Essayes-tu de me faire honte ? Je vais raccourcir ta langue de quelques pouces !","Tu me menaces ? Accroche-toi à ton chapeau maintenant !","Es-tu un philosophe ou quoi ? Je vais te remettre les idées en place !");
			link.l1.go = "Convict_Fight";	
			pchar.GenQuest.Convict = "fight";
		break;
		
		case "Convict_Fight":
			LAi_SetPlayerType(pchar);
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);	 
			LAi_LockFightMode(pchar, false); 
			LAi_SetFightMode(pchar, true);
			chrDisableReloadToLocation = true;
			iTemp = sti(PChar.GenQuest.Convict.ConvictQty);
			for(i = 0; i < iTemp; i++)
			{
				rChar = CharacterFromID("Convict_" + i);
				DeleteAttribute(rChar, "City");
				LAi_SetWarriorType(rChar);
				LAi_group_MoveCharacter(rChar, "ConvictGroup");
				LAi_SetImmortal(rChar, false);
			}
			LAi_group_SetRelation("ConvictGroup", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("ConvictGroup", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("ConvictGroup", "OpenTheDoors"); 
			DialogExit();	
			AddDialogExitQuest("MainHeroFightModeOn");		
		break;
		
		case "Convict_15":
			dialog.text = LinkRandPhrase("Alors, capitaine ? Nous avez-vous apporté un navire ?","Salutations, capitaine. Alors, qu'en est-il de notre accord ?","Bonjour, capitaine. Nous commencions déjà à nous inquiéter. Tout s'est bien passé, je suppose ?");
			if(Convict_CheckShipType(SHIP_TARTANE) || Convict_CheckShipType(SHIP_WAR_TARTANE))
			{
				link.l1 = "Ouais, voici ta barcasse. Et n'oublie pas le paiement. J'ai payé "+pchar.GenQuest.Convict.ShipPrice+"  pièces pour ça, donc tu me dois "+sti(pchar.GenQuest.Convict.ShipPrice)* 2+", comme nous en étions convenus.";
				link.l1.go = "Convict_15_1";
			}	
			link.l2 = "Non, j'ai changé d'avis. Trouve-toi un autre assistant. Adieu...";
			link.l2.go = "Convict_15_2";
		break;
		
		case "Convict_15_1":
			switch(sti(pchar.GenQuest.Convict.variant))
			{
				case 1:
					dialog.text = "Mais bien sûr ! Ils ont pris notre liberté, mais pas notre conscience ! Veuillez accepter votre argent avec notre gratitude sans bornes. Vous nous avez vraiment aidés. Cela vous dérange-t-il si nous vous payons en lingots d'argent ?";
					link.l1 = "Bien sûr que non. Bonne chance à toi dans ton voyage. Et prie pour que je ne te croise pas en haute mer, je t'enverrai par le fond en un rien de temps.";
					link.l1.go = "Convict_15_1_1End";
					AddCharacterExpToSkill(pchar, "Leadership", 30);
					AddCharacterExpToSkill(pchar, "Commerce", 30);
					TakeNItems(pchar, "jewelry6", makeint(sti(pchar.GenQuest.Convict.ShipPrice)/50));
				break;
				case 2:
					dialog.text = "Capitaine, vous savez, nous pensions que l'argent n'est vraiment pas si important dans la vie. Et, franchement, nous en avons bien plus besoin que vous en ce moment. Mais nous avons une chose que nous avions volée à notre ancien patron. Peut-être que cela vous intéresserait bien plus que de l'or. Voulez-vous y jeter un œil ?...";
					link.l1 = "Oui, tu as raison. C'est une chose merveilleuse, en effet. D'accord, très bien, marché conclu, merci et adieu.";
					link.l1.go = "Convict_15_1_2End";
					AddCharacterExpToSkill(pchar, "Leadership", 30);
					AddCharacterExpToSkill(pchar, "Fortune", 30);
					GiveItem2Character(pchar, pchar.GenQuest.Convict.Item);
				break;
				case 3:
					pchar.GenQuest.Convict = "FightInShore";
					SetFunctionExitFromLocationCondition("Convict_LocExit", pchar.location, false);				
					dialog.text = "Pourquoi diable auriez-vous besoin de tant d'argent, capitaine ? Vous êtes riche, de toute façon, et nous sommes condamnés si nous n'obtenons pas ce navire. Alors... nous allons simplement vous le prendre. Pas de rancune.";
					link.l1 = "Ce fut ta dernière erreur. Sans navire, tu aurais encore pu t'enfuir à la nage, mais à présent, tu flotteras ou sombreras.";
					link.l1.go = "Convict_Fight";
					AddCharacterExpToSkill(pchar, "Leadership", 30);
					AddCharacterExpToSkill(pchar, "Sneak", 30);
				break;
			}
		break;
	
		case "Convict_15_1_1End":
			AddQuestRecord("Convict", "4");
			AddQuestUserData("Convict", "sSex", GetSexPhrase("",""));
			AddQuestUserData("Convict", "sShoreName", XI_ConvertString(pchar.GenQuest.Convict.ShoreLocation + "Gen")); // belamour gen
			CloseQuestHeader("Convict");
			AddDialogExitQuestFunction("Convict_DialogDisable");
			AddDialogExitQuestFunction("Convict_SetConvictToShip");
			AddDialogExitQuest("OpenTheDoors");
			DialogExit();
		break;
	
		case "Convict_15_1_2End":
			AddQuestRecord("Convict", "5");
			AddQuestUserData("Convict", "sSex", GetSexPhrase("",""));
			AddQuestUserData("Convict", "sShoreName", XI_ConvertString(pchar.GenQuest.Convict.ShoreLocation + "Gen")); // belamour gen
			CloseQuestHeader("Convict");
			AddDialogExitQuestFunction("Convict_DialogDisable");
			AddDialogExitQuestFunction("Convict_SetConvictToShip");
			AddDialogExitQuest("OpenTheDoors");
			DialogExit();
		break;	
	
		case "Convict_15_2":
			AddQuestRecord("Convict", "3");
			AddQuestUserData("Convict", "sSex", GetSexPhrase("",""));
			CloseQuestHeader("Convict");
			for(i = 0; i < sti(pchar.GenQuest.Convict.ConvictQty); i++)
			{
				sld = CharacterFromID("Convict_" + i);
				sld.LifeDay = 0;
			}	
			ChangeCharacterComplexReputation(pchar,"nobility", -2);	
			LAi_group_Delete("ConvictGroup");
			DeleteAttribute(pchar, "GenQuest.Convict");
			DialogExit();
			AddDialogExitQuestFunction("Convict_DialogDisable");
			AddDialogExitQuest("OpenTheDoors");
		break;
		
		case "Convict_16":
			dialog.text = RandPhraseSimple("Alors, capitaine ? Peut-on commencer à nous charger ?","Enfin ! Nous commencions déjà à nous inquiéter, nous pensions que tu avais changé d'avis.");
			link.l1 = "Désolé, j'ai changé de plan. Tu devras chercher un autre capitaine maintenant.";
			link.l1.go = "Convict_16_1";
			if(pchar.GenQuest.Convict == "ToMayak")
			{
				link.l2 = "Chargez dans le bateau, je n'ai pas beaucoup de temps.";
				link.l2.go = "Convict_16_2";			
			}			
			if(pchar.GenQuest.Convict == "ToShore" && GetFreeCrewQuantity(pchar) >= sti(pchar.GenQuest.Convict.ConvictQty))
			{
				link.l2 = "Montez dans le bateau, je n'ai pas beaucoup de temps.";
				link.l2.go = "Convict_16_2";			
			}			
		break;
		
		case "Convict_16_1":
			if(rand(1) == 0)
			{
				dialog.text = "Que le diable t'emporte ! Tu as sûrement déjà envoyé une patrouille à notre poursuite ?! Tu ne t'en tireras pas comme ça !";
				link.l1 = "De quoi parles-tu ?! Tu veux mourir ou quoi ?!";
				link.l1.go = "Convict_Fight";
				pchar.GenQuest.Convict = "ShoreFight";
				SetFunctionExitFromLocationCondition("Convict_LocExit", pchar.location, false);
			}
			else
			{
				dialog.text = "Capitaine "+GetSexPhrase(", es-tu un homme de parole ou quoi ?","?")+" Ou es-tu juste un putain de bavard...";
				link.l1 = "Tu ferais mieux de surveiller ta langue...";
				link.l1.go = "Convict_16_3";
			}
		break;
		
		case "Convict_16_2":
			if(pchar.GenQuest.Convict == "ToShore")
			{
				AddCharacterExpToSkill(pchar, "Leadership", 30);
				AddCharacterCrew(pchar, sti(pchar.GenQuest.Convict.ConvictQty));
				OfficersReaction("bad");
				pchar.GenQuest.Convict = "close";
				AddQuestRecord("Convict", "10");
				CloseQuestHeader("Convict");				
				SetFunctionExitFromLocationCondition("Convict_LocExit", pchar.location, false);
			}
			if(pchar.GenQuest.Convict == "ToMayak")
			{
				AddQuestRecord("Convict", "10");
				sld = characterFromId("Convict_0");
				AddPassenger(pchar, sld, false);
				SetCharacterRemovable(sld, false); 
				SetFunctionExitFromLocationCondition("Convict_LocExit", pchar.location, false);
				SetFunctionLocationCondition("Convict_OnMayak", pchar.GenQuest.Convict.Mayak, true);
				locations[FindLocation(pchar.GenQuest.Convict.Mayak)].DisableEncounters = true;			
			}
			DialogExit();
			AddDialogExitQuestFunction("Convict_DialogDisable");
			AddDialogExitQuest("OpenTheDoors");
		break;
		
		case "Convict_16_3":
			ChangeCharacterComplexReputation(pchar,"nobility", -2);
			OfficersReaction("bad");
			pchar.GenQuest.Convict = "close";
			AddQuestRecord("Convict", "3");
			AddQuestUserData("Convict", "sSex", GetSexPhrase("",""));
			CloseQuestHeader("Convict");				
			SetFunctionExitFromLocationCondition("Convict_LocExit", pchar.location, false);
			AddDialogExitQuestFunction("Convict_DialogDisable");			
			DialogExit();
			AddDialogExitQuest("OpenTheDoors");
		break;
						
		case "Convict_17":
			dialog.text = LinkRandPhrase("Oh, merci, "+GetSexPhrase("homme bon","belle demoiselle")+".","Merci, capitaine, vous m'avez vraiment éloigné de la corde.","Beaucoup apprecie un si beau voyage.");
			link.l1 = LinkRandPhrase("Tout cela est bien beau, mais j'attends l'argent.","Il est temps de payer, tu sais.","Espèces sonnantes et trébuchantes, comme convenu.");
			link.l1.go = "Convict_17_1";
		break;
		
		case "Convict_17_1":
			switch(sti(pchar.GenQuest.Convict.variant))
			{
				case 1:
					dialog.text = "Bien sûr, quelles questions ! Voici votre argent en lingots d'or et veuillez accepter notre plus sincère gratitude.";
					link.l1 = "Bonne chance à toi aussi. Adieu.";
					link.l1.go = "Convict_17_1_1End";
					AddCharacterExpToSkill(pchar, "Sailing", 80);
					AddCharacterExpToSkill(pchar, "Commerce", 80);
					TakeNItems(pchar, "jewelry5", makeint(sti(pchar.GenQuest.Convict.Sum)/200));
					break;
				case 2:
					dialog.text = "Capitaine, vous savez, nous pensions que l'argent n'est vraiment pas si important dans la vie. Et, franchement, nous en avons bien plus besoin que vous à ce stade. Mais nous avons une chose que nous avons volée à notre ancien patron. Peut-être que cela vous intéresserait bien plus que de l'or. Voulez-vous y jeter un œil ?...";
					link.l1 = "Oui, tu as raison. C'est une chose merveilleuse, en effet. Bon d'accord, marché conclu, merci et adieu.";
					link.l1.go = "Convict_17_1_2End";
					AddCharacterExpToSkill(pchar, "Sailing", 80);
					AddCharacterExpToSkill(pchar, "Fortune", 80);
					GiveItem2Character(pchar, pchar.GenQuest.Convict.Item);
					break;
				case 3:
					dialog.text = "Pourquoi as-tu besoin de tant d'argent ? Tu es riche de toute façon. Tu nous as aidés, nous t'aiderons une autre fois.";
					link.l1 = "Il n'y aura pas une telle occasion. Dites vos prières, canailles, je ne tolère pas les dettes.";
					link.l1.go = "Convict_Fight";
					pchar.GenQuest.Convict = "MayakFight";
					SetFunctionExitFromLocationCondition("Convict_LocExit", pchar.location, false);				
					AddCharacterExpToSkill(pchar, "Sailing", 80);
					AddCharacterExpToSkill(pchar, "Sneak", 80);			
					break;
			}
		break;
		
		
		case "Convict_17_1_1End":
			AddQuestRecord("Convict", "11");
			AddQuestUserData("Convict", "sSex", GetSexPhrase("",""));
			AddQuestUserData("Convict", "sMayak", XI_ConvertString(pchar.GenQuest.Convict.Mayak + "Dat"));	//belamour gen			
			AddQuestUserData("Convict", "sSum", makeint(pchar.GenQuest.Convict.Sum));
			CloseQuestHeader("Convict");
			pchar.GenQuest.Convict = "close";
			SetFunctionExitFromLocationCondition("Convict_LocExit", pchar.location, false);
			DialogExit();
			AddDialogExitQuest("OpenTheDoors");
		break;
		
		case "Convict_17_1_2End":
			AddQuestRecord("Convict", "12");
			AddQuestUserData("Convict", "sSex", GetSexPhrase("",""));
			AddQuestUserData("Convict", "sMayak", XI_ConvertString(pchar.GenQuest.Convict.Mayak + "Dat"));	// belamour gen	
			CloseQuestHeader("Convict");
			pchar.GenQuest.Convict = "close";
			SetFunctionExitFromLocationCondition("Convict_LocExit", pchar.location, false);
			DialogExit();
			AddDialogExitQuest("OpenTheDoors");
		break;		
		// <-- Генератор "State convicts"
		
		// Генератор "A reason to hurry" -->
		// Встреча с ОЗГ на берегу
		case "ReasonToFast_Hunter1":
			dialog.text = "J'ai été envoyé ici par "+GetName(NAMETYPE_MAIN,pchar.questTemp.ReasonToFast.p3,NAME_NOM)+" lui-même...";
			link.l1 = GetName(NAMETYPE_MAIN,pchar.questTemp.ReasonToFast.p3,NAME_NOM)+" t'attend déjà avec une réponse depuis quelques heures. Il m'a envoyé immédiatement après toi.";
			link.l1.go = "ReasonToFast_Hunter4";
		break;
		
		case "ReasonToFast_Hunter2":
			dialog.text = "Je te suis à la trace depuis un bon moment, mais tu es juste trop rapide.";
			link.l1 = "Et alors ?";
			link.l1.go = "ReasonToFast_Hunter6";		
		break;
		
		case "ReasonToFast_Hunter3":
			dialog.text = "Mieux vaut me dire combien le gouverneur paie ses subalternes ?";
			link.l1 = "Sacrebleu !";
			link.l1.go = "ReasonToFast_Fight";		
		break;
		
		case "ReasonToFast_Hunter4":
			dialog.text = "Je n'ai pas bu ! Je cherchais le contremaître...";
			link.l1 = "Va maintenant... Je te dirai "+GetName(NAMETYPE_MAIN,pchar.questTemp.ReasonToFast.p3,NAME_DAT)+", que vous étiez perdu dans la jungle.";
			link.l1.go = "ReasonToFast_Hunter5";		
			AddQuestRecord("ReasonToFast", "5");
			AddQuestUserData("ReasonToFast", "sName", GetName( NAMETYPE_MAIN, pchar.questTemp.ReasonToFast.p3, NAME_GEN));
		break;
		
		case "ReasonToFast_Hunter5":
			LAi_SetPlayerType(pchar);
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			AddDialogExitQuest("ReasonToFast_HunterGoOut");
		break;
		
		case "ReasonToFast_Hunter6":
			pchar.questTemp.ReasonToFast = "MeetHunterFail";
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			AddDialogExitQuest("ReasonToFast_PatrolAngry");
		break;
		
		case "ReasonToFast_Fight":
			LAi_SetPlayerType(pchar);
			pchar.questTemp.ReasonToFast = "PatrolAngry";
			pchar.questTemp.ReasonToFast.relation = GetNationRelation2MainCharacter(sti(pchar.questTemp.ReasonToFast.GuardNation));
			SetNationRelation2MainCharacter(sti(pchar.questTemp.ReasonToFast.GuardNation), RELATION_ENEMY); 
			pchar.GenQuest.HunterScore2Pause = 1; //НЗГ не начисляются
			pchar.GenQuest.ReputationNotChange = 1; //репутацию не менять
			sTemp = "Patrol" + pchar.questTemp.ReasonToFast.LocIdx + "_";
			sGroup = "PatrolGroup_" + pchar.questTemp.ReasonToFast.LocIdx;
			LAi_LocationFightDisable(&locations[FindLocation(pchar.questTemp.ReasonToFast.PatrolLocation)], false);	
			iTemp = sti(pchar.questTemp.ReasonToFast.PatrolNum);
			chrDisableReloadToLocation = true;
			rChar = CharacterFromID("ReasonToFast_Hunter");
			LAi_SetWarriorType(rChar);
			LAi_group_MoveCharacter(rChar, sGroup);
			for(i = 0; i < iTemp; i++)
			{
				rChar = CharacterFromID(sTemp + i);
				LAi_SetWarriorType(rChar);
				LAi_group_MoveCharacter(rChar, sGroup);
			}			
			LAi_group_SetRelation(sGroup, LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups(sGroup, LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck(sGroup, "OpenTheDoors"); 
			LAi_group_SetCheck(sGroup, "ReasonToFast_PatrolDied");
			DialogExit();	
			AddDialogExitQuest("MainHeroFightModeOn");		
		break;
		
		// бой с кэпом пиратского корабля
		case "ReasonToFast_FightCap": 
			dialog.text = "Et tu es un malin. Prie Dieu pour que tes astuces ne soient pas découvertes par "+GetName(NAMETYPE_MAIN,pchar.questTemp.ReasonToFast.p3,NAME_NOM)+".";
			link.l1 = "Il ne saura pas si tu ne lui dis pas... Et tu ne le feras pas, n'est-ce pas ?";
			link.l1.go = "ReasonToFast_FightCap_1";
		break;
		
		case "ReasonToFast_FightCap_1":
			dialog.text = "Pourquoi ? Assurément, je le ferai, et avec grand plaisir !";
			link.l1 = "Il te pendra de toute façon pour cette folie. Alors ne perdons pas de temps, et je t'aiderai à échapper à la potence.";
			link.l1.go = "ReasonToFast_FightCap_2";
		break;
		
		case "ReasonToFast_FightCap_2":
			dialog.text = "Hmm... Et comment comptes-tu faire cela ?";
			link.l1 = "Je te tuerai moi-même...";
			link.l1.go = "ReasonToFast_FightCap_Last";
		break;
		
		case "ReasonToFast_FightCap_Last":
			LAi_SetCurHPMax(NPChar);
			LAi_GetCharacterMaxEnergy(NPChar);
			QuestAboardCabinDialogExitWithBattle(""); 
			DialogExit();	
			AddDialogExitQuest("MainHeroFightModeOn");		
		break;		
		
		// встреча с лакеем в резиденции
		case "ReasonToFast_Lakey":
			dialog.text = "As-tu des affaires ici, "+GetSexPhrase("monsieur","mademoiselle")+"?";
			link.l1 = "Non-non, je suis ici sur invitation de la charmante épouse du gouverneur, explorant cette résidence vraiment luxueuse.";
			link.l1.go = "ReasonToFast_Lakey1";
			link.l2 = "J'ai un message de la part de personnes que tu connais.";
			link.l2.go = "ReasonToFast_Lakey2";
			link.l3 = "Oui. Je veux te traduire en justice !";
			link.l3.go = "ReasonToFast_Lakey3";
			pchar.questTemp.ReasonToFast = "MeetLakey";
			pchar.questTemp.ReasonToFast.SpeakOther = true;			
		break;
		
		case "ReasonToFast_Lakey1":
			NextDiag.TempNode = "ReasonToFast_Lakey11";
			dialog.text = "Ah oui, j'ai vraiment eu de la chance de servir dans une si belle maison.";
			link.l1 = "Aucun étonnement...";
			link.l1.go = "ReasonToFast_Lakey11";
		break;

		case "ReasonToFast_Lakey11":
			NextDiag.TempNode = "ReasonToFast_Lakey11";
			dialog.text = "N'oubliez pas de jeter un oeil à notre jardin !";
			link.l1 = "Merci, bonhomme !";
			link.l1.go = "exit";			
			bDisableFastReload = false;
		break;
		
		case "ReasonToFast_Lakey2":
			dialog.text = "Ehh... "+pchar.questTemp.ReasonToFast.password+"?";
			link.l1.edit = 1;			
			link.l1 = "Bonjour, mon ami."; 
			link.l1.go = "ReasonToFast_Lakey21";
		break;

		case "ReasonToFast_Lakey3":
			dialog.text = "Tu ne t'en tireras pas comme ça, traître !";
			link.l1 = "Reste tranquille, scélérat !";
			link.l1.go = "ReasonToFast_Lakey_exit";
			pchar.questTemp.ReasonToFast = "LakeyExitFail";
			bDisableFastReload = false;			
		break;

		case "ReasonToFast_Lakey21":
			if(GetStrSmallRegister(pchar.questTemp.ReasonToFast.ShipName) == GetStrSmallRegister(dialogEditStrings[1]))
			{
				dialog.text = "Dépêche-toi ! Prends tout ce qui a de la valeur et file !";
				link.l1 = "Je pense que tu devrais courir aussi.";
				link.l1.go = "ReasonToFast_Lakey_exit";
				TakeNItems(pchar,"icollection", sti(pchar.questTemp.ReasonToFast.p8));
				TakeNItems(pchar,"Chest", sti(pchar.questTemp.ReasonToFast.p7));
				pchar.questTemp.ReasonToFast = "LakeyExitSuccess";					
				bDisableFastReload = true;		
				//chrDisableReloadToLocation = true;			
			}
			else
			{
				dialog.text = "Mmm, excusez-moi, je dois prendre congé.";
				link.l1 = "Tiens-toi tranquille, scélérat !";
				link.l1.go = "ReasonToFast_Lakey_exit";
				pchar.questTemp.ReasonToFast = "LakeyExitFail";
				bDisableFastReload = false;
			}			 
		break;

		case "ReasonToFast_Lakey_exit":
			DialogExit();	
			DeleteAttribute(pchar, "GenQuest.CannotWait");
			pchar.quest.ReasonToFast_ClearLakey.over = "yes"; //снимаем таймер
			ReasonToFast_SetHunterCoastal();
			AddDialogExitQuest("ReasonToFast_LakeyGoOut");
		break;		
		
		case "Man_FackYou":
			dialog.text = LinkRandPhrase("Tu es "+GetSexPhrase("un voleur, je vois ! Gardes, saisissez-le","un voleur, je vois ! Gardes, saisissez-la")+" !","Je n'en reviens pas ! J'ai détourné le regard une seconde, et tu plonges dans mon coffre ! Arrêtez le voleur !","Gardes ! Vol ! Arrêtez le voleur !");
			link.l1 = "Aaaah, diable !";
			link.l1.go = "ReasonToFast_Lakey_exit";
			pchar.questTemp.ReasonToFast = "LakeyExitFail";
			bDisableFastReload = false;
		break; 
		// Генератор "A reason to hurry" <--
		
		// ситуации с капитаном захваченного корабля
		// взрыв на корабле
		case "ShipSituation11": // пираты или ДУ
			dialog.text = RandPhraseSimple("Salut, "+GetSexPhrase("compère","fille")+"! Je t'ai préparé une surprise, j'ai allumé la mèche de la chambre à poudre. Ça va exploser jusqu'aux cieux !","Pourquoi restes-tu planté là ? Il y a un incendie dans la salle de poudre ! Ça va exploser, et les feux d'artifice seront visibles jusqu'en Europe !");
			link.l1 = RandPhraseSimple("Scélérat, tu ne me duperas pas ! Bats-toi, lâche !","Je vois les rats quitter le navire, et tu es parmi les premiers ?");
			link.l1.go = "ShipSituation12";
		break;
		
		case "ShipSituation12":
			dialog.text = RandPhraseSimple("Tu devrais courir aussi, si tu tiens à ta vie... Eh bien, je n'ai pas le temps, un bateau m'attend. Passe un bon moment à pêcher!","Je n'ai pas le temps de jouer les héros, les gars dans le bateau m'attendent. Passez un bon moment à pêcher, gagnant !");
			link.l1 = RandPhraseSimple("Sapristi! Coupez les défenses! Allez-vous-en!","Oh, bon dieu, comment avons-nous pu nous retrouver dans un tel pétrin ! Ouvrez les criques maritimes ! Dégagez !");
			link.l1.go = "ShipSituation_End";
		break;
		
		case "ShipSituation21": // военный корабль (не флагман)
			dialog.text = "Et alors?! Tu penses avoir gagné le combat?! Pas question. J'ai mis le feu à la soute à poudre, tu ne quitteras pas ce navire vivant.";
			link.l1 = RandPhraseSimple("Va-nu-pieds, tu ne me duperas pas ! Bats-toi, lâche !","Je vois les rats quitter le navire, et tu es parmi les premiers ?");
			link.l1.go = "ShipSituation22";
		break;
		
		case "ShipSituation22":
			dialog.text = RandPhraseSimple("Je suis lié par un serment, mais cela ne signifie pas que je doive mourir pour rien. Désolé de ne pas vous offrir une place dans le bateau, les marins ne comprendront pas.","Les navires sont liés l'un à l'autre lors de l'abordage, donc ton sort est scellé. Excuse-moi, mais mon bateau m'attend...");
			link.l1 = RandPhraseSimple("Bon sang ! Coupez les défenses ! Allez-y !","Ô Dieu, comment avons-nous pu nous retrouver dans un tel pétrin ! Ouvrez les écoutilles ! Dégagez !");
			link.l1.go = "ShipSituation_End";
		break;
		
		case "ShipSituation31": // ОЗГ
			dialog.text = RandPhraseSimple("Tu es victorieux ! Bienvenue en enfer ! J'ai mis le feu à la sainte-barbe.","Te voilà, mon brave ! Et c'est fait, j'ai mis le feu à la poudrière.");
			link.l1 = RandPhraseSimple("Vaurien, tu ne me tromperas pas ! Bats-toi, lâche !","Je vois les rats quitter le navire, et tu es parmi les premiers ?");
			link.l1.go = "ShipSituation32";
		break;
		
		case "ShipSituation32":
			dialog.text = RandPhraseSimple("Je te traquais depuis un bon moment. Dommage que j'aie dû sacrifier mon navire, mais ta tête en vaut bien deux nouveaux, de toute façon. Passe un bon moment à pêcher !","Tu vas voir comment tu vas partir ? Avec des feux d'artifice, comme un prince indien"+GetSexPhrase("ce","échec")+"Mais je ne vais pas me laisser faire comme un perdant, ta tête vaut bien plus que mon navire. Adieu maintenant, mon bateau ne va pas attendre trop longtemps...");
			link.l1 = RandPhraseSimple("Sacrebleu ! Coupez les défenses ! Allez-vous-en !","Oh, mon Dieu, comment avons-nous pu nous retrouver dans un tel pétrin ! Ouvrez les criques ! Détachez les amarres !");
			link.l1.go = "ShipSituation_End";			
		break;
		
		case "ShipSituation_End":
			AddCharacterExpToSkill(pchar, "Sneak", 200);
			DialogExit();
			LAi_SetActorType(NPChar); 
			LAi_ActorRunToLocation(NPChar, "reload", "reload1", "none", "", "", "", -1);
			NPChar.LifeDay = 0;
			LAi_LockFightMode(pchar, false);	
			Log_Info(XI_ConvertString("Ship can explode"));
			pchar.GenQuest.ShipSituation.Explosion = ShipSituation_4;	
			pchar.GenQuest.ShipSituation.Explosion.CapId = NPChar.CaptanId;
			LAi_EnableReload();
			Log_SetActiveAction("Reload");
		break;
		
		// эпидемия
		case "ShipEpidemy1":
			AddCharacterExpToSkill(pchar, "Fortune", 200);
			dialog.text = RandPhraseSimple("Attends, capitaine ! Pour quelques mots.","Attends, capitaine ! Je pense que cela pourrait t'intéresser.");
			link.l1 = LinkRandPhrase("Pourquoi parler pendant un combat?!","Et de quoi devrais-je parler avec un homme mort ?","Quel est le marché ? Tu veux faire un testament à mon nom ?");
			link.l1.go = "ShipEpidemy2";
		break;
		
		case "ShipEpidemy2":
			dialog.text = "Il y a une épidémie à bord. J'ai perdu un quart de mon équipage pendant le voyage. Vous êtes tous condamnés...";
			link.l1 = RandPhraseSimple("Espèce de salaud pourri ! Pourquoi n'as-tu pas signalé qu'il y a une catastrophe sur ton navire ?!","Avez-vous oublié le code de la mer ? Vous auriez dû afficher un signal sur le mât indiquant qu'il y a un désastre sur votre navire !");
			link.l1.go = "ShipEpidemy3";
		break;
		
		case "ShipEpidemy3":
			dialog.text = "Nous allions mourir de toute façon. C'est pourquoi nous n'avons pas abandonné, nous voulions t'emmener, toi et tes démons, dans l'autre monde avec nous ! Maintenant je suis pleinement satisfait. Tu peux accomplir ton acte infâme.";
			link.l1 = RandPhraseSimple("Je te ferai payer pour ça !..","J'aime l'idée que tu meures en premier. Et je vais regarder ça.");
			link.l1.go = "ShipEpidemy31";
			link.l2 = RandPhraseSimple("Je ne souillerai pas ma lame avec ton sang infâme, tu peux vivre, bien que... pour quoi faire ? Je vais éloigner mon équipage de cette vieille carcasse pourrie.","Tu devrais être pendu pour ça, mais ce n'est pas nécessaire maintenant. J'emmène mes hommes... Tu peux vivre, bien que ton temps devrait être court...");
			link.l2.go = "ShipEpidemy32";
			pchar.GenQuest.ShipSituation.Epidemy.CapId = NPChar.CaptanId;
			pchar.GenQuest.ShipSituation.Epidemy = ShipSituation_4;
		break;
		
		case "ShipEpidemy31":
			pchar.GenQuest.QuestAboardCabinDialogIdx = NPChar.index;
			pchar.GenQuest.ShipSituation.Epidemy.CapState = "Died"; // вражеский кэп на волосок от смерти от переизбытка стали и свинца в организме
			LAi_LockFightMode(pchar, false);
			QuestAboardCabinDialogExitWithBattle(""); 
			DialogExit();
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		
		case "ShipEpidemy32":
			DialogExit();
			LAi_SetActorType(NPChar); 
			LAi_ActorGoToLocation(NPChar, "reload", "reload1", "none", "", "", "", -1);
			LAi_LockFightMode(pchar, false);	
			pchar.GenQuest.ShipSituation.Epidemy.CapState = "Live"; // вражеский кэп остался в живых
			LAi_EnableReload();
			Log_SetActiveAction("Reload");
		break;
		// ситуации с капитаном захваченного корабля
		
		// Генератор "A damsel in the jungle"
		case "EncGirl_Lover":
			dialog.text = "Bonjour, capitaine, on m'a dit que vous me cherchiez.";
			link.l1 = "Je le suis - si tu l'es "+pchar.GenQuest.EncGirl.sLoverId+".";
			link.l1.go = "EncGirl_Lover1";
		break;
		
		case "EncGirl_Lover1":
			dialog.text = "Je le suis. Quelque chose d'important?";
			link.l1 = "Je ne sais pas si cela vous importe, mais j'ai apporté "+pchar.GenQuest.EncGirl.name+". Elle s'est enfuie de chez elle et vous attend maintenant non loin de la taverne.";
			link.l1.go = "EncGirl_Lover2";
		break;
		
		case "EncGirl_Lover2":
			dialog.text = "Oh là là... Je savais que tout finirait comme ça... Et pourquoi s'est-elle enfuie ? T'a-t-elle dit ?";
			link.l1 = "Son père veut la marier au fils de l'usurier.";
			link.l1.go = "EncGirl_Lover3";
		break;
		
		case "EncGirl_Lover3":
			pchar.GenQuest.EncGirl.LoverCity = GetQuestNationsCity(sti(pchar.GenQuest.EncGirl.nation));
			pchar.GenQuest.EncGirl.LoverIsland = GetIslandByCityName(pchar.GenQuest.EncGirl.LoverCity);
			dialog.text = "Oh non, nous ne pouvons pas laisser cela se produire ! Capitaine, vous savez, je suis dans une situation si stupide... Je voulais vous demander de nous emmener à "+XI_ConvertString(pchar.GenQuest.EncGirl.LoverIsland+"Acc")+" à la ville appelée "+XI_ConvertString("Colony"+pchar.GenQuest.EncGirl.LoverCity)+", mais en ce moment je n'ai pas d'argent et je n'ai toujours pas trouvé de travail. J'ai une famille aisée et une carrière prometteuse en "+XI_ConvertString("Colony"+pchar.GenQuest.EncGirl.LoverCity)+"...\nJe vous assure, mes parents seront ravis de me voir avec une jeune fiancée et ils vous récompenseront généreusement. Alors, êtes-vous partant ?";
			link.l1 = "...Ecoute maintenant, j'ai des plans totalement différents. Je peux te donner un conseil pour devenir marin et louer une cabine pour ta fiancée avec ton salaire. Les gens arrivent en Europe de cette manière, et ton bled se trouve à un vol de nuit d'oiseau.";
			link.l1.go = "EncGirl_Lover4";
			link.l2 = "Oh, la jeunesse... Te rends-tu compte de ce que tu me demandes de faire ? Enlever une fille à ses parents sans leur bénédiction ? ... Et quel genre d'homme refuserait une telle chose, bien sûr que je suis partant !";
			link.l2.go = "EncGirl_Lover5";
		break;
		
		case "EncGirl_Lover4":
			npchar.lifeDay = 0;
			AddDialogExitQuestFunction("EncGirl_LoverExit");	
			DialogExit();
		break;
		
		case "EncGirl_Lover5":
			AddDialogExitQuestFunction("EncGirl_ToLoverParents");	
			DialogExit();
		break;
		
		case "EncGirl_Lover6":
			AddSimpleRumourCityTip(RandPhraseSimple("Have you heard, " + pchar.GenQuest.EncGirl.name + " ran off with her lover. She decided not to bind her life to an invalid. That's surely the mistake of her parents, they should not have become tempted with the money of her fiance and try to give such a beauty in marriage to a fright.",  
				"Have you heard?" + pchar.GenQuest.EncGirl.name + " tricked both her dad and her would-be fiance. They say one noble captain helped her and her lover to get to another island, where her lover's parents lived... Imagine that, there still are people, who had not yet forgotten the taste of passion!"), pchar.GenQuest.EncGirl.LoverCity, 3, 2, "citizen,habitue", "");
			dialog.text = "Merci, capitaine. Nous nous souviendrons de votre aide pour le reste de nos jours.";
			link.l1 = "C'était rien. J'espère que tout se passera bien pour toi.";
			link.l1.go = "EncGirl_Lover7";
		break;
		
		case "EncGirl_Lover7":
			switch (rand(4))
			{
				case 0:
					sTemp = "the shop";
					pchar.GenQuest.EncGirl.LoverFather = "store_keeper";
				break;
				case 1:
					sTemp = "the shipyard";					
					pchar.GenQuest.EncGirl.LoverFather = "shipyard_keeper";
				break;
				case 2:
					sTemp = "the port office";					
					pchar.GenQuest.EncGirl.LoverFather = "portman_keeper";
				break;
				case 3:
					sTemp = "the tavern";					
					pchar.GenQuest.EncGirl.LoverFather = "tavern_keeper";
				break;
				case 4:
					sTemp = "the bank";					
					pchar.GenQuest.EncGirl.LoverFather = "usurer_keeper";
				break;
			}	
			pchar.GenQuest.EncGirl.FatherLoc = sTemp;
			dialog.text = "J'avais promis de te présenter à mes parents. Si tu as une minute de libre, passe donc me voir "+sTemp+", mon père y travaille, et je lui dirai ce que vous avez fait pour nous. Je suis sûr qu'il sera ravi de vous voir.";
			link.l1 = "D'accord, je passerai dès que j'aurai un moment. Soyez heureux et prenez soin l'un de l'autre, vous deux...";
			link.l1.go = "EncGirl_Lover8";
		break;
		
		case "EncGirl_Lover8":
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1_back", "none", "", "", "", 5.0);
			npchar.lifeday = 0;
			AddQuestRecord("JungleGirl", "16");
			AddQuestUserData("JungleGirl", "sSex", GetSexPhrase("",""));
			AddQuestUserData("JungleGirl", "sText", pchar.GenQuest.EncGirl.FatherLoc);
			if((GetSummonSkillFromName(pchar, SKILL_FORTUNE) + GetSummonSkillFromName(pchar, SKILL_LEADERSHIP)) < 175)
			{
				pchar.GenQuest.EncGirl.LoverFatherAngry = 0; // папочка жениха счастлив за сына :)
			}
			else
			{
				pchar.GenQuest.EncGirl.LoverFatherAngry = 1; // папочка жениха разъярен за то что сын притащил в дом шалаву :)
			}
			chrDisableReloadToLocation = false; 
			pchar.GenQuest.EncGirl = "toLoverFather";
			pchar.quest.EncGirl_GetLoverFather.win_condition.l1 = "Timer";
			pchar.quest.EncGirl_GetLoverFather.win_condition.l1.date.day = GetAddingDataDay(0, 0, 2);
			pchar.quest.EncGirl_GetLoverFather.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 2);
			pchar.quest.EncGirl_GetLoverFather.win_condition.l1.date.year = GetAddingDataYear(0, 0, 2);
			pchar.quest.EncGirl_GetLoverFather.function = "EncGirl_GenQuest_GetLoverFather";
			DialogExit();	
		break;
		// Генератор "A damsel in the jungle"
		
		// Генератор "Captain's request"
		case "CaptainComission_1":
			dialog.text = RandPhraseSimple("Attends ! Attends, capitaine ! Je vous en prie.","Capitaine, s'il vous plaît, attendez, je vous en supplie...");
			link.l1 = LinkRandPhrase("Quoi ? T'as perdu ton souffle ?","Leve ton sabre, espèce de lâche!","Quoi de neuf ? T'as oublié de rédiger ton testament ?");
			link.l1.go = "CaptainComission_2";
		break;
		
		case "CaptainComission_2":
			dialog.text = "Attends... Je suis blessé et je suis trop faible pour continuer à me battre... Je ne demande pas pitié, mais j'ai une affaire inachevée. S'il te plaît, promets-moi que tu accompliras la dernière volonté d'un homme mourant.";
			link.l1 = RandPhraseSimple("Ne sois pas une mauviette, capitaine, accepte la mort comme un homme se doit de le faire !","Capitaine, quelle sentimentalité ? Une bataille fait rage autour, alors finissons ce que nous avions commencé.");
			link.l1.go = "CaptainComission_21";
			link.l2 = "Parle maintenant et sois rapide.";
			link.l2.go = "CaptainComission_22";
		break;
		
		case "CaptainComission_21":
			LAi_SetCurHPMax(NPChar);
			LAi_GetCharacterMaxEnergy(NPChar);
			ChangeCharacterComplexReputation(pchar,"nobility", -2);
			DeleteAttribute(pchar,"GenQuest.CaptainComission");
			QuestAboardCabinDialogExitWithBattle(""); 
			DialogExit();	
			AddDialogExitQuest("MainHeroFightModeOn");		
		break;
		
		case "CaptainComission_22":		
			if(rand(1) == 0) // "Ransom"
			{
				CaptainComission_Init(NPChar);
				dialog.text = "Dites "+pchar.GenQuest.CaptainComission.Name+"  de la colonie de "+XI_ConvertString("Colony"+pchar.GenQuest.CaptainComission.City)+", que je n'ai pas réussi à accomplir sa demande... avant d'avoir eu le temps de... Qu'il me pardonne...";
				link.l1 = RandPhraseSimple("Et c'est tout ?! D'accord, je peux le faire. Hé, l'ami...","D'accord, je lui dirai si j'ai le temps. Hé, l'ami...");
				link.l1.go = "CaptainComission_22_1";
				link.l2 = "Je ne crois pas. Je n'ai pas de temps pour de telles sottises. Finissons ce que nous avions commencé.";
				link.l2.go = "CaptainComission_22_2";
			}
			else // "Operation 'Galleon'"
			{			
				CaptainComission_GaleonInit(NPChar);
				dialog.text = "S'il vous plaît, dites au capitaine d'une patrouille "+GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.CaptainComission.ShipType),"Nom")+"Gen"))+" ' "+pchar.GenQuest.CaptainComission.ShipTypeName+"' "+pchar.GenQuest.CaptainComission.Name+", qu'il ne devrait pas montrer son visage dans "+XI_ConvertString("Colony"+pchar.GenQuest.CaptainComission.City+"Voc")+"... "+"Les autorités sont au courant des véritables circonstances de sa mort "+GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.CaptainComission.ShipTypeVictim),"Nom")+"Gen"))+" ' "+pchar.GenQuest.CaptainComission.VictimShipName+"... le temps presse, il va être arrêté... naviguant vers "+XI_ConvertString("Colony"+pchar.GenQuest.CaptainComission.City+"Acc")+" de "+XI_ConvertString("Colony"+pchar.GenQuest.CaptainComission.City1+"Gen")+", le voyage prendra presque quinze jours... ahh... il faut se dépêcher..."; // belamour gen
				link.l1 = RandPhraseSimple("Je ne promets rien, mais j'essaierai à l'occasion. Hé, l'ami...","D'accord, je lui dirai si j'ai le temps. Hé, l'ami...");
				link.l1.go = "CaptainComission_300";
			}					
		break;
		
		case "CaptainComission_22_1":
			ReOpenQuestHeader("CaptainComission1");
			AddQuestRecord("CaptainComission1", "1");
			AddQuestUserData("CaptainComission1", "sShipName", pchar.GenQuest.CaptainComission.ShipName);
			AddQuestUserData("CaptainComission1", "sCapName", pchar.GenQuest.CaptainComission.CapName);
			AddQuestUserData("CaptainComission1", "sCharName", pchar.GenQuest.CaptainComission.Name);
			AddQuestUserData("CaptainComission1", "sCity", XI_ConvertString("Colony" + pchar.GenQuest.CaptainComission.City));	
			SetFunctionTimerCondition("CaptainComission_Speak", 0, 0, 30, false);
			SetFunctionTimerCondition("CaptainComission_SellSlave", 0, 0, 15 + rand(5), false);
			LAi_KillCharacter(NPChar);
			LAi_SetPlayerType(pchar); 
			pchar.GenQuest.CaptainComission = "Begin_1";
			LAi_EnableReload();
			Log_SetActiveAction("Reload");
			DialogExit();	
		break;
		
		case "CaptainComission_22_2":
			dialog.text = "Quelle cruauté ! J'espère que tu répondras de cela.";
			link.l1 = "Et pour beaucoup plus...";
			link.l1.go = "CaptainComission_22_3";
		break;
		
		case "CaptainComission_22_3":
			ReOpenQuestHeader("CaptainComission1");
			AddQuestRecord("CaptainComission1", "1");
			AddQuestUserData("CaptainComission1", "sShipName", pchar.GenQuest.CaptainComission.ShipName);
			AddQuestUserData("CaptainComission1", "sCapName", pchar.GenQuest.CaptainComission.CapName);
			AddQuestUserData("CaptainComission1", "sCharName", pchar.GenQuest.CaptainComission.Name);
			AddQuestUserData("CaptainComission1", "sCity", XI_ConvertString("Colony" + pchar.GenQuest.CaptainComission.City));
			SetFunctionTimerCondition("CaptainComission_Speak", 0, 0, 30, false);
			SetFunctionTimerCondition("CaptainComission_SellSlave", 0, 0, 15 + rand(5), false);
			LAi_SetCurHPMax(NPChar);
			LAi_GetCharacterMaxEnergy(NPChar);
			ChangeCharacterComplexReputation(pchar,"nobility", -3);
			pchar.GenQuest.CaptainComission = "Begin_2";
			QuestAboardCabinDialogExitWithBattle(""); 
			DialogExit();	
			AddDialogExitQuest("MainHeroFightModeOn");		
		break;
		
		case "CaptainComission_3":
			dialog.text = LinkRandPhrase("Je t'écoute, "+GetAddress_Form(pchar)+".","Que voulais-tu ?","Comment puis-je vous aider ?");
			if (pchar.GenQuest.CaptainComission == "Begin_1" || pchar.GenQuest.CaptainComission == "Begin_2") // лесник - доп.проверка если есть квест. для перехода .
			{	
			link.l1 = "Es-tu "+pchar.GenQuest.CaptainComission.Name+"? J'ai affaire avec vous. Capitaine "+pchar.GenQuest.CaptainComission.CapName+"a demandé de te transmettre une information importante.";
			link.l1.go = "CaptainComission_4";
			break;
			}
			link.l2 = "Non, rien...";
			link.l2.go = "exit";
			NextDiag.TempNode = "CaptainComission_3"; // лесник - переход чтобы не вызывал баг при повтороном обращении
		break;
		
		case "CaptainComission_4":
			dialog.text = "A-t-il ? D'accord. Alors, qu'est-ce que c'est que ce capitaine "+pchar.GenQuest.CaptainComission.CapName+"voulait que je sache ?";
			link.l1 = "Il m'a demandé de vous dire qu'il ne pourrait pas satisfaire votre demande.";
			link.l1.go = "CaptainComission_5";
		break;
		
		case "CaptainComission_5":
			dialog.text = "De quoi parlez-vous ?! Je le connais depuis des lustres, c'est un homme très honnête. Il n'aurait tout simplement pas pu vous dire ça !";
			link.l1 = "Disons que c'était pour des raisons hors de son contrôle. En d'autres termes - c'était son dernier souhait.";
			link.l1.go = "CaptainComission_6";
		break;
		
		case "CaptainComission_6":
			CaptainComission_GetPirateIsland();
			CaptainComission_GetFamilyType();
			if(pchar.GenQuest.CaptainComission == "Begin_1")
			{
				dialog.text = "Ah, c'est complètement déplacé ! Tant de temps perdu\n"+"Capitaine, dans ce cas, je dois vous demander de m'aider. Des pirates de "+XI_ConvertString("Colony"+pchar.GenQuest.CaptainComission.PiratesCity+"Gén")+"ont capturé mon parent"+pchar.GenQuest.CaptainComission.SlaveName+" et exigent une rançon pour lui. Pourriez-vous entreprendre cette mission ? La récompense devrait être assez généreuse.";
				link.l1 = "Malheureusement, j'ai d'autres projets.";
				link.l1.go = "CaptainComission_6_1";
				link.l2 = "Je vais essayer de t'aider si tu m'expliques plus en détail.";
				link.l2.go = "CaptainComission_6_2";
			}
			
			if(pchar.GenQuest.CaptainComission == "Begin_2")
			{
				dialog.text = "Ah, cela n’a aucun sens! Tant de temps perdu\nEt qu’en est-il des coffres?";
				link.l1 = "Euh... quels coffres?";
				link.l1.go = "CaptainComission_6_3";
				pchar.GenQuest.CaptainComission.CanFindChest = true;
			}	
		break;
		
		case "CaptainComission_6_1":
			dialog.text = "Quel dommage, capitaine... C'est bien dommage que vous ne vouliez pas m'aider.";
			link.l1 = "Ce n'est pas une question de volonté, mon ami. Vous devez comprendre. Adieu.";
			link.l1.go = "CaptainComission_6_1End";
		break;
		
		case "CaptainComission_6_2":
			dialog.text = "Hier, j'ai reçu une lettre de "+ChangeNameCase(NAMETYPE_MAIN,pchar.GenQuest.CaptainComission.PirateName,NAME_ACC)+", dans lequel il m'informait que la rançon allait être plus élevée, et il menaçait également de le vendre en esclavage. Le défunt capitaine aurait dû informer "+ChangeNameCase(NAMETYPE_MAIN,pchar.GenQuest.CaptainComission.PirateName,NAME_ACC)+", j'accepte les conditions précédentes et fais un paiement anticipé. Mais maintenant je comprends pourquoi les pirates ont augmenté les enjeux.";
			link.l1 = "Et que suggérez-vous ?";
			link.l1.go = "CaptainComission_6_21";
		break;
		
		case "CaptainComission_6_3":
			dialog.text = "Oh, "+GetSexPhrase("matelot","fille")+"Je sens un mauvais coup ici. Je vous avertis que c'est très dangereux et peut entraîner de graves conséquences. Capitaine"+pchar.GenQuest.CaptainComission.CapName+" avait trois coffres pleins d'or, qu'il aurait dû remettre à "+ChangeNameCase(NAMETYPE_MAIN,pchar.GenQuest.CaptainComission.PirateName,NAME_DAT)+" sur "+XI_ConvertString("Colony"+pchar.GenQuest.CaptainComission.PiratesCity+"Acc")+" en rançon pour un homme -  "+pchar.GenQuest.CaptainComission.SlaveName+". Et s'il voulait que vous veniez à nous, il n'aurait pas pu oublier de vous parler des coffres.";
			link.l1 = "En disant ses derniers mots, il ne semblait pas avoir terminé sa phrase. J'espérais que tu m'en dirais plus.";
			link.l1.go = "CaptainComission_6_31";
		break;
		
		case "CaptainComission_6_1End":
			AddQuestRecord("CaptainComission1", "3");
			AddQuestUserData("CaptainComission1", "sSex", GetSexPhrase("",""));
			AddQuestUserData("CaptainComission1", "sCharName", pchar.GenQuest.CaptainComission.Name);
			AddQuestUserData("CaptainComission1", "sCharType", GetStrSmallRegister(XI_ConvertString("Family" + pchar.GenQuest.CaptainComission.FamilyType + "Gen")));
			CloseQuestHeader("CaptainComission1");
			sld = CharacterFromID("CapComission_1"); // удаление если послал нахуй. лесник.
			sld.LifeDay = 0;
			DeleteAttribute(pchar,"GenQuest.CaptainComission");
			ChangeCharacterComplexReputation(pchar,"nobility", -2);
			DialogExit();	
		break;
		
		case "CaptainComission_6_21":
			dialog.text = "Je n'ai plus le choix... J'ai déjà réuni la somme requise, 150 000 pesos. Je vous demande de la livrer à "+XI_ConvertString("Colony"+pchar.GenQuest.CaptainComission.PiratesCity+"Acc")+" et amène mon parent ici. Je te paierai 40 000 dès que ce sera fait.";
			link.l1 = "D'accord, je suis prêt.";
			link.l1.go = "CaptainComission_6_22";
			link.l2 = "Malheureusement, j'ai d'autres projets.";
			link.l2.go = "CaptainComission_6_1";			
		break;
		
		case "CaptainComission_6_22":
			dialog.text = "Alors prends l'argent et que notre Seigneur te bénisse. Mais s'il te plaît, dépêche-toi. J'ai peur que "+ChangeNameCase(NAMETYPE_MAIN,pchar.GenQuest.CaptainComission.PirateName,NAME_NOM)+" ne va pas attendre et va vendre l'âme pauvre en esclavage.";
			link.l1 = "Attends-moi ici. Je pense pas que ça prendra trop de temps.";
			link.l1.go = "CaptainComission_6_22End";
		break;
		
		case "CaptainComission_6_22End":
			AddQuestRecord("CaptainComission1", "4");
			AddQuestUserData("CaptainComission1", "sCharName", pchar.GenQuest.CaptainComission.Name);
			AddQuestUserData("CaptainComission1", "sCity", XI_ConvertString("Colony" + pchar.GenQuest.CaptainComission.City + "Gen"));
			AddQuestUserData("CaptainComission1", "sPirateName", ChangeNameCase(NAMETYPE_MAIN, pchar.GenQuest.CaptainComission.PirateName, NAME_DAT));
			AddQuestUserData("CaptainComission1", "sPirateCity", XI_ConvertString("Colony" + pchar.GenQuest.CaptainComission.PiratesCity + "Acc"));
			AddQuestUserData("CaptainComission1", "sFamilyType", GetStrSmallRegister(XI_ConvertString("Family" + pchar.GenQuest.CaptainComission.FamilyType + "Gen")));
			AddQuestUserData("CaptainComission1", "sSlaveName",pchar.GenQuest.CaptainComission.SlaveName);
			addMoneyToCharacter(pchar, 150000);
			pchar.GenQuest.CaptainComission = "Begin_11";
			pchar.GenQuest.CaptainComission.AfterTavernSpeak = "goodSpeak";
			pchar.GenQuest.CaptainComission.GetSlave = "NoSlave";
			pchar.GenQuest.CaptainComission.toMayor = true;
			SetFunctionTimerCondition("CaptainComission_30DaysIsLeft", 0, 0, 30, false);
			NextDiag.TempNode = "CaptainComission_7";
			NextDiag.CurrentNode = NextDiag.TempNode; 
			DialogExit();
		break;
		
		case "CaptainComission_6_31":
			dialog.text = "Ça ne fait rien\nLes gens qui ont rassemblé la rançon s'en moqueront. Ils n'ont besoin que du résultat, vivant et entier - "+pchar.GenQuest.CaptainComission.SlaveName+"Alors ne perds pas de temps.";
			link.l1 = "Et que se passera-t-il si je refuse ?";
			link.l1.go = "CaptainComission_6_32";
		break;
						
		case "CaptainComission_6_32":
			dialog.text = "En fait, je n'ai pas besoin de votre consentement. Je vous informe simplement que si vous ne livrez pas "+pchar.GenQuest.CaptainComission.SlaveName+" vivant et en pleine forme à la taverne, je vais envoyer des chasseurs de primes après toi...";
			link.l1 = "Hmm... C'est sérieux. Et si je le fais ?";
			link.l1.go = "CaptainComission_6_33";
		break;
		
		case "CaptainComission_6_33":
			dialog.text = "Alors nous en discuterons plus avant.";
			link.l1 = "D'accord... Voyons comment cela se passe.";
			link.l1.go = "CaptainComission_6_33End";
		break;
		
		case "CaptainComission_6_33End":
			AddQuestRecord("CaptainComission1", "5");
			AddQuestUserData("CaptainComission1", "sSex", GetSexPhrase("",""));
			AddQuestUserData("CaptainComission1", "sSex", GetSexPhrase("",""));
			AddQuestUserData("CaptainComission1", "sCapName",pchar.GenQuest.CaptainComission.CapName);
			AddQuestUserData("CaptainComission1", "sPirateName", ChangeNameCase(NAMETYPE_MAIN, pchar.GenQuest.CaptainComission.PirateName, NAME_DAT));
			AddQuestUserData("CaptainComission1", "sPirateCity", XI_ConvertString("Colony" + pchar.GenQuest.CaptainComission.PiratesCity + "Acc"));
			AddQuestUserData("CaptainComission1", "sSlaveName",pchar.GenQuest.CaptainComission.SlaveName);
			AddQuestUserData("CaptainComission1", "sCharName", pchar.GenQuest.CaptainComission.Name);
			AddQuestUserData("CaptainComission1", "sCity", XI_ConvertString("Colony" + pchar.GenQuest.CaptainComission.City + "Gen"));
			pchar.GenQuest.CaptainComission = "Begin_22";
			pchar.GenQuest.CaptainComission.AfterTavernSpeak = "badSpeak";
			pchar.GenQuest.CaptainComission.GetSlave = "NoSlave";
			pchar.GenQuest.CaptainComission.toMayor = true;
			SetFunctionTimerCondition("CaptainComission_30DaysIsLeft", 0, 0, 30, false);
			NextDiag.TempNode = "CaptainComission_7";
			NextDiag.CurrentNode = NextDiag.TempNode; 
			DialogExit();
		break;
		
		case "CaptainComission_7":
			if(pchar.GenQuest.CaptainComission.GetSlave == "NoSlave")
			{
				if(pchar.GenQuest.CaptainComission.AfterTavernSpeak == "goodSpeak")
				{
					dialog.text = LinkRandPhrase("Bonjour, capitaine "+GetFullName(pchar)+"Des nouvelles ?","Alors, capitaine, avez-vous déjà livré la rançon ?","Bonjour, j'espère que tu es venu avec de bonnes nouvelles ?");
					if(makeint(pchar.money)>=150000)
					{
						link.l1 = "Malheureusement, mes plans ont changé, je dois donc annuler notre accord.";
						link.l1.go = "CaptainComission_7_1";
					}
					link.l2 = "Pas encore. Je suis encore occupé avec ça.";
					link.l2.go = "CaptainComission_7_2";
				}
				if(pchar.GenQuest.CaptainComission.AfterTavernSpeak == "badSpeak")
				{
					dialog.text = LinkRandPhrase("Oh, heureux de vous saluer, capitaine "+GetFullName(pchar)+"Des bonnes nouvelles ?","Alors, capitaine, avez-vous secouru notre ami souffrant ?","Ravi de te voir vivant et en pleine forme, capitaine. Quel est le statut de notre affaire commune ?");
					link.l1 = "Pas de nouvelles pour l'instant, mais  je m'en occupe.";
					link.l1.go = "CaptainComission_7_3";
					link.l2 = "Ecoute, mon ami, et pourquoi essaies-tu de me rendre responsable de cet accord?";
					link.l2.go = "CaptainComission_7_4";
				}
			}
			if(pchar.GenQuest.CaptainComission.GetSlave == "GetSlave")
			{
				if(pchar.GenQuest.CaptainComission.AfterTavernSpeak == "goodSpeak")
				{
					dialog.text = LinkRandPhrase("Bonjour, capitaine "+GetFullName(pchar)+"Des nouvelles?","Alors, capitaine, avez-vous déjà livré la rançon ?","Bonjour, j'espere que tu viens avec de bonnes nouvelles ?");
					link.l1 = "Oui. Votre demande a été accomplie, "+pchar.GenQuest.CaptainComission.SlaveName+" est à bord de mon navire et se prépare à venir à terre.";
					link.l1.go = "CaptainComission_30";
				}
				else
				{
					dialog.text = LinkRandPhrase("Oh, heureux de vous saluer, capitaine "+GetFullName(pchar)+"Des bonnes nouvelles ?","Alors, capitaine, avez-vous sauvé notre ami souffrant ?","Ravi de te voir vivant et en pleine forme, capitaine. Quel est le statut de notre affaire commune ?");	
					link.l1 = "J'ai amené un homme dont nous avons parlé. Il est à bord de mon navire.";
					link.l1.go = "CaptainComission_32";
				}
			}
			if(pchar.GenQuest.CaptainComission.GetSlave == "SlaveDied")
			{
				if(pchar.GenQuest.CaptainComission.AfterTavernSpeak == "goodSpeak")
				{
					dialog.text = LinkRandPhrase("Bonjour, capitaine "+GetFullName(pchar)+" . Des nouvelles ?","Alors, capitaine, avez-vous déjà livré la rançon ?","Bonjour, j'espère que vous venez avec une bonne nouvelle ?");
					link.l1 = "Salutations, "+pchar.GenQuest.CaptainComission.Name+", je dois te contrarier.";
					link.l1.go = "CaptainComission_50";
				}
				else
				{
					dialog.text = LinkRandPhrase("Oh, heureux de te saluer, capitaine "+GetFullName(pchar)+"Des bonnes nouvelles ?","Alors, capitaine, avez-vous sauvé notre ami souffrant ?","Content de te voir vivant et en pleine forme, capitaine. Quel est le statut de notre affaire commune ?");
					link.l1 = "L'homme, pour qui tu intercédais, est mort.";
					link.l1.go = "CaptainComission_60";
				}
			}
		break;
		
		case "CaptainComission_30":
			dialog.text = "Merci, capitaine, vous avez rendu un grand service à notre famille. Voici votre récompense... Il y a trois coffres - cela équivaut exactement à 40 000 pesos. Veuillez m'excuser, je dois le voir maintenant.";
			link.l1 = "Bien sûr, ayez une chaleureuse rencontre et bonne chance à vous deux.";
			link.l1.go = "CaptainComission_30_1";
			if(CheckAttribute(pchar, "GenQuest.CaptainComission.SlaveAddMoney"))
			{
				link.l2 = "Je comprends parfaitement votre impatience, mais des circonstances imprévues m'ont obligé à supporter des coûts supplémentaires.";
				link.l2.go = "CaptainComission_31";
			}	
		break;
		
		case "CaptainComission_30_1":
			//addMoneyToCharacter(pchar, 25000);
			TakeNItems(pchar, "chest", 3);
			Log_Info("You have received credit chests");
			PlaySound("interface\important_item.wav");
			AddQuestRecord("CaptainComission1", "14");
			AddQuestUserData("CaptainComission1", "sSex", GetSexPhrase("",""));
			AddQuestUserData("CaptainComission1", "sName", pchar.GenQuest.CaptainComission.SlaveName);
			CloseQuestHeader("CaptainComission1");
			ChangeCharacterComplexReputation(pchar,"nobility", 2);
			DialogExit();
			AddDialogExitQuestFunction("CaptainComission_EndTavern");
		break;
		
		case "CaptainComission_31":
			//addMoneyToCharacter(pchar, 25000);
			TakeNItems(pchar, "chest", 2);
			Log_Info("You have received credit chests");
			PlaySound("interface\important_item.wav");
			dialog.text = "Je ne comprends pas... Nous nous sommes déjà mis d'accord sur le montant de votre paiement, n'est-ce pas ?";
			link.l1 = "Nous avons, mais au lieu de 150000 pesos, j'ai été contraint de payer 200000, sans parler du voyage à la Barbade.";
			link.l1.go = "CaptainComission_31_1";
		break;
		
		case "CaptainComission_31_1":
			dialog.text = "Capitaine, ce n'est que le résultat de votre propre paresse. Les pirates n'ont fait aucune demande supplémentaire avec moi. Quel drôle de gaillard, essayer de gagner quelque chose au détriment des difficultés des autres ?";
			link.l1 = "D'accord, je vois qu'il est futile de tenter de t'expliquer quoi que ce soit...";
			link.l1.go = "CaptainComission_31_1End";
		break;
		
		case "CaptainComission_31_1End":
			AddQuestRecord("CaptainComission1", "15");
			AddQuestUserData("CaptainComission1", "sSex", GetSexPhrase("",""));
			AddQuestUserData("CaptainComission1", "sName", pchar.GenQuest.CaptainComission.SlaveName);
			CloseQuestHeader("CaptainComission1");			
			DialogExit();
			AddDialogExitQuestFunction("CaptainComission_EndTavern");
		break;

		case "CaptainComission_32":
			dialog.text = "Excellent ! Et tu doutais que nous travaillerions bien ensemble.";
			link.l1 = "Mais j'ai dû dépenser beaucoup pour cette affaire.";
			link.l1.go = "CaptainComission_32_1";
		break;
		
		case "CaptainComission_32_1":
			GetSlaveSpeciality();
			dialog.text = "Je sais, je sais... Mais tu as ta part de responsabilité là-dedans. Comment as-tu pu couler trois coffres remplis d'or, que nous avons dû littéralement secouer du trésor, pour que "+NationNameNominative(sti(pchar.GenQuest.CaptainComission.Nation))+" pourrait avoir un tel spécialiste "+pchar.GenQuest.CaptainComission.SlaveSpeciality+"?";
			link.l1 = "Sache que je ne te le donnerai pas sans une compensation adéquate.";
			link.l1.go = "CaptainComission_32_2";
		break;
		
		case "CaptainComission_32_2":
			dialog.text = "Eh bien, vous êtes un homme intelligent, sûrement, vous comprenez qu'il est trop tard pour marchander. Nous aurions pu arrêter votre navire avec sa cargaison.\nMais la compensation a été fournie auparavant. Par conséquent, le gouvernement de "+NationNameGenitive(sti(pchar.GenQuest.CaptainComission.Nation))+"vous félicite pour une opération réussie et vous présente ce cadeau précieux et une modeste récompense.";
			link.l1 = "Hmm... Eh bien, c'est toujours mieux que rien. Prends ton précieux spécialiste.";
			link.l1.go = "CaptainComission_32_2End";
		break;
		
		case "CaptainComission_32_2End":
			AddQuestRecord("CaptainComission1", "16");
			AddQuestUserData("CaptainComission1", "sSex", GetSexPhrase("",""));
			AddQuestUserData("CaptainComission1", "sSpeciality", pchar.GenQuest.CaptainComission.SlaveSpeciality);
			AddQuestUserData("CaptainComission1", "sNation", NationNameNominative(sti(pchar.GenQuest.CaptainComission.Nation)));
			CloseQuestHeader("CaptainComission1");			
			ChangeCharacterNationReputation(pchar, sti(NPChar.nation), 15);			
			GiveItem2Character(pchar, pchar.GenQuest.CaptainComission.Item); 
			TakeNItems(pchar, "jewelry5", 100);
			PlaySound("interface\important_item.wav");
			DialogExit();
			AddDialogExitQuestFunction("CaptainComission_EndTavern");
		break;
		
		case "CaptainComission_7_1":
			dialog.text = "Oh, quel dommage ! J'ai déjà perdu trop de temps. Tu m'as vraiment déçu, capitaine !";
			link.l1 = "Je comprends, mais les circonstances ne pouvaient être surmontées. Voici votre argent.";
			link.l1.go = "CaptainComission_7_1End";
		break;
		
		case "CaptainComission_7_1End":
			AddQuestRecord("CaptainComission1", "8");
			AddQuestUserData("CaptainComission1", "sSex", GetSexPhrase("",""));
			AddQuestUserData("CaptainComission1", "sCharName", pchar.GenQuest.CaptainComission.Name);
			CloseQuestHeader("CaptainComission1");
			rChar = characterFromId("CapComission_1");
			rChar.lifeDay = 0; 
			pchar.quest.CaptainComission1_30DaysIsLeft.over = "yes";
			addMoneyToCharacter(pchar, -150000);
			ChangeCharacterComplexReputation(pchar,"nobility", -4);
			LAi_CharacterDisableDialog(NPChar);
			DialogExit();
			AddDialogExitQuestFunction("CaptainComission_EndTavern");
		break;
		
		case "CaptainComission_7_2":
			dialog.text = "Pourriez-vous vous dépêcher, je vous prie ? Je crains que les pirates ne changent une fois de plus les termes de l'accord.";
			link.l1 = "Ne t'inquiète pas, nous nous débrouillerons.";
			link.l1.go = "exit";
			NextDiag.TempNode = "CaptainComission_7";
		break;
		
		case "CaptainComission_7_3":
			dialog.text = "J'espère que tu te rends compte que tu es en train de courir après le temps?";
			link.l1 = "Encore une fois ! Je m'en charge. Ayez patience.";
			link.l1.go = "exit";
			NextDiag.TempNode = "CaptainComission_7";
		break;
		
		case "CaptainComission_7_4":
			dialog.text = "Que Dieu nous protège ! Pas de pression, simplement une aide du modeste puritain\nC'est de ta faute. Tu as tué le capitaine "+pchar.GenQuest.CaptainComission.CapName+", perdu notre or et échoué à la rançon d'un homme très précieux. C'est la galère maintenant et c'est ta responsabilité. Ne pense même pas que tu es pardonné... Tu paieras pour tout.";
			link.l1 = "Va te faire foutre !";
			link.l1.go = "exit";
			NextDiag.TempNode = "CaptainComission_7";
		break;
		
		// диалоги с управляющим на плантации
		case "CaptainComission_10":
			dialog.text = "Bonjour, avais-tu besoin de quelque chose ?";
			link.l1 = "Puis-je voir le propriétaire de cette plantation ?";
			link.l1.go = "CaptainComission_10_1";
		break;
		
		case "CaptainComission_10_1":
			dialog.text = "Il n'est pas ici, il cherche un esclave en fuite, Blade, ou Blood, je ne me souviens plus... Et moi, je suis l'intendant local "+npchar.name+" et je suis autorisé à régler toutes les affaires pendant que le patron est en congé.";
			link.l1 = "Es-tu? C'est bien... Et vendre des esclaves, c'est aussi ton affaire?";
			link.l1.go = "CaptainComission_10_2";
		break;
		
		case "CaptainComission_10_2":
			dialog.text = "Bien sûr. Combien voulez-vous en acheter ?";
			link.l1 = "Juste un.";
			link.l1.go = "CaptainComission_10_3";
		break;
		
		case "CaptainComission_10_3":
			dialog.text = "Ehh... Es-tu sûr de n'avoir besoin que d'un seul esclave ?";
			link.l1 = "Bien sûr, je le suis. Son nom est "+pchar.GenQuest.CaptainComission.SlaveName+".";
			link.l1.go = "CaptainComission_10_4";
		break;
		
		case "CaptainComission_10_4":
			if(rand(1) == 0)
			{
				dialog.text = "Mais certainement vous réalisez que le prix d'un esclave sera plus élevé comparé au prix d'un esclave dans un lot plus grand ?";
				link.l1 = "Bien sûr que oui. Peux-tu nommer le prix ?";
				link.l1.go = "CaptainComission_11";
			}
			else
			{
				if(rand(100) < makeint(sti(pchar.rank) + 0.75 * GetSummonSkillFromName(pchar, SKILL_FORTUNE)))
				{
					dialog.text = "Hmm... J'espère que tu sais pour qui tu intercèdes ?";
					link.l1 = "Que veux-tu dire ?";
					link.l1.go = "CaptainComission_12";
				}
				else
				{
					dialog.text = "Oh, ce fainéant. Je ne donnerais pas un sou pour lui. Depuis qu'il a été amené ici, il n'a jamais fait de véritable travail. Je n'ai aucune idée de pourquoi le colonel gaspillerait de l'argent sur ces condamnés d'État. Maintenant, les gars noirs, c'est une autre histoire. Ce sont de grands travailleurs, c'est dans leur sang, à la fois forts et dociles. Et croyez-moi, ils peuvent faire absolument n'importe quel travail. Récolte de canne à sucre ou service en tant qu'intendant - ils le feront de la meilleure façon possible, il suffit de leur donner un peu de 'persuasion'...";
					link.l1 = "Mon ami, je me fiche de tes gars noirs. Je suis seulement intéressé par ce fainéant dont tu parlais, il ne vivra pas longtemps de toute façon, j'ai besoin de lui comme chair à canon et je paierai plus pour lui.";
					link.l1.go = "CaptainComission_13";
				}
			}
		break;
		
		case "CaptainComission_11":
			dialog.text = "Bien sûr, bien sûr. Laisse-moi voir les prix\nOh !!! 150000 pesos.";
			link.l1 = "Ouah...";
			link.l1.go = "CaptainComission_11_1";
		break;
		
		case "CaptainComission_11_1":
			dialog.text = "Le prix devrait être dans la liste des prix. Ici. Tu sais, je ne comprends pas bien. Les autres esclaves sont vendus à des prix raisonnables, mais celui-là est vendu pour une fortune...";
			if(sti(pchar.money) >= 150000)
			{
				link.l1 = "Je crois comprendre de quoi il s'agit ici... Très bien, voici l'argent, et je l'emmène avec moi.";
				link.l1.go = "CaptainComission_14";
			}	
			link.l2 = "Hmm... Mais je ne fais pas de rançon pour un otage, je veux acheter un esclave ordinaire. Ne penses-tu pas qu'on pourrait acheter un navire entièrement équipé pour une telle somme?";
			link.l2.go = "CaptainComission_15";
		break;
		
		case "CaptainComission_12":
			dialog.text = "Ce n'est pas un esclave ordinaire. Le colonel Bishop a même ordonné de le garder.";
			link.l1 = "Alors je ne peux même pas l'acheter ?";
			link.l1.go = "CaptainComission_12_1";
		break;
		
		case "CaptainComission_12_1":
			dialog.text = "Eh bien, certainement que tu peux. Le colonel a fixé un prix pour lui - 200000 pesos, selon la liste des prix.";
			if(sti(pchar.money) >= 200000)
			{
				link.l1 = "Ouah ! Eh bien, sûrement que ce colonel doit être conscient du genre de personne que cet esclave est...";
				link.l1.go = "CaptainComission_16";
			}	
			link.l2 = "Hmm... Mais je ne rachète pas un otage, je veux acheter un esclave ordinaire. Ne pensez-vous pas qu'on pourrait acheter un navire bien équipé pour une telle somme ?";
			link.l2.go = "CaptainComission_15";	
		break;
		
		case "CaptainComission_13":
			dialog.text = "Ah, oui. Pardonnez-moi. Laissez-moi voir le prix que l'Évêque a laissé.\nAh, le voici. Eh bien. Oh!.. 150 000 pesos!..";
			if(sti(pchar.money) >= 15000)
			{
				link.l1 = "Apparemment, c'est une sorte d'erreur. Vous réalisez bien qu'aucun esclave ne peut coûter autant. Je suppose qu'il y a un zéro en trop, et la somme devrait être de 15000 pesos. Et c'est encore trop, étant donné que c'est un fainéant et un idiot.";
				link.l1.go = "CaptainComission_17";
			}	
			link.l2 = "Hmm... Mais je ne suis pas en train de racheter un otage, je veux acheter un simple esclave. Ne pensez-vous pas qu'on pourrait acheter un navire bien équipé pour une telle somme ?";
			link.l2.go = "CaptainComission_15";
		break;
		
		case "CaptainComission_14":
			addMoneyToCharacter(pchar, -150000);
			pchar.GenQuest.CaptainComission.SlaveMoney = 150000;
			dialog.text = "Superbe ! C'est magnifique ! Ils vont l'amener ici tout de suite... Euh... Du thé, peut-être ?";
			link.l1 = "Non, merci... Passe le bonjour au colonel Bishop...";
			link.l1.go = "CaptainComission_14_1";
		break;
		
		case "CaptainComission_14_1":
			dialog.text = "Et de qui, puis-je savoir?";
			link.l1 = "Mmm... Laisse tomber, ne t'embête pas. Adieu.";
			link.l1.go = "CaptainComission_14_1End";
		break;
		
		case "CaptainComission_14_1End":
			NextDiag.TempNode = "CaptainComission_18";
			NextDiag.CurrentNode = NextDiag.TempNode;
			pchar.GenQuest.CaptainComission.GetSlave = "GetSlave";
			DialogExit();
			AddDialogExitQuestFunction("CaptainComission_GetSlave");
		break;
		
		case "CaptainComission_15":
			dialog.text = "Je suis désolé, mais il n'y a rien que je puisse faire. Voici la liste des prix.";
			link.l1 = "Oh arrêtez ça, 'liste de prix, liste de prix...' Vous ne pouvez pas décider de la chose la plus simple sans Bishop. Dites-lui... Peu importe, ne lui dites rien.";
			link.l1.go = "CaptainComission_15_1";
		break;
		
		case "CaptainComission_15_1":
			dialog.text = "Alors, tu ne vas pas acheter cet esclave.";
			link.l1 = "Non. Adieu.";
			link.l1.go = "CaptainComission_15_1End";
		break;
		
		case "CaptainComission_15_1End":
			OfficersReaction("bad");
			AddQuestRecord("CaptainComission1", "30");
			AddQuestUserData("CaptainComission1", "sSex", GetSexPhrase("",""));
			NextDiag.TempNode = "CaptainComission_19";
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			AddDialogExitQuestFunction("CaptainComission_GetSlave");
		break;
		
		case "CaptainComission_16":
			dialog.text = "Je n'en sais rien. J'ai seulement des instructions précises concernant la vente de cet esclave en particulier.";
			link.l1 = "Balivernes... Bon, peu importe. Voici l'argent. Amène l'esclave.";
			link.l1.go = "CaptainComission_16_1"; 
		break;
		
		case "CaptainComission_16_1":
			addMoneyToCharacter(pchar, -200000);
			pchar.GenQuest.CaptainComission.SlaveMoney = 200000;
			dialog.text = "Bien sûr. Il sera livré ici en un instant.";
			link.l1 = "Adieu.";
			link.l1.go = "CaptainComission_16_1End";
		break;
		
		case "CaptainComission_16_1End":
			NextDiag.TempNode = "CaptainComission_18";
			NextDiag.CurrentNode = NextDiag.TempNode;
			pchar.GenQuest.CaptainComission.GetSlave = "GetSlave";
			DialogExit();
			AddDialogExitQuestFunction("CaptainComission_GetSlave");
		break;
		
		case "CaptainComission_17":
			dialog.text = "Hmm... Ouais, peut-être que tu as raison. Ça doit être une erreur.";
			link.l1 = "Eh bien, si nous sommes d'accord sur le prix, puis-je l'emmener avec moi maintenant ?";
			link.l1.go = "CaptainComission_17_1";
		break;
		
		case "CaptainComission_17_1":
			dialog.text = "Oui, bien sûr. Il sera amené ici dans un instant.";
			link.l1 = "Très bien. Voici votre argent... Adieu.";
			link.l1.go = "CaptainComission_17_1End";
		break;
		
		case "CaptainComission_17_1End":
			addMoneyToCharacter(pchar, -15000);
			pchar.GenQuest.CaptainComission.SlaveMoney = 15000;
			NextDiag.TempNode = "CaptainComission_18";
			NextDiag.CurrentNode = NextDiag.TempNode;
			pchar.GenQuest.CaptainComission.GetSlave = "GetSlave";
			DialogExit();
			AddDialogExitQuestFunction("CaptainComission_GetSlave");
		break;
		
		case "CaptainComission_18":
			dialog.text = "Voulez-vous du thé, capitaine ?";
			link.l1 = "Non, merci.";
			link.l1.go = "exit";
		break;
		
		case "CaptainComission_19":
			dialog.text = "Avez-vous décidé de l'acheter.";
			link.l1 = "Non. Adieu.";
			link.l1.go = "exit";
		break;
		
		// диалоги с рабом
		case "CaptainComission_20":
			if(pchar.GenQuest.CaptainComission.AfterTavernSpeak == "goodSpeak")
			{
				dialog.text = "Bonjour, capitaine. Comment puis-je vous aider? Je n'arrive pas à croire que ce supplice soit enfin terminé.";
				link.l1 = "Tu devrais remercier non pas moi, mais plutôt ton parent "+pchar.GenQuest.CaptainComission.Name+" de "+XI_ConvertString("Colony"+pchar.GenQuest.CaptainComission.City+"Gen")+"Il a rassemblé la rançon.";
				link.l1.go = "CaptainComission_201";
			}
			else
			{
				dialog.text = "Bonjour, capitaine. On m'a dit que vous aviez payé la rançon pour moi. Je dois vous remercier pour cela, bien que je réalise que vous n'étiez qu'un simple messager.";
				link.l1 = "Tu n'as pas l'air si heureux de ta liberté nouvellement retrouvée. T'inquiètes-tu de quelque chose?";
				link.l1.go = "CaptainComission_202";
			}
		break;
		
		case "CaptainComission_201":
			dialog.text = "S'il vous plaît, si cela ne perturbe pas trop vos plans, emmenez-moi à lui. J'aimerais le remercier personnellement.";
			link.l1 = "Bien sûr, je le ferai. Viens, je te conduirai au navire.";
			link.l1.go = "CaptainComission_201_1";
		break;
		
		case "CaptainComission_201_1":
			AddQuestRecord("CaptainComission1", "11");
			AddQuestUserData("CaptainComission1", "sSex", GetSexPhrase("",""));
			AddQuestUserData("CaptainComission1", "sName", pchar.GenQuest.CaptainComission.SlaveName);
			AddQuestUserData("CaptainComission1", "sSum", pchar.GenQuest.CaptainComission.SlaveMoney);
			AddQuestUserData("CaptainComission1", "sCity", XI_ConvertString("Colony" + pchar.GenQuest.CaptainComission.City + "Acc"));
			AddQuestUserData("CaptainComission1", "sCharName", pchar.GenQuest.CaptainComission.Name);
			AddPassenger(pchar, npchar, false);
			SetCharacterRemovable(npchar, false);
			LAi_SetActorType(NPChar);
			LAi_ActorRunToLocation(NPChar, "reload", "reload2_back", "none", "", "", "OpenTheDoors", -1.0);
			DialogExit();
		break;
		
		case "CaptainComission_202":
			dialog.text = "Pour être sûr de ma liberté, il me faut connaître les noms de ceux qui l'ont payée.";
			link.l1 = "Eh bien, c'est moi qui ai payé, bien que ce ne fût pas de mon plein gré.";
			link.l1.go = "CaptainComission_202_1";
		break;
		
		case "CaptainComission_202_1":
			dialog.text = "Alors, mes soupçons étaient confirmés. Vous avez été forcé de le faire par "+NationNamePeople(sti(pchar.GenQuest.CaptainComission.Nation))+"?";
			link.l1 = "Oui, c'est "+pchar.GenQuest.CaptainComission.Name+" de "+XI_ConvertString("Colony"+pchar.GenQuest.CaptainComission.City+"Gen")+".";
			link.l1.go = "CaptainComission_202_2";
		break;
		
		case "CaptainComission_202_2":
			iNation = FindEnemyNation2NationWithoutPirates(sti(pchar.GenQuest.CaptainComission.Nation));	// mitrokosta 
			if(iNation == -1) iNation = rand(NON_PIRATES);
			pchar.GenQuest.CaptainComission.SlaveCity = FindAlliedColonyForNation(iNation, true);
			pchar.GenQuest.CaptainComission.EnemyNation = iNation;
			LAi_SetImmortal(npchar, true);// лесник . откатил .  и защиту  чтоб умники не убили.
			dialog.text = "Je vois. Je n'ai aucune idée de ce qu'ils vous avaient promis, mais voici l'affaire : emmenez-moi à la taverne de "+XI_ConvertString("Colony"+pchar.GenQuest.CaptainComission.SlaveCity+"Gen")+", je serai en sécurité là-bas pour de bon. En retour, je partagerai quelques informations que je possède avec toi.";
			link.l1 = "C'est bien, d'autant plus qu'ils n'ont rien promis jusqu'à présent. Viens avec moi, je te conduirai à mon navire.";
			link.l1.go = "CaptainComission_202_3";
			link.l2 = "Je ne vais pas risquer d'attirer des ennuis sur moi-même à cause de quelque information douteuse.";
			link.l2.go = "CaptainComission_203";
		break;
		
		
		
		case "CaptainComission_202_3":
			AddPassenger(pchar, npchar, false);
			SetCharacterRemovable(npchar, false);
			rChar = characterFromId("CapComission_1");
			ChangeCharacterAddress(rChar, "none", "");			
			rChar.lifeDay = 0; 
			AddQuestRecord("CaptainComission1", "12");
			AddQuestUserData("CaptainComission1", "sSex", GetSexPhrase("",""));
			AddQuestUserData("CaptainComission1", "sSex1", GetSexPhrase("",""));
			AddQuestUserData("CaptainComission1", "sName", pchar.GenQuest.CaptainComission.SlaveName);
			AddQuestUserData("CaptainComission1", "sSum", pchar.GenQuest.CaptainComission.SlaveMoney);
			AddQuestUserData("CaptainComission1", "sCity", XI_ConvertString("Colony" + pchar.GenQuest.CaptainComission.SlaveCity + "Acc"));
			pchar.quest.CapComission_DeliveSlave.win_condition.l1 = "location";
			pchar.quest.CapComission_DeliveSlave.win_condition.l1.location = pchar.GenQuest.CaptainComission.SlaveCity + "_tavern";
			pchar.quest.CapComission_DeliveSlave.function = "CaptainComission_DeliveSlave";
			LAi_SetActorType(NPChar);
			LAi_ActorFollow(NPChar, PChar, "OpenTheDoors", -1.0); //лесник  идем за ГГ
			DialogExit();
		break;
		
		case "CaptainComission_203":
			dialog.text = "Malheureusement, je ne peux pas te le révéler pour l'instant. Cela pourrait causer des ennuis à nous deux.";
			link.l1 = "Tout d'autant plus... Suivez-moi et pas de bêtises, s'il vous plaît. Considérez-vous à nouveau en état d'arrestation.";
			link.l1.go = "CaptainComission_203_1";
		break;
		
		case "CaptainComission_203_1":
			AddQuestRecord("CaptainComission1", "13");
			AddQuestUserData("CaptainComission1", "sSex", GetSexPhrase("",""));
			AddQuestUserData("CaptainComission1", "sName", pchar.GenQuest.CaptainComission.SlaveName);
			AddQuestUserData("CaptainComission1", "sSum", pchar.GenQuest.CaptainComission.SlaveMoney);
			AddPassenger(pchar, npchar, false);
			SetCharacterRemovable(npchar, false);
			LAi_SetActorType(NPChar);
			LAi_ActorRunToLocation(NPChar, "reload", "reload2_back", "none", "", "", "OpenTheDoors", -1.0); //лесник - провожаем на корабль типа..
			DialogExit();
		break;
		
		case "CaptainComission_50":
			dialog.text = "Quoi?! Les pirates ont encore modifié l'accord ? Mais je ne peux plus retirer d'argent des affaires ! De cette façon, je serai bientôt en faillite !";
			link.l1 = "Non... Votre parent a péri sur les plantations de la Barbade lors d'une tentative d'évasion infructueuse.";
			link.l1.go = "CaptainComission_51";
		break;
		
		case "CaptainComission_51":
			ChangeCharacterComplexReputation(pchar,"nobility", -3);
			dialog.text = "Oh... Je suis complètement anéanti... Comment cela a-t-il pu arriver ?";
			link.l1 = "Les pirates n'avaient pas attendu la rançon et l'avaient vendu comme esclave. Je suis allé le chercher à la Barbade, mais je n'ai pas réussi à le sauver...";
			link.l1.go = "CaptainComission_52";
		break;
		
		case "CaptainComission_52":
			dialog.text = "Jésus ! Que se passe-t-il ?\nBien, capitaine, merci pour votre participation. Et s'il vous plaît, rendez-moi l'argent que je vous ai donné.";
			link.l1 = "Mes dépenses ont dépassé toutes les attentes, donc je garderai votre argent... Adieu.";
			link.l1.go = "CaptainComission_53";
			if(sti(pchar.money) >= 150000)
			{
				link.l2 = "Bien sûr, prends-le... Désolé de ne pas avoir réussi à t'aider... Adieu.";
				link.l2.go = "CaptainComission_54";
			}
		break;
		
		case "CaptainComission_53":
			ChangeCharacterComplexReputation(pchar,"nobility", -5);
			OfficersReaction("bad");			
			AddQuestRecord("CaptainComission1", "22");
			AddQuestUserData("CaptainComission1", "sSex", GetSexPhrase("",""));
			AddQuestUserData("CaptainComission1", "sCharName", pchar.GenQuest.CaptainComission.Name);
			AddQuestUserData("CaptainComission1", "sName", pchar.GenQuest.CaptainComission.SlaveName);
			CloseQuestHeader("CaptainComission1");
			LAi_CharacterDisableDialog(npchar);
			npchar.lifeDay = 0; 			
			DeleteAttribute(pchar,"GenQuest.CaptainComission");
			DialogExit();
		break;
		
		case "CaptainComission_54":
			OfficersReaction("good");
			addMoneyToCharacter(pchar, -150000);
			AddQuestRecord("CaptainComission1", "23");
			AddQuestUserData("CaptainComission1", "sSex", GetSexPhrase("",""));
			AddQuestUserData("CaptainComission1", "sCharName", pchar.GenQuest.CaptainComission.Name);
			AddQuestUserData("CaptainComission1", "sName", pchar.GenQuest.CaptainComission.SlaveName);
			CloseQuestHeader("CaptainComission1");
			LAi_CharacterDisableDialog(npchar);
			npchar.lifeDay = 0; 			
			DeleteAttribute(pchar,"GenQuest.CaptainComission");
			DialogExit();
		break;
		
		case "CaptainComission_60":
			dialog.text = "C'est bien dommage. Tu n'as aucune idée à quel point c'est vraiment mauvais...";
			link.l1 = "Je ne peux rien y faire. Je suis même content que tout cela se soit passé ainsi. Adieu.";
			link.l1.go = "CaptainComission_61";
		break;
		
		case "CaptainComission_61":
			ChangeCharacterComplexReputation(pchar,"nobility", -2);
			ChangeCharacterNationReputation(pchar, sti(NPChar.nation), -15);
			AddQuestRecord("CaptainComission1", "32");
			AddQuestUserData("CaptainComission1", "sSex", GetSexPhrase("",""));
			AddQuestUserData("CaptainComission1", "sName", pchar.GenQuest.CaptainComission.Name);
			CloseQuestHeader("CaptainComission1");
			LAi_CharacterDisableDialog(npchar);
			npchar.lifeDay = 0; 			
			DeleteAttribute(pchar,"GenQuest.CaptainComission");			
			DialogExit();
		break;
		
		// диалог с рабом в колодках
		case "CaptainComission_70":
			dialog.text = "Bois... capitaine, apporte un peu d'eau...";
			link.l1 = "Eh, l'ami, n'es-tu pas "+pchar.GenQuest.CaptainComission.SlaveName+"?";
			link.l1.go = "CaptainComission_71";
		break;
		
		case "CaptainComission_71":
			dialog.text = "Ouais... C'est moi...";
			link.l1 = "Ecoute ! Si tu ne veux pas périr ici, comme un poisson plat sur un banc de sable, ressaisis-toi et écoute-moi. Sais-tu où se trouve le Phare de la Barbade ?";
			link.l1.go = "CaptainComission_72";
		break;
		
		case "CaptainComission_72":
			dialog.text = "Je fais...";
			link.l1 = "Une fois que tu auras l'occasion, cours là-bas. J'essaierai de te ménager une telle occasion.";
			link.l1.go = "CaptainComission_73";			
		break;
		
		case "CaptainComission_73":	
			LAi_SetPlayerType(pchar); 
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
			LAi_LockFightMode(pchar, false);			
			sTemp = GetNationNameByType(GetCityNation("Bridgetown"))  + "_citizens";
			for(i = 0; i < 3; i++)
			{
				if (GetCharacterIndex("SlaveGuard_" + i) == -1) continue;
				sld = CharacterFromID("SlaveGuard_" + i);			
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "SlaveGuards");
			}
						
			LAi_group_SetRelation("SlaveGuards", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_SetRelation("SlaveGuards", sTemp, LAI_GROUP_NEITRAL);			
			LAi_group_SetAlarmReaction("SlaveGuards", sTemp, LAI_GROUP_NEITRAL, LAI_GROUP_FRIEND);
			LAi_group_FightGroups("SlaveGuards", LAI_GROUP_PLAYER, true);
			LAi_group_SetAlarm("SlaveGuards", LAI_GROUP_PLAYER, 0);
			LAi_group_SetCheck("SlaveGuards", "OpenTheDoors");
			LAi_group_SetCheckFunction("SlaveGuards", "CaptainComission_GuardsAfter");
			
			DialogExit();
			AddDialogExitQuest("MainHeroFightModeOn"); 
		break;
		
		// диалог охранников раба
		case "CaptainComission_80":
			dialog.text = RandPhraseSimple("Allez-y, capitaine, posez votre question, mais faites vite, je suis de service.","Parle, mais fais vite et ne me dérange pas avec des broutilles.");
			link.l1 = RandPhraseSimple("Peux-tu me dire comment je peux trouver un certain esclave ? Il s'appelle "+pchar.GenQuest.CaptainComission.SlaveName+".","Quelque part dans cette plantation, il devrait y avoir un esclave du nom de "+pchar.GenQuest.CaptainComission.SlaveName+"Peux-tu me dire comment pourrais-je lui parler?");
			link.l1.go = "CaptainComission_81";			
		break;
		
		case "CaptainComission_81":
			dialog.text = "Aujourd'hui, il est puni et sous garde.";
			link.l1 = "Merci.";
			link.l1.go = "exit";
			NextDiag.TempNode = "CaptainComission_80";
			NextDiag.CurrentNode = NextDiag.TempNode;
		break;
		
		case "CaptainComission_85":
			dialog.text = "Merci... capitaine, vous m'avez sauvé la vie...";
			link.l1 = "Courez jusqu'au phare de la Barbade et attendez-moi là-bas.";
			link.l1.go = "CaptainComission_86";
		break;
		
		case "CaptainComission_86":
			LAi_SetActorType(NPChar);
			LAi_ActorRunToLocation(NPChar, "reload", "reload2_back", "none", "", "", "OpenTheDoors", -1.0);
			sTemp = GetNationNameByType(GetCityNation("Bridgetown"))  + "_citizens";
			LAi_group_AttackGroup(sTemp, LAI_GROUP_PLAYER);
			DialogExit();
		break;
		
		case "CaptainComission_90":
			if(pchar.GenQuest.CaptainComission.AfterTavernSpeak == "goodSpeak")
			{
				dialog.text = "Capitaine, comment puis-je vous remercier ? Je n'arrive toujours pas à croire que ce tourment est enfin terminé.";
				link.l1 = "J'ai déjà été remercié par votre parent "+pchar.GenQuest.CaptainComission.Name+" de "+XI_ConvertString("Colony"+pchar.GenQuest.CaptainComission.City+"Gen")+"Je suis ses instructions.";
				link.l1.go = "CaptainComission_91";
			}
			if(pchar.GenQuest.CaptainComission.AfterTavernSpeak == "badSpeak")
			{
				dialog.text = "Merci, capitaine. Je ne sais pas au nom de qui vous agissez, mais même une mauvaise liberté vaut mieux qu'une bonne esclavage.";
				link.l1 = "Que veux-tu dire ?";
				link.l1.go = "CaptainComission_92";
			}
		break;
		
		case "CaptainComission_91":
			dialog.text = "Si cela ne contrarie pas trop vos plans, emmenez-moi vers lui, je vous prie. Je suis trop las de tout cela.";
			link.l1 = "Bien sûr, je vais... si nous parvenons à sortir d'ici vivants.";
			link.l1.go = "CaptainComission_91End";
		break;
		
		case "CaptainComission_91End":
			pchar.GenQuest.CaptainComission = "toOurTavern";
			rChar = CharacterFromID("CapComission_Slave");
			LAi_SetWarriorType(rChar);
			LAi_group_MoveCharacter(rChar, LAI_GROUP_PLAYER);
			DialogExit();
			AddDialogExitQuestFunction("CaptainComission_GeneratePatrol");
		break;
		
		case "CaptainComission_92":
			dialog.text = "Et puis-je savoir les noms des personnes qui ont payé pour ma liberté ?";
			link.l1 = "Eh bien, en fait, je n'ai pas été payé. Ils ne m'ont laissé aucun choix.";
			link.l1.go = "CaptainComission_93";
		break;
		
		case "CaptainComission_93":
			dialog.text = "Alors, mes soupçons ont été confirmés. Vous avez été contraint de le faire par "+NationNamePeople(sti(pchar.GenQuest.CaptainComission.Nation))+"?";
			link.l1 = "Oui, c'est "+pchar.GenQuest.CaptainComission.Name+" de "+XI_ConvertString("Colony"+pchar.GenQuest.CaptainComission.City+"Gen")+".";
			link.l1.go = "CaptainComission_94";
		break;		
		
		case "CaptainComission_94":
			iNation = FindEnemyNation2NationWithoutPirates(sti(pchar.GenQuest.CaptainComission.Nation));	// mitrokosta
			if(iNation == -1) iNation = rand(NON_PIRATES);
			pchar.GenQuest.CaptainComission.SlaveCity = FindAlliedColonyForNation(iNation, true);
			pchar.GenQuest.CaptainComission.EnemyNation = iNation;
			LAi_SetImmortal(npchar, true);// лесник . откатил .  и защиту  чтоб умники не убили.
			dialog.text = "Je n'ai aucune idee de ce qu'ils t'ont promis, mais voici le marche : emmene-moi a la taverne de "+XI_ConvertString("Colony"+pchar.GenQuest.CaptainComission.SlaveCity+"Gen")+", je serai vraiment en sécurité là-bas. En échange, je partagerai avec vous quelques informations que je possède.";
			link.l1 = "C'est bien, d'autant plus qu'ils n'ont rien promis jusqu'à présent. Viens avec moi, je te conduirai à mon navire.";
			link.l1.go = "CaptainComission_95";
			link.l2 = "Je ne vais pas m'attirer des ennuis pour des informations douteuses.";
			link.l2.go = "CaptainComission_96";
		break;	
		
		case "CaptainComission_95":
		AddQuestRecord("CaptainComission1", "12"); // поставил запись в СЖ лесник
			AddQuestUserData("CaptainComission1", "sSex", GetSexPhrase("",""));
			AddQuestUserData("CaptainComission1", "sSex1", GetSexPhrase("",""));
			AddQuestUserData("CaptainComission1", "sName", pchar.GenQuest.CaptainComission.SlaveName);
			AddQuestUserData("CaptainComission1", "sSum", pchar.GenQuest.CaptainComission.SlaveMoney);
			AddQuestUserData("CaptainComission1", "sCity", XI_ConvertString("Colony" + pchar.GenQuest.CaptainComission.SlaveCity + "Acc"));
			pchar.GenQuest.CaptainComission = "toEnemyTavern";
			DialogExit();
			AddDialogExitQuestFunction("CaptainComission_GeneratePatrol");
		break;
		
		case "CaptainComission_96":
			dialog.text = "Malheureusement, je ne peux pas te le révéler pour l'instant. Cela pourrait causer des ennuis à nous deux.";
			link.l1 = "Tout d'autant plus... Suis-moi et pas de bêtises, s'il te plaît. Considère-toi à nouveau sous arrestation.";
			link.l1.go = "CaptainComission_97";
		break;
		
		case "CaptainComission_97":	
            AddQuestRecord("CaptainComission1", "13");
			AddQuestUserData("CaptainComission1", "sSex", GetSexPhrase("",""));
			AddQuestUserData("CaptainComission1", "sName", pchar.GenQuest.CaptainComission.SlaveName);
			AddQuestUserData("CaptainComission1", "sSum", pchar.GenQuest.CaptainComission.SlaveMoney);		
			pchar.GenQuest.CaptainComission = "toTavern";
			DialogExit();
			AddDialogExitQuestFunction("CaptainComission_GeneratePatrol");
		break;
		
		case "CaptainComission_100":		
			dialog.text = "Merci, capitaine. Maintenant, je suis enfin en sécurité. Je ne vous offre pas d'argent, car je suis sûr que la connaissance et son application habile valent bien plus que le métal périssable.";
			link.l1 = "J'attends les informations";
			link.l1.go = "CaptainComission_101";
		break;
		
		case "CaptainComission_101":
			GetSlaveSpeciality();
			dialog.text = "La chose est que je suis un scientifique, spécialiste de "+pchar.GenQuest.CaptainComission.SlaveSpeciality+" et "+NationNamePeople(sti(pchar.GenQuest.CaptainComission.EnemyNation))+"m'avait proposé une coopération depuis un bon moment,"+"mais je suis un ingénieur militaire et je garde mes serments d'allégeance. Ils ont essayé de me voler, bien que les vrais problèmes aient commencé lorsque les pirates ont appris ma véritable identité et importance\n"+"À la fin, ils avaient réussi à me capturer, mais l'or était la seule chose qu'ils voulaient, ils n'ont jamais eu besoin de mon savoir. Mes amis et ennemis ont échoué à me racheter à temps et j'ai été vendu aux plantations. Vous connaissez la suite.";
			link.l1 = "Oui, malheur à l'esprit, comme on dit, en effet.";	
			link.l1.go = "CaptainComission_102";
		break;
		
		case "CaptainComission_102":
			switch(sti(pchar.GenQuest.CaptainComission.Speciality))
			{
				case 0:
					sTemp = "protecting your ship and its crew during combat.";
				break;	
				case 1:
					sTemp = "quickly reloading your cannons and firing aimed shot under conditions of dusting. ";
				break;					
				case 2:
					sTemp = "quickly managing the sails and maneuvering in combat.";
				break;					
			}
			dialog.text = "Eh bien, on pourrait dire ça. Alors, si tu prêtes attention à ce que je peux te dire, tu deviendras bien plus habile dans l'art de "+sTemp;
			link.l1 = "Merci, cette information est vraiment utile, en effet.";
			link.l1.go = "CaptainComission_103";
		break;
		
		case "CaptainComission_103":
			dialog.text = "Eh bien, adieu et merci pour tout.";
			link.l1 = "Merci à toi aussi. Adieu, et essaie de ne pas te faire prendre la prochaine fois.";
			link.l1.go = "CaptainComission_104";
		break;
		
		case "CaptainComission_104":
			AddQuestRecord("CaptainComission1", "21");
			CloseQuestHeader("CaptainComission1");
			// а теперь раздача слонов !!!!!!!
			switch(sti(pchar.GenQuest.CaptainComission.Speciality))
			{
				case 0:
					if(hrand(1) == 0) 
					{
						AddCharacterSkill(pchar, SKILL_DEFENCE, 10);
					}
					else
					{
						AddCharacterSkill(pchar, SKILL_REPAIR, 10);
					}					
				break;
				case 1:
					if(hrand(1) == 0) 
					{
						AddCharacterSkill(pchar, SKILL_CANNONS, 10);
					}
					else
					{
						AddCharacterSkill(pchar, SKILL_ACCURACY, 10);
					}	
				break;
				case 2:
					AddCharacterSkill(pchar, SKILL_SAILING, 10);
				break;
			}
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1_back", "none", "", "","OpenTheDoors", -1.0);
			NPChar.lifeDay = 0;
			DeleteAttribute(pchar,"GenQuest.CaptainComission");
			DialogExit();
		break;
		// Генератор "Captain's request"
		
		// Генератор "Operation 'Galleon'"
		case "CaptainComission_300":
			ReOpenQuestHeader("CaptainComission2");
			AddQuestRecord("CaptainComission2", "1");
			AddQuestUserData("CaptainComission2", "sName", pchar.GenQuest.CaptainComission.CapName);
			AddQuestUserData("CaptainComission2", "sShipType", GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.CaptainComission.ShipType),"Name") + "Gen"))); //ПРАВКА
			AddQuestUserData("CaptainComission2", "sShipName", pchar.GenQuest.CaptainComission.ShipTypeName);
			AddQuestUserData("CaptainComission2", "sCapName",  pchar.GenQuest.CaptainComission.Name);
			AddQuestUserData("CaptainComission2", "sCity1", XI_ConvertString("Colony" + pchar.GenQuest.CaptainComission.City + "Voc")); // belamour gen
			AddQuestUserData("CaptainComission2", "sShipTypeNom", GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.CaptainComission.ShipType),"Name"))));
			AddQuestUserData("CaptainComission2", "sCity2", XI_ConvertString("Colony" + pchar.GenQuest.CaptainComission.City1 + "Gen"));
			AddQuestUserData("CaptainComission2", "sCity11", XI_ConvertString("Colony" + pchar.GenQuest.CaptainComission.City + "Gen"));			
			SetFunctionLocationCondition("CaptainComission_GenerateQuestContinuation", GetArealByCityName(pchar.GenQuest.CaptainComission.City), false);
			SetFunctionTimerCondition("CaptainComission_TimeIsOver", 0, 0, 15, false);
			SaveCurrentQuestDateParam("GenQuest.CaptainComission");
			LAi_KillCharacter(NPChar);
			LAi_SetPlayerType(pchar); 
			pchar.GenQuest.CaptainComission = "Begin_1";
			LAi_EnableReload();
			Log_SetActiveAction("Reload");
			DialogExit();			
		break;
		
		// диалог с кэпом на палубе 
		case "CaptainComission_301":
		    if (!CheckAttribute(pchar,"GenQuest.pizdezh_uze_bil")) // проверка если разговор уже состоялся . чтобы не повторяться. лесник
			{
			pchar.quest.CaptainComission_TimeIsOver.over = "yes";
			dialog.text = RandPhraseSimple("Ahoy, je suis capitaine "+GetFullName(NPChar)+", qu'est-ce qui t'a amené sur le pont de mon navire '"+pchar.GenQuest.CaptainComission.ShipTypeName+"'?'","Ahoy, je suis toujours heureux d'avoir des invités sur mon navire. Capitaine "+GetFullName(NPChar)+" à votre service.");
			link.l1 = "Bonjour, je suis capitaine "+GetFullName(pchar)+", agissant au nom de quelque capitaine "+pchar.GenQuest.CaptainComission.CapName+"Il m'a demandé de vous dire que vous seriez arrêté dans "+XI_ConvertString("Colony"+pchar.GenQuest.CaptainComission.City+"Voc")+". Les autorités sont au courant de "+GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.CaptainComission.ShipTypeVictim),"Nom")+"Gen"))+"."; // ПРАВКА + belamour gen
			link.l1.go = "CaptainComission_302";
			break;
			}
			dialog.text = "Que diable fais-tu ici ? Nous avons tout arrangé ! Retourne sur ton navire !";
			link.l2 = "Euh..Ouais, c'est ça !";
			link.l2.go = "exit";
			NextDiag.TempNode = "CaptainComission_301"; // чтобы не было перехода на баг  - и т.д.  лесник 
			
		break;
		
		case "CaptainComission_302":
			dialog.text = "Ah, quel dommage ! Laisse-moi réfléchir\nEt où est le capitaine "+pchar.GenQuest.CaptainComission.CapName+"?";
			link.l1 = "Il est mort.";
			link.l1.go = "CaptainComission_303";
		break;
		
		case "CaptainComission_303":
			dialog.text = "Merde ! Les choses ne font qu'empirer... Écoute, "+GetFullName(pchar)+", je ne suis pas prêt à affronter un tel tournant des événements. Capitaine "+pchar.GenQuest.CaptainComission.CapName+" et j'ai accepté de rencontrer à "+XI_ConvertString("Colony"+pchar.GenQuest.CaptainComission.City+"Voc")+"Le plan était de charger du fret dans son navire. Maintenant que le capitaine est mort, je ne peux pas me montrer dans la colonie\nIl semble qu'il ne me reste plus qu'à te demander une faveur.";
			link.l1 = "Mon consentement dépendra du type d'aide dont tu as besoin.";
			link.l1.go = "CaptainComission_304";
		break;
		
		case "CaptainComission_304":
			pchar.GenQuest.CaptainComission.ShoreLocation = SelectQuestShoreLocationFromSea(GetArealByCityName(pchar.GenQuest.CaptainComission.City));
			dialog.text = "Aidez-moi avec des hommes et des chaloupes. J'ai besoin que la cargaison soit emportée de "+XI_ConvertString(pchar.GenQuest.CaptainComission.ShoreLocation+"Gen")+". Tu peux garder la part de la cargaison du défunt capitaine.";
			link.l1 = "Hmm... Apparemment, tu as mordu plus que tu ne pouvais avaler. J'ai besoin de plus d'informations.";
			link.l1.go = "CaptainComission_305";
			link.l2 = "Malheureusement, je ne suis pas en position de perdre du temps avec ça.";
			link.l2.go = "CaptainComission_306";
		break;
		
		case "CaptainComission_305":
			sTemp = GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.CaptainComission.ShipTypeVictim),"Name") + "Gen"));
			dialog.text = "D'accord, je te donnerai les détails\n"+"Lors d'une de mes patrouilles régulières, j'ai rencontré un navire sous le pavillon de "+NationNameGenitive(sti(pchar.GenQuest.CaptainComission.Nation))+"Ils avaient ignoré mes ordres de se rendre."+"Lorsque, après une courte poursuite, nous avions rattrapé "+sTemp+" '"+pchar.GenQuest.CaptainComission.VictimShipName+"' et ainsi ils ont hissé le pavillon noir. Le fort était assez loin, alors nous avons dû nous battre seuls. Ils ont détruit notre beaupré, c'est pourquoi nous n'avons pas pu éviter l'abordage.\n"+"C'était juste, mais nous avons réussi à tous les tuer grâce à la Sainte Marie et à une unité de mousquetaires. Imagine notre bonheur quand nous avons découvert que "+sTemp+" était rempli de. "+"Nous avons décidé que c'est une récompense décente pour nos blessures et la mort de nos camarades\nIl faisait déjà nuit, nous avons pris "+sTemp+" à la baie la plus proche et cacher la cargaison à terre. Ensuite, nous avions explosé "+sTemp+" et j'ai rapporté l'épave du navire pirate. Bien sûr, je n'ai pas mentionné la cargaison.";
			link.l1 = "Apparemment, quelqu'un a encore bavardé...";	
			link.l1.go = "CaptainComission_307";
		break;
		
		case "CaptainComission_306":
			dialog.text = "Quel dommage, capitaine... C'est dommage que vous ne soyez pas disposé à m'aider.";
			link.l1 = "Ce n'est pas une question de ma volonté, ma chère. Vous devez comprendre. Adieu.";
			link.l1.go = "CaptainComission_306End";			
		break;
		
		case "CaptainComission_306End":
			AddQuestRecord("CaptainComission2", "3");
			AddQuestUserData("CaptainComission2", "sSex", GetSexPhrase("",""));
			AddQuestUserData("CaptainComission2", "sName", pchar.GenQuest.CaptainComission.CapName);
			CloseQuestHeader("CaptainComission2");
			GetCharacterPos(pchar, &locx, &locy, &locz);
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", LAi_FindNearestLocator("reload", locx, locy, locz), "none", "", "", "", 1.5);			
			pchar.GenQuest.CaptainComission = "close";
			SetFunctionExitFromLocationCondition("CaptainComission_ExitFromLoc", pchar.location, false);
			DialogExit();
		break;
		
		case "CaptainComission_307":
			dialog.text = "Je ne pense pas que ce soient mes hommes. Très probablement, le propriétaire de la cargaison est impatient d'atténuer la douleur de la perte\nAlors ? Puis-je compter sur votre assistance ?";
			link.l1 = "Oui, ça semble bon.";
			link.l1.go = "CaptainComission_308";
			link.l2 = "Non, mon ami. Premièrement : je ne sais pas combien de cargaison ira dans ma cale. Et deuxièmement : il n'y a aucune garantie que les autorités ne l'aient pas déjà trouvé et emporté, tout en laissant une embuscade à la cachette.";
			link.l2.go = "CaptainComission_309";
		break;
		
		case "CaptainComission_308":
			dialog.text = "Rencontrons-nous à "+XI_ConvertString(pchar.GenQuest.CaptainComission.ShoreLocation+"Gen")+" puis, juste après minuit. Ma position actuelle nécessite d'être discret. Nous devons éviter les patrouilles."; // belamour gen
			link.l1 = "D'accord, attends-moi là-bas.";
			link.l1.go = "CaptainComission_313";
//			bQuestDisableMapEnter = true;
		break;
		
		case "CaptainComission_309":
			dialog.text = "Hélas, mais tu ne me laisses pas le choix. Un seul navire ne suffit pas pour emporter toute la cargaison. J'ai risqué ma carrière et ma propre vie pour cela. Assurément, ton équipage m'aidera volontiers en échange d'une part décente.";
			link.l1 = "Et que suggérez-vous?";
			link.l1.go = "CaptainComission_310";
		break;
		
		case "CaptainComission_310":
			dialog.text = "Je prendrai ton navire et te laisserai à "+XI_ConvertString(pchar.GenQuest.CaptainComission.ShoreLocation+"Gen")+"."; // belamour gen
			link.l1 = "Ton succes me semble improbable. Je retournerai a mon navire meme si je dois abattre tout ton equipage.";
			link.l1.go = "CaptainComission_311";
			link.l2 = "Il semble que je n'ai pas le choix. Eh bien, je me soumettrai à la violence...";
			link.l2.go = "CaptainComission_312";
		break;
		
		case "CaptainComission_311":
			pchar.GenQuest.CaptainComission.FightAfterDeck = true; //после резни на палубе - драка в море		
			GetCharacterPos(pchar, &locx, &locy, &locz);
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", LAi_FindNearestLocator("reload", locx, locy, locz), "none", "", "", "CaptainComission_FightInDeck", 3.5);
			DialogExit();
		break;
		
		case "CaptainComission_312":
			DialogExit();
			AddDialogExitQuestFunction("CaptainComission_toShore");
		break;
		
		case "CaptainComission_313": 		
			NextDiag.TempNode = "CaptainComission_314";
			NextDiag.CurrentNode = NextDiag.TempNode;
			AddQuestRecord("CaptainComission2", "7");
			AddQuestUserData("CaptainComission2", "sName", pchar.GenQuest.CaptainComission.Name);
			AddQuestUserData("CaptainComission2", "sGoods", GetStrSmallRegister(XI_ConvertString(Goods[sti(pchar.GenQuest.CaptainComission.Goods)].Name + "Gen")));
			AddQuestUserData("CaptainComission2", "sShoreName", XI_ConvertString(pchar.GenQuest.CaptainComission.ShoreLocation + "Gen"));
			AddQuestUserData("CaptainComission2", "sShoreNameDat", XI_ConvertString(pchar.GenQuest.CaptainComission.ShoreLocation + "Dat"));
			SetFunctionTimerCondition("CaptainComission_SailToShore", 0, 0, 1, false);
		    pchar.GenQuest.pizdezh_uze_bil = "true"; // лесник временная запоминалка для диалога 
			DialogExit();			
		break;
		
		case "CaptainComission_314":
			NextDiag.TempNode = "CaptainComission_314";
			dialog.text = "Capitaine, nous devons nous dépêcher. Je crains qu'une patrouille ne nous repère.";
			link.l1 = "D'accord, dépêchons-nous.";
			link.l1.go = "exit";
		break;
		
		case "CaptainComission_315":
			dialog.text = "Capitaine, ordonnez de lancer tous les canots de sauvetage. Nous devrons y aller plusieurs fois, et je crains qu'une patrouille ne vienne à l'anse.";
			link.l1 = "Ne t'inquiète pas, tout devrait bien se passer. Les bateaux arrivent déjà sur le rivage.";
			link.l1.go = "CaptainComission_316";
		break;
		
		case "CaptainComission_316":
			dialog.text = "Oh, bon sang. Maintenant, on a de la compagnie...";
			link.l1 = "Vraiment, si tu mentionnes un imbécile, il apparaîtra aussitôt...";
			link.l1.go = "exit";
			DeleteAttribute(pchar, "GenQuest.pizdezh_uze_bil"); // удаление проверки на повтор диалога лесник
			AddDialogExitQuestFunction("CaptainComission_GenerateShorePatrol");
		break;
		
		// диалог с патрулем на берегу
		case "CaptainComission_317":
			dialog.text = "Capitaine, nous cherchons un criminel de guerre "+pchar.GenQuest.CaptainComission.Name+", qui a dissimulé une cargaison précieuse aux autorités. Vos documents, s'il vous plaît.";
			link.l1 = "Quels documents, officier ? Nous avons débarqué pour reconstituer nos réserves d'eau douce.";
			link.l1.go = "CaptainComission_318";
		break;
		
		case "CaptainComission_318":
			dialog.snd = "Voice\COGU\COGU004"; 
			dialog.text = "Et le voilà, "+pchar.GenQuest.CaptainComission.Name+" lui-même . Rendez vos armes et suivez-moi, vous deux !";
			link.l1 = "C'était vraiment un très mauvais moment, officier...";
			link.l1.go = "CaptainComission_319";
		break;
		
		case "CaptainComission_319":
			DialogExit();
			for (i = 1; i <= sti(pchar.GenQuest.CaptainComission.SoldierQty); i++)
			{
    			sTemp = "SoldierIDX" + i;
				sld = GetCharacter(sti(pchar.GenQuest.CaptainComission.(sTemp)));
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "CoastalGuards");
            }
			
			LAi_group_SetHearRadius("CoastalGuards", 100.0);			
		    sld = characterFromId("CapComission_1");
			LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);		
			LAi_group_SetRelation("CoastalGuards", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("CoastalGuards", LAI_GROUP_PLAYER, true);
            LAi_SetFightMode(Pchar, true);
				
		break;
		
		case "CaptainComission_320":
		    pchar.quest.CaptainComission_Capitan_Cdoxul.over = "yes"; // лесник . снял событие если жив.
			pchar.GenQuest.CaptainComission.GoodsQty = makeint((sti(GetBaseShipParamFromType(sti(pchar.GenQuest.CaptainComission.ShipTypeVictim),"Capacity")) - sti(GetBaseShipParamFromType(sti(pchar.GenQuest.CaptainComission.ShipType),"Capacity")) + rand(250)) / sti(Goods[sti(pchar.GenQuest.CaptainComission.Goods)].Weight));	
			pchar.GenQuest.CaptainComission.GoodsQtyNorm = sti(pchar.GenQuest.CaptainComission.GoodsQty);
			dialog.text = "Nous devons nous dépêcher avant que les renforts n'arrivent ici. Le chargement est sur le point de se terminer, et ta part est "+pchar.GenQuest.CaptainComission.GoodsQty+" unités de "+GetStrSmallRegister(XI_ConvertString(Goods[sti(pchar.GenQuest.CaptainComission.Goods)].Name+"Général"))+".";
			link.l1 = "Excellent. Il est temps de partir maintenant. C'était un plaisir de faire affaire avec vous.";
			link.l1.go = "CaptainComission_321";
		break;
		
		case "CaptainComission_321":		
			iTmp = FindNonEnemyColonyForAdventure(sti(pchar.GenQuest.CaptainComission.Nation),pchar.GenQuest.CaptainComission.City, true);			
			sTemp = Colonies[iTmp].id;
			pchar.GenQuest.CaptainComission.ConvoyIsland = GetArealByCityName(sTemp);
			pchar.GenQuest.CaptainComission.ConvoyShore = SelectQuestShoreLocationFromSea(pchar.GenQuest.CaptainComission.ConvoyIsland);
			pchar.GenQuest.CaptainComission.ConvoyCity = sTemp;
			dialog.text = "Et juste une demande de plus. Les autorités vont sûrement nous poursuivre, pourriez-vous escorter mon navire jusqu'à "+XI_ConvertString(pchar.GenQuest.CaptainComission.ConvoyShore+"Gén")+", qui est sur "+XI_ConvertString(GetIslandByCityName(sTemp)+"Voc")+"?"; // belamour gen
			link.l1 = "Non, mon ami, désormais chacun pour soi. Adieu...";
			link.l1.go = "CaptainComission_322";
			if (GetCompanionQuantity(pchar) < COMPANION_MAX)
			{
				link.l2 = "Bien sûr, je pourrais faire cela pour une bonne récompense.";
				link.l2.go = "CaptainComission_323";
			}				
		break;
		
		case "CaptainComission_322":
			Group_DeleteGroup("Sea_CapComission_1"); 
			sld = characterFromId("CapComission_1");
			GetCharacterPos(pchar, &locx, &locy, &locz);
			LAi_SetActorType(sld);
			LAi_ActorGoToLocation(sld, "reload", LAi_FindNearestFreeLocator("reload", locx, locy, locz), "none", "", "", "OpenTheDoors", 5.0);
			sld.lifeDay = 0; 	
			CaptainComission_GenerateCoastalPatrol();
			iGoods = GetSquadronFreeSpace(pchar, sti(pchar.GenQuest.CaptainComission.Goods)); 
			if(iGoods < sti(pchar.GenQuest.CaptainComission.GoodsQty)) pchar.GenQuest.CaptainComission.GoodsQty = iGoods;
			SetCharacterGoods(pchar, sti(pchar.GenQuest.CaptainComission.Goods), GetCargoGoods(pchar, sti(pchar.GenQuest.CaptainComission.Goods)) + sti(pchar.GenQuest.CaptainComission.GoodsQty));// перегруз
			AddQuestRecord("CaptainComission2", "10");
			AddQuestUserData("CaptainComission2", "sGoodsQuantity", pchar.GenQuest.CaptainComission.GoodsQty);
			AddQuestUserData("CaptainComission2", "sGoods", GetStrSmallRegister(XI_ConvertString(Goods[sti(pchar.GenQuest.CaptainComission.Goods)].Name + "Gen")));
			CloseQuestHeader("CaptainComission2");	
			DeleteAttribute(pchar, "GenQuest.CaptainComission");		
			DialogExit();
		break;
		
		case "CaptainComission_323":
			sld = characterFromId("CapComission_1");
			Fantom_SetCharacterGoods(sld, sti(pchar.GenQuest.CaptainComission.Goods), GetCargoFreeSpace(sld), 1);
			pchar.GenQuest.CaptainComission.ConvoyMoney = makeint((sti(pchar.rank)*100 + sti(NPChar.rank)*170 + hRand(30)*20) * 2.5);
			pchar.GenQuest.CaptainComission.iDay  = 15 + hRand(10);
			iGoods = GetSquadronFreeSpace(pchar, sti(pchar.GenQuest.CaptainComission.Goods)); 
			if(iGoods < sti(pchar.GenQuest.CaptainComission.GoodsQty)) pchar.GenQuest.CaptainComission.GoodsQty = iGoods;
			SetCharacterGoods(pchar, sti(pchar.GenQuest.CaptainComission.Goods), GetCargoGoods(pchar, sti(pchar.GenQuest.CaptainComission.Goods)) + sti(pchar.GenQuest.CaptainComission.GoodsQty));// перегруз
			dialog.text = "Bien sûr. Pour l'escorte, je suis prêt à payer  "+pchar.GenQuest.CaptainComission.ConvoyMoney+" pesos. Mais il y a une autre condition, cela ne devrait pas prendre plus de "+pchar.GenQuest.CaptainComission.iDay+" jours. C'est important.";	
			link.l1 = "D'accord. Partons immédiatement.";
			link.l1.go = "CaptainComission_324";
			NextDiag.TempNode = "CaptainComission_325";
			NextDiag.CurrentNode = NextDiag.TempNode;
		break;
		
		case "CaptainComission_324":
			pchar.GenQuest.CannotWait = 1; // лочим интерфейс отдыха 
			sld = characterFromId("CapComission_1");
			sTemp = LAi_FindNearestFreeLocator2Pchar("reload");
			LAi_SetActorType(sld);
			LAi_ActorSetStayMode(sld);
			CharacterIntoCompanionAndGoOut(pchar, sld, "reload", sTemp, 5, false);
			SetShipRemovable(sld, false);
			SetCharacterRemovable(sld, false);
			Group_ChangeCharacter(PLAYER_GROUP, "CapComission_1");
			AddQuestRecord("CaptainComission2", "11");
			AddQuestUserData("CaptainComission2", "sSex", GetSexPhrase("",""));
			AddQuestUserData("CaptainComission2", "sGoodsQuantity", pchar.GenQuest.CaptainComission.GoodsQty);
			AddQuestUserData("CaptainComission2", "sGoods", GetStrSmallRegister(XI_ConvertString(Goods[sti(pchar.GenQuest.CaptainComission.Goods)].Name + "Gen")));		
			AddQuestUserData("CaptainComission2", "sName", pchar.GenQuest.CaptainComission.Name);
			AddQuestUserData("CaptainComission2", "sShoreName", XI_ConvertString(pchar.GenQuest.CaptainComission.ConvoyShore + "Gen"));
			AddQuestUserData("CaptainComission2", "sShoreType", XI_ConvertString(GetIslandByCityName(pchar.GenQuest.CaptainComission.ConvoyCity) + "Voc")); // belamour gen
			AddQuestUserData("CaptainComission2", "sSum", pchar.GenQuest.CaptainComission.ConvoyMoney);
			CaptainComission_GenerateCoastalPatrol();
			pchar.quest.CaptainComission_MapEnter.win_condition.l1 = "MapEnter";
			pchar.quest.CaptainComission_MapEnter.function = "CaptainComission_MapEnter"; 
			pchar.quest.CaptainComission_CapShip_Sink.win_condition.l1 = "Character_sink";
			pchar.quest.CaptainComission_CapShip_Sink.win_condition.l1.character = "CapComission_1";
			pchar.quest.CaptainComission_CapShip_Sink.function = "CaptainComission_CapShip_Sink";
			DialogExit();
		break;
		
		case "CaptainComission_325":
			NextDiag.TempNode = "CaptainComission_314";
			dialog.text = LinkRandPhrase("Capitaine, nous perdons du temps. Ils pourraient nous trouver à tout moment.","Capitaine, nous courons contre la montre. N'oubliez pas qu'ils me cherchent.","Capitaine, nous ne devons pas traîner. Mon navire est trop grand pour éviter l'attention des patrouilles.");
			link.l1 = LinkRandPhrase("Oui, tu as raison. Nous devons nous dépêcher.","Alors, embarquez-vous dans les bateaux sans plus tarder.","C'est ça... Rassemblez vos hommes. Nous partons.");
			link.l1.go = "exit";
		break;
		
		case "CaptainComission_326_0":
			dialog.text = "Capitaine, je dois parler à mes hommes.";
			link.l1 = "Allez-y.";
			link.l1.go = "exit";
			InterfaceStates.Buttons.Save.enable = false; 
			AddDialogExitQuestFunction("CaptainComission_DialogInShore");
		break;
		
		case "CaptainComission_326":
			sld = characterFromId("Blaze");
			dialog.text = "Je te salue, capitaine "+pchar.CaptainComission.Name+". Alors, as-tu apporté toute la cargaison ? Et où est le capitaine "+pchar.CaptainComission.CapName+" ?";
			link.l1 = pchar.CaptainComission.CapName+" est mort. J'ai dû demander "+NPCharSexPhrase(sld,"ce gentilhomme","cette dame")+" pour de l'aide. Je vais vous présenter, c'est le capitaine "+pchar.CaptainComission.FullName+".";
			link.l1.go = "CaptainComission_327";
		break;
		
		case "CaptainComission_327":
			sld = characterFromId("Blaze");
			dialog.text = "Et "+NPCharSexPhrase(sld,"qui est-il ? Est-ce qu'il","qui est-elle ? Est-ce qu'elle")+" au courant de nos affaires ?";
			link.l1 = "Généralement, oui. Mais il y a un problème -"+NPCharSexPhrase(sld,"il en est certain","elle en est certaine")+", que la moitié de la cargaison appartient à "+NPCharSexPhrase(sld,"lui","elle")+". Nous devons convaincre "+NPCharSexPhrase(sld,"lui","elle")+", que ce n'est pas exactement le cas.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("CaptainComission_GangDialog");
		break;
		
		case "CaptainComission_328":
			dialog.text = "Mon ami "+GetFullName(pchar)+", vous avez déjà entendu tout ce que vous deviez savoir. Nous devons accéder à votre cale.";
			link.l1 = "Et tu penses que mes gars vont rester là à regarder, pendant que des va-nu-pieds vident leur cale ?";
			link.l1.go = "CaptainComission_329";
		break;
		
		case "CaptainComission_329":
			pchar.GenQuest.CaptainComission.GoodsSum = 2 * sti(pchar.GenQuest.CaptainComission.GoodsQtyNorm) * sti(Goods[sti(pchar.GenQuest.CaptainComission.Goods)].Cost);
			dialog.text = "Vous n'avez pas tort. De l'argent liquide, disons, "+pchar.GenQuest.CaptainComission.GoodsSum+"pesos, nous dispenseront de la nécessité de croiser le fer avec ton équipage. N'oublie pas que cela couvre la moitié de notre cargaison, donc tout est équitable. Si tu acceptes, alors personne ne sera blessé.";
			link.l1 = "Et que se passe-t-il si je refuse?";
			link.l1.go = "CaptainComission_330";
		break;
		
		case "CaptainComission_330":
			dialog.text = "Dans ce cas, la violence est inévitable. Vous serez la première victime et vous trouverez la paix dans cette crique douillette, et votre équipage sera tout simplement incapable de venir à votre secours... Comment cela vous plairait-il ?";
			link.l1 = "Tu ne me laisses pas le choix. Eh bien, je vais simplement tous vous tuer.";
			link.l1.go = "CaptainComission_331";
			if(sti(pchar.money) >= sti(pchar.GenQuest.CaptainComission.GoodsSum))
			{
				link.l2 = "Je pense que je n'ai pas le choix. D'accord, voici votre argent.";
				link.l2.go = "CaptainComission_332";
			}	
		break;
		
		case "CaptainComission_331":
			dialog.text = "Eh bien, c'est une décision appropriée pour "+GetSexPhrase("un noble gentilhomme","une dame vaillante")+".";
			link.l1 = "Arrête de philosopher ! Passons aux affaires !";
			link.l1.go = "CaptainComission_334";
			CaptainComission_ChangeCaptain();
		break;
		
		case "CaptainComission_332":
			dialog.text = "Une sage décision. Bonne chance à vous.";
			link.l1 = "Que tu t'en étouffes...";
			link.l1.go = "CaptainComission_333";
		break;
		
		case "CaptainComission_333":
		    LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);// лесник - разрешить снова драться после сдачи денег. но после драки кулаками не машут ..как говориться))
			addMoneyToCharacter(pchar, -sti(pchar.GenQuest.CaptainComission.GoodsSum));
			AddQuestRecord("CaptainComission2", "17");
			AddQuestUserData("CaptainComission2", "sName", pchar.GenQuest.CaptainComission.Name);
			AddQuestUserData("CaptainComission2", "sShoreName", UpperFirst(XI_ConvertString(pchar.GenQuest.CaptainComission.ConvoyShore + "Gen")));
			AddQuestUserData("CaptainComission2", "sSum", pchar.GenQuest.CaptainComission.GoodsSum);
			CloseQuestHeader("CaptainComission2");	
			ChangeOfficersLoyality("bad_all", 1);
			DialogExit();
			AddDialogExitQuestFunction("CaptainComission_GangExit");
		break;

		case "CaptainComission_334":
			LAi_SetPlayerType(pchar);
			sTemp = "Gang_";
			sGroup = "GangGroup_0";			
			LAi_LocationFightDisable(&locations[FindLocation(pchar.GenQuest.CaptainComission.ConvoyShore)], false);	
			iTemp = sti(pchar.GenQuest.CaptainComission.GangNum);
			chrDisableReloadToLocation = true;
			rChar = CharacterFromID("CapComission_1");
			LAi_SetWarriorType(rChar);
			LAi_group_MoveCharacter(rChar, sGroup);
			for(i = 0; i < iTemp; i++)
			{
				rChar = CharacterFromID(sTemp + i);
				LAi_SetWarriorType(rChar);
				LAi_group_MoveCharacter(rChar, sGroup);
				LAi_SetImmortal(rChar, false);
			}			
			LAi_group_SetRelation(sGroup, LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups(sGroup, LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck(sGroup, "OpenTheDoors"); 
			LAi_group_SetCheckFunction(sGroup, "CaptainComission_GangDied");
			DialogExit();	
			AddDialogExitQuest("MainHeroFightModeOn");		
		break;

		case "CaptainComission_340":
			dialog.text = "Capitaine "+GetFullName(pchar)+", nous sommes en retard. J'espère que vous comprenez que vous n'êtes désormais pas éligible pour une récompense.";
			link.l1 = "Bien sûr que oui. J'ai déjà gagné un bon paquet, grâce à toi. Adieu...";
			link.l1.go = "CaptainComission_341";
		break;
		
		case "CaptainComission_341":
			Group_DeleteGroup("Sea_CapComission_1");			
			LAi_SetImmortal(NPChar, true);
			GetCharacterPos(pchar, &locx, &locy, &locz);
			LAi_SetActorType(NPChar);
			LAi_ActorGoToLocation(NPChar, "reload", LAi_FindNearestLocator("reload", locx, locy, locz), "none", "", "", "OpenTheDoors", 5.0);
			NPChar.lifeDay = 0; 						
			AddQuestRecord("CaptainComission2", "15");
			AddQuestUserData("CaptainComission2", "sSex", GetSexPhrase("",""));
			AddQuestUserData("CaptainComission2", "sSex1", GetSexPhrase("",""));
			AddQuestUserData("CaptainComission2", "sShipType", GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.CaptainComission.ShipType),"Name")))); 
			AddQuestUserData("CaptainComission2", "sShipName", pchar.GenQuest.CaptainComission.ShipTypeName);
			AddQuestUserData("CaptainComission2", "sName", pchar.GenQuest.CaptainComission.Name);
			CloseQuestHeader("CaptainComission2");	
			DeleteAttribute(pchar, "GenQuest.CaptainComission");					
			DialogExit();
		break;
		
		case "CaptainComission_Canoneer":
			dialog.text = "Achèteriez-vous du rhum pour un vieux soldat qui a beaucoup souffert dans les batailles pour la gloire de la Couronne ?";
			link.l1 = "Patron! Sers-nous du rhum!";
			link.l1.go = "exit";
			NextDiag.TempNode = "CaptainComission_Canoneer1";
			NextDiag.CurrentNode = NextDiag.TempNode;
			AddDialogExitQuest("CaptainComission_TalkCanoneer");
		break;
		
		case "CaptainComission_Canoneer1":
			dialog.text = "Oh, merci, "+GetAddress_Form(pchar)+", très aimable de ta part de traiter un handicapé qui avait complètement perdu la mémoire...";
			link.l1 = "Completement, tu dis?";
			link.l1.go = "CaptainComission_Canoneer2";
		break;
		
		case "CaptainComission_Canoneer2":
			dialog.text = "Absolument, ma mie"+GetSexPhrase("ter","s")+" capitaine... entièrement. Je ne me souviens de rien sauf d'un boulet qui m'a frappé directement à la tête. Regardez le trou qu'il y a fait, je suppose que toute ma mémoire a dû s'en échapper.";
			link.l1 = "Mon gars, garde tes histoires pathétiques pour les bonnes femmes. J'ai vu des gens qui ont pris un coup direct de mitraille, leur mémoire a été complètement effacée... avec leurs têtes... Et toi, tu parles de quelque chaîne imaginaire. Parlons plutôt du capitaine "+pchar.GenQuest.CaptainComission.Name+". ";
			link.l1.go = "CaptainComission_Canoneer3";
		break;
		
		case "CaptainComission_Canoneer3":
			dialog.text = "Oh, eh bien, vous savez. Je dois bien gagner ma vie d'une manière ou d'une autre. Quant au capitaine "+pchar.GenQuest.CaptainComission.Name+", y a pas d'profit pour moi à jacter... Si j'facturais cent pièces pour chaque question à son sujet, j'aurais plus d'or maintenant que l'gouverneur n'en amasse de ses sujets en un an... ";
			link.l1 = "Avez-vous essayé de vendre la cargaison, cachée par ce capitaine ?";
			link.l1.go = "CaptainComission_Canoneer4";
		break;
		
		case "CaptainComission_Canoneer4":
			dialog.text = "Quoi ? Encore un fouineur ? Je te le dis encore une fois, je ne me souviens d'aucun capitaine "+pchar.GenQuest.CaptainComission.Name+"! Je suis contusionné, et j'ai le certificat du médecin pour le prouver ! Que voulez-vous de plus ?!";
			link.l1 = "Woah, ne t'emballe pas. Tu sais... Il était trop tard. Capitaine "+pchar.GenQuest.CaptainComission.CapName+"m'a demandé de dire que "+pchar.GenQuest.CaptainComission.Name+" ne devrait pas montrer son visage dans cette colonie, les autorités connaissent les circonstances de la destruction de "+GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.CaptainComission.ShipTypeVictim),"Nom")+"Acc"))+" ' "+pchar.GenQuest.CaptainComission.VictimShipName+", et il sera arrêté.";
			link.l1.go = "CaptainComission_Canoneer5";
		break;
		
		case "CaptainComission_Canoneer5":
			dialog.text = "Fichtre. Tu aurais dû le dire tout de suite et ne pas tourner autour du pot. C'est moi qui ai demandé au capitaine "+pchar.GenQuest.CaptainComission.CapName+"pour intercepter notre navire à son retour."+"Il a été déplacé sur les quais juste après ce foutu combat. Que faisait ce maudit pirate là-bas avec sa marchandise ? Tant de gars sont morts à cause de lui.";
			link.l1 = "Et comment as-tu réussi à survivre ?";
			link.l1.go = "CaptainComission_Canoneer6";	
		break;
		
		case "CaptainComission_Canoneer6":
			dialog.text = "Par erreur. Pour être honnête, par ma propre foutue erreur. Je n'ai pas été assez rapide, donc notre chaloupe n'a pas pu sortir de la zone dangereuse. J'étais le seul à en souffrir cependant. J'ai été frappé par une épave et jeté à l'eau. Je ne me souviens même pas comment j'ai atteint le rivage.";
			link.l1 = "Et comment as-tu réussi à te tirer de l'enquête ?";
			link.l1.go = "CaptainComission_Canoneer7";
		break;
		
		case "CaptainComission_Canoneer7":
			dialog.text = "Je leur ai dit que j'avais été contusionné lors de l'abordage et que je ne savais rien à propos de la cargaison. J'ai aussi fait semblant d'être simple d'esprit, vous savez, je viens tout juste de retrouver mes esprits, juste avant l'arrivée de "+GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.CaptainComission.ShipType),"Nom")+"D'accord"))+"Je ne pouvais pas bouger correctement, ma coordination était foutue.";
			link.l1 = "Eh bien, mais qui donc avait craché le morceau sur la cargaison, de toute façon ?";
			link.l1.go = "CaptainComission_Canoneer8";
		break;
		
		case "CaptainComission_Canoneer8":
			dialog.text = "Les pirates ont envoyé une lettre au gouverneur, prétendument au nom du marchand blessé. Ils ont décidé de prendre vengeance sur le capitaine pour son obstination. C'était sa faute, sa maudite obstination à nous mener dans ce pétrin.";
			link.l1 = "Mais comment as-tu rencontré ce pirate en premier lieu ?";
			link.l1.go = "CaptainComission_Canoneer9";
		break;
		
		case "CaptainComission_Canoneer9":
			dialog.text = "Je ne sais pas. C'était une patrouille ordinaire et il y avait un navire ordinaire naviguant sous le pavillon de "+NationNameGenitive(sti(pchar.GenQuest.CaptainComission.Nation))+". Je n'ai aucune idée pourquoi le capitaine a décidé de l'inspecter, mais ils n'ont prêté aucune attention à un coup de semonce, et quand nous les avons rattrapés, ils ont hissé le 'Jolly Roger'. "+"Nous n'avions pas le soutien du fort, donc le combat n'était pas facile. Puis la partie abordage. Je ne sais toujours pas comment nous avons réussi à les vaincre.\n"+"Eh bien, et nous avons vu tout ce précieux chargement. Le diable en personne a dû nous le donner. Nous avons dû cacher la cargaison à terre et faire sauter le navire capturé jusqu'au ciel. Elle était trop endommagée.";
			link.l1 = "N'as-tu pas peur que tous tes efforts et sacrifices soient vains, si les hommes du gouverneur découvrent la cachette ?";	
			link.l1.go = "CaptainComission_Canoneer10";
		break;
		
		case "CaptainComission_Canoneer10":
			iTmp = FindNonEnemyColonyForAdventure(sti(pchar.GenQuest.CaptainComission.Nation),pchar.GenQuest.CaptainComission.City, true);			
			pchar.GenQuest.CaptainComission.CanoneerCity = Colonies[iTmp].id;			
			pchar.GenQuest.CaptainComission.Sum = 20000 + 2000 * sti(pchar.rank);
			dialog.text = "Ils ne le trouveront pas. J'ai bien fait sauter l'entrée de la grotte, après tout, j'étais le meilleur expert en explosifs de tout l'escadron. Seuls les contrebandiers peuvent trouver ma cachette, ils connaissent chaque recoin de cet endroit.\n"+"Ecoute, moi-même je n'ai aucune idée de quoi faire avec le butin. Je ne peux ni le vendre ni le déplacer tout seul. En plus, personne ne fera affaire avec un crâne fendu. Je ne veux pas gagner de l'argent sur la mort de mes camarades d'équipage, mais je peux te dire l'emplacement de la cachette pour "+pchar.GenQuest.CaptainComission.Sum+"  pesos si tu me conduis à "+XI_ConvertString("Colony"+pchar.GenQuest.CaptainComission.CanoneerCity)+".";
			if(sti(pchar.money) >= sti(pchar.GenQuest.CaptainComission.Sum))	
			{
				link.l1 = "Je suis d'accord. Voici votre argent. Maintenant, parlez.";	
				link.l1.go = "CaptainComission_Canoneer11";
			}
			else
			{
				link.l1 = "Merde ! D'accord, attends ici, je vais chercher l'argent.";
				link.l1.go = "CaptainComission_Canoneer12";				
			}	
			link.l2 = "C'est trop, camarade. De plus, je n'ai pas de navire approprié. Eh bien, bonne chance à toi et adieu...";
			link.l2.go = "CaptainComission_Canoneer13";
		break;
		
		case "CaptainComission_Canoneer11":
			addMoneyToCharacter(pchar, -sti(pchar.GenQuest.CaptainComission.Sum));
			pchar.GenQuest.CaptainComission.ConvoyShore = SelectQuestShoreLocationFromSea(GetArealByCityName(pchar.GenQuest.CaptainComission.City));
			pchar.GenQuest.CaptainComission.GoodsQty = makeint(sti(GetBaseShipParamFromType(sti(pchar.GenQuest.CaptainComission.ShipTypeVictim),"Capacity")) / sti(Goods[sti(pchar.GenQuest.CaptainComission.Goods)].Weight));
			dialog.text = "Eh bien, très bien. Rendez-vous ce soir après minuit aux alentours de "+XI_ConvertString(pchar.GenQuest.CaptainComission.ConvoyShore+"Gen")+". Et assure-toi d'avoir de la place dans ta cale pour "+pchar.GenQuest.CaptainComission.GoodsQty+" pcs. "+GetStrSmallRegister(XI_ConvertString(Goods[sti(pchar.GenQuest.CaptainComission.Goods)].Name+"Gen"))+". Ce serait dommage d'en jeter une partie..."; // belamour gen
			link.l1 = "Je m'occuperai de ça. On se voit dans la crique...";
			link.l1.go = "CaptainComission_Canoneer14";
		break;
		
		case "CaptainComission_Canoneer12":
			AddQuestRecord("CaptainComission2", "41");
			AddQuestUserData("CaptainComission2", "sShipType", GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.CaptainComission.ShipType),"Name") + "Gen"))); //Gen лесник
			AddQuestUserData("CaptainComission2", "sShipName", pchar.GenQuest.CaptainComission.ShipTypeName);			
			AddQuestUserData("CaptainComission2", "sSum", pchar.GenQuest.CaptainComission.Sum);
			AddQuestUserData("CaptainComission2", "sName", GetName( NAMETYPE_ORIG, pchar.GenQuest.CaptainComission.CanoneerName, NAME_NOM));
			SetFunctionTimerCondition("CaptainComission_CanoneerWaitMoney", 0, 0, 1, false);
			NextDiag.TempNode = "CaptainComission_Canoneer15";
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			AddDialogExitQuest("CaptainComission_exit_sit");
		break;
		
		case "CaptainComission_Canoneer13":
			AddQuestRecord("CaptainComission2", "40");
			AddQuestUserData("CaptainComission2", "sSex", GetSexPhrase("",""));
			AddQuestUserData("CaptainComission2", "sShipType", GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.CaptainComission.ShipType),"Name") + "Gen"))); // belamour gen
			AddQuestUserData("CaptainComission2", "sShipName", pchar.GenQuest.CaptainComission.ShipTypeName);			
			AddQuestUserData("CaptainComission2", "sName", GetName( NAMETYPE_ORIG, pchar.GenQuest.CaptainComission.CanoneerName, NAME_NOM));
			AddQuestUserData("CaptainComission2", "sShipTypeQuest", GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.CaptainComission.ShipTypeVictim),"Name") + "Gen"))); // belamour gen
			AddQuestUserData("CaptainComission2", "sShipNameQuest", pchar.GenQuest.CaptainComission.VictimShipName);
			CloseQuestHeader("CaptainComission2");
			LAi_CharacterDisableDialog(NPChar);
			pchar.GenQuest.CaptainComission = "close";
			SetFunctionExitFromLocationCondition("CaptainComission_ExitFromLoc", pchar.location, false);
			DialogExit();
			AddDialogExitQuest("CaptainComission_exit_sit");
		break;
		
		case "CaptainComission_Canoneer14":
			AddQuestRecord("CaptainComission2", "43");
			AddQuestUserData("CaptainComission2", "sShipType", GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.CaptainComission.ShipType),"Name") + "Gen"))); 
			AddQuestUserData("CaptainComission2", "sShipName", pchar.GenQuest.CaptainComission.ShipTypeName);			
			AddQuestUserData("CaptainComission2", "sName", GetName( NAMETYPE_ORIG, pchar.GenQuest.CaptainComission.CanoneerName, NAME_NOM));
			AddQuestUserData("CaptainComission2", "sShipTypeQuest", GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.CaptainComission.ShipTypeVictim),"Name") + "Gen")));
			AddQuestUserData("CaptainComission2", "sShipNameQuest", pchar.GenQuest.CaptainComission.VictimShipName);
			AddQuestUserData("CaptainComission2", "sSum", pchar.GenQuest.CaptainComission.GoodsQty);
			AddQuestUserData("CaptainComission2", "sGoods", GetStrSmallRegister(XI_ConvertString(Goods[sti(pchar.GenQuest.CaptainComission.Goods)].Name + "Gen")));
			AddQuestUserData("CaptainComission2", "sShoreName", XI_ConvertString(pchar.GenQuest.CaptainComission.ConvoyShore + "Dat"));	// belamour gen
			LAi_CharacterDisableDialog(NPChar);
			SetFunctionTimerConditionParam("CaptainComission_TimeIsOver", 0, 0, 1, MakeInt(24 - GetHour()), false);
			SetFunctionTimerCondition("CaptainComission_MeetCanoneerInShoreTimer", 0, 0, 1, false);
			DialogExit();
			AddDialogExitQuest("CaptainComission_exit_sit");
		break;
		
		case "CaptainComission_Canoneer15":
			if(sti(pchar.money) >= sti(pchar.GenQuest.CaptainComission.Sum))	
			{
				dialog.text = "Et te voilà, enfin. Je commençais déjà à m'inquiéter. Je pensais que tu allais me livrer aux autorités.";
				link.l1 = "Je n'ai pas encore perdu la tête. Voici votre argent. Maintenant, c'est votre parole.";
				pchar.quest.CaptainComission_CanoneerWaitMoney.over = "yes";// лесник . снят таймер ожилания бабла
				link.l1.go = "CaptainComission_Canoneer11";
			}	
			else
			{
				dialog.text = "Alors, où est l'argent ?";	
				link.l1 = "Bon sang! D'accord, attends ici, je vais le chercher.";
				link.l1.go = "exit";
				NextDiag.TempNode = "CaptainComission_Canoneer15";
				NextDiag.CurrentNode = NextDiag.TempNode;
			}
		break;
		
		case "CaptainComission_350":
			dialog.text = "Capitaine, apparemment, nous sommes en retard. Les contrebandiers ont trouvé la cachette.";
			link.l1 = "Je ne vais pas renoncer à mon butin, même le diable en personne ne me l'arrachera pas.";
			link.l1.go = "CaptainComission_351";
			link.l2 = "Je démissionne, débrouille-toi avec tes concurrents tout seul.";	
			link.l2.go = "CaptainComission_352";
		break;
		
		case "CaptainComission_351":
			DialogExit();
			AddDialogExitQuest("CaptainComission_GangDialog_1");
		break;
		
		case "CaptainComission_352":
			DialogExit();
			//SetFunctionExitFromLocationCondition("CaptainComission_NoGangDialog", pchar.location, false);
			 AddDialogExitQuestFunction("CaptainComission_NoGangDialog");   // лесник - исправлено . предыдцщий код не работал
		break;
		
		case "CaptainComission_360":
			dialog.text = "Capitaine, nous avons une affaire sérieuse ici. Je vous conseille de retirer votre escadron avant que nos navires n'arrivent.";
			link.l1 = "Messieurs, on dirait que vous essayez de prendre ce qui ne vous appartient pas.";
			link.l1.go = "CaptainComission_361";
		break;
		
		case "CaptainComission_361":
			dialog.text = "Oh, vraiment ?! As-tu une idée de à qui tu parles ?";
			link.l1 = "Je te parle, l'ami. Ce chargement, il a un propriétaire légitime, et je le représente.";
			link.l1.go = "CaptainComission_362";
		break;
		
		case "CaptainComission_362":
			dialog.text = "Nous ne permettrons pas que tu t'immisces dans nos affaires, même si tu étais le Messie de notre Dieu ! Dégage le chenal, si tu tiens à ta vie ?";
			link.l1 = "Ne me suis-je pas fait comprendre? Cette cargaison est à moi, et je ne partirai pas sans elle!";
			link.l1.go = "CaptainComission_363";
		break;
		
		case "CaptainComission_363":
			dialog.text = "Que diable! Si tu le veux tant, alors tu l'attendras ici, pour l'éternité!";
			link.l1 = "Le destin décidera qui restera ici pour toujours.";
			link.l1.go = "CaptainComission_364";
		break;
				
		case "CaptainComission_364":
			LAi_SetPlayerType(pchar);
			sTemp = "Gang_";
			sGroup = "GangGroup_0";			
			LAi_LocationFightDisable(&locations[FindLocation(pchar.GenQuest.CaptainComission.ConvoyShore)], false);	
			iTemp = sti(pchar.GenQuest.CaptainComission.GangNum);
			chrDisableReloadToLocation = true;
			if(pchar.GenQuest.CaptainComission.variant == "A2")
			{
				rChar = CharacterFromID("CapComission_1");
				LAi_SetWarriorType(rChar);
				LAi_group_MoveCharacter(rChar, LAI_GROUP_PLAYER);						
			}
			if(pchar.GenQuest.CaptainComission.variant == "A3")
			{
				rChar = CharacterFromID("CapComission_Canoneer");
				//LAi_SetWarriorType(rChar);
				LAi_SetImmortal(rChar, false);
				LAi_group_MoveCharacter(rChar, LAI_GROUP_PLAYER);			
			}	
			for(i = 0; i < iTemp; i++)
			{
				rChar = CharacterFromID(sTemp + i);
				LAi_SetWarriorType(rChar);
				LAi_group_MoveCharacter(rChar, sGroup);
				LAi_SetImmortal(rChar, false);
			}			
			LAi_group_SetRelation(sGroup, LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups(sGroup, LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck(sGroup, "OpenTheDoors"); 
			if(pchar.GenQuest.CaptainComission.variant == "A2")
			{
				LAi_group_SetCheckFunction(sGroup, "CaptainComission_CheckCaptainAfterBattle");
			}
			if(pchar.GenQuest.CaptainComission.variant == "A3")
			{
				LAi_group_SetCheckFunction(sGroup, "CaptainComission_CheckGangAfterBattle");
			}	
			DialogExit();	
			AddDialogExitQuest("MainHeroFightModeOn");						
		break;
		
		case "CaptainComission_365":
			dialog.text = "Capitaine, ordonnez à vos hommes de se dépêcher, une patrouille peut arriver à tout moment. De plus, les contrebandiers attendaient évidemment leurs transports aussi.";
			link.l1 = "Oui, nous devons nous dépêcher... Chargez la cargaison dans les cales, et filons d'ici.";
			link.l1.go = "exit";
			NextDiag.TempNode = "CaptainComission_365";
			NextDiag.CurrentNode = NextDiag.TempNode;
		break;
		
		case "CaptainComission_366":
			dialog.text = "Merci, capitaine "+GetFullName(pchar)+". Si ce n'était pas toi, les contrebandiers auraient pris notre cargaison, et ces gars qui sont tombés en la défendant seraient morts en vain...";
			link.l1 = "Et merci de me faire confiance.";
			link.l1.go = "CaptainComission_367";
		break;
		
		case "CaptainComission_367":
			dialog.text = "J'ai un bibelot ici, je lui dois la vie. Je vous en prie, acceptez-le, il pourrait être votre porte-bonheur. Et merci encore, ami. Que les vents soient toujours en votre faveur.";
			link.l1 = "Merci pour le cadeau, je ne m'y attendais pas. Et tu ferais mieux de prendre soin de ta santé tant que tu as de la monnaie dans tes poches.";
			link.l1.go = "CaptainComission_368";
		break;
		
		case "CaptainComission_368":
			LAi_SetActorType(NPChar);
			LAi_SetImmortal(NPChar, true);
			GetCharacterPos(pchar, &locx, &locy, &locz);
			LAi_SetActorType(NPChar);
			LAi_ActorGoToLocation(NPChar, "reload", LAi_FindNearestLocator("reload", locx, locy, locz), "none", "", "", "OpenTheDoors", 5.0);			
			NPChar.LifeDay = 0;
			GiveItem2Character(pchar, pchar.GenQuest.CaptainComission.Prize);
			AddQuestRecord("CaptainComission2", "48");
			AddQuestUserData("CaptainComission2", "sShipType", GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.CaptainComission.ShipType),"Name") + "Gen"))); // лесник окончание
			AddQuestUserData("CaptainComission2", "sShipName", pchar.GenQuest.CaptainComission.ShipTypeName);
			AddQuestUserData("CaptainComission2", "sCharName", GetName( NAMETYPE_ORIG, pchar.GenQuest.CaptainComission.CanoneerName, NAME_ABL));
			AddQuestUserData("CaptainComission2", "sCity", XI_ConvertString("Colony" + pchar.GenQuest.CaptainComission.CanoneerCity + "Gen"));
			CloseQuestHeader("CaptainComission2");
			DeleteAttribute(pchar, "GenQuest.CaptainComission");
			DialogExit();
		break;
		
		case "CaptainComission_370":
			if(pchar.GenQuest.CaptainComission == "MayorTalkBad")
			{
				pchar.quest.CaptainComission_TimeIsOver.over = "yes";
			}	
			dialog.text = "Apparemment, aujourd'hui est mon jour de visite. As-tu besoin de moi ?";
			link.l1 = "Si tu es capitaine "+pchar.GenQuest.CaptainComission.Name+"alors oui.";
			link.l1.go = "CaptainComission_371";
		break;
		
		case "CaptainComission_371":
			dialog.text = "...ancien capitaine"+pchar.GenQuest.CaptainComission.Name+"...";
			link.l1 = "Je suis "+GetFullName(pchar)+", et j'ai quelques questions à vous poser.";
			link.l1.go = "CaptainComission_372";
		break;
		
		case "CaptainComission_372":
			dialog.text = "Et pourquoi penses-tu que je te répondrais ?";
			link.l1 = "Capitaine "+pchar.GenQuest.CaptainComission.CapName+" m'a demandé de vous avertir que les circonstances de la destruction de "+GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.CaptainComission.ShipTypeVictim),"Nom")+"Acc"))+"' "+pchar.GenQuest.CaptainComission.VictimShipName+" est devenu connu des autorités, "+"mais je n'ai pas aperçu ton navire lors du voyage depuis "+XI_ConvertString("Colony"+pchar.GenQuest.CaptainComission.City1+"Gen")+".";
			link.l1.go = "CaptainComission_373";	
		break;
		
		case "CaptainComission_373":
			dialog.text = "Et où est le capitaine "+pchar.GenQuest.CaptainComission.CapName+"?";
			link.l1 = "Il est mort.";
			link.l1.go = "CaptainComission_374";
		break;
		
		case "CaptainComission_374":
			dialog.text = "Je vois... Alors c'est comme ça, hein? Beaucoup de choses s'éclaircissent maintenant. Alors, quelqu'un a bavardé que nous avions pillé "+GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.CaptainComission.ShipTypeVictim),"Nom")+"Gén"))+". "+"Tôt ou tard, ils trouveront la cargaison et me pendre. Capitaine "+pchar.GenQuest.CaptainComission.CapName+"est mort, cela signifie que personne ne peut m'aider\nSauf toi\n"+GetFullName(pchar)+", sors-moi d'ici et je te récompenserai comme il se doit.";
			if(!CheckAttribute(pchar,"GenQuest.CaptainComission.GetRumour"))
			{
				if(CheckAttribute(pchar,"GenQuest.CaptainComission.SpeakMayor"))
				{
					link.l1 = "Le gouverneur a reçu un message du propriétaire de la cargaison. Et les chiffres y sont assez impressionnants, tu sais.";
					link.l1.go = "CaptainComission_375";
				}
				else
				{
					link.l1 = "Mais tu ne penses sûrement pas que je vais t'aider les yeux bandés ?";
					link.l1.go = "CaptainComission_375";
				}
			}			
			else
			{
				if(CheckAttribute(pchar,"GenQuest.CaptainComission.SpeakMayor"))
				{
					link.l1 = "Le gouverneur a reçu un message du propriétaire de la cargaison. Et les chiffres y sont assez impressionnants, tu sais.";
					link.l1.go = "CaptainComission_375";				
				}
				else
				{
					link.l1 = "Il y a des rumeurs dans la colonie que tu as des affaires avec les contrebandiers...";
					link.l1.go = "CaptainComission_375";				
				}
			}
		break;
		
		case "CaptainComission_375":
			sTemp = GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.CaptainComission.ShipTypeVictim),"Name") + "Gen"));
			dialog.text = "On dirait que je vais devoir te raconter toute l'histoire.\n"+"Lors d'une des patrouilles régulières, j'ai rencontré un navire sous le pavillon de "+NationNameGenitive(sti(pchar.GenQuest.CaptainComission.Nation))+" . Ils avaient ignoré mes ordres de se rendre. "+"Nous étions arrivés "+sTemp+" '"+pchar.GenQuest.CaptainComission.VictimShipName+"après une courte poursuite et ils ont hissé le pavillon noir. Le fort était assez éloigné, nous avons donc dû nous battre seuls. Ils ont détruit notre beaupré, c'est pourquoi nous n'avons pas pu éviter l'abordage.\n"+"C'était juste, mais nous avons réussi à tous les tuer grâce à la Sainte Vierge et à une unité de mousquetaires. Imagine notre bonheur quand nous avons découvert que "+sTemp+" était rempli de trésors. "+"Nous avons décidé que c'est une récompense décente pour nos blessures et la mort de nos hommes\nIl faisait déjà sombre, nous avons réussi à prendre "+sTemp+" à la baie la plus proche et cacher la cargaison à terre. Puis nous avons brûlé "+sTemp+" et j'ai rapporté un navire pirate coulé. Bien sûr, je n'ai pas mentionné la cargaison.";		
			link.l1 = "Je pense qu'il n'y a aucun intérêt pour toi à me tromper. Alors, je te propose un marché : tu me montres la cachette, et je te conduis où tu veux dans l'archipel.";
			link.l1.go = "CaptainComission_376";
		break;
		
		case "CaptainComission_376":
			dialog.text = "Ha-ha-ha... Non, capitaine, je ne quitterai pas la colonie sans ma part, même si je dois finir pendu à la potence.";
			link.l1 = "D'accord. Tu recevras ta moitié.";
			link.l1.go = "CaptainComission_377";
			link.l2 = "Hmm... Tu sais, je ne suis pas prêt à risquer ma tête pour ton bien-être. Adieu...";
			link.l2.go = "CaptainComission_378";
		break;
		
		case "CaptainComission_377":
			dialog.text = "Maintenant tu parles. Je suis prêt\nD'abord, tu devrais me cacher à bord de ton vaisseau. Je te montrerai la baie où le magot est planqué.";
			link.l1 = "Alors agissons rapidement et de manière coordonnée. Je vais ouvrir ta cellule, et tu me suis. Ne traîne pas et pas de questions jusqu'à ce qu'on soit hors du fort.";
			link.l1.go = "CaptainComission_379";
		break;
		
		case "CaptainComission_378":
			pchar.quest.CaptainComission_GetSecretTimeIsOut.over = "yes";
			sld = CharacterFromID("CapComission_1");
			sld.LifeDay = 0;
			ChangeCharacterComplexReputation(pchar,"nobility", -5);			
			AddQuestRecord("CaptainComission2", "8");
			AddQuestUserData("CaptainComission2", "sSex", GetSexPhrase("",""));
			AddQuestUserData("CaptainComission2", "sName", pchar.GenQuest.CaptainComission.Name);
			CloseQuestHeader("CaptainComission2");
			LAi_CharacterDisableDialog(npchar);// лесник - запрет диалога
			DeleteAttribute(pchar, "GenQuest.CaptainComission");
			DialogExit();
		break;
		
		case "CaptainComission_379":
			AddQuestRecord("CaptainComission2", "21");
			AddQuestUserData("CaptainComission2", "sName", pchar.GenQuest.CaptainComission.Name);
			pchar.quest.CaptainComission_PrisonFree_Death.win_condition.l1 = "NPC_Death";
			pchar.quest.CaptainComission_PrisonFree_Death.win_condition.l1.character = "CapComission_1";
			pchar.quest.CaptainComission_PrisonFree_Death.win_condition = "CaptainComission_PrisonFree_Death";
			GetCharacterPos(npchar, &locx, &locy, &locz);	
			ChangeCharacterAddressGroup(npchar, npchar.location, "reload", LAi_FindNearestFreeLocator("reload", locx, locy, locz));
			LAi_group_Register("CapComission_Prison");
			LAi_group_SetRelation("CapComission_Prison", LAI_GROUP_PLAYER, LAI_GROUP_FRIEND);
			LAi_group_SetAlarmReaction(LAI_GROUP_PLAYER, "CapComission_Prison", LAI_GROUP_ENEMY, LAI_GROUP_FRIEND);
			LAi_group_MoveCharacter(npchar, "CapComission_Prison");
			LAi_SetActorType(npchar);
			LAi_ActorFollowEverywhere(npchar, "", -1);
			LAi_CharacterDisableDialog(npchar);
			pchar.GenQuest.CaptainComission.PrisonFree = true;
			if(pchar.GenQuest.CaptainComission == "MayorTalkGood") 
			{
				chrDisableReloadToLocation = true;	
				sld = CharacterFromId(pchar.GenQuest.CaptainComission.City + "JailOff");	
				sld.dialog.currentnode = "CapComission_PrisonFree1";
			}	
			pchar.quest.CapComission_ExitFromPrison.win_condition.l1 = "ExitFromLocation";
            pchar.quest.CapComission_ExitFromPrison.win_condition.l1.location = pchar.location;
            pchar.quest.CapComission_ExitFromPrison.win_condition = "CaptainComission_ExitFromPrison"; 
			DialogExit();
		break;		
		
		case "CaptainComission_380":
			pchar.quest.CaptainComission_GetSecretTimeIsOut.over = "yes";
			pchar.quest.CaptainComission_PrisonFree_Death.over = "yes";
			DeleteAttribute(pchar,"GenQuest.CaptainComission.canSpeakCaptain");
			DeleteAttribute(pchar,"GenQuest.CaptainComission.PrisonFree");
			pchar.GenQuest.CaptainComission = "CanGetGoods";
			pchar.GenQuest.CaptainComission.ConvoyShore = SelectQuestShoreLocationFromSea(GetArealByCityName(pchar.GenQuest.CaptainComission.City));
			dialog.text = "Merci pour le sauvetage. Allons-nous-en à "+XI_ConvertString(pchar.GenQuest.CaptainComission.ConvoyShore+"Ce")+", je vous indiquerai l'emplacement de la cachette. Nous devrions nous dépêcher avant que les sauvages ne trouvent l'endroit.";	// belamour gen	
			link.l1 = "Es-tu sûr que nous pourrons récupérer toute la cargaison ?";
			link.l1.go = "CaptainComission_381";
		break;
		
		case "CaptainComission_381":
			pchar.GenQuest.CaptainComission.GoodsQty = makeint(sti(GetBaseShipParamFromType(sti(pchar.GenQuest.CaptainComission.ShipTypeVictim),"Capacity")) / sti(Goods[sti(pchar.GenQuest.CaptainComission.Goods)].Weight));
			dialog.text = "Vous avez raison, assurez-vous d'avoir assez de place pour "+pchar.GenQuest.CaptainComission.GoodsQty+" pièces de "+GetStrSmallRegister(XI_ConvertString(Goods[sti(pchar.GenQuest.CaptainComission.Goods)].Name+"Gen"))+". Ce serait dommage de perdre un butin si précieux avec tant de sang dessus. Ils ne nous donneront pas une seconde chance.";
			link.l1 = "Je m'en occupe.";
			link.l1.go = "CaptainComission_382";
		break;
		
		case "CaptainComission_382":
			AddQuestRecord("CaptainComission2", "24");
			AddQuestUserData("CaptainComission2", "sName", pchar.GenQuest.CaptainComission.Name);
			AddQuestUserData("CaptainComission2", "sShoreName", XI_ConvertString(pchar.GenQuest.CaptainComission.ConvoyShore + "Gen")); // belamour gen
			AddQuestUserData("CaptainComission2", "sGoodsQuantity", pchar.GenQuest.CaptainComission.GoodsQty);
			AddQuestUserData("CaptainComission2", "sGoods", GetStrSmallRegister(XI_ConvertString(Goods[sti(pchar.GenQuest.CaptainComission.Goods)].Name + "Gen")));
			SetFunctionLocationCondition("CaptainComission_MeetInShore", pchar.GenQuest.CaptainComission.ConvoyShore, false); 
			SetFunctionTimerConditionParam("CaptainComission_CapEscapeTimer", 0, 0, 1, MakeInt(24 - GetHour()), false);
			AddPassenger(pchar, npchar, false);
			SetCharacterRemovable(npchar, false);
			chrDisableReloadToLocation = false; // Откроем выход
			DeleteAttribute(pchar,"TownEscape");
			QuestOpenSeaExit();
			DialogExit();
			AddDialogExitQuest("CanEnterToMap");
		break;
		
		case "CaptainComission_383":
			dialog.text = "Capitaine, nous n'avons pas besoin de témoins. S'il vous plaît, essayez de convaincre ces gens de quitter la crique.";
			link.l1 = "Très bien, faisons cela.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("CaptainComission_GangDialogGetGoods");
		break;
		
		case "CaptainComission_384":
			dialog.text = "Capitaine, je suis désolé, mais ce n'est pas le meilleur endroit pour vos exercices. Ce quai est déjà occupé.";
			link.l1 = "Messieurs, je ne suis pas venu ici pour faire du tourisme. J'ai des affaires ici.";
			link.l1.go = "CaptainComission_385";
		break;
		
		case "CaptainComission_385":
			dialog.text = "Eh bien, nous n'attrapons pas de méduses ici non plus, faites demi-tour avec vos navires et foutez le camp d'ici.";
			link.l1 = "Je n'ai pas envie de perdre mon temps à te convaincre de partir. Soit tu le fais de bon gré et tu restes en vie, soit tu restes ici pour de bon.";
			link.l1.go = "CaptainComission_386";
		break;
		
		case "CaptainComission_386":
			dialog.text = "Je vois que tu as du mal à comprendre mes mots. Très bien, si tu y tiens tant...";
			link.l1 = "C'est mieux !";
			link.l1.go = "CaptainComission_364";
		break;
		
		case "CaptainComission_387":
			LAi_LocationDisableOfficersGen(pchar.GenQuest.CaptainComission.ConvoyShore, false);
			pchar.GenQuest.CaptainComission.MaxGoodsQty = GetSquadronFreeSpace(pchar, sti(pchar.GenQuest.CaptainComission.Goods));
			if(sti(pchar.GenQuest.CaptainComission.MaxGoodsQty) > sti(pchar.GenQuest.CaptainComission.GoodsQty)) pchar.GenQuest.CaptainComission.MaxGoodsQty = pchar.GenQuest.CaptainComission.GoodsQty;
			dialog.text = "Nous y sommes. La cachette est dans une niche de cette falaise. L'entrée est bloquée par des rochers. Dans la cache, il y a "+pchar.GenQuest.CaptainComission.GoodsQty+"unités de "+GetStrSmallRegister(XI_ConvertString(Goods[sti(pchar.GenQuest.CaptainComission.Goods)].Name+"Gen"))+"Rappelle-toi que la moitié est à moi ?";
			link.l1 = "Bien sûr que oui. Nous avons un peu de temps pendant que mes hommes chargent les marchandises. Parlons de l'endroit où vous et votre cargaison devez être emmenés.";
			link.l1.go = "CaptainComission_388";
			if (!CheckAttribute(pchar,"GenQuest.CaptainComission.MayorTalkGood"))
			{	
			link.l2 = "Très bien. Maintenant, dis-moi, y a-t-il une raison pour que je partage?";
			link.l2.go = "CaptainComission_389";
			}
			if(CheckAttribute(pchar,"GenQuest.CaptainComission.MayorTalkGood"))
			{
				link.l3 = "Capitaine "+pchar.GenQuest.CaptainComission.Name+", je dois te dire quelque chose de déplaisant. Je travaille pour le gouverneur. Et j'ai l'intention de lui livrer toute la cargaison que tu as cachée. Tu devrais retourner en prison et y attendre ton sort.";
				link.l3.go = "CaptainComission_389";
				link.l2 = "Très bien. Mais voilà le truc... Au début, je voulais te livrer aux autorités, mais pourquoi ferais-je cela maintenant ? Et pourquoi partagerais-je avec toi ?";
			    link.l2.go = "CaptainComission_3899"; // // лесник . отдельный диалог в случае обмана всех.
			}	
		break;
		
		case "CaptainComission_388":
		    pchar.quest.CaptainComission_Capitan_Cdoxul.over = "yes"; // лесник . снял событие ,иначе в СЖ не то пишут.
			iTmp = FindNonEnemyColonyForAdventure(sti(pchar.GenQuest.CaptainComission.Nation),pchar.GenQuest.CaptainComission.City, true);			
			sTemp = Colonies[iTmp].id;
			pchar.GenQuest.CaptainComission.ConvoyIsland = GetArealByCityName(sTemp);
			pchar.GenQuest.CaptainComission.ConvoyShore = SelectQuestShoreLocationFromSea(pchar.GenQuest.CaptainComission.ConvoyIsland);
			pchar.GenQuest.CaptainComission.ConvoyCity = sTemp;			
			pchar.GenQuest.CaptainComission.iDay  = 20 + hRand(10);
			iGoods = GetSquadronFreeSpace(pchar, sti(pchar.GenQuest.CaptainComission.Goods)); 
			if(iGoods < sti(pchar.GenQuest.CaptainComission.GoodsQty)) pchar.GenQuest.CaptainComission.GoodsQty = iGoods;
			SetCharacterGoods(pchar, sti(pchar.GenQuest.CaptainComission.Goods), GetCargoGoods(pchar, sti(pchar.GenQuest.CaptainComission.Goods)) + sti(pchar.GenQuest.CaptainComission.GoodsQty));// перегруз
			dialog.text = "J'ai besoin d'aller à "+XI_ConvertString(pchar.GenQuest.CaptainComission.ConvoyShore+"Gen")+", à "+XI_ConvertString(GetIslandByCityName(sTemp)+"Voc")+" pour "+pchar.GenQuest.CaptainComission.iDay+" jours. Mes hommes là-bas ont dû préparer la cargaison pour la vendre."; // belamour gen
			link.l1 = "D'accord. Il est temps de partir, alors.";
			link.l1.go = "CaptainComission_391";
		break;
		case "CaptainComission_3899": // лесник . отдельный диалог в случае обмана всех.
		    DeleteAttribute(pchar,"GenQuest.CaptainComission.MayorTalkGood");
			ChangeCharacterNationReputation(pchar, sti(NPChar.nation), -10);
		    pchar.quest.CaptainComission_Capitan_Cdoxul.over = "yes"; // лесник . снял событие ,иначе в СЖ не то пишут.
			dialog.text = "D'accord. On doit toujours faire confiance à l'esprit, pas au coeur. Vivre et apprendre\nMême si je ne m'attendais pas à cela, je suis toujours prêt à me battre. Tu paieras pour ta trahison.";
			link.l1 = "Eh bien, si tu as de la chance...";
			link.l1.go = "CaptainComission_390";
			SetFunctionTimerConditionParam("CaptainComission_NaebalGubera", 0, 0, 1, MakeInt(24 - GetHour()), false);
		break;
		
		case "CaptainComission_389":
			pchar.quest.CaptainComission_Capitan_Cdoxul.over = "yes"; // лесник . снял событие ,иначе в СЖ не то пишут.
			dialog.text = "D'accord. Il faut toujours faire confiance à l'esprit, pas au coeur. Vivre et apprendre\nMême si je ne m'attendais pas à cela, je suis toujours prêt pour un combat. Tu répondras de ta trahison.";
			link.l1 = "Je suis à votre service...";
			link.l1.go = "CaptainComission_390";
		break;
		
		
		case "CaptainComission_390":
			LAi_SetPlayerType(pchar);
			LAi_group_Delete("EnemyFight");
			chrDisableReloadToLocation = true;
			rChar = CharacterFromID("CapComission_1");
			LAi_SetWarriorType(rChar);
			LAi_SetImmortal(rChar, false);// лесник.  
			LAi_group_MoveCharacter(rChar, "EnemyFight");		
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("EnemyFight", "OpenTheDoors"); 			
			if(pchar.GenQuest.CaptainComission == "CapDuel")
			{
				LAi_group_SetCheckFunction("EnemyFight", "CaptainComission_CaptainDiedDuel");
			}
			else
			{
				LAi_group_SetCheckFunction("EnemyFight", "CaptainComission_CheckCaptainDied");
			}	
			DialogExit();	
			AddDialogExitQuest("MainHeroFightModeOn");						
		break;
		
		case "CaptainComission_391":
			AddPassenger(pchar, npchar, false);
			SetCharacterRemovable(npchar, false);
			GetCharacterPos(NPChar, &locx, &locy, &locz);
			LAi_SetActorType(NPChar);
			LAi_ActorGoToLocation(NPChar, "reload", LAi_FindNearestLocator("reload", locx, locy, locz), "none", "", "", "OpenTheDoors", 5.0);			
			pchar.GenQuest.CaptainComission.CapGoodsQty = sti(pchar.GenQuest.CaptainComission.GoodsQty)/2;
			if(sti(pchar.GenQuest.CaptainComission.CapGoodsQty) > sti(pchar.GenQuest.CaptainComission.MaxGoodsQty)) pchar.GenQuest.CaptainComission.CapGoodsQty = pchar.GenQuest.CaptainComission.MaxGoodsQty;
			if(CheckAttribute(pchar,"GenQuest.CaptainComission.MayorTalkGood"))AddQuestRecord("CaptainComission2", "53");// лесник. выбор записи в СЖ
			else AddQuestRecord("CaptainComission2", "26");// смотря по какому пути пошел 
			AddQuestUserData("CaptainComission2", "sGoodsQuantity", pchar.GenQuest.CaptainComission.MaxGoodsQty);
			AddQuestUserData("CaptainComission2", "sGoods", GetStrSmallRegister(XI_ConvertString(Goods[sti(pchar.GenQuest.CaptainComission.Goods)].Name + "Gen")));
			AddQuestUserData("CaptainComission2", "sSum1", pchar.GenQuest.CaptainComission.CapGoodsQty);
			AddQuestUserData("CaptainComission2", "sName", pchar.GenQuest.CaptainComission.Name);
			AddQuestUserData("CaptainComission2", "sDays", pchar.GenQuest.CaptainComission.iDay);
			AddQuestUserData("CaptainComission2", "sShoreName", XI_ConvertString(pchar.GenQuest.CaptainComission.ConvoyShore + "Dat")); // belamour gen
			AddQuestUserData("CaptainComission2", "sShoreType", XI_ConvertString(pchar.GenQuest.CaptainComission.ConvoyIsland + "Gen")); // belamour gen
			OfficersReaction("bad");
			if(CheckAttribute(pchar,"GenQuest.CaptainComission.MayorTalkGood"))
			{
				ChangeCharacterComplexReputation(pchar,"nobility", -5);
				ChangeCharacterNationReputation(pchar, sti(NPChar.nation), -10);
			}
			CaptainComission_GenerateCoastalPatrol();
			pchar.GenQuest.CaptainComission = "GetGoodsEscape";
			SetFunctionLocationCondition("CaptainComission_CapMeetInShore", pchar.GenQuest.CaptainComission.ConvoyShore, false);
			SaveCurrentQuestDateParam("GenQuest.CaptainComission.DeleiveCapShore");	
			DialogExit();
		break;
		
		case "CaptainComission_392":
			dialog.text = "Apparemment, nous étions en retard... Les clients n'ont pas attendu, et je n'ai aucune opportunité d'organiser le stockage et la vente de la cargaison par moi-même...";
			link.l1 = "Avez-vous des propositions particulières à cet égard ?";
			link.l1.go = "CaptainComission_393";
		break;
		
		case "CaptainComission_393":
			pchar.GenQuest.CaptainComission.GoodsPrice = makeint(sti(pchar.GenQuest.CaptainComission.CapGoodsQty) * 0.75 * sti(Goods[sti(pchar.GenQuest.CaptainComission.Goods)].Cost));
			dialog.text = "Capitaine "+GetFullName(pchar)+", je sais que c'est un peu gênant, mais... pourriez-vous me donner l'équivalent monétaire de ma part? Je suppose, "+pchar.GenQuest.CaptainComission.GoodsPrice+" pesos pourraient être un bon compromis.";
			if(sti(pchar.money) >= sti(pchar.GenQuest.CaptainComission.GoodsPrice))
			{
				link.l1 = "Oui, c'est un prix équitable. Ça ne me dérange pas. Voici votre argent, et adieu.";
				link.l1.go = "CaptainComission_394";
			}
			link.l2 = "Oh, non, mon ami, cela ne va pas. Je ne peux pas te materner éternellement. Si tu ne veux pas récupérer ta cargaison, je vais simplement la garder. Sois assuré que je trouverai un moyen de la stocker et de la vendre à terme.";
			link.l2.go = "CaptainComission_3951";
		break;
		
		case "CaptainComission_394":
			addMoneyToCharacter(pchar, -sti(pchar.GenQuest.CaptainComission.GoodsPrice));
			dialog.text = "Attends, capitaine. Je veux te remercier pour mon sauvetage. Tu sais, j'avais presque perdu espoir... Tiens, je suis sûr que tu trouveras ce bibelot très utile dans de nombreuses situations difficiles... Adieu maintenant.";
			link.l1 = "Merci. Je ne m'y attendais pas. Plaisir de faire affaire avec vous.";
			link.l1.go = "CaptainComission_395";
		break;
		
		case "CaptainComission_3951": // лесник . верное назначение диалога
			pchar.quest.CaptainComission_Capitan_Cdoxul.over = "yes";
			dialog.text = "Je ne m'attendais pas à cela de ta part... Apparemment, je n'ai pas d'autre choix que de te défier en duel.";
			link.l1 = "Je suis à votre service...";
			link.l1.go = "CaptainComission_390";
			pchar.GenQuest.CaptainComission = "CapDuel";
		break;
		
		case "CaptainComission_395":
			GiveItem2Character(pchar, pchar.GenQuest.CaptainComission.Prize);
			AddQuestRecord("CaptainComission2", "32");
			AddQuestUserData("CaptainComission2", "sSex", GetSexPhrase("",""));
			AddQuestUserData("CaptainComission2", "sShoreName", XI_ConvertString(pchar.GenQuest.CaptainComission.ConvoyShore + "Gen")); // belamour gen
			AddQuestUserData("CaptainComission2", "sName", pchar.GenQuest.CaptainComission.Name);
			AddQuestUserData("CaptainComission2", "sSum", pchar.GenQuest.CaptainComission.GoodsPrice);
			CloseQuestHeader("CaptainComission2");	
			GetCharacterPos(pchar, &locx, &locy, &locz);
			LAi_SetActorType(NPChar);
			LAi_ActorGoToLocation(NPChar, "reload", LAi_FindNearestLocator("reload", locx, locy, locz), "none", "", "", "OpenTheDoors", 5.0);
			NPChar.lifeDay = 0; 						
			DeleteAttribute(pchar, "GenQuest.CaptainComission");
			DialogExit();
		break;

		case "CaptainComission_396_0":
			dialog.text = "Capitaine, je dois parler à mes hommes.";
			link.l1 = "Allez-y.";
			link.l1.go = "exit";
			InterfaceStates.Buttons.Save.enable = false; 
			AddDialogExitQuestFunction("CaptainComission_DialogInShore");
		break;
		
		case "CaptainComission_396":
			sld = characterFromId("Blaze");
			dialog.text = "Je vous salue, capitaine "+GetFullName(pchar)+". Alors, as-tu apporté toute la cargaison ? Et où est le capitaine "+pchar.CaptainComission.CapName+"?";
			link.l1 = pchar.CaptainComission.CapName+" est mort, et j'ai été arrêté sur dénonciation. Et si le capitaine "+pchar.CaptainComission.FullName+"ne m'avais pas aidé, tu n'aurais vu ni moi ni la cargaison.";
			link.l1.go = "CaptainComission_397";
		break;
		
		case "CaptainComission_397":
			sld = characterFromId("Blaze");
			dialog.text = "Et "+NPCharSexPhrase(sld,"qui est-il ? Est-il","qui est-elle? Est-elle")+" au courant de nos affaires ?";
			link.l1 = "Bien sûr. "+NPCharSexPhrase(sld,"Il a extrait","Elle a extrait")+" me from the jail and undertook to deliver half of the cargo here; the other half I promised "+ NPCharSexPhrase(sld, "him","her") +" as a compensation.";
			link.l1.go = "CaptainComission_398";
		break;
		
		case "CaptainComission_398":
			sld = characterFromId("Blaze");
			dialog.text = "Eh, capitaine, pas question. Ce sont tes problèmes ! J'avais suggéré qu'on prenne le navire et qu'on se tire, mais tu étais trop occupé à t'occuper de ta fichue carrière. Et te voilà, ton cher gouverneur t'a mis en prison."+" Ta part etait bien plus petite qu'une moitie ! On n'a pas mis nos tetes sous les mitrailles pour te laisser voler toute la moitie pour toi-meme !";
			link.l1 = "Écoute, maître d'équipage, ne te souviens-tu pas que le navire était complètement en pièces ? Qu'il était presque sous l'eau ? Ne comprends-tu pas que si je n'avais pas donné la moitié à cet homme, tu n'aurais jamais revu même un petit morceau de la cargaison ?";	
			link.l1.go = "CaptainComission_399";
		break;
		
		case "CaptainComission_399":
			dialog.text = "Tu ne vas pas me duper ! Comment pourrions-nous savoir que tu n'étais pas de mèche ? Et s'il n'y avait pas eu d'arrestation du tout ? Et si tu étais simplement trop avide et avais décidé de voler nos biens ? Ou penses-tu que nous avons oublié comment manier une lame ?!";
			link.l1 = "Je vois que tu es devenu fou. Tu n'entends rien d'autre que le tintement des pièces dans tes oreilles.";
			link.l1.go = "CaptainComission_400";
		break;
		
		case "CaptainComission_400":
			sld = characterFromId("Blaze");
			dialog.text = "Les gars ! Regardez comment notre capitaine parle maintenant ! En effet, la cupidité l'a totalement consumé ! Il a vendu notre part à "+NPCharSexPhrase(sld,"un vaurien","une aventurière")+"!!";
			link.l1 = "Ferme ta gueule immonde maintenant, ou je te ferai taire pour de bon !";
			link.l1.go = "exit";
			AddDialogExitQuest("CaptainComission_ShoreGangDialog");
		break;
		
		case "CaptainComission_401":
			dialog.text = "Je suis désolé, capitaine, que vous ayez dû assister à cette scène ridicule et même y participer. Il est difficile de croire qu'il y a à peine un mois, nous étions un équipage uni, et chacun de nous aurait volontiers sacrifié sa vie pour sauver un ami.";
			link.l1 = "Je dois admettre, je ne peux pas imaginer cela, sans vouloir vous offenser.";
			link.l1.go = "CaptainComission_402";
		break;
		
		case "CaptainComission_402":
			dialog.text = "Malheureusement, je n'ai pas l'opportunité d'organiser moi-même le stockage et la vente de la cargaison...";
			link.l1 = "As-tu des propositions particulières à cet égard ?";
			link.l1.go = "CaptainComission_403";
		break;
		
		case "CaptainComission_403":
			pchar.GenQuest.CaptainComission.GoodsPrice = makeint(sti(pchar.GenQuest.CaptainComission.CapGoodsQty) * 0.75 * sti(Goods[sti(pchar.GenQuest.CaptainComission.Goods)].Cost));
			dialog.text = "Capitaine "+GetFullName(pchar)+", je sais que c'est un peu gênant, mais... pourrais-tu me donner l'équivalent monétaire de ma part? Je suppose, "+pchar.GenQuest.CaptainComission.GoodsPrice+" pesos pourraient être un bon compromis.";
			if(sti(pchar.money) >= sti(pchar.GenQuest.CaptainComission.GoodsPrice))
			{
				pchar.quest.CaptainComission_Capitan_Cdox.over = "yes"; // на всякий случай .лесник
				pchar.quest.CaptainComission_Capitan_Cdoxul.over = "yes"; // лесник
				link.l1 = "D'accord, ça ne me dérange pas. Voici ton argent, et adieu.";
				link.l1.go = "CaptainComission_404";
			}	
			link.l2 = "Non, cela ne marchera pas. Tu peux prendre ta cargaison ou la laisser dans la cale, mais je ne te donnerai pas une seule pièce.";
			link.l2.go = "CaptainComission_405";
		break;
		
		case "CaptainComission_404":
			bTemp = false;
			if(hrand(1) == 0)
			{
			    NPChar.reputation = 60 + rand(20); 
				NPChar.alignment = "good"; 
			}	
			else
			{
			    NPChar.reputation = 10 + rand(20); 
				NPChar.alignment = "bad"; 			
			}
			if (NPChar.alignment == "good" && sti(pchar.reputation.nobility) > 50) bTemp = true; 
			if (NPChar.alignment == "bad" && sti(pchar.reputation.nobility) <= 50) bTemp = true;
			
			addMoneyToCharacter(pchar, -sti(pchar.GenQuest.CaptainComission.GoodsPrice));
			
			if(!bTemp || FindFreeRandomOfficer() < 0)
			{
				dialog.text = "Attendez, capitaine. Je veux vous remercier pour mon sauvetage. Vous savez, j'avais presque perdu espoir... Tenez, je suis sûr que vous trouverez ce bibelot très utile dans de nombreuses situations difficiles... Adieu maintenant.";
				link.l1 = "Merci. Je ne m'y attendais pas. Ce fut un plaisir de traiter avec vous.";
				link.l1.go = "CaptainComission_406";
			}
			else
			{
				dialog.text = "Attendez... Je viens de penser... Vous savez, ma carrière est finie maintenant, je n'ai plus d'équipage et je suis en exil dans ma patrie. Vous aurez certainement besoin d'hommes de confiance à la main sûre, qui savent tenir leur langue. S'il vous plaît, acceptez-moi dans votre équipage, je vous promets que vous ne le regretterez pas.";
				if(!CaptainComission_CheckAllPassengersHired())
				{
					link.l1 = "Pour être honnête, j'attendais avec impatience votre accord depuis un certain temps. Bien sûr. Voyez-moi à bord.";
					link.l1.go = "CaptainComission_407";
				}	
				link.l2 = "Hmm... tu sais, il me semble que tu es bien trop malin pour servir sous quelqu'un. Adieu...";
				link.l2.go = "CaptainComission_408";
			}
		break;
		
		case "CaptainComission_405":
			dialog.text = "Eh bien, apparemment, aujourd'hui n'est clairement pas mon jour de chance... D'accord capitaine, dégainons nos lames et finissons-en une bonne fois pour toutes...";
			link.l1 = "Je suis à votre service...";
			link.l1.go = "CaptainComission_390";
			pchar.GenQuest.CaptainComission = "CapDuel";
			pchar.GenQuest.CaptainComission.Duel = true;
		break;
		
		case "CaptainComission_406":
			GiveItem2Character(pchar, pchar.GenQuest.CaptainComission.Prize);
			AddQuestRecord("CaptainComission2", "34");
			AddQuestUserData("CaptainComission2", "sSex", GetSexPhrase("",""));
			AddQuestUserData("CaptainComission2", "sName", pchar.GenQuest.CaptainComission.Name);
			AddQuestUserData("CaptainComission2", "sSum", pchar.GenQuest.CaptainComission.GoodsPrice);
			CloseQuestHeader("CaptainComission2");
			GetCharacterPos(pchar, &locx, &locy, &locz);
			LAi_SetActorType(NPChar);
			LAi_ActorGoToLocation(NPChar, "reload", LAi_FindNearestLocator("reload", locx, locy, locz), "none", "", "", "OpenTheDoors", 5.0);			
			NPChar.lifeDay = 0; 						
			DeleteAttribute(pchar, "GenQuest.CaptainComission");
			DialogExit();
		break;
	
		
		case "CaptainComission_407":	
			AddQuestRecord("CaptainComission2", "36");
			AddQuestUserData("CaptainComission2", "sSex", GetSexPhrase("",""));
			AddQuestUserData("CaptainComission2", "sName", pchar.GenQuest.CaptainComission.Name);
			AddQuestUserData("CaptainComission2", "sSum", pchar.GenQuest.CaptainComission.GoodsPrice);
			CloseQuestHeader("CaptainComission2");		
			npchar.CaptainComission = true;
			SetCharacterRemovable(Npchar, true);
			DeleteAttribute(pchar, "GenQuest.CaptainComission");
			NPChar.Dialog.Filename = "Enc_Officer_dialog.c";
			NPChar.Dialog.CurrentNode = "hired";
            NPChar.greeting = "Gr_Officer"; 			
			NPChar.quest.OfficerPrice = sti(pchar.rank)*500;	
			NPChar.loyality = MAX_LOYALITY;
			DeleteAttribute(NPChar, "LifeDay");
			NPChar.id = "GenChar_" + NPChar.index;// лесник . смена ИД при взятии в оффы. 
			pchar.questTemp.HiringOfficerIDX = GetCharacterIndex(NPChar.id);
			AddDialogExitQuestFunction("LandEnc_OfficerHired"); 
			NPChar.quest.meeting = true; 
			DialogExit();
		break;		
		
		case "CaptainComission_408":
			AddQuestRecord("CaptainComission2", "35");
			AddQuestUserData("CaptainComission2", "sSex", GetSexPhrase("",""));
			AddQuestUserData("CaptainComission2", "sName", pchar.GenQuest.CaptainComission.Name);
			AddQuestUserData("CaptainComission2", "sSum", pchar.GenQuest.CaptainComission.GoodsPrice);
			CloseQuestHeader("CaptainComission2");
			GetCharacterPos(pchar, &locx, &locy, &locz);
			LAi_SetActorType(NPChar);
			LAi_ActorGoToLocation(NPChar, "reload", LAi_FindNearestLocator("reload", locx, locy, locz), "none", "", "", "OpenTheDoors", 5.0);						
			NPChar.lifeDay = 0; 						
			DeleteAttribute(pchar, "GenQuest.CaptainComission");		
			DialogExit();
		break;		
		// Генератор "Operation 'Galleon'"
		
		// Квест "meeting in the cove" -->
		// Офицер
		case "ContraMeetManQuest_Sold_1":
			dialog.text = "Ce ne sont pas tes affaires. Maintenant dis-moi, qu'est-ce que tu renifles ici ? Ne cherches-tu pas un homme qui vient d'être arrêté ?!";
				link.l1 = "Un homme ?! Non...";
				link.l1.go = "ContraMeetManQuest_Sold_2";
			break;
			
		case "ContraMeetManQuest_Sold_2":
			dialog.text = "Bien pour toi. Sinon, toi aussi tu finirais en prison avec lui. Alors ne traîne pas ici, matelot. Déguerpis !";
				link.l1 = "Ouais, je ferais mieux de partir...";
				link.l1.go = "ContraMeetManQuest_Sold_3";
			break;
			
		case "ContraMeetManQuest_Sold_3":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			DeleteQuestCondition("ContraMeetManQuest_TimeIsLeft"); // Время больше не роляет
			sQuestTitle = PChar.GenQuest.ContraMeetMan.QuestTown + "ContraMeetManQuest";
			AddQuestRecordEx(sQuestTitle, "ContraMeetManQuest", "8");
			PChar.GenQuest.ContraMeetMan.ToTavernPatrolInShore = true;
			LAi_CharacterDisableDialog(NPChar);
			DeleteAttribute(&Locations[FindLocation(PChar.GenQuest.ContraMeetMan.ShoreID)], "DisableEncounters"); // Включаем случайки
			ContraMeetManQuest_DeletePatrolFromShore(); // По выходу потрем всех из локации
			break;
			
		// Сам чел
		case "ContraMeetManQuest_1":
			dialog.text = "Super ! Nous devrions nous diriger vers la taverne pour voir ce contrebandier maintenant. Je n'aimerais pas traîner ici !";
				link.l1 = "Aucun problème avec ça. Allons-y...";
				link.l1.go = "ContraMeetManQuest_2";
			break;
			
		case "ContraMeetManQuest_2":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			LAi_SetActorType(NPChar);
			LAi_ActorFollowEverywhere(NPChar, "", -1);
			sQuestTitle = PChar.GenQuest.ContraMeetMan.QuestTown + "ContraMeetManQuest";
			AddQuestRecordEx(sQuestTitle, "ContraMeetManQuest", "3");
			AddQuestUserData(sQuestTitle, "sDestination", XI_ConvertString(PChar.GenQuest.ContraMeetMan.ShoreID + "Dat"));
			PChar.GenQuest.ContraMeetMan.ToTavernWithMan = true;
			DeleteAttribute(&Locations[FindLocation(PChar.GenQuest.ContraMeetMan.ShoreID)], "DisableEncounters"); // Включаем случайки
			break;
		
		// Контрики в комнате таверны	
		case "ContraMeetManQuest_3":
			ContraMeetManQuest_ContersGoQut();
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			AddMoneyToCharacter(PChar, sti(PChar.GenQuest.ContraMeetMan.Money));
			sQuestTitle = PChar.GenQuest.ContraMeetMan.QuestTown + "ContraMeetManQuest";
			AddQuestRecordEx(sQuestTitle, "ContraMeetManQuest", "4");
			AddQuestUserData(sQuestTitle, "sMoney", FindRussianMoneyString(sti(PChar.GenQuest.ContraMeetMan.Money)));
			CloseQuestHeader(sQuestTitle);
			ChangeContrabandRelation(PChar, 5);
			DeleteAttribute(PChar, "GenQuest.ContraMeetMan");
			break;
			
		case "ContraMeetManQuest_4":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			AddMoneyToCharacter(PChar, sti(PChar.GenQuest.ContraMeetMan.Money));
			sQuestTitle = PChar.GenQuest.ContraMeetMan.QuestTown + "ContraMeetManQuest";
			AddQuestRecordEx(sQuestTitle, "ContraMeetManQuest", "5");
			AddQuestUserData(sQuestTitle, "sMoney", FindRussianMoneyString(sti(PChar.GenQuest.ContraMeetMan.Money)));
			CloseQuestHeader(sQuestTitle);
			ContraMeetManQuest_ContraBeatMan();
			ChangeContrabandRelation(PChar, 5);
			ChangeCharacterComplexReputation(pchar,"nobility", -5);
			DeleteAttribute(PChar, "GenQuest.ContraMeetMan");
			break;
			
		case "ContraMeetManQuest_5":
			dialog.text = "Hi-hi... Il semble, "+GetSexPhrase("compagnon","fille")+", tu iras en enfer avec lui très bientôt... Hé, mate - étripons-les tous les deux !";
				link.l1 = "Sale cochon ! Défends-toi !";
				link.l1.go = "ContraMeetManQuest_6";
			break;
			
		case "ContraMeetManQuest_6":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			ContraMeetManQuest_PlayerBeatContra();
			break;
			
		case "ContraMeetManQuest_7":
			dialog.text = "Je vous remercie encore une fois, "+PChar.name+" Adieu...";
				link.l1 = "... ";
				link.l1.go = "ContraMeetManQuest_9";
			break;
			
		case "ContraMeetManQuest_8":
			iMoney = (rand(3)+2)*500;
			PChar.GenQuest.ContraMeetMan.Money = iMoney;
			dialog.text = "Une récompense ?! Oh, bien sûr. Tiens - prends "+FindRussianMoneyString(iMoney)+"et adieu...";
				link.l1 = "Adieu...";
				link.l1.go = "ContraMeetManQuest_10";
			break;
			
		case "ContraMeetManQuest_9":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			ChangeCharacterComplexReputation(pchar,"nobility", 10);
			sQuestTitle = PChar.GenQuest.ContraMeetMan.QuestTown + "ContraMeetManQuest";
			AddQuestRecordEx(sQuestTitle, "ContraMeetManQuest", "6");
			AddQuestUserData(sQuestTitle, "sMoney", FindRussianMoneyString(iMoney));
			AddQuestUserData(sQuestTitle, "sDestination", XI_ConvertString(PChar.GenQuest.ContraMeetMan.ShoreID + "Dat"));
			CloseQuestHeader(sQuestTitle);
			ContraMeetManQuest_ContersGoQut();
			DeleteAttribute(PChar, "GenQuest.ContraMeetMan");
			break;
			
		case "ContraMeetManQuest_10":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			AddMoneyToCharacter(PChar, sti(PChar.GenQuest.ContraMeetMan.Money));
			sQuestTitle = PChar.GenQuest.ContraMeetMan.QuestTown + "ContraMeetManQuest";
			AddQuestRecordEx(sQuestTitle, "ContraMeetManQuest", "7");
			AddQuestUserData(sQuestTitle, "sMoney", FindRussianMoneyString(sti(PChar.GenQuest.ContraMeetMan.Money)));
			AddQuestUserData(sQuestTitle, "sDestination", XI_ConvertString(PChar.GenQuest.ContraMeetMan.ShoreID + "Dat"));
			CloseQuestHeader(sQuestTitle);
			ContraMeetManQuest_ContersGoQut();
			DeleteAttribute(PChar, "GenQuest.ContraMeetMan");
			break;
		// <-- Квест "meeting in the cove"
			
		// Квест на доставку письма контрику -->
		case "ContraDeliverQuest_Sold1":
			dialog.text = "Hé ! Tu t'attends à ce qu'on croie à ces foutaises ?! Les gars, attrapez ces deux vauriens !";
			//if(80 > rand(100) || sti(PChar.skill.Fortune) > rand(100)) // Попытка отмазаться
			//{
				link.l1 = "Officier, vous commettez une erreur grave en cherchant à retenir deux innocents. Croyez-moi, je ne connais pas cet homme et je me moque éperdument de lui."+" Je suis certain que votre commandant sera fort mécontent de vous, si vous retenez deux citoyens respectueux des lois...";
				link.l1.go = "ContraDeliverQuest_Sold2_Liberty";
			//}
			/*else // Тюрьма
			{
				link.l1 = "";
				link.l1.go = "ContraDeliverQuest_Sold2_Prison";
			}*/
			break;
			
		case "ContraDeliverQuest_Sold2_Liberty":
			dialog.text = "Hmm... Oui, peut-être que tu as raison. Le commandant sera sûrement mécontent de cela. Tu sais quoi - oublions simplement ce petit incident.";
				link.l1 = "Merci, officier, vous nous avez fait gagner du temps. J'aimerais vous demander d'être plus prudent la prochaine fois, certainement vous ne voudriez pas être rétrogradé, n'est-ce pas ?";
				link.l1.go = "ContraDeliverQuest_Sold2_Liberty1";
			break;
			
		case "ContraDeliverQuest_Sold2_Liberty1":
			dialog.text = "Non, en aucun cas. Dans ce cas, veuillez vous disperser. À bientôt...";
				link.l1 = "C'est mieux !";
				link.l1.go = "ContraDeliverQuest_Sold2_Liberty2";
			break;
			
		case "ContraDeliverQuest_Sold2_Liberty2":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			ContraDeliverQuest_SoldiersGoOut();
			break;
		
		case "ContraDeliverQuest_1":
			iMoney = (rand(3)+2)*500;
			if(rand(1) == 0) // Денег не даёт
			{
				dialog.text = "Excellent ! Et maintenant, tu peux t'égarer !";
					link.l1 = "Quoi ?! Et qu'en est-il de l'argent ? Nous avions un accord...";
					link.l1.go = "ContraDeliverQuest_NoMon";
			}
			else // Деньги или патруль
			{
				if(rand(2) == 1) // Патруль
				{
					dialog.text = "Merci pour la livraison. Maintenant, tu peux filer... attends, quelqu'un arrive...";
						link.l1 = "Quoi?!";
						link.l1.go = "ContraDeliverQuest_Patrol";
				}
				else // Просто отдает деньги
				{
					dialog.text = "Génial. Merci pour la livraison. Tiens, prends "+FindRussianMoneyString(iMoney)". Et garde à l'esprit que les contrebandiers se souviendront toujours des braves gens...";
					link.l1 = "J'espère bien. Adieu.";
					link.l1.go = "ContraDeliverQuest_GoWithMoney";
					PChar.GenQuest.ContraDeliver.Money = iMoney;
				}
			}
			
			ChangeContrabandRelation(PChar, 5); // Письмо доставили - повышаем отношение у контриков
			ChangeCharacterComplexReputation(pchar,"nobility", -5); // Помогли контрикам - репу понижаем
			RemoveItems(PChar, "letter_1", 1);
			BackItemDescribe("letter_1");
			DeleteAttribute(&Items[FindItem("letter_1")], "City");
			rChar = &Characters[GetCharacterIndex(Locations[FindLocation(PChar.location)].townsack + "_Smuggler")];
			SaveCurrentNpcQuestDateParam(rChar, "work_date");
			break;
			
		case "ContraDeliverQuest_Patrol":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			LAi_LocationFightDisable(LoadedLocation, true); // Чтоб не поубивали кого-нить
			ContraDeliverQuest_GeneratePatrolToRoom();
			break;
			
		case "ContraDeliverQuest_NoMon":
			dialog.text = "Ecoute... toi et moi n'avions aucun accord entre nous. Réclame ton argent à celui qui a conclu cet accord avec toi.";
				link.l1 = "Eh bien, ce n'est certainement pas mon jour de chance, que puis-je dire de plus?! Bon, à la prochaine...";
				link.l1.go = "ContraDeliverQuest_GoWithoutMoney";
				link.l2 = RandSwear()+"Tu répondras de cela ! Prépare-toi à mourir !";
				link.l2.go = "ContraDeliverQuest_PrepareToFight";
			break;
			
		case "ContraDeliverQuest_GoWithoutMoney": // Уходим без денег
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			chrDisableReloadToLocation = false;
			bDisableFastReload         = false;
			PChar.GenQuest.ContraDeliver.Complete.WithoutMoney = true;
			sQuestTitle = PChar.GenQuest.ContraDeliver.QuestTown + "ContraDeliverQuest";
			AddQuestRecordEx(sQuestTitle, "ContraDeliverQuest", "4");
			AddQuestUserData(sQuestTitle, "sColony", XI_ConvertString("Colony" + PChar.GenQuest.ContraDeliver.QuestTown));
			LAi_ActorGoToLocation(NPChar, "reload", "reload1_back", "none", "", "", "", 3.0);
			break;
			
		case "ContraDeliverQuest_PrepareToFight":
			dialog.text = "Tu as osé me défier, "+GetSexPhrase("avorton","ordure")+"? Eh bien, tu ne sais vraiment pas ce qui est bon pour toi. Je vais t'éventrer !";
				link.l1 = "... ";
				link.l1.go = "ContraDeliverQuest_Fight";
			break;
			
		case "ContraDeliverQuest_Fight": // Бой
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			LAi_SetImmortal(NPChar, false);
			LAi_ActorAttack(NPChar, PChar, "");
			LAi_SetFightMode(PChar, true);
			SetFunctionNPCDeathCondition("ContraDeliverQuest_ContraIsDead", NPChar.ID, false);
			break;
			
		case "ContraDeliverQuest_GoWithMoney": // Уходим с деньгами
			AddMoneyToCharacter(PChar, sti(PChar.GenQuest.ContraDeliver.Money));
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			chrDisableReloadToLocation = false;
			bDisableFastReload         = false;
			sQuestTitle = PChar.GenQuest.ContraDeliver.QuestTown + "ContraDeliverQuest";
			AddQuestRecordEx(sQuestTitle, "ContraDeliverQuest", "3");
			AddQuestUserData(sQuestTitle, "sMoney", FindRussianMoneyString(sti(PChar.GenQuest.ContraDeliver.Money)));
			CloseQuestHeader(sQuestTitle);
			DeleteAttribute(PChar, "GenQuest.ContraDeliver"); // Квест пройден - атрибуды потрем
			LAi_ActorGoToLocation(NPChar, "reload", "reload1_back", "none", "", "", "", 3.0);
			break;
		// <-- Квест на доставку письма контрику
			
		// Церковеый генератор. Квест № 1. Диалог кэпа, которого ищем -->
		case "ChurchGenQuest_1_DeckDialog_1":
			if(CheckAttribute(PChar, "GenQuest.ChurchQuest_1.NeedToDialogWithCap"))
			{
				if(CheckAttribute(PChar, "GenQuest.ChurchQuest_1.CapWaitOnTavern")) // Если ждёт в таверне
				{
					dialog.text = RandPhraseSimple("Un demi-millier d'hommes ! Et un coffre de mort ! Hic !","Bois ! Hic ! Et le diable a fait pour le - Hic ! - reste !");
						link.l1 = "Ohh... Eh bien. Bonjour, monsieur "+GetFullname(NPChar)+".";
						link.l1.go = "ChurchGenQuest1_DialogInTavernWithCap_2";
						PChar.Quest.Church_GenQuest1_Timer.over = "yes";
				}
				else // на палубе своего шипа
				{
					if(!CheckAttribute(PChar, "GenQuest.ChurchQuest_1.Complete"))
					{
						dialog.text = "D'accord, voyons voir maintenant... Trois morceaux de toile à voile, des planches pour la coque du navire, remplacer les haubans et les cordages sur les vergues...";
							link.l1 = "Bonjour, monsieur "+GetFullName(NPChar)+". Je suis capitaine "+PChar.name+".";
							link.l1.go = "ChurchGenQuest1_DialogShip_1";
					}
					else
					{
						dialog.text = LinkRandPhrase("Quittez mon navire immédiatement, j'ai beaucoup à faire sans vous !","Vous avez reçu vos livres, que voulez-vous d'autre?!","J'ai fait tout ce que tu voulais, que veux-tu de plus de moi?!");
							link.l1 = "Ne t'excite pas autant ou tu vas faire une crise cardiaque !";
							link.l1.go = "exit";
					}					
				}
			}
			else
			{
				dialog.text = RandPhraseSimple("Rhum, rhum ! Donne-moi du rhum... Hic !","Ça fait longtemps... hic... que je n'ai pas été saoul comme ça...");
					link.l1 = "Oui, ta cale est pleine... peut-être qu'il est temps de mettre le cap sur une crique ?";
					link.l1.go = "exit";
			}			
			NextDiag.TempNode = "ChurchGenQuest_1_DeckDialog_1";
			break;
			
		case "ChurchGenQuest1_DialogInTavernWithCap_2":
			dialog.text = RandPhraseSimple("Veuillez vous asseoir, cap... hic... taine ! Quel est votre poison ?","Asseyez-vous, capitaine ! Que voulez-vous boire ? Hips...");
					link.l1 = "Merci, mais je préférerais une bonne conversation avec un homme respectable.";
					link.l1.go = "ChurchGenQuest1_DialogInTavernWithCap_3";
			break;
			
		case "ChurchGenQuest1_DialogInTavernWithCap_3":
			dialog.text = "Essaye-tu - hic ! - de m'insulter ?.. Il n'y a pas un seul homme décent dans cette taverne ! Hic ! Que des bandits et des coupe-jarrets ! Tous des extorqueurs, et celui-là... le premier d'entre eux ! Leur chef, une murène dans la gorge !";
				link.l1 = "Je parlais de vous. C'est vous que je souhaite rencontrer. Et qui est le chef des bandits et pourquoi voudrait-il...";
				link.l1.go = "ChurchGenQuest1_DialogInTavernWithCap_4";
			break;
			
		case "ChurchGenQuest1_DialogInTavernWithCap_4":
			dialog.text = "Raté"+GetSexPhrase("ter","s")+"! Ma chère ! Comment vous appeliez-vous, déjà ? Je vous respecte ! Personne n'a encore traité un vieux loup de mer d'homme décent jusqu'à présent ! Je ferais n'importe quoi pour vous ! Je vous donnerais tout mon argent, jusqu'au dernier peso !.. Oh, j'ai juste oublié. Je suis fauché. Je n'ai même plus un seul roolie. Ce salaud, ce racketteur vient de me prendre le dernier rouleau, que les démons chargent leurs canons avec ses tripes en enfer !";
				link.l1 = "Capitaine monsieur? Êtes-vous d'accord? Réalisez-vous que vous délirez? Quels parchemins?";
				link.l1.go = "ChurchGenQuest1_DialogInTavernWithCap_5";
			break;
			
		case "ChurchGenQuest1_DialogInTavernWithCap_5":
			dialog.text = "Non, non ! Ce vieux capitaine est peut-être ivre, mais il garde encore toute sa tête. Les livres et les parchemins m'ont été donnés par le père "+PChar.GenQuest.ChurchQuest_1.ToName+", je les emmenais à "+XI_ConvertString("Colony"+PChar.GenQuest.ChurchQuest_1.QuestTown)+"Et le matin, je suis allé à l'église locale et j'ai mentionné ces livres au père local. Bien sûr, il voulait les voir, tu sais comment ils sont, ils sont fous de la vie de leurs saints et tout ce bazar. Alors, j'ai envoyé un mousse chercher le coffre avec eux. Et pendant que j'attendais, j'ai décidé de jouer un peu... et d'une manière ou d'une autre j'ai perdu tout mon argent. Tout! Rien pour payer la boisson! Alors, le propriétaire de la taverne a pris les livres en gage, et puis je lui ai aussi donné les rouleaux...";
				link.l1 = "Alors, tu as vendu des livres, les livres sacrés qui t'ont été confiés par le prêtre  "+XI_ConvertString("Colony"+PChar.GenQuest.ChurchQuest_1.ToColony+"Gén")+"?";
				link.l1.go = "ChurchGenQuest1_DialogInTavernWithCap_6";
			break;
			
		case "ChurchGenQuest1_DialogInTavernWithCap_6":
			dialog.text = "Je sais, je sais... Je brûlerai en Enfer pour toute l'éternité. Je ne peux plus montrer mon visage ni au Père, qui m'a confié cette mission, ni à celui qui livrait les papiers, ni au local... Qui priera maintenant pour mon âme ? Et s'ils m'excommunient ? Oh, malheur à moi... J'ai besoin d'un verre...";
				link.l1 = "Eh là, détends-toi, ce n'est pas si grave. Tes actions étaient misérables et impies, et pourtant je suis prêt à t'aider. Je vais payer ta dette et acheter ces manuscrits. De plus, puisque je connais déjà les deux prêtres mentionnés, je vais naviguer directement vers "+XI_ConvertString("Colony"+PChar.GenQuest.ChurchQuest_1.QuestTown)+" afin de livrer les documents là-bas. Marché conclu ?";
				link.l1.go = "ChurchGenQuest1_DialogInTavernWithCap_7";
			break;
			
		case "ChurchGenQuest1_DialogInTavernWithCap_7":
			dialog.text = "Sauveur ! Ange de Dieu... Bien sûr, j'accepte ! Je te donnerais tout... tout ! Si seulement je pouvais boire encore un coup...";
				link.l1 = "Je suppose que tu en as déjà assez... Oh, peu importe. Je t'achèterai encore du rhum chez le barman.";
				link.l1.go = "ChurchGenQuest1_DialogInTavernWithCap_8";
			break;
			
		case "ChurchGenQuest1_DialogInTavernWithCap_8":
			DialogExit();
			DeleteAttribute(PChar, "GenQuest.ChurchQuest_1.NeedToDialogWithCap");
			PChar.GenQuest.ChurchQuest_1.NeedToDialogWithBarmen = true;
			sQuestTitle = PChar.GenQuest.ChurchQuest_1.QuestTown + "ChurchGenQuest1";
			AddQuestRecordEx(sQuestTitle, "ChurchGenQuest1", "7_2");
			AddQuestUserData(sQuestTitle, "sColony", XI_ConvertString("Colony" + PChar.GenQuest.ChurchQuest_1.QuestTown));
			AddQuestUserData(sQuestTitle, "sCapName", GetFullName(NPChar));
			NextDiag.CurrentNode = "ChurchGenQuest_1_DeckDialog_1";
			break;
			
		case "ChurchGenQuest1_DialogShip_1":
			dialog.text = "...et les draps ! Nous devons aussi remplacer les draps !.. Oh, salut. S'il vous plaît, ne soyez pas offensé, m'sieur"+GetSexPhrase("ter","s")+" quel-que-soit-votre-nom, mais pour l'instant, comme vous pouvez le voir, je suis assez occupé, alors si vous avez affaire avec moi, veuillez être rapide.";
				link.l1 = "Autant que je sache, père "+PChar.GenQuest.ChurchQuest_1.ToName+"a donné quelques papiers sacrés dans "+XI_ConvertString("Colony"+PChar.GenQuest.ChurchQuest_1.ToColony+"Voc")+". Tu as promis de les livrer à "+XI_ConvertString("Colony"+PChar.GenQuest.ChurchQuest_1.QuestTown)+" parce que tu naviguais de toute façon dans cette direction."; // belamour gen
				link.l1.go = "ChurchGenQuest1_DialogShip_2";
			break;
			
		case "ChurchGenQuest1_DialogShip_2":
			dialog.text = "Je me dirigeais dans cette direction, jusqu'à ce que cette maudite tempête détruise presque mon vieux rafiot, et je suis resté coincé ici pour l'amour du ciel sait combien de temps ! Ces escrocs sur les quais essaient sans cesse de me refourguer des planches pourries échouées par la marée pour la coque du navire, et pour les voiles, quelque vieux sac de jute sur lequel leurs grands-mères dormaient quand elles étaient encore jeunes.";
				link.l1 = "Monsieur, la prochaine fois je serai ravi d'écouter vos histoires magnifiques mais pour l'instant j'aimerais en savoir plus sur le sort des livres et manuscrits que vous avez reçus à "+XI_ConvertString("Colony"+PChar.GenQuest.ChurchQuest_1.ToColony+"Ça")+".";
				link.l1.go = "ChurchGenQuest1_DialogShip_3";
			break;
			
		case "ChurchGenQuest1_DialogShip_3":
			dialog.text = "Personne, tu m'entends ? Personne n'ose me blâmer pour le retard de la livraison de ces maudits papiers !";
				link.l1 = "Oh, non, je n'ai certainement pas voulu dire cela. Je voulais seulement alléger votre fardeau. Le fait est que "+PChar.GenQuest.ChurchQuest_1.ToName+"s'inquiète beaucoup des livres et papiers à livrer à "+XI_ConvertString("Colony"+PChar.GenQuest.ChurchQuest_1.QuestTown)+"En fait, je vais y naviguer tout de suite.";
				link.l1.go = "ChurchGenQuest1_DialogShip_4";
			break;
			
		case "ChurchGenQuest1_DialogShip_4":
		if(rand(3) != 1)
		{
			dialog.text = "Il me semble, mis"+GetSexPhrase("ter","s")+", que vous avez un conseiller spirituel dans chaque port. Bien que cela ne me concerne en rien. Si tu t'intéresses à ces foutaises, alors prends tes livres et fiche le camp ! Bon débarras !";
				link.l1 = "Merci, monsieur le capitaine. Bonne chance avec vos réparations.";
				link.l1.go = "ChurchGenQuest1_DialogShip_5_1";
		}
		else // Свитки не отдает
		{
			dialog.text = "Ne t'en fais pas pour ça, mon vieux"+GetSexPhrase("ter","s")+", et voyagez vers "+XI_ConvertString("Colony"+PChar.GenQuest.ChurchQuest_1.QuestTown)+" légèrement, puisque c'était moi qui m'étais chargé de livrer ces papiers, et ce sera moi qui vais le faire à tout prix, pour que personne ne crie à chaque coin de rue que le capitaine "+NPChar.name+" n'a pas tenu parole !";
				link.l1 = "Mais monsieur le capitaine, le fait est en réalité...";
				link.l1.go = "ChurchGenQuest1_DialogShip_5_2";
		}
			break;
			
		case "ChurchGenQuest1_DialogShip_5_1":
			DialogExit();
			AddItems(PChar, "Bible", 1);	// Даем рукописи
			items[FindItem("Bible")].Name = "itmname_ChurchGenQuest1Bible";	// Меняем имя. Потом поменять обратно!
			ChangeItemDescribe("Bible", "itmdescr_ChurchGenQuest1Bible"); // Меняем дескрайб. Потом поменять обратно!
			items[FindItem("Bible")].City = XI_ConvertString("Colony" + PChar.GenQuest.ChurchQuest_1.QuestTown + "Gen"); // Переменная. Потом удалить!
			sQuestTitle = PChar.GenQuest.ChurchQuest_1.QuestTown + "ChurchGenQuest1";
			AddQuestRecordEx(sQuestTitle, "ChurchGenQuest1", "10");
			AddQuestUserData(sQuestTitle, "sSex", GetSexPhrase("",""));
			AddQuestUserData(sQuestTitle, "sColony", XI_ConvertString("Colony" + PChar.GenQuest.ChurchQuest_1.QuestTown));
			AddQuestUserData(sQuestTitle, "sCapName", GetFullName(NPChar));
			PChar.GenQuest.ChurchQuest_1.Complete = true; // Квест выполнен
			SetFunctionTimerCondition("Church_GenQuest1_DeleteCapitan", 0, 0, 1, false); // Трем судно кэпа
			break;
			
		case "ChurchGenQuest1_DialogShip_5_2":
			dialog.text = "En fait, le point est que je n'ai aucune affaire avec toi du tout. Le Saint Père m'a donné une tâche, livrer les livres à "+XI_ConvertString("Colony"+PChar.GenQuest.ChurchQuest_1.QuestTown)+" et remets-les au prêtre local. Et je ne te vois pas là-bas. Pas du tout ! Bonne chance.";
//				link.l1 = "Très bien, alors. Vous êtes un homme très responsable, bien que ce soit votre seul mérite. Bonne chance à vous, mon ami discourtois";
//				link.l1.go = "ChurchGenQuest1_DialogShip_5_2_1"; // Сваливаем, поверили ему
				link.l2 = "J'en ai assez de ton comportement insolent. Ta bouche stupide peut forcer même un ange à devenir violent. Je dois accomplir la volonté de mon saint père et j'utiliserai mon arme si je dois !";
				link.l2.go = "ChurchGenQuest1_DialogShip_5_2_2"; // 
			break;
			
		case "ChurchGenQuest1_DialogShip_5_2_1":
			DialogExit();
			sQuestTitle = PChar.GenQuest.ChurchQuest_1.QuestTown + "ChurchGenQuest1";
			AddQuestRecordEx(sQuestTitle, "ChurchGenQuest1", "11");
			AddQuestUserData(sQuestTitle, "sColony", XI_ConvertString("Colony" + PChar.GenQuest.ChurchQuest_1.QuestTown));
			AddQuestUserData(sQuestTitle, "sCapName", GetFullName(NPChar));
			PChar.GenQuest.ChurchQuest_1.Complete.NoManuscripts = true; // Квест выполнен без манускриптов
			SetFunctionTimerCondition("Church_GenQuest1_DeleteCapitan", 0, 0, 1, false); // Трем судно кэпа
			break;
			
		case "ChurchGenQuest1_DialogShip_5_2_2":
			dialog.text = "Silence, silence, capitaine "+PChar.name+"! Qu'est-ce qui t'arrive ? Oh, eh bien, je vois que si tu n'apportes pas ces papiers, tous ces Saints Pères seraient assez en colère contre toi, sans parler de notre Père céleste. D'accord, prends tes précieuses théologiques et pars avec la bénédiction de Dieu.";
				link.l1 = "Ravi que tu aies non seulement compris ma position, mais aussi retenu mon nom. Je te suggère de t'en souvenir chaque fois que tu t'apprêtes à faire quelque chose de stupide.";
				link.l1.go = "ChurchGenQuest1_DialogShip_5_2_3"; // Сваливаем, поверили ему
			break;
			
		case "ChurchGenQuest1_DialogShip_5_2_3":
			DialogExit();
			AddItems(PChar, "Bible", 1);	// Даем рукописи
			items[FindItem("Bible")].Name = "itmname_ChurchGenQuest1Bible";	// Меняем имя. Потом поменять обратно!
			ChangeItemDescribe("Bible", "itmdescr_ChurchGenQuest1Bible"); // Меняем дескрайб. Потом поменять обратно!
			items[FindItem("Bible")].City = XI_ConvertString("Colony" + PChar.GenQuest.ChurchQuest_1.QuestTown + "Gen"); // Переменная. Потом удалить!
			sQuestTitle = PChar.GenQuest.ChurchQuest_1.QuestTown + "ChurchGenQuest1";
			AddQuestRecordEx(sQuestTitle, "ChurchGenQuest1", "10");
			AddQuestUserData(sQuestTitle, "sSex", GetSexPhrase("",""));
			AddQuestUserData(sQuestTitle, "sColony", XI_ConvertString("Colony" + PChar.GenQuest.ChurchQuest_1.QuestTown)); // belamour gen
			AddQuestUserData(sQuestTitle, "sCapName", GetFullName(NPChar));
			PChar.GenQuest.ChurchQuest_1.Complete = true; // Квест выполнен
			SetFunctionTimerCondition("Church_GenQuest1_DeleteCapitan", 0, 0, 1, false); // Трем судно кэпа
			break;
			
		// <-- Церковеый генератор. Квест № 1. Диалог кэпа, которого ищем
			
		case "Left_Time_Case":
			dialog.text = RandPhraseSimple("Va-t'en...","Ne me dérange pas !");
				link.l1 = "...";
				link.l1.go = "exit";
				NextDiag.TempNode = "Left_Time_Case";
			break;
			
		case "Church_GenQuest_2_1":
			if(sti(PChar.GenQuest.ChurchQuest_2.BanditsCount) == 1)
			{
				dialog.text = RandSwear()+"Tu n'aurais pas dû dire ça ! Maintenant, je vais devoir t'envoyer voir le Seigneur pour prier pour le pardon de mes péchés !";
			}
			
			if(sti(PChar.GenQuest.ChurchQuest_2.BanditsCount) == 2)
			{
				dialog.text = RandSwear()+"Tu n'aurais pas dû dire ça ! Maintenant, je vais devoir t'envoyer voir le Seigneur pour prier pour le pardon de nos péchés !";
			}
			
			if(sti(PChar.GenQuest.ChurchQuest_2.BanditsCount) > 2)
			{
				dialog.text = RandSwear()+"Tu n'aurais pas dû dire ça ! Maintenant, je vais devoir t'envoyer auprès du Seigneur pour prier le pardon de tous nos péchés !";
			}
			
				link.l1 = "Guère, mate. Chacun répondra de lui-même au bon Dieu !";
				link.l1.go = "exit";
				NPChar.money = sti(PChar.GenQuest.ChurchQuest_2.MoneyCount);
				LAi_LocationFightDisable(LoadedLocation, false);
				AddDialogExitQuest("Church_GenQuest2_BanditsIsEnemies");
			break;
			
		case "Church_GenQuest_2_ShoreBandit_1":
			dialog.text = "Hé, pourquoi jurer ? Et si j'avais affaire avec toi.";
				link.l1 = "Ça, c'est des nouvelles ! Tu sais, je cause pas beaucoup avec des gens comme toi !";
				link.l1.go = "Church_GenQuest_2_ShoreBandit_2";
				LAi_LocationFightDisable(LoadedLocation, false);
			break;
			
		case "Church_GenQuest_2_ShoreBandit_2":
			dialog.text = "Eh bien, je ne vais pas non plus m'éterniser en discussions avec toi. Mais peut-être serais-tu intéressé par l'achat de quelques babioles à bon prix ?";
				link.l1 = "Ai-je l'air d'un fichu receleur de biens volés ?!";
				link.l1.go = "Church_GenQuest_2_ShoreBandit_3";
			break;
			
		case "Church_GenQuest_2_ShoreBandit_3":
			if(rand(1) == 0)
			{
				dialog.text = "Doucement, doucement, il n'y a point de voleurs parmi nous ! Ce vase nous a été donné pour un travail honnête ! Regardez donc... or pur, orné de perles. Mais le fait est que nous n'en avons point besoin. Alors nous voulons simplement le vendre et partager l'argent.";
					link.l1 = "Laisse-moi regarder de plus près... Oh là là ! C'est le calice de communion !!! Donc, vous êtes ces blasphémateurs qui ont pillé l'église de "+XI_ConvertString("Colony"+PChar.GenQuest.ChurchQuest_2.QuestTown+"Gen")+"?! Te voilà!";
					link.l1.go = "Church_GenQuest_2_ShoreBandit_4";
					break;
			}
		
			dialog.text = "Silence, moussaillon"+GetSexPhrase("ter"," s ")+" hypocrite! Tu sais, nous manquons un peu d'argent, alors nous avons décidé de vendre quelque chose. Regarde ce vase... or pur, orné de perles. Prix spécial pour toi, disons, mille pièces.";
				link.l1 = "Laissez-moi y jeter un oeil de plus près... Oh là là ! C'est le calice de communion !!! Alors, vous êtes ces blasphémateurs qui avaient pillé l'église de "+XI_ConvertString("Colony"+PChar.GenQuest.ChurchQuest_2.QuestTown+"Gen")+"?! Te voilà!";
				link.l1.go = "Church_GenQuest_2_ShoreBandit_Real_Band_1";
			break;
			
		case "Church_GenQuest_2_ShoreBandit_4":
			dialog.text = "Du calme, m'sieur"+GetSexPhrase("ter","s")+"!.. Bon sang, j'ai dit à cet imbécile de ne pas faire de grabuge avant que le moment soit venu...";
				link.l1 = "Qu'est-ce que tu radotes ? Bon, fais ton choix : soit tu me donnes ton butin volé de ton plein gré, soit j'appelle la garde.";
				link.l1.go = "Church_GenQuest_2_ShoreBandit_5";
			break;
			
		case "Church_GenQuest_2_ShoreBandit_5":
			dialog.text = "Écoute, "+GetSexPhrase("bonhomme","jeune demoiselle")+", nous n'avons pas besoin de querelles, alors résolvons cette affaire pacifiquement. Vous devez nous croire, nous n'avons pas réellement pillé cette église, et nous n'avons pas d'argent. Oui, nous avons reçu quelques pesos et ce bibelot doré pour avoir simulé le vol. Et cette coupe en or était la seule chose qu'il nous restait après avoir payé les contrebandiers...";
				link.l1 = "Alors, tu essaies de dire que...";
				link.l1.go = "Church_GenQuest_2_ShoreBandit_6";
			break;
			
		case "Church_GenQuest_2_ShoreBandit_6":
			dialog.text = "Ce maudit prêtre nous a engagés, c'est ce que je dis ! Mais pourquoi a-t-il dû vous envoyer vers nous ?.. Eh bien, nous sommes quittes maintenant. Prenez ce vase et montrez-le à cet hypocrite, vous verrez par vous-même qu'il se tortillera comme un calamar sur le banc de sable !";
				link.l1 = "Donne-moi la coupe et dégage, avant que je change d'avis.";
				link.l1.go = "Church_GenQuest_2_ShoreBandit_7";
				link.l2 = "Tu parles bien, mais je ne suis pas si facile à duper. Si tu veux me convaincre, alors convaincs d'abord ma lame.";
				link.l2.go = "Church_GenQuest_2_ShoreBandit_8";
				// Тут давать чашу, если будет
				ChurchGenQuest2_GiveCup();
				PChar.GenQuest.ChurchQuest_2.Complete.PriestIsThief = true;
			break;
			
		case "Church_GenQuest_2_ShoreBandit_7":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			iBanditsCount = PChar.GenQuest.ChurchQuest_2.BanditsCount;
			for(i=0; i<iBanditsCount; i++)
			{
				rChar = CharacterFromID("Church_GenQuest2_Bandit_" + i);
				LAi_Type_Actor_Reset(rChar);
				LAi_CharacterDisableDialog(rChar);
				rChar.LifeDay = 0;
				LAi_ActorRunToLocation(rChar, "reload", "reload1_back", "none", "", "", "", -1);
			}
			
			// Разрешим генерацию энкаунтеров, откроем выходы
			DeleteAttribute(LoadedLocation, "DisableEncounters");
			chrDisableReloadToLocation = false;
			
			sQuestTitle = PChar.GenQuest.ChurchQuest_2.QuestTown + "ChurchGenQuest2";
			AddQuestrecordEx(sQuestTitle, "ChurchGenQuest2", "10_1");
			AddQuestUserData(sQuestTitle, "sName", PChar.GenQuest.ChurchQuest_2.QuestTown.PriestName);
			break;
			
		case "Church_GenQuest_2_ShoreBandit_8":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			AddDialogExitQuest("Church_GenQuest2_BanditsIsEnemies");
			sQuestTitle = PChar.GenQuest.ChurchQuest_2.QuestTown + "ChurchGenQuest2";
			AddQuestrecordEx(sQuestTitle, "ChurchGenQuest2", "10_2");
			break;
			
		case "Church_GenQuest_2_ShoreBandit_Real_Band_1":
			if(PChar.GenQuest.ChurchQuest_2.BanditsCount == 1)
			{
				dialog.text = RandSwear()+"N'ai-je pas dit à ces vauriens : gardez vos pattes avides et ne prenez rien d'autre que de l'argent du prêtre !";
			}
			else
			{
				dialog.text = RandSwear()+"N'ai-je pas dit à ces insatiables fripouilles : gardez vos pattes avides et ne prenez rien d'autre que de l'argent du prêtre !";
			}
			
					link.l1 = "Qu'est-ce que tu radotes ? Très bien, fais ton choix : soit tu me donnes ton butin volé de ton plein gré, soit j'appelle les gardes.";
					link.l1.go = "Church_GenQuest_2_ShoreBandit_Real_Band_2";
			break;
			
		case "Church_GenQuest_2_ShoreBandit_Real_Band_2":
			dialog.text = "Je fais un autre choix, tu fermes ta grande gueule et tu me donnes ta bourse, et je t'épargne la vie.";
				link.l1 = "Je vais vous aider à obtenir une audience avec notre Seigneur maintenant !";
				link.l1.go = "Church_GenQuest_2_ShoreBandit_Real_Band_2_1";
				link.l2 = "D'accord, je vais te donner un peu d'argent, mais de mon propre gré, pour que toi et tes amis puissiez mener une vie honnête et n'ayez pas à vous abaisser à des actes de piraterie.";
				link.l2.go = "Church_GenQuest_2_ShoreBandit_Real_Band_2_2";
				link.l3 = "Ehh... D'accord, mettons de côté nos différends et revenons au début de notre conversation. Alors, combien voulais-tu pour ce truc ?";
				link.l3.go = "Church_GenQuest_2_ShoreBandit_Real_Band_2_3";
			break;
			
		case "Church_GenQuest_2_ShoreBandit_Real_Band_2_1":
			// Не забыть чашу!
			ChurchGenQuest2_GiveCup();
			PChar.GenQuest.ChurchQuest_2.Complete.With_All = true;
			NPChar.money = ((rand(3) + 6) * 1000);
			PChar.GenQuest.ChurchQuest_2.MoneyCount = NPChar.money;
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			AddDialogExitQuest("Church_GenQuest2_BanditsIsEnemies");
			sQuestTitle = PChar.GenQuest.ChurchQuest_2.QuestTown + "ChurchGenQuest2";
			AddQuestrecordEx(sQuestTitle, "ChurchGenQuest2", "11_1");
			AddQuestUserData(sQuestTitle, "sSex", GetSexPhrase("",""));
			AddQuestUserData(sQuestTitle, "sSex1", GetSexPhrase("",""));
			break;
			
		case "Church_GenQuest_2_ShoreBandit_Real_Band_2_2":
			AddMoneyToCharacter(PChar, -sti(PChar.money)/2); // Забираем половину денег
			PChar.GenQuest.ChurchQuest_2.Complete.Without_All = true; // Полностью проигрышный вариант. Остаемся ни с чем
			iBanditsCount = PChar.GenQuest.ChurchQuest_2.BanditsCount;
			for(i=0; i<iBanditsCount; i++)
			{
				rChar = CharacterFromID("Church_GenQuest2_Bandit_" + i);
				LAi_SetCitizenType(rChar);
				rChar.LifeDay = 0;
				rChar.Dialog.Currentnode = "First time";
			}
			
			DeleteAttribute(PChar, "GenQuest.ChurchQuest_2.BanditsInShore");
			sQuestTitle = PChar.GenQuest.ChurchQuest_2.QuestTown + "ChurchGenQuest2";
			AddQuestRecordEx(sQuestTitle, "ChurchGenQuest2", "11_2");
			AddQuestUserData(sQuestTitle, "sSex", GetSexPhrase("",""));
			AddQuestUserData(sQuestTitle, "sSex1", GetSexPhrase("",""));
			DeleteAttribute(LoadedLocation, "DisableEncounters");
			chrDisableReloadToLocation = false;
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			break;
			
		case "Church_GenQuest_2_ShoreBandit_Real_Band_2_3":
			iMoney = makeint(makeint(Pchar.money)/20)*10;
			dialog.text = "Je n'ai pas besoin de problèmes non plus, "+GetAddress_Form(pchar)+", mais maintenant le prix a augmenté. Pour cette coupe précieuse, je réclamerai tout ce que vous avez sur vous.";
			if(iMoney >= makeint(Pchar.rank)*300)
			{
				link.l1 = "Espèce de canaille avide ! Je n'ai que "+FindRussianMoneyString(iMoney)+"avec moi. Prends-le et va-t'en !";
				link.l1.go = "Church_GenQuest_2_ShoreBandit_Real_Band_2_3_1";
			}
			else
			{
				link.l1 = "Mauvais choix, rat cupide. Tu ne profiteras pas à mes dépens !"+GetSexPhrase(" Je suis libre comme le vent - aujourd'hui ici, demain là-bas, aujourd'hui je suis pauvre - demain je serai riche...","")+"";
				link.l1.go = "Church_GenQuest_2_ShoreBandit_Real_Band_2_3_2";
			}
			break;
			
		case "Church_GenQuest_2_ShoreBandit_Real_Band_2_3_1":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			ChurchGenQuest2_GiveCup();	// Даем чашу
			AddMoneyToCharacter(PChar, -(makeint(makeint(Pchar.money)/20)*10));
			PChar.GenQuest.ChurchQuest_2.Complete.Only_With_Cup = true;
			iBanditsCount = PChar.GenQuest.ChurchQuest_2.BanditsCount;
			for(i=0; i<iBanditsCount; i++)
			{
				rChar = CharacterFromID("Church_GenQuest2_Bandit_" + i);
				LAi_SetCitizenType(rChar);
				rChar.LifeDay = 0;
				rChar.Dialog.Currentnode = "Left_Time_Case"; // Диалог не забыть поменять.
			}
			
			DeleteAttribute(LoadedLocation, "DisableEncounters");
			chrDisableReloadToLocation = false;
			sQuestTitle = PChar.GenQuest.ChurchQuest_2.QuestTown + "ChurchGenQuest2";
			AddQuestrecordEx(sQuestTitle, "ChurchGenQuest2", "11_3");
			AddQuestUserData(sQuestTitle, "sSex", GetSexPhrase("",""));
			DeleteAttribute(PChar, "GenQuest.ChurchQuest_2.BanditsInShore");
			break;

		case "Church_GenQuest_2_ShoreBandit_Real_Band_2_3_2":
			dialog.text = "N'essaierais-tu pas de dire qu'en ce jour particulier "+GetSexPhrase("tu es pauvre","tu n'as pas d'argent")+"?! ";
				link.l1 = "Exactement, mon avide ami, à votre grande déception. Et maintenant je dois m'excuser, j'ai beaucoup à faire.";
				link.l1.go = "Church_GenQuest_2_ShoreBandit_Real_Band_2_3_3";	
			break;
			
		case "Church_GenQuest_2_ShoreBandit_Real_Band_2_3_3":
			dialog.text = "Halte-là ! Nous allons vérifier cela, et si tu n'as pas dit la vérité, je mettrai ta langue menteuse dans une colonie de fourmis !";
				link.l1 = "Après avoir dit ça, t'es foutu!";
				link.l1.go = "Church_GenQuest_2_ShoreBandit_Real_Band_2_3_4";
			break;
			
		// Можно этот кэйс - Church_GenQuest_2_ShoreBandit_Real_Band_2_1
		case "Church_GenQuest_2_ShoreBandit_Real_Band_2_3_4":
				// ГГ как-бы может обыскать трупики и забрать все барахло...
				PChar.GenQuest.ChurchQuest_2.Complete.With_All = true;
				NPChar.money = ((rand(3) + 6) * 1000);
				PChar.GenQuest.ChurchQuest_2.MoneyCount = NPChar.money;
				DialogExit();
				NextDiag.CurrentNode = NextDiag.TempNode;
				AddDialogExitQuest("Church_GenQuest2_BanditsIsEnemies");
				sQuestTitle = PChar.GenQuest.ChurchQuest_2.QuestTown + "ChurchGenQuest2";
				AddQuestrecordEx(sQuestTitle, "ChurchGenQuest2", "11_4");
				AddQuestUserData(sQuestTitle, "sSex", GetSexPhrase("As a real gentleman, I am honest","I am honest"));
			break;
			
		///////////////////////////////////////////////////////////////////////////////////////////////////
		// ГЕНЕР "PIRATES ON AN UNINHABITED ISLAND"
		///////////////////////////////////////////////////////////////////////////////////////////////////
		
		case "PiratesOnUninhabited_1":
			dialog.text = "Oh, il n'y a rien à décider. Nous pouvons tout décider nous-mêmes. Mais nous prendrons ton navire et nous sortirons d'ici.";
			link.l1 = "Il y a une condition, d'abord tu devras me prendre ma lame...";
			link.l1.go = "PiratesOnUninhabited_2";
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		
		case "PiratesOnUninhabited_2":
			for(i = 0; i < sti(PChar.GenQuest.PiratesOnUninhabited.PiratesQty); i++)
			{
				LAi_SetImmortal(CharacterFromID("PirateOnUninhabited_" + i), false);
			}
			
			LAi_Group_SetRelation("PiratesOnUninhabitedGroup", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_Group_FightGroups("PiratesOnUninhabitedGroup", LAI_GROUP_PLAYER, true);
			DialogExit();
		break;
		
		case "PiratesOnUninhabited_3":
			PChar.GenQuest.PiratesOnUninhabited.MainPirateName = GetRandName(NAMETYPE_NICK, NAME_GEN);
			PChar.GenQuest.PiratesOnUninhabited.BadPirateName = GetRandName(NAMETYPE_ORIG, NAME_NOM);
			
				i = PiratesOnUninhabited_GenerateShipType();
				PChar.GenQuest.PiratesOnUninhabited.StartShipType = i;
			
			if(hrand(1) == 0)
			{
				PChar.GenQuest.PiratesOnUninhabited.Shipwrecked = true;
				
				dialog.text = "Bonjour, capitaine ! Apparemment, la Providence elle-même vous a envoyé pour sauver "+PChar.GenQuest.PiratesOnUninhabited.MainPirateName+" et ses garçons. Nous sommes dans le besoin ici."+"Notre "+GetStrSmallRegister(XI_ConvertString(ShipsTypes[i].Name))+" s'est échoué dans la tempête sur les récifs locaux, et les vagues ont rejeté sur le rivage les survivants de l'équipage."+"Pour "+(5+hrand(7))+"des semaines entières nous scrutions l'horizon, espérant voir la voile d'un navire qui viendrait nous secourir.";
				link.l1 = RandPhraseSimple(RandPhraseSimple("Oui, c'est un sort peu enviable. Mais tel est le destin de la vie de marin, n'importe qui pourrait se retrouver à ta place.","Je vois... Dieu tient chaque vie, c'est juste qu'il est trop occupé pour se souvenir de tout le monde."),RandPhraseSimple("En effet. L'homme propose, mais Dieu dispose.","Oui, c'était sûrement un coup de malchance."));
				link.l1.go = "PiratesOnUninhabited_4";
			}
			else
			{
				dialog.text = "C'était très sérieux ! Ce vaurien "+PChar.GenQuest.PiratesOnUninhabited.BadPirateName+"ne pouvait penser à une punition autre que partir"+ChangeNameCase(NAMETYPE_NICK,PChar.GenQuest.PiratesOnUninhabited.MainPirateName,NAME_ACC)+" sur une île déserte, comme un chien galeux ! "+"Il espérait que le soleil et la soif nous dessécheraient comme un maquereau séché sur l'étal d'un pêcheur ! Mais il avait tort, car la Providence elle-même était de notre côté, puisqu'Elle t'a envoyé ici pour nous secourir...";
				link.l1 = RandPhraseSimple("Pas si vite, l'ami. Autant que je puisse dire, vous êtes des hommes d'une profession libre, et vous vous êtes retrouvés ici pas par hasard.","Déjà en train de parler de salut ? Si je comprends bien, tu es ici à cause de quelques exploits particuliers.");
				link.l1.go = "PiratesOnUninhabited_41";
			}
		break;
		
		case "PiratesOnUninhabited_4":
			PChar.GenQuest.PiratesOnUninhabited.PiratesCount = 5 + hrand(5);
			
			dialog.text = RandPhraseSimple("Capitaine, je vous en prie, soyez une âme charitable et aidez "+PiratesOnUninhabited_GetStringNum(sti(PChar.GenQuest.PiratesOnUninhabited.PiratesCount))+"hommes sans le sou. Vous êtes notre seul espoir, sauf notre très gracieux Seigneur.","Capitaine, auriez-vous des coffres libres sur votre navire pour "+PiratesOnUninhabited_GetStringNum(sti(PChar.GenQuest.PiratesOnUninhabited.PiratesCount))+"hommes indigents ?");
			
			if(GetFreeCrewQuantity(PChar) >= sti(PChar.GenQuest.PiratesOnUninhabited.PiratesCount) && GetPassengersQuantity(PChar) < PASSENGERS_MAX)
			{
				link.l1 = "Ohh... et où veux-tu que je t'emmène?";
				link.l1.go = "PiratesOnUninhabited_5";
			}
			
			link.l2 = RandPhraseSimple(RandPhraseSimple("Je suis vraiment désolé, mais il n'y a même pas un seul hamac libre, sans parler des cabines. Les marins dorment sur le pont, ils ne peuvent même pas prendre un bon repos nocturne après une veille...","Je détesterais vraiment te décevoir, mais le navire est surchargé, et les gens doivent dormir par mauvais temps. Si une épidémie éclate, je perdrai la moitié de l'équipage."),RandPhraseSimple("Je suis vraiment désolé, mais il n'y a absolument pas de place libre pour l'équipage sur mon navire. Je ne peux pas embarquer d'autres passagers.","Je dois te décevoir, mais mon navire est surchargé d'équipage. Je crains l'épidémie..."));
			link.l2.go = "PiratesOnUninhabited_21";
			
			if(stf(PChar.reputation.nobility) <= REPUTATION_NEUTRAL)
			{
				link.l3 = "Vous êtes un marin aguerri et vous devriez savoir que la présence de quelqu'un qui a subi un naufrage est un très mauvais présage. Mes marins vont simplement vous jeter tous par-dessus bord.";
				link.l3.go = "PiratesOnUninhabited_7";
			}
		break;
		
		case "PiratesOnUninhabited_5":
			dialog.text = "Hmm... Vous savez, pour plusieurs raisons nous préférerions rester aussi loin que possible des autorités... Je vous prie, déposez-nous dans une crique sur une île habitée ou sur la côte, et nous saurons nous débrouiller.";
			link.l1 = "Eh bien, j'ai assez de coffres et de hamacs libres. Monte à bord.";
			link.l1.go = "PiratesOnUninhabited_10";
			link.l2 = "Hmm... malchance... Nous avons des batailles à venir, et je ne sais pas où tu seras plus en sécurité, à bord de mon navire ou dans cette crique douillette.";
			link.l2.go = "PiratesOnUninhabited_6";
		break;
		
		case "PiratesOnUninhabited_6":
			dialog.text = "Ah, capitaine ! Ce sont des temps où l'on ne peut se sentir en sécurité même dans un lit avec sa femme ha-ha, encore moins en mer... Regardez ces vauriens, chacun d'eux est prêt à se battre à mains nues contre des canons. Ils ne recherchent ni la sécurité ni le confort, cela se lit sur leurs visages !";
			link.l1 = "Sur leurs visages, je ne lis que la volonté de poignarder leur imbécile de bienfaiteur dans le dos.";
			link.l1.go = "PiratesOnUninhabited_7";
			link.l2 = "Hmm... Cela, en fait, est une bonne idée. Dis-moi ami, tes voyous sont-ils prêts à servir dans mon équipage ?";
			link.l2.go = "PiratesOnUninhabited_8";
		break;
		
		case "PiratesOnUninhabited_7":
			dialog.text = "Quel dommage, capitaine... Je vois que nous ne pouvons pas régler ça amicalement. Je suppose que je vais devoir te rappeler le code de la mer. Et garde à l'esprit que, lorsqu'il s'agit d'un abordage, nous n'avons pas notre pareil...";
			link.l1 = "Eh bien, maintenant je peux enfin te voir tel que tu es vraiment...";
			link.l1.go = "PiratesOnUninhabited_2";
			AddDialogExitQuest("MainHeroFightModeOn");
			ChangeCharacterComplexReputation(pchar,"nobility", -3.0);
		break;
		
		// Берем их в команду
		case "PiratesOnUninhabited_8":
			dialog.text = "Mais bien sûr ! Ils seraient ravis de rejoindre votre équipe d'abordage ! Personne ne les surpassera dans un combat, sauf peut-être Davy Jones lui-même ! Ha-ha-ha !";
			link.l1 = "Très bien, alors. Montez dans les barques...";
			link.l1.go = "PiratesOnUninhabited_9";
		break;
		
		case "PiratesOnUninhabited_9":
			bTemp = CheckAttribute(PChar, "GenQuest.PiratesOnUninhabited.Shipwrecked");
			
			for(i = 0; i < sti(PChar.GenQuest.PiratesOnUninhabited.PiratesQty); i++)
			{
				rChar = CharacterFromID("PirateOnUninhabited_" + i);
				LAi_SetWarriorTypeNoGroup(rChar);
				rChar.LifeDay = 0;
				
				if(bTemp)
				{
					rChar.Dialog.currentnode = "PiratesOnUninhabited_11_Again";
				}
				else
				{
					rChar.Dialog.currentnode = "PiratesOnUninhabited_43_again";
				}
			}
			
			AddCharacterCrew(PChar, sti(PChar.GenQuest.PiratesOnUninhabited.PiratesCount));
			
			Log_Info("Your crew was increased by " + PChar.GenQuest.PiratesOnUninhabited.PiratesCount + " men.");
			OfficersReaction("bad");
			
			//PChar.Quest.PiratesOnUninhabited_LocExit.over = "yes"; // Снимаем прерывание на выход из локации
			
			//DeleteAttribute(PChar, "GenQuest.PiratesOnUninhabited");
			
			DialogExit();
			
			// Конец квеста
		break;
		
		case "PiratesOnUninhabited_10":
			dialog.text = "Merci, capitaine ! Le chargement ne devrait pas prendre trop de temps. Mon Dieu, comme nous avions prié pour que ce moment arrive !";
			link.l1 = "Très bien, alors.";
			link.l1.go = "PiratesOnUninhabited_11";
		break;
		
		// Берем их в пассажирами - держать курс на населенный остров
		case "PiratesOnUninhabited_11":
			for(i = 0; i < sti(PChar.GenQuest.PiratesOnUninhabited.PiratesQty); i++)
			{
				rChar = CharacterFromID("PirateOnUninhabited_" + i);
				LAi_SetWarriorTypeNoGroup(rChar);
				rChar.Dialog.currentnode = "PiratesOnUninhabited_11_Again";
			}
			
			Log_Info("Your crew was increased by " + PChar.GenQuest.PiratesOnUninhabited.PiratesCount + " men.");
			
			ChangeCharacterComplexReputation(pchar,"nobility", 3.0);
			
			AddCharacterCrew(PChar, sti(PChar.GenQuest.PiratesOnUninhabited.PiratesCount) - 1);
			OfficersReaction("good");
			PChar.Quest.PiratesOnUninhabited_LocExit.over = "yes"; // Снимаем прерывание на выход из локации
			
			AddPassenger(PChar, NPChar, false); // Главного в пассажиры
			SetCharacterRemovable(NPChar, false);
			
			sTemp = XI_ConvertString(PChar.location + "Gen"); // belamour gen
			
			sTitle = "PiratesOnUninhabited" + PChar.location;
			ReOpenQuestHeader(sTitle);
			
			if(!CheckAttribute(PChar, "GenQuest.PiratesOnUninhabited.TreasureMap"))
			{
				if(CheckAttribute(PChar, "GenQuest.PiratesOnUninhabited.Shipwrecked"))
				{
					AddQuestRecordEx(sTitle, "PiratesOnUninhabited", "1");
					AddQuestUserData(sTitle, "shipTypeName", GetStrSmallRegister(XI_ConvertString(ShipsTypes[sti(PChar.GenQuest.PiratesOnUninhabited.StartShipType)].name + "Gen"))); // belamour gen
					// --> belamour gen: нужно разделить, иначе получается с потерпевшего крушение бригантины 
					if(ShipsTypes[sti(PChar.GenQuest.PiratesOnUninhabited.StartShipType)].name == "SHIP_BRIGANTINE" || ShipsTypes[sti(PChar.GenQuest.PiratesOnUninhabited.StartShipType)].name == "SHIP_SCHOONER_W")
					{
						AddQuestUserData(sTitle, "sText", "wrecked pirate");
					}
					else
					{
						AddQuestUserData(sTitle, "sText", "wrecked pirate");
					}
					// <-- belamour gen
				}
				else
				{
					AddQuestRecordEx(sTitle, "PiratesOnUninhabited", "11");
					AddQuestUserData(sTitle, "pirateName", ChangeNameCase(NAMETYPE_ORIG, PChar.GenQuest.PiratesOnUninhabited.BadPirateName, NAME_ABL));
				}
			}
			else
			{
				AddQuestRecordEx(sTitle, "PiratesOnUninhabited", "5");
				AddQuestUserData(sTitle, "shipTypeName", GetStrSmallRegister(XI_ConvertString(ShipsTypes[sti(PChar.GenQuest.PiratesOnUninhabited.StartShipType)].name + "Gen"))); // belamour gen
				// --> belamour gen: нужно разделить, иначе получается с потерпевшего крушение бригантины 
				if(ShipsTypes[sti(PChar.GenQuest.PiratesOnUninhabited.StartShipType)].name == "SHIP_BRIGANTINE" || ShipsTypes[sti(PChar.GenQuest.PiratesOnUninhabited.StartShipType)].name == "SHIP_SCHOONER_W")
				{
					AddQuestUserData(sTitle, "sText", "wrecked pirate");
				}
				else
				{
					AddQuestUserData(sTitle, "sText", "wrecked pirate");
				}
				// <-- belamour gen
			}
			
			AddQuestUserDataForTitle(sTitle, "shoreName", sTemp);
			AddQuestUserData(sTitle, "shoreName", sTemp);
			AddQuestUserData(sTitle, "count", PChar.GenQuest.PiratesOnUninhabited.PiratesCount + " sailors"); // belamour gen
			
			PChar.GenQuest.PiratesOnUninhabited.StartShore = PChar.location;
			
			PChar.Quest.PiratesOnUninhabited_LocExitGood.win_condition.l1 = "ExitFromLocation";
			PChar.Quest.PiratesOnUninhabited_LocExitGood.win_condition.l1.location = PChar.location;
			PChar.Quest.PiratesOnUninhabited_LocExitGood.function = "PiratesOnUninhabited_LocationExit_Good";
			
			PChar.Quest.PiratesOnUninhabited_OnShore.win_condition.l1 = "Location_Type";
			PChar.Quest.PiratesOnUninhabited_OnShore.win_condition.l1.location_type = "seashore";
			PChar.Quest.PiratesOnUninhabited_OnShore.again = true;
			PChar.Quest.PiratesOnUninhabited_OnShore.function = "PiratesOnUninhabited_OnShore";
			
			PChar.Quest.PiratesOnUninhabited_OnMayak.win_condition.l1 = "Location_Type";
			PChar.Quest.PiratesOnUninhabited_OnMayak.win_condition.l1.location_type = "mayak";
			PChar.Quest.PiratesOnUninhabited_OnMayak.again = true;
			PChar.Quest.PiratesOnUninhabited_OnMayak.function = "PiratesOnUninhabited_OnShore";
			
			DialogExit();
		break;
		
		case "PiratesOnUninhabited_11_Again":
			dialog.text = LinkRandPhrase("Pourquoi traînes-tu, capitaine ? Ordonne de lever l'ancre.","Nous sommes désolés, capitaine, mais nous devons nous préparer à mettre les voiles.","Nous avons tellement de chance que vous ayez décidé de venir ici !");
			link.l1 = "Dépêche-toi. Le navire n'attendra personne.";
			link.l1.go = "exit";
			NextDiag.TempNode = "PiratesOnUninhabited_11_Again";
		break;
		
		// Базар с главарем уже в другой бухте на обитаемом острове
		case "PiratesOnUninhabited_12":
			if(hrand(1) == 0)
			{
				// Успешное завершение квеста - даст награду
				dialog.text = "Merci, capitaine. En effet, nous avons bien fait de croire en notre chance... S'il vous plaît, acceptez ce joyau, je l'ai trouvé dans cette crique funeste. J'espère qu'il vous portera chance.";
				link.l1 = "Je ne m'attendais pas à un tel cadeau.";
				link.l1.go = "PiratesOnUninhabited_13";
			}
			else
			{
				// Требуют денег
				dialog.text = "Capitaine, s'il vous plaît, ne pensez pas que nous sommes trop impudents, mais nous manquons vraiment d'argent. Vous savez, nous avons tout perdu. Pourriez-vous nous prêter quelques poignées de pesos ? Nous vous rembourserons à coup sûr... quand l'occasion se présentera...";
				link.l1 = "Eh bien ! En effet, l'insolence n'a pas de limites. Eh bien, la seule chose que je pourrais faire pour vous maintenant, après tout ce que j'ai déjà fait, serait de ne pas informer les autorités à votre sujet.";
				link.l1.go = "PiratesOnUninhabited_15";
				link.l2 = "Tu ne dis pas... Et combien veux-tu?";
				link.l2.go = "PiratesOnUninhabited_17";
			}
			
			RemovePassenger(PChar, NPChar);
			RemoveCharacterCrew(PChar, sti(PChar.GenQuest.PiratesOnUninhabited.PiratesCount) - 1);
		break;
		
		case "PiratesOnUninhabited_13":
			AddItems(PChar, "jewelry4", 1);
			
			for(i = 0; i < sti(PChar.GenQuest.PiratesOnUninhabited.PiratesQty); i++)
			{
				rChar = CharacterFromID("PirateOnUninhabited_" + i);
				LAi_SetWarriorTypeNoGroup(rChar);
				LAi_SetImmortal(rChar, false);
				rChar.LifeDay = 0;
				
				rChar.Dialog.currentnode = "PiratesOnUninhabited_14";
			}
			
			sTitle = "PiratesOnUninhabited" + PChar.GenQuest.PiratesOnUninhabited.StartShore;
			AddQuestRecordEx(sTitle, "PiratesOnUninhabited", "2");
			AddQuestUserData(sTitle, "sSex", GetSexPhrase("",""));
			AddQuestUserData(sTitle, "toShore", LowerFirst(XI_ConvertString(PChar.location + "Gen"))); // belamour gen
			CloseQuestHeader(sTitle);
			
			DeleteAttribute(PChar, "GenQuest.PiratesOnUninhabited");
			
			DialogExit();
			
			// Конец квеста
		break;
		
		case "PiratesOnUninhabited_14":
			dialog.text = LinkRandPhrase("Merci, capitaine.","Capitaine, nous vous sommes tellement reconnaissants.","Nous prierons pour toi, capitaine "+PChar.name+" !");
			link.l1 = "Bonne chance à vous. Adieu...";
			link.l1.go = "exit";
			NextDiag.TempNode = "PiratesOnUninhabited_14";
		break;
		
		case "PiratesOnUninhabited_15":
			dialog.text = "Heh, capitaine... Tu sais, on s'entendait bien... Ce serait vraiment dommage de te tuer...";
			link.l1 = "Vous pouvez essayer !";
			link.l1.go = "PiratesOnUninhabited_16";
			AddDialogExitQuest("MainHeroFightModeOn");
			ChangeCharacterComplexReputation(pchar,"nobility", 2.0);
		break;
		
		case "PiratesOnUninhabited_16":
			for(i = 0; i < sti(PChar.GenQuest.PiratesOnUninhabited.PiratesQty); i++)
			{
				rChar = CharacterFromID("PirateOnUninhabited_" + i);
				
				LAi_SetImmortal(rChar, false);
				rChar.LifeDay = 0;
			}
			
			LAi_Group_SetRelation("PiratesOnUninhabitedGroup", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_Group_FightGroups("PiratesOnUninhabitedGroup", LAI_GROUP_PLAYER, true);
			
			sTitle = "PiratesOnUninhabited" + PChar.GenQuest.PiratesOnUninhabited.StartShore;
			AddQuestRecordEx(sTitle, "PiratesOnUninhabited", "3");
			AddQuestUserData(sTitle, "sSex", GetSexPhrase("",""));
			AddQuestUserData(sTitle, "toShore", LowerFirst(XI_ConvertString(PChar.location + "Gen"))); // belamour gen
			CloseQuestHeader(sTitle);
			
			DeleteAttribute(PChar, "GenQuest.PiratesOnUninhabited");
			
			DialogExit();
			
			// Конец квеста
		break;
		
		case "PiratesOnUninhabited_17":
			iMoney = sti(PChar.rank) * 500;
			PChar.GenQuest.PiratesOnUninhabited.Money = iMoney * sti(PChar.GenQuest.PiratesOnUninhabited.PiratesCount);
			
			dialog.text = "Eh bien, dis, "+iMoney+" pesos pour chacun de nous ferait l'affaire... Bien sûr, si tu ne penses pas que cette compensation pour toute notre douleur et souffrance est trop petite, hé-hé...";
			link.l1 = RandPhraseSimple("Au contraire, je suis certain que c'est bien trop... Une corde autour du cou pour chacun d'entre vous serait le mieux.","Je te pendrai comme des singes aux palmiers pour cet argent moi-même !");
			link.l1.go = "PiratesOnUninhabited_18";
			
			if(sti(PChar.money) >= iMoney * sti(PChar.GenQuest.PiratesOnUninhabited.PiratesCount))
			{
				link.l2 = "D'accord, prends-le. J'espère que je ne te dois rien d'autre ?";
				link.l2.go = "PiratesOnUninhabited_19";
			}
		break;
		
		case "PiratesOnUninhabited_18":
			dialog.text = "Quelle générosité ! Franchement, je pensais que tu avais déjà eu l'occasion de voir que nous obtenons toujours ce que nous désirons. Et cette fois, nous n'allons pas reculer non plus...";
			link.l1 = "Vous pouvez essayer !";
			link.l1.go = "PiratesOnUninhabited_16";
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		
		case "PiratesOnUninhabited_19":
			dialog.text = "Oh non, capitaine, que dites-vous ?! Nous allumerons certainement une bougie en votre nom, si jamais nous entrons dans une église... hah !";
			link.l1 = "J'espère bien...";
			link.l1.go = "PiratesOnUninhabited_20";
			
			iMoney = sti(PChar.GenQuest.PiratesOnUninhabited.Money);
			
			AddMoneyToCharacter(PChar, -iMoney);
			AddMoneyToCharacter(NPChar, iMoney);
		break;
		
		case "PiratesOnUninhabited_20":
			for(i = 0; i < sti(PChar.GenQuest.PiratesOnUninhabited.PiratesQty); i++)
			{
				rChar = CharacterFromID("PirateOnUninhabited_" + i);
				
				LAi_SetWarriorTypeNoGroup(rChar);
				LAi_CharacterDisableDialog(rChar);
				LAi_SetImmortal(rChar, false);
				rChar.LifeDay = 0;
			}
			
			ChangeCharacterComplexReputation(pchar,"nobility", 2.0);
			OfficersReaction("good");
			
			sTitle = "PiratesOnUninhabited" + PChar.GenQuest.PiratesOnUninhabited.StartShore;
			AddQuestRecordEx(sTitle, "PiratesOnUninhabited", "4");
			AddQuestUserData(sTitle, "sSex", GetSexPhrase("",""));
			AddQuestUserData(sTitle, "sSex1", GetSexPhrase("",""));
			AddQuestUserData(sTitle, "toShore", LowerFirst(XI_ConvertString(PChar.location + "Acc")));
			CloseQuestHeader(sTitle);
			
			NPChar.SaveItemsForDead = true; // сохранять на трупе вещи
			NPChar.DontClearDead = true;  // не убирать труп через 200с
			
			DeleteAttribute(PChar, "GenQuest.PiratesOnUninhabited");
			
			DialogExit();
			
			// Конец квеста
		break;
		
		case "PiratesOnUninhabited_21":
			if(GetFreeCrewQuantity(PChar) >= sti(PChar.GenQuest.PiratesOnUninhabited.PiratesCount))
			{
				// Игрок врет - свободное место есть
				dialog.text = "Oh non, capitaine, qu'est-ce que vous racontez ?! Nous allumerons certainement une bougie en votre nom, si jamais nous entrons dans une église... ha!";
				link.l1 = "J'espère bien...";
				link.l1.go = "PiratesOnUninhabited_23";
			}
			else
			{
				dialog.text = "Heh, capitaine, tu sais, ce n'est pas vraiment un problème. Moi et mes garçons sommes prêts à libérer une douzaine de hamacs sur ton navire de ceux qui les occupent actuellement...";
				link.l1 = "Hmm... cela ressemble à une menace...";
				link.l1.go = "PiratesOnUninhabited_22";
			}
		break;
		
		case "PiratesOnUninhabited_22":
			dialog.text = "Eh bien, en fait, c'est une menace. J'ai besoin de ton navire, et je quitterai cet endroit, avec ou sans ton consentement !";
			link.l1 = "Eh bien, maintenant je peux enfin te voir pour ce que tu es vraiment...";
			link.l1.go = "PiratesOnUninhabited_2";
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		
		case "PiratesOnUninhabited_23":
			dialog.text = "Je vous comprends, capitaine. Je vous comprends parfaitement... Qui voudrait s'occuper de pauvres pirates qui n'ont que mérité la corde?.. Mais... que diriez-vous d'un échange? Vous nous déposez dans une crique d'une île habitée ou sur le continent, et je vous donne une carte au trésor en échange. Marché conclu?";
			link.l1 = "Hmm... Et comment peux-tu garantir que cette carte n'est pas un faux ?";
			link.l1.go = "PiratesOnUninhabited_25";
			link.l2 = "Ha, je suis sûr que ta carte vaut autant que le morceau de papier sur lequel elle a été dessinée...";
			link.l2.go = "PiratesOnUninhabited_24";
		break;
		
		case "PiratesOnUninhabited_24":
			dialog.text = "Eh bien... Tu ne nous laisses pas le choix... Cependant, nous allons sortir de cet endroit, avec ou sans ton consentement !";
			link.l1 = "Eh bien, maintenant je peux enfin te voir tel que tu es vraiment...";
			link.l1.go = "PiratesOnUninhabited_2";
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		
		case "PiratesOnUninhabited_25":
			dialog.text = "Et comment peux-tu garantir que tu ne nous dénonceras pas aux autorités dans le port le plus proche ? Nous jouons tous deux sans voir les cartes de l'autre...";
			link.l1 = "D'accord, tu as un marché.";
			link.l1.go = "PiratesOnUninhabited_11";
			PChar.GenQuest.PiratesOnUninhabited.TreasureMap = true;
		break;
		
		// Базар с главарем уже в другой бухте на обитаемом острове. Вариант, когда нам обещали карту сокровищ
		case "PiratesOnUninhabited_26":
			// PChar.GenQuest.PiratesOnUninhabited.MainPirateName - имя в родительном падеже
			
			dialog.text = "Merci, capitaine "+PChar.name+". Tu as accompli"+GetSexPhrase("","")+" ta promesse, il est temps "+ChangeNameCase(NAMETYPE_NICK,PChar.GenQuest.PiratesOnUninhabited.MainPirateName,NAME_DAT)+" pour accomplir le mien. Je n'ai pas la carte avec moi, mais je vais te dire où se trouve le trésor. Va à la crique...";
			link.l1 = "Ah, alors c'est ainsi que tu présentes les choses maintenant ! Je vois que tu comptais me duper dès le début...";
			link.l1.go = "PiratesOnUninhabited_27";
			link.l2 = "J'ai su tout de suite qu'on ne pouvait pas te faire confiance...";
			link.l2.go = "PiratesOnUninhabited_30";
			link.l3 = "C'est ce qui arrive quand on fait confiance à un pirate. Quelle sorte de gens êtes-vous ? Rien n'est sacré pour vous !";
			link.l3.go = "PiratesOnUninhabited_33";
			
			RemovePassenger(PChar, NPChar);
			RemoveCharacterCrew(PChar, sti(PChar.GenQuest.PiratesOnUninhabited.PiratesCount) - 1);
		break;
		
		case "PiratesOnUninhabited_27":
			dialog.text = "Ne fais pas d'histoires... Je ne suis pas un saint, mais je tiens parole !";
			link.l1 = "Et tu t'attends à ce que je te croie encore une fois ? Pour que demain tout l'archipel se moque de moi ?";
			link.l1.go = "PiratesOnUninhabited_28";
		break;
		
		case "PiratesOnUninhabited_28":
			dialog.text = "Hmm... Apparemment, il n'y aura pas de résolution pacifique. Mais, Dieu sait, je ne le voulais pas...";
			link.l1 = "Dégaine ton épée, ou je t'écraserai comme le rat que tu es !";
			link.l1.go = "PiratesOnUninhabited_29";
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		
		case "PiratesOnUninhabited_29":
			for(i = 0; i < sti(PChar.GenQuest.PiratesOnUninhabited.PiratesQty); i++)
			{
				rChar = CharacterFromID("PirateOnUninhabited_" + i);
				
				LAi_SetImmortal(rChar, false);
				rChar.LifeDay = 0;
			}
			
			LAi_Group_SetRelation("PiratesOnUninhabitedGroup", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_Group_FightGroups("PiratesOnUninhabitedGroup", LAI_GROUP_PLAYER, true);
			
			sTitle = "PiratesOnUninhabited" + PChar.GenQuest.PiratesOnUninhabited.StartShore;
			AddQuestRecordEx(sTitle, "PiratesOnUninhabited", "6");
			CloseQuestHeader(sTitle);
			
			DeleteAttribute(PChar, "GenQuest.PiratesOnUninhabited");
			
			DialogExit();
			
			// Конец квеста
		break;
		
		case "PiratesOnUninhabited_30":
			sTitle = PiratesOnUninhabited_GenerateTreasureShore(&sTemp);
			PChar.GenQuest.PiratesOnUninhabited.TreasureShore = sTitle;
			PChar.GenQuest.PiratesOnUninhabited.TreasureBox = sTemp;
			
			dialog.text = "Et qu'aurais-je pu faire d'autre? Rester dans cette mare puante avec mes gars et pourrir jusqu'à la mort? Tu ferais mieux de m'écouter..."+XI_ConvertString(sTitle+"Gen")+" capitaine "+ChangeNameCase(NAMETYPE_ORIG,PChar.GenQuest.PiratesOnUninhabited.BadPirateName,NAME_GEN)+" il y a une cachette où il garde son butin. Mais fais attention"+GetSexPhrase("","")+", il s'y rend fréquemment. Trouver la cachette ne sera pas difficile, si vous gardez la tête froide..."; // belamour gen
			link.l1 = "Et tu t'attends à ce que je te croie encore une fois ? Pour que demain tout l'archipel se moque de moi ?";
			link.l1.go = "PiratesOnUninhabited_28";
			link.l2 = "D'accord. Mais si tu me joues encore un tour, je te trouverai.";
			link.l2.go = "PiratesOnUninhabited_31";
		break;
		
		case "PiratesOnUninhabited_31":
			for(i = 0; i < sti(PChar.GenQuest.PiratesOnUninhabited.PiratesQty); i++)
			{
				rChar = CharacterFromID("PirateOnUninhabited_" + i);
				
				LAi_SetWarriorTypeNoGroup(rChar);
				LAi_SetImmortal(rChar, false);
				rChar.LifeDay = 0;
				rChar.Dialog.currentnode = "PiratesOnUninhabited_32";
			}
			
			sTitle = "PiratesOnUninhabited" + PChar.GenQuest.PiratesOnUninhabited.StartShore;
			AddQuestRecordEx(sTitle, "PiratesOnUninhabited", "7");
			AddQuestUserData(sTitle, "capName", ChangeNameCase(NAMETYPE_ORIG, PChar.GenQuest.PiratesOnUninhabited.BadPirateName, NAME_NOM));
			AddQuestUserData(sTitle, "toShore", LowerFirst(XI_ConvertString(PChar.GenQuest.PiratesOnUninhabited.TreasureShore + "Gen"))); // belamour gen
			
			// Таймер для клада. По прошествии 10 дней в кладе будут всякие бакланы и т.д.
			PChar.Quest.PiratesOnUninhabited_TreasureLose.win_condition.l1 = "Timer";
			PChar.Quest.PiratesOnUninhabited_TreasureLose.win_condition.l1.date.day = GetAddingDataDay(0, 0, 10);
			PChar.Quest.PiratesOnUninhabited_TreasureLose.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 10);
			PChar.Quest.PiratesOnUninhabited_TreasureLose.win_condition.l1.date.year = GetAddingDataYear(0, 0, 10);
			PChar.Quest.PiratesOnUninhabited_TreasureLose.function = "PiratesOnUninhabited_TreasureLose"; // belamour gen
			
			PChar.Quest.PiratesOnUninhabited_InTreasureLoc.win_condition.l1 = "Location";
			PChar.Quest.PiratesOnUninhabited_InTreasureLoc.win_condition.l1.Location = PChar.GenQuest.PiratesOnUninhabited.TreasureShore;
			PChar.Quest.PiratesOnUninhabited_InTreasureLoc.function = "PiratesOnUninhabited_InTreasureLoc";
			
			DialogExit();
			
			// Курс в бухту, которую назвал пират. У нас сроку 10 дней, котом клад пропадёт
		break;
		
		case "PiratesOnUninhabited_32":
			sTemp = ChangeNameCase(NAMETYPE_NICK, PChar.GenQuest.PiratesOnUninhabited.MainPirateName, NAME_ACC);
			
			dialog.text = LinkRandPhrase("Ecoute "+sTemp+", il parle avec raison.","Ne sois pas en colère contre "+sTemp+", il n'avait tout simplement pas d'autre choix.","Merci, capitaine.");
			link.l1 = "Bonne chance à vous...";
			link.l1.go = "exit";
			NextDiag.TempNode = "PiratesOnUninhabited_32";
		break;
		
		case "PiratesOnUninhabited_33":
			sTitle = PiratesOnUninhabited_GenerateTreasureShore(&sTemp);
			PChar.GenQuest.PiratesOnUninhabited.TreasureShore = sTitle;
			PChar.GenQuest.PiratesOnUninhabited.TreasureBox = sTemp;
			
			dialog.text = "Et qu'aurais-je pu faire d'autre ? Rester dans ce bourbier puant avec mes gars et pourrir jusqu'à la mort ? Tu ferais mieux de m'écouter..."+XI_ConvertString(sTitle+"Gen")+" capitaine "+ChangeNameCase(NAMETYPE_ORIG,PChar.GenQuest.PiratesOnUninhabited.BadPirateName,NAME_GEN)+" il y a une cachette où il garde son butin. Mais fais attention, il y va fréquemment. Trouver la cachette ne sera pas difficile, si tu gardes ton esprit alerte..."; // belamour gen
			link.l1 = "Et tu t'attends à ce que je te croie encore une fois ? Pour que demain tout l'archipel se moque de moi ?";
			link.l1.go = "PiratesOnUninhabited_28";
		break;
		
		// Пираты в бухте с сокровищем
		case "PiratesOnUninhabited_34":
			dialog.text = "Qui es-tu,"+GetSexPhrase(" compagnon","lascive")+"? Et qu'est-ce qui t'a amené en ce lieu désert ?";
			link.l1 = "Je me suis arrêté pour refaire le plein d'eau douce.";
			link.l1.go = "PiratesOnUninhabited_35";
			link.l2 = "Je suis ici au nom de "+ChangeNameCase(NAMETYPE_NICK,PChar.GenQuest.PiratesOnUninhabited.MainPirateName,NAME_GEN)+".";
			link.l2.go = "PiratesOnUninhabited_38";
			NextDiag.TempNode = "PiratesOnUninhabited_34";
		break;
		
		case "PiratesOnUninhabited_35":
			dialog.text = "Tu as choisi un mauvais endroit pour ça... Bien, prends ton temps.";
			link.l1 = "Ah-ha...";
			link.l1.go = "exit";
			link.l2 = "Et qui es-tu pour me dire ce que je dois faire ?";
			link.l2.go = "PiratesOnUninhabited_36";
		break;
		
		case "PiratesOnUninhabited_36":
			dialog.text = "Je dis à tout le monde quoi faire. Et ceux qui se croient trop malins se balanceront au palmier.";
			link.l1 = "Je te couperai la langue, chien.";
			link.l1.go = "PiratesOnUninhabited_37";
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		
		case "PiratesOnUninhabited_37":
			DialogExit();
			LAi_Group_SetRelation("PiratesOnUninhabited_ShoreGroup", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
		break;
		
		case "PiratesOnUninhabited_38":
			dialog.text = "Et pourquoi n'est-il pas venu lui-même ?";
			link.l1 = "Il ne voulait pas, est resté à "+LowerFirst(XI_ConvertString(PChar.GenQuest.PiratesOnUninhabited.StartShore+"Gen"))+" et m'attendant."; // belamour gen
			link.l1.go = "PiratesOnUninhabited_39";
		break;
		
		case "PiratesOnUninhabited_39":
			dialog.text = "Ce vieux vaurien ! Il essaie encore de nous rouler, n'est-ce pas ? Cela ne marchera pas. Dis-lui qu'il peut récupérer l'argent seulement avec nous !";
			link.l1 = "Il m'a dit de ne pas revenir sans argent et de ne prendre personne à bord...";
			link.l1.go = "PiratesOnUninhabited_40";
		break;
		
		case "PiratesOnUninhabited_40":
			dialog.text = "Eh bien, si tu lui fais tellement confiance, tu peux rester ici. Mais nous prendrons ton navire, ton argent et mettrons le cap sur "+LowerFirst(XI_ConvertString(PChar.GenQuest.PiratesOnUninhabited.StartShore+"Gen"))+". Nous sommes impatients de voir la tête de "+PChar.GenQuest.PiratesOnUninhabited.MainPirateName+"."; // belamour gen
			link.l1 = "Si tu l'aimes tant, tu peux nager jusqu'à lui... ou tu peux crever ici.";
			link.l1.go = "PiratesOnUninhabited_37";
			AddDialogExitQuest("MainHeroFightModeOn");
			PChar.GenQuest.PiratesOnUninhabited.UseMainPiratename = true;
		break;
		
		// Ветка из PiratesOnUninhabited_3
		case "PiratesOnUninhabited_41":
			iBanditsCount = 5 + hrand(5);
			iMoney = GetFreeCrewQuantity(PChar);
			
			PChar.GenQuest.PiratesOnUninhabited.PiratesCount = iBanditsCount;
			
			dialog.text = "Vous êtes une personne rusée. Mais permettez-moi de vous assurer que notre conflit avec le capitaine "+ChangeNameCase(NAMETYPE_ORIG,PChar.GenQuest.PiratesOnUninhabited.BadPirateName,NAME_ABL)+" est purement d'ordre idéologique. Je l'ai averti que ses opérations douteuses seraient un jour punies et maintenant moi et mon "+iBanditsCount+" les copains souffrent à cause de notre amour pour Dieu et la justice.";
			link.l1 = "Comment cela... Je parie que vous étiez les véritables instigateurs de la mutinerie, et vous avez eu ce que vous méritiez.";
			link.l1.go = "PiratesOnUninhabited_42";
			
			if(iMoney >= iBanditsCount - 1 && GetPassengersQuantity(PChar) < PASSENGERS_MAX)
			{
				link.l2 = "Bien sûr... Ce serait bien d'entendre l'opinion du capitaine "+ChangeNameCase(NAMETYPE_ORIG,PChar.GenQuest.PiratesOnUninhabited.BadPirateName,NAME_GEN)+"lui-même concernant vos désaccords.";
				link.l2.go = "PiratesOnUninhabited_44";
			}
		break;
		
		case "PiratesOnUninhabited_42":
			dialog.text = "Capitaine, pourquoi offenseriez-vous des gens honnêtes avec votre méfiance ? Regardez simplement leurs visages... pensez-vous vraiment qu'ils sont des mutins ? Ils sont aussi humbles que possible... Mais ils ne cèdent à personne dans un combat pour une cause juste sous un bon commandement ! Je peux personnellement garantir chacun d'entre eux.";
			link.l1 = "D'accord, mais que vais-je faire de toi maintenant ?";
			link.l1.go = "PiratesOnUninhabited_43";
		break;
		
		case "PiratesOnUninhabited_43":
			iBanditsCount = sti(PChar.GenQuest.PiratesOnUninhabited.PiratesCount);
			iMoney = GetFreeCrewQuantity(PChar);
			
			dialog.text = "Tout ce que tu désires. C'est à toi de décider, amène-nous à une colonie ou accepte-nous dans ton équipage, tu me sembles être un bon capitaine.";
			
			if(iMoney >= iBanditsCount)
			{
				link.l1 = "Très bien, je te prends dans mon équipage. Mais pas de bêtises ! J'ai une discipline stricte sur mon navire !";
				link.l1.go = "PiratesOnUninhabited_9"; // Берем в команду
			}
			
			link.l2 = "Je ne vous emmène nulle part. J'ai déjà assez de brutes dans mon équipage.";
			link.l2.go = "PiratesOnUninhabited_24"; // Рубилово и конец квеста
			
			if(iMoney >= iBanditsCount - 1 && GetPassengersQuantity(PChar) < PASSENGERS_MAX)
			{
				link.l3 = "D'accord, monte dans le bateau, je t'emmène quelque part.";
				link.l3.go = "PiratesOnUninhabited_11"; // В пассажиры и на остров
			}
		break;
		
		case "PiratesOnUninhabited_43_again":
			dialog.text = LinkRandPhrase("Je te jure, capitaine, tu ne le regretteras pas.","Vous avez fait le bon choix, capitaine.","Capitaine, soyez assuré que vous avez eu autant de chance que nous !");
			link.l1 = RandPhraseSimple("Je l'espère.","Dépêche-toi. Le navire n'attendra personne.");
			link.l1.go = "exit";
			NextDiag.TempNode = "PiratesOnUninhabited_43_again";
		break;
		
		case "PiratesOnUninhabited_44":
			sTitle = GenerateRandomNameToShip(PIRATE);
			PChar.GenQuest.PiratesOnUninhabited.StartShipName = sTitle;
			
			dialog.text = "Ce peut être facilement arrangé. Il navigue sur  "+GetStrSmallRegister(XI_ConvertString(ShipsTypes[sti(PChar.GenQuest.PiratesOnUninhabited.StartShipType)].Name+"Voc"))+" '"+sTitle+" et s'occupe du commerce d'esclaves... Faisons ainsi : Si nous le trouvons, vous prenez la cargaison et nous prenons le navire. Oh, et vous pouvez aussi lui demander s'il sait quelque chose à propos de "+ChangeNameCase(NAMETYPE_NICK,PChar.GenQuest.PiratesOnUninhabited.MainPirateName,NAME_ACC)+". J'espère qu'il ne se fera pas dans le froc en entendant ce nom, parce que c'est mon navire..."; // belamour gen
			link.l1 = "D'accord, marché conclu.";
			link.l1.go = "PiratesOnUninhabited_45";
		break;
		
		case "PiratesOnUninhabited_45":
			for(i = 0; i < sti(PChar.GenQuest.PiratesOnUninhabited.PiratesQty); i++)
			{
				rChar = CharacterFromID("PirateOnUninhabited_" + i);
				LAi_SetWarriorTypeNoGroup(rChar);
				rChar.Dialog.currentnode = "PiratesOnUninhabited_11_Again";
				rChar.location = "none"; // Убираем из локации при выходе   исправлено с NPChar на rChar - лесник
				rChar.location.locator = ""; // лесник  - так же исправлено .  тогда бага не будет.
			}
			
			Log_Info("Your crew was increased by " + PChar.GenQuest.PiratesOnUninhabited.PiratesCount + " men.");
			
			ChangeCharacterComplexReputation(pchar,"nobility", 3.0);
			
			AddCharacterCrew(PChar, sti(PChar.GenQuest.PiratesOnUninhabited.PiratesCount) - 1)
			AddPassenger(PChar, NPChar, false); // Главного в пассажиры
			SetCharacterRemovable(NPChar, false);
			//NPChar.FaceId = 101; // лесник потом подобрать аву бандиту.   
			
			PChar.Quest.PiratesOnUninhabited_LocExit.over = "yes"; // Снимаем прерывание на выход из локации
			
			sTemp = XI_ConvertString(PChar.location + "Gen"); // belamour gen
			
			sTitle = "PiratesOnUninhabited" + PChar.location;
			ReOpenQuestHeader(sTitle);
			AddQuestRecordEx(sTitle, "PiratesOnUninhabited", "13");
			AddQuestUserDataForTitle(sTitle, "shoreName", sTemp);
			AddQuestUserData(sTitle, "shoreName", sTemp);
			// --> belamour окончание по количеству персон
			if(sti(PChar.GenQuest.PiratesOnUninhabited.PiratesCount) >= 5)
			{
				AddQuestUserData(sTitle, "count", PChar.GenQuest.PiratesOnUninhabited.PiratesCount + " sailors");
			}
			else
			{
				AddQuestUserData(sTitle, "count", PChar.GenQuest.PiratesOnUninhabited.PiratesCount + " sailor");
			}
			// <-- belamour
			AddQuestUserData(sTitle, "badCapName", ChangeNameCase(NAMETYPE_ORIG, PChar.GenQuest.PiratesOnUninhabited.BadPirateName, NAME_ABL));
			AddQuestUserData(sTitle, "ship", GetStrSmallRegister(XI_ConvertString(ShipsTypes[sti(PChar.GenQuest.PiratesOnUninhabited.StartShipType)].name + "Voc")) + " '" + PChar.GenQuest.PiratesOnUninhabited.StartShipName + "'"); // belamour gen
			
			PChar.GenQuest.PiratesOnUninhabited.StartShore = PChar.location;
			
			PiratesOnUninhabited_SetCapToMap(); // Ставим корабль на карту
			
			DialogExit();
		break;
		
		// Диалог с кэпом в каюте
		case "PiratesOnUninhabited_46":
			dialog.text = "Que diable veux-tu de moi ?";
			link.l1 = "Je suis venu dire bonjour de la part de "+ChangeNameCase(NAMETYPE_NICK,PChar.GenQuest.PiratesOnUninhabited.MainPirateName,NAME_GEN)+". Je suppose que tu le connais ?";
			link.l1.go = "PiratesOnUninhabited_47";
			
			PChar.Quest.PiratesOnUninhabited_ShipSink.over = "yes";
			PChar.GenQuest.PiratesOnUninhabited.ClearShip = true;
			Map_ReleaseQuestEncounter("PiratesOnUninhabited_BadPirate"); // Убираем с глобалки
		break;
		
		case "PiratesOnUninhabited_47":
			dialog.text = "C'est dommage que je n'aie pas étranglé ce vaurien plus tôt. Eh bien, je suppose que le moment est venu de payer pour ma bienveillance...";
			link.l1 = "En effet... Et le temps vient juste de s'écouler...";
			link.l1.go = "PiratesOnUninhabited_48";
		break;
		
		case "PiratesOnUninhabited_48":
			LAi_CharacterDisableDialog(NPChar);
			LAi_Group_Attack(NPChar, Pchar);
			
			LAi_SetCurHPMax(NPChar);
			QuestAboardCabinDialogFree(); // важный метод
			
			LAi_Group_SetRelation(LAI_GROUP_BRDENEMY, LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_Group_FightGroups(LAI_GROUP_BRDENEMY, LAI_GROUP_PLAYER, true);
			LAi_Group_SetCheckFunction(LAI_GROUP_BRDENEMY, "PiratesOnUninhabited_CapDeath");
			
			AddDialogExitQuest("MainHeroFightModeOn");
			
			DialogExit();
		break;
		
		case "PiratesOnUninhabited_49":
			dialog.text = "Beau travail, capitaine ! Tout comme convenu, alors ? Nous prenons le navire et vous prenez la cargaison ?";
			link.l1 = "Bien sûr. Prends le navire et fais-en bon usage.";
			link.l1.go = "PiratesOnUninhabited_50";
		break;
		
		case "PiratesOnUninhabited_50":
			NPChar.LifeDay = 0;
			NPChar.location = "none"; // Убираем из каюты
			NPChar.location.locator = "";
			
			RemovePassenger(PChar, NPChar);
			RemoveCharacterCrew(PChar, sti(PChar.GenQuest.PiratesOnUninhabited.PiratesCount) - 1);
			
			sTitle = "PiratesOnUninhabited" + PChar.GenQuest.PiratesOnUninhabited.StartShore;
			AddQuestRecordEx(sTitle, "PiratesOnUninhabited", "14");
			AddQuestUserData(sTitle, "ship", GetStrSmallRegister(XI_ConvertString(ShipsTypes[sti(PChar.GenQuest.PiratesOnUninhabited.StartShipType)].name)) + " '" + PChar.GenQuest.PiratesOnUninhabited.StartShipName + "'");
			CloseQuestHeader(sTitle);
			
			DeleteAttribute(PChar, "GenQuest.PiratesOnUninhabited");
			
			ChangeAttributesFromCharacter(CharacterFromID("PiratesOnUninhabited_BadPirate"), NPChar, true);
			DialogExit();
			
		break;
		
		// На палубе, когда корабль с нашим пиратом отпустили
		case "PiratesOnUninhabited_50_Deck1":
			dialog.text = "Je te salue, capitaine "+PChar.name+".";
			link.l1 = "Alors, comment trouves-tu ton navire?";
			link.l1.go = "PiratesOnUninhabited_50_Deck2";
		break;
		
		case "PiratesOnUninhabited_50_Deck2":
			dialog.text = "Heh... ça grince et ça craque, tout comme moi. Je pense que nous n'avons plus beaucoup de temps à écumer les mers...";
			link.l1 = "Bonne chance, alors...";
			link.l1.go = "exit";
			NextDiag.TempNode = "PiratesOnUninhabited_50_Deck1";
		break;
		
		// В бухте, вариант, когда корабль, который нужно было захватить, утопили
		case "PiratesOnUninhabited_51":
			dialog.text = "Pourquoi as-tu coulé mon navire ?! Te souviens-tu même de notre accord ?";
			link.l1 = "Quoi, je ne voulais pas qu'il me coule à la place. Ne vois-tu pas que je m'en suis à peine sorti ?";
			link.l1.go = "PiratesOnUninhabited_52";
		break;
		
		case "PiratesOnUninhabited_52":
			if(hrand(1) == 1)
			{
				dialog.text = "Qui se bat comme ça ? Tu as perdu un tel navire ! Nom d'un chien ! Qu'est-ce qu'un gamin comme toi fait même ici ?";
				link.l1 = "Je te couperai la langue, chien.";
				link.l1.go = "PiratesOnUninhabited_53";
			}
			else
			{
				iMoney = sti(ShipsTypes[sti(PChar.GenQuest.PiratesOnUninhabited.StartShipType)].Price);
				iMoney = MakeInt((iMoney / 1.2 + hrand(iMoney - (iMoney / 1.2))) * 1.2);
				dialog.text = "Qui se bat ainsi ? Tu as perdu un tel navire ! As-tu la moindre idée de combien cela m'a coûté ? "+FindRussianMoneyString(iMoney)+" ! Tu me dois maintenant...";
				link.l1 = "Ne serait-ce pas trop pour toi ? N'oublie pas que je t'ai déjà rendu un service.";
				link.l1.go = "PiratesOnUninhabited_54";
				
				if(sti(PChar.money) >= iMoney)
				{
					link.l2 = "Que le diable t'emporte avec ce maudit navire ! Prends ton argent et ne te montre plus à mes yeux !";
					link.l2.go = "PiratesOnUninhabited_55";
				}
			}
		break;
		
		case "PiratesOnUninhabited_53":
			for(i = 0; i < sti(PChar.GenQuest.PiratesOnUninhabited.PiratesQty); i++)
			{
				rChar = CharacterFromID("PirateOnUninhabited_" + i);
				LAi_SetImmortal(rChar, false);
				rChar.LifeDay = 0;
			}
			
			LAi_Group_SetRelation("PiratesOnUninhabitedGroup", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_Group_FightGroups("PiratesOnUninhabitedGroup", LAI_GROUP_PLAYER, true);
			
			sTitle = "PiratesOnUninhabited" + PChar.GenQuest.PiratesOnUninhabited.StartShore;
			AddQuestRecordEx(sTitle, "PiratesOnUninhabited", "15");
			AddQuestUserData(sTitle, "ship", GetStrSmallRegister(XI_ConvertString(ShipsTypes[sti(PChar.GenQuest.PiratesOnUninhabited.StartShipType)].name)) + " '" + PChar.GenQuest.PiratesOnUninhabited.StartShipName + "'");
			CloseQuestHeader(sTitle);
			
			DeleteAttribute(PChar, "GenQuest.PiratesOnUninhabited");
			
			AddDialogExitQuest("MainHeroFightModeOn");
			
			DialogExit();
		break;
		
		case "PiratesOnUninhabited_54":
			dialog.text = "Et à quoi bon ce service pour moi maintenant ?! Si le capitaine "+ChangeNameCase(NAMETYPE_ORIG,PChar.GenQuest.PiratesOnUninhabited.BadPirateName,NAME_NOM)+"est maintenant au fond de la mer avec mon navire ! Maintenant, je n'ai ni ma part, ni mon navire de retour ! Quel destin, mourir dans le caniveau, comme un vagabond !!!";
			link.l1 = "Mais pourquoi ? Je peux organiser des funérailles spectaculaires pour toi. Juste ici, si cela te convient...";
			link.l1.go = "PiratesOnUninhabited_53";
		break;
		
		case "PiratesOnUninhabited_55":
			for(i = 0; i < sti(PChar.GenQuest.PiratesOnUninhabited.PiratesQty); i++)
			{
				rChar = CharacterFromID("PirateOnUninhabited_" + i);
				LAi_SetWarriorTypeNoGroup(rChar);
				LAi_SetImmortal(rChar, false);
				LAi_CharacterDisableDialog(rChar);
				rChar.LifeDay = 0;
			}
			
			sTitle = "PiratesOnUninhabited" + PChar.GenQuest.PiratesOnUninhabited.StartShore;
			AddQuestRecordEx(sTitle, "PiratesOnUninhabited", "16");
			AddQuestUserData(sTitle, "sSex", GetSexPhrase("",""));
			AddQuestUserData(sTitle, "ship", GetStrSmallRegister(XI_ConvertString(ShipsTypes[sti(PChar.GenQuest.PiratesOnUninhabited.StartShipType)].name)) + " '" + PChar.GenQuest.PiratesOnUninhabited.StartShipName + "'");
			CloseQuestHeader(sTitle);
			
			DeleteAttribute(PChar, "GenQuest.PiratesOnUninhabited");
			
			DialogExit();
		break;
		
		// КОНЕЦ
		
		// Warship, 15.05.11. Генер "Justice for sale".
		case "JusticeOnSale_1":
			dialog.text = "Je pensais que nous pourrions... parvenir à un accord, peut-être ? Si vous nous rendez un service, nous le rembourserons, ha-ha.";
			link.l1 = "Un service? Et c'est quoi l'affaire et qu'offres-tu en retour?";
			link.l1.go = "JusticeOnSale_3";
		break;
		
		case "JusticeOnSale_2":
			LAi_Group_SetRelation("JusticeOnSaleGroup_" + LoadedLocation.index, LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_Group_FightGroups("JusticeOnSaleGroup_" + LoadedLocation.index, LAI_GROUP_PLAYER, true);
			
			DialogExit();
			LAi_SetFightMode(PChar, true);
		break;
		
		case "JusticeOnSale_3":
			dialog.text = "Notre capitaine "+PChar.GenQuest.JusticeOnSale.SmugglerName+"a été attrapé par la patrouille locale de "+XI_ConvertString("Colony"+PChar.GenQuest.JusticeOnSale.CityId+"Gen")+". Ils l'ont emprisonné mais ils n'ont pas assez de preuves pour le pendre. Nous ne pouvons pas le sortir nous-mêmes\n"+"Vous êtes un homme respecté. Les gens vous connaissent. Peut-être pourriez-vous négocier, payer sa caution ou simplement l'acheter? Faites-nous confiance, nous quitterons l'île dès que nous aurons notre homme, ainsi votre renommée ne souffrira pas!"; // belamour gen
			link.l1 = "Disons que je peux t'aider. Mais qu'en est-il de mon paiement ?";
			link.l1.go = "JusticeOnSale_4";
			link.l2 = "Va en enfer, rejeton du diable ! Je ne traiterai point avec toi !";
			link.l2.go = "JusticeOnSale_5";
		break;
		
		case "JusticeOnSale_4":
			dialog.text = "Voudriez-vous plusieurs colifichets et talismans indiens ? Ils sont assez rares... Ou préférez-vous du cash sur le comptoir ? Plusieurs milliers de pesos, dis-je ?";
			link.l1 = "Va en enfer, rejeton du diable ! Je ne traiterai pas avec toi !";
			link.l1.go = "JusticeOnSale_5";
			link.l2 = "Je suis intéressé par les babioles indiennes. Je suppose que je vais accepter.";
			link.l2.go = "JusticeOnSale_6";
			link.l3 = "L'argent est le meilleur ami du marin. L'argent n'a pas d'odeur, comme nous le savons tous. Je suis d'accord.";
			link.l3.go = "JusticeOnSale_7";
		break;
		
		case "JusticeOnSale_5":
			for(i = 0; i < sti(PChar.GenQuest.JusticeOnSale.EncQty); i++)
			{
				rChar = CharacterFromID("JusticeOnSale_Jungle_" + i);
				LAi_CharacterDisableDialog(rChar);
			}
			DialogExit();
		break;
		
		case "JusticeOnSale_6":
			PChar.GenQuest.JusticeOnSale.ShipName = GenerateRandomNameToShip(PIRATE);
			PChar.GenQuest.JusticeOnSale.ShipType = PiratesOnUninhabited_GenerateShipType();
			PChar.GenQuest.JusticeOnSale.RewardType = 0; // Подрякушки.
			dialog.text = "Merci, capitaine. Nous vous compenserons le montant de la caution en plus de votre récompense. Je suppose que vous devriez parler au commandant au sujet de notre capitaine. Peut-être pourrez-vous le persuader. Une fois que vous l'aurez sorti, venez à "+XI_ConvertString(PChar.GenQuest.JusticeOnSale.ShoreId+"Ça")+", c'est là que notre navire a jeté l'ancre - "+LowerFirst(XI_ConvertString(ShipsTypes[sti(PChar.GenQuest.JusticeOnSale.ShipType)].name))+" ' "+PChar.GenQuest.JusticeOnSale.ShipName+"'. Nous vous attendrons sur le rivage."; // belamour gen
			link.l1 = "... ";
			link.l1.go = "JusticeOnSale_8";
		break;
		
		case "JusticeOnSale_7":
			PChar.GenQuest.JusticeOnSale.ShipName = GenerateRandomNameToShip(PIRATE);
			PChar.GenQuest.JusticeOnSale.ShipType = PiratesOnUninhabited_GenerateShipType();
			PChar.GenQuest.JusticeOnSale.RewardType = 1; // Монеты.
			
			dialog.text = "Merci, capitaine. Nous vous dédommagerons la somme de la caution en plus de votre récompense. Je suppose que vous devriez parler au commandant au sujet de notre capitaine. Peut-être que vous pourrez le persuader. Une fois que vous l'aurez libéré, venez à "+XI_ConvertString(PChar.GenQuest.JusticeOnSale.ShoreId+"Ce")+", c'est là que notre navire a jeté l'ancre - "+LowerFirst(XI_ConvertString(ShipsTypes[sti(PChar.GenQuest.JusticeOnSale.ShipType)].name))+" ' "+PChar.GenQuest.JusticeOnSale.ShipName+"Nous t'attendrons sur le rivage."; // belamour gen
			link.l1 = "... ";
			link.l1.go = "JusticeOnSale_8";
		break;
		
		case "JusticeOnSale_8":
			for(i = 0; i < sti(PChar.GenQuest.JusticeOnSale.EncQty); i++)
			{
				rChar = CharacterFromID("JusticeOnSale_Jungle_" + i);
				LAi_CharacterDisableDialog(rChar);
			}
			ReOpenQuestHeader("JusticeOnSale");
			AddQuestRecord("JusticeOnSale", "1");
			AddQuestUserData("JusticeOnSale", "cityName", XI_ConvertString("Colony" + PChar.GenQuest.JusticeOnSale.CityId + "Gen")); // belamour gen
			PChar.GenQuest.JusticeOnSale.MayorWait = true;
			PChar.GenQuest.JusticeOnSale.PrisonWait = true;
			
			DialogExit();
		break;
		
		case "JusticeOnSale_9":
			if(hrand(1) == 0)
			{
				if(sti(PChar.GenQuest.JusticeOnSale.RewardType) == 0)
				{
					// Награда побрякушками.
					dialog.text = "Nous y sommes, capitaine ! Vous avez fait un excellent travail en bernant ces bureaucrates ventrus ! Voici votre récompense. Les gars, apportez les babioles !";
				}
				else
				{
					// Награда золотом.
					dialog.text = "Nous y sommes, capitaine! Vous avez fait un excellent travail en trompant ces bureaucrates ventrus! Voici votre récompense. Les gars, allez chercher le coffre!";
				}
				
				link.l1 = "Donne-moi ma part et fiche le camp !";
				link.l1.go = "JusticeOnSale_10";
			}
			else
			{
				// Массакра.
				dialog.text = "Nous y sommes, capitaine ! Je vois que vous avez tout bien arrangé. Mais voyez-vous... nous n'avons pas besoin de témoins, alors... Remercions le capitaine, les gars !";
				link.l1 = RandSwear()+"J'aurais dû te descendre dès notre première rencontre !";
				link.l1.go = "JusticeOnSale_11";
			}
			chrDisableReloadToLocation = false;
		break;
		
		case "JusticeOnSale_10":
			DialogExit();
			if(sti(PChar.GenQuest.JusticeOnSale.RewardType) == 0)
			{
				if(CheckAttribute(PChar, "GenQuest.JusticeOnSale.PrisonMoney"))
				{
					AddItems(PChar, "indian_"+(1+hrand(10)), 1);
				}
				else
				{
					AddItems(PChar, "obereg_"+(1+hrand(10)), 1);
				}
			}
			else
			{
				if(CheckAttribute(PChar, "GenQuest.JusticeOnSale.PrisonMoney"))
				{
					AddMoneyToCharacter(PChar, sti(PChar.rank) * 700 + hrand(2000));
				}
				else
				{
					AddMoneyToCharacter(PChar, sti(PChar.rank) * 500 + hrand(1000));
				}
			}
			for(i = 0; i < sti(PChar.GenQuest.JusticeOnSale.EncQty); i++)
			{
				rChar = CharacterFromID("JusticeOnSale_ShorePirate_" + i);
				LAi_Type_Actor_Reset(rChar);
				LAi_ActorGoToLocation(rChar, "reload", LAi_FindNearestFreeLocator2Pchar("reload"), "none", "", "", "", 3.0);
			}
			AddQuestRecord("JusticeOnSale", "3");
			CloseQuestHeader("JusticeOnSale");
		break;
		
		case "JusticeOnSale_11":
			AddQuestRecord("JusticeOnSale", "4");
			CloseQuestHeader("JusticeOnSale");
			for(i = 0; i < sti(PChar.GenQuest.JusticeOnSale.EncQty); i++)
			{
				rChar = CharacterFromID("JusticeOnSale_ShorePirate_" + i);
				LAi_SetWarriorTypeNoGroup(rChar);
				LAi_Group_MoveCharacter(rChar, "JusticeOnSale_ShoreGroup");
			}
			
			LAi_Group_SetRelation("JusticeOnSale_ShoreGroup", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			AddDialogExitQuest("MainHeroFightModeOn");
			DialogExit();
		break;
		
		// belamour постоялец-->
		case "Unwantedpostor_room":
			dialog.text = ""+GetSexPhrase("Qui es-tu? Et pourquoi tu fais irruption dans ma chambre?","Ouah. Qui es-tu ? C'est ma chambre, bien sûr, mais une telle compagnie ne me dérange pas. Est-ce une livraison d'amour ?")+"";
			link.l1 = ""+GetSexPhrase("Ce n'est plus le tien. L'aubergiste m'a loué la chambre, et puisque tu ne la paies pas, tu vas devoir partir d'ici. Maintenant, on peut faire ça de manière douce ou de manière difficile. Le choix t'appartient.","Tu rêves. Dans notre cas, c'est du nettoyage. Alors débarrasse cet endroit de ta présence. C'est ma chambre maintenant, puisque contrairement à toi, je paie toujours les aubergistes.")+"";
			link.l1.go = "Unwantedpostor_room_1";
		break;
		
		case "Unwantedpostor_room_1":
			If(sti(pchar.reputation.fame) > 60)
			{
				dialog.text = ""+GetSexPhrase("Je pense avoir entendu parler de toi. D'accord, tu as gagné, je m'en vais, je veux encore vivre...","Hmm, j'ai beaucoup entendu parler de vous. Je suppose que ce n'est pas seulement votre langue qui est acérée. Très bien, ne vous fâchez pas, la chambre est à vous.")+"";
				link.l1 = ""+GetSexPhrase("Tu as pris une bonne décision.","Bon garçon.")+"Bonjour, mon ami.";
				link.l1.go = "Unwantedpostor_peace";
				break;
			}
			dialog.text = ""+GetSexPhrase("Alors c'est comme ça, hein ? Eh bien, je choisis la voie difficile.","Sale garce ! Je voulais m'occuper de toi gentiment...")+" ";
			link.l1 = "Bonjour, mon ami."+GetSexPhrase("Comme vous le souhaitez...","Et tu appelles ça 'gentiment'? Je te plains. Quoique, peut-être pas.")+"";
			link.l1.go = "Unwantedpostor_fight";
		break;
		
		case "Unwantedpostor_peace":
			DialogExit();
			sld = CharacterFromID("Berglar_Unwantedpostor");
			ChangeCharacterAddressGroup(sld, "none", "", "");
			sld.lifeday = 0;
			DeleteAttribute(PChar, "GenQuest.Unwantedpostor");
			SetFunctionTimerCondition("Unwantedpostor_NextQuest", 0, 0, 180, false);
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false); //разрешить драться
			chrDisableReloadToLocation = false; // открыть локацию
			sTemp = 40*MOD_SKILL_ENEMY_RATE/2;
			AddCharacterExpToSkill(pchar, "Fortune", sti(sTemp));
			AddCharacterExpToSkill(pchar, "Sneak", sti(sTemp));
			AddCharacterExpToSkill(pchar, "Leadership", sti(sTemp));
			AddDialogExitQuest("sleep_in_tavern");
			TavernWaitDate("wait_day");
		break;
		
		case "Unwantedpostor_fight":
			DialogExit();
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);//разрешить драться
			LAi_SetFightMode(pchar, true);
			sld = characterFromId("Berglar_Unwantedpostor"); 
			LAi_SetWarriorType(sld);
			LAi_Group_MoveCharacter(sld, "EnemyFight");
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_SetCheckMinHP(sld, 10, true, "Unwantedpostor_Win");
			LAi_SetCheckMinHP(pchar, 10, true, "Unwantedpostor_Lose");	
		break;
		
		case "Unwantedpostor_Win":
			dialog.text = ""+GetSexPhrase("Très bien, d'accord, arrête! Ne me tue pas. Je m'en vais.","Halte ! Qu'est-ce qu'on est censés faire maintenant, s'entretuer pour cette pièce ?! Étouffe-toi avec, elle est toute à toi. Enflure...")+" ";
			link.l1 = ""+GetSexPhrase("Bonne décision. La prochaine fois, réfléchis avec ta tête : tout le monde n'est pas aussi clément que moi, ils peuvent tuer par inadvertance.","Hommes.")+"";
			link.l1.go = "Unwantedpostor_Win_1";
		break;
		
		case "Unwantedpostor_Win_1":
			DialogExit();
			sld = CharacterFromID("Berglar_Unwantedpostor");
			ChangeCharacterAddressGroup(sld, "none", "", "");
			sld.lifeday = 0;
			if(CheckAttribute(pchar,"GenQuest.Unwantedpostor")) DeleteAttribute(PChar, "GenQuest.Unwantedpostor"); // полуночная драка
			SetFunctionTimerCondition("Unwantedpostor_NextQuest", 0, 0, 170+rand(20), false);
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false); //разрешить драться
			chrDisableReloadToLocation = false; // открыть локацию
			sTemp = 40*MOD_SKILL_ENEMY_RATE/2;
			AddCharacterExpToSkill(pchar, "FencingL", sti(sTemp));
			AddCharacterExpToSkill(pchar, "FencingS", sti(sTemp));
			AddCharacterExpToSkill(pchar, "FencingH", sti(sTemp));
			AddDialogExitQuest("sleep_in_tavern");
			TavernWaitDate("wait_day");
		break;
		
		case "Unwantedpostor_Lose":
			dialog.text = ""+GetSexPhrase("Eh bien, m'as-tu expulsé ? Dégage d'ici avant que je te tranche.","Donc tout ce que tu sais faire, c'est bavarder. Sois content que je sois encore de bonne humeur, sinon je t'aurais fait quelque chose de bien pire. Va-t'en d'ici !")+"";
			link.l1 = ""+GetSexPhrase("Merde...","Merde, je t'ai sous-estimé... D'accord, d'accord, je m'en vais maintenant.")+"Bonjour, mon ami.";
			link.l1.go = "Unwantedpostor_Lose_1";
		break;
		
		case "Unwantedpostor_Lose_1":
			DialogExit();
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false); //разрешить драться
			chrDisableReloadToLocation = false; // открыть локацию
			sld = CharacterFromID("Berglar_Unwantedpostor");
			sld.lifeday = 0;
			if(CheckAttribute(pchar,"GenQuest.Unwantedpostor")) pchar.GenQuest.Unwantedpostor = "Lose"; // если драка за полночь перевалит
			DoQuestReloadToLocation(Locations[FindLocation(pchar.location)].fastreload+"_tavern", "reload", "reload2_back", "");	
		break;
		// <-- belamour постоялец
		
		// belamour пьяный матрос -->
		case "GuiltySailor":
			dialog.text = "Ah?.. Dégage, bleubite, je ne bois pas... hic !.. avec n'importe qui.";
			link.l1 = "Je vais te frapper si fort maintenant que tu ne boiras plus pendant une semaine.";
			link.l1.go = "GuiltySailor_1";
		break;
		
		case "GuiltySailor_1":
			dialog.text = "Quoi ?! Sais-tu à qui tu parles ? Je suis un marin du navire '"+pchar.ship.name+"'! Je n'ai qu'à prévenir le capitaine, et tu n'auras même pas le temps de quitter la ville ! Déguerpis d'ici tant que tu es encore entier."; 
			link.l1 = "... ";
			link.l1.go = "GuiltySailor_2";
		break;
		
		case "GuiltySailor_2":
			dialog.text = "...";
			link.l1 = "... ";
			link.l1.go = "GuiltySailor_3";
		break;
		
		case "GuiltySailor_3":
			dialog.text = "Capitaine ?..";
			link.l1 = "Vous allez récurer le pont pendant un mois.";
			link.l1.go = "GuiltySailor_4";
		break;
		
		case "GuiltySailor_4":
			NPChar.Dialog.currentnode = "GuiltySailor_Again";
			SetFunctionTimerCondition("GuiltySailor_NextQ", 0, 0, 45+rand(45), false);
			DialogExit();
		break;
		
		case "GuiltySailor_Again":
			dialog.text = "Desole, capitaine!";
			link.l1 = "...";
			link.l1.go = "exit";
			NextDiag.TempNode = "GuiltySailor_Again";
		break;
		// <-- пьяный матрос
		
		// belamour хороший специалист -->
		case "ExpertSailor":
			int ExpertSailorVar = 1 + hrand(2);
			dialog.text = "Salutations capitaine ! Je sais que vous êtes le capitaine, oui.";
			link.l1 = "Salutations. Comment savez-vous que je suis le capitaine ?";
			link.l1.go = "ExpertSailor_"+ExpertSailorVar;
		break;
		
		case "ExpertSailor_1": // матрос
			dialog.text = "Ha, je suis un vieux loup de mer, je navigue sur les flots depuis plus d'une décennie. Je me suis principalement occupé de navigation : j'ai navigué par temps calme, par tempête, sur un lougre, et même sur un vaisseau de guerre. Il est vrai que le mois dernier, j'ai été blessé après une dure bataille, il y avait une forte tempête et personne n'osait monter à la voile alors je l'ai fait, mais j'en ai payé le prix, heureusement je me suis juste tordu la cheville et je ne pouvais pas marcher pendant quelques semaines. Alors ils m'ont mis à terre. Maintenant je vais mieux et je suis assis ici, attendant une opportunité.";
			link.l1 = "Intéressant. Je ne serais pas contre un spécialiste en la matière. Voudrais-tu rejoindre mon équipage ?";
			link.l1.go = "ExpertSailor_1_1";
		break;
		
		case "ExpertSailor_1_1":
			dialog.text = "Pourquoi pas ? Le pont du navire me manque déjà, ainsi que le bruit des voiles gonflées par le vent frais. Je pourrais aussi entraîner votre équipage, si nécessaire. Mais je vous demanderai tout de suite mille pesos, sinon mes poches sont déjà vides. Encore une fois, comme le reste de l'équipage. Je suis une personne honnête.";
			link.l1 = "Non, je vais probablement refuser. Si tous les marins sont payés mille pesos pour l'embauche, je ferai faillite. Ne m'en voulez pas.";
			link.l1.go = "ExpertSailor_nomoney";
			if(GetFreeCrewQuantity(pchar) > 0 && sti(pchar.money) >= 1000)
			{
				link.l2 = "Marché conclu. Je ne rechigne pas à payer mille pesos pour un bon spécialiste. Tiens... voilà. Et je t'attends sur le navire.";
				link.l2.go = "ExpertSailor_payS";
			}
		break;
		
		case "ExpertSailor_nomoney":
			DialogExit();
			NPChar.Dialog.currentnode = "ExpertSailor_Again";
		break;
		
		case "ExpertSailor_payS":
			DialogExit();
			AddMoneyToCharacter(pchar, -1000);
			AddCharacterCrew(pchar, 1);
			ChangeCrewExp(pchar, "Sailors", 10);
			AddCrewMorale(pchar, 1);
			LAi_SetStayType(npchar);
			GetCharacterPos(pchar, &locx, &locy, &locz);
			ChangeCharacterAddressGroup(npchar, pchar.location, "goto", LAi_FindNearestFreeLocator("goto", locx, locy, locz));
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1_back", "", "", "", "", 5);
			npchar.lifeday = 0;
		break;
		
		case "ExpertSailor_2": // канонир
			dialog.text = "Ha, je suis un vieux loup de mer aguerri, je navigue sur les flots depuis plus d'une décennie. J'ai surtout été près des canons : tiré depuis des falconets, des carronades, des coulevrines, des sacres... servi sur un lougre, et même sur un vaisseau de guerre. C'est vrai, le mois dernier j'ai été blessé après une bataille acharnée, un ricochet de mitraille m'a touché, rien de grave juste une éraflure à la jambe, alors ils m'ont débarqué. Maintenant, je vais mieux et je suis assis ici, attendant une occasion.";
			link.l1 = "Intéressant. Je ne serais pas contre un spécialiste en la matière. Voudrais-tu rejoindre mon équipage ?";
			link.l1.go = "ExpertSailor_2_1";
		break;
		
		case "ExpertSailor_2_1":
			dialog.text = "Pourquoi pas ? Le pont-batterie me manque déjà, l'odeur de la poudre à canon brûlée et le rugissement des volées de canons. Je pourrais aussi entraîner votre équipe, si nécessaire. Mais je vais immédiatement vous demander mille pesos, sinon mes poches sont déjà vides. Ensuite, comme le reste de l'équipe, je suis un homme honnête.";
			link.l1 = "Non, je refuserai probablement. Si tous les marins sont payés mille pesos pour l'embauche, je ferai faillite. Ne m'en veux pas.";
			link.l1.go = "ExpertSailor_nomoney";
			if(GetFreeCrewQuantity(pchar) > 0 && sti(pchar.money) >= 1000)
			{
				link.l2 = "D'accord. Je ne rechigne pas à payer mille pesos pour un bon spécialiste. Tiens... voilà. Et je t'attends sur le navire.";
				link.l2.go = "ExpertSailor_payС";
			}
		break;
		
		case "ExpertSailor_payС":
			DialogExit();
			AddMoneyToCharacter(pchar, -1000);
			AddCharacterCrew(pchar, 1);
			ChangeCrewExp(pchar, "Cannoners", 10);
			AddCrewMorale(pchar, 1);
			LAi_SetStayType(npchar);
			GetCharacterPos(pchar, &locx, &locy, &locz);
			ChangeCharacterAddressGroup(npchar, pchar.location, "goto", LAi_FindNearestFreeLocator("goto", locx, locy, locz));
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1_back", "", "", "", "", 5);
			npchar.lifeday = 0;
		break;
		
		case "ExpertSailor_3": // солдат
			dialog.text = "Ha, je suis un vieux loup de mer, je navigue sur les mers depuis plus d'une décennie. J'ai surtout combattu lors d'abordages : j'ai combattu des pirates et des armées régulières, je sais manier toutes sortes d'armes, j'ai été sur un lougre, et même sur un vaisseau de guerre. C'est vrai, le mois dernier j'ai été blessé après une bataille acharnée, ce n'était qu'une petite éraflure de sabre dans le dos, le lâche n'a pas pu m'affronter, mais je l'ai tué en retour, oh tu aurais dû voir leurs têtes quand ils ont vu l'éraflure ha-ha. Alors, ils m'ont mis à terre. Maintenant je vais mieux et je suis assis ici à attendre une opportunité.";
			link.l1 = "Intéressant. Je ne serais pas contre un spécialiste en la matière. Voudrais-tu rejoindre mon équipage ?";
			link.l1.go = "ExpertSailor_3_1";
		break;
		
		case "ExpertSailor_3_1":
			dialog.text = "Pourquoi pas ? Le son des sabres me manque déjà, le crépitement des navires convergeant sur les flancs, et l'adrénaline du combat. Je pourrais aussi entraîner ton équipe, si nécessaire. Mais je te demanderai immédiatement mille pesos, autrement mes poches sont déjà vides. Ensuite, comme le reste de l'équipage, je suis un homme honnête.";
			link.l1 = "Non, je vais probablement refuser. Si tous les matelots sont payés mille pesos pour l'embauche, je vais faire faillite. Ne m'en veux pas.";
			link.l1.go = "ExpertSailor_nomoney";
			if(GetFreeCrewQuantity(pchar) > 0 && sti(pchar.money) >= 1000)
			{
				link.l2 = "D'accord. Je ne rechigne pas à débourser mille pesos pour un bon spécialiste. Tiens... voilà. Et je t'attends sur le navire.";
				link.l2.go = "ExpertSailor_payA";
			}
		break;
		
		case "ExpertSailor_payA":
			DialogExit();
			AddMoneyToCharacter(pchar, -1000);
			AddCharacterCrew(pchar, 1);
			ChangeCrewExp(pchar, "Soldiers", 10);
			AddCrewMorale(pchar, 1);
			LAi_SetStayType(npchar);
			GetCharacterPos(pchar, &locx, &locy, &locz);
			ChangeCharacterAddressGroup(npchar, pchar.location, "goto", LAi_FindNearestFreeLocator("goto", locx, locy, locz));
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1_back", "", "", "", "", 5);
			npchar.lifeday = 0;
		break;
		
		case "ExpertSailor_Again":
			dialog.text = "Bonne chance en mer, capitaine !";
			link.l1 = "Toi aussi.";
			link.l1.go = "exit";
			NextDiag.TempNode = "ExpertSailor_Again";
		break;
		// <-- хороший специалист
		
		//belamour ночной приключенец -->
		// матрос -->
		case "NightAdventure_Sailor":
			LAi_RemoveLoginTime(npchar);
			dialog.text = "Q-qui êtes-vous ?";
			link.l1 = "Je suis capitaine "+GetFullName(pchar)+".";
			if (pchar.id == "Knippel")
			{
				link.l1 = "Désolé, l'ami, je suis pressé.";
				link.l1.go = "exit";
				LAi_CharacterDisableDialog(npchar);
				break;
			}
			switch(pchar.GenQuest.NightAdventureVar)
			{
				case "NightAdventure_SailorTavern":          link.l1.go = "NightAdventure_Sailor_1_1"; break; // до таверны
				case "NightAdventure_SailorShuler0":         link.l1.go = "NightAdventure_Sailor_2_1"; break; // шулер
				case "NightAdventure_SailorShulerGiveMoney": link.l1.go = "NightAdventure_Sailor_2_1"; break;
				case "NightAdventure_SailorShulerGiveOk":    link.l1.go = "NightAdventure_Sailor_2_1"; break; 
				case "NightAdventure_SailorShulerFight":     link.l1.go = "NightAdventure_Sailor_2_1"; break; 
				case "NightAdventure_SailorBoat":      		 link.l1.go = "NightAdventure_Sailor_3_1"; break; // до пирса
				case "NightAdventure_SailorShip":            link.l1.go = "NightAdventure_Sailor_3_1"; break;
				case "NightAdventure_Bull":                  link.l1.go = "NightAdventure_Bull";       break; // наезд
			}
		break;
		// до таверны 
		case "NightAdventure_Sailor_1_1":
			dialog.text = "Capitaine?.. hic ! C-capitaine... escortez-moi jusqu'à la taverne... hic !.. hein ? S'il vous plaît. Il semble que... je me suis p-perdu dans cette c-colonie, oui... hic !..";
			link.l1 = "Fiche-moi la paix, je n'ai pas le temps !";
			link.l1.go = "NightAdventure_End";
			link.l2 = "D'accord, allons-y. Tu ne sembles pas capable d'y arriver tout seul.";
			link.l2.go = "NightAdventure_Sailor_1_2";
		break;
		
		case "NightAdventure_Sailor_1_2":
			dialog.text = "Juste... hic!.. lentement, s'il vous plaît. Je ne suis... hic!.. pas... capable de... me tenir...";
			link.l1 = "D'accord, allons-y, doucement.";
			link.l1.go = "NightAdventure_Sailor_tavern";
		break;
		
		case "NightAdventure_Sailor_tavern":
			DialogExit();
			DeleteAttribute(pchar,"GenQuest.GenQuest.NightAdventure_money");
			NPChar.Dialog.currentnode = "NightAdventure_SailorAgain"; 
			pchar.GenQuest.CantRun = true; // ме-е-едленно ))
			bDisableFastReload = true; // ножками
			LAi_SetActorType(pchar);
			LAi_SetPlayerType(pchar); // обновить для ходьбы
			pchar.GenQuest.NightAdventureNode = "NA_SailorTavern"; // для выбора диалога
			LAi_SetActorType(npchar);
			LAi_ActorFollowEverywhere(npchar, "", -1);
			LAi_Actor2WaitDialog(npchar, pchar);
			SetFunctionLocationCondition("NightAdventure_Intavern", npchar.City+"_tavern", true);
			SetFunctionLocationCondition("NightAdventure_JungleExit", npchar.City+"_Exittown", false);
			pchar.quest.NightAdventure_SeaExit.win_condition.l1 = "EnterToSea";
			pchar.quest.NightAdventure_SeaExit.function = "NightAdventure_SeaExit";
		break;
		
		// шулер
		case "NightAdventure_Sailor_2_1":
			dialog.text = "Capitaine?.. hic!.. C-capitaine... aidez-moi !";
			link.l1 = "Lâche-moi, je n'ai pas le temps !";
			link.l1.go = "NightAdventure_End";
			link.l2 = "Qu'est-ce qui ne va pas chez toi ?";
			link.l2.go = "NightAdventure_Sailor_2_2";
		break;
		
		case "NightAdventure_Sailor_2_2":
			dialog.text = "Là... dans l'auberge... hic !.. le Finaud !";
			link.l1 = "Eh bien, qu'est-ce qui ne va pas avec ça ? Dans n'importe quelle taverne de n'importe quelle colonie, il y a des tricheurs, comme de la vermine.";
			link.l1.go = "NightAdventure_Sailor_2_3";
		break;
		
		case "NightAdventure_Sailor_2_3":
			dialog.text = "C-capitaine, vous... ne comprenez pas... hic !... Il m'a laissé... sans un seul peso ! Hic !.. Et puis... il m'a chassé... hic !..";
			link.l1 = "Alors, que veux-tu de moi maintenant ?";
			link.l1.go = "NightAdventure_Sailor_2_4";
		break;
		
		case "NightAdventure_Sailor_2_4":
			dialog.text = "Viens avec moi... hic !... Occupe-toi de lui ! F-fais... hic !.. qu'il me rende mon argent ! hic !..";
			link.l1 = "Tu n'as pas besoin d'être un filou pour battre un ivrogne à la planche. Bois moins la prochaine fois.";
			link.l1.go = "NightAdventure_End";
			link.l2 = "Eh bien, à quoi ça me sert, hein ? .. Bon, allons-y, regardons ton tricheur de cartes.";
			link.l2.go = "NightAdventure_Sailor_2_5";
		break;
		
		case "NightAdventure_Sailor_2_5":
			dialog.text = "Juste... hic!.. lentement, s'il vous plaît. Je ne suis... hic!.. pas... capable de... me lever...";
			link.l1 = "Très bien, allons-y lentement.";
			link.l1.go = "NightAdventure_Sailor_gambler";
		break;
		
		case "NightAdventure_Sailor_gambler":
			DialogExit();
			NPChar.Dialog.currentnode = "NightAdventure_SailorAgain"; 
			pchar.GenQuest.CantRun = true; // ме-е-едленно ))
			bDisableFastReload = true; // ножками
			LAi_SetActorType(pchar);
			LAi_SetPlayerType(pchar); // обновить для ходьбы
			pchar.GenQuest.NightAdventureNode = "NA_SailorGambler"; // для выбора диалога
			LAi_SetActorType(npchar);
			LAi_ActorFollowEverywhere(npchar, "", -1);
			LAi_Actor2WaitDialog(npchar, pchar);
			SetFunctionLocationCondition("NightAdventure_Intavern", npchar.City+"_tavern", true);
			SetFunctionLocationCondition("NightAdventure_JungleExit", npchar.City+"_Exittown", false);
			pchar.quest.NightAdventure_SeaExit.win_condition.l1 = "EnterToSea";
			pchar.quest.NightAdventure_SeaExit.function = "NightAdventure_SeaExit";
		break;
		
		// диалог в таверне с матросом
		case "NA_SailorTavern":
			dialog.text = "C-capitaine... hic!.. merci beaucoup... vous m'avez sauvé la mise! Je... tenez, voilà... hic!.. C'est pour vous.";
			link.l1 = "Allez, laisse tomber... Ne bois plus comme ça. Ou du moins, ne cherche pas l'aventure.";
			link.l1.go = "NA_SailorTavern_1";
		break;
		
		case "NA_SailorTavern_1":
			DialogExit();
			pchar.quest.NightAdventure_Intavern.over = "yes";
			chrDisableReloadToLocation = false;
			if(GetDataDay() < 7) AddMoneyToCharacter(pchar, 10);
			if(GetDataDay() >= 7  && GetDataDay() < 13) {GiveItem2Character(pchar, "slave_01");  Log_Info("You've received Harpoon");}
			if(GetDataDay() >= 13 && GetDataDay() < 19) {GiveItem2Character(pchar, "potion5");   Log_Info("You've received Ginger root");}
			if(GetDataDay() >= 19 && GetDataDay() < 25) {GiveItem2Character(pchar, "cartridge"); Log_Info("You've received Paper cartridge");}
			if(GetDataDay() >= 25) 
			{
				if(GetDataDay() == 25) {GiveItem2Character(pchar, "amulet_8");  Log_Info("You've received amulet 'Anchor'");}
				if(GetDataDay() == 26) {GiveItem2Character(pchar, "amulet_9");  Log_Info("You've received amulet 'Encolpion'");}
				if(GetDataDay() == 27) {GiveItem2Character(pchar, "obereg_7");  Log_Info("You've received amulet 'Fisher'");}
				if(GetDataDay() >  27) {GiveItem2Character(pchar, "obereg_11"); Log_Info("You've received amulet 'Pilgrim'");}
			}
			DeleteAttribute(pchar,"GenQuest.NightAdventureNode");
			SetFunctionExitFromLocationCondition("NightAdventure_KillPhant", pchar.location, false);
		break;
		// разговор про  шулера
		case "NA_SailorGambler":
			if(pchar.GenQuest.NightAdventureVar == "NightAdventure_SailorShuler0")
			{
				dialog.text = "C-capitaine!.. Le... Hip!.. Tricheur de cartes!..";
				link.l1 = "Qui, moi? Tricheur aux cartes?";
				link.l1.go = "NA_SailorGamblerBelka";
			}
			else	
			{
				dialog.text = "Le voilà, capitaine ! Hic !.. A-assis à la table...";
				link.l1 = "Allez...";
				link.l1.go = "NA_SailorGamblerCards"; 
			}
					
		break;
		// шулер сбежал
		case "NA_SailorGamblerBelka": 
			dialog.text = "Non... hic !... Aiguisé !... Il a disparu !...";
			link.l1 = "Eh bien, il est parti, donc il ne t'a pas attendu.";
			link.l1.go = "NA_SailorGamblerBelka_1";
		break;
		
		case "NA_SailorGamblerBelka_1":
			dialog.text = "Et qu'est-ce qui vient... a-après? Hic!..";
			link.l1 = "Eh bien, il n'y a plus rien que tu puisses faire maintenant. Je ne vais certainement pas aller le chercher la nuit dans toute la colonie. Ne bois plus comme ça. Ou au moins, ne joue pas en étant ivre.";
			link.l1.go = "NA_SailorGamblerBelka_2";
		break;
		
		case "NA_SailorGamblerBelka_2":
			DialogExit();
			pchar.quest.NightAdventure_Intavern.over = "yes";
			chrDisableReloadToLocation = false;
			DeleteAttribute(pchar,"GenQuest.GenQuest.NightAdventure_money");
			DeleteAttribute(pchar,"GenQuest.NightAdventureNode");
			SetFunctionExitFromLocationCondition("NightAdventure_KillPhant", pchar.location, false);
		break;
		
		// шулер остался таверне
		case "NA_SailorGamblerCards":
			DialogExit();
			pchar.quest.NightAdventure_Intavern.over = "yes";
			iNation = npchar.nation
			iRank = MOD_SKILL_ENEMY_RATE+sti(pchar.rank);
			iScl = 15 + 2*sti(pchar.rank);
			sld = GetCharacter(NPC_GenerateCharacter("NightAdventure_CardProf", "citiz_"+(rand(9)+11), "man", "man", iRank, iNation, 1, false, "soldier"));
			FantomMakeCoolFighter(sld, iRank, iScl, iScl, "blade_04", "pistol1", "bullet", iScl*2);
			sld.dialog.filename    = "GenQuests_Dialog.c";
			sld.dialog.currentnode = "NightAdventure_CardProf";
			sld.greeting = "player";
			sld.SaveItemsForDead = true;
			sld.DontClearDead = true;
			AddMoneyToCharacter(sld, sti(pchar.GenQuest.NightAdventure_money));
			GiveItem2Character(sld, "totem_13");
			FreeSitLocator(pchar.location, "sit_front4");
			ChangeCharacterAddressGroup(sld, pchar.location, "sit", "sit_front4");
			LAi_SetSitType(sld);
			chrDisableReloadToLocation = false;
			SetFunctionExitFromLocationCondition("NightAdventure_KillPhant", pchar.location, false);
		break;
		// разговор с самим шулером
		case "NightAdventure_CardProf":
			dialog.text = "Je te propose une partie de dés. Ça te tente ?";
			link.l1 = "Pas question. Je suis le capitaine du navire et je ne joue pas avec les tricheurs de cartes. Mais je peux facilement te briser les côtes si tu ne rends pas l'argent à ce brave homme là-bas.";
			link.l1.go = "NightAdventure_CardProf_1";
		break;
		
		case "NightAdventure_CardProf_1":
			dialog.text = "Avec des tricheurs de cartes ?! Suis-je un tricheur de cartes ? A qui rendre l'argent, à ce poivrot ?! Vous m'offensez, capitaine...";
			link.l1 = "Je peux offenser davantage. Rends l'argent.";
			link.l1.go = "NightAdventure_CardProf_2";
		break;
		
		case "NightAdventure_CardProf_2":
			dialog.text = "Oui, je ne suis pas un tricheur ! Je suis un joueur honnête. La chance gagne, et ton ami n'a tout simplement pas eu de chance, c'est tout.";
			link.l1 = "La chance, hein ? Donne-moi tes dés, et je verrai si le sort te sourira.";
			link.l1.go = "NightAdventure_CardProf_3";
		break;
		
		case "NightAdventure_CardProf_3":
			if(pchar.GenQuest.NightAdventureVar == "NightAdventure_SailorShulerGiveMoney") // отдал деньги
			{
				AddMoneyToCharacter(pchar, makeint(pchar.GenQuest.NightAdventure_money));
				dialog.text = "D'accord, d'accord, du calme, capitaine. Eh bien, j'ai battu l'ivrogne, et j'ai un peu triché, comme le fait chaque deuxième joueur. Voici son argent.";
				link.l1 = "C'est mieux. Et, j'espère que tu comprends que si mon ami dit maintenant que ce n'est pas le montant total, alors je reviendrai te voir ?";
				link.l1.go = "NightAdventure_CardProf_GiveMoney";
			}
			if(pchar.GenQuest.NightAdventureVar == "NightAdventure_SailorShulerGiveOk") // играл честно
			{
				dialog.text = "Oui, s'il vous plaît, voici mes dés. Les deux jeux. Vérifiez. Je n'ai rien à cacher.";
				link.l1 = "Alors... Paire... Rien... Paire... Full... Rien... Rien... Deux Paires... Brelan... Rien... Paire...";
				link.l1.go = "NightAdventure_CardProf_Ok";
			}
			if(pchar.GenQuest.NightAdventureVar == "NightAdventure_SailorShulerFight") // драка
			{
				dialog.text = "Oui, s'il vous plaît, voici mes dés. Les deux jeux. Vérifiez. Je n'ai rien à cacher.";
				link.l1 = "Alors... Carré... Carré... Full... Full... Carré... Poker... Full... Poker... Carré... Full... Hmm, et comment vas-tu m'expliquer ça ?";
				link.l1.go = "NightAdventure_CardProf_Fight";
			}
		break;
		// разошлись миром
		case "NightAdventure_CardProf_GiveMoney":
			dialog.text = "Je comprends tout, voici la somme entière. Bonne chance à toi et à ton ami.";
			link.l1 = "Toi aussi.";
			link.l1.go = "NightAdventure_CardProf_GiveMoney_1";
		break;
		
		case "NightAdventure_CardProf_GiveMoney_1":
			DialogExit();
			chrDisableReloadToLocation = true;
			LAi_CharacterDisableDialog(npchar);
			sld = characterFromId(pchar.GenQuest.NightAdventureId);
			sld.dialog.currentnode = "NightAdventure_CardProf_GiveMoney_2";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
		break;
		// матрос забирает свои деньги
		case "NightAdventure_CardProf_GiveMoney_2":
			AddMoneyToCharacter(pchar, - makeint(pchar.GenQuest.NightAdventure_money));
			dialog.text = "Mais... il ne voulait pas l'admettre ! Hic !..";
			link.l1 = "Oui, il a essayé de l'éviter. Tiens, garde ton argent.";
			link.l1.go = "NightAdventure_CardProf_GiveMoney_3";
		break;
		
		case "NightAdventure_CardProf_GiveMoney_3":
			AddMoneyToCharacter(pchar, makeint(pchar.GenQuest.NightAdventure_money)/2);
			dialog.text = "C-captain... hic !.. merci beaucoup... tu m'as aidé ! Je... 'vomit sur le côté'... tiens, voilà... hic !.. C'est pour toi.";
			link.l1 = "Allez, euh... laisse tomber... Ne bois plus comme ça. Ou au moins ne joue pas quand tu es ivre.";
			link.l1.go = "NightAdventure_CardProf_GiveMoney_4";
		break;
		
		case "NightAdventure_CardProf_GiveMoney_4":
			DialogExit();
			chrDisableReloadToLocation = false;
			DeleteAttribute(pchar,"GenQuest.NightAdventureNode");
			DeleteAttribute(pchar,"GenQuest.GenQuest.NightAdventure_money");
			SetFunctionExitFromLocationCondition("NightAdventure_KillPhant", pchar.location, false);
		break;
		// играл честно
		case "NightAdventure_CardProf_Ok":
			dialog.text = "Alors ? Convaincu ?";
			link.l1 = "Hmm, cela semble vraiment être des dés ordinaires ...";
			link.l1.go = "NightAdventure_CardProf_Ok_1";
		break;
		
		case "NightAdventure_CardProf_Ok_1":
			dialog.text = "Je te l'ai dit. Et ton ami est juste ivre. Il n'a pas non plus voulu admettre sa défaite, alors il t'a amené ici.";
			link.l1 = "D'accord, je suis désolé pour l'incident. Bonne chance.";
			link.l1.go = "NightAdventure_CardProf_Ok_2";
		break;
		
		case "NightAdventure_CardProf_Ok_2":
			DialogExit();
			chrDisableReloadToLocation = true;
			LAi_CharacterDisableDialog(npchar);
			sld = characterFromId(pchar.GenQuest.NightAdventureId);
			sld.dialog.currentnode = "NightAdventure_CardProf_Ok_3";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
		break;
		// подходит матрос
		case "NightAdventure_CardProf_Ok_3":
			dialog.text = "Alors... hic !.. qu'est-ce que c'est ?.. Il... hic !.. n'est pas un filou ?..";
			link.l1 = "Eh bien, il semble avoir joué honnêtement.";
			link.l1.go = "NightAdventure_CardProf_Ok_4";
		break;
		
		case "NightAdventure_CardProf_Ok_4":
			dialog.text = "Et qu'est-ce qui... s-suit? Hic!.. ";
			link.l1 = "Eh bien, il n'y a rien que tu puisses faire maintenant. Il t'a honnêtement battu. Ne bois plus comme ça. Ou du moins ne joue pas quand tu es ivre.";
			link.l1.go = "NightAdventure_CardProf_Ok_5";
		break;
		
		case "NightAdventure_CardProf_Ok_5":
			DialogExit();
			chrDisableReloadToLocation = false;
			DeleteAttribute(pchar,"GenQuest.NightAdventureNode");
			DeleteAttribute(pchar,"GenQuest.NightAdventure_money");
			SetFunctionExitFromLocationCondition("NightAdventure_KillPhant", pchar.location, false);
		break;
		// драка 
		case "NightAdventure_CardProf_Fight":
			dialog.text = "Chance. Tu as juste eu de la chance, c'est tout. La chance est une dame capricieuse.";
			link.l1 = "Hmm, vraiment. Eh bien, jouons ensemble alors, mais attention, je joue avec ces dés !";
			link.l1.go = "NightAdventure_CardProf_Fight_1";
		break;
		
		case "NightAdventure_CardProf_Fight_1":
			dialog.text = "Ces?.. C'est-à-dire... Non, je ne veux pas jouer avec toi ! Tu m'as insulté. Et de toute façon, je suis fauché...";
			link.l1 = "Peut-être que tu veux que je raconte à tout le monde dans cette taverne à propos de tes dés ? Ou peut-être que je les montre ? Et ensuite, tu leur parles de la chance. Qu'en penses-tu ?";
			link.l1.go = "NightAdventure_CardProf_Fight_2";
		break;
		
		case "NightAdventure_CardProf_Fight_2":
			dialog.text = "Quoi ?! Pour qui te prends-tu ?! Essaies-tu de me faire chanter ?! Je vais te faire quelques trous maintenant, si tu ne déguerpis pas !";
			link.l1 = "Je préfère rester ici et montrer à tout le monde tes dés.";
			link.l1.go = "NightAdventure_CardProf_Fight_3";
		break;
		
		case "NightAdventure_CardProf_Fight_3":
			dialog.text = "Eh bien, approche, charogne !";
			link.l1 = "Ne perds pas ton pantalon.";
			link.l1.go = "NightAdventure_CardProf_Fight_4";
		break;
		
		case "NightAdventure_CardProf_Fight_4":
			LAi_LocationDisableOfficersGen(pchar.location, true); // офицеров не  пускать
			SetFunctionLocationCondition("NightAdventure_Duel", Locations[FindLocation(pchar.location)].fastreload+"_town", false);
			pchar.quest.NightAdventure_KillPhant.over = "yes";
			PChar.questTemp.duel.enemy = NPChar.id;
			AddDialogExitQuestFunction("Duel_Prepare_Fight");
			DialogExit();
		break;
		// матрос на выходе
		case "NightAdventure_CardProf_Fight_5":
			dialog.text = "C-capitaine ?.. Vous... hic!.. vous êtes battu ?.. Et celui-là... hic!.. plus rusé ?";
			link.l1 = "Il s'est pris un coup lui-même. Il ne jouera plus avec personne d'autre.";
			link.l1.go = "NightAdventure_CardProf_Fight_6";
		break;
		
		case "NightAdventure_CardProf_Fight_6":
			dialog.text = "Mais... il ne voulait pas l'admettre ! Hic !..";
			link.l1 = "Oui, il a essayé de l'éviter. Il n'avait tout simplement pas votre argent. Il l'a probablement dépensé.";
			link.l1.go = "NightAdventure_CardProf_Fight_7NM";
			link.l2 = "Oui, il a essayé de l'éviter. Voici, ton argent.";
			link.l2.go = "NightAdventure_CardProf_Fight_7";
		break;
		
		case "NightAdventure_CardProf_Fight_7NM": // скажем, что нет денег
			ChangeCharacterComplexReputation(pchar,"nobility", -5); 
			ChangeOfficersLoyality("bad", 2); 
			dialog.text = "Et qu'est-ce qui... s-suit? Hic!..";
			link.l1 = "Eh bien, il n'y a rien que tu puisses faire maintenant. Il t'a battu honnêtement. Ne bois plus comme ça. Ou au moins ne joue pas quand tu es saoul.";
			link.l1.go = "NightAdventure_CardProf_Fight_End";
		break;
		
		case "NightAdventure_CardProf_Fight_7": // деньги есть
			AddMoneyToCharacter(pchar, - makeint(pchar.GenQuest.NightAdventure_money));
			ChangeCharacterComplexReputation(pchar,"nobility", 3); 
			ChangeOfficersLoyality("good", 1); 
			dialog.text = "C-capitaine... hic!.. merci beaucoup... tu m'as aidé ! Je...'vomit sur le côté'... tiens... hic!.. C'est pour toi.";
			link.l1 = "Allez, euh... laisse tomber... Ne bois plus comme ça. Ou au moins ne joue pas quand tu es ivre.";
			link.l1.go = "NightAdventure_CardProf_Fight_End";
			AddMoneyToCharacter(pchar, makeint(pchar.GenQuest.NightAdventure_money)/2);
		break;
		
		case "NightAdventure_CardProf_Fight_End": 
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload4_back", "none", "", "", "OpenTheDoors", 5.0);
			SetFunctionExitFromLocationCondition("NightAdventure_KillPhant", pchar.location, false);
			DeleteAttribute(pchar,"GenQuest.NightAdventure_money");
			DeleteAttribute(pchar,"GenQuest.NightAdventureNode");
			DialogExit();
			
		break;
		// проводить до пирса
		case "NightAdventure_Sailor_3_1":
			dialog.text = "Capitaine?.. hic!.. C-capitaine... escortez-moi jusqu'au q-q-quai... hic!.. hein? S'il vous plaît. J... hic!.. j'ai b-besoin d'aller... au navire... le maître d'équipage... va jurer... hic!.. si je suis en r-retard...";
			link.l1 = "Lâche-moi, je n'ai pas le temps !";
			link.l1.go = "NightAdventure_End";
			link.l2 = "D'accord, allons-y. Tu sembles incapable d'y arriver par toi-même";
			link.l2.go = "NightAdventure_Sailor_3_2";
		break;
		
		case "NightAdventure_Sailor_3_2":
			dialog.text = "Juste... hic!.. lentement, s'il v-vous plaît. Je ne suis... hic!.. pas... capable de... me lever...";
			link.l1 = "D'accord, allons-y doucement.";
			link.l1.go = "NightAdventure_Sailor_3_3";
		break;
		
		case "NightAdventure_Sailor_3_3":
			DialogExit();
			DeleteAttribute(pchar,"GenQuest.GenQuest.NightAdventure_money");
			NPChar.Dialog.currentnode = "NightAdventure_SailorAgain"; 
			pchar.GenQuest.CantRun = true; // ме-е-едленно ))
			bDisableFastReload = true; // ножками
			LAi_SetActorType(pchar);
			LAi_SetPlayerType(pchar); // обновить для ходьбы
			if(pchar.GenQuest.NightAdventureVar == "NightAdventure_SailorBoat")
			{
				pchar.GenQuest.NightAdventureNode = "NA_SailorBoat"; 
			}
			else
			{
				pchar.GenQuest.NightAdventureNode = "NA_SailorShip"; 
			}
			LAi_SetActorType(npchar);
			LAi_ActorFollowEverywhere(npchar, "", -1);
			LAi_Actor2WaitDialog(npchar, pchar);
			SetFunctionLocatorCondition("NightAdventure_ToBoat",  npchar.City+"_town", "quest", "quest1", false)
			SetFunctionLocationCondition("NightAdventure_JungleExit", npchar.City+"_Exittown", false);
			pchar.quest.NightAdventure_SeaExit.win_condition.l1 = "EnterToSea";
			pchar.quest.NightAdventure_SeaExit.function = "NightAdventure_SeaExit";
		break;
		// вариант просто проводить
		case "NA_SailorBoat":
			dialog.text = "C-capitaine... hic!.. merci beaucoup... tu m'as aidé ! Je...'vomit sur le côté'... tiens... hic!.. C'est pour toi.";
			link.l1 = "Allez, euh... laisse tomber... Ne bois plus comme ça. Ou au moins, ne cherche pas l'aventure.";
			link.l1.go = "NA_SailorBoat_1";
		break;
		
		case "NA_SailorBoat_1":
			DialogExit();
			chrDisableReloadToLocation = false;
			if(GetDataDay() < 7) AddMoneyToCharacter(pchar, 10);
			if(GetDataDay() >= 7  && GetDataDay() < 13)  {GiveItem2Character(pchar, "slave_01");  Log_Info("You've received Harpoon");}
			if(GetDataDay() >= 13 && GetDataDay() < 19)  {GiveItem2Character(pchar, "potion5");   Log_Info("You've received Ginger root");}
			if(GetDataDay() >= 19 && GetDataDay() < 25)  {GiveItem2Character(pchar, "cartridge"); Log_Info("You've received Paper cartridge");}
			if(GetDataDay() >= 25) 
			{
				if(GetDataDay() == 25) {GiveItem2Character(pchar, "amulet_8");  Log_Info("You've received amulet 'Anchor'");}
				if(GetDataDay() == 26) {GiveItem2Character(pchar, "amulet_9");  Log_Info("You've received amulet 'Encolpion'");}
				if(GetDataDay() == 27) {GiveItem2Character(pchar, "obereg_7");  Log_Info("You've received amulet 'Fisher'");}
				if(GetDataDay() >  27) {GiveItem2Character(pchar, "obereg_11"); Log_Info("You've received amulet 'Pilgrim'");}
			}
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1_back", "none", "", "", "NightAdventure_OpenLoc", -1); 
			DeleteAttribute(pchar,"GenQuest.NightAdventureNode");
			SetFunctionExitFromLocationCondition("NightAdventure_KillPhant", pchar.location, false);
		break;
		// просится на корабль
		case "NA_SailorShip":
			dialog.text = "C-capitaine!.. Navire!";
			link.l1 = "Quel 'navire'?";
			link.l1.go = "NA_SailorShip_1";
		break;
		
		case "NA_SailorShip_1":
			dialog.text = "B-bateau!.. Où est-il?.. hic!..";
			link.l1 = "Évidemment, il est parti. Tu devrais moins boire dans les tavernes. Tout le navire n'attendra pas un seul marin ivre.";
			link.l1.go = "NA_SailorShip_2";
		break;
		
		case "NA_SailorShip_2":
			dialog.text = "Mais je suis... hic !... pas ivre... presque... peut-être...";
			link.l1 = "Ah, oui, en effet. Bonne chance.";
			link.l1.go = "NA_SailorShip_3";
		break;
		
		case "NA_SailorShip_3":
			dialog.text = "Attendez, c-capitaine ! E-emmenez-moi... hic!.. à votre n-navire ! Je ne boirai plus... hic !.. jamais...";
			if(GetFreeCrewQuantity(pchar) > 0)
			{
				link.l1 = "D'accord, que peux-tu y faire. Mais va immédiatement au navire. Et que Dieu ne plaise, si je te vois quelque part ivre, tu récureras le pont jusqu'au prochain port d'escale.";
				link.l1.go = "NA_SailorShip_4";
			}
			link.l2 = "Pour que tu te saoules avec mon salaire, et ensuite je te cherche dans toutes les tavernes et les porches de la colonie ? Non, je n'ai pas besoin d'un tel bonheur.";
			link.l2.go = "NA_SailorShip_6";
			
		break; 
		
		case "NA_SailorShip_4": 
			AddCharacterCrew(pchar, 1);
			dialog.text = "Oui, c-capitaine!.. hic!..";
			link.l1 = "... ";
			link.l1.go = "NA_SailorShip_5";
		break;
		
		case "NA_SailorShip_5": 
			DialogExit();
			LAi_ActorRunToLocation(npchar, "reload", "reload1_back", "none", "", "", "NightAdventure_OpenLoc", 5.0); // побежит вдохновленный 
			SetFunctionExitFromLocationCondition("NightAdventure_KillPhant", pchar.location, false);
		break;
		
		case "NA_SailorShip_6": 
			DialogExit();
			LAi_SetActorType(pchar);
			LAi_ActorTurnToLocator(pchar, "reload", "reload4_back");
			LAi_ActorGoToLocation(npchar, "reload", "reload4_back", "none", "", "", "NightAdventure_OpenLoc", -1);
			SetFunctionExitFromLocationCondition("NightAdventure_KillPhant", pchar.location, false);
		break;
		// пьяные наезды
		case "NightAdventure_Bull":
			switch (rand(5))
			{
				case 0:
				dialog.text = "Capitaine?.. hic!.. Vous êtes... un rat de terre... hic!.. pas un capitaine!..";
				link.l1 = "J'ai tranché des centaines de types comme toi lors des abordages, alors dégage, ivrogne.";
				link.l1.go = "NightAdventure_End";
				break;
				
				case 1:
				dialog.text = "Capitaine... hic !.. C-capitaine de cette auge dans le raid ?.. hic !..";
				link.l1 = "Si tu vois cette auge à l'horizon lorsque tu es en mer, il vaut mieux plonger immédiatement dans l'eau : avec les requins, tu auras plus de chances de survivre qu'en affrontant mon navire. Maintenant, va-t'en !";
				link.l1.go = "NightAdventure_End";
				break;
				
				case 2:
				dialog.text = "Capitaine?.. hic!.. Vous êtes un buveur de lait, pas un capitaine!.. Votre m-mère était encore une fillette... hic!.. quand je naviguais déjà sur les mers...";
				link.l1 = "Mais ta mère serait probablement heureuse de savoir qu'un gamin comme moi est devenu capitaine, tandis que toi, tu es resté un marin ivrogne, bon seulement à frotter les ponts.";
				link.l1.go = "NightAdventure_End";
				break;
				
				case 3:
				dialog.text = "Capitaine?.. Faites attention... hic!.. capitaine... Je vais vous casser les dents... hic!.. vous n'aurez pas le temps de cligner des yeux!..";
				link.l1 = "Le recul te tuera. Dégage ! Fais-moi sauter les dents si tu l'oses...";
				link.l1.go = "NightAdventure_End";
				break;
				
				case 4:
				dialog.text = "Capitaine?.. On dirait... hic!.. une espèce de va-nu-pieds...";
				link.l1 = "On dirait que tu ne t'es pas encore regardé dans le miroir...";
				link.l1.go = "NightAdventure_End";
				break;
				
				case 5:
				dialog.text = "C-capitaine?.. Je n'aurais pas... hic!.. même accepté de s-servir... sur votre navire... hic!..";
				link.l1 = "Et personne ne t'a proposé de monter à bord de mon navire pour que tu acceptes. Dégage de mon chemin.";
				link.l1.go = "NightAdventure_End";
				break;
			}
		break;
		
		case "NightAdventure_End":
			DialogExit();
			SetFunctionExitFromLocationCondition("NightAdventure_KillPhant", pchar.location, false);
			NPChar.Dialog.currentnode = "NightAdventure_Again";
		break;
		
		case "NightAdventure_Again":
			NextDiag.TempNode = "NightAdventure_Again";
			dialog.text = "Hic!.. ";
			link.l1 = "Va dormir.";
			link.l1.go = "exit";
		break;
		
		case "NightAdventure_SailorAgain":
			dialog.text = "Hic!.. Oui... encore loin?..";
			link.l1 = "Nous sommes proches, sois patient.";
			link.l1.go = "exit";
			NextDiag.TempNode = "NightAdventure_SailorAgain";
			LAi_SetActorType(npchar);
			LAi_ActorFollowEverywhere(npchar, "", -1);
			LAi_Actor2WaitDialog(npchar, pchar);
		break;
		// <-- матрос
		// горожанин -->
		case "NightAdventure_Citizen":
			LAi_RemoveLoginTime(npchar);
			dialog.text = "Q-qui... hic!.. es-tu?..";
			link.l1 = "Je suis capitaine "+GetFullName(pchar)+".";
			if (pchar.id == "Knippel")
			{
				link.l1 = "Désolé, camarade, je suis pressé.";
				link.l1.go = "exit";
				LAi_CharacterDisableDialog(npchar);
				break;
			}
			switch(pchar.GenQuest.NightAdventureVar)
			{
				case "NightAdventure_CitizenHomie":          link.l1.go = "NightAdventure_Citizen_1_1"; break; // выручить приятеля
				case "NightAdventure_CitizenHomieSolderNM":  link.l1.go = "NightAdventure_Citizen_1_1"; break; 
				case "NightAdventure_CitizenHomieSolderGM":  link.l1.go = "NightAdventure_Citizen_1_1"; break;
				case "NightAdventure_CitizenHomieOfficer":   link.l1.go = "NightAdventure_Citizen_1_1"; break; 
				case "NightAdventure_SailorShuler0":         link.l1.go = "NightAdventure_Sailor_2_1";  break; // шулер
				case "NightAdventure_SailorShulerGiveMoney": link.l1.go = "NightAdventure_Sailor_2_1";  break;
				case "NightAdventure_SailorShulerGiveOk":    link.l1.go = "NightAdventure_Sailor_2_1";  break; 
				case "NightAdventure_SailorShulerFight":     link.l1.go = "NightAdventure_Sailor_2_1";  break; 
				case "NightAdventure_Bull":                  link.l1.go = "NightAdventure_Bull";        break;// наезд
			}
		break;
		
		// дружок
		case "NightAdventure_Citizen_1_1":
			dialog.text = "Capitaine?.. hic!.. C-capitaine... aidez-moi ! Je... je veux dire... hic!.. mon ami... a vraiment besoin de votre a-aide ! Je vous en prie.";
			link.l1 = "Je ne vais pas résoudre les problèmes de chaque ivrogne que je rencontre au milieu de la nuit..";
			link.l1.go = "NightAdventure_End";
			link.l2 = "D'accord, dis-moi ce qui est arrivé à ton ami là-bas.";
			link.l2.go = "NightAdventure_Citizen_1_2";
		break;
		
		case "NightAdventure_Citizen_1_2":
			dialog.text = "Mon ami ... il, en général ... il s'est saoulé. Juste en général ... hic ! .. s'est saoulé ...";
			link.l1 = "Bien sûr, j'ai dégrisé les marins qui buvaient en service, mais par des méthodes assez radicales. Je ne pense pas que ton ami en ait besoin.";
			link.l1.go = "NightAdventure_Citizen_1_3";
		break;
		
		case "NightAdventure_Citizen_1_3":
			dialog.text = "Non ! Il... il est avec la g-garde ! Il s'est arrr...gumenté avec lui. Et il s'est battu. Et il... hic !.. a été emmené en prison... il est juste soûl !";
			link.l1 = "Et que veux-tu de moi maintenant ? C'est sa faute à lui-même : il faut boire moins. Ou au moins éviter de chercher des ennuis tout seul...";
			link.l1.go = "NightAdventure_Citizen_1_4";
		break;
		
		case "NightAdventure_Citizen_1_4":
			dialog.text = "Parle au gardien, cap... hic! .. capitaine! Il laissera partir... laisse-le partir! Hmm... voilà... hic!.. quelle chance tu as... Mon ami vient de... se disputer... eh bien... et voulait me frapper au visage... mais... hic!.. n'a pas eu d'arme...";
			link.l1 = "Maintenant, je n'ai plus rien à faire, sauf sortir des ivrognes de prison la nuit après qu'ils se soient battus avec les gardes. Non, qu'il reste là quelques jours. Peut-être que la prochaine fois, tu y réfléchiras à deux fois.";
			link.l1.go = "NightAdventure_End";
			link.l2 = "Oui, au diable avec toi. D'accord, je parlerai au geôlier.";
			link.l2.go = "NightAdventure_Citizen_1_5";
			if(GetNationRelation2MainCharacter(sti(NPChar.nation)) == RELATION_ENEMY && !CheckNationLicence(HOLLAND))
			{
				link.l2 = "Je ne suis pas sûr que le gardien apprécie mon accent. Il ira simplement en informer le gouverneur plus tard. Alors continuez sans moi.";
				link.l2.go = "NightAdventure_Citizen_RE";
			}
			if(ChangeCharacterNationReputation(pchar, sti(NPChar.nation), 0) <= -15)
			{
				link.l2 = "Je crains, ami, que le chemin vers les casemates locales me soit bloqué. Le gardien garde mon portrait comme une icône, et je n'ai pas l'intention de m'installer dans ces appartements hospitaliers. Je suis donc désolé, mais je ne peux pas t'aider.";
				link.l2.go = "NightAdventure_Citizen_NR";
			}
		break;
		
		case "NightAdventure_Citizen_1_5":
			DialogExit();
			pchar.GenQuest.NightAdventureToJail = true;
			DeleteAttribute(pchar,"GenQuest.GenQuest.NightAdventure_money");
			chrDisableReloadToLocation = true; //закрыть локацию пока бежит
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload4_back", "none", "", "", "OpenTheDoors", 5.0); 
			SetFunctionLocationCondition("NightAdventure_JungleExit", npchar.City+"_Exittown", false);
			pchar.quest.NightAdventure_SeaExit.win_condition.l1 = "EnterToSea";
			pchar.quest.NightAdventure_SeaExit.function = "NightAdventure_SeaExit";
		break;
		
		case "NightAdventure_CitizenHomiePresent":
			dialog.text = "M-merci... capitaine. Et pour mon a-ami aussi. V-voici... c'est pour vous.";
			link.l1 = "La prochaine fois, surveille ton ami quand il se saoule et décide d'aller se battre avec les gardes. Ce n'est pas chaque nuit que des capitaines arpentent les rues, prêts à négocier avec le geôlier pour quelques ivrognes. Bonne chance.";
			link.l1.go = "NightAdventure_CitizenHomiePresent_1";
		break;
		
		case "NightAdventure_CitizenHomiePresent_1":
			DialogExit();
			LAi_SetPlayerType(pchar);
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload4_back", "none", "", "", "", 5.0);
			sld = characterFromId("NightAdventure_Homie");
			sld.lifeday = 0;
			LAi_SetActorType(sld);
			LAi_ActorRunToLocation(sld, "reload", "reload4_back", "none", "", "", "OpenTheDoors", 5.0);
			if(GetDataDay() < 7) 						{GiveItem2Character(pchar, "indian_2");  Log_Info("You've received amulet 'Gunpowder tester'");}
			if(GetDataDay() >= 7  && GetDataDay() < 13) {GiveItem2Character(pchar, "obereg_5");  Log_Info("You've received amulet 'Jade turtle'");}
			if(GetDataDay() >= 13 && GetDataDay() < 19) {GiveItem2Character(pchar, "obereg_6");  Log_Info("You've received amulet 'Monkey's fist'");}
			if(GetDataDay() >= 19 && GetDataDay() < 25) {GiveItem2Character(pchar, "obereg_8");  Log_Info("You've received amulet 'Merchant's beads'");}
			if(GetDataDay() == 25) 		    			{GiveItem2Character(pchar, "indian_9");  Log_Info("You've received amulet 'Baldo'");}
			if(GetDataDay() == 26) 	    				{GiveItem2Character(pchar, "obereg_11"); Log_Info("You've received amulet 'Pilgrim'");}
			if(GetDataDay() >= 27 && GetDataDay() < 31) {GiveItem2Character(pchar, "obereg_4");  Log_Info("You've received amulet 'Gypsy's fan'");}
			if(GetDataDay() == 31) 	    				{GiveItem2Character(pchar, "amulet_11"); Log_Info("You've received amulet 'Cimaruta'");}
			SetFunctionExitFromLocationCondition("NightAdventure_KillPhant", pchar.location, false);
		break;
		
		case "NightAdventure_Citizen_RE":
			if (GetSummonSkillFromName(pchar, SKILL_SNEAK) + GetSummonSkillFromName(pchar, SKILL_FORTUNE)  < (rand(100)+rand(100)))
			{
				dialog.text = "Oh!.. Alors je sais comment... hic!.. libérer mon... a-ami... hic!.. Gardes! Un espion dans la ville!.. hic!..";
				link.l1 = "Tu as choisi une très mauvaise option pour libérer ton ami.";
				link.l1.go = "NightAdventure_Fight";
			}
			else
			{
				AddCharacterExpToSkill(pchar, SKILL_SNEAK, 100);
				AddCharacterExpToSkill(pchar, SKILL_FORTUNE, 100);
				dialog.text = "Ah, é-étranger... hic! .. Tu... tu auras des problèmes... hic! .. D'accord... J'ai ici... hic! .. tout est sous contrôle.";
				link.l1 = "Bien sûr. Si quelque chose se passe, je viendrai te voir tout de suite.";
				link.l1.go = "NightAdventure_End";
			}
		break;
		
		case "NightAdventure_Citizen_NR":
			if (GetSummonSkillFromName(pchar, SKILL_SNEAK) + GetSummonSkillFromName(pchar, SKILL_FORTUNE) < (rand(100)+rand(100)))
			{
				dialog.text = "Ah ... alors tu ... hips ! .. Tu es un criminel ! Gardes !";
				link.l1 = "Ah, donc c'est comme ça que tu parles maintenant !";
				link.l1.go = "NightAdventure_Fight";
			}
			else
			{
				AddCharacterExpToSkill(pchar, SKILL_SNEAK, 100);
				AddCharacterExpToSkill(pchar, SKILL_FORTUNE, 100);
				dialog.text = "Oh, comment ... hic ! .. désolé. Et si... vous me laissiez... négocier pour vous avec... hic !.. le gardien, et vous... hic !.. pour m-mon ami ?..";
				link.l1 = "Non, tu n'as pas besoin de négocier pour moi, merci. Bonne chance.";
				link.l1.go = "NightAdventure_End";
			}
		break;
		
		case "NightAdventure_Fight":
			DialogExit();
			SetFunctionExitFromLocationCondition("NightAdventure_KillPhant", pchar.location, false);
			LAi_group_Attack(NPChar, Pchar);
		break;
		// контрабандист 
		case "NightAdventure_Pirate": 
			LAi_RemoveLoginTime(npchar);
			dialog.text = "Q-q-qui... hic !.. es-tu ?...";
			link.l1 = "Je suis capitaine "+GetFullName(pchar)+".";
			if (pchar.id == "Knippel")
			{
				link.l1 = "Désolé, l'ami, je suis pressé.";
				link.l1.go = "exit";
				LAi_CharacterDisableDialog(npchar);
				break;
			}
			switch(pchar.GenQuest.NightAdventureVar)
			{
				case "NightAdventure_Bull":          		 link.l1.go = "NightAdventure_Bull";       break; // пьяные наезды
				case "NightAdventure_PiratePeace":           link.l1.go = "NightAdventure_PirateCave"; break; // до пещеры
				case "NightAdventure_PirateBad":             link.l1.go = "NightAdventure_PirateCave"; break;
			}
		break;
		
		case "NightAdventure_PirateCave":
			dialog.text = "Capitaine ?.. hic !.. C-capitaine... écoutez, escortez-moi à la grotte près de la ville... hic !.. hein ? J-je vous en prie.";
			link.l1 = "À la grotte ? Je ne comprends pas. Pourquoi vas-tu à la grotte ? Et pourquoi as-tu besoin de moi ?";
			link.l1.go = "NightAdventure_PirateCave_1";
		break;
		
		case "NightAdventure_PirateCave_1":
			dialog.text = "Tu vois... c-capitaine... hic !.. Je n'ai plus d'argent pour les boissons... Et dans... hic !.. dans une grotte j'ai... une cachette, alors... hic !.. Mais je... c'est... j'ai peur d'aller seul dans la j... j... jungle... hic !.. la nuit... Alors...";
			link.l1 = "Lâche-moi, je n'ai pas le temps !";
			link.l1.go = "NightAdventure_End";
			link.l2 = "Très bien, allons-y. Tu sembles incapable d'y arriver par toi-même";
			link.l2.go = "NightAdventure_PirateCave_2";
		break;
		
		case "NightAdventure_PirateCave_2":
			dialog.text = "J-juste... hic !.. doooucement, s'il vous plaît. Je ne suis... hic !.. pas... capable de... me lever...";
			link.l1 = "D'accord, allons-y lentement.";
			link.l1.go = "NightAdventure_PirateCave_3";
		break;
		
		case "NightAdventure_PirateCave_3":
			DialogExit();
			NPChar.Dialog.currentnode = "NightAdventure_SailorAgain"; 
			pchar.GenQuest.CantRun = true; // ме-е-едленно ))
			bDisableFastReload = true; // ножками
			LAi_SetActorType(pchar);
			LAi_SetPlayerType(pchar); // обновить для ходьбы
			pchar.GenQuest.NightAdventureNode = true; // что взяли квест
			LAi_SetActorType(npchar);
			LAi_ActorFollowEverywhere(npchar, "", -1);
			LAi_Actor2WaitDialog(npchar, pchar);
			string NAIsland = GetIslandByCityName(npchar.city);
			string NACave = "absent. Tell belamour that you are";
			// найти пещеру на острове
			i = Findlocation(NAIsland+"_Grot");
			if(i != -1) NACave = NAIsland+"_Grot";
			i = Findlocation(NAIsland+"_Cave");
			if(i != -1) NACave = NAIsland+"_Cave";
			// для мейна и капстервиля
			i = Findlocation(npchar.city+"_Cave");
			if(i != -1) NACave = npchar.city+"_Cave";
			i = Findlocation(npchar.city+"_Grot");
			if(i != -1) NACave = npchar.city+"_Grot";
			
			log_testinfo("Cave "+NACave+" on the island " +NAIsland);
			SetFunctionLocationCondition("NightAdventure_InCave", NACave, false);
			SetFunctionLocationCondition("NightAdventure_InFort", npchar.city+"_ammo", false);
			pchar.quest.NightAdventure_SeaExit.win_condition.l1 = "EnterToSea";
			pchar.quest.NightAdventure_SeaExit.function = "NightAdventure_SeaExit";
		break;
		
		case "NightAdventure_PirateCave_4": // диалог в пищере
			if(pchar.GenQuest.NightAdventureVar == "NightAdventure_PiratePeace")
			{
				AddMoneyToCharacter(pchar, 1000);
				TakeNItems(pchar, "potionrum", 1);   
				TakeNItems(pchar, "potionwine", 1);
				PlaySound("interface\important_item.wav");
				Log_Info("You've received an alcohol")
				dialog.text = "C-capt'ain... hic!.. merci beaucoup... vous m'avez sauvé la mise! Je... tenez... hic!.. C'est pour vous.";
				link.l1 = "Allez, euh... laisse tomber... Ne bois plus comme ça.";
				link.l1.go = "NightAdventure_PirateCave_4_1";
				break;
			} 
			if(pchar.GenQuest.NightAdventureVar == "NightAdventure_PirateBad")
			{
				dialog.text = "Excellent, capitaine ! Je suis ravi que vous ayez accepté.";
				link.l1 = "Eh bien, où est ta planque ? Attends une minute, il semble que tu n'es pas saoul.";
				link.l1.go = "NightAdventure_PirateCave_5";
				break;
			} 
		break;
		
		case "NightAdventure_PirateCave_4_1": // мирный исход
			DialogExit();
			LAi_ActorRunToLocation(npchar, "reload", "reload1_back", "none", "", "", "OpenTheDoors", 5.0); 
			SetFunctionTimerCondition("NightAdventure_KillPhant", 0, 0, 0, false);
		break;
		
		case "NightAdventure_PirateCave_5": // драка
			dialog.text = "Oui, je n'ai pas beaucoup bu, ne t'inquiète pas pour moi. Et à propos de la cachette... Les gars !";
			link.l1 = "...";
			link.l1.go = "NightAdventure_PirateCave_6";
		break;
		
		case "NightAdventure_PirateCave_6": 
			DialogExit();
			AddDialogExitQuestFunction("NightAdventure_PiratesInCave");
		break;
		
		case "NightAdventure_PirateCave_7": 
			dialog.text = "Les gars, j'ai apporté une cachette ici. Vous devez l'ouvrir. À moins, bien sûr, que cette cachette ne s'ouvre d'elle-même, de bon gré. Capitaine, qu'en pensez-vous ?";
			link.l1 = LinkRandPhrase("Je pense qu'il vaudrait mieux que tu te saoules jusqu'à perdre la mémoire. Au moins, tu resterais en vie. Et maintenant, il ne reste qu'une seule route... "," Je pense que tu n'as pas toute ta tête, puisque tu as décidé de dévaliser le capitaine d'un navire de guerre ... "," Je pense que tu es probablement fatigué de vivre, puisque tu as décidé d'essayer ça...");
			link.l1.go = "NightAdventure_PirateCave_8F";
			link.l2 = "D'accord, j'imagine qu'il vaut mieux partir en bons termes. Et combien vous faut-il ?";
			link.l2.go = "NightAdventure_PirateCave_8A";
		break;
		
		case "NightAdventure_PirateCave_8F": 
			dialog.text = "Alors, on n'ouvrira pas la cachette de bon gré ?";
			link.l1 = "J'ai bien peur que ce soit le dernier magot de ta vie.";
			link.l1.go = "NightAdventure_PirateCave_9F";
		break;
		
		case "NightAdventure_PirateCave_9F": 
			DialogExit();
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false); // разрешить драться
			sld = CharacterFromID(pchar.GenQuest.NightAdventureId);
			sld.SaveItemsForDead   = true; // сохранять на трупе вещи
			sld.DontClearDead = true;  // не убирать труп через 200с
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, "EnemyFight");
			for(i=0 ; i < 3; i++)
			{
				sld = CharacterFromID("NAPirat_" + i);
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "EnemyFight");
			}
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("EnemyFight", "OpenTheDoors");
			LAi_SetFightMode(pchar, true);
			SetFunctionExitFromLocationCondition("NightAdventure_KillPhant", pchar.location, false);
		break;
		
		case "NightAdventure_PirateCave_8A": // испугался
			iMoney = sti(pchar.money)/3;
			dialog.text = "Oh, nous ne sommes pas gourmands. Juste "+FindRussianMoneyString(iMoney)+"."; 
			link.l1 = "J'ai bien peur que ce soit la dernière cachette de ta vie.";
			link.l1.go = "NightAdventure_PirateCave_9F";
			link.l2 = "D'accord, fais comme tu veux. Je n'aiderai plus jamais un ivrogne...";
			link.l2.go = "NightAdventure_PirateCave_9A";
		break;
		
		case "NightAdventure_PirateCave_9A": 
			DialogExit();
			NPChar.Dialog.currentnode = "NightAdventure_PirateCaveAgain";
			SetFunctionExitFromLocationCondition("NightAdventure_KillPhant", pchar.location, false); 
			iMoney = sti(pchar.money)/3;
			AddMoneyToCharacter(pchar, -iMoney);
			AddMoneyToCharacter(npchar, iMoney);
			npchar.SaveItemsForDead   = true; // сохранять на трупе вещи
			npchar.DontClearDead = true;  // не убирать труп через 200с
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false); // разрешить драться
			chrDisableReloadToLocation = false;//открыть локацию
			LAi_SetWarriorType(npchar);
			LAi_group_MoveCharacter(npchar, "EnemyFight");
			for(i=0 ; i < 3; i++)
			{
				sld = CharacterFromID("NAPirat_" + i);
				sld.dialog.currentnode = "NightAdventure_PirateCaveAgain";
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "EnemyFight");
			}
			LAi_Group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_NEITRAL);
		break;
		
		case "NightAdventure_PirateCaveAgain": 
			dialog.text = "Capitaine, vous me surprenez par votre générosité. Voulez-vous partager davantage avec nous ?";
			link.l1 = "Je t'ai déjà tout donné. Je m'en vais...";
			link.l1.go = "exit";
			NextDiag.TempNode = "NightAdventure_PirateCaveAgain";
		break;
		
		// дворянин -->
		case "NightAdventure_Noble":
			LAi_RemoveLoginTime(npchar);
			dialog.text = "Q-q-qui... hic!.. êtes-vous?...";
			link.l1 = "Je suis capitaine "+GetFullName(pchar)+".";
			if (pchar.id == "Knippel")
			{
				link.l1 = "Désolé, camarade, je suis pressé.";
				link.l1.go = "exit";
				LAi_CharacterDisableDialog(npchar);
				break;
			}
			switch(pchar.GenQuest.NightAdventureVar)
			{
				case "NightAdventure_NobleGame":             link.l1.go = "NightAdventure_NobleGame";  break; // карты
				case "NightAdventure_NobleGameDuel":         link.l1.go = "NightAdventure_NobleGame";  break; 
				case "NightAdventure_NobleWhore": 			 link.l1.go = "NightAdventure_NobleWhore"; break; // жрица
			}
		break;
		// карты
		case "NightAdventure_NobleGame": 
			dialog.text = "Capitaine?.. hic!.. oh, "+GetAddress_Form(NPChar)+" ... Je suis tellement d-désolé... hic !.. pour mon... é-état. Voudriez-vous vous joindre à m-moi ? hic !.. S-s'il vous plaît."; 
			link.l1 = "Désolé, "+GetAddress_Form(NPChar)+", mais je suis occupé."; 
			link.l1.go = "NightAdventure_NobleEnd";
			link.l2 = "Rejoindre ? Je suis désolé, mais je ne bois pas aujourd'hui..."; 
			link.l2.go = "NightAdventure_NobleGame_1";
		break;
		
		case "NightAdventure_NobleGame_1":
			dialog.text = "Oh, tu n'as pas b-besoin... hic!.. de boire! Voilà une chose... Eh bien... J'ai bu avec mon ami... Donc... Je suis déjà éméché... tu vois?";
			link.l1 = "D'accord. Alors, as-tu besoin d'aide pour dégriser?";
			link.l1.go = "NightAdventure_NobleGame_2";
		break;
		
		case "NightAdventure_NobleGame_2": 
			dialog.text = "Pas vraiment ! Je suis bien. Maintenant je veux j-jouer... aux cartes, en général je veux jouer... hic !.. M-mais pas pour des misérables... p-pesos... avec ces vauriens dans... hic !.. l'auberge... Mais avec un vrai noble ! hic !.. Pour de vrais enjeux !.."; 
			link.l1 = "Désolé, "+GetAddress_Form(NPChar)+", que puis-je dire... Je ne suis pas un adepte du jeu. Il faut payer les salaires des marins, entretenir le navire, tu sais..."; 
			link.l1.go = "NightAdventure_NobleEnd";
			link.l2 = "Hmm, d'accord, jouons. Allons-nous à la taverne ?"; 
			link.l2.go = "NightAdventure_NobleGame_3";
		break;
		
		case "NightAdventure_NobleGame_3": 
			dialog.text = "Très bien ! Juste... hic !.. lentement, s'il vous plaît. Je ne suis... hic !.. pas... capable de... me tenir debout..."; 
			link.l1 = "Très bien, avançons lentement."; 
			link.l1.go = "NightAdventure_NobleGame_4";
		break;
		
		case "NightAdventure_NobleGame_4":
			DialogExit();
			NPChar.Dialog.currentnode = "NightAdventure_NobleTownAgain"; 
			pchar.GenQuest.CantRun = true; // ме-е-едленно ))
			bDisableFastReload = true; // ножками
			LAi_SetActorType(pchar);
			LAi_SetPlayerType(pchar); // обновить для ходьбы
			pchar.GenQuest.NightAdventureNode =  "NightAdventure_NobleGame_5"; // для выбора диалога
			LAi_SetActorType(npchar);
			LAi_ActorFollowEverywhere(npchar, "", -1);
			LAi_Actor2WaitDialog(npchar, pchar);
			SetFunctionLocationCondition("NightAdventure_Intavern", npchar.City+"_tavern", true);
			SetFunctionLocationCondition("NightAdventure_JungleExit", npchar.City+"_Exittown", false);
			pchar.quest.NightAdventure_SeaExit.win_condition.l1 = "EnterToSea";
			pchar.quest.NightAdventure_SeaExit.function = "NightAdventure_SeaExit";
		break;
		
		case "NightAdventure_NobleGame_5": 
			pchar.quest.NightAdventure_Intavern.over = "yes";
			FreeSitLocator(pchar.location, "sit_front4");
			FreeSitLocator(pchar.location, "sit_base4");
			dialog.text = "Po-pour cette table... hip !.. allons-y !"; 
			link.l1 = "Bien, allons-y."; 
			link.l1.go = "NightAdventure_NobleGame_6";
		break;
		
		case "NightAdventure_NobleGame_6": 
			DialogExit();
			//if(CheckAttribute(pchar, "IsMushketer")) SetMainCharacterToMushketer("", false);
			LAi_Fade("NightAdventure_NobleGameDialogPrep", "NightAdventure_NobleGameDialog");
		break;
		
		case "NightAdventure_NobleGame_7": 
			dialog.text = "Vous n'avez pas... idée, c-capitaine, combien... hic !.. combien je suis heureux de rencontrer un vrai noble ! hic !.. Dans ce désert... d'habitude seulement... hic !.. d-déchets..."; 
			link.l1 = "Oui, c'est monnaie courante dans les colonies locales. Eh bien, allons-nous jouer ?"; 
			link.l1.go = "NightAdventure_NobleGame_8";
		break;
		
		case "NightAdventure_NobleGame_8": 
			dialog.text = "Oui, jouons ! hic !.. Quels paris ?.."; 
			if(sti(pchar.money) > 10000)
			{
				link.l1 = "Nous jouons pour 1000 pesos."; 
				link.l1.go = "NightAdventure_NobleGame_9_1";
			}
			if(sti(pchar.money) > 20000)
			{
				link.l2 = "Nous jouons pour 2000 pesos."; 
				link.l2.go = "NightAdventure_NobleGame_9_2";
			}
			link.l3 = "Hmm, je suis désolé, il semble que ma poche soit vide en ce moment..."; 
			link.l3.go = "NightAdventure_NobleGame_Голодранец";
		break;
		
		case "NightAdventure_NobleGame_Голодранец": 
			dialog.text = "Q-quoi?.. Tu n'as... hic !.. pas d'argent pour jouer... avec moi ?.."; 
			link.l1 = "Eh bien, ça arrive. Nous jouerons la prochaine fois, ne t'inquiète pas."; 
			link.l1.go = "NightAdventure_NobleGame_Голодранец_1";
		break;
		
		case "NightAdventure_NobleGame_Голодранец_1": 
			DialogExit();
			SetFunctionExitFromLocationCondition("NightAdventure_KillPhant", pchar.location, false);
			chrDisableReloadToLocation = false; // открыть локацию
			LAI_SetPlayerType(pchar);           
			DoQuestReloadToLocation(pchar.location, "tables", "stay4", "");
			ChangeCharacterAddressGroup(npchar, "none", "", "");
		break;
		
		case "NightAdventure_NobleGame_9_1": 
			DialogExit();
			npchar.money = 15000;
			pchar.questTemp.NA.Cards = true; 
			pchar.GenQuest.Cards.npcharIdx = npchar.index;
			pchar.GenQuest.Cards.iRate     = 1000; 
			LaunchCardsGame();
		break;
		
		case "NightAdventure_NobleGame_9_2": 
			DialogExit();
			npchar.money = 30000;
			pchar.questTemp.NA.Cards = true; 
			pchar.GenQuest.Cards.npcharIdx = npchar.index;
			pchar.GenQuest.Cards.iRate     = 2000; 
			LaunchCardsGame();
		break;
		
		case "NightAdventure_NobleGame_Win": 
			DeleteAttribute(pchar, "questTemp.NA.Cards.Win");
			dialog.text = "Hic!.. J'ai passé un bon moment, c-capitaine! hic!.."; 
			link.l1 = "Je suis d'accord avec toi. Au moins, fais une pause dans les affaires."; 
			link.l1.go = "NightAdventure_NobleGame_HappyEnd";
		break;
		
		case "NightAdventure_NobleGame_Lose": 
			DeleteAttribute(pchar, "questTemp.NA.Cards.Fail");
			dialog.text = "Hic!.. J'ai passé un bon moment, c-capitaine ! hic!.."; 
			link.l1 = "Je suis d'accord avec toi. Prends au moins une pause des affaires."; 
			link.l1.go = "NightAdventure_NobleGame_Lose_1";
		break;
		
		case "NightAdventure_NobleGame_Lose_1": 
			dialog.text = "Parfois, il suffit de... hic!.. passer du temps avec une bonne... hic!.. compagnie. Merci beaucoup... hic!.. pour ta compagnie !"; 
			if(pchar.GenQuest.NightAdventureVar == "NightAdventure_NobleGameDuel")
			{		
				link.l1 = "Oui, je viens de perdre en miettes. Et comment se fait-il que tu gagnes même dans ces cas où j'avais toutes les chances de gagner ?"; 
				link.l1.go = "NightAdventure_NobleGame_Duel";
				break;
			}	
			link.l1 = "Mutuellement, merci pour le jeu et pour la conversation."; 
			link.l1.go = "NightAdventure_NobleGame_HappyEnd_1";
		break;
		
		case "NightAdventure_NobleGame_HappyEnd": 
			dialog.text = "Parfois, il suffit de... hic!.. p-passer du temps avec une agréable... hic!.. compagnie. Merci beaucoup... hic!.. pour votre compagnie!"; 
			link.l1 = "Mutuellement, merci pour le jeu et pour la conversation."; 
			link.l1.go = "NightAdventure_NobleGame_HappyEnd_1";
		break;
		
		case "NightAdventure_NobleGame_HappyEnd_1":
			DialogExit();
			DeleteAttribute(pchar, "questTemp.NA.Cards");
			SetFunctionExitFromLocationCondition("NightAdventure_KillPhant", pchar.location, false);
			chrDisableReloadToLocation = false; // открыть локацию
			LAI_SetPlayerType(pchar);           
			DoQuestReloadToLocation(pchar.location, "tables", "stay4", "");
			ChangeCharacterAddressGroup(npchar, "none", "", "");
		break;
		
		case "NightAdventure_NobleGame_Duel": 
			dialog.text = "Juste de la chance, c-capitaine... hic!.."; 
			link.l1 = "Ça ne ressemble pas juste à de la chance...."; 
			link.l1.go = "NightAdventure_NobleGame_Duel_1";
		break;
		
		case "NightAdventure_NobleGame_Duel_1": 
			dialog.text = "Que veux-tu insinuer ? Veux-tu dire que j'ai joué de manière malhonnête ? Tu as tout vu toi-même, nous avons pris les cartes du même paquet !"; 
			link.l1 = "Oui, j'ai vu. Et j'ai aussi vu qu'il y a une minute, ta langue bougeait à peine, et maintenant tu parles comme si tu n'étais pas saoul."; 
			link.l1.go = "NightAdventure_NobleGame_Duel_2";
		break;
		
		case "NightAdventure_NobleGame_Duel_2": 
			dialog.text = "Ah, damnation ! Et vous m'avez bien attrapé ! Soit, j'avoue, je ne vais pas me cacher. Je n'étais pas ivre. Mais savez-vous à quel point les gens se laissent berner par ces soi-disant riches et ivrognes qui veulent jouer aux cartes ? Tous ceux qui ont quelque chose à parier se précipitent presque en premier à la taverne pour obtenir rapidement un gain indubitablement grand d'un noble indubitablement riche mais ivre. Permettez-moi de dire que vous êtes le premier à percer mon secret."; 
			link.l1 = "Alors, et maintenant ? Allez-vous me rendre mon argent à l'amiable ?"; 
			link.l1.go = "NightAdventure_NobleGame_Duel_3";
		break;
		
		case "NightAdventure_NobleGame_Duel_3": 
			dialog.text = "Ha ha ha, ne me fais pas rire, capitaine. Bien sûr, je ne vous rembourserai rien ! Et ne pensez pas que vous pouvez m'y contraindre. Je peux facilement jouer le rôle d'un noble respecté qui se fait rabrouer par un capitaine errant. Alors mon conseil pour vous est : acceptez votre défaite et partez simplement."; 
			link.l1 = "Eh bien, je vous souhaite sincèrement de ne pas me croiser dans des circonstances moins favorables, car alors vous ne rirez plus ainsi. Adieu."; 
			link.l1.go = "NightAdventure_NobleGame_HappyEnd_1";
			link.l2 = "Et mon conseil pour toi, essaye de trouver le temps d'obtenir une épée."; 
			link.l2.go = "NightAdventure_NobleGame_Duel_4";
		break;
		
		case "NightAdventure_NobleGame_Duel_4": 
			dialog.text = "Tu n'oserais pas... C'est une taverne, pleine de monde..."; 
			link.l1 = "Alors je suis juste un capitaine errant, qu'est-ce que ça peut me faire des règles de la décence. Et dans la taverne du port la nuit, que peut-il arriver ... Je manie l'épée de bien des façons mieux que toi."; 
			link.l1.go = "NightAdventure_NobleGame_Duel_5";
		break;
		
		case "NightAdventure_NobleGame_Duel_5": 
			dialog.text = "Ah c'est donc comme ça ?! Eh bien, maintenant nous allons vérifier qui le possède mieux !"; 
			link.l1 = "À votre service..."; 
			link.l1.go = "NightAdventure_NobleGame_Duel_6";
		break;
		
		case "NightAdventure_NobleGame_Duel_6": 
			DeleteAttribute(pchar, "questTemp.NA.Cards");
			SetFunctionLocationCondition("NightAdventure_KillPhant", NPChar.City+"_town", false);
			npchar.money = 0;
			AddMoneyToCharacter(npchar, makeint(pchar.GenQuest.NightAdventure_money));
			GiveItem2Character(npchar, "totem_13");
			npchar.SaveItemsForDead   = true; // сохранять на трупе вещи
			npchar.DontClearDead = true;  // не убирать труп через 200с
			chrDisableReloadToLocation = false; // открыть локацию
			PChar.questTemp.duel.enemy = NPChar.id;
			AddDialogExitQuestFunction("Duel_Prepare_Fight");
			DialogExit();
		break;
		// жрица
		case "NightAdventure_NobleWhore": 
			dialog.text = "Capitaine?.. hic!.. oh, "+GetAddress_Form(NPChar)+" ... j-je suis tellement d-désolé... hic !.. pour ma... c-condition. Pouvez-vous m'aider ? hic !.. S-s'il vous plaît."; 
			link.l1 = "Désolé, "+GetAddress_Form(NPChar)+", mais je suis occupé."; 
			link.l1.go = "NightAdventure_NobleEnd";
			link.l2 = "Oh... j'écoute."; 
			link.l2.go = "NightAdventure_NobleWhore_1";
		break;
		
		case "NightAdventure_NobleWhore_1": 
			dialog.text = "C'est une chose... En général... Je suis... déjà éméché... Tu peux voir... hic !.. oui ?"; 
			link.l1 = "Pour être honnête, oui. As-tu besoin d'aide pour dégriser?"; 
			link.l1.go = "NightAdventure_NobleWhore_2";
		break;
		
		case "NightAdventure_NobleWhore_2": 
			dialog.text = "Pas vraiment ! Je vais b-bien. Je veux une dame. Mais je suis si s-saoûl... hic !.. La d-dame me virera, donc. Pourriez-vous... hic !... n-négocier pour moi ? Je donnerai de l'argent."; 
			link.l1 = "Je suis désolé, "+GetAddress_Form(NPChar)+", mais comment te dire... Je ne vais pas aux bordels. Honneur, réputation... tu sais ..."; 
			link.l1.go = "NightAdventure_NobleEnd";
			link.l2 = "D'accord, je vais t'aider."; 
			link.l2.go = "NightAdventure_NobleWhore_3";
		break;
		
		case "NightAdventure_NobleWhore_3": 
			dialog.text = "Juste... hic !.. lentement, s'il vous plaît. Je ne suis pas... hic !.. capable de... me tenir debout..."; 
			link.l1 = "D'accord, allons-y lentement."; 
			link.l1.go = "NightAdventure_NobleWhore_4";
		break;
		
		case "NightAdventure_NobleWhore_4":
			DialogExit();
			if(npchar.city != "Charles" || npchar.city != "Tortuga") // вход только с парадного
			{
				LocatorReloadEnterDisable(npchar.city+"_town", "reload91", true);
			}
			NPChar.Dialog.currentnode = "NightAdventure_NobleTownAgain"; 
			pchar.GenQuest.CantRun = true; // ме-е-едленно ))
			bDisableFastReload = true; // ножками
			LAi_SetActorType(pchar);
			LAi_SetPlayerType(pchar); // обновить для ходьбы
			pchar.GenQuest.NightAdventure_money = 3000+(rand(4)*500);
			pchar.GenQuest.NightAdventureNode =  "NightAdventure_NobleWhore_5"; // для выбора диалога
			LAi_SetActorType(npchar);
			LAi_ActorFollowEverywhere(npchar, "", -1);
			LAi_Actor2WaitDialog(npchar, pchar);
			SetFunctionLocationCondition("NightAdventure_InBrothel", npchar.City+"_Brothel", false);
			SetFunctionLocationCondition("NightAdventure_JungleExit", npchar.City+"_Exittown", false);
			pchar.quest.NightAdventure_SeaExit.win_condition.l1 = "EnterToSea";
			pchar.quest.NightAdventure_SeaExit.function = "NightAdventure_SeaExit";
		break;
		
		case "NightAdventure_NobleWhore_5": 
			pchar.GenQuest.NightAdventureVar = "NightAdventure_NobleWhoreMoney";
			AddMoneyToCharacter(pchar, 5000);
			dialog.text = "Voici l'argent... hic !... Je t'attendrai i-ici."; 
			link.l1 = "Bien, je reviendrai bientôt."; 
			link.l1.go = "NightAdventure_NobleWhore_6";
		break;
		
		case "NightAdventure_NobleWhore_6": 
			LAi_SetCitizenType(npchar);
			chrDisableReloadToLocation = false;
			LocatorReloadEnterDisable(npchar.city + "_Brothel", "reload1_back", true); 
			LocatorReloadEnterDisable(npchar.city + "_SecBrRoom", "reload2", true); 
			NPChar.Dialog.currentnode = "NightAdventure_NobleBrothelAgain";
			dialog.text = "J-j-juste... amène-moi... hic !.. le... meilleur !.. Oui..."; 
			link.l1 = "Très bien, d'accord, j'ai compris."; 
			link.l1.go = "exit";
		break;
		
		case "NightAdventure_NobleWhore_7": // заказ исполнен
			dialog.text = "Hic!.. Combien de temps encore ?"; 
			link.l1 = "La meilleure fille de cette colonie t'attend à l'étage."; 
			link.l1.go = "NightAdventure_NobleWhore_8";
		break;
		
		case "NightAdventure_NobleWhore_8": 
			dialog.text = "Oui!.. Ce soir... est magnifique... M-merci, "+GetAddress_Form(NPChar)+". Le reste de l'argent... hic !... prends-le. Et je sombre... dans... ma..... beeeelle... dam-daame...";
			link.l1 = "Eh bien, amuse-toi bien."; 
			link.l1.go = "NightAdventure_NobleWhore_9";
		break;
		
		case "NightAdventure_NobleWhore_9": 
			DialogExit();
			chrDisableReloadToLocation = true; // закрыть пока бежит
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload2_back", "", "", "", "NightAdventure_OpenBrothel", -1);
		break;
		
		case "NightAdventure_NobleBrothelAgain":
			NextDiag.TempNode = "NightAdventure_NobleBrothelAgain";
			dialog.text = "Hic !.. Combien de temps encore ?";
			link.l1 = "Je négocierai bientôt, sois patient.";
			link.l1.go = "exit";
		break;
		
		case "NightAdventure_NobleEnd":
			DialogExit();
			SetFunctionExitFromLocationCondition("NightAdventure_KillPhant", pchar.location, false);
			NPChar.Dialog.currentnode = "NightAdventure_NobleEndAgain";
		break;
		
		case "NightAdventure_NobleEndAgain":
			NextDiag.TempNode = "NightAdventure_NobleEndAgain";
			dialog.text = "Hic!.. ";
			link.l1 = "Tu as besoin de dormir.";
			link.l1.go = "exit";
		break;
		
		case "NightAdventure_NobleTownAgain":
			dialog.text = "Hic!.. Oui... est-ce encore loin?..";
			link.l1 = "Nous y sommes presque, sois patient.";
			link.l1.go = "exit";
			NextDiag.TempNode = "NightAdventure_SailorAgain";
			LAi_SetActorType(npchar);
			LAi_ActorFollowEverywhere(npchar, "", -1);
			LAi_Actor2WaitDialog(npchar, pchar);
		break;
		// <-- ночной приключенец
		
		// belamour квест на получение фонаря Xenon -->
		case "CemeteryMan":
			dialog.text = "Quoi? Qui êtes-vous? Que faites-vous ici?";
			link.l1 = "Je pourrais vous poser la même question.";
			link.l1.go = "CemeteryMan_1";
		break;
		
		case "CemeteryMan_1":
			dialog.text = "Nous ? Oh, nous... euh... Nous cueillons des fleurs ici...";
			link.l1 = "Des fleurs de tombe ? Eh bien, comment se présente l'herbier ?";
			link.l1.go = "CemeteryMan_2";
		break;
		
		case "CemeteryMan_2":
			dialog.text = "Elle... Cela a-t-il un rapport avec les herbes ?";
			link.l1 = "Alors... Je pense que je comprends ce qui se passe ici.";
			link.l1.go = "CemeteryMan_3";
		break;
		
		case "CemeteryMan_3":
			dialog.text = "Nous ne sommes pas des maraudeurs ! Ne parle pas de nous comme ça ! Nous sommes juste...";
			link.l1 = "Juste quoi ?";
			link.l1.go = "CemeteryMan_4";
		break;
		
		case "CemeteryMan_4":
			dialog.text = "Eh bien, nous... Mon père nous interdit de nous voir ! Et son père aussi ! Alors nous... nous cherchions un endroit sans témoins. Pour être seuls. La serrure de la porte est de toute façon cassée, donc c'est facile d'entrer ici...";
			link.l1 = "Je comprends maintenant d'où venaient ces gémissements effrayants de l'âme tourmentée...";
			link.l1.go = "CemeteryMan_5";
		break;
		
		case "CemeteryMan_5":
			DialogExit();
			sld = characterFromId("CemeteryCouple_2");
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.3);
		break;
		
		case "CemeteryMan_6":
			dialog.text = "Eh bien, si vous avez tout compris, peut-être que vous nous laisserez tranquilles ?";
			link.l1 = "N'as-tu pas peur d'organiser tes rendez-vous dans une crypte ? Pas le meilleur endroit...";
			link.l1.go = "CemeteryMan_7";
		break;
		
		case "CemeteryMan_7":
			dialog.text = "Nous ne sommes pas superstitieux ! Et même si c'était effrayant - quel choix avons-nous ? En ville, les parents l'auraient su tout de suite. Mais ici, personne ne nous dénoncera. Donc, pour l'instant, c'est la meilleure option.";
			link.l1 = "Je suis vraiment désolé, mais pourriez-vous chercher un autre endroit ? Ne vous méprenez pas, je comprends tout - la jeunesse et tout ça - mais vos rendez-vous ont effrayé le gardien du cimetière à mort, avec tous ces bruits et gémissements venant de la crypte chaque nuit.";
			link.l1.go = "CemeteryMan_8";
		break;
		
		case "CemeteryMan_8":
			dialog.text = "Eh bien... Effrayer la garde n'était pas prévu dans notre plan. Mais alors, où pouvons-nous nous rencontrer ? Ou suggères-tu que nous ayons nos rendez-vous sous le ciel ouvert ?";
			link.l1 = "L'amour ne connaît pas de frontières. Trouvez un autre endroit où vous ne dérangerez sûrement personne. Alors personne ne vous dérangera. Probablement. Et il vaut mieux régler les choses avec vos parents - vous ne comptez pas vous cacher pour toujours, n'est-ce pas ?";
			link.l1.go = "CemeteryMan_9";
		break;
		
		case "CemeteryMan_9":
			dialog.text = "Fine, we'll think of something... We won't be scaring the guard anymore; you have my word.";
			link.l1 = "Merveilleux. Bonne chance à vous !";
			link.l1.go = "CemeteryMan_10";
		break;
		
		case "CemeteryMan_10":
			sld = characterFromId("CemeteryCouple_1");
			sld.lifeDay = 0;
			ChangeCharacterAddressGroup(sld, "none", "", "");
			sld = characterFromId("CemeteryCouple_2");
			sld.lifeDay = 0;
			ChangeCharacterAddressGroup(sld, "none", "", "");
			pchar.questTemp.Lantern = "ToKeeper";
			DeleteAttribute(pchar,"questTemp.Lantern.nation");
			chrDisableReloadToLocation = false;
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
			AddQuestRecord("NoiseCemetery", "2");
			DialogExit();
		break;
		
		case "CemeteryGirl":
			dialog.text = "Quoi?!";
			link.l1 = "Oh, rien...";
			link.l1.go = "CemeteryGirl_1";
		break;
		
		case "CemeteryGirl_1":
			DialogExit();
			sld = characterFromId("CemeteryCouple_1");
			sld.dialog.currentnode = "CemeteryMan_6";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.3);
		break;
		// <-- квест на получение фонаря 

		//замечание по обнажённому оружию от персонажей типа citizen // лесник вставил в ген.квесты чтобы не было пустого диалога .
		case "CitizenNotBlade":
			dialog.text = NPCharSexPhrase(NPChar,"Ecoute, je suis citoyen de la ville et je te demanderais de baisser ton épée.","Ecoute, je suis citoyen de la ville et je te demanderais de ranger ta lame.");
			link.l1 = LinkRandPhrase("D'accord.","Comme vous voulez...","Comme tu dis...");
			link.l1.go = "exit";
		break;																																																				  
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			break;
	}
}

void ChurchGenQuest2_GiveCup()
{
	AddItems(PChar, "Bible", 1);
	ref rItem = ItemsFromID("Bible");
	rItem.Name = "itmname_ChurchGenQuest2Cup"; // rItem.Name = "itmname_bible";
	rItem.City = XI_ConvertString("Colony" + PChar.GenQuest.ChurchQuest_2.QuestTown + "Gen");
	rItem.Weight = 15.0; // rItem.Weight = 2;
	rItem.picIndex = 13; // itm.picIndex = 6;
	rItem.picTexture = "ITEMS_31"; // itm.picTexture = "ITEMS_9";
	ChangeItemDescribe("Bible", "itmdescr_ChurchGenQuest2Cup");
}

// Для генера "Пираты на необитаемом острове"
String PiratesOnUninhabited_GetStringNum(int _num)
{
	String retValue = "";
	
	switch(_num)
	{
		case 5: retValue = "five"; break;
		case 6: retValue = "six"; break;
		case 7: retValue = "seven"; break;
		case 8: retValue = "eight"; break;
		case 9: retValue = "nine"; break;
		case 10: retValue = "ten"; break;
	}
	
	return retValue;
}

int PiratesOnUninhabited_GenerateShipType()
{
	int rank = sti(PChar.rank);
	int retShipType;
	
	if(rank < 5)
	{
		switch(hrand(1))
		{
			case 0: retShipType = SHIP_LUGGER; break;
			case 1: retShipType = SHIP_SLOOP; break;
		}
	}
	
	if(rank >= 5 && rank < 20)
	{
		switch(hrand(3))
		{
			case 0: retShipType = SHIP_SLOOP; break;
			case 1: retShipType = SHIP_BRIGANTINE; break;
			case 2: retShipType = SHIP_SCHOONER_W; break;
			case 3: retShipType = SHIP_BRIG; break;
		}
	}
	
	if(rank >= 20)
	{
		switch(hrand(2))
		{
			case 0: retShipType = SHIP_CORVETTE; break;
			case 1: retShipType = SHIP_GALEON_H; break;
			case 2: retShipType = SHIP_FRIGATE; break;
		}
	}
	
	return retShipType;
}

String PiratesOnUninhabited_GenerateTreasureShore(ref _boxId)
{
	String retShoreId;
	
	switch(hrand(4))
	{
		case 0:
			retShoreId = "Shore9";
			_boxId = "box1";
		break;
		
		case 1:
			retShoreId = "Shore55";
			_boxId = "box" + (1 + rand(1)); // Сундук пусть рандомится и при с/л
		break;
	
		case 2:
			retShoreId = "Shore_ship1";
			_boxId = "box" + (1 + rand(1)); // Сундук пусть рандомится и при с/л
		break;
		
		case 3:
			retShoreId = "Shore_ship2";
			_boxId = "box" + (1 + rand(1)); // Сундук пусть рандомится и при с/л
		break;
		
		case 4:
			retShoreId = "Shore_ship3";
			_boxId = "box" + (1 + rand(1)); // Сундук пусть рандомится и при с/л
		break;
	}
	
	return retShoreId;
}

void PiratesOnUninhabited_SetCapToMap()
{
	int temp;
	String group = "PiratesOnUninhabited_SeaGroup";
	ref character = GetCharacter(NPC_GenerateCharacter("PiratesOnUninhabited_BadPirate", "", "man", "man", sti(pchar.rank) + 5, PIRATE, -1, true, "soldier"));		
	character.Ship.Type = GenerateShipExt(sti(PChar.GenQuest.PiratesOnUninhabited.StartShipType), true, character);
	character.Ship.Name = PChar.GenQuest.PiratesOnUninhabited.StartShipName;
    SetBaseShipData(character);
    SetCrewQuantityFull(character);
    Fantom_SetCannons(character, "pirate");
    Fantom_SetBalls(character, "pirate");
	Fantom_SetUpgrade(character, "pirate");
	
	character.Ship.Mode = "pirate";	
	SetCaptanModelByEncType(character, "pirate");

	DeleteAttribute(character, "SinkTenPercent");
	DeleteAttribute(character, "SaveItemsForDead");
	DeleteAttribute(character, "DontClearDead");
	DeleteAttribute(character, "AboardToFinalDeck");
	DeleteAttribute(character, "SinkTenPercent");
	
	character.AlwaysSandbankManeuver = true;
	character.AnalizeShips = true;  //анализировать вражеские корабли при выборе таска
	character.DontRansackCaptain = true; //не сдаваться
	
	SetAllPerksToChar(character, false);
	
	Group_FindOrCreateGroup(group);
	Group_SetTaskAttackInMap(group, PLAYER_GROUP);
	Group_LockTask(group);
	Group_AddCharacter(group, character.id);
	Group_SetGroupCommander(group, character.id);
	SetRandGeraldSail(character, PIRATE);
	
	character.fromCity = SelectAnyColony(""); // Колония, из бухты которой выйдет
	character.fromShore = GetIslandRandomShoreId(GetArealByCityName(character.fromCity));
	character.toCity = SelectAnyColony(character.fromCity); // Колония, в бухту которой придёт
	character.toShore = GetIslandRandomShoreId(GetArealByCityName(character.toCity));
	
	character.mapEnc.type = "trade";
	character.mapEnc.worldMapShip = "quest_ship";
	character.mapEnc.Name = LowerFirst(XI_ConvertString(ShipsTypes[sti(PChar.GenQuest.PiratesOnUninhabited.StartShipType)].name)) + " '" + PChar.GenQuest.PiratesOnUninhabited.StartShipName + "'";
	
	Map_CreateTrader(character.fromShore, character.toShore, "PiratesOnUninhabited_BadPirate", GetMaxDaysFromIsland2Island(GetArealByCityName(character.toCity), GetArealByCityName(character.fromCity)) + 3);
	
	temp = GetCharacterFreeSpace(character, GOOD_SLAVES); // Сколько влезет рабов
	AddCharacterGoodsSimple(character, GOOD_SLAVES, makeint(temp / 2 + hrand(temp / 2)) - 1);
	
	PChar.Quest.PiratesOnUninhabited_ShipSink.win_condition.l1 = "Character_sink";
	PChar.Quest.PiratesOnUninhabited_ShipSink.win_condition.l1.character = "PiratesOnUninhabited_BadPirate";
	PChar.Quest.PiratesOnUninhabited_ShipSink.function = "PiratesOnUninhabited_ShipSink";
	
	Log_TestInfo("Pirates on an uninhabited island: cap left " + character.fromCity + " and went to: " + character.toShore);
}
// belamour gen количество каторжан прописью -->
String Convict_GetStringNum(int iCQTY)
{
	String ConvictStr = "";
	
	switch(iCQTY)
	{
		case 2: ConvictStr = "two"; break;
		case 3: ConvictStr = "three"; break;
		case 4: ConvictStr = "four"; break;
		case 5: ConvictStr = "five"; break;
		case 6: ConvictStr = "six"; break;
		case 7: ConvictStr = "seven"; break;
	}
	
	return ConvictStr;
}
// <-- gen
