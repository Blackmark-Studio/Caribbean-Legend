// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("Milyen kérdések, "+ GetSexPhrase("fiam","lányom") +"?", "Kérdezz csak, hallgatlak..."), "Figyelek, beszélj most, "+ GetSexPhrase("fiam","lányom") +"...", "Harmadszorra, "+ GetSexPhrase("fiam","lányom") +", kérd, amire szükséged van.",
                          "Egy lelkésznek rengeteg munkája van, és te eltereled a figyelmemet, "+ GetSexPhrase("fiam","lányom") +"...", "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("Meggondoltam magam...", "Most nem, atyám..."), "Nincs mit mondanom, elnézést kérek.",
                      "Megkérdezem, de késôbb. Bocsásson meg, atyám.", "Bocsásson meg, szent atyám...", npchar, Dialog.CurrentNode);
			link.l1.go = "exit";		
			if (CheckAttribute(pchar, "questTemp.Guardoftruth") && pchar.questTemp.Guardoftruth == "utensil" && !CheckAttribute(npchar, "quest.utensil"))
			{
				link.l1 = "Egy szokatlan ügy miatt jöttem hozzád, szent atyám. Egy Guy Marchais nevû kalóz nemrég egy nagyon értékes tárgyat ajándékozott a plébániádnak. Egy arany mellkereszt volt, melybe lazurit volt ágyazva. Igaz ez?";
                link.l1.go = "guardoftruth";
			}
		break;
		
		case "guardoftruth":
			dialog.text = "Ó, igen, fiam!  Ez a legjobb tárgy a plébániánkon. Egész életemben nem láttam még ilyen pompát! De miért kérdezed, fiam? Miért érdekel téged ez a kereszt?";
			link.l1 = "Szentatya, tudom, hogy ez nem fog tetszeni neked, de ezt a keresztet egy másik plébániáról lopták el, és a papot közben meggyilkolták. Az az ember, aki ezt a tárgyat bemutatta neked, egy gyilkos.";
			link.l1.go = "guardoftruth_1";
		break;
		
		case "guardoftruth_1":
			dialog.text = "Mindannyian vétkezünk, fiam, és egy lelkész meggyilkolása súlyos vád. Van rá bizonyítéka? Melyik plébániáról lopták el ezt a keresztet?";
			link.l1 = "Az én szavam nem elég bizonyíték? Ezt a keresztet a santiagói plébániáról lopták el, és vissza kell szolgáltatni.";
			link.l1.go = "guardoftruth_2";
		break;
		
		case "guardoftruth_2":
			dialog.text = "Santiago? Az nem egy spanyol város? Fiam, meglepsz engem...";
			link.l1 = "Szent Atyám, mindenki egyenlô Isten elôtt. A spanyolok ugyanolyan keresztények, mint mi, és a nemzetek közötti nézeteltérések nem vonatkozhatnak a hívôk' érzéseire. Könyörgöm, hogy ezt a keresztet juttassa vissza a santiagói plébániára.";
			link.l1.go = "guardoftruth_3";
		break;
		
		case "guardoftruth_3":
			dialog.text = "Fiam, nem érted, hogy ez a kereszt a szeretô keresztények ajándéka a mi plébániánk számára?! Nem, fiam, nem tehetem meg, amit kérsz.";
			link.l1 = "Nem érdekel, hogy vér folyt ki ezért a keresztért? Egy pap vére, spanyol vagy nem spanyol, nem számít.";
			link.l1.go = "guardoftruth_4";
		break;
		
		case "guardoftruth_4":
			dialog.text = "Fiam, nem mutattál semmilyen bizonyítékot, és nem hihetek vakon a szavadnak. A kereszt a plébániánkon marad. Ez a végsô döntésem. Egyébként is, a spanyolok megsegítésére tett erôfeszítéseid ebben az ügyben nagyon zavarnak engem.";
			link.l1 = "Legyen úgy, Isten önnel, szent atya...";
			link.l1.go = "guardoftruth_5";
		break;
		
		case "guardoftruth_5":
			DialogExit();
			npchar.quest.utensil = "true";
			pchar.questTemp.Guardoftruth.Baster_church = "seek";
			AddQuestRecord("Guardoftruth", "27");
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
