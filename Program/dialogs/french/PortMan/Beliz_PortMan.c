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
				dialog.text = "Que voulez-vous ? A-ha, vous êtes le participant de la régate ! Ai-je raison ?";
				link.l1 = "Exactement, monsieur. Je dois m'enregistrer ici selon les règles.";
				link.l1.go = "Regata_check";
				break;
			}
			//регата
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("Quel genre de questions?","Que veux-tu, "+GetAddress_Form(NPChar)+"?"),"Vous avez déjà essayé de me poser une question "+GetAddress_Form(NPChar)+"... ","Vous parlez de cette question pour la troisième fois aujourd'hui...","Écoutez, si vous n'avez rien à me dire sur les affaires portuaires, alors ne me dérangez pas avec vos questions.","bloc",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("J'ai changé d'avis.","Je n'ai rien à dire."),"Peu importe.","En effet, déjà la troisième fois...","Désolé, mais les affaires du port ne m'intéressent pas pour le moment.",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
			//--> Грани справедливости
			if (CheckAttribute(pchar, "questTemp.GS_Portman"))
			{
				link.l1 = "J'ai entendu dire qu'on avait tenté de vous assassiner, et que vous cherchez l'agresseur ?";
				link.l1.go = "GS_Portman_1";
			}
			if (CheckAttribute(pchar, "questTemp.GS_NaemnikMertv"))
			{
				link.l1 = "L'homme qui a attenté à votre vie est tombé, monsieur "+npchar.lastname+". Plus rien ne vous menace.";
				link.l1.go = "GS_Portman_6";
			}
			//<-- Грани справедливости
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
			if (CheckAttribute(pchar, "questTemp.Regata.Breach") || GetCompanionQuantity(pchar) > 1 || !bRegLugger || pchar.Ship.Name != "Saint Catherine")
			{
			dialog.text = "Hm... Vous avez enfreint les règles de la régate et je dois vous disqualifier. Je suis désolé. Vous ne participerez pas au prochain voyage. J'ai déjà préparé une dépêche pour Port-Royal.";
			link.l1 = "Oups... quel dommage ! Mais je ne peux rien faire ici, tu étais trop vigilant. Adieu !";
			link.l1.go = "exit";
			DeleteAttribute(pchar, "questTemp.Regata");
			pchar.quest.Regata_PU.over = "yes"; // mitrokosta снимаем прерывание
			AddQuestRecord("Regata", "45");
			CloseQuestHeader("Regata");
			}
			else
			{
			pchar.questTemp.Regata.FirstTransitionTime = GetPastTime("hour", sti(pchar.questTemp.Regata.StartYear), sti(pchar.questTemp.Regata.StartMonth), sti(pchar.questTemp.Regata.StartDay), stf(pchar.questTemp.Regata.StartTime), GetDataYear(), GetDataMonth(), GetDataDay(), GetTime());//истратил ГГ в часах на 1 переход
			dialog.text = "Enregistrons-nous : capitaine "+GetFullName(pchar)+", le navire est "+pchar.Ship.Name+"... le temps de la régate en heures est "+sti(pchar.questTemp.Regata.FirstTransitionTime)+". Fait, votre résultat est enregistré, vous pouvez continuer votre chemin.";
			link.l1 = "Dis-moi mon grade.";
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
				if (pchar.questTemp.Regata.AdversaryFirstTransition.Time.(sTemp) < sti(pchar.questTemp.Regata.FirstTransitionTime))
				{
					n++;
					sName = pchar.questTemp.Regata.AdversaryName.(sTemp);//имя ближайшего противника
					sShip = pchar.questTemp.Regata.AdversaryShipName.(sTemp);//его корабль
				}
			}
			if (n==1)
			{
			dialog.text = "Vous êtes en tête. Félicitations ! Continuez comme ça !";
			link.l1 = "Merci !";
			link.l1.go = "exit";
			AddQuestRecord("Regata", "4");
			}
			else
			{
				if (n==6)
				{
				dialog.text = "Vous êtes le dernier. Vous devriez vous dépêcher.";
				link.l1 = "Je suis en route !";
				link.l1.go = "exit";
				AddQuestRecord("Regata", "9");
				}
				else
				{
					if (n==2)
					{
					dialog.text = "Vous êtes le second. Le chef est "+sName+" sur le navire "+sShip+"Je suppose que tu peux encore le distancer.";
					link.l1 = "Merci ! Je vais essayer !";
					link.l1.go = "exit";
					AddQuestRecord("Regata", "5");
					}
					else
					{
					dialog.text = "Votre rang est "+n+". Votre adversaire le plus proche est "+sName+" sur le navire "+sShip+".";
					link.l1 = "Merci !";
					link.l1.go = "exit";
					if (n==3) AddQuestRecord("Regata", "6");
					if (n==4) AddQuestRecord("Regata", "7");
					if (n==5) AddQuestRecord("Regata", "8");
					}
				}
			}
			AddCharacterExpToSkill(pchar, "Sailing", 50);//навигация
			npchar.quest.regatatalk = "true";
			pchar.questTemp.Regata.Beliz = "true";//отметка Белиза
			pchar.quest.Regata_Check1.win_condition.l1 = "location";
			pchar.quest.Regata_Check1.win_condition.l1.location = "Cuba1";
			pchar.quest.Regata_Check1.function = "RegataCheck";//проверка 1
			pchar.quest.Regata_Check2.win_condition.l1 = "location";
			pchar.quest.Regata_Check2.win_condition.l1.location = "Cuba2";
			pchar.quest.Regata_Check2.function = "RegataCheck";//проверка 2
			pchar.quest.Regata_Check.win_condition.l1 = "location";
			pchar.quest.Regata_Check.win_condition.l1.location = "Hispaniola2";
			pchar.quest.Regata_Check.function = "RegataCheck";//проверка 3
			pchar.questTemp.Regata.AttackIsland = "Cuba1";
			pchar.questTemp.Regata.AttackNation = SPAIN;
			pchar.quest.Regata_Attack.win_condition.l1 = "location";
			pchar.quest.Regata_Attack.win_condition.l1.location = "Cuba1";
			pchar.quest.Regata_Attack.function = "RegataAttack_Lugger";//первая засада у Сантьяго
			pchar.quest.Regata_Hunter.win_condition.l1 = "location";
			pchar.quest.Regata_Hunter.win_condition.l1.location = "Cuba2";
			pchar.quest.Regata_Hunter.function = "RegataAttack_Hunter";//ДУ у Гаваны
			pchar.questTemp.Regata.Town = "Portpax";
			pchar.quest.Regata_PU.win_condition.l1 = "locator";
			pchar.quest.Regata_PU.win_condition.l1.location = "Portpax_town";
			pchar.quest.Regata_PU.win_condition.l1.locator_group = "reload";
			pchar.quest.Regata_PU.win_condition.l1.locator = "reload10_back";
			pchar.quest.Regata_PU.win_condition.l2 = "Night";
			pchar.quest.Regata_PU.function = "RegataPU_Open";//вход в ПУ ночью
		break;
		//регата
		//--> Грани справедливости
		case "GS_Portman_1":
			dialog.text = "Oui, une tentative d'assassinat a bien eu lieu, c'est vrai. Quant à retrouver le coupable... c'est un peu différent. Je ne veux pas qu'on me ramène un criminel en fuite – je veux sa tête. C’est le seul moyen de retrouver la paix.";
			Link.l1 = "Avez-vous une idée de qui a pu vous attaquer et pourquoi ?";
			Link.l1.go = "GS_Portman_2";
			DelLandQuestMark(npchar);
		break;
		
		case "GS_Portman_2":
			dialog.text = "Je... Je ne sais pas qui c'était ! Je ne sais pas d'où il venait ni pourquoi il m'a attaqué. Mais une chose est sûre – il voulait ma mort. Et maintenant... maintenant je veux la sienne avec la même fureur ! Vous comprenez ?\nAlors épargnez-moi vos questions inutiles. Votre curiosité ne m'aide en rien, seules les actions comptent. Deux cents doublons pour sa tête – voilà ce que je propose. Recherchez-le, ou cessez de perdre mon temps avec des bavardages.";
			Link.l1 = "Je comprends que la peur et la colère vous aveuglent, et je vous pardonne même ce ton. Mais reprenez-vous. Je ne vois pas foule pour résoudre vos problèmes, alors modérez-vous. Deux cents doublons me conviennent, mais avant de commencer, je dois tout savoir.";
			Link.l1.go = "GS_Portman_3";
			Link.l2 = "Vos paroles ne sont que des bavardages creux, sans le moindre indice. Chercher un inconnu dans la jungle, c’est comme chercher une aiguille dans une meule de foin. Je ne vais pas perdre mon temps dans une quête sans espoir. Bonne chance. Vous en aurez besoin.";
			Link.l2.go = "GS_Portman_End";
		break;
		
		case "GS_Portman_End":
			DialogExit();
			CloseQuestHeader("GS");
			DeleteAttribute(pchar, "questTemp.GS_Portman");
		break;
		
		case "GS_Portman_3":
			dialog.text = "Grrh... Pardonnez-moi, "+GetAddress_Form(NPChar)+", mes nerfs sont à vif... Que voulez-vous savoir précisément ?";
			Link.l1 = "Avez-vous remarqué des détails particuliers qui pourraient m’aider à l’identifier ? Était-il seul, ou agissait-il pour le compte d’un ennemi plus puissant ? Plus vous en dites, plus vite vous retrouverez la paix.";
			Link.l1.go = "GS_Portman_4";
		break;
		
		case "GS_Portman_4":
			dialog.text = "Quel ennemi ?! Je n’ai pas d’ennemis ! Je n’en ai jamais eu ! Je ne fais rien qui mérite la mort, surtout pas ainsi, en plein jour, au milieu de la rue\nCe vaurien... c’est juste un fou enragé, comme il y en a tant dans ces colonies\nQuant à sa cachette... je parie qu’il se terre dans la jungle. C’est facile de s’y perdre, mais je suis certain qu’il a gagné les grottes ou les criques – des endroits faciles à dissimuler\nPour son apparence, son visage était couvert d’un foulard, il portait un chapeau, et il avait plus d’armes sur lui qu’un garde royal. Je n’ai pas eu le temps d’en voir davantage.";
			Link.l1 = "Très bien, ce n’est pas beaucoup, mais c’est suffisant pour commencer. Je pars sur-le-champ. Ne cachez pas votre or trop loin – je reviendrai bientôt.";
			Link.l1.go = "GS_Portman_5";
		break;
		
		case "GS_Portman_5":
			DialogExit();
			AddQuestRecord("GS", "2");
			DeleteAttribute(pchar, "questTemp.GS_Portman");
			
			PChar.quest.GS_Peshera.win_condition.l1 = "location";
			PChar.quest.GS_Peshera.win_condition.l1.location = "Beliz_Cave";
			PChar.quest.GS_Peshera.function = "GS_Peshera";
			locations[FindLocation("Beliz_Cave")].DisableEncounters = true;
			
			PChar.quest.GS_Peshera_pusto.win_condition.l1 = "location";
			PChar.quest.GS_Peshera_pusto.win_condition.l1.location = "Beliz_Cave_2";
			PChar.quest.GS_Peshera_pusto.function = "GS_Peshera_pusto";
		break;
		
		case "GS_Portman_6":
			dialog.text = "Excellent, "+GetFullName(pchar)+" ! Tout simplement excellent ! Vous avez prouvé que votre habileté est sans égale. Voici votre récompense – deux cents doublons. Je vous en prie, acceptez-les !";
			Link.l1 = "Merci ! Mais dites-moi, avez-vous des raisons de croire que le tueur a été engagé par l'un de vos anciens clients ?";
			Link.l1.go = "GS_Portman_7";
			AddItems(pchar, "gold_dublon", 200);
			DelLandQuestMark(npchar);
		break;
		
		case "GS_Portman_7":
			dialog.text = "D'anciens clients ?... Quelle absurdité !... Je suis un homme honnête, et mes affaires ont toujours été propres ! Mais puisque vous m'avez aidé, je vais vous dire. Il n'y a pas longtemps, des pirates sont venus me voir\nIls m'ont proposé de me payer pour vendre des informations sur les navires marchands. J'ai refusé, et ils m'ont lancé des menaces et des malédictions, puis sont partis. Je pense que cet assassin est leur œuvre. Ils ne tolèrent pas les refus.";
			Link.l1 = "Dans ce cas, prenez soin de vous. Qui sait combien d'autres tueurs à gages ces ‘pirates’ pourraient encore envoyer ? Sur ce, je dois prendre congé — des affaires m'attendent.";
			Link.l1.go = "GS_Portman_8";
		break;
		
		case "GS_Portman_8":
			dialog.text = "Attendez, Capitaine. Je tiens à vous remercier une fois de plus. En plus de l'argent, vous avez gagné ma faveur. Tant que je serai chef du port ici, vous pourrez laisser n'importe lequel de vos navires ici pour la durée que vous voulez avec une remise de cinquante pour cent. Qu'en dites-vous ?";
			Link.l1 = "Très généreux de votre part ! Merci encore !";
			Link.l1.go = "GS_Portman_9";
		break;
		
		case "GS_Portman_9":
			dialog.text = "Et je vous remercie encore une fois pour le travail accompli. Je suis sûr que si des pensées inutiles ne vous distraient pas de ce qui est important, vos affaires continueront à être aussi prospères qu'aujourd'hui. Au revoir, Capitaine.";
			Link.l1 = "Au revoir.";
			Link.l1.go = "GS_Portman_10";
		break;
		
		case "GS_Portman_10":
			DialogExit();
			AddQuestRecord("GS", "4");
			CloseQuestHeader("GS");
			DeleteAttribute(pchar, "questTemp.GS_NaemnikMertv");
			pchar.questTemp.GS_BelizSkidka = true;
		break;
		//<-- Грани справедливости
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
