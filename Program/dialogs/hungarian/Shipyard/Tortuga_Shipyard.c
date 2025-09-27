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
			if (CheckAttribute(pchar, "questTemp.Guardoftruth") && pchar.questTemp.Guardoftruth == "tortuga1")
			{
				link.l1 = "Egy Gaius Marchais-t keresek. Az utolsó dolog, amit hallottam róla, az volt, hogy kikötötte a gályáját 'Santa Margarita' hogy megjavítsa...";
                link.l1.go = "guardoftruth";
			}
		break;
		
		case "guardoftruth":
			dialog.text = "A saját gályája? Ho-ho, ez egy jó vicc, kapitány. Gaius Marchaisnak csak egy félholt sloopja volt... egy gályát zsákmányolt zsákmányként, miután úgy döntött, hogy magánzó lesz. Szerencsés ördög, elsô rajtaütés és egy ilyen trófea\nJó pénzt ajánlottam érte, de visszautasította, képzeld! Ehelyett eladta szánalmas sloopját egy kis összegért, és a gálya javítására fordította! Új vitorlák, új színek és egy új név, ami általában nem jó jel\nS persze, a név túlságosan pápista volt, de a lányomat is Margaritának hívják, szóval azt hiszem, végül is rendben volt... Azt mondta, hogy elege van az erôszakból, ezért kereskedô lesz. És volt szerencséje...";
			link.l1 = "A kereskedelem, gondolom, nyugodt lenne, de a pápista gályákat nem szokták zsákmányolni a sloopok. És most mi a hajója új neve?";
			link.l1.go = "guardoftruth_1";
		break;
		
		case "guardoftruth_1":
			dialog.text = "'Admirable'... Nem csoda! Csak úgy rohangált az új gályája körül, mintha menyasszonyért hajkurászna, egyszerûen nem tudta abbahagyni a csodálását.";
			link.l1 = "Értem. Gaius most is a Tortugán van?";
			link.l1.go = "guardoftruth_2";
		break;
		
		case "guardoftruth_2":
			dialog.text = "Nem. Elindult az új hajójával, és még mindig nem tért vissza Tortugára. Nem tudom, hová tartott, így nem tudok segíteni neked ebben az ügyben.";
			link.l1 = "Micsoda kellemetlenség... Tényleg szükségem van rá. Még egy kör italt is meg kéne innunk az ô 'admirable' shipjére. Mindenesetre köszi az információt.";
			link.l1.go = "guardoftruth_3";
		break;
		
		case "guardoftruth_3":
			dialog.text = "Ó, semmi gond. Ugorjon be újra, kapitány. És ne felejtse el, hogy itt mindig van egy szabad hely a hajójának, ha javításra van szüksége!";
			link.l1 = "...";
			link.l1.go = "exit";
			AddQuestRecord("Guardoftruth", "9");
			pchar.questTemp.Guardoftruth = "tortuga2";
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
