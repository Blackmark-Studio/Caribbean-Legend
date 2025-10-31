// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{

	switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat("Gyerünk, mit akarsz?",
                          "Épp errôl beszéltünk. Biztos elfelejtetted...", "Ma már harmadszor beszélsz valami kérdésrôl...",
                          "Figyelj, ez egy bolt. Az emberek itt vásárolnak. Ne zavarjon!", "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("Tudod, " + NPChar.name + ", talán legközelebb.", "Rendben, valamiért elfelejtettem...",
                      "Igen, ez tényleg a harmadik alkalom...", "Hm, nem fogom...", npchar, Dialog.CurrentNode);
			link.l1.go = "exit";
			//Голландский гамбит
			if (CheckAttribute(pchar, "questTemp.HWIC.Eng") && pchar.questTemp.HWIC.Eng == "GotoBridgetown" && !CheckAttribute(npchar, "quest.HWICTalked"))
            {
                link.l1 = "Figyelj, egy kismadár azt mondta nekem, hogy a vörös fa és a kakaó ára Belize-ben hamarosan fel fog szökni. Nemrég jó üzletet kötöttem, és megtömtem az erszényemet dublonnal, he-he... Szeretnék beszerezni ebbôl az áruból. Számíthatok kedvezményre?";
                link.l1.go = "StoreDone";
            }
			if (CheckAttribute(pchar, "questTemp.Guardoftruth") && pchar.questTemp.Guardoftruth == "barbados1")
			{
				link.l1 = "A 'Admirable' nevû gálya nemrég kikötött a kolóniádnál Gaius Marchais kapitány parancsnoksága alatt. Mondja, lehet, hogy lôszert vagy árut vásárolt itt, hogy továbbértékesítse?";
                link.l1.go = "guardoftruth";
			}
		break;
		
		case "StoreDone":
			dialog.text = "Nos, uram, ha a szállítmány valóban nagy, akkor természetesen megbeszélhetünk egy ésszerû árengedményt.";
			link.l1 = "Csodálatos! Úgy hallottam, hogy egy új fluyt fog megjelenni eladásra a hajógyárban bármelyik nap. Megvárom és megveszem azt a hajót. Hiába szedtem le az összes ágyút a briggrôl, még mindig nincs elég hely a raktérben a sok árunak! Majd késôbb benézek!";
			link.l1.go = "exit";	
			npchar.quest.HWICTalked = "true";
			pchar.questTemp.HWIC.Eng.BridgeCounter = sti(pchar.questTemp.HWIC.Eng.BridgeCounter)+1;
			AddQuestRecord("Holl_Gambit", "2-11");
			DelLandQuestMark(npchar);
			if (sti(pchar.questTemp.HWIC.Eng.BridgeCounter) == 7) 
			{
				AddQuestRecord("Holl_Gambit", "2-6");
				pchar.questTemp.HWIC.Eng = "SeekVanBerg";
				pchar.quest.GotoBridgetownOver.over = "yes";//снять таймер
				DelMapQuestMarkCity("Bridgetown");
				pchar.quest.VanBergAttack_Check.win_condition.l1 = "MapEnter";
				pchar.quest.VanBergAttack_Check.function = "VanBergAttackCheck";
			}
		break;
		
		case "guardoftruth":
			dialog.text = "Ha! Emlékszem arra a furcsa fickóra! Bízott valami ostoba pletykában, miszerint Guadeloupe-nak égetô szüksége lenne vaníliára, mert európai kereskedôk nagy karavánja fog ott megállni, hogy annyi fûszert vegyen, amennyit csak elbír\nHavonta hallok ilyen ostobaságokat, de Marchais ezt a legkomolyabban vette. Egy hetet töltött itt, azt mondta, hogy gyûjtsek annyi vaníliát, hogy megteljen a raktere\nÚgy tûnik, minden pénzérmét erre költötte. Sajnálom azt az embert, de nem tudom megakadályozni, hogy a férfiak megôrüljenek, ha akarnak.";
			link.l1 = "Szóval, lehet, hogy most Guadeloupe-ban van?";
			link.l1.go = "guardoftruth_1";
		break;
		
		case "guardoftruth_1":
			dialog.text = "Valószínûleg. Mert továbbra is várni fog a fantáziabeli 'kereskedôire' Krisztus második eljöveteléig, és csak pénzt veszít a vanília eladásával. Ha bölcs, akkor addig marad Basse-Terre-ben, amíg a vanília iránti kereslet meg nem szökik, vagy amíg biztosan nem talál egy másik helyet, ahol nagyobb szükség van rá.";
			link.l1 = "Igenis. Köszönöm, sokat segítettél nekem!";
			link.l1.go = "guardoftruth_2";
		break;
		
		case "guardoftruth_2":
			DialogExit();
			AddQuestRecord("Guardoftruth", "14");
			pchar.questTemp.Guardoftruth = "guadeloupe";
			pchar.quest.GuardOT_guadeloupe.win_condition.l1 = "location";
			pchar.quest.GuardOT_guadeloupe.win_condition.l1.location = "guadeloupe";
			pchar.quest.GuardOT_guadeloupe.function = "GuardOT_CreateTwoShips";
		break;
	}
	UnloadSegment(NPChar.FileDialog2);
}
