// диалоги обитателей плантаций
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	int iTemp, i, n;
	string sTemp;
	bool bOk;
	
	DeleteAttribute(&Dialog,"Links");
	
	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

	switch(Dialog.CurrentNode)
	{
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
        case "First time":
			dialog.text = "Avez-vous besoin de quelque chose?";
			link.l1 = "Non, je ne le fais pas.";
			link.l1.go = "exit";
		break;
		
		case "fight":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			LAi_group_Attack(NPChar, Pchar);
			SetNationRelation2MainCharacter(sti(npchar.nation), RELATION_ENEMY);
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		
		// рабы
		case "plantation_slave":
			dialog.text = RandPhraseSimple(RandPhraseSimple("Je suis si fatigué, je suis déjà en train de tomber...","Je ne peux plus vivre comme ça !"),RandPhraseSimple("Ce travail me tue.","Les gardes veulent tous nous tuer !"));				
			link.l1 = RandPhraseSimple("Quel dommage.","Je suis désolé.");
			link.l1.go = "exit";				
		break;
		
		// рабы-пираты по пиратской линейке
		case "pirate_slave":
			dialog.text = RandPhraseSimple(RandPhraseSimple("Écoute, va-t'en !","Va-t'en !"),RandPhraseSimple("Que voulez-vous?!","Dégage d'ici !"));				
			link.l1 = RandPhraseSimple("Hm...","Eh bien...");
			link.l1.go = "exit";				
		break;
		
		// охрана - солдаты
		case "plantation_soldier":
            dialog.text = RandPhraseSimple(RandPhraseSimple("Va embêter le chef de plantation","Ne dérange pas les esclaves, mon pote."),RandPhraseSimple("Mon travail est de motiver ces fainéants paresseux.","Sacrébleu, trop chaud aujourd'hui, comme toujours..."));
			link.l1 = RandPhraseSimple("Je vois...","En effet...");
			link.l1.go = "exit";
		break;
		
		// охрана - протектор
		case "plantation_protector":
            if (GetNationRelation2MainCharacter(sti(NPChar.nation)) == RELATION_ENEMY && sti(NPChar.nation) != PIRATE)
			{
				if (sti(pchar.nation) == PIRATE)
				{
					PlaySound("Voice\English\soldier_arest_1.wav");
    				dialog.text = RandPhraseSimple("Pirate?! Saisissez-le !","Il est un pirate! Attaque!");
					link.l1 = RandPhraseSimple("Pirate. Et alors ?","Heh, vas-y et essaie.");
					link.l1.go = "fight"; 
					break;
				}
				PlaySound("Voice\English\soldier_arest_2.wav");
				dialog.text = RandPhraseSimple("Ho-ho, vous naviguez sous le drapeau de "+NationNameGenitive(sti(pchar.nation))+"! Je pense que notre commandant sera ravi de parler avec vous !","Eh bien, ça sent le "+NationNameAblative(sti(pchar.nation))+" ici ! Un espion ?! Il est temps pour toi de parler avec notre commandant.");
				link.l1 = RandPhraseSimple("D'abord, je t'enverrai en enfer !","C'est l'heure pour toi de parler avec ma lame !");
				link.l1.go = "fight"; 
			}
			else
			{
				if (GetNationRelation(sti(NPChar.nation), GetBaseHeroNation()) == RELATION_ENEMY && sti(NPChar.nation) != PIRATE)
				{
					if (sti(pchar.nation) == PIRATE)
					{
						PlaySound("Voice\English\soldier_arest_1.wav");
						dialog.text = RandPhraseSimple("Pirate?! Saisissez-le!","Il est un pirate! Attaque!");
						link.l1 = RandPhraseSimple("Pirate !? Ou ?","Heh, vas-y et essaie.");
						link.l1.go = "fight"; 
						break;
					}
					PlaySound("Voice\English\soldier_arest_4.wav");
					dialog.text = RandPhraseSimple("Qui êtes-vous et que voulez-vous ici?","Arrêtez! Quelle est votre affaire ici?");
					if (CheckNationLicence(HOLLAND))
					{
						link.l1 = "Je veux voir le chef de cet endroit pour discuter affaires. J'ai une licence de commerce.";
						link.l1.go = "Licence";
					}
					else
					{
						link.l1 = "Je veux voir le chef de cet endroit pour discuter affaires.";
						if (GetSummonSkillFromName(pchar, SKILL_SNEAK) < (10+rand(50)+rand(50))) link.l1.go = "PegYou";
						else link.l1.go = "NotPegYou";
					}
					if (IsCharacterPerkOn(pchar, "Trustworthy"))
					{
						link.l2 = "(Digne de confiance) Honorables seigneurs, je suis ici pour un commerce juste et mutuellement bénéfique. S'il vous plaît, laissez-moi voir le propriétaire de la plantation.";
						link.l2.go = "mtraxx_soldier_1";
						notification("Trustworthy", "Trustworthy");
					}
				}
				else
				{
					PlaySound("Voice\English\soldier_arest_4.wav");
					dialog.text = RandPhraseSimple("Qui êtes-vous et que voulez-vous ici?","Arrêtez! Quelle est votre affaire ici?");
					link.l1 = "Je veux voir le chef de cet endroit pour discuter affaires.";
					link.l1.go = "NotPegYou";
				}
			}
		break;
		
		case "Licence":
			iTemp = GetDaysContinueNationLicence(HOLLAND);
			if (ChangeCharacterNationReputation(pchar, sti(NPChar.nation), 0) <= -12)
			{
				PlaySound("Voice\English\soldier_arest_2.wav");
				dialog.text = "Une licence? Attendez une seconde... Ha-ha, c'est drôle! Je sais qui vous êtes. Vous êtes recherché, mon pote! Et la récompense pour votre tête est très grande! Attrapez-le!";
				link.l1 = RandPhraseSimple("Eh bien dans ce cas, tu dois juste rencontrer ma lame!","Va te faire foutre.");
				link.l1.go = "fight";	
				break;
			}
			if (iTemp == -1)
			{
				PlaySound("Voice\English\soldier_arest_1.wav");
				dialog.text = "Allons voir... ha ! Votre licence est en retard. Alors suivez-moi, je vous amènerai au commandant...";
				link.l1 = RandPhraseSimple("Merde! Je suppose que c'est le moment pour toi de rencontrer ma lame, mon pote.","Je ne pense pas...");
				link.l1.go = "fight";	
				TakeNationLicence(HOLLAND);
				break;
			}
			dialog.text = "D'accord. Tu peux entrer. Comporte-toi bien et ne derange pas les esclaves.";
			link.l1 = "Ne t'inquiète pas, mon ami.";
			link.l1.go = "plantation_exit";
		break;
		
		case "PegYou":
			PlaySound("Voice\English\soldier_arest_2.wav");
            dialog.text = "Affaires? Ha-ha! Eh bien, c'est drôle! Tu sens le "+NationNameAblative(sti(GetBaseHeroNation()))+" de mille milles! Il est temps pour vous de rencontrer notre commandant.";
			link.l1 = "Non, je pense qu'il est temps pour toi de rencontrer ma lame.";
			link.l1.go = "fight";
		break;
		
		case "NotPegYou":
            dialog.text = "D'accord. Tu peux entrer. Comporte-toi bien et ne dérange pas les esclaves.";
			link.l1 = "Ne t'inquiète pas, mon ami.";
			link.l1.go = "plantation_exit";
		break;
		
		case "plantation_exit":
           DialogExit();
		   NextDiag.CurrentNode = "plantation_repeat";
		break;
		
		case "plantation_repeat":
            dialog.text = "Allez, avancez !";
			link.l1 = "...";
			link.l1.go = "plantation_exit";
		break;
		
		// управляющий в Маракайбо // Addon 2016-1 Jason
		case "Plantator":
			if (CheckAttribute(pchar, "questTemp.Mtraxx") && pchar.questTemp.Mtraxx == "plant_2") // belamour legendary edition 
			{
				dialog.text = "Quelle est votre affaire ici, senor?";
				link.l1 = TimeGreeting()+", monsieur. J'ai une proposition d'affaire pour vous. J'ai des esclaves à vendre. "+FindRussianQtyString(sti(GetSquadronGoods(pchar,GOOD_SLAVES)))+". Intéressé?";
				link.l1.go = "mtraxx";
				break;
			}
            dialog.text = "Quelle est votre affaire ici, senor?";
			link.l1 = "Juste en promenade, je voulais dire bonjour.";
			link.l1.go = "plantator_x";
		break;
		
		case "plantator_x":
           DialogExit();
		   npchar.dialog.currentnode = "plantator";
		break;
		
		case "plantator_1":
			bOk = GetSquadronGoods(pchar, GOOD_COFFEE) >= 500 || GetSquadronGoods(pchar, GOOD_CINNAMON) >= 500 || GetSquadronGoods(pchar, GOOD_COPRA) >= 500;
			if (CheckAttribute(pchar, "questTemp.mtraxx_PlantVykup") && bOk) //пробуем выкупить Красавчика
			{
				dialog.text = "Vous encore, senor. Comment allez-vous?";
				link.l1 = "J'ai une proposition commerciale pour vous. Vous produisez du sucre et du cacao. J'aimerais acheter vos marchandises mais pas pour de l'argent, je peux offrir mes propres marchandises en échange. Peut-être, pourrions-nous faire un marché ?";
				link.l1.go = "mtraxx_5";
				break;
			}
			if (CheckAttribute(pchar, "questTemp.Mtraxx") && pchar.questTemp.Mtraxx == "plant_6" && bOk)
			{
				dialog.text = "Vous encore, senor. Comment allez-vous?";
				link.l1 = "J'ai une proposition commerciale pour vous. Vous produisez du sucre et du cacao. J'aimerais acheter vos marchandises mais pas avec de l'argent, je peux offrir mes propres marchandises en échange. Peut-être, pourrions-nous faire un troc?";
				link.l1.go = "mtraxx_5";
				break;
			}
            dialog.text = "Vous encore, senor. Comment allez-vous?";
			link.l1 = "Merci, je vais bien.";
			link.l1.go = "plantator_1x";
		break;
		
		case "plantator_1x":
           DialogExit();
		   npchar.dialog.currentnode = "plantator_1";
		break;
		
		case "mtraxx":
			// belamour legendary edition возможность обмануть плантатора -->
			if(GetSquadronGoods(pchar, GOOD_SLAVES) >= 50 || CheckCharacterPerk(pchar, "Trustworthy") || ChangeCharacterHunterScore(Pchar, "spahunter", 0) <= -50)
			{
            dialog.text = "Je dois vous décevoir, senor, mais nous n'avons pas besoin d'esclaves pour le moment. Le capitaine Eduardo de Losada nous a déjà fourni des pirates qu'il a capturés lors de sa dernière attaque.";
			link.l1 = "Des pirates ici? Comment pouvez-vous même dormir ici?";
			link.l1.go = "mtraxx_1";
			}
			else
			{
				dialog.text = "Ah, voyons voir alors... J'achèterai tes esclaves. Il me semble juste que tu n'es pas qui tu prétends être. Viens avec moi au bureau du commandant, ma chère, et si je me trompe, je couvrirai entièrement tes frais moraux. Et maintenant, je te prie de m'excuser. Garde!";
				link.l1 = RandPhraseSimple("Continue à rêver, je ne me rendrai pas vivant!");
				link.l1.go = "mtraxx_fail";
			}
		break;
		
		case "mtraxx_fail":
            DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			LAi_group_Attack(NPChar, Pchar);
			SetNationRelation2MainCharacter(sti(npchar.nation), RELATION_ENEMY);
			AddQuestRecord("Roger_3", "27");
			sld = characterFromId("Mtr_plantation_boss");
			sld.lifeday = 0;
			Mtraxx_PlantPellyClear();
			Mtraxx_TerraxReset(3);
		break;
		// <-- legendary edition
		case "mtraxx_1":
			DelMapQuestMarkCity("baster");
			DelLandQuestMark(characterFromId("Fadey"));
            dialog.text = "Nous avons une bonne garde, donc les chances de révolte sont faibles. Mais vous avez raison sur un point : ces salauds sont de terribles travailleurs. Je ne les aurais pas achetés si le gouverneur ne m'avait pas demandé de montrer du respect à don de Losada. De plus, il n'a pas non plus demandé beaucoup pour eux.";
			link.l1 = "Je vois. Je vais devoir naviguer vers Los-Teques alors... Seigneur, puis-je me promener autour de votre plantation et l'explorer ? Peut-être, j'aimerais acheter une partie de votre production...";
			link.l1.go = "mtraxx_2";
		break;
		
		case "mtraxx_2":
            dialog.text = "Êtes-vous un marchand?";
			link.l1 = "Dans une certaine mesure, oui. Je ne suis pas un marchand professionnel mais je ne refuserais jamais une affaire prometteuse.";
			link.l1.go = "mtraxx_3";
		break;
		
		case "mtraxx_3":
            dialog.text = "Intéressant. Très bien, tu as ma permission. Reviens si tu as des idées.";
			link.l1 = "Merci, monsieur. Je crois que je vais le faire.";
			link.l1.go = "mtraxx_4";
		break;
		
		case "mtraxx_4":
           DialogExit();
		   NextDiag.CurrentNode = "plantator_1";
		   pchar.questTemp.Mtraxx = "plant_3";
		   AddQuestRecord("Roger_3", "5");
		   Mtraxx_PlantSetMaxRocur();
		break;
		
		case "mtraxx_5":
            dialog.text = "Pourquoi pas? Quels biens proposez-vous?";
			if (GetSquadronGoods(pchar, GOOD_COFFEE) >= 500)
			{
				link.l1 = "500 boîtes de café.";
				link.l1.go = "mtraxx_coffee";
			}
			if (GetSquadronGoods(pchar, GOOD_CINNAMON) >= 500)
			{
				link.l2 = "500 boîtes de vanille.";
				link.l2.go = "mtraxx_cinnamon";
			}
			if (GetSquadronGoods(pchar, GOOD_COPRA) >= 500)
			{
				link.l3 = "500 boîtes de coprah.";
				link.l3.go = "mtraxx_copra";
			}
		break;
		
		case "mtraxx_coffee":
			i = hrand(3)+1;
			n = 5 - i;
			pchar.questTemp.Mtraxx.PlantGood.Cargo = 11;
			pchar.questTemp.Mtraxx.PlantGood.Sugar = i * 100;
			pchar.questTemp.Mtraxx.PlantGood.Cocoa = n * 100;
            dialog.text = "Cinq cents boîtes de café? Eh bien-eh bien... Voyons voir... (comptant) Je suis prêt à échanger votre café pour "+sti(pchar.questTemp.Mtraxx.PlantGood.Sugar)+" sacs de sucre et "+sti(pchar.questTemp.Mtraxx.PlantGood.Cocoa)+"  boîtes de cacao. Marché conclu?";
			link.l1 = "Hmm... J'espérais de meilleures conditions. Eh bien, peu importe. Marché conclu !";
			link.l1.go = "mtraxx_6";
			if (CheckAttribute(pchar, "questTemp.mtraxx_PlantVykup"))
			{
				link.l1 = "(Digne de confiance) Monsieur estimé, permettez-moi de m'opposer! J'ai apporté des marchandises de la plus haute qualité. Je connais la valeur de chaque unité, à la fois de ce que j'offre et de ce que vous offrez en retour. Je mérite une charge légèrement plus grande de votre côté, et cette affaire sera toujours rentable pour vous - vous le savez très bien.";
				link.l1.go = "mtraxx_PlantVykup_2";
				notification("Trustworthy", "Trustworthy");
			}
		break;
		
		case "mtraxx_cinnamon":
			i = hrand(3)+1;
			n = 5 - i;
			pchar.questTemp.Mtraxx.PlantGood.Cargo = 19;
			pchar.questTemp.Mtraxx.PlantGood.Sugar = i * 106;
			pchar.questTemp.Mtraxx.PlantGood.Cocoa = n * 106;
            dialog.text = "Cinq cents boîtes de vanille? Eh bien, voyons... (comptant) Je suis prêt à échanger votre vanille contre "+sti(pchar.questTemp.Mtraxx.PlantGood.Sugar)+" sacs de sucre et "+sti(pchar.questTemp.Mtraxx.PlantGood.Cocoa)+"  boîtes de cacao. Marché conclu?";
			link.l1 = "Hmm... J'espérais de meilleures conditions. Enfin, qui s'en soucie. Marché conclu !";
			link.l1.go = "mtraxx_6";
			if (CheckAttribute(pchar, "questTemp.mtraxx_PlantVykup"))
			{
				link.l1 = "(Digne de confiance) Monsieur estimé, permettez-moi de protester! Je vous ai apporté des marchandises de la plus haute qualité. Je connais la valeur de chaque unité, à la fois de ce que j'offre et de ce que vous offrez en retour. Je mérite une charge légèrement plus grande de votre côté, et cette affaire sera toujours rentable pour vous - vous le savez très bien.";
				link.l1.go = "mtraxx_PlantVykup_2";
				notification("Trustworthy", "Trustworthy");
			}
		break;
		
		case "mtraxx_copra":
			i = hrand(3)+1;
			n = 5 - i;
			pchar.questTemp.Mtraxx.PlantGood.Cargo = 20;
			pchar.questTemp.Mtraxx.PlantGood.Sugar = i * 100;
			pchar.questTemp.Mtraxx.PlantGood.Cocoa = n * 100;
            dialog.text = "Cinq cents boîtes de coprah? Eh bien-eh bien... Voyons voir...(compte) Je suis prêt à échanger votre coprah pour "+sti(pchar.questTemp.Mtraxx.PlantGood.Sugar)+" sacs de sucre et "+sti(pchar.questTemp.Mtraxx.PlantGood.Cocoa)+"  boîtes de cacao. Marché conclu?";
			link.l1 = "Hmm... J'espérais de meilleures conditions... Eh bien, peu importe. Marché conclu!";
			link.l1.go = "mtraxx_6";
			if (CheckAttribute(pchar, "questTemp.mtraxx_PlantVykup"))
			{
				link.l1 = "(Digne de confiance) Estimé monsieur, permettez-moi de m'opposer! Je vous ai apporté des biens de la plus haute qualité. Je connais la valeur de chaque unité, tant de ce que j'offre que de ce que vous offrez en retour. Je mérite une charge légèrement plus grande de votre part, et cette affaire sera toujours rentable pour vous - vous le savez très bien.";
				link.l1.go = "mtraxx_PlantVykup_2";
				notification("Trustworthy", "Trustworthy");
			}
		break;
		
		case "mtraxx_6":
            dialog.text = "Splendide! C'est une affaire rentable pour nous deux! Quand ferons-nous l'échange?";
			link.l1 = "Je devrais préparer les marchandises d'abord. Toi aussi, je crois. Commençons l'échange demain à quatre heures de l'après-midi. Mes hommes livreront les caisses avant le coucher du soleil.";
			link.l1.go = "mtraxx_7";
		break;
		
		
		case "mtraxx_7":
            dialog.text = "Marché conclu. Alors, je vous verrai demain monsieur!";
			link.l1 = "Au revoir...";
			link.l1.go = "mtraxx_8";
		break;
		
		case "mtraxx_8":
            DialogExit();
			NextDiag.CurrentNode = "plantator_1";
			AddQuestRecord("Roger_3", "10");
			pchar.questTemp.Mtraxx = "plant_7";
			pchar.GenQuest.CannotWait = true;//запрет ожидания
			pchar.quest.mtraxx_plant_goods.win_condition.l1 = "ExitFromLocation";
			pchar.quest.mtraxx_plant_goods.win_condition.l1.location = pchar.location;
			pchar.quest.mtraxx_plant_goods.function = "Mtraxx_PlantFindRocurDay";
		break;
		
		case "mtraxx_9":
            dialog.text = "C'est ça, monsieur. Si vous avez jamais besoin de sucre ou de cacao, venez me voir. N'importe quand!";
			link.l1 = "Si cet accord s'avère rentable - nous nous reverrons. Je dois partir maintenant, senor.";
			link.l1.go = "mtraxx_10";
		break;
		
		case "mtraxx_10":
            dialog.text = "Adieu, monsieur !";
			link.l1 = "";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Mtraxx_PlantAfterTrading");
		break;
		
		case "mtraxx_soldier_1":
            dialog.text = "Vous ne ressemblez pas à un marchand, étranger. Montrez votre licence.";
			link.l1 = "Epargne-moi! Est-ce qu'un bout de papier décide si une personne peut commercer ou non? Ils sont trop chers! J'ai seulement commencé à commercer récemment, mais c'est déjà devenu ma passion! Laissez-moi passer, et je m'assurerai de dire du bien de vous deux au propriétaire.";
			link.l1.go = "mtraxx_10";
		break;
		
		case "mtraxx_soldier_2":
            dialog.text = "Vous avez une langue d'argent, vous, le radin. Bien, allez-y. Mais n'oubliez pas de dire au patron que nous sommes ceux qui vous avons recommandé à lui.";
			link.l1 = "Certainement. Merci.";
			link.l1.go = "plantation_exit";
		break;
		
		case "mtraxx_PlantVykup_2":
            dialog.text = "Vous connaissez bien les prix actuels, Capitaine ! Vous avez un véritable talent pour la négociation, même si vous avez l'air d'un novice. Très bien, si vos marchandises sont vraiment de première classe, je suppose que je devrais ajouter un petit extra pour vous.";
			link.l1 = "Bien sûr, de première classe, je le jure! Une chose de plus, monsieur. J'aimerais vous acheter quelque chose.";
			link.l1.go = "mtraxx_PlantVykup_3";
		break;
		
		case "mtraxx_PlantVykup_3":
            dialog.text = "Oh? Et qu'est-ce que ce pourrait être?";
			link.l1 = "Quelqu'un, pas quelque chose. J'aimerais acheter un de vos esclaves comme serviteur personnel. Est-ce possible?";
			link.l1.go = "mtraxx_PlantVykup_4";
		break;
		
		case "mtraxx_PlantVykup_4":
            dialog.text = "Aucun problème. Nous trouverons quelqu'un de convenable pour vous.";
			link.l1 = "Je suis intéressé par un esclave spécifique. Celui avec le visage charmant-quelqu'un dont vous n'auriez pas honte d'amener à des événements formels ou de servir du vin à vos invités. Il s'est présenté comme Jean Picard. Nous nous sommes déjà bien entendus.";
			link.l1.go = "mtraxx_PlantVykup_5";
		break;
		
		case "mtraxx_PlantVykup_5":
			if (GetSummonSkillFromName(pchar, SKILL_COMMERCE) >= 70)
			{
				dialog.text = "Oui, il y a une demande pour Jean Picard - pas seulement pour servir du vin. Un Anglais influent m'a déjà contacté. Un homme nommé, comment était-ce... Pattornson? Il m'a remis une lettre.";
				link.l1 = "Mais ni Pattornson ni son client ne se sont encore présentés. Je suis prêt à vous acheter Jean ici et maintenant. Nommez votre prix - les dames attendent!";
				link.l1.go = "mtraxx_PlantVykup_10";
				notification("Skill Check Passed", SKILL_COMMERCE);
			}
			else
			{
				dialog.text = "Ah, je comprends. Mais je crains de devoir refuser - Jean Picard n'est pas à vendre. Je suis désolé, señor.";
				link.l1 = "Oh? Pourquoi cela? Je suis prêt à payer gracieusement. Nommez simplement votre prix.";
				link.l1.go = "mtraxx_PlantVykup_6";
				notification("Skill Check Failed (70)", SKILL_COMMERCE);
			}
		break;
		
		case "mtraxx_PlantVykup_6":
            dialog.text = "Inestimable. Il a déjà un acheteur. Je lui ai promis à quelqu'un d'autre. Il n'y a rien de plus à dire. Revenons à notre accord initial et terminons l'échange.";
			link.l1 = "Hmm, comme vous voulez, senor.";
			link.l1.go = "mtraxx_PlantVykup_7";
		break;
		
		case "mtraxx_PlantVykup_7":
            dialog.text = "Splendide! C'est une affaire rentable pour nous deux! Quand ferons-nous l'échange?";
			link.l1 = "Je devrais préparer les marchandises d'abord. Vous aussi, je crois. Commençons l'échange demain à quatre heures de l'après-midi. Mes hommes livreront les caisses avant le coucher du soleil.";
			link.l1.go = "mtraxx_PlantVykup_8";
		break;
		
		
		case "mtraxx_PlantVykup_8":
            dialog.text = "Marché conclu. Eh bien, je te verrai demain, senor!";
			link.l1 = "Au revoir...";
			link.l1.go = "mtraxx_PlantVykup_9";
		break;
		
		case "mtraxx_PlantVykup_9":
            DialogExit();
			NextDiag.CurrentNode = "plantator_1";
			pchar.questTemp.mtraxx_PlantVykup2 = true;
			DeleteAttribute(pchar, "questTemp.mtraxx_PlantVykup");
			DoFunctionReloadToLocation("Shore37", "goto", "goto6", "Mtraxx_PlantPlantVykup_1");
		break;
		
		case "mtraxx_PlantVykup_10":
            dialog.text = "Comme vous voudrez, senor. Mais comprenez, le prix est raide : cinq cents doublons.";
			if (PCharDublonsTotal() >= 500)
			{
				link.l1 = "Ce n'est pas un problème - voici. Un bon serviteur personnel vaut plus qu'un esclave ordinaire, comme vous le savez bien.";
				link.l1.go = "mtraxx_PlantVykup_11";
			}
			else
			{
				link.l2 = "C'est un sacré prix que vous avez fixé, monsieur. Mais je suis très intéressé par cet esclave. Attendez ici. Si Pattornson se pointe, dites-lui que Picard a déjà été vendu - ha-ha-ha!";
				link.l2.go = "mtraxx_PlantVykup_13";
			}
		break;
		
		case "mtraxx_PlantVykup_11":
            dialog.text = "Tu as raison. Je vais faire les arrangements. Picard t'attendra dehors.";
			link.l1 = "Bonjour, monami.";
			link.l1.go = "mtraxx_PlantVykup_12";
			RemoveDublonsFromPCharTotal(500);
		break;
		
		case "mtraxx_PlantVykup_12":
            DialogExit();
			NextDiag.CurrentNode = "plantator_1";
			pchar.questTemp.mtraxx_PlantVykup3 = true;
			DeleteAttribute(pchar, "questTemp.mtraxx_PlantVykup");
			DoFunctionReloadToLocation("Maracaibo_ExitTown", "rld", "loc17", "Mtraxx_PlantPlantVykup_2");
		break;
		
		case "mtraxx_PlantVykup_13":
            dialog.text = "S'il vient avec le montant total, je doute que je le refuserai. Alors dépêche-toi, Capitaine.";
			link.l1 = "Je reviendrai bientôt.";
			link.l1.go = "mtraxx_PlantVykup_14";
		break;
		
		case "mtraxx_PlantVykup_14":
            DialogExit();
			NextDiag.CurrentNode = "mtraxx_PlantVykup_15";
			DeleteAttribute(pchar, "questTemp.mtraxx_PlantVykup");
		break;
		
		case "mtraxx_PlantVykup_15":
            dialog.text = "Avez-vous apporté l'or pour Jean Picard, Capitaine? Le temps presse.";
			if (PCharDublonsTotal() >= 500)
			{
				link.l1 = "Je suis bien conscient de cela. Alors voici, prenez votre or et donnez-moi mon nouveau domestique.";
				link.l1.go = "mtraxx_PlantVykup_16";
			}
			else
			{
				link.l2 = "Toujours en train de le ramasser - c'est vous qui avez fixé un prix si élevé, senor.";
				link.l2.go = "mtraxx_PlantVykup_14";
			}
		break;
		
		case "mtraxx_PlantVykup_16":
            dialog.text = "Je n'ai jamais vu quelqu'un dépenser autant pour acquérir un serviteur. Mais à en juger par la façon dont vous êtes bien habillé, vous devez être habitué à de tels achats grandioses. J'informerai mes hommes, et Picard vous attendra à la sortie.";
			link.l1 = "Bonjour, monami.";
			link.l1.go = "mtraxx_PlantVykup_12";
			RemoveDublonsFromPCharTotal(500);
		break;
	}
} 
