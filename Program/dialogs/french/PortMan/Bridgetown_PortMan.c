// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
	bool ok;
    int iTest;
    ref rColony;
    string sFrom_sea = "";
    switch (Dialog.CurrentNode)
	{
		case "quests":
			//регата
			if (CheckAttribute(pchar, "questTemp.Regata.Go") && !CheckAttribute(npchar, "quest.regatatalk"))
			{
				dialog.text = "Que voulez-vous? Ah-ha, vous êtes le participant de la régate! Ai-je raison?";
				link.l1 = "Exactement, monsieur. Je dois m'enregistrer ici selon les règles.";
				link.l1.go = "Regata_check";
				break;
			}
			//регата
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("Quel genre de questions ?","Que voulez-vous, "+GetAddress_Form(NPChar)+"?"),"Vous avez déjà essayé de me poser une question "+GetAddress_Form(NPChar)+"... ","Tu parles de cette question pour la troisième fois aujourd'hui...","Écoutez, si vous n'avez rien à me dire sur les affaires du port, alors ne me dérangez pas avec vos questions.","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("J'ai changé d'avis.","Je n'ai rien à dire."),"Peu importe.","En effet, déjà la troisième fois...","Désolé, mais les affaires du port ne m'intéressent pas pour l'instant.",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
			//Голландский гамбит
			if (CheckAttribute(pchar, "questTemp.HWIC.Eng") && pchar.questTemp.HWIC.Eng == "GotoBridgetown" && !CheckAttribute(npchar, "quest.HWICTalked"))
            {
                link.l1 = "Je navigue vers Blueweld pour vendre du paprika. Dites-moi, monsieur, avez-vous des passagers qui se dirigent vers Blueweld ? Ou au moins vers Port-Royal. Ce serait formidable de gagner un peu d'argent grâce à un passager, ça pourrait aider à payer les gages de l'équipage. Je les ai déjà réduits au minimum, mais ces fainéants demandent encore de l'argent...";
                link.l1.go = "PortofficeDone";
            }
			// Страж Истины
			if (CheckAttribute(pchar, "questTemp.Guardoftruth") && pchar.questTemp.Guardoftruth == "barbados")
			{
				link.l1 = "Il y avait un galion nommé 'Admirable' chargé à Philipsburg sous le commandement de Gaius Marchais. Il devait livrer ici une cargaison de paprika. Pouvez-vous m'aider à retrouver ce capitaine ?";
                link.l1.go = "guardoftruth";
			}
			// калеуче
			if (CheckAttribute(pchar, "questTemp.Caleuche") && pchar.questTemp.Caleuche == "hunting" && !CheckAttribute(npchar, "quest.garpiya"))
			{
				if (CheckAttribute(npchar, "questTemp.caleuche"))
				{
					link.l1 = "Je voulais me renseigner sur un chébec avec un nom étrange.";
					link.l1.go = "caleuche_2";
				}
				else
				{
					link.l1 = "J'ai entendu dire qu'un chebec appartenant à un capitaine Jack... ou Jackson visite souvent votre port. Pourriez-vous me dire où le chercher ?";
					link.l1.go = "caleuche";
				}
			}
		break;

		//Голландский гамбит
		case "PortofficeDone":
			dialog.text = "Malheureusement, il n'y a pas de passagers pour Blueweld ni pour Port-Royal. Revenez demain ou après-demain.";
			link.l1 = "Quel dommage. Adieu alors.";
			link.l1.go = "exit";	
			npchar.quest.HWICTalked = "true";
			pchar.questTemp.HWIC.Eng.BridgeCounter = sti(pchar.questTemp.HWIC.Eng.BridgeCounter)+1;
			AddQuestRecord("Holl_Gambit", "2-9");
			DelLandQuestMark(npchar);
			if (sti(pchar.questTemp.HWIC.Eng.BridgeCounter) == 7) 
			{
				AddQuestRecord("Holl_Gambit", "2-6");
				pchar.quest.GotoBridgetownOver.over = "yes";//снять таймер
				DelMapQuestMarkCity("Bridgetown");
				pchar.questTemp.HWIC.Eng = "SeekVanBerg";
				pchar.quest.VanBergAttack_Check.win_condition.l1 = "MapEnter";
				pchar.quest.VanBergAttack_Check.function = "VanBergAttackCheck";
			}
		break;

		//регата
		case "Regata_check":
		iTest = FindColony(npchar.city); 
		if (iTest != -1)
		{
			rColony = GetColonyByIndex(iTest);
			sFrom_sea = rColony.from_sea;
		}
		ok = (rColony.from_sea == "") || (Pchar.location.from_sea == rColony.from_sea);
		if(sti(Pchar.Ship.Type) != SHIP_NOTUSED && ok)//проверка на наличие корабля в порту
		{
			bool bRegLugger = sti(RealShips[sti(pchar.ship.type)].basetype) == SHIP_LUGGER || sti(RealShips[sti(pchar.ship.type)].basetype) == SHIP_CAREERLUGGER;
			pchar.quest.Regata_PU.over = "yes"; // mitrokosta снимаем прерывание
			if (CheckAttribute(pchar, "questTemp.Regata.Breach") || !CheckAttribute(pchar, "questTemp.Regata.Sentjons") || GetCompanionQuantity(pchar) > 1 || !bRegLugger || pchar.Ship.Name != "Saint Catherine")
			{
				dialog.text = "Hm... Vous avez enfreint les règles de la régate et je dois vous disqualifier. Je suis désolé. Vous ne participerez pas au prochain voyage. J'ai déjà préparé un message pour Port-Royal.";
				link.l1 = "Eh... quel dommage ! Mais je ne peux rien y faire, tu étais trop vigilant. Adieu !";
				link.l1.go = "exit";
				DeleteAttribute(pchar, "questTemp.Regata");
				AddQuestRecord("Regata", "45");
				CloseQuestHeader("Regata");
			}
			else
			{
				pchar.questTemp.Regata.FourthTransitionTime = GetPastTime("hour", sti(pchar.questTemp.Regata.StartYear), sti(pchar.questTemp.Regata.StartMonth), sti(pchar.questTemp.Regata.StartDay), stf(pchar.questTemp.Regata.StartTime), GetDataYear(), GetDataMonth(), GetDataDay(), GetTime());//истратил ГГ в часах на 1+2+3+4 переход
				dialog.text = "Vous avez peut-être remarqué, capitaine, que la ville est assiégée. Nous nous attendons à ce que les Espagnols nous attaquent à tout moment et nous mobilisons nos forces. Mais la régate continue toujours\nInscrivons-nous : capitaine "+GetFullName(pchar)+", le navire est - "+pchar.Ship.Name+"Le temps de la régate en heures est "+sti(pchar.questTemp.Regata.FourthTransitionTime)+"Fait, votre résultat est enregistré, vous pouvez continuer votre chemin.";
				link.l1 = "Dis-moi mon rang.";
				link.l1.go = "Regata_info";
			}
		}
		else
		{
			dialog.text = "Vous êtes ici mais je ne vois pas votre navire. Où est-il ?";
			link.l1 = "Je suis désolé, monsieur. Je vais transférer mon navire au port immédiatement.";
			link.l1.go = "exit";
		}
		break;
		
		case "Regata_info":
			int n=1;
			string sTemp, sName, sShip;
			for (int i=1; i <=5; i++)
			{
				if (i==1) sTemp = "a";
				if (i==2) sTemp = "b";
				if (i==3) sTemp = "c";
				if (i==4) sTemp = "d";
				if (i==5) sTemp = "e";
				if (pchar.questTemp.Regata.AdversaryFourthTransition.Time.(sTemp) < sti(pchar.questTemp.Regata.FourthTransitionTime))
				{
					n++;
					sName = pchar.questTemp.Regata.AdversaryName.(sTemp);//имя ближайшего противника
					sShip = pchar.questTemp.Regata.AdversaryShipName.(sTemp);//его корабль
				}
			}
			if (n==1)
			{
			dialog.text = "Ah, oui... Je suis désolé, j'étais trop occupé pour cela. Vous êtes le premier.";
			link.l1 = "Je vois. Merci pour vos informations.";
			link.l1.go = "exit";
			AddQuestRecord("Regata", "22");
			}
			else
			{
				if (n==6)
				{
				dialog.text = "Ah, oui... Je suis désolé, je suis trop occupé pour cela. Vous êtes le dernier.";
				link.l1 = "Je vois. Merci pour vos informations.";
				link.l1.go = "exit";
				AddQuestRecord("Regata", "27");
				}
				else
				{
					if (n==2)
					{
						dialog.text = "Ah, oui... Je suis désolé, je suis trop occupé pour cela. Vous êtes le deuxième. Il n'y a qu'un seul capitaine qui vous devance. Son nom est "+sName+" sur le navire "+sShip+".";
						link.l1 = "Je vois. Merci pour votre information.";
						link.l1.go = "exit";
						AddQuestRecord("Regata", "23");
					}
					else
					{
						dialog.text = "Ah, oui... Je suis désolé, je suis trop occupé pour cela. Ton rang est "+n+" . Votre adversaire le plus proche est "+sName+" sur le navire "+sShip+".";
						link.l1 = "Je vois. Merci pour votre information.";
						link.l1.go = "exit";
						if (n==3) AddQuestRecord("Regata", "24");
						if (n==4) AddQuestRecord("Regata", "25");
						if (n==5) AddQuestRecord("Regata", "26");
					}
				}
			}
			AddCharacterExpToSkill(pchar, "Sailing", 50);//навигация
			AddCharacterExpToSkill(pchar, "Defence", 30);//защита
			AddCharacterExpToSkill(pchar, "Repair", 30);//починка
			AddCharacterExpToSkill(pchar, "Fortune", 30);//везение
			AddCharacterExpToSkill(pchar, "Sneak", 30);//скрытность
			npchar.quest.regatatalk = "true";
			pchar.questTemp.Regata.Bridgetown = "true";//отметка Бриджтауна
			pchar.quest.Regata_Check1.win_condition.l1 = "location";
			pchar.quest.Regata_Check1.win_condition.l1.location = "Curacao";
			pchar.quest.Regata_Check1.function = "RegataCheck";//проверка 1
			pchar.quest.Regata_Check2.win_condition.l1 = "location";
			pchar.quest.Regata_Check2.win_condition.l1.location = "Caracas";
			pchar.quest.Regata_Check2.function = "RegataCheck";//проверка 2
			pchar.quest.Regata_Check3.win_condition.l1 = "location";
			pchar.quest.Regata_Check3.win_condition.l1.location = "PortoBello";
			pchar.quest.Regata_Check3.function = "RegataCheck";//проверка 3
			pchar.quest.Regata_Check.win_condition.l1 = "location";
			pchar.quest.Regata_Check.win_condition.l1.location = "Jamaica";
			pchar.quest.Regata_Check.function = "RegataCheck";//проверка 4
			pchar.questTemp.Regata.AttackIsland = "Curacao";
			pchar.questTemp.Regata.AttackNation = HOLLAND;
			pchar.quest.Regata_Attack.win_condition.l1 = "location";
			pchar.quest.Regata_Attack.win_condition.l1.location = "Curacao";
			pchar.quest.Regata_Attack.function = "RegataAttack_Brigantine";
			pchar.quest.Regata_Attack1.win_condition.l1 = "location";
			pchar.quest.Regata_Attack1.win_condition.l1.location = "Curacao";
			pchar.quest.Regata_Attack1.function = "RegataAttack_Corvette";//третья засада
			pchar.quest.Regata_Hunter.win_condition.l1 = "location";
			pchar.quest.Regata_Hunter.win_condition.l1.location = "Barbados";
			pchar.quest.Regata_Hunter.function = "RegataAttack_Hunter";//ДУ у Барбадоса
			pchar.quest.Regata_Finish.win_condition.l1 = "location";
			pchar.quest.Regata_Finish.win_condition.l1.location = "Jamaica";
			pchar.quest.Regata_Finish.function = "RegataFinishSea";
			pchar.quest.Regata_Finish1.win_condition.l1 = "location";
			pchar.quest.Regata_Finish1.win_condition.l1.location = "Portroyal_town";
			pchar.quest.Regata_Finish1.function = "RegataFinishTown";//финиш регаты
			//ситуации
			pchar.quest.Regata_Siege.win_condition.l1 = "location";
			pchar.quest.Regata_Siege.win_condition.l1.location = "Bridgetown_town";
			pchar.quest.Regata_Siege.function = "RegataSiegeOfficer";//на квест по вывозу жителей
		break;
		//регата
		
		// Страж Истины
		case "guardoftruth":
			dialog.text = "Oui, ce galion était ici, il s'est fait délester de ses marchandises et a quitté notre port ensuite. Des informations sur sa destination... hm... aucune, il n'y a rien. Je suis désolé, mais je ne peux rien faire.";
			link.l1 = "Je vois. Quel dommage... Je continuerai à le chercher.";
			link.l1.go = "guardoftruth_1";
		break;
		
		case "guardoftruth_1":
			DialogExit();
			AddQuestRecord("Guardoftruth", "13");
			pchar.questTemp.Guardoftruth = "barbados1";
		break;
		
		// калеуче
		case "caleuche":
			dialog.text = "Monsieur, j'ai besoin du nom exact du navire. Nous avons des tonnes de Jacks et Jacksons qui passent par notre port. Alors, quel est le nom ?";
			link.l1 = "Sirène"; 
			link.l1.go = "caleuche_wrong_name";
			link.l2 = "Lamia"; 
			link.l2.go = "caleuche_wrong_name";
			link.l3 = "Harpie"; 
			link.l3.go = "caleuche_name";
			link.l4 = "Furie"; 
			link.l4.go = "caleuche_wrong_name";
			link.l5 = "Le problème, c'est que je ne connais pas le nom de sa vieille barcasse. C'est étrange, une femme oiseau, née...";
			link.l5.go = "caleuche_1";
		break;
		
		case "caleuche_1":
			dialog.text = "Monsieur, allez raconter vos histoires et énigmes à la taverne, nous avons ici un établissement sérieux. Soit vous me dites le nom de ce chébec, soit vous cessez de me déranger dans mon travail.";
			link.l1 = "D'accord, je vais essayer de découvrir.";
			link.l1.go = "exit";
			npchar.questTemp.caleuche = "true";
		break;
		
		case "caleuche_2":
			dialog.text = "Alors ? Avez-vous le nom du navire ? J'écoute.";
			link.l1 = "Sirène"; 
			link.l1.go = "caleuche_wrong_name";
			link.l2 = "Lamia"; 
			link.l2.go = "caleuche_wrong_name";
			link.l3 = "Harpie"; 
			link.l3.go = "caleuche_name";
			link.l4 = "Furie"; 
			link.l4.go = "caleuche_wrong_name";
			link.l5 = "J'ai besoin de réfléchir encore un peu.";
			link.l5.go = "exit";
		break;
		
		case "caleuche_name":
			dialog.text = "'Harpy'? Bien sûr, je connais ce chébec. Son capitaine est Reginald Jackson. Mais il n'était pas à Bridgetown depuis longtemps. J'ai entendu dire qu'il travaille maintenant pour la Compagnie néerlandaise des Indes occidentales. Donc, vous devriez le chercher à Willemstad.";
			link.l1 = "Merci beaucoup ! Vous m'avez beaucoup aidé.";
			link.l1.go = "caleuche_3";
			DelLandQuestMark(npchar);
		break;
		
		case "caleuche_wrong_name":
			dialog.text = "Je suis désolé, mais cela ne me dit rien. Êtes-vous sûr que votre capitaine est déjà venu ici, à Bridgetown ?";
			link.l1 = "Je suis sûr. D'accord, peut-être que je vais trouver quelque chose ...";
			link.l1.go = "exit";
			npchar.questTemp.caleuche = "true";
		break;
		
		case "caleuche_3":
			DialogExit();
			AddQuestRecord("Caleuche", "18");
			pchar.questTemp.Caleuche.Garpiya = "gwik"; 
			npchar.quest.garpiya = "true";
			AddLandQuestMarkToPhantom("GVIK", "HWIC_headclerk");
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
