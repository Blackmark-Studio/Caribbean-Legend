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
			// Addon 2016-1 Jason пиратскаЯ линейка
			if (CheckAttribute(pchar, "questTemp.Mtraxx") && pchar.questTemp.Mtraxx == "silk_2")
            {
                link.l1 = "Figyelj, mester, te itt hajókat építesz, nem? És vitorlákat is cserélünk... nem gondoltál már... valami jobb vitorlavászon anyagra?";
                link.l1.go = "mtraxx";
			}
		break;
		
		// Addon 2016-1 Jason пиратскаЯ линейка
		case "mtraxx":
            dialog.text = "Rejtvényekben beszélsz, uram... Beszélj ôszintén, mi szél hozta ide? Semmi ok az aggodalomra, én nem vagyok valami tollforgató, és ez itt nem egy vámház.";
			link.l1 = "Ah, örülök, hogy egy hullámhosszon vagyunk! Selyem vitorlavászon, uram. Ha jól tudom, nincs jobb anyag a vitorlákhoz, ha a sebesség a fontos.";
			link.l1.go = "mtraxx_1";
		break;
		
		case "mtraxx_1":
            dialog.text = "Nem csak a sebesség, hanem az is, hogy képes legyen a széllel vitorlázni. Hajóselymet kínál megvételre? Valóban értékes szállítmány. De van egy akadály: egyszerûen nem tudom, hogyan használhatnám fel a gyártásban. Érti, amit mondok? Egy ilyen anyag nagyon különleges képességeket és készségeket igényel, amelyek nekem nem állnak rendelkezésemre. Hogy ôszinte legyek, az én hajógyáram egészen másra specializálódott, ha önök az orosz cárságból származó köteleket ajánlottak volna nekem, szívesen megvenném mindet, nem számít az ára. Nekünk állandóan szükségünk van kötelekre, azonban a hajóselyemre itt nincs kereslet, sajnálom!";
			link.l1 = "Hm. Értem. Köszönöm az idejét, mester. Sok szerencsét!";
			link.l1.go = "mtraxx_2";
		break;
		
		case "mtraxx_2":
            DialogExit();
			AddQuestRecord("Roger_2", "4");
			pchar.questTemp.Mtraxx = "silk_3";
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
