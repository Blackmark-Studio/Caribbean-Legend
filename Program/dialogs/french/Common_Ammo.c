// диалог коменданта форта
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

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

    // вызов диалога по городам -->
   /*NPChar.FileDialog2 = "DIALOGS\" + LanguageGetLanguage() + "\Prison\" + NPChar.City + "_Prison.c";
    if (LoadSegment(NPChar.FileDialog2))
	{
        ProcessCommonDialog(NPChar, Link, NextDiag);
		UnloadSegment(NPChar.FileDialog2);
	}*/
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
		
		case "First time":
			location = &Locations[FindLocation(pchar.location)];
			if (rand(4) == 4 && GetNpcQuestPastDayParam(location, "gun_date") > 365 && !CheckAttribute(pchar, "questTemp.PrisonGun"))
			{
				dialog.text = RandPhraseSimple(RandPhraseSimple("Écoutez, j'ai une affaire importante avec vous. J'espère que vous pourrez aider.","Capitaine, puis-je vous intéresser avec une offre assez rentable?"),RandPhraseSimple("Je pense que vous pourriez nous aider dans une affaire importante.","Capitaine, j'ai une offre délicate pour vous, qui pourrait être assez profitable pour nous deux."));					
				link.l1 = "Eh bien, parle, et nous verrons...";
				link.l1.go = "GiveTaskGun";
				location.quest.PrisonGun = "Target"; 
				SaveCurrentNpcQuestDateParam(location, "gun_date");
				break;
			}
		
			dialog.text = RandPhraseSimple("Je suis le commandant du fort. Que cherchez-vous ici ?","De quoi as-tu besoin? Pourquoi es-tu venu ici?");
			link.l1 = "Oh, rien, juste en train de regarder autour de la ville et ses environs. Je suis venu ici juste par un coup de chance.";
			//belamour legendary edition диалоги, если герой имеет звания и заслуги перед отечеством -->
			// Офицер с патентом
			if(IsOfficerFullEquip())
			{
				dialog.text = "Bienvenue au fort, capitaine. Avez-vous besoin de quelque chose?";
				link.l1 = "Non, rien, juste passé par hasard.";
			}
			// вице-адмирал
			if(isMainCharacterPatented() && sti(Items[sti(pchar.EquipedPatentId)].TitulCur) > 4 && npchar.nation == sti(Items[sti(pchar.EquipedPatentId)].Nation))
			{
				dialog.text = "Salutations Vice-Amiral ! Avez-vous des ordres ?";
				link.l1 = "Non, officier, pas d'ordres. Je suis juste venu voir le fort.";
			}
			// генерал-губернатор
			if(CheckAttribute(pchar, "questTemp.Patria.GenGovernor") && npchar.nation == FRANCE)
			{
				dialog.text = "Gouverneur Général, Votre Grâce! J'ai l'ordre complet dans le fort. Y aura-t-il des ordres?";
				link.l1 = "Je suis content que tu ailles bien, officier. Pas d'ordres, je suis juste venu vérifier le fort.";
			}
			// <-- legendary edition
			link.l1.go = "exit";
			//Jason --> мини-квест Дефицитный товар
			if (CheckAttribute(pchar, "questTemp.Wine.bottle") && NPChar.location == pchar.questTemp.Wine.City + "_ammo" && GetQuestPastDayParam("questTemp.Wine_bottle") < 5)
			{
				link.l11 = "J'ai une information intéressante pour vous, officier. Un de vos soldats, "+pchar.questTemp.Wine.SName+" m'a demandé d'acheter du vin en ville par ma médiation. Compte tenu de vos ordres...";
				link.l11.go = "Wine_prison";
			}
			// <-- мини-квест Дефицитный товар
			// Карибские нравы
			if (CheckAttribute(pchar, "questTemp.Trial") && pchar.questTemp.Trial == "fraht" && NPChar.location == "portpax_ammo")
			{
				link.l11 = "Bonjour, officier. Je viens de la colonie de Basse-Terre, sur ordres d'un homme du nom de Gerard LeCroix. Il y a une cargaison de poudre à canon et de bombes pour vous dans ma cale...";
				link.l11.go = "trial";
			}
			// Опасный груз -->
			if (pchar.location == "Cumana_Ammo")
			{
				if (pchar.questTemp.zpq != "begin" && pchar.questTemp.zpq != "failed" && pchar.questTemp.zpq != "completed")
				{
					link.l2 = "Vous avez l'air inquiet, officier. Comment puis-je vous aider?";
					link.l2.go = "zpq_prs1";
				}
				if (pchar.questTemp.zpq == "begin" && GetSquadronGoods(pchar, GOOD_POWDER) >= 15000 && GetQuestPastDayParam("pchar.questTemp.zpq") >= 7)
				{
					link.l3 = "Je suis prêt à signaler que toute la cargaison de poudre à canon est livrée. Mon navire est prêt pour le déchargement.";
					link.l3.go = "zpq_ex";
				}
				if (pchar.questTemp.zpq == "begin")
				{
					link.l4 = "Je veux annuler notre accord sur la poudre à canon. C'est trop problématique.";
					link.l4.go = "zpq_fld2";
				}
			}
			// <-- Опасный груз
			NextDiag.TempNode = "First time";
		break;

		// --> Орудия для форта
		case "GiveTaskGun":
			dialog.Text = LinkRandPhrase("Vous voyez, les canons du fort sont assez usés. Le trésor a attribué des fonds pour les remplacer, mais je n'ai simplement aucune idée d'où acheter les nouveaux : il n'y a tout simplement aucun moyen de les trouver dans notre colonie en quantité requise. Alors, j'ai pensé que les canons des navires que vous avez abordés pourraient être très utiles pour nous ici.","J'ai besoin de remplacer la batterie de canon du fort. Les fonds ont déjà été alloués, mais, tu sais... Il est tout simplement impossible d'acheter la quantité nécessaire dans notre colonie.","On m'a chargé de remplacer les canons usés du fort, mais je ne semble tout simplement pas en trouver assez nulle part.");
			Link.l1 = "Hmm... Pouvez-vous entrer dans un peu plus de détails ? Calibre, quantité, prix ?";
			Link.l1.go = "GiveTaskGun_1";
			pchar.questTemp.PrisonGun = true;
			SaveCurrentQuestDateParam("pchar.questTemp.PrisonGun");
		break;
			
		case "GiveTaskGun_1":
			GetGunType();
			pchar.questTemp.PrisonGun.Sum = makeint(sti(pchar.questTemp.PrisonGun.Price)*sti(pchar.questTemp.PrisonGun.Qty));
			pchar.questTemp.PrisonGun.Luck = rand(4);
			pchar.questTemp.PrisonGun.Id = npchar.location;
			dialog.Text = "J'ai besoin "+pchar.questTemp.PrisonGun.Text+", dans la quantité de "+sti(pchar.questTemp.PrisonGun.Qty)+"  unités exactement. Je vais payer en doublons d'or, "+sti(pchar.questTemp.PrisonGun.Price)+" pour une pièce. Cela s'élèvera à "+FindRussianDublonString(sti(pchar.questTemp.PrisonGun.Sum))+" au total. Que diras-tu ? Oh, et encore une chose - j'accepterai la totalité du lot, mais pas avant un mois - l'argent n'est pas encore arrivé.";
			Link.l1 = RandPhraseSimple("Non, officier, votre offre ne m'a pas du tout intéressé... Je suis désolé.","C'est tentant, mais je pense que je suis dehors. Permettez-moi de garder mes raisons pour moi-même.");
			Link.l1.go = "exit_gun";
			Link.l2 = RandPhraseSimple("Eh bien, cette offre est certainement intéressante. Considérez que c'est une affaire.","Je suppose que je vais le prendre. Ce n'est pas si difficile et clairement rentable.");
			Link.l2.go = "GiveTaskGun_2";
		break;
			
		case "exit_gun":
			dialog.Text = "Dommage, capitaine, je comptais sur vous. Et... J'espère que cette conversation reste à l'intérieur du fort?";
			Link.l1 = "Vous n'avez pas à me rappeler cela. Mes meilleurs voeux.";
			Link.l1.go = "exit";
			DeleteAttribute(pchar, "questTemp.PrisonGun");
			NextDiag.TempNode = "First time";
		break;
			
		case "GiveTaskGun_2":
			dialog.Text = "Eh bien, alors c'est une affaire! Je ne vous limite pas à certaines conditions, mais s'il vous plaît, essayez de ne pas le prolonger plus d'une demi-année. Et j'espère que vous comprenez que c'est strictement confidentiel?";
			Link.l1 = "Bien sûr que je le fais. Au revoir, commandant.";
			Link.l1.go = "exit";
			ReOpenQuestHeader("PrisonGun");
			AddQuestRecord("PrisonGun", "1");
			AddQuestUserData("PrisonGun", "sSex", GetSexPhrase("",""));
			AddQuestUserData("PrisonGun", "sName", GetFullName(npchar));
			AddQuestUserData("PrisonGun", "sCity", XI_ConvertString("Colony" + npchar.city + "Gen"));
			AddQuestUserData("PrisonGun", "sQty", makeint(pchar.questTemp.PrisonGun.Qty));
			AddQuestUserData("PrisonGun", "sSum", makeint(pchar.questTemp.PrisonGun.Sum));
			AddQuestUserData("PrisonGun", "sText", pchar.questTemp.PrisonGun.Text);
			NextDiag.TempNode = "First time";
		break;	
		
		case "CheckGun":
			if (GetQuestPastDayParam("pchar.questTemp.PrisonGun") < 30)
			{
				dialog.Text = "Je t'ai dit de ne pas venir plus tôt qu'un mois!";
				Link.l1 = "Zut! J'étais tellement occupé"+GetSexPhrase("","")+", que j'ai perdu un"+GetSexPhrase("","")+" piste du temps ... Désolé, je viendrai plus tard, comme convenu.";
				Link.l1.go = "exit";
				NextDiag.TempNode = "First time";
				break;
			}
			if (GetQuestPastDayParam("pchar.questTemp.PrisonGun") > 180)
			{
				dialog.Text = "Hmm... Tu sais, cela fait plus d'une demi-année depuis le jour où nous avons conclu notre 'accord'. J'ai déjà acheté les canons. Pensais-tu vraiment que je t'attendrais éternellement?";
				Link.l1 = "Sacré bleu! Et que suis-je censé faire avec eux maintenant?";
				Link.l1.go = "TakeGun_late";
				break;
			}
			iGunGoods = pchar.questTemp.PrisonGun.Goods;
			amount = GetSquadronGoods(Pchar, iGunGoods) - sti(pchar.questTemp.PrisonGun.Qty);
			sTemp = sti(pchar.questTemp.PrisonGun.Qty);
			iTest = FindColony(NPChar.City); // город
			
			if (iTest != -1)
			{
				rColony = GetColonyByIndex(iTest);
			}
			ok = (rColony.from_sea == "") || (Pchar.location.from_sea == rColony.from_sea);
			if(sti(Pchar.Ship.Type) != SHIP_NOTUSED && ok)
			{
				dialog.Text = "Oui, êtes-vous prêt à m'aider?";
				if (amount < 0)
				{
					Link.l1 = "Non, toujours en cours. Je voulais juste m'assurer que notre accord tient toujours.";
					Link.l1.go = "exit";
				}
				else
				{
					Link.l1 = "Je le suis. Tout le lot est dans la cale - "+sTemp+" unités, comme convenu.";
					Link.l1.go = "TakeGun";
				}
			}
			else 
			{
				dialog.text = "Je ne vois pas votre navire dans le port. Suggérez-vous de traîner ces canons à travers la jungle ? Hâtez-vous à notre port et revenez.";
				link.l1 = "Mon navire est de l'autre côté de l'île. Je le mènerai au port.";
				link.l1.go = "exit";
			}
		break;
		
		case "TakeGun":
			if (pchar.questTemp.PrisonGun.Luck == 4)
			{
				dialog.Text = RandPhraseSimple("Vous savez, c'est vraiment gênant, mais je dois dénoncer notre accord. Nous venons d'avoir une inspection financière, et vous savez combien ils sont scrupuleux dans ces choses. Je ne peux tout simplement rien faire. Désolé.","Capitaine, vous savez... Eh bien, des canons nous ont été envoyés de la métropole, et j'ai été obligé de les racheter, bien sûr. Des prix exorbitants, mais... Je suis vraiment désolé de vous avoir déçu... Je ne me sens pas bien non plus à ce sujet.");
				Link.l1 = "Bon sang! Et qu'est-ce que je suis censé faire avec eux maintenant?";
				Link.l1.go = "TakeGun_no";
			}
			else
			{
				dialog.Text = RandPhraseSimple("Excellent. J'enverrai une escouade de la garnison pour les décharger.","Excellent. Mes soldats vous aideront à décharger les canons.");
				Link.l1 = "Avez-vous préparé le paiement?";
				Link.l1.go = "TakeGun_1";
			}
		break;
		
		case "TakeGun_no":
			dialog.Text = "Je ne sais pas. Vendez-les au chantier naval, équipez un navire de commerce, coulez-les... Je n'ai vraiment aucune idée. Et s'il vous plaît, ne parlez à personne de cet accord.";
			Link.l1 = "Oh, tu dis ça ! Je n'ai tout simplement pas de mots !";
            Link.l1.go = "exit";
			AddQuestRecord("PrisonGun", "3");
			CloseQuestHeader("PrisonGun");
			DeleteAttribute(pchar, "questTemp.PrisonGun");
			NextDiag.TempNode = "First time";
		break;
		
		case "TakeGun_late":
			dialog.Text = "Je n'en ai aucune idée. C'est ton problème. Vends-les, jette-les, coule-les - je m'en fiche vraiment.";
			Link.l1 = "Oh, c'était simplement une perte de temps...";
            Link.l1.go = "exit";
			AddQuestRecord("PrisonGun", "4");
			AddQuestUserData("PrisonGun", "sSex", GetSexPhrase("",""));
			AddQuestUserData("PrisonGun", "sName", GetFullName(npchar));
			CloseQuestHeader("PrisonGun");
			DeleteAttribute(pchar, "questTemp.PrisonGun");
			NextDiag.TempNode = "First time";
		break;
		
		case "TakeGun_1":
			iGunGoods = pchar.questTemp.PrisonGun.Goods;
			amount = sti(pchar.questTemp.PrisonGun.Qty);
			iTemp = sti(pchar.questTemp.PrisonGun.Sum);
			dialog.Text = "Bien sûr. Voici votre or - faites comme bon vous semble.";
			Link.l1 = "Merci! Ce fut un plaisir de faire affaire avec vous!";
            Link.l1.go = "TakeGun_2";
			TakeNItems(pchar, "gold_dublon", iTemp);
			Log_Info("You have received "+FindRussianDublonString(sti(pchar.questTemp.WPU.Escort.Money))+"");
			PlaySound("interface\important_item.wav");
			RemoveCharacterGoods(Pchar, iGunGoods, amount);
		break;
		
		case "TakeGun_2":
			dialog.Text = "Le sentiment est réciproque. Vous avez été très utile. Et, je vous en supplie, gardez cette affaire dans cette pièce.";
			Link.l1 = "Bien sûr. Mes meilleurs voeux à vous.";
            Link.l1.go = "exit";
			AddQuestRecord("PrisonGun", "2");
			AddQuestUserData("PrisonGun", "sSex", GetSexPhrase("",""));
			CloseQuestHeader("PrisonGun");
			DeleteAttribute(pchar, "questTemp.PrisonGun");
			NextDiag.TempNode = "First time";
		break;
		// <-- орудия для форта

		//Jason --> мини-квест Дефицитный товар
		case "Wine_prison":
			dialog.text = "Quoi?! J'ai strictement interdit toute boisson sur le territoire du fort! Eh bien, il devra payer pour cela. Je déduirai 1000 pesos de son paiement et vous les remettrai en récompense de votre vigilance. Et ce gars restera en détention pendant trois jours.";
			link.l1 = "Merci, "+GetAddress_FormToNPC(NPChar)+". Arrêter de telles violations est notre devoir commun.";
			link.l1.go = "exit";
			AddMoneyToCharacter(pchar, 1000);
			ChangeCharacterComplexReputation(pchar,"nobility", -1); 
			DeleteAttribute(pchar, "questTemp.Wine.bottle");
			pchar.quest.Wine_Exchange.over = "yes";//снять прерывание
			pchar.quest.WineTraderQM.over = "yes";//снять прерывание
			WineTraderQMDel();
			sld = characterFromId(pchar.questTemp.Wine.id);
			sld.lifeday = 0;
			CloseQuestHeader("Wine");
			NextDiag.TempNode = "First time";
		break;
		// <-- мини-квест Дефицитный товар
		
		// Карибские нравы
		case "trial":
			iTest = FindColony(NPChar.City); // город
			QuestPointerDelLoc("portpax_town", "reload", "gate_back");
			QuestPointerDelLoc("portpax_exittown", "reload", "reload2_back");
			QuestPointerDelLoc("portpax_fort", "reload", "reload2");
			if (iTest != -1)
			{
				rColony = GetColonyByIndex(iTest);
			}
			ok = (rColony.from_sea == "") || (Pchar.location.from_sea == rColony.from_sea);
			if(sti(Pchar.Ship.Type) != SHIP_NOTUSED && ok)
			{
				if (GetSquadronGoods(pchar, GOOD_BOMBS) < 2500 || GetSquadronGoods(pchar, GOOD_POWDER) < 2500)
				{
					dialog.text = "Hmm. Mais ce lot n'est pas complet ! Comment cela s'est-il passé ?";
					link.l1 = "Zut ! Veuillez me pardonner, c'est ma faute. J'achèterai immédiatement la quantité manquante et vous remettrai le lot entier, comme nous l'avons convenu.";
					link.l1.go = "exit";
				}
				else
				{
					dialog.text = "Alors vous êtes notre courrier? Bien. Réglons les choses avec la cargaison, et ensuite vous recevrez d'autres instructions.";
					link.l1 = "D'accord.";
					link.l1.go = "trial_1";
				}
			}
			else
			{
				dialog.text = "Je ne vois pas votre navire dans le port. Suggérez-vous de traîner la cargaison à travers la jungle? Hâtez-vous à notre port et revenez.";
				link.l1 = "Mon navire est de l'autre côté de l'île. Je le porterai au port.";
				link.l1.go = "exit";
			}
		break;
		
		case "trial_1":
			if(!bImCasual) pchar.quest.Trial_FrahtFail.over = "yes"; // belamour legendary edition если был - снять таймер
			dialog.text = "D'accord, bombes et poudre à canon, 2500 unités chacun... Bon. Les soldats déchargeront la cargaison, vos hommes peuvent prendre une pause. Voici votre paiement pour le fret - cinq mille pesos.";
			link.l1 = "Merci! Que dois-je faire ensuite? Monsieur LeCroix a dit...";
			link.l1.go = "trial_2";
			DelLandQuestMark(npchar);
		break;
		
		case "trial_2":
			AddMoneyToCharacter(pchar, 5000);
			RemoveCharacterGoods(pchar, GOOD_BOMBS, 2500);
			RemoveCharacterGoods(pchar, GOOD_POWDER, 2500);
			dialog.text = "Oui, oui, vous allez recevoir vos instructions maintenant. Êtes-vous prêt à prêter attention?";
			link.l1 = "Certainement, officier.";
			link.l1.go = "trial_3";
		break;
		
		case "trial_3":
			dialog.text = "So, our military ship 'Warlike' is cruising near the Spanish colony Porto Bello, in the southern part of the Spanish Main. This vessel is under the command of Florian Shoke, who is preparing an ambush of a Spanish heavy galleon set to leave Porto Bello in two weeks.\nThe problem is that our frigate's cannons are suffering from a casting defect, and we need to replace fifteen cannons to save the mission; otherwise, the galleon will outnumber 'Warlike' in both guns and men. \nWithout the replacement, Florian Shoke will be forced to sail away with no result. Such a sequence of events is highly undesirable. Your task is to save the mission by delivering fifteen cannons within fourteen days.";
			link.l1 = "Alors, je dois prendre à bord quinze canons, me diriger vers Portobello, chercher la frégate 'Militant' et remettre les canons au capitaine Florian Shoke?";
			link.l1.go = "trial_4";
		break;
		
		case "trial_4":
			dialog.text = "Exactement. Vous avez tout compris. Êtes-vous prêt à entreprendre cette mission?";
			link.l1 = "Et qu'en est-il du paiement?";
			link.l1.go = "trial_5";
			link.l2 = "Je suis désolé, officier, mais je ne veux tout simplement pas m'impliquer. Veuillez m'excuser.";
			link.l2.go = "trial_exit";
		break;
		
		case "trial_exit":
			dialog.text = "Vous avez raison, mais je comptais sur votre accord. Maintenant, je vais devoir trouver un autre courrier, bien que je n'ai pas beaucoup de temps... Eh bien, je ne vous retiens pas plus longtemps, capitaine.";
			link.l1 = "Meilleurs voeux.";
			link.l1.go = "trial_exit_1";
		break;
		
		case "trial_exit_1":
			DialogExit();
			AddQuestRecord("Trial", "6");
			CloseQuestHeader("Trial");
			DeleteAttribute(pchar, "questTemp.Trial");
			pchar.questTemp.TrialEnd = true;
		break;
		
		case "trial_5":
			dialog.text = "Ne vous inquiétez pas à ce sujet. Florian Shoke vous paiera deux cents doublons d'or du trésor du navire. De plus, je suis certain qu'il voudrait utiliser vous et votre navire pour ses propres objectifs - avec votre consentement, bien sûr.";
			link.l1 = "D'accord, je suis en mission ! Où sont les canons ?";
			link.l1.go = "trial_6";
		break;
		
		case "trial_6":
			dialog.text = "Je donnerai l'ordre aux soldats de les charger sur votre navire immédiatement. Mettez les voiles dès que vous le pouvez, monsieur! Bonne chance!";
			link.l1 = "Merci. La chance ne fera sûrement pas de mal, et le vent arrière non plus...";
			link.l1.go = "trial_7";
		break;
		
		case "trial_7":
			DialogExit();
			AddQuestRecord("Trial", "7");
			pchar.questTemp.Trial = "cannon";
			// belamour legendary edition
			if(!bImCasual) SetFunctionTimerCondition("Trial_CannonFail", 0, 0, 21, false); 
			else NewGameTip("Exploration mode: timer is disabled.");
			SetCharacterGoods(pchar, GOOD_CANNON_24, GetCargoGoods(pchar, GOOD_CANNON_24)+15);
			if (MOD_SKILL_ENEMY_RATE >= 6)
			{
				EnemyNationHunterOnMap(true);//запуск перехватчиков
			}
			pchar.quest.Trial_cannon.win_condition.l1 = "location";
			pchar.quest.Trial_cannon.win_condition.l1.location = "Portobello";
			pchar.quest.Trial_cannon.function = "Trial_CreateFlorianFrigate";
			// Sinistra - квест "Встреча с Диего"
			bDisableFastReload = true;
			PChar.quest.VsD_GiumDyubua.win_condition.l1 = "location";
			PChar.quest.VsD_GiumDyubua.win_condition.l1.location = "PortPax_Fort";
			PChar.quest.VsD_GiumDyubua.win_condition = "VsD_GiumDyubua";
			AddMapQuestMarkShore("Shore47", false);
		break;
		
		// Опасный груз -->
		case "zpq_prs1":
			if(!isBadReputation(pchar, 70))
			{
				dialog.text = "Hm, peut-être. Eh bien, à cause de votre bonne réputation, je vais prendre le risque de vous faire confiance. Dans un autre cas, je n'en parlerais même pas avec vous. Le fait est que nous avons besoin d'une quantité assez importante de marchandises spéciales, donc vous aurez besoin d'un grand navire de charge et d'une volonté de prendre des risques. Aussi, vous devez me donner votre parole de ne le dire à personne.\nSi vous trouvez cela gênant, dites-le moi tout de suite. Je pense que j'ai fait mon point...";
				link.l1 = "Cela semble intrigant. Je suis partant si le paiement est correct, bien que je n'aie aucune idée de la cargaison dont vous parlez. Vous avez ma parole de toute façon.";
				link.l1.go = "zpq_prs2";
				link.l2 = "Je dirais non, je suppose... si je te donnais ma parole, je devrais faire un travail qui semble assez ennuyeux. Je ne ferai pas cela.";
				link.l2.go = "zpq_fld";
				notification("Reputation Check Passed", "None");
			}
			else
			{
				dialog.text = "Votre réputation est inacceptable pour moi. Je vous demande de quitter la salle. Nous sommes capables de résoudre nos problèmes par nous-mêmes.";
				link.l1 = "Peu importe, résous-les alors...";
				link.l1.go = "exit";
				notification("Reputation Too Low! ("+XI_ConvertString(GetReputationName(71))+")", "None");
			}		
		break;
		
		case "zpq_fld":
			dialog.text = "Eh bien, au moins tu as refusé de manière honnête... Je ne te retiens plus.";
			link.l1 = "Adieu.";
			link.l1.go = "exit";
			pchar.questTemp.zpq = "failed";
			DelLandQuestMark(npchar);
			DelMapQuestMarkCity("Cumana");
		break;
		
		case "zpq_fld2":
			dialog.text = "Hm, en fait, je ne m'attendais pas à cela de votre part. Je dois vous demander de partir... Et rappelez-vous de votre promesse de ne divulguer aucune information.";
			link.l1 = "Je suis désolé...";
			link.l1.go = "exit";
    		ChangeCharacterComplexReputation(pchar,"nobility", -3);
			if (pchar.questTemp.zpq == "begin")
			{
				AddQuestRecord("zpq", "6");
				AddQuestUserData("zpq", "sSex", GetSexPhrase("",""));
				CloseQuestHeader("zpq");
			}
			pchar.questTemp.zpq = "failed";
		break;
		
		case "zpq_prs2":
			dialog.text = "Splendide. Splendide. Le problème est que la récente tempête a endommagé notre réserve de poudre à canon dans l'arsenal du fort. J'espère que je n'ai pas besoin de vous expliquer que nous avons un problème délicat ici. En cas de siège prolongé, le fort ne pourra rien faire. Nous ne tiendrons pas longtemps.";
			link.l1 = "Maintenant je comprends. Quelle cargaison avez-vous besoin - et quelle quantité?";
			link.l1.go = "zpq_prs3";
			DelLandQuestMark(npchar);
			DelMapQuestMarkCity("Cumana");
		break;
		
		case "zpq_prs3":
			dialog.text = "Nous avons besoin de 15 000 barils de poudre à canon. Je vous paierai 100 000 pesos... Vous devez comprendre que c'est un très bon prix. Notre situation actuelle m'oblige à aller avec de tels coûts bien que ce fut difficile de convaincre le boursier du gouverneur de cela... La saison des tempêtes ne nous permet pas d'utiliser nos propres lignes d'approvisionnement et nous ne voulons pas que tout le monde sache à propos de ce problème...";
			link.l1 = "Je vois... le prix est vraiment intéressant. Vous avez mentionné des risques...";
			link.l1.go = "zpq_prs4";
		break;
		
		case "zpq_prs4":
			dialog.text = "Je voulais dire qu'une telle quantité de poudre à canon peut être très dangereuse pendant le transport. J'ai vu quelques explosions de mes propres yeux, parfois une seule étincelle peut faire l'affaire. Mais si vous affrontez la tempête... Les convois entiers gardent généralement une distance du brûleur potentiel. S'il explose, alors tout le monde est mort !";
			link.l1 = "Je vois... Mais je tiens toujours ma parole, considère que c'est fait.";
			link.l1.go = "zpq_prs5";
			link.l2 = "Eh bien, senor... Vous m'avez raconté des choses si terribles, que j'ai perdu toute envie de faire ce travail.";
			link.l2.go = "zpq_fld2";
		break;
		
		case "zpq_prs5":
			dialog.text = "Bien, je suis très content que nous ayons conclu un accord. Je vous paierai dès que vous m'apporterez la cargaison.\nJ'aurai de l'argent dans une semaine, pas avant, alors prenez votre temps mais je vous demanderais d'essayer de ne pas trop tarder.";
			link.l1 = "Je comprends, monsieur. Je m'en occupe.";
			link.l1.go = "zpq_prs5_ok";
		break;
		
		case "zpq_prs5_ok":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			pchar.questTemp.zpq = "begin";
			pchar.questTemp.zpq.time = 20;
			AddQuestRecord("zpq", "1");
			AddQuestUserData("zpq", "sSex", GetSexPhrase("",""));
			SaveCurrentQuestDateParam("pchar.questTemp.zpq");
		break;
		
		case "zpq_ex":
			dialog.text = "Enfin! Je pensais que vous aviez déjà oublié notre accord. Je vais immédiatement ordonner à mes soldats de commencer à décharger votre navire. Travailler avec de la poudre à canon est une affaire très délicate, ha-ha!";
			link.l1 = "C'est formidable, monsieur, mais je dois vous rappeler du paiement.";
			link.l1.go = "zpq_ex2";
			RemoveCharacterGoods(pchar, GOOD_POWDER, 15000);
			AddCharacterExpToSkill(pchar, "Sailing", 500);
			AddCharacterExpToSkill(pchar, "Fortune", 500);

            pchar.quest.zpq_sld1_fc.win_condition.l1 = "location";
            pchar.quest.zpq_sld1_fc.win_condition.l1.location = "Cumana_ExitTown";
            pchar.quest.zpq_sld1_fc.function = "zpq_sld1_fc";
		break;
		
		case "zpq_ex2":
			dialog.text = "Oui, bien sûr. Vous serez payé 50 000 pesos comme nous l'avons convenu.";
			link.l1 = "Vous vous moquez probablement de moi, senor?! Nous avions conclu un accord sur 100 000 pesos!";
			link.l1.go = "zpq_ex3";
			if(CheckCharacterPerk(pchar, "Trustworthy"))
			{
				notification("Trustworthy", "Trustworthy");
				link.l2 = "(Digne de confiance) Je commence à croire que tu vas me tromper alors je ne partirai pas d'ici sans mes 125 000 pesos !";
				link.l2.go = "zpq_ex4";
			}
			link.l3 = "Hm.. Je vois que les circonstances ont changé. Eh bien, je ferais mieux de prendre l'argent et de partir...";
			link.l3.go = "zpq_ex5";
		break;
		
		case "zpq_ex3":
			if (GetSummonSkillFromName(pchar, "Leadership") > 35)
			{
				notification("Skill Check Passed", "Leadership");
				dialog.text = "Ah, oui ... Exactement ! 100 000 pesos. J'ai oublié, pardonnez-moi. C'est à cause de mon âge, la sclérose vous savez ... Bien sûr, voici vos pièces. C'était un plaisir de faire affaire avec vous, capitaine. Maintenant, je suis désolé, mais j'ai beaucoup de travail à faire ...";
				link.l1 = "La même chose pour vous, señor. À bientôt.";
				link.l1.go = "exit";
				pchar.questTemp.zpq = "completed";
				AddQuestRecord("zpq", "2");
				AddQuestUserData("zpq", "sSex", GetSexPhrase("",""));
				CloseQuestHeader("zpq");
				pchar.questTemp.zpq.sum = 100000;
				AddMoneyToCharacter(pchar, makeint(pchar.questTemp.zpq.sum));
			}
			else
			{
				notification("Skill Check Failed (36)", "Leadership");
				dialog.text = "Quoi ?! Prends ton argent et fous le camp, ou tu vas pourrir dans cette casemate !";
				link.l1 = "Vous êtes un tel menteur, monsieur! Je vous conseille de me donner mon argent de manière honnête, ou je prendrai la cargaison!";
				link.l1.go = "zpq_ex_agry";
				link.l2 = "Excusez-moi... D'accord, je prendrai la somme que vous proposez et nous en avons fini.";
				link.l2.go = "zpq_ex5";
				Log_info("Leadership skill is not sufficient");
			}
		break;
		
		case "zpq_ex4":
				dialog.text = "Quelle impolitesse ! Je ne suis pas mentalement malade et je me souviens précisément avoir offert 100 000 pesos.\n Zut ! Je ne vais pas jouer à vos jeux !";
				link.l1 = "Calmez-vous. Pensez au marquoir prêt rempli de poudre à canon juste devant votre fort. Si je dis juste un mot, votre fort se transformera en ruines.";
				link.l1.go = "zpq_ex6";
		break;
		
		case "zpq_ex6":
			dialog.text = "Hm-Hm... argument convaincant. 125 000 pesos, dites-vous ? Tenez, prenez-les, et pardonnez-moi maintenant mais j'ai du travail à faire...";
			link.l1 = "Adieu, monsieur. A bientot.";
			link.l1.go = "exit";
			pchar.questTemp.zpq = "completed";
            AddQuestRecord("zpq", "5");
			CloseQuestHeader("zpq");
			pchar.questTemp.zpq.sum = 125000;
			AddMoneyToCharacter(pchar, makeint(pchar.questTemp.zpq.sum));
			/*else
			{
				dialog.text = "Quoi?! Je suis un officier militaire! Tu penses que tu peux me faire peur, gamin?! Gardes, prenez "+GetSexPhrase("lui","elle")+"!";
				link.l1 = "Bonne chance en essayant, rats des casemates...";
				link.l1.go = "zpq_ex_war";
			}*/
		break;
		
		case "zpq_ex5":
			dialog.text = "Magnifique! Tu as fait le bon choix. Prends tes pièces et au revoir. Ce fut un plaisir!";
			link.l1 = "Adieu...";
			link.l1.go = "exit";
			pchar.questTemp.zpq = "completed";
            AddQuestRecord("zpq", "3");
			AddQuestUserData("zpq", "sSex", GetSexPhrase("",""));
			CloseQuestHeader("zpq");
			pchar.questTemp.zpq.sum = 50000;
			AddMoneyToCharacter(pchar, makeint(pchar.questTemp.zpq.sum));
		break;
		
		case "zpq_ex_agry":
			dialog.text = "Ah, tu es un salaud ! Gardes, prenez "+GetSexPhrase("lui","elle")+"!";
			link.l1 = "Argh ! Il semble que je dois prendre mon argent de ton corps sans vie...";
			link.l1.go = "zpq_ex_war";
		break;
		
        case "zpq_ex_war":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			LAi_SetFightMode(PChar, true);
			pchar.questTemp.zpq = "failed";
            AddQuestRecord("zpq", "4");
			CloseQuestHeader("zpq");
			pchar.questTemp.zpq.sum = 100000;
			AddMoneyToCharacter(npchar, makeint(sti(pchar.questTemp.zpq.sum)*2 + rand(5000)));
			GiveItem2Character(npchar, "blade_21");
			EquipCharacterbyItem(npchar, "blade_21");
			npchar.SaveItemsForDead  = true;
			npchar.DontClearDead = true;
			npchar.cirassId = Items_FindItemIdx("cirass3");
			chrDisableReloadToLocation = true;
			string slai_group = GetNationNameByType(sti(npchar.nation))  + "_citizens";
			LAi_group_AttackGroup(slai_group, LAI_GROUP_PLAYER);
			LAi_group_SetCheck(slai_group, "OpenTheDoors");
			AddSimpleRumour("Such terrible things happen here! They say that some prisoner has escaped from the casemates! He slaughtered all the guards, stole the treasury, and just went away! Wow!", SPAIN, 5, 1);
		break;
		// <-- Опасный груз
	}
}

