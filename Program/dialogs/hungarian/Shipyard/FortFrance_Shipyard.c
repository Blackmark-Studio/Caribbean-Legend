// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("Milyen kérdései vannak?", "Miben segíthetek?"), "Nemrég megpróbált feltenni nekem egy kérdést...", "Ilyen kíváncsi emberekkel még nem találkoztam sem a hajógyáramban, sem máshol ebben a városban.",
                          "Mi ez a sok kérdés? Az én munkám az, hogy hajókat építsek. Gondoskodjunk errôl.", "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("Meggondoltam magam...", "Jelenleg nincs mirôl beszélnem."), "Umph, hová tûnt a memóriám...",
                      "Hm, nos...", "Folytasd csak...", npchar, Dialog.CurrentNode);
			link.l1.go = "exit";
			// Addon-2016 Jason ”ЊЉ-Њартиника
			if (CheckAttribute(pchar, "questTemp.FMQM") && pchar.questTemp.FMQM == "begin")
            {
                link.l1 = "Az embered mondta, hogy látni akarsz. Csupa fül vagyok.";
                link.l1.go = "FMQM";
            }
			if (CheckAttribute(pchar, "questTemp.FMQM") && pchar.questTemp.FMQM == "oil" && GetSquadronGoods(pchar, GOOD_OIL) >= 50)
            {
                link.l1 = "Elvégeztem a munkát. "+FindRussianQtyString(GetSquadronGoods(pchar, GOOD_OIL))+" hordónyi gyanta van a raktérben.";
                link.l1.go = "FMQM_9";
            }
		break;
		
		// Addon-2016 Jason ”ЊЉ-Њартиника
		case "FMQM":
			pchar.quest.FMQM_Denial.over = "yes";
			dialog.text = "Igen-igen, kapitány "+GetFullName(pchar)+". Láttam, hogy a hajójuk belép a kikötônkbe, és azonnal elküldtem a munkásomat önhöz. Egyenesen az üzletre tehát: Ön újonc, de azt mondják, hogy már tapasztalt tengerész lett, és a szerencse az Ön oldalán áll. Ezért van egy üzleti ajánlatom az Ön számára.";
			link.l1 = "Érdekes! Rajta, mondd el!";
			link.l1.go = "FMQM_1";
			DelLandQuestMark(npchar);
		break;
		
		case "FMQM_1":
			dialog.text = "Hallottál már a különleges gyantáról, amelyet a spanyolok Trinidad szigetén állítanak elô? Ez egy ritka, stratégiai értékû nyersanyag, amelyet a hajók burkolatának megerôsítésére használnak. Minden egyes hordó borsos összegbe kerül, mert a spanyolok az összes gyantát a haditengerészetük igényeihez irányítják. Minden gyarmati hatóság ellenôrzés alatt tartja ennek az árunak a kereskedelmét, egyszerûen fogalmazva, ez tiszta csempészáru\nEz a gyanta egy különleges megrendeléshez kell. Természetesen a mi boltunkban nincs, ugyanez elmondható a helyi katonai raktárakról is, vagy egyszerûen nem akarták eladni. Ez igazából lényegtelen. Ami lényeges, az az, hogy szükségem van a gyantára, és tudom, hol lehet beszerezni. Már csak egy kapitányra van szükségem, aki jól érzi magát a beszállással kapcsolatban.";
			link.l1 = "Azt hiszem, kezdem érteni, mire akarsz kilyukadni...";
			link.l1.go = "FMQM_2";
		break;
		
		case "FMQM_2":
			dialog.text = "Pompás. Figyeljetek, egy kisebb kereskedelmi konvoj Trinidad közelében, pontosabban San Jose kikötôjében tartózkodott. Az egyik hajó egy jó adag gyantát szállít, ugyanazt a gyantát, amire nekem is nagy szükségem van. Többet is elmondok, ha tetszik az ötlet, hogy kifosztjuk nemzetünk ellenségeit. Mi a döntésed?";
			link.l1 = "Tetszik az ajánlatod. Kész vagyok kipróbálni.";
			link.l1.go = "FMQM_3";
			link.l2 = "Kihagyom, monsieur. A hajóm és a legénységem jelenleg nincs a legvirágosabb állapotban.";
			link.l2.go = "FMQM_exit";
		break;
		
		case "FMQM_exit":
			dialog.text = "Rendben, joga van hozzá, hogy azt tegye, amit akar. Elnézést, hogy elraboltam az idejét, kapitány.";
			link.l1 = "Viszontlátásra.";
			link.l1.go = "FMQM_exit_1";
		break;
		
		case "FMQM_exit_1":
			DialogExit();
			pchar.questTemp.FMQM = "fail";
			AddQuestRecord("FMQ_Martinique", "3");
			CloseQuestHeader("FMQ_Martinique");
		break;
		
		case "FMQM_3":
			string sTemp = "barquentin";
			if (MOD_SKILL_ENEMY_RATE < 7) sTemp = "barque";// Addon 2016-1 Jason пиратскаЯ линейка
			dialog.text = "Akkor figyeljetek: a konvoj három hajóból áll, a gyanta egyebek mellett egy "+sTemp+" nevû 'Bensecho'. árun lesz, ez a fô célpontotok. Mint már mondtam, a spanyolok San Jose - Trinidad, San Juan - Puerto Rico felé hajóznak. Holnap fognak kihajózni, így szabadon választhatjátok meg, hogy hol támadjátok meg ôket.";
			link.l1 = "Megvan. Mi a helyzet a jutalommal?";
			link.l1.go = "FMQM_4";
		break;
		
		case "FMQM_4":
			dialog.text = "Engem csak a gyanta érdekel. Tizenöt aranydublont fizetek minden egyes hordóért. Információim szerint a 'Bensecho' körülbelül száz hordót szállít.";
			link.l1 = "Szent tehén! Ez aztán a nagy összeg!";
			link.l1.go = "FMQM_5";
		break;
		
		case "FMQM_5":
			dialog.text = "Igen. Már mondtam, hogy ez a bizonyos áru nagyon drága és ritka.";
			link.l1 = "Azt is mondta, hogy ez csempészáru.";
			link.l1.go = "FMQM_6";
		break;
		
		case "FMQM_6":
			dialog.text = "Ne aggódjon, nem lesz szükség arra, hogy a boltba vagy a csempészekhez vigye. Gyere el hozzám, ha végeztünk a munkával, a hajódat a hajógyáramban fogjuk kikötni javítás céljából, majd éjszaka titokban kirakodjuk az összes rakományt. Senki sem fog gyanút fogni.";
			link.l1 = "Elôre gondolkodsz, mester. Rendben van. Ne vesztegessük az idôt. Már úton vagyok, hogy kihajózzak.";
			link.l1.go = "FMQM_7";
		break;
		
		case "FMQM_7":
			dialog.text = "Isten éltessen, kapitány.";
			link.l1 = "...";
			link.l1.go = "FMQM_8";
		break;
		
		case "FMQM_8":
			DialogExit();
			pchar.questTemp.FMQM = "convoy";
			AddQuestRecord("FMQ_Martinique", "4");
			SetFunctionTimerCondition("FMQM_ConvoyStart", 0, 0, 1, false);
		break;
		
		case "FMQM_9":
			dialog.text = "Kitûnô! Tegyük a hajót a dokkba, ahogy korábban megbeszéltük. Ma este kirakodjuk. Menj vissza a hajódra, hadd készítsem elô a pénzt.";
			link.l1 = "Csináljuk ezt.";
			link.l1.go = "FMQM_10";
			DelLandQuestMark(npchar);
		break;
		
		case "FMQM_10":
			pchar.quest.FMQM_Late.over = "yes";
			DialogExit();
			InterfaceStates.Buttons.Save.enable = false;
			chrDisableReloadToLocation = true;
			pchar.GenQuest.FrameLockEsc = true;
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], true);
			pchar.questTemp.FMQM = "remove_oil";
			pchar.questTemp.FMQM.Oil = "true";
			pchar.questTemp.FMQM.Qty = GetSquadronGoods(pchar, GOOD_OIL);
			DoQuestFunctionDelay("FMQM_WaitTime", 1.0);
			RemoveCharacterGoods(pchar, GOOD_OIL, GetSquadronGoods(pchar, GOOD_OIL));
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
