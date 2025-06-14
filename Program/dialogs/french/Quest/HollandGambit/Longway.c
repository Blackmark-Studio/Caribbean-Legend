// китаец Лонгвэй, подручный Роденбурга
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
	if (findsubstr(sAttr, "SetMusketBullets1_" , 0) != -1)
 	{
        i = findsubstr(sAttr, "_" , 0);
	 	NPChar.SetMusketBullets = strcut(sAttr, i + 1, strlen(sAttr) - 1); // индекс в конце
 	    Dialog.CurrentNode = "SetMusketBullets2";
 	}
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			dialog.text = "Chuanzhang. Mon nom est Longway. Longway met son navire sous votre commandement. Longway aussi sous votre commandement. Ordre de mynheer Rodenburg.";
			link.l1 = "Salutations, Longway. Charles de Maure, à votre service. Avez-vous des pistes sur l'opération pour éliminer Jacob van Berg ?";
			link.l1.go = "Longway_friend";
			link.l2 = "Ravi de te voir, Longway. Je m'appelle Charles de Maure. Pas de temps à perdre - mynheer Rodenburg apprécie le travail rapide et de haute qualité. Où se cache Jacob van Berg maintenant ?";
			link.l2.go = "Longway_neutral";
			link.l3 = "Eh bien, et le mien est Charles de Maure ! Espérons que les nôtres travailleront bien ensemble ! Alors, mon cher Longway, dites-moi, je vous prie, où devrions-nous chercher Jacob van Berg ?";
			link.l3.go = "Longway_enemy";
			NextDiag.TempNode = "First time";
			pchar.questTemp.HWIC.Holl.JacobCity = SelectJacobCity();
		break;
		
