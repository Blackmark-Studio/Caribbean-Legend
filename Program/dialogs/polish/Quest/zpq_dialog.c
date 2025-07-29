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
			dialog.text = "Nie chcę rozmawiać.";
			link.l1 = "Hm, rozumiem.";
			link.l1.go = "exit";
		break;

		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;

		case "zpq_sld2":
			dialog.text = "Chwileczkę, señor, ty jesteś "+GetFullName(pchar)+"?";
			link.l1 = "Tak... Jak mogę ci pomóc??";
			link.l1.go = "zpq_sld2_1";
		break;
		case "zpq_sld2_1":
			dialog.text = "Potrzebujemy cię. A mówiąc konkretniej, twoich pieniędzy. I nie próbuj być uparty, bo nie jestem dziś w dobrym nastroju, mogę się rozgniewać.";
			link.l1 = "Och, proszę, o jakich pieniądzach mówisz? Czy naprawdę myślisz, że będę przy sobie nosił caluśki skarbiec?";
			link.l1.go = "zpq_sld2_2";
		break;
		case "zpq_sld2_2":
			dialog.text = "Nie próbuj mnie oszukać. Po prostu daj mi pieniądze - "+FindRussianMoneyString(sti(pchar.questTemp.zpq.sum))+" i możesz odejść swoją drogą. Albo weźmiemy je siłą.";
			if (pchar.questTemp.zpq == "failed")
			{
				link.l1 = "Nie pracujesz dla tego szczura z fortu? Mam dla ciebie dobrą wiadomość, wysłałem go do piekła.";
				link.l1.go = "zpq_sld2_3_1";
			}
			else
			{
				link.l1 = "Nie pracujesz dla tego szczura fortowego? Powiedz mu, że pieniądze zostały przekazane w godne zaufania ręce, więc może o nich zapomnieć.";
			link.l1.go = "zpq_sld2_3";
			}
			if(makeint(Pchar.money) >= sti(pchar.questTemp.zpq.sum))
			{
				link.l2 = "Dobrze, weź swoje brudne pieniądze, łajdaku!";
				link.l2.go = "zpq_sld2_6";
			}
			else
			{
				link.l2 = "Nie mam ich...";
				link.l2.go = "zpq_sld2_3";
			}
		break;
		case "zpq_sld2_3":
			dialog.text = "To twój los - umrzeć młodo z powodu swojej chciwości. Zbyt niebezpiecznie jest pozwolić ci pozostać przy życiu.";
			link.l1 = "Taka pewność siebie.";
			link.l1.go = "zpq_sld2_4";
		break;
		case "zpq_sld2_3_1":
			dialog.text = "Ha-ha, twój los to umrzeć z powodu twojej chciwości. To nam pasuje, nie chcemy się dzielić.";
			link.l1 = "Ta twoja chciwość cię zgubi...";
			link.l1.go = "zpq_sld2_4";
		break;
		case "zpq_sld2_4":
			dialog.text = "Hej, chłopaki!! Załóżcie mu worek na głowę!";
			link.l1 = "Cóż, to był twój wybór...";
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
			dialog.text = "Ładnie. Daj je i zmykaj, kapitanie!";
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
