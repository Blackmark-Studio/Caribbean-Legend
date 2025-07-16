void ProcessDialogEvent()
{
	ref NPChar;
	aref Link, NextDiag;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			dialog.text = "Non ho voglia di parlare.";
			link.l1 = "Mm, capisco.";
			link.l1.go = "exit";
		break;

		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;

		case "zpq_sld2":
			dialog.text = "Un attimo, señor, siete voi per caso "+GetFullName(pchar)+"?";
			link.l1 = "Sì... In che modo posso esserti d’aiuto??";
			link.l1.go = "zpq_sld2_1";
		break;
		case "zpq_sld2_1":
			dialog.text = "Abbiamo bisogno di te. O meglio, dei tuoi dobloni. E non fare il testardo, ché oggi non ho il vento in poppa: potrei anche perdere la pazienza.";
			link.l1 = "Oh, ti prego, di quali soldi vai cianciando? Davvero pensi che mi porti il tesoro appresso?";
			link.l1.go = "zpq_sld2_2";
		break;
		case "zpq_sld2_2":
			dialog.text = "Non provare a fregarmi. Dammi solo i soldi – "+FindRussianMoneyString(sti(pchar.questTemp.zpq.sum))+" e puoi andartene per la tua strada. Oppure ce lo prenderemo con la forza.";
			if (pchar.questTemp.zpq == "failed")
			{
				link.l1 = "Non lavori forse per quella carogna del forte? Allora ti porto buone nuove, l’ho già mandato all’inferno.";
				link.l1.go = "zpq_sld2_3_1";
			}
			else
			{
				link.l1 = "Non lavori forse per quella carogna del forte? Digli che il denaro è finito in mani fidate, così può pure scordarsene.";
			link.l1.go = "zpq_sld2_3";
			}
			if(makeint(Pchar.money) >= sti(pchar.questTemp.zpq.sum))
			{
				link.l2 = "Va bene, prendi i tuoi sporchi dobloni, bastardo!";
				link.l2.go = "zpq_sld2_6";
			}
			else
			{
				link.l2 = "Non li ho addosso...";
				link.l2.go = "zpq_sld2_3";
			}
		break;
		case "zpq_sld2_3":
			dialog.text = "Allora questo è il tuo destino: crepare giovane per la tua brama. Lasciarti vivo sarebbe una follia troppo pericolosa.";
			link.l1 = "Che sfrontatezza.";
			link.l1.go = "zpq_sld2_4";
		break;
		case "zpq_sld2_3_1":
			dialog.text = "He-he, allora il tuo destino è crepare per la tua avidità. Fa comodo a noi: non vogliamo spartire un bel niente.";
			link.l1 = "È la tua brama che ti porterà alla rovina...";
			link.l1.go = "zpq_sld2_4";
		break;
		case "zpq_sld2_4":
			dialog.text = "Ehi, ragazzi!! Mettetegli un sacco in testa!";
			link.l1 = "Ebbene, è stata la tua scelta...";
			link.l1.go = "zpq_sld2_5";
		break;
		case "zpq_sld2_5":
			LAi_LocationFightDisable(loadedLocation, false);
			LAi_SetFightMode(PChar, true);

			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			DialogExit();	
			AddDialogExitQuest("MainHeroFightModeOn");
			AddQuestRecord("zpq", "7");

			pchar.quest.zpq_seaBattle.win_condition.l1 = "location";
			pchar.quest.zpq_seaBattle.win_condition.l1.location = "Cumana";
			pchar.quest.zpq_seaBattle.function = "zpq_seaBattle";
		break;
		case "zpq_sld2_6":
			dialog.text = "Bene. Dalli qui e sparisci, capitano!";
			link.l1 = "...";
			link.l1.go = "zpq_sld2_7";
			AddMoneyToCharacter(Pchar, -makeint(pchar.questTemp.zpq.sum));
			ChangeCharacterComplexReputation(pchar,"nobility", -5);
			AddQuestRecord("zpq", "8");
			AddQuestUserData("zpq", "sSex", GetSexPhrase("",""));
		break;
		case "zpq_sld2_7":
			DialogExit();
			LAi_LocationFightDisable(loadedLocation, false);
			for(int i = 1; i <= 3; i++)

			{

				sld = CharacterFromID("qp2_" +i);
				LAi_SetImmortal(sld, true);
				LAi_type_actor_Reset(sld);
				LAi_ActorGoToLocation(sld, "reload", "reload1_back", "none", "", "", "", 6.0);
			}
		break;
	}
}
