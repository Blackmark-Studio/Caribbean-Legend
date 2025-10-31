// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat("A "+ GetCityName(npchar.city) +" összes pletykája az Ön rendelkezésére áll. Mit szeretnél megtudni?",
                          "Éppen errôl beszéltünk. Biztos elfelejtette...", "Ma már harmadszor beszélsz valamilyen kérdésrôl...",
                          "Ismétled ugyanazt, mint egy papagáj...", "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("Tudod, " + NPChar.name + ", talán legközelebb.", "Rendben, valamiért elfelejtettem...",
                      "Igen, ez tényleg a harmadik alkalom...", "Igen...", npchar, Dialog.CurrentNode);
			link.l1.go = "exit";
			if (CheckAttribute(pchar, "questTemp.Guardoftruth") && pchar.questTemp.Guardoftruth == "portprince")
			{
				link.l1 = "Mondd csak, megfordult mostanában a kolóniádnál egy 'Santa Margarita' nevû gálya? Talán egy magánhajós zsákmányaként?";
                link.l1.go = "guardoftruth";
			}
			//--> Украденное воспоминание
			if (CheckAttribute(pchar, "questTemp.UV_DialogCitizen"))
			{
				link.l1 = "Járt itt mostanában Tristan Renier?";
				link.l1.go = "UV_DialogTavern";
			}
			//<-- Украденное воспоминание
		break;
		
		case "guardoftruth":
			dialog.text = "Haver, elég ritkán fordul elô, hogy valaki megáll a kolóniánkon zsákmánnyal, és még nem láttunk ilyen nevû gályát. Hispaniola egy vad sziget, mi pedig egy kis kolónia vagyunk. Csend van itt. A felvidéki kalózokkal kereskedünk tehénbôrökért és szárított marhahúsért. A kalózok nem szoktak errefelé lófrálni, bordélyházaink sincsenek, és a spanyolok a közelben vannak. Menj és keresd a gályádat máshol.";
			link.l1 = "Értem. Köszönöm a tanácsot!";
			link.l1.go = "exit";
			AddQuestRecord("Guardoftruth", "7");
			pchar.questTemp.Guardoftruth = "tortuga";
		break;
		
		//--> Украденное воспоминание
		case "UV_DialogTavern":
			dialog.text = "Renier? Igen, nem csak járt itt, de nem is ment el. Kivett egy szobát.";
			link.l1 = "A szerencse rám mosolyog! A jó kapitánnyal való üzletem nem tûr halasztást - a magánéletének engednie kell a szükségnek. Melyik szobában találom?";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("UV_GoldSeagull_RoomInTavern");
			DelLandQuestMark(npchar);
		break;
		//<-- Украденное воспоминание

	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