//-----------------------------------------------за Голландию-----------------------------------------------
		case "Longway_neutral":
			dialog.text = "Longway sûr que nous travaillerons bien ensemble, chuanzhang. Jacob van Berg actuellement à "+XI_ConvertString("Colony"+pchar.questTemp.HWIC.Holl.JacobCity+"Gen")+"J'ai organisé une rencontre avec lui dans la taverne locale. Il y sera.";
			link.l1 = "Levons l'ancre !";
			link.l1.go = "Longway_JacobGo";	
			pchar.questTemp.HWIC.Holl.LongwayNeutral = "true";//признак враждебности китайца
		break;
		
		case "Longway_enemy":
			dialog.text = "L'ordre du seigneur Rodenburg pour Longway... Jacob van Berg actuellement à "+XI_ConvertString("Colonie"+pchar.questTemp.HWIC.Holl.JacobCity+"Gén")+"J'ai organisé une rencontre avec lui dans la taverne locale. Il y sera.";
			link.l1 = "Mettons les voiles !";
			link.l1.go = "Longway_JacobGo";	
			pchar.questTemp.HWIC.Holl.LongwayEnemy = "true";//признак враждебности китайца
			notification("Longway disapproves", "Longway");
		break;
		
		case "Longway_friend":
			dialog.text = "Longway fera tout son possible, chuanzhang. Et Jacob van Berg est actuellement à "+XI_ConvertString("Colony"+pchar.questTemp.HWIC.Holl.JacobCity+"Dat")+". J'ai arrangé une rencontre avec lui dans la taverne locale. Il y sera.";
			link.l1 = "Mettons les voiles !";
			link.l1.go = "Longway_JacobGo";	
			pchar.questTemp.HWIC.Holl.LongwayFriend = "true";//признак враждебности китайца
			notification("Longway approves", "Longway");
		break;
		
		case "Longway_JacobGo":
			//Лонгвэя - в офицеры
			npchar.quest.OfficerPrice = sti(pchar.rank)*500;
			Pchar.questTemp.HiringOfficerIDX = GetCharacterIndex(npchar.id);
			npchar.OfficerWantToGo.DontGo = true; //не пытаться уйти
			npchar.HalfImmortal = true;//полубессмертен
			npchar.loyality = 18;
			AddDialogExitQuestFunction("LandEnc_OfficerHired");
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload2_back", "none", "", "", "", -1);
			AddQuestRecord("Holl_Gambit", "1-8");
			AddQuestUserData("Holl_Gambit", "sCity", XI_ConvertString("Colony"+pchar.questTemp.HWIC.Holl.JacobCity+"Dat"));
			AddMapQuestMarkCity(pchar.questTemp.HWIC.Holl.JacobCity, true);
			AddLandQuestMark(characterFromId(""+pchar.questTemp.HWIC.Holl.JacobCity+"_tavernkeeper"), "questmarkmain");
			pchar.questTemp.HWIC.Holl = "JacobOnMain";
			if(bImCasual)
			{
				NewGameTip("Exploration mode: quest duration doubled");
				SetFunctionTimerCondition("JacobOnMainOver", 0, 0, 30, false);
			}
			else SetFunctionTimerCondition("JacobOnMainOver", 0, 0, 15, false);
		break;
		
		case "hired":
			dialog.text = "Que peut faire Longway, chuanzhang ?";
			link.l1 = "Rien pour l'instant.";
			link.l1.go = "exit";
			NextDiag.TempNode = "hired";
		break;
		
		case "MC_GoAway":
			PlaySound("Voice\English\hambit\Longway-02.wav");
			if (pchar.questTemp.HWIC.Holl == "MirageFail")
			{
				dialog.text = "Imbécile de Mongol, chuanzhang ! Nous avions une tâche facile - capturer 'Mirage' sans perdre 'Meifeng'. Elle était une cible facile sans son chuanzhang, et pourtant tu as échoué à faire le travail\nLongway ne te servira plus et ne te verra plus. Longway est sûr que M. Rodenburg approuvera sa décision.";
				link.l1 = "Au diable avec toi et ton maître !";
				link.l1.go = "exit";
				AddQuestRecord("Holl_Gambit", "1-10");
			}
			if (pchar.questTemp.HWIC.Holl == "JacobOnMain" || pchar.questTemp.HWIC.Holl == "JacobInRoom")
			{
				dialog.text = "Espèce d'idiot de Mongol, chuanzhang ! Nous avons perdu trop de temps à résoudre tes propres affaires au lieu de rencontrer Jacob van Berg. Il est déjà parti de "+XI_ConvertString("Colony"+pchar.questTemp.HWIC.Holl.JacobCity+"Caillou")+"\nVous avez échoué à accomplir la tâche. Longway ne souhaite ni vous servir, ni vous voir à nouveau. Longway est certain que Monsieur Rodenburg approuvera sa décision.";
				link.l1 = "Au diable toi et ton maître !";
				link.l1.go = "exit";
				AddQuestRecord("Holl_Gambit", "1-9");
			}
			if (pchar.questTemp.HWIC.Holl == "lateVillemstad")
			{
				dialog.text = "Chuanzhang, tu as gaspillé trop de temps sans résultat. Ce n'est pas ton navire et Longway n'est pas ton coolie. Longway retourne à Willemstad\nLongway ne te servira plus, ni ne te verra plus. Longway est sûr que Monsieur Rodenburg approuvera sa décision.";
				link.l1 = "Au diable toi et ton maître !";
				link.l1.go = "exit";
			}
			PChar.quest.Munity = "Deads";
			LAi_LocationFightDisable(&Locations[FindLocation("Ship_deck")], false);
			if(sti(RealShips[sti(pchar.ship.type)].basetype) == SHIP_MAYFANG)//если сам на Мейфенг
			{
			pchar.Ship.Type = GenerateShipExt(SHIP_TARTANE, true, pchar);
			pchar.Ship.name = "Boat";
			SetBaseShipData(pchar);
			SetCrewQuantityOverMax(PChar, 0);
			}
			else
			{
				for(i=1; i < COMPANION_MAX; i++)
				{
					int iTemp = GetCompanionIndex(PChar, i);
					if(iTemp > 0)
					{
						sld = GetCharacter(iTemp);
						if(sti(RealShips[sti(sld.ship.type)].basetype) == SHIP_MAYFANG)
						{
							pchar.questTemp.HWIC.Holl.CompanionIndex = sld.Index;
							sld = GetCharacter(sti(pchar.questTemp.HWIC.Holl.CompanionIndex));
							RemoveCharacterCompanion(PChar, sld);
							AddPassenger(PChar, sld, false);
						}
					}
				}
			}
			LAi_CharacterDisableDialog(npchar);
			LAi_SetImmortal(npchar, true);
			npchar.lifeday = 0;
			DeleteAttribute(pchar, "questTemp.HWIC.TakeQuestShip");//ПУ откроем
			DeleteAttribute(pchar, "questTemp.HWIC.HollEquip");
			pchar.questTemp.HWIC.Holl = "end";
			CloseQuestHeader("Holl_Gambit");
			pchar.questTemp.HWIC.Detector = "holl_fail";
		break;
		
		case "Longway_hire":
			PlaySound("Voice\English\hambit\Longway-03.wav");
			dialog.text = "Chuanzhang, Longway a quitté Mynheer Rodenburg. Longway ne retournera jamais vers lui. Vous avez été bon envers Longway et vous êtes un brave chuanzhang. Longway veut rejoindre votre équipage en tant que serviteur, Seigneur Capitaine.";
			link.l1 = "Pas comme un serviteur, mais comme un officier ! Bienvenue à bord, ami !";
			link.l1.go = "Longway_hire_1";	
			link.l2 = "Non merci, Longway. Tu es un homme libre. Je n'ai pas besoin de tes services.";
			link.l2.go = "Longway_exit";	
		break;
		
		case "Longway_exit":
			DialogExit();
			npchar.lifeday = 0;
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload2", "none", "", "", "", 30.0);
			AddQuestRecord("Holl_Gambit", "1-37");
		break;
		
		case "Longway_hire_1"://нанимаем китайца
			DialogExit();
			DeleteAttribute(npchar, "LifeDay");
			DeleteAttribute(npchar, "HalfImmortal");
			npchar.quest.OfficerPrice = sti(pchar.rank)*500;
			npchar.OfficerWantToGo.DontGo = true;
			npchar.loyality = MAX_LOYALITY;
			AddPassenger(pchar, npchar, false);
			SetCharacterRemovable(npchar, true);
			npchar.OfficerImmortal = true;
			npchar.Health.HP       = 60.0; 
			npchar.Health.maxHP    = 60.0;
			SetCharacterPerk(npchar, "ShipEscape");
			npchar.CanTakeMushket = true;
			npchar.Payment = true;
			LAi_SetOfficerType(npchar);
			NextDiag.CurrentNode = "Longway_officer";
			npchar.quest.meeting = true;
			npchar.HoldEquip = true;
			LAi_SetImmortal(npchar, false);
			LAi_SetHP(npchar, 200, 200);
			LAi_group_MoveCharacter(npchar, LAI_GROUP_PLAYER);
			SaveCurrentNpcQuestDateParam(npchar, "HiredDate");
			AddQuestRecord("Holl_Gambit", "1-38");
			
			//Sinistra - квест Лонгвэя "Путеводная звезда"
			PChar.quest.PZ_Start.win_condition.l1 = "location";
			PChar.quest.PZ_Start.win_condition.l1.location = "Curacao";
			PChar.quest.PZ_Start.win_condition = "PZ_Start";
		break;
		
