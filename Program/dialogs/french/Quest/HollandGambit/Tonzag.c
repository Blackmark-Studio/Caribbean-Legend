// Эркюль Тонзаг, он же Плешивый Гастон
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
			if (CheckAttribute(pchar, "questTemp.HWIC.Self") && pchar.questTemp.HWIC.Self == "MainBegin")
			{
				dialog.text = "Eh bien, bonjour, "+pchar.name+". Heureux de vous voir en vie.";
				link.l1 = "Gaston ! Est-ce toi ?";
				link.l1.go = "SJ_talk";
				break;
			}
			if (CheckAttribute(pchar, "questTemp.HWIC.Self") && pchar.questTemp.HWIC.Self == "MeetTonzag")
			{
				dialog.text = "Salutations, "+pchar.name+"Je sais déjà tout sur tes affaires - John m'a tout raconté. Je ne sais même pas quoi dire. Je t'admire !";
				link.l1 = "Je suis ravi d'entendre de tels éloges de ta part, Hercule !";
				link.l1.go = "SJ_talk_11";
				break;
			}
			dialog.text = "Bon après-midi. Avez-vous des affaires pour moi ?";
			link.l1 = "Non. Ma faute. Je suis désolé. Adieu. .";
			link.l1.go = "exit";	
			NextDiag.TempNode = "First time";
		break;

		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
		case "SJ_talk":
			dialog.text = "Vous me connaissiez sous ce nom-là. Mais mon vrai nom est Hercule. Hercule Tonzag.";
			link.l1 = "Saint Seigneur ! Je suis également heureux de vous voir... Je ne vous ai pas reconnu dans la chaleur de la bataille. Vous êtes arrivé juste à temps avec votre aide.";
			link.l1.go = "SJ_talk_1";
		break;
		
		case "SJ_talk_1":
			dialog.text = "Juste après ton départ, j'ai appris que Fleetwood avait renforcé les efforts pour protéger sa maison. J'ai suggéré qu'il pourrait y avoir un piège derrière cela. J'ai immédiatement mis les voiles vers Antigua sur mon navire 'Crépuscule' - et, comme tu le vois maintenant, pour une bonne raison.";
			link.l1 = "C'est vrai. J'ai à peine réussi à me débarrasser des gardes à l'intérieur de la maison, mais j'étais trop épuisé pour continuer à me battre dans la rue...";
			link.l1.go = "SJ_talk_2";
		break;
		
		case "SJ_talk_2":
			dialog.text = "Apres ce combat, Fleetwood avait mis un espion hollandais sur la liste des recherchés. Ils pensaient que vous étiez un espion hollandais. Il est à une haine invétérée avec eux. Le pire, c'est qu'un soldat dans la maison a survécu et se souvenait de votre visage. Mais, de toute façon, ce n'est plus un problème maintenant. J'ai terminé ce que vous aviez commencé. Ce soldat ne pourra plus reconnaître personne, et personne ne le reconnaîtra...";
			link.l1 = "Tu l'as tué ? Je vois...";
			link.l1.go = "SJ_talk_3";
		break;
		
		case "SJ_talk_3":
			dialog.text = "Oui. Pendant que tu étais inconscient chez John, j'ai blessé Fleetwood, mais ce salaud a réussi à survivre. Je l'ai rendu aveugle - j'ai jeté du poivre dans ses yeux, puis je l'ai frappé avant qu'il ait la chance de dégainer son épée. Mais la vermine portait une cotte de mailles sous son uniforme - cela lui a sauvé la vie. Malin. Maintenant, il reste alité chez lui avec une sécurité renforcée. C'est bien malheureux qu'il ait survécu.";
			link.l1 = "Alors, votre tâche principale à Antigua était d'éliminer Fleetwood ?";
			link.l1.go = "SJ_talk_4";
		break;
		
		case "SJ_talk_4":
			dialog.text = "Généralement, oui. Maintenant, cela semble impossible, cependant - la maison est toujours verrouillée, il y a une demi-douzaine de gardes triés sur le volet en service jour et nuit, et ils n'autorisent que son homme de confiance à le voir - un vieux canonnier Charlie, surnommé le Knippel.";
			link.l1 = "C'est déjà quelque chose...";
			link.l1.go = "SJ_talk_5";
		break;
		
		case "SJ_talk_5":
			dialog.text = "Attendez un peu... Allez-vous vous mêler de cette affaire ?";
			link.l1 = "Pourquoi pas? Tu n'as pas besoin d'aide? Tu m'as sauvé, et je veux aider. De plus, j'ai toujours besoin de pièces.";
			link.l1.go = "SJ_talk_6";
			// belamour legendary edition -->
			link.l2 = "Pourquoi pas ? Vous êtes des gens sérieux. Et les gens sérieux paient généreusement. Je cherche juste un emploi.";
			link.l2.go = "SJ_talk_6a";
		break;
		
		case "SJ_talk_6a":
			ChangeCharacterComplexReputation(pchar, "nobility", -1);
			AddCharacterExpToSkill(pchar, "Sneak", 120);
			dialog.text = "Crois-moi, ami, tu n'y arriveras pas. Tu es un brave gars, un véritable talent, et le journal de bord que tu as récupéré m'a aidé à planifier une tentative contre la vie de Fleetwood, tu as bien fait de découper les gardes - mais tu ne pourras jamais atteindre Fleetwood maintenant. Même moi, je n'ai pas la moindre idée de comment faire.";
			if (pchar.Ship.Type == SHIP_NOTUSED)
			{
				link.l1 = "Je vais y réfléchir. J'ai encore le temps. Dommage que mon navire ait été saisi, et je n'ai pas d'équipage.";
				link.l1.go = "SJ_talk_7";
			}
			else
			{
				link.l1 = "Je vais y réfléchir. J'ai du temps et un navire.";
				link.l1.go = "SJ_talk_8";
			}
		break;
		
		case "SJ_talk_6":
			AddCharacterExpToSkill(pchar, "Leadership", 120);
			// <-- legendary edition
			dialog.text = "Crois-moi, ami, tu n'y parviendras pas. Tu es un brave gars, un vrai talent, et le journal de bord que tu as ramené m'a aidé à planifier une tentative contre la vie de Fleetwood, tu as bien fait de découper les gardes - mais tu ne pourras jamais atteindre Fleetwood maintenant. Même moi, je n'ai pas la moindre idée de comment y parvenir.";
			if (pchar.Ship.Type == SHIP_NOTUSED)
			{
				link.l1 = "Je vais y réfléchir. J'ai encore du temps. C'est bien dommage que mon navire ait été saisi, et que je n'aie pas d'équipage.";
				link.l1.go = "SJ_talk_7";
			}
			else
			{
				link.l1 = "Je vais y réfléchir. J'ai le temps et un navire.";
				link.l1.go = "SJ_talk_8";
			}
		break;
		
		case "SJ_talk_7":
			dialog.text = "Ne t'inquiète pas pour ça. Quand ta vieille barcasse a été mise sous arrestation, j'ai pris tous tes officiers et quelques marins à bord de mon 'Crépuscule'. Ils savent que tu es en vie et ont accepté de rester en service. Et en récompense pour le journal, je te cède mon navire 'Crépuscule'.";
			link.l1 = "Merci ! Je m'en souviendrai !";
			link.l1.go = "SJ_talk_9";
			if(GetSummonSkillFromName(pchar, SKILL_SAILING) < 46)
			{
				pchar.Ship.Type = GenerateShipHand(pchar, SHIP_CAREERLUGGER, 12, 580, 30, 800, 20000, 16.5, 65.5, 1.6);
			}
			else
			{
				pchar.Ship.Type = GenerateShipHand(pchar, SHIP_SCHOONER, 16, 1900, 50, 1350, 25000, 13.5, 55.0, 1.10);
			}
			pchar.Ship.name = "Twilight";
			SetBaseShipData(pchar);
			if(GetSummonSkillFromName(pchar, SKILL_SAILING) < 46) pchar.Ship.Cannons.Type = CANNON_TYPE_CANNON_LBS12;
			else pchar.Ship.Cannons.Type = CANNON_TYPE_CANNON_LBS16;
			SetCrewQuantityFull(pchar);
			pchar.Ship.Crew.Morale = 80;
			pchar.Ship.Crew.Exp.Sailors = 90;
			pchar.Ship.Crew.Exp.Cannoners = 70;
			pchar.Ship.Crew.Exp.Soldiers = 70;
			SetCharacterGoods(pchar, GOOD_BALLS, 100);
			SetCharacterGoods(pchar, GOOD_GRAPES, 100);
			SetCharacterGoods(pchar, GOOD_KNIPPELS, 100);
			SetCharacterGoods(pchar, GOOD_BOMBS, 100);
			SetCharacterGoods(pchar, GOOD_FOOD, 100);
			SetCharacterGoods(pchar, GOOD_POWDER, 300);
			SetCharacterGoods(pchar, GOOD_WEAPON, 60);
			SetCharacterGoods(pchar, GOOD_MEDICAMENT, 60);
		break;
		
		case "SJ_talk_8":
			AddMoneyToCharacter(pchar, 15000);
			dialog.text = "Oui, je voudrais vous payer pour le journal. 15000 pesos - je n'ai pas plus pour le moment, malheureusement. Nous réglerons cela en un jour. ";
			link.l1 = "Pas besoin. C'est suffisant. Si tu n'étais pas arrivé à temps, je n'aurais de toute façon pas eu besoin d'argent.";
			link.l1.go = "SJ_talk_9";
		break;
		
		case "SJ_talk_9":
			dialog.text = "D'accord, "+pchar.name+", je dois y aller. Je ne retourne pas à Bridgetown pour l'instant. Si jamais tu as besoin de moi - demande à John. Bonne chance !";
			link.l1 = "Bonne chance, Hercule !";
			link.l1.go = "SJ_talk_10";
		break;
		
		case "SJ_talk_10":
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1_back", "none", "", "", "", 10);
			DialogExit();
			AddQuestRecord("Holl_Gambit", "3-13");
			pchar.questTemp.HWIC.Self = "HuntFleetwood";
			AddLandQuestMark(characterFromId("Merdok"), "questmarkmain");
		break;
		
		case "SJ_talk_11":
			dialog.text = "Je voudrais vous présenter cette armure pour avoir éliminé Fleetwood. Elle vous protégera dans les futures batailles. Allons voir John maintenant. Il veut vous parler et vous proposer... une affaire intéressante.";
			link.l1 = "Merci pour le cadeau. D'accord, allons-y...";
			link.l1.go = "SJ_talk_12";
		break;
		
		case "SJ_talk_12":
			DialogExit();
			GiveItem2Character(pchar, "cirass7");//дать вещь
			sld = characterFromId("Merdok");
			AddLandQuestMark(sld, "questmarkmain");
			LAi_SetOwnerType(sld);
			LAi_SetActorType(npchar);
			LAi_ActorFollow(npchar, pchar, "", -1);
			AddQuestRecord("Holl_Gambit", "3-35");
		break;
		
		case "Tonzag_hired":
			dialog.text = "J'aimerais aussi vous parler, capitaine. J'allais vous enseigner mon métier, mais maintenant je vois que c'est moi qui devrais apprendre de vous. Engagez-moi comme officier sur votre navire - vous ne le regretterez pas.";
			link.l1 = "C'est un plaisir, Hercule ! Bienvenue à bord de l'équipage !";
			link.l1.go = "Tonzag_hired_1";
			link.l2 = "Hercule, je ne peux pas m'imaginer être ton supérieur. Merci pour ton offre, mais je ne peux tout simplement pas te voir comme mon subordonné.";
			link.l2.go = "Tonzag_exit";
		break;
		
		case "Tonzag_hired_1"://Тонзага - в офицеры
			DialogExit();
			DeleteAttribute(npchar, "LifeDay");
			npchar.quest.OfficerPrice = sti(pchar.rank)*500;
			npchar.OfficerWantToGo.DontGo = true;
			npchar.loyality = MAX_LOYALITY;
			AddPassenger(pchar, npchar, false);
			SetCharacterRemovable(npchar, true);
			npchar.Payment = true;
			LAi_SetOfficerType(npchar);
			npchar.greeting = "tonzag_hire";
			NextDiag.CurrentNode = "tonzag_officer";
			npchar.quest.meeting = true;
			npchar.HoldEquip = true;
			npchar.OfficerImmortal = true;
			npchar.Health.HP       = 60.0; 
			npchar.Health.maxHP    = 60.0;
			LAi_SetImmortal(npchar, false);
			SetCharacterPerk(npchar, "ShipEscape");
			LAi_group_MoveCharacter(npchar, LAI_GROUP_PLAYER);
			SaveCurrentNpcQuestDateParam(npchar, "HiredDate");
		break;
		
		case "Tonzag_exit":
			dialog.text = "Comme vous le souhaitez, "+pchar.name+"À bientôt. Peut-être nous reverrons-nous. Cela a été un plaisir de travailler avec vous.";
			link.l1 = "Bonne chance, ami !";
			link.l1.go = "Tonzag_exit_1";
		break;
		
		case "Tonzag_exit_1":
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1_back", "none", "", "", "", -1);
			npchar.lifeday = 0;
			DialogExit();
		break;
		
		//--> ----------------------------------- офицерский блок ------------------------------------------
		case "tonzag_officer":
			dialog.text = "Je vous écoute, capitaine. Que voulez-vous dire ?";
			if (CheckAttribute(pchar, "questTemp.Dolly_Tieyasal") && !CheckAttribute(npchar, "quest.Tieyasal"))
			{
				Link.l4 = "Hercule, je vais à l'ancienne cité indienne de Tayasal et, ce qui est encore plus inhabituel, mon chemin passe par une statue de téléportation. Te joindras-tu à moi ?";
				Link.l4.go = "tieyasal";
			}
			
			////////////////////////казначей///////////////////////////////////////////////////////////
           	// boal отчёт о корабле
			if(CheckAttribute(NPChar, "treasurer") && NPChar.treasurer == 1)
			{
			    Link.l11 = "Hercule, donne-moi un rapport complet du navire.";
			    Link.l11.go = "QMASTER_1";
				
			    // Warship. Автозакупка товара
				Link.l12 = "Je veux que tu achètes certaines marchandises chaque fois que nous sommes à quai.";
				Link.l12.go = "QMASTER_2";
			}

			if (CheckAttribute(NPChar, "IsCompanionClone"))//////////////////компаньон//////////////////////////////////////////////
			{
				//dialog.text = "Je suis arrivé selon vos ordres, capitaine.";
				Link.l2 = "Je dois vous donner plusieurs ordres.";
				Link.l2.go = "Companion_Tasks";
				NextDiag.TempNode = "tonzag_officer";// не забыть менять в зависисомости от оффа
				break;
			}
			Link.l1 = "Ecoutez mon ordre !";
            Link.l1.go = "stay_follow";
			link.l2 = "Rien pour le moment. Au repos!";
			link.l2.go = "exit";
			NextDiag.TempNode = "tonzag_officer";
		break;
		
		/////////////////////////// ответы для казначея ///////////////////////////////////
		case "QMASTER_1":
			dialog.Text = "Capitaine, je suis navré, mais je ne m'occupe pas des chiffres et des calculs. Demandez à van Merden - il a un talent pour ces choses, cependant, je doute qu'il soit intéressé à quitter son nid.";
			Link.l1 = "Tu as raison, Hercule. Bah, faut que je me trouve un commissaire...";
			Link.l1.go = "exit";
		break;	

		case "QMASTER_2":
			dialog.text = "Capitaine, quand j'étais aubergiste à la Barbade, je n'achetais que du rhum et des provisions. Et par provisions, j'entends de la vraie nourriture, pas des biscuits et du boeuf salé. Désolé, mais ce n'est pas mon département.";
			link.l1 = "Peut-être devrions-nous transformer mon navire en taverne... Je plaisante, Hercule. Quoi qu'il en soit, je le ferai moi-même.";
			link.l1.go = "exit";
		break;
		
		//Указания для компаньона 19.02.08 -->/////////////////////////////////////////////////////////////////////////////////////////
		case "Companion_Tasks":
			dialog.Text = "Je vous écoute.";
			Link.l1 = "C'est une affaire d'abordage.";
			Link.l1.go = "Companion_TaskBoarding";
			Link.l2 = "C'est à propos de votre navire.";
			Link.l2.go = "Companion_TaskChange";
			Link.l8 = "Rien jusqu'à présent.";
			Link.l8.go = "exit";
		break;

		case "Companion_TaskBoarding":
			dialog.Text = "Alors, quel est ton souhait.";
			Link.l1 = "N'abordez pas les navires ennemis. Prenez soin de vous et de l'équipage.";
			Link.l1.go = "Companion_TaskBoardingNo";
			Link.l2 = "Je veux que tu abordes les navires ennemis.";
			Link.l2.go = "Companion_TaskBoardingYes";
		break;

		case "Companion_TaskChange":
			dialog.Text = "Alors, quel est votre souhait.";
			Link.l1 = "Je voudrais que tu ne changes pas ton navire pour un autre après l'abordage. Il est trop précieux.";
			Link.l1.go = "Companion_TaskChangeNo";
			Link.l2 = "Lorsque vous abordez des navires ennemis, vous pouvez les prendre pour vous, s'ils sont convenables.";
			Link.l2.go = "Companion_TaskChangeYes";
		break;

		case "Companion_TaskBoardingNo":
			dialog.Text = "Aye-aye.";
			Link.l1 = "Repos.";
			Link.l1.go = "exit";
			NPChar.Tasks.CanBoarding = false;
		break;

		case "Companion_TaskBoardingYes":
			dialog.Text = "Ce sera fait.";
			Link.l1 = "Repos.";
			Link.l1.go = "exit";
			NPChar.Tasks.CanBoarding = true;
		break;

		case "Companion_TaskChangeNo":
			dialog.Text = "D'accord, capitaine.";
			Link.l1 = "Ce sera fait.";
			Link.l1.go = "exit";
			NPChar.Tasks.CanChangeShipAfterBoarding = false;
		break;

		case "Companion_TaskChangeYes":
			dialog.Text = "Ce sera fait.";
			Link.l1 = "Repos.";
			Link.l1.go = "exit";
			NPChar.Tasks.CanChangeShipAfterBoarding = true;
		break;
	//	<========////////////////////////////////////////
		
		case "stay_follow":
            dialog.Text = "Quels sont vos ordres ? ?";
            Link.l1 = "Reste ici !";
            Link.l1.go = "Boal_Stay";
            Link.l2 = "Suis-moi et ne reste pas à la traîne !";
            Link.l2.go = "Boal_Follow";
			sGun = GetCharacterEquipByGroup(NPChar, GUN_ITEM_TYPE);
			if(sGun != "")
			{
				rItm = ItemsFromID(sGun);
				if(CheckAttribute(NPChar, "chr_ai.gun.bulletNum") && sti(NPChar.chr_ai.gun.bulletNum) > 1)
				{
					Link.l3 = "Changez le type de vos munitions.";
					Link.l3.go = "SetGunBullets";
				}	
			}		
		break;
		
		case "SetGunBullets":
			Dialog.Text = "Choix du type de munitions :";
			sGun = GetCharacterEquipByGroup(NPChar, GUN_ITEM_TYPE);
			rItm = ItemsFromID(sGun);
			makearef(rType, rItm.type);	
			for (i = 0; i < sti(NPChar.chr_ai.gun.bulletNum); i++)
			{
				sAttr = GetAttributeName(GetAttributeN(rType, i));
				sBullet = rItm.type.(sAttr).bullet;
				rItem = ItemsFromID(sBullet);								
				attrL = "l" + i;
				Link.(attrL) = GetConvertStr(rItem.name, "ItemsDescribe.txt");;
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
			notification(GetFullName(NPChar)+" "+XI_ConvertString("AmmoSelectNotif")+GetConvertStr(rItem.name, "ItemsDescribe.txt")+"", "AmmoSelect");
			DeleteAttribute(NPChar,"SetGunBullets");
			DialogExit();
		break;		
		
        case "Boal_Stay":
            Pchar.questTemp.HiringOfficerIDX = GetCharacterIndex(Npchar.id);
            AddDialogExitQuestFunction("LandEnc_OfficerStay");
            dialog.Text = "Oui !";
            Link.l1 = "Repos.";
            Link.l1.go = "Exit";
            Npchar.chr_ai.tmpl = LAI_TMPL_STAY;
        break;
        
        case "Boal_Follow":
            SetCharacterTask_FollowCharacter(Npchar, PChar);
            dialog.Text = "Ouais !";
            Link.l1 = "Repos.";
            Link.l1.go = "Exit";
        break;
	//<-- ----------------------------------- офицерский блок ----------------------------------------
	
	// на Тайясаль
		case "tieyasal":
			dialog.text = "Tu es un sacré veinard, capitaine. Je suis content de t'avoir rejoint quand moi, toi et John travaillions ensemble. Qu'un requin me bouffe, si je ne te soutiens pas dans cette entreprise !";
			link.l1 = "Merci, Hercule ! Je suis ravi d'avoir eu raison à ton sujet.";
			link.l1.go = "tieyasal_1";
		break;
		
		case "tieyasal_1":
			dialog.text = "Alors, quand partons-nous?";
			link.l1 = "Un peu plus tard. Maintenant, nous devrions nous préparer pour le voyage.";
			link.l1.go = "tieyasal_2";
		break;
		
		case "tieyasal_2":
			DialogExit();
			AddQuestRecord("Tieyasal", "23");
			npchar.quest.Tieyasal = "teleport";
		break;
		
		case "tonzag_jailed":
			dialog.text = "Pratiquement rien, Cap. Si cela concernait notre affaire, ils nous auraient déjà mis sur la table de torture.\nPuisqu'ils ne nous ont pas emmenés pour un interrogatoire immédiatement, l'affaire n'est apparemment pas urgente.\nSoit un coup monté, soit une extorsion.\nIls vont nous faire mariner ici pendant quelques jours sans rien expliquer. Puis ils viendront avec une offre, que nous accepterons.";
			link.l1 = "Expérience personnelle ?";
			link.l1.go = "tonzag_jailed_1";
			link.l2 = "Eh bien, y a-t-il un moyen de les faire venir avec une telle offre dès maintenant ?";
			link.l2.go = "tonzag_jailed_2";
			locCameraFromToPos(-14.82, 0.92, 2.74, true, -60.00, -5.60, -22.70);
		break;
		
		case "tonzag_jailed_1":
			dialog.text = "Bien sûr. Gruoh a autrefois été payée par les proches d'un homme mort pour l'épargner des caresses d'adieu du bourreau de Trinidad.\nElle a payé le commandant pour le droit de traverser les cellules de détention. Pratique courante - beaucoup paient les soldats pour avoir l'opportunité de tourmenter ceux qui ne peuvent pas riposter sans témoins.\nL'homme est mort paisiblement et sans souffrance. Travail propre et décent.";
			link.l1 = "Gruoh ? Qui est-ce ?";
			link.l1.go = "tonzag_jailed_1_1";
		break;
		
		case "tonzag_jailed_1_1":
			dialog.text = "Désolé, Cap. Mauvais endroit et mauvais moment.";
			link.l1 = " ";
			link.l1.go = "exit";
		break;
		
		case "tonzag_jailed_2":
			dialog.text = "Nous pouvons essayer. Attendons l'heure du repas, et j'échangerai quelques mots avec le sentinelle. Vous voyez, ils n'ont toujours pas appris à fouiller correctement. Eh...";
			link.l1 = "Qu'est-ce qui ne va pas ?";
			link.l1.go = "tonzag_jailed_2_1";
		break;
		
		case "tonzag_jailed_2_1":
			dialog.text = "Étrange sentiment, Capitaine. Je l'appellerais même une prémonition. Excusez-moi, parlons plus tard.";
			link.l1 = "Bonjour, mon ami.";
			link.l1.go = "exit";
		break;
		
		case "tonzag_killed_hunters":
			dialog.text = "Ai-je manqué quelque chose, Capitaine ?";
			link.l1 = "Oh, rien de spécial, juste un autre jour en mer. Regarde, vieux brigand ! Tu m'as fait un sacré foutoir ici.";
			link.l1.go = "tonzag_killed_hunters_1";
		break;
		
		case "tonzag_killed_hunters_1":
			dialog.text = "Le sang se lave à l'eau froide, Capitaine. Nous devons parler.";
			link.l1 = "Tu crois ? Ça ne ferait pas de mal de survivre à cette journée pour commencer.";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("Tonzag_Victory");
		break;
		
		case "tonzag_after_victory_helena":
			dialog.text = "Je suis ravi de te voir aussi, Rumba. Capitaine, je ne vais pas vous déranger, nous parlerons plus tard.";
			link.l1 = " ";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("Tonzag_HelenBoardingDialog1");
		break;
		
		case "tonzag_after_victory_mary":
			dialog.text = "Salut, Rouquin. Capitaine, je ne dérangerai pas, nous parlerons plus tard.";
			link.l1 = "";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("Tonzag_MaryBoardingDialog1");
		break;
		
		case "tonzag_after_victory_alonso":
			dialog.text = "Capitaine, je ne vous dérangerai pas, nous parlerons plus tard.";
			link.l1 = "";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("Tonzag_ShowFrame");
		break;
		
		case "tonzag_drink":
			dialog.text = "Prêt à m'écouter, Capitaine ?";
			link.l1 = "Il est grand temps que nous parlions, Hercule. Je viens de réaliser que je ne sais presque rien de toi.";
			link.l1.go = "tonzag_drink_1";
		break;
		
		case "tonzag_drink_1":
			dialog.text = "Il est donc temps de faire connaissance. Passons sur les premières années, ne serait-ce que parce qu'il n'y a rien à en dire - un soldat victorieux, un soldat vaincu, un déserteur, un maraudeur... vous savez comment ça se passe.";
			link.l1 = "En fait, je n'en ai aucune idée, mais jusqu'à présent, cela semble assez ordinaire.";
			link.l1.go = "tonzag_drink_2";
		break;
		
		case "tonzag_drink_2":
			dialog.text = "Les perspectives de carrière après un tel parcours militaire étaient peu nombreuses pour moi - un bandit, un pendu, ou un garde digne de la Compagnie néerlandaise des Indes occidentales. J'ai choisi la dernière option, comme vous le comprenez.";
			link.l1 = "As-tu déserté de là aussi ?";
			link.l1.go = "tonzag_drink_3";
		break;
		
		case "tonzag_drink_3":
			dialog.text = "Au contraire, j'y ai fait carrière. J'ai reçu une offre pour rejoindre l'aile de combat du département de renseignement de la Compagnie, où j'ai rencontré ma future épouse.";
			link.l1 = "D'accord, jusqu'à présent l'histoire est assez paisible... surtout si tu ne réfléchis pas trop aux méthodes des Hollandais.";
			link.l1.go = "tonzag_drink_4";
		break;
		
		case "tonzag_drink_4":
			dialog.text = "Tu ne gagneras pas une fortune en étant honnête, et tu peux combattre la concurrence de diverses manières. Oui, nous opérions avec des méthodes spéciales...";
			link.l1 = "Je suppose que je comprends ce que tu veux dire...";
			link.l1.go = "tonzag_drink_5";
		break;
		
		case "tonzag_drink_5":
			dialog.text = "Oui, cela pouvait être n'importe quoi : de la piraterie à l'incendie de entrepôts avec des marchandises. À la fin, le stratagème a été découvert, et nous avons été dissous... sur le papier, bien sûr. C'est ainsi que la Ligue est née, connue et contrôlée uniquement par les dirigeants choisis des échelons supérieurs de la Compagnie. Pour un hors-la-loi caribéen qui vaut quelque chose, il n'y avait que deux options : la piraterie ou la Ligue. Et la Ligue payait généralement mieux. \nPour la plupart, la Ligue travaillait encore pour les Hollandais, mais elle pouvait aussi accepter des commandes secondaires...";
			link.l1 = "Les choses commencent à s'éclaircir...";
			link.l1.go = "tonzag_drink_6";
		break;
		
		case "tonzag_drink_6":
			dialog.text = "La Ligue était derrière cette farce à Tortuga. Et puis ce groupe de débarquement...";
			link.l1 = "Je m'en doutais. Mais pourquoi ?";
			link.l1.go = "tonzag_drink_7";
		break;
		
		case "tonzag_drink_7":
			dialog.text = "Parce que personne ne quitte la Ligue vivant, et on ne peut pas s'en tirer à bon compte avec ce que nous avons fait là-bas, Capitaine. Je voulais prendre ma retraite, alors j'ai essayé quand même. Comme vous pouvez le voir, pas très réussie.";
			link.l1 = "Voulez-vous dire que vos anciens collègues ont engagé d'énormes dépenses financières, sacrifié presque une centaine de personnes, brûlé un brûlot, et risqué leur vaisseau de guerre juste pour... vous tuer pour désertion ?";
			link.l1.go = "tonzag_drink_8";
		break;
		
		case "tonzag_drink_8":
			dialog.text = "J'étais plus qu'un simple gringalet dans la Ligue, Capitaine. J'en sais trop à son sujet. On ne peut pas simplement me laisser partir, et ils doivent le faire comprendre, pour que personne d'autre n'envisage de quitter le métier... Ils ont essayé de m'atteindre avant... il y a fort longtemps... Ils ont tué ma femme et m'ont défiguré, même si cela leur a coûté cher. Il n'y a pas de fin heureuse à cette histoire, Capitaine. Donnez simplement un ordre, et je quitterai le navire pour m'occuper d'eux moi-même, une fois pour toutes.";
			link.l1 = "Ne raconte pas de bêtises, Hercule... Et quel rôle a joué Lucas Rodenburg dans tout cela ? Il a dû être impliqué dans ces affaires ! Ton, ou plutôt son, 'organisation', la Ligue...";
			link.l1.go = "tonzag_drink_9";
		break;
		
		case "tonzag_drink_9":
			dialog.text = "Différentes agences, Capitaine. Certes, elles obéissaient souvent à la même personne et travaillaient étroitement. Mais les agents spéciaux de Rodenburg livraient des frappes d'une précision redoutable, tandis que la Ligue menait des opérations de masse. Et maintenant, qu'est devenu la Ligue ? L'organisation n'existe plus, comme vous pouvez le voir : je suis ici avec vous, John Murdock est parti, Longway s'est enfui, Van Berg repose au fond de la mer, Rodenburg a été exécuté... Pourtant, je devais une fière chandelle à ce gredin défunt. Il m'a remarqué dans la Ligue, et lorsque j'ai essayé de la quitter, il m'a sorti de sérieux ennuis et m'a fait son adjoint. Bien sûr, les autres n'ont pas aimé ça, mais personne n'a osé lui désobéir... Et puis, dans les circonstances connues, il a décidé de se débarrasser de Murdock et de moi, mais vous êtes intervenu et m'avez pris à votre service. Et alors je me suis dit, 'Voilà ma deuxième chance de rompre avec le passé...' Vous avez déjoué Rodenburg, la Ligue a perdu son mécène, il n'y avait plus de danger... Mais, bien sûr, je me suis trompé... Vieux fou... Mais assez parlé de ça, Capitaine. Réfléchissons à ce qu'il faut faire ensuite, si bien sûr, vous n'envisagez vraiment pas de me laisser partir au premier port.";
			link.l1 = "Je n'en ai pas. Je suppose que tu as un plan ?";
			link.l1.go = "tonzag_drink_10";
		break;
		
		case "tonzag_drink_10":
			dialog.text = "Rien de spécial, en fait. Nous ne les anéantirons jamais tous, mais nous pouvons leur infliger des pertes si importantes que cela ne vaudra pas la peine pour eux de continuer à me...nous poursuivre.";
			link.l1 = "Et comment fait-on cela? Ont-ils un camp?";
			link.l1.go = "tonzag_drink_11";
		break;
		
		case "tonzag_drink_11":
			dialog.text = "Une grande forteresse ? À peine. Ce serait trop visible et dangereux pour la Ligue. Et par pertes, je ne parle pas de pertes humaines - ils se moquent des gens, mais ils n'apprécieront pas de perdre de l'or. L'argent de la Compagnie ne leur parvient plus, n'est-ce pas ? Je doute que la Ligue ait trouvé un nouveau mécène, donc ils doivent extraire de l'or d'ailleurs.";
			link.l1 = "Et quel serait cet endroit?";
			link.l1.go = "tonzag_drink_12";
		break;
		
		case "tonzag_drink_12":
			dialog.text = "Je ne sais pas, Capitaine.";
			link.l1 = "Hercule, mais tu viens juste de dire que tu es poursuivi précisément parce que tu en sais trop !";
			link.l1.go = "tonzag_drink_13";
		break;
		
		case "tonzag_drink_13":
			dialog.text = "Laissez-moi réfléchir... Peut-être que la Ligue opère actuellement contre les Espagnols. Ils sont les principaux candidats pour une bonne secousse. D'ailleurs, Rodenburg était toujours en bons termes avec les gros bonnets castillans. Parfois, il dirigeait les gars de la Ligue vers eux pour divers travaux et interdisait toujours de leur causer du tort, ce qui, soit dit en passant, ne plaisait pas beaucoup aux gars...";
			link.l1 = "De bons termes, dites-vous ? Et qu'en est-il de ce Hidalgo et de son doigt que vous m'avez fait traîner jusqu'à votre taverne ?";
			link.l1.go = "tonzag_drink_14";
		break;
		
		case "tonzag_drink_14":
			dialog.text = "C'était un cas spécial, une commande annexe. Si vous vous sentez coupable, Capitaine, vous pouvez être tranquille - ce Don a eu ce qu'il méritait... Mais je parle d'autre chose : après la disparition de leur employeur, les agents de la Ligue pourraient simplement céder à leurs désirs et essayer de s'emparer d'une bonne part du gâteau espagnol. Grâce à leur travail avec les Espagnols sous Rodenburg, ils savent où et quoi prendre.";
			link.l1 = "Hm... tu as peut-être raison. Mais autant que je sache, personne ne s'introduit vraiment dans les banques espagnoles, en opérant contre les Espagnols en mer - cela dépend de la fortune de dame chance... Peut-être devrions-nous chercher une entreprise espagnole ? Une usine ?";
			link.l1.go = "tonzag_drink_15";
		break;
		
		case "tonzag_drink_15":
			dialog.text = "Supposition raisonnable, Capitaine... Avons-nous d'autres pistes?";
			link.l1 = "Hm... le navire qui nous a attaqués aujourd'hui est allé vers le sud...";
			link.l1.go = "tonzag_drink_16";
		break;
		
		case "tonzag_drink_16":
			dialog.text = "Il est peu probable que son capitaine nous dérange à nouveau, mais il doit avertir les autres que les choses ne se sont pas déroulées comme prévu, et peut-être transporter le personnel ailleurs. Autre chose ?";
			if (CheckAttribute(pchar, "questTemp.TonzagQuest.KnowMain")) {
				link.l1 = "Oui, j'ai eu une conversation amicale avec le commandant de la prison de Tortuga... Il a mentionné quelque chose à propos du continent.";
				link.l1.go = "tonzag_drink_know";
			} else {
				link.l1 = "Non, rien d'autre.";
				link.l1.go = "tonzag_drink_notknow";
			}
		break;
		
		case "tonzag_drink_know":
			dialog.text = "Excellent, Capitaine ! Sud, terre ferme, Espagnols - cela signifie que nous les trouverons rapidement. Levons l'ancre ? Et merci d'avoir écouté mon histoire.";
			link.l1 = "Eh bien, quelle conversation à cœur ouvert nous avons eue... Mettons les voiles !";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("Tonzag_ExitToSea");
		break;
		
		case "tonzag_drink_notknow":
			dialog.text = "Pas grand-chose sur quoi s'appuyer. Mais pour des gens comme nous, c'est suffisant. Allons-nous vers le sud? Chercher une entreprise commerciale espagnole? Et merci d'avoir écouté mon histoire.";
			link.l1 = "Ouais, quelle conversation à cœur ouvert nous avons eue, toi et moi... Levons l'ancre !";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("Tonzag_ExitToSea");
		break;
		
		case "tonzag_dead":
			dialog.text = "Regarde, Capitaine. C'est ainsi qu'ils opèrent.";
			link.l1 = "Et tu as travaillé comme ça aussi ?";
			link.l1.go = "tonzag_dead_1";
		break;
		
		case "tonzag_dead_1":
			dialog.text = "Allons-y, voyons ce qu'il y a à l'intérieur.";
			link.l1 = "";
			link.l1.go = "exit";
			
			NextDiag.TempNode = "tonzag_officer";
			AddDialogExitQuestFunction("Tonzag_AfterDead");
		break;
		
		case "tonzag_afterminefight":
			dialog.text = "Une affaire sordide, Capitaine. Nous avons nettoyé ce repaire, mais ce n'est certainement pas le dernier...";
			link.l1 = "Qu'en est-il de la mine, Hercule ?! Tous ces gens dehors ?! Ils ont aussi été 'débarassés' ! Et que voulait dire ce scélérat ?";
			link.l1.go = "tonzag_afterminefight_1";
		break;
		
		case "tonzag_afterminefight_1":
			dialog.text = "Let's discuss this later, Captain. Their commander survived; we need to interrogate him.";
			link.l1 = "Et s'il ne sait rien ?";
			link.l1.go = "tonzag_afterminefight_2";
		break;
		
		case "tonzag_afterminefight_2":
			dialog.text = "He knows something. Think about it - they were waiting for us, carried out all the gold, and eliminated witnesses. That means they had a plan. I want to take a look around here, and later I'll bring the scoundrel to the ship myself. You should also keep an eye out; perhaps they were too hasty and missed something.";
			link.l1 = "D'accord, mais quand nous serons de retour sur le navire, il y aura une conversation sérieuse à avoir !";
			link.l1.go = "exit";
			
			NextDiag.TempNode = "tonzag_officer";
			locations[FindLocation("LosTeques_town")].locators_radius.reload.gate_back = 1.0;
			DeleteAttribute(&locations[FindLocation("LosTeques_town")], "locators_radius.reload.reload1_back");
			AddDialogExitQuestFunction("Tonzag_PrepareJournal");
		break;
		
		case "tonzag_in_hold":
			dialog.text = "Bonne nouvelle, Capitaine.";
			link.l1 = "Je ne vois rien de bon dans notre situation, Hercule. Allons-y, il faut que nous parlions en privé.";
			link.l1.go = "tonzag_in_hold_1";
		break;
		
		case "tonzag_in_hold_1":
			dialog.text = "Alors, c'est comme ça, hein ? Aye, Capitaine.";
			link.l1 = "";
			link.l1.go = "exit";
			
			NextDiag.TempNode = "tonzag_officer";
			AddDialogExitQuestFunction("Tonzag_EnterAlonso");
		break;
		
		case "tonzag_drink_again":
			dialog.text = "Je vois que nous sommes partis pour une conversation sérieuse, Capitaine.";
			link.l1 = "Oui, et c'est moi qui vais parler. Tout d'abord, ne penses-tu pas qu'une certaine tendance se dessine ici ? Des tas de cadavres nous suivent partout où nous allons ! D'abord, tu prends une volée de mitraille dans le ventre, et le lendemain, plus d'une centaine de personnes, bonnes et moins bonnes, meurent dans... Je ne peux même pas appeler ça une bataille navale ! Un établissement a été anéanti il y a à peine quelques jours, et aujourd'hui nous avons contribué à l'accumulation en massacrant une bande de gens dans les mines.";
			link.l1.go = "tonzag_drink_again_1_1";
		break;
		
		case "tonzag_drink_again_1_1":
			dialog.text = "";
			link.l1 = "Naturellement, je suis inquiet à l'idée que le tas ne devienne une montagne demain, mais ce qui me terrifie vraiment, c'est que tout ce sang est versé à cause d'une seule personne. Et cette personne occupe une position importante dans mon équipage !";
			link.l1.go = "tonzag_drink_again_1";
		break;
		
		case "tonzag_drink_again_1":
			dialog.text = "";
			link.l1 = "Deuxièmement, tu m'as menti, Hercule. Aucun déserteur ne mérite les efforts que tes anciens collègues déploient pour t'éliminer. Que criait notre prisonnier dans les mines ? Traître ? Porto Bello ? Gruoh ? Tu as fait quelque chose, Hercule, et cette fois je veux la vérité.";
			link.l1.go = "tonzag_drink_again_2";
		break;
		
		case "tonzag_drink_again_2":
			dialog.text = "Truth? The truth is, Captain, that I did desert, along with my wife Gruoh. Madame Tonzag didn't want to leave the League; she loved that life, but she loved me even more. We were supposed to take care of a Spanish hidalgo, but he made a better offer. It was our chance, and we both agreed to go into his service. Of course, the League thought we perished on a mission and sent a second group to Porto Bello to finish the job and seek revenge.";
			link.l1 = "Et tu les as tous tués ?";
			link.l1.go = "tonzag_drink_again_3";
		break;
		
		case "tonzag_drink_again_3":
			dialog.text = "D'abord, ils ont tué Gruoh et m'ont défiguré. L'hidalgo ne voulait plus rien avoir à faire avec moi et m'a jeté dehors. C'est alors que Rodenburg m'a trouvé...";
			link.l1 = "Et comment suis-je censé te faire confiance maintenant? Tu as déserté l'armée, déserté la Ligue, et tué tes propres partenaires ! Quand le moment sera venu, me trahiras-tu aussi ?";
			link.l1.go = "tonzag_drink_again_4";
		break;
		
		case "tonzag_drink_again_4":
			dialog.text = "Oui, j'ai déserté, j'ai rompu le contrat, j'ai tué quelques douzaines de membres de la Ligue. Mais j'ai appris la leçon, Capitaine. Et puis, un mort ne peut trahir personne, et je suis mort depuis longtemps, depuis Porto Bello. Et c'est peut-être pour ça qu'il est si difficile de me tuer maintenant.";
			link.l1 = "Cela suffit pour aujourd'hui. J'ai l'impression que tu ne me dis toujours pas tout.";
			link.l1.go = "tonzag_drink_again_5";
		break;
		
		case "tonzag_drink_again_5":
			dialog.text = "Je m'occuperai moi-même du prisonnier, ou souhaitez-vous vous joindre à moi ?";
			link.l1 = "Allons-y. Je l'interrogerai moi-même.";
			link.l1.go = "tonzag_drink_again_hold";
			link.l2 = "Non, ces affaires ne sont pas pour moi. Rendez-vous dans ma cabine dans une demi-heure !";
			link.l2.go = "tonzag_drink_again_cabin";
		break;
		
		case "tonzag_drink_again_hold":
			DialogExit();
			
			NextDiag.CurrentNode = "tonzag_officer";
			AddDialogExitQuestFunction("Tonzag_ReturnToHold");
		break;
		
		case "tonzag_drink_again_cabin":
			DialogExit();
			
			NextDiag.CurrentNode = "tonzag_officer";
			AddDialogExitQuestFunction("Tonzag_ReturnToCabin");
		break;
		
		case "tonzag_hold":
			dialog.text = "Qui commande maintenant ? Arno ?";
			link.l1 = "";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("Tonzag_HoldDialog1");
		break;
		
		case "tonzag_hold_1":
			dialog.text = "Cette racaille est montée au pouvoir ? Il ne t'a pas fallu longtemps pour te dégrader en une simple bande de bandits...";
			link.l1 = "Qui est Austin ?";
			link.l1.go = "tonzag_hold_2";
		break;
		
		case "tonzag_hold_2":
			dialog.text = "La bande d'Austin était célèbre pour attirer les capitaines libres dans la nature, les découper et dépouiller complètement leurs cadavres de tout argent ou babiole. Bon commerce, et il ne manquait pas de chercheurs d'aventure, donc personne ne s'en souciait. Mais ils ont rencontré un os avec un capitaine, et il a donc dû prendre son équipage sous l'aile de la Compagnie. Nous l'avons gardé en laisse et ne l'avons lâché que lorsque nous avions besoin de résoudre des problèmes de manière rapide et simple.";
			link.l1 = "Je doute de pouvoir négocier un accord avec une telle personne.";
			link.l1.go = "tonzag_hold_3";
		break;
		
		case "tonzag_hold_3":
			dialog.text = "C'est sûr. Si lui et ses hommes dirigent les choses maintenant, bientôt la Ligue deviendra juste une autre bande.";
			link.l1 = "";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("Tonzag_HoldDialog3");
		break;
		
		case "tonzag_after_hold":
			dialog.text = "Nous avons eu une conversation intéressante.";
			link.l1 = "J'aimerais savoir combien de cela est vrai... Qu'en est-il du massacre de Porto Bello ? S'il ne mentait pas, cela signifie que la dernière fois que toi et moi avons parlé, tu as de nouveau omis quelques faits importants de ta brillante biographie.";
			link.l1.go = "tonzag_after_hold_1";
		break;
		
		case "tonzag_after_hold_1":
			dialog.text = "Il faisait chaud à Porto Bello, Capitaine. J'ai combattu pour ma vie, pour la vie de mon employeur, pour la vie de ma femme. Je n'avais pas le temps de compter les morts et de pleurer chaque paysan qui se montrait dans la rue au mauvais moment.";
			link.l1 = "Dans cet ordre de priorité ?";
			link.l1.go = "tonzag_after_hold_2";
		break;
		
		case "tonzag_after_hold_2":
			dialog.text = "Non, bien sûr que non. Les siennes d'abord. Toujours.";
			link.l1 = "Qu'en penses-tu ? Devrions-nous aller à Caracas ?";
			link.l1.go = "tonzag_after_hold_3";
		break;
		
		case "tonzag_after_hold_3":
			dialog.text = "Personnellement, je ne le ferais pas, Capitaine. Et je vous déconseille de le faire également. Pour la Ligue, vous n'êtes plus un ennemi, et je ne les intéresse pas, du moins pour l'instant tant que je suis à votre service. De plus, j'ai ce mauvais pressentiment au fond de moi\nÇa ira mal si nous y allons. Très mal. Cette histoire n'a pas de fin heureuse. Mais je serai avec vous jusqu'à la fin, Capitaine.";
			link.l1 = "Je vais y réfléchir.";
			link.l1.go = "exit";
			
			if (CheckCharacterItem(pchar, "MerdokArchive")) {
				link.l1.go = "tonzag_after_hold_4";
			}
			
			AddDialogExitQuestFunction("Tonzag_GoToCaracas");
		break;
		
		case "tonzag_after_hold_4":
			dialog.text = "";
			link.l1 = "Soit dit en passant, tu avais raison - ils n'ont pas réussi à bien nettoyer la mine. Regarde.";
			link.l1.go = "tonzag_after_hold_5";
		break;
		
		case "tonzag_after_hold_5":
			dialog.text = "Le journal d'un officier... crypté, mais c'est une vieille méthode, je la connais\nRien d'intéressant, semble-t-il. C'était le journal de notre prisonnier. C'est maintenant clair pourquoi il était si disposé à parler. Regardez ici - des indications d'un trésor caché ! Le gredin avait clairement prévu de prendre sa retraite et était prêt à s'éclipser à tout moment!";
			link.l1 = "Où se trouve cet endroit caché?";
			link.l1.go = "tonzag_after_hold_6";
		break;
		
		case "tonzag_after_hold_6":
			dialog.text = "Vous connaissez cette île, Capitaine. Dans ses eaux, vous avez mis fin à Van Berd.";
			link.l1 = "D'accord, ce n'est pas très loin, alors allons voir. Quant à Caracas, je n'ai pas encore décidé, mais je pense que nous avons un mois.";
			link.l1.go = "tonzag_after_hold_7";
		break;
		
		case "tonzag_after_hold_7":
			dialog.text = "Comme vous le souhaitez, Capitaine. Je suis avec vous jusqu'à la fin.";
			link.l1 = "";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("Tonzag_CreateLoot");
		break;
		
		case "tonzag_after_drink":
			dialog.text = "It's done, Captain. Austin is currently in Caracas; I think we have a month.";
			link.l1 = "Premièrement, que disait le prisonnier? Qui est cet Austin? Et pourquoi devrions-nous nous rendre à Caracas?";
			link.l1.go = "tonzag_after_drink_1";
		break;
		
		case "tonzag_after_drink_1":
			dialog.text = "La bande d'Austin était célèbre pour attirer les capitaines libres dans la nature, les découper et dépouiller complètement leurs cadavres de tout argent ou babiole. Bon commerce, et il n'y a pas de pénurie de chercheurs d'aventure, donc personne ne s'en souciait. Mais ils ont rencontré un pépin avec un capitaine, alors il a dû prendre son équipage sous l'aile de la Compagnie. Nous l'avons gardé en laisse et ne le laissions libre que lorsque nous avions besoin de résoudre des problèmes de manière rapide et simple.";
			link.l1 = "Je doute de pouvoir négocier un accord avec une telle personne.";
			link.l1.go = "tonzag_after_drink_2";
		break;
		
		case "tonzag_after_drink_2":
			dialog.text = "C'est certain. Si lui et ses hommes sont aux commandes maintenant, bientôt la Ligue ne sera plus qu'une autre bande de vauriens. Mais je n'irais pas à Caracas, Capitaine.";
			link.l1 = "Sérieusement ? As-tu peur ?";
			link.l1.go = "tonzag_after_drink_3";
		break;
		
		case "tonzag_after_drink_3":
			dialog.text = "Ce n'est pas comme ça, Capitaine. Avant de mourir de ses blessures, le prisonnier a révélé que vous n'êtes plus un ennemi de la Ligue, et je ne les intéresse pas, du moins pour l'instant tant que je suis à votre service. La Ligue semble avoir un nouveau mécène influent qui a ordonné de nous laisser tranquilles\nEt Caracas... J'ai ce mauvais pressentiment au fond de moi... Ce sera mauvais si nous y allons. Très mauvais. Cette histoire n'a pas de fin heureuse. Mais je serai avec vous jusqu'à la fin, Capitaine.";
			link.l1 = "Je vais y réfléchir. Bien sûr, j'aimerais régler cette histoire une fois pour toutes, mais peut-être as-tu raison. Je doute qu'après les événements de la semaine dernière, ils osent nous approcher à nouveau.";
			link.l1.go = "exit";
			
			if (CheckCharacterItem(pchar, "MerdokArchive")) {
				link.l1.go = "tonzag_after_drink_4";
			}
			
			AddDialogExitQuestFunction("Tonzag_GoToCaracas");
		break;
		
		case "tonzag_after_drink_4":
			dialog.text = "";
			link.l1 = "Soit dit en passant, tu avais raison - ils n'ont pas réussi à bien nettoyer la mine. Regarde.";
			link.l1.go = "tonzag_after_drink_5";
		break;
		
		case "tonzag_after_drink_5":
			dialog.text = "Le journal d'un officier... chiffré, mais c'est un vieux code, je le connais\nRien d'intéressant, il semble. C'était le journal de notre prisonnier. Regardez ici - des indications d'un trésor caché ! Le gredin avait clairement prévu de prendre sa retraite et était prêt à s'éclipser à tout moment !";
			link.l1 = "Où se trouve cet endroit caché ?";
			link.l1.go = "tonzag_after_drink_6";
		break;
		
		case "tonzag_after_drink_6":
			dialog.text = "Vous connaissez cette île, Capitaine. Dans ses eaux, vous avez mis fin à Van Berd.";
			link.l1 = "D'accord, ce n'est pas très loin, alors allons voir. Quant à Caracas, je n'ai pas encore décidé, mais je pense que nous avons un mois.";
			link.l1.go = "tonzag_after_drink_7";
		break;
		
		case "tonzag_after_drink_7":
			dialog.text = "Comme vous le souhaitez, Capitaine.";
			link.l1 = "";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("Tonzag_CreateLoot");
		break;
		
		case "tonzag_church":
			dialog.text = "Attends, Capitaine. J'y vais seul.";
			link.l1 = "And why is that? Feeling heroic now? It's too late; you've made this mess, but we have to clean it together.";
			link.l1.go = "tonzag_church_1";
		break;
		
		case "tonzag_church_1":
			dialog.text = "Inutile de payer pour mes erreurs, Capitaine. Vous aviez raison - où que j'aille, les gens meurent et le sang innocent coule. Si nous entrons ensemble dans cette église, ce sera un autre Porto Bello, et je ne veux pas cela.";
			link.l1 = "Que s'est-il vraiment passé là-bas ?";
			link.l1.go = "tonzag_church_2";
		break;
		
		case "tonzag_church_2":
			dialog.text = "Un massacre. Je voulais prendre ma retraite, Capitaine. Je voulais prendre l'or, ma femme, et rentrer chez moi à Carcassonne. Je savais que la Ligue enverrait plus de monde pour finir mon travail et j'ai pris un généreux acompte de mon nouveau patron. Ensuite, tout ce qu'il restait à faire était de monter la garde de la ville contre mes anciens complices et le nouvel employeur. Dans tout ce tumulte, je devais disparaître avec l'argent, et peut-être, si le temps le permettait, dépouiller quelques gros bonnets de Porto Bello.";
			link.l1 = "Bon plan, bien que je l'aurais fait autrement. Trop de choses pourraient mal tourner.";
			link.l1.go = "tonzag_church_2a";
			link.l2 = "Je ne suis pas un ange moi-même, mais ton approche me fait frémir. Je suis surpris que tu ne m'aies pas encore trahi, comme tu l'as fait avec la Ligue, l'Hidalgo, et même ta propre femme.";
			link.l2.go = "tonzag_church_2a";
		break;
		
		case "tonzag_church_2a":
			dialog.text = "Everything that could go wrong, did go wrong. Shooting a three-pounder towards the governor's palace was a mistake. It barely scratched the governor himself, but his beautiful daughter, as I hear, had to have both her legs amputated below the knees to save her life. The response was horrific - a blood bath; great many people perished, Captain. Now you're looking at the last living witness to those events, and not long ago, you cut down another one yourself.";
			link.l1 = "Explique.";
			link.l1.go = "tonzag_church_3";
		break;
		
		case "tonzag_church_2b":
			dialog.text = "Si Madame Tonzag était encore en vie, je t'aurais trahi sans hésiter, Capitaine. Je suis un mort-vivant, te suivant parce que je n'ai pas d'autre place en ce monde. Maintenant, tu regardes le dernier témoin vivant de ces événements, et il n'y a pas longtemps, tu en as abattu un autre toi-même.";
			link.l1 = "Explique.";
			link.l1.go = "tonzag_church_3";
		break;
		
		case "tonzag_church_3":
			dialog.text = "Excusez-moi, Capitaine, de ne pas vous avoir tout dit en chemin. Quand nous nous sommes rencontrés, je vous ai pris pour un autre salaud comme moi. Et vous savez ce que j'ai fait en premier ? Je vous ai envoyé nettoyer derrière moi - pour tuer ce Don espagnol que je ne voulais pas tuer au départ et que j'ai ensuite décidé de trahir. Ce Hidalgo, Rodriguez...";
			link.l1 = "Et pourquoi avais-tu besoin de son doigt ?";
			link.l1.go = "tonzag_church_4";
		break;
		
		case "tonzag_church_4":
			dialog.text = "Aucun subterfuge ici. Juste un test, Capitaine. Nous recrutons des dizaines de jeunes gredins comme vous chaque année. Seuls quelques-uns passent le test d'honnêteté de base, et même eux meurent lors des premières opérations. Vous n'étiez pas censé survivre à l'opération avec le journal de bord de Fleetwood. Je prévoyais simplement d'entrer dans la maison, de finir les survivants et de prendre le journal.";
			link.l1 = "Si ma mémoire est bonne, l'histoire a pris un tournant légèrement différent.";
			link.l1.go = "tonzag_church_5";
		break;
		
		case "tonzag_church_5":
			dialog.text = "D'accord, capitaine. Je ne sais pas ce qui m'a poussé à vous aider, mais vous avez combattu les Renards avec une telle joie de vivre que vous m'avez même contaminé, ne serait-ce que brièvement. En fin de compte, sans le savoir, vous m'avez sauvé. Vous ne me devez rien, capitaine. Et je ne vous laisserai pas entrer là. C'est mon affaire, ma rédemption.";
			link.l1 = "Comme tu veux, Hercule. Cela fait mal de perdre un tel combattant, mais tu t'es perdu il y a longtemps, et tu ne vaux pas plus de sang versé. Tu ne me dois rien non plus, et j'espère que tu trouveras la rédemption dans cette petite église.";
			link.l1.go = "tonzag_church_bad";
			link.l2 = "Beau discours, Hercule. Va au diable ! Si tu n'as pas remarqué, tes problèmes sont devenus les miens dernièrement. Tu es mon officier, et moi seul déciderai si tu mérites le pardon ou non. Donc tu devras rester avec nous un peu plus longtemps et gagner ta rédemption avec vaillance en tant que membre de mon équipage !";
			link.l2.go = "tonzag_church_good";
		break;
		
		case "tonzag_church_bad":
			dialog.text = "Merci pour tout, Capitaine. Adieu !";
			link.l1 = "";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("Tonzag_ChurchBad");
		break;
		
		case "tonzag_church_good":
			dialog.text = "Oui, capitaine!";
			link.l1 = "";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("Tonzag_ChurchGood");
		break;
		
		case "tonzag_afterchurchfight":
			dialog.text = "J'ai vu bien des vauriens en mon temps, Capitaine, mais pour la première fois, j'ai ressenti un frisson d'horreur en moi. Que penses-tu : si un monstre plus petit tue un monstre plus grand, cela compte-t-il pour une rédemption ?";
			link.l1 = "Est-ce qu'ils diluent le rhum avec de l'eau ? Dis-moi quand tu auras compris. Allons-y, nous avons fini ici.";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("Tonzag_ResetTonzag");
		break;

	}
}