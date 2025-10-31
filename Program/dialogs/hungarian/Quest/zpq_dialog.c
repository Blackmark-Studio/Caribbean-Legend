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
			dialog.text = "Nem akarok beszélni.";
			link.l1 = "Hm, értem.";
			link.l1.go = "exit";
		break;

		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;

		case "zpq_sld2":
			dialog.text = "Egy pillanat, senor, maga "+ GetFullName (pchar) +"?";
			link.l1 = "Igen... Miben segíthetek?";
			link.l1.go = "zpq_sld2_1";
		break;
		case "zpq_sld2_1":
			dialog.text = "Szükségünk van magára. Pontosabban a pénzére. És ne próbáljon makacskodni, mert ma nem vagyok jó kedvemben, tudok dühös lenni.";
			link.l1 = "Ó, kérem, milyen pénzrôl beszél? Tényleg azt hiszed, hogy magammal viszem a kincset?";
			link.l1.go = "zpq_sld2_2";
		break;
		case "zpq_sld2_2":
			dialog.text = "Ne próbálj átverni. Csak adja ide a pénzt - " + FindRussianMoneyString(sti(pchar.questTemp.zpq.sum)) + " és mehet a saját útjára. Vagy erôszakkal vesszük el.";
			if (pchar.questTemp.zpq == "failed")
			{
				link.l1 = "Nem dolgozol ennek az erôdpatkánynak? Akkor jó hírem van számodra, a pokolba küldtem.";
				link.l1.go = "zpq_sld2_3_1";
			}
			else
			{
				link.l1 = "Nem ennek a patkánynak dolgozol? Mondd meg neki, hogy a pénzt megbízható kezekbe adták, hogy elfelejthesse ôket.";
			link.l1.go = "zpq_sld2_3";
			}
			if(makeint(Pchar.money) >= sti(pchar.questTemp.zpq.sum))
			{
				link.l2 = "Rendben, vidd a mocskos pénzed, te szemétláda!";
				link.l2.go = "zpq_sld2_6";
			}
			else
			{
				link.l2 = "Nincsenek nálam...";
				link.l2.go = "zpq_sld2_3";
			}
		break;
		case "zpq_sld2_3":
			dialog.text = "Akkor ez a sorsod - fiatalon meghalni a kapzsiságod miatt. Túl veszélyes életben hagyni téged.";
			link.l1 = "Micsoda önbizalom.";
			link.l1.go = "zpq_sld2_4";
		break;
		case "zpq_sld2_3_1":
			dialog.text = "Hé, akkor az a sorsod, hogy meghalsz a kapzsiságod miatt. Nekünk megfelel, mi nem akarunk osztozkodni.";
			link.l1 = "A kapzsiságod az, ami meg fog ölni...";
			link.l1.go = "zpq_sld2_4";
		break;
		case "zpq_sld2_4":
			dialog.text = "Hé, srácok!!! Tegyetek egy zsákot a fejére!";
			link.l1 = "Nos, a te döntésed volt...";
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
			dialog.text = "Szép volt. Add oda és tûnj el, kapitány!";
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