//---------------------------------------------против всех-------------------------------------------------
		case "Longway_abordage":
			PlaySound("Voice\English\hambit\Longway-02.wav");
			dialog.text = "Pourquoi tu t'arrêtes ? Tue. Longway fatigué, Longway veut la mort. Xing... pardonne-moi.";
			link.l1 = "Pas si vite, Chinetoque. Je te tuerai si je le veux, mais je dois d'abord te parler. Ton destin dépend de tes actions futures. Pour l'instant, bienvenue dans ma cale !";
			link.l1.go = "Longway_abordage_1";			
		break;
		
		case "Longway_abordage_1":
			AddQuestRecord("Holl_Gambit", "3-45");
		    DoQuestCheckDelay("LAi_ReloadBoarding", 1.0);
            DialogExit();
			LAi_SetPlayerType(pchar);
			pchar.questTemp.HWIC.Self = "LongwayPrisoner";
			npchar.lifeday = 0;
			SetFunctionTimerCondition("RemoveLongwayOver", 0, 0, 1, false);//таймер до конца суток, ибо нефиг
		break;
		
		case "Longway_prisoner":
			DelLandQuestMark(npchar);
			dialog.text = "";
			link.l1 = "Maintenant, nous pouvons parler sans que le fracas de l'acier ne me vrille les oreilles. Écoute Longway, j'ai besoin d'informations et je ne doute pas que tu sais ce que je dois savoir. La question est : vas-tu me le dire de la manière facile ou difficile ?";
			link.l1.go = "Longway_prisoner_1";			
		break;
		
		case "Longway_prisoner_1":
			dialog.text = "Bonjour, mon ami.";
			link.l1 = "Tu restes silencieux ? Très bien. Je te propose un marché. Je t'épargne la vie et te débarque sur la prochaine côte. En échange, tu me diras où et pourquoi Lucas Rodenburg t'a envoyé. Marché conclu ?";
			link.l1.go = "Longway_prisoner_2";			
		break;
		
		case "Longway_prisoner_2":
			dialog.text = "";
			link.l1 = "Je sais que tu comprends l'anglais, le néerlandais et le français. Tu es aussi un bon auditeur. Maintenant, il est temps de commencer à parler. Tu finiras par me dire tout ce que tu sais. Je sais que vous, Chinois, êtes fiers de votre art de la torture, mais nous, les hommes de l'Occident, avons fait nos propres avancées dans cette science ancienne. Alonso ici est un maître pour délier les langues des gens. Il était interrogateur pour la Sainte Inquisition à Santiago avant d'être engagé sur mon navire. Il connaît toutes sortes de tours qu'il a appris des saints pères qui ont perfectionné l'art de faire avouer les gens... tu n'as même pas besoin d'être protestant !";
			link.l1.go = "Longway_prisoner_3";			
		break;
		
		case "Longway_prisoner_3":
			dialog.text = "";
			link.l1 = "Mon esprit est perdu pour toi. Tu me diras tout, mon ami aux yeux bridés... Tout... Mais tu ne vivras pas longtemps après cela, non, tu ne vivras pas. Ton corps souffrira beaucoup après la rencontre avec Alonso/. Donc, le choix t'appartient. Soit tu me dis toute la vérité et tu vis, soit tu me dis toute la vérité et tu meurs dans l'agonie sur le chevalet. Tourmenté par la douleur sur le chevalet. Compris ? Ne t'inquiète pas, je m'assurerai qu'un prêtre soit présent pour te baptiser chrétien afin d'épargner à ton âme païenne les feux éternels de l'enfer.";
			link.l1.go = "Longway_prisoner_4";
		break;
		
		case "Longway_prisoner_4":
			dialog.text = "";
			link.l1 = "Je vois le doute grandir dans tes yeux noirs. Pourquoi mourir pour les péchés de ton maître ? En vaut-il la peine ? Rodenburg vaut-il vraiment que ton âme soit arrachée de ton corps souffrant ?";
			link.l1.go = "Longway_prisoner_5";			
		break;
		
		case "Longway_prisoner_5":
			dialog.text = "Longway parle. Mais d'abord, Longway veut s'assurer que tu tiens parole, chuanzhang.";
			link.l1 = "Ha ! Des paroles sages ! Je te donne ma parole, garçon.";
			link.l1.go = "Longway_prisoner_6";			
		break;
		
		case "Longway_prisoner_6":
			dialog.text = "Désolé chuanzhang, votre parole ne suffit pas. Vous obtenez des informations et tuez Longway après ! Longway veut des garanties.";
			link.l1 = "Tu marchandises comme un Juif. Quelles garanties veux-tu ?";
			link.l1.go = "Longway_prisoner_7";			
		break;
		
		case "Longway_prisoner_7":
			dialog.text = "Il y a une petite île au sud de la Guadeloupe. Cap Inaccessible. Débarque Longway là-bas et donne-lui une arme. Ce n'est qu'alors que Longway te dira tout ce qu'il sait sur Lucas Rodenburg.";
			link.l1 = "Tu n'es pas en position de marchander avec moi, Chinois.";
			link.l1.go = "Longway_prisoner_8";			
		break;
		
		case "Longway_prisoner_8":
			dialog.text = "Tu ferais pareil si tu étais Longway, chuanzhang. Pas facile pour ton homme d'obtenir des mots de moi, même avec des tortures. Longway n'est pas un faible homme blanc.";
			link.l1 = "D'accord. Marché conclu. Mais je te préviens - ne tente pas de me duper ou je te découperai personnellement en morceaux. Mille morceaux, et lentement... tout comme vos empereurs le font. Alonso !";
			link.l1.go = "Longway_prisoner_9";
			// belamour legendary edition -->
			link.l2 = "Tu dis vrai. Mais garde à l'esprit - je suis allé trop loin pour que tu gâches tout. Si tu essaies de m'arrêter, je mettrai fin à ta vie comme on écrase un insecte.";
			link.l2.go = "Longway_prisoner_9a";
		break;
		
		case "Longway_prisoner_9a":
			ChangeCharacterComplexReputation(pchar, "nobility", 1);
			AddCharacterExpToSkill(pchar, "Leadership", 120);
			DialogExit();
			NextDiag.Currentnode = "Longway_prisoner_0";
			npchar.greeting = "longway";
			sld = characterFromId("Sailor_3");
			sld.dialog.currentnode = "Sailor_deck_7";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);	
			pchar.quest.RemoveLongwayOver.over = "yes";//снять таймер
			pchar.quest.RemoveLongwayTimer.win_condition.l1 = "Timer";
			pchar.quest.RemoveLongwayTimer.win_condition.l1.date.hour  = sti(GetTime());
			pchar.quest.RemoveLongwayTimer.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 10);
			pchar.quest.RemoveLongwayTimer.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 10);
			pchar.quest.RemoveLongwayTimer.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 10);
			pchar.quest.RemoveLongwayTimer.function = "RemoveLongwayOver";
			pchar.questTemp.HWIC.Self = "GotoGuadeloupe";
		break;
		
		case "Longway_prisoner_9":
			ChangeCharacterComplexReputation(pchar, "nobility",-5);
			AddCharacterExpToSkill(pchar, "FencingL", 30);
			AddCharacterExpToSkill(pchar, "FencingS", 30);
			AddCharacterExpToSkill(pchar, "FencingH", 30);
			AddCharacterExpToSkill(pchar, "Pistol", 30);
			// <-- legendary edition
			DialogExit();
			NextDiag.Currentnode = "Longway_prisoner_0";
			npchar.greeting = "longway";
			sld = characterFromId("Sailor_3");
			sld.dialog.currentnode = "Sailor_deck_7";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);	
			pchar.quest.RemoveLongwayOver.over = "yes";//снять таймер
			pchar.quest.RemoveLongwayTimer.win_condition.l1 = "Timer";
			pchar.quest.RemoveLongwayTimer.win_condition.l1.date.hour  = sti(GetTime());
			pchar.quest.RemoveLongwayTimer.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 10);
			pchar.quest.RemoveLongwayTimer.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 10);
			pchar.quest.RemoveLongwayTimer.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 10);
			pchar.quest.RemoveLongwayTimer.function = "RemoveLongwayOver";
			pchar.questTemp.HWIC.Self = "GotoGuadeloupe";
		break;
		
		case "Longway_prisoner_0":
			dialog.text = "Sommes-nous arrivés à la Guadeloupe, chuanzhang ?";
			link.l1 = "Calme-toi, nous y serons bientôt.";
			link.l1.go = "exit";
			NextDiag.Tempnode = "Longway_prisoner_0";
		break;
		
		case "Longway_prisoner_10":
			dialog.text = "Vous avez tenu parole, chuanzhang. Longway aussi. Vouliez-vous en savoir plus sur la mission de Longway?";
			link.l1 = "Oui. Mais permettez-moi de vous rappeler votre propre promesse envers moi : vous me direz *tout* ce que vous savez.";
			link.l1.go = "Longway_prisoner_11";			
		break;
		
		case "Longway_prisoner_11":
			dialog.text = "Longway se souvient. Il répondra à tout ce que tu demandes sur Rodenburg, chuanzhang.";
			link.l1 = "Commence à parler.";
			link.l1.go = "Longway_prisoner_12";			
		break;
		
		case "Longway_prisoner_12":
			dialog.text = "'Meifeng' naviguait du port de Willemstad vers le nord, vers les côtes de Saint-Christophe. Dans cinq jours, il y aurait un galion sous le commandement de Peter Stuyvesant. L'ordre de Longway était de couler ce navire avec son capitaine à bord.";
			link.l1 = "Dieu du ciel ! Rodenburg vous a ordonné de tuer Stuyvesant ? C'est de la folie !";
			link.l1.go = "Longway_prisoner_13";			
		break;
		
		case "Longway_prisoner_13":
			dialog.text = "Longway dit la vérité, capitaine. C'était l'ordre de Monsieur Rodenburg. Longway n'a pas aimé ça mais Longway ne remet pas en question les ordres.";
			link.l1 = "Comme c'est typiquement chinois. Quel jeu joue votre maître ?";
			link.l1.go = "Longway_prisoner_14";			
		break;
		
		case "Longway_prisoner_14":
			dialog.text = "Pas mon maître plus, chuanzhang. Longway ne retournera pas auprès de Mynheer Rodenburg. Rodenburg a pris le pouvoir à Curaçao. Mathias Beck était une proie facile, l'autorité de Rodenburg et ses connexions avec le commandant suffisent pour mettre le gouverneur en prison\nLe seul obstacle restant est le directeur de la Compagnie des Indes occidentales, Mynheer Stuyvesant. Une fois Stuyvesant éliminé, Rodenburg détiendra tous les postes de pouvoir dans les colonies néerlandaises.";
			link.l1 = "Dis-moi, Longway, qu'est-ce qui a poussé un homme respecté et puissant comme Rodenburg à commettre des actions si radicales contre sa compagnie et sa république ? Et ne me dis pas que c'est à cause d'un coup de soleil ou d'une poussée de folie.";
			link.l1.go = "Longway_prisoner_15";			
		break;
		
		case "Longway_prisoner_15":
			dialog.text = "Longway voulait savoir lui-même de toi, chuanzhang. C'est toi qui as capturé le navire de la Compagnie et pris la lettre pour Rodenburg, n'est-ce pas? La raison est dans cette lettre.";
			link.l1 = "Je vois maintenant... Il semble qu'il y ait beaucoup de choses merveilleuses dans les archives de John Murdock pour effrayer Rodenburg au point de lancer une rébellion contre son propre pays.";
			link.l1.go = "Longway_prisoner_16";			
		break;
		
		case "Longway_prisoner_16":
			dialog.text = "Veux-tu savoir autre chose, chuanzhang ?";
			link.l1 = "Oui. Qu'a fait d'autre Rodenburg ?";
			link.l1.go = "Longway_prisoner_17";			
		break;
		
		case "Longway_prisoner_17":
			dialog.text = "Monsieur Rodenburg a ordonné de vous tuer. Longway était à Caracas avant de traquer Stuyvesant et a eu une rencontre avec Chuanzhang Jacob et lui a donné des ordres.";
			link.l1 = "Capitaine Jacob van Berg ?";
			link.l1.go = "Longway_prisoner_18";			
		break;
		
		case "Longway_prisoner_18":
			dialog.text = "Vous êtes bien informé. Oui. Chuanzhang Jacob van Berg vous traque, capitaine. Il finira par vous trouver. Personne ne peut se cacher de van Berg longtemps.";
			link.l1 = "S'il saigne, je peux le tuer. Je m'occuperai de van Berg et de son fameux navire fantôme.";
			link.l1.go = "Longway_prisoner_19";			
		break;
		
		case "Longway_prisoner_19":
			dialog.text = "Vous en savez beaucoup, chuanzhang. Longway n'a rien à ajouter. Demandez si vous avez encore quelque chose à demander.";
			link.l1 = "Stuyvesant sera-t-il près des côtes de Saint-Christophe ?";
			link.l1.go = "Longway_prisoner_20";			
		break;
		
		case "Longway_prisoner_20":
			dialog.text = "Oui, chuanzhang. Vous pourrez trouver son galion près des côtes de cette île dans environ une semaine.";
			link.l1 = "Chouette ! Attrapons ce renard dans son propre piège... Je n'ai plus de questions. Je sais tout ce que je voulais savoir.";
			link.l1.go = "Longway_prisoner_21";			
		break;
		
		case "Longway_prisoner_21":
			dialog.text = "Un dernier conseil, chuanzhang. Tu dois prendre 'Meifeng' si tu veux t'approcher du galion sans être attaqué.";
			link.l1 = "Compris. Merci pour vos informations.";
			link.l1.go = "Longway_prisoner_22";			
		break;
		
		case "Longway_prisoner_22":
			dialog.text = "Longway s'en va maintenant. Adieu, chuanzhang.";
			link.l1 = "Bon vent, mon camarade oriental.";
			link.l1.go = "Longway_prisoner_23";			
		break;
		
		case "Longway_prisoner_23":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1_back", "none", "", "", "ReturnShoreToNormal", -1);
			npchar.lifeday = 0;
			AddQuestRecord("Holl_Gambit", "3-49");
			pchar.questTemp.HWIC.Self = "MeetingStivesant";
			pchar.quest.Seek_Piter.win_condition.l1 = "location";
			pchar.quest.Seek_Piter.win_condition.l1.location = "Nevis";
			pchar.quest.Seek_Piter.function = "CreatePiterHalleon";
			pchar.quest.RemoveLongwayTimer.over = "yes";//снять прерывание
			SetFunctionTimerCondition("QuestShipsTerms_Over", 0, 0, 8, false); // таймер
			AddMapQuestMarkIsland("Nevis", true);
		break;
		
		//--> ----------------------------------- офицерский блок ------------------------------------------
		case "Longway_officer":
			dialog.text = "Longway à l'écoute, chuanzhang.";
			if (CheckAttribute(pchar, "questTemp.Dolly_Tieyasal") && !CheckAttribute(npchar, "quest.Tieyasal"))
			{
				Link.l4 = "Longway, je vais dans une ancienne cité indienne, Tayasal. Je serai clair, ce sera un voyage vraiment dangereux et aussi mystique - nous y arriverons par l'idole de téléportation. Voudrais-tu... te joindre à moi ?";
				Link.l4.go = "tieyasal";
			}
			
			////////////////////////казначей///////////////////////////////////////////////////////////
           	// boal отчёт о корабле
			if(CheckAttribute(NPChar, "treasurer") && NPChar.treasurer == 1)
			{
			    Link.l11 = "Longway, donne-moi un rapport complet du navire.";
			    Link.l11.go = "QMASTER_1";
				
			    // Warship. Автозакупка товара
				Link.l12 = "Je veux que tu achètes certains biens chaque fois que nous sommes à quai.";
				Link.l12.go = "QMASTER_2";
			}

			if (CheckAttribute(NPChar, "IsCompanionClone"))//////////////////компаньон//////////////////////////////////////////////
			{
				//dialog.text = "Je suis arrivé selon vos ordres, capitaine.";
				Link.l2 = "Je dois te donner plusieurs ordres.";
				Link.l2.go = "Companion_Tasks";
				NextDiag.TempNode = "Longway_officer";// не забыть менять в зависисомости от оффа
				break;
			}
			Link.l1 = "Ecoutez mon ordre !";
            Link.l1.go = "stay_follow";
			link.l2 = "Rien. Rompez !";
			link.l2.go = "exit";
			NextDiag.TempNode = "Longway_officer";
		break;
		
		/////////////////////////// ответы для казначея ///////////////////////////////////
		case "QMASTER_1":
			dialog.Text = "Longway n'a jamais été commissaire, chuanzhang. Longway peut te dire comment naviguer de Trinidad à La Havane et combien de temps cela prendra. Mais Longway ne compte jamais la cargaison, les ventes et le commerce.";
			Link.l1 = "Je suppose que tu as raison. Ce serait une honte de gâcher un si bon navigateur.";
			Link.l1.go = "exit";
		break;	

		case "QMASTER_2":
			dialog.text = "Longway ne commerce pas avec les gwailos, chuanzhang. Longway a toujours été à la barre, pas dans une boutique où le vieux crochu marchande jusqu'au dernier réal.";
			link.l1 = "Hm, tu as raison. Tu ferais sans doute peur aux marchands.";
			link.l1.go = "exit";
		break;

		//Указания для компаньона 19.02.08 -->/////////////////////////////////////////////////////////////////////////////////////////
		case "Companion_Tasks":
			dialog.Text = "Je vous écoute.";
			Link.l1 = "Parlons d'abordage.";
			Link.l1.go = "Companion_TaskBoarding";
			Link.l2 = "Parlons de votre navire.";
			Link.l2.go = "Companion_TaskChange";
			if (bBettaTestMode) // Только при бета-тесте
			{
				Link.l3 = "Je veux que tu quittes mon escadron pour un moment et que tu cherches fortune par toi-même.";
				Link.l3.go = "CompanionTravel";
			}
			Link.l8 = "Rien jusqu'à présent.";
			Link.l8.go = "exit";
		break;

		case "Companion_TaskBoarding":
			dialog.Text = "Quel est votre souhait.";
			Link.l1 = "Ne monte pas à l'abordage des navires ennemis. Prends soin de toi et de l'équipage.";
			Link.l1.go = "Companion_TaskBoardingNo";
			Link.l2 = "Je veux que tu abordes les navires ennemis avec agressivité.";
			Link.l2.go = "Companion_TaskBoardingYes";
		break;

		case "Companion_TaskChange":
			dialog.Text = "Quel est votre souhait.";
			Link.l1 = "Ne troque pas ton navire contre un autre après l'avoir abordé. Il est trop précieux.";
			Link.l1.go = "Companion_TaskChangeNo";
			Link.l2 = "Lorsque vous abordez des navires ennemis, vous pouvez les prendre pour vous, s'ils se révèlent être décents.";
			Link.l2.go = "Companion_TaskChangeYes";
		break;

		case "Companion_TaskBoardingNo":
			dialog.Text = "Oui, oui.";
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
			dialog.Text = "Oui, oui.";
			Link.l1 = "Ce sera fait.";
			Link.l1.go = "exit";
			NPChar.Tasks.CanChangeShipAfterBoarding = false;
		break;

		case "Companion_TaskChangeYes":
			dialog.Text = "« Ce sera fait. »";
			Link.l1 = "Repos.";
			Link.l1.go = "exit";
			NPChar.Tasks.CanChangeShipAfterBoarding = true;
		break;
	//	<========////////////////////////////////////////
		case "stay_follow":
            dialog.Text = "Ordres, chuanzhang?";
            Link.l1 = "Tenez bon !";
            Link.l1.go = "Boal_Stay";
            Link.l2 = "Suis-moi et tiens le rythme !";
            Link.l2.go = "Boal_Follow";
			if(CheckAttribute(NPChar, "equip.gun"))
			{
				if(CheckAttribute(NPChar, "chr_ai.gun.bulletNum") && sti(NPChar.chr_ai.gun.bulletNum) > 1)
				{
					Link.l3 = "Changez le type de munitions pour vos armes à feu.";
					Link.l3.go = "SetGunBullets";
				}	
			}
			if(CheckAttribute(NPChar, "equip.musket"))
			{
				if(CheckAttribute(NPChar, "chr_ai.musket.bulletNum") && sti(NPChar.chr_ai.musket.bulletNum) > 1)
				{
					Link.l4 = "Changer le type de munition pour votre mousquet.";
					Link.l4.go = "SetMusketBullets";
				}
					Link.l5 = "Changez votre arme prioritaire pour le combat.";
					Link.l5.go = "SetPriorityMode";
					Link.l6 = "Je veux que tu tires sur les ennemis à une certaine distance, Lonway.";
					Link.l6.go = "TargetDistance";
			}	
		break;
		
		case "SetGunBullets":
			Dialog.Text = "Choisir le type de munitions :";
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
			NextDiag.CurrentNode = NextDiag.TempNode;
			rItem = ItemsFromID(sBullet);
			notification(GetFullName(NPChar)+" "+XI_ConvertString("AmmoSelectNotif")+GetConvertStr(rItem.name, "ItemsDescribe.txt")+"", "AmmoSelect");
			DeleteAttribute(NPChar,"SetGunBullets");
			DialogExit();
		break;

		case "SetMusketBullets":
			Dialog.Text = "Sélectionnez le type de munitions :";
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
				Link.(attrL).go = "SetGunBullets1_" + i;
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
			NextDiag.CurrentNode = NextDiag.TempNode;
			rItem = ItemsFromID(sBullet);
			notification(GetFullName(NPChar)+" "+XI_ConvertString("AmmoSelectNotif")+GetConvertStr(rItem.name, "ItemsDescribe.txt")+"", "AmmoSelect");
			DeleteAttribute(NPChar,"SetMusketBullets");
			DialogExit();
		break;
		
		case "SetPriorityMode":
			Dialog.Text = "Au début du combat, tu utiliseras :";
			Link.l1 = "Lame";
			Link.l1.go = "BladePriorityMode";
			Link.l2 = "Fusil";
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
		
		//--> задать дистанцию стрельбы
		case "TargetDistance":
			dialog.text = "Et quelle distance cela ferait-il ? Gardez à l'esprit, Seigneur Capitaine, que vous ne pouvez toucher quoi que ce soit avec un mousquet au-delà de vingt mètres.";
			link.l1 = "Bonjour, mon ami.";
			Link.l1.edit = 3;
			link.l1.go = "TargetDistance_1";			
		break;
		
		case "TargetDistance_1":
			iTemp = sti(dialogEditStrings[3]);
			if (iTemp < 0)
			{
				dialog.text = "Que voulez-vous dire, Seigneur Capitaine ?";
				link.l1 = "Désolé, parfois j'oublie que tu n'es pas doué avec les blagues.";
				link.l1.go = "exit";
				break;
			}
			if (iTemp == 0)
			{
				dialog.text = "Je tiendrai ma position mais tirerai sur tout ennemi qui s'approche trop près. Est-ce ce que tu veux ?";
				link.l1 = "Oui, exactement, Lonway.";
				link.l1.go = "exit";
				npchar.MusketerDistance = 0;
				break;
			}
			if (iTemp > 20)
			{
				dialog.text = "C'est trop loin, Seigneur Capitaine. Vous pourriez atteindre la foule, mais viser une cible unique - aucune chance.";
				link.l1 = "Ca vaudrait le coup d'essayer, mais d'accord.";
				link.l1.go = "exit";
				npchar.MusketerDistance = 20.0;
				break;
			}
			dialog.text = "Je comprends, Seigneur Capitaine.";
			link.l1 = "Excellent.";
			link.l1.go = "exit";
			npchar.MusketerDistance = iTemp;
		break;
		//<-- задать дистанцию стрельбы
	//<-- ----------------------------------- офицерский блок ----------------------------------------
	
	// на Тайясаль
		case "tieyasal":
			dialog.text = "Longway te suit depuis longtemps. Longway te suivra comme toujours. Longway ne quitte pas son chuanzhang.";
			link.l1 = "Merci, Longway ! Je suis heureux d'avoir eu raison à ton sujet.";
			link.l1.go = "tieyasal_1";
		break;
		
		case "tieyasal_1":
			dialog.text = "Quand commencerons-nous ?";
			link.l1 = "Un peu plus tard. Nous devons nous y préparer.";
			link.l1.go = "tieyasal_2";
		break;
		
		case "tieyasal_2":
			DialogExit();
			AddQuestRecord("Tieyasal", "24");
			npchar.quest.Tieyasal = "teleport";
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}

string SelectJacobCity()
{
	string sTemp;
	switch (hrand(4))
	{
		case 0: sTemp = "Cumana" break;
		case 1: sTemp = "Caracas" break;
		case 2: sTemp = "Maracaibo" break;
		case 3: sTemp = "Cartahena" break;
		case 4: sTemp = "Portobello" break;
	}
	return sTemp;
}