void GetGunType()
{
	int iGunType;
	if(makeint(pchar.rank) < 6) iGunType = rand(1);	//18&&24
	if(makeint(pchar.rank) >= 6 && makeint(pchar.rank) < 15) iGunType = rand(2); //24&&32	
	if(makeint(pchar.rank) >= 15 && makeint(pchar.rank) < 24) iGunType = rand(2)+2; //32&&36&&42
	if(makeint(pchar.rank) >= 24) iGunType = 5-rand(1); //36clv&&42
	int iAdd = makeint(GetSummonSkillFromName(pchar, SKILL_COMMERCE)/20);
	
	switch (iGunType)
	{
		case 0:  
			pchar.questTemp.PrisonGun.Goods = GOOD_CANNON_24;     					
			pchar.questTemp.PrisonGun.Price = 28 + iAdd;
			pchar.questTemp.PrisonGun.Qty = sti(pchar.rank)*5+25+rand(sti(pchar.rank));
			pchar.questTemp.PrisonGun.Text = "24 calibre cannons";
		break; 
		case 1:  
			pchar.questTemp.PrisonGun.Goods = GOOD_CULVERINE_18;     					
			pchar.questTemp.PrisonGun.Price = 25 + iAdd;
			pchar.questTemp.PrisonGun.Qty = sti(pchar.rank)*5+25+rand(sti(pchar.rank));
			pchar.questTemp.PrisonGun.Text = "couleuvrines";
		break; 
		case 2:  
			pchar.questTemp.PrisonGun.Goods = GOOD_CANNON_32;     					
			pchar.questTemp.PrisonGun.Price = 32 + iAdd;
			pchar.questTemp.PrisonGun.Qty = sti(pchar.rank)*3+15+rand(sti(pchar.rank));
			pchar.questTemp.PrisonGun.Text = "32 calibre cannons";
		break; 
		case 3:  
			pchar.questTemp.PrisonGun.Goods = GOOD_CANNON_36;     					
			pchar.questTemp.PrisonGun.Price = 36 + iAdd;
			pchar.questTemp.PrisonGun.Qty = sti(pchar.rank)*3+15+rand(sti(pchar.rank));
			pchar.questTemp.PrisonGun.Text = "36 calibre cannons";
		break;
		case 4:  
			pchar.questTemp.PrisonGun.Goods = GOOD_CULVERINE_36;     					
			pchar.questTemp.PrisonGun.Price = 49 + iAdd;
			pchar.questTemp.PrisonGun.Qty = sti(pchar.rank)+15+rand(sti(pchar.rank));
			pchar.questTemp.PrisonGun.Text = "full couleuvrines";
		break; 
		case 5:  
			pchar.questTemp.PrisonGun.Goods = GOOD_CANNON_42;     					
			pchar.questTemp.PrisonGun.Price = 40 + iAdd;
			pchar.questTemp.PrisonGun.Qty = sti(pchar.rank)+20+rand(sti(pchar.rank));
			pchar.questTemp.PrisonGun.Text = "42 calibre cannons";
		break; 
	}
}
