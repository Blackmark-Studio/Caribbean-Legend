// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
	bool bOk;
	switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat("Gyerünk, mit akarsz?",
                          "Épp errôl beszéltünk. Biztos elfelejtetted...", "Ma már harmadszor beszélsz valami kérdésrôl...",
                          "Figyelj, ez egy bolt. Az emberek itt vásárolnak. Ne zavarjon!", "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("Tudod, " + NPChar.name + ", talán legközelebb.", "Rendben, valamiért elfelejtettem...",
                      "Igen, ez tényleg a harmadik alkalom...", "Hm, nem fogom...", npchar, Dialog.CurrentNode);
			link.l1.go = "exit";
			if(CheckAttribute(pchar, "questTemp.Tieyasal") && pchar.questTemp.Tieyasal == "begin" && !CheckAttribute(npchar, "quest.Tieyasal"))
			{
				link.l1 = "Figyelj, "+npchar.name+", láttad mostanában Miguel Dichosót az Isla Tesorón?";
				link.l1.go = "tieyasal";
			}
			// Addon 2016-1 Jason пиратскаЯ линейка
			if(CheckAttribute(pchar, "questTemp.Mtraxx") && pchar.questTemp.Mtraxx == "pasq_start")
			{
				link.l1 = ""+npchar.name+", Marcus Tyrex nevében vagyok itt. Azt mondta, hogy szükséged van egy emberre egy munkához.";
				link.l1.go = "mtraxx";
			}
			if(CheckAttribute(pchar, "questTemp.Mtraxx") && pchar.questTemp.Mtraxx == "pasq_win")
			{
				link.l1 = ""+npchar.name+", a 'Rosbohom' megtalálták és elfogták. Elkezdhetjük a kirakodást és a számolást?";
				link.l1.go = "mtraxx_5";
			}
		break;
				
		// город майя
		case "tieyasal":
			dialog.text = "Igen, már megtettem. Itt vásárolt ellátmányt a hajójának. Egyébként nemrégen volt. Szó szerint pár nappal maradtatok le egymásról. Egyébként lehet, hogy még mindig itt van a településen. Tudja, én nem kémkedek emberek után. Kérdezôsködj még egy kicsit, és ki tudja, talán megtalálod a donodat.";
			link.l1 = "Rendben. Rendben. Köszönöm az infót!";
			link.l1.go = "tieyasal_1";
		break;
		
		case "tieyasal_1":
			DialogExit();
			npchar.quest.tieyasal = "true";
		break;
		
		// Addon 2016-1 Jason пиратскаЯ линейка
		case "mtraxx":
			pchar.quest.Mtraxx_PasqualeLate.over = "yes";
            dialog.text = "Pontosan! Jó, hogy idôben érkeztél. Most pedig hadd mondjam el a lényeget...";
			link.l1 = "Csupa fül vagyok.";
			link.l1.go = "mtraxx_1";
		break;
		
		case "mtraxx_1":
			string sTemp = GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.questTemp.Mtraxx.Crdn.Ship), "Name")));
            dialog.text = "Ebben a pillanatban egy "+sTemp+", a 'Rosbohom', nevû holland hajó érkezik a vizeinkre egy ôrhajóval együtt. Ébenfával van megrakodva, és Willemstadból indul, hogy találkozzon egy másik ôrhajóval, hogy biztosítsa a biztonságos utat Európába. Nem tudom, milyen útvonalon megy, Sint Maartenen vagy Espanyolon keresztül, de ismerem a találkozási pontjuk koordinátáit\nA küldetésed az, hogy ott megtaláld a hollandokat, szállj fel a kereskedôre, és juttasd el hozzám a rakományát. Fizetni fogok, amint a rakományt leszállították.";
			link.l1 = "Értettem. Idôpont és helyszín?";
			link.l1.go = "mtraxx_2";
		break;
		
		case "mtraxx_2":
			int i = sti(pchar.questTemp.Mtraxx.Crdn.minN2)-10;
			int n = sti(pchar.questTemp.Mtraxx.Crdn.minW2)-10;
            dialog.text = ""+sti(pchar.questTemp.Mtraxx.Crdn.degN)+" "+i+" Észak és "+sti(pchar.questTemp.Mtraxx.Crdn.degW)+" "+n+" Nyugat. Valahol délre vagy délnyugatra kell lennie az Isla Tesorótól, én nem értek hozzá, nem vagyok tengerész, de te igen. Körülbelül öt napotok van a feladatra.";
			link.l1 = "Megjegyeztem... Értettem. Akkor ne vesztegessük az idôt!";
			link.l1.go = "mtraxx_3";
		break;
		
		case "mtraxx_3":
            dialog.text = "Isten éltessen, kapitány. Várni fogom magát és a rakományt.";
			link.l1 = "...";
			link.l1.go = "mtraxx_4";
		break;
		
		case "mtraxx_4":
           DialogExit();
		   pchar.questTemp.Mtraxx = "pasq_convoy";
		   i = sti(pchar.questTemp.Mtraxx.Crdn.minN2)-10;
           n = sti(pchar.questTemp.Mtraxx.Crdn.minW2)-10;
		   AddQuestRecord("Roger_4", "3");
		   AddQuestUserData("Roger_4", "sShip", GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.questTemp.Mtraxx.Crdn.Ship), "Name")+ "Gen")));
		   AddQuestUserData("Roger_4", "sdegN", sti(pchar.questTemp.Mtraxx.Crdn.degN));
		   AddQuestUserData("Roger_4", "sminN", i);
		   AddQuestUserData("Roger_4", "sdegW", sti(pchar.questTemp.Mtraxx.Crdn.degW));
		   AddQuestUserData("Roger_4", "sminW", n);
		   SetFunctionTimerCondition("Mtraxx_PasqualeTimeConvoy", 0, 0, 6, false);
		   SetFunctionTimerCondition("Mtraxx_PasqualeConvoyOver", 0, 0, 7, false);
		break;
		
		case "mtraxx_5":
			iTotalTemp = GetSquadronGoods(pchar, GOOD_EBONY);
			if (iTotalTemp < 1)
			{
				dialog.text = "Viccelsz velem, fiatalember? A rakterében nincs egyetlen ébenfa deszka sem! Ez egy szemtelen trükk! Tûnjön el innen! Errôl tájékoztatom Marcust! Kifelé!";
				link.l1 = "Hm...";
				link.l1.go = "mtraxx_6";
				break;
			}
			if (iTotalTemp < makeint(sti(pchar.questTemp.Mtraxx.Crdn.Ebony)/4))
			{
				dialog.text = "Viccelsz velem fiú? A rakteredben csak néhány ébenfa szilánk van! Ez egy szemtelen trükk! Takarodj innen! Errôl tájékoztatom Marcust! Kifelé!";
				link.l1 = "Hm...";
				link.l1.go = "mtraxx_6";
				break;
			}
			if (iTotalTemp < sti(pchar.questTemp.Mtraxx.Crdn.Ebony)-20)
			{
				dialog.text = "A Rosbohomnak legalább "+FindRussianQtyString(sti(pchar.questTemp.Mtraxx.Crdn.Ebony))+" ébenfa volt. Miért hoztál nekem kevesebbet?";
				link.l1 = "Hát... tudod, meg kellett szabadulnom egy részétôl a harc során. Plusz a patkányok, átkozottak...";
				link.l1.go = "mtraxx_7";
				break;
			}
            dialog.text = "Nagyon jó. Mennyi van nálad? "+FindRussianQtyString(iTotalTemp)+"? Pompás! 150 pezót fizetek egy darabért.";
			link.l1 = "150 darab pesó? Gondolom az ébenfa sokkal többe kerül.";
			link.l1.go = "mtraxx_10";
		break;
		
		case "mtraxx_6":
           DialogExit();
		   pchar.questTemp.Mtraxx = "pasq_angry";
		   DoQuestReloadToLocation("Pirates_town", "reload", "reload6", "");
		   AddQuestRecord("Roger_4", "8");
		   CloseQuestHeader("Roger_4");
		   QuestSetCurrentNode("Terrax", "mtraxx_34");
		break;
		
		case "mtraxx_7":
            dialog.text = "Patkányok? Nos, nos, nos... De rendben. 100 pezó darabonként és szabadon távozhat.";
			link.l1 = "Csak 100 pezó? Ez rablás!";
			link.l1.go = "mtraxx_8";
		break;
		
		case "mtraxx_8":
			AddMoneyToCharacter(pchar, iTotalTemp*100);
			RemoveCharacterGoods(pchar, GOOD_EBONY, iTotalTemp);
            dialog.text = "A rablás a maga mestersége, kapitány, én egy egyszerû kereskedô vagyok. Fogd a pénzed, és ne vitatkozzunk tovább, már így is jó pénzt kerestél azzal, hogy a rakományom egy részét máshol adtad el.";
			link.l1 = "Akkor baszódj meg!";
			link.l1.go = "mtraxx_9";
		break;
		
		case "mtraxx_9":
           DialogExit();
		   pchar.questTemp.Mtraxx = "pasq_fail";
		   AddQuestRecord("Roger_4", "8");
		   CloseQuestHeader("Roger_4");
		   QuestSetCurrentNode("Terrax", "mtraxx_34");
		break;
		
		case "mtraxx_10":
            dialog.text = "És igaza van, kapitány, de elôbb próbálja meg eladni a lopott árut, és meglátom, mennyit fizetnek érte a többi kereskedô. Az önnek ajánlott ár nagyon magas. Másodszor, ez az én nyomom volt, egyedül sosem találnád meg azt a karavánt, ráadásul más értékek és áruk is voltak rajta, és én nem tartok igényt rájuk. Harmadszor, Marcus Tyrex szemében a legjobb krediteket adom neked, és ez sokba kerül, hidd el. És végül negyedszer, egy szegény kereskedônek valahogy meg kell élnie.";
			link.l1 = "Hûha! Vissza kell vonulnom az ilyen érvekkel szemben "+npchar.name+". Számoljunk!";
			link.l1.go = "mtraxx_11";
		break;
		
		case "mtraxx_11":
			AddMoneyToCharacter(pchar, iTotalTemp*150);
			RemoveCharacterGoods(pchar, GOOD_EBONY, iTotalTemp);
            dialog.text = "Pompás. Fogd az érméket. Örömömre szolgált. Idônként nézzen be a boltomba. Legyen szerencséd a tengerben!";
			link.l1 = "Neked pedig a kereskedelmedben...";
			link.l1.go = "mtraxx_12";
		break;
		
		case "mtraxx_12":
           DialogExit();
		   pchar.questTemp.Mtraxx = "pasq_complete";
		   AddQuestRecord("Roger_4", "9");
		   pchar.quest.mtr_pasq_fin.win_condition.l1 = "location";
		   pchar.quest.mtr_pasq_fin.win_condition.l1.location = "Pirates_town";
		   pchar.quest.mtr_pasq_fin.function = "Mtraxx_PasqualeJeffry";
		   bDisableFastReload = true;
		break;
	}
	UnloadSegment(NPChar.FileDialog2);
}
